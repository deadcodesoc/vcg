/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */
/*		--------------------------------------		      */
/*								      */
/*   file:	   X11devti.c					      */
/*   version:	   1.00.00					      */
/*   creation:	   9.4.93					      */
/*   author:	   I. Lemke  (...-Version 0.99.99)		      */
/*		   G. Sander (Version 1.00.00-...)		      */
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */
/*   description:  Device driver for X11, Title Dialog Box	      */
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/

#ifndef lint
static char *id_string="$Id: X11devti.c,v 1.8 1995/02/08 18:39:04 sander Exp $";
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
 * $Log: X11devti.c,v $
 * Revision 1.8  1995/02/08  18:39:04  sander
 * Small bug for K&R C solved.
 *
 * Revision 1.7  1995/02/08  11:11:14  sander
 * Distribution version 1.3.
 *
 * Revision 1.6  1994/12/23  18:12:45  sander
 * Manhatten layout added.
 * Option interface cleared.
 * infobox behaviour improved.
 * First version of fisheye (carthesian).
 * Options Noedge and nonode.
 * Titles in the node title box are now sorted.
 *
 * Revision 1.5  1994/11/23  14:50:47  sander
 * Drawing speed improved by removing some superfluous XSyncs.
 *
 * Revision 1.4  1994/08/03  13:58:44  sander
 * Horizontal order mechanism changed.
 * Attribute horizontal_order for edges added.
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
 * Device driver for X11: Title Dialog Box    
 * ---------------------------------------
 *
 * This module contains the management of the dialog box that appears
 * if we want to select a titlei of a node.
 * 
 * This file provides the following functions:
 * ------------------------------------------
 *
 *    x11_init_title_dialog(rd,rs)      initialize the dialogbox.
 *    x11_destroy_title_dialog(rd,rs)   destroys   the dialogbox.
 *
 *    x11_print_title_dialog()
 *
 *    This function opens the dialog box that allows to enter the
 *    title of a node to be centered. Alternatively, we can also
 *    look at the label, etc.
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
#include "X11devti.h"


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
	char   *t;			/* Text of the scroll bar          */
	char   *f;			/* Format of the value             */
	int    yt;			/* Y-Position of the text          */
	int    yv;			/* Y-Position of the value         */
	int    yb;			/* Y-Position of the bar           */
	int    x;			/* X-Position                      */
	int    len;			/* Length of scrollbar             */
	int    is;			/* actual value                    */
	int    *glob;			/* corresponding global value      */
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
void m_center_node      _PP((GNODE v,int invis));
void gs_exit            _PP((int x));
void do_gblExpose       _PP((XEvent *eventp));
void do_gblConfigureNotify  _PP((XEvent *eventp));



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
static void draw_textwin	_PP((void));
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

static void 	read_title_scrollbar	_PP((int val));
static void 	set_title_scrollbar	_PP((void));


/* Positions and Sizes
 * ===================
 */

/* Size of a normal point */

#define POINT_W  10 

/* Size of a normal button */

#define BUTTON_W   130

/* Sizes of a scrollbar and its thumb */

#define SCROLL_W  250  
#define SCROLLBAR_LEN 20

/* Sizes of the scroll window */

#define SCROLLW_W  350 
#define SCROLLW_H  SCROLL_W


/* Positions of the radio points */

#define SEL_POS  SCROLLW_W+35

/* Position of the input text */

#define TEXT_POS 55+SCROLLW_H 

/* Size of the dialog box */

#define DIAL_W   530
#define DIAL_H   TEXT_POS+10


/* Variables
 * =========
 */

/* Dialog handling: On success (i.e. Okay-Button), success becomes 1 */

static int dialog_notready = 1;
static int dialog_success  = 0;

static GNODE act_node;

static char act_title[256];
static int  act_selection = 0;


/*  Radio buttons are partitioned into those that have the same global 
 *  variable. If a radio-button is selected, all other radio buttons 
 *  of the same partition became unselected. 
 */

static int sel_mode = 0;

#define MAX_RADIO_POINTS 6 
static GS_SEL_POINT radio_point[MAX_RADIO_POINTS] = {

/* window,  text           , xpos,      ypos, isval,  selval     , globvar   , key */ 
{  0     ,  "title"        , SEL_POS,     41,    0,      0       , &sel_mode , 't' },   
{  0     ,  "label"        , SEL_POS,     59,    0,      1       , &sel_mode , 'l' },   
{  0     ,  "info field 1" , SEL_POS,     77,    0,      2       , &sel_mode , '1' },   
{  0     ,  "info_field 2" , SEL_POS,     95,    0,      3       , &sel_mode , '2' },   
{  0     ,  "info field 3" , SEL_POS,    113,    0,      4       , &sel_mode , '3' },   
{  0     ,  "co-ordinates" , SEL_POS,    131,    0,      5       , &sel_mode , 'c' }   

};


/*  Horizontal integer scrollbars are used to change a value by the read and 
 *  set functions. Here, these values must be integer values.
 */

static int my_scroll_val = 0;

#define MAX_VSCROLLBARS 1 

#ifdef ANSI_C
static GS_SCROLL_BAR vscrollbar[MAX_VSCROLLBARS] = {

    {  0, 0, "" ,"", 27 , 27, 27, SCROLLW_W+5, SCROLL_W,
		0, &my_scroll_val , &read_title_scrollbar, &set_title_scrollbar }
};
#else
static GS_SCROLL_BAR vscrollbar[MAX_VSCROLLBARS] = {

    {  0, 0, "" ,"", 27 , 27, 27, SCROLLW_W+5, SCROLL_W,
		0, &my_scroll_val , read_title_scrollbar, set_title_scrollbar }
};
#endif


/* Root displays */

static Display *root_display;	/* Root display          */
static int      root_screen;	/* and its screen number */


/* Windows */

static Window	dialog_window;
static Window	scroll_show_window;
static Window	text_window;

static Window   test_button;
static Window   okay_button;
static Window   cancel_button;
static Window   next_button;
static Window   prev_button;


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


/*--------------------------------------------------------------------*/
/*  Sorting auxiliary functions                                       */
/*--------------------------------------------------------------------*/

/*  Compare function for sorting according NTITLE 
 *  ---------------------------------------------
 *  returns 1 if NTITLE(*a) > NTITLE(*b), 0 if equal, -1 otherwise.
 */

#ifdef ANSI_C
static int      compare_ntitle(const GNODE *a, const GNODE *b)
#else
static int      compare_ntitle(a,b)
GNODE   *a;
GNODE   *b;
#endif
{
	int h;

	if ((*a==NULL)&&(*b==NULL))  return(0);
	if (*a==NULL)  return(1);
	if (*b==NULL)  return(-1);
	return(strcmp(NTITLE(*a), NTITLE(*b)));
}


/*  Compare function for sorting according NLABEL 
 *  ---------------------------------------------
 *  returns 1 if NLABEL(*a) > NLABEL(*b), 0 if equal, -1 otherwise.
 */

#ifdef ANSI_C
static int      compare_nlabel(const GNODE *a, const GNODE *b)
#else
static int      compare_nlabel(a,b)
GNODE   *a;
GNODE   *b;
#endif
{
	if ((*a==NULL)&&(*b==NULL))  return(0);
	if (*a==NULL)  return(1);
	if (*b==NULL)  return(-1);
	return(strcmp(NLABEL(*a), NLABEL(*b)));
}


/*  Compare function for sorting according NINFO1 
 *  ---------------------------------------------
 *  returns 1 if NINFO1(*a) > NINFO1(*b), 0 if equal, -1 otherwise.
 */

#ifdef ANSI_C
static int      compare_ninfo1(const GNODE *a, const GNODE *b)
#else
static int      compare_ninfo1(a,b)
GNODE   *a;
GNODE   *b;
#endif
{
	if ((*a==NULL)&&(*b==NULL))  return(0);
	if (*a==NULL)  return(1);
	if (*b==NULL)  return(-1);
	return(strcmp(NINFO1(*a), NINFO1(*b)));
}


/*  Compare function for sorting according NINFO2 
 *  ---------------------------------------------
 *  returns 1 if NINFO2(*a) > NINFO2(*b), 0 if equal, -1 otherwise.
 */

#ifdef ANSI_C
static int      compare_ninfo2(const GNODE *a, const GNODE *b)
#else
static int      compare_ninfo2(a,b)
GNODE   *a;
GNODE   *b;
#endif
{
	if ((*a==NULL)&&(*b==NULL))  return(0);
	if (*a==NULL)  return(1);
	if (*b==NULL)  return(-1);
	return(strcmp(NINFO2(*a), NINFO2(*b)));
}


/*  Compare function for sorting according NINFO3 
 *  ---------------------------------------------
 *  returns 1 if NINFO3(*a) > NINFO3(*b), 0 if equal, -1 otherwise.
 */

#ifdef ANSI_C
static int      compare_ninfo3(const GNODE *a, const GNODE *b)
#else
static int      compare_ninfo3(a,b)
GNODE   *a;
GNODE   *b;
#endif
{
	if ((*a==NULL)&&(*b==NULL))  return(0);
	if (*a==NULL)  return(1);
	if (*b==NULL)  return(-1);
	return(strcmp(NINFO3(*a), NINFO3(*b)));
}


/*  Compare function for sorting according NLABEL 
 *  ---------------------------------------------
 *  returns 1 if NX(*a) > NX(*b), 0 if equal, -1 otherwise.
 */

#ifdef ANSI_C
static int      compare_nxy(const GNODE *a, const GNODE *b)
#else
static int      compare_nxy(a,b)
GNODE   *a;
GNODE   *b;
#endif
{
	if ((*a==NULL)&&(*b==NULL))  return(0);
	if (*a==NULL)  return(1);
	if (*b==NULL)  return(-1);
	if (NX(*a)<NX(*b)) return(-1);
	if (NX(*a)>NX(*b)) return(1);
	if (NY(*a)<NY(*b)) return(-1);
	if (NY(*a)>NY(*b)) return(1);
	return(0);
}


/*  Resort the node table 
 *  ---------------------
 *  The node table is used to show the nodes in a sorted order in title
 *  dialog box.
 */


static GNODE *node_table = NULL;   /* Table to sort the nodes */
static int    act_node_table_pos;


#ifdef ANSI_C
static void resort_node_table(void)
#else
static void resort_node_table()
#endif
{
	if (!node_table) return; 
#ifdef ANSI_C
	switch (sel_mode) {
	case 0: qsort(node_table,act_hash_size,sizeof(GNODE),
		  	(int (*) (const void *, const void *))compare_ntitle);
		break;
	case 1: qsort(node_table,act_hash_size,sizeof(GNODE),
		  	(int (*) (const void *, const void *))compare_nlabel);
		break;
	case 2: qsort(node_table,act_hash_size,sizeof(GNODE),
		  	(int (*) (const void *, const void *))compare_ninfo1);
		break;
	case 3: qsort(node_table,act_hash_size,sizeof(GNODE),
		  	(int (*) (const void *, const void *))compare_ninfo2);
		break;
	case 4: qsort(node_table,act_hash_size,sizeof(GNODE),
		  	(int (*) (const void *, const void *))compare_ninfo3);
		break;
	case 5: qsort(node_table,act_hash_size,sizeof(GNODE),
		  	(int (*) (const void *, const void *))compare_nxy);
		break;
	}
#else
	switch (sel_mode) {
	case 0: qsort(node_table,act_hash_size,sizeof(GNODE), 
				compare_ntitle);
		break;
	case 1: qsort(node_table,act_hash_size,sizeof(GNODE),
		  		compare_nlabel);
		break;
	case 2: qsort(node_table,act_hash_size,sizeof(GNODE),
		  		compare_ninfo1);
		break;
	case 3: qsort(node_table,act_hash_size,sizeof(GNODE),
		  		compare_ninfo2);
		break;
	case 4: qsort(node_table,act_hash_size,sizeof(GNODE),
		  		compare_ninfo3);
		break;
	case 5: qsort(node_table,act_hash_size,sizeof(GNODE),
		  		compare_nxy);
		break;
	}
#endif

}



/*--------------------------------------------------------------------*/
/*  Dialog box initialization and entry points                        */
/*--------------------------------------------------------------------*/

/*  Initialize the dialog box 
 *  -------------------------
 *  This is done once at the beginning.
 */

#ifdef ANSI_C
void 	x11_init_title_dialog(Display *rd, int rs)
#else
void 	x11_init_title_dialog(rd, rs)
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
void	x11_destroy_title_dialog(Display *rd, int rs)
#else
void	x11_destroy_title_dialog(rd, rs)
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
        strcat(x11_win_label, " Title");


	XStoreName(root_display, dialog_window, x11_win_label);
	XSetNormalHints(root_display, dialog_window, &hints);

        text_window = XCreateWindow(root_display, dialog_window,
				      5, TEXT_POS-22,
                           	      DIAL_W-10, 25, 
				      1, (int)CopyFromParent,
                                      InputOutput, 
				      (Visual *)CopyFromParent,
                           	      mask, &attr);

        scroll_show_window = XCreateWindow(root_display, dialog_window,
				      5, 27,
                                      SCROLLW_W, SCROLLW_H, 
				      1, (int)CopyFromParent,
                                      InputOutput, 
				      (Visual *)CopyFromParent,
                           	      mask, &attr);

	XDefineCursor(root_display,text_window, 
			XCreateFontCursor(root_display,XC_xterm));
	XDefineCursor(root_display,dialog_window, 
			XCreateFontCursor(root_display,XC_left_ptr));

	scrollCursor = XCreateFontCursor(root_display,XC_sb_v_double_arrow);

	for (i=0; i<MAX_RADIO_POINTS; i++)
		radio_point[i].w = allocate_selection_point(
					radio_point[i].x,
					radio_point[i].y-10);

	for (i=0; i<MAX_VSCROLLBARS; i++) {
		vscrollbar[i].ws = allocate_scroll_bar(vscrollbar[i].x,
						       vscrollbar[i].yb, 
						       vscrollbar[i].len);
		vscrollbar[i].wt = last_tmb;
	}
	

	test_button   = allocate_button(SEL_POS,179);
	cancel_button = allocate_button(SEL_POS,179+35);
	okay_button   = allocate_button(SEL_POS,179+70);
	next_button   = allocate_general_button(SEL_POS,145,60,20);
	prev_button   = allocate_general_button(SEL_POS+70,145,60,20);
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
                           8, len, 
                           1, (int)CopyFromParent,
                           InputOutput,
                           (Visual *)CopyFromParent,
                           mask, &attr);
        wt = XCreateSimpleWindow (root_display, w, 0,0,
                                    6, SCROLLBAR_LEN, 
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
GNODE x11_print_title_dialog(void)
#else
GNODE x11_print_title_dialog()
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


	act_node = NULL;
	act_title[0] = 0;
	act_selection = 0;
	strcpy(act_title,"Enter title: _");
	init_hash_cursor();
	my_scroll_val = sel_mode = 0;
	box_exposed = 0;

	node_table = (GNODE *)malloc((act_hash_size)*sizeof(GNODE));
	if (node_table) {
		for (i=0; i<act_hash_size; i++) node_table[i]=0;
		position_hash_cursor(0);
		for (i=0; i<act_hash_size; i++)
			node_table[i] = get_hash_cursor_succ(i);
		resort_node_table();
	}

	for (i=0; i<MAX_RADIO_POINTS; i++)
		radio_point[i].is = *(radio_point[i].glob);

	for (i=0; i<MAX_VSCROLLBARS; i++) 
		vscrollbar[i].is = *(vscrollbar[i].glob);

        XMapRaised(root_display, dialog_window);
        XMapRaised(root_display, scroll_show_window);
        XMapRaised(root_display, text_window);

	for (i=0; i<MAX_RADIO_POINTS; i++) {
		XMapRaised(root_display, radio_point[i].w);
		normalize_point(radio_point[i].w);
	}
	for (i=0; i<MAX_VSCROLLBARS; i++) {
        	XMapRaised(root_display, vscrollbar[i].ws);
        	XMapRaised(root_display, vscrollbar[i].wt);
	}

        XMapRaised(root_display, test_button);
        XMapRaised(root_display, okay_button);
        XMapRaised(root_display, cancel_button);
        XMapRaised(root_display, next_button);
        XMapRaised(root_display, prev_button);
	normalize_point(test_button);
	normalize_point(okay_button);
	normalize_point(cancel_button);
	normalize_point(next_button);
	normalize_point(prev_button);

	for (i=0; i<MAX_VSCROLLBARS; i++) (*(vscrollbar[i].sf))();

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

	if (node_table) free(node_table);
	node_table = NULL;
	i=0;
	while ((act_title[i]) && (i<253)) i++;
	if (act_title[i-1]=='_') i--;
	act_title[i]=0;
	act_node = search_visible_node(&(act_title[13]));
	if (dialog_success)  return(act_node); 
	else		     return(NULL);
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

	i = XTextWidth(dialog_font,"next",strlen("next"));
	i = (60-i)/2;
	XDrawString(root_display,
		(Drawable)next_button,
		XDefaultGC(root_display, root_screen),
		i,16,"next",strlen("next"));

	i = XTextWidth(dialog_font,"prev.",strlen("prev."));
	i = (60-i)/2;
	XDrawString(root_display,
		(Drawable)prev_button,
		XDefaultGC(root_display, root_screen),
		i,16,"prev.",strlen("prev."));

	i = XTextWidth(dialog_font,"Apply",strlen("Apply"));
	i = (BUTTON_W-i)/2;
	XDrawString(root_display,
		(Drawable)test_button,
		XDefaultGC(root_display, root_screen),
		i,18,"Apply",strlen("Apply"));


	draw_underl_text(5,18,"Select a graph node");

	for (i=0; i<MAX_RADIO_POINTS; i++)
		draw_text(radio_point[i].x+20,radio_point[i].y,
			  radio_point[i].t);

	/* for (i=0; i<MAX_VSCROLLBARS; i++) 
	 * 	draw_text(vscrollbar[i].x, vscrollbar[i].yt, vscrollbar[i].t);
	 */

	for (i=0; i<MAX_RADIO_POINTS; i++)
		if (radio_point[i].is == radio_point[i].sel)
			draw_dialog_point(radio_point[i].w,1);
		else    draw_dialog_point(radio_point[i].w,0);

	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XWhitePixel(root_display, root_screen));
	XFillRectangle(root_display, 
		(Drawable)text_window,
		XDefaultGC(root_display, root_screen),
		0,0, DIAL_W, 25);
	draw_sizes();

	for (i=0; i<MAX_VSCROLLBARS; i++) (*(vscrollbar[i].sf))();

	XSync(root_display, 0);
}


static char mxbuffer[128];

#ifdef ANSI_C
static void draw_sizes(void)
#else
static void draw_sizes()
#endif
{
	int i, j, yp;
	GNODE h;
	char *c;

	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XWhitePixel(root_display, root_screen));
	XFillRectangle(root_display, 
		(Drawable)scroll_show_window,
		XDefaultGC(root_display, root_screen),
		0,0, SCROLLW_W, SCROLLW_H);

	if (node_table) act_node_table_pos = vscrollbar[0].is;
	else		position_hash_cursor(vscrollbar[0].is);

	yp = 18;
	if (vscrollbar[0].is+act_selection>=act_hash_size) 
		act_selection = act_hash_size-1-vscrollbar[0].is;
	if (act_selection<0) act_selection = 0;
	if (act_selection>SCROLLW_H/18) act_selection = SCROLLW_H/18;

	for (i=0; i<(SCROLLW_H/18+1); i++) {
		if (node_table) {
			if (act_node_table_pos+i<act_hash_size) 
				h = node_table[act_node_table_pos+i];
			else h = NULL;
		}
		else h = get_hash_cursor_succ(i);

		XSetForeground(root_display,
			XDefaultGC(root_display, root_screen),
			XBlackPixel(root_display, root_screen));
		if (i==act_selection) {
			XFillRectangle(root_display, 
				(Drawable)scroll_show_window,
				XDefaultGC(root_display, root_screen),
				0,yp-16, SCROLLW_W, 19);
			XSetForeground(root_display,
				XDefaultGC(root_display, root_screen),
				XWhitePixel(root_display, root_screen));
			if (h) SPRINTF(act_title,"Enter title: %s_",NTITLE(h));
			else   SPRINTF(act_title,"Enter title: _");
			XFillRectangle(root_display, 
				(Drawable)text_window,
				XDefaultGC(root_display, root_screen),
				0, 0, DIAL_W, 25);
		}

		if (!h) strcpy(mxbuffer,"");
		else {	for (j=0; j<MAX_RADIO_POINTS; j++)
                        	if (radio_point[j].is == radio_point[j].sel)
					break;

			switch(j) {
			case 0: c = NTITLE(h);    break;
			case 1: c = NLABEL(h);    break;
			case 2: c = NINFO1(h);    break;
			case 3: c = NINFO2(h);    break;
			case 4: c = NINFO3(h);    break;
			case 5: SPRINTF(mxbuffer,"(%d,%d)",NX(h),NY(h)); break;
			}

			if (j!=5) {
				j = 0;
				while ((*c)&&(j<127)) {
					switch (*c) {
					case '\n': mxbuffer[j++]='|'; break;
					case '\t': mxbuffer[j++]=' '; break;
					case '\r': break;
					case '\v': break;
#ifdef ANSI_C
					case '\a': break;
#endif
					case '\b': break;
					case '\f': 
						c++;
						if (!*c) break;
						if (*c=='u');
						else if (*c=='n');
						else { c++; if (!*c) break; }
						break;
					default  : mxbuffer[j++] = *c;
					}
					c++;
				}
				mxbuffer[j] = 0;
			}
		}

		XDrawString(root_display,
			(Drawable)scroll_show_window,
			XDefaultGC(root_display, root_screen),
			2,yp,mxbuffer,strlen(mxbuffer));
		yp += 18;
	}
	draw_textwin();
	
	/* XSync(root_display, 0); */
}


#ifdef ANSI_C
static void draw_textwin(void)
#else
static void draw_textwin()
#endif
{
	int i;

	i=0;
	while ((act_title[i]) && (i<253)) i++;
	if (act_title[i-1]=='_') i--;
	act_title[i]=0;
	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XWhitePixel(root_display, root_screen));
	XFillRectangle(root_display, 
		(Drawable)text_window,
		XDefaultGC(root_display, root_screen),
		5+XTextWidth(dialog_font,act_title,strlen(act_title)),
		0, DIAL_W, 25);
	act_title[i]='_';
	act_title[i+1]=0;
	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XBlackPixel(root_display, root_screen));
	XDrawString(root_display,
		(Drawable)text_window,
		XDefaultGC(root_display, root_screen),
		5,18,act_title,strlen(act_title));
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
static void draw_dialog_point(Window w, int color)
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
    	int nbytes, i, j, old_sel_mode;
    	char str[256+1];
	char lk, uk;

	old_sel_mode = sel_mode;

    	nbytes = XLookupString (e, str, 256, &ks, NULL);
    	if (nbytes < 0) nbytes = 0;
    	if (nbytes > 256) nbytes = 256;
    	str[nbytes] = '\0';

	if (ks==0xff54) { /* Down */
		if (vscrollbar[0].is<act_hash_size-1) vscrollbar[0].is++;
		set_title_scrollbar();
		draw_sizes();
		return;
	}
	else if (ks==0xff53) { /* Right */
		if (vscrollbar[0].is<act_hash_size-1) vscrollbar[0].is++;
		set_title_scrollbar();
		draw_sizes();
		return;
	}
	else if (ks==0xff52) { /* Up */
		if (vscrollbar[0].is>0) vscrollbar[0].is--;
		else act_selection--;
		set_title_scrollbar();
		draw_sizes();
		return;
	}
	else if (ks==0xff51) { /* Left */
		if (vscrollbar[0].is>0) vscrollbar[0].is--;
		else act_selection--;
		set_title_scrollbar();
		draw_sizes();
		return;
	}

	if (nbytes==1) {

		if (e->window == text_window) {
			i = 0;
			while ((act_title[i]) && (i<253)) i++;
			if (act_title[i-1]=='_') i--;
			act_title[i]=0;
			XSetForeground(root_display,
				XDefaultGC(root_display, root_screen),
				XWhitePixel(root_display, root_screen));
			XFillRectangle(root_display, 
				(Drawable)text_window,
				XDefaultGC(root_display, root_screen),
				5+XTextWidth(dialog_font,act_title,strlen(act_title)),
				0, DIAL_W, 25);
			if ((ks==0xff08)||(ks==0xffff)) { 
				i--; 
				if (i<13) i=13; 
				act_title[i]=0;
			}
			else if ((ks==0xff0a)||(ks==0xff0d)) { 
				dialog_notready = 0;
				dialog_success  = 1;
			}
			else if (str[0]==27) {
				dialog_notready = 0;
				dialog_success  = 0;
			}
			else { 	/* assert((i<=253)); */
				act_title[i]  = str[0];
				act_title[i+1]= 0;
			}
			act_title[255] = 0;
			draw_textwin();
			return;
		}
		/* No operation on ' ' */
		if (str[0]==' ') return;

               	for (i=0; i<MAX_RADIO_POINTS; i++) {
                        lk = uk = radio_point[i].key;
                        lk = tolower(lk);
                        uk = toupper(uk);
                        if ((lk==str[0])||(uk==str[0])) {
                                radio_point[i].is = radio_point[i].sel;
                                *(radio_point[i].glob) = radio_point[i].sel;
                                break;
                        }
                }

                if (i<MAX_RADIO_POINTS) {
                        for (j=0; j<MAX_RADIO_POINTS; j++) {
                                if ((i!=j) && (radio_point[i].glob==radio_point[j].glob))
                                        radio_point[j].is = radio_point[j].sel-1
;
                        }
			if (old_sel_mode != sel_mode) resort_node_table();
			draw_dialog_box();
			return;
                }

		switch (str[0]) {
		case '_' :
		case '-' :
		case 'p' :
		case 'P' :
			if (vscrollbar[0].is>0) vscrollbar[0].is--;
			else act_selection--;
			set_title_scrollbar();
			draw_sizes();
			return;
		case '*' :
		case '+' :
		case 'n' :
		case 'N' :
			if (vscrollbar[0].is<act_hash_size-1) vscrollbar[0].is++;
			set_title_scrollbar();
			draw_sizes();
			return;

		case 'a': 
		case 'A': 
			i=0;
			while ((act_title[i]) && (i<253)) i++;
			if (act_title[i-1]=='_') i--;
			act_title[i]=0;
			act_node = search_visible_node(&(act_title[13]));
			m_center_node(act_node,0);
			return;
		case '\r': /* Carriage Return */
		case '\n': /* Carriage Return */
			dialog_notready = 0;
			dialog_success  = 1;
			return;
		case 27: /* Cancel */
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
	int i,j, old_sel_mode;

	w = e->window;

	act_scroll_window = w;	
	old_sel_mode = sel_mode;

	for (i=0; i<MAX_RADIO_POINTS; i++) {
		if (w == radio_point[i].w) {
			radio_point[i].is = radio_point[i].sel;
			*(radio_point[i].glob) = radio_point[i].sel;
			break;
		}
	}

	if (i<MAX_RADIO_POINTS) {
		for (j=0; j<MAX_RADIO_POINTS; j++) {
			if ((i!=j) && (radio_point[i].glob==radio_point[j].glob)) 
				radio_point[j].is = radio_point[j].sel-1;
		}
		if (old_sel_mode != sel_mode) resort_node_table();
		draw_sizes();
	}

	for (i=0; i<MAX_RADIO_POINTS; i++)
		if (radio_point[i].is == radio_point[i].sel)
			draw_dialog_point(radio_point[i].w,1);
		else    draw_dialog_point(radio_point[i].w,0);


	for (i=0; i<MAX_VSCROLLBARS; i++) {
		if (act_scroll_window==vscrollbar[i].ws) {
		 	(*(vscrollbar[i].rf))(e->y);
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
		i=0;
		while ((act_title[i]) && (i<253)) i++;
		if (act_title[i-1]=='_') i--;
		act_title[i]=0;
		act_node = search_visible_node(&(act_title[13]));
		m_center_node(act_node,0);
	}
	else if (w==next_button) {
		if (vscrollbar[0].is<act_hash_size-1) vscrollbar[0].is++;
		set_title_scrollbar();
		draw_sizes();
	}
	else if (w==prev_button) {
		if (vscrollbar[0].is>0) vscrollbar[0].is--;
		else act_selection--;
		set_title_scrollbar();
		draw_sizes();
	}
	else if (w==scroll_show_window) {
		act_selection = (e->y)/18;
		draw_sizes();
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
		for (i=0; i<MAX_VSCROLLBARS; i++) (*(vscrollbar[i].sf))();
		draw_dialog_box();
		act_scroll_window = 0; 
		return;
	}

	for (i=0; i<MAX_VSCROLLBARS; i++) {
		if (act_scroll_window==vscrollbar[i].ws) {
		 	(*(vscrollbar[i].rf))(e->y);
			break;
		}
	}
	if (i<MAX_VSCROLLBARS) draw_sizes();
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

	for (i=0; i<MAX_RADIO_POINTS; i++)
		if (w==radio_point[i].w) is_point = 1;

	if (  (w==okay_button)||(w==cancel_button)||(w==test_button)
	    ||(w==next_button)||(w==prev_button))   is_point = 1;

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

	for (i=0; i<MAX_RADIO_POINTS; i++)
		if (w==radio_point[i].w) is_point = 1;

	if (  (w==okay_button)||(w==cancel_button)||(w==test_button)
	    ||(w==next_button)||(w==prev_button))   is_point = 1;

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

	for (i=0; i<MAX_VSCROLLBARS; i++) { 
		if (act_scroll_window==vscrollbar[i].ws) {
		 	(*(vscrollbar[i].rf))(e->y);
			break;
		}
	}
	if (i<MAX_VSCROLLBARS) draw_sizes();
}


/*--------------------------------------------------------------------*/
/*  Scrollbar handling 						      */
/*--------------------------------------------------------------------*/


#ifdef ANSI_C
static void read_title_scrollbar(int val)
#else
static void read_title_scrollbar(val)
int val;
#endif
{
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= vscrollbar[0].len) 
		val = vscrollbar[0].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,vscrollbar[0].wt,0,val,6,SCROLLBAR_LEN);
	vscrollbar[0].is = act_hash_size*val/(vscrollbar[0].len-SCROLLBAR_LEN);
}


#ifdef ANSI_C
static void set_title_scrollbar(void)
#else
static void set_title_scrollbar()
#endif
{
	int val;

	val =  (vscrollbar[0].is)*(vscrollbar[0].len-SCROLLBAR_LEN)/act_hash_size;
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= vscrollbar[0].len) 
		val = vscrollbar[0].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display, vscrollbar[0].wt,0,val,6,SCROLLBAR_LEN);
}


/*--------------------------------------------------------------------*/

#endif /* X11 */

