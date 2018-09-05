/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */ 
/*		--------------------------------------		      */ 
/*								      */
/*   file:	   infobox.c					      */
/*   version:	   1.00.00					      */
/*   creation:	   23.12.94				      	      */
/*   author:	   I. Lemke  (...-Version 0.99.99)		      */ 
/*		   G. Sander (Version 1.00.00-...)		      */ 
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */ 
/*   description:  Info and label box drawing 			      */ 
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/


#ifndef lint
static char *id_string="$Id: infobox.c,v 1.3 1995/02/08 16:00:33 sander Exp $";
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
 * $Log: infobox.c,v $
 * Revision 1.3  1995/02/08  16:00:33  sander
 * Small bug with K&R C solved.
 *
 * Revision 1.2  1995/02/08  11:11:14  sander
 * Distribution version 1.3.
 *
 * Revision 1.1  1994/12/23  18:12:45  sander
 * Initial revision
 *
 */

/************************************************************************
 *  This file is a collection of auxiliary functions that implement the
 *  primitives to draw info boxes.
 *  Info boxes are only needed by the interactive device drivers, i.e.
 *  the SunView driver and the X11 driver, since info boxes are only
 *  drawn after an interactive selection.
 *  Note: we are independent from the device here, but use the function
 *  from the drawlib instance used for the interactive device (There should
 *  be only and exactly one interactive device.
 *
 *  This file here provides the following functions:
 *    gs_infobox              draw an info box containing either the
 *                            background fields or the label or the
 *                            layout attributes.
 *
 *  See drawlib.c for further details of the methology.
 ************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "globals.h"
#include "main.h"
#include "options.h"
#include "alloc.h"
#include "grprint.h"
#include "fisheye.h"
#include "drawlib.h"
#include "infobox.h"


/*  Types
 *  ----- 
 */

typedef struct infobox_node {
	GNODE v;
	long  x;		/* Position in the graph */
	long  y;		/* Position in the graph */
	int   w;		/* Width  on the screen  */
	int   h;		/* Height on the screen  */
	int   stretch;
	int   shrink;
	int   info;
	struct infobox_node *ibnext;
	struct infobox_node *ibprev;
} *INFOBOX;

#define IBNODE(p)    ((p)->v)
#define IBX(p)       ((p)->x)
#define IBY(p)       ((p)->y)
#define IBWIDTH(p)   ((p)->w)
#define IBHEIGHT(p)  ((p)->h)
#define IBSTRETCH(p) ((p)->stretch)
#define IBSHRINK(p)  ((p)->shrink)
#define IBINFO(p)    ((p)->info)
#define IBNEXT(p)    ((p)->ibnext)
#define IBPREV(p)    ((p)->ibprev)



/*  Prototypes
 *  ---------- 
 */

/* The following two functions are device dependent and are implemented
 * in sunvdv.c or X11dv.c.
 */

extern void gs_rectangle _PP((long x,long y,int w,int h,int c));

/* Static functions */

static void	draw_infoborder	 _PP((long x,long y,int w,int h,int t,int c));
static void  	draw_one_infobox _PP((INFOBOX b));


/*  Variables
 *  ---------
 */

static INFOBOX infobox_freelist = NULL;
static INFOBOX infobox_list     = NULL;
static INFOBOX infobox_listend  = NULL;

/*--------------------------------------------------------------------*/
/*   Memory management for info box lists.                            */
/*--------------------------------------------------------------------*/

/* Allocate a infobox node
 * -----------------------
 * Since this is done only once per interaction, it is not necessary 
 * to make it fast. Thus we use a freelist and normal malloc, and
 * not myalloc !!!
 */

#ifdef ANSI_C
static INFOBOX alloc_infobox(GNODE v)
#else
static INFOBOX alloc_infobox(v)
GNODE v;
#endif
{
	INFOBOX h;

	debugmessage("alloc_infobox","");

	if (infobox_freelist) {
		h = infobox_freelist;
		infobox_freelist = IBNEXT(infobox_freelist);
	}
	else {	h = (INFOBOX)malloc(sizeof(struct infobox_node));
		if (!h) Fatal_error("memory exhausted","");
	}
	IBNODE(h)    = v;
	IBX(h)       = 0L;
	IBY(h)       = 0L;
	IBWIDTH(h)   = 0;
	IBHEIGHT(h)  = 0;
	IBSTRETCH(h) = 0;
	IBSHRINK(h)  = 0;
	IBINFO(h)    = 0;
	IBNEXT(h)    = NULL;
	IBPREV(h)    = NULL;
	return(h);
}


/* Free all info boxes in the infobox_list
 * ---------------------------------------
 */

#ifdef ANSI_C
void free_infoboxes(void)
#else
void free_infoboxes()
#endif
{
	INFOBOX h;

	debugmessage("free_infoboxes","");

	h = infobox_list;
	if (!h) return;
	while (IBNEXT(h)) h = IBNEXT(h); 
	IBNEXT(h) = infobox_freelist;
	infobox_freelist = h;
	infobox_list    = NULL;
	infobox_listend = NULL;
}


/* Delete one info box from the infobox_list
 * -----------------------------------------
 */

#ifdef ANSI_C
static void delete_infobox(INFOBOX b)
#else
static void delete_infobox(b)
INFOBOX b;
#endif
{
	debugmessage("delete_infobox","");

	if (!IBPREV(b)) infobox_list    = IBNEXT(b);
	else IBNEXT(IBPREV(b)) = IBNEXT(b); 
	if (!IBNEXT(b)) infobox_listend = IBPREV(b);
	else IBPREV(IBNEXT(b)) = IBPREV(b); 
	IBNEXT(b) = infobox_freelist;
	IBPREV(b) = NULL; 
	infobox_freelist = b;
}



/* Append one info box to the infobox_list
 * ---------------------------------------
 */

#ifdef ANSI_C
static INFOBOX append_infobox(GNODE v)
#else
static INFOBOX append_infobox(v)
GNODE v;
#endif
{
	INFOBOX h;

	debugmessage("append_infobox","");

	h = alloc_infobox(v);
	/* IBNEXT(h) == NULL */
	IBPREV(h) = infobox_listend;
	if (infobox_listend) IBNEXT(infobox_listend) = h;
	infobox_listend = h;
	if (!infobox_list) infobox_list = h;
	return(h);
}


/*--------------------------------------------------------------------*/
/*  Action with info boxes					      */
/*--------------------------------------------------------------------*/

/*  Check whether an info box is closed
 *  -----------------------------------
 *  This is the case, if the mouse click coordinate are inside the
 *  info box. Then, we delete the box from the infobox list and
 *  return 1, otherwise we return 0.
 */
 
#ifdef ANSI_C
int search_and_close_infobox(long x, long y)
#else
int search_and_close_infobox(x, y)
long x, y;
#endif
{
	INFOBOX h;
	long xpos, ypos;
	int x1,y1;

	debugmessage("search_and_close_infobox","");

	/* x,y is the position in the graph */
	if (fisheye_view) {
		fe_g_to_s(x, y, &x1, &y1);
		x = x1;
		y = y1;
	}
	else {
		x = x*(long)G_stretch/(long)G_shrink - V_xmin;
		y = y*(long)G_stretch/(long)G_shrink - V_ymin;
	}
	/* Now, x, y is the position on the screen */

	h = infobox_listend;
	while (h) {
		xpos = IBX(h);
		ypos = IBY(h);
		/* xpos,ypos are the positions in the graph */
		if (fisheye_view) {
			fe_g_to_s(xpos, ypos, &x1, &y1);
			xpos = x1;
			ypos = y1;
		}
		else {
			xpos = xpos*(long)G_stretch/(long)G_shrink - V_xmin;
			ypos = ypos*(long)G_stretch/(long)G_shrink - V_ymin;
		}
		/* Now, xpos, ypos are the positions on the screen */

		if (   (xpos<=x) && (xpos+(long)IBWIDTH(h) >=x) 
		    && (ypos<=y) && (ypos+(long)IBHEIGHT(h)>=y)) break; 
		h = IBPREV(h);
	}
	if (h) {
		delete_infobox(h);
		return(1);
	}
	return(0);
}



/*  Draw all open info boxes
 *  ------------------------
 */
 
#ifdef ANSI_C
void draw_infoboxes(void)
#else
void draw_infoboxes()
#endif
{
	INFOBOX h;

	debugmessage("draw_infoboxes","");

	h = infobox_list;
	while (h) {
		draw_one_infobox(h);
		h = IBNEXT(h);
	}
}



/*  Open an info box for node v
 *  ---------------------------
 *  The box is scaled to a/b, drawn at position (x,y) in the graph.
 *  We append the box to the infobox_list and draw the box.
 */

#ifdef ANSI_C
void gs_infobox(GNODE v,long x, long y, int a,int b,int info)
#else
void gs_infobox(v,x,y,a,b,info)
GNODE	v;
long	x,y;
int	a,b,info;
#endif
{
	int	x1, y1, w, h;
	INFOBOX hh;
	float f1, f2;

	debugmessage("gs_infobox","");

	assert((b!=0));
	gs_setshrink(a,b);
	switch (info) {
		case 1: gs_calcstringsize(NINFO1(v)); break;
		case 2: gs_calcstringsize(NINFO2(v)); break;
		case 3: gs_calcstringsize(NINFO3(v)); break;
		case 8: gs_calcstringsize(NLABEL(v)); break;
		case 7: gs_stringw = 35*8; 
			gs_stringh = 15*16;
			break;
		default: assert((0));
	}
	h = gs_stringh + 10 * a/b;
	w = gs_stringw + 10 * a/b;

	/* First look whether this node is already in the info box */
	hh = infobox_list;
	while (hh) {
		if (IBNODE(hh)==v) break;
		hh = IBNEXT(hh);
	}
	if (hh) {
		x1 = IBWIDTH(hh) -10*IBSTRETCH(hh)/IBSHRINK(hh);
		y1 = IBHEIGHT(hh)-10*IBSTRETCH(hh)/IBSHRINK(hh);
		if (gs_stringw==0)  f1 = (float)a/(float)b; 
		else f1 = (float)x1*(float)a/((float)gs_stringw*b);
		if (gs_stringh==0)  f2 = (float)a/(float)b;
		else f2 = (float)y1*(float)a/((float)gs_stringh*b);
		w = IBWIDTH(hh);
		h = IBHEIGHT(hh);
		if (f2<f1) f1 = f2;
		a = (int)(f1*100.0);
		b = 100;
		delete_infobox(hh);
	}

	hh = append_infobox(v);

	IBSTRETCH(hh) = a;
	IBSHRINK(hh)  = b;
	IBINFO(hh)    = info;

	IBX(hh)       = x;
	IBY(hh)       = y;
	IBWIDTH(hh)   = w;
	IBHEIGHT(hh)  = h;

	draw_one_infobox(hh);
}


/*--------------------------------------------------------------------*/

 
/*  Draw an info box border 
 *  -----------------------
 *  draw a border line of thickness t around a box at (x,y).
 *  The box has width w and height h. The drawing color is c.
 *  NO SCALING !!!
 */

#ifdef ANSI_C
static void	draw_infoborder(long x,long y,int w,int h,int t,int c)
#else
static void	draw_infoborder(x, y, w, h, t, c)
long x, y;
int  w, h, t, c;
#endif
{
	long mx,my;
	int  mw,mh;

	mx = x;
	my = y;
	mw = w;
	mh = h;
	/* Check visibility */
	if (x           >=V_xmax)  return;
	if (y	        >=V_ymax)  return;
	if (x+(long)w   < V_xmin)  return;
	if (y+(long)h   < V_ymin)  return;
	if (x	        < V_xmin)  { mx = V_xmin; mw = w+(int)(x-V_xmin); }
	if (y	        < V_ymin)  { my = V_ymin; mh = h+(int)(y-V_ymin); }
	if (mx+(long)mw >=V_xmax)  mw = (int)(V_xmax-mx)-1;
	if (my+(long)mh >=V_ymax)  mh = (int)(V_ymax-my)-1;

	/* We draw the visible part only */ 
	if ((y>=V_ymin)&&(y<V_ymax)) 
		gs_rectangle(mx, y, mw, t, c);
	if ((x>=V_xmin)&&(x<V_xmax)) 
		gs_rectangle(x, my, t, mh, c);
	if ((y+(long)(h-t)>=V_ymin)&&(y+(long)(h-t)<V_ymax)) 
		gs_rectangle(mx, y + (long)(h - t), mw, t, c);
	if ((x+(long)(w-t)>=V_xmin)&&(x+(long)(w-t)<V_xmax)) 
		gs_rectangle(x + (long)(w - t), my, t, mh, c);
}


/*  Draw a boxed info field for node v
 *  ----------------------------------
 *  The box is scaled to a/b, drawn near position (myxpos,myypos). 
 *  The text of the box is centered.
 */

static char myspecbuffer[50];

#ifdef ANSI_C
static void  draw_one_infobox(INFOBOX b)
#else
static void  draw_one_infobox(b)
INFOBOX b;
#endif
{
	int  	oldfev;
	GNODE	v;
	long	x,y;
	int	w,h,info;
	int	x1, y1;

	gs_setshrink(IBSTRETCH(b),IBSHRINK(b));
	v    = IBNODE(b);
	info = IBINFO(b);
	x    = IBX(b);
	y    = IBY(b);
	w    = IBWIDTH(b);
	h    = IBHEIGHT(b);

	if (fisheye_view) {
		fe_g_to_s(x, y, &x1, &y1);
		x = x1;
		y = y1;
	}
	else {
		x = x * (long)G_stretch/(long)G_shrink;
		y = y * (long)G_stretch/(long)G_shrink;
	}

	oldfev = fisheye_view;
	fisheye_view = 0;

	/* clear background with color of node */
	gs_rectangle(x,y,w,h,WHITE);
	gs_actbackground = WHITE;
	/* draw border */
	draw_infoborder(x,y,w,h,3,BLACK);

	/* calc string position */
	gs_setto(x + (long)(5 * IBSTRETCH(b)/IBSHRINK(b)), 
		 y + (long)(5 * IBSTRETCH(b)/IBSHRINK(b)));

	/* print string */
	switch (info) {
		case 1: gs_printstr(NINFO1(v),BLACK); break;
		case 2: gs_printstr(NINFO2(v),BLACK); break;
		case 3: gs_printstr(NINFO3(v),BLACK); break;
		case 8: gs_printstr(NLABEL(v),BLACK); break;
	}
	if (info<7)  { fisheye_view = oldfev; return; }
	if (info==8) { fisheye_view = oldfev; return; } 
	SPRINTF(myspecbuffer,"title:         %-20s\n",NTITLE(v));
	gs_printstr(myspecbuffer,BLACK);
	SPRINTF(myspecbuffer,"refnum:        %-8ld\n",NREFNUM(v));
	gs_printstr(myspecbuffer,BLACK);
	SPRINTF(myspecbuffer,"shape:         %-20s\n",
					shape_text(NSHAPE(v)));
	gs_printstr(myspecbuffer,BLACK);
	SPRINTF(myspecbuffer,"textmode:      %-20s\n",
					textmode_text(NTEXTMODE(v)));
	gs_printstr(myspecbuffer,BLACK);
	SPRINTF(myspecbuffer,"(x,y):         (%ld,%ld)\n",NX(v),NY(v));
	gs_printstr(myspecbuffer,BLACK);
	SPRINTF(myspecbuffer,"vert.order:    %d -> %d\n",NLEVEL(v),NTIEFE(v));
	gs_printstr(myspecbuffer,BLACK);
	SPRINTF(myspecbuffer,"hor.order:     %d -> %d\n",NHORDER(v),NPOS(v));
	gs_printstr(myspecbuffer,BLACK);
	SPRINTF(myspecbuffer,"width:         %-8d\n",NWIDTH(v));
	gs_printstr(myspecbuffer,BLACK);
	SPRINTF(myspecbuffer,"height:        %-8d\n",NHEIGHT(v));
	gs_printstr(myspecbuffer,BLACK);
	SPRINTF(myspecbuffer,"borderwidth:   %-8d\n",NBORDERW(v));
	gs_printstr(myspecbuffer,BLACK);
	SPRINTF(myspecbuffer,"color:         %-20s\n",color_text(NCOLOR(v)));
	gs_printstr(myspecbuffer,BLACK);
	SPRINTF(myspecbuffer,"textcolor:     %-20s\n",color_text(NTCOLOR(v)));
	gs_printstr(myspecbuffer,BLACK);
	SPRINTF(myspecbuffer,"bordercolor:   %-20s\n",color_text(NBCOLOR(v)));
	gs_printstr(myspecbuffer,BLACK);
	SPRINTF(myspecbuffer,"stretch/shrink:%d/%d\n",NSTRETCH(v),NSHRINK(v));
	gs_printstr(myspecbuffer,BLACK);

	fisheye_view = oldfev; 
	
}

