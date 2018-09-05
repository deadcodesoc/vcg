/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */
/*		--------------------------------------		      */
/*								      */
/*   file:	   sunvdev.c					      */
/*   version:	   1.00.00					      */
/*   creation:	   9.4.93					      */
/*   author:	   I. Lemke  (...-Version 0.99.99)		      */
/*		   G. Sander (Version 1.00.00-...)		      */
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */
/*   description:  Device driver for Sunview			      */
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/

#ifndef lint
static char *id_string="$Id: sunvdev.c,v 3.5 1995/02/08 11:11:14 sander Exp $";
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
 * $Log: sunvdev.c,v $
 * Revision 3.5  1995/02/08  11:11:14  sander
 * Distribution version 1.3.
 *
 * Revision 3.4  1994/12/23  18:12:45  sander
 * Manhatten layout added.
 * Option interface cleared.
 * infobox behaviour improved.
 * First version of fisheye (carthesian).
 * Options Noedge and nonode.
 *
 * Revision 3.3  1994/05/16  08:56:03  sander
 * shape attribute (boxes, rhombs, ellipses, triangles) added.
 *
 * Revision 3.2  1994/04/27  16:05:19  sander
 * Minor changes.
 *
 * Revision 3.1  1994/03/01  10:59:55  sander
 * Copyright and Gnu Licence message added.
 * Problem with "nearedges: no" and "selfloops" solved.
 *
 * Revision 2.6  1994/02/14  11:03:24  sander
 * Menu point `Node Information -> Statistics' added.
 * It is now possible to get a statistics of the visibility
 * of nodes and edges.
 *
 * Revision 2.5  1994/01/21  19:33:46  sander
 * VCG Version tested on Silicon Graphics IRIX, IBM R6000 AIX and Sun 3/60.
 * Option handling improved. Option -grabinputfocus installed.
 * X11 Font selection scheme implemented. The user can now select a font
 * during installation.
 * Sun K&R C (a nonansi compiler) tested. Some portabitility problems solved.
 *
 * Revision 2.4  1994/01/10  09:22:52  sander
 * Distribution version 1.
 *
 * Revision 2.3  1994/01/03  15:29:06  sander
 * First complete X11 version.
 *
 */

/************************************************************************
 * Device driver for Sunview
 * -------------------------
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

#ifdef SUNVIEW

#include <sun/fbio.h>
#include <sys/ioccom.h>
#include <suntool/sunview.h>
#include <suntool/icon.h>
#include <suntool/canvas.h>
#include <suntool/panel.h>
#include <pixrect/pr_line.h>
#include <fcntl.h>
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

/*--------------------------------------------------------------------*/

/* Prototypes
 * ----------
 */

void display_part	_PP((void));
void setScreenSpecifics	_PP((void));
void gs_exit		_PP((int x));
void gs_line		_PP((int fx,int fy,int tx,int ty,int c));
void gs_rectangle	_PP((int x,int y,int w,int h,int c));
void gs_open		_PP((void));
void gs_close		_PP((void));

void	InitDevice		_PP((void));

static void	ExitDevice		_PP((void));
static void 	setColormap		_PP((void));
static void	allocateFrame		_PP((void));
static void	allocateMyPixwin	_PP((void));
static void	allocateMyPanel		_PP((void));
static void	resizeWindow		_PP((void));
static void	frame_resize_proc	_PP((Frame frame, Event *event));
static void	displayCanvas		_PP((void));
static void	buildCanvas		_PP((void));

static void set_normal_cursor		_PP((void));
static void set_busy_cursor		_PP((void));
static void set_select_cursor		_PP((void));
static void set_fold_cursor		_PP((void));

static void 	normalize_scaling	_PP((void));
static void	main_menu_check	_PP((void));
static void 	panel_outp	_PP((char *x));
static char 	*int_to_str		_PP((int n));
static char 	*class_num 		_PP((int n));
static char 	*act_info_num		_PP((int n));
static void 	check_keyboard_event		_PP((Event *event));
static void 	check_minimalkeyboard_event	_PP((Event *event));
static void	myCanvas_event_proc		_PP((Canvas myCanvas, Event *event));
static GNODE 	search_target_node		_PP((GNODE v,GEDGE e));
static void 	next_follow_edge		_PP((void));
static void	follow_edge_event_proc		_PP((Canvas myCanvas, Event *event));
static void	follow_nextedge_event_proc	_PP((Canvas myCanvas, Event *event));
static void	follow_centeredge_event_proc   	_PP((Canvas myCanvas, Event *event));
static void	fold_subgraph_event_proc	_PP((Canvas myCanvas, Event *event));
static void	unfold_subgraph_event_proc	_PP((Canvas myCanvas, Event *event));
static void	select_foldstops_proc		_PP((Canvas myCanvas, Event *event));
static void	select_info_proc		_PP((Canvas myCanvas, Event *event));
static void	fold_region_proc		_PP((Canvas myCanvas, Event *event));
static void	unfold_region_proc		_PP((Canvas myCanvas, Event *event));
static void	pic_position_proc		_PP((Canvas myCanvas, Event *event));
static void	menu_proc			_PP((Menu m, Menu_item mi));
static void	info_proc			_PP((Menu m, Menu_item mi));
static void	hide_class_proc			_PP((Menu m, Menu_item mi));
static void	expose_class_proc		_PP((Menu m, Menu_item mi));
static void	fold_class_proc			_PP((Menu m, Menu_item mi));
static void	scroll_proc			_PP((Menu m, Menu_item mi));
static void	save_proc			_PP((Menu m, Menu_item mi));
static void	lab_on_off_proc			_PP((Menu m, Menu_item mi));
static void	rul_on_off_proc			_PP((Menu m, Menu_item mi));
static void	scale_proc			_PP((Menu m, Menu_item mi));
static void	node_title_proc			_PP((Panel_item item, Event *event));
static void	load_proc			_PP((Panel_item item, Event *event));
static void	x_proc				_PP((Panel_item item, Event *event));
static void	y_proc				_PP((Panel_item item, Event *event));
static void	createMenu			_PP((void));
static void	m_fold_subgraph			_PP((void));
static void	m_unfold_subgraph		_PP((void));
static void	m_hide_edges			_PP((Menu_item mi));
static void	m_expose_edges			_PP((Menu_item mi));
static void	m_fold_region			_PP((Menu_item mi));
static void	m_unfold_region			_PP((Menu_item mi));
static void	m_position			_PP((void));
static void	m_center_node			_PP((void));
static void	m_follow_edge			_PP((void));
static void	m_pic_position			_PP((void));
static void	m_ask_size			_PP((void));
static void	ask_scale			_PP((Panel_item	item, Event *event));
static void	ask_filename			_PP((Panel_item	item, Event *event));
static void	m_load				_PP((void));
void		m_reload			_PP((void));
static Menu	gen_lab_on_off_proc		_PP((Menu m, Menu_generate op));
static Menu	gen_rul_on_off_proc		_PP((Menu m, Menu_generate op));
static Menu	gen_hide_class_proc	    	_PP((Menu m, Menu_generate op));
static Menu	gen_expose_class_proc	    	_PP((Menu m, Menu_generate op));

static void	ruler_paint				_PP((void));
static void	set_upper_ruler				_PP((void));
static void	set_lower_ruler				_PP((void));
static void	set_left_ruler				_PP((void));
static void	set_right_ruler				_PP((void));
static void	set_h_scale				_PP((int w, int h));
static void	set_v_scale				_PP((int w, int h));
static void	set_value				_PP((int x, int y, char *s));

static void 	finish_selection	_PP((void));
static void 	handle_selected_node	_PP((GNODE v));

static void     suntextout              _PP((int y,char *msg));
static void     suninttextout           _PP((int y,char *msg,int i));
static void 	show_statistics		_PP((void));



/* Defines
 * -------
 * The horizontal and vertical size of a scrollbar. These are
 * experimental values.
 */

#define H_SCROLLBAR	23
#define V_SCROLLBAR	10


/* The draw mode of the curser */

#define CURSORMODE  (PIX_SRC ^ PIX_DST)

/* Variables
 * ---------
 */

/* the VCG icon */

unsigned short icon_image[] = { 
/* Format_version=1, Width=64, Height=64, Depth=1, Valid_bits_per_item=16
 */
	0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
        0xC000,0x0000,0x0000,0x0003,0xC010,0x0000,0x0000,0x0003,
        0xC010,0x0000,0x0000,0x8003,0xC010,0x0000,0x0000,0x8003,
        0xC010,0x0000,0x0000,0x8003,0xC010,0x0000,0x0000,0x8003,
        0xC010,0x0000,0x0000,0x8003,0xC010,0x0000,0x0000,0x8003,
        0xC010,0x0000,0x0000,0x8003,0xDFFF,0xF000,0x00FF,0xFF83,
        0xD000,0x1000,0x0080,0x0083,0xD000,0x1000,0x0080,0x0083,
        0xD000,0x1000,0x0080,0x0083,0xD084,0x1000,0x0082,0x2083,
        0xD008,0x1000,0x0080,0x4083,0xD0AA,0x1000,0x008C,0x4883,
        0xD000,0x1000,0x0080,0x8083,0xD000,0x1000,0x0080,0x0083,
        0xD000,0x1000,0x0080,0x0083,0xDFFF,0xF000,0x0080,0x0083,
        0xC007,0x0000,0x00FF,0xFF83,0xC000,0xE000,0x000F,0x0003,
        0xC000,0x1E00,0x0070,0x0003,0xC000,0x01C0,0x0380,0x0003,
        0xC000,0x0038,0x3C00,0x0003,0xC000,0x0006,0x6000,0x0003,
        0xC000,0x02AA,0xAAA0,0x0003,0xC000,0x0400,0x0010,0x0003,
        0xC000,0x0000,0x0000,0x0003,0xC000,0x0402,0x0010,0x0003,
        0xC000,0x0010,0x2000,0x0003,0xC000,0x0421,0x1210,0x0003,
        0xC000,0x0004,0x1400,0x0003,0xC000,0x0400,0x0010,0x0003,
        0xC000,0x0000,0x0000,0x0003,0xC000,0x0400,0x0010,0x0003,
        0xC000,0x02AA,0xAAA0,0x0003,0xC000,0x0006,0x0000,0x0003,
        0xC000,0x0018,0x0000,0x0003,0xC000,0x0000,0x0000,0x0003,
        0xC000,0x0000,0x0000,0x0003,0xC000,0x00E0,0xE0FC,0x0FC3,
        0xC000,0x0C60,0x4106,0x1063,0xC000,0x1030,0x8202,0x2023,
        0xC01F,0xFF30,0x8200,0x2003,0xC010,0x0030,0x8600,0x6003,
        0xC010,0x0019,0x0600,0x6003,0xC010,0x1019,0x0600,0x6003,
        0xC011,0x0019,0x0600,0x6003,0xC010,0x480C,0x0600,0x61F3,
        0xC010,0x840E,0x0600,0x6063,0xC010,0x000E,0x0200,0x2063,
        0xC010,0x0004,0x0302,0x3063,0xC010,0x0004,0x0184,0x1863,
        0xC01F,0xFF04,0x00F8,0x0F83,0xC000,0x0000,0x0000,0x0003,
        0xC000,0x0000,0x0000,0x0003,0xC000,0x0000,0x0000,0x0003,
        0xC000,0x0000,0x0000,0x0003,0xC000,0x0000,0x0000,0x0003,
        0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF
};
mpr_static(icon_pr, 64, 64, 1, icon_image);

/* the windows */

static Frame		frame;
static Icon		vcg_icon;
static Canvas		myCanvas;
static Pixwin		*myPixwin;
static Panel		myPanel;
static Panel_item	message_item, text1_item, text2_item;

/* the cursors */

static Cursor standard_cursor;     /* Remembered old cursor        */
static Cursor workingCursor;	   /* If the tool is busy          */
static Cursor selectCursor;	   /* If a node should be selected */ 
static Cursor foldCursor;	   /* If a node should be folded   */ 

short workingCursorData[] = {
	0x7FFE,0x4002,0x200C,0x1A38,0x0FF0,0x07E0,0x03C0,0x0180,
	0x0180,0x0240,0x0520,0x0810,0x1108,0x23C4,0x47E2,0x7FFE
};
mpr_static(workingCursorPixrect, 16, 16, 1, workingCursorData);

short selectCursorData[] = {
	0x0F00,0x30C0,0x4020,0x4020,0x8010,0x8610,0x8610,0x8010,
	0x4020,0x4020,0x30C0,0x0F00,0x0000,0x0000,0x0000,0x0000
};
mpr_static(selectCursorPixrect, 16, 16, 1, selectCursorData);

short foldCursorData[] = {
	0x0000, 0x03E0, 0x0C18, 0x1004, 0x2006, 0x201A, 0x4021, 0x40C1,
	0x4101, 0x4201, 0x4C01, 0x3002, 0x2002, 0x1004, 0x0C18, 0x03E0
};
mpr_static(foldCursorPixrect, 16, 16, 1, foldCursorData);

static short arrowCursorData[] = {
        0x0000, 0x7fe0, 0x7f80, 0x7e00, 0x7e00, 0x7f00, 0x7f80, 0x67c0,
        0x63e0, 0x41f0, 0x40f8, 0x007c, 0x003e, 0x001f, 0x000e, 0x0004
};
mpr_static_static(arrowCursorPixrect, 16, 16, 1, arrowCursorData);


/* the menu's */

static Menu		menu, on_off_menu1, on_off_menu2;
static Menu		class_menu1, class_menu2, class_menu3;
static Menu		scroll_menu, scale_menu, info_menu;
static Menu		save_menu;

/* this flag indicates whether the panel is already available
 * for output.
 */

static int panel_there = 0;

/* this counter is used to generate a message that the user 
 * should wait.
 */

static int waitcnt=0;

/* this flag indicates whether the ruler should be drawn.
 */

static int		V_ruler = 0;

/* Flag, whether the device is already initialized */

static int device_there = 0;

/* Flag to select which info is needed about a node */

static int info_val;
static int truesize;

static int load_save;

#define LS_LOAD      0
#define LS_SAVEASCII 1
#define LS_SAVEPBM   2
#define LS_SAVEPPM   3

/*--------------------------------------------------------------------*/
/*  Check the screen device                                           */
/*--------------------------------------------------------------------*/

/* We look into the frame buffer: how many colors are available?
 * What is the size of the framebuffer?
 * maxDepth, ScreenWidth, ScreenHeight are set according to this.
 * G_width and G_height are preinitialized with appropriate values.
 */

/*
 * static Pixfont *font;
 */

void setScreenSpecifics()
{
	struct fbtype	FbType;
	int		Fb;    
 
	Fb = open("/dev/fb", O_RDONLY, 0);
   
	if (Fb < 0) {
		perror("open");
		FPRINTF(stderr,"Unable to open /dev/fb\n");
		gs_exit(1);
	}
	if (ioctl(Fb, FBIOGTYPE, &FbType) == -1) {
		perror("ioctl");
		FPRINTF(stderr,"Unable to determine screen size\n");
		gs_exit(1);
	}
	maxDepth	= FbType.fb_depth;
	ScreenWidth	= FbType.fb_width;
	G_width 	= ScreenWidth-V_SCROLLBAR;
	ScreenHeight	= FbType.fb_height;
	G_height	= ScreenHeight-COFFSET-H_SCROLLBAR;	
	close(Fb);

/*
 *	font = pf_open("/usr/lib/fonts/fixedwidthfonts/screen.r.16");
 */
}



/*--------------------------------------------------------------------*/
/*  Drawing primitives                                                */
/*--------------------------------------------------------------------*/

/* Draw a line
 * -----------
 * from fx,fy to tx,ty with color c.
 */

void	gs_line(fx, fy, tx, ty, c)
int	fx, fy, tx, ty, c;
{
	 pw_vector(myPixwin, fx-V_xmin,fy-V_ymin,tx-V_xmin,ty-V_ymin,
		   (PIX_SRC | PIX_COLOR(COLOR(c))), c);
}

/* Draw a rectangle
 * ----------------
 * at (x,y) with width w, height h and color c
 */

void 	gs_rectangle(x, y, w, h, c)
int	x, y, w, h, c;
{
	pw_writebackground(myPixwin, 
		x-V_xmin, y-V_ymin, w, h, (PIX_SRC | PIX_COLOR(COLOR(c))));
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

void	display_part()
{
	/* semaphore: we come only once to here */
	if (not_firstcall) return;
	not_firstcall = 1;

	/* first: initialize the device */

	InitDevice();
	displayCanvas();
	enable_signal();
	touch_specification();

	/* Now we go into the interaction main loop */
	window_main_loop(frame);

	ExitDevice();
}

#ifdef DRAWDEBUG
void	debug_display_part()
{
	displayCanvas();
	enable_signal();
	touch_specification();
}
#endif

/* Initialize the device 
 * ---------------------
 */

void 	InitDevice()
{
	/* first: initialize the device */

	if (device_there) return;
	device_there = 1;

	allocateFrame();
	allocateMyPixwin();
	allocateMyPanel();
	if (colored) setColormap();
	window_fit(frame);
	createMenu();

	notify_no_dispatch();
	window_set(frame,
		WIN_SHOW,	TRUE,
		0);
	window_set(myPanel,
		WIN_SHOW,	TRUE,
		0);
	window_set(myCanvas,
		WIN_SHOW,   	TRUE,
		WIN_IGNORE_PICK_EVENT,	LOC_MOVE,
		WIN_IGNORE_PICK_EVENT, 	WIN_MOUSE_BUTTONS,
		WIN_IGNORE_KBD_EVENT,   WIN_TOP_KEYS,
		WIN_IGNORE_KBD_EVENT,   WIN_RIGHT_KEYS,
		WIN_IGNORE_KBD_EVENT,  WIN_LEFT_KEYS,
		WIN_IGNORE_KBD_EVENT,  WIN_ASCII_EVENTS,
		0);
	set_busy_cursor();
	notify_do_dispatch();
}

/* Exit the device
 * ---------------
 * It is enough to deallocate the root frame, because all its 
 * childs are deallocated automatically.
 */

static void	ExitDevice()
{
	if (!device_there) return;
	window_set(frame, FRAME_NO_CONFIRM, TRUE, 0);
	window_destroy(frame);
}


/* Exit all
 * --------
 */

void	gs_exit(x)
int x;
{
	if (device_there) ExitDevice();
	PRINTF("\n");
	exit(x);
}


/* Set the colormap
 * ----------------
 */

static void setColormap()
{
	pw_setcmsname(myPixwin, "draw");
	pw_putcolormap(myPixwin, 0, CMAPSIZE, redmap, greenmap, bluemap);
}


/*--------------------------------------------------------------------*/
/*  Window allocation funtions                                        */
/*--------------------------------------------------------------------*/

/* Allocate root frame
 * -------------------
 * The root frame contains all other display objects.
 */

static void	allocateFrame()
{
	int x,y;

	x = y = 0;
	if (G_x!= -1) x = G_x;
	if (G_y!= -1) y = G_y;
	vcg_icon = icon_create(ICON_IMAGE, &icon_pr, 0);   /* Create icon. */

	frame = window_create(NULL, FRAME,
			WIN_EVENT_PROC, 		frame_resize_proc,   
			FRAME_DONE_PROC,		ExitDevice,
			FRAME_SUBWINDOWS_ADJUSTABLE,	TRUE,
			WIN_X,				x,
			WIN_Y,				y,
			WIN_WIDTH,			G_width+V_SCROLLBAR,
			WIN_HEIGHT,			G_height+COFFSET+H_SCROLLBAR,
			FRAME_ICON,			vcg_icon,
			0);

	if (frame == NULL) Fatal_error("Unable to create window","");

	standard_cursor = cursor_create(CURSOR_IMAGE, &arrowCursorPixrect,
                                CURSOR_OP, CURSORMODE, 0);
	selectCursor  = cursor_create(CURSOR_IMAGE, &selectCursorPixrect,
                                CURSOR_OP, CURSORMODE, 0);
	foldCursor    = cursor_create(CURSOR_IMAGE, &foldCursorPixrect,
                                CURSOR_OP, CURSORMODE, 0);
	workingCursor = cursor_create(CURSOR_IMAGE, &workingCursorPixrect,
                                CURSOR_OP, CURSORMODE, 0);
}



/* Allocate PixWindow 
 * ------------------
 * The PixWindow is the real drawing area.
 */


static void	allocateMyPixwin()
{
	int	width, height;

	width = (int)window_get(frame, WIN_WIDTH)-V_SCROLLBAR;
	height = (int)window_get(frame, WIN_HEIGHT)-COFFSET-H_SCROLLBAR;
	if ( G_xmax < width )	G_xmax = width;
	if ( G_ymax < height)	G_ymax = height;
	myCanvas =  window_create(frame, CANVAS,
			CANVAS_AUTO_SHRINK,		FALSE,
			CANVAS_AUTO_EXPAND,		TRUE,
			CANVAS_WIDTH,			G_xmax,   
			CANVAS_HEIGHT,			G_ymax,
			WIN_X,				0,
			WIN_Y,				0,
			WIN_WIDTH,			width,	 
			WIN_HEIGHT,			height, 
			CANVAS_RETAINED,		TRUE,
			WIN_VERTICAL_SCROLLBAR, 	scrollbar_create(0),
			WIN_HORIZONTAL_SCROLLBAR,	scrollbar_create(0),
			WIN_SHOW,			FALSE,
			0);
	if (myCanvas == NULL) Fatal_error("Unable to create window","");

	window_fit(myCanvas);
	myPixwin = (Pixwin*) canvas_pixwin(myCanvas);

	if (myPixwin == NULL) Fatal_error("Unable to create window","");
}


/* Allocate Panel 
 * --------------
 * The Panel is used to print messages and to get input.
 * The Panel contains 1 message line and two text input items.
 */

static void	allocateMyPanel()
{
	panel_there = 1;
	myPanel = window_create(frame, PANEL,
			WIN_BELOW,			myCanvas,
			WIN_X,				0,
			WIN_HEIGHT,			50,
			WIN_SHOW,			FALSE,
			0);
 
	message_item = panel_create_item(myPanel, PANEL_MESSAGE,
			0);
	text1_item  = panel_create_item(myPanel,  PANEL_TEXT,
			PANEL_SHOW_ITEM,	FALSE,
			PANEL_ITEM_X,		1,
			PANEL_ITEM_Y,		1,
			0);
	text2_item  = panel_create_item(myPanel,  PANEL_TEXT,
			PANEL_ITEM_X,		1,
			PANEL_ITEM_Y,		25,
			PANEL_SHOW_ITEM,	FALSE,
			0);
}


/*--------------------------------------------------------------------*/
/*  Canvas displaying                                                 */
/*--------------------------------------------------------------------*/

/* display the graph in the pixwin
 * -------------------------------
 */

static void	displayCanvas()
{
	set_busy_cursor();
	buildCanvas();
	main_menu_check();
	set_normal_cursor();
}


/* build the pixwin
 * ----------------
 * This is used to refresh the pixwin after any change like scaling,
 * scrolling etc.
 * During animations, it is not needed to redisplay, because
 * gs_open is called. In this case, we set animflag to 1.
 */

int anim_flag = 0;

static void	buildCanvas()
{
	if (anim_flag) return;

	if (touch_file) window_set(myCanvas, WIN_SHOW,	FALSE, 0);

	if (!colored) G_color = WHITE;
	pw_writebackground(myPixwin, 
		0, 0, G_xmax, G_ymax+COFFSET, 
		(PIX_SRC | PIX_COLOR(COLOR(G_color))));

	draw_main();
	draw_infoboxes();
	waitcnt=0;

	if ( V_ruler )	ruler_paint();

	panel_outp("");
	window_set(myCanvas, WIN_SHOW,	TRUE, 0);
}



/*--------------------------------------------------------------------*/
/*  Window resizing procedure                                         */
/*--------------------------------------------------------------------*/

/* If we resize the window, we must take care that the panel stays
 * visible. Otherwise, the user could not see messages, etc.
 */

static void	resizeWindow()
{
	window_set(frame,
		WIN_WIDTH,	G_width+V_SCROLLBAR,
		WIN_HEIGHT,	G_height+COFFSET+H_SCROLLBAR,
		0);
	window_set(myCanvas,
		WIN_HEIGHT,	G_height,
		WIN_WIDTH,	G_width,
		0);
	window_set(myPanel,
		WIN_HEIGHT,	50,
		WIN_BELOW,	myCanvas,
		0);
}


/* The default resize procedure
 * ----------------------------
 */

static void	frame_resize_proc(frame, event)
Frame	frame;
Event	*event;
{
	int	width, height;

	if ( event_id(event) == WIN_RESIZE ) {
		width = (int)window_get(frame, WIN_WIDTH)-V_SCROLLBAR;
		height = (int)window_get(frame, WIN_HEIGHT)-COFFSET-H_SCROLLBAR;
		if (G_xmax<width)  width = G_xmax;
		if (G_ymax<height) height = G_ymax;
		window_set(frame,
			WIN_WIDTH,	width+V_SCROLLBAR,
			WIN_HEIGHT,	height+COFFSET+H_SCROLLBAR,
			0);
		window_set(myCanvas,
			WIN_WIDTH,	width,
			WIN_HEIGHT,	height,
			0);
		window_fit(myCanvas);
		window_set(myPanel,
			WIN_HEIGHT,	50,
			WIN_BELOW,	myCanvas,
			0);
		displayCanvas();
	}
}


/*--------------------------------------------------------------------*/
/*  Display window open and close                                     */
/*--------------------------------------------------------------------*/

/* These functions are used to allow the animation interface to
 * open or close the window.
 */

void	gs_open()
{
	window_set(frame, FRAME_CLOSED, FALSE, 0);
	window_fit(frame);
}


void	gs_close()
{
	window_set(frame, FRAME_CLOSED, TRUE, 0);
}


/*--------------------------------------------------------------------*/
/*  Cursor management                                                 */
/*--------------------------------------------------------------------*/

static void set_normal_cursor()
{
    window_set(myCanvas, WIN_CURSOR, standard_cursor, 0);
}

static void set_busy_cursor()
{
    window_set(myCanvas, WIN_CURSOR, workingCursor, 0);
}

static void set_select_cursor()
{
    window_set(myCanvas, WIN_CURSOR, selectCursor, 0);
}

static void set_fold_cursor()
{
    window_set(myCanvas, WIN_CURSOR, foldCursor, 0);
}


/*--------------------------------------------------------------------*/
/*  Menu Handling Auxiliaries                                         */
/*--------------------------------------------------------------------*/

/*  Reinit the main menu of the canvas
 *  ==================================
 *  After building the canvas, we reinitialize the main menu procedure
 *  of the canvas. For security reason, because some event handling
 *  use own canvas selection procedures. 
 */

static GEDGE   act_follow_edge = NULL;
static GNODE   act_follow_node = NULL;
static GNODE   act_follow_target = NULL;
static int edge_thickness;
static int follow_state;

static void	main_menu_check()
{
	notify_no_dispatch();
	window_set(myPanel,
		WIN_SHOW,	TRUE,
		0);
	window_set(myCanvas,
		WIN_SHOW,   	TRUE,
		WIN_IGNORE_PICK_EVENT,	LOC_MOVE,
		WIN_CONSUME_PICK_EVENT, WIN_MOUSE_BUTTONS,
		WIN_CONSUME_KBD_EVENT,  WIN_TOP_KEYS,
		WIN_CONSUME_KBD_EVENT,  WIN_RIGHT_KEYS,
		WIN_CONSUME_KBD_EVENT,  WIN_LEFT_KEYS,
		WIN_CONSUME_KBD_EVENT,  WIN_ASCII_EVENTS,
		WIN_EVENT_PROC,         myCanvas_event_proc,
		0);
	if (act_follow_edge)
		ETHICKNESS(act_follow_edge) = edge_thickness;
	if (act_follow_target)
		NREVERT(act_follow_target) = 0;
	set_normal_cursor();
	notify_do_dispatch();
}


/*  Handling of items
 *  =================
 */

/*  Ask at text_item1
 *  -----------------
 *  This routine ask a question, visible in text_item1, and waits
 *  for dispatching. The dispatcher continues with the cont_proc 
 *  after answering the question by then user.
 */

#ifdef ANSI_C
static void 	ask_item1(msg,cont_proc)
char *msg;
void	cont_proc();
#else
static void 	ask_item1(msg,cont_proc)
char *msg;
#endif
{
	notify_no_dispatch();

	panel_outp(""); 

	/* Move mouse into the panel */
	window_set(myPanel, 
		WIN_MOUSE_XY,		20, 20,
		0);

	/* Clear any old value */
	panel_set_value(text1_item, "");

	/* Ask and continue at cont_proc */
	panel_set(text1_item,
		PANEL_SHOW_ITEM,	TRUE,
		PANEL_LABEL_STRING,	msg,
		PANEL_VALUE_DISPLAY_LENGTH,	80,
		PANEL_NOTIFY_LEVEL,	PANEL_SPECIFIED,
		PANEL_NOTIFY_STRING,	"\r",
		PANEL_NOTIFY_PROC,	cont_proc,
		0);

	notify_do_dispatch();
}

/*  Ask at text_item2
 *  -----------------
 *  This routine ask a question, visible in text_item2, and waits
 *  for dispatching. The dispatcher continues with the cont_proc 
 *  after answering the question by then user.
 */

#ifdef ANSI_C
static void 	ask_item2(msg,cont_proc)
char *msg;
void	cont_proc();
#else
static void 	ask_item2(msg,cont_proc)
char *msg;
#endif
{
	notify_no_dispatch();

	/* Move mouse into the panel */
	window_set(myPanel, 
		WIN_MOUSE_XY,		20, 20,
		0);

	/* Clear any old value */
	panel_set_value(text2_item, "");

	/* Ask and continue at cont_proc */
	panel_set(text2_item,
		PANEL_SHOW_ITEM,	TRUE,
		PANEL_LABEL_STRING,	msg,
		PANEL_VALUE_DISPLAY_LENGTH,	80,
		PANEL_NOTIFY_LEVEL,	PANEL_SPECIFIED,
		PANEL_NOTIFY_STRING,	"\r",
		PANEL_NOTIFY_PROC,	cont_proc,
		0);

	notify_do_dispatch();
}


/*  Clear text_items
 *  ----------------
 *  To avoid, that old parts of the text items stay visible.
 */

static void 	clear_items()
{
	notify_no_dispatch();

	panel_set_value(text1_item, "");
	panel_set(text1_item,
		PANEL_SHOW_ITEM,	FALSE,
		0);
	panel_set_value(text2_item, "");
	panel_set(text2_item,
		PANEL_SHOW_ITEM,	FALSE,
		0);

	/* Move mouse into the canvas */
	window_set(myCanvas, 
		WIN_MOUSE_XY,		20, 20,
		0);

	notify_do_dispatch();
}



/* Menu activation and deactivation
 * ================================
 */

/* Desactivate the panel menu 
 * --------------------------
 */

static void 	desactivate_panel_menu()
{
	notify_no_dispatch();

	/* desactivate menu  */
	window_set(myCanvas, 
		WIN_IGNORE_KBD_EVENT,   WIN_TOP_KEYS,
		WIN_IGNORE_KBD_EVENT,   WIN_RIGHT_KEYS,
		WIN_IGNORE_KBD_EVENT,   WIN_LEFT_KEYS,
		WIN_IGNORE_KBD_EVENT,   WIN_ASCII_EVENTS,
		WIN_IGNORE_PICK_EVENT,  WIN_MOUSE_BUTTONS, 
		0);

	notify_do_dispatch();
}

/* Activate the panel menu for mouse selection
 * -------------------------------------------
 * Reaction on mouse button down and keyboard commands. 
 */

#ifdef ANSI
static void	activate_select_menu(cont_proc)
void	cont_proc();
#else
static void	activate_select_menu(cont_proc)
#endif
{
	notify_no_dispatch();

	window_set(myCanvas,
		WIN_CONSUME_KBD_EVENT,  WIN_TOP_KEYS,
		WIN_CONSUME_KBD_EVENT,  WIN_RIGHT_KEYS,
		WIN_CONSUME_KBD_EVENT,  WIN_LEFT_KEYS,
		WIN_CONSUME_KBD_EVENT,  WIN_ASCII_EVENTS,
		WIN_IGNORE_PICK_EVENT,	LOC_MOVE,
		WIN_CONSUME_PICK_EVENT,	WIN_MOUSE_BUTTONS,
		WIN_EVENT_PROC,		cont_proc,
		0);
	notify_do_dispatch();
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

static char 	*int_to_str(n)
int	n;
{
	char *r;

	r = (char *)myalloc(4);
	if ((n<-999)||(n>9999)) n = 0;
	SPRINTF(r, "%d", n);
	return (r);
}

/* Convert an integer to a string of 4 digits for the class field
 * --------------------------------------------------------------
 * It is important that each time the string memory is newly allocated.
 */

static char 	*class_num(n)
int	n;
{
	char *r;

	assert((n>0)&&(n<=16));
	if (class_name_available && class_names[n-1]) {
		return(class_names[n-1]);
	}
	r = (char *)myalloc(4);
	if ((n<-999)||(n>9999)) n = 0;
	SPRINTF(r, "%d", n);
	return (r);
}

/* Convert an integer to a string of 4 digits for the info field
 * -------------------------------------------------------------
 * It is important that each time the string memory is newly allocated.
 */

static char 	*act_info_num(n)
int	n;
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
/*  Panel messages                                                    */
/*--------------------------------------------------------------------*/

/* Write a message into the panel
 * ------------------------------
 */

static char mbuffer[80];

static void 	panel_outp(x)
char *x;
{
	int  i;

	i = 0;
	while ((*x)&&(i<79)) 	mbuffer[i++]= *x++;
	while (i<79) 		mbuffer[i++]= ' ';
	mbuffer[79] = 0;
	panel_set( message_item, PANEL_SHOW_ITEM,	TRUE,
				 PANEL_LABEL_STRING,	mbuffer,
		   0);
}

/* Write a Waitmessage into the panel
 * ----------------------------------
 */

void gs_wait_message(c)
char c;
{
	int i;

	waitcnt++;
	if (!panel_there) {
		if (silent) return;
		FPRINTF(stdout,"\b.%c",c); 
		FFLUSH(stdout);
		return;
	}
	strcpy(mbuffer,"Wait  .");
	for (i=5; i<6+waitcnt; i++) {
		if (i>=70) { waitcnt=0; break; }
		mbuffer[i] = '.';		
	}
	mbuffer[i-1]=c;
	mbuffer[i]=0;
	panel_set( message_item, PANEL_SHOW_ITEM,	TRUE,
				 PANEL_LABEL_STRING,	mbuffer,
		   0);
}


/* Relayout and display the new graph
 * ----------------------------------
 * If after folding, a complete relayout is necessary, we start here.
 */

static void complete_relayout()
{
	set_busy_cursor();
	disable_signal();
	relayout();
	displayCanvas();	/* this set the cursor normal */
	enable_signal();
}

/*--------------------------------------------------------------------*/
/*  Menu allocation funtions                                          */
/*--------------------------------------------------------------------*/

/* Create all menus
 * ----------------
 */

static void	createMenu()
{
	int	i;

	/* Menu of classes: its currently a list of numbers */

	class_menu1 = menu_create(
		MENU_GEN_PROC,			gen_hide_class_proc,
		MENU_NOTIFY_PROC,		hide_class_proc,	
		0);
	class_menu2 = menu_create(
		MENU_GEN_PROC,			gen_expose_class_proc,
		MENU_NOTIFY_PROC,		expose_class_proc,	
		0);
	class_menu3 = menu_create(
		MENU_NOTIFY_PROC,		fold_class_proc,	
		0);
	for (i=1; i<=16; i++) {
		menu_set(class_menu1,
			MENU_STRING_ITEM, class_num(i), i, 
			0);
		menu_set(class_menu2,
			MENU_STRING_ITEM, class_num(i), i, 
			0);
		menu_set(class_menu3,
			MENU_STRING_ITEM, class_num(i), i, 
			0);
	}
	(void)gen_hide_class_proc(class_menu1, MENU_CREATE);
	(void)gen_expose_class_proc(class_menu2, MENU_CREATE);

	/* Info menu: its currently a list of numbers */

	info_menu = menu_create(
		MENU_NOTIFY_PROC,info_proc,	
		0);
	for (i=1; i<=6; i++) {
		menu_set(info_menu,
			MENU_STRING_ITEM, act_info_num(i), i, 
			0);
	}
	menu_set(info_menu,
			MENU_STRING_ITEM, "Layout Attributes", 7, 
			MENU_STRING_ITEM, "Label of Node",     8, 
			MENU_STRING_ITEM, "Statistics",        9, 
			0);

	/* Scrolling menu */

	scroll_menu = menu_create(
		MENU_ITEM,	MENU_STRING, 	"left",		0,
		MENU_ITEM,	MENU_STRING, 	"right",	0,
		MENU_ITEM,	MENU_STRING, 	"up",		0,
		MENU_ITEM,	MENU_STRING, 	"down",		0,
		MENU_ITEM,	MENU_STRING, 	"lleft",	0,
		MENU_ITEM,	MENU_STRING, 	"rright",	0,
		MENU_ITEM,	MENU_STRING, 	"uup",		0,
		MENU_ITEM,	MENU_STRING, 	"ddown",	0,
		MENU_ITEM,	MENU_STRING, 	"llleft",	0,
		MENU_ITEM,	MENU_STRING, 	"rrright",	0,
		MENU_ITEM,	MENU_STRING, 	"uuup",		0,
		MENU_ITEM,	MENU_STRING, 	"dddown",	0,
		MENU_ITEM,	MENU_STRING, 	"origin",	0,
		MENU_NOTIFY_PROC,		scroll_proc,
		0);

	/* Scaling menu */

	scale_menu = menu_create(
		MENU_ITEM,	MENU_STRING,	"normal",	0,
		MENU_ITEM,	MENU_STRING,	"400 %",	0,
		MENU_ITEM,	MENU_STRING,	"200 %",	0,
		MENU_ITEM,	MENU_STRING,	"150 %",	0,
		MENU_ITEM,	MENU_STRING,	"90 %",		0,
		MENU_ITEM,	MENU_STRING,	"80 %",		0,
		MENU_ITEM,	MENU_STRING,	"70 %",		0,
		MENU_ITEM,	MENU_STRING,	"60 %",		0,
		MENU_ITEM,	MENU_STRING,	"50 %",		0,
		MENU_ITEM,	MENU_STRING,	"25 %",		0,
		MENU_NOTIFY_PROC,		scale_proc,
		0);

	/* On/Off menu used for ruler and labels */

	on_off_menu1 = menu_create(
		MENU_ITEM,	MENU_STRING,	"on",		0,
		MENU_ITEM,	MENU_STRING,	"off",		0,
		MENU_GEN_PROC,			gen_lab_on_off_proc,
		MENU_NOTIFY_PROC,		lab_on_off_proc,
		0);

	on_off_menu2 = menu_create(
		MENU_ITEM,	MENU_STRING,	"on",		0,
		MENU_ITEM,	MENU_STRING,	"off",		0,
		MENU_GEN_PROC,			gen_rul_on_off_proc,
		MENU_NOTIFY_PROC,		rul_on_off_proc,
		0);

	(void)gen_lab_on_off_proc(on_off_menu1, MENU_CREATE);
	(void)gen_rul_on_off_proc(on_off_menu2, MENU_CREATE);

	/* Print & Save menu */

	save_menu = menu_create(
		MENU_ITEM,	MENU_STRING, 	"Save to file",		0,
		MENU_ITEM,	MENU_STRING, 	"Export to PBM",	0,
		MENU_ITEM,	MENU_STRING, 	"Export to PPM",	0,
		MENU_NOTIFY_PROC,		save_proc,
		0);

	/* Main menu */

	menu = menu_create(
		MENU_ITEM,  MENU_STRING, "Fold Subgraph",	0,
		MENU_ITEM,  MENU_STRING, "Unfold Subgraph",	0,
		MENU_ITEM,
			MENU_STRING,	 "Hide Edges",
			MENU_PULLRIGHT,	 class_menu1,
			0,
		MENU_ITEM,
			MENU_STRING,	 "Expose Edges",
			MENU_PULLRIGHT,	 class_menu2,
			0,
		MENU_ITEM,
			MENU_STRING,	 "Fold Region",
			MENU_PULLRIGHT,	 class_menu3,
			0,
		MENU_ITEM,  MENU_STRING, "Unfold Region",	0,
		MENU_PULLRIGHT_ITEM,	 "Scroll",		scroll_menu,
		MENU_ITEM,
			MENU_STRING,	 "Node Information",
			MENU_PULLRIGHT,	 info_menu,
			0,
		MENU_ITEM,  MENU_STRING, "Position",		0,
		MENU_ITEM,  MENU_STRING, "Pick Position",	0,
		MENU_ITEM,  MENU_STRING, "Center Node",		0,
		MENU_ITEM,  MENU_STRING, "Follow Edge",		0,
		MENU_ITEM,
			MENU_STRING,	 "Ruler",
			MENU_PULLRIGHT,	 on_off_menu2,
			0,
		MENU_ITEM,
			MENU_STRING,	 "Label of Edges",	
			MENU_PULLRIGHT,	 on_off_menu1,
			0,
		MENU_PULLRIGHT_ITEM,	 "Scale",		scale_menu,
		MENU_PULLRIGHT_ITEM,	 "Save/Export",		save_menu,
		MENU_ITEM,  MENU_STRING, "Load",		0,
		MENU_ITEM,  MENU_STRING, "Reload",		0,
		MENU_ITEM,  MENU_STRING, "Quit",		0,
		MENU_NOTIFY_PROC,	 menu_proc,
		0);
}


/*--------------------------------------------------------------------*/
/*  Menu event functions                                              */
/*--------------------------------------------------------------------*/

/* Left mouse into Canvas: Show the main menu 
 *-------------------------------------------
 */

static void	myCanvas_event_proc(myCanvas, event)
Canvas	myCanvas;
Event	*event;
{
        Event   *local_event;

        local_event = canvas_window_event(myCanvas, event);
	if ( (event_id(event) == MS_LEFT) && event_is_down(event) )
		menu_show(menu, myCanvas, local_event, 0);
	else if ( event_id(event) == WIN_REPAINT ) {
		/* Nothing */
	}
	else check_keyboard_event(local_event);
}


/* Selection in the main menu
 * --------------------------
 */

static void	menu_proc(m, mi)
Menu		m;
Menu_item	mi;
{
	int		state;

	state = (int) menu_get(m, MENU_SELECTED);
	switch (state)
	{
		case 1:	panel_outp("Fold Subgraph");
			m_fold_subgraph();
			break;
		case 2:	panel_outp("Unfold Subgraph");
			m_unfold_subgraph();
			break;
		case 3:	panel_outp("Hide Edges"); 
			m_hide_edges(mi);
			break;
		case 4:	panel_outp("Expose Edges"); 
			m_expose_edges(mi);
			break;
		case 5:	panel_outp("Fold Region"); 
			m_fold_region(mi);
			break;
		case 6:	panel_outp("Unfold Region"); 
			m_unfold_region(mi);
			break;
		case 7:	panel_outp("Scroll"); 
			menu_get(mi, MENU_VALUE);
			break;
		case 8:	panel_outp("Node Info"); 
			menu_get(mi, MENU_VALUE);
			break;
		case 9:	panel_outp("XY-Position"); 
			m_position();
			break;
		case 10:panel_outp("Mouse Position");  
			m_pic_position();
			break;
		case 11:panel_outp("Center Node");  
			m_center_node();
			break;
		case 12:panel_outp("Follow Edge");  
			m_follow_edge();
			break;
		case 13:panel_outp("Ruler"); 

			/* Call the submenu. This will change V_ruler,
			 * see rul_on_off_proc 
			 */
			menu_get(mi, MENU_VALUE);
			if (V_ruler) {
				disable_signal();
				ruler_paint();
				panel_outp("");
				enable_signal();
			}
			else {  disable_signal();
				displayCanvas();
				enable_signal();
			}
			break;
		case 14:panel_outp("Label of Edges"); 

			/* Call the submenu. This will change
			 * G_displayel. See lab_on_off_proc.
			 */
			menu_get(mi, MENU_VALUE);
			complete_relayout();	
			break; 

		case 15:panel_outp("Scale");  
			menu_get(mi, MENU_VALUE); 
			break; 
		case 16:panel_outp("Save/Export");  
			menu_get(mi, MENU_VALUE); 
			break; 
		case 17:panel_outp("Load");  
			load_save = LS_LOAD;
			m_load();
			break;
		case 18:panel_outp("Reload"); 
			m_reload();
			break;
		case 19:/* "Quit" */
			gs_exit(0);
			break;
		default:
			break;
	}
}


/* Analyse the full set of keyboard events
 * ---------------------------------------
 */

static void 	check_keyboard_event(event)
Event *event;
{
	int redraw_necessary;
	int i;

	i = 0;
	if ( event_id(event) == WIN_REPAINT ) return;
	switch (event_id(event)) {
	case '1': /* Expose of hide class 1 */
	case '2': /* Expose of hide class 2 */
	case '3': /* Expose of hide class 3 */
	case '4': /* Expose of hide class 4 */
	case '5': /* Expose of hide class 5 */
	case '6': /* Expose of hide class 6 */
	case '7': /* Expose of hide class 7 */
	case '8': /* Expose of hide class 8 */
	case '9': /* Expose of hide class 9 */
		i = event_id(event)-'0';	
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
		panel_outp("Select a node to get information about this node.");
		activate_select_menu(select_info_proc);
		set_select_cursor();
		return;
	case 'e':
	case 'E':
		m_follow_edge();
		return;
	case 'n':
	case 'N':
		m_center_node();
		return;
	case 'f':
	case 'F':
		load_save = LS_LOAD;
		m_load();
		return;
	case 'g':
	case 'G':
		m_reload();
		return;
	case 'l': /* Label of Edges */
	case 'L': /* Label of Edges */
		G_displayel = 1-G_displayel;
		complete_relayout();	
		return;
	case 'q': /* Quit */
	case 'Q': /* Quit */
		gs_exit(0);
		return;
#ifdef DRAWDEBUG
	case ' ': /* Debug */
		step3_main();
#endif 
	default: check_minimalkeyboard_event(event); 
		main_menu_check();
		return;
	}
	if (redraw_necessary) {
		disable_signal(); 
       		displayCanvas(); 
        	enable_signal();
	}
}


/* Analyse the minimal set of keyboard events
 * ------------------------------------------
 * Note: we do not change the eventhandler here.
 */

static void 	check_minimalkeyboard_event(event)
Event *event;
{
	int redraw_necessary;
	int xx,yy; 

	redraw_necessary = 0;

	if ( event_id(event) == WIN_REPAINT ) return;
	switch (event_id(event)) {
	case 'd':  /* R10: left */
	case 'D':  /* R10: left */
		V_xmin -= 256;
		V_xmax = V_xmin+G_xmax;
		redraw_necessary = 1;
		break;
	case 'c':  /* R12: right */
	case 'C':  /* R12: right */
		V_xmin += 256;
		V_xmax = V_xmin+G_xmax;
		redraw_necessary = 1;
		break;
	case 'a':  /* R8: up */
	case 'A':  /* R8: up */
		V_ymin -= 256;
		V_ymax = V_ymin+G_ymax+COFFSET;
		redraw_necessary = 1;
		break;
	case 'b':  /* R14: down */
	case 'B':  /* R14: down */
		V_ymin += 256;
		V_ymax = V_ymin+G_ymax+COFFSET;
		redraw_necessary = 1;
		break;
	case 'o':  /* origin */
	case 'O':  /* origin */
		redraw_necessary = 1;
		V_xmin = 0;
		V_ymin = 0;
		V_xmax = V_xmin+G_xmax;
		V_ymax = V_ymin+G_ymax+COFFSET;
		break;
	case 'q': /* Quit */
	case 'Q': /* Quit */
		gs_exit(0);
		break;
	case '0':  /* normal */
		redraw_necessary = 1;
		xx = V_xmin * G_shrink/G_stretch;
		yy = V_ymin * G_shrink/G_stretch;
		G_stretch = 1;
		G_shrink  = 1;
		V_xmin = xx * G_stretch/G_shrink;
		V_ymin = yy * G_stretch/G_shrink;
		V_xmax = V_xmin+G_xmax;
		V_ymax = V_ymin+G_ymax+COFFSET;
		break;
	case '-':  /* shrink */
		redraw_necessary = 1;
		xx = V_xmin * G_shrink/G_stretch;
		yy = V_ymin * G_shrink/G_stretch;
		G_stretch *= 2;
		G_shrink  *= 3;
		V_xmin = xx * G_stretch/G_shrink;
		V_ymin = yy * G_stretch/G_shrink;
		V_xmax = V_xmin+G_xmax;
		V_ymax = V_ymin+G_ymax+COFFSET;
		break;
	case '_':  /* shrink */
		redraw_necessary = 1;
		xx = V_xmin * G_shrink/G_stretch;
		yy = V_ymin * G_shrink/G_stretch;
		G_shrink  *= 2;
		V_xmin = xx * G_stretch/G_shrink;
		V_ymin = yy * G_stretch/G_shrink;
		V_xmax = V_xmin+G_xmax;
		V_ymax = V_ymin+G_ymax+COFFSET;
		break;
	case '+':  /* stretch */
		redraw_necessary = 1;
		xx = V_xmin * G_shrink/G_stretch;
		yy = V_ymin * G_shrink/G_stretch;
		G_stretch *= 3;
		G_shrink  *= 2;
		V_xmin = xx * G_stretch/G_shrink;
		V_ymin = yy * G_stretch/G_shrink;
		V_xmax = V_xmin+G_xmax;
		V_ymax = V_ymin+G_ymax+COFFSET;
		break;
	case '=':  /* stretch */
		redraw_necessary = 1;
		xx = V_xmin * G_shrink/G_stretch;
		yy = V_ymin * G_shrink/G_stretch;
		G_stretch *= 2;
		V_xmin = xx * G_stretch/G_shrink;
		V_ymin = yy * G_stretch/G_shrink;
		V_xmax = V_xmin+G_xmax;
		V_ymax = V_ymin+G_ymax+COFFSET;
		break;
	case 'r' : /* ruler */
	case 'R' : /* ruler */
		V_ruler = 1-V_ruler;
		if (V_ruler) {
			disable_signal();
			ruler_paint();
			panel_outp("");
			enable_signal();
		}
		else redraw_necessary = 1;
		break;
	}
	normalize_scaling();
	if (redraw_necessary) {
		disable_signal(); 
       		buildCanvas(); 
        	enable_signal();
	}
}


/*--------------------------------------------------------------------*/
/*  Main menu event procedures                                        */
/*--------------------------------------------------------------------*/

/* Follow an edge
 * --------------
 * The start/end-node of the edge is selected by mouse clicking. 
 * Use special event procedures for the canvas to implement this. After
 * folding or unfolding, the original event provcedure of the canvas is 
 * reinstalled by main_menu_check.
 */

static void	m_follow_edge()
{
	panel_outp("Select a node to follow its edges.");

	activate_select_menu(follow_edge_event_proc);
	act_follow_edge = NULL;
	act_follow_node = NULL;
	set_select_cursor();
	
	/* next interaction will cause a call of follow_edge_event_proc */
}


/* Folding and unfolding
 * ---------------------
 * Use special event procedures for the canvas to implement this. After
 * folding or unfolding, the original event provcedure of the canvas is 
 * reinstalled by main_menu_check.
 */

static void	m_fold_subgraph()
{
	panel_outp("Select nodes: the subgraphs the selected nodes belongs to are folded.");

	activate_select_menu(fold_subgraph_event_proc);
	set_fold_cursor();
	
	/* next interaction will cause a call of fold_subgraph_event_proc */
}


static void	m_unfold_subgraph()
{
	panel_outp("Select summary nodes: the subgraphs of these nodes are shown explicitly.");

	activate_select_menu(unfold_subgraph_event_proc);
	set_select_cursor();

	/* next interaction will cause a call of unfold_subgraph_event_proc */
}


/* Hiding and exposing of edges
 * ----------------------------
 * After selection of a class, the class menu event handler
 * `...class_proc' is called.
 */


static void	m_hide_edges(mi)
Menu_item	mi;
{
	menu_get(mi, MENU_VALUE);

	/* next interaction will cause a call of hide_class_proc */
}


static void	m_expose_edges(mi)
Menu_item	mi;
{
	menu_get(mi, MENU_VALUE);

	/* next interaction will cause a call of expose_class_proc */
}


/* Folding and unfolding of regions
 * --------------------------------
 * Folding: we must first select a class:
 * After selection of a class, the class menu event handler
 * `fold_class_proc' is called automatically. 
 *
 * Unfolding:
 * Use special event procedures for the canvas to implement this. After
 * folding or unfolding, the original event provcedure of the canvas is 
 * reinstalled by main_menu_check.
 */

static void	m_fold_region(mi)
Menu_item	mi;
{
	menu_get(mi, MENU_VALUE);

	/* next interaction will cause a call of fold_class_proc */
}


static void	m_unfold_region(mi)
Menu_item	mi;
{
	panel_outp("Select a node: the region of this summary node is unfolded.");

	activate_select_menu(unfold_region_proc);
	set_select_cursor();

	/* next interaction will cause a call of unfold_region_proc */
}


/* Enter Position 
 * --------------
 */

static void	m_position()
{
	desactivate_panel_menu();
	ask_item1("x-co-ordinate:",x_proc);

	/* next interaction will cause a call of x_proc */
}


/* Centering of nodes
 * ------------------
 */

static void	m_center_node()
{
	desactivate_panel_menu();
	ask_item1("Enter title of node:",node_title_proc);

	/* next interaction will cause a call of node_title_proc */
}


/* Pick position 
 * -------------
 */

static void	m_pic_position()
{
	panel_outp("Pick with the mouse into the window to select the new origin.");
	activate_select_menu(pic_position_proc);
	set_select_cursor();

	/* next interaction will cause a call of pic_position_proc */
}


/* Load/Save a file 
 * ----------------
 */

static void	m_load()
{
	desactivate_panel_menu();
	ask_item1("Enter file name:",load_proc);

	/* next interaction will cause a call of load_proc */
}


/* Reload the same file
 * --------------------
 */

void	m_reload()
{
	FILE *f;

	/* Check whether file is readable */
        if ( strcmp(Dataname,"-")==0 ) { 
		panel_outp("Illegal filename."); 
		main_menu_check(); 
		return;
	}
        f = fopen(Dataname,"r");
        if (f == NULL) { 
		panel_outp("Cannot open file."); 
		main_menu_check(); 
		return;
        }
	fclose(f);

	set_busy_cursor();
	disable_signal(); 
	clear_hide_class();
	parse_part();
	visualize_part();
	resizeWindow(); 
        displayCanvas(); 
        enable_signal();
}


/*--------------------------------------------------------------------*/
/*  Continuation menu event handlers                                  */
/*--------------------------------------------------------------------*/

/* Info menu event  handler
 * ========================
 * Here we come from `node info'
 */

static void	info_proc(m, mi)
Menu		m;
Menu_item	mi;
{
	info_val = (int)menu_get(m, MENU_SELECTED);
	truesize = 1;
	if (info_val==9) { show_statistics(); return; }
	if ((info_val!=7) && (info_val!=8) && (info_val>3)) { 
		info_val -= 3;
		truesize = 0;
	}
	panel_outp("Select a node to get information about this node.");

	activate_select_menu(select_info_proc);
	set_select_cursor();

	/* next interaction will cause a call of 
	 * select_info_proc 
 	 */
}


			
/* Show the statistics
 * -------------------
 */

static int selected_flag = 0;

static void show_statistics()
{
	panel_outp("Press button to continue.");
	set_select_cursor();

	if (!colored) G_color = WHITE;
        pw_writebackground(myPixwin,
                           0, 0, G_xmax, G_ymax+COFFSET,
                           (PIX_SRC | PIX_COLOR(COLOR(G_color))));
	suntextout(1,"Statistics:");
	statistics();
	suninttextout(2,"Number of visible real  nodes: ............... %d",
                                st_nr_vis_nodes);
        suninttextout(3,"Number of visible dummy nodes: ............... %d",
                                st_nr_vis_dummies);
        suninttextout(4,"Number of visible label nodes: ............... %d",
                                st_nr_vis_labels);
        suninttextout(5,"Number of invisible nodes: ................... %d",
                                st_nr_invis_nodes);
        suninttextout(6,"Number of invisible graph summary nodes:...... %d",
                                st_nr_invis_graphs);
        suninttextout(7,"Number of visible edges (excluding nearedges): %d",
                                st_nr_vis_edges);
        suninttextout(8,"Number of visible nearedges (+ anchordummies): %d",
                                st_nr_vis_nearedges);
        suninttextout(9,"Number of invisible edges: ................... %d",
                                st_nr_invis_edges);
        suninttextout(10,"Maximal indegree  of a visible node: ......... %d",
                                st_max_indeg);
        suninttextout(11,"Maximal outdegree of a visible node: ......... %d",
                                st_max_outdeg);
        suninttextout(12,"Maximal degree    of a visible node: ......... %d",
                                st_max_degree);
        suninttextout(13,"Number of crossings in this layout: .......... %d",
                                nr_crossings);
        suntextout(14,   "(except the crossings at anchor points)");
        suninttextout(15,"Maximal x co-ordinate: ....................... %d",
                                maximal_xpos);
        suninttextout(16,"Maximal y co-ordinate: ....................... %d",
                                maximal_ypos);

	activate_select_menu(follow_centeredge_event_proc);
}


/* Print a text into the pixwindow at position y*19
 * ------------------------------------------------
 */

static void suntextout(y,msg)
int  y;
char *msg;
{
	(G_color == BLACK) ?
		pw_text(myPixwin, 15, y*19, 
			(PIX_SRC | PIX_COLOR(COLOR(WHITE))), 0, msg) :
		pw_text(myPixwin, 15, y*19, 
			(PIX_SRC | PIX_COLOR(COLOR(BLACK))), 0, msg);
}


/* Print a text and integer into the pixwindow at position y*19
 * ------------------------------------------------------------
 */


static void suninttextout(y,msg,i)
int  y;
char *msg;
int i;
{
        SPRINTF(mbuffer,msg,i);
        suntextout(y,mbuffer);
}



/* Class menu event  handler
 * =========================
 * Here we come from `hide edges', `expose edges', `fold region'.
 */


/* These functions generate the menus
 * ----------------------------------
 * The menu must be generated because on of off must be unselectable,
 * depending on what is on or off.
 */

static Menu	gen_hide_class_proc(m, op)
Menu 		m;
Menu_generate	op;
{
	int i;

	if (op != MENU_CREATE)	return(m); 

	for (i=0; i<16; i++) {
		if (hide_class[i]) 
			menu_set(menu_get(m, MENU_NTH_ITEM, i+1), 
				MENU_INACTIVE, TRUE,
				0);
		else 	menu_set(menu_get(m, MENU_NTH_ITEM, i+1), 
				MENU_INACTIVE, FALSE,
				0);
	}	
	return(m);
}

static Menu	gen_expose_class_proc(m, op)
Menu 		m;
Menu_generate	op;
{
	int i;

	if (op != MENU_CREATE)	return(m); 

	for (i=0; i<16; i++) {
		if (hide_class[i]) 
			menu_set(menu_get(m, MENU_NTH_ITEM, i+1), 
				MENU_INACTIVE, FALSE,
				0);
		else 	menu_set(menu_get(m, MENU_NTH_ITEM, i+1), 
				MENU_INACTIVE, TRUE,
				0);
	}	
	return(m);
}


/* Hide edge class handler
 * ----------------------
 */

static void	hide_class_proc(m, mi)
Menu		m;
Menu_item	mi;
{
	int		value;

	value = (int)menu_get(m, MENU_SELECTED);
	if (hide_class[value-1]==0) {
			hide_class[value-1] = 1;
			complete_relayout();
	}
	else {  panel_outp("Class is already hidden.");
		main_menu_check();
	}
}
			
/* Expose edge class handler
 * -------------------------
 */

static void	expose_class_proc(m, mi)
Menu		m;
Menu_item	mi;
{
	int		value;

	value = (int)menu_get(m, MENU_SELECTED);
	if (hide_class[value-1]==1) {
			hide_class[value-1] = 0;
			complete_relayout();
	}
	else {  panel_outp("Class is already exposed.");
		main_menu_check();
	}
}
			


/* Fold region class handler 
 * -------------------------
 * If we do fold region, we store in foldregion_class the class to fold.
 */

static int foldregion_class;

static void	fold_class_proc(m, mi)
Menu		m;
Menu_item	mi;
{
	int		value;

	foldregion_class = value = (int)menu_get(m, MENU_SELECTED);
	panel_outp("Select nodes: the 'Fold Region' operation stops at these nodes.");

	activate_select_menu(select_foldstops_proc);
	set_select_cursor();

	/* next interaction will cause a call of 
	 * select_foldstops_proc 
 	 */
}



/* Scroll Menu Handler
 * ===================
 */

static void	scroll_proc(m, mi)
Menu		m;
Menu_item	mi;
{
	int	state;

	state = (int) menu_get(m, MENU_SELECTED);
	switch (state) {
		case 1:	/* "left" */
			V_xmin -= 32;
			V_xmax = V_xmin+G_xmax;
			break;
		case 2:	/* "right" */
			V_xmin += 32;
			V_xmax = V_xmin+G_xmax;
			break;
		case 3:	/* "up" */
			V_ymin -= 32;
			V_ymax = V_ymin+G_ymax+COFFSET;
			break;
		case 4:	/* "down" */
			V_ymin += 32;
			V_ymax = V_ymin+G_ymax+COFFSET;
			break;
		case 5:	/* "lleft" */
			V_xmin -= 256;
			V_xmax = V_xmin+G_xmax;
			break;
		case 6:	/* "rright" */
			V_xmin += 256;
			V_xmax = V_xmin+G_xmax;
			break;
		case 7:	/* "uup" */
			V_ymin -= 256;
			V_ymax = V_ymin+G_ymax+COFFSET;
			break;
		case 8:	/* "ddown" */
			V_ymin += 256;
			V_ymax = V_ymin+G_ymax+COFFSET;
			break;
		case 9:	/* "llleft" */
			V_xmin -= G_width;
			V_xmax = V_xmin+G_xmax;
			break;
		case 10:/* "rrright" */
			V_xmin += G_width;
			V_xmax = V_xmin+G_xmax;
			break;
		case 11:/* "uuup" */
			V_ymin -= G_height;
			V_ymax = V_ymin+G_ymax+COFFSET;
			break;
		case 12:/* "dddown" */
			V_ymin += G_height;
			V_ymax = V_ymin+G_ymax+COFFSET;
			break;
		case 13:/* "origin" */
			V_xmin = 0;
			V_xmax = V_xmin+G_xmax;
			V_ymin = 0;
			V_ymax = V_ymin+G_ymax+COFFSET;
			break;
		default:
			break;
	}
	disable_signal(); 
        displayCanvas(); 
        enable_signal();
}


/* Save/Export Menu Handler
 * ========================
 */

static void	save_proc(m, mi)
Menu		m;
Menu_item	mi;
{
	int	state;

	state = (int) menu_get(m, MENU_SELECTED);
	switch (state) {
		case 1:	/* "Save to file" */
			load_save=LS_SAVEASCII;
			m_load();	
			return;
		case 2:	/* "Export to PBM" */
			load_save=LS_SAVEPBM;
			m_ask_size();	
			return;
		case 3:	/* "Export to PPM" */
			load_save=LS_SAVEPPM;
			m_ask_size();	
			return;
		default:
			break;
	}
	disable_signal(); 
        displayCanvas(); 
        enable_signal();
}


/* Ask for the size of the region:
 * ------------------------------
 */

static char ask_buffer[128];

static void m_ask_size()
{
	desactivate_panel_menu();
	SPRINTF(ask_buffer,"In pixels: Full graph = 0,0,%d,%d. Actual screen = %d,%d,%d,%d.",
		maximal_xpos, maximal_ypos,V_xmin,V_ymin,V_xmax,V_ymax);
	panel_outp(ask_buffer);

	ask_item2("Enter region to save:",ask_scale);

	/* next interaction will cause a call of ask_scale */
}


/* Ask for the scaling 
 * -------------------
 */

static int  region_minx,region_miny;
static int  region_maxx,region_maxy;
static int  region_shrink, region_stretch;

static void	ask_scale(item, event)
Panel_item	item;
Event		*event;
{
	char	*answer;
	char    *c;
	int     res,res2;

	answer = (char *) panel_get(item, PANEL_VALUE);

	res = 1;
	region_minx = region_miny = region_maxx = region_maxy = 0;
	if (answer) {
		c = answer;
		while ((*c) && (*c==' ')) c++;
		while ((*c) && (*c>='0') && (*c<='9')) {
			region_minx = region_minx*10+(*c)-'0';
			c++;
		}
		while ((*c) && ((*c==' ') || (*c==','))) c++;
		while ((*c) && (*c>='0') && (*c<='9')) {
			region_miny = region_miny*10+(*c)-'0';
			c++;
		}
		while ((*c) && ((*c==' ') || (*c==','))) c++;
		while ((*c) && (*c>='0') && (*c<='9')) {
			region_maxx = region_maxx*10+(*c)-'0';
			c++;
		}
		while ((*c) && ((*c==' ') || (*c==','))) c++;
		while ((*c) && (*c>='0') && (*c<='9')) {
			region_maxy = region_maxy*10+(*c)-'0';
			c++;
		}
		while ((*c) && ((*c==' ') || (*c==','))) c++;
		if (*c) res = 0;
	}
	else res = 0;

	if (region_minx>=region_maxx) res = 0;
	if (region_miny>=region_maxy) res = 0;
	if (!res) { 
		panel_outp("Error: Illegal region !\n");
		main_menu_check();
		return;
	}

	if (maximal_xpos > 0) res = region_maxx*100/maximal_xpos;
	else res = 100;
	if (maximal_ypos > 0) res2 = region_maxy*100/maximal_ypos;
	else res2 = 100;
	if (res>res2) res = res2;

	SPRINTF(ask_buffer,"Region = %d,%d,%d,%d. Scale: Full graph: %d,100. Actual: %d,%d.",
		region_minx,region_miny,region_maxx,region_maxy,
		res, G_stretch,G_shrink);
	panel_outp(ask_buffer);

	ask_item2("Enter scaling factors:",ask_filename);

	/* next interaction will cause a call of ask_filename */
}


/* Ask for the filename 
 * --------------------
 */

static void	ask_filename(item, event)
Panel_item	item;
Event		*event;
{
	char	*answer;
	char    *c;
	int     res;

	answer = (char *) panel_get(item, PANEL_VALUE);

	res = 1;
	region_shrink = region_stretch = 0;
	if (answer) {
		c = answer;
		while ((*c) && (*c==' ')) c++;
		while ((*c) && (*c>='0') && (*c<='9')) {
			region_stretch = region_stretch*10+(*c)-'0';
			c++;
		}
		while ((*c) && ((*c==' ') || (*c==','))) c++;
		while ((*c) && (*c>='0') && (*c<='9')) {
			region_shrink = region_shrink*10+(*c)-'0';
			c++;
		}
		while ((*c) && ((*c==' ') || (*c==','))) c++;
		if (*c) res = 0;
	}
	else res = 0;
	if (region_shrink<=0) res = 0;
	if (region_stretch<=0) res = 0;

	clear_items();

	if (!res) { 
		panel_outp("Error: Illegal scaling !\n");
		main_menu_check();
		return;
	}

	SPRINTF(ask_buffer,"Region = %d,%d,%d,%d. Scaling: %d,%d.",
		region_minx,region_miny,region_maxx,region_maxy,
		region_stretch,region_shrink);
	panel_outp(ask_buffer);

	ask_item2("Enter filename:",load_proc);

	/* next interaction will cause a call of load_proc */
}


/* On-Off Menu handler
 * ===================
 * We come to this menu if we want to display or to hide edge labels,
 * or if we want to display or hide the ruler.
 */

/* This function generates the menu 
 * --------------------------------
 * The menu must be generated because on of off must be unselectable,
 * depending on what is on or off.
 */

static Menu	gen_lab_on_off_proc(m, op)
Menu 		m;
Menu_generate	op;
{
	if (op != MENU_CREATE)	return(m); 

	if (G_displayel) {
		menu_set(menu_get(m, MENU_NTH_ITEM, 1), 
			MENU_INACTIVE, TRUE,
			0);
		menu_set(menu_get(m, MENU_NTH_ITEM, 2), 
			MENU_INACTIVE, FALSE,
			0);
	}	
	else { /* !G_displayel */
		menu_set(menu_get(m, MENU_NTH_ITEM, 1), 
			MENU_INACTIVE, FALSE,
			0);
		menu_set(menu_get(m, MENU_NTH_ITEM, 2), 
			MENU_INACTIVE, TRUE,
			0);
	}
	return(m);
}

static Menu	gen_rul_on_off_proc(m, op)
Menu 		m;
Menu_generate	op;
{
	if (op != MENU_CREATE)	return(m); 

	if (V_ruler) {
		menu_set(menu_get(m, MENU_NTH_ITEM, 1), 
			MENU_INACTIVE, TRUE,
			0);
		menu_set(menu_get(m, MENU_NTH_ITEM, 2), 
			MENU_INACTIVE, FALSE,
			0);
	}	
	else { /* !V_ruler */
		menu_set(menu_get(m, MENU_NTH_ITEM, 1), 
			MENU_INACTIVE, FALSE,
			0);
		menu_set(menu_get(m, MENU_NTH_ITEM, 2), 
			MENU_INACTIVE, TRUE,
			0);
	}
	return(m);
}


/* This function handles the interaction
 * -------------------------------------
 */

static void	lab_on_off_proc(m, mi)
Menu		m;
Menu_item	mi;
{
	int		value;

	value = (int) menu_get(m, MENU_SELECTED);

	G_displayel = 1-(value-1);
}


static void	rul_on_off_proc(m, mi)
Menu		m;
Menu_item	mi;
{
	int		value;

	value = (int) menu_get(m, MENU_SELECTED);

	V_ruler = 1-(value-1);
}


/* Scale menu handler
 * ==================
 */

static void	scale_proc(m, mi)
Menu		m;
Menu_item	mi;
{
	int	state;
	int xx,yy; 

	xx = V_xmin * G_shrink/G_stretch;
	yy = V_ymin * G_shrink/G_stretch;
	state = (int) menu_get(m, MENU_SELECTED);
	switch (state) {
		case 1: /* normal */
			G_stretch = 1;
			G_shrink  = 1;
			break;
		case 2: /* "400 %" */
			G_stretch *= 4;
			break;
		case 3: /* "200 %" */
			G_stretch *= 2;
			break;
		case 4: /* "150 %" */
			G_stretch *= 3;
			G_shrink  *= 2;
			break;
		case 5: /* "90 %" */
			G_stretch *= 9;
			G_shrink  *= 10;
			break;
		case 6: /* "80 %" */
			G_stretch *= 8;
			G_shrink  *= 10;
			break;
		case 7: /* "70 %" */
			G_stretch *= 7;
			G_shrink  *= 10;
			break;
		case 8: /* "60 %" */
			G_stretch *= 6;
			G_shrink  *= 10;
			break;
		case 9: /* "50 %" */
			G_shrink  *= 2;
			break;
		case 10: /* "25 %" */
			G_shrink  *= 4;
			break;
		default:
			break;
	}

	normalize_scaling();
	V_xmin = xx * G_stretch/G_shrink;
	V_ymin = yy * G_stretch/G_shrink;
	V_xmax = V_xmin+G_xmax;
	V_ymax = V_ymin+G_ymax+COFFSET;
	
	disable_signal(); 
        displayCanvas(); 
        enable_signal();
}


static void normalize_scaling()
{
	if (G_shrink==G_stretch) G_shrink = G_stretch = 1;
	if (G_stretch > G_shrink) {
		G_stretch = G_stretch * 60 / G_shrink;
		G_shrink  = 60;
	}
	if (G_stretch < G_shrink) {
		G_shrink  = G_shrink * 60 / G_stretch;
		G_stretch = 60;
	}
	while ((G_shrink%2==0) && (G_stretch%2==0)) {
		G_shrink   = G_shrink/2;
		G_stretch  = G_stretch/2;
	}
	while ((G_shrink%3==0) && (G_stretch%3==0)) {
		G_shrink   = G_shrink/3;
		G_stretch  = G_stretch/3;
	}
	while ((G_shrink%5==0) && (G_stretch%5==0)) {
		G_shrink   = G_shrink/5;
		G_stretch  = G_stretch/5;
	}
	while ((G_shrink%7==0) && (G_stretch%7==0)) {
		G_shrink   = G_shrink/7;
		G_stretch  = G_stretch/7;
	}
	if (G_shrink ==0) G_shrink=1;
	if (G_stretch==0) G_stretch=1;
}
	


/* Fold subgraph event handler
 * ===========================
 * Wait for a selection of a node with the left mouse button.
 * Selections that do not touch a node have no effect.
 * Pushing another button than the right button stops this
 * procedure.
 */ 

static void	follow_edge_event_proc(myCanvas, event)
Canvas	myCanvas;
Event	*event;
{
	GNODE	v;

	if ( (event_id(event) == MS_LEFT) && event_is_down(event) ) {
		v = search_xy_node(event_x(event),event_y(event));
		if (v && (NSUCC(v)||NPRED(v)||NCONNECT(v))) {
			panel_outp("Select an edge to follow: Left button for next, right button to continue.");
			act_follow_node = v;
			follow_state = 0;
			next_follow_edge();
			edge_thickness = ETHICKNESS(act_follow_edge);
			ETHICKNESS(act_follow_edge) += 
						(3*G_shrink/G_stretch);
			disable_signal(); displayCanvas(); enable_signal();
			activate_select_menu(follow_nextedge_event_proc);
		}
		else {  panel_outp("");
			panel_outp("This is not a node or it has no edges. Try again!");
		}
	}
	else if ( (event_id(event) == MS_RIGHT) && event_is_down(event) ) {
		finish_selection();
	}
	else check_minimalkeyboard_event(event);
}

static void	follow_nextedge_event_proc(myCanvas, event)
Canvas	myCanvas;
Event	*event;
{
	GNODE	v;
	int     x,y,width,height,w,h;

	if ( (event_id(event) == MS_LEFT) && event_is_down(event) ) {
		ETHICKNESS(act_follow_edge) = edge_thickness;
		next_follow_edge();
		edge_thickness = ETHICKNESS(act_follow_edge);
		ETHICKNESS(act_follow_edge) += 
					(3*G_shrink/G_stretch);
		disable_signal(); displayCanvas(); enable_signal();

		panel_outp("");
		panel_outp("Left button for next, right button to continue.");
		activate_select_menu(follow_nextedge_event_proc);
	}
	else if ( (event_id(event) == MS_RIGHT) && event_is_down(event) ) {

		v = search_target_node(act_follow_node,act_follow_edge);
		if (v) {
			act_follow_target = v;
			NREVERT(v) = 1;
			x      = (NX(v)*G_stretch)/G_shrink;
			y      = (NY(v)*G_stretch)/G_shrink;
			width  = (NWIDTH(v)*NSTRETCH(v)*G_stretch)/(NSHRINK(v)*G_shrink);
			height = (NHEIGHT(v)*NSTRETCH(v)*G_stretch)/(NSHRINK(v)*G_shrink); 
			w = (int)window_get(frame, WIN_WIDTH)-V_SCROLLBAR;
			h = (int)window_get(frame, WIN_HEIGHT)-COFFSET-H_SCROLLBAR;
			V_xmin = (x+width/2) - w/2;
			V_xmax = V_xmin + G_xmax;
			V_ymin = (y+height/2) - h/2;
			V_ymax = V_ymin + G_ymax + COFFSET;
			disable_signal(); 
                	buildCanvas(); 
             	   	enable_signal();
			panel_outp("Press mouse button to continue.");
			activate_select_menu(follow_centeredge_event_proc);
		}
		else { assert((0)); }
	}
	else check_minimalkeyboard_event(event);
}

static void	follow_centeredge_event_proc(myCanvas, event)
Canvas	myCanvas;
Event	*event;
{
	GNODE	v;

	if ( (event_id(event) == MS_LEFT) && event_is_down(event) ) {
		if (act_follow_edge)
			ETHICKNESS(act_follow_edge) = edge_thickness;
		if (act_follow_target)
			NREVERT(act_follow_target) = 0;
		disable_signal(); buildCanvas(); enable_signal();
		panel_outp("");
		finish_selection();
	}
	else if ( (event_id(event) == MS_RIGHT) && event_is_down(event) ) {
		if (act_follow_edge)
			ETHICKNESS(act_follow_edge) = edge_thickness;
		if (act_follow_target)
			NREVERT(act_follow_target) = 0;
		disable_signal(); buildCanvas(); enable_signal();
		panel_outp("");
		finish_selection();
	}
	else check_minimalkeyboard_event(event);
}


static void next_follow_edge()
{
	ADJEDGE a;
	CONNECT c;

	if (follow_state==1) {
		a = NSUCC(act_follow_node);
		while (a) {
			if (AKANTE(a)==act_follow_edge) break;
			a = ANEXT(a);
		}
		if (a && ANEXT(a)) { 
			act_follow_edge = AKANTE(ANEXT(a));
			return;
		}
	}
	else if (follow_state==2) {
		a = NPRED(act_follow_node);
		while (a) {
			if (AKANTE(a)==act_follow_edge) break;
			a = ANEXT(a);
		}
		if (a && ANEXT(a)) { 
			act_follow_edge = AKANTE(ANEXT(a));
			return;
		}
	}

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


static GNODE search_target_node(v,e)
GNODE v;
GEDGE e;
{
	GNODE w,h;
	GEDGE e1;
	CONNECT c;

	assert((e));
	w = ESTART(e);
	if (w==v) w = EEND(e);
	h = nodelist;
	while (h) { 
		if (h==w) break;
		h = NNEXT(h);
	}
	if (!h) {
		c = NCONNECT(w);
		if (c && (CEDGE(c))) {
			e1 = CEDGE(c);
			if (e1!=e) return(search_target_node(w,e1));
		}
		if (c && (CEDGE2(c))) {
			e1 = CEDGE2(c);
			if (e1!=e) return(search_target_node(w,e1));
		}
		if (NSUCC(w)) {
			e1 = AKANTE(NSUCC(w));
			if (e1!=e) return(search_target_node(w,e1));
		}	
		if (NPRED(w)) {
			e1 = AKANTE(NPRED(w));
			if (e1!=e) return(search_target_node(w,e1));
		}	
	}
	return(w);
}


/* Fold subgraph event handler
 * ===========================
 * Wait for a selection of a node with the left mouse button.
 * Selections that do not touch a node have no effect.
 * Pushing another button than the right button stops this
 * procedure.
 */ 

static void	fold_subgraph_event_proc(myCanvas, event)
Canvas	myCanvas;
Event	*event;
{
	GNODE	v;

	if ( (event_id(event) == MS_LEFT) && event_is_down(event) ) {
		v = search_xy_node(event_x(event),event_y(event));
		if (v && NROOT(v)) {
			NSTATE(NROOT(v)) = 2;
			add_sgfoldstart(NROOT(v));
			buildCanvas();
			handle_selected_node(v);
		}
		else {  panel_outp("");
			panel_outp("This is not a node or it is not part of a subgraph. Try again!");
		}
	}
	else if ( (event_id(event) == MS_RIGHT) && event_is_down(event) ) {
		finish_selection();
	}
	else check_minimalkeyboard_event(event);
}



/* Unfold subgraph event handler
 * =============================
 * Wait for a selection of a node with the left mouse button.
 * Selections that do not touch a node have no effect.
 * Pushing another button than the right button stops this
 * procedure.
 */ 

static void	unfold_subgraph_event_proc(myCanvas, event)
Canvas	myCanvas;
Event	*event;
{
	GNODE	v;

	if ( (event_id(event) == MS_LEFT) && event_is_down(event) ) {
		v = search_xy_node(event_x(event),event_y(event));
		if (v  && NSGRAPH(v)) {
			NSTATE(v) = 0;
			add_sgunfoldstart(v);
			handle_selected_node(v);
		}
		else {  panel_outp("");
			panel_outp("This is not a node or it is not a subgraph summary node. Try again!");
		}
	}
	else if ( (event_id(event) == MS_RIGHT) && event_is_down(event) ) {
		finish_selection();
	}
	else check_minimalkeyboard_event(event);
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

static void	select_foldstops_proc(myCanvas, event)
Canvas	myCanvas;
Event	*event;
{
	GNODE	v;

	if ( (event_id(event) == MS_LEFT) && event_is_down(event) ) {
		v = search_xy_node(event_x(event),event_y(event));
		if (v) {
			add_foldstop(v);
			handle_selected_node(v);
		}
		else {  panel_outp("");
			panel_outp("This is not an appropriate  node. Try again!");
		}
	}
	else if ( (event_id(event) == MS_RIGHT) && event_is_down(event) ) {
		panel_outp("Select nodes: the 'Fold Region' operation starts from these nodes.");
		notify_no_dispatch();

		/* the fold stopper alone don't cause a relayout
		 */
		if (selected_flag) selected_flag = -1;

		/* set canvas event procedure new */
		activate_select_menu(fold_region_proc);
		set_fold_cursor();
	
		/* next interaction will cause a call of fold_region_proc */
	}
	else check_minimalkeyboard_event(event);
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

static void	fold_region_proc(myCanvas, event)
Canvas	myCanvas;
Event	*event;
{
	GNODE	v;

	if ( (event_id(event) == MS_LEFT) && event_is_down(event) ) {
		v = search_xy_node(event_x(event),event_y(event));
		if (v) {
			NFOLDING(v) = foldregion_class;
			add_foldstart(v);
			handle_selected_node(v);
		}
		else {  panel_outp("");
			panel_outp("This is not an appropriate node. Try again!");
		}
	}
	else if ( (event_id(event) == MS_RIGHT) && event_is_down(event) ) {
		finish_selection();
	}
	else check_minimalkeyboard_event(event);
}


/* Unfold region Event handler 
 * ===========================
 * Wait for a selection of a node with the left mouse button.
 * Selections that do not touch a node have no effect.
 * Pushing another button than the right button stops this
 * procedure.
 */ 

static void	unfold_region_proc(myCanvas, event)
Canvas	myCanvas;
Event	*event;
{
	GNODE	v;

	if ( (event_id(event) == MS_LEFT) && event_is_down(event) ) {
		v = search_xy_node(event_x(event),event_y(event));
		if (v && NREGREPL(v)) {
			add_unfoldstart(v);
			handle_selected_node(v);
		}
		else {  panel_outp("");
			panel_outp("This is not a node or it is not a region summary node. Try again!");
		}
	}
	else if ( (event_id(event) == MS_RIGHT) && event_is_down(event) ) {
		finish_selection();
	}
	else check_minimalkeyboard_event(event);
}


/* Selection of an info node
 * =========================
 * Wait for a selection of a node with the left mouse button.
 * Selections that do not touch a node have no effect.
 * Pushing another button than the right button stops this
 * procedure.
 */ 

static void	select_info_proc(myCanvas, event)
Canvas	myCanvas;
Event	*event;
{
	GNODE	v;

	if ( (event_id(event) == MS_LEFT) && event_is_down(event) ) {
		v = 0;
		if (search_and_close_infobox(
                        (event_x(event)+V_xmin)*G_shrink/G_stretch,
                        (event_y(event)+V_ymin)*G_shrink/G_stretch)) {
                	disable_signal();
                        buildCanvas();
                        enable_signal();
			panel_outp("Select a node to get information about this node.");
                        return;
      
		}
		else v = search_xy_node(event_x(event),event_y(event));
		if (v) {
			selected_flag = -1;
			if (truesize) gs_infobox(v,
     		  			NX(v), NY(v), 
					1,1,info_val);
			else          gs_infobox(v,
     		  			NX(v), NY(v), 
					G_stretch,G_shrink,info_val);
			window_set(myCanvas, WIN_SHOW, 	TRUE, 0);
		}
		else {  panel_outp("");
			panel_outp("This is not an appropriate node. Try again!");
		}
	}
	else if ( (event_id(event) == MS_RIGHT) && event_is_down(event) ) {
		free_infoboxes();
		finish_selection();
	}
	else check_minimalkeyboard_event(event);
}

/* Handle selection of nodes
 * -------------------------
 * If a node was selected, it is added to the folding keepers.
 * Depending whether the node was a folding keeper before, it is now
 * one ore not. Thus we must redisplay the node and notify the
 * selection.
 */

static void handle_selected_node(v)
GNODE v;
{
        gs_setshrink(G_stretch * NSTRETCH(v),
       		     G_shrink  * NSHRINK(v)  );
       	gs_setto(NX(v) * G_stretch / G_shrink,
       	         NY(v) * G_stretch / G_shrink );
	draw_one_node(v);
	window_set(myCanvas, WIN_SHOW, 	TRUE, 0);
	selected_flag = 1;
	panel_outp("Next node ... (right mouse button to continue).");
}

/* Finish the selection
 * --------------------
 * If something was selected, the selected_flag is true. Then, we must
 * relayout. Otherwise, we only must reinstall the main menu.
 */

static void finish_selection()
{
	panel_outp(""); 
	if (selected_flag==1) complete_relayout();
	else { 	clear_folding_keepers();
		if (selected_flag== -1) buildCanvas();
		main_menu_check(); 
	}
	selected_flag = 0;
}



/* Input of an position
 * ====================
 */

/* x co-ordinate 
 * -------------
 * The menu item position was selected. 
 * We have asked for an x-co-ordinate. Now we fetch this x-co-ordinate
 * and ask for the y-co-ordinate. 
 */

static void	x_proc(item, event)
Panel_item	item;
Event		*event;
{
	char	*xpos_string;

	xpos_string = (char *) panel_get(item, PANEL_VALUE);
	V_xmin = (atoi(xpos_string)*G_stretch)/G_shrink;
	V_xmax = V_xmin + G_xmax;

	/* ask for the y co-ordinate */
	ask_item2("y-co-ordinate:",y_proc);
}


/* y co-ordinate 
 * -------------
 * The menu item position was selected and we have already an x-co-cordinate. 
 * We have asked for an y-co-ordinate. Now we fetch this y-co-ordinate
 * and continue. 
 */

static void	y_proc(item, event)
Panel_item	item;
Event		*event;
{
	char	*ypos_string;

	ypos_string = (char *) panel_get(item, PANEL_VALUE);
	V_ymin = (atoi(ypos_string)*G_stretch)/G_shrink;
	V_ymax = V_ymin + G_ymax + COFFSET;

	clear_items();

	disable_signal(); 
        displayCanvas(); 
        enable_signal();

	panel_outp(""); 
	main_menu_check(); 
}

/* Pick a position by the mouse 
 * ============================
 */

static void	pic_position_proc(myCanvas, event)
Canvas	myCanvas;
Event	*event;
{

	if ( (event_id(event) == MS_LEFT) && event_is_down(event) ) {
		V_xmin += event_x(event);
		V_xmax = V_xmin + G_xmax;
		V_ymin += event_y(event);
		V_ymax = V_ymin + G_ymax + COFFSET;
	
		disable_signal(); 
       	 	displayCanvas(); 
       	 	enable_signal();

		panel_outp(""); 
		main_menu_check(); 
	}
}


/* Centering of nodes
 * ==================
 * We have asked for a title of a node. Now we fetch this title.
 */

static void	node_title_proc(item, event)
Panel_item	item;
Event		*event;
{
	char	*title;
	GNODE	v;
	int	x, y, width, height,w,h;

	title = (char *) panel_get(item, PANEL_VALUE);
	v = search_visible_node(title);
	if (v) {
		if (NINLIST(v)) {
			x      = (NX(v)*G_stretch)/G_shrink;
			y      = (NY(v)*G_stretch)/G_shrink;
			width  = (NWIDTH(v)*NSTRETCH(v)*G_stretch)/(NSHRINK(v)*G_shrink);
			height = (NHEIGHT(v)*NSTRETCH(v)*G_stretch)/(NSHRINK(v)*G_shrink); 
			w = (int)window_get(frame, WIN_WIDTH)-V_SCROLLBAR;
			h = (int)window_get(frame, WIN_HEIGHT)-COFFSET-H_SCROLLBAR;
			V_xmin = (x+width/2) - w/2;
			V_xmax = V_xmin + G_xmax;
			V_ymin = (y+height/2) - h/2;
			V_ymax = V_ymin + G_ymax + COFFSET;
			disable_signal(); 
       	        	displayCanvas(); 
                	enable_signal();
			panel_outp(""); 
		}
		else {
			clear_items();
			panel_outp("This title is currently not visible. Press button to continue."); 
			act_follow_edge = NULL;
			act_follow_node = NULL;
			if (!colored) G_color = WHITE;
			pw_writebackground(myPixwin, 
				0, 0, G_xmax, G_ymax+COFFSET, 
				(PIX_SRC | PIX_COLOR(COLOR(G_color))));
			V_xmin = 0;
			V_xmax = V_xmin + G_xmax;
			V_ymin = 0;
			V_ymax = V_ymin + G_ymax + COFFSET;
			NX(v) = NY(v) = 0;
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
			activate_select_menu(follow_centeredge_event_proc);
			return;
		}
	}
	else panel_outp("This title is not known."); 

	clear_items();
	main_menu_check(); 
}


/* Fetch a new file and load it
 * ============================
 */

static char fbuf[1024];

static void	load_proc(item, event)
Panel_item	item;
Event		*event;
{
	char	*name;
	FILE    *f;

	name = (char *) panel_get(item, PANEL_VALUE);

	if (load_save==LS_LOAD) {
		strcpy(Dataname, name);

		/* Check whether file is readable */
       	 	if ( strcmp(Dataname,"-")==0 ) { 
			panel_outp("Illegal filename."); 
			main_menu_check(); 
			return;
		}
       	 	f = fopen(Dataname,"r");
       	 	if (f == NULL) { 
			panel_outp("Cannot open file."); 
			main_menu_check(); 
			return;
       	 	}
		fclose(f);

		clear_items();
	
		set_busy_cursor();
		disable_signal(); 
		clear_hide_class();
		parse_part();
		visualize_part();
		resizeWindow(); 
       	 	displayCanvas(); 
       		enable_signal();
		return;
	}
	else if (load_save==LS_SAVEASCII) {
		if (name) strcpy(fbuf, name);
		clear_items();
		set_busy_cursor();
		disable_signal(); 
		if (!*fbuf) 
			panel_outp("Illegal filename."); 
		else if (!print_graph(fbuf))
			panel_outp("Error on writing file. File may exist or is unwriteable."); 
       		enable_signal();
       	 	displayCanvas(); 
       		enable_signal();
		return;
	}
	else if (load_save==LS_SAVEPBM) {
		if (name) strcpy(fbuf, name);
		clear_items();

		set_busy_cursor();
		print_pbm(fbuf, region_minx, region_miny, 
				region_maxx, region_maxy, 0, 0, 0,
				region_stretch, region_shrink); 
       		enable_signal();
       	 	displayCanvas(); 
       		enable_signal();
		return;
	}
	else if (load_save==LS_SAVEPPM) {
		if (name) strcpy(fbuf, name);
		clear_items();

		set_busy_cursor();
		print_ppm(fbuf, region_minx, region_miny, 
				region_maxx, region_maxy, 0, 0, 0,
				region_stretch, region_shrink); 
       		enable_signal();
       	 	displayCanvas(); 
       		enable_signal();
		return;
	}
}


/*--------------------------------------------------------------------*/
/*  Management of the ruler                                           */
/*--------------------------------------------------------------------*/

static void	ruler_paint()
{
	set_upper_ruler();
	set_lower_ruler();
	set_left_ruler();
	set_right_ruler();
}


static void	set_upper_ruler()
{
	int	l, i, j;
	char	*s;

	(G_color == BLACK) ?
		pw_vector(myPixwin,0,10,G_xmax,10,PIX_SRC,COLOR(WHITE)) :
		pw_vector(myPixwin,0,10,G_xmax,10,PIX_SRC,COLOR(BLACK));
	j = V_xmin + 100;
	i = 100;
	while (j < V_xmax)
	{
		set_h_scale(i,10);
		s = (char *)int_to_str((int)(j*G_shrink/G_stretch));
		l = strlen(s);
		if ( l%2 == 0 )
			set_value(i-l*4,30,s);
		else
			set_value(i-(l-1)*4-4,30,s);
		i += 100;
		j += 100;
	}
}


static void	set_lower_ruler()
{
	int	l, i, j;
	char	*s;

	(G_color == BLACK ) ?
	    pw_vector(myPixwin,0,G_ymax+COFFSET-24,G_xmax,G_ymax+COFFSET-24,
			PIX_SRC,COLOR(WHITE)) :
	    pw_vector(myPixwin,0,G_ymax+COFFSET-24,G_xmax,G_ymax+COFFSET-24,
			PIX_SRC,COLOR(BLACK)) ;
	j = V_xmin + 100;
	i = 100;
	while (j < V_xmax)
	{
		set_h_scale(i,G_ymax+COFFSET-24);
		s = (char *)int_to_str((int)(j*G_shrink/G_stretch));
		l = strlen(s);
		if ( l%2 == 0 )
			set_value(i-l*4,G_ymax+COFFSET-30,s);
		else
			set_value(i-(l-1)*4-4,G_ymax+COFFSET-30,s);
		i += 100;
		j += 100;
	}
}


static void	set_left_ruler()
{
	int	i, j;
	char	*s;

	(G_color == BLACK ) ?
		pw_vector(myPixwin,10,0,10,G_ymax+COFFSET,PIX_SRC,COLOR(WHITE)) :
		pw_vector(myPixwin,10,0,10,G_ymax+COFFSET,PIX_SRC,COLOR(BLACK));
	j = V_ymin + 100;
	i = 100;
	while (j < V_ymax)
	{
		set_v_scale(10,i);
		s = (char *)int_to_str((int)(j*G_shrink/G_stretch));
		set_value(16,i+4,s);
		i += 100;
		j += 100;
	}
}


static void	set_right_ruler()
{
	int	l, i, j;
	char	*s;

	(G_color == BLACK) ?
	    pw_vector(myPixwin,G_xmax-24,0,G_xmax-24,G_ymax+COFFSET,
			PIX_SRC,COLOR(WHITE)) :
	    pw_vector(myPixwin,G_xmax-24,0,G_xmax-24,G_ymax+COFFSET,
			PIX_SRC,COLOR(BLACK));
	j = V_ymin + 100;
	i = 100;
	while (i < V_ymax)
	{
		set_v_scale(G_xmax-24,i);
		s = (char *)int_to_str((int)(j*G_shrink/G_stretch));
		l = strlen(s);
		set_value(G_xmax-30-l*8,i+4,s);
		i += 100;
		j += 100;
	}
}


static void	set_h_scale(x,y)
int	x, y;
{
	(G_color == BLACK) ?
		pw_vector(myPixwin,x,y-5,x,y+5,PIX_SRC,COLOR(WHITE)) :
		pw_vector(myPixwin,x,y-5,x,y+5,PIX_SRC,COLOR(BLACK));
}


static void	set_v_scale(x,y)
int	x, y;
{
	(G_color == BLACK) ?
		pw_vector(myPixwin,x-5,y,x+5,y,PIX_SRC,COLOR(WHITE)) :
		pw_vector(myPixwin,x-5,y,x+5,y,PIX_SRC,COLOR(BLACK));
}


static void	set_value(x,y,s)
int	x, y;
char	*s;
{

	(G_color == BLACK) ?
		pw_text(myPixwin, x, y, (PIX_SRC | PIX_COLOR(COLOR(WHITE))), 0, s) :
		pw_text(myPixwin, x, y, (PIX_SRC | PIX_COLOR(COLOR(BLACK))), 0, s);
}


#endif /* SUNVIEW */

