/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */ 
/*		--------------------------------------		      */ 
/*								      */
/*   file:	   grprint2.c					      */
/*   version:	   1.00.00					      */
/*   creation:	   14.4.93					      */
/*   author:	   G. Sander (Version 1.00.00-...)		      */ 
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */ 
/*   description:  Print bitmap into a file   			      */ 
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/


#ifndef lint
static char *id_string="$Id: grprint2.c,v 3.6 1995/02/08 11:11:14 sander Exp $";
#endif


/*
 *   Copyright (C) 1993-2005 Saarland University
 *
 *  This program and documentation is free software; you can redistribute 
 *  it under the terms of the  GNU General Public License as published by
 *  the  Free Software Foundation;  either version 2  of the License,  or
 *  (at your option) any later version.
 *
 *  This  program  is  distributed  in  the hope that it will be useful,
 *  but  WITHOUT ANY WARRANTY;  without  even  the  implied  warranty of
 *  MERCHANTABILITY  or  FITNESS  FOR  A  PARTICULAR  PURPOSE.  See  the
 *  GNU General Public License for more details.
 *
 *  You  should  have  received a copy of the GNU General Public License
 *  along  with  this  program;  if  not,  write  to  the  Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  The software is available per anonymous ftp at ftp.cs.uni-sb.de.
 *  Contact  sander@cs.uni-sb.de  for additional information.
 */


/* 
 * $Log: grprint2.c,v $
 * Revision 3.6  1995/02/08  11:11:14  sander
 * Distribution version 1.3.
 *
 * Revision 3.5  1994/12/23  18:12:45  sander
 * Manhatten layout added.
 * Option interface cleared.
 * infobox behaviour improved.
 * First version of fisheye (carthesian).
 * Options Noedge and nonode.
 *
 * Revision 3.4  1994/06/07  14:09:59  sander
 * Splines implemented.
 * HP-UX, Linux, AIX, Sun-Os, IRIX compatibility tested.
 * The tool is now ready to be distributed.
 *
 * Revision 3.3  1994/05/16  08:56:03  sander
 * shape attribute (boxes, rhombs, ellipses, triangles) added.
 *
 * Revision 3.2  1994/04/27  16:05:19  sander
 * Revert of page and margins added. Messages while waiting
 * added. Adaption to the new print-dialog box.
 *
 * Revision 3.1  1994/03/01  10:59:55  sander
 * Copyright and Gnu Licence message added.
 * Problem with "nearedges: no" and "selfloops" solved.
 *
 * Revision 2.2  1994/01/21  19:33:46  sander
 * VCG Version tested on Silicon Graphics IRIX, IBM R6000 AIX and Sun 3/60.
 * Option handling improved. Option -grabinputfocus installed.
 * X11 Font selection scheme implemented. The user can now select a font
 * during installation.
 * Sun K&R C (a nonansi compiler) tested. Some portabitility problems solved.
 *
 * Revision 2.1  1993/12/08  21:20:09  sander
 * Reasonable fast and stable version
 *
 *
 */

/************************************************************************
 *  This file allows to write the graph bitmap into a file. These routines
 *  are called, if the "export"-menu was selected. The supported formats
 *  are pbm-P4 format and ppm-P6 format.
 * 
 *  The implementation idea is a little bit ugly: We use the same 
 *  drawing driver "draw.c" and "drawlib.c" and only redefine the
 *  device dependent functions. This duplication of code ensures that
 *  the speed is reasonable. All global function names must be mapped
 *  to new names, otherwise we have linking conflicts.
 * 
 *  Basically, the following functions are in this file:
 *    print_pbm		      prints the B&W   bitmap into a PBM-file
 *    print_ppm		      prints the color bitmap into a PPM-file
 ************************************************************************/


/* Mapping of global names of draw.c, drawstr.c, drawlib.c
 * =======================================================
 */


#define INCLUDE_DRAW

#define draw_main      bm_draw_main
#define draw_one_node  bm_draw_one_node
#define gs_stringw     bm_stringw
#define gs_stringh     bm_stringh
#define gs_boxw        bm_boxw
#define gs_boxh        bm_boxh

#define gs_printstr          bm_printstr         
#define gs_calcstringsize    bm_calcstringsize  
#define gs_setto             bm_setto          
#define gs_setshrink         bm_setshrink        
#define gs_calctextboxsize   bm_calctextboxsize 
#define gs_anchornode        bm_anchornode        
#define gs_textbox           bm_textbox        
#define gs_reverttextbox     bm_reverttextbox 
#define gs_halfreverttextbox bm_halfreverttextbox  
#define gs_stringbox         bm_stringbox         
#define gs_calcrhombsize     bm_calcrhombsize
#define gs_rhomb             bm_rhomb       
#define gs_revertrhomb       bm_revertrhomb
#define gs_halfrevertrhomb   bm_halfrevertrhomb
#define gs_calctrianglesize  bm_calctrianglesize
#define gs_triangle          bm_triangle       
#define gs_reverttriangle    bm_reverttriangle
#define gs_halfreverttriangle bm_halfreverttriangle
#define gs_calcellipsesize   bm_calcellipsesize
#define gs_ellipse           bm_ellipse       
#define gs_revertellipse     bm_revertellipse
#define gs_halfrevertellipse bm_halfrevertellipse
#define gs_solidarrow        bm_solidarrow       
#define gs_dashedarrow       bm_dashedarrow     
#define gs_dottedarrow       bm_dottedarrow    
#define gs_line              bm_line
#define gs_rectangle         bm_rectangle
#define gs_actbackground     bm_actbackground

#define mystretch            bm_mystretch
#define myshrink             bm_myshrink
#define myxpos               bm_myxpos
#define myypos               bm_myypos
#define gs_stlimit           bm_stlimit
#define gs_shlimit           bm_shlimit


/* Includes, Prototypes, Variables
 * ===============================
 * We must include globals.h before everything, otherwise we cannot
 * define the prototypes.
 * Even if globals.h is included in draw.c and drawlib.c again, this
 * is correct, because of the include-security mechanism, that prevents
 * second inclusion of a file from having ugly effects.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

/* Prototypes
 * ----------
 */

static FILE *check_and_open_file  _PP((char *fname));

void bm_line            _PP((int fx,int fy,int tx,int ty,int c));
static void bm_rectangle       _PP((int x,int y,int w,int h,int c));

static void bw_point	       _PP(( int x, int y, int c));
static void bw_line            _PP((int fx,int fy,int tx,int ty,int c));
static void bw_rectangle       _PP((int x,int y,int w,int h,int c));
static void co_point	       _PP(( int x, int y, int c));
static void co_line            _PP((int fx,int fy,int tx,int ty,int c));
static void co_rectangle       _PP((int x,int y,int w,int h,int c));



/* Variables 
 * ---------
 */

/* from X11devpb.c */

extern int   act_output_type;
extern int   act_color_type;
extern int   act_ori_type;
extern int   act_paper_num;
extern float act_width;
extern float act_height;
extern float act_left_margin;
extern float act_right_margin;
extern float act_top_margin;
extern float act_bottom_margin;
extern int   act_xdpi;
extern int   act_ydpi;
extern float act_scaling;


/* Counter for the wait message */

static int wait_cntr;


/* horizontal and vertical length of the bitmap.
 * hlen % 8 should be 0.
 */

static int hlen,vlen;

/* Flag: 1, if output is landscape (rotated)
 */

static int rotated = 0;

/* Left margin and top margin in pixels. 
 */

static int leftmargin, topmargin;

/* The bitmap itself, where the output is prepared. 
 */

static unsigned char *bitmap=NULL;

/* Flag, wether pbm or ppm 
 */

static int pbm_flag;

/* Modules
 * -------
 * We use this ugly trick to reuse the files draw.c and drawlib.c 
 */
 
#include "draw.c"
#include "drawlib.c"
#include "grprint.h"


/*--------------------------------------------------------------------*/
/*  Print all nodes into a file                                       */
/*--------------------------------------------------------------------*/

/*  General driver
 *  ==============
 */

#ifdef ANSI_C
int print_pbm_or_ppm(char *fname,int a,int b,int c,int d)
#else
int print_pbm_or_ppm(fname, a, b, c, d)
char *fname;
int a, b, c, d;
#endif
{
        int form, da, db, dc, dd, st, sh, lm, tm;
        float xscale, yscale;

        assert(((act_output_type==1)||(act_output_type==2)));

        if (a>c)  { form = a; a = c; c = form; }
        if (b>d)  { form = b; b = d; d = form; }

	form = 0;
        switch (act_ori_type) {
        case 1: form = 0; break;
        case 2: form = 1; break;
        }

	lm = gstoint(act_left_margin/2.54 * act_xdpi);
	tm = gstoint(act_top_margin/2.54  * act_ydpi);

	st = gstoint(act_scaling * 1000);
	sh = 1000;


	da = gstoint((float)a*act_scaling);
	db = gstoint((float)b*act_scaling);
	dc = gstoint((float)c*act_scaling);
	dd = gstoint((float)d*act_scaling);

	switch (act_color_type) {
	case 1:
		return(print_ppm(fname,da,db,dc,dd,lm,tm,form,st,sh));
	case 3:
		return(print_pbm(fname,da,db,dc,dd,lm,tm,form,st,sh));
	}
	return(0);
}


/*  Print PBM-file
 *  ==============
 *  The region (a,b)-(c,d) is printed to the file.
 *  The scaling is st/sh. We return 1 on success.
 *  r = 1 means landscape (rotated), l and t are left and top margin.
 *
 *  The PBM-format is defined as follows (1989, 1991 by Jef Poskanzer)
 *
 *    - A "magic number" for identifying the  file  type. A  pbm
 *      file's magic number is the two characters "P4".
 *
 *    - Some whitespace (blanks, TABs, CRs, LFs).
 *
 *    - A width, formatted as ASCII characters in decimal. The 
 *      width is dividible by 8.
 *
 *    - Some whitespace.
 *
 *    - A height, again in ASCII decimal.
 *
 *    - 1 whitespace character (typically a newline).
 *
 *    - Width * height bits, each either 1 or 0,  starting  at
 *      the  top-left  corner  of the bitmap, proceeding in normal
 *      English reading order. The bits are stored eight per byte, 
 *      high bit first low bit last. A bit 1 means black, a bit 0
 *      means white.
 *
 *    - No whitespace is allowed in the bits section.
 */


#ifdef ANSI_C
int print_pbm(char *fname,int a,int b,int c,int d,
		int l,int t,int r,int st,int sh)
#else
int print_pbm(fname, a, b, c, d, l, t, r, st, sh)
char *fname;
int  a,b,c,d,l,t,r,sh,st;
#endif
{
	int Vs_xmin, Vs_ymin, Vs_xmax, Vs_ymax;
	int s_stretch, s_shrink, col;
	int i,j;
	FILE *f;

	pbm_flag = 1;

	f = check_and_open_file(fname);
	if (f==NULL)  return(0);

	rotated    = r;
	leftmargin = l;
	topmargin  = t;
	wait_cntr  = 0;

	assert((c>=a));
	assert((d>=b));

	if (rotated==1) {
		hlen = d-b+topmargin;	
		vlen = c-a+leftmargin; 
	}
	else {
		hlen = c-a+leftmargin; 
		vlen = d-b+topmargin;	
	}

	if ((hlen<=0)||(vlen<=0)) return(0);
	hlen = ((hlen+7)/8)*8;	/* align hlen to 8 */

	/* save old values */
	Vs_xmin = V_xmin;     Vs_ymin = V_ymin; 
	Vs_xmax = V_xmax;     Vs_ymax = V_ymax;
	s_shrink  = G_shrink; s_stretch = G_stretch;
	col       = colored;

	/* install printout values */
	V_xmin = a;     V_ymin = b;
	V_xmax = c;     V_ymax = d;
	G_shrink  = sh; G_stretch = st;
	colored   = 0;

	gs_wait_message('m');
	bitmap = (unsigned char *)malloc(hlen/8*vlen+vlen);
	gs_wait_message('M');
	if (!bitmap) Fatal_error("memory exhausted","");
	for (i=0; i<vlen; i++) {
		wait_cntr++;
		if (wait_cntr > 60)  { gs_wait_message('i'); wait_cntr = 0; }
		for (j=0; j<hlen/8; j++) bitmap[i*hlen/8+j] = 0;
	}

	/* draw bitmap */
	bm_draw_main();

	/* save PBM format into file */
	FPRINTF(f,"P4\n");
	FPRINTF(f,"%d %d\n",hlen,vlen);
	for (i=0; i<vlen; i++) {
		wait_cntr++;
		if (wait_cntr > 30)  { gs_wait_message('s'); wait_cntr = 0; }
		fwrite(&(bitmap[i*hlen/8]),1,hlen/8,f);
	}

	if (f) fclose(f);
	
	if (bitmap)  free(bitmap);
	bitmap = NULL;

	/* restore old values */
	V_xmin = Vs_xmin;     V_ymin = Vs_ymin;
	V_xmax = Vs_xmax;     V_ymax = Vs_ymax;
	G_shrink  = s_shrink; G_stretch = s_stretch;
	colored   = col;
	return(1);
}


/*  Print PPM-file
 *  ==============
 *  The region (a,b)-(c,d) is printed to the file.
 *  The scaling is st/sh. We return 1 on success.
 *  r = 1 means landscape (rotated), l and t are left and top margin.
 *
 *  The PPM-format is defined as follows (1989, 1991 by Jef Poskanzer)
 *
 *    - A "magic number" for identifying the  file  type. A  pbm
 *      file's magic number is the two characters "P6".
 *
 *    - Some whitespace (blanks, TABs, CRs, LFs).
 *
 *    - A width, formatted as ASCII characters in decimal. The 
 *      width is dividible by 8.
 *
 *    - Some whitespace.
 *
 *    - A height, again in ASCII decimal.
 *
 *    - Some whitespace.
 *
 *    - The maximum color-component value, again in ASCII decimal.
 *
 *    - 1 whitespace character (typically a newline).
 *
 *    - Width * height pixels, each  three plain bytes between 0 
 *      and the specified maximum value (<256), starting at the
 *      top-left  corner  of  the  pixmap,  proceeding  in  normal
 *      English  reading  order.   The three bytes for each pixel
 *      represent red, green, and blue, respectively; a value of 0
 *      means  that color is off, and the maximum value means that
 *      color is maxxed out.
 *
 *    - No whitespace is allowed in the bits section.
 */


#ifdef ANSI_C
int print_ppm(char *fname,int a,int b,int c,int d,
		int l,int t,int r,int st,int sh)
#else
int print_ppm(fname, a, b, c, d, l, t, r, st, sh)
char *fname;
int  a,b,c,d,l,t,r,sh,st;
#endif
{
	int Vs_xmin, Vs_ymin, Vs_xmax, Vs_ymax;
	int s_stretch, s_shrink, col;
	int i,j;
	FILE *f;

	pbm_flag = 0;
	f = check_and_open_file(fname);
	if (f==NULL) return(0);

	rotated    = r;
	leftmargin = l;
	topmargin  = t;
	wait_cntr  = 0;

	assert((c>=a));
	assert((d>=b));

	if (rotated==1) {
		hlen = d-b+topmargin;	
		vlen = c-a+leftmargin; 
	}
	else {
		hlen = c-a+leftmargin; 
		vlen = d-b+topmargin;	
	}

	if ((hlen<=0)||(vlen<=0)) return(0);
	hlen = ((hlen+7)/8)*8;	/* align hlen to 8 */

	/* save old values */
	Vs_xmin = V_xmin;     Vs_ymin = V_ymin; 
	Vs_xmax = V_xmax;     Vs_ymax = V_ymax;
	s_shrink  = G_shrink; s_stretch = G_stretch;
	col       = colored;

	/* install printout values */
	V_xmin = a;     V_ymin = b;
	V_xmax = c;     V_ymax = d;
	G_shrink  = sh; G_stretch = st;
	colored   = 1;

	gs_wait_message('m');
	bitmap = (unsigned char *)malloc((hlen*vlen+vlen)*3);
	gs_wait_message('M');
	if (!bitmap) Fatal_error("memory exhausted","");
	for (i=0; i<vlen; i++) {
		wait_cntr++;
		if (wait_cntr > 60)  { gs_wait_message('i'); wait_cntr = 0; }
		for (j=0; j<3*hlen; j++) bitmap[i*3*hlen+j] = 255;
	}

        bm_rectangle(a, b, c-a, d-b, G_color);

	/* draw bitmap */
	bm_draw_main();

	/* save PPM format into file */
	FPRINTF(f,"P6\n");
	FPRINTF(f,"%d %d\n",hlen,vlen);
	FPRINTF(f,"255\n");
	for (i=0; i<vlen; i++) {
		fwrite(&(bitmap[i*hlen*3]),1,hlen*3,f);
		wait_cntr++;
		if (wait_cntr > 30)  { gs_wait_message('s'); wait_cntr = 0; }
	}
	if (f) fclose(f);
	
	if (bitmap)  free(bitmap);
	bitmap = NULL;

	/* restore old values */
	V_xmin = Vs_xmin;     V_ymin = Vs_ymin;
	V_xmax = Vs_xmax;     V_ymax = Vs_ymax;
	G_shrink  = s_shrink; G_stretch = s_stretch;
	colored   = col;
	return(1);
}


/* Check a file
 * ------------
 * Try to open a file `fname' for writing.
 * If the file exists already, or the filename is not appropriate,
 * it is an error.
 * On error, we return NULL, otherwise the opend file.
 */

#ifdef ANSI_C
static FILE *check_and_open_file(char *fname)
#else
static FILE *check_and_open_file(fname)
char *fname;
#endif
{
	FILE *f;
	char *c;

        c = fname;
        while (*c) c++;
        if (c>fname) c--;
#ifdef VMS 
        if (*c==']') {
#else
        if (*c=='/') {
#endif
                return(NULL);
        }

	/* check whether filename is useful */
	if (!fname)  return(NULL);
	if (!*fname) return(NULL);

	/* check whether file already exists */ 
	f = fopen(fname,"r");
	if (f) { fclose(f); return(NULL); }

	f = fopen(fname,"w");
	return(f);
}


/*--------------------------------------------------------------------*/
/*  Device driver for pbm and ppm Files                               */
/*--------------------------------------------------------------------*/

/* Draw a rectangle
 * ----------------
 * at (x,y) with width w, height h and color c
 */

#ifdef ANSI_C
static void    bm_rectangle(int x,int y,int w,int h,int c)
#else
static void    bm_rectangle(x, y, w, h, c)
int     x, y, w, h, c;
#endif
{
	wait_cntr++;
	if (wait_cntr > 30)  { gs_wait_message('r'); wait_cntr = 0; }
	if (pbm_flag) bw_rectangle(x, y, w, h, c);
	else 	      co_rectangle(x, y, w, h, c);  
}

/* Draw a line
 * -----------
 * from fx,fy to tx,ty with color c.
 */

#ifdef ANSI_C
void    bm_line(int fx,int fy,int tx,int ty,int c)
#else
void    bm_line(fx, fy, tx, ty, c)
int     fx, fy, tx, ty, c;
#endif
{
	wait_cntr++;
	if (wait_cntr > 30)  { gs_wait_message('l'); wait_cntr = 0; }
	if (pbm_flag) bw_line(fx, fy, tx, ty, c);
	else          co_line(fx, fy, tx, ty, c); 
}


/*--------------------------------------------------------------------*/
/*  Device driver for pbm-Files                                       */
/*--------------------------------------------------------------------*/

/* Draw a point 
 * ------------
 * at (x,y) with color c
 */

#ifdef ANSI_C
static void bw_point(int x,int y,int c)
#else
static void bw_point(x,y,c)
int x;
int y;
int c;
#endif
{	unsigned char mask,*cc;
	int xx,yy;

	if (rotated) {
		xx = hlen - 1 - (y + topmargin);
		yy = x + leftmargin;
	}
	else {
		xx = x + leftmargin;
		yy = y + topmargin;
	}
	if (xx<0) return;
	if (yy<0) return;
	if (xx>=hlen) return;
	if (yy>=vlen) return;

	cc = &(bitmap[yy*(hlen/8)+xx/8]);
	switch (xx%8) {
	case 0: mask = 0x80; break;
	case 1: mask = 0x40; break;
	case 2: mask = 0x20; break;
	case 3: mask = 0x10; break;
	case 4: mask = 0x08; break;
	case 5: mask = 0x04; break;
	case 6: mask = 0x02; break;
	case 7: mask = 0x01; break;
	}
	
	if (c==WHITE) {
		mask = ~mask;
		*cc = (*cc) & mask;
	}
	else {
		*cc = (*cc) | mask;
	}
}


/* Draw a rectangle
 * ----------------
 * at (x,y) with width w, height h and color c
 */

#ifdef ANSI_C
static void    bw_rectangle(int x,int y,int w,int h,int c)
#else
static void    bw_rectangle(x, y, w, h, c)
int     x, y, w, h, c;
#endif
{
	int i,j;

	for (i=0; i<h; i++) {
		for (j=0; j<w; j++) {
			bw_point(x-V_xmin+j,y-V_ymin+i,c);
		}
	}
}

/* Draw a line
 * -----------
 * from fx,fy to tx,ty with color c.
 */

#ifdef ANSI_C
static void    bw_line(int fx,int fy,int tx,int ty,int c)
#else
static void    bw_line(fx, fy, tx, ty, c)
int     fx, fy, tx, ty, c;
#endif
{
	 int x1,y1,x2,y2,xp,yp;

	 x1 = fx-V_xmin;
	 y1 = fy-V_ymin;
	 x2 = tx-V_xmin;
	 y2 = ty-V_ymin;
	 bw_point(x1,y1,c);
	 if ((x2-x1==0)&&(y2-y1==0)) return;
	 if ((x2-x1)*(x2-x1) > (y2-y1)*(y2-y1)) {
		xp = x1;
		if (x1<x2) while (xp<=x2) {
			yp = ((y2-y1)*(xp-x1)+y1*(x2-x1))/(x2-x1);
	 		bw_point(xp,yp,c);
			xp++;
		} 	
		else while (xp>=x2) {
			yp = ((y2-y1)*(xp-x1)+y1*(x2-x1))/(x2-x1);
	 		bw_point(xp,yp,c);
			xp--;
		} 	
	 }
	 else {
		yp = y1;
		if (y1<y2) while (yp<=y2) {
			xp = ((x2-x1)*(yp-y1)+x1*(y2-y1))/(y2-y1);
	 		bw_point(xp,yp,c);
			yp++;
		}
		else while (yp>=y2) {
			xp = ((x2-x1)*(yp-y1)+x1*(y2-y1))/(y2-y1);
	 		bw_point(xp,yp,c);
			yp--;
		}
	 }
}


/*--------------------------------------------------------------------*/
/*  Device driver for ppm-Files                                       */
/*--------------------------------------------------------------------*/

/* Draw a point 
 * ------------
 * at (x,y) with color c
 */

#ifdef ANSI_C
static void co_point(int x,int y,int c)
#else
static void co_point(x,y,c)
int x;
int y;
int c;
#endif
{	unsigned char *cc;
	int xx, yy;

	if (x<0) return;
	if (y<0) return;
	if (rotated) {
		xx = hlen - 1 - (y + topmargin);
		yy = x + leftmargin;
	}
	else {
		xx = x + leftmargin;
		yy = y + topmargin;
	}
	if (xx<0) return;
	if (yy<0) return;
	if (xx>=hlen) return;
	if (yy>=vlen) return;

	cc = &(bitmap[yy*hlen*3+xx*3]);

	*cc++ = redmap[c];
	*cc++ = greenmap[c];
	*cc   = bluemap[c];
}


/* Draw a rectangle
 * ----------------
 * at (x,y) with width w, height h and color c
 */

#ifdef ANSI_C
static void    co_rectangle(int x,int y,int w,int h,int c)
#else
static void    co_rectangle(x, y, w, h, c)
int     x, y, w, h, c;
#endif
{
	int i,j;

	for (i=0; i<h; i++) {
		for (j=0; j<w; j++) {
			co_point(x-V_xmin+j,y-V_ymin+i,c);
		}
	}
}

/* Draw a line
 * -----------
 * from fx,fy to tx,ty with color c.
 */

#ifdef ANSI_C
static void    co_line(int fx,int fy,int tx,int ty,int c)
#else
static void    co_line(fx, fy, tx, ty, c)
int     fx, fy, tx, ty, c;
#endif
{
	 int x1,y1,x2,y2,xp,yp;

	 x1 = fx-V_xmin;
	 y1 = fy-V_ymin;
	 x2 = tx-V_xmin;
	 y2 = ty-V_ymin;
	 co_point(x1,y1,c);
	 if ((x2-x1==0)&&(y2-y1==0)) return;
	 if ((x2-x1)*(x2-x1) > (y2-y1)*(y2-y1)) {
		xp = x1;
		if (x1<x2) while (xp<=x2) {
			yp = ((y2-y1)*(xp-x1)+y1*(x2-x1))/(x2-x1);
	 		co_point(xp,yp,c);
			xp++;
		} 	
		else while (xp>=x2) {
			yp = ((y2-y1)*(xp-x1)+y1*(x2-x1))/(x2-x1);
	 		co_point(xp,yp,c);
			xp--;
		} 	
	 }
	 else {
		yp = y1;
		if (y1<y2) while (yp<=y2) {
			xp = ((x2-x1)*(yp-y1)+x1*(y2-y1))/(y2-y1);
	 		co_point(xp,yp,c);
			yp++;
		}
		else while (yp>=y2) {
			xp = ((x2-x1)*(yp-y1)+x1*(y2-y1))/(y2-y1);
	 		co_point(xp,yp,c);
			yp--;
		}
	 }
}

/*--------------------------------------------------------------------*/

