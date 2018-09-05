/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */
/*		--------------------------------------		      */
/*								      */
/*   file:	   X11devcl.c					      */
/*   version:	   1.00.00					      */
/*   creation:	   9.4.93					      */
/*   author:	   I. Lemke  (...-Version 0.99.99)		      */
/*		   G. Sander (Version 1.00.00-...)		      */
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */
/*   description:  Device driver for X11, Hide Class Dialog Box       */
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/

#ifndef lint
static char *id_string="$Id: X11devcl.c,v 1.9 1995/02/08 11:11:14 sander Exp $";
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
 * $Log: X11devcl.c,v $
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
 * Revision 1.7  1994/11/23  14:50:47  sander
 * Drawing speed improved by removing some superfluous XSyncs.
 *
 * Revision 1.6  1994/08/09  14:00:40  sander
 * XLoadQuery-Font-Debugging removed again.
 *
 * Revision 1.5  1994/08/03  13:58:44  sander
 * Horizontal order mechanism changed.
 * Attribute horizontal_order for edges added.
 *
 * Revision 1.4  1994/08/02  15:36:12  sander
 * Minor change. Some debugmessages added.
 *
 * Revision 1.3  1994/06/07  14:09:59  sander
 * Splines implemented.
 * HP-UX, Linux, AIX, Sun-Os, IRIX compatibility tested.
 * The tool is now ready to be distributed.
 *
 * Revision 1.2  1994/05/16  08:56:03  sander
 * shape attribute (boxes, rhombs, ellipses, triangles) added.
 *
 * Revision 1.1  1994/05/05  08:20:30  sander
 * Initial revision
 *
 */

/************************************************************************
 * Device driver for X11: Hide Classes Dialog Box    
 * ----------------------------------------------
 *
 * This module contains the management of the dialog box that appears
 * if we want to hide or expose edge classes.
 * 
 * This file provides the following functions:
 * ------------------------------------------
 *
 *    x11_init_classes_dialog(rd,rs)      initialize the dialogbox.
 *    x11_destroy_classes_dialog(rd,rs)   destroys   the dialogbox.
 *
 *    x11_print_classes_dialog()
 *
 *    This function opens the dialog box that allows to hide or expose
 *    edge classes. On successful exit (Okay-button), the classes are 
 *    updated, such that they become valid at the next relayout.  
 *    On every exit, the dialog box is closed. The function returns 1, 
 *    if the Okay-button was pressed.
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
#include "folding.h"
#include "X11devcl.h"


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



/* Prototypes
 * ==========
 */


/* from X11dev.c */

char	*class_num	_PP((int n));
void 	gs_exit         _PP((int x));
void   	do_gblExpose    _PP((XEvent *eventp));
void    do_gblConfigureNotify  _PP((XEvent *eventp));


static void   allocateDialogBox         _PP((void));
static Window allocate_selection_point  _PP((int x,int y));
static Window allocate_button		_PP((int x,int y));
static Window allocate_general_button   _PP((int x,int y,int w,int h));
static void   allocate_class_table	_PP((void));

static void draw_dialog_box     _PP((void));
static void draw_text           _PP(( int x, int y, char *m));
static void draw_underl_text    _PP(( int x, int y, char *m));
static void draw_dialog_point   _PP((Window w, int color));
static void normalize_point	_PP((Window w));


#ifdef EVENT_DEBUG
static void prologue    _PP((XEvent *eventp, char *event_name));
#else
#define prologue(a,b)
#endif

static void     dialog_main_loop        _PP((void));
static void     do_KeyPress             _PP((XEvent *eventp));
static void     do_ButtonPress          _PP((XEvent *eventp));
static void     do_EnterNotify          _PP((XEvent *eventp));
static void     do_LeaveNotify          _PP((XEvent *eventp));
static void     do_Expose               _PP((XEvent *eventp));
static void     do_ConfigureNotify      _PP((XEvent *eventp));



/* Positions and Sizes
 * ===================
 */

/* Size of the dialog box */


int dial_width;
int dial_height;

/* Size of a normal point */

#define POINT_W  10 

/* Size of a normal button */

#define BUTTON_W   120



/* Variables
 * =========
 */

/* Dialog handling: On success (i.e. Okay-Button), success becomes 1 */

static int dialog_notready = 1;
static int dialog_success  = 0;


/*  On-Off-points are buttons that switch their state if we select them */

int max_onoff_points;

static GS_SEL_POINT *on_off_point = NULL;


/* Root displays */

static Display *root_display;	/* Root display          */
static int      root_screen;	/* and its screen number */


/* Windows */

static Window	dialog_window;

static Window   okay_button;
static Window   cancel_button;


/* Mouse Buttons */

#define G_MOUSE_LEFT  1
#define G_MOUSE_RIGHT 3


/* the panel font */

extern char Xfontname[512];
static  XFontStruct *dialog_font = NULL;

/* Flag wheter the dialog_box is initialized */

static int dialog_box_there = 0;



/*--------------------------------------------------------------------*/
/*  Dialog box initialization and entry points                        */
/*--------------------------------------------------------------------*/


/*  Initialize the dialog box 
 *  -------------------------
 *  This is done once at the beginning.
 */

#ifdef ANSI_C
void 	x11_init_classes_dialog(Display *rd, int rs)
#else
void 	x11_init_classes_dialog(rd, rs)
Display *rd;
int rs;
#endif
{
	debugmessage("x11_init_classes_dialog","");
	if (dialog_box_there) return;
	root_display = rd;
	root_screen  = rs;
	debugmessage("before XLoadQueryFont","");
	dialog_font = XLoadQueryFont(root_display,Xfontname);
	debugmessage("after XLoadQueryFont","");
	if (!dialog_font) {
		Fatal_error("Font not found. Please use option -font","");
	}

	allocateDialogBox();

	dialog_box_there = 1;
	debugmessage("end of x11_init_classes_dialog","");
}



/*   Destroy the dialog box 
 *   ----------------------
 *   This is done once on ExitDevice.
 */

#ifdef ANSI_C
void	x11_destroy_classes_dialog(Display *rd, int rs)
#else
void	x11_destroy_classes_dialog(rd, rs)
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

	debugmessage("allocateDialogBox","");
	/* select for all events */
	attr.event_mask = KeyPressMask           | 
			  ButtonPressMask        | 
			  EnterWindowMask        | 
                          ExposureMask           | StructureNotifyMask | 
                          SubstructureNotifyMask | 
                          FocusChangeMask        | OwnerGrabButtonMask;

	attr.background_pixel = XWhitePixel(root_display,root_screen);
	attr.border_pixel = XBlackPixel(root_display,root_screen);

	mask |= (CWBackPixel | CWBorderPixel | CWEventMask);

	(void)XQueryPointer(root_display,RootWindow(root_display, root_screen),
		&rret1, &rret2,&xpos, &ypos, &i, &i, &j); 

	allocate_class_table();

        dialog_window = XCreateWindow(root_display, 
				      RootWindow(root_display, root_screen), 
				      xpos, ypos,
                           	      dial_width, dial_height, 
				      Xmyborderwidth, (int)CopyFromParent,
                                      InputOutput, 
				      (Visual *)CopyFromParent,
                           	      mask, &attr);

	hints.flags = PPosition;
	hints.x = xpos;
	hints.y = ypos;

	strcpy(x11_win_label, "VCG ");
        strcat(x11_win_label, Dataname);
        strcat(x11_win_label, " Edge Classes");

	XStoreName(root_display, dialog_window, x11_win_label);
	XSetNormalHints(root_display, dialog_window, &hints);

	XDefineCursor(root_display,dialog_window, 
			XCreateFontCursor(root_display,XC_left_ptr));

	for (i=0; i<max_onoff_points; i++)
		on_off_point[i].w = allocate_selection_point(
					on_off_point[i].x, 
					on_off_point[i].y-10);

	cancel_button = allocate_button(180,5);
	okay_button   = allocate_button(180+BUTTON_W+20,5);
}


/*  Allocate on-off-point table of classes
 *  --------------------------------------
 *  This calculates dial_width and dial_height, too.
 */

#ifdef ANSI_C
static void allocate_class_table(void)
#else
static void allocate_class_table()
#endif
{
	int i, len, xpos1, xpos2, xpos3, diff, mpart, add1, add2, add3;

	debugmessage("allocate_class_table","");
	max_onoff_points = max_nr_classes;
	if (on_off_point) free(on_off_point);
	on_off_point = (GS_SEL_POINT *)malloc(max_onoff_points 
						* sizeof(GS_SEL_POINT));
	if (!on_off_point) Fatal_error("memory exhausted","");

	for (i=0; i<max_onoff_points; i++) {
		on_off_point[i].t = class_num(i+1);
		on_off_point[i].y = 50 + i/3 * 18;
		on_off_point[i].sel = 0;
		on_off_point[i].glob = &(hide_class[i]);
		on_off_point[i].key = ' ';
		if (i<9) on_off_point[i].key = '0'+i+1;
	}

	xpos1 = xpos2 = xpos3 = 0;
	for (i=0; i<max_onoff_points; i+=3) {
		len = XTextWidth(dialog_font,on_off_point[i].t,
				 strlen(on_off_point[i].t));
		if (len>xpos1) xpos1 = len;
	}
	for (i=1; i<max_onoff_points; i+=3) {
		len = XTextWidth(dialog_font,on_off_point[i].t,
				 strlen(on_off_point[i].t));
		if (len>xpos2) xpos2 = len;
	}
	for (i=2; i<max_onoff_points; i+=3) { 
		len = XTextWidth(dialog_font,on_off_point[i].t,
				 strlen(on_off_point[i].t));
		if (len>xpos3) xpos3 = len;
	}

	if (xpos1+xpos2+xpos3+110<220+2*BUTTON_W) {
		diff = 220+2*BUTTON_W - (xpos1+xpos2+xpos3+110);
		mpart = (220+2*BUTTON_W-110)/3;
		add1 = mpart - xpos1;
		if (add1<0) add1 = 0;
		add2 = mpart - xpos2;
		if (add2<0) add2 = 0;
		add3 = mpart - xpos3;
		if (add3<0) add3 = 0;
		xpos1 += (diff * add1)/(add1+add2+add3);
		xpos2 += (diff * add2)/(add1+add2+add3);
		xpos3 += (diff * add3)/(add1+add2+add3);
	}

	for (i=0; i<max_onoff_points; i+=3) 
		on_off_point[i].x = 5;
	for (i=1; i<max_onoff_points; i+=3) 
		on_off_point[i].x = xpos1 + 40;
	for (i=2; i<max_onoff_points; i+=3) 
		on_off_point[i].x = xpos2 + xpos1 + 75;

	dial_height = max_onoff_points/3 * 18 + 70;
	dial_width  = xpos1 + xpos2 + xpos3 + 110;
	if (dial_width < 220+2*BUTTON_W) dial_width = 220+2*BUTTON_W;
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
			  ButtonPressMask        |
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



/*--------------------------------------------------------------------*/
/*   Entry point for the dialog                                       */
/*--------------------------------------------------------------------*/

static int box_exposed;
static int first_exposed = 1;

#ifdef ANSI_C
int x11_print_classes_dialog(void)
#else
int x11_print_classes_dialog()
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

	for (i=0; i<max_onoff_points; i++)
		on_off_point[i].is = *(on_off_point[i].glob);

        XMapRaised(root_display, dialog_window);

	for (i=0; i<max_onoff_points; i++) {
		normalize_point(on_off_point[i].w);
		XMapRaised(root_display, on_off_point[i].w);
	}

        XMapRaised(root_display, okay_button);
        XMapRaised(root_display, cancel_button);
	normalize_point(okay_button);
	normalize_point(cancel_button);

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
		for (i=0; i<max_onoff_points; i++)
			*(on_off_point[i].glob) = on_off_point[i].is;

	}

	return(dialog_success);
}



/*--------------------------------------------------------------------*/
/*   Redraw routine                                                   */
/*--------------------------------------------------------------------*/

/*  Draw dialog box
 *  ---------------
 */

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
		0,0, dial_width, dial_height);

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

	draw_underl_text(5,22,"Show Edge Classes");

	for (i=0; i<max_onoff_points; i++)
		draw_text(on_off_point[i].x+20,on_off_point[i].y,
			  on_off_point[i].t);

	for (i=0; i<max_onoff_points; i++)
		if (on_off_point[i].is == on_off_point[i].sel)
			draw_dialog_point(on_off_point[i].w,1);
		else    draw_dialog_point(on_off_point[i].w,0);

	XSync(root_display, 0);
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
	char lk, uk; 

    	nbytes = XLookupString (e, str, 256, &ks, NULL);
    	if (nbytes < 0) nbytes = 0;
    	if (nbytes > 256) nbytes = 256;
    	str[nbytes] = '\0';

	if (nbytes==1) {
		/* No operation on ' ' */
		if (str[0]==' ') return;

		for (i=0; i<max_onoff_points; i++) {
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
	int i;

	w = e->window;

	act_scroll_window = w;	

	for (i=0; i<max_onoff_points; i++) {
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

	if (w==okay_button) {
		dialog_notready = 0;
		dialog_success  = 1;
	}
	else if (w==cancel_button) {
		dialog_notready = 0;
		dialog_success  = 0;
	}
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

	for (i=0; i<max_onoff_points; i++)
		if (w==on_off_point[i].w) is_point = 1;

	if ((w==okay_button)||(w==cancel_button)) is_point = 1;

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

	for (i=0; i<max_onoff_points; i++)
		if (w==on_off_point[i].w) is_point = 1;

	if ((w==okay_button)||(w==cancel_button)) is_point = 1;

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
		XResizeWindow(root_display, dialog_window,
				dial_width, dial_height);
		draw_dialog_box(); 
	}
	else do_gblConfigureNotify(eventp);
}



/*--------------------------------------------------------------------*/

#endif /* X11 */

