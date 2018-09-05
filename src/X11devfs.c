/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */
/*		--------------------------------------		      */
/*								      */
/*   file:	   X11devfs.c					      */
/*   version:	   1.00.00					      */
/*   creation:	   9.4.93					      */
/*   author:	   I. Lemke  (...-Version 0.99.99)		      */
/*		   G. Sander (Version 1.00.00-...)		      */
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */
/*   description:  Device driver for X11, File Selector Dialog Box    */ 
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/

#ifndef lint
static char *id_string="$Id: X11devfs.c,v 1.7 1995/02/09 20:44:22 sander Exp $";
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
 * $Log: X11devfs.c,v $
 * Revision 1.7  1995/02/09  20:44:22  sander
 * Call of getwd removed.
 *
 * Revision 1.6  1995/02/08  11:11:14  sander
 * Distribution version 1.3.
 *
 * Revision 1.5  1994/12/23  18:12:45  sander
 * Manhatten layout added.
 * Option interface cleared.
 * infobox behaviour improved.
 * First version of fisheye (carthesian).
 * Options Noedge and nonode.
 * Titles in the node title box are now sorted.
 *
 * Revision 1.4  1994/11/23  14:50:47  sander
 * Drawing speed improved by removing some superfluous XSyncs.
 *
 * Revision 1.3  1994/08/03  13:58:44  sander
 * Horizontal order mechanism changed.
 * Attribute horizontal_order for edges added.
 *
 * Revision 1.2  1994/06/07  14:09:59  sander
 * Splines implemented.
 * HP-UX, Linux, AIX, Sun-Os, IRIX compatibility tested.
 * The tool is now ready to be distributed.
 *
 * Revision 1.1  1994/05/16  08:56:03  sander
 * Initial revision
 *
 */

/************************************************************************
 * Device driver for X11: File Selector Dialog Box
 * -----------------------------------------------
 *
 * This module contains the management of the dialog box that appears
 * if we want to select a file.
 * 
 * This file provides the following functions:
 * ------------------------------------------
 *
 *    x11_init_fisel_dialog(rd,rs)      initialize the dialogbox.
 *    x11_destroy_fisel_dialog(rd,rs)   destroys   the dialogbox.
 *
 *    x11_print_fisel_dialog()
 *
 *    This function opens the dialog box that allows to enter the
 *    name of a file.
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
#ifdef VMS
#include <unixio.h>
#include <unixlib.h>
#include <processes.h>
#include <file.h>
#include <descrip.h>
#include <rmsdef.h>
#include <rms.h>
#include <types.h>
#include <ssdef.h>
#include <stat.h>
#define STAT stat
#else
#include <sys/types.h> 
#include <sys/stat.h> 
#include <sys/param.h> 
#include <dirent.h> 
#include <grp.h> 
#include <pwd.h> 
#endif
#include <time.h> 
#include <string.h> 
#include <math.h>
#include "options.h"
#include "main.h"
#include "grammar.h"
#include "X11devfs.h"


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

void    gs_exit         _PP((int x));
void    do_gblExpose    _PP((XEvent *eventp));
void    do_gblConfigureNotify  _PP((XEvent *eventp));

 
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

static void 	read_fisel_scrollbar	_PP((int val));
static void 	set_fisel_scrollbar	_PP((void));

static int 	calc_dir_entries	_PP((void));
static void 	alloc_fnames		_PP((void));
static void 	rescan_fnames		_PP((void));
static int      compare_fnames		_PP((const int *a,const int *b));
static int      compare_finfos		_PP((const int *a,const int *b));


/* Positions and Sizes
 * ===================
 */

/* Size of a normal point */

#define POINT_W  10 

/* Size of a normal button */

#define BUTTON_W   130

/* Sizes of a scrollbar and its thumb */

#define SCROLL_W  286  
#define SCROLLBAR_LEN 20

/* Sizes of the scroll window */

#define SCROLLW_W  460 
#define SCROLLW_H  SCROLL_W


/* Positions of the radio points */

#define SEL_POS  SCROLLW_W+35

/* Position of the input text */

#define TEXT_POS 55+SCROLLW_H 

/* Size of the dialog box */

#define DIAL_W   660
#define DIAL_H   TEXT_POS+30+10

/* Size of the filename */

#define FNAMESIZE 34  

/* Size of the infofield */

#define INFOSIZE  16  


/* Variables
 * =========
 */

/* Dialog handling: On success (i.e. Okay-Button), success becomes 1 */

static int dialog_notready = 1;
static int dialog_success  = 0;

#ifndef MAXPATHLEN
#define MAXPATHLEN 1024
#endif

static char act_fisel[256];
static char act_path[MAXPATHLEN];
static char act_fpath[MAXPATHLEN];
static int  act_selection = -1;
static int  old_selection = -1;

/* Buffers for the file names and infos
 */

static int act_fbuf_size = 0;
static int max_fname     = 0;
static char *act_fnames  = NULL;
static char *act_infos   = NULL;
static int  *act_fsort   = NULL;
static char *act_dirtag  = NULL;


/*  Radio buttons are partitioned into those that have the same global 
 *  variable. If a radio-button is selected, all other radio buttons 
 *  of the same partition became unselected. 
 */

static int sel_mode = 0;
static int sort_mode = 1;
static int presel_mode = 0;

#define MAX_RADIO_POINTS 13 
static GS_SEL_POINT radio_point[MAX_RADIO_POINTS] = {

/* window,  text                 , xpos,      ypos, isval,  selval     , globvar   , key */ 
{  0     ,  "size"               , SEL_POS,     41,    0,      0       , &sel_mode , 's' },   
{  0     ,  "mode"               , SEL_POS,     59,    0,      1       , &sel_mode , 'm' },   
{  0     ,  "date"               , SEL_POS,     77,    0,      2       , &sel_mode , 'd' },   
{  0     ,  "owner"              , SEL_POS,     95,    0,      3       , &sel_mode , 'o' },   
{  0     ,  "group"              , SEL_POS,    113,    0,      4       , &sel_mode , 'g' },   
{  0     ,  "unsorted"           , SEL_POS,    131,    0,      0       , &sort_mode, 'u' },   
{  0     ,  "sorted by name"     , SEL_POS,    149,    0,      1       , &sort_mode, 'b' },   
{  0     ,  "sorted by info"     , SEL_POS,    167,    0,      2       , &sort_mode, 'i' }, 

{  0     ,  "all"                , SEL_POS+80,  41,    0,      0       , &presel_mode , 'a' },   
{  0     ,  "*.vcg"              , SEL_POS+80,  59,    0,      1       , &presel_mode , 'v' },   
{  0     ,  "*.ps"               , SEL_POS+80,  77,    0,      2       , &presel_mode , ' ' },   
{  0     ,  "*.pbm"              , SEL_POS+80,  95,    0,      3       , &presel_mode , ' ' },   
{  0     ,  "*.ppm"              , SEL_POS+80, 113,    0,      4       , &presel_mode , ' ' }   

};


/*  Horizontal integer scrollbars are used to change a value by the read and 
 *  set functions. Here, these values must be integer values.
 */

static int my_scroll_val = 0;

#define MAX_VSCROLLBARS 1 

#ifdef ANSI_C
static GS_SCROLL_BAR vscrollbar[MAX_VSCROLLBARS] = {

    {  0, 0, "" ,"", 27 , 27, 27, SCROLLW_W+5, SCROLL_W,
		0, &my_scroll_val , &read_fisel_scrollbar, &set_fisel_scrollbar }
};
#else
static GS_SCROLL_BAR vscrollbar[MAX_VSCROLLBARS] = {

    {  0, 0, "" ,"", 27 , 27, 27, SCROLLW_W+5, SCROLL_W,
		0, &my_scroll_val , read_fisel_scrollbar, set_fisel_scrollbar }
};
#endif


/* Root displays */

static Display *root_display;	/* Root display          */
static int      root_screen;	/* and its screen number */


/* Windows */

static Window	dialog_window;
static Window	scroll_show_window;
static Window	text_window;
static Window	path_window;

static Window   resc_button;
static Window   okay_button;
static Window   cancel_button;
static Window   next_button;
static Window   prev_button;


/* Cursors */

static Cursor scrollCursor; 
static Cursor pointCursor; 
static Cursor busyCursor; 

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
void 	x11_init_fisel_dialog(Display *rd, int rs)
#else
void 	x11_init_fisel_dialog(rd, rs)
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
void	x11_destroy_fisel_dialog(Display *rd, int rs)
#else
void	x11_destroy_fisel_dialog(rd, rs)
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
        strcat(x11_win_label, " File");

	XStoreName(root_display, dialog_window, x11_win_label);
	XSetNormalHints(root_display, dialog_window, &hints);

        path_window = XCreateWindow(root_display, dialog_window,
				      5, TEXT_POS-22,
                           	      DIAL_W-10, 25, 
				      1, (int)CopyFromParent,
                                      InputOutput, 
				      (Visual *)CopyFromParent,
                           	      mask, &attr);

        text_window = XCreateWindow(root_display, dialog_window,
				      5, TEXT_POS-22+28,
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

	XDefineCursor(root_display,path_window, 
			XCreateFontCursor(root_display,XC_xterm));
	XDefineCursor(root_display,text_window, 
			XCreateFontCursor(root_display,XC_xterm));
	pointCursor = XCreateFontCursor(root_display,XC_left_ptr);
	busyCursor  = XCreateFontCursor(root_display,XC_watch);
	XDefineCursor(root_display,dialog_window,pointCursor); 

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
	

	resc_button   = allocate_button(SEL_POS,181+34);
	cancel_button = allocate_button(SEL_POS,181+34+35);
	okay_button   = allocate_button(SEL_POS,181+34+70);
	next_button   = allocate_general_button(SEL_POS,181,60,20);
	prev_button   = allocate_general_button(SEL_POS+70,181,60,20);
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
char *x11_print_fisel_dialog(void)
#else
char *x11_print_fisel_dialog()
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

	old_selection = -1;
	act_fisel[0]  = 0;
	act_path[0]   = 0;
	act_fpath[0]  = 0;
	act_selection = 0;
	sel_mode = presel_mode = 0;
	for (i=0; i<MAX_RADIO_POINTS; i++)
		radio_point[i].is = *(radio_point[i].glob);
        if (!getcwd(act_path,MAXPATHLEN-1)) act_path[0]=0;
	SPRINTF(act_fpath,"Enter path: %s_",act_path);
	vscrollbar[0].is = 0;
	rescan_fnames();
	SPRINTF(act_fpath,"Enter path: %s_",act_path);

	my_scroll_val = sel_mode = presel_mode = 0;
	sort_mode = 1;
	box_exposed = 0;

        XMapRaised(root_display, dialog_window);
        XMapRaised(root_display, scroll_show_window);
        XMapRaised(root_display, path_window);
        XMapRaised(root_display, text_window);

	for (i=0; i<MAX_RADIO_POINTS; i++) {
		XMapRaised(root_display, radio_point[i].w);
		normalize_point(radio_point[i].w);
	}
	for (i=0; i<MAX_VSCROLLBARS; i++) {
        	XMapRaised(root_display, vscrollbar[i].ws);
        	XMapRaised(root_display, vscrollbar[i].wt);
	}

        XMapRaised(root_display, resc_button);
        XMapRaised(root_display, okay_button);
        XMapRaised(root_display, cancel_button);
        XMapRaised(root_display, next_button);
        XMapRaised(root_display, prev_button);
	normalize_point(resc_button);
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

	i=0;
	while ((act_fisel[i]) && (i<253)) i++;
	if (act_fisel[i-1]=='_') i--;
	act_fisel[i]=0;
	i=0;
	while ((act_fpath[i]) && (i<MAXPATHLEN-3)) i++;
	if (act_fpath[i-1]=='_') i--;
	act_fpath[i]=0;

#ifdef VMS
	SPRINTF(act_path,"%s%s",&(act_fpath[12]), &(act_fisel[16]) );
#else
	SPRINTF(act_path,"%s/%s",&(act_fpath[12]), &(act_fisel[16]) );
#endif
	if (dialog_success)  return(act_path); 
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

	i = XTextWidth(dialog_font,"Rescan",strlen("Rescan"));
	i = (BUTTON_W-i)/2;
	XDrawString(root_display,
		(Drawable)resc_button,
		XDefaultGC(root_display, root_screen),
		i,18,"Rescan",strlen("Rescan"));


	draw_underl_text(5,18,"Select a filename");

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
		(Drawable)path_window,
		XDefaultGC(root_display, root_screen),
		0,0, DIAL_W, 25);
	XFillRectangle(root_display, 
		(Drawable)text_window,
		XDefaultGC(root_display, root_screen),
		0,0, DIAL_W, 25);
	draw_sizes();

	for (i=0; i<MAX_VSCROLLBARS; i++) (*(vscrollbar[i].sf))();

	XSync(root_display, 0);
}



#ifdef ANSI_C
static void draw_sizes(void)
#else
static void draw_sizes()
#endif
{
	int i, k, yp;
	char *c1,*c2,*c3,isdir;

	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XWhitePixel(root_display, root_screen));
	XFillRectangle(root_display, 
		(Drawable)scroll_show_window,
		XDefaultGC(root_display, root_screen),
		0,0, SCROLLW_W, SCROLLW_H);

	k = vscrollbar[0].is;

	yp = 18;
	if (vscrollbar[0].is>=max_fname+2) vscrollbar[0].is = max_fname+1;
	if (act_selection   >=max_fname+2) act_selection    = max_fname+1; 
	if (vscrollbar[0].is<0) vscrollbar[0].is = 0;
	if (act_selection<0)    act_selection    = 0;

	for (i=0; i<(SCROLLW_H/18+1); i++) {

		if (k+i==0)      { c1 = ".";  c2 = c3 = ""; isdir = 0; }
		else if (k+i==1) { c1 = ".."; c2 = c3 = ""; isdir = 1; }
		else if (k+i-2<max_fname) {
		  	c1 = c3 = &(act_fnames[ act_fsort[k+i-2] * FNAMESIZE]);
			c2 = &(act_infos[  act_fsort[k+i-2] * INFOSIZE]);
			isdir = act_dirtag[act_fsort[k+i-2]];
		}
		else { c1 = c2 = c3 = ""; isdir = 0; }

		XSetForeground(root_display,
			XDefaultGC(root_display, root_screen),
			XBlackPixel(root_display, root_screen));
		if (k+i==old_selection) {
			XDrawLine(root_display,(Drawable)scroll_show_window,
                		XDefaultGC(root_display, root_screen),
                		14,yp-16,SCROLLW_W-2,yp-16);
			XDrawLine(root_display,(Drawable)scroll_show_window,
                		XDefaultGC(root_display, root_screen),
                		14,yp+2 ,SCROLLW_W-2,yp+2);
			XDrawLine(root_display,(Drawable)scroll_show_window,
                		XDefaultGC(root_display, root_screen),
                		14,yp-16 ,14,yp+2);
			XDrawLine(root_display,(Drawable)scroll_show_window,
                		XDefaultGC(root_display, root_screen),
                		SCROLLW_W-1,yp-16,SCROLLW_W-2,yp-16);
		}
		if (k+i==act_selection) {
			XFillRectangle(root_display, 
				(Drawable)scroll_show_window,
				XDefaultGC(root_display, root_screen),
				0,yp-16, SCROLLW_W, 19);
			XSetForeground(root_display,
				XDefaultGC(root_display, root_screen),
				XWhitePixel(root_display, root_screen));

			if (isdir) {
				if (k+i==1) {
					c1 = act_path;
					while (*c1++);
					while (c1>act_path) {
#ifdef VMS
						if (*c1==']') break;
#else
						if (*c1=='/') break;
#endif
						c1--;
					}
					*c1 = 0;
				}
				else {
#ifdef VMS
					strcat(act_path,"]");
#else
					strcat(act_path,"/");
#endif
					strcat(act_path,c3);
				}
				SPRINTF(act_fpath,"Enter path: %s_",act_path);
				vscrollbar[0].is = 0;
				rescan_fnames();
				old_selection = -1;
				act_selection = 0;
				draw_sizes();
				return;
			}

			SPRINTF(act_fisel,"Enter filename: %s_",c3);
			if (*c3) SPRINTF(act_fpath,"Enter path: %s_",act_path);

			XFillRectangle(root_display, 
				(Drawable)text_window,
				XDefaultGC(root_display, root_screen),
				0, 0, DIAL_W, 25);
			XFillRectangle(root_display, 
				(Drawable)path_window,
				XDefaultGC(root_display, root_screen),
				0, 0, DIAL_W, 25);
		}

		if (isdir || (i+k==0)) {
			XDrawLine(root_display,(Drawable)scroll_show_window,
                		XDefaultGC(root_display, root_screen),
                		2,yp-10,10,yp-10);
			XDrawLine(root_display,(Drawable)scroll_show_window,
                		XDefaultGC(root_display, root_screen),
                		2,yp,2,yp-10);
			XDrawLine(root_display,(Drawable)scroll_show_window,
                		XDefaultGC(root_display, root_screen),
                		10,yp,10,yp-10);
			XDrawLine(root_display,(Drawable)scroll_show_window,
                		XDefaultGC(root_display, root_screen),
                		2,yp,10,yp);
		}

		XDrawString(root_display,
			(Drawable)scroll_show_window,
			XDefaultGC(root_display, root_screen),
			17,yp,c1,strlen(c1));
		XDrawString(root_display,
			(Drawable)scroll_show_window,
			XDefaultGC(root_display, root_screen),
			330,yp,c2,strlen(c2));
		yp += 18;
	}
	draw_textwin();
}


#ifdef ANSI_C
static void draw_textwin(void)
#else
static void draw_textwin()
#endif
{
	int i;

	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XWhitePixel(root_display, root_screen));
	i=0;
	while ((act_fisel[i]) && (i<253)) i++;
	if (act_fisel[i-1]=='_') i--;
	act_fisel[i]=0;
	XFillRectangle(root_display, 
		(Drawable)text_window,
		XDefaultGC(root_display, root_screen),
		5+XTextWidth(dialog_font,act_fisel,strlen(act_fisel)),
		0, DIAL_W, 25);
	act_fisel[i]='_';
	act_fisel[i+1]=0;

	i=0;
	while ((act_fpath[i]) && (i<MAXPATHLEN-3)) i++;
	if (act_fpath[i-1]=='_') i--;
	act_fpath[i]=0;
	XFillRectangle(root_display, 
		(Drawable)path_window,
		XDefaultGC(root_display, root_screen),
		5+XTextWidth(dialog_font,act_fpath,strlen(act_fpath)),
		0, DIAL_W, 25);
	act_fpath[i]='_';
	act_fpath[i+1]=0;

	XSetForeground(root_display,
		XDefaultGC(root_display, root_screen),
		XBlackPixel(root_display, root_screen));
	XDrawString(root_display,
		(Drawable)text_window,
		XDefaultGC(root_display, root_screen),
		5,18,act_fisel,strlen(act_fisel));
	XDrawString(root_display,
		(Drawable)path_window,
		XDefaultGC(root_display, root_screen),
		5,18,act_fpath,strlen(act_fpath));
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
    	int nbytes, i, j;
    	char str[256+1];
	char lk, uk;

    	nbytes = XLookupString (e, str, 256, &ks, NULL);
    	if (nbytes < 0) nbytes = 0;
    	if (nbytes > 256) nbytes = 256;
    	str[nbytes] = '\0';

	if (ks==0xff54) { /* Down */
		old_selection = -1;
		if (vscrollbar[0].is<max_fname-1) vscrollbar[0].is++;
		set_fisel_scrollbar();
		draw_sizes();
		return;
	}
	else if (ks==0xff53) { /* Right */
		old_selection = -1;
		if (vscrollbar[0].is<max_fname-1) vscrollbar[0].is++;
		set_fisel_scrollbar();
		draw_sizes();
		return;
	}
	else if (ks==0xff52) { /* Up */
		old_selection = -1;
		if (vscrollbar[0].is>0) vscrollbar[0].is--;
		set_fisel_scrollbar();
		draw_sizes();
		return;
	}
	else if (ks==0xff51) { /* Left */
		old_selection = -1;
		if (vscrollbar[0].is>0) vscrollbar[0].is--;
		set_fisel_scrollbar();
		draw_sizes();
		return;
	}

	if (nbytes==1) {

		if (e->window == path_window) {
			old_selection = -1;
			act_selection = 0;
			i = 0;
			while ((act_fpath[i]) && (i<MAXPATHLEN-3)) i++;
			if (act_fpath[i-1]=='_') i--;
			act_fpath[i]=0;
			XSetForeground(root_display,
				XDefaultGC(root_display, root_screen),
				XWhitePixel(root_display, root_screen));
			XFillRectangle(root_display, 
				(Drawable)path_window,
				XDefaultGC(root_display, root_screen),
				5+XTextWidth(dialog_font,act_fpath,strlen(act_fpath)),
				0, DIAL_W, 25);
			if ((ks==0xff08)||(ks==0xffff)) { 
				i--; 
				if (i<12) i=12; 
				act_fpath[i]=0;
			}
			else if ((ks==0xff0a)||(ks==0xff0d)) { 
				dialog_notready = 0;
				dialog_success  = 1;
			}
			else if (str[0]==27) {
				dialog_notready = 0;
				dialog_success  = 0;
			}
			else { 	/* assert((i<=MAXPATHLEN-3)); */
				act_fpath[i]  = str[0];
				act_fpath[i+1]= 0;
			}
			act_fpath[MAXPATHLEN-1] = 0;
			draw_textwin();
			return;
		}
		else if (e->window == text_window) {
			old_selection = -1;
			act_selection = 0;
			i = 0;
			while ((act_fisel[i]) && (i<253)) i++;
			if (act_fisel[i-1]=='_') i--;
			act_fisel[i]=0;
			XSetForeground(root_display,
				XDefaultGC(root_display, root_screen),
				XWhitePixel(root_display, root_screen));
			XFillRectangle(root_display, 
				(Drawable)text_window,
				XDefaultGC(root_display, root_screen),
				5+XTextWidth(dialog_font,act_fisel,strlen(act_fisel)),
				0, DIAL_W, 25);
			if ((ks==0xff08)||(ks==0xffff)) { 
				i--; 
				if (i<16) i=16; 
				act_fisel[i]=0;
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
				act_fisel[i]  = str[0];
				act_fisel[i+1]= 0;
			}
			act_fisel[255] = 0;
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
                                break;
                        }
                }

                if (i<MAX_RADIO_POINTS) {
                        for (j=0; j<MAX_RADIO_POINTS; j++) {
                                if ((i!=j) && (radio_point[i].glob==radio_point[j].glob))
                                        radio_point[j].is = radio_point[j].sel-1
;
                        }
			draw_dialog_box();
			rescan_fnames();
			draw_dialog_box();
			old_selection = -1;
			return;
                }

		switch (str[0]) {
		case '_' :
		case '-' :
		case 'p' :
		case 'P' :
			if (vscrollbar[0].is>0) vscrollbar[0].is--;
			set_fisel_scrollbar();
			old_selection = -1;
			draw_sizes();
			return;
		case '*' :
		case '+' :
		case 'n' :
		case 'N' :
			if (vscrollbar[0].is<max_fname-1) vscrollbar[0].is++;
			set_fisel_scrollbar();
			old_selection = -1;
			draw_sizes();
			return;
		case 'r' :
		case 'R' :
			vscrollbar[0].is = 0;
			rescan_fnames();
			act_selection = 0;
			draw_sizes();
			old_selection = -1;
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
	int i,j;

	w = e->window;

	act_scroll_window = w;	

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
		draw_dialog_point(radio_point[i].w,1);
		rescan_fnames();
		draw_sizes();
		old_selection = -1;
	}

	for (i=0; i<MAX_RADIO_POINTS; i++)
		if (radio_point[i].is == radio_point[i].sel)
			draw_dialog_point(radio_point[i].w,1);
		else    draw_dialog_point(radio_point[i].w,0);


	for (i=0; i<MAX_VSCROLLBARS; i++) {
		if (act_scroll_window==vscrollbar[i].ws) {
		 	(*(vscrollbar[i].rf))(e->y);
			draw_sizes();
			old_selection = -1;
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
	else if (w==resc_button) {
		vscrollbar[0].is = 0;
		rescan_fnames();
		act_selection = 0;
		draw_sizes();
		old_selection = -1;
	}
	else if (w==next_button) {
		if (vscrollbar[0].is<max_fname-1) vscrollbar[0].is++;
		set_fisel_scrollbar();
		draw_sizes();
		old_selection = -1;
	}
	else if (w==prev_button) {
		if (vscrollbar[0].is>0) vscrollbar[0].is--;
		set_fisel_scrollbar();
		draw_sizes();
		old_selection = -1;
	}
	else if (w==scroll_show_window) {
		if (old_selection == vscrollbar[0].is + (e->y)/18)
			act_selection = vscrollbar[0].is + (e->y)/18;
		old_selection = vscrollbar[0].is + (e->y)/18;
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

	if (  (w==okay_button)||(w==cancel_button)||(w==resc_button)
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

	if (  (w==okay_button)||(w==cancel_button)||(w==resc_button)
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
	old_selection = -1;
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

	old_selection = -1;
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
	old_selection = -1;
}


/*--------------------------------------------------------------------*/
/*  Scrollbar handling 						      */
/*--------------------------------------------------------------------*/


#ifdef ANSI_C
static void read_fisel_scrollbar(int val)
#else
static void read_fisel_scrollbar(val)
int val;
#endif
{
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= vscrollbar[0].len) 
		val = vscrollbar[0].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,vscrollbar[0].wt,0,val,6,SCROLLBAR_LEN);
	vscrollbar[0].is = (2+max_fname)*val/(vscrollbar[0].len-SCROLLBAR_LEN);
}


#ifdef ANSI_C
static void set_fisel_scrollbar(void)
#else
static void set_fisel_scrollbar()
#endif
{
	int val;

	val =  (vscrollbar[0].is)*(vscrollbar[0].len-SCROLLBAR_LEN)/
		(2+max_fname);
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= vscrollbar[0].len) 
		val = vscrollbar[0].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display, vscrollbar[0].wt,0,val,6,SCROLLBAR_LEN);
}


/*--------------------------------------------------------------------*/
/*  Directory handling 						      */
/*--------------------------------------------------------------------*/

/* Calculate the number of entries of a directory
 * ----------------------------------------------
 */

#ifdef ANSI_C
static int calc_dir_entries(void)
#else
static int calc_dir_entries()
#endif
{
#ifdef VMS
static 	char dirp[MAXPATHLEN];
static 	char specif[255];
	long context=0;
	$DESCRIPTOR(lib_spec,specif);
	$DESCRIPTOR(lib_result,dirp);
#else
	DIR *dirp;
	struct dirent *dp;
#endif
	int result;
	char *c;
	struct stat file_stat;

	result = 0;
#ifdef VMS
	if (act_path[0]) SPRINTF(specif,"%s*.*;*",act_path);
	else SPRINTF(specif,"[]*.*;*");
#else
	if (act_path[0]) dirp = opendir(act_path);
	else dirp = opendir(".");
	if (!dirp) return(0);
#endif

#ifdef VMS
	while (lib$find_file(&lib_spec,&lib_result,&context) != RMS$_NMF) {
		if (!stat(dirp,&file_stat)) {
			if( ((file_stat.st_mode)&S_IFMT) == S_IFDIR ) {
				result++;
				continue;
			}
		}
		c = dirp;
		while (*c) c++;
		while ((c>(dirp)) && (*c!=';')) c--;
		*c='\0';
		while ((c>(dirp)) && (*c!='.')) c--;
#else
	while ((dp = readdir(dirp))!=NULL) {
		if (dp->d_name[0]!='.') {
			SPRINTF(act_fpath,"%s/%s",act_path,dp->d_name);
			if (!stat(act_fpath,&file_stat)) {
				if (S_ISDIR(file_stat.st_mode)) {
					result++;
					continue;
				}
			}
			c = dp->d_name;
			while (*c) c++;
			while ((c>(dp->d_name)) && (*c!='.')) c--;
#endif
			switch (presel_mode) {
			case 0: result++; 
				break;
			case 1: if (strcmp(c,".vcg")==0) result++;
			        if (strcmp(c,".VCG")==0) result++;
				break;
			case 2: if (strcmp(c,".ps")==0) result++;
			        if (strcmp(c,".PS")==0) result++;
				break;
			case 3: if (strcmp(c,".pbm")==0) result++;
			        if (strcmp(c,".PBM")==0) result++;
				break;
			case 4: if (strcmp(c,".ppm")==0) result++;
			        if (strcmp(c,".PPM")==0) result++;
				break;
			}
#ifndef VMS
		}
#endif
	}
#ifdef VMS
	lib$find_file_end(&context);
#else
	(void)closedir(dirp);
#endif
	return(result);
}


/* Allocate filename array and info field array
 * --------------------------------------------
 */

#ifdef ANSI_C
static void alloc_fnames(void)
#else
static void alloc_fnames()
#endif
{
	int newsize,i;

	newsize = calc_dir_entries();
	max_fname = newsize;
	newsize = newsize + 2;

	if (newsize>act_fbuf_size) {
		if (act_fnames) free(act_fnames);
		if (act_infos ) free(act_infos );
		if (act_fsort ) free(act_fsort );
		if (act_dirtag) free(act_dirtag);
		act_fbuf_size = newsize;
		act_fnames = (char *)malloc(FNAMESIZE*newsize);
		act_infos  = (char *)malloc(INFOSIZE *newsize);
		act_fsort  = (int *)malloc(sizeof(int)*newsize);
		act_dirtag = (char*)malloc(sizeof(char)*newsize);
		if (!act_fnames) Fatal_error("memory exhausted","");
		if (!act_infos ) Fatal_error("memory exhausted","");
		if (!act_fsort ) Fatal_error("memory exhausted","");
		if (!act_dirtag) Fatal_error("memory exhausted","");
	}

	for (i=0; i<newsize; i++) {
		act_fnames[i*FNAMESIZE]=0;
		act_infos[i*INFOSIZE]  =0;
		act_fsort[i]  = i;
		act_dirtag[i] = 0;
	}
}


/* Fill the filename array and info field array
 * --------------------------------------------
 */

#ifdef ANSI_C
static void rescan_fnames(void)
#else
static void rescan_fnames()
#endif
{
#ifdef VMS
static 	char dirp[MAXPATHLEN];
static 	char specif[255];
	long context = 0;
	$DESCRIPTOR(lib_spec,specif);
	$DESCRIPTOR(lib_result,dirp);
	char d_name[MAXPATHLEN];
#else
	DIR *dirp;
	struct dirent *dp;
#endif
	int i,j,month,is_okay;
	struct stat   file_stat;
	struct group  *gid_stat = 0;
	struct passwd *uid_stat = 0;
	char *c = 0;

	XDefineCursor(root_display,dialog_window,busyCursor); 
	XSync(root_display, 0);
        XFlush(root_display);

	i = 0;
	while ((act_fpath[i]) && (i<MAXPATHLEN-3)) i++;
	if (act_fpath[i-1]=='_') i--;
#ifndef VMS
	if (act_fpath[i-1]=='/') i--;
#endif
	act_fpath[i]=0;
	SPRINTF(act_path,"%s",&(act_fpath[12]));

	/* Initialize presel_mode, sel_mode and sort_mode */
	for (i=0; i<MAX_RADIO_POINTS; i++)
		if (radio_point[i].is == radio_point[i].sel)
			*(radio_point[i].glob) = radio_point[i].is;

	/* Allocate memory to contain the directory */
	alloc_fnames();

#ifdef VMS
	if (act_path[0]) SPRINTF(specif,"%s*.*;*",act_path);
	else SPRINTF(specif,"[]*.*;*");
#else
	if (act_path[0]) dirp = opendir(act_path);
	else dirp = opendir(".");
	if (!dirp) { 
		XDefineCursor(root_display,dialog_window,pointCursor);
		return; 
	}
#endif

	i = 0;
#ifdef VMS
	while (lib$find_file(&lib_spec,&lib_result,&context) != RMS$_NMF) {
		if (!stat(dirp,&file_stat)) {
			is_okay = 0;
			if( ((file_stat.st_mode)&S_IFMT)==S_IFDIR ) is_okay = 1;
			c = dirp;
			while ( (*c) && (*c!=']') ) c++;
			c++;
			strcpy(d_name,c);
			while (*c) c++;
			while ((c>(dirp)) && (*c!='.')) c--;
#else
	while ((dp = readdir(dirp))!=NULL) {
		if (dp->d_name[0]=='.') continue;
		SPRINTF(act_fpath,"%s/%s",act_path,dp->d_name);
		if (!stat(act_fpath,&file_stat)) {
			is_okay = 0;
			if (S_ISDIR(file_stat.st_mode)) is_okay = 1; 
			c = dp->d_name;
			while (*c) c++;
			while ((c>(dp->d_name)) && (*c!='.')) c--;
#endif
			switch (presel_mode) {
			case 0: is_okay = 1; break;
			case 1: if (strncmp(c,".vcg",4)==0) is_okay = 1; 
			        if (strncmp(c,".VCG",4)==0) is_okay = 1;
				break;
			case 2: if (strncmp(c,".ps",4)==0)  is_okay = 1;
			        if (strncmp(c,".PS",4)==0)  is_okay = 1;
				break;
			case 3: if (strncmp(c,".pbm",4)==0) is_okay = 1;
			        if (strncmp(c,".PBM",4)==0) is_okay = 1;
				break;
			case 4: if (strncmp(c,".ppm",4)==0) is_okay = 1;
			        if (strncmp(c,".PPM",4)==0) is_okay = 1;
				break;
			}
			if (!is_okay) continue;
			for (j=0; j<FNAMESIZE; j++) {
#ifdef VMS
				act_fnames[i*FNAMESIZE+j] = d_name[j];
				if (d_name[j]==0) break;
#else
				act_fnames[i*FNAMESIZE+j] = dp->d_name[j];
				if (dp->d_name[j]==0) break;
#endif
			}

#ifdef VMS
			if (((file_stat.st_mode)&S_IFMT)==S_IFDIR) 
				act_dirtag[i] = 1;
#else
			if (S_ISDIR(file_stat.st_mode)) act_dirtag[i] = 1;
#endif
			switch (sel_mode) {
			case 0: /* size  */
				SPRINTF(&(act_infos[i*INFOSIZE]),"%12d",file_stat.st_size);


				break;
			case 1: /* mode  */
#ifdef VMS
				if( ((file_stat.st_mode)&S_IFMT)==S_IFDIR ) 
				     act_infos[i* INFOSIZE]='d';
				else act_infos[i* INFOSIZE]='-';
				if ((file_stat.st_mode)&S_IREAD) 
				     act_infos[i* INFOSIZE+1]='r';
				else act_infos[i* INFOSIZE+1]='-';
				if ((file_stat.st_mode)&S_IWRITE) 
			  	     act_infos[i* INFOSIZE+2]='w';
				else act_infos[i* INFOSIZE+2]='-';
				if ((file_stat.st_mode)&S_IEXEC) 
				     act_infos[i* INFOSIZE+3]='e';
				else act_infos[i* INFOSIZE+3]='-';
				act_infos[i* INFOSIZE+4]=0;
#else
				if (S_ISDIR(file_stat.st_mode)) act_infos[i* INFOSIZE]='d';
				else act_infos[i* INFOSIZE]='-';
				if ((file_stat.st_mode)&S_IRUSR) act_infos[i* INFOSIZE+1]='r';
				else act_infos[i* INFOSIZE+1]='-';
				if ((file_stat.st_mode)&S_IWUSR) act_infos[i* INFOSIZE+2]='w';
				else act_infos[i* INFOSIZE+2]='-';
				if ((file_stat.st_mode)&S_IXUSR) act_infos[i* INFOSIZE+3]='x';
				else act_infos[i* INFOSIZE+3]='-';
				if ((file_stat.st_mode)&S_IRGRP) act_infos[i* INFOSIZE+4]='r';
				else act_infos[i* INFOSIZE+4]='-';
				if ((file_stat.st_mode)&S_IWGRP) act_infos[i* INFOSIZE+5]='w';
				else act_infos[i* INFOSIZE+5]='-';
				if ((file_stat.st_mode)&S_IXGRP) act_infos[i* INFOSIZE+6]='x';
				else act_infos[i* INFOSIZE+6]='-';
				if ((file_stat.st_mode)&S_IROTH) act_infos[i* INFOSIZE+7]='r';
				else act_infos[i* INFOSIZE+7]='-';
				if ((file_stat.st_mode)&S_IWOTH) act_infos[i* INFOSIZE+8]='w';
				else act_infos[i* INFOSIZE+8]='-';
				if ((file_stat.st_mode)&S_IXOTH) act_infos[i* INFOSIZE+9]='x';
				else act_infos[i* INFOSIZE+9]='-';
				act_infos[i* INFOSIZE+10] = 0;
#endif
				break;
			case 2: /* date  */
				SPRINTF(act_fpath,"%s",
#ifdef VMS
					ctime(&(file_stat.st_ctime)));
#else
					asctime(gmtime(&(file_stat.st_ctime))));
#endif
				act_fpath[7]=0;
				act_fpath[10]=0;
				act_fpath[16]=0;
				act_fpath[24]=0;
				if (act_fpath[8]==' ') act_fpath[8]='0';
				month = 0;
				if (strcmp(&(act_fpath[4]),"Jan")==0) month=1;
				if (strcmp(&(act_fpath[4]),"Feb")==0) month=2;
				if (strcmp(&(act_fpath[4]),"Mar")==0) month=3;
				if (strcmp(&(act_fpath[4]),"Apr")==0) month=4;
				if (strcmp(&(act_fpath[4]),"May")==0) month=5;
				if (strcmp(&(act_fpath[4]),"Jun")==0) month=6;
				if (strcmp(&(act_fpath[4]),"Jul")==0) month=7;
				if (strcmp(&(act_fpath[4]),"Aug")==0) month=8;
				if (strcmp(&(act_fpath[4]),"Sep")==0) month=9;
				if (strcmp(&(act_fpath[4]),"Oct")==0) month=10;
				if (strcmp(&(act_fpath[4]),"Nov")==0) month=11;
				if (strcmp(&(act_fpath[4]),"Dec")==0) month=12;
				SPRINTF(&(act_infos[i*INFOSIZE]),
					"%s/%2.2d/%s %s",
					&(act_fpath[22]),
					month,
					&(act_fpath[8]),
					&(act_fpath[11]));
				break;
			case 3: /* owner */
#ifndef VMS
				uid_stat = getpwuid(file_stat.st_uid);
				if (uid_stat) 
					SPRINTF(&(act_infos[i*INFOSIZE]),
						"%s",uid_stat->pw_name);
				else 	
#endif
					SPRINTF(&(act_infos[i*INFOSIZE]),
						"%12d",file_stat.st_uid);
				break;
			case 4: /* group */
#ifndef VMS
				gid_stat = getgrgid(file_stat.st_gid);

				if (gid_stat)
					SPRINTF(&(act_infos[i*INFOSIZE]),
						"%s",gid_stat->gr_name);
				else    
#endif
					SPRINTF(&(act_infos[i*INFOSIZE]),
						"%12d",file_stat.st_gid);
				break;
			}
			i++;
			act_fnames[i*FNAMESIZE-1] = 0;
			act_infos[i*INFOSIZE-1]  = 0;
			if (i>max_fname) break;
		}
	}
#ifdef VMS
	lib$find_file_end(&context);
#else
	(void)closedir(dirp);
#endif

	/* Sort the entries in act_fsort */
	switch (sort_mode) {
	case 0: break;
	case 1:
#ifdef ANSI_C
        	qsort(act_fsort,max_fname,sizeof(int),
                	(int (*) (const void *, const void *))compare_fnames);
#else
        	qsort(act_fsort,max_fname,sizeof(int), compare_fnames);
#endif
		break;
	case 2:
#ifdef ANSI_C
        	qsort(act_fsort,max_fname,sizeof(int),
                	(int (*) (const void *, const void *))compare_finfos);
#else
        	qsort(act_fsort,max_fname,sizeof(int), compare_finfos);
#endif
		break;
	}
	set_fisel_scrollbar();
	SPRINTF(act_fpath,"Enter path: %s_",act_path);
	XDefineCursor(root_display,dialog_window,pointCursor); 
	XSync(root_display, 0);
        XFlush(root_display);
}


/*  Compare function for sorting according filenames 
 *  -------------------------------------------------
 */

#ifdef ANSI_C
static int      compare_fnames(const int *a,const int *b)
#else
static int      compare_fnames(a,b)
int   *a;
int   *b;
#endif
{
	return(strcmp(	&(act_fnames[*a*FNAMESIZE]),
			&(act_fnames[*b*FNAMESIZE])));
}


/*  Compare function for sorting according fileinfos 
 *  ------------------------------------------------
 */

#ifdef ANSI_C
static int      compare_finfos(const int *a,const int *b)
#else
static int      compare_finfos(a,b)
int   *a;
int   *b;
#endif
{
	return(strcmp(	&(act_infos[*a*INFOSIZE]),
			&(act_infos[*b*INFOSIZE])));
}



/*--------------------------------------------------------------------*/

#endif /* X11 */

