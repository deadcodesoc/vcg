/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */
/*		--------------------------------------		      */
/*								      */
/*   file:	   X11devpb.c					      */
/*   version:	   1.00.00					      */
/*   creation:	   9.4.93					      */
/*   author:	   I. Lemke  (...-Version 0.99.99)		      */
/*		   G. Sander (Version 1.00.00-...)		      */
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */
/*   description:  Device driver for X11, Export Dialog Box	      */
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/

#ifndef lint
static char *id_string="$Id: X11devpb.c,v 1.9 1995/02/08 11:11:14 sander Exp $";
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
 * $Log: X11devpb.c,v $
 * Revision 1.9  1995/02/08  11:11:14  sander
 * Distribution version 1.3.
 *
 * Revision 1.8  1994/12/23  18:12:45  sander
 * Manhatten layout added.
 * Option interface cleared.
 * infobox behaviour improved.
 * First version of fisheye (carthesian).
 * Options Noedge and nonode.
 *
 * Revision 1.7  1994/11/25  15:43:29  sander
 * Printer interface added to allow to use VCG as a converter.
 *
 * Revision 1.6  1994/11/23  14:50:47  sander
 * Drawing speed improved by removing some superfluous XSyncs.
 *
 * Revision 1.5  1994/08/03  13:58:44  sander
 * Horizontal order mechanism changed.
 * Attribute horizontal_order for edges added.
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
 * Small corrections: Flickering of the box removed.
 *
 * Revision 1.1  1994/04/27  16:05:19  sander
 * Initial revision
 *
 *
 */

/************************************************************************
 * Device driver for X11: Export Dialog Box    
 * ----------------------------------------
 *
 * This module contains the management of the dialog box that appears
 * if we export the graph to pbm, ppm or PostScript. 
 * 
 * This file provides the following functions:
 * ------------------------------------------
 *
 *    x11_init_dialog(rd,rs)      initialize the dialogbox.
 *    x11_destroy_dialog(rd,rs)   destroys   the dialogbox.
 *
 *    x11_print_dialog(rminx, rminy, rmaxx, rmaxy)
 *
 *    This function takes the region border lines, opens the dialog
 *    box and asks for information about the type of output.
 *    It returns the scale factor, output size etc. in global 
 *    variables.
 *
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
#include "X11devpb.h"


/*--------------------------------------------------------------------*/

#undef EVENT_DEBUG


/* Prototypes
 * ----------
 */

void    gs_exit         _PP((int x));
void    do_gblExpose    _PP((XEvent *eventp));
void    do_gblConfigureNotify  _PP((XEvent *eventp));


static void   allocateDialogBox         _PP((void));
static Window allocate_selection_point  _PP((int x,int y));
static Window allocate_button		_PP((int x,int y));
static Window allocate_general_button   _PP((int x,int y,int w,int h));
static Window allocate_scroll_bar	_PP((int x,int y));

static void draw_dialog_box     _PP((void));
static void draw_text           _PP(( int x, int y, char *m));
static void draw_dialog_point   _PP((Window w, int color));
static void draw_sizes		_PP((void));


#ifdef EVENT_DEBUG
static void prologue    _PP((XEvent *eventp, char *event_name));
#else
#define prologue(a,b)
#endif

static void     dialog_main_loop        _PP((void));
static void     do_KeyPress             _PP((XEvent *eventp));
static void     do_ButtonPress          _PP((XEvent *eventp));
static void     do_ButtonRelease        _PP((XEvent *eventp));
static void     do_EnterNotify          _PP((XEvent *eventp));
static void     do_LeaveNotify          _PP((XEvent *eventp));
static void     do_Expose               _PP((XEvent *eventp));
static void     do_ConfigureNotify      _PP((XEvent *eventp));
static void     do_MotionNotify         _PP((XEvent *eventp));

static void 	read_xdpiscrollbar	_PP((int val));
static void 	set_xdpiscrollbar	_PP((void));
static void 	set_xdpi		_PP((int val));
static void 	read_ydpiscrollbar	_PP((int val));
static void 	set_ydpiscrollbar	_PP((void));
static void 	set_ydpi		_PP((int val));
static void 	read_scalescrollbar	_PP((int val));
static void 	set_scalescrollbar	_PP((void));
static void 	read_widthscrollbar	_PP((int val));
static void 	set_widthscrollbar	_PP((void));
static void 	read_heightscrollbar	_PP((int val));
static void 	set_heightscrollbar	_PP((void));

static void 	read_marginpanner	_PP((int valx,int valy));
static void 	read_marginxpanner	_PP((int valx,int valy));
static void 	set_marginpanner	_PP((void));

#endif /* X11 */

static void 	calc_paper_size	_PP((void));
static int 	refocus_dpi	_PP((int x));
static float    refocus_scale	_PP((float x));



/* Variables
 * ---------
 */


/* Actual output type: 1 = PBM, 2 = PPM, 3 = PS */

int act_output_type = 1;

/* Actual color: 1 = color,  2 = grey,  3 = bw */

int act_color_type = 3;

/* Actual orientation: 1 = portrait,  2 = landscape */

int act_ori_type = 1;

/* Actual paper size:   1 = A4, 2 = B5, 3 = A5, 4 = 11x17, 
 * 		  	5 = 8.5x11, 6 = 8.5x14 
 */

int act_paper_type = 1;

static float maxx, maxy;

/* Actual page repetitor */

int act_paper_num = 1;

/* Actual size (cm) */

float act_width  = 20.0;
float act_height = 20.0;

/* Margins (cm) */

float act_left_margin   = 0.0;
float act_right_margin  = 0.0;
float act_top_margin    = 0.0;
float act_bottom_margin = 0.0;

/* Dpi */

int act_xdpi;
int act_ydpi;

/* Scaling */

float act_scaling = 1.0;

/* Region */

static int rgx1, rgy1, rgx2, rgy2;

/* Bounding box: yes or no (?) */

int   act_bbox = 1;


#ifdef X11

/* Dialog handling */

static int dialog_notready = 1;
static int dialog_success  = 0;

/* Root displays */

static Display *root_display;	/* Root display          */
static int      root_screen;	/* and its screen number */


/* Windows */

static Window	dialog_window;

static Window   pbm_point;
static Window   ppm_point;
static Window   ps_point;
static Window   color_point;
static Window   grey_point;
static Window   bw_point;
static Window   portr_point;
static Window   landsc_point;
static Window   pa4_point;
static Window   pb5_point;
static Window   pa5_point;
static Window   p11x17_point;
static Window   p8x11_point;
static Window   p8x14_point;
static Window   scale1_point;
static Window   maxspect_point;
static Window   center_point;
static Window   centerx_point;
static Window   centery_point;
static Window   dpi300_point;
static Window   dpi400_point;
static Window   dpi180_point;
static Window   bbox_point;

static Window   okay_button;
static Window   cancel_button;

static Window   pn1_point;
static Window   pn2_point;
static Window   pn3_point;
static Window   pn4_point;
static Window   pn5_point;

static Window	xdpiscrollbar;
static Window	ydpiscrollbar;
static Window	scalescrollbar;
static Window	widthscrollbar;
static Window	heightscrollbar;

static Window	xdpiscrolltmb;
static Window	ydpiscrolltmb;
static Window	scalescrolltmb;
static Window	widthscrolltmb;
static Window	heightscrolltmb;

static Window	marginpanner;
static Window	marginmiddle;
static Window	margintmb;


/* Cursors */

static Cursor scrollCursor; 

/* Mouse Buttons */

#define G_MOUSE_LEFT  1
#define G_MOUSE_RIGHT 3


/* the panel font */

extern char Xfontname[512];
static  XFontStruct *dialog_font = NULL;

/* Flag wheter the dialog_box is initialized */

static int dialog_box_there = 0;


#define DIAL_W   540
#define DIAL_H   410

#define POINT_W  10 

#define SCROLL_W  240 
#define SCROLLBAR_LEN 20

#define PANNER_W 150
#define PANNER_H 150

/*--------------------------------------------------------------------*/
/*  Dialog box initialization and entry points                        */
/*--------------------------------------------------------------------*/

/*  Initialize the dialog box 
 *  -------------------------
 *  This is done once at the beginning.
 */

#ifdef ANSI_C
void 	x11_init_dialog(Display *rd, int rs)
#else
void 	x11_init_dialog(rd, rs)
Display *rd;
int rs;
#endif
{
	if (dialog_box_there) return;
	root_display = rd;
	root_screen  = rs;
	dialog_font = XLoadQueryFont(root_display,Xfontname);
	if (!dialog_font) {
		Fatal_error("Font not found. Please use option -font","");
	}

	allocateDialogBox();

	dialog_box_there = 1;

}



/*   Destroy the dialog box 
 *   ----------------------
 *   This is done once on ExitDevice.
 */

#ifdef ANSI_C
void	x11_destroy_dialog(Display *rd, int rs)
#else
void	x11_destroy_dialog(rd, rs)
Display *rd;
int rs;
#endif
{
	if (!dialog_box_there) return;
	XDestroyWindow(root_display,dialog_window);
	dialog_box_there = 0;
}



/*   Allocate the Dialog Box 
 *   -----------------------
 *   Scrollbar-Thumbs are returned in last_tmb;
 */

static Window last_tmb;
static char x11_win_label[1024];

#ifdef ANSI_C
static void allocateDialogBox(void)
#else
static void allocateDialogBox()
#endif
{
	Window rret1, rret2;
	XSetWindowAttributes attr;
	unsigned long mask = 0L;
	int i;
	unsigned int j;
	int xpos, ypos;
	XSizeHints hints;

	/* select for all events */
	attr.event_mask = KeyPressMask           | 
			  ButtonPressMask        | ButtonReleaseMask  |
			  EnterWindowMask        | 
                          ExposureMask           | StructureNotifyMask | 
                          SubstructureNotifyMask | 
                          FocusChangeMask        | OwnerGrabButtonMask;

	attr.background_pixel = XWhitePixel(root_display,root_screen);
	attr.border_pixel = XBlackPixel(root_display,root_screen);

	mask |= (CWBackPixel | CWBorderPixel | CWEventMask);

	(void)XQueryPointer(root_display,RootWindow(root_display, root_screen),
		&rret1, &rret2,&xpos, &ypos, &i, &i, &j); 

	xpos = xpos;
	ypos = ypos;

        dialog_window = XCreateWindow(root_display, 
				      RootWindow(root_display, root_screen), 
				      xpos, ypos,
                           	      DIAL_W, DIAL_H, 
				      Xmyborderwidth, (int)CopyFromParent,
                                      InputOutput, 
				      (Visual *)CopyFromParent,
                           	      mask, &attr);

	hints.flags = PPosition;
	hints.x = xpos;
	hints.y = ypos;

        strcpy(x11_win_label, "VCG ");
        strcat(x11_win_label, Dataname);
        strcat(x11_win_label, " Export");

	XStoreName(root_display, dialog_window, x11_win_label);
	XSetNormalHints(root_display, dialog_window, &hints);

	XDefineCursor(root_display,dialog_window, 
			XCreateFontCursor(root_display,XC_left_ptr));

	scrollCursor = XCreateFontCursor(root_display,XC_sb_h_double_arrow);

	pbm_point = allocate_selection_point(120,8);
	ppm_point = allocate_selection_point(240,8);
	ps_point  = allocate_selection_point(360,8);
	bw_point     = allocate_selection_point(120,26);
	color_point  = allocate_selection_point(240,26);
	grey_point   = allocate_selection_point(360,26);
	portr_point  = allocate_selection_point(120,44);
	landsc_point = allocate_selection_point(240,44);
	pa4_point	= allocate_selection_point(120,62);
	pb5_point	= allocate_selection_point(240,62);
	pa5_point	= allocate_selection_point(360,62);
	p11x17_point	= allocate_selection_point(120,80);
	p8x11_point	= allocate_selection_point(240,80);
	p8x14_point	= allocate_selection_point(360,80);

	pn1_point       = allocate_selection_point(350,268);
	pn2_point       = allocate_selection_point(400,268);
	pn3_point       = allocate_selection_point(450,268);
	pn4_point       = allocate_selection_point(350,286);
	pn5_point       = allocate_selection_point(400,286);

	scale1_point    = allocate_selection_point(180,250);
	maxspect_point  = allocate_selection_point(180,268);
	center_point    = allocate_selection_point(180,286);
	centerx_point   = allocate_selection_point(180,304);
	centery_point   = allocate_selection_point(180,322);
	dpi300_point    = allocate_selection_point(180,340);
	dpi400_point    = allocate_selection_point(180,358);
	dpi180_point    = allocate_selection_point(180,376);
	bbox_point      = allocate_selection_point(180,340);

	cancel_button = allocate_button(350,320);
	okay_button   = allocate_button(350,365);

	xdpiscrollbar	= allocate_scroll_bar(280,152);
	xdpiscrolltmb   = last_tmb;
	ydpiscrollbar	= allocate_scroll_bar(280,170);
	ydpiscrolltmb   = last_tmb;
	scalescrollbar	= allocate_scroll_bar(280,188);
	scalescrolltmb  = last_tmb;
	widthscrollbar	= allocate_scroll_bar(280,206);
	widthscrolltmb  = last_tmb;
	heightscrollbar	= allocate_scroll_bar(280,224);
	heightscrolltmb = last_tmb;

        /* select for all events */
        attr.event_mask = KeyPressMask           | ButtonMotionMask   |
                          ButtonPressMask        | ButtonReleaseMask  |
                          EnterWindowMask        | LeaveWindowMask    |
                          ExposureMask           | ResizeRedirectMask |
                          SubstructureNotifyMask |
                          FocusChangeMask        | OwnerGrabButtonMask;

        attr.background_pixel = XBlackPixel(root_display,root_screen);
        attr.border_pixel = XBlackPixel(root_display,root_screen);

        mask |= (CWBackPixel | CWBorderPixel | CWEventMask);

        marginpanner = XCreateWindow (root_display, dialog_window, 
			   5,246,
                           PANNER_W+1, PANNER_H+1,
                           1, (int)CopyFromParent,
                           InputOutput,
                           (Visual *)CopyFromParent,
                           mask, &attr);

        attr.background_pixel = XWhitePixel(root_display,root_screen);
        attr.border_pixel = XBlackPixel(root_display,root_screen);

        marginmiddle = XCreateWindow (root_display, marginpanner, 
			   0,0,
                           PANNER_W-5, PANNER_H-5,
                           1, (int)CopyFromParent,
                           InputOutput,
                           (Visual *)CopyFromParent,
                           mask, &attr);
        margintmb = XCreateWindow (root_display, marginmiddle, 
			   5,5, 20, 20,
                           1, (int)CopyFromParent,
                           InputOutput,
                           (Visual *)CopyFromParent,
                           mask, &attr);

}



/*  Allocate an selection point (button or radio button)
 *  ----------------------------------------------------
 */

#ifdef ANSI_C
static Window allocate_selection_point(int x,int y)
#else
static Window allocate_selection_point(x,y)
int x, y;
#endif
{
	return(allocate_general_button(x,y,POINT_W,POINT_W));
}



/*  Allocate an selection point (button or radio button)
 *  ----------------------------------------------------
 */

#ifdef ANSI_C
static Window allocate_button(int x,int y)
#else
static Window allocate_button(x,y)
int x, y;
#endif
{
	return(allocate_general_button(x,y,170,25));
}



/*  Allocate a general button or point
 *  ----------------------------------
 */

#ifdef ANSI_C
static Window allocate_general_button(int x,int y,int w,int h)
#else
static Window allocate_general_button(x,y,w,h)
int x, y, w, h;
#endif
{
	Window ww;
	XSetWindowAttributes attr;
	unsigned long mask = 0L;

	/* select for all events */
	attr.event_mask = KeyPressMask           | 
			  ButtonPressMask        | ButtonReleaseMask   |
			  EnterWindowMask        | LeaveWindowMask     |
                          ExposureMask           | StructureNotifyMask | 
                          SubstructureNotifyMask | 
                          FocusChangeMask        | OwnerGrabButtonMask;

	attr.background_pixel = XWhitePixel(root_display,root_screen);
	attr.border_pixel = XBlackPixel(root_display,root_screen);

	mask |= (CWBackPixel | CWBorderPixel | CWEventMask);

	ww = XCreateWindow(root_display,
			dialog_window,
			x,y,
			w,h,
			1, (int)CopyFromParent,
			InputOutput,
			(Visual *)CopyFromParent,
			mask, &attr);

	return(ww);
}


/*  Allocate a scroll bar
 *  ---------------------
 */

#ifdef ANSI_C
static Window allocate_scroll_bar(int x,int y)
#else
static Window allocate_scroll_bar(x,y)
int x, y;
#endif
{
	Window w, wt;
	XSetWindowAttributes attr;
	unsigned long mask = 0L;

        /* select for all events */
        attr.event_mask = KeyPressMask           | ButtonMotionMask   |
                          ButtonPressMask        | ButtonReleaseMask  |
                          EnterWindowMask        | LeaveWindowMask    |
                          ExposureMask           | ResizeRedirectMask |
                          SubstructureNotifyMask |
                          FocusChangeMask        | OwnerGrabButtonMask;

        attr.background_pixel = XWhitePixel(root_display,root_screen);
        attr.border_pixel = XBlackPixel(root_display,root_screen);

        mask |= (CWBackPixel | CWBorderPixel | CWEventMask);

        w = XCreateWindow (root_display, dialog_window, x,y,
                           SCROLL_W, 8,
                           1, (int)CopyFromParent,
                           InputOutput,
                           (Visual *)CopyFromParent,
                           mask, &attr);
        wt = XCreateSimpleWindow (root_display, w, 0,0,
                                    SCROLLBAR_LEN, 6,
                                    1,
                                    XWhitePixel(root_display,root_screen),
                                    XBlackPixel(root_display,root_screen));

	XDefineCursor(root_display,w,scrollCursor); 
	
	last_tmb = wt;
	return(w);
}


/*--------------------------------------------------------------------*/
/*   Entry point for the dialog                                       */
/*--------------------------------------------------------------------*/

static int box_exposed;
static int first_exposed = 1;

#ifdef ANSI_C
void x11_print_dialog(int rminx,int rminy,int rmaxx,int rmaxy)
#else
void x11_print_dialog(rminx, rminy, rmaxx, rmaxy)
int rminx, rminy, rmaxx, rmaxy;
#endif
{
	XEvent event;
        int i, x, y;
        Window rret1, rret2;
        unsigned int j;

        if (first_exposed) {
                first_exposed = 0;
                (void)XQueryPointer(root_display,RootWindow(root_display, root_screen),
                        &rret1, &rret2,&x, &y, &i, &i, &j);
                XMoveWindow(root_display,dialog_window, x, y);
        }

	box_exposed = 0;
	act_output_type = 0;
	if ((rminx==0)&&(rminy==0)&&(rmaxx==0)&&(rmaxy==0)) return;

	set_of_region(rminx, rminy, rmaxx, rmaxy);

        XMapRaised(root_display, dialog_window);
        XMapRaised(root_display, pbm_point);
        XMapRaised(root_display, ppm_point);
        XMapRaised(root_display, ps_point);
        XMapRaised(root_display, color_point);
        XMapRaised(root_display, grey_point);
        XMapRaised(root_display, bw_point);
        XMapRaised(root_display, portr_point);
        XMapRaised(root_display, landsc_point);
        XMapRaised(root_display, pa4_point);
        XMapRaised(root_display, pb5_point);
        XMapRaised(root_display, pa5_point);
        XMapRaised(root_display, p11x17_point);
        XMapRaised(root_display, p8x11_point);
        XMapRaised(root_display, p8x14_point);
        XMapRaised(root_display, scale1_point);
        XMapRaised(root_display, maxspect_point);
        XMapRaised(root_display, center_point);
        XMapRaised(root_display, centerx_point);
        XMapRaised(root_display, centery_point);
        XMapRaised(root_display, dpi300_point);
        XMapRaised(root_display, dpi400_point);
        XMapRaised(root_display, dpi180_point);
        XMapRaised(root_display, bbox_point);
        XMapRaised(root_display, pn1_point);
        XMapRaised(root_display, pn2_point);
        XMapRaised(root_display, pn3_point);
        XMapRaised(root_display, pn4_point);
        XMapRaised(root_display, pn5_point);

        XMapRaised(root_display, cancel_button);
        XMapRaised(root_display, okay_button);

        XMapRaised(root_display, xdpiscrollbar);
        XMapRaised(root_display, xdpiscrolltmb);
        XMapRaised(root_display, ydpiscrollbar);
        XMapRaised(root_display, ydpiscrolltmb);
        XMapRaised(root_display, scalescrollbar);
        XMapRaised(root_display, scalescrolltmb);
        XMapRaised(root_display, widthscrollbar);
        XMapRaised(root_display, widthscrolltmb);
        XMapRaised(root_display, heightscrollbar);
        XMapRaised(root_display, heightscrolltmb);

        XMapRaised(root_display, marginpanner);
        XMapRaised(root_display, marginmiddle);
        XMapRaised(root_display, margintmb);


	act_output_type = 3;
	act_color_type  = 3;
	act_ori_type    = 1;
	act_paper_type  = 1;
	act_paper_num   = 1;
	act_scaling = 1.0;
	set_xdpi(72);
	set_ydpi(72);

	set_xdpiscrollbar();
	set_ydpiscrollbar();
	set_scalescrollbar();
	set_widthscrollbar();
	set_heightscrollbar();
	set_marginpanner();
        XFlush(root_display);

        /*
         * Wait for Exposure event.
         */
#ifndef ULTRIX
#ifndef AIX
        do { XNextEvent(root_display, &event);
        } while (event.type != Expose && event.type != MapNotify);
#endif
#endif

	draw_dialog_box();
	dialog_main_loop();

        XUnmapWindow(root_display, dialog_window);

	if (dialog_success == 0) act_output_type = 0;
}



/*--------------------------------------------------------------------*/
/*   Redraw routine                                                   */
/*--------------------------------------------------------------------*/

/*  Draw dialog box
 *  ---------------
 */

static char mxbuffer[256];

#ifdef ANSI_C
static void draw_dialog_box(void)
#else
static void draw_dialog_box()
#endif
{
	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XWhitePixel(root_display, root_screen));
	XFillRectangle(root_display, 
		(Drawable)dialog_window,
		XDefaultGC(root_display, root_screen),
		0,0, DIAL_W, DIAL_H);

	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XBlackPixel(root_display, root_screen));
	XDrawString(root_display,
		(Drawable)cancel_button,
		XDefaultGC(root_display, root_screen),
		30,18,"Cancel (Esc)",strlen("Cancel (Esc)"));
	XDrawString(root_display,
		(Drawable)okay_button,
		XDefaultGC(root_display, root_screen),
		65,18,"Okay",strlen("Okay"));

	draw_text(5,18,"Export to ");
	draw_text(140,18,"PBM(1)");
	draw_text(260,18,"PPM(2)");
	draw_text(380,18,"PostScript(3)");

	draw_text(5,36,"Color mode:");

	draw_text(5,54,"Orientation:");
	draw_text(140,54,"portrait");
	draw_text(260,54,"landscape");

	draw_text(5,72,"Paper size:");
	draw_text(140,72,"A4");
	draw_text(260,72,"B5");
	draw_text(380,72,"A5");
	draw_text(140,90,"11\"x17\"");
	draw_text(260,90,"8.5\"x11\"");
	draw_text(380,90,"8.5\"x14\"");

	draw_text(5,108,"Region:");
	SPRINTF(mxbuffer,"(%d,%d) - (%d,%d)  =>  %d X %d pixels",
		rgx1,rgy1,rgx2,rgy2, 
		(rgx2>rgx1?rgx2-rgx1:rgx1-rgx2), 
		(rgy2>rgy1?rgy2-rgy1:rgy1-rgy2));
	draw_text(100,108,mxbuffer);


	draw_dialog_point(scale1_point, 0);
	draw_text(200,260,"Scaling: 100%");
	draw_dialog_point(maxspect_point, 0);
	draw_text(200,278,"Maxspect");
	draw_dialog_point(center_point, 0);
	draw_text(200,296,"Center");
	draw_dialog_point(centerx_point, 0);
	draw_text(200,314,"Center width");
	draw_dialog_point(centery_point, 0);
	draw_text(200,332,"Center height");

	switch (act_output_type) {
	case 1: draw_dialog_point(pbm_point,1);
		draw_dialog_point(ppm_point,0);
		draw_dialog_point(ps_point, 0);
        	XUnmapWindow(root_display, bbox_point);
        	XUnmapWindow(root_display, pn1_point);
        	XUnmapWindow(root_display, pn2_point);
        	XUnmapWindow(root_display, pn3_point);
        	XUnmapWindow(root_display, pn4_point);
        	XUnmapWindow(root_display, pn5_point);
        	XUnmapWindow(root_display, grey_point);
        	XUnmapWindow(root_display, color_point);
		act_color_type=3;
        	XMapRaised(root_display, bw_point);
		draw_text(140,36,"b&w");
        	XMapRaised(root_display, dpi300_point);
		draw_dialog_point(dpi300_point, 0);
		draw_text(200,350,"XY-dpi: 300");
        	XMapRaised(root_display, dpi400_point);
		draw_dialog_point(dpi400_point, 0);
		draw_text(200,368,"XY-dpi: 400");
        	XMapRaised(root_display, dpi180_point);
		draw_dialog_point(dpi180_point, 0);
		draw_text(200,386,"XY-dpi: 180");
		break;
	case 2: draw_dialog_point(pbm_point,0);
		draw_dialog_point(ppm_point,1);
		draw_dialog_point(ps_point, 0);
        	XUnmapWindow(root_display, bbox_point);
        	XUnmapWindow(root_display, pn1_point);
        	XUnmapWindow(root_display, pn2_point);
        	XUnmapWindow(root_display, pn3_point);
        	XUnmapWindow(root_display, pn4_point);
        	XUnmapWindow(root_display, pn5_point);
        	XUnmapWindow(root_display, grey_point);
        	XUnmapWindow(root_display, bw_point);
		act_color_type=1;
        	XMapRaised(root_display, color_point);
		draw_text(260,36,"full color");
        	XMapRaised(root_display, dpi300_point);
		draw_dialog_point(dpi300_point, 0);
		draw_text(200,350,"XY-dpi: 300");
        	XMapRaised(root_display, dpi400_point);
		draw_dialog_point(dpi400_point, 0);
		draw_text(200,368,"XY-dpi: 400");
        	XMapRaised(root_display, dpi180_point);
		draw_dialog_point(dpi180_point, 0);
		draw_text(200,386,"XY-dpi: 180");
		break;
	case 3: draw_dialog_point(pbm_point,0);
		draw_dialog_point(ppm_point,0);
		draw_dialog_point(ps_point, 1);
        	XMapRaised(root_display, pn1_point);
        	XMapRaised(root_display, pn2_point);
        	XMapRaised(root_display, pn3_point);
        	XMapRaised(root_display, pn4_point);
        	XMapRaised(root_display, pn5_point);
		draw_text(350,260,"Split output into");
		draw_text(370,278,"1");
		draw_text(420,278,"4");
		draw_text(470,278,"9");
		draw_text(370,296,"16");
		draw_text(420,296,"25 pages");
        	XMapRaised(root_display, grey_point);
        	XMapRaised(root_display, color_point);
        	XMapRaised(root_display, bw_point);
		draw_text(380,36,"grey");
		draw_text(260,36,"full color");
		draw_text(140,36,"b&w");
		set_xdpi(72);
		set_ydpi(72);
        	XMapRaised(root_display, bbox_point);
		draw_dialog_point(bbox_point, act_bbox);
		draw_text(200,350,"Bounding Box");
        	XUnmapWindow(root_display, dpi300_point);
        	XUnmapWindow(root_display, dpi400_point);
        	XUnmapWindow(root_display, dpi180_point);
		break;
	}

	switch (act_color_type) {
	case 1: draw_dialog_point(color_point,1);
		draw_dialog_point(grey_point, 0);
		draw_dialog_point(bw_point,   0);
		break;
	case 2: draw_dialog_point(color_point,0);
		draw_dialog_point(grey_point, 1);
		draw_dialog_point(bw_point,   0);
		break;
	case 3: draw_dialog_point(color_point,0);
		draw_dialog_point(grey_point, 0);
		draw_dialog_point(bw_point,   1);
		break;
	}

	switch (act_ori_type) {
	case 1: draw_dialog_point(portr_point, 1);
		draw_dialog_point(landsc_point,0);
		break;
	case 2: draw_dialog_point(portr_point, 0);
		draw_dialog_point(landsc_point,1);
		break;
	}

	switch (act_paper_type) {
	case 1: draw_dialog_point(pa4_point,    1);
		draw_dialog_point(pb5_point,    0);
		draw_dialog_point(pa5_point,    0);
		draw_dialog_point(p11x17_point, 0);
		draw_dialog_point(p8x11_point,  0);
		draw_dialog_point(p8x14_point,  0);
		break;
	case 2: draw_dialog_point(pa4_point,    0);
		draw_dialog_point(pb5_point,    1);
		draw_dialog_point(pa5_point,    0);
		draw_dialog_point(p11x17_point, 0);
		draw_dialog_point(p8x11_point,  0);
		draw_dialog_point(p8x14_point,  0);
		break;
	case 3: draw_dialog_point(pa4_point,    0);
		draw_dialog_point(pb5_point,    0);
		draw_dialog_point(pa5_point,    1);
		draw_dialog_point(p11x17_point, 0);
		draw_dialog_point(p8x11_point,  0);
		draw_dialog_point(p8x14_point,  0);
		break;
	case 4: draw_dialog_point(pa4_point,    0);
		draw_dialog_point(pb5_point,    0);
		draw_dialog_point(pa5_point,    0);
		draw_dialog_point(p11x17_point, 1);
		draw_dialog_point(p8x11_point,  0);
		draw_dialog_point(p8x14_point,  0);
		break;
	case 5: draw_dialog_point(pa4_point,    0);
		draw_dialog_point(pb5_point,    0);
		draw_dialog_point(pa5_point,    0);
		draw_dialog_point(p11x17_point, 0);
		draw_dialog_point(p8x11_point,  1);
		draw_dialog_point(p8x14_point,  0);
		break;
	case 6: draw_dialog_point(pa4_point,    0);
		draw_dialog_point(pb5_point,    0);
		draw_dialog_point(pa5_point,    0);
		draw_dialog_point(p11x17_point, 0);
		draw_dialog_point(p8x11_point,  0);
		draw_dialog_point(p8x14_point,  1);
		break;
	}

	switch (act_paper_num) {
	case 1: draw_dialog_point(pn1_point, 1);
	        draw_dialog_point(pn2_point, 0);
	        draw_dialog_point(pn3_point, 0);
	        draw_dialog_point(pn4_point, 0);
	        draw_dialog_point(pn5_point, 0);
		break;
	case 2: draw_dialog_point(pn1_point, 0);
	        draw_dialog_point(pn2_point, 1);
	        draw_dialog_point(pn3_point, 0);
	        draw_dialog_point(pn4_point, 0);
	        draw_dialog_point(pn5_point, 0);
		break;
	case 3: draw_dialog_point(pn1_point, 0);
	        draw_dialog_point(pn2_point, 0);
	        draw_dialog_point(pn3_point, 1);
	        draw_dialog_point(pn4_point, 0);
	        draw_dialog_point(pn5_point, 0);
		break;
	case 4: draw_dialog_point(pn1_point, 0);
	        draw_dialog_point(pn2_point, 0);
	        draw_dialog_point(pn3_point, 0);
	        draw_dialog_point(pn4_point, 1);
	        draw_dialog_point(pn5_point, 0);
		break;
	case 5: draw_dialog_point(pn1_point, 0);
	        draw_dialog_point(pn2_point, 0);
	        draw_dialog_point(pn3_point, 0);
	        draw_dialog_point(pn4_point, 0);
	        draw_dialog_point(pn5_point, 1);
		break;
	}

	draw_text(5,126,"Margins:");
	draw_text(5,162,"X-dpi:");
	draw_text(5,180,"Y-dpi:");
	draw_text(5,198,"Scaling:");
	draw_text(5,216,"Width:");
	draw_text(5,234,"Height:");

	draw_sizes();
	set_xdpiscrollbar();
	set_ydpiscrollbar();
	set_scalescrollbar();
	set_widthscrollbar();
	set_heightscrollbar();
	set_marginpanner();

	XSync(root_display, 0);
}



#ifdef ANSI_C
static void draw_sizes(void)
#else
static void draw_sizes()
#endif
{
	if (act_paper_num>1) {
		act_left_margin    =1.0;
		act_bottom_margin  =1.0;
		act_right_margin   = maxx - act_width -act_left_margin;
		act_top_margin     = maxy - act_height-act_bottom_margin;
	}
	if (act_output_type==3) {
		set_xdpi(72); 
		set_ydpi(72);
		set_xdpiscrollbar();
		set_ydpiscrollbar();
		set_widthscrollbar();
		set_heightscrollbar();
	}
	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XWhitePixel(root_display, root_screen));
	XFillRectangle(root_display, 
		(Drawable)dialog_window,
		XDefaultGC(root_display, root_screen),
		100,112,DIAL_W-100,18);
	XFillRectangle(root_display, 
		(Drawable)dialog_window,
		XDefaultGC(root_display, root_screen),
		100,130,DIAL_W-100,18);

	XFillRectangle(root_display, 
		(Drawable)dialog_window,
		XDefaultGC(root_display, root_screen),
		100,148,170,18);
	XFillRectangle(root_display, 
		(Drawable)dialog_window,
		XDefaultGC(root_display, root_screen),
		100,166,170,18);
	XFillRectangle(root_display, 
		(Drawable)dialog_window,
		XDefaultGC(root_display, root_screen),
		100,184,170,18);
	XFillRectangle(root_display, 
		(Drawable)dialog_window,
		XDefaultGC(root_display, root_screen),
		100,202,170,18);
	XFillRectangle(root_display, 
		(Drawable)dialog_window,
		XDefaultGC(root_display, root_screen),
		100,220,170,18);

	calc_paper_size();

	act_right_margin = maxx - act_width -act_left_margin;
	act_top_margin   = maxy - act_height-act_bottom_margin;

	if (act_right_margin<0) {
		act_right_margin = 0.0;
		act_left_margin = maxx - act_width -act_right_margin;
	}
	if (act_left_margin<0) {
		act_left_margin = 0.0;
		act_right_margin = maxx - act_width -act_left_margin;
	}
	if (act_bottom_margin<0) {
		act_bottom_margin = 0.0;
		act_top_margin   = maxy - act_height-act_bottom_margin;
	}
	if (act_top_margin<0) {
		act_top_margin = 0.0;
		act_bottom_margin   = maxy - act_height-act_top_margin;
	}

	SPRINTF(mxbuffer, "Left: %3.2fcm/%3.2f\" ",
		act_left_margin,  act_left_margin/2.54);
	draw_text(100,126,mxbuffer);
	SPRINTF(mxbuffer, "Right:  %3.2fcm/%3.2f\" ",
		act_right_margin, act_right_margin/2.54);
	draw_text(320,126,mxbuffer);
	SPRINTF(mxbuffer, "Top:  %3.2fcm/%3.2f\" ",
           	act_top_margin,  act_top_margin/2.54);
	draw_text(100,144,mxbuffer);
	SPRINTF(mxbuffer, "Bottom: %3.2fcm/%3.2f\" ",
           	act_bottom_margin,  act_bottom_margin/2.54);
	draw_text(320,144,mxbuffer);

	if (act_output_type==3) SPRINTF(mxbuffer, "---");
	else			SPRINTF(mxbuffer, "%d",act_xdpi);
	draw_text(100,162,mxbuffer);
	if (act_output_type==3) SPRINTF(mxbuffer, "---");
	else			SPRINTF(mxbuffer, "%d",act_ydpi);
	draw_text(100,180,mxbuffer);
	SPRINTF(mxbuffer, "%3.2f %% ", act_scaling*100.0);
	draw_text(100,198,mxbuffer);
	SPRINTF(mxbuffer, "%3.2fcm/%3.2f\" ",
           	act_width,  act_width/2.54);
	draw_text(100,216,mxbuffer);
	SPRINTF(mxbuffer, "%3.2fcm/%3.2f\" ",
           	act_height,  act_height/2.54);
	draw_text(100,234,mxbuffer);
	/* XSync(root_display, 0); */
}



/*  Draw text m into the dialog box at position x, y
 *  ------------------------------------------------
 */

#ifdef ANSI_C
static void draw_text(int x,int y,char *m)
#else
static void draw_text(x,y, m)
int x, y;
char *m;
#endif
{
	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XBlackPixel(root_display, root_screen));
	XDrawString(root_display,
		(Drawable)dialog_window,
		XDefaultGC(root_display, root_screen),
		x,y,m,strlen(m));
}


/*  Draw a dialog point in a color
 *  ------------------------------
 */

#ifdef ANSI_C
static void draw_dialog_point(Window w,int color)
#else
static void draw_dialog_point(w, color)
Window w;
int color;
#endif
{
	if (color==0) {
		XSetForeground(root_display,
			XDefaultGC(root_display, root_screen),
			XWhitePixel(root_display, root_screen));
	}
	else {
		XSetForeground(root_display,
			XDefaultGC(root_display, root_screen),
			XBlackPixel(root_display, root_screen));
	}
	XFillRectangle(root_display,(Drawable)w, 
			XDefaultGC(root_display, root_screen),
			1,1,
			POINT_W-2,POINT_W-2);
	/* XSync(root_display, 0); */
        XFlush(root_display);
}


/*--------------------------------------------------------------------*/
/*  Event handling                                                    */
/*--------------------------------------------------------------------*/

/* The main loop for interaction
 * =============================
 */

#ifdef ANSI_C
static void dialog_main_loop(void)
#else
static void dialog_main_loop()
#endif
{
	XEvent event;

	dialog_notready = 1;
	dialog_success  = 0;
	while (dialog_notready) {

		XNextEvent (root_display, &event);

		if (event.type != Expose)
			box_exposed = 0;

		switch (event.type) {
	  	case KeyPress:
	   		prologue (&event, "KeyPress");
	    		do_KeyPress (&event);
	    		break;
	  	case ButtonPress:
	    		prologue (&event, "ButtonPress");
	    		do_ButtonPress (&event);
	    		break;
	  	case ButtonRelease:
	    		prologue (&event, "ButtonRelease");
	    		do_ButtonRelease (&event);
	    		break;
	  	case EnterNotify:
	    		prologue (&event, "EnterNotify");
			do_EnterNotify(&event);
	    		break;
	  	case LeaveNotify:
	    		prologue (&event, "LeaveNotify");
			do_LeaveNotify(&event);
	    		break;
	  	case FocusIn:
	    		prologue (&event, "FocusIn");
	    		break;
	  	case FocusOut:
	    		prologue (&event, "FocusOut");
	    		break;
	  	case Expose:
	    		prologue (&event, "Expose");
	    		do_Expose (&event);
	    		break;
	  	case ConfigureNotify:
	    		prologue (&event, "ConfigureNotify");
	    		do_ConfigureNotify (&event);
	    		break;
	  	case MotionNotify:
	    		prologue (&event, "MotionNotify");
			do_MotionNotify(&event);
	    		break;
	  	case GravityNotify:
	  	case CirculateRequest:
	  	case PropertyNotify:
	  	case SelectionClear:
	  	case SelectionRequest:
	  	case SelectionNotify:
	  	case ColormapNotify:
	  	case ClientMessage:
	  	case MappingNotify:
	  	case CreateNotify:
	  	case DestroyNotify:
	  	case CirculateNotify:
	  	case VisibilityNotify:
	 	case KeyRelease:
	  	case KeymapNotify:
	  	case NoExpose:
	  	case GraphicsExpose:
	    		prologue (&event, "Unhandled");
	    		break;
		}
    	}
}


#ifdef EVENT_DEBUG

/* For debugging only: Print event message
 * ---------------------------------------
 */

#ifdef ANSI_C
static void prologue (XEvent *eventp, char *event_name)
#else
static void prologue (eventp, event_name)
XEvent *eventp;
char *event_name;
#endif
{
	XAnyEvent *e = (XAnyEvent *) eventp;

	PRINTF ("\n%s event, serial %ld, synthetic %s, window 0x%lx,\n",
	    event_name, e->serial, e->send_event ? "Yes" : "No", e->window);
}

#endif /* EVENT_DEBUG */



/* Keypress Events
 * ---------------
 */

#ifdef ANSI_C
static void do_KeyPress (XEvent *eventp)
#else
static void do_KeyPress (eventp)
XEvent *eventp;
#endif
{
    	XKeyEvent *e = (XKeyEvent *) eventp;
    	KeySym ks;
    	int nbytes, i;
    	char str[256+1];

    	nbytes = XLookupString (e, str, 256, &ks, NULL);
    	if (nbytes < 0) nbytes = 0;
    	if (nbytes > 256) nbytes = 256;
    	str[nbytes] = '\0';

	i = 0;
	if (nbytes==1) {
		switch (str[0]) {
		case '1': /* PBM */
			act_output_type = 1;
			break;
		case '2': /* PPM */
			act_output_type = 2;
			break;
		case '3': /* PostScript */
			act_output_type = 3;
			break;
		case 'F': /* full color */
		case 'f': /* full color */
			act_color_type = 1;
			break;
		case 'G': /* grey */
		case 'g': /* grey */
			act_color_type = 2;
			break;
		case 'B': /* b&w */
		case 'b': /* b&w */
			act_color_type = 3;
			break;
		case 'P': /* portrait */
		case 'p': /* portrait */
			act_ori_type = 1;
			break;
		case 'L': /* landscape */
		case 'l': /* landscape */
			act_ori_type = 2;
			break;
		case 'S': /* scaling: 1 */
		case 's': /* scaling: 1 */
			set_of_scaling(1.0);
			break;
		case 'M': /* maxspect */
		case 'm': /* maxspect */
			set_of_maxspect();
			break;
		case 'C': /* center */
		case 'c': /* center */
			set_of_centerx();
			set_of_centery();
			break;
		case '\r': /* Carriage Return */
		case '\n': /* Carriage Return */
			dialog_notready = 0;
			dialog_success  = 1;
			return;
		case 27: /* Cancel */
			dialog_notready = 0;
			dialog_success  = 0;
			return;
		case 'q': /* Quit */
		case 'Q': /* Quit */
			dialog_notready = 0;
			dialog_success  = 0;
			return;
		}
		draw_dialog_box();
	}
}




/* Button Press 
 * ------------
 */

static Window act_scroll_window = 0;
 
#ifdef ANSI_C
static void do_ButtonPress (XEvent *eventp)
#else
static void do_ButtonPress (eventp)
XEvent *eventp;
#endif
{
	XButtonEvent *e = (XButtonEvent *) eventp;
	Window w;
	int old_output_type, old_color_type, old_ori_type;
	int old_paper_type, old_paper_num;

	w = e->window;

	old_output_type = act_output_type;
	old_color_type  = act_color_type;
	old_ori_type    = act_ori_type;
	old_paper_type  = act_paper_type;
	old_paper_num   = act_paper_num;

	act_scroll_window = w;	
	if (act_scroll_window==xdpiscrollbar) {
		read_xdpiscrollbar(e->x);
		draw_sizes();
	}
	else if (act_scroll_window==ydpiscrollbar) {
		read_ydpiscrollbar(e->x);
		draw_sizes();
	}
	else if (act_scroll_window==scalescrollbar) {
		read_scalescrollbar(e->x);
		draw_sizes();
	}
	else if (act_scroll_window==widthscrollbar) {
		read_widthscrollbar(e->x);
		draw_sizes();
	}
	else if (act_scroll_window==heightscrollbar) {
		read_heightscrollbar(e->x);
		draw_sizes();
	}
	else if (act_scroll_window==margintmb) {
		read_marginpanner(e->x,e->y);
		draw_sizes();
	}
	else if (act_scroll_window==marginmiddle) {
		read_marginxpanner(e->x,e->y);
		draw_sizes();
	}

	if (w==pbm_point)  		act_output_type = 1;
	else if (w==ppm_point)		act_output_type = 2;
	else if (w==ps_point)		act_output_type = 3;
	else if (w==pn1_point)		act_paper_num  = 1;
	else if (w==pn2_point)		act_paper_num  = 2;
	else if (w==pn3_point)		act_paper_num  = 3;
	else if (w==pn4_point)		act_paper_num  = 4;
	else if (w==pn5_point)		act_paper_num  = 5;
	else if (w==color_point)	act_color_type = 1;
	else if (w==grey_point)		act_color_type = 2;
	else if (w==bw_point)		act_color_type = 3;
	else if (w==portr_point)	act_ori_type = 1;
	else if (w==landsc_point)	act_ori_type = 2;
	else if (w==pa4_point)		act_paper_type = 1;
	else if (w==pb5_point)		act_paper_type = 2;
	else if (w==pa5_point)		act_paper_type = 3;
	else if (w==p11x17_point)	act_paper_type = 4;
	else if (w==p8x11_point)	act_paper_type = 5;
	else if (w==p8x14_point)	act_paper_type = 6;
	else if (w==scale1_point) {
		set_of_scaling(1.0);
		draw_dialog_box();
	}
	else if (w==maxspect_point) {
		set_of_maxspect();
		draw_dialog_box();
	}
	else if (w==center_point) {
		set_of_centerx();
		set_of_centery();
		draw_dialog_box();
	}
	else if (w==centerx_point) {
		set_of_centerx();
		draw_dialog_box();
	}
	else if (w==centery_point) {
		set_of_centery();
		draw_dialog_box();
	}
	else if (w==dpi300_point) {
		set_xdpi(300);
		set_ydpi(300);
		draw_dialog_box();
	}
	else if (w==dpi400_point) {
		set_xdpi(400);
		set_ydpi(400);
		draw_dialog_box();
	}
	else if (w==dpi180_point) {
		set_xdpi(180);
		set_ydpi(180);
		draw_dialog_box();
	}
	else if (w==bbox_point) {
		act_bbox = 1-act_bbox;
		draw_dialog_box();
	}
	else if (w==okay_button) {
		dialog_notready = 0;
		dialog_success  = 1;
	}
	else if (w==cancel_button) {
		dialog_notready = 0;
		dialog_success  = 0;
	}

	if (old_output_type != act_output_type) {
		switch (act_output_type) {
		case 1: draw_dialog_point(pbm_point,1);
			draw_dialog_point(ppm_point,0);
			draw_dialog_point(ps_point, 0);
			set_xdpi(300);
			set_ydpi(300);
			act_paper_num = 1;
			calc_paper_size();
			act_left_margin =0.0;
			act_top_margin  =0.0;
			act_right_margin   = maxx - act_width -act_left_margin;
			act_bottom_margin  = maxy - act_height-act_top_margin;
			break;
		case 2: draw_dialog_point(pbm_point,0);
			draw_dialog_point(ppm_point,1);
			draw_dialog_point(ps_point, 0);
			set_xdpi(300);
			set_ydpi(300);
			act_paper_num = 1;
			calc_paper_size();
			act_left_margin =0.0;
			act_top_margin  =0.0;
			act_right_margin   = maxx - act_width -act_left_margin;
			act_bottom_margin  = maxy - act_height-act_top_margin;
			break;
		case 3: draw_dialog_point(pbm_point,0);
			draw_dialog_point(ppm_point,0);
			draw_dialog_point(ps_point, 1);
			set_xdpi(72);
			set_ydpi(72);
			break;
		}
	}
	if (old_paper_num != act_paper_num) {
		switch (act_paper_num) {
		case 1: draw_dialog_point(pn1_point, 1);
		        draw_dialog_point(pn2_point, 0);
		        draw_dialog_point(pn3_point, 0);
		        draw_dialog_point(pn4_point, 0);
		        draw_dialog_point(pn5_point, 0);
			break;
		case 2: draw_dialog_point(pn1_point, 0);
		        draw_dialog_point(pn2_point, 1);
		        draw_dialog_point(pn3_point, 0);
		        draw_dialog_point(pn4_point, 0);
		        draw_dialog_point(pn5_point, 0);
			break;
		case 3: draw_dialog_point(pn1_point, 0);
		        draw_dialog_point(pn2_point, 0);
		        draw_dialog_point(pn3_point, 1);
		        draw_dialog_point(pn4_point, 0);
		        draw_dialog_point(pn5_point, 0);
			break;
		case 4: draw_dialog_point(pn1_point, 0);
		        draw_dialog_point(pn2_point, 0);
		        draw_dialog_point(pn3_point, 0);
		        draw_dialog_point(pn4_point, 1);
		        draw_dialog_point(pn5_point, 0);
			break;
		case 5: draw_dialog_point(pn1_point, 0);
		        draw_dialog_point(pn2_point, 0);
		        draw_dialog_point(pn3_point, 0);
		        draw_dialog_point(pn4_point, 0);
		        draw_dialog_point(pn5_point, 1);
			break;
		}
	}
	if (old_color_type != act_color_type) {
		switch (act_color_type) {
		case 1: draw_dialog_point(color_point,1);
			draw_dialog_point(grey_point, 0);
			draw_dialog_point(bw_point,   0);
			break;
		case 2: draw_dialog_point(color_point,0);
			draw_dialog_point(grey_point, 1);
			draw_dialog_point(bw_point,   0);
			break;
		case 3: draw_dialog_point(color_point,0);
			draw_dialog_point(grey_point, 0);
			draw_dialog_point(bw_point,   1);
			break;
		}
	}
	if (old_ori_type != act_ori_type) {
		switch (act_ori_type) {
		case 1: draw_dialog_point(portr_point, 1);
			draw_dialog_point(landsc_point,0);
			break;
		case 2: draw_dialog_point(portr_point, 0);
			draw_dialog_point(landsc_point,1);
			break;
		}
	}
	if (old_paper_type != act_paper_type) {
		switch (act_paper_type) {
		case 1: draw_dialog_point(pa4_point,    1);
			draw_dialog_point(pb5_point,    0);
			draw_dialog_point(pa5_point,    0);
			draw_dialog_point(p11x17_point, 0);
			draw_dialog_point(p8x11_point,  0);
			draw_dialog_point(p8x14_point,  0);
			break;
		case 2: draw_dialog_point(pa4_point,    0);
			draw_dialog_point(pb5_point,    1);
			draw_dialog_point(pa5_point,    0);
			draw_dialog_point(p11x17_point, 0);
			draw_dialog_point(p8x11_point,  0);
			draw_dialog_point(p8x14_point,  0);
			break;
		case 3: draw_dialog_point(pa4_point,    0);
			draw_dialog_point(pb5_point,    0);
			draw_dialog_point(pa5_point,    1);
			draw_dialog_point(p11x17_point, 0);
			draw_dialog_point(p8x11_point,  0);
			draw_dialog_point(p8x14_point,  0);
			break;
		case 4: draw_dialog_point(pa4_point,    0);
			draw_dialog_point(pb5_point,    0);
			draw_dialog_point(pa5_point,    0);
			draw_dialog_point(p11x17_point, 1);
			draw_dialog_point(p8x11_point,  0);
			draw_dialog_point(p8x14_point,  0);
			break;
		case 5: draw_dialog_point(pa4_point,    0);
			draw_dialog_point(pb5_point,    0);
			draw_dialog_point(pa5_point,    0);
			draw_dialog_point(p11x17_point, 0);
			draw_dialog_point(p8x11_point,  1);
			draw_dialog_point(p8x14_point,  0);
			break;
		case 6: draw_dialog_point(pa4_point,    0);
			draw_dialog_point(pb5_point,    0);
			draw_dialog_point(pa5_point,    0);
			draw_dialog_point(p11x17_point, 0);
			draw_dialog_point(p8x11_point,  0);
			draw_dialog_point(p8x14_point,  1);
			break;
		}
	}
	if (  (old_output_type != act_output_type) 
	    ||(old_paper_type  != act_paper_type)
	    ||(old_paper_num   != act_paper_num)
	    ||(old_ori_type    != act_ori_type)) {
		draw_dialog_box();
	}
}



/* Button Release
 * --------------
 */

#ifdef ANSI_C
static void do_ButtonRelease (XEvent *eventp)
#else
static void do_ButtonRelease (eventp)
XEvent *eventp;
#endif
{
	XButtonEvent *e = (XButtonEvent *) eventp;

	if (act_scroll_window && (e->window!=act_scroll_window)) {
		set_xdpiscrollbar();
		set_ydpiscrollbar();
		set_scalescrollbar();
		set_widthscrollbar();
		set_heightscrollbar();
		set_marginpanner();
		draw_dialog_box();
		act_scroll_window = 0; 
		return;
	}
	if (act_scroll_window==xdpiscrollbar) 
		read_xdpiscrollbar(e->x);
	else if (act_scroll_window==ydpiscrollbar) 
		read_ydpiscrollbar(e->x);
	else if (act_scroll_window==scalescrollbar) 
		read_scalescrollbar(e->x);
	else if (act_scroll_window==widthscrollbar) 
		read_widthscrollbar(e->x);
	else if (act_scroll_window==heightscrollbar) 
		read_heightscrollbar(e->x);
	else if (act_scroll_window==margintmb) 
		read_marginpanner(e->x,e->y);
	else if (act_scroll_window==marginmiddle) 
		read_marginxpanner(e->x,e->y);
	else return;
	draw_dialog_box();
	act_scroll_window = 0; 
}



/* Mark a selection point as selectable
 * ------------------------------------
 */

#ifdef ANSI_C
static void do_EnterNotify (XEvent *eventp)
#else
static void do_EnterNotify (eventp)
XEvent *eventp;
#endif
{
    	XCrossingEvent *e = (XCrossingEvent *) eventp;
	Window w;
	XWindowAttributes retWinAttr;

	w = e->window;
	if (  (w==pbm_point)
	    ||(w==ppm_point)
	    ||(w==ps_point)
	    ||(w==pn1_point)
	    ||(w==pn2_point)
	    ||(w==pn3_point)
	    ||(w==pn4_point)
	    ||(w==pn5_point)
	    ||(w==color_point)
	    ||(w==grey_point)
	    ||(w==bw_point)
	    ||(w==pa4_point)
	    ||(w==pb5_point)
	    ||(w==pa5_point)
	    ||(w==p11x17_point)
	    ||(w==p8x11_point)
	    ||(w==p8x14_point)
	    ||(w==scale1_point)
	    ||(w==maxspect_point)
	    ||(w==center_point)
	    ||(w==centerx_point)
	    ||(w==centery_point)
	    ||(w==okay_button)
	    ||(w==cancel_button)
	    ||(w==dpi180_point)
	    ||(w==dpi300_point)
	    ||(w==dpi400_point)
	    ||(w==bbox_point)
	    ||(w==portr_point)
	    ||(w==landsc_point)) {
	        if (!XGetWindowAttributes(root_display,w,&retWinAttr)) {
               		FPRINTF(stderr,"Can't get window attributes.");
                	gs_exit(1);
        	}
		if (retWinAttr.border_width==1) {
			XMoveWindow(root_display,w,
				retWinAttr.x-2, retWinAttr.y-2);
		}
		XSetWindowBorderWidth(root_display, w, 3L);
	}
}


/* Unmark a selection point
 * ------------------------
 * The menupoint is not anymore selected.
 */ 

#ifdef ANSI_C
static void do_LeaveNotify (XEvent *eventp)
#else
static void do_LeaveNotify (eventp)
XEvent *eventp;
#endif
{
    	XCrossingEvent *e = (XCrossingEvent *) eventp;
	Window w;
	XWindowAttributes retWinAttr;

	w = e->window;
	if (  (w==pbm_point)
	    ||(w==ppm_point)
	    ||(w==ps_point)
	    ||(w==pn1_point)
	    ||(w==pn2_point)
	    ||(w==pn3_point)
	    ||(w==pn4_point)
	    ||(w==pn5_point)
	    ||(w==color_point)
	    ||(w==grey_point)
	    ||(w==bw_point)
	    ||(w==pa4_point)
	    ||(w==pb5_point)
	    ||(w==pa5_point)
	    ||(w==p11x17_point)
	    ||(w==p8x11_point)
	    ||(w==p8x14_point)
	    ||(w==scale1_point)
	    ||(w==maxspect_point)
	    ||(w==center_point)
	    ||(w==centerx_point)
	    ||(w==centery_point)
	    ||(w==okay_button)
	    ||(w==cancel_button)
	    ||(w==dpi180_point)
	    ||(w==dpi300_point)
	    ||(w==dpi400_point)
	    ||(w==bbox_point)
	    ||(w==portr_point)
	    ||(w==landsc_point)) {
	        if (!XGetWindowAttributes(root_display,w,&retWinAttr)) {
               		FPRINTF(stderr,"Can't get window attributes.");
                	gs_exit(1);
        	}
		if (retWinAttr.border_width==3) {
			XMoveWindow(root_display,w,
				retWinAttr.x+2, retWinAttr.y+2);
		}
		XSetWindowBorderWidth(root_display, w, 1L);
	}
}


/* Expose a window
 * ---------------
 */

#ifdef ANSI_C
static void do_Expose (XEvent *eventp)
#else
static void do_Expose (eventp)
XEvent *eventp;
#endif
{
	XExposeEvent *e = (XExposeEvent *) eventp;

	if (e->window==dialog_window) {
		if ((e->width>12)&&(e->height>12)&&(!box_exposed)) {
			draw_dialog_box(); 
			box_exposed = 1;
		}
	}
	else box_exposed = 0;
	do_gblExpose(eventp);
}


/* Resize or move a window
 * -----------------------
 */

#ifdef ANSI_C
static void do_ConfigureNotify (XEvent *eventp)
#else
static void do_ConfigureNotify (eventp)
XEvent *eventp;
#endif
{
	XConfigureEvent *e = (XConfigureEvent *) eventp;

	if (e->window==dialog_window) {
		XResizeWindow(root_display,dialog_window,DIAL_W,DIAL_H);
		draw_dialog_box(); 
	}
        else do_gblConfigureNotify(eventp);
}


/* Motion with pressed button 
 * --------------------------
 */

#ifdef ANSI_C
static void do_MotionNotify (XEvent *eventp)
#else
static void do_MotionNotify (eventp)
XEvent *eventp;
#endif
{
	XMotionEvent *e = (XMotionEvent *) eventp;

	if (e->window == margintmb) act_scroll_window = e->window;	

	if (act_scroll_window==xdpiscrollbar) 
		read_xdpiscrollbar(e->x);
	else if (act_scroll_window==ydpiscrollbar) 
		read_ydpiscrollbar(e->x);
	else if (act_scroll_window==scalescrollbar) 
		read_scalescrollbar(e->x);
	else if (act_scroll_window==widthscrollbar) 
		read_widthscrollbar(e->x);
	else if (act_scroll_window==heightscrollbar) 
		read_heightscrollbar(e->x);
	else if (act_scroll_window==margintmb) 
		read_marginpanner(e->x,e->y);
	else if (act_scroll_window==marginmiddle) 
		read_marginxpanner(e->x,e->y);
	else return;
	draw_sizes();
}


/*--------------------------------------------------------------------*/
/*  Scrollbar handling 						      */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
static void read_xdpiscrollbar(int val)
#else
static void read_xdpiscrollbar(val)
int val;
#endif
{
	int z;
	double factor;

	z = SCROLL_W/2;
	assert((z>0));
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= SCROLL_W) 
		val = SCROLL_W - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,xdpiscrolltmb,val,0,SCROLLBAR_LEN,6);
	factor = 300.0 * exp((double)(3*(val-z))/(double)z);
	set_xdpi(refocus_dpi(gstoint(factor)));
	if (act_output_type == 3) set_xdpiscrollbar();
	set_widthscrollbar();
}


#ifdef ANSI_C
static void set_xdpi(int val)
#else
static void set_xdpi(val)
int val;
#endif
{
	set_of_xdpi(val);
	act_width =(float)((rgx1>rgx2)?rgx1-rgx2:rgx2-rgx1)*act_scaling
			*2.54/(float)act_xdpi;
}


#ifdef ANSI_C
static void set_xdpiscrollbar(void)
#else
static void set_xdpiscrollbar()
#endif
{
	int z, val;

	z = SCROLL_W/2;
	assert((z>0));

	if (act_xdpi<=0) val = 0;
	else val = gstoint(log((double)act_xdpi/(double)300.0)*(double)z/3)+z;

	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= SCROLL_W) 
		val = SCROLL_W - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display, xdpiscrolltmb,val,0,SCROLLBAR_LEN,6);
}


#ifdef ANSI_C
static void read_ydpiscrollbar(int val)
#else
static void read_ydpiscrollbar(val)
int val;
#endif
{
	int z;
	double factor;

	z = SCROLL_W/2;
	assert((z>0));
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= SCROLL_W) 
		val = SCROLL_W - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,ydpiscrolltmb,val,0,SCROLLBAR_LEN,6);
	factor = 300.0 * exp((double)(3*(val-z))/(double)z);
	set_ydpi(refocus_dpi(gstoint(factor)));
	if (act_output_type == 3) set_ydpiscrollbar();
	set_heightscrollbar();
}

#ifdef ANSI_C
static void set_ydpi(int val)
#else
static void set_ydpi(val)
int val;
#endif
{
	set_of_ydpi(val);
	act_height=(float)((rgy1>rgy2)?rgy1-rgy2:rgy2-rgy1)*act_scaling
		*2.54/(float)act_ydpi;
}


#ifdef ANSI_C
static void set_ydpiscrollbar(void)
#else
static void set_ydpiscrollbar()
#endif
{
	int z, val;

	z = SCROLL_W/2;
	assert((z>0));

	if (act_ydpi<=0) val = 0;
	else val = gstoint(log((double)act_ydpi/(double)300.0)*(double)z/3)+z;

	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= SCROLL_W) 
		val = SCROLL_W - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display, ydpiscrolltmb,val,0,SCROLLBAR_LEN,6);
}


#ifdef ANSI_C
static void read_scalescrollbar(int val)
#else
static void read_scalescrollbar(val)
int val;
#endif
{
	int z;

	z = SCROLL_W/2;
	assert((z>0));
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= SCROLL_W) 
		val = SCROLL_W - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,scalescrolltmb,val,0,SCROLLBAR_LEN,6);
	set_of_scaling( exp((double)(3*(val-z))/(double)z));
	set_widthscrollbar();
	set_heightscrollbar();
}


#ifdef ANSI_C
static void set_scalescrollbar(void)
#else
static void set_scalescrollbar()
#endif
{
	int z, val;

	z = SCROLL_W/2;
	assert((z>0));

	if (act_scaling<=0) val = 0;
	else val = gstoint(log((double)act_scaling)*(double)z/3)+z;

	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= SCROLL_W) 
		val = SCROLL_W - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display, scalescrolltmb,val,0,SCROLLBAR_LEN,6);
}



#ifdef ANSI_C
static void read_widthscrollbar(int val)
#else
static void read_widthscrollbar(val)
int val;
#endif
{
	calc_paper_size();

	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= SCROLL_W) 
		val = SCROLL_W - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,widthscrolltmb,val,0,SCROLLBAR_LEN,6);
	set_of_width(maxx*val/(SCROLL_W-SCROLLBAR_LEN));

	set_scalescrollbar();
	set_heightscrollbar();
}



#ifdef ANSI_C
static void set_widthscrollbar(void)
#else
static void set_widthscrollbar()
#endif
{
	int val;

	calc_paper_size();

	if (act_width<=0) val = 0;
	else val = (int)(act_width*(SCROLL_W-SCROLLBAR_LEN)/maxx);

	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= SCROLL_W) 
		val = SCROLL_W - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display, widthscrolltmb,val,0,SCROLLBAR_LEN,6);
}


#ifdef ANSI_C
static void read_heightscrollbar(int val)
#else
static void read_heightscrollbar(val)
int val;
#endif
{
	calc_paper_size();

	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= SCROLL_W) 
		val = SCROLL_W - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,heightscrolltmb,val,0,SCROLLBAR_LEN,6);
	set_of_height(maxy*val/(SCROLL_W-SCROLLBAR_LEN));

	set_scalescrollbar();
	set_widthscrollbar();
}


#ifdef ANSI_C
static void set_heightscrollbar(void)
#else
static void set_heightscrollbar()
#endif
{
	int val;

	calc_paper_size();

	if (act_height<=0) val = 0;
	else val = (int)(act_height*(SCROLL_W-SCROLLBAR_LEN)/maxy);

	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= SCROLL_W) 
		val = SCROLL_W - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display, heightscrolltmb,val,0,SCROLLBAR_LEN,6);
}


#ifdef ANSI_C
static void read_marginpanner(int x,int y)
#else
static void read_marginpanner(x, y)
int x;
int y;
#endif
{
	float fac;
	int nx, ny;
	int aw, ah;

	calc_paper_size();

	fac = maxx/(PANNER_W-1);
	if (maxy/(PANNER_H-1) > fac) fac = maxy/(PANNER_H-1);
	aw = gstoint(act_width/fac);
	ah = gstoint(act_height/fac);
	if (aw<5) aw = 5;
	if (ah<5) ah = 5;

	nx = gstoint(act_left_margin/fac) + (x - aw/2);
	ny = gstoint(act_top_margin/fac) +  (y - ah/2);

	if (nx+aw/2 < 0) nx = 0;
	if (nx+aw/2 > gstoint(maxx/fac)) nx = gstoint(maxx/fac)-aw/2;
	if (ny+ah/2 < 0) ny = 0;
	if (ny+ah/2 > gstoint(maxy/fac)) ny = gstoint(maxy/fac)-ah/2;

	act_left_margin =fac*nx;
	act_top_margin  =fac*ny;
	act_right_margin  = maxx - act_width -act_left_margin;
	act_bottom_margin = maxy - act_height-act_top_margin;
	if (act_paper_num>1) {
		act_left_margin    =1.0;
		act_bottom_margin  =1.0;
		act_right_margin   = maxx - act_width -act_left_margin;
		act_top_margin     = maxy - act_height-act_bottom_margin;
		nx = (int)(act_left_margin/fac);
		ny = (int)(act_top_margin/fac);
	}
	draw_sizes();
	
	XMoveResizeWindow(root_display,margintmb,
		nx,ny, aw, ah);
	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XBlackPixel(root_display, root_screen));
	XDrawLine(root_display,(Drawable)margintmb,
		XDefaultGC(root_display, root_screen),
		0,0,aw,ah);
	XDrawLine(root_display,(Drawable)margintmb,
		XDefaultGC(root_display, root_screen),
		0,ah,aw,0);
	/* XSync(root_display, 0); */
}


#ifdef ANSI_C
static void read_marginxpanner(int x,int y)
#else
static void read_marginxpanner(x, y)
int x;
int y;
#endif
{
	float fac;
	int nx, ny;
	int aw, ah;

	calc_paper_size();

	fac = maxx/(PANNER_W-1);
	if (maxy/(PANNER_H-1) > fac) fac = maxy/(PANNER_H-1);
	aw = gstoint(act_width/fac);
	ah = gstoint(act_height/fac);
	if (aw<5) aw = 5;
	if (ah<5) ah = 5;

	nx = (x - aw/2);
	ny = (y - ah/2);

	if (nx+aw/2 < 0) nx = 0;
	if (nx+aw/2 > gstoint(maxx/fac)) nx = gstoint(maxx/fac)-aw/2;
	if (ny+ah/2 < 0) ny = 0;
	if (ny+ah/2 > gstoint(maxy/fac)) ny = gstoint(maxy/fac)-ah/2;
	act_left_margin =fac*nx;
	act_top_margin  =fac*ny;
	act_right_margin  = maxx - act_width -act_left_margin;
	act_bottom_margin = maxy - act_height-act_top_margin;
	if (act_paper_num>1) {
		act_left_margin    =1.0;
		act_bottom_margin  =1.0;
		act_right_margin   = maxx - act_width -act_left_margin;
		act_top_margin     = maxy - act_height-act_bottom_margin;
		nx = (int)(act_left_margin/fac);
		ny = (int)(act_top_margin/fac);
	}
	draw_sizes();
	
	XMoveResizeWindow(root_display,margintmb,
		nx,ny, aw, ah);
	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XBlackPixel(root_display, root_screen));
	XDrawLine(root_display,(Drawable)margintmb,
		XDefaultGC(root_display, root_screen),
		0,0,aw,ah);
	XDrawLine(root_display,(Drawable)margintmb,
		XDefaultGC(root_display, root_screen),
		0,ah,aw,0);
	/* XSync(root_display, 0); */
}


#ifdef ANSI_C
static void set_marginpanner(void)
#else
static void set_marginpanner()
#endif
{
	float fac;
	int aw, ah;

	calc_paper_size();

	fac = maxx/(PANNER_W-1);
	if (maxy/(PANNER_H-1) > fac) fac = maxy/(PANNER_H-1);
	aw = gstoint(act_width/fac);
	ah = gstoint(act_height/fac);
	if (aw<5) aw = 5;
	if (ah<5) ah = 5;
	
	XMoveResizeWindow(root_display,marginmiddle,
		(PANNER_W-1-gstoint(maxx/fac))/2,
		(PANNER_H-1-gstoint(maxy/fac))/2,
		gstoint(maxx/fac)+1, gstoint(maxy/fac)+1);

	XMoveResizeWindow(root_display,margintmb,
		gstoint(act_left_margin/fac),
		gstoint(act_top_margin/fac),
		aw, ah);
	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XBlackPixel(root_display, root_screen));
	XDrawLine(root_display,(Drawable)margintmb,
		XDefaultGC(root_display, root_screen),
		0,0,gstoint(act_width/fac), gstoint(act_height/fac));
	XDrawLine(root_display,(Drawable)margintmb,
		XDefaultGC(root_display, root_screen),
		0,gstoint(act_height/fac),gstoint(act_width/fac),0);
	/* XSync(root_display, 0); */
}


#endif /* X11 */


/*--------------------------------------------------------------------*/

/*  Global Interface Functions to set the form of output
 *  ====================================================
 *  These Interface Functions are independend of X11.
 */



/*  Set the region coordinates 
 *  --------------------------
 */

#ifdef ANSI_C
void set_of_region(int rminx,int rminy,int rmaxx,int rmaxy)
#else
void set_of_region(rminx, rminy, rmaxx, rmaxy)
int rminx; 
int rminy; 
int rmaxx;
int rmaxy;
#endif
{
	rgx1 = rminx;
	rgy1 = rminy;
	rgx2 = rmaxx;
	rgy2 = rmaxy;
}


/*  Set the xdpi Value
 *  ------------------
 */

#ifdef ANSI_C
void set_of_xdpi(int val)
#else
void set_of_xdpi(val)
int val;
#endif
{
        act_xdpi = val;
        if (act_output_type == 3) act_xdpi = 72;
}


/*  Set the ydpi Value
 *  ------------------
 */

#ifdef ANSI_C
void set_of_ydpi(int val)
#else
void set_of_ydpi(val)
int val;
#endif
{
        act_ydpi = val;
        if (act_output_type == 3) act_ydpi = 72;
}


/*  Set the scaling value and calculate width and height from it
 *  ------------------------------------------------------------
 */

#ifdef ANSI_C
void set_of_scaling(float val)
#else
void set_of_scaling(val)
float val;
#endif
{
	act_scaling = refocus_scale(val);
	act_width =((rgx1>rgx2)?rgx1-rgx2:rgx2-rgx1)*act_scaling*2.54/act_xdpi;
	act_height=((rgy1>rgy2)?rgy1-rgy2:rgy2-rgy1)*act_scaling*2.54/act_ydpi;
}



/*  Set the width and calculate scaling and height from it
 *  ------------------------------------------------------
 */

#ifdef ANSI_C
void set_of_width(float val)
#else
void set_of_width(val)
float val;
#endif
{
	act_width = val;
        act_scaling = act_width*act_xdpi/2.54/((rgx1>rgx2)?rgx1-rgx2:rgx2-rgx1);
        act_height=((rgy1>rgy2)?rgy1-rgy2:rgy2-rgy1)*act_scaling*2.54/act_ydpi;
}


/*  Set the height and calculate scaling and width from it
 *  ------------------------------------------------------
 */

#ifdef ANSI_C
void set_of_height(float val)
#else
void set_of_height(val)
float val;
#endif
{
        act_height=val;
        act_scaling = act_height*act_ydpi/2.54/((rgy1>rgy2)?rgy1-rgy2:rgy2-rgy1);
        act_width=((rgx1>rgx2)?rgx1-rgx2:rgx2-rgx1)*act_scaling*2.54/act_xdpi;
}


/*  Fit into height/width box and calculate scaling 
 *  -----------------------------------------------
 */

#ifdef ANSI_C
void fit_of_heightwidth(float h, float w)
#else
void fit_of_heightwidth(h, w)
float h;
float w;
#endif
{
	float scale1, scale2;

        scale1 = w*act_xdpi/2.54/((rgx1>rgx2)?rgx1-rgx2:rgx2-rgx1);
        scale2 = h*act_ydpi/2.54/((rgy1>rgy2)?rgy1-rgy2:rgy2-rgy1);
	if (scale1<scale2) 	set_of_width(w);
	else 			set_of_height(h);
}


/*  Fit into paper at maximal aspect ratio
 *  --------------------------------------
 */
 
#ifdef ANSI_C
void set_of_maxspect(void)
#else
void set_of_maxspect()
#endif
{
	float fac1,fac2;

	calc_paper_size();
	fac1 = (maxx - 1.0)*(float)act_xdpi/2.54
			/((rgx1>rgx2)?rgx1-rgx2:rgx2-rgx1);	
	fac2 = (maxy - 1.0)*(float)act_ydpi/2.54
			/((rgy1>rgy2)?rgy1-rgy2:rgy2-rgy1);	
	if (fac1<fac2) set_of_scaling(fac1);
	else	       set_of_scaling(fac2);

	set_of_centerx();
	set_of_centery();
}


/*  Center paper in x orientation
 *  -----------------------------
 */

#ifdef ANSI_C
void set_of_centerx(void)
#else
void set_of_centerx()
#endif
{
	calc_paper_size();
	act_left_margin = (maxx-act_width)/2;
	act_right_margin  = maxx - act_width - act_left_margin;
	if (act_paper_num>1) {
                act_left_margin    =1.0;
                act_bottom_margin  =1.0;
                act_right_margin   = maxx - act_width -act_left_margin;
                act_top_margin     = maxy - act_height-act_bottom_margin;
        }
}


/*  Center paper in y orientation
 *  -----------------------------
 */

#ifdef ANSI_C
void set_of_centery(void)
#else
void set_of_centery()
#endif
{
	calc_paper_size();
	act_top_margin  = (maxy-act_height)/2;
	act_bottom_margin = maxy - act_height - act_top_margin;
	if (act_paper_num>1) {
                act_left_margin    =1.0;
                act_bottom_margin  =1.0;
                act_right_margin   = maxx - act_width -act_left_margin;
                act_top_margin     = maxy - act_height-act_bottom_margin;
        }
}


/*  Set left margin of the paper
 *  ----------------------------
 */

#ifdef ANSI_C
void set_of_leftmargin(float val)
#else
void set_of_leftmargin(val)
float val;
#endif
{
	calc_paper_size();
	act_left_margin = val;
	act_right_margin  = maxx - act_width - act_left_margin;
	if (act_paper_num>1) {
                act_left_margin    =1.0;
                act_bottom_margin  =1.0;
                act_right_margin   = maxx - act_width -act_left_margin;
                act_top_margin     = maxy - act_height-act_bottom_margin;
        }
}


/*  Set right margin of the paper
 *  -----------------------------
 */

#ifdef ANSI_C
void set_of_rightmargin(float val)
#else
void set_of_rightmargin(val)
float val;
#endif
{
	calc_paper_size();
	act_right_margin = val;
	act_left_margin  = maxx - act_width - act_right_margin;
	if (act_paper_num>1) {
                act_left_margin    =1.0;
                act_bottom_margin  =1.0;
                act_right_margin   = maxx - act_width -act_left_margin;
                act_top_margin     = maxy - act_height-act_bottom_margin;
        }
}


/*  Set bottom margin of the paper
 *  ------------------------------
 */

#ifdef ANSI_C
void set_of_bottommargin(float val)
#else
void set_of_bottommargin(val)
float val;
#endif
{
	calc_paper_size();
	act_bottom_margin  = val;
	act_top_margin = maxy - act_height - act_bottom_margin;
	if (act_paper_num>1) {
                act_left_margin    =1.0;
                act_bottom_margin  =1.0;
                act_right_margin   = maxx - act_width -act_left_margin;
                act_top_margin     = maxy - act_height-act_bottom_margin;
        }
}


/*  Set top margin of the paper
 *  ---------------------------
 */

#ifdef ANSI_C
void set_of_topmargin(float val)
#else
void set_of_topmargin(val)
float val;
#endif
{
	calc_paper_size();
	act_top_margin  = val;
	act_bottom_margin = maxy - act_height - act_top_margin;
	if (act_paper_num>1) {
                act_left_margin    =1.0;
                act_bottom_margin  =1.0;
                act_right_margin   = maxx - act_width -act_left_margin;
                act_top_margin     = maxy - act_height-act_bottom_margin;
        }
}



/*--------------------------------------------------------------------*/

/*  Calc maximal paper sizes
 *  ------------------------
 *  and set the colbal variables maxx and maxy corresponmding.
 */

#ifdef ANSI_C
static void calc_paper_size(void)
#else
static void calc_paper_size()
#endif
{
	switch (act_paper_type) {
	case 1: 
		if (act_ori_type==1) 	{ maxx = 21.0; maxy = 30.0; }
		else 			{ maxx = 30.0; maxy = 21.0; }
		break;
	case 2: 
		if (act_ori_type==1) 	{ maxx = 18.5; maxy = 27.0; }
		else 			{ maxx = 27.0; maxy = 18.5; }
		break;
	case 3: 
		if (act_ori_type==1) 	{ maxx = 15.0; maxy = 21.0; }
		else 			{ maxx = 21.0; maxy = 15.0; }
		break;
	case 4: 
		if (act_ori_type==1) 	{ maxx = 27.94; maxy = 43.18; }
		else 			{ maxx = 43.18; maxy = 27.94; }
		break;
	case 5: 
		if (act_ori_type==1) 	{ maxx = 21.59; maxy = 27.94; }
		else 			{ maxx = 27.94; maxy = 21.59; }
		break;
	case 6: 
		if (act_ori_type==1) 	{ maxx = 21.59; maxy = 35.56; }
		else 			{ maxx = 35.56; maxy = 21.59; }
		break;
	}
	if (act_paper_num > 1) {
		/* 2 cm margin for multipage output */
		maxx = (maxx-3.0) * (float)act_paper_num;
		maxy = (maxy-3.0) * (float)act_paper_num;
	}
}

/*--------------------------------------------------------------------*/


/* Refocus dpi values
 * ------------------
 * Some dpi values are more often used than others. Thus we recalculate
 * the dpi values such that these values can be selected easyer.
 */

#define m_abs(x)  ((x>0)?(x):-(x))


#ifdef ANSI_C
static int refocus_dpi(int x)
#else
static int refocus_dpi(x)
int x;
#endif
{
	if (m_abs(x-2400)<95) return(2400);
	if (m_abs(x-1200)<65) return(1200);
	if (m_abs(x-720)<10) return(720);
	if (m_abs(x-700)<10) return(700);
	if (m_abs(x-600)<9) return(600);
	if (m_abs(x-500)<9) return(500);
	if (m_abs(x-400)<9) return(400);
	if (m_abs(x-360)<8) return(360);
	if (m_abs(x-300)<8) return(300);
	if (m_abs(x-288)<7) return(288);
	if (m_abs(x-240)<7) return(240);
	if (m_abs(x-200)<7) return(200);
	if (m_abs(x-100)<5) return(100);
	if (m_abs(x-180)<5) return(180);
	if (m_abs(x-144)<5) return(144);
	if (m_abs(x-120)<5) return(120);
	if (m_abs(x-100)<5) return(100);
	if (m_abs(x-90)<5)  return(90);
	if (m_abs(x-72)<5)  return(72);
	if (m_abs(x-50)<5)  return(50);
	return(x);
}


/*--------------------------------------------------------------------*/

/* Refocus scale values
 * --------------------
 * Some scale values are more often used than others. Thus we recalculate
 * the scale values such that these values can be selected easyer.
 */


#ifdef ANSI_C
static float refocus_scale(float x)
#else
static float refocus_scale(x)
float x;
#endif
{
	if (m_abs(x-12.0)<0.20)  return(12.0);
	if (m_abs(x-11.0)<0.09)  return(11.0);
	if (m_abs(x-10.0)<0.06)  return(10.0);
	if (m_abs(x-9.00)<0.06)  return(9.00);
	if (m_abs(x-8.00)<0.06)  return(8.00);
	if (m_abs(x-7.00)<0.06)  return(7.00);
	if (m_abs(x-6.00)<0.06)  return(6.00);
	if (m_abs(x-5.00)<0.06)  return(5.00);
	if (m_abs(x-4.00)<0.06)  return(4.00);
	if (m_abs(x-3.00)<0.02)  return(3.00);
	if (m_abs(x-2.00)<0.02)  return(2.00);
	if (m_abs(x-0.75)<0.01)  return(0.75);
	if (m_abs(x-0.50)<0.01)  return(0.50);
	if (m_abs(x-0.25)<0.01)  return(0.25);
	return(x);
}


/*--------------------------------------------------------------------*/

