/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */
/*		--------------------------------------		      */
/*								      */
/*   file:	   X11dev.c					      */
/*   version:	   1.00.00					      */
/*   creation:	   9.4.93					      */
/*   author:	   I. Lemke  (...-Version 0.99.99)		      */
/*		   G. Sander (Version 1.00.00-...)		      */
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */
/*   description:  Device driver for X11    			      */
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/

#ifndef lint
static char *id_string="$Id: X11dev.c,v 3.21 1995/02/08 18:34:15 sander Exp $";
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
 * $Log: X11dev.c,v $
 * Revision 3.21  1995/02/08  18:34:15  sander
 * Same as before.
 *
 * Revision 3.20  1995/02/08  15:47:22  sander
 * Small bug with K&R C solved.
 *
 * Revision 3.19  1995/02/08  13:12:22  sander
 * Register variables changed to normal variables for portability reasons.
 *
 * Revision 3.18  1995/02/08  11:11:14  sander
 * Distribution version 1.3.
 *
 * Revision 3.17  1994/12/23  18:12:45  sander
 * Manhatten layout added.
 * Option interface cleared.
 * infobox behaviour improved.
 * First version of fisheye (carthesian).
 * Options Noedge and nonode.
 *
 * Revision 3.16  1994/11/25  15:43:29  sander
 * Printer interface added to allow to use VCG as a converter.
 *
 * Revision 3.15  1994/11/23  14:50:47  sander
 * Drawing speed improved by removing some superfluous XSyncs.
 * Better rubber band method.
 * Bug in draw_right_ruler solved.
 * Scrollbar-Behaviour improved. Small touch points for the scrollbars
 * added.
 * Touch point for "Fit to screen" added.
 *
 * Revision 3.14  1994/08/09  10:44:03  sander
 * Spline drawing visibility check added.
 *
 * Revision 3.13  1994/08/08  16:01:47  sander
 * rubberband for pick position operation added.
 * Order of follow edge operation changed: The first edge
 * of a reached node is now the edge we come from.
 *
 * Revision 3.12  1994/08/05  14:27:31  sander
 * Negative values of G_width, etc. corrected.
 *
 * Revision 3.11  1994/08/02  15:36:12  sander
 * Minor change. Some debugmessages added.
 *
 * Revision 3.10  1994/06/07  14:09:59  sander
 * Splines implemented.
 * HP-UX, Linux, AIX, Sun-Os, IRIX compatibility tested.
 * The tool is now ready to be distributed.
 *
 * Revision 3.9  1994/05/16  08:56:03  sander
 * shape attribute (boxes, rhombs, ellipses, triangles) added.
 *
 * Revision 3.8  1994/05/05  12:03:00  sander
 * Follow edge action speedup by a special drawing routine.
 *
 * Revision 3.7  1994/05/05  08:20:30  sander
 * The following dialog boxes added: Center title, Graph layout,
 * Edge Class selection.
 *
 * Revision 3.6  1994/04/27  16:05:19  sander
 * PostScript driver added. New print-dialog box with rubberband.
 *
 * Revision 3.5  1994/04/19  15:17:33  sander
 * Scrollbars for X11 added.
 *
 * Revision 3.4  1994/03/04  19:11:24  sander
 * Specification of levels per node added.
 * X11 geometry behaviour (option -geometry) changed such
 * that the window is now opened automatically.
 *
 * Revision 3.3  1994/03/03  14:12:21  sander
 * Shift the unconnected parts together after the layout.
 *
 * Revision 3.2  1994/03/02  11:48:54  sander
 * Layoutalgoritms mindepthslow, maxdepthslow, minindegree, ... mandegree
 * added.
 * Anchors and nearedges are not anymore allowed to be intermixed.
 * Escapes in strings are now allowed.
 *
 * Revision 3.1  1994/03/01  10:59:55  sander
 * Copyright and Gnu Licence message added.
 * Problem with "nearedges: no" and "selfloops" solved.
 *
 * Revision 1.6  1994/02/14  11:03:24  sander
 * Menu point `Node Information -> Statistics' added.
 * It is now possible to get a statistics of the visibility
 * of nodes and edges.
 *
 * Revision 1.5  1994/02/11  08:19:01  sander
 * The problem with animations in X11 is solved:
 * The window opens and closes now automatically.
 *
 * Revision 1.4  1994/02/10  15:55:00  sander
 * With X11, the output of '/' does not work.
 * Solved.
 *
 * Revision 1.3  1994/01/21  19:33:46  sander
 * VCG Version tested on Silicon Graphics IRIX, IBM R6000 AIX and Sun 3/60.
 * Option handling improved. Option -grabinputfocus installed.
 * X11 Font selection scheme implemented. The user can now select a font
 * during installation.
 * Sun K&R C (a nonansi compiler) tested. Some portabitility problems solved.
 *
 */

/************************************************************************
 * Device driver for X11    
 * ---------------------
 * This module contains basically the interaction main loop, that displays 
 * the graph, reacts on interactions, handles menues, restart actions.
 *
 * This file provides the following functions:
 * ------------------------------------------
 *    display_part()          interaction main loop  
 *    setScreenSpecifics()    initializes the device and ask for device
 *			      specifics 
 *    gs_line(x1,y1,x2,y2,c)  draws a line of color c
 *                            from (x1,y1) to (x2,y2)
 *    gs_rectangle(x,y,w,h,c) draws a filled rectangle of
 *                            color c at (x,y) with size w and h
 *    gs_exit(x)	      exit the program, i.e. clean up and abort
 *    gs_open()	      	      open the device window
 *    gs_close()      	      open the device window
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
#include "steps.h"
#include "drawlib.h"
#include "infobox.h"
#include "draw.h"
#include "folding.h"
#include "grprint.h"
#include "usrsignal.h"
#include "fisheye.h"
#include "X11devpb.h"
#include "X11devla.h"
#include "X11devcl.h"
#include "X11devti.h"
#include "X11devfe.h"
#include "X11devfs.h"
#include "X11devvw.h"


/*--------------------------------------------------------------------*/

#undef  EVENT_DEBUG
#define GNUCOPYRIGHT

/* Types
 * -----
 */

/* Menu Items */

typedef struct gs_MenuItem_str {
	Drawable mi_dw;
	Window	 mi_win;
	char 	 mi_selected;
	char 	 mi_selectable;
	char    *mi_txt;
	struct	 gs_Menu_str *mi_submenu;
} *gs_MenuItem;

/* Menu */

typedef struct gs_Menu_str {
	Drawable     m_dw;
	Window	     m_win;
	GC           m_GC;
	XGCValues    m_GCvalues;
	int	     m_width;
	int	     m_height;
	int	     m_len;
	int          m_x;
	int	     m_y;
	char	     m_visible;
	gs_MenuItem  m_item[1];
} *gs_Menu;


#define MENUITEM_DW(x)	((x)->mi_dw)
#define MENUITEM_WIN(x)	((x)->mi_win)
#define MENUITEM_SEL(x)	((x)->mi_selected)
#define MENUITEM_EXP(x)	((x)->mi_selectable)
#define MENUITEM_TXT(x)	((x)->mi_txt)
#define MENUITEM_SUB(x)	((x)->mi_submenu)
#define MENUITEM_HEIGHT 20

#define MENU_DW(x)      ((x)->m_dw)
#define MENU_WIN(x)     ((x)->m_win)
#define MENU_GC(x)      ((x)->m_GC)
#define MENU_GCVAL(x)   ((x)->m_GCvalues)
#define MENU_WIDTH(x)	((x)->m_width)
#define MENU_HEIGHT(x)	((x)->m_height)
#define MENU_LEN(x)	((x)->m_len)
#define MENU_X(x)	((x)->m_x)
#define MENU_Y(x)	((x)->m_y)
#define MENU_VIS(x)	((x)->m_visible)
#define MENU_ITEM(x,i)  ((x)->m_item[(i)-1])



/* Prototypes
 * ----------
 */

#ifdef FAST_X11_DRAWING
void X11_fast_line _PP((int x1,int y1,int x2,int y3,int t,int c));
void X11_fast_dashedline 
		_PP((int x1,int y1,int x2,int y3,int t,int c,int dashlen));
void X11_fast_dottedline 
		_PP((int x1,int y1,int x2,int y3,int t,int c,int dashlen));
void X11_fast_ellipse       _PP((int x,int y,int w,int h,int t,int c));
void X11_fast_filledellipse _PP((int x,int y,int w,int h,int c1, int c2));
#endif


extern void print_all_ps _PP((char *fb, int x1, int y1, int x2, int y2));

#ifdef VMS
extern int  XGetWindowAttributes(Display* d, Window w, XWindowAttributes* a);
#endif

void setScreenSpecifics	_PP((void));
void gs_wait_message	_PP((int c));
void InitDevice		_PP((void));
void display_part	_PP((void));
void gs_exit		_PP((int x));
void gs_line		_PP((int fx,int fy,int tx,int ty,int c));
void gs_rectangle	_PP((long x,long y,int w,int h,int c));
void gs_open		_PP((void));
void gs_close		_PP((void));
int which_button	_PP((XEvent *eventp));

#undef DRAWDEBUG
#ifdef DRAWDEBUG
void debug_display_part _PP((void));
#endif

static void	ExitDevice		_PP((void));
static void 	setColormap		_PP((void));
static void 	mapColorIndex		_PP((int i,int r,int g,int b));

static void 	ask_window_size		_PP((Window w));

static void	allocateFrame		_PP((void));
static void	allocateMyPixwin	_PP((void));
static void	allocateMyPanel		_PP((void));
static void	allocateScrollbars	_PP((void));
static void     allocateOneScrollbar
   _PP((Window *bar,Window *tmb,Window *dir1,Window *dir2,unsigned long mask,XSetWindowAttributes *attr,int x,int  y,int  w,int  h));
static void     MoveResizeScrollbar
   _PP((Window bar,Window dir1,Window dir2,int x,int  y,int  w,int  h));


static void set_sizehints _PP((XSizeHints *hp,int mw,int mh,int dw,int dh,int dx,int dy,char *geom));
static int  parse_backing_store	_PP((char *s));

static void	displayCanvas		_PP((void));
static void	buildCanvas		_PP((void));
void 	show_buffer		_PP((void));

#ifdef EVENT_DEBUG
static void prologue	_PP((XEvent *eventp, char *event_name));
#else
#define prologue(a,b)   
#endif

static void 	make_complete_graph_visible _PP((void));

static void 	set_normal_cursor	_PP((void));
static void	set_busy_cursor		_PP((void));
static void 	set_select_cursor	_PP((void));
static void 	set_fold_cursor		_PP((void));
static void 	set_text_cursor		_PP((void));
static void 	set_leftscroll_cursor	_PP((void));
static void 	set_lowerscroll_cursor	_PP((void));
static void 	set_leftpos_cursor	_PP((void));
static void 	set_lowerpos_cursor	_PP((void));
static void 	set_left_cursor		_PP((void));
static void 	set_right_cursor	_PP((void));
static void 	set_up_cursor		_PP((void));
static void 	set_down_cursor		_PP((void));
static void 	reset_cursor		_PP((void));

static void 	clear_panel		_PP((void));
static void 	clear_from_xy_panel	_PP((int x,int y));
static void 	panel_outp		_PP((char *x,char *y,char *z));
static void 	fast_panel_outp		_PP((char *x));
static void 	panel_event		_PP((char *x));

static char 	*read_text		_PP((char *msg,int ypos,int mode));

/* Menu handling */

static gs_Menu	allocate_Menu		_PP((int len, char *itemtab[]));

static gs_Menu 	alloc_Menu _PP((int width,int height,int itemw,int itemh,int len,char *itemtab[]));
static gs_MenuItem alloc_MenuItem _PP((int width,int height,int itemw,int itemh,Window win,int pos,char *entry));
static void install_SubMenu	_PP((gs_Menu r, int i, gs_Menu s, Window *t));

static void 	gs_Hide_MenuItem	_PP((gs_Menu m, int i));
static void 	gs_Expose_MenuItem	_PP((gs_Menu m, int i));
static void 	gs_NewText_MenuItem	_PP((gs_Menu m, int i, char *s));
static void 	gs_check_allmenues	_PP((void));
static void 	gs_draw_menu		_PP((gs_Menu m, int x, int y));
static void 	gs_draw_menuitem	_PP((gs_Menu m, int i));
static void 	gs_draw_submenu		_PP((gs_Menu rootm,int i));
static void 	gs_hide_menu		_PP((gs_Menu m));
static void	gs_hide_all_menus	_PP((void));
static int 	gs_check_menureturn	_PP((gs_Menu m));
static int 	gs_check_menuselect	_PP((Window w,gs_Menu m));
static void 	gs_unselect_allmenus	_PP((void));
static void 	gs_unselect_menu	_PP((gs_Menu m));
static void 	gs_redraw_menu		_PP((gs_Menu m));
static int 	gs_check_vis_changed	_PP((gs_Menu m));
static void 	gs_handle_menu_selection _PP((void));

/* Event handling */

static void 	window_main_loop	_PP((void));
static void 	do_KeyPress		_PP((XEvent *eventp));
static void 	do_minimalKeyPress	_PP((XEvent *eventp));
static void 	do_ButtonPress 		_PP((XEvent *eventp));
static void 	do_ButtonRelease 	_PP((XEvent *eventp));
static void     do_EnterNotify 		_PP((XEvent *eventp));
static void 	do_LeaveNotify 		_PP((XEvent *eventp));
static void 	do_Expose		_PP((XEvent *eventp));
void 		do_gblExpose		_PP((XEvent *eventp));
void 		do_gblConfigureNotify	_PP((XEvent *eventp));
static void 	do_MotionNotify		_PP((XEvent *eventp));

/* Auxiliaries */

static void	resizeWindow		_PP((void));
static void 	position_abs_scrollbars	_PP((void));
static void 	position_nor_scrollbars	_PP((void));
static void     read_leftscrollbar	_PP((int val));
static void     read_lowerscrollbar	_PP((int val));
static void     read_leftabsscrollbar	_PP((int val));
static void     read_lowerabsscrollbar	_PP((int val));
static void     read_rightscrollbar	_PP((int val));
static char 	*int_to_str		_PP((int n));
char 	*class_num 		_PP((int n));
static char 	*act_info_num		_PP((int n));
static void 	xtextout		_PP((int y,char *msg));
static void 	xinttextout		_PP((int y,char *msg,int i));

/* Ruler management */

static void	ruler_paint				_PP((void));
static void	set_upper_ruler				_PP((void));
static void	set_lower_ruler				_PP((void));
static void	set_left_ruler				_PP((void));
static void	set_right_ruler				_PP((void));
static void	set_h_scale				_PP((int w, int h));
static void	set_v_scale				_PP((int w, int h));
static void	set_value				_PP((int x, int y, char *s));


/* Interactions */

static void 	dispatch_interaction	_PP((gs_Menu m,int item));
static void 	handle_frame_menu	_PP((int item));
static void 	handle_fold_menu	_PP((int item));
static void 	handle_scroll_menu	_PP((int item));
static void 	handle_info_menu	_PP((int item));
static void 	handle_scale_menu	_PP((int item));
static void 	handle_export_menu	_PP((int item));

static void 	default_handler		_PP((XEvent *event));
static int  	esc_handler		_PP((XEvent *event));
static int  	gkey_handler		_PP((XEvent *event, char * z));

static void	m_fold_subgraph		_PP((void));
static void	m_unfold_subgraph	_PP((void));
static void	m_fold_region		_PP((void));
static void	m_fold_p2_region	_PP((void));
static void	m_unfold_region		_PP((void));
static void	m_position		_PP((void));
static void	m_pic_position		_PP((void));
void		m_center_node		_PP((GNODE v,int invis));
static int  	m_wait_until_button	_PP((int e));
static void	m_follow_edge		_PP((void));
static void	m_follow_p2_edge	_PP((void));
static void 	m_fetch_region		_PP((int mode));
static void 	draw_rubberband		_PP((int a,int b,int c,int d));
static void	m_loadsave		_PP((void));
void		m_reload		_PP((void));

static int 	is_readeable		_PP((char *fname));
static int 	is_writable		_PP((char *fname));

static void 	followedge_msg		_PP((char *a, char *b, char *c));
static void 	next_follow_edge	_PP((void));
static GNODE 	search_target_node	_PP((GNODE v,GEDGE e));

/* Auxiliaries for interactions */

static void	reset_menues		_PP((void));
static void 	finish_selection	_PP((void));
static void 	handle_selected_node	_PP((GNODE v));
static void	complete_relayout	_PP((void));	

/* Font buffering */

void 		alloc_all_fontbuffers 
	_PP((Display *rd, int rs, Drawable dw, GC gc, unsigned long *ca));
void 		new_scale_fontbuffers 	_PP((int stretch, int shrink));

/* Follow edge feature */

void do_act_follow_edge   _PP((void));
void set_act_follow_node  _PP((GNODE v, int mov));
void set_next_follow_edge _PP((void));


/* Variables
 * ---------
 */

static char las_buf[60];

/* Root displays */

static Display *root_display;	/* Root display          */
static int      root_screen;	/* and its screen number */
static Colormap colormap;	/* and its color map     */
static unsigned long carray[CMAPSIZE]; /* and our update */

/* Windows */

static int win_exposed;

static Window	frame_window;
static Window	pix_window;
static Window	panel_window;
static Pixmap   pix_buffer;

static Window	maxscalepoint;

static Window	leftscrollbar;
static Window	leftscrolltmb;
static Window	leftscrollup;
static Window	leftscrolldown;
static Window	lowerscrollbar;
static Window	lowerscrolltmb;
static Window	lowerscrollleft;
static Window	lowerscrollright;
static Window	rightscrollbar;
static Window	rightscrolltmb;
static Window	rightscrollup;
static Window	rightscrolldown;

static Window	leftabsscrollbar;
static Window	leftabsscrolltmb;
static Window	leftabsscrollup;
static Window	leftabsscrolldown;
static Window	lowerabsscrollbar;
static Window	lowerabsscrolltmb;
static Window	lowerabsscrollleft;
static Window	lowerabsscrollright;

static Window	foldregion_touch;
static Window	scroll_touch;
static Window	info_touch;
static Window	scale_touch;
static Window	export_touch;

/* Offsets, the inner pix_window has relatively to the frame_window */

/* #define PIXW_XOFFSET  24 */
#define PIXW_XOFFSET  34 
#define PIXW_YOFFSET  82

#define SCROLLBAR_LEN 20
 
/* Drawable and graphic contexts */

static  Drawable        pix_dw = 0;
static  GC              pix_GC;
static  XGCValues       pix_GCvalues;
static  Drawable        panel_dw = 0;
static  GC              panel_GC;
static  XGCValues       panel_GCvalues;
static  Pixmap 		vcg_icon;

/* Menu's */

static  gs_Menu 	frame_menu;

#define FRAME_MENULEN 17 
static char *frame_menutab[] = {
	"Fold Subgraph       ",
	"Unfold Subgraph     ",
	"Expose/Hide Edges...",
	"Fold Region         ",
	"Unfold Region       ",
	"Scroll              ",
	"Node Information    ",
	"Position            ",
	"Pick Position       ",
	"Center Node...      ",
	"Follow Edge         ",
	"Ruler on            ",
	"Layout...           ",
	"View...             ",
	"Scale               ",	
	"File                ",
    	"Quit                "	
};

static 	gs_Menu		foldregion_menu;

static char **class_menutab;


static  gs_Menu 	scroll_menu;

#define SCROLL_MENULEN 13 
static char *scroll_menutab[] = {
	"left",		
	"right",	
	"up",		
	"down",		
	"lleft",	
	"rright",	
	"uup",		
	"ddown",	
	"llleft",	
	"rrright",	
	"uuup",		
	"dddown",	
	"origin"	
};


static  gs_Menu		info_menu;

#define INFO_MENULEN  9
static char *info_menutab[INFO_MENULEN];

static 	gs_Menu		scale_menu;

#define SCALE_MENULEN 10
static char *scale_menutab[] = {
	"normal",
	"400 %",
	"200 %",
	"150 %",
	"90 %",
	"80 %",
	"70 %",
	"60 %",
	"50 %",
	"25 %"
};

static 	gs_Menu		export_menu;

#define EXPORT_MENULEN 5
static char *export_menutab[] = {
	"Load...        ",
	"Reload         ",
	"Save to file...",
	"Export part... ",
	"Export graph...",
};



/*----------------*/

/* the mouse buttons */

#define G_MOUSE_LEFT  1
#define G_MOUSE_RIGHT 3


/* the panel font */

char Xfontname[512] = VCG_DEFAULT_FONT;

static  XFontStruct *panel_font = NULL;

/* the cursors */

static Cursor standard_cursor;     /* Remembered old cursor        */
static Cursor workingCursor;	   /* If the tool is busy          */
static Cursor selectCursor;	   /* If a node should be selected */ 
static Cursor foldCursor;	   /* If a node should be folded   */ 
static Cursor textCursor;	   /* If text input is required    */ 
static Cursor leftscrollCursor;    /* Scroll cursor <->            */
static Cursor lowerscrollCursor;   /* Scroll cursor <->            */
static Cursor leftposCursor;       /* Scroll cursor  ->            */
static Cursor lowerposCursor;      /* Scroll cursor  ->            */

static Cursor rightCursor;         /* Scroll cursor  ->            */
static Cursor leftCursor;          /* Scroll cursor  <-            */
static Cursor upCursor;            /* Scroll cursor  up            */
static Cursor downCursor;          /* Scroll cursor  down          */
static int    act_cursor;

#define STD_CURSOR 1
#define WOR_CURSOR 2
#define SEL_CURSOR 3
#define FOL_CURSOR 4
#define TXT_CURSOR 5

/* Flag, whether the device is already initialized */

static int device_there = 0;

/* this flag indicates whether the panel is already available
 * for output.
 */

static int panel_there = 0;

/* this counter is used to generate a message that the user 
 * should wait.
 */

static int waitcnt=0;

/* Flag for the animation handler */

int anim_flag = 0;

/* Flag indicates whether the ruler should be drawn.
 */

static int V_ruler = 0;

/* Flag, indicating that a node was selected 
 */

static int selected_flag = 0;

/* Flag to select which info is needed about a node */

static int info_val;
static int truesize;

/* State during the follow_edge command
 */

static GEDGE   act_follow_edge = NULL;
static GNODE   act_follow_node = NULL;
static GNODE   act_revert_node = NULL;
static GEDGE   last_follow_edge = (GEDGE)-1;
static int follow_state;

/* Flag, indicating what to do with file operations: 
 * load or save in different formats
 */

static int load_save_flag;

#define LS_LOAD      0
#define LS_SAVEASCII 1
#define LS_SAVEPPM   2
#define LS_SAVEPS    3


/*--------------------------------------------------------------------*/
/*  Pixmaps                                                           */
/*--------------------------------------------------------------------*/

/* the VCG icon */

static unsigned char icon_image[] = { 
/* Format_version=1, Width=64, Height=64, Depth=1, Valid_bits_per_item=16
 */
 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
 0xff,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x03,0x08,0x00,0x00,0x00,0x00,
 0x00,0xc0,0x03,0x08,0x00,0x00,0x00,0x00,0x01,0xc0,0x03,0x08,0x00,0x00,0x00,
 0x00,0x01,0xc0,0x03,0x08,0x00,0x00,0x00,0x00,0x01,0xc0,0x03,0x08,0x00,0x00,
 0x00,0x00,0x01,0xc0,0x03,0x08,0x00,0x00,0x00,0x00,0x01,0xc0,0x03,0x08,0x00,
 0x00,0x00,0x00,0x01,0xc0,0x03,0x08,0x00,0x00,0x00,0x00,0x01,0xc0,0xfb,0xff,
 0x0f,0x00,0x00,0xff,0xff,0xc1,0x0b,0x00,0x08,0x00,0x00,0x01,0x00,0xc1,0x0b,
 0x00,0x08,0x00,0x00,0x01,0x00,0xc1,0x0b,0x00,0x08,0x00,0x00,0x01,0x00,0xc1,
 0x0b,0x21,0x08,0x00,0x00,0x41,0x04,0xc1,0x0b,0x10,0x08,0x00,0x00,0x01,0x02,
 0xc1,0x0b,0x55,0x08,0x00,0x00,0x31,0x12,0xc1,0x0b,0x00,0x08,0x00,0x00,0x01,
 0x01,0xc1,0x0b,0x00,0x08,0x00,0x00,0x01,0x00,0xc1,0x0b,0x00,0x08,0x00,0x00,
 0x01,0x00,0xc1,0xfb,0xff,0x0f,0x00,0x00,0x01,0x00,0xc1,0x03,0xe0,0x00,0x00,
 0x00,0xff,0xff,0xc1,0x03,0x00,0x07,0x00,0x00,0xf0,0x00,0xc0,0x03,0x00,0x78,
 0x00,0x00,0x0e,0x00,0xc0,0x03,0x00,0x80,0x03,0xc0,0x01,0x00,0xc0,0x03,0x00,
 0x00,0x1c,0x3c,0x00,0x00,0xc0,0x03,0x00,0x00,0x60,0x06,0x00,0x00,0xc0,0x03,
 0x00,0x40,0x55,0x55,0x05,0x00,0xc0,0x03,0x00,0x20,0x00,0x00,0x08,0x00,0xc0,
 0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x03,0x00,0x20,0x40,0x00,0x08,0x00,
 0xc0,0x03,0x00,0x00,0x08,0x04,0x00,0x00,0xc0,0x03,0x00,0x20,0x84,0x48,0x08,
 0x00,0xc0,0x03,0x00,0x00,0x20,0x28,0x00,0x00,0xc0,0x03,0x00,0x20,0x00,0x00,
 0x08,0x00,0xc0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x03,0x00,0x20,0x00,
 0x00,0x08,0x00,0xc0,0x03,0x00,0x40,0x55,0x55,0x05,0x00,0xc0,0x03,0x00,0x00,
 0x60,0x00,0x00,0x00,0xc0,0x03,0x00,0x00,0x18,0x00,0x00,0x00,0xc0,0x03,0x00,
 0x00,0x00,0x00,0x00,0x00,0xc0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x03,
 0x00,0x00,0x07,0x07,0x3f,0xf0,0xc3,0x03,0x00,0x30,0x06,0x82,0x60,0x08,0xc6,
 0x03,0x00,0x08,0x0c,0x41,0x40,0x04,0xc4,0x03,0xf8,0xff,0x0c,0x41,0x00,0x04,
 0xc0,0x03,0x08,0x00,0x0c,0x61,0x00,0x06,0xc0,0x03,0x08,0x00,0x98,0x60,0x00,
 0x06,0xc0,0x03,0x08,0x08,0x98,0x60,0x00,0x06,0xc0,0x03,0x88,0x00,0x98,0x60,
 0x00,0x06,0xc0,0x03,0x08,0x12,0x30,0x60,0x00,0x86,0xcf,0x03,0x08,0x21,0x70,
 0x60,0x00,0x06,0xc6,0x03,0x08,0x00,0x70,0x40,0x00,0x04,0xc6,0x03,0x08,0x00,
 0x20,0xc0,0x40,0x0c,0xc6,0x03,0x08,0x00,0x20,0x80,0x21,0x18,0xc6,0x03,0xf8,
 0xff,0x20,0x00,0x1f,0xf0,0xc1,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x03,
 0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,
 0x03,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
 0xc0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
 0xff,0xff
};


/*--------------------------------------------------------------------*/
/*  Check the screen device                                           */
/*--------------------------------------------------------------------*/

/* We look into the frame buffer: how many colors are available?
 * What is the size of the framebuffer?
 * maxDepth, ScreenWidth, ScreenHeight are set according to this.
 * G_width and G_height are preinitialized with appropriate values.
 */

static int ScreenOpen = 0;

#ifdef ANSI_C
void setScreenSpecifics(void)
#else
void setScreenSpecifics()
#endif
{
	int i;
 
	if (ScreenOpen) return;
	ScreenOpen = 1;
	root_display = XOpenDisplay(Xmydiplayname);
	if (!root_display) {
		FPRINTF(stderr,"Unable to open display %s\n",
			XDisplayName(Xmydiplayname));
		gs_exit(1);
	}
	root_screen = XDefaultScreen (root_display);

#ifdef VMS
	RootWinMaxDepth = XDisplayPlanes(root_display,root_screen);
#else
	maxDepth        = XDisplayPlanes(root_display,root_screen);
#endif
	ScreenWidth	= XDisplayWidth(root_display,root_screen);
	G_width 	= ScreenWidth-100;
	ScreenHeight	= XDisplayHeight(root_display,root_screen); 
	G_height	= ScreenHeight-100;	
	colormap 	= XDefaultColormap(root_display,root_screen);
	carray[0] 	= XWhitePixel(root_display, root_screen);
	for (i = 1; i < cmap_size; i++)
        	carray[i] = XBlackPixel(root_display, root_screen);

}


/*--------------------------------------------------------------------*/
/*  Interaction main loop                                             */
/*--------------------------------------------------------------------*/

/* Initialize the device
 * =====================
 * allocate all frames, windows and menues, display the graph,
 * then go into the interaction main loop. 
 */

static int not_firstcall = 0;
static int no_buffer = 0;

#ifdef ANSI_C
void	display_part(void)
#else
void	display_part()
#endif
{
	debugmessage("display_part","");

	/* semaphore: we come only once to here */
	if (not_firstcall) return;
	not_firstcall = 1;
	no_buffer = 1;

	/* first: initialize the device */

	debugmessage("before InitDevice","");
	InitDevice();
	debugmessage("after InitDevice","");

	position_abs_scrollbars();
	/* displayCanvas(); */
	reset_menues(); 
	enable_signal();
	touch_specification();

	/* Copyright message */

	XSetForeground(root_display, pix_GC, carray[WHITE]);
	XFillRectangle(root_display,
                pix_dw,
                pix_GC,
		0, 
		0, 
		G_xmax, G_ymax);

	gs_setshrink(1,1);
	gs_setto(10,10);
	gs_printstr("\f02\fbUSAAR Visualization Tool ",31);
	gs_setto(210,10);
	gs_printstr(version_str,31);
	gs_setto(10,26);
	gs_printstr("\f01\fi169 1993-1995 by G.Sander, I.Lemke & the Compare Consortium",31);
	gs_setto(10,42);
	gs_printstr(&(revision_str[1]),31);
	gs_setto(18+8*strlen(&(revision_str[1])),42);
	gs_printstr(date_str,31);
	gs_setto(10,58);
	gs_printstr("No warranty ! See the file COPYING for licence conditions.",31);

	no_buffer = 0;
	show_buffer();

	/* Now we set the input focus to us and
 	 * go into the interaction main loop 
	 */

	init_fe(0,300,0,300,200,200);
	resizeWindow();
	no_buffer = 0;
	show_buffer();
	if (grabinputfocus)
		XSetInputFocus(root_display,frame_window,
				RevertToParent,CurrentTime);

	window_main_loop();
}


/* This is only used for debugging. See step2.c
 * --------------------------------------------
 */

#ifdef DRAWDEBUG
#ifdef ANSI_C
void	debug_display_part(void)
#else
void	debug_display_part()
#endif
{
	displayCanvas();
	enable_signal();
	touch_specification();
	/* window_main_loop(); */
}
#endif

/* Initialize the device 
 * ---------------------
 */

#ifdef ANSI_C
void 	InitDevice(void)
#else
void 	InitDevice()
#endif
{
	int i;

	/* first: initialize the device */

	debugmessage("InitDevice","");
	if (device_there) {
		if (class_menutab) free(class_menutab);
		class_menutab = (char **)malloc(max_nr_classes*sizeof(char *));
		if (!class_menutab) Fatal_error("memory exhausted","");
		for (i=1; i<=max_nr_classes; i++) 
			class_menutab[i-1] = class_num(i);
		for (i=1; i<=6; i++) 
			info_menutab[i-1] = act_info_num(i);
		return;
	}
	device_there = 1;
	win_exposed = 0;

	allocateFrame();
	alloc_all_fontbuffers(root_display,root_screen,pix_dw,pix_GC,carray);

	setColormap();

	debugmessage("before x11_init_dialog InitDevice","");
	x11_init_dialog(root_display, root_screen);
	debugmessage("before x11_init_layout InitDevice","");
	x11_init_layout_dialog(root_display, root_screen);
	debugmessage("before x11_init_classes InitDevice","");
	x11_init_classes_dialog(root_display, root_screen);
	debugmessage("before x11_init_title InitDevice","");
	x11_init_title_dialog(root_display, root_screen);
	debugmessage("before x11_init_fedge InitDevice","");
	x11_init_fedge_dialog(root_display, root_screen, 
			frame_window, pix_window);
	debugmessage("before x11_init_fisel InitDevice","");
	x11_init_fisel_dialog(root_display, root_screen);
	debugmessage("before x11_init_view InitDevice","");
	x11_init_view_dialog(root_display, root_screen);

	debugmessage("before set_busy_cursor InitDevice","");
	set_busy_cursor();
	debugmessage("end of InitDevice","");
}

/* Exit the device
 * ---------------
 * It is enough to deallocate the root frame, because all its 
 * childs are deallocated automatically.
 */

#ifdef ANSI_C
static void	ExitDevice(void)
#else
static void	ExitDevice()
#endif
{
	if (!device_there) return; 
	XDestroyWindow(root_display,frame_window);
	x11_destroy_dialog(root_display, root_screen);
	x11_destroy_layout_dialog(root_display, root_screen);
	x11_destroy_classes_dialog(root_display, root_screen);
	x11_destroy_title_dialog(root_display, root_screen);
	x11_destroy_fedge_dialog(root_display, root_screen);
	x11_destroy_fisel_dialog(root_display, root_screen);
	x11_destroy_view_dialog(root_display, root_screen);
    	XCloseDisplay (root_display);
}


/* Exit all
 * --------
 */

#ifdef ANSI_C
void	gs_exit(int x)
#else
void	gs_exit(x)
int x;
#endif
{
	int i, success;

	if ((x==0) && (multiple_files==1)) {
		success = scanOptions(gblargc, gblargv); 
		if ((!success)||(!Dataname[0])) {
			if (device_there) ExitDevice();
			if (!silent) PRINTF("\n"); 
			exit(x);
		}
		for (i=0; i<800; i++) { if (Dataname[i]!=' ') break; }
        	strncpy(filename,&(Dataname[i]),  800-i);
        	filename[ 800] = 0;

		success = is_readeable(Dataname);
	
		if (success) {
			clear_hide_class();
			parse_part();
			visualize_part();
			init_fe(0,300,0,300,200,200);
			resizeWindow(); 
		}
		else { 	panel_outp("File ", filename,
			   	   " is notreadable."); 
		}

		return;
	}
	if (device_there) ExitDevice();
	if (!silent) PRINTF("\n"); 
	exit(x);
}


/* Set the colormap
 * ----------------
 */

static int col_msg_shown;   /* flag indicates whether a color msg was there */ 

#ifdef ANSI_C
static void setColormap(void)
#else
static void setColormap()
#endif
{
	int i;

	if (!colored)      return;
	if (!cmap_changed) return;
	cmap_changed = 0;
	col_msg_shown = 0; 

	for (i = 0; i < cmap_size; i++)
        	mapColorIndex(i,(int)redmap[i],
			    	(int)greenmap[i],
			    	(int)bluemap[i]);
}


/* Change index i in the color map to the appropriate r, g, b value.
 * ----------------------------------------------------------------
 * Try to get closed as possible to the wanted color.
 */

#ifdef ANSI_C
static void mapColorIndex(int i,int r,int g,int b)
#else
static void mapColorIndex(i, r, g, b)
int     i;
int     r, g, b;
#endif
{
        int     stat;
        XColor  tmp;

        if (i >= cmap_size) return;

        tmp.red   = (unsigned short)(r / 255.0 * 65535);
        tmp.green = (unsigned short)(g / 255.0 * 65535);
        tmp.blue  = (unsigned short)(b / 255.0 * 65535);
        tmp.flags = 0;
        tmp.pixel = (unsigned long)i;
 
        if ((stat = XAllocColor(root_display, colormap, &tmp)) == 0) {
		if (!col_msg_shown) {
			col_msg_shown = 1;
                	FPRINTF(stderr, "WARNING: XAllocColor failed (status = %d)\n", stat);
			FPRINTF(stderr, "If you have a lot of color tools running, which use\n");
			FPRINTF(stderr, "a lot of DIFFERENT colors, it comes to this situation.\n");
			FPRINTF(stderr, "Usually, if you have a small frame buffer with a lookup\n");
			FPRINTF(stderr, "table with only 256 colors, and for instance you put a colored\n"); 
			FPRINTF(stderr, "picture as background image on your X11 desktop,\n"); 
			FPRINTF(stderr, "the color allocation fails. The VCG tool needs %d colors such\n",cmap_size);
			FPRINTF(stderr, "that all other programs on the desktop should only use %d\n", 256-cmap_size);
			FPRINTF(stderr, "colors, or they should use the same colors as the VCG tool.\n");
			FPRINTF(stderr, "As alternative, you can use the option -nocolors.\n");
			FPRINTF(stderr, "We try to proceed now, but the selected colors are probably\n");
			FPRINTF(stderr, "garbled and the result may be ugly.\n");

		}
        }
        carray[i] = tmp.pixel;
 
        XFlush(root_display);
}


/*--------------------------------------------------------------------*/
/*  Window management                                                 */
/*--------------------------------------------------------------------*/

/* Ask size of a window w
 * ======================
 * The return values are in window_width and window_height.
 */

static int window_width;
static int window_height;

#ifdef ANSI_C
static void ask_window_size(Window w)
#else
static void ask_window_size(w)
Window w;
#endif
{
	XWindowAttributes retWindowAttributes;

	debugmessage("ask_window_size","");
        if (!XGetWindowAttributes(root_display, w, &retWindowAttributes)) {
                FPRINTF(stderr,"Can't get window attributes.");
                gs_exit(1);
        }

        window_width  = retWindowAttributes.width;
        window_height = retWindowAttributes.height;
}
  
/*--------------------------------------------------------------------*/
/*  Window allocation funtions                                        */
/*--------------------------------------------------------------------*/

/* Allocate root frame
 * -------------------
 * The root frame contains all other display objects.
 */

static char x11_win_label[1024];

#ifdef ANSI_C
static void	allocateFrame(void)
#else
static void	allocateFrame()
#endif
{
	XSetWindowAttributes attr;
	XSizeHints hints;
	unsigned long mask = 0L;
	XAnyEvent event;
	int i;

	/* select for all events */
	attr.event_mask = KeyPressMask           | 
			  ButtonPressMask        | ButtonReleaseMask  |
			  EnterWindowMask        | 
                          ExposureMask           | StructureNotifyMask | 
                          SubstructureNotifyMask | 
                          FocusChangeMask        | OwnerGrabButtonMask;

	attr.background_pixel = XWhitePixel(root_display,root_screen);
	attr.border_pixel = XBlackPixel(root_display,root_screen);

        set_sizehints (&hints, 200, 200, G_width, G_height, 0, 0, 
			Xmygeometry);

	mask |= (CWBackPixel | CWBorderPixel | CWEventMask);

	if (Xmybackingstore) {
		attr.backing_store = parse_backing_store (Xmybackingstore);
		mask |= CWBackingStore;
	}

        frame_window = XCreateWindow (root_display, 
				      RootWindow(root_display, root_screen), 
				      hints.x, hints.y,
                           	      hints.width, hints.height, 
				      Xmyborderwidth, (int)CopyFromParent,
                                      InputOutput, 
				      (Visual *)CopyFromParent,
                           	      mask, &attr);

	/* Create icon */

	vcg_icon = XCreateBitmapFromData(
		root_display,
		frame_window,
		(char *)icon_image,
		64,64);

	/* Open Font */

	panel_font = XLoadQueryFont(root_display,Xfontname);
	if (!panel_font) 
		Fatal_error("Font not found. Please use option -font","");


	strcpy(x11_win_label, "VCG ");
	strcat(x11_win_label, Dataname);
	
        XSetStandardProperties(root_display,
                frame_window,
                x11_win_label,
                x11_win_label,
                vcg_icon,
                gblargv,
                gblargc,
                &hints
        );

	allocateMyPixwin();
	allocateMyPanel();
	allocateScrollbars();
	frame_menu  = allocate_Menu(FRAME_MENULEN,frame_menutab);

	if (class_menutab) free(class_menutab);
	class_menutab = (char **)malloc(max_nr_classes*sizeof(char *));
	if (!class_menutab) Fatal_error("memory exhausted","");
	for (i=1; i<=max_nr_classes; i++) 
		class_menutab[i-1] = class_num(i);
	foldregion_menu = allocate_Menu(max_nr_classes,class_menutab);
	scroll_menu = allocate_Menu(SCROLL_MENULEN,scroll_menutab);
	for (i=1; i<=6; i++) 
		info_menutab[i-1] = act_info_num(i);
	info_menutab[6] = "Layout Attributes";
	info_menutab[7] = "Label of Node";
	info_menutab[8] = "Statistics";
	info_menu   = allocate_Menu(INFO_MENULEN,  info_menutab);
	scale_menu  = allocate_Menu(SCALE_MENULEN, scale_menutab);
	export_menu = allocate_Menu(EXPORT_MENULEN,export_menutab);

	install_SubMenu(frame_menu,4, foldregion_menu,&foldregion_touch);
	install_SubMenu(frame_menu,6, scroll_menu,     &scroll_touch);
	install_SubMenu(frame_menu,7, info_menu,      &info_touch);
	install_SubMenu(frame_menu,15,scale_menu,     &scale_touch);
	install_SubMenu(frame_menu,16,export_menu,    &export_touch);

        XMapRaised(root_display, frame_window);
        XFlush(root_display);

        /*
         * Wait for Exposure event.
         */
/*
        do { XNextEvent(root_display, (XEvent *)&event);
        } while (  (event.type != Expose || event.window!=pix_window) 
                 &&(event.type != MapNotify || event.window!=pix_window));
 */
#ifndef ULTRIX
#ifndef AIX
        do { XNextEvent(root_display, (XEvent *)&event);
        } while (event.type != Expose || event.window!=pix_window);
#endif
#endif

 
	standard_cursor   = XCreateFontCursor(root_display,XC_left_ptr);
	selectCursor      = XCreateFontCursor(root_display,XC_hand1);
	foldCursor        = XCreateFontCursor(root_display,XC_crosshair);
	workingCursor     = XCreateFontCursor(root_display,XC_watch);
	textCursor        = XCreateFontCursor(root_display,XC_xterm);
	leftscrollCursor  = XCreateFontCursor(root_display,
						XC_sb_v_double_arrow);
	lowerscrollCursor = XCreateFontCursor(root_display,
						XC_sb_h_double_arrow);
	rightCursor       = XCreateFontCursor(root_display,
						XC_sb_right_arrow);
	leftCursor        = XCreateFontCursor(root_display,
						XC_sb_left_arrow);
	upCursor          = XCreateFontCursor(root_display,
						XC_sb_up_arrow);
	downCursor        = XCreateFontCursor(root_display,
						XC_sb_down_arrow);
	leftposCursor     = rightCursor;
	lowerposCursor    = upCursor;

	set_normal_cursor();
	reset_cursor();
}


/* Allocate PixWindow 
 * ------------------
 * The PixWindow is the real drawing area.
 */


#ifdef ANSI_C
static void	allocateMyPixwin(void)
#else
static void	allocateMyPixwin()
#endif
{
	XSetWindowAttributes attr;
	unsigned long mask = 0L;

	ask_window_size(frame_window);

	if ( G_xmax < window_width    )	G_xmax = window_width;
	if ( G_ymax < window_height-60)	G_ymax = window_height-60;

	/* select for all events */
	attr.event_mask = KeyPressMask           | ButtonMotionMask   |
			  ButtonPressMask        | ButtonReleaseMask  |
			  EnterWindowMask        | 
                          ExposureMask           | StructureNotifyMask | 
                          SubstructureNotifyMask | 
                          FocusChangeMask        | OwnerGrabButtonMask;

	attr.background_pixel = XWhitePixel(root_display,root_screen);
	attr.border_pixel = XBlackPixel(root_display,root_screen);

	mask |= (CWBackPixel | CWBorderPixel | CWEventMask);

        pix_window = XCreateWindow (root_display, 
				    frame_window, 
				    20,2,
                                    window_width- PIXW_XOFFSET, 
				    window_height-PIXW_YOFFSET,
				    2, (int)CopyFromParent,
                                    InputOutput, 
				    (Visual *)CopyFromParent,
                           	    mask, &attr);

/*        pix_window = XCreateSimpleWindow (root_display, frame_window, 20, 2,
 *                                   window_width- PIXW_XOFFSET, 
 *				    window_height-PIXW_YOFFSET,
 *                                    2,
 *				    XBlackPixel(root_display,root_screen),
 *				    XWhitePixel(root_display,root_screen));
 */

        XMapWindow (root_display, pix_window);

	pix_dw = (Drawable)pix_window;
	pix_GC = XDefaultGC(root_display, root_screen);
        pix_GCvalues.graphics_exposures = False;
        XChangeGC(root_display, pix_GC, GCGraphicsExposures, &pix_GCvalues);
	pix_dw = (Drawable)pix_window;

	/* We buffer this window */

#ifdef VMS
        pix_buffer = XCreatePixmap(root_display,
                        (Drawable)pix_window,
                        (unsigned int)G_xmax+1,
                        (unsigned int)G_ymax+1,
                        (unsigned int)RootWinMaxDepth);
#else
        pix_buffer = XCreatePixmap(root_display,
                        (Drawable)pix_window,
                        (unsigned int)G_xmax+1,
                        (unsigned int)G_ymax+1,
                        (unsigned int)maxDepth);
#endif


	pix_dw = (Drawable)pix_buffer;
	if (panel_font)
		XSetFont(root_display,pix_GC,panel_font->fid);
}


/* Allocate PanelWindow 
 * --------------------
 * The PanelWindow is used for text output.
 */


#ifdef ANSI_C
static void	allocateMyPanel(void)
#else
static void	allocateMyPanel()
#endif
{
	ask_window_size(frame_window);

        panel_window = XCreateSimpleWindow (root_display, frame_window, 2, 
				    window_height-60+4,
                                    window_width-6, 50,
                                    2,
				    XBlackPixel(root_display,root_screen),
				    XWhitePixel(root_display,root_screen));

        XMapWindow (root_display, panel_window);

	panel_dw = (Drawable)panel_window;
	panel_GC = XDefaultGC(root_display, root_screen);
        panel_GCvalues.graphics_exposures = False;
        XChangeGC(root_display, panel_GC, GCGraphicsExposures, &panel_GCvalues);
	panel_dw = (Drawable)panel_window;
	if (panel_font)
		XSetFont(root_display,panel_GC,panel_font->fid);

	panel_there = 1;
}


/* Allocate Scrollbars
 * -------------------
 */


static int act_x_pos, act_y_pos;

#ifdef ANSI_C
static void	allocateScrollbars(void)
#else
static void	allocateScrollbars()
#endif
{
	XSetWindowAttributes attr;
	unsigned long mask = 0L;

	ask_window_size(frame_window);

	act_x_pos = act_y_pos = 0;

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

        maxscalepoint = XCreateWindow (root_display, frame_window, 
				    window_width-11, 
				    window_height-PIXW_YOFFSET+4,
                                    8, 18,
                                    1, (int)CopyFromParent,
				    InputOutput,
				    (Visual *)CopyFromParent,
				    mask, &attr);

	allocateOneScrollbar(
		&leftscrollbar,
		&leftscrolltmb,
		&leftscrollup,
		&leftscrolldown,
		mask, &attr, 11, 2, 8, window_height-PIXW_YOFFSET);

	allocateOneScrollbar(
		&leftabsscrollbar,
		&leftabsscrolltmb,
		&leftabsscrollup,
		&leftabsscrolldown,
		mask, &attr, 2, 2, 8, window_height-PIXW_YOFFSET);

	allocateOneScrollbar(
		&rightscrollbar,
		&rightscrolltmb,
		&rightscrollup,
		&rightscrolldown,
		mask, &attr, window_width-11, 2, 8,window_height-PIXW_YOFFSET);

	allocateOneScrollbar(
		&lowerscrollbar,
		&lowerscrolltmb,
		&lowerscrollleft,
		&lowerscrollright,
		mask, &attr, 
		20, window_height-PIXW_YOFFSET+5, 
		window_width-PIXW_XOFFSET+1, 8);

	allocateOneScrollbar(
		&lowerabsscrollbar,
		&lowerabsscrolltmb,
		&lowerabsscrollleft,
		&lowerabsscrollright,
		mask, &attr, 
		20, window_height-PIXW_YOFFSET+14, 
		window_width-PIXW_XOFFSET+1, 8);

        XMapWindow (root_display, maxscalepoint);
 	position_abs_scrollbars();
}


/* Allocate one Scrollbar
 * ----------------------
 * A complete scrollbar consists of the scroll bar, the scoll thumb,
 * and two touching points of incremental scrolling in both directions.
 */

#ifdef ANSI_C
static void allocateOneScrollbar(
	Window *bar,
	Window *tmb,
	Window *dir1,
	Window *dir2,
	unsigned long mask,
	XSetWindowAttributes *attr,
	int x,
	int y,
	int w,
	int h)
#else
static void allocateOneScrollbar(bar,tmb,dir1,dir2,mask,attr, x, y, w, h)
	Window *bar;
	Window *tmb;
	Window *dir1;
	Window *dir2;
	unsigned long mask;
	XSetWindowAttributes *attr;
	int x;
	int y;
	int w;
	int h;
#endif
{
	int tmb_w, tmb_h;
	int bar_w, bar_h, bar_x, bar_y;
	int d1_w,  d1_h,  d1_x,  d1_y;
	int d2_w,  d2_h,  d2_x,  d2_y;

	if (w<h) {
		tmb_w = w-2;
		tmb_h = SCROLLBAR_LEN;
		bar_w = w;
		bar_h = h - 2 * w;
		bar_x = x;
		bar_y = y + w;
		d1_w = w;
		d1_h = w-1;
		d1_x = x;
		d1_y = y;
		d2_w = w;
		d2_h = w-1;
		d2_x = x;
		d2_y = y + h - w + 1;
	}
	else {
		tmb_w = SCROLLBAR_LEN;
		tmb_h = h-2;
		bar_w = w - 2 * h;
		bar_h = h;
		bar_x = x + h;
		bar_y = y;
		d1_w = h-1;
		d1_h = h;
		d1_x = x;
		d1_y = y;
		d2_w = h-1;
		d2_h = h;
		d2_x = x + w - h - 1;
		d2_y = y;
	}

        *bar = XCreateWindow (root_display, frame_window, bar_x, bar_y, 
                                    bar_w, bar_h,
                                    1, (int)CopyFromParent,
				    InputOutput,
				    (Visual *)CopyFromParent,
				    mask, attr);
        *tmb = XCreateSimpleWindow (root_display, *bar, 0,0, 
                                    tmb_w, tmb_h,
                                    1,
				    XWhitePixel(root_display,root_screen),
				    XBlackPixel(root_display,root_screen));
        *dir1 = XCreateWindow (root_display, frame_window, d1_x, d1_y, 
                                    d1_w, d1_h,
                                    1, (int)CopyFromParent,
				    InputOutput,
				    (Visual *)CopyFromParent,
				    mask, attr);
        *dir2 = XCreateWindow (root_display, frame_window, d2_x, d2_y,
				    d2_w, d2_h, 
                                    1, (int)CopyFromParent,
				    InputOutput,
				    (Visual *)CopyFromParent,
				    mask, attr);
        XMapWindow (root_display, *dir1);
        XMapWindow (root_display, *dir2);
        XMapWindow (root_display, *tmb);
        XMapWindow (root_display, *bar);
}



/* Move and Resize one Scrollbar
 * -----------------------------
 * A complete scrollbar consists of the scroll bar, the scoll thumb,
 * and two touching points of incremental scrolling in both directions.
 */

#ifdef ANSI_C
static void MoveResizeScrollbar(
	Window bar,
	Window dir1,
	Window dir2,
	int x,
	int y,
	int w,
	int h)
#else
static void MoveResizeScrollbar(bar,dir1,dir2, x, y, w, h)
	Window bar;
	Window dir1;
	Window dir2;
	int x;
	int y;
	int w;
	int h;
#endif
{
	int bar_w, bar_h, bar_x, bar_y;
	int d1_w,  d1_h,  d1_x,  d1_y;
	int d2_w,  d2_h,  d2_x,  d2_y;

	if (w<h) {
		bar_w = w;
		bar_h = h - 2 * w;
		bar_x = x;
		bar_y = y + w;
		d1_w = w;
		d1_h = w-1;
		d1_x = x;
		d1_y = y;
		d2_w = w;
		d2_h = w-1;
		d2_x = x;
		d2_y = y + h - w + 1;
	}
	else {
		bar_w = w - 2 * h;
		bar_h = h;
		bar_x = x + h;
		bar_y = y;
		d1_w = h-1;
		d1_h = h;
		d1_x = x;
		d1_y = y;
		d2_w = h-1;
		d2_h = h;
		d2_x = x + w - h + 1;
		d2_y = y;
	}

	XMoveResizeWindow(root_display,dir1, d1_x, d1_y, d1_w, d1_h );
	XMoveResizeWindow(root_display,dir2, d2_x, d2_y, d2_w, d2_h );
	XMoveResizeWindow(root_display,bar,  bar_x,bar_y,bar_w,bar_h);
}




/* Initialize hint structure
 * -------------------------
 * This algorithm is taken from xlib xbiff
 */

#define maximum(a,b) ((a) > (b) ? (a) : (b))

#ifdef ANSI_C
static void set_sizehints(
	XSizeHints *hintp,
	int min_width, 
	int min_height,
	int defwidth,
	int defheight,
	int defx,
	int defy,
	char *geom)
#else
static void set_sizehints (hintp, min_width, min_height, defwidth, defheight, defx, defy, geom)
XSizeHints *hintp;
int min_width, min_height, defwidth, defheight, defx, defy;
char *geom;
#endif
{
	int geom_result;

	hintp->width = hintp->min_width = min_width;
	hintp->height = hintp->min_height = min_height;
	hintp->flags = PMinSize;
	hintp->x = hintp->y = 0;
	geom_result = NoValue;
	if (geom != NULL) {
		geom_result = XParseGeometry (geom, &hintp->x, &hintp->y,
				      (unsigned int *)&hintp->width,
				      (unsigned int *)&hintp->height);
		if ((geom_result&WidthValue) && (geom_result&HeightValue)) {
			hintp->width =maximum(hintp->width, hintp->min_width);
			hintp->height=maximum(hintp->height,hintp->min_height);
			hintp->flags |= USSize;
		}
		if ((geom_result & XValue) && (geom_result & YValue)) {
			hintp->flags += USPosition;
		}
    	}
	if (!(hintp->flags & USSize)) {
		hintp->width = defwidth;
		hintp->height = defheight;
		hintp->flags |= PSize;
    	}

/*
 *   	if (!(hintp->flags & USPosition)) {
 *		hintp->x = defx;
 *		hintp->y = defy;
 *		hintp->flags |= PPosition;
 *   	}
 */

	if (geom_result & XNegative) {
		hintp->x = DisplayWidth (root_display, 
				DefaultScreen (root_display)) + 
				hintp->x - hintp->width;
    	}
    	if (geom_result & YNegative) {
		hintp->y = DisplayHeight (root_display, 
				DefaultScreen (root_display)) + 
				hintp->y - hintp->height;
    	}
}

/* Check which backing store algorithm needed.
 * -------------------------------------------
 */

#ifdef ANSI_C
static int parse_backing_store(char *s)
#else
static int parse_backing_store(s)
char *s;
#endif
{
    int len = strlen (s);
    char *cp;

    for (cp = s; *cp; cp++) {
        if (isascii (*cp) && isupper (*cp)) *cp = tolower (*cp);
    }

    if (strncmp (s, "notuseful", len) == 0) return(NotUseful);
    if (strncmp (s, "whenmapped", len) == 0) return(WhenMapped);
    if (strncmp (s, "always", len) == 0) return(Always);
    return(0);
}


/*--------------------------------------------------------------------*/
/*  Drawing primitives                                                */
/*--------------------------------------------------------------------*/

/* Draw a line
 * -----------
 * from fx,fy to tx,ty with color c.
 */

#ifdef ANSI_C
void	gs_line(int fx,int fy,int tx,int ty,int c)
#else
void	gs_line(fx, fy, tx, ty, c)
int	fx, fy, tx, ty, c;
#endif
{
	int x1, y1, x2, y2, x3, y3, hx, hy, d;

	XSetForeground(root_display, pix_GC, carray[c]);
	x1 = fx-V_xmin;
	y1 = fy-V_ymin;
	x2 = tx-V_xmin;
	y2 = ty-V_ymin;

	if (fisheye_view != 0) {
		fe_g_to_s(fx,fy,&x1,&y1);
		fe_g_to_s(tx,ty,&x2,&y2);
		d = 1;
		while ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) > 50*50) {
			hx = fx + d * (tx-fx)/7;
			hy = fy + d * (ty-fy)/7;
			fe_g_to_s(hx,hy,&x3,&y3);
			XDrawLine(root_display, pix_dw, pix_GC, x1, y1, x3, y3);
			x1 = x3;
			y1 = y3;
			d++;
		}
	}
	
	XDrawLine(root_display, pix_dw, pix_GC, x1, y1, x2, y2);
	/* XSync(root_display, 0); */
}

/* Draw a rectangle
 * ----------------
 * at (x,y) with width w, height h and color c
 */

#ifdef ANSI_C
void 	gs_rectangle(long x,long y,int w,int h,int c)
#else
void 	gs_rectangle(x, y, w, h, c)
long	x, y;
int 	w, h, c;
#endif
{
	int x1, y1, x2, y2, hx, hy, j, d;
	XPoint hp[29];

	XSetForeground(root_display, pix_GC, carray[c]);
	x1 = x - V_xmin;
	y1 = y - V_ymin;
	if (fisheye_view != 0) {
		switch (fisheye_view) {
        	case FPSCF_VIEW:
        	case PSCF_VIEW:
			j = 0;
			fe_g_to_s(x,y,&x1,&y1);
			fe_g_to_s(x,y+h,&x2,&y2);
			hp[j].x =  x1;
			hp[j++].y = y1;
			d = 1;
			while ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1) > 50*50) {
				hx = x;
				hy = y + d * h/7;
				fe_g_to_s(hx, hy, &x1, &y1);
				hp[j].x   = x1;
				hp[j++].y = y1;
				d++;
				if (j>7) break;
			}
			x1 = hp[j].x   = x2;
			y1 = hp[j++].y = y2;
			fe_g_to_s(x+w,y+h,&x2,&y2);
			d = 1;
			while ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1) > 50*50) {
				hx = x + d * w/7;
				hy = y + h;
				fe_g_to_s(hx, hy, &x1, &y1);
				hp[j].x   = x1;
				hp[j++].y = y1;
				d++;
				if (j>14) break;
			}
			x1 = hp[j].x   = x2;
			y1 = hp[j++].y = y2;
			fe_g_to_s(x+w,y,&x2,&y2);
			d = 1;
			while ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1) > 50*50) {
				hx = x + w;
				hy = y + h - d * h/7;
				fe_g_to_s(hx, hy, &x1, &y1);
				hp[j].x   = x1;
				hp[j++].y = y1;
				d++;
				if (j>21) break;
			}
			x1 = hp[j].x   = x2;
			y1 = hp[j++].y = y2;
			x2 = hp[0].x;
			y2 = hp[0].y;
			d = 1;
			while ((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1) > 50*50) {
				hx = x + w - d * w/7;
				hy = y;
				fe_g_to_s(hx, hy, &x1, &y1);
				hp[j].x   = x1;
				hp[j++].y = y1;
				d++;
				if (j>28) break;
			}
			if (j<=4)
			XFillPolygon(root_display, pix_dw, pix_GC, hp, j, 
					Convex, CoordModeOrigin);
			else XFillPolygon(root_display, pix_dw, pix_GC, hp, j, 
					Complex, CoordModeOrigin);
			return;
        	case FCSCF_VIEW:
        	case CSCF_VIEW:
			fe_g_to_s(x,y,&x1,&y1);
			fe_g_to_s(x+w,y+h,&x2,&y2);
			w = x2-x1;
			h = y2-y1;
			if ((w<=0) && (h<=0)) return;
			if (w<=0) w =1;
			if (h<=0) h =1;
			break;
		}
	}
	XFillRectangle(root_display, pix_dw, pix_GC, x1, y1, w, h);
	/* XSync(root_display, 0); */
}


/* Draw a fast line using X11 special features
 * -------------------------------------------
 * from fx,fy to tx,ty with color c and thickness t.
 */

#ifdef FAST_X11_DRAWING

#ifdef ANSI_C
void	X11_fast_line(int fx,int fy,int tx,int ty,int t,int c)
#else
void	X11_fast_line(fx, fy, tx, ty, t, c)
int	fx, fy, tx, ty, t, c;
#endif
{
	int x1, y1, x2, y2, x3, y3, hx, hy, d;

	XSetForeground(root_display, pix_GC, carray[c]);
	XSetLineAttributes(root_display, pix_GC, (t>0?t-1:0), 
		LineSolid, CapRound, JoinRound);
	x1 = fx-V_xmin;
	y1 = fy-V_ymin;
	x2 = tx-V_xmin;
	y2 = ty-V_ymin;

	if (fisheye_view != 0) {
		fe_g_to_s(fx,fy,&x1,&y1);
		fe_g_to_s(tx,ty,&x2,&y2);
		d = 1;
		while ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) > 50*50) {
			hx = fx + d * (tx-fx)/7;
			hy = fy + d * (ty-fy)/7;
			fe_g_to_s(hx,hy,&x3,&y3);
			XDrawLine(root_display, pix_dw, pix_GC, x1, y1, x3, y3);
			x1 = x3;
			y1 = y3;
			d++;
		}
	}
	
	XDrawLine(root_display, pix_dw, pix_GC, x1, y1, x2, y2);
	/* XSync(root_display, 0); */
	XSetLineAttributes(root_display, pix_GC, 0, 
		LineSolid, CapRound, JoinRound);
}

#endif


/* Draw a fast dashed line using X11 special features
 * --------------------------------------------------
 * from fx,fy to tx,ty with color c and thickness t.
 * The length of the dashes is d.
 */

#ifdef FAST_X11_DRAWING

#ifdef ANSI_C
void	X11_fast_dashedline(int fx,int fy,int tx,int ty,int t,int c,int d)
#else
void	X11_fast_dashedline(fx, fy, tx, ty, t, c, d)
int	fx, fy, tx, ty, t, c, d;
#endif
{
	char dash_list[2];
	int x1, y1, x2, y2, x3, y3, hx, hy, dd;

	if (d<1) d = 1;
	dash_list[0]=d;
	dash_list[1]=d;
	XSetForeground(root_display, pix_GC, carray[c]);
	XSetLineAttributes(root_display, pix_GC, (t>0?t-1:0), 
		LineOnOffDash, CapRound, JoinRound);
	XSetDashes(root_display, pix_GC, 0, dash_list, 2); 
	x1 = fx-V_xmin;
	y1 = fy-V_ymin;
	x2 = tx-V_xmin;
	y2 = ty-V_ymin;

	if (fisheye_view != 0) {
		fe_g_to_s(fx,fy,&x1,&y1);
		fe_g_to_s(tx,ty,&x2,&y2);
		dd = 1;
		while ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) > 50*50) {
			hx = fx + dd * (tx-fx)/7;
			hy = fy + dd * (ty-fy)/7;
			fe_g_to_s(hx,hy,&x3,&y3);
			XDrawLine(root_display, pix_dw, pix_GC, x1, y1, x3, y3);
			x1 = x3;
			y1 = y3;
			dd++;
		}
	}

	XDrawLine(root_display, pix_dw, pix_GC, x1, y1, x2, y2);
	/* XSync(root_display, 0); */
	XSetLineAttributes(root_display, pix_GC, 0, 
		LineSolid, CapRound, JoinRound);
}

#endif


/* Draw a fast dotted line using X11 special features
 * --------------------------------------------------
 * from fx,fy to tx,ty with color c and thickness t.
 * The length of the spaces between the dottes is d.
 */

#ifdef FAST_X11_DRAWING

#ifdef ANSI_C
void	X11_fast_dottedline(int fx,int fy,int tx,int ty,int t,int c,int d)
#else
void	X11_fast_dottedline(fx, fy, tx, ty, t, c, d)
int	fx, fy, tx, ty, t, c, d;
#endif
{
	char dash_list[2];
	int x1, y1, x2, y2, x3, y3, hx, hy, dd;

	if (d<1) d = 1;
	if (d<t) d = t;
	dash_list[0]=1;
	dash_list[1]=d;
	XSetForeground(root_display, pix_GC, carray[c]);
	XSetLineAttributes(root_display, pix_GC, (t>0?t-1:0), 
		LineOnOffDash, CapRound, JoinRound);
	XSetDashes(root_display, pix_GC, 0, dash_list, 2); 
	x1 = fx-V_xmin;
	y1 = fy-V_ymin;
	x2 = tx-V_xmin;
	y2 = ty-V_ymin;

	if (fisheye_view != 0) {
		fe_g_to_s(fx,fy,&x1,&y1);
		fe_g_to_s(tx,ty,&x2,&y2);
		dd = 1;
		while ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) > 50*50) {
			hx = fx + dd * (tx-fx)/7;
			hy = fy + dd * (ty-fy)/7;
			fe_g_to_s(hx,hy,&x3,&y3);
			XDrawLine(root_display, pix_dw, pix_GC, x1, y1, x3, y3);
			x1 = x3;
			y1 = y3;
			dd++;
		}
	}
	XDrawLine(root_display, pix_dw, pix_GC, x1, y1, x2, y2);
	/* XSync(root_display, 0); */
	XSetLineAttributes(root_display, pix_GC, 0, 
		LineSolid, CapRound, JoinRound);
}

#endif


/* Draw a fast ellipse as border using X11 special features
 * --------------------------------------------------------
 * (x,y) is the left upper point of the bounding box around the
 * ellipse, and w and h are the width and height, and c and t
 * the color and thickness. 
 */ 

#ifdef FAST_X11_DRAWING

#ifdef ANSI_C
void X11_fast_ellipse(int x,int y,int w,int h,int t,int c)
#else
void X11_fast_ellipse(x,y,w,h,t,c)
int	x, y, w, h, t, c;
#endif
{
	XSetLineAttributes(root_display, pix_GC, (t>0?t-1:0), 
		LineSolid, CapRound, JoinRound);
	XSetForeground(root_display, pix_GC, carray[c]);
	XDrawArc(root_display,
		pix_dw,
                pix_GC,
		x-V_xmin, y-V_ymin,
		w,h,
		0, 360*64);
	/* XSync(root_display, 0); */
	XSetLineAttributes(root_display, pix_GC, 0, 
		LineSolid, CapRound, JoinRound);
}

#endif

/* Draw a fast filled ellipse using X11 special features
 * -----------------------------------------------------
 * (x,y) is the left upper point of the bounding box around the 
 * ellipse, and w and h are the width and height, and c1 and c2 
 * the colors.
 */

#ifdef FAST_X11_DRAWING

#ifdef ANSI_C
void X11_fast_filledellipse(int x,int y,int w,int h,int c1,int c2)
#else
void X11_fast_filledellipse(x,y,w,h,c1,c2)
int     x, y, w, h, c1, c2;
#endif
{
	int x1, y1;
	XPoint hp[25];
	int i,j,k;

	if (fisheye_view != 0) {
		k = 0;
		fe_g_to_s(x+w/2, y+h, &x1,&y1);
		hp[k].x   = x1;
		hp[k++].y = y1;
		for (i=0; i<=(w+1)/2; ) {
			j = h*h/4 - i*h/w * i*h/w;
                	if (j>=0) j = gstoint(sqrt((double)j));
                	else j = 0;
			fe_g_to_s(x+w/2-i, y+h/2+j, &x1,&y1);
			hp[k].x   = x1;
			hp[k++].y = y1;
			if (k>12) break;
			if ((w+1)/20>0) i+= ((w+1)/20); 
			else i++;
		}
		for (i=(w+1)/2; i>=0; ) {
			j = h*h/4 - i*h/w * i*h/w;
                	if (j>=0) j = gstoint(sqrt((double)j));
                	else j = 0;
			fe_g_to_s(x+w/2-i, y+h/2-j, &x1,&y1);
			hp[k].x   = x1;
			hp[k++].y = y1;
			if (k>23) break;
			if ((w+1)/20>0) i-= ((w+1)/20); 
			else i--;
		}
		fe_g_to_s(x+w/2, y, &x1,&y1);
		hp[k].x   = x1;
		hp[k++].y = y1;
		XSetForeground(root_display, pix_GC, carray[c2]);
		XFillPolygon(root_display, pix_dw, pix_GC, hp, k, 
					Complex, CoordModeOrigin);

		k = 0;
		fe_g_to_s(x+w/2, y+h, &x1,&y1);
		hp[k].x   = x1;
		hp[k++].y = y1;
		for (i=0; i<=(w+1)/2; ) {
			j = h*h/4 - i*h/w * i*h/w;
                	if (j>=0) j = gstoint(sqrt((double)j));
                	else j = 0;
			fe_g_to_s(x+w/2+i, y+h/2+j, &x1,&y1);
			hp[k].x   = x1;
			hp[k++].y = y1;
			if (k>12) break;
			if ((w+1)/20>0) i+= ((w+1)/20); 
			else i++;
		}
		for (i=(w+1)/2; i>=0; ) {
			j = h*h/4 - i*h/w * i*h/w;
                	if (j>=0) j = gstoint(sqrt((double)j));
                	else j = 0;
			fe_g_to_s(x+w/2+i, y+h/2-j, &x1,&y1);
			hp[k].x   = x1;
			hp[k++].y = y1;
			if (k>23) break;
			if ((w+1)/20>0) i-= ((w+1)/20); 
			else i--;
		}
		fe_g_to_s(x+w/2, y, &x1,&y1);
		hp[k].x   = x1;
		hp[k++].y = y1;
		XSetForeground(root_display, pix_GC, carray[c1]);
		XFillPolygon(root_display, pix_dw, pix_GC, hp, k, 
					Complex, CoordModeOrigin);

		return;
	}
	XSetForeground(root_display, pix_GC, carray[c2]);
	XFillArc(root_display,
		pix_dw,
                pix_GC,
		x-V_xmin, y-V_ymin,
		w,h,
		180*64, 360*64);
	XSetForeground(root_display, pix_GC, carray[c1]);
	XFillArc(root_display,
		pix_dw,
                pix_GC,
		x-V_xmin, y-V_ymin,
		w,h,
		0, 180*64);
}

#endif


/* Draw a fast filled triangle using X11 special features
 * ------------------------------------------------------
 * (x1,y1) - (x2,y2) - (x3,y3) form the triangle.
 * c is the color.
 */

#ifdef FAST_X11_DRAWING

#ifdef ANSI_C
void X11_fast_triangle(int x1,int y1,int x2,int y2, int x3,int y3,int c)
#else
void X11_fast_triangle(x1,y1,x2,y2,x3,y3,c)
int     x1, y1, x2, y2, x3, y3, c;
#endif
{
	XPoint hp[22];
	int j, sx, sy, hx, hy, tx, ty, ttx, tty, d, d1, d2, d3;

	XSetForeground(root_display, pix_GC, carray[c]);
	hp[0].x = x1 - V_xmin;
	hp[0].y = y1 - V_ymin;
	hp[1].x = x2 - V_xmin;
	hp[1].y = y2 - V_ymin;
	hp[2].x = x3 - V_xmin;
	hp[2].y = y3 - V_ymin;
	if (fisheye_view != 0) {
		j = 0;
		fe_g_to_s(x1, y1, &sx,&sy);
		hp[j].x   = sx;
		hp[j++].y = sy;
		fe_g_to_s(x2, y2, &tx, &ty);
		fe_g_to_s(x3, y3, &ttx,&tty);
		d1 = sx-tx;
		if (d1<0) d1 = -d1;
		d2 = sx-ttx;
		if (d2<0) d2 = -d2;
		d3 = tx-ttx;
		if (d3<0) d3 = -d3;
		d = d1;
		if (d2>d) d = d2;
		if (d3>d) d = d3;
		d1 = sy-ty;
		if (d1<0) d1 = -d1;
		d2 = sy-tty;
		if (d2<0) d2 = -d2;
		d3 = ty-tty;
		if (d3<0) d3 = -d3;
		if (d2>d1) d1 = d2;
		if (d3>d1) d1 = d3;
		if (d==0) return; 
		if (d1==0) return; 
		if ((d<=1) && (d1<=1)) return; 
		d = 1;
		while ((tx-sx)*(tx-sx)+(ty-sy)*(ty-sy) > 50*50) {
			hx = x1 + d * (x2-x1)/7;
			hy = y1 + d * (y2-y1)/7;
			fe_g_to_s(hx, hy, &sx, &sy);
			hp[j].x   = sx;
			hp[j++].y = sy;
			d++;
			if (j>7) break;
		}
		sx = hp[j].x   = tx;
		sy = hp[j++].y = ty;
		tx = ttx;
		ty = tty;
		d = 1;
		while ((tx-sx)*(tx-sx)+(ty-sy)*(ty-sy) > 50*50) {
			hx = x2 + d * (x3-x2)/7;
			hy = y2 + d * (y3-y2)/7;
			fe_g_to_s(hx, hy, &sx, &sy);
			hp[j].x   = sx;
			hp[j++].y = sy;
			d++;
			if (j>14) break;
		}
		sx = hp[j].x   = tx;
		sy = hp[j++].y = ty;
		tx = hp[0].x;
		ty = hp[0].y;
		d = 1;
		while ((tx-sx)*(tx-sx)+(ty-sy)*(ty-sy) > 50*50) {
			hx = x3 + d * (x1-x3)/7;
			hy = y3 + d * (y1-y3)/7;
			fe_g_to_s(hx, hy, &sx, &sy);
			hp[j].x   = sx;
			hp[j++].y = sy;
			d++;
			if (j>21) break;
		}
		if (j<=3) XFillPolygon(root_display, pix_dw, pix_GC, hp, j, 
					Convex, CoordModeOrigin);
		else 	  XFillPolygon(root_display, pix_dw, pix_GC, hp, j, 
					Complex, CoordModeOrigin);
		return;
	}
	XFillPolygon(root_display, pix_dw, pix_GC, hp, 3, Convex, 
			CoordModeOrigin);
	/* XSync(root_display, 0); */
}

#endif


/*--------------------------------------------------------------------*/
/*  Canvas displaying                                                 */
/*--------------------------------------------------------------------*/

/* display the graph in the pixwin
 * -------------------------------
 */

#ifdef ANSI_C
static void	displayCanvas(void)
#else
static void	displayCanvas()
#endif
{
	buildCanvas();
	reset_menues(); 
}


/* build the pixwin
 * ----------------
 * This is used to refresh the pixwin after any change like scaling,
 * scrolling etc.
 */

#ifdef ANSI_C
static void	buildCanvas(void)
#else
static void	buildCanvas()
#endif
{
	int old_cursor;

	debugmessage("buildCanvas","");
	setColormap();
	old_cursor = act_cursor;
	set_busy_cursor(); 
	if (!colored) 
		XSetForeground(root_display, pix_GC, carray[WHITE]);
	else	XSetForeground(root_display, pix_GC, carray[G_color]);
	XFillRectangle(root_display,
                pix_dw,
                pix_GC,
		0, 
		0, 
		G_xmax, G_ymax);

	if (fisheye_view!=0) {
		V_xmin = V_ymin = 0;
		V_xmax = V_ymax = MAXINT;
	}
	draw_main();
	draw_infoboxes();
	waitcnt=0;

	clear_panel();
	show_buffer();
	act_cursor = old_cursor;
	reset_cursor();
}


#ifdef ANSI_C
void show_buffer(void)
#else
void show_buffer()
#endif
{
	if (no_buffer) return;

	ask_window_size(frame_window);
	if (act_x_pos+window_width- PIXW_XOFFSET>G_xmax) { 
		act_x_pos=0;
		position_nor_scrollbars();
	}
	if (act_y_pos+window_height-PIXW_YOFFSET>G_ymax) { 
		act_y_pos=0;
		position_nor_scrollbars();
	}
        XCopyArea(root_display,
                pix_dw,
                pix_window,
                pix_GC,
                act_x_pos, act_y_pos,
		window_width  - PIXW_XOFFSET,
		window_height - PIXW_YOFFSET,
                0, 0
        );
        XSync(root_display, 0);
	if ( V_ruler && (fisheye_view==0) ) ruler_paint(); 
        XSync(root_display, 0);
}



/*--------------------------------------------------------------------*/
/*  Event handling                                                    */
/*--------------------------------------------------------------------*/

/* The main loop for interaction
 * =============================
 */


#ifdef ANSI_C
static void window_main_loop(void)
#else
static void window_main_loop()
#endif
{
	int notready = 1;
	XEvent event;


	set_normal_cursor();
	while (notready) {

		XNextEvent (root_display, &event);

		if (event.type != Expose) win_exposed = 0;

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
	    		do_gblConfigureNotify (&event);
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
	    		/* prologue (&event, "Unhandled"); */
	    		break;
		}
    	}
}


#ifdef EVENT_DEBUG

/* For debugging only: Print event message
 * ---------------------------------------
 */

#ifdef ANSI_C
static void prologue(XEvent *eventp, char *event_name)
#else
static void prologue(eventp, event_name)
XEvent *eventp;
char *event_name;
#endif
{
	XAnyEvent *e = (XAnyEvent *) eventp;

	panel_event(event_name);
	PRINTF ("\n%s event, serial %ld, synthetic %s, window 0x%lx,\n",
	    event_name, e->serial, e->send_event ? "Yes" : "No", e->window);
}

#endif /* EVENT_DEBUG */



/* Standard Keypress Event
 * -----------------------
 * These are allowed if we are in the main loop.
 */

#ifdef ANSI_C
static void do_KeyPress(XEvent *eventp)
#else
static void do_KeyPress(eventp)
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
		case '1': /* Expose or hide class 1 */
		case '2': /* Expose or hide class 2 */
		case '3': /* Expose or hide class 3 */
		case '4': /* Expose or hide class 4 */
		case '5': /* Expose or hide class 5 */
		case '6': /* Expose or hide class 6 */
		case '7': /* Expose or hide class 7 */
		case '8': /* Expose or hide class 8 */
		case '9': /* Expose or hide class 9 */
			i = str[0]-'0';	
			if (i<1) return;
			if (i>max_nr_classes) return;
			if (hide_class[i-1]==0) 
				hide_class[i-1] = 1;
		 	else	hide_class[i-1] = 0;
			complete_relayout();
			return;
		case 'p':
			m_pic_position();
			return;
		case 'P':
			m_position();
			return;
		case 'j':
		case 'J':
			info_val = 3;
			i = 1;
			/* Fall through */
		case 'i': 
			if (!i) info_val = 1;
			i = 1;
			/* Fall through */
		case 'I': 
			if (!i) info_val = 2;
			truesize = 1;
			handle_info_menu(info_val);
			return;
		case 'e':
		case 'E':
			m_follow_edge();
			return;
		case 'n':
		case 'N':
			m_center_node(x11_print_title_dialog(),1);
			return;
		case 'f':
		case 'F':
			load_save_flag = LS_LOAD;
			clear_panel();
			m_loadsave();
			return;
		case 'g':
		case 'G':
			m_reload();
			return;
		case 'l': /* Layout Box */
		case 'L': /* Layout Box */
			if (x11_print_layout_dialog()) complete_relayout();
			else show_buffer();
			return;
		case 'v': /* View Box*/
		case 'V': /* View Box */
			(void)x11_print_view_dialog();
			show_buffer();
			return;
		case 'q': /* Quit */
		case 'Q': /* Quit */
			gs_exit(0);
			return;
#ifdef DRAWDEBUG
		case ' ': /* Debug */
			step3_main(); 
			return;
#endif 
		default: do_minimalKeyPress(eventp);
			reset_menues();
			return;
		}
	}
	else do_minimalKeyPress(eventp);
}

/* Minimal Keypress Event
 * ----------------------
 * These are always allowed because they do not cause a relayout.
 */

#ifdef ANSI_C
static void do_minimalKeyPress(XEvent *eventp)
#else
static void do_minimalKeyPress(eventp)
XEvent *eventp;
#endif
{
    	XKeyEvent *e = (XKeyEvent *) eventp;
    	KeySym ks;
    	int nbytes;
    	char str[256+1];
	int redraw_necessary;

    	nbytes = XLookupString (e, str, 256, &ks, NULL);
    	if (nbytes < 0) nbytes = 0;
    	if (nbytes > 256) nbytes = 256;
    	str[nbytes] = '\0';

	redraw_necessary = 0;
	if (ks==0xff54) { /* Down */
		redraw_necessary = incr_fe_focus(0, 256);
	}
	else if (ks==0xff53) { /* Right */
		redraw_necessary = incr_fe_focus(256, 0);
	}
	else if (ks==0xff52) { /* Up */
		redraw_necessary = incr_fe_focus(0, -256);
	}
	else if (ks==0xff51) { /* Left */
		redraw_necessary = incr_fe_focus(-256, 0);
	}
	else if (nbytes==1) {
		switch (str[0]) {
		case 'd':  /* R10: left */
		case 'D':  /* R10: left */
			redraw_necessary = incr_fe_focus(-256, 0);
			break;
		case 'c':  /* R12: right */
		case 'C':  /* R12: right */
			redraw_necessary = incr_fe_focus(256, 0);
			break;
		case 'a':  /* R8: up */
		case 'A':  /* R8: up */
			redraw_necessary = incr_fe_focus(0, -256);
			break;
		case 'b':  /* R14: down */
		case 'B':  /* R14: down */
			redraw_necessary = incr_fe_focus(0, 256);
			break;
		case 'o':  /* origin */
		case 'O':  /* origin */
			redraw_necessary = normal_fe_focus();
			break;
		case 'q': /* Quit */
		case 'Q': /* Quit */
			gs_exit(0);
			break;
		case 'm':
		case 'M':  /* maximal graph visible */
			make_complete_graph_visible();
			break;
		case '0':  /* normal */
			redraw_necessary = 1;
			set_fe_scaling(1, 1);
			new_scale_fontbuffers(G_stretch,G_shrink);
			break;
		case '-':  /* shrink */
			redraw_necessary = 1;
			change_fe_scaling(2, 3);
			new_scale_fontbuffers(G_stretch,G_shrink);
			break;
		case '_':  /* shrink */
			redraw_necessary = 1;
			change_fe_scaling(1, 2);
			new_scale_fontbuffers(G_stretch,G_shrink);
			break;
		case '+':  /* stretch */
			redraw_necessary = 1;
			change_fe_scaling(3, 2);
			new_scale_fontbuffers(G_stretch,G_shrink);
			break;
		case '=':  /* stretch */
			redraw_necessary = 1;
			change_fe_scaling(2, 1);
			new_scale_fontbuffers(G_stretch,G_shrink);
			break;
		case 'r' : /* ruler */
		case 'R' : /* ruler */
			V_ruler = 1-V_ruler;
			clear_panel();
			if (V_ruler && (fisheye_view!=0)) {
			 	panel_outp("Ruler is not available ",
					   "in the fisheye view.",
				   	   ""); 
				V_ruler = 0;
			}
			show_buffer();
			break;
		}
	}
	if (redraw_necessary) {
		position_abs_scrollbars();
		disable_signal(); 
       		buildCanvas(); 
       		enable_signal();
	}
}


/* Button Press shows the main menu
 * --------------------------------
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

	w = e->window;
	act_scroll_window = w; 
	if (w==leftscrollbar)          return; 
	else if (w==lowerscrollbar)    return; 
	else if (w==leftabsscrollbar)  return;
	else if (w==lowerabsscrollbar) return;
	else if (w==rightscrollbar)    return; 
	else if (w==leftscrollup) {
		if (which_button(eventp)==G_MOUSE_LEFT) act_y_pos -= 16;
		else act_y_pos -= 2;
		if (act_y_pos<0) act_y_pos = 0;
		show_buffer();
		position_nor_scrollbars();
		return;
	} 
	else if (w==leftscrolldown) {
		ask_window_size(frame_window);
		if (which_button(eventp)==G_MOUSE_LEFT) act_y_pos += 16;
		else act_y_pos += 2;
		if (act_y_pos+window_height-PIXW_YOFFSET>G_ymax) 
			act_y_pos = G_ymax-window_height+PIXW_YOFFSET;
		show_buffer();
		position_nor_scrollbars();
		return;
	} 
	else if (w==lowerscrollleft) {
		if (which_button(eventp)==G_MOUSE_LEFT) act_x_pos -= 16;
		else act_x_pos -= 2;
		if (act_x_pos<0) act_x_pos = 0;
		show_buffer();
		position_nor_scrollbars();
		return;
	} 
	else if (w==lowerscrollright) {
		ask_window_size(frame_window);
		if (which_button(eventp)==G_MOUSE_LEFT) act_x_pos += 16;
		else act_x_pos += 2;
		if (act_x_pos+window_width-PIXW_XOFFSET>G_xmax) 
			act_x_pos = G_xmax-window_width+PIXW_XOFFSET;
		show_buffer();
		position_nor_scrollbars();
		return;
	} 
	else if (w==leftabsscrollup) {
		if (which_button(eventp)==G_MOUSE_LEFT) 
			(void)incr_fe_focus(0,-16);
		else	(void)incr_fe_focus(0,-2);
		position_abs_scrollbars();
		disable_signal();
                buildCanvas();
                enable_signal();
		return;
	} 
	else if (w==leftabsscrolldown) {
		if (which_button(eventp)==G_MOUSE_LEFT) 
			(void)incr_fe_focus(0,16);
		else	(void)incr_fe_focus(0,2);
		position_abs_scrollbars();
		disable_signal();
                buildCanvas();
                enable_signal();
		return;
	} 
	else if (w==lowerabsscrollleft) {
		if (which_button(eventp)==G_MOUSE_LEFT) 
			(void)incr_fe_focus(-16, 0);
		else	(void)incr_fe_focus(-2, 0);
		position_abs_scrollbars();
		disable_signal();
                buildCanvas();
                enable_signal();
		return;
	} 
	else if (w==lowerabsscrollright) {
		if (which_button(eventp)==G_MOUSE_LEFT)
			(void)incr_fe_focus(16, 0);
		else	(void)incr_fe_focus(2, 0);
		position_abs_scrollbars();
		disable_signal();
                buildCanvas();
                enable_signal();
		return;
	} 
	else if (w==rightscrollup) {
		if (which_button(eventp)==G_MOUSE_LEFT) 
			change_fe_scaling(2, 3);
		else 	change_fe_scaling(4, 5);
		new_scale_fontbuffers(G_stretch,G_shrink);
		if (fisheye_view==0) 
			SPRINTF(las_buf,
				"Scaling to %d.%d %%",G_stretch*100/G_shrink,
				(G_stretch*100/G_shrink)%10);
		else    SPRINTF(las_buf,
				"Fisheye to %ld.0 %%",fe_scaling);
		fast_panel_outp(las_buf);
		position_abs_scrollbars();
		disable_signal();
                buildCanvas();
                enable_signal();
		return;
	} 
	else if (w==rightscrolldown) {
		if (which_button(eventp)==G_MOUSE_LEFT) 
			change_fe_scaling(3, 2);
		else 	change_fe_scaling(4, 5);
		new_scale_fontbuffers(G_stretch,G_shrink);
		if (fisheye_view==0) 
			SPRINTF(las_buf,
				"Scaling to %d.%d %%",G_stretch*100/G_shrink,
				(G_stretch*100/G_shrink)%10);
		else    SPRINTF(las_buf,
				"Fisheye to %ld.0 %%",fe_scaling);
		fast_panel_outp(las_buf);
		position_abs_scrollbars();
		disable_signal();
                buildCanvas();
                enable_signal();
		return;
	} 
	else if (w==maxscalepoint) {
		make_complete_graph_visible();
	   	return; 
	}

	gs_check_allmenues();
	gs_draw_menu(frame_menu,e->x,e->y);
}

/* Button Release handles the selection in the main menu
 * -----------------------------------------------------
 */

#ifdef ANSI_C
static void do_ButtonRelease (XEvent *eventp)
#else
static void do_ButtonRelease (eventp)
XEvent *eventp;
#endif
{
	XButtonEvent *e = (XButtonEvent *) eventp;

	if (act_scroll_window && (act_scroll_window!=e->window)) {
		position_nor_scrollbars();
		position_abs_scrollbars();
	}
	else if (act_scroll_window==leftscrollbar) 
		read_leftscrollbar(e->y);
	else if (act_scroll_window==lowerscrollbar) 
		read_lowerscrollbar(e->x);
	else if (act_scroll_window==leftabsscrollbar) 
		read_leftabsscrollbar(e->y);
	else if (act_scroll_window==lowerabsscrollbar) 
		read_lowerabsscrollbar(e->x);
	else if (act_scroll_window==rightscrollbar) 
		read_rightscrollbar(e->y);

	if (act_scroll_window==leftscrollbar) {
		show_buffer();
		act_scroll_window = 0; 
		return;
	} 
	else if (act_scroll_window==lowerscrollbar) {
		show_buffer();
		act_scroll_window = 0; 
		return;
	}
	else if (act_scroll_window==leftabsscrollbar) {
		position_abs_scrollbars();
		disable_signal(); 
       		buildCanvas(); 
       		enable_signal();
		act_scroll_window = 0; 
		return;
	} 
	else if (act_scroll_window==lowerabsscrollbar) {
		position_abs_scrollbars();
		disable_signal(); 
       		buildCanvas(); 
       		enable_signal();
		act_scroll_window = 0; 
		return;
	}
	else if (act_scroll_window==rightscrollbar) {
		position_abs_scrollbars();
		disable_signal(); 
       		buildCanvas(); 
       		enable_signal();
		act_scroll_window = 0; 
		return;
	} 
	gs_handle_menu_selection();
}


/* Touch new menu point
 * --------------------
 * We first check which point was selected. Then we check whether this
 * causes a change of the visibility of the menu. A change of the 
 * visibility happens if a submenu previous visible is folded now.
 * Then we redraw the menu by highlighting the selected part, and
 * optinally by showing a selected submenu.
 * If the visibility was changed, we must redraw the whole menu.
 */

#ifdef ANSI_C
static void do_EnterNotify (XEvent *eventp)
#else
static void do_EnterNotify (eventp)
XEvent *eventp;
#endif
{
    	XCrossingEvent *e = (XCrossingEvent *) eventp;
	XWindowAttributes retWinAttr;
	Window w;
	int    vis;

	w = e->window;

	vis = 0;
	if (w==foldregion_touch)	{gs_draw_submenu(frame_menu,4);  return; }
	else if (w==scroll_touch)	{gs_draw_submenu(frame_menu,6);  return; }
	else if (w==info_touch)		{gs_draw_submenu(frame_menu,7);  return; }
	else if (w==scale_touch)	{gs_draw_submenu(frame_menu,15); return; }
	else if (w==export_touch)	{gs_draw_submenu(frame_menu,16); return; }
	else if (w==maxscalepoint) {
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
	if (MENU_VIS(frame_menu)) {
		(void)gs_check_menuselect(w,frame_menu);
		if ((vis=gs_check_vis_changed(frame_menu))>0) show_buffer();
		gs_redraw_menu(frame_menu);
		if (vis) gs_draw_menu(	frame_menu,
					MENU_X(frame_menu),		
					MENU_Y(frame_menu));
	}
}


/* Untouch menu point
 * ------------------
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
	XWindowAttributes retWinAttr;
	Window w;

	w = e->window;

	if (w==maxscalepoint) {
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
	gs_unselect_allmenus();
}


/* Expose a window
 * ---------------
 * Only for the frame window, we have to redraw the contents.
 */

#ifdef ANSI_C
static void do_Expose (XEvent *eventp)
#else
static void do_Expose (eventp)
XEvent *eventp;
#endif
{
	XExposeEvent *e = (XExposeEvent *) eventp;

	if (  (e->window==pix_window)
	    ||(e->window==frame_window)) {
		if ((!win_exposed)&&(e->width>10) && (e->height>10)) {
		  	show_buffer();
		  	win_exposed = 1;
		}
	}
	else win_exposed = 0;
}


/* Expose a window
 * ---------------
 * Only for the frame window, we have to redraw the contents.
 */

#ifdef ANSI_C
void do_gblExpose (XEvent *eventp)
#else
void do_gblExpose (eventp)
XEvent *eventp;
#endif
{
	XExposeEvent *e = (XExposeEvent *) eventp;

	if (  (e->window==pix_window)
	    ||(e->window==frame_window)) {
		  show_buffer();
	}
}


/* Resize or move a window
 * -----------------------
 */

#ifdef ANSI_C
void do_gblConfigureNotify (XEvent *eventp)
#else
void do_gblConfigureNotify (eventp)
XEvent *eventp;
#endif
{
	int width,height,done;
	XConfigureEvent *e = (XConfigureEvent *) eventp;

	if (e->window==frame_window) {
		width = e->width;
		height = e->height;
		done = 0;
		if (G_xmax<width)  { width  = G_xmax; done = 1; }
		if (G_ymax<height) { height = G_ymax; done = 1; }
		if (done)
			XResizeWindow(root_display,frame_window,width,height);

		XMoveResizeWindow(root_display,pix_window,
				20,2,width-PIXW_XOFFSET,height-PIXW_YOFFSET);
		XMoveResizeWindow(root_display,panel_window,
				2,height-60+4,width-6,50);

		XMoveResizeWindow(root_display,maxscalepoint,
				width-11, 
				height-PIXW_YOFFSET+4,
                                8, 18);

		MoveResizeScrollbar( leftscrollbar,
			leftscrollup,leftscrolldown,
			11, 2, 8, height-PIXW_YOFFSET);
		MoveResizeScrollbar( leftabsscrollbar,
			leftabsscrollup,leftabsscrolldown,
			2, 2, 8, height-PIXW_YOFFSET);
		MoveResizeScrollbar( rightscrollbar,
			rightscrollup,rightscrolldown,
			width-11, 2, 8, height-PIXW_YOFFSET);
		MoveResizeScrollbar( lowerscrollbar,
			lowerscrollleft,lowerscrollright,
			20, height-PIXW_YOFFSET+5, width-PIXW_XOFFSET+1, 8);
		MoveResizeScrollbar( lowerabsscrollbar,
			lowerabsscrollleft,lowerabsscrollright,
			20, height-PIXW_YOFFSET+14, width-PIXW_XOFFSET+1, 8);

		position_nor_scrollbars();
		position_abs_scrollbars();
		if (change_fe_winsize(0, width-PIXW_XOFFSET,
				      0, height-PIXW_YOFFSET)) {
			disable_signal(); 
       			buildCanvas(); 
       			enable_signal();
		}
		gs_hide_all_menus();
	}
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

	if (act_scroll_window==leftscrollbar) {
		read_leftscrollbar(e->y);
		show_buffer();
	}
	else if (act_scroll_window==lowerscrollbar) {
		read_lowerscrollbar(e->x);
		show_buffer();
	}
	else if (act_scroll_window==leftabsscrollbar) {
		read_leftabsscrollbar(e->y);
	}
	else if (act_scroll_window==lowerabsscrollbar) {
		read_lowerabsscrollbar(e->x);
	}
	else if (act_scroll_window==rightscrollbar) {
		read_rightscrollbar(e->y);
	}
}



/*--------------------------------------------------------------------*/
/*  Set G_shrink, G_stretch such that the complete graph is visible   */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
static void make_complete_graph_visible(void)
#else
static void make_complete_graph_visible()
#endif
{
	(void)normal_fe_focus();
        act_x_pos = act_y_pos = 0;
	ask_window_size(frame_window);

	if (maximal_xpos*(window_height-60) > maximal_ypos*window_width) {
		if (window_width<=40)
			set_fe_scaling(1,maximal_xpos);
		else	set_fe_scaling(window_width-40,maximal_xpos);
	}
	else {
		if (window_height<=60-35)
			set_fe_scaling(1,maximal_ypos);
		else	set_fe_scaling(window_height-60-35,maximal_ypos);
	}
	new_scale_fontbuffers(G_stretch,G_shrink);
	position_nor_scrollbars();
	position_abs_scrollbars();
	disable_signal(); 
       	buildCanvas(); 
       	enable_signal();
	show_buffer();
}



/*--------------------------------------------------------------------*/
/*  Cursor management                                                 */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
static void set_normal_cursor(void)
#else
static void set_normal_cursor()
#endif
{
	XDefineCursor(root_display,frame_window,standard_cursor);
	act_cursor = STD_CURSOR;
}

#ifdef ANSI_C
static void set_busy_cursor(void)
#else
static void set_busy_cursor()
#endif
{
	XDefineCursor(root_display,frame_window,workingCursor);
	XDefineCursor(root_display,leftabsscrollbar,workingCursor);
	XDefineCursor(root_display,lowerabsscrollbar,workingCursor);
	XDefineCursor(root_display,leftscrollbar,workingCursor);
	XDefineCursor(root_display,lowerscrollbar,workingCursor);
	XDefineCursor(root_display,rightscrollbar,workingCursor);
	act_cursor = WOR_CURSOR;
}

#ifdef ANSI_C
static void set_select_cursor(void)
#else
static void set_select_cursor()
#endif
{
	XDefineCursor(root_display,frame_window,selectCursor);
	act_cursor = SEL_CURSOR;
}

#ifdef ANSI_C
static void set_fold_cursor(void)
#else
static void set_fold_cursor()
#endif
{
	XDefineCursor(root_display,frame_window,foldCursor);
	act_cursor = FOL_CURSOR;
}

#ifdef ANSI_C
static void set_text_cursor(void)
#else
static void set_text_cursor()
#endif
{
	XDefineCursor(root_display,frame_window,textCursor);
	act_cursor = TXT_CURSOR;
}

#ifdef ANSI_C
static void set_leftscroll_cursor(void)
#else
static void set_leftscroll_cursor()
#endif
{
	XDefineCursor(root_display,leftscrollbar, leftscrollCursor);
	XDefineCursor(root_display,rightscrollbar,leftscrollCursor);
}

#ifdef ANSI_C
static void set_lowerscroll_cursor(void)
#else
static void set_lowerscroll_cursor()
#endif
{
	XDefineCursor(root_display,lowerscrollbar,lowerscrollCursor);
}

#ifdef ANSI_C
static void set_leftpos_cursor(void)
#else
static void set_leftpos_cursor()
#endif
{
	XDefineCursor(root_display,leftabsscrollbar,leftposCursor);
}

#ifdef ANSI_C
static void set_lowerpos_cursor(void)
#else
static void set_lowerpos_cursor()
#endif
{
	XDefineCursor(root_display,lowerabsscrollbar,lowerposCursor);
}

#ifdef ANSI_C
static void set_left_cursor(void)
#else
static void set_left_cursor()
#endif
{
	XDefineCursor(root_display,lowerscrollleft,   leftCursor);
	XDefineCursor(root_display,lowerabsscrollleft,leftCursor);
}

#ifdef ANSI_C
static void set_right_cursor(void)
#else
static void set_right_cursor()
#endif
{
	XDefineCursor(root_display,lowerscrollright,   rightCursor);
	XDefineCursor(root_display,lowerabsscrollright,rightCursor);
}

#ifdef ANSI_C
static void set_up_cursor(void)
#else
static void set_up_cursor()
#endif
{
	XDefineCursor(root_display,rightscrollup,  upCursor);
	XDefineCursor(root_display,leftscrollup,   upCursor);
	XDefineCursor(root_display,leftabsscrollup,upCursor);
}

#ifdef ANSI_C
static void set_down_cursor(void)
#else
static void set_down_cursor()
#endif
{
	XDefineCursor(root_display,rightscrolldown,  downCursor);
	XDefineCursor(root_display,leftscrolldown,   downCursor);
	XDefineCursor(root_display,leftabsscrolldown,downCursor);
}


#ifdef ANSI_C
static void reset_cursor(void)
#else
static void reset_cursor()
#endif
{
	switch (act_cursor) {
	case STD_CURSOR : set_normal_cursor(); break;
	case WOR_CURSOR : set_busy_cursor();   break;
	case SEL_CURSOR : set_select_cursor(); break;
	case FOL_CURSOR : set_fold_cursor();   break;
	case TXT_CURSOR : set_text_cursor();   break;
	}

	/* For the scrollbars */
	set_leftscroll_cursor();
	set_lowerscroll_cursor();
	set_leftpos_cursor();
	set_lowerpos_cursor();
	set_left_cursor();
	set_right_cursor();
	set_up_cursor();
	set_down_cursor();
}


/*--------------------------------------------------------------------*/
/*  Panel messages                                                    */
/*--------------------------------------------------------------------*/

/* Clear the panel
 * ---------------
 */

#ifdef ANSI_C
static void clear_panel(void)
#else
static void clear_panel()
#endif
{
	clear_from_xy_panel(0,0);
}


/* Clear the panel starting at special x position
 * ----------------------------------------------
 */

#ifdef ANSI_C
static void clear_from_xy_panel(int x, int y)
#else
static void clear_from_xy_panel(x,y)
int x;
int y;
#endif
{
	ask_window_size(panel_window);

	if (x>window_width) return;

	XSetForeground(root_display, panel_GC, carray[WHITE]);
	XFillRectangle(root_display,
                panel_dw,
                panel_GC,
		x, 
		y, 
		window_width-x, 
		window_height-y
	);
}


/* Write a message into the panel
 * ------------------------------
 * The message can be concatenated by x, y, and z.
 */

static char mbuffer[80];

#ifdef ANSI_C
static void 	panel_outp(char *x,char *y,char *z)
#else
static void 	panel_outp(x,y,z)
char *x;
char *y;
char *z;
#endif
{
	int  i;

	if (!panel_there) {
		if (silent) return;
		PRINTF("%s%s%s",x,y,z);
		return;
	}	
	clear_panel();
	XSetForeground(root_display, panel_GC, carray[BLACK]);
	i = 0;
	while ((*x)&&(i<79)) 	mbuffer[i++]= *x++;
	while ((*y)&&(i<79)) 	mbuffer[i++]= *y++;
	while ((*z)&&(i<79)) 	mbuffer[i++]= *z++;
	while (i<79) 		mbuffer[i++]= ' ';
	mbuffer[79] = 0;
	XDrawString(root_display,panel_dw,panel_GC,5,18,mbuffer,strlen(mbuffer));
	XSync(root_display, 0);
}


/* Write a message into the panel (line 2)
 * ---------------------------------------
 * The message can be concatenated by x, y, and z.
 */

#ifdef ANSI_C
static void 	panel_outp2(char *x,char *y,char *z,char *zz)
#else
static void 	panel_outp2(x,y,z,zz)
char *x;
char *y;
char *z;
char *zz;
#endif
{
	int  i;

	if (!panel_there) {
		if (silent) return;
		PRINTF("%s%s%s%s",x,y,z,zz);
		return;
	}	
	clear_from_xy_panel(0,21);
	XSetForeground(root_display, panel_GC, carray[BLACK]);
	i = 0;
	while ((*x)&&(i<79)) 	mbuffer[i++]= *x++;
	while ((*y)&&(i<79)) 	mbuffer[i++]= *y++;
	while ((*z)&&(i<79)) 	mbuffer[i++]= *z++;
	while ((*zz)&&(i<79)) 	mbuffer[i++]= *zz++;
	while (i<79) 		mbuffer[i++]= ' ';
	mbuffer[79] = 0;
	XDrawString(root_display,panel_dw,panel_GC,5,36,mbuffer,strlen(mbuffer));
	XSync(root_display, 0);
}


/* Write a message into the panel (fast version without XSync)
 * -----------------------------------------------------------
 */

#ifdef ANSI_C
static void 	fast_panel_outp(char *x)
#else
static void 	fast_panel_outp(x)
char *x;
#endif
{
	if (!panel_there) {
		if (silent) return;
		PRINTF("%s",x);
		return;
	}	
	clear_panel();
	XSetForeground(root_display, panel_GC, carray[BLACK]);
	XDrawString(root_display,panel_dw,panel_GC,5,18,x,strlen(x));
}


/* Write an event message into the panel
 * -------------------------------------
 */

static char ebuffer[20];

#ifdef ANSI_C
static void 	panel_event(char *x)
#else
static void 	panel_event(x)
char *x;
#endif
{
	int  i;

	clear_from_xy_panel(730,0);

	XSetForeground(root_display, panel_GC, carray[BLACK]);
	i = 0;
	while ((*x)&&(i<19)) 	ebuffer[i++]= *x++;
	while (i<19) 		ebuffer[i++]= ' ';
	ebuffer[19] = 0;
	XDrawString(root_display,panel_dw,panel_GC,730,18,
		ebuffer,strlen(ebuffer));
	XSync(root_display, 0);
}


/* Write a Waitmessage into the panel
 * ----------------------------------
 */

#ifdef ANSI_C
void gs_wait_message(int c)
#else
void gs_wait_message(c)
int c;
#endif
{
	int i;

	waitcnt++;
	if (!panel_there) {
		if (silent) return;
		FPRINTF(stdout,"\b.%c",c); 
		FFLUSH(stdout);
		return;
	}

	clear_panel();
	XSetForeground(root_display, panel_GC, carray[BLACK]);
	strcpy(mbuffer,"Wait  .");
	for (i=5; i<6+waitcnt; i++) {
		if (i>=70) { waitcnt=0; break; }
		mbuffer[i] = '.';		
	}
	mbuffer[i-1]=c;
	mbuffer[i]=0;
	XDrawString(root_display,panel_dw,panel_GC,5,18,mbuffer,i);
	/* XSync(root_display, 0); */
}


/*--------------------------------------------------------------------*/
/*  Panel Input                                                       */
/*--------------------------------------------------------------------*/

/* Read text in the panel
 * ----------------------
 * First msg is printed at position ypos.
 * If mode = 1, we allow only digits as input.
 */

#ifdef ANSI_C
static char *read_text(char *msg, int  ypos, int  mode)
#else
static char *read_text(msg,ypos,mode)
char *msg;
int  ypos;
int  mode;
#endif
{
	int i,j;
	int xpos,xoripos;
	int old_cursor;
	XEvent event;
    	XKeyEvent *e;
    	KeySym ks;
    	char str[256+1];

	xpos = 5;
	XSetForeground(root_display, panel_GC, carray[BLACK]);
	i = 0;
	while ((*msg)&&(i<79)) 	mbuffer[i++]= *msg++;
	mbuffer[i] = 0;
	XDrawString(root_display,panel_dw,panel_GC,xpos,ypos,
			mbuffer,strlen(mbuffer));
	XSync(root_display, 0);
	xpos += XTextWidth(panel_font,mbuffer,strlen(mbuffer));
	xoripos = xpos;

	old_cursor = act_cursor;
	set_text_cursor();

	j = 0;
	mbuffer[j]=0;
	ks =0;
	while (ks!=0xff0d) {
		if (j>78) j=78;
		clear_from_xy_panel(xpos,ypos-16);
		XSetForeground(root_display, panel_GC, carray[BLACK]);
		XDrawString(root_display,panel_dw,panel_GC,xpos,ypos,
			"_",1);
		XSync(root_display, 0);

		XNextEvent (root_display, &event);
		switch (event.type) {
	  	case KeyPress: 	break;
		default: 	default_handler(&event);
				continue;
		}

		clear_from_xy_panel(xpos,ypos-16);
		XSetForeground(root_display, panel_GC, carray[BLACK]);
    		e = (XKeyEvent *)&event;
    		i = XLookupString (e, str, 256, &ks, NULL);
    		if (i < 0)    i = 0;
    		if (i > 256)  i = 256;
    		str[i] = 0;
		if (ks==0xff0d)      { mbuffer[j]=0; }
		else if (ks==0xff0a) { mbuffer[j]=0; }
		else if (ks==0xff08) { j--; if (j<0) j=0; mbuffer[j]=0; }
		else if (ks==0xffff) { j--; if (j<0) j=0; mbuffer[j]=0; }
		else if (i==1) { 
			if ((mode==1)&&((str[0]<'0')||(str[0]>'9'))) continue; 
			if (  (mode==2) 
			    &&((str[0]<'0')||(str[0]>'9'))
			    &&(str[0]!=' ')&&(str[0]!=','))
				continue; 
			mbuffer[j++]=str[0];
			mbuffer[j]  =0;
			XDrawString(root_display,panel_dw,panel_GC,xpos,ypos,
				str,1);
			XSync(root_display, 0);
		}
		xpos = xoripos + XTextWidth(panel_font,mbuffer,strlen(mbuffer));
	}
	mbuffer[j]=0;
	act_cursor = old_cursor;
	reset_cursor();
	return(mbuffer);
}



/*--------------------------------------------------------------------*/
/*  Menu Memory allocation                                            */
/*--------------------------------------------------------------------*/

/* General note: Menu's are allocated only once. Thus we use malloc
 * instead of our internal memory allocation mechanism, because 
 * speed is not important here and the menus are needed until the program
 * is finished.
 */

/* Allocate Menu 
 * -------------
 * A Menu is simply a window containing several subwindows. 
 * len is the len of itemtab.
 */


#ifdef ANSI_C
static gs_Menu	allocate_Menu(int len,char *itemtab[])
#else
static gs_Menu	allocate_Menu(len,itemtab)
int len;
char *itemtab[];
#endif
{
	int 	itemlen,h,i;

	ask_window_size(frame_window);

	itemlen = 0;
	for (i=0;i<len;i++) {
		h = XTextWidth(panel_font,itemtab[i],strlen(itemtab[i]));
		if (h>itemlen) itemlen = h;
	}	
	itemlen += 6;

	return(alloc_Menu(
			window_width,
			window_height,
			itemlen,
			MENUITEM_HEIGHT,
			len,
			itemtab)
	      );
}


/* Allocate a menu window
 * ----------------------
 * width and height are the position points to get the menu invisible.
 * itemw and itemh are the size of each item.
 * len is the size of the itemtab, which are the entry strings.
 */

#ifdef ANSI_C
static gs_Menu alloc_Menu(
	int width,int height,int itemw,int itemh,int len,char *itemtab[])
#else
static gs_Menu alloc_Menu(width,height,itemw,itemh,len,itemtab)
int width;
int height;
int itemw;
int itemh;
int len;
char *itemtab[];
#endif
{
	int i;
	gs_Menu m;
	Window  w;

	m = (gs_Menu)malloc(sizeof(struct gs_Menu_str)+len*sizeof(gs_MenuItem));
	if (!m) Fatal_error("memory exhausted","");

        w = XCreateSimpleWindow (root_display, frame_window, width+1, 
				    height+1,
                                    itemw, len*itemh,
                                    1,
				    XBlackPixel(root_display,root_screen),
				    XWhitePixel(root_display,root_screen));

	MENU_WIN(m)    = w;
	MENU_WIDTH(m)  = itemw;
	MENU_HEIGHT(m) = len*itemh;
	MENU_VIS(m)    = 0;
	MENU_LEN(m)    = len;
	MENU_DW(m)     = (Drawable)w;
	MENU_GC(m)     = XDefaultGC(root_display, root_screen);
        MENU_GCVAL(m).graphics_exposures = False;
        XChangeGC(root_display, MENU_GC(m), GCGraphicsExposures, &MENU_GCVAL(m));
	MENU_DW(m)     = (Drawable)w;
	if (panel_font)
		XSetFont(root_display,MENU_GC(m),panel_font->fid);

	for (i=1;i<=len;i++) {
		MENU_ITEM(m,i) = alloc_MenuItem(width,height,
					itemw,itemh,
					w,i,itemtab[i-1]);
	} 

        XMapWindow(root_display, w);

	return(m);
}


/* Allocate a menu item 
 * --------------------
 * width and height are the position points to get the menu invisible.
 * itemw and itemh are the size of each item.
 * len is the size of the itemtab, which are the entry strings.
 */

#ifdef ANSI_C
static gs_MenuItem alloc_MenuItem(
	int width,int height,int itemw,int itemh,
	Window win,int pos,char *entry)
#else
static gs_MenuItem alloc_MenuItem(width,height,itemw,itemh,win,pos,entry)
int width;
int height;
int itemw;
int itemh;
Window win;
int pos;
char *entry;
#endif
{
	gs_MenuItem m;
	Window      w;
	XSetWindowAttributes attr;
	unsigned long mask = 0L;

	m = (gs_MenuItem)malloc(sizeof(struct gs_MenuItem_str));
	if (!m) Fatal_error("memory exhausted","");

	/* select for all events */
	attr.event_mask = KeyPressMask           | 
			  ButtonPressMask        | ButtonReleaseMask  |
			  EnterWindowMask        | LeaveWindowMask    |
                          ExposureMask           | ResizeRedirectMask | 
                          SubstructureNotifyMask | 
                          FocusChangeMask        | OwnerGrabButtonMask;

	attr.background_pixel = XWhitePixel(root_display,root_screen);
	attr.border_pixel = XBlackPixel(root_display,root_screen);

	mask |= (CWBackPixel | CWBorderPixel | CWEventMask);

        w = XCreateWindow (root_display,win, 
				      0, (pos-1)*itemh,
                                      itemw, itemh,
				      1, (int)CopyFromParent,
                                      InputOutput, 
				      (Visual *)CopyFromParent,
                           	      mask, &attr);

        XMapWindow(root_display, w);

	MENUITEM_WIN(m) = w;
	MENUITEM_DW(m)  = (Drawable)w;
	MENUITEM_SEL(m) = 0;
	MENUITEM_EXP(m) = 1;
	MENUITEM_TXT(m) = entry;
	MENUITEM_SUB(m)	= NULL;

	return(m);
}


/* Install a submenu toucher 
 * -------------------------
 */


#ifdef ANSI_C
static void install_SubMenu(
	gs_Menu root_menu,
	int     item,
	gs_Menu sub_menu,
	Window *sub_touch)
#else
static void install_SubMenu(root_menu,item,sub_menu,sub_touch)
	gs_Menu root_menu;
	int item;
	gs_Menu sub_menu;
	Window *sub_touch;
#endif
{
	Window      w;
	unsigned long mask = 0L;
	XSetWindowAttributes attr;
	gs_MenuItem mi;

	mi = MENU_ITEM(root_menu,item);

	/* select for all events */
	attr.event_mask = KeyPressMask           | 
			  ButtonPressMask        | ButtonReleaseMask  |
			  EnterWindowMask        | LeaveWindowMask    |
                          ExposureMask           | ResizeRedirectMask | 
                          SubstructureNotifyMask | 
                          FocusChangeMask        | OwnerGrabButtonMask;

	attr.background_pixel = XWhitePixel(root_display,root_screen);
	attr.border_pixel = XBlackPixel(root_display,root_screen);

	mask |= (CWBackPixel | CWBorderPixel | CWEventMask);

        w = XCreateWindow (root_display,MENUITEM_WIN(mi), 
				      MENU_WIDTH(root_menu)-30,0,
                                      30, MENUITEM_HEIGHT,
				      0,(int)CopyFromParent,
                                      InputOutput, 
				      (Visual *)CopyFromParent,
                           	      mask, &attr);

        XMapWindow(root_display, w);

	*sub_touch = w;
	MENUITEM_SUB(mi)  = sub_menu;
}


 
/*--------------------------------------------------------------------*/
/*  Menu Drawing and Management                                       */
/*--------------------------------------------------------------------*/

/* Hide and expose a menu item
 * ---------------------------
 */

#ifdef ANSI_C
static void gs_Hide_MenuItem(gs_Menu m,int i)
#else
static void gs_Hide_MenuItem(m,i)
gs_Menu m;
int     i;
#endif
{
	MENUITEM_EXP(MENU_ITEM(m,i)) = 0;
}

#ifdef ANSI_C
static void gs_Expose_MenuItem(gs_Menu m,int i)
#else
static void gs_Expose_MenuItem(m,i)
gs_Menu m;
int     i;
#endif
{
	MENUITEM_EXP(MENU_ITEM(m,i)) = 1;
}

#ifdef ANSI_C
static void gs_NewText_MenuItem(gs_Menu m,int i,char *s)
#else
static void gs_NewText_MenuItem(m,i,s)
gs_Menu m;
int     i;
char *s;
#endif
{
	MENUITEM_TXT(MENU_ITEM(m,i)) = s;
}


#ifdef ANSI_C
static void gs_check_allmenues(void)
#else
static void gs_check_allmenues()
#endif
{
	if (V_ruler) 
		gs_NewText_MenuItem(frame_menu,12,"Ruler off           ");
	else
		gs_NewText_MenuItem(frame_menu,12,"Ruler on            ");

	/* if (G_displayel) {
	 *	gs_NewText_MenuItem(layout_menu,1,"Label of edges off");
	 * }	
	 */
}


/* Menu Drawing Functions
 * ======================
 */

/* Draw a menu at position x,y
 * ---------------------------
 */

#ifdef ANSI_C
static void gs_draw_menu(gs_Menu m, int x, int y)
#else
static void gs_draw_menu(m,x,y)
gs_Menu m;
int x;
int y;
#endif
{
	int 	i;
	int 	xpos,  ypos;

	ask_window_size(frame_window);

	xpos = x;
	ypos = y;
	if (xpos+MENU_WIDTH(m)  > window_width)  
		    xpos = window_width - MENU_WIDTH(m);
	if (ypos+MENU_HEIGHT(m) > window_height) 
		    ypos = window_height- MENU_HEIGHT(m);
	if (xpos<0) xpos = 0;
	if (ypos<0) ypos = 0;
	
	XMoveWindow(root_display,MENU_WIN(m),xpos,ypos);
	if (!MENU_VIS(m)) XMapRaised(root_display,MENU_WIN(m));
	MENU_VIS(m) = 1;
	MENU_X(m) = xpos;
	MENU_Y(m) = ypos;

	for (i=1; i<=MENU_LEN(m); i++) gs_draw_menuitem(m,i);
}


/* Draw a submenu of a menu
 * ------------------------
 * rootm is the root menu.
 */

#ifdef ANSI_C
static void gs_draw_submenu(gs_Menu rootm, int i)
#else
static void gs_draw_submenu(rootm,i)
gs_Menu rootm;
int i;
#endif
{
	int xpos,ypos;
	gs_MenuItem mi;

	xpos = MENU_X(rootm)+MENU_WIDTH(rootm)-19;
	ypos = MENU_Y(rootm)+MENUITEM_HEIGHT*(i-1);

	MENUITEM_SEL(MENU_ITEM(rootm,i)) = 1;
	mi = MENU_ITEM(rootm,i);
	if (MENUITEM_SUB(mi)) 
		gs_draw_menu(MENUITEM_SUB(mi),xpos,ypos);
}


/* Draw a menu item 
 * ----------------
 */

#ifdef ANSI_C
static void gs_draw_menuitem(gs_Menu m, int i)
#else
static void gs_draw_menuitem(m,i)
gs_Menu m;
int i;
#endif
{
	gs_MenuItem mi;

	mi = MENU_ITEM(m,i);
	if (MENUITEM_EXP(mi)==0) MENUITEM_SEL(mi)=0; 
	if (MENUITEM_SEL(mi)) 
		XSetForeground(root_display, MENU_GC(m), carray[BLACK]);
	else    XSetForeground(root_display, MENU_GC(m), carray[WHITE]);

	XFillRectangle(root_display,MENUITEM_DW(mi),MENU_GC(m),
		0,0,
		MENU_WIDTH(m),MENUITEM_HEIGHT);
	if (m==frame_menu) {
		switch (i) {
		case 4:
			XFillRectangle(root_display,
				(Drawable)foldregion_touch,MENU_GC(m),
				0,0,30,MENUITEM_HEIGHT);
			break;
		case 6:
			XFillRectangle(root_display,
				(Drawable)scroll_touch,MENU_GC(m),
				0,0,30,MENUITEM_HEIGHT);
			break;
		case 7:
			XFillRectangle(root_display,
				(Drawable)info_touch,MENU_GC(m),
				0,0,30,MENUITEM_HEIGHT);
			break;
		case 15:
			XFillRectangle(root_display,
				(Drawable)scale_touch,MENU_GC(m),
				0,0,30,MENUITEM_HEIGHT);
			break;
		case 16:
			XFillRectangle(root_display,
				(Drawable)export_touch,MENU_GC(m),
				0,0,30,MENUITEM_HEIGHT);
			break;
		}
	}

	if (MENUITEM_SEL(mi)) 
		XSetForeground(root_display, MENU_GC(m), carray[WHITE]);
	else    XSetForeground(root_display, MENU_GC(m), carray[BLACK]);

	XDrawString(root_display,MENUITEM_DW(mi),MENU_GC(m),3,15,
			MENUITEM_TXT(mi),strlen(MENUITEM_TXT(mi)));

	if (m==frame_menu) {
		switch (i) {
		case 4:
			XDrawString(root_display,
				(Drawable)foldregion_touch,MENU_GC(m),
				0,15,"=>",2);
			break;
		case 6:
			XDrawString(root_display,
				(Drawable)scroll_touch,MENU_GC(m),
				0,15,"=>",2);
			break;
		case 7:
			XDrawString(root_display,
				(Drawable)info_touch,MENU_GC(m),
				0,15,"=>",2);
			break;
		case 15:
			XDrawString(root_display,
				(Drawable)scale_touch,MENU_GC(m),
				0,15,"=>",2);
			break;
		case 16:
			XDrawString(root_display,
				(Drawable)export_touch,MENU_GC(m),
				0,15,"=>",2);
			break;
		}
	}


	if (m == frame_menu) {
		if (MENUITEM_EXP(mi)==0) {
			XDrawLine(root_display,MENUITEM_DW(mi),MENU_GC(m),
				0,0,MENU_WIDTH(m)-30,MENUITEM_HEIGHT);
			XDrawLine(root_display,MENUITEM_DW(mi),MENU_GC(m),
				MENU_WIDTH(m)-30,0,0,MENUITEM_HEIGHT);
		}
	}
	else {
		if (MENUITEM_EXP(mi)==0) {
			XDrawLine(root_display,MENUITEM_DW(mi),MENU_GC(m),
				0,0,MENU_WIDTH(m),MENUITEM_HEIGHT);
			XDrawLine(root_display,MENUITEM_DW(mi),MENU_GC(m),
				MENU_WIDTH(m),0,0,MENUITEM_HEIGHT);
		}
	}
	XSync(root_display, 0);
}


/* Redraw a menu
 * -------------
 * We assume that the menu itself is currently already drawn, but
 * its state has changed.
 * This recursive function traverses a menu and all its submenus.
 * The unselected submenues are hidden. 
 * The selected items are highlighted. The submenus that become
 * visible are drawn.
 */

#ifdef ANSI_C
static void gs_redraw_menu(gs_Menu m)
#else
static void gs_redraw_menu(m)
gs_Menu m;
#endif
{
	int i;
	gs_MenuItem mi;

	if (MENU_VIS(m)) {
		for (i=1; i<=MENU_LEN(m); i++) {
			mi = MENU_ITEM(m,i);
			if (MENUITEM_SUB(mi)) {
				if (!MENUITEM_SEL(mi)) {
					MENU_VIS(MENUITEM_SUB(mi))=0;
					gs_hide_menu(MENUITEM_SUB(mi));
				}
			}
		}
		for (i=1; i<=MENU_LEN(m); i++) {
			mi = MENU_ITEM(m,i);
			if (MENUITEM_SEL(mi)) gs_draw_menuitem(m,i);
			if (MENUITEM_SUB(mi)) {
				if (MENUITEM_SEL(mi)) {
					gs_redraw_menu(MENUITEM_SUB(mi)); 
				}
			}
		}
	}
}


/* Menu hiding
 * ===========
 */

/* Hide menu 
 * ---------
 */

#ifdef ANSI_C
static void gs_hide_menu(gs_Menu m)
#else
static void gs_hide_menu(m)
gs_Menu m;
#endif
{
	MENU_VIS(m) = 0;
	XUnmapWindow(root_display,MENU_WIN(m));
}



/* Hide all menus
 * --------------
 */

#ifdef ANSI_C
static void gs_hide_all_menus(void)
#else
static void gs_hide_all_menus()
#endif
{
	gs_hide_menu(frame_menu);
	gs_hide_menu(foldregion_menu);
	gs_hide_menu(scroll_menu);
	gs_hide_menu(info_menu);
	gs_hide_menu(scale_menu);
	gs_hide_menu(export_menu);
 	show_buffer();
}


/* Check whether the visibility of a menu has changed.
 * --------------------------------------------------
 * The visibility of a menu has changed if a submenu is unselected 
 * now and was selected previously. Then we return 1.
 * The reason that we call this a change of visibility is, that the
 * shape of the menu has changed now and we must redraw the background. 
 */

#ifdef ANSI_C
static int gs_check_vis_changed(gs_Menu m)
#else
static int gs_check_vis_changed(m)
gs_Menu m;
#endif
{
	int i;
	gs_MenuItem mi;

	if (MENU_VIS(m)) {
		for (i=1; i<=MENU_LEN(m); i++) {
			mi = MENU_ITEM(m,i);
			if (MENUITEM_SUB(mi)) {
				if (!MENUITEM_SEL(mi)) { 
					if (MENU_VIS(MENUITEM_SUB(mi))) 
						return(1);
				}
				if (gs_check_vis_changed(MENUITEM_SUB(mi))) 
					return(1);
			}
		}
	}
	return(0);
}


/* Check which menupoint is selected 
 * ---------------------------------
 * A menupoint is selected if it is touched, or if there it is
 * a submenu containing the touched point. w is the touched window.
 * We return 1 if a a point of the menu m is selected. 
 */

#ifdef ANSI_C
static int gs_check_menuselect(Window w, gs_Menu m)
#else
static int gs_check_menuselect(w,m)
Window w;
gs_Menu m;
#endif
{ 
	int i,found,found1;

	found = 0;
	if (MENU_VIS(m)) {
		for (i=1; i<=MENU_LEN(m); i++) {
			found1 = 0;
			if (MENUITEM_WIN(MENU_ITEM(m,i))==w) found1 = 1;
			if (MENUITEM_SUB(MENU_ITEM(m,i))) 
				found1 |= gs_check_menuselect(w,
					 MENUITEM_SUB(MENU_ITEM(m,i)));
			if (found1) MENUITEM_SEL(MENU_ITEM(m,i)) = 1;
			else MENUITEM_SEL(MENU_ITEM(m,i)) = 0;
			found |= found1;
		}
	}
	return(found);
}


/* Calculate the selected menu item
 * ================================
 * and handle the selection.
 */

#ifdef ANSI_C
static void gs_handle_menu_selection(void)
#else
static void gs_handle_menu_selection()
#endif
{
	int     retitem;
	gs_Menu retmenu;

	retitem = -1;
	if ((retitem== -1) && ((retitem=gs_check_menureturn(foldregion_menu))!= -1)) 
		retmenu = foldregion_menu;
	if ((retitem== -1) && ((retitem=gs_check_menureturn(scroll_menu))    != -1)) 
		retmenu = scroll_menu;
	if ((retitem== -1) && ((retitem=gs_check_menureturn(info_menu))      != -1)) 
		retmenu = info_menu;
	if ((retitem== -1) && ((retitem=gs_check_menureturn(scale_menu))     != -1)) 
		retmenu = scale_menu;
	if ((retitem== -1) && ((retitem=gs_check_menureturn(export_menu))    != -1)) 
		retmenu = export_menu;
	if ((retitem== -1) && ((retitem=gs_check_menureturn(frame_menu))     != -1)) 
		retmenu = frame_menu;
	gs_unselect_allmenus();
	gs_hide_all_menus();
	dispatch_interaction(retmenu,retitem);
}


/* Check the return value of one menu
 * ----------------------------------
 */

#ifdef ANSI_C
static int gs_check_menureturn(gs_Menu m)
#else
static int gs_check_menureturn(m)
gs_Menu m;
#endif
{
	int retitem;
	int i;

	retitem = -1;
	if (MENU_VIS(m)) {
		for (i=1; i<=MENU_LEN(m); i++) {
			if (MENUITEM_SEL(MENU_ITEM(m,i))) {
				retitem = i;
			}
			MENUITEM_SEL(MENU_ITEM(m,i)) = 0;
		}
	}
	return(retitem);
}



/* Menu point unselecting
 * ======================
 */

/* Unselect all menu points
 * ------------------------
 */

#ifdef ANSI_C
static void gs_unselect_allmenus(void)
#else
static void gs_unselect_allmenus()
#endif
{
	gs_unselect_menu(foldregion_menu);
	gs_unselect_menu(scroll_menu); 
	gs_unselect_menu(info_menu); 
	gs_unselect_menu(scale_menu); 
	gs_unselect_menu(export_menu); 
	gs_unselect_menu(frame_menu);
}


/* Unselect a menu point 
 * ---------------------
 */

#ifdef ANSI_C
static void gs_unselect_menu(gs_Menu m)
#else
static void gs_unselect_menu(m)
gs_Menu m;
#endif
{ 
	int i;

	if (MENU_VIS(m)) {
		for (i=1; i<=MENU_LEN(m); i++) {
			if (MENUITEM_SEL(MENU_ITEM(m,i))) {
				MENUITEM_SEL(MENU_ITEM(m,i)) = 0;
				gs_draw_menuitem(m,i);
			}
		}
	}
}


/*--------------------------------------------------------------------*/
/*  Window resizing procedure                                         */
/*--------------------------------------------------------------------*/

/* If we resize the window, we must take care that the panel stays
 * visible. Otherwise, the user could not see messages, etc.
 */

#ifdef ANSI_C
static void	resizeWindow(void)
#else
static void	resizeWindow()
#endif
{
	int width,height;
	int no_xy, no_wh;

	width  = G_width;
	height = G_height;

	if (G_xmax<width)  { width = G_xmax;  }
	if (G_ymax<height) { height = G_ymax; }

	no_xy = 0;
	no_wh = 0;
	if (G_x== -1) { G_x = 0; no_xy = 1; }
	if (G_y== -1) { G_y = 0; no_xy = 1; }
	if (!G_width_set)  no_wh = 1;
	if (!G_height_set) no_wh = 1;

	if (no_xy) {
		if (no_wh) {
			ask_window_size(frame_window);
			if ((G_xmax<window_width)||(G_ymax<window_height))
				XResizeWindow(root_display,frame_window,
					width,height);
		}
		else XResizeWindow(root_display,frame_window,width,height);
	}
	else {
		if (no_wh) {
			ask_window_size(frame_window);
			if ((G_xmax<window_width)||(G_ymax<window_height))
				XMoveResizeWindow(root_display,frame_window,
					G_x,G_y,width,height);
			else	XMoveResizeWindow(root_display,frame_window,
					G_x,G_y,window_width,window_height);
		}
		else XMoveResizeWindow(root_display,frame_window,
				G_x,G_y,width,height);
	}

	XMoveResizeWindow(root_display,pix_window,20,2,
		width-PIXW_XOFFSET,height-PIXW_YOFFSET);
	XMoveResizeWindow(root_display,panel_window,2,height-60+4,
		width-6,50);

	XMoveResizeWindow(root_display,maxscalepoint,
			width-11, 
			height-PIXW_YOFFSET+4,
                        8, 18);

	MoveResizeScrollbar( leftscrollbar,
			leftscrollup,leftscrolldown,
			11, 2, 8, height-PIXW_YOFFSET);
	MoveResizeScrollbar( leftabsscrollbar,
			leftabsscrollup,leftabsscrolldown,
			2, 2, 8, height-PIXW_YOFFSET);
	MoveResizeScrollbar( rightscrollbar,
			rightscrollup,rightscrolldown,
			width-11, 2, 8, height-PIXW_YOFFSET);
	MoveResizeScrollbar( lowerscrollbar,
			lowerscrollleft,lowerscrollright,
			20, height-PIXW_YOFFSET+5, width-PIXW_XOFFSET+1, 8);
	MoveResizeScrollbar( lowerabsscrollbar,
			lowerabsscrollleft,lowerabsscrollright,
			20, height-PIXW_YOFFSET+14, width-PIXW_XOFFSET+1, 8);

	position_nor_scrollbars();
	position_abs_scrollbars();
	(void)change_fe_winsize(0, width-PIXW_XOFFSET,
			      0, height-PIXW_YOFFSET);
	disable_signal(); 
       	buildCanvas(); 
       	enable_signal();
	gs_hide_all_menus();
}



#ifdef ANSI_C
static void read_leftscrollbar(int val)
#else
static void read_leftscrollbar(val)
int val;
#endif
{
	int barlen;

	ask_window_size(frame_window);
	barlen = window_height-PIXW_YOFFSET - 2 * 8 - 2;
	if (val<0) val=0;
	if (val+SCROLLBAR_LEN >= barlen) val = barlen-SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,leftscrolltmb, 0,val,6,SCROLLBAR_LEN);
	if (barlen-SCROLLBAR_LEN==0) act_y_pos=0;
	else act_y_pos = val * (G_ymax-window_height+PIXW_YOFFSET) 
				/ (barlen-SCROLLBAR_LEN);
	fast_panel_outp("Scrolling");
}


#ifdef ANSI_C
static void read_lowerscrollbar(int val)
#else
static void read_lowerscrollbar(val)
int val; 
#endif
{
	int barlen;

	ask_window_size(frame_window);
	barlen = window_width-PIXW_XOFFSET - 2 * 8 - 1;
	if (val<0) val=0;
	if (val+SCROLLBAR_LEN >= barlen) val = barlen-SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,lowerscrolltmb, val,0,SCROLLBAR_LEN,6);
	if (barlen-SCROLLBAR_LEN==0) act_x_pos=0;
	else act_x_pos = val * (G_xmax-window_width+PIXW_XOFFSET) 
				/ (barlen-SCROLLBAR_LEN);
	fast_panel_outp("Scrolling");
}



#ifdef ANSI_C
static void read_leftabsscrollbar(int val)
#else
static void read_leftabsscrollbar(val)
int val;
#endif
{
	int barlen;

	ask_window_size(frame_window);
	barlen = window_height-PIXW_YOFFSET - 2 * 8 - 2;
	if (val<0) val=0;
	if (val+SCROLLBAR_LEN >= barlen) val = barlen-SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,leftabsscrolltmb,0,val,6,SCROLLBAR_LEN);
	if (barlen-SCROLLBAR_LEN==0) (void)set_fe_yfocus(0);
	else if (fisheye_view==0) {
	     	(void)set_fe_yfocus(val * (maximal_ypos*G_stretch/G_shrink
				-window_height+PIXW_YOFFSET)
		     / (barlen-SCROLLBAR_LEN));
	}
	else (void)set_fe_yfocus(val * maximal_ypos / (barlen-SCROLLBAR_LEN));
	if (fisheye_view==0) 
		SPRINTF(las_buf,"Position to co-ordinate (x,y) = (%ld,%ld)",
			V_xmin*G_shrink/G_stretch,V_ymin*G_shrink/G_stretch);
	else    SPRINTF(las_buf,"Fisheye focus (x,y) = (%ld,%ld)",
			gfocus_x, gfocus_y);
	fast_panel_outp(las_buf);
}


#ifdef ANSI_C
static void read_lowerabsscrollbar(int val)
#else
static void read_lowerabsscrollbar(val)
int val;
#endif
{
	int barlen;

	ask_window_size(frame_window);
	barlen = window_width-PIXW_XOFFSET - 2 * 8 - 1;
	if (val<0) val=0;
	if (val+SCROLLBAR_LEN >= barlen) val = barlen-SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,lowerabsscrolltmb,val,0,SCROLLBAR_LEN,6);
	if (barlen-SCROLLBAR_LEN==0) (void)set_fe_xfocus(0);
	else if (fisheye_view==0) {
	     	(void)set_fe_xfocus(val * (maximal_xpos*G_stretch/G_shrink
				-window_width+PIXW_XOFFSET)
		     / (barlen-SCROLLBAR_LEN));
	}
	else (void)set_fe_xfocus(val * maximal_xpos / (barlen-SCROLLBAR_LEN));
	if (fisheye_view==0) 
		SPRINTF(las_buf,"Position to co-ordinate (x,y) = (%ld,%ld)",
			V_xmin*G_shrink/G_stretch,V_ymin*G_shrink/G_stretch);
	else    SPRINTF(las_buf,"Fisheye focus (x,y) = (%ld,%ld)",
			gfocus_x, gfocus_y);
	fast_panel_outp(las_buf);
}


#ifdef ANSI_C
static void read_rightscrollbar(int val)
#else
static void read_rightscrollbar(val)
int val;
#endif
{
	int z, barlen;
	double factor;

	ask_window_size(frame_window);
	barlen = window_height-PIXW_YOFFSET - 2 * 8 - 2;
	z = (barlen-SCROLLBAR_LEN)/2;
	if (val<0) val=0;
	if (val+SCROLLBAR_LEN >= barlen) val = barlen-SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,rightscrolltmb, 0,val,6,SCROLLBAR_LEN);
	if (z==0) factor = 1;
	else factor = exp((double)(3*(val-z))/(double)z);
	set_fe_scaling(gstoint(factor*1000),1000);
	if (fisheye_view==0) 
		SPRINTF(las_buf,"Scaling to %d.%d %%",(G_stretch*100/G_shrink),
					(G_stretch*100/G_shrink)%10);
	else    SPRINTF(las_buf,"Fisheye to %ld.0 %%",fe_scaling);
	fast_panel_outp(las_buf);
	new_scale_fontbuffers(G_stretch,G_shrink);

}



#ifdef ANSI_C
static void position_nor_scrollbars(void)
#else
static void position_nor_scrollbars()
#endif
{
	int val;
	int barlen; 

	ask_window_size(frame_window);

	/* This is the inverse of the read_leftscrollbar-formula 
	 */
	barlen = window_height-PIXW_YOFFSET - 2 * 8 - 2;

	if (G_ymax-window_height+PIXW_YOFFSET==0) val = 30000;
	else val=act_y_pos * (barlen-SCROLLBAR_LEN)
		      		/ (G_ymax-window_height+PIXW_YOFFSET);
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= barlen) val = barlen-SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,leftscrolltmb, 0,val,6,SCROLLBAR_LEN);

	/* This is the inverse of the read_lowerscrollbar-formula 
	 */
	barlen = window_width-PIXW_XOFFSET - 2 * 8 - 1;

	if (G_xmax-window_width+PIXW_XOFFSET==0) val = 30000;
	else val=act_x_pos * (barlen-SCROLLBAR_LEN)
		      		/ (G_xmax-window_width+PIXW_XOFFSET);
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= barlen) val = barlen-SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,lowerscrolltmb, val,0,SCROLLBAR_LEN,6);
}


#ifdef ANSI_C
static void position_abs_scrollbars(void)
#else
static void position_abs_scrollbars()
#endif
{
	int val;
	int z;
	int barlen; 

	ask_window_size(frame_window);

	/* This is the inverse of the read_leftabsscrollbar-formula 
	 */
	barlen = window_height-PIXW_YOFFSET - 2 * 8 - 2;
	
	if (fisheye_view == 0) {
		if (maximal_ypos*G_stretch/G_shrink-window_height+PIXW_YOFFSET
			== 0) 	val = 30000;
		else val = V_ymin*(barlen-SCROLLBAR_LEN) / 
		   (maximal_ypos*G_stretch/G_shrink-window_height+PIXW_YOFFSET);
	}
	else  val = gfocus_y * (barlen-SCROLLBAR_LEN) / maximal_ypos;
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= barlen) val = barlen-SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,
		leftabsscrolltmb, 0,val,6,SCROLLBAR_LEN);

	/* This is the inverse of the read_lowerabsscrollbar-formula 
	 */
	barlen = window_width-PIXW_XOFFSET - 2 * 8 - 1;

	if (fisheye_view == 0) {
		if (maximal_xpos*G_stretch/G_shrink-window_width+PIXW_XOFFSET
			== 0)  	val = 30000;
		else val = V_xmin*(barlen-SCROLLBAR_LEN) / 
		    (maximal_xpos*G_stretch/G_shrink-window_width+PIXW_XOFFSET);
	}
	else val = gfocus_x * (barlen-SCROLLBAR_LEN) / maximal_xpos;
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= barlen) val = barlen-SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,
		lowerabsscrolltmb, val,0,SCROLLBAR_LEN,6);

	/* This is the inverse of the read_rightscrollbar-formula 
	 */
	barlen = window_height-PIXW_YOFFSET - 2 * 8 - 2;

	z = (barlen-SCROLLBAR_LEN)/2;
	if (fisheye_view==0) {
		if (G_stretch==0) val = 0;
		else if (G_shrink==0)  val = 2*z;
		else val = gstoint(log((double)G_stretch/(double)G_shrink)*(double)z/3)+z;
	}
	else {  if (fe_scaling==0) val = 0;
		else val = gstoint(log((double)fe_scaling/(double)100)*(double)z/3)+z;
	}
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= barlen) val = barlen-SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,
		rightscrolltmb, 0,val,6,SCROLLBAR_LEN);
}


/*--------------------------------------------------------------------*/
/*  Display window open and close                                     */
/*--------------------------------------------------------------------*/

/* These functions are used to allow the animation interface to
 * open or close the window. 
 */

static int is_closed = 0;

#ifdef ANSI_C
void	gs_open(void)
#else
void	gs_open()
#endif
{
	if (is_closed) {
		XMapRaised(root_display,frame_window);
		XSync(root_display,True);
		is_closed = 0;
	}
}


#ifdef ANSI_C
void	gs_close(void)
#else
void	gs_close()
#endif
{
	if (!is_closed) {
		XIconifyWindow(root_display, frame_window, root_screen);
		XSync(root_display,True);
		is_closed = 1;
	}
}

/*--------------------------------------------------------------------*/
/*  Auxiliaries with strings                                          */
/*--------------------------------------------------------------------*/

/* Convertion of integers to strings
 * =================================
 */

/* Convert an integer to a string of 4 digits
 * ------------------------------------------
 * It is important that each time the string memory is newly allocated.
 */

#ifdef ANSI_C
static char 	*int_to_str(int n)
#else
static char 	*int_to_str(n)
int	n;
#endif
{
	char *r;

	r = (char *)myalloc(5);
	if ((n<-9999)||(n>99999)) return("*");
	SPRINTF(r, "%d", n);
	return (r);
}

/* Convert an integer to a string of 4 digits for the class field
 * --------------------------------------------------------------
 * It is important that each time the string memory is newly allocated.
 */

#ifdef ANSI_C
char 	*class_num(int n)
#else
char 	*class_num(n)
int	n;
#endif
{
	char *r;

	assert((n>0)&&(n<=max_nr_classes));
	if (class_name_available && class_names[n-1]) {
		return(class_names[n-1]);
	}
	r = (char *)myalloc(7);
	if ((n<-999)||(n>9999)) n = 0;
	SPRINTF(r, " %d", n);
	return (r);
}

/* Convert an integer to a string of 4 digits for the info field
 * -------------------------------------------------------------
 * It is important that each time the string memory is newly allocated.
 */

#ifdef ANSI_C
static char 	*act_info_num(int n)
#else
static char 	*act_info_num(n)
int	n;
#endif
{
	char *r;
	int  sc;

	if (n>3) { sc=1; n=n-3; } 
	else       sc=0;  
	
	assert((n>0)&&(n<=3));

	if (info_name_available && info_names[n-1]) {
		r = myalloc(strlen(info_names[n-1])+20);
		if (sc) SPRINTF(r, "%s (scaled)", info_names[n-1]);
		else    SPRINTF(r, "%s (normal)", info_names[n-1]);
		return(r);
	}
	r = (char *)myalloc(20);
	if ((n<-999)||(n>9999)) n = 0;
	if (sc) SPRINTF(r, "%d (scaled)", n);
	else    SPRINTF(r, "%d (normal)", n);
	return (r);
}



/*--------------------------------------------------------------------*/
/*  Management of the ruler                                           */
/*--------------------------------------------------------------------*/

/* Paint all rulers
 * ================
 * Here, we do not use the buffer, but paint into the unbuffered window
 * directly. The reason is, that painting the rulers is so fast that
 * we can do it to refresh the window. 
 * On the other side, we do not need to reconstruct the buffer if we
 * switch the ruler off: we simply reshow the buffer. That's faster.
 */

#ifdef ANSI_C
static void	ruler_paint(void)
#else
static void	ruler_paint()
#endif
{
	set_upper_ruler();
	set_lower_ruler();
	set_left_ruler ();
	set_right_ruler();
}


/* Upper, lower, left and right rulers
 * -----------------------------------
 */

#ifdef ANSI_C
static void	set_upper_ruler(void)
#else
static void	set_upper_ruler()
#endif
{
	int	l, i, j;
	char	*s;

	if ((G_color == BLACK) && (colored))
		XSetForeground(root_display, pix_GC, carray[WHITE]);
	else	XSetForeground(root_display, pix_GC, carray[BLACK]);
	XDrawLine(root_display, (Drawable)pix_window, pix_GC, 
			0, 10, G_xmax, 10);

	j = V_xmin + 100 + act_x_pos;
	i = 100;
	while (j < V_xmax) {
		set_h_scale(i,10);
		s = (char *)int_to_str((int)(j*G_shrink/G_stretch));
		l = strlen(s);
		if ( l%2 == 0 ) set_value(i-l*4,30,s);
		else 		set_value(i-(l-1)*4-4,30,s);
		i += 100;
		j += 100;
	}
}


#ifdef ANSI_C
static void	set_lower_ruler(void)
#else
static void	set_lower_ruler()
#endif
{
	int	l, i, j;
	char	*s;

	ask_window_size(frame_window);

	if ((G_color == BLACK) && (colored))
		XSetForeground(root_display, pix_GC, carray[WHITE]);
	else	XSetForeground(root_display, pix_GC, carray[BLACK]);
	XDrawLine(root_display, (Drawable)pix_window, pix_GC, 
			0,window_height-10-PIXW_YOFFSET,
			G_xmax,window_height-10-PIXW_YOFFSET);

	j = V_xmin + 100 + act_x_pos;
	i = 100;
	while (j < V_xmax) {
		set_h_scale(i,window_height-10-PIXW_YOFFSET);
		s = (char *)int_to_str((int)(j*G_shrink/G_stretch));
		l = strlen(s);
		if ( l%2 == 0 ) set_value(i-l*4,window_height-16-PIXW_YOFFSET,s);
		else 		set_value(i-(l-1)*4-4,window_height-16-PIXW_YOFFSET,s);
		i += 100;
		j += 100;
	}
}


#ifdef ANSI_C
static void	set_left_ruler(void)
#else
static void	set_left_ruler()
#endif
{
	int	i, j;
	char	*s;

	if ((G_color == BLACK) && (colored))
		XSetForeground(root_display, pix_GC, carray[WHITE]);
	else	XSetForeground(root_display, pix_GC, carray[BLACK]);
	XDrawLine(root_display, (Drawable)pix_window, pix_GC, 
			10,0,10,G_ymax);

	j = V_ymin + 100 + act_y_pos;
	i = 100;
	while (j < V_ymax) {
		set_v_scale(10,i);
		s = (char *)int_to_str((int)(j*G_shrink/G_stretch));
		set_value(16,i+4,s);
		i += 100;
		j += 100;
	}
}


#ifdef ANSI_C
static void	set_right_ruler(void)
#else
static void	set_right_ruler()
#endif
{
	int	l, i, j;
	char	*s;

	ask_window_size(frame_window);

	if ((G_color == BLACK) && (colored))
		XSetForeground(root_display, pix_GC, carray[WHITE]);
	else	XSetForeground(root_display, pix_GC, carray[BLACK]);
	XDrawLine(root_display, (Drawable)pix_window, pix_GC, 
			window_width-PIXW_XOFFSET-10,0,window_width-PIXW_XOFFSET-10,G_ymax);

	j = V_ymin + 100 + act_y_pos;
	i = 100;
	while (j < V_ymax) {
		set_v_scale(window_width-PIXW_XOFFSET-10,i);
		s = (char *)int_to_str((int)(j*G_shrink/G_stretch));
		l = strlen(s);
		set_value(window_width-PIXW_XOFFSET-16-l*8,i+4,s);
		i += 100;
		j += 100;
	}
}


/* Set a horizontal and vertical scale line item
 * ---------------------------------------------
 */

#ifdef ANSI_C
static void	set_h_scale(int x,int y)
#else
static void	set_h_scale(x,y)
int	x, y;
#endif
{
	XDrawLine(root_display, (Drawable)pix_window, pix_GC, x,y-5,x,y+5);
}


#ifdef ANSI_C
static void	set_v_scale(int x,int y)
#else
static void	set_v_scale(x,y)
int	x, y;
#endif
{
	XDrawLine(root_display, (Drawable)pix_window, pix_GC, x-5,y,x+5,y);
}


/* Draw a scaling number that is given as string s
 * -----------------------------------------------
 */

#ifdef ANSI_C
static void	set_value(int x,int y,char *s)
#else
static void	set_value(x,y,s)
int	x, y;
char	*s;
#endif
{
	XDrawString(root_display,(Drawable)pix_window,pix_GC, 
		    x, y, s, strlen(s));
}



/*--------------------------------------------------------------------*/
/*  Interactions                                                      */
/*--------------------------------------------------------------------*/

/* Dispatcher 
 * ----------
 */

#ifdef ANSI_C
static void dispatch_interaction(gs_Menu m, int item)
#else
static void dispatch_interaction(m,item)
gs_Menu m;
int item;
#endif
{
	if (item== -1) return;
	MENUITEM_SEL(MENU_ITEM(m,item)) = 0;
	if (m==frame_menu)           handle_frame_menu(item);
	else if (m==foldregion_menu) handle_fold_menu(item); 
	else if (m==scroll_menu)     handle_scroll_menu(item); 
	else if (m==info_menu)       handle_info_menu(item); 
	else if (m==scale_menu)      handle_scale_menu(item); 
	else if (m==export_menu)     handle_export_menu(item); 
}


/* Analyse buttons
 * ---------------
 * As side effect, we fill button_x and button_y with the position.
 */

static int button_x, button_y;

#ifdef ANSI_C
int which_button(XEvent *eventp)
#else
int which_button(eventp)
XEvent *eventp;
#endif
{
	long hx, hy;

	XButtonEvent *e = (XButtonEvent *) eventp;

	button_x = e->x+act_x_pos;
	button_y = e->y+act_y_pos;
	if (fisheye_view != 1) {
		fe_s_to_g(button_x, button_y, &hx, &hy);
		button_x = hx;
		button_y = hy;
	}
	return(e->button);
}


/* Frame menu handler
 * ------------------
 */

#ifdef ANSI_C
static void handle_frame_menu(int item)
#else
static void handle_frame_menu(item)
int item;
#endif
{
	switch(item) {
	case 1:
		panel_outp("Fold Subgraph  ","","");
		m_fold_subgraph(); 
		break;
	case 2:	panel_outp("Unfold Subgraph","","");
		m_unfold_subgraph(); 
		break;
	case 3:	panel_outp("Expose/Hide Edges","",""); 
		if (x11_print_classes_dialog()) complete_relayout();
		else show_buffer();
		break;
	case 4:	panel_outp("Fold Region    ","",""); 
		handle_fold_menu(1);
		break;
	case 5:	panel_outp("Unfold Region  ","",""); 
		m_unfold_region(); 
		break;
	case 6:	/* Scroll */
		break;
	case 7:	panel_outp("Node Info      ","",""); 
		handle_info_menu(7); 
		break;
	case 8:	panel_outp("XY-Position    ","",""); 
		m_position(); 
		break;
	case 9:panel_outp("Mouse Position ","","");  
		m_pic_position(); 
		break;
	case 10:panel_outp("Center Node    ","","");  
		m_center_node(x11_print_title_dialog(),1);
		break;
	case 11:panel_outp("Follow Edge    ","","");  
		m_follow_edge(); 
		break;
	case 12:/* Ruler */
		V_ruler = 1-V_ruler;
		clear_panel();
		if (V_ruler && (fisheye_view!=0)) {
		 	panel_outp("Ruler is not available ",
				   "in the fisheye view.",
			   	   ""); 
			V_ruler = 0;
		}
		show_buffer();
		break;
	case 13:/* Layout */
		if (x11_print_layout_dialog()) complete_relayout();
		break;
	case 14:/* Layout */
		(void)x11_print_view_dialog();
		break;
	case 15:/* Scale */ 
		break; 
	case 16:panel_outp("File           ","","");  
		handle_export_menu(1);
		break; 
	case 17:/* "Quit" */
		gs_exit(0);
		break;
	}
}



/* Region fold menu handler
 * ------------------------
 * If we do fold region, we store in foldregion_class the class to fold.
 */

static int foldregion_class;

#ifdef ANSI_C
static void handle_fold_menu(int item)
#else
static void handle_fold_menu(item)
int item;
#endif
{
	int		value;

	panel_outp("Fold Region","",""); 
	foldregion_class = value = item;
	m_fold_region();
}


/* Macros for try again messages
 * -----------------------------
 */

#define TRY_AGAIN_MESSAGE(x,y) panel_outp(x,y," Try again !")


/* Fold subgraph event handler
 * ===========================
 * Wait for a selection of a node with the left mouse button.
 * Selections that do not touch a node have no effect.
 * Pushing another button than the right button stops this
 * procedure.
 */ 


#ifdef ANSI_C
static void	m_fold_subgraph(void)
#else
static void	m_fold_subgraph()
#endif
{
	GNODE	v;
	XEvent  event;
	int	notready,old_cursor;

	panel_outp("Select nodes: ",
		   "the subgraphs the selected nodes belongs to are folded.",
		   ""
		  );

	old_cursor = act_cursor;
	set_fold_cursor();
	notready = 1;

	while (notready) {

		XNextEvent (root_display, &event);

		switch (event.type) {
	  	case ButtonPress:
	    		prologue (&event, "ButtonPress");
			if (which_button(&event)==G_MOUSE_LEFT) {
				v = search_xy_node(button_x,button_y);
				if (v && NROOT(v)) {
					NSTATE(NROOT(v)) = 2;
					add_sgfoldstart(NROOT(v));
					position_abs_scrollbars();
					buildCanvas();
					handle_selected_node(v);
				}
				else TRY_AGAIN_MESSAGE( 
					"This is not a node or ",
				        "it is not part of a subgraph.");
			}
			else if (which_button(&event)==G_MOUSE_RIGHT) {
				notready = 0;
				finish_selection();
			}
	    		break;
		default:
			if (esc_handler(&event)) {
				notready = 0;
				finish_selection();
			}
			else default_handler(&event);
	    		break;
		}
    	}

	act_cursor = old_cursor;
 	reset_cursor();
}



/* Unfold subgraph event handler
 * =============================
 * Wait for a selection of a node with the left mouse button.
 * Selections that do not touch a node have no effect.
 * Pushing another button than the right button stops this
 * procedure.
 */ 

#ifdef ANSI_C
static void	m_unfold_subgraph(void)
#else
static void	m_unfold_subgraph()
#endif
{
	GNODE	v;
	XEvent  event;
	int	notready,old_cursor;

	panel_outp("Select summary nodes: ",
		   "the subgraphs of these nodes are shown explicitly.",
		   ""
		  );

	old_cursor = act_cursor;
	set_select_cursor();
	notready = 1;

	while (notready) {

		XNextEvent (root_display, &event);

		switch (event.type) {
	  	case ButtonPress:
	    		prologue (&event, "ButtonPress");
			if (which_button(&event)==G_MOUSE_LEFT) {
				v = search_xy_node(button_x,button_y);
				if (v  && NSGRAPH(v)) {
					NSTATE(v) = 0;
					add_sgunfoldstart(v);
					handle_selected_node(v);
				}
				else TRY_AGAIN_MESSAGE( 
					"This is not a node or ",
					"it is not a subgraph summary node.");
			}
			else if (which_button(&event)==G_MOUSE_RIGHT) {
				notready = 0;
				finish_selection();
			}
	    		break;
		default:
			if (esc_handler(&event)) {
				notready = 0;
				finish_selection();
			}
			else default_handler(&event);
	    		break;
		}
    	}

	act_cursor = old_cursor;
 	reset_cursor();
}


/* Fold region Event handler 
 * =========================
 */ 

/* Selection of Foldstoppers
 * -------------------------
 * We have selected a class of edges to fold, which is in
 * the variable foldregion_class. Now we need the selection
 * of foldstoppers.
 * The actual curser is the select curser.
 * Wait for a selection of a node with the left mouse button.
 * Selections that do not touch a node have no effect.
 * Pushing another button than the right button starts the
 * selection of the foldstarter.
 */

#ifdef ANSI_C
static void	m_fold_region(void)
#else
static void	m_fold_region()
#endif
{
	GNODE	v;
	XEvent  event;
	int	notready,old_cursor;

	panel_outp("Select nodes: ",
		   "the 'Fold Region' operation stops at these nodes.",
		   ""
		  );

	old_cursor = act_cursor;
	set_select_cursor();
	notready = 1;

	while (notready) {

		XNextEvent (root_display, &event);

		switch (event.type) {
	  	case ButtonPress:
	    		prologue (&event, "ButtonPress");
			if (which_button(&event)==G_MOUSE_LEFT) {
				v = search_xy_node(button_x,button_y);
				if (v) {
					add_foldstop(v);
					handle_selected_node(v);
				}
				else TRY_AGAIN_MESSAGE( 
					"This is not an appropriate node.","");
			}
			else if (which_button(&event)==G_MOUSE_RIGHT) {
				notready = 0;
				m_fold_p2_region();
			}
	    		break;
		default:
			if (esc_handler(&event)) {
				notready = 0;
				finish_selection();
			}
			else default_handler(&event);
	    		break;
		}
    	}

	act_cursor = old_cursor;
 	reset_cursor();
}


/* Selection of the Foldstarter
 * ----------------------------
 * We have selected a class of edges to fold, which is in
 * the variable foldregion_class, and a set of fold stoppers.
 * The actual curser is the fold curser.
 * Wait for a selection of a node with the left mouse button.
 * Selections that do not touch a node have no effect.
 * Pushing another button than the right button stops this
 * procedure.
 */

#ifdef ANSI_C
static void	m_fold_p2_region(void)
#else
static void	m_fold_p2_region()
#endif
{
	GNODE	v;
	XEvent  event;
	int	notready,old_cursor;

	panel_outp("Select nodes: ",
		   "the 'Fold Region' operation starts from these nodes.",
		   ""
		  );

	/* the fold stopper alone don't cause a relayout
	 */
	if (selected_flag) selected_flag = -1;

	old_cursor = act_cursor;
	set_fold_cursor();
	notready = 1;

	while (notready) {

		XNextEvent (root_display, &event);

		switch (event.type) {
	  	case ButtonPress:
	    		prologue (&event, "ButtonPress");
			if (which_button(&event)==G_MOUSE_LEFT) {
				v = search_xy_node(button_x,button_y);
				if (v) {
					NFOLDING(v) = foldregion_class;
					add_foldstart(v);
					handle_selected_node(v);
				}
				else TRY_AGAIN_MESSAGE( 
					"This is not an appropriate node.","");
			}
			else if (which_button(&event)==G_MOUSE_RIGHT) {
				notready = 0;
				finish_selection();
			}
	    		break;
		default:
			if (esc_handler(&event)) {
				notready = 0;
				finish_selection();
			}
			else default_handler(&event);
	    		break;
		}
    	}

	act_cursor = old_cursor;
 	reset_cursor();
}



/* Unfold region Event handler 
 * ===========================
 * Wait for a selection of a node with the left mouse button.
 * Selections that do not touch a node have no effect.
 * Pushing another button than the right button stops this
 * procedure.
 */ 

#ifdef ANSI_C
static void	m_unfold_region(void)
#else
static void	m_unfold_region()
#endif
{
	GNODE	v;
	XEvent  event;
	int	notready,old_cursor;

	panel_outp("Select a node: ",
		   "the region of this summary node is unfolded.",
		   ""
		  );

	old_cursor = act_cursor;
	set_select_cursor();
	notready = 1;

	while (notready) {

		XNextEvent (root_display, &event);

		switch (event.type) {
	  	case ButtonPress:
	    		prologue (&event, "ButtonPress");
			if (which_button(&event)==G_MOUSE_LEFT) {
				v = search_xy_node(button_x,button_y);
				if (v && NREGREPL(v)) {
					add_unfoldstart(v);
					handle_selected_node(v);
				}
				else TRY_AGAIN_MESSAGE( 
					"This is not a node or ",
					"it is not a region summary node.");
			}
			else if (which_button(&event)==G_MOUSE_RIGHT) {
				notready = 0;
				finish_selection();
			}
	    		break;
		default:
			if (esc_handler(&event)) {
				notready = 0;
				finish_selection();
			}
			else default_handler(&event);
	    		break;
		}
    	}

	act_cursor = old_cursor;
 	reset_cursor();
}


/* Scroll Menu Handler
 * ===================
 */

#ifdef ANSI_C
static void handle_scroll_menu(int item)
#else
static void handle_scroll_menu(item)
int item;
#endif
{
	switch(item) {
	case 1:	/* "left" */
		(void)incr_fe_focus(-32,0);
		break;
	case 2:	/* "right" */
		(void)incr_fe_focus(32,0);
		break;
	case 3:	/* "up" */
		(void)incr_fe_focus(0,-32);
		break;
	case 4:	/* "down" */
		(void)incr_fe_focus(0,32);
		break;
	case 5:	/* "lleft" */
		(void)incr_fe_focus(-256,0);
		break;
	case 6:	/* "rright" */
		(void)incr_fe_focus(256,0);
		break;
	case 7:	/* "uup" */
		(void)incr_fe_focus(0,-256);
		break;
	case 8:	/* "ddown" */
		(void)incr_fe_focus(0,256);
		break;
	case 9:	/* "llleft" */
		(void)incr_fe_focus(-G_width,0);
		break;
	case 10:/* "rrright" */
		(void)incr_fe_focus(G_width,0);
		break;
	case 11:/* "uuup" */
		(void)incr_fe_focus(0, -G_height);
		break;
	case 12:/* "dddown" */
		(void)incr_fe_focus(0, G_height);
		break;
	case 13:/* "origin" */
		(void)normal_fe_focus();
		break;
	}
	position_abs_scrollbars();
	disable_signal(); 
        displayCanvas(); 
        enable_signal();
}


/* Info Menu Handler
 * =================
 */

#ifdef ANSI_C
static void handle_info_menu(int item)
#else
static void handle_info_menu(item)
int item;
#endif
{
	GNODE	v;
	XEvent  event;
	int	notready,old_cursor;

	info_val = item;
	truesize = 1;
	if (info_val == 9) {
		old_cursor = act_cursor;
		show_buffer();
		set_select_cursor();
		panel_outp("Press button to continue.","","");
		if (!colored) 
			XSetForeground(root_display, pix_GC, carray[WHITE]);
		else	XSetForeground(root_display, pix_GC, carray[G_color]);
		XFillRectangle(root_display,
               	 	(Drawable)pix_window,
              	  	pix_GC,
			0, 
			0, 
			G_xmax, G_ymax);
		if ((G_color == BLACK) && (colored))
			XSetForeground(root_display, pix_GC, carray[WHITE]);
		else	XSetForeground(root_display, pix_GC, carray[BLACK]);
		xtextout(1,"Statistics:");
		XSync(root_display, 0);
		statistics();

		xinttextout(2,"Number of visible real  nodes: ............... %d",
				st_nr_vis_nodes);
		xinttextout(3,"Number of visible dummy nodes: ............... %d",
				st_nr_vis_dummies);
		xinttextout(4,"Number of visible label nodes: ............... %d",
				st_nr_vis_labels);
		xinttextout(5,"Number of invisible nodes: ................... %d",
				st_nr_invis_nodes);
		xinttextout(6,"Number of invisible graph summary nodes:...... %d",
				st_nr_invis_graphs);
		xinttextout(7,"Number of visible normal edge segments:....... %d",
				st_nr_vis_edges);
		xinttextout(8,"Number of visible nearedges (+ anchordummies): %d",
				st_nr_vis_nearedges);
		xinttextout(9,"Number of reverted edge segments:............. %d",
				number_reversions);
		xinttextout(10,"Number of invisible edges: ................... %d",
				st_nr_invis_edges);
		xinttextout(11,"Maximal indegree  of a visible node: ......... %d",
				st_max_indeg);
		xinttextout(12,"Maximal outdegree of a visible node: ......... %d",
				st_max_outdeg);
		xinttextout(13,"Maximal degree    of a visible node: ......... %d",
				st_max_degree);
		xinttextout(14,"Number of crossings in this layout: .......... %d",
				nr_crossings);
		xtextout(15,   "(except the crossings at anchor points)");
		xinttextout(16,"Maximal x co-ordinate: ....................... %d",
				maximal_xpos);
		xinttextout(17,"Maximal y co-ordinate: ....................... %d",
				maximal_ypos);

		XSync(root_display, 0);
		(void)m_wait_until_button(0);
		show_buffer();
		clear_panel();
		finish_selection();
		act_cursor = old_cursor;
 		reset_cursor();
		return;
	}
	if ((info_val!=7) && (info_val!=8) && (info_val>3)) { 
		info_val -= 3;
		truesize = 0;
	}
	panel_outp("Select a node ",
		   "to get information about this node.",
		   ""
		  );

	old_cursor = act_cursor;
	set_select_cursor();
	notready = 1;

	while (notready) {

		XNextEvent (root_display, &event);

		switch (event.type) {
	  	case ButtonPress:
	    		prologue (&event, "ButtonPress");
			if (which_button(&event)==G_MOUSE_LEFT) {
				if (search_and_close_infobox(
					(button_x+V_xmin)*G_shrink/G_stretch,
					(button_y+V_ymin)*G_shrink/G_stretch
					)) {
					position_abs_scrollbars();
					disable_signal(); 
					buildCanvas(); 
					enable_signal();
					show_buffer();
					panel_outp("Select a node ",
		 			  "to get information about this node.",
		   			  ""
		  			);
					break;
				}
				v = search_xy_node(button_x,button_y);
				if (v) {
					set_busy_cursor();
					selected_flag = -1;
					if (truesize) gs_infobox(v,
     				  			NX(v), NY(v), 
							1,1,info_val);
					else          gs_infobox(v,
     				  			NX(v), NY(v), 
							G_stretch,G_shrink,
							info_val);
					show_buffer();
					set_select_cursor();
				}
				else TRY_AGAIN_MESSAGE( 
					"This is not an appropriate node.","");
			}
			else if (which_button(&event)==G_MOUSE_RIGHT) {
				notready = 0;
				free_infoboxes();
				finish_selection();
			}
	    		break;
		default:
			if (esc_handler(&event)) {
				notready = 0;
				free_infoboxes();
				finish_selection();
			}
			else default_handler(&event);
	    		break;
		}
    	}

	act_cursor = old_cursor;
 	reset_cursor();
	free_infoboxes();
}


/* Print a text into the pixwindow at position y*19
 * ------------------------------------------------
 */

#ifdef ANSI_C
static void xtextout(int y,char *msg)
#else
static void xtextout(y,msg)
int  y;
char *msg;
#endif
{
	XDrawString(root_display,(Drawable)pix_window,pix_GC, 
		    15, y*19, msg, strlen(msg));
}


/* Print a text and integer into the pixwindow at position y*19
 * ------------------------------------------------------------
 */


#ifdef ANSI_C
static void xinttextout(int y,char *msg,int i)
#else
static void xinttextout(y,msg,i)
int  y;
char *msg;
int i;
#endif
{
	SPRINTF(mbuffer,msg,i);
	xtextout(y,mbuffer);
}


/* Absolute Position Handler
 * =========================
 */

#ifdef ANSI_C
static void	m_position(void)
#else
static void	m_position()
#endif
{
	int xpos,ypos,redraw_necessary;

	clear_panel();
	xpos = atoi(read_text("x-co-ordinate:",18,1));

	redraw_necessary= set_fe_xfocus((xpos*G_stretch)/G_shrink);

	ypos = atoi(read_text("y-co-ordinate:",36,1));

	redraw_necessary += set_fe_yfocus((ypos*G_stretch)/G_shrink);

	position_abs_scrollbars();
	disable_signal(); 
        if (redraw_necessary) displayCanvas(); 
        enable_signal();

	clear_panel();
	reset_menues(); 
}


/* Pick Position Handler
 * =====================
 */

static int reg_minx, reg_miny, reg_maxx, reg_maxy;
static int reg_there;


#ifdef ANSI_C
static void m_pic_position(void)
#else
static void m_pic_position()
#endif
{
	int	notready,h;
	double  scaleval1, scaleval2;

	notready = 1;

	while (notready) {
		m_fetch_region(1);
		if (!reg_there) {
			position_abs_scrollbars();
			disable_signal(); 
      		 	displayCanvas(); 
   		   	enable_signal();

			clear_panel(); 
			reset_menues(); 
			break;
		}
		ask_window_size(frame_window);

		if (reg_minx>reg_maxx) { 
			h = reg_minx;
			reg_minx = reg_maxx;
			reg_maxx = h;
		}
		if (reg_miny>reg_maxy) { 
			h = reg_miny;
			reg_miny = reg_maxy;
			reg_maxy = h;
		}
	
		if (reg_minx!=reg_maxx) 
			scaleval1 = (float)(window_width)/
					(float)(reg_maxx-reg_minx);
		else 	scaleval1 = 1.0;
		if (reg_miny!=reg_maxy) 
			scaleval2 = (float)(window_height)/
					(float)(reg_maxy-reg_miny);
		else 	scaleval2 = 1.0;

		if (scaleval2<scaleval1) scaleval1 = scaleval2;
		if (scaleval1<0.0) scaleval1 = 1.0;

		if ((reg_maxx-reg_minx>10) || (reg_maxy-reg_miny>10)) {
			if (scaleval1<1.0) 
				set_fe_scaling(gstoint(scaleval1*1000.0),1000);
			else 	set_fe_scaling(1000,gstoint(1000.0/scaleval1));
			new_scale_fontbuffers(G_stretch,G_shrink);
			notready = 0;
		}
		if (fisheye_view==0) {
			set_fe_xfocus(reg_minx * G_stretch/G_shrink);
			set_fe_yfocus(reg_miny * G_stretch/G_shrink);
		}
		else {
			set_fe_xfocus((reg_minx+reg_maxx)/2);
			set_fe_yfocus((reg_miny+reg_maxy)/2);
		}
		position_abs_scrollbars();
		disable_signal(); 
       		displayCanvas(); 
      		enable_signal();

		clear_panel(); 
		reset_menues(); 
	}
}



/* Centering of Nodes - Handler
 * ============================
 */

#ifdef ANSI_C
void	m_center_node(GNODE v,int invis)
#else
void	m_center_node(v,invis)
GNODE v;
int   invis;
#endif
{
	int	x, y, width, height;

	clear_panel();

	if (v) {
		if (NINLIST(v)) {
			x      = (NX(v)*G_stretch)/G_shrink;
			y      = (NY(v)*G_stretch)/G_shrink;
			width  = (NWIDTH(v)*NSTRETCH(v)*G_stretch)/(NSHRINK(v)*G_shrink);
			height = (NHEIGHT(v)*NSTRETCH(v)*G_stretch)/(NSHRINK(v)*G_shrink); 
			ask_window_size(frame_window);

			if (fisheye_view==0) {
				(void)set_fe_xfocus((x+width/2) - 
							window_width/2);
				(void)set_fe_yfocus((y+height/2)- 
							(window_height-60)/2);
			}
			else {  (void)set_fe_xfocus(x);
				(void)set_fe_yfocus(y);
			}
			position_abs_scrollbars();
			disable_signal(); 
       	        	displayCanvas(); 
                	enable_signal();
			clear_panel(); 
		}
		else {
			if (invis)
				panel_outp("This title is currently not visible. ",
					   "Press button to continue.",
				   	   ""); 
			else 	panel_outp("This title is currently not visible. ",
					   "",
				   	   ""); 
			act_follow_edge = NULL;
			act_follow_node = NULL;
			if (!colored) 
				XSetForeground(root_display, pix_GC, carray[WHITE]);
			else	XSetForeground(root_display, pix_GC, carray[G_color]);
			XFillRectangle(root_display,
               		 	pix_dw,
              		  	pix_GC,
				0, 
				0, 
				G_xmax, G_ymax);
			(void)set_fe_xfocus(0);
			(void)set_fe_yfocus(0);
			NX(v) = NY(v) = 0L;
			x = G_shrink;
			y = G_stretch;
			G_shrink = G_stretch = 1;
			calc_node_size(v);
			gs_setshrink(NSTRETCH(v),
                             	     NSHRINK(v)  );
                	gs_setto(0,0);

			draw_one_node(v);

			G_shrink  = x;
			G_stretch = y;
			show_buffer();
			if (invis) (void)m_wait_until_button(0);
			return;
		}
	}
	else {
		position_abs_scrollbars();
		disable_signal(); buildCanvas(); enable_signal();
		show_buffer();
		panel_outp("Cancelled (may be: title is not known).","",""); 
	}
	reset_menues(); 
}


/* Wait until a button is pressed 
 * ==============================
 * We return the code of the button that was presses.
 */

#ifdef ANSI_C
static int m_wait_until_button(int expose_allowed)
#else
static int m_wait_until_button(expose_allowed)
int expose_allowed;
#endif
{
	XEvent  event;
	int	notready,old_cursor,result;

	old_cursor = act_cursor;
	set_select_cursor();
	notready = 1;

	result = G_MOUSE_LEFT;
	while (notready) {

		XNextEvent (root_display, &event);

		switch (event.type) {
	  	case ButtonPress:
	    		prologue (&event, "ButtonPress");
			if (act_revert_node)
				NREVERT(act_revert_node) = 0;
			position_abs_scrollbars();
			disable_signal(); buildCanvas(); enable_signal();
			show_buffer();
			clear_panel();
			finish_selection();
			notready = 0;
			result = which_button(&event);
	    		break;
	  	case Expose:
			if (!expose_allowed) break;
			/*FALLTHROUGH*/
		default:
			if (esc_handler(&event)) {
				if (act_revert_node)
					NREVERT(act_revert_node) = 0;
				act_revert_node = NULL;
				position_abs_scrollbars();
				disable_signal(); 
				buildCanvas(); 
				enable_signal();
				show_buffer();
				clear_panel();
				finish_selection();
				notready = 0;
				result = 4711;
			}
			else default_handler(&event);
	    		break;
		}
    	}

	act_cursor = old_cursor;
 	reset_cursor();
	return(result);
}



/* Wait until a button is pressed (version 2)
 * ==========================================
 * We return the code of the button that was presses.
 */

#ifdef ANSI_C
static int m_wait_until_histbutton(int expose_allowed)
#else
static int m_wait_until_histbutton(expose_allowed)
int expose_allowed;
#endif
{
	XEvent  event;
	int	notready,old_cursor,result;

	old_cursor = act_cursor;
	set_select_cursor();
	notready = 1;

	result = G_MOUSE_LEFT;
	while (notready) {

		XNextEvent (root_display, &event);

		switch (event.type) {
	  	case ButtonPress:
	    		prologue (&event, "ButtonPress");
			if (act_revert_node)
				NREVERT(act_revert_node) = 0;
			position_abs_scrollbars();
			disable_signal(); buildCanvas(); enable_signal();
			show_buffer();
			clear_panel();
			finish_selection();
			notready = 0;
			result = which_button(&event);
	    		break;
	  	case Expose:
			if (!expose_allowed) break;
			/*FALLTHROUGH*/
		default:
			if (gkey_handler(&event,"hH")) {
				(void)x11_print_fedge_dialog();
				if (act_revert_node)
					 NREVERT(act_revert_node) = 0;
				act_revert_node = NULL;
				position_abs_scrollbars();
				disable_signal(); 
				buildCanvas(); 
				enable_signal();
				show_buffer();
				clear_panel();
				finish_selection();
				notready = 0;
				result = 4711;
			}
			else if (esc_handler(&event)) {
				if (act_revert_node)
					NREVERT(act_revert_node) = 0;
				act_revert_node = NULL;
				position_abs_scrollbars();
				disable_signal(); 
				buildCanvas(); 
				enable_signal();
				show_buffer();
				clear_panel();
				finish_selection();
				notready = 0;
				result = 4711;
			}
			else default_handler(&event);
	    		break;
		}
    	}

	act_cursor = old_cursor;
 	reset_cursor();
	return(result);
}


/* Follow an Edge - Handler
 * =========================
 * The start/end-node of the edge is selected by mouse clicking. 
 */


#ifdef ANSI_C
static void	m_follow_edge(void)
#else
static void	m_follow_edge()
#endif
{
	GNODE	v;
	XEvent  event;
	int	notready,old_cursor;

	panel_outp("Select a node to follow its edges.","","");

	init_fedge_history();
	if (act_revert_node) NREVERT(act_revert_node) = 0;
	act_revert_node = NULL;
	act_follow_edge = NULL;
	act_follow_node = NULL;
	last_follow_edge = (GEDGE)-1;
	old_cursor = act_cursor;
	set_select_cursor();
	notready = 1;

	while (notready) {

		XNextEvent (root_display, &event);

		switch (event.type) {
	  	case ButtonPress:
	    		prologue (&event, "ButtonPress");
			if (which_button(&event)==G_MOUSE_LEFT) {
				v = search_xy_node(button_x,button_y);
				if (v && (NSUCC(v)||NPRED(v)||NCONNECT(v))) {
					set_act_follow_node(v,0); 
					notready = 0;
					m_follow_p2_edge();
				}
				else TRY_AGAIN_MESSAGE( 
					"This is not a node or ",
					"it has no edges.");
			}
			else if (which_button(&event)==G_MOUSE_RIGHT) {
				notready = 0;
				finish_selection();
			}
	    		break;
		default:
			if (esc_handler(&event)) {
				notready = 0;
				finish_selection();
			}
			else default_handler(&event);
	    		break;
		}
    	}

	act_cursor = old_cursor;
 	reset_cursor();
}



int act_follow_edge_visible;

#ifdef ANSI_C
static void	m_follow_p2_edge(void)
#else
static void	m_follow_p2_edge()
#endif
{
	XEvent  event;
	int	notready;

	notready = 1;
	while (notready) {

		XNextEvent (root_display, &event);

		switch (event.type) {
	  	case ButtonPress:
	    		prologue (&event, "ButtonPress");
			if (which_button(&event)==G_MOUSE_LEFT) {
				set_next_follow_edge(); 
			}
			else if (which_button(&event)==G_MOUSE_RIGHT) {
				notready = 0;
				do_act_follow_edge(); 
				panel_outp("Press left button to follow some edge,",
			  		 " right button to stop.", "");
				if (m_wait_until_histbutton(0)==G_MOUSE_LEFT) {
					x11_followedge_arrow(act_follow_edge);
					act_follow_edge_visible = 1;
					followedge_msg("Select an edge to follow: ",
		   				"Left button for next, ",
		   				"right button to continue.");
					notready = 1;
				}
			}
	    		break;
		default:
			if (gkey_handler(&event,"hH")) {
				(void)x11_print_fedge_dialog();
				if (act_revert_node)
					 NREVERT(act_revert_node) = 0;
				act_revert_node = NULL;
				position_abs_scrollbars();
				disable_signal(); buildCanvas(); enable_signal();
				show_buffer();
				clear_panel();
				finish_selection();
				notready = 0;
			}
			else if (esc_handler(&event)) {
				if (act_revert_node)
					 NREVERT(act_revert_node) = 0;
				act_revert_node = NULL;
				position_abs_scrollbars();
				disable_signal(); buildCanvas(); enable_signal();
				show_buffer();
				clear_panel();
				finish_selection();
				notready = 0;
			}
			else default_handler(&event);
	    		break;
		}
    	}
}



/* Set the target node of the follow edge as actual node to follow
 * ---------------------------------------------------------------
 * We return 1 if we have to continue the operation.
 */


#ifdef ANSI_C
void do_act_follow_edge(void) 
#else
void do_act_follow_edge()
#endif
{
	GNODE v;

	if (!act_follow_edge_visible) return;
	if (!act_follow_node) return;
	if (!act_follow_edge) return;
	v = search_target_node(act_follow_node,act_follow_edge);
	set_act_follow_node(v,1);
}



/* Set the actual node to follow its edge
 * --------------------------------------
 * We return 1 if we have to continue the operation.
 */

#ifdef ANSI_C
void set_act_follow_node(GNODE v, int mov) 
#else
void set_act_follow_node(v, mov)
GNODE v; 
int mov;
#endif
{
	int     x,y,width,height;
	int     i;

	if (!v) return;
	add_fedge_history(v);
	if (act_revert_node) NREVERT(act_revert_node) = 0;
	act_follow_node = act_revert_node = v;
	NREVERT(v) = 1;
	x      = (NX(v)*G_stretch)/G_shrink;
	y      = (NY(v)*G_stretch)/G_shrink;
	width  = (NWIDTH(v)*NSTRETCH(v)*G_stretch)/(NSHRINK(v)*G_shrink);
	height = (NHEIGHT(v)*NSTRETCH(v)*G_stretch)/(NSHRINK(v)*G_shrink); 
	if (fisheye_view==0) {
		if (mov) {
			ask_window_size(frame_window);
			(void)set_fe_xfocus((x+width/2) - window_width/2);
			(void)set_fe_yfocus((y+height/2) - (window_height-60)/2);
		}
	}
	else {  (void)set_fe_xfocus(x+width/2);
		(void)set_fe_yfocus(y+height/2);
	}
	position_abs_scrollbars();
	if ((fisheye_view!=0) || (mov)) {
		disable_signal(); 
       		buildCanvas(); 
       		enable_signal();
	}
	show_buffer();
	follow_state = 0;
	act_follow_edge = NULL;
	i = 0;
	while (last_follow_edge!=act_follow_edge) {
		next_follow_edge();
		i++;
		if (i>100) break;
	}
	if (mov==1) { 
		panel_outp("Press left button to follow some edge,",
			   " right button to stop.","");
		act_follow_edge_visible = 0;
	}
	else { followedge_msg("Select an edge to follow: ",
		   "Left button for next, ",
		   "right button to continue.");
		x11_followedge_arrow(act_follow_edge);
		act_follow_edge_visible = 1;
	}
}


/* Set the next follow edge
 * ------------------------
 */

#ifdef ANSI_C
void set_next_follow_edge(void) 
#else
void set_next_follow_edge()
#endif
{
	if (!act_follow_node) {
		panel_outp("No node selected","","");
		return;
	}
	next_follow_edge();
	show_buffer();
	x11_followedge_arrow(act_follow_edge);
	act_follow_edge_visible = 1;
	followedge_msg("Left button for next, ",
		   "right button to continue.","");
}



/* Get the next follow edge
 * ------------------------
 * This functions sets the global variable act_follow_edge
 * to the next edge of the node act_follow_node.
 * If act_follow_edge was NULL, it becomes the first edge.
 * Depending on the follow_state, we see which edges are
 * currently actual:
 *   follow_state = 0   =>  no edges are actual  
 *   follow_state = 1   =>  successor   edges NSUCC
 *   follow_state = 2   =>  predecessor edges NPRED
 *   follow_state = 3   =>  connections (near edges)
 *
 * Note that on follow_state = 3, we fetch also the edges
 * that are touched by anchors. Here, we must switch the 
 * act_follow_node to the anchordummy and back.
 */ 

#ifdef ANSI_C
static void next_follow_edge(void)
#else
static void next_follow_edge()
#endif
{
	ADJEDGE a;
	CONNECT c;

	switch (follow_state) {
	case 1: a = NSUCC(act_follow_node);
		while (a) {  /* look for act_follow_edge */
			if (AKANTE(a)==act_follow_edge) break;
			a = ANEXT(a);
		}
		if (a && ANEXT(a)) { 
			act_follow_edge = AKANTE(ANEXT(a));
			return;
		}
		break;
	case 2: a = NPRED(act_follow_node);
		while (a) { /* look for act_follow_edge */
			if (AKANTE(a)==act_follow_edge) break;
			a = ANEXT(a);
		}
		if (a && ANEXT(a)) { 
			act_follow_edge = AKANTE(ANEXT(a));
			return;
		}
		break;
	}

	/* Now, we have not found an act_follow_edge, or the
 	 * next edge in the same act_follow_state does not
	 * exist. Thus we must switch the act_follow_state.
	 */
	act_follow_edge = 0;
	while (!act_follow_edge) {
		if (follow_state==0) {
			a = NSUCC(act_follow_node);
			follow_state = 1;
			if (a) act_follow_edge = AKANTE(a);
		}
		else if (follow_state==1) {
			a = NPRED(act_follow_node);
			follow_state = 2;
			if (a) act_follow_edge = AKANTE(a);
		}
		else if (follow_state==2) {
			c = NCONNECT(act_follow_node);
			if ((c)&&(CEDGE2(c))) act_follow_edge = CEDGE2(c);
			follow_state = 3;
		}
		else if (follow_state==3) {
			c = NCONNECT(act_follow_node);
			if ((c)&&(CEDGE(c))) act_follow_edge = CEDGE(c);
			follow_state = 0;
			if ((c)&&(CEDGE(c))&&(NANCHORNODE(CTARGET(c)))) {
				act_follow_node = CTARGET(c);
				act_follow_edge = 0;
			}
			else if (NANCHORNODE(act_follow_node)) {
				act_follow_node = CTARGET(c);
				act_follow_edge = 0;
			}
		}
	}
}


/* Look for the target of edge e that starts at node v
 * ---------------------------------------------------
 * We get a real node as target, but not a dummy node
 * or a label.
 * Note: v and e must be visible.
 */

#ifdef ANSI_C
static GNODE search_target_node(GNODE v,GEDGE e)
#else
static GNODE search_target_node(v,e)
GNODE v;
GEDGE e;
#endif
{
	GNODE w,h;
	GEDGE e1;
	CONNECT c;

	assert((e));
	w = ESTART(e);
	if (w==v) w = EEND(e);

	last_follow_edge = e;

	/* check whether w is in the nodelist, i.e. a visible
	 * original node or graph summary node. 
	 */
	h = nodelist;
	while (h) { 
		if (h==w) break;
		h = NNEXT(h);
	}

	if (!h) { /* w is not in the nodelist. It must be a dummy
		   * node or a label.
		   */

		c = NCONNECT(w);
		if (c && (CEDGE(c))) {
			e1 = CEDGE(c);
			if (e1!=e) return(search_target_node(w,e1));
		}
		if (c && (CEDGE2(c))) {
			e1 = CEDGE2(c);
			if (e1!=e) return(search_target_node(w,e1));
		}
		/* dummy nodes and labels have maximal 2 successors */
		if (NSUCC(w)) {
			e1 = AKANTE(NSUCC(w));
			if (e1!=e) return(search_target_node(w,e1));
		}	
		if (NSUCC(w) && (ANEXT(NSUCC(w)))) {
			e1 = AKANTE(ANEXT(NSUCC(w)));
			if (e1!=e) return(search_target_node(w,e1));
		}	
		/* dummy nodes and labels have maximal 2 predecessors */
		if (NPRED(w)) {
			e1 = AKANTE(NPRED(w));
			if (e1!=e) return(search_target_node(w,e1));
		}	
		if (NPRED(w) && (ANEXT(NPRED(w)))) {
			e1 = AKANTE(ANEXT(NPRED(w)));
			if (e1!=e) return(search_target_node(w,e1));
		}	
	}
	return(w);
}


/* To speedup the follow edge operation, we use a special
 * drawing routine in x11_followedge_arrow that does not
 * draws to the buffer but to the window.
 * Thus, the window can be cleaned by simply refreshing it.
 */


#ifdef ANSI_C
void x11_followedge_line(int fx,int fy,int tx,int ty,int t,int c) 
#else
void x11_followedge_line(fx,fy,tx,ty,t,c) 
int fx,fy,tx,ty,t,c;
#endif
{
	int x1, y1, x2, y2, x3, y3, hx, hy, d;

	XSetForeground(root_display, pix_GC, carray[c]);
	XSetLineAttributes(root_display, pix_GC, (t>0?t-1:0),
                LineSolid, CapRound, JoinRound);
	x1 = fx-V_xmin - act_x_pos;
	y1 = fy-V_ymin - act_y_pos;
	x2 = tx-V_xmin - act_x_pos;
	y2 = ty-V_ymin - act_y_pos;

	if (fisheye_view != 0) {
		fe_g_to_s(fx, fy, &x1, &y1);
		x1 -= act_x_pos;
		y1 -= act_y_pos;
		fe_g_to_s(tx, ty, &x2, &y2);
		x2 -= act_x_pos;
		y2 -= act_y_pos;
		d = 1;
		while ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2) > 50*50) {
			hx = fx + d * (tx-fx)/7;
			hy = fy + d * (ty-fy)/7;
			fe_g_to_s(hx, hy, &x3, &y3);
			x3 -= act_x_pos;
			y3 -= act_y_pos;		
			XDrawLine(root_display, (Drawable)pix_window, 
				pix_GC, x1, y1, x3, y3);
			x1 = x3;
			y1 = y3;
			d++;
		}
	}
	
	XDrawLine(root_display, (Drawable)pix_window, pix_GC, x1, y1, x2, y2);
	/* XSync(root_display, 0); */
	XSetLineAttributes(root_display, pix_GC, 0, 
		LineSolid, CapRound, JoinRound);
}


/* Print the target of the follow_edge in the panel
 */

static char followedge_buf[30];

#ifdef ANSI_C
static void 	followedge_msg(char *a, char *b, char *c)
#else
static void 	followedge_msg(a, b, c)
char *a;
char *b;
char *c;
#endif
{
	char *cc;
	int i;
	GNODE v;

	panel_outp(a, b, c);
	if (!act_follow_node) return;
	if (!act_follow_edge) return;
	v = search_target_node(act_follow_node,act_follow_edge);
	if (!v) return; 
	cc = NLABEL(v);
	for (i=0; i<30; i++) {
		if (!*cc) break;
		followedge_buf[i] = *cc++;
		if (followedge_buf[i]=='\n') followedge_buf[i]='|';
		if (followedge_buf[i]=='\t') followedge_buf[i]=' ';
		if (followedge_buf[i]=='\r') followedge_buf[i]=' ';
		if (followedge_buf[i]=='\v') followedge_buf[i]=' ';
#ifdef ANSI_C
		if (followedge_buf[i]=='\a') followedge_buf[i]=' ';
#endif
		if (followedge_buf[i]=='\b') followedge_buf[i]=' ';
		if (followedge_buf[i]=='\f') followedge_buf[i]=' ';
	}
	if (i<30) followedge_buf[i] = 0;
	followedge_buf[26] = '.';
	followedge_buf[27] = '.';
	followedge_buf[28] = '.';
	followedge_buf[29] = 0;
 	panel_outp2("Press 'h' for history. Target: Title=",
			NTITLE(v)," Label=",followedge_buf);
}



/* Scale Menu Handler
 * ==================
 */

#ifdef ANSI_C
static void 	handle_scale_menu(int item)
#else
static void 	handle_scale_menu(item)
int item;
#endif
{
	switch(item) {
	case 1: /* normal */
		set_fe_scaling(1, 1);
		break;
	case 2: /* "400 %" */
		change_fe_scaling(4, 1);
		break;
	case 3: /* "200 %" */
		change_fe_scaling(2, 1);
		break;
	case 4: /* "150 %" */
		change_fe_scaling(3, 2);
		break;
	case 5: /* "90 %" */
		change_fe_scaling(9, 10);
		break;
	case 6: /* "80 %" */
		change_fe_scaling(8, 10);
		break;
	case 7: /* "70 %" */
		change_fe_scaling(7, 10);
		break;
	case 8: /* "60 %" */
		change_fe_scaling(6, 10);
		break;
	case 9: /* "50 %" */
		change_fe_scaling(1, 2);
		break;
	case 10: /* "25 %" */
		change_fe_scaling(1, 4);
		break;
	}

	new_scale_fontbuffers(G_stretch,G_shrink);
	position_abs_scrollbars();
	disable_signal(); 
        displayCanvas(); 
        enable_signal();
}


/* Export Menu Handler
 * ===================
 */


#ifdef ANSI_C
static void 	handle_export_menu(int item)
#else
static void 	handle_export_menu(item)
int item;
#endif
{
	if ((item==4)&&(G_spline)) item=5;

	switch(item) {
	case 1: /* "Load" */
		load_save_flag = LS_LOAD;
		clear_panel();
		m_loadsave();
		return;
	case 2: /* "Reload" */
		m_reload();
		return;
	case 3:	/* "Save to file" */
		load_save_flag=LS_SAVEASCII;
		m_loadsave();	
		return;
	case 4:	/* "Export part" */
		m_fetch_region(0);	
		if (!reg_there) break;
		x11_print_dialog(reg_minx, reg_miny, reg_maxx, reg_maxy);
		switch (act_output_type) { 
		case 0:
			panel_outp("Cancelled !\n","","");
			reset_menues();
			return;
		case 1: load_save_flag=LS_SAVEPPM;
			break;
		case 2: load_save_flag=LS_SAVEPPM;
			break;
		case 3: load_save_flag=LS_SAVEPS;
			break;
		}
		m_loadsave();
		return;
	case 5:	/* "Export full graph" */
		reg_minx = reg_miny = 0;
		reg_maxx = maximal_xpos + G_xbase; 
		reg_maxy = maximal_ypos + G_ybase; 
		reg_there = 1;
		x11_print_dialog(reg_minx, reg_miny, reg_maxx, reg_maxy);
		switch (act_output_type) { 
		case 0:
			panel_outp("Cancelled !\n","","");
			reset_menues();
			return;
		case 1: load_save_flag=LS_SAVEPPM;
			break;
		case 2: load_save_flag=LS_SAVEPPM;
			break;
		case 3: load_save_flag=LS_SAVEPS;
			break;
		}
		m_loadsave();
		return;
	}
	position_abs_scrollbars();
	disable_signal(); 
        displayCanvas(); 
        enable_signal();
}


/*  Fetch a region to by a rubber band
 *  ----------------------------------
 *  The result is in region_[min|max][x|y].
 */

#ifdef ANSI_C
static void m_fetch_region(int mode)
#else
static void m_fetch_region(mode)
int mode;
#endif
{
	int notready, old_cursor, rubberthere;
	XEvent  event;
	int sx,sy,tx,ty;

	reg_there = 1;
	reg_minx = reg_miny = reg_maxx = reg_maxy = 0;

	if (mode==1) {
	    	panel_outp("Select next position/region by a rubberband. ",
		   	   "Right button to cancel.","");
	}
	else	panel_outp("Select a region by a rubberband. ",
		   	   "Right mouse button to cancel.","");

	old_cursor = act_cursor;
	set_fold_cursor();
	notready = 1;
	rubberthere = 0;

	while (notready) {

		XNextEvent (root_display, &event);

		switch (event.type) {
	  	case ButtonPress:
	    		prologue (&event, "ButtonPress");
			if (which_button(&event)==G_MOUSE_LEFT) {
				if (!rubberthere) {
					rubberthere = 1;
					reg_minx = (button_x+V_xmin)
							*G_shrink/G_stretch;
					reg_miny = (button_y+V_ymin)
							*G_shrink/G_stretch;
				        panel_outp(
             				    "Select a region by a rubberband. ",
		   			    "Right mouse button to retry.","");
				}
			}
			else if (which_button(&event)==G_MOUSE_RIGHT) {
				if (!rubberthere) {
					reg_minx = reg_miny = 
					reg_maxx = reg_maxy = 0;
					reg_there = 0;
					notready = 0; 
				}
				else {
				       panel_outp(
             				    "Select a region by a rubberband. ",
		   			    "Right mouse button to cancel.","");
					rubberthere = 0;
					reg_minx = reg_miny = 
					reg_maxx = reg_maxy = 0;
				}
			}	
	    		break;
	  	case MotionNotify:
	    		prologue (&event, "MotionNotify");
			if (((XMotionEvent *)(&event))->window==pix_window) {
				if (fisheye_view==0) {
					sx = reg_minx*G_stretch/G_shrink
						-V_xmin-act_x_pos;
					sy = reg_miny*G_stretch/G_shrink
						-V_ymin-act_y_pos;
				}
				else {  fe_g_to_s(reg_minx,reg_miny,&sx, &sy);
					sx -= act_x_pos;
					sy -= act_y_pos;		
				}
				tx = ((XMotionEvent *)(&event))->x;
				ty = ((XMotionEvent *)(&event))->y;
				if (rubberthere) draw_rubberband(sx,sy,tx,ty);
				else draw_rubberband(0,0,0,0);
			}
			break;
	  	case ButtonRelease:
	    		prologue (&event, "ButtonRelease");
			if (which_button(&event)==G_MOUSE_LEFT) {
				if (rubberthere) {
					reg_maxx = (button_x+V_xmin)
							*G_shrink/G_stretch;
					reg_maxy = (button_y+V_ymin)
							*G_shrink/G_stretch;
					if (fisheye_view == 0) {
						sx = reg_minx*G_stretch/G_shrink
							-V_xmin-act_x_pos;
						sy = reg_miny*G_stretch/G_shrink
							-V_ymin-act_y_pos;
						tx = reg_maxx*G_stretch/G_shrink
							-V_xmin-act_x_pos;
						ty = reg_maxy*G_stretch/G_shrink
							-V_ymin-act_y_pos;
					}
					else {  fe_g_to_s(reg_minx,reg_miny,
								&sx, &sy);
						sx -= act_x_pos;
						sy -= act_y_pos;		
					        fe_g_to_s(reg_maxx,reg_maxy,
								&tx, &ty);
						tx -= act_x_pos;
						ty -= act_y_pos;		
					}
					draw_rubberband(sx,sy,tx,ty);
					notready = 0;
				}
			}
			break;
		default:
			if (esc_handler(&event)) {
				if (!rubberthere) {
					reg_minx = reg_miny = 
					reg_maxx = reg_maxy = 0;
					reg_there = 0;
					notready = 0; 
				}
				else {
				       panel_outp(
             				    "Select a region by a rubberband. ",
		   			    "Right mouse button to cancel.","");
					rubberthere = 0;
					reg_minx = reg_miny = 
					reg_maxx = reg_maxy = 0;
				}
			}
			else default_handler(&event);
	    		break;
		}
    	}

	act_cursor = old_cursor;
 	reset_cursor();
	clear_panel();
	show_buffer();
}



#ifdef ANSI_C
static void draw_rubberband(int a,int b,int c,int d)
#else
static void draw_rubberband(a,b,c,d)
int a,b,c,d;
#endif
{
	if (no_buffer) return;
 
	ask_window_size(frame_window);
       	XCopyArea(root_display,
        	pix_dw,
            	pix_window,
               	pix_GC,
               	act_x_pos, act_y_pos,
		window_width  - PIXW_XOFFSET,
		window_height - PIXW_YOFFSET,
               	0, 0
       	);
	if ((G_color == BLACK) && (colored))
		XSetForeground(root_display, pix_GC, carray[WHITE]);
	else	XSetForeground(root_display, pix_GC, carray[BLACK]);

	XDrawLine(root_display, (Drawable)pix_window, pix_GC, a,b, c,b);
	XDrawLine(root_display, (Drawable)pix_window, pix_GC, c,b, c,d);
	XDrawLine(root_display, (Drawable)pix_window, pix_GC, c,d, a,d);
	XDrawLine(root_display, (Drawable)pix_window, pix_GC, a,d, a,b);
}



/* Load/Save a file 
 * ================
 */

static char fbuf[1024];

#ifdef ANSI_C
static void	m_loadsave(void)
#else
static void	m_loadsave()
#endif
{
	char	*name;
	int old_cursor,success,pos;


	pos = 18;
	success = 0;
	old_cursor = act_cursor;
	while (!success) {
		set_busy_cursor();
		name = x11_print_fisel_dialog();
		if (!name) break;
		*fbuf = 0;
		if (name) strcpy(fbuf, name);
	
		disable_signal(); 

		success = 1;
		if (load_save_flag==LS_LOAD) {
			strcpy(Dataname, fbuf);
	
			success = is_readeable(Dataname);
	
			if (success) {
				clear_hide_class();
				parse_part();
				visualize_part();
				init_fe(0,300,0,300,200,200);
				resizeWindow(); 
			}
		}
		else if (load_save_flag==LS_SAVEASCII) {
			success = is_writable(fbuf);
			if (success && (!print_graph(fbuf))) {
				panel_outp("Error on writing file. ",
					   "File may exist or is unwriteable.",""); 
				success = 0;
			}
		}
		else if (load_save_flag==LS_SAVEPPM) {
			success = is_writable(fbuf);
			if (success) 
				(void)print_pbm_or_ppm(fbuf,reg_minx,reg_miny,
						       	    reg_maxx, reg_maxy);
		}
		else if (load_save_flag==LS_SAVEPS) {
			success = is_writable(fbuf);
			if (success) print_all_ps(fbuf, reg_minx, reg_miny, 
							reg_maxx, reg_maxy); 
		}
		pos = 36;
	}
	position_abs_scrollbars();
       	if (success) displayCanvas(); 
	act_cursor = old_cursor;
 	reset_cursor();
       	enable_signal();
}


/* Reload the same file
 * ====================
 */

#ifdef ANSI_C
void	m_reload(void)
#else
void	m_reload()
#endif
{
	int old_cursor,success;

	success = is_readeable(Dataname);
	if (!success) return; 

	old_cursor = act_cursor;
	set_busy_cursor();
	disable_signal(); 
	clear_hide_class();
	parse_part();
	visualize_part();
	init_fe(0,300,0,300,200,200);
	resizeWindow(); 
	position_abs_scrollbars();
        displayCanvas(); 
	act_cursor = old_cursor;
 	reset_cursor();
        enable_signal();
}


/* Auxiliaries for load and save procedures
 * ----------------------------------------
 */


/* Check whether file is readable.
 * Returns 1 if yes. Opens file stream fp.  
 */

#ifdef ANSI_C
static int is_readeable(char *fname)
#else
static int is_readeable(fname)
char *fname;
#endif
{
	FILE *f;
	char *c;

	f = NULL;
	c = fname;
	while (*c) c++;
	if (c>fname) c--;
#ifdef VMS
	if (*c==']') {
#else
	if (*c=='/') {
#endif
		panel_outp("Illegal filename.","",""); 
		reset_menues(); 
		return(0);
	}
       	if (( strcmp(fname,"-")==0 ) || (*fname==0)) { 
		panel_outp("Illegal filename.","",""); 
		reset_menues(); 
		return(0);
	}
       	f = fopen(fname,"r");
       	if (f == NULL) { 
		panel_outp("Cannot open file '",fname,"'."); 
		reset_menues(); 
		return(0);
	}
	else fclose(f);
	return(1);
}


/* Check whether file is writable.
 * Returns 1 if yes. Opens file stream fp.  
 */

#ifdef ANSI_C
static int is_writable(char *fname)
#else
static int is_writable(fname)
char *fname;
#endif
{
	FILE *f;
	char *c;

	f = NULL;
	c = fname;
	while (*c) c++;
	if (c>fname) c--;
#ifdef VMS
	if (*c==']') {
#else
	if (*c=='/') {
#endif
		panel_outp("Illegal filename.","",""); 
		reset_menues(); 
		return(0);
	}
       	if (( strcmp(fname,"-")==0 ) || (*fname==0)) { 
		panel_outp("Illegal filename.","",""); 
		reset_menues(); 
		return(0);
	}
       	f = fopen(fname,"r");
       	if (f != NULL) { 
		panel_outp("Error on writing file. ",
			   "File may exist or is unwriteable.",""); 
		reset_menues(); 
		fclose(f);
		return(0);
	}
	return(1);
}


/*--------------------------------------------------------------------*/


/* Handle fisheye mode selection
 * =============================
 */

#ifdef ANSI_C
void m_validate_fe()
#else
void m_validate_fe()
#endif
{
	long h;

	h = gfishdist;
	ask_window_size(frame_window);
	init_fe(0,window_width-PIXW_XOFFSET,
		0,window_height-PIXW_YOFFSET,200,200);
	set_gfishdist(h);
	position_nor_scrollbars();
        position_abs_scrollbars();
	disable_signal();
        buildCanvas();
        enable_signal();
        gs_hide_all_menus();
}

/*--------------------------------------------------------------------*/


/* Default Event Handler
 * =====================
 * This handler manages the absolutely basic events like resize of
 * windows, expose, or the minimal keyboard events.
 */

#ifdef ANSI_C
static void default_handler(XEvent *event)
#else
static void default_handler(event)
XEvent *event;
#endif
{
	switch (event->type) {
	  case KeyPress:
	  	prologue (event, "KeyPress");
	    	do_minimalKeyPress (event);
	    	break;
	  case Expose:
	  	prologue (event, "Expose");
	    	do_Expose (event);
	    	break;
	  case ConfigureNotify:
	  	prologue (event, "ConfigureNotify");
	    	do_gblConfigureNotify (event);
	    	break;
	}
}


/* Esc Event Handler
 * =================
 * Return 1 if ESC was pressed.
 */

#ifdef ANSI_C
static int esc_handler(XEvent *event)
#else
static int esc_handler(event)
XEvent *event;
#endif
{
	char mkeys[4];

	mkeys[0]=27;
	mkeys[1]='q';
	mkeys[2]='Q';
	mkeys[3]=0;
	return(gkey_handler(event,mkeys));
}


/* General key handler 
 * ===================
 * Return 1 if the key was pressed.
 */

#ifdef ANSI_C
static int gkey_handler(XEvent *event, char *z)
#else
static int gkey_handler(event, z)
XEvent *event;
char *z;
#endif
{
    	XKeyEvent *e = (XKeyEvent *) event;
    	KeySym ks;
    	int nbytes;
    	char str[256+1];

	switch (event->type) {
	case KeyPress:
	  	prologue (event, "KeyPress");
    		nbytes = XLookupString (e, str, 256, &ks, NULL);
    		if (nbytes < 0) nbytes = 0;
    		if (nbytes > 256) nbytes = 256;
    		str[nbytes] = '\0';

		if (nbytes==1) {
			while (*z) {
				if (str[0]== *z) return(1);   
				else z++;
			}
		}
	}
	return(0);
}



/*--------------------------------------------------------------------*/
/*  Node selection handler                                            */
/*--------------------------------------------------------------------*/

/* Handle selection of nodes
 * -------------------------
 * If a node was selected, it is added to the folding keepers.
 * Depending whether the node was a folding keeper before, it is now
 * one ore not. Thus we must redisplay the node and notify the
 * selection.
 */

#ifdef ANSI_C
static void handle_selected_node(GNODE v)
#else
static void handle_selected_node(v)
GNODE v;
#endif
{
        gs_setshrink(G_stretch * NSTRETCH(v),
       		     G_shrink  * NSHRINK(v)  );
       	gs_setto(NX(v) * G_stretch / G_shrink,
       	         NY(v) * G_stretch / G_shrink );
	draw_one_node(v);
	show_buffer();
	selected_flag = 1;
	panel_outp("Next node ... (right mouse button to continue).","","");
}


/* Finish the selection
 * --------------------
 * If something was selected, the selected_flag is true. Then, we must
 * relayout. Otherwise, we only must reinstall the main menu.
 */

#ifdef ANSI_C
static void finish_selection(void)
#else
static void finish_selection()
#endif
{
	clear_panel();
	if (selected_flag==1) complete_relayout();
	else { 	clear_folding_keepers();
		position_abs_scrollbars();
		if (selected_flag== -1) buildCanvas();
		reset_menues(); 
	}
	selected_flag = 0;
}


/*  Reinit the main menu of the canvas
 *  ==================================
 *  After building the canvas, we reinitialize the main menu procedure
 *  of the canvas. For security reason, because some event handling
 *  use own canvas selection procedures. 
 */

#ifdef ANSI_C
static void	reset_menues(void)
#else
static void	reset_menues()
#endif
{
	if (act_revert_node)
		NREVERT(act_revert_node) = 0;
 	reset_cursor();
}

/* Relayout and display the new graph
 * ----------------------------------
 * If after folding, a complete relayout is necessary, we start here.
 */

#ifdef ANSI_C
static void complete_relayout(void)
#else
static void complete_relayout()
#endif
{
	int old_cursor;

	old_cursor = act_cursor;
	set_busy_cursor();
	disable_signal();
	relayout();
	init_fe(0,0,0,0,200,200);
	position_abs_scrollbars();
	displayCanvas();
	act_cursor = old_cursor;
 	reset_cursor();
	enable_signal();
}


/*--------------------------------------------------------------------*/

#endif /* X11 */

