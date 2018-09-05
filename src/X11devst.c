/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */ 
/*		--------------------------------------		      */ 
/*								      */
/*   file:	   X11devst.c 	 				      */
/*   version:	   1.00.00					      */
/*   creation:	   01.2.95					      */
/*   author:	   G. Sander (Version 1.00.00-...)		      */ 
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */ 
/*   description:  X11 device driver, font buffering routines         */ 
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/


#ifndef lint
static char *id_string="$Id: X11devst.c,v 1.1 1995/02/08 11:11:14 sander Exp $";
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
 * $Log: X11devst.c,v $
 * Revision 1.1  1995/02/08  11:11:14  sander
 * Initial revision
 *
 *
 */

/************************************************************************
 *  This is the font buffering routine of the X11 device driver.
 *  This is used for speedup.
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"

#ifdef X11

#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/Xproto.h>
#include <ctype.h>
#include <math.h>

#include "main.h"
#include "options.h"
#include "alloc.h"
#include "grprint.h"
#include "drawlib.h"
#include "fisheye.h"



/* Prototypes
 * ==========
 */

void            enable_font_buffering   _PP((void));
void            disable_font_buffering  _PP((void));
int             set_fontbuffer          _PP((int stretch, int shrink));
void            draw_fast_char          _PP((int a,int c,int x,int y));
void            finish_fast_chars       _PP((void));

void 		alloc_all_fontbuffers
	_PP((Display *rd, int rs, Drawable dw, GC gc, unsigned long *ca));
static Pixmap   alloc_fontbuffer        _PP((Display *rd, int rs));
static void     fill_fontbuffer         _PP((int buf, int stretch, int shrink));
void            new_scale_fontbuffers   _PP((int stretch, int shrink));
static void     charbuffer_draw         _PP((int c));


/*--------------------------------------------------------------------*/
/*  Character buffering                                               */
/*--------------------------------------------------------------------*/

/* One large problem with X11 is, that it is ridiculus slow.
 * Especially drawing characters may be improved, if we buffer
 * the character shape and perform bitmap plane copies instead 
 * of drawing characters line by line.
 * 
 * Thus, for small fontsizes, we buffer the fonts, i.e. store 
 * the whole character set in a bitmap and only copy the characters
 * to the pix_window.
 * We use for buffers. The first has the absolute scale factor 1.
 * The second has the relative scale factor 1. 
 * The others have scale factors as determined dynamically during
 * drawing.
 * We use buffering until a scaling factor of 2.
 */

#define MAX_FONTBUFS 6

static Pixmap font_buffer[MAX_FONTBUFS];

static  GC        fbuf_GC;
static  XGCValues fbuf_GCvalues;

static int fbuf_shrink[MAX_FONTBUFS];
static int fbuf_stretch[MAX_FONTBUFS];
static int fbuf_filled[MAX_FONTBUFS];

static int font_buffering = 1;

static int act_font_buffer;
static int act_font_width;
static int act_font_height;

#define FBUF_BLACK 1
#define FBUF_WHITE 0

static Display *root_display;
static int      root_screen;
static Drawable pix_dw = 0;
static GC       pix_GC;
static unsigned long *carray;

/* Enable or disable font buffering
 * ================================
 */

#ifdef ANSI_C
void enable_font_buffering(void)
#else
void enable_font_buffering()
#endif
{
	font_buffering = 1;
}

#ifdef ANSI_C
void disable_font_buffering(void)
#else
void disable_font_buffering()
#endif
{
	font_buffering = 0;
}


/* Allocate all fontbuffers
 * ========================
 */

#ifdef ANSI_C
void alloc_all_fontbuffers(
	Display *rd, int rs, Drawable dw, GC gc, unsigned long *ca)
#else
void alloc_all_fontbuffers(rd, rs, dw, gc, ca)
Display *rd; 
int rs;
Drawable dw;
GC gc;
unsigned long *ca;
#endif
{
	int i;

	root_display = rd;
	root_screen  = rs;
	pix_dw = dw;
	pix_GC = gc;
	carray = ca;
	for (i=0; i<MAX_FONTBUFS; i++) {
		font_buffer[i] = alloc_fontbuffer(rd, rs);
		fbuf_filled[i] = 0;
	}
        fbuf_GCvalues.graphics_exposures = False;
        fbuf_GCvalues.foreground = FBUF_BLACK;
        fbuf_GCvalues.background = FBUF_WHITE;
	fbuf_GC = XCreateGC(rd, (Drawable)(font_buffer[0]),
		GCGraphicsExposures | GCForeground | GCBackground, 
		&fbuf_GCvalues);
	set_fe_scaling(G_stretch,G_shrink);
	new_scale_fontbuffers(G_stretch,G_shrink);
}


/* Allocate a fontbuffer and return it
 * -----------------------------------
 */

#ifdef ANSI_C
static Pixmap alloc_fontbuffer(Display *rd, int rs)
#else
static Pixmap alloc_fontbuffer(rd, rs)
Display *rd; 
int rs;
#endif
{
	Pixmap p;

        p = XCreatePixmap(rd,
                        (Drawable)RootWindow(rd, rs), 
                        (unsigned int)(256*8*2),
                        (unsigned int)(16*2),
                        (unsigned int)1);
	return(p);
}


/* Fill a fontbuffer buf
 * =====================
 * The scaling factors are shrink and stretch.
 */


static int bufstretch; /* local updates of scaling factors */
static int bufshrink;

#ifdef ANSI_C
static void fill_fontbuffer(int buf,int stretch,int shrink)
#else
static void fill_fontbuffer(buf,stretch,shrink)
int buf;
int stretch;
int shrink;
#endif
{
	int i;

	if (buf>=MAX_FONTBUFS) return;
	if (fbuf_filled[buf])  return;
	bufstretch = stretch;
	bufshrink  = shrink;
	XSetForeground(root_display, fbuf_GC, FBUF_WHITE);
	XFillRectangle(root_display,
               	(Drawable)font_buffer[buf],
               	fbuf_GC,
		0, 
		0, 
		256*8*2, 16*2);
	XSetForeground(root_display, fbuf_GC, FBUF_BLACK);
	act_font_buffer = buf;
	for (i=0; i<128; i++) charbuffer_draw(i);
	fbuf_filled[buf]  = 1;
	fbuf_shrink[buf]  = shrink;
	fbuf_stretch[buf] = stretch;
}

/* Set a new shrink/stretch value
 * ==============================
 */

#ifdef ANSI_C
void new_scale_fontbuffers(int stretch, int shrink)
#else
void new_scale_fontbuffers(stretch,shrink)
int stretch;
int shrink;
#endif
{
	int i;

	for (i=1; i<MAX_FONTBUFS; i++) fbuf_filled[i] = 0;
	fill_fontbuffer(0,1,1);
	if (stretch>2*shrink) return;
	if ((stretch!=1)||(shrink!=1)) fill_fontbuffer(1,stretch,shrink);
}


/* Set a new scaling value for font buffering 
 * ==========================================
 * We return 1 on success and 0 on failure.
 * Further, we set act_font_buffer to the number of the buffer, that
 * contains this font.
 */

#ifdef ANSI_C
int set_fontbuffer(int stretch,int shrink)
#else
int set_fontbuffer(stretch,shrink)
int stretch;
int shrink;
#endif
{
	int i;

	if (fisheye_view!=0)  return(0);
	if (!font_buffering)  return(0);
	if (stretch>2*shrink) return(0);
	act_font_width  = 8*stretch/shrink;
	act_font_height = 16*stretch/shrink;
	for (i=0; i<MAX_FONTBUFS; i++) {
		if (   fbuf_filled[i] 
		    && (fbuf_stretch[i]==stretch) && (fbuf_shrink[i]==shrink)) {
			act_font_buffer = i;
			return(1);
		}
	}
	for (i=0; i<MAX_FONTBUFS; i++) {
		if (!fbuf_filled[i]) { 
			fill_fontbuffer(i,stretch,shrink);
			act_font_buffer = i;
			return(1);
		}
	}
	act_font_buffer = 0;
	return(0);
}


/* Draw a buffered character
 * =========================
 */

#ifdef ANSI_C
void draw_fast_char(int color,int c,int xpos,int ypos)
#else
void draw_fast_char(color,c,xpos,ypos)
int color;
int c;
int xpos;
int ypos;
#endif
{
	XSetForeground(root_display, pix_GC, carray[color]);
	XSetBackground(root_display, pix_GC, carray[gs_actbackground]);
	XCopyPlane(root_display,
               	   (Drawable)font_buffer[act_font_buffer],
		   pix_dw,
               	   pix_GC,
		   c * 8*2, 0,
		   act_font_width,
		   act_font_height,
		   xpos-V_xmin, ypos-V_ymin, 1); 
}


/* After drawing a sequence of chars, we should do this:
 * -----------------------------------------------------
 */

#ifdef ANSI_C
void finish_fast_chars(void)
#else
void finish_fast_chars()
#endif
{
	/* XSync(root_display, 0); */
}


/*  Turtle graphics cursor positions
 *  --------------------------------
 *  The relative origin of the turtle graphics is (bufxpos,bufypos).  
 *  All co-ordinates of the turtle graphics are scaled offsets to this
 *  origin.
 *  The actual position of the turtle is (bufactxpos, bufactypos). 
 */

static int bufxpos,bufypos;
static int bufactxpos, bufactypos;

/*  Turtle graphics primitiva 
 *  -------------------------
 */

/* 
 *  Set turtle to (x,y) relatively to the origin (bufxpos,bufypos).
 */

#ifdef ANSI_C
static void bufsetto(int x,int y)
#else
static void bufsetto(x,y)
int x,y;
#endif
{
	int s=bufstretch;
	int t=bufshrink;
	bufactxpos = bufxpos+(s*x)/t;
	bufactypos = bufypos+(s*y)/t;
}

/* 
 *  Move the turtle from its actual position to (x,y) relatively to 
 *  the origin (bufxpos,bufypos). Draw this movement with color c.
 */

#ifdef ANSI_C
static void bufmoveto(int x,int y)
#else
static void bufmoveto(x,y)
int x,y;
#endif
{
	int s=bufstretch;
	int t=bufshrink;
	int a = bufxpos+(s*x)/t;
	int b = bufypos+(s*y)/t;
	XDrawLine(root_display,
               	(Drawable)font_buffer[act_font_buffer],
                fbuf_GC,
		bufactxpos,
		bufactypos,
		a,b);
	bufactxpos = a;
	bufactypos = b;
}



/*--------------------------------------------------------------------*/
/*   Character drawing routine                                        */
/*--------------------------------------------------------------------*/

/*  The module drawchr.h contains the definition of the characters.
 *  The advantage of including it here is, that the C compiler will be
 *  able to inline the turtle graphic routines.
 */


#define mysetto(a,b)      bufsetto(a,b)
#define mymoveto(a,b,c)   bufmoveto(a,b)

#include "drawchr.h"


/* Draw a character into a buffer
 * ==============================
 * The following is copied and modified from drawlib.c.
 */


#ifdef ANSI_C
static void charbuffer_draw(int c)
#else
static void charbuffer_draw(c)
int c;
#endif
{
	assert((c<128));
	bufxpos = bufactxpos = c * 8 * 2;
	bufypos = bufactypos = 0;
	myasciichar(c, 0);

	bufxpos = bufactxpos = (128 + c) * 8 * 2;
	bufypos = bufactypos = 0;
	myisochar(c, 0);
}


/*--------------------------------------------------------------------*/

#endif /* X11 */

