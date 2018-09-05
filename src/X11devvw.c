/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */
/*		--------------------------------------		      */
/*								      */
/*   file:	   X11devvw.c					      */
/*   version:	   1.00.00					      */
/*   creation:	   12.1.95				      */
/*   author:	   I. Lemke  (...-Version 0.99.99)		      */
/*		   G. Sander (Version 1.00.00-...)		      */
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */
/*   description:  Device driver for X11, View Dialog Box	      */
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/

#ifndef lint
static char *id_string="$Id: X11devvw.c,v 1.2 1995/02/08 16:15:14 sander Exp $";
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
 * $Log: X11devvw.c,v $
 * Revision 1.2  1995/02/08  16:15:14  sander
 * Small bug with K&R C solved.
 *
 * Revision 1.1  1995/02/08  11:11:14  sander
 * Initial revision
 *
 */

/************************************************************************
 * Device driver for X11: View Dialog Box    
 * --------------------------------------
 *
 * This module contains the management of the dialog box that appears
 * if we want to change the view.
 * 
 * This file provides the following functions:
 * ------------------------------------------
 *
 *    x11_init_view_dialog(rd,rs)      initialize the dialogbox.
 *    x11_destroy_view_dialog(rd,rs)   destroys   the dialogbox.
 *
 *    x11_print_view_dialog()
 *
 *    This function opens the dialog box that allows to change the
 *    view parameters. On successful exit (Okay-button), the
 *    view parameters are updated, such that they become valid
 *    at the next draw_main.  On every exit, the dialog box is
 *    closed. The function returns 1, if the Okay-button was pressed.
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
#include "grammar.h"
#include "alloc.h"
#include "steps.h"
#include "fisheye.h"
#include "X11devvw.h"


/*--------------------------------------------------------------------*/

#undef EVENT_DEBUG


/* Types 
 * =====
 */

/*   Selection points: On/Off-Buttons, Radio/Buttons, Touch Buttons 
 *   Radio-Buttons are On-buttons, i.e. they don't go off, if we retouch
 *   them. Further, all radio buttons of one section have the same glob.
 */

typedef struct gs_selection_point {
	Window w;			/* Window of the point             */
	char   *t;			/* Text of the point               */
	int    x;			/* X-Position                      */
	int    y;			/* Y-Position                      */
	int    is;			/* actual value                    */
	int    sel;			/* value, if the point is selected */
	int    *glob;			/* corresponding global value      */
	char   key;			/* key action                      */
} GS_SEL_POINT;


/*  Horizontal integer scroll bars
 */


typedef struct gs_scroll_bar {
	Window ws;			/* Window of the bar itself        */
	Window wt;			/* Window of the scroll thumb      */
	Window wl;			/* Window of the left toucher      */
	Window wr;			/* Window of the left toucher      */
	char   *t;			/* Text of the scroll bar          */
	char   *f;			/* Format of the value             */
	int    xt;			/* X-Position of the text          */
	int    xv;			/* X-Position of the value         */
	int    xb;			/* X-Position of the bar           */
	int    y;			/* Y-Position                      */
	int    len;			/* Length of scrollbar             */
	long   is;			/* actual value                    */
	long   *glob;			/* corresponding global value      */
#ifdef ANSI_C
	void   (*rf)(int);		/* read function		   */
	void   (*sf)(void);		/* set function		   	   */
#else 
	void   (*rf)();
	void   (*sf)();
#endif
} GS_SCROLL_BAR;




/* Prototypes
 * ==========
 */

/* from X11dev.c */

void    gs_exit         _PP((int x));
void    do_gblExpose    _PP((XEvent *eventp));
void    do_gblConfigureNotify  _PP((XEvent *eventp));
void	m_validate_fe	_PP((void));

static void   allocateDialogBox         _PP((void));
static Window allocate_selection_point  _PP((int x,int y));
static Window allocate_button		_PP((int x,int y));
static Window allocate_general_button   _PP((int x,int y,int w,int h));
static Window allocate_scroll_bar	_PP((int x,int y,int len));

static void draw_dialog_box     _PP((void));
static void draw_text           _PP(( int x, int y, char *m));
static void draw_underl_text    _PP(( int x, int y, char *m));
static void draw_dialog_point   _PP((Window w, int color));
static void draw_sizes		_PP((void));
static void normalize_point     _PP((Window w));


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

static void 	do_apply		_PP((void));
static void 	read_fishdistscrollbar	_PP((int val));
static void 	set_fishdistscrollbar	_PP((void));


/* Positions and Sizes
 * ===================
 */

/* Size of the dialog box */

#define DIAL_W   580
#define DIAL_H   170

/* Size of a normal point */

#define POINT_W  10 

/* Size of a normal button */

#define BUTTON_W   116

/* Sizes of a scrollbar and its thumb */

#define SCROLL_W  200  
#define SCROLLBAR_LEN 15



/* Variables
 * =========
 */

/* View variable */

static int myview = 0;

/* If it is fisheye with fixed width */

static int fixed_width = 0;

/* Dialog handling: On success (i.e. Okay-Button), success becomes 1 */

static int dialog_notready = 1;
static int dialog_success  = 0;


/*  On-Off-points are buttons that switch their state if we select them */

#define MAX_ONOFF_POINTS 4
static GS_SEL_POINT on_off_point[MAX_ONOFF_POINTS] = {

/* window,  text       , xpos, ypos, isval, selval , globvar      , key */ 
{  0     ,  "edges",       5,  108,   0,      0 , &supress_edges   , 'e' },   
{  0     ,  "nodes",       5,  126,   0,      0 , &supress_nodes   , 'n' },   
{  0     ,  "splines"  ,   5,  144,   0,      1 , &G_spline        , 's' },   
{  0     ,  "fixed radius",200,108,   0,      1 , &fixed_width     , 'f' }
};

#define FIXED_WBUT 3


/*  Touch-points are buttons that don't their change state if we select them. 
 *  Instead, some other actions are performed. They don't correspond to 
 *  global variables.
 */

#define MAX_TOUCH_POINTS 0 
static GS_SEL_POINT touch_point[1]; 
#ifdef NEVERNEVERNEVER
static GS_SEL_POINT touch_point[MAX_TOUCH_POINTS] = {
/* window,  text       , xpos, ypos,     isval, selval, globvar , key */ 
};
#endif



/*  Radio buttons are partitioned into those that have the same global 
 *  variable. If a radio-button is selected, all other radio buttons 
 *  of the same partition became unselected. 
 */


#define MAX_RADIO_POINTS 3 
static GS_SEL_POINT radio_point[MAX_RADIO_POINTS] = {

/* window,  text               ,xpos,ypos,isval, selval     , globvar             , key */ 
{  0     ,  "normal view"      ,  5,   36,  0,   0        , &myview, 'v' },   
{  0     ,  "cartesian fisheye",  5,   54,  0,   CSCF_VIEW, &myview, 'c' },   
{  0     ,  "polar fisheye"    ,  5,   72,  0,   PSCF_VIEW, &myview, 'p' }

};

#define NORM_VW 0


/*  Horizontal long scrollbars are used to change a value by the read and 
 *  set functions. Here, these values must be long values.
 */


#define MAX_HSCROLLBARS 1 

#ifdef ANSI_C
static GS_SCROLL_BAR hscrollbar[MAX_HSCROLLBARS] = {

    {  0, 0, 0, 0, "Radius:" ,"%d%", 200, 270, 320, 126, SCROLL_W,
	0, &gfishdist  , &read_fishdistscrollbar, &set_fishdistscrollbar }
};

#else

static GS_SCROLL_BAR hscrollbar[MAX_HSCROLLBARS] = {

    {  0, 0, 0, 0, "Radius:" ,"%ld%", 200, 270, 320, 126, SCROLL_W,
	0, &gfishdist  , read_fishdistscrollbar, set_fishdistscrollbar }
};
#endif

#define GFISHDIST   0



/* Root displays */

static Display *root_display;	/* Root display          */
static int      root_screen;	/* and its screen number */


/* Windows */

static Window	dialog_window;

static Window   okay_button;
static Window   test_button;
static Window   cancel_button;



/* Cursors */

static Cursor standardCursor;      /* Remembered old cursor        */
static Cursor workingCursor;       /* If the tool is busy          */
static Cursor scrollCursor; 
static Cursor leftscrollCursor; 
static Cursor rightscrollCursor; 

/* Mouse Buttons */

#define G_MOUSE_LEFT  1
#define G_MOUSE_RIGHT 3


/* the panel font */

extern char Xfontname[512];
static  XFontStruct *dialog_font = NULL;

/* Flag whether the dialog_box is initialized */

static int dialog_box_there = 0;


/*--------------------------------------------------------------------*/
/*  Dialog box initialization and entry points                        */
/*--------------------------------------------------------------------*/

/*  Initialize the dialog box 
 *  -------------------------
 *  This is done once at the beginning.
 */

#ifdef ANSI_C
void 	x11_init_view_dialog(Display *rd, int rs)
#else
void 	x11_init_view_dialog(rd, rs)
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
void	x11_destroy_view_dialog(Display *rd, int rs)
#else
void	x11_destroy_view_dialog(rd, rs)
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
static Window last_left;
static Window last_right;
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
        strcat(x11_win_label, " View");

	XStoreName(root_display, dialog_window, x11_win_label);
	XSetNormalHints(root_display, dialog_window, &hints);

        standardCursor = XCreateFontCursor(root_display,XC_left_ptr);
        workingCursor  = XCreateFontCursor(root_display,XC_watch);
	scrollCursor   = XCreateFontCursor(root_display,XC_sb_h_double_arrow);
	leftscrollCursor  = XCreateFontCursor(root_display,XC_sb_left_arrow);
	rightscrollCursor = XCreateFontCursor(root_display,XC_sb_right_arrow);
	XDefineCursor(root_display,dialog_window, standardCursor);

	for (i=0; i<MAX_ONOFF_POINTS; i++)
		on_off_point[i].w = allocate_selection_point(
					on_off_point[i].x, 
					on_off_point[i].y-10);
	for (i=0; i<MAX_TOUCH_POINTS; i++)
		touch_point[i].w = allocate_selection_point(
					touch_point[i].x,
				    	touch_point[i].y-10);
	for (i=0; i<MAX_RADIO_POINTS; i++)
		radio_point[i].w = allocate_selection_point(
					radio_point[i].x,
					radio_point[i].y-10);

	for (i=0; i<MAX_HSCROLLBARS; i++) {
		hscrollbar[i].ws = allocate_scroll_bar(hscrollbar[i].xb,
						       hscrollbar[i].y-10, 
						       hscrollbar[i].len);
		hscrollbar[i].wt = last_tmb;
		hscrollbar[i].wl = last_left;
		hscrollbar[i].wr = last_right;
	}
	

	cancel_button = allocate_button(200,36);
	okay_button   = allocate_button(200+(BUTTON_W+10),36);
	test_button   = allocate_button(200+2*(BUTTON_W+10),36);
}



/*  Allocate a selection point (button or radio button)
 *  ---------------------------------------------------
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



/*  Allocate an normal button
 *  -------------------------
 */

#ifdef ANSI_C
static Window allocate_button(int x,int y)
#else
static Window allocate_button(x,y)
int x, y;
#endif
{
	return(allocate_general_button(x,y,BUTTON_W,25));
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
static Window allocate_scroll_bar(int x,int y,int len)
#else
static Window allocate_scroll_bar(x,y,len)
int x, y, len;
#endif
{
	Window w, wt, wl, wr;
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

        w = XCreateWindow (root_display, dialog_window, x+9,y,
                           len, 8,
                           1, (int)CopyFromParent,
                           InputOutput,
                           (Visual *)CopyFromParent,
                           mask, &attr);
        wt = XCreateSimpleWindow (root_display, w, 0,0,
                                    SCROLLBAR_LEN, 6,
                                    1,
                                    XWhitePixel(root_display,root_screen),
                                    XBlackPixel(root_display,root_screen));
        wl = XCreateWindow (root_display, dialog_window, x,y,
                           8, 8,
                           1, (int)CopyFromParent,
                           InputOutput,
                           (Visual *)CopyFromParent,
                           mask, &attr);
        wr = XCreateWindow (root_display, dialog_window, x+len+10,y,
                           8, 8,
                           1, (int)CopyFromParent,
                           InputOutput,
                           (Visual *)CopyFromParent,
                           mask, &attr);

	XDefineCursor(root_display,w,scrollCursor); 
	XDefineCursor(root_display,wl,leftscrollCursor); 
	XDefineCursor(root_display,wr,rightscrollCursor); 
	
	last_tmb   = wt;
	last_left  = wl;
	last_right = wr;
	return(w);
}


/*--------------------------------------------------------------------*/
/*   Entry point for the dialog                                       */
/*--------------------------------------------------------------------*/

static int box_exposed;
static int first_exposed = 1;

#ifdef ANSI_C
int x11_print_view_dialog(void)
#else
int x11_print_view_dialog()
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

        switch (fisheye_view) {
	case 0:		 myview = 0;         fixed_width = 0; break;
        case CSCF_VIEW:  myview = CSCF_VIEW; fixed_width = 0; break; 
        case FCSCF_VIEW: myview = CSCF_VIEW; fixed_width = 1; break; 
        case PSCF_VIEW:  myview = PSCF_VIEW; fixed_width = 0; break;
        case FPSCF_VIEW: myview = PSCF_VIEW; fixed_width = 1; break;
        }
  
	for (i=0; i<MAX_ONOFF_POINTS; i++)
		on_off_point[i].is = *(on_off_point[i].glob);

	for (i=0; i<MAX_RADIO_POINTS; i++)
		radio_point[i].is = *(radio_point[i].glob);

	for (i=0; i<MAX_HSCROLLBARS; i++) 
		hscrollbar[i].is = *(hscrollbar[i].glob);

        XMapRaised(root_display, dialog_window);

	for (i=0; i<MAX_ONOFF_POINTS; i++) {
		XMapRaised(root_display, on_off_point[i].w);
		normalize_point(on_off_point[i].w);
	}
	for (i=0; i<MAX_TOUCH_POINTS; i++) {
		XMapRaised(root_display, touch_point[i].w);
		normalize_point(touch_point[i].w);
	}
	for (i=0; i<MAX_RADIO_POINTS; i++) {
		XMapRaised(root_display, radio_point[i].w);
		normalize_point(radio_point[i].w);
	}
	for (i=0; i<MAX_HSCROLLBARS; i++) {
        	XMapRaised(root_display, hscrollbar[i].ws);
        	XMapRaised(root_display, hscrollbar[i].wt);
        	XMapRaised(root_display, hscrollbar[i].wl);
        	XMapRaised(root_display, hscrollbar[i].wr);
	}

        XMapRaised(root_display, test_button);
        XMapRaised(root_display, okay_button);
        XMapRaised(root_display, cancel_button);
	normalize_point(test_button);
	normalize_point(okay_button);
	normalize_point(cancel_button);

	for (i=0; i<MAX_HSCROLLBARS; i++) (*(hscrollbar[i].sf))();

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

	if (event.type == Expose) do_Expose(&event);

	dialog_main_loop();

        XUnmapWindow(root_display, dialog_window);

	if (dialog_success) {

		do_apply();
	}

	return(dialog_success);
}


/*--------------------------------------------------------------------*/
/*   Constraint routine                                               */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
static void special_constraints(int redraw, int sel)
#else
static void special_constraints(redraw, sel)
int redraw;
int sel;
#endif
{
	/* Normal View => no Fixed Width */

	if (radio_point[NORM_VW].is == radio_point[NORM_VW].sel) {
		on_off_point[FIXED_WBUT].is = on_off_point[FIXED_WBUT].sel-1;
		if (redraw) draw_dialog_point(on_off_point[FIXED_WBUT].w,0);
	}
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
	int i;

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

	i = XTextWidth(dialog_font,"Cancel (Esc)",strlen("Cancel (Esc)"));
	i = (BUTTON_W-i)/2;
	XDrawString(root_display,
		(Drawable)cancel_button,
		XDefaultGC(root_display, root_screen),
		i,18,"Cancel (Esc)",strlen("Cancel (Esc)"));

	i = XTextWidth(dialog_font,"Okay",strlen("Okay"));
	i = (BUTTON_W-i)/2;
	XDrawString(root_display,
		(Drawable)okay_button,
		XDefaultGC(root_display, root_screen),
		i,18,"Okay",strlen("Okay"));

	i = XTextWidth(dialog_font,"Apply",strlen("Apply"));
	i = (BUTTON_W-i)/2;
	XDrawString(root_display,
		(Drawable)test_button,
		XDefaultGC(root_display, root_screen),
		i,18,"Apply",strlen("Apply"));

	draw_underl_text(5,18,  "General View");
	draw_underl_text(5,90,  "General Parameter");
	draw_underl_text(200,90,"Fisheye Parameter");

	special_constraints(0, -1);

	for (i=0; i<MAX_ONOFF_POINTS; i++)
		draw_text(on_off_point[i].x+20,on_off_point[i].y,
			  on_off_point[i].t);

	for (i=0; i<MAX_TOUCH_POINTS; i++)
		draw_text(touch_point[i].x+20,touch_point[i].y,
			  touch_point[i].t);

	for (i=0; i<MAX_RADIO_POINTS; i++)
		draw_text(radio_point[i].x+20,radio_point[i].y,
			  radio_point[i].t);

	for (i=0; i<MAX_HSCROLLBARS; i++) 
		draw_text(hscrollbar[i].xt, hscrollbar[i].y, hscrollbar[i].t);

	for (i=0; i<MAX_ONOFF_POINTS; i++)
		if (on_off_point[i].is == on_off_point[i].sel)
			draw_dialog_point(on_off_point[i].w,1);
		else    draw_dialog_point(on_off_point[i].w,0);

	for (i=0; i<MAX_TOUCH_POINTS; i++)
		draw_dialog_point(touch_point[i].w,0);

	for (i=0; i<MAX_RADIO_POINTS; i++)
		if (radio_point[i].is == radio_point[i].sel)
			draw_dialog_point(radio_point[i].w,1);
		else    draw_dialog_point(radio_point[i].w,0);

	draw_sizes();

	for (i=0; i<MAX_HSCROLLBARS; i++) (*(hscrollbar[i].sf))();

	XSync(root_display, 0);
}



#ifdef ANSI_C
static void draw_sizes(void)
#else
static void draw_sizes()
#endif
{
	int i;

	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XWhitePixel(root_display, root_screen));
	XFillRectangle(root_display, 
		(Drawable)dialog_window,
		XDefaultGC(root_display, root_screen),
		270,108,100,1*18);

	special_constraints(0, -1);

	for (i=0; i<MAX_HSCROLLBARS; i++) {
		if (hscrollbar[i].is == MAXLONG) SPRINTF(mxbuffer, "inf."); 
		else SPRINTF(mxbuffer, hscrollbar[i].f, hscrollbar[i].is);
		draw_text(hscrollbar[i].xv,hscrollbar[i].y,mxbuffer);
	}

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


/*  Draw underlined text m into the dialog box at position x, y
 *  -----------------------------------------------------------
 */

#ifdef ANSI_C
static void draw_underl_text(int x,int y,char *m)
#else
static void draw_underl_text(x,y, m)
int x, y;
char *m;
#endif
{
	int len;

	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XBlackPixel(root_display, root_screen));
	XDrawString(root_display,
		(Drawable)dialog_window,
		XDefaultGC(root_display, root_screen),
		x,y,m,strlen(m));
	len = XTextWidth(dialog_font,m,strlen(m));
	XDrawLine(root_display,(Drawable)dialog_window,
                XDefaultGC(root_display, root_screen),
                x,y+2,x+len,y+2);
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


/* Normalize a button or point
 * ---------------------------
 */

#ifdef ANSI_C
static void normalize_point(Window w)
#else
static void normalize_point(w)
Window w;
#endif
{
        XWindowAttributes retWinAttr;

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
    	int nbytes, i,j;
    	char str[256+1];
	char lk, uk; 

    	nbytes = XLookupString (e, str, 256, &ks, NULL);
    	if (nbytes < 0) nbytes = 0;
    	if (nbytes > 256) nbytes = 256;
    	str[nbytes] = '\0';

	if (nbytes==1) {
		/* No operation on ' ' */
		if (str[0]==' ') return;

		for (i=0; i<MAX_ONOFF_POINTS; i++) {
			lk = uk = on_off_point[i].key;
			lk = tolower(lk);
			uk = toupper(uk);
			if ((lk==str[0])||(uk==str[0])) {
				if (on_off_point[i].is == on_off_point[i].sel) 
					on_off_point[i].is = on_off_point[i].sel-1;
				else    on_off_point[i].is = on_off_point[i].sel;
				break;
			}
		}
	
		special_constraints(0, i);

		for (i=0; i<MAX_TOUCH_POINTS; i++) {
			lk = uk = touch_point[i].key;
			lk = tolower(lk);
			uk = toupper(uk);
			if ((lk==str[0])||(uk==str[0])) break;
		}

		for (i=0; i<MAX_RADIO_POINTS; i++) {
			lk = uk = radio_point[i].key;
			lk = tolower(lk);
			uk = toupper(uk);
			if ((lk==str[0])||(uk==str[0])) {
				radio_point[i].is = radio_point[i].sel;
				break;
			}
		}

		if (i<MAX_RADIO_POINTS) {
			for (j=0; j<MAX_RADIO_POINTS; j++) {
				if ((i!=j) && (radio_point[i].glob==radio_point[j].glob)) 
					radio_point[j].is = radio_point[j].sel-1;
			}
		}

		special_constraints(0, -1);

		switch (str[0]) {
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
		case 'a': /* Apply */
		case 'A': /* Apply */
			do_apply();
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
	int i,j;

	w = e->window;

	act_scroll_window = w;	

	for (i=0; i<MAX_ONOFF_POINTS; i++) {
		if (w == on_off_point[i].w) {
			if (on_off_point[i].is == on_off_point[i].sel) {
				on_off_point[i].is = on_off_point[i].sel-1;
				draw_dialog_point(on_off_point[i].w,0);
			}
			else {  
				on_off_point[i].is = on_off_point[i].sel;
				draw_dialog_point(on_off_point[i].w,1);
			}
			break;
		}
	}

	special_constraints(1, i);


	for (i=0; i<MAX_TOUCH_POINTS; i++) {
		if (w == touch_point[i].w) break;
	}


	for (i=0; i<MAX_RADIO_POINTS; i++) {
		if (w == radio_point[i].w) {
			radio_point[i].is = radio_point[i].sel;
			break;
		}
	}

	if (i<MAX_RADIO_POINTS) {
		for (j=0; j<MAX_RADIO_POINTS; j++) {
			if ((i!=j) && (radio_point[i].glob==radio_point[j].glob)) 
				radio_point[j].is = radio_point[j].sel-1;
		}
	}

	special_constraints(1, -1);

	for (i=0; i<MAX_RADIO_POINTS; i++)
		if (radio_point[i].is == radio_point[i].sel)
			draw_dialog_point(radio_point[i].w,1);
		else    draw_dialog_point(radio_point[i].w,0);


	for (i=0; i<MAX_HSCROLLBARS; i++) {
		if (act_scroll_window==hscrollbar[i].ws) {
		 	(*(hscrollbar[i].rf))(e->x);
			draw_sizes();
		}
	}

	for (i=0; i<MAX_HSCROLLBARS; i++) {
		if (act_scroll_window==hscrollbar[i].wl) {
			if (e->button==G_MOUSE_LEFT)
		 		hscrollbar[i].is -= 200;
		  	else	hscrollbar[i].is -= 10;
		 	(*(hscrollbar[i].sf))();
			draw_sizes();
		}
		if (act_scroll_window==hscrollbar[i].wr) {
		 	if (hscrollbar[i].is < MAXLONG-200) {
				if (e->button==G_MOUSE_LEFT)
		 			hscrollbar[i].is += 200;
		  		else	hscrollbar[i].is += 10;
			}
		 	(*(hscrollbar[i].sf))();
			draw_sizes();
		}
	}

	if (w==okay_button) {
		dialog_notready = 0;
		dialog_success  = 1;
	}
	else if (w==cancel_button) {
		dialog_notready = 0;
		dialog_success  = 0;
	}
	else if (w==test_button) {
		do_apply();
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
	int i;

	if (act_scroll_window && (e->window!=act_scroll_window)) {
		for (i=0; i<MAX_HSCROLLBARS; i++) (*(hscrollbar[i].sf))();
		draw_dialog_box();
		act_scroll_window = 0; 
		return;
	}

	for (i=0; i<MAX_HSCROLLBARS; i++) {
		if (act_scroll_window==hscrollbar[i].ws) {
		 	(*(hscrollbar[i].rf))(e->x);
			break;
		}
	}
	if (i<MAX_HSCROLLBARS) draw_dialog_box();
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
	int i, is_point;

	is_point = 0;
	w = e->window;

	for (i=0; i<MAX_ONOFF_POINTS; i++)
		if (w==on_off_point[i].w) is_point = 1;
	for (i=0; i<MAX_TOUCH_POINTS; i++)
		if (w==touch_point[i].w) is_point = 1;
	for (i=0; i<MAX_RADIO_POINTS; i++)
		if (w==radio_point[i].w) is_point = 1;

	if ((w==okay_button)||(w==cancel_button)||(w==test_button))
		is_point = 1;

	if (is_point) {
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
	int i, is_point;

	is_point = 0;
	w = e->window;

	for (i=0; i<MAX_ONOFF_POINTS; i++)
		if (w==on_off_point[i].w) is_point = 1;
	for (i=0; i<MAX_TOUCH_POINTS; i++)
		if (w==touch_point[i].w) is_point = 1;
	for (i=0; i<MAX_RADIO_POINTS; i++)
		if (w==radio_point[i].w) is_point = 1;

	if ((w==okay_button)||(w==cancel_button)||(w==test_button))
		is_point = 1;

	if (is_point) normalize_point(w);
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
	int i;

	XMotionEvent *e = (XMotionEvent *) eventp;

	for (i=0; i<MAX_HSCROLLBARS; i++) { 
		if (act_scroll_window==hscrollbar[i].ws) {
		 	(*(hscrollbar[i].rf))(e->x);
			break;
		}
	}
	if (i<MAX_HSCROLLBARS) draw_sizes();
}


/*--------------------------------------------------------------------*/
/*  Apply handling     						      */
/*--------------------------------------------------------------------*/

/*  This is done if we want to validate the current selection
 *  ---------------------------------------------------------
 */

#ifdef ANSI
static void do_apply(void)
#else
static void do_apply()
#endif
{
	int i;

	XDefineCursor(root_display,dialog_window, workingCursor);
	for (i=0; i<MAX_ONOFF_POINTS; i++)
		*(on_off_point[i].glob) = on_off_point[i].is;

	for (i=0; i<MAX_RADIO_POINTS; i++) 
		if (radio_point[i].is == radio_point[i].sel) 
			*(radio_point[i].glob) = radio_point[i].is;

	for (i=0; i<MAX_HSCROLLBARS; i++) 
		*(hscrollbar[i].glob) = hscrollbar[i].is;

	exit_fe();
	if (fixed_width) {
       		switch (myview) {
		case 0:		 fisheye_view = 0;          break;
       		case CSCF_VIEW:  fisheye_view = FCSCF_VIEW; break; 
       		case FCSCF_VIEW: fisheye_view = FCSCF_VIEW; break; 
       		case PSCF_VIEW:  fisheye_view = FPSCF_VIEW; break;
       		case FPSCF_VIEW: fisheye_view = FPSCF_VIEW; break;
       		}
	}
	else {
       		switch (myview) {
		case 0:		 fisheye_view = 0;         break;
       		case CSCF_VIEW:  fisheye_view = CSCF_VIEW; break; 
       		case FCSCF_VIEW: fisheye_view = CSCF_VIEW; break; 
       		case PSCF_VIEW:  fisheye_view = PSCF_VIEW; break;
       		case FPSCF_VIEW: fisheye_view = PSCF_VIEW; break;
       		}
	}
	m_validate_fe();
	XDefineCursor(root_display,dialog_window, standardCursor);
}


/*--------------------------------------------------------------------*/
/*  Scrollbar handling 						      */
/*--------------------------------------------------------------------*/


/*  General scrollbar actions with scaling 30 
 *  -----------------------------------------
 *  The general scrollbar actions for bars that have a scaling of 1, i.e.
 *  produce values 30, 80, 130 ..., 
 */


#ifdef ANSI_C
static void read_fishdistscrollbar(int val)
#else
static void read_fishdistscrollbar(val)
int val;
#endif
{
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= hscrollbar[GFISHDIST].len) 
		val = hscrollbar[GFISHDIST].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,hscrollbar[GFISHDIST].wt,
			val,0,SCROLLBAR_LEN,6);
	hscrollbar[GFISHDIST].is = 30L + 50L*(long)val;
}


#ifdef ANSI_C
static void set_fishdistscrollbar(void)
#else
static void set_fishdistscrollbar()
#endif
{
	int val;

	if (hscrollbar[GFISHDIST].is<30L)  hscrollbar[GFISHDIST].is = 30L;
	val = (int)((hscrollbar[GFISHDIST].is - 30L) / 50L);
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= hscrollbar[GFISHDIST].len) 
		val = hscrollbar[GFISHDIST].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display, hscrollbar[GFISHDIST].wt,
			val,0,SCROLLBAR_LEN,6);
}


/*--------------------------------------------------------------------*/

#endif /* X11 */

