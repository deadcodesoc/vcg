/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */ 
/*		--------------------------------------		      */ 
/*								      */
/*   file:	   PSDev.c   					      */
/*   version:	   1.00.00					      */
/*   creation:	   14.4.93					      */
/*   author:	   G. Sander (Version 1.00.00-...)		      */ 
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */ 
/*   description:  PostScript Device: Print bitmap into a file in     */
/*		   PostScript format    			      */ 
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/


#ifndef lint
static char *id_string="$Id: PSdev.c,v 1.8 1995/02/08 11:11:14 sander Exp $";
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
 * $Log: PSdev.c,v $
 * Revision 1.8  1995/02/08  11:11:14  sander
 * Distribution version 1.3.
 *
 * Revision 1.7  1994/12/23  18:12:45  sander
 * Manhatten layout added.
 * Option interface cleared.
 * infobox behaviour improved.
 * First version of fisheye (carthesian).
 * Options Noedge and nonode.
 * Titles in the node title box are now sorted.
 *
 * Revision 1.6  1994/11/25  15:43:29  sander
 * Printer interface added to allow to use VCG as a converter.
 *
 * Revision 1.5  1994/08/02  15:36:12  sander
 * Bounding box for landscape format corrected.
 *
 * Revision 1.4  1994/06/07  14:09:59  sander
 * Splines implemented.
 * HP-UX, Linux, AIX, Sun-Os, IRIX compatibility tested.
 * The tool is now ready to be distributed.
 *
 * Revision 1.3  1994/05/16  08:56:03  sander
 * shape attribute (boxes, rhombs, ellipses, triangles) added.
 *
 * Revision 1.2  1994/05/05  08:20:30  sander
 * Small corrections.
 *
 * Revision 1.1  1994/04/27  16:05:19  sander
 * Initial revision
 *
 *
 */

/************************************************************************
 *  This file allows to write the graph into a PostScript file. These 
 *  routines are called, if the "export"-menu was selected. 
 * 
 *  The implementation idea is a little bit ugly: We use the same 
 *  drawing driver "draw.c" and "drawlib.c" and only redefine the
 *  device dependent functions. This duplication of code ensures that
 *  the speed is reasonable. All global function names must be mapped
 *  to new names, otherwise we have linking conflicts.
 * 
 *  Basically, the following function are in this file:
 *    print_all_ps	     prints the PostScript to a file 
 ************************************************************************/


/* Mapping of global names of draw.c, drawstr.c, drawlib.c
 * =======================================================
 */

#define INCLUDE_DRAW
#define POSTSCRIPT_DEVICE

#define draw_main      ps_draw_main
#define draw_one_node  ps_draw_one_node
#define gs_stringw     ps_stringw
#define gs_stringh     ps_stringh
#define gs_boxw        ps_boxw
#define gs_boxh        ps_boxh

#define gs_printstr          ps_printstr         
#define gs_calcstringsize    ps_calcstringsize  
#define gs_setto             ps_setto          
#define gs_setshrink         ps_setshrink        
#define gs_calctextboxsize   ps_calctextboxsize 
#define gs_anchornode        ps_anchornode        
#define gs_textbox           ps_textbox        
#define gs_reverttextbox     ps_reverttextbox 
#define gs_halfreverttextbox ps_halfreverttextbox  
#define gs_stringbox         ps_stringbox         
#define gs_calcrhombsize     ps_calcrhombsize 
#define gs_rhomb             ps_rhomb        
#define gs_revertrhomb       ps_revertrhomb 
#define gs_halfrevertrhomb   ps_halfrevertrhomb  
#define gs_calctrianglesize  ps_calctrianglesize 
#define gs_triangle          ps_triangle        
#define gs_reverttriangle    ps_reverttriangle 
#define gs_halfreverttriangle ps_halfreverttriangle  
#define gs_calcellipsesize   ps_calcellipsesize 
#define gs_ellipse           ps_ellipse        
#define gs_revertellipse     ps_revertellipse 
#define gs_halfrevertellipse ps_halfrevertellipse  
#define gs_solidarrow        ps_solidarrow       
#define gs_dashedarrow       ps_dashedarrow     
#define gs_dottedarrow       ps_dottedarrow    
#define gs_line              ps_line
#define gs_rectangle         ps_rectangle
#define gs_actbackground     ps_actbackground

#define mystretch            ps_mystretch
#define myshrink             ps_myshrink
#define myxpos               ps_myxpos
#define myypos               ps_myypos
#define gs_stlimit           ps_stlimit
#define gs_shlimit           ps_shlimit


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
#include <math.h>
#include "globals.h"


/* Prototypes
 * ----------
 */

static int print_ps 
   _PP((char *fname, int a,int b,int c,int d, float scale, float lm, float bm,
float tm, int   form, int col, int numpag));

static FILE *check_and_open_file  _PP((char *fname));

void ps_line            
		_PP((int fx,int fy,int tx,int ty,int c));
void ps_thickline 
		_PP((int fx,int fy,int tx,int ty,int t,int c));
static void ps_dashedthickline 
		_PP((int fx,int fy,int tx,int ty,int t,int c,int d));
static void ps_dottedthickline 
		_PP((int fx,int fy,int tx,int ty,int t,int c,int d));
static void ps_bezierspline
		_PP((int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,int t,int c,int m));
static void ps_rectangle       
		_PP((int x,int y,int w,int h,int c));
static void ps_fillrhomb 
		_PP((int x,int y,int w,int h,int c));
static void ps_filltriangle 
		_PP((int x,int y,int w,int h,int c));
static void ps_fillellipse 
		_PP((int x,int y,int w,int h,int c));
static void ps_freearrowpoint
		_PP((int x1,int y1,int rx1,int ry1,int rx2,int ry2,int c));
static void ps_w_arrowpoint
		_PP((int x,int y,int size,int c));
static void ps_s_arrowpoint
		_PP((int x,int y,int size,int c));
static void ps_n_arrowpoint
		_PP((int x,int y,int size,int c));
static void ps_e_arrowpoint
		_PP((int x,int y,int size,int c));
static void ps_sw_arrowpoint
		_PP((int x,int y,int size,int c));
static void ps_nw_arrowpoint
		_PP((int x,int y,int size,int c));
static void ps_ne_arrowpoint
		_PP((int x,int y,int size,int c));
static void ps_se_arrowpoint
		_PP((int x,int y,int size,int c));

static void portrait_header
	_PP((int a,int  b,int  c,int  d,float scale,float lm, float bm));
static void landscape_header
	_PP((int a,int  b,int  c,int  d,float scale,float lm, float bm));

static void common_header _PP((void));

static void init_postscriptpage _PP((void));
static void calc_paper_width	_PP((void));

static void ps_setcolor _PP((int c));



/* Variables 
 * ---------
 */

static char *mfilename;

/* Flag, wether cps (2), gps (1) or bps (0)
 */

static int bps_flag;
static FILE *fptr;

static int dist;

/* from X11devpb.c */

extern int   act_output_type;
extern int   act_color_type;
extern int   act_ori_type;
extern int   act_paper_num;
extern int   act_paper_type;
extern float act_width;
extern float act_height;
extern float act_left_margin;
extern float act_right_margin;
extern float act_top_margin;
extern float act_bottom_margin;
extern int   act_xdpi;
extern int   act_ydpi;
extern float act_scaling;
extern int   act_bbox;

/* Counter for the wait message */

static int wait_cntr;

static int mreg_xmin;
static int mreg_xmax;
static int mreg_ymin;
static int mreg_ymax;
static int maxxdist;
static int maxydist;
static int maxover;


/* Modules
 * -------
 * We use this ugly trick to reuse the files draw.c and drawlib.c 
 */
 
#include "draw.c"
#include "drawlib.c"
#include "PSdev.h"


/*--------------------------------------------------------------------*/
/*  Print all nodes into a file, Entry point                          */
/*--------------------------------------------------------------------*/

/*  We take the arguments that are setup in X11devpb, recalculate
 *  the measures, and output the graph. 
 */ 

#ifdef ANSI_C
void print_all_ps(char *fname, int a, int b, int c, int d)
#else
void print_all_ps(fname, a, b, c, d)
char *fname;
int a, b, c, d;
#endif
{
	int form;
	float scale, lm, bm, tm;	

	assert((act_output_type==3));


	wait_cntr  = 0;
	if (a>c)  { form = a; a = c; c = form; }
	if (b>d)  { form = b; b = d; d = form; }
	mreg_xmin = a;
	mreg_xmax = c;
	mreg_ymin = b;
	mreg_ymax = d;

	switch (act_ori_type) {
	case 1: form = 0; break;
	case 2: form = 1; break;
	}

	scale = (float)(act_xdpi)/act_scaling;
	lm = act_left_margin/2.54; 
	bm = act_bottom_margin/2.54; 
	tm = act_top_margin/2.54; 

	switch (act_color_type) {
	case 1: print_ps(fname, a, b, c, d,scale,lm,bm,tm,form,2,act_paper_num);
		break;
	case 2: print_ps(fname, a, b, c, d,scale,lm,bm,tm,form,1,act_paper_num);
		break;
	case 3: print_ps(fname, a, b, c, d,scale,lm,bm,tm,form,0,act_paper_num);
		break;
	}
} 



/*--------------------------------------------------------------------*/
/*  Print all nodes into a file, driver                               */
/*--------------------------------------------------------------------*/

/*  Print ps-file
 *  =============
 *  This is the black and white driver. No colors, no grayscales.
 *  The region (a,b)-(c,d) is printed to the file.
 *  The scaling is scale, however different as before, it gives the
 *  scaling of 1 inch. E.g. scale = 300 means we have 300 units per
 *  inch, i.e. 300 dpi.
 *  lm,bm are the left margin, bottom margin in inches.
 *
 *  We follow the Adobe 2.0 PostScript format with Bounding Box.
 *  Note: the bounding box gives the true size of the picture in 72dpi,
 *  E.g.  BoundingBox: 72 72 518 762  is a picture that is on a din A 4
 *  1 inc far from the border.
 *      A 4 maximal:     0 0 590 834
 *      Letter maximal:  0 0 590 864 
 *  form gives the format: 1 is landscape, 0 is portrait
 *  We return 1 on success.
 */


#ifdef ANSI_C           
static int print_ps(char *fname,int a,int b,int c,int d,float scale,float lm,float bm,float tm,int form,int col,int numpag)
#else
static int print_ps(fname, a, b, c, d,scale,lm,bm,tm,form,col,numpag)
char *fname;
int   a,b,c,d;
float scale;
float lm,bm,tm;
int   form;
int col;
int numpag;
#endif
{
	int Vs_xmin, Vs_ymin, Vs_xmax, Vs_ymax;
	int s_stretch, s_shrink, oldcol;
	int i, j;
	int oldx, oldy;

	mfilename = fname;
	bps_flag = col;

	if (c<=a) return(0);
	if (d<=b) return(0);

	if (act_paper_num > 1) {
		lm = 1.0/2.54; 
		bm = 1.0/2.54; 
		tm = 1.0/2.54; 
		calc_paper_width();
		act_bbox = 0;
	}

	fptr = check_and_open_file(fname);
	if (fptr==NULL)  return(0);

	/* save old values */
	Vs_xmin = V_xmin;     Vs_ymin = V_ymin; 
	Vs_xmax = V_xmax;     Vs_ymax = V_ymax;
	s_shrink  = G_shrink; s_stretch = G_stretch;
	oldcol       = colored;

	/* install printout values. We leave the scaling to postscript */
	V_xmin = a;     V_ymin = b;
	V_xmax = c;     V_ymax = d;
	G_shrink  = 1; G_stretch = 1;
	
	switch (bps_flag) {
	case 2: colored   = 1; break;
	case 1: colored   = 1; break;
	case 0: colored   = 0; break;
	}

	wait_cntr  = 0;

	/* Header */
	if (form == 1) 	landscape_header(a, b, c, d, scale, lm, tm);
	else		portrait_header( a, b, c, d, scale, lm, bm);

	oldx = mreg_xmin;
	for (i=1; i<=numpag; i++) {
		if (numpag!=1) {
			a = oldx;
			if (a>=mreg_xmax) break;
			c = a + maxxdist + maxover;
			oldx = a + maxxdist;
			if (c>=mreg_xmax) {
				oldx = mreg_xmax;
				c = mreg_xmax;
			}
			oldy = mreg_ymin;
		}
		for (j=1; j<=numpag; j++) {

			gs_wait_message('y');

			if (numpag==1) {
				a = mreg_xmin;
				c = mreg_xmax;
				b = mreg_ymin;
				d = mreg_ymax;
			}
			else {
				b = oldy;
				if (b>=mreg_ymax) break;

				d = b + maxydist + maxover;
				oldy = b + maxydist;
				if (d>=mreg_ymax) {
					oldy = mreg_ymax;
					d = mreg_ymax;
				}
			}
			V_xmin = a;
			V_xmax = c;
			V_ymin = b;
			V_ymax = d;
			dist = V_ymax-V_ymin;

			FPRINTF(fptr,"%%%%Page: %d %d\n",
				(i-1)*numpag+j, (i-1)*numpag+j);
			/* if (numpag>1) init_postscriptpage(); */
			FPRINTF(fptr,"72 %3.2f div dup scale\n",scale);
			if (numpag == 1) {
				if (form == 1) {	
					FPRINTF(fptr,"90 rotate\n");
					FPRINTF(fptr,"%f %f translate\n",
						lm*scale,
						-tm*scale
					        -(float)(d-b));
				}
				else {
					FPRINTF(fptr,"%f %f translate\n",
						lm*scale,bm*scale);
				}
			}
			else {
				if (form == 1) {	
					FPRINTF(fptr,"90 rotate\n");
					FPRINTF(fptr,"%f %f translate\n",
						0.39*scale,
						-0.39*scale
					        -(float)(d-b));
				}
				else {
					FPRINTF(fptr,"%f %f translate\n",
						0.39*scale,0.39*scale);
				}
			}

			/* draw to file */
	
			if (colored) {
				ps_rectangle(V_xmin, V_ymin, V_xmax-V_xmin, V_ymax-V_ymin, G_color);
			}
			else {	
				ps_rectangle(V_xmin, V_ymin, V_xmax-V_xmin, V_ymax-V_ymin, WHITE);
			}
			ps_draw_main();

			FPRINTF(fptr,"showpage\n");
			FPRINTF(fptr,"%%%%PageTrailer\n");
		}
	}
	FPRINTF(fptr,"%%%%Trailer\n");
	FPRINTF(fptr,"%%%%EOF\n");

	if (fptr) fclose(fptr);
	fptr = NULL;
	
	/* restore old values */
	V_xmin = Vs_xmin;     V_ymin = Vs_ymin;
	V_xmax = Vs_xmax;     V_ymax = Vs_ymax;
	G_shrink  = s_shrink; G_stretch = s_stretch;
	colored   = oldcol;
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
/*  Initializing sequences for PostScript                             */
/*--------------------------------------------------------------------*/

/*  Portrait format
 *  ---------------
 */

#ifdef ANSI_C           
static void portrait_header(int a,int b,int c,int d,float scale,float lm,float bm)
#else
static void portrait_header(a, b, c, d, scale, lm, bm)
int a, b, c, d;
float scale, lm, bm;
#endif
{
	float numxunits, numyunits;

	assert((c>a));
	assert((d>b));

	numxunits = (float)(c-a);
	numyunits = (float)(d-b);

	FPRINTF(fptr,"%%!PS-Adobe-2.0 EPSF-1.2\n");
	FPRINTF(fptr,"%%%%Creator: %s (P)\n", short_banner);
	FPRINTF(fptr,"%%%%Title: %s\n", mfilename);
	FPRINTF(fptr,"%%%%RCS-info: $I");
	FPRINTF(fptr,"d$\n");
        FPRINTF(fptr,"%%%%SCCS-info: %%W");
        FPRINTF(fptr,"%% %%E");
        FPRINTF(fptr,"%%\n");
	if (act_bbox) FPRINTF(fptr,"%%%%BoundingBox: ");
	else          FPRINTF(fptr,"%%%%ProposedBoundings: ");
	FPRINTF(fptr," %d %d %d %d\n",
		gstoint(lm*72),gstoint(bm*72),
		gstoint(lm*72)+gstoint(72*numxunits/scale),
		gstoint(bm*72)+gstoint(72*numyunits/scale));

	FPRINTF(fptr,"%%%%EndComments\n");
	
	common_header();
}


/*  Landscape format
 *  ----------------
 */

#ifdef ANSI_C           
static void landscape_header(int a,int b,int c,int d,float scale,float lm,float tm)
#else
static void landscape_header(a, b, c, d, scale, lm, tm)
int a, b, c, d;
float scale, lm, tm;
#endif
{
	float numxunits, numyunits;

	assert((c>a));
	assert((d>b));

	numxunits = (float)(c-a);
	numyunits = (float)(d-b);

	FPRINTF(fptr,"%%!PS-Adobe-2.0 EPSF-1.2\n");
	FPRINTF(fptr,"%%%%Creator: %s (L)\n", short_banner);
	FPRINTF(fptr,"%%%%Title: %s\n", mfilename);
	FPRINTF(fptr,"%%%%RCS-info: $I");
	FPRINTF(fptr,"d$\n");
        FPRINTF(fptr,"%%%%SCCS-info: %%W");
        FPRINTF(fptr,"%% %%E");
        FPRINTF(fptr,"%%\n");
	if (act_bbox) FPRINTF(fptr,"%%%%BoundingBox: ");
	else          FPRINTF(fptr,"%%%%ProposedBoundings: ");
	FPRINTF(fptr," %d %d %d %d\n",
		gstoint(tm*72),gstoint(lm*72),
		gstoint(tm*72)+gstoint(72*numyunits/scale),
		gstoint(lm*72)+gstoint(72*numxunits/scale));
	FPRINTF(fptr,"%%%%EndComments\n");
	
	common_header();
}


/*  Common Header for both formats
 */

#ifdef ANSI_C
static void common_header(void)
#else
static void common_header()
#endif
{
	FPRINTF(fptr,"1 setlinecap\n");
	FPRINTF(fptr,"1 setlinejoin\n");

	/* Position turtle without drawing */

	FPRINTF(fptr,"/M /moveto load def\n");

	/* Draw linw from actual point to specified point */

	FPRINTF(fptr,"/D { lineto currentpoint stroke moveto } def\n");

	/* Define line from actual point to specified point without drawing */

	FPRINTF(fptr,"/P /lineto load def\n");

	/* Text print command (currently not used) */

	FPRINTF(fptr,"/S /show load def\n");

	/* Set gray value color. 0 = Black */

	FPRINTF(fptr,"/G /setgray load def\n");

	/* Set real RGB color */

	FPRINTF(fptr,"/C /setrgbcolor load def\n");

	/* Set line width */

	FPRINTF(fptr,"/LW /setlinewidth load def\n");

	/* Define a new path (for filling) */

	FPRINTF(fptr,"/NP /newpath load def\n");

	/* Close a path, i.e. combine start and end point */

	FPRINTF(fptr,"/CP /closepath load def\n");

	/* Set Dashing mode */

	FPRINTF(fptr,"/SD /setdash load def\n");

	/* Default line thickness is 1 */

	FPRINTF(fptr,"1 LW\n");
}


/*  Initialize a page, i.e. fill the whole page with the background color
 *  ---------------------------------------------------------------------
 */

#ifdef ANSI_C
static void init_postscriptpage(void)
#else
static void init_postscriptpage()
#endif
{
	int a, b, h;

	switch (act_paper_type) {
	case 1: a = 595;  b = 850;  break;
	case 2: a = 525;  b = 765;  break;
	case 3: a = 425;  b = 595;  break;
	case 4: a = 792;  b = 1224; break;
	case 5: a = 612;  b = 792;  break;
	case 6: a = 612;  b = 1008; break;
	}

	if (colored) ps_setcolor(G_color);
	else ps_setcolor(WHITE);

	FPRINTF(fptr,"NP %d %d M %d %d P %d %d P %d %d P CP fill\n",
		0,   0,  0,  b,  a,  b,  a,  0);
}



/*  Calculate the maximal number of pixels on a page 
 *  ------------------------------------------------
 *  This is used for multipage output only.
 */

#ifdef ANSI_C
static void calc_paper_width(void)
#else
static void calc_paper_width()
#endif
{
	float mx, my;

	assert((act_paper_num>1));
        switch (act_paper_type) {
        case 1:
                if (act_ori_type==1)    { mx = 21.0; my = 30.0; }
                else                    { mx = 30.0; my = 21.0; }
                break;
        case 2:
                if (act_ori_type==1)    { mx = 18.5; my = 27.0; }
                else                    { mx = 27.0; my = 18.5; }
                break;
        case 3:
                if (act_ori_type==1)    { mx = 15.0; my = 21.0; }
                else                    { mx = 21.0; my = 15.0; }
                break;
        case 4:
                if (act_ori_type==1)    { mx = 27.94; my = 43.18; }
                else                    { mx = 43.18; my = 27.94; }
                break;
        case 5:
                if (act_ori_type==1)    { mx = 21.59; my = 27.94; }
                else                    { mx = 27.94; my = 21.59; }
                break;
        case 6:
                if (act_ori_type==1)    { mx = 21.59; my = 35.56; }
                else                    { mx = 35.56; my = 21.59; }
                break;
        }
        mx = (mx-3.0);
        my = (my-3.0);
	maxxdist = (int)(mx * act_xdpi / act_scaling / 2.54);
	maxydist = (int)(my * act_ydpi / act_scaling / 2.54);
	maxover =  (int)(1.0 * act_ydpi / act_scaling / 2.54);
}


/*--------------------------------------------------------------------*/
/*  Device driver for pbm and ppm Files                               */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
static void 	ps_setcolor(int c)
#else
static void 	ps_setcolor(c)
int c; 
#endif
{
	float col;

        wait_cntr++;
        if (wait_cntr > 40)  { gs_wait_message('x'); wait_cntr = 0; }

	switch(bps_flag) {
	case 0:
		if (c==WHITE) FPRINTF(fptr,"1.0 G ");
		else 	      FPRINTF(fptr,"0.0 G ");
		break;
	case 1:
		col = (float)(299*redmap[c]+587*greenmap[c]+114*bluemap[c]);
		FPRINTF(fptr,"%3.2f G ", col/1000.0/255.0);
		break;
	case 2:
		FPRINTF(fptr,"%3.2f %3.2f %3.2f C ", 
			redmap[c]/255.0, greenmap[c]/255.0, bluemap[c]/255.0);
		break;
	}
}


/* Draw a rectangle
 * ----------------
 * at (x,y) with width w, height h and color c
 */

#ifdef ANSI_C
static void    ps_rectangle(int x,int y,int w,int h,int c)
#else
static void    ps_rectangle(x, y, w, h, c)
int     x, y, w, h, c;
#endif
{
	ps_setcolor(c);

	FPRINTF(fptr,"NP %d %d M %d %d P %d %d P %d %d P CP fill\n",
		x-V_xmin,   dist - (y-V_ymin),
		x-V_xmin+w, dist - (y-V_ymin),
		x-V_xmin+w, dist - (y-V_ymin+h),
		x-V_xmin,   dist - (y-V_ymin+h)); 
}


/* Draw a rhomb 
 * ------------
 * at (x,y) with width w, height h and color c
 */

#ifdef ANSI_C
static void    ps_fillrhomb(int x,int y,int w,int h,int c)
#else
static void    ps_fillrhomb(x, y, w, h, c)
int     x, y, w, h, c;
#endif
{
	ps_setcolor(c);

	FPRINTF(fptr,"NP %d %d M %d %d P %d %d P %d %d P CP fill\n",
		x-V_xmin,     dist - (y-V_ymin+h/2),
		x-V_xmin+w/2, dist - (y-V_ymin),
		x-V_xmin+w,   dist - (y-V_ymin+h/2),
		x-V_xmin+w/2, dist - (y-V_ymin+h)); 
}


/* Draw a triangle 
 * ---------------
 * at (x,y) with width w, height h and color c
 */

#ifdef ANSI_C
static void    ps_filltriangle(int x,int y,int w,int h,int c)
#else
static void    ps_filltriangle(x, y, w, h, c)
int     x, y, w, h, c;
#endif
{
	ps_setcolor(c);

	switch (G_orientation) {
	case LEFT_TO_RIGHT:
		FPRINTF(fptr,"NP %d %d M %d %d P %d %d P CP fill\n",
			x-V_xmin+w  , dist - (y-V_ymin),
			x-V_xmin+w  , dist - (y-V_ymin+h),
			x-V_xmin    , dist - (y-V_ymin+h/2));
		return;
	case RIGHT_TO_LEFT:
		FPRINTF(fptr,"NP %d %d M %d %d P %d %d P CP fill\n",
			x-V_xmin  , dist - (y-V_ymin),
			x-V_xmin  , dist - (y-V_ymin+h),
			x-V_xmin+w, dist - (y-V_ymin+h/2));
		return;
	case BOTTOM_TO_TOP:
		FPRINTF(fptr,"NP %d %d M %d %d P %d %d P CP fill\n",
			x-V_xmin+w/2, dist - (y-V_ymin+h),
			x-V_xmin+w  , dist - (y-V_ymin),
			x-V_xmin    , dist - (y-V_ymin));
		return;
	case TOP_TO_BOTTOM:
		FPRINTF(fptr,"NP %d %d M %d %d P %d %d P CP fill\n",
			x-V_xmin+w/2, dist - (y-V_ymin),
			x-V_xmin+w  , dist - (y-V_ymin+h),
			x-V_xmin    , dist - (y-V_ymin+h));
		return;
	}
}


/* Draw an ellipse 
 * ---------------
 * at (x,y) with width w, height h and color c
 */

#ifdef ANSI_C
static void    ps_fillellipse(int x,int y,int w,int h,int c)
#else
static void    ps_fillellipse(x, y, w, h, c)
int     x, y, w, h, c;
#endif
{
        int i,j;

	ps_setcolor(c);

	FPRINTF(fptr,"NP %d %d M\n", x+w/2-V_xmin, dist-(y+h-V_ymin));
        for (i=0; i<=(w+1)/2; i++) {
                j = h*h/4 - i*h/w * i*h/w;
                if (j>=0) j = gstoint(sqrt((double)j));
                else j = 0;
		FPRINTF(fptr,"%d %d P\n", 
				x+w/2+i-V_xmin, dist-(y+h/2+j-V_ymin));
	}
        for (i=(w+1)/2; i>0; i--) {
                j = h*h/4 - i*h/w * i*h/w;
                if (j>=0) j = gstoint(sqrt((double)j));
                else j = 0;
		FPRINTF(fptr,"%d %d P\n", 
				x+w/2+i-V_xmin, dist-(y+h/2-j-V_ymin));
	}
        for (i=0; i<=(w+1)/2; i++) {
                j = h*h/4 - i*h/w * i*h/w;
                if (j>=0) j = gstoint(sqrt((double)j));
                else j = 0;
		FPRINTF(fptr,"%d %d P\n", 
				x+w/2-i-V_xmin, dist-(y+h/2-j-V_ymin));
	}
        for (i=(w+1)/2; i>0; i--) {
                j = h*h/4 - i*h/w * i*h/w;
                if (j>=0) j = gstoint(sqrt((double)j));
                else j = 0;
		FPRINTF(fptr,"%d %d P\n", 
				x+w/2-i-V_xmin, dist-(y+h/2+j-V_ymin));
	}
	
	FPRINTF(fptr,"CP fill\n");
}


/* Draw a line
 * -----------
 * from fx,fy to tx,ty with color c.
 */

#ifdef ANSI_C
void    ps_line(int fx,int fy,int tx,int ty,int c)
#else
void    ps_line(fx, fy, tx, ty, c)
int     fx, fy, tx, ty, c;
#endif
{
	ps_setcolor(c);

	FPRINTF(fptr,"%d %d M %d %d D\n",
	 	fx-V_xmin, dist - (fy-V_ymin), 
		tx-V_xmin, dist - (ty-V_ymin));

}


/* Draw a solid line of thickness t
 * --------------------------------
 * from fx,fy to tx,ty with color c.
 */

#ifdef ANSI_C
void    ps_thickline(int fx,int fy,int tx,int ty,int t,int c)
#else
void    ps_thickline(fx, fy, tx, ty, t, c)
int     fx, fy, tx, ty, t, c;
#endif
{
        ps_setcolor(c);

	FPRINTF(fptr,"%d LW ",t);
        FPRINTF(fptr,"%d %d M %d %d D 1 LW\n",
                fx-V_xmin, dist - (fy-V_ymin), 
		tx-V_xmin, dist - (ty-V_ymin));
}


/* Draw a dashed line of thickness t
 * ---------------------------------
 * from fx,fy to tx,ty with color c.
 */

#ifdef ANSI_C
static void    ps_dashedthickline(int fx,int fy,int tx,int ty,int t,int c,int d)
#else
static void    ps_dashedthickline(fx, fy, tx, ty, t, c, d)
int     fx, fy, tx, ty, t, c, d;
#endif
{
        ps_setcolor(c);

	FPRINTF(fptr,"[ %d %d ] 0 SD %d LW ",d,d,t);
        FPRINTF(fptr,"%d %d M %d %d D [ 100 0 ] 0 SD 1 LW\n",
                fx-V_xmin, dist - (fy-V_ymin), 
		tx-V_xmin, dist - (ty-V_ymin));
}


/* Draw a dotted line of thickness t
 * ---------------------------------
 * from fx,fy to tx,ty with color c.
 */

#ifdef ANSI_C
static void    ps_dottedthickline(int fx,int fy,int tx,int ty,int t,int c,int d)
#else
static void    ps_dottedthickline(fx, fy, tx, ty, t, c, d)
int     fx, fy, tx, ty, t, c, d;
#endif
{
        ps_setcolor(c);

	FPRINTF(fptr,"[ 1 %d ] 0 SD %d LW ",d,t);
        FPRINTF(fptr,"%d %d M %d %d D [ 100 0 ] 0 SD 1 LW\n",
                fx-V_xmin, dist - (fy-V_ymin), 
		tx-V_xmin, dist - (ty-V_ymin));
}


/* Draw a bezier spline of thickness t
 * -----------------------------------
 * with color c and mode m.
 */

#ifdef ANSI_C
static void ps_bezierspline(
	int x0,int y0,int x1,int y1,int x2,int y2,int x3,int y3,
	int t,int c,int m)
#else
static void ps_bezierspline(x0,y0,x1,y1,x2,y2,x3,y3,t,c,m)
int x0,y0,x1,y1,x2,y2,x3,y3,t,c,m;
#endif
{
	int d;

        ps_setcolor(c);

	switch (m) {
	case SOLID:
		FPRINTF(fptr,"%d LW ",t);
		break;
	case DOTTED:
		d = 15*3*G_stretch/12/G_shrink;
		FPRINTF(fptr,"[ 1 %d ] 0 SD %d LW ",d,t);
		break;
	case DASHED:
		d = 15*G_stretch/G_shrink;
		FPRINTF(fptr,"[ %d %d ] 0 SD %d LW ",d,d,t);
		break;
	case UNVISIBLE:
		return;
	}
        FPRINTF(fptr,"%d %d M %d %d ",
                x0-V_xmin, dist - (y0-V_ymin), 
		x1-V_xmin, dist - (y1-V_ymin));
        FPRINTF(fptr,"%d %d %d %d curveto stroke\n",
                x2-V_xmin, dist - (y2-V_ymin), 
		x3-V_xmin, dist - (y3-V_ymin));
	FPRINTF(fptr,"[ 100 0] 0 SD 1 LW\n");
}


/* Draw a free arrowhead
 * ---------------------
 * i.e. draw a triangle between (x1, y1), (rx1, ry1), (rx2, ry2)
 */


#ifdef ANSI_C
static void ps_freearrowpoint(int x1,int y1,int rx1,int ry1,int rx2,int ry2,
		int c)
#else
static void ps_freearrowpoint(x1, y1, rx1, ry1, rx2, ry2, c)
int x1, y1, rx1, ry1, rx2, ry2, c;
#endif
{
	ps_setcolor(c);
	FPRINTF(fptr,"NP %d %d M %d %d P %d %d P CP fill\n",
		x1-V_xmin, dist - (y1-V_ymin),
		rx1-V_xmin,dist - (ry1-V_ymin),
		rx2-V_xmin,dist - (ry2-V_ymin));
}



/* Draw an arrowhead to the north
 * ------------------------------
 * with `size' of katheses and color
 */

#ifdef ANSI_C
static void ps_n_arrowpoint(int x,int y,int size,int c)
#else
static void ps_n_arrowpoint(x, y, size, c)
int     x, y, size, c;
#endif
{
	int k;

	ps_setcolor(c);

	k = 7*size/10 - 1;

	FPRINTF(fptr,"NP %d %d M %d %d P %d %d P CP fill\n",
		x-k-V_xmin, dist - (y+k-V_ymin),
		x-V_xmin,   dist - (y-V_ymin),
		x+k-V_xmin, dist - (y+k-V_ymin));
}


/* Draw an arrowhead to the south 
 * ------------------------------
 * with `size' of katheses and color
 */

#ifdef ANSI_C
static void ps_s_arrowpoint(int x,int y,int size,int c)
#else
static void ps_s_arrowpoint(x, y, size, c)
int     x, y, size, c;
#endif
{
	int k;

	ps_setcolor(c);

	k = 7*size/10 - 1;

	FPRINTF(fptr,"NP %d %d M %d %d P %d %d P CP fill\n",
		x-k-V_xmin, dist - (y-k-V_ymin),
		x-V_xmin,   dist - (y-V_ymin),
		x+k-V_xmin, dist - (y-k-V_ymin));
}



/* Draw an arrowhead to the east 
 * -----------------------------
 * with `size' of katheses and color
 */

#ifdef ANSI_C
static void ps_e_arrowpoint(int x,int y,int size,int c)
#else
static void ps_e_arrowpoint(x, y, size, c)
int     x, y, size, c;
#endif
{
	int k;

	ps_setcolor(c);

	k = 7*size/10 - 1;

	FPRINTF(fptr,"NP %d %d M %d %d P %d %d P CP fill\n",
		x-k-V_xmin,   dist - (y-k-V_ymin),
		x-V_xmin,     dist - (y-V_ymin),
		x-k-V_xmin,   dist - (y+k-V_ymin));
}



/* Draw an arrowhead to the west 
 * -----------------------------
 * with `size' of katheses and color
 */

#ifdef ANSI_C
static void ps_w_arrowpoint(int x,int y,int size,int c)
#else
static void ps_w_arrowpoint(x, y, size, c)
int     x, y, size, c;
#endif
{
	int k;

	ps_setcolor(c);

	k = 7*size/10 - 1;

	FPRINTF(fptr,"NP %d %d M %d %d P %d %d P CP fill\n",
		x+k-V_xmin,   dist - (y-k-V_ymin),
		x-V_xmin,     dist - (y-V_ymin),
		x+k-V_xmin,   dist - (y+k-V_ymin));
}


/* Draw an arrowhead to the northeast 
 * ----------------------------------
 * with `size' of katheses and color
 */

#ifdef ANSI_C
static void ps_ne_arrowpoint(int x,int y,int size,int c)
#else
static void ps_ne_arrowpoint(x, y, size, c)
int     x, y, size, c;
#endif
{
	ps_setcolor(c);

	FPRINTF(fptr,"NP %d %d M %d %d P %d %d P CP fill\n",
		x-size+1-V_xmin, dist - (y-V_ymin),
		x-V_xmin,        dist - (y-V_ymin),
		x-V_xmin,        dist - (y+size-1-V_ymin));
}


/* Draw an arrowhead to the northwest 
 * ----------------------------------
 * with `size' of katheses and color
 */

#ifdef ANSI_C
static void ps_nw_arrowpoint(int x,int y,int size,int c)
#else
static void ps_nw_arrowpoint(x, y, size, c)
int     x, y, size, c;
#endif
{
	ps_setcolor(c);

	FPRINTF(fptr,"NP %d %d M %d %d P %d %d P CP fill\n",
		x+size-1-V_xmin, dist - (y-V_ymin),
		x-V_xmin,        dist - (y-V_ymin),
		x-V_xmin,        dist - (y+size-1-V_ymin));
}


/* Draw an arrowhead to the southeast 
 * ----------------------------------
 * with `size' of katheses and color
 */

#ifdef ANSI_C
static void ps_se_arrowpoint(int x,int y,int size,int c)
#else
static void ps_se_arrowpoint(x, y, size, c)
int     x, y, size, c;
#endif
{
	ps_setcolor(c);

	FPRINTF(fptr,"NP %d %d M %d %d P %d %d P CP fill\n",
		x-size+1-V_xmin, dist - (y-V_ymin),
		x-V_xmin,        dist - (y-V_ymin),
		x-V_xmin,        dist - (y-size+1-V_ymin));
}


/* Draw an arrowhead to the southwest 
 * ----------------------------------
 * with `size' of katheses and color
 */

#ifdef ANSI_C
static void ps_sw_arrowpoint(int x,int y,int size,int c)
#else
static void ps_sw_arrowpoint(x, y, size, c)
int     x, y, size, c;
#endif
{
	ps_setcolor(c);

	FPRINTF(fptr,"NP %d %d M %d %d P %d %d P CP fill\n",
		x+size-1-V_xmin, dist - (y-V_ymin),
		x-V_xmin,        dist - (y-V_ymin),
		x-V_xmin,        dist - (y-size+1-V_ymin));
}



/*--------------------------------------------------------------------*/

