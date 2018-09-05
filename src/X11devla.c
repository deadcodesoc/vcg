/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */
/*		--------------------------------------		      */
/*								      */
/*   file:	   X11devla.c					      */
/*   version:	   1.00.00					      */
/*   creation:	   9.4.93					      */
/*   author:	   I. Lemke  (...-Version 0.99.99)		      */
/*		   G. Sander (Version 1.00.00-...)		      */
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */
/*   description:  Device driver for X11, Layout Dialog Box	      */
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/

#ifndef lint
static char *id_string="$Id: X11devla.c,v 1.11 1995/02/14 17:15:43 sander Exp $";
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
 * $Log: X11devla.c,v $
 * Revision 1.11  1995/02/14  17:15:43  sander
 * Small bug: tree point was wrong.
 *
 * Revision 1.10  1995/02/08  15:58:59  sander
 * Small bug with K&R C solved.
 *
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
 * Revision 1.6  1994/08/05  12:13:25  sander
 * Treelayout added. Attributes "treefactor" and "spreadlevel" added.
 * Scaling as abbreviation of "stretch/shrink" added.
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
 * Revision 1.3  1994/05/17  16:39:10  sander
 * attribute node_align added to allow nodes to be centered in the levels.
 *
 * Revision 1.2  1994/05/16  08:56:03  sander
 * shape attribute (boxes, rhombs, ellipses, triangles) added.
 *
 * Revision 1.1  1994/05/05  08:20:30  sander
 * Initial revision
 *
 */

/************************************************************************
 * Device driver for X11: Layout Dialog Box    
 * ----------------------------------------
 *
 * This module contains the management of the dialog box that appears
 * if we want to change the layout.
 * 
 * This file provides the following functions:
 * ------------------------------------------
 *
 *    x11_init_layout_dialog(rd,rs)      initialize the dialogbox.
 *    x11_destroy_layout_dialog(rd,rs)   destroys   the dialogbox.
 *
 *    x11_print_layout_dialog()
 *
 *    This function opens the dialog box that allows to change the
 *    layout parameters. On successful exit (Okay-button), the
 *    layout parameters are updated, such that they become valid
 *    at the next relayout.  On every exit, the dialog box is
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
#include "X11devla.h"


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

static void 	read_40sc_scrollbar	_PP((int val,int i));
static void 	set_40sc_scrollbar	_PP((int i));
static void 	read_5sc_scrollbar	_PP((int val,int i));
static void 	read_5in_scrollbar	_PP((int val,int i));
static void 	set_5sc_scrollbar	_PP((int i));

static void 	read_downfacscrollbar	_PP((int val));
static void 	set_downfacscrollbar	_PP((void));
static void 	read_upfacscrollbar	_PP((int val));
static void 	set_upfacscrollbar	_PP((void));
static void 	read_nearfacscrollbar	_PP((int val));
static void 	set_nearfacscrollbar	_PP((void));
static void 	read_xbasescrollbar	_PP((int val));
static void 	set_xbasescrollbar	_PP((void));
static void 	read_ybasescrollbar	_PP((int val));
static void 	set_ybasescrollbar	_PP((void));
static void 	read_xspacescrollbar	_PP((int val));
static void 	set_xspacescrollbar	_PP((void));
static void 	read_xlspacescrollbar	_PP((int val));
static void 	set_xlspacescrollbar	_PP((void));
static void 	read_yspacescrollbar	_PP((int val));
static void 	set_yspacescrollbar	_PP((void));
static void 	read_baryscrollbar	_PP((int val));
static void 	set_baryscrollbar	_PP((void));
static void 	read_centerscrollbar	_PP((int val));
static void 	set_centerscrollbar	_PP((void));
static void 	read_mediumscrollbar	_PP((int val));
static void 	set_mediumscrollbar	_PP((void));
static void 	read_bendscrollbar	_PP((int val));
static void 	set_bendscrollbar	_PP((void));
static void 	read_strascrollbar	_PP((int val));
static void 	set_strascrollbar	_PP((void));
static void 	read_splinescrollbar	_PP((int val));
static void 	set_splinescrollbar	_PP((void));
static void 	read_tlimitscrollbar	_PP((int val));
static void 	set_tlimitscrollbar	_PP((void));
static void 	read_mbaryscrollbar	_PP((int val));
static void 	set_mbaryscrollbar	_PP((void));
static void 	read_mcenterscrollbar	_PP((int val));
static void 	set_mcenterscrollbar	_PP((void));
static void 	read_mmediumscrollbar	_PP((int val));
static void 	set_mmediumscrollbar	_PP((void));


/* Positions and Sizes
 * ===================
 */

/* Size of the dialog box */

#define DIAL_W   570
#define DIAL_H   514+18+18+18+7

/* Size of a normal point */

#define POINT_W  10 

/* Size of a normal button */

#define BUTTON_W   130

/* Sizes of a scrollbar and its thumb */

#define SCROLL_W  80  
#define SCROLLBAR_LEN 15

/* Position of the edge label phase */

#define ELPH_POS 237+7

/* Position of Layoutfactors: */

#define LFAC_POS ELPH_POS+20 

/* Position of Layoutspeeds */

#define LSPE_POS LFAC_POS+203

/* Position of Partition algorithms */

#define LPAR_POS LSPE_POS+23



/* Variables
 * =========
 */

/* Dialog handling: On success (i.e. Okay-Button), success becomes 1 */

static int dialog_notready = 1;
static int dialog_success  = 0;


/*  On-Off-points are buttons that switch their state if we select them */

#define MAX_ONOFF_POINTS 14 
static GS_SEL_POINT on_off_point[MAX_ONOFF_POINTS] = {

/* window,  text          , xpos, ypos, isval, selval , globvar                , key */ 
{  0     ,  "edge  labels",    5,   36,     0,      1 , &G_displayel           , 'l' },   
{  0     ,  "dirty labels",    5,   54,     0,      1 , &G_dirtyel             , 'd' },   
{  0     ,  "near edges"  ,    5,   72,     0,      1 , &near_edge_layout      , ' ' },   
{  0     ,  "double edges",    5,   90,     0,      0 , &summarize_double_edges, ' ' },   
{  0     ,  "finetuning"  ,    5,  108,     0,      1 , &fine_tune_layout      , ' ' },
{  0     ,  "splines"     ,    5,  126,     0,      1 , &G_spline              , ' ' },
{  0     ,  "manhatten edges", 5,  144,     0,      1 , &manhatten_edges       , ' ' },
{  0     ,  "smanhatten edges",5,  162,     0,      1 , &one_line_manhatten    , ' ' },
{  0     ,  "priority phase",  5,  180,     0,      1 , &prio_phase            , ' ' },
{  0     ,  "straight phase",  5,  198,     0,      1 , &straight_phase            , ' ' },
{  0     ,  "port sharing",    200,198,     0,    YES , &G_portsharing         , ' ' },
{  0     ,  "optimize phase 2",380,108,     0,      0 , &skip_baryphase2        , 'o' },
{  0     ,  "optimize local",  380,126,     0,      1 , &local_unwind          , ' ' },
{  0     ,  "fixed arrow heads",200,216,    0,AMFIXED , &G_arrowmode           , ' ' }
};

#define EDGE_LABLS 0
#define DIRT_LABLS 1
#define MANH_EDGES 6
#define SMAN_EDGES 7
#define PRIO_PHASE 8
#define STRA_PHASE 9


/*  Touch-points are buttons that don't their change state if we select them. 
 *  Instead, some other actions are performed. They don't correspond to 
 *  global variables.
 */

static int dummy;

#define MAX_TOUCH_POINTS 4 
static GS_SEL_POINT touch_point[MAX_TOUCH_POINTS] = {

/* window,  text       , xpos, ypos,     isval, selval, globvar , key */ 
{  0     ,  "slow&nice",  140, LSPE_POS,   0,      1  , &dummy  , 's' },   
{  0     ,  "normal"   ,  260, LSPE_POS,   0,      1  , &dummy  , 'n' },   
{  0     ,  "medium"   ,  360, LSPE_POS,   0,      1  , &dummy  , 'm' },   
{  0     ,  "fast&ugly",  460, LSPE_POS,   0,      1  , &dummy  , 'f' }
};

#define SLOWSPEED 0
#define NORMSPEED 1
#define MEDISPEED 2
#define FASTSPEED 3


/*  Radio buttons are partitioned into those that have the same global 
 *  variable. If a radio-button is selected, all other radio buttons 
 *  of the same partition became unselected. 
 */


#define MAX_RADIO_POINTS 27 
static GS_SEL_POINT radio_point[MAX_RADIO_POINTS] = {

/* window,  text           , xpos,     ypos, isval,  selval     , globvar             , key */ 
{  0     ,  "barycenter"   ,  380,       36,    0,      0       , &crossing_heuristics, ' ' },   
{  0     ,  "mediancenter" ,  380,       54,    0,      1       , &crossing_heuristics, ' ' },   
{  0     ,  "top to bottom",  200,       36,    0, TOP_TO_BOTTOM, &G_orientation,       '1' },   
{  0     ,  "bottom to top",  200,       54,    0, BOTTOM_TO_TOP, &G_orientation,       '2' },   
{  0     ,  "left to right",  200,       72,    0, LEFT_TO_RIGHT, &G_orientation,       '3' },   
{  0     ,  "right to left",  200,       90,    0, RIGHT_TO_LEFT, &G_orientation,       '4' },   

{  0     ,  "top"          ,  200,      153   , 0, AL_TOP       , &G_yalign,            '7' },
{  0     ,  "center"        , 280,      153   , 0, AL_CENTER    , &G_yalign,            '8' },
{  0     ,  "bottom"        , 380,      153   , 0, AL_BOTTOM    , &G_yalign,            '9' },
{  0     ,  "after folding",  160, ELPH_POS   , 0,      0       , &edge_label_phase,    ' ' },
{  0  ,"after partitioning",  340, ELPH_POS   , 0,      1       , &edge_label_phase,    ' ' },
{  0     ,  "normal"       ,    5, LPAR_POS+18, 0,      0       , &layout_flag,         ' ' },   
{  0     ,  "maxdepth"     ,    5, LPAR_POS+36, 0,      1       , &layout_flag,         ' ' },   
{  0     ,  "mindepth"     ,    5, LPAR_POS+54, 0,      2       , &layout_flag,         ' ' },   
{  0     ,  "minbackward"  ,  120, LPAR_POS+18, 0,      3       , &layout_flag,         ' ' },   
{  0     ,  "maxdegree"    ,  120, LPAR_POS+36, 0,     11       , &layout_flag,         ' ' },   
{  0     ,  "mindegree"    ,  120, LPAR_POS+54, 0,     10       , &layout_flag,         ' ' },   
{  0     ,  "maxindegree"  ,  270, LPAR_POS+18, 0,      7       , &layout_flag,         ' ' },   
{  0     ,  "maxoutdegree" ,  270, LPAR_POS+36, 0,      9       , &layout_flag,         ' ' },   
{  0     ,  "maxdepthslow" ,  270, LPAR_POS+54, 0,      4       , &layout_flag,         ' ' },   
{  0     ,  "minindegree"  ,  420, LPAR_POS+18, 0,      6       , &layout_flag,         ' ' },   
{  0     ,  "minoutdegree" ,  420, LPAR_POS+36, 0,      8       , &layout_flag,         ' ' },   
{  0     ,  "mindepthslow" ,  420, LPAR_POS+54, 0,      5       , &layout_flag,         ' ' },
{  0     ,  "dfs"          ,    5, LPAR_POS+72, 0,     12       , &layout_flag,         ' ' }, 
{  0     ,  "tree layout"  ,  120, LPAR_POS+72, 0, TREE_LAYOUT  , &layout_flag,         ' ' }, 
{  0     ,  "barymedian"   ,  380,       72,    0,      2       , &crossing_heuristics, ' ' },   
{  0     ,  "medianbary"   ,  380,       90,    0,      3       , &crossing_heuristics, ' ' }   

};


#define AFTER_FOLD   9
#define AFTER_PART   10
#define TREE_POINT   24


/*  Horizontal integer scrollbars are used to change a value by the read and 
 *  set functions. Here, these values must be integer values.
 */


#define MAX_HSCROLLBARS 18 

#ifdef ANSI_C
static GS_SCROLL_BAR hscrollbar[MAX_HSCROLLBARS] = {

    {  0, 0, 0, 0, "Down-factor:" ,"%d%", 5  , 120, 160, LFAC_POS+18 , SCROLL_W,
		0, &layout_downfactor  , &read_downfacscrollbar, &set_downfacscrollbar },
    {  0, 0, 0, 0, "Up  -factor:" ,"%d%", 5  , 120, 160, LFAC_POS+36 , SCROLL_W,
		0, &layout_upfactor    , &read_upfacscrollbar  , &set_upfacscrollbar   },
    {  0, 0, 0, 0, "Near-factor:" ,"%d%", 5  , 120, 160, LFAC_POS+54 , SCROLL_W,
		0, &layout_nearfactor  , &read_nearfacscrollbar, &set_nearfacscrollbar },
    {  0, 0, 0, 0, "X-Base:"      ,"%d%", 5  , 120, 160, LFAC_POS+72 , SCROLL_W,
		0, &G_xbase            , &read_xbasescrollbar  , &set_xbasescrollbar   },
    {  0, 0, 0, 0, "Y-Base:"      ,"%d%", 5  , 120, 160, LFAC_POS+90 , SCROLL_W,
		0, &G_ybase            , &read_ybasescrollbar  , &set_ybasescrollbar   },
    {  0, 0, 0, 0, "X-Space:"     ,"%d%", 5  , 120, 160, LFAC_POS+108, SCROLL_W,
		0, &G_xspace           , &read_xspacescrollbar , &set_xspacescrollbar  },
    {  0, 0, 0, 0, "Y-Space:"     ,"%d%", 5  , 120, 160, LFAC_POS+126, SCROLL_W,
		0, &G_yspace           , &read_yspacescrollbar , &set_yspacescrollbar  },
    {  0, 0, 0, 0, "XL-Space:"    ,"%d%", 5  , 120, 160, LFAC_POS+144, SCROLL_W,
		0, &G_dspace           , &read_xlspacescrollbar , &set_xlspacescrollbar  },
    {  0, 0, 0, 0, "Crossingred.:","%d%", 280, 410, 450, LFAC_POS+18 , SCROLL_W,
		0, &max_baryiterations , &read_baryscrollbar   , &set_baryscrollbar    },
    {  0, 0, 0, 0, "Mediumshifts:","%d%", 280, 410, 450, LFAC_POS+36 , SCROLL_W,
		0, &max_mediumshifts   , &read_mediumscrollbar , &set_mediumscrollbar  },
    {  0, 0, 0, 0, "Centershifts:","%d%", 280, 410, 450, LFAC_POS+54,  SCROLL_W,
		0, &max_centershifts   , &read_centerscrollbar , &set_centerscrollbar  },
    {  0, 0, 0, 0, "Straightlin.:","%d%", 280, 410, 450, LFAC_POS+72,  SCROLL_W,
		0, &max_straighttune   , &read_strascrollbar   , &set_strascrollbar    },
    {  0, 0, 0, 0, "Bendingsred.:","%d%", 280, 410, 450, LFAC_POS+90,  SCROLL_W,
		0, &max_edgebendings   , &read_bendscrollbar   , &set_bendscrollbar    },
    {  0, 0, 0, 0, "Crossingred.:","%d%", 280, 410, 450, LFAC_POS+126, SCROLL_W,
		0, &min_baryiterations , &read_mbaryscrollbar  , &set_mbaryscrollbar    },
    {  0, 0, 0, 0, "Mediumshifts:","%d%", 280, 410, 450, LFAC_POS+144, SCROLL_W,
		0, &min_mediumshifts   , &read_mmediumscrollbar, &set_mmediumscrollbar  },
    {  0, 0, 0, 0, "Centershifts:","%d%", 280, 410, 450, LFAC_POS+162,  SCROLL_W,
		0, &min_centershifts   , &read_mcenterscrollbar, &set_mcenterscrollbar  },
    {  0, 0, 0, 0, "Splinefactor:","%d%",   5, 120, 160, LFAC_POS+162, SCROLL_W,
		0, &G_flat_factor      , &read_splinescrollbar , &set_splinescrollbar  },
    {  0, 0, 0, 0, "Time limit:","%d%",     5, 120, 160, LFAC_POS+180, SCROLL_W,
		0, &G_timelimit        , &read_tlimitscrollbar , &set_tlimitscrollbar  }
};

#else

static GS_SCROLL_BAR hscrollbar[MAX_HSCROLLBARS] = {

    {  0, 0, 0, 0, "Down-factor:" ,"%d%", 5  , 120, 160, LFAC_POS+18 , SCROLL_W,
		0, &layout_downfactor  , read_downfacscrollbar, set_downfacscrollbar },
    {  0, 0, 0, 0, "Up  -factor:" ,"%d%", 5  , 120, 160, LFAC_POS+36 , SCROLL_W,
		0, &layout_upfactor    , read_upfacscrollbar  , set_upfacscrollbar   },
    {  0, 0, 0, 0, "Near-factor:" ,"%d%", 5  , 120, 160, LFAC_POS+54 , SCROLL_W,
		0, &layout_nearfactor  , read_nearfacscrollbar, set_nearfacscrollbar },
    {  0, 0, 0, 0, "X-Base:"      ,"%d%", 5  , 120, 160, LFAC_POS+72 , SCROLL_W,
		0, &G_xbase            , read_xbasescrollbar  , set_xbasescrollbar   },
    {  0, 0, 0, 0, "Y-Base:"      ,"%d%", 5  , 120, 160, LFAC_POS+90 , SCROLL_W,
		0, &G_ybase            , read_ybasescrollbar  , set_ybasescrollbar   },
    {  0, 0, 0, 0, "X-Space:"     ,"%d%", 5  , 120, 160, LFAC_POS+108, SCROLL_W,
		0, &G_xspace           , read_xspacescrollbar , set_xspacescrollbar  },
    {  0, 0, 0, 0, "Y-Space:"     ,"%d%", 5  , 120, 160, LFAC_POS+126, SCROLL_W,
		0, &G_yspace           , read_yspacescrollbar , set_yspacescrollbar  },
    {  0, 0, 0, 0, "XL-Space:"    ,"%d%", 5  , 120, 160, LFAC_POS+144, SCROLL_W,
		0, &G_dspace           , read_xlspacescrollbar ,set_xlspacescrollbar  },
    {  0, 0, 0, 0, "Crossingred.:","%d%", 280, 410, 450, LFAC_POS+18 , SCROLL_W,
		0, &max_baryiterations , read_baryscrollbar   , set_baryscrollbar    },
    {  0, 0, 0, 0, "Mediumshifts:","%d%", 280, 410, 450, LFAC_POS+36 , SCROLL_W,
		0, &max_mediumshifts   , read_mediumscrollbar , set_mediumscrollbar  },
    {  0, 0, 0, 0, "Centershifts:","%d%", 280, 410, 450, LFAC_POS+54,  SCROLL_W,
		0, &max_centershifts   , read_centerscrollbar , set_centerscrollbar  },
    {  0, 0, 0, 0, "Straightlin.:","%d%", 280, 410, 450, LFAC_POS+72,  SCROLL_W,
		0, &max_straighttune   , read_strascrollbar   , set_strascrollbar    },
    {  0, 0, 0, 0, "Bendingsred.:","%d%", 280, 410, 450, LFAC_POS+90,  SCROLL_W,
		0, &max_edgebendings   , read_bendscrollbar   , set_bendscrollbar    },
    {  0, 0, 0, 0, "Crossingred.:","%d%", 280, 410, 450, LFAC_POS+126, SCROLL_W,
		0, &min_baryiterations , read_mbaryscrollbar  , set_mbaryscrollbar    },
    {  0, 0, 0, 0, "Mediumshifts:","%d%", 280, 410, 450, LFAC_POS+144, SCROLL_W,
		0, &min_mediumshifts   , read_mmediumscrollbar, set_mmediumscrollbar  },
    {  0, 0, 0, 0, "Centershifts:","%d%", 280, 410, 450, LFAC_POS+162,  SCROLL_W,
		0, &min_centershifts   , read_mcenterscrollbar, set_mcenterscrollbar  },
    {  0, 0, 0, 0, "Splinefactor:","%d%",   5, 120, 160, LFAC_POS+162, SCROLL_W,
		0, &G_flat_factor      , read_splinescrollbar , set_splinescrollbar  },
    {  0, 0, 0, 0, "Time limit:","%d%",     5, 120, 160, LFAC_POS+180, SCROLL_W,
		0, &G_timelimit        , read_tlimitscrollbar , set_tlimitscrollbar  }
};
#endif

#define DOWNFAC     0
#define UPFAC       1
#define NEARFAC     2
#define XBASESCR    3
#define YBASESCR    4
#define XSPACESCR   5
#define YSPACESCR   6
#define XLSPACESCR  7
#define BARYSCR     8
#define MEDIUMSCR   9
#define CENTERSCR  10
#define STRASCR    11
#define BENDSCR    12
#define MBARYSCR   13
#define MMEDIUMSCR 14
#define MCENTERSCR 15
#define SPLINESCR  16
#define TLIMITSCR  17




/* Root displays */

static Display *root_display;	/* Root display          */
static int      root_screen;	/* and its screen number */


/* Windows */

static Window	dialog_window;

static Window   okay_button;
static Window   cancel_button;



/* Cursors */

static Cursor scrollCursor; 
static Cursor leftscrollCursor; 
static Cursor rightscrollCursor; 

/* Mouse Buttons */

#define G_MOUSE_LEFT  1
#define G_MOUSE_RIGHT 3


/* the panel font */

extern char Xfontname[512];
static  XFontStruct *dialog_font = NULL;

/* Flag wheter the dialog_box is initialized */

static int dialog_box_there = 0;

/* Flag whether the actual layout is tree layout */

static int is_tree_layout = 0;
static int mytreefactor;

/*--------------------------------------------------------------------*/
/*  Dialog box initialization and entry points                        */
/*--------------------------------------------------------------------*/

/*  Initialize the dialog box 
 *  -------------------------
 *  This is done once at the beginning.
 */

#ifdef ANSI_C
void 	x11_init_layout_dialog(Display *rd, int rs)
#else
void 	x11_init_layout_dialog(rd, rs)
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
void	x11_destroy_layout_dialog(Display *rd, int rs)
#else
void	x11_destroy_layout_dialog(rd, rs)
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
        strcat(x11_win_label, " Layout");

	XStoreName(root_display, dialog_window, x11_win_label);
	XSetNormalHints(root_display, dialog_window, &hints);

	XDefineCursor(root_display,dialog_window, 
			XCreateFontCursor(root_display,XC_left_ptr));

	scrollCursor = XCreateFontCursor(root_display,XC_sb_h_double_arrow);
	leftscrollCursor  = XCreateFontCursor(root_display,XC_sb_left_arrow);
	rightscrollCursor = XCreateFontCursor(root_display,XC_sb_right_arrow);

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
	

	cancel_button = allocate_button(420,195);
	okay_button   = allocate_button(420,164);
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
int x11_print_layout_dialog(void)
#else
int x11_print_layout_dialog()
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

	mytreefactor = (int)(tree_factor * 100);

	box_exposed = 0;

	for (i=0; i<MAX_ONOFF_POINTS; i++)
		on_off_point[i].is = *(on_off_point[i].glob);

	for (i=0; i<MAX_RADIO_POINTS; i++)
		radio_point[i].is = *(radio_point[i].glob);

	for (i=0; i<MAX_HSCROLLBARS; i++) 
		hscrollbar[i].is = *(hscrollbar[i].glob);

	is_tree_layout =  
		(radio_point[TREE_POINT].is == radio_point[TREE_POINT].sel);

	if (is_tree_layout) {
		hscrollbar[MEDIUMSCR].t = "Spreadlevel: ";
		hscrollbar[MEDIUMSCR].glob = &spread_level;
		hscrollbar[MEDIUMSCR].is   = spread_level;
		hscrollbar[CENTERSCR].t = "Treefactor:  ";
		hscrollbar[CENTERSCR].glob = &mytreefactor;
		hscrollbar[CENTERSCR].is = mytreefactor;
	}
	else {
		hscrollbar[MEDIUMSCR].t = "Mediumshifts:";
		hscrollbar[MEDIUMSCR].glob = &max_mediumshifts;
		hscrollbar[MEDIUMSCR].is   = max_mediumshifts;
		hscrollbar[CENTERSCR].t = "Centershifts:";
		hscrollbar[CENTERSCR].glob = &max_centershifts;
		hscrollbar[CENTERSCR].is = max_centershifts;
	}

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

        XMapRaised(root_display, okay_button);
        XMapRaised(root_display, cancel_button);
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

		for (i=0; i<MAX_ONOFF_POINTS; i++)
			*(on_off_point[i].glob) = on_off_point[i].is;

		for (i=0; i<MAX_RADIO_POINTS; i++) 
			if (radio_point[i].is == radio_point[i].sel) 
				*(radio_point[i].glob) = radio_point[i].is;

		for (i=0; i<MAX_HSCROLLBARS; i++) 
			*(hscrollbar[i].glob) = hscrollbar[i].is;

		tree_factor = (double)mytreefactor/(double)100;
		if (G_arrowmode!=AMFIXED) G_arrowmode = AMFREE;
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
	/* Dirtylabels => Labels */

	if (sel == DIRT_LABLS) {
	if (on_off_point[DIRT_LABLS].is == on_off_point[DIRT_LABLS].sel) {
		on_off_point[EDGE_LABLS].is = on_off_point[EDGE_LABLS].sel;
		if (redraw) draw_dialog_point(on_off_point[EDGE_LABLS].w,1);
	}
	}
	if (sel == EDGE_LABLS) {
	if (on_off_point[EDGE_LABLS].is != on_off_point[EDGE_LABLS].sel) {
	    	on_off_point[DIRT_LABLS].is= on_off_point[DIRT_LABLS].sel-1;
		if (redraw) draw_dialog_point(on_off_point[DIRT_LABLS].w,0);
	}
	}

	/* One_line_Manhatten => Manhatten phase */

	if (sel == SMAN_EDGES) {
	if (on_off_point[SMAN_EDGES].is == on_off_point[SMAN_EDGES].sel) {
		on_off_point[MANH_EDGES].is = on_off_point[MANH_EDGES].sel;
		if (redraw) draw_dialog_point(on_off_point[MANH_EDGES].w,1);
	}
	}
	if (sel == MANH_EDGES) {
	if (on_off_point[MANH_EDGES].is != on_off_point[MANH_EDGES].sel) {
	    	on_off_point[SMAN_EDGES].is= on_off_point[SMAN_EDGES].sel-1;
		if (redraw) draw_dialog_point(on_off_point[SMAN_EDGES].w,0);
	}
	}

	/* Manhatten => Priority phase, if prio_phase == 0 */

	if (  (on_off_point[MANH_EDGES].is == on_off_point[MANH_EDGES].sel) 
	    &&(on_off_point[PRIO_PHASE].is == 0)) {
		on_off_point[PRIO_PHASE].is = on_off_point[PRIO_PHASE].sel;
		if (redraw) draw_dialog_point(on_off_point[PRIO_PHASE].w,1);
	}

	/* Priority phase => Straight phase, if straight_phase == 0 */

	if (  (on_off_point[PRIO_PHASE].is == on_off_point[PRIO_PHASE].sel) 
	    &&(on_off_point[STRA_PHASE].is == 0)) {
		on_off_point[STRA_PHASE].is = on_off_point[STRA_PHASE].sel;
		if (redraw) draw_dialog_point(on_off_point[STRA_PHASE].w,1);
	}

	/* Straight phase => priority phase, if prio_phase == 0 */

	if (  (on_off_point[STRA_PHASE].is == on_off_point[STRA_PHASE].sel) 
	    &&(on_off_point[PRIO_PHASE].is == 0)) {
		on_off_point[PRIO_PHASE].is = on_off_point[PRIO_PHASE].sel;
		if (redraw) draw_dialog_point(on_off_point[PRIO_PHASE].w,1);
	}


	/* No labels => label phase = 0 */

	if (on_off_point[EDGE_LABLS].is != on_off_point[EDGE_LABLS].sel) {
		radio_point[AFTER_FOLD].is = radio_point[AFTER_FOLD].sel;
		radio_point[AFTER_PART].is = radio_point[AFTER_PART].sel-1;
		if (redraw) draw_dialog_point(radio_point[AFTER_FOLD].w,1);
		if (redraw) draw_dialog_point(radio_point[AFTER_PART].w,0);
	}

	/* Dirty labels => label phase = 0 */

	if (on_off_point[DIRT_LABLS].is == on_off_point[DIRT_LABLS].sel) {
		radio_point[AFTER_FOLD].is = radio_point[AFTER_FOLD].sel;
		radio_point[AFTER_PART].is = radio_point[AFTER_PART].sel-1;
		if (redraw) draw_dialog_point(radio_point[AFTER_FOLD].w,1);
		if (redraw) draw_dialog_point(radio_point[AFTER_PART].w,0);
	}

	if (hscrollbar[MBARYSCR].is > hscrollbar[BARYSCR].is)  
		hscrollbar[BARYSCR].is = hscrollbar[MBARYSCR].is; 
	if (hscrollbar[MMEDIUMSCR].is > hscrollbar[MEDIUMSCR].is)  
		hscrollbar[MEDIUMSCR].is = hscrollbar[MMEDIUMSCR].is; 
	if (hscrollbar[MCENTERSCR].is > hscrollbar[CENTERSCR].is)  
		hscrollbar[CENTERSCR].is = hscrollbar[MCENTERSCR].is; 
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

	draw_underl_text(5,18,"Layout Attributes");
	draw_underl_text(200,18,"Orientation");
	draw_underl_text(380,18,"Crossing-Heuristics");
	draw_underl_text(200,135,"Node Alignment");
	draw_underl_text(200,180,"Arrow Heads");
	draw_underl_text(5,ELPH_POS,"Adding Labels");
	draw_underl_text(5,LFAC_POS,"Layout Factors");
	draw_underl_text(5,LSPE_POS,"Layout Speed");
	draw_underl_text(5,LPAR_POS,"Partitioning Algorithm");

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
		120,LFAC_POS+4,100,10*18);
	XFillRectangle(root_display, 
		(Drawable)dialog_window,
		XDefaultGC(root_display, root_screen),
		410,LFAC_POS+4,100,10*18);

	special_constraints(0, -1);

	for (i=0; i<MAX_HSCROLLBARS; i++) {
		if (i==CENTERSCR) continue;
		if (i==TLIMITSCR) continue;
		if (hscrollbar[i].is == MAXINT) SPRINTF(mxbuffer, "inf."); 
		else SPRINTF(mxbuffer, hscrollbar[i].f, hscrollbar[i].is);
		draw_text(hscrollbar[i].xv,hscrollbar[i].y,mxbuffer);
	}

	i = CENTERSCR;
	if (is_tree_layout) {
		if (hscrollbar[i].is == MAXINT) hscrollbar[i].is = 330; 
		SPRINTF(mxbuffer, "%4.2f", (float)hscrollbar[i].is/100.0);
		draw_text(hscrollbar[i].xv,hscrollbar[i].y,mxbuffer);
	}
	else {
		if (hscrollbar[i].is == MAXINT) SPRINTF(mxbuffer, "inf."); 
		else SPRINTF(mxbuffer, hscrollbar[i].f, hscrollbar[i].is);
		draw_text(hscrollbar[i].xv,hscrollbar[i].y,mxbuffer);
	}
	i = TLIMITSCR;
	if (hscrollbar[i].is == 0) SPRINTF(mxbuffer, "inf."); 
	else SPRINTF(mxbuffer, hscrollbar[i].f, hscrollbar[i].is);
	draw_text(hscrollbar[i].xv,hscrollbar[i].y,mxbuffer);

	draw_underl_text(280,LFAC_POS,"Maximal Iteration Factors");
	draw_underl_text(280,LFAC_POS+108,"Minimal Iteration Factors");

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
				switch (i) {
				case MANH_EDGES: 
				case PRIO_PHASE: 
				case SMAN_EDGES: 
				case STRA_PHASE: 
					if (on_off_point[i].is != 
						on_off_point[i].sel)
							on_off_point[i].is = 2;
					break; 
				}
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

		/* Management of the touch buttons */

		switch (i) {
		case SLOWSPEED: 
			hscrollbar[TLIMITSCR].is  = 0;
			hscrollbar[BARYSCR].is    = MAXINT;
			hscrollbar[MEDIUMSCR].is  = MAXINT;
			hscrollbar[CENTERSCR].is  = MAXINT;
			hscrollbar[STRASCR].is    = MAXINT;
			hscrollbar[BENDSCR].is    = MAXINT;
			hscrollbar[MBARYSCR].is   = 0;
			hscrollbar[MMEDIUMSCR].is = 0;
			hscrollbar[MCENTERSCR].is = 0;
			break;
		case NORMSPEED:
			hscrollbar[TLIMITSCR].is  = 0;
			hscrollbar[BARYSCR].is    = MAXINT;
			hscrollbar[MEDIUMSCR].is  = 100;
			hscrollbar[CENTERSCR].is  = 100;
			hscrollbar[STRASCR].is    = 100;
			hscrollbar[BENDSCR].is    = 100;
			hscrollbar[MBARYSCR].is   = 0;
			hscrollbar[MMEDIUMSCR].is = 0;
			hscrollbar[MCENTERSCR].is = 0;
			break;
		case MEDISPEED:
			hscrollbar[TLIMITSCR].is  = 0;
			hscrollbar[BARYSCR].is    = 10;
			hscrollbar[MEDIUMSCR].is  = 20;
			hscrollbar[CENTERSCR].is  = 30;
			hscrollbar[STRASCR].is    = 50;
			hscrollbar[BENDSCR].is    = 50;
			hscrollbar[MBARYSCR].is   = 0;
			hscrollbar[MMEDIUMSCR].is = 0;
			hscrollbar[MCENTERSCR].is = 0;
			break;
		case FASTSPEED:
			hscrollbar[TLIMITSCR].is  = 0;
			hscrollbar[BARYSCR].is    = 2;
			hscrollbar[MEDIUMSCR].is  = 2;
			hscrollbar[CENTERSCR].is  = 2; 
			hscrollbar[STRASCR].is    = 2;
			hscrollbar[BENDSCR].is    = 2;
			hscrollbar[MBARYSCR].is   = 0;
			hscrollbar[MMEDIUMSCR].is = 0;
			hscrollbar[MCENTERSCR].is = 0;
			break;
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

		i = is_tree_layout;
		is_tree_layout =  
		   (radio_point[TREE_POINT].is == radio_point[TREE_POINT].sel);

		if (i!=is_tree_layout) {
			if (is_tree_layout) {
				hscrollbar[MEDIUMSCR].t = "Spreadlevel: ";
				hscrollbar[MEDIUMSCR].glob = &spread_level;
				hscrollbar[MEDIUMSCR].is   = spread_level;
				hscrollbar[CENTERSCR].t = "Treefactor:  ";
				hscrollbar[CENTERSCR].glob = &mytreefactor;
				hscrollbar[CENTERSCR].is = mytreefactor;
			}
			else {
				hscrollbar[MEDIUMSCR].t = "Mediumshifts:";
				hscrollbar[MEDIUMSCR].glob = &max_mediumshifts;
				hscrollbar[MEDIUMSCR].is   = max_mediumshifts;
				hscrollbar[CENTERSCR].t = "Centershifts:";
				hscrollbar[CENTERSCR].glob = &max_centershifts;
				hscrollbar[CENTERSCR].is = max_centershifts;
			}
			draw_dialog_box();
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
	switch (i) {
	case MANH_EDGES: 
	case SMAN_EDGES: 
	case PRIO_PHASE: 
	case STRA_PHASE: 
		if (on_off_point[i].is != on_off_point[i].sel)
			on_off_point[i].is = 2;
		break; 
	}

	special_constraints(1, i);


	for (i=0; i<MAX_TOUCH_POINTS; i++) {
		if (w == touch_point[i].w) break;
	}

	switch (i) {
	case SLOWSPEED: 
		hscrollbar[TLIMITSCR].is  = 0;
		hscrollbar[BARYSCR].is    = MAXINT;
		hscrollbar[MEDIUMSCR].is  = MAXINT;
		hscrollbar[CENTERSCR].is  = MAXINT;
		hscrollbar[STRASCR].is    = MAXINT;
		hscrollbar[BENDSCR].is    = MAXINT;
		hscrollbar[MBARYSCR].is   = 0;
		hscrollbar[MMEDIUMSCR].is = 0;
		hscrollbar[MCENTERSCR].is = 0;
		draw_dialog_box();
		break;
	case NORMSPEED:
		hscrollbar[TLIMITSCR].is  = 0;
		hscrollbar[BARYSCR].is    = MAXINT;
		hscrollbar[MEDIUMSCR].is  = 100;
		hscrollbar[CENTERSCR].is  = 100;
		hscrollbar[STRASCR].is    = 100;
		hscrollbar[BENDSCR].is    = 100;
		hscrollbar[MBARYSCR].is   = 0;
		hscrollbar[MMEDIUMSCR].is = 0;
		hscrollbar[MCENTERSCR].is = 0;
		draw_dialog_box();
		break;
	case MEDISPEED:
		hscrollbar[TLIMITSCR].is  = 0;
		hscrollbar[BARYSCR].is    = 10;
		hscrollbar[MEDIUMSCR].is  = 20;
		hscrollbar[CENTERSCR].is  = 30;
		hscrollbar[STRASCR].is    = 50;
		hscrollbar[BENDSCR].is    = 50;
		hscrollbar[MBARYSCR].is   = 0;
		hscrollbar[MMEDIUMSCR].is = 0;
		hscrollbar[MCENTERSCR].is = 0;
		draw_dialog_box();
		break;
	case FASTSPEED:
		hscrollbar[TLIMITSCR].is  = 0;
		hscrollbar[BARYSCR].is    = 2;
		hscrollbar[MEDIUMSCR].is  = 2;
		hscrollbar[CENTERSCR].is  = 2; 
		hscrollbar[STRASCR].is    = 2;
		hscrollbar[BENDSCR].is    = 2;
		hscrollbar[MBARYSCR].is   = 0;
		hscrollbar[MMEDIUMSCR].is = 0;
		hscrollbar[MCENTERSCR].is = 0;
		draw_dialog_box();
		break;
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

	i = is_tree_layout;
	is_tree_layout =  
		(radio_point[TREE_POINT].is == radio_point[TREE_POINT].sel);
	if (i!=is_tree_layout) {
		if (is_tree_layout) {
			hscrollbar[MEDIUMSCR].t = "Spreadlevel: ";
			hscrollbar[MEDIUMSCR].glob = &spread_level;
			hscrollbar[MEDIUMSCR].is   = spread_level;
			hscrollbar[CENTERSCR].t = "Treefactor:  ";
			hscrollbar[CENTERSCR].glob = &mytreefactor;
			hscrollbar[CENTERSCR].is = mytreefactor;
		}
		else {
			hscrollbar[MEDIUMSCR].t = "Mediumshifts:";
			hscrollbar[MEDIUMSCR].glob = &max_mediumshifts;
			hscrollbar[MEDIUMSCR].is   = max_mediumshifts;
			hscrollbar[CENTERSCR].t = "Centershifts:";
			hscrollbar[CENTERSCR].glob = &max_centershifts;
			hscrollbar[CENTERSCR].is = max_centershifts;
		}
		draw_dialog_box();
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
		 		hscrollbar[i].is -= 5;
		  	else	hscrollbar[i].is -= 1;
		 	(*(hscrollbar[i].sf))();
			draw_sizes();
		}
		if (act_scroll_window==hscrollbar[i].wr) {
		 	if (hscrollbar[i].is < MAXINT-5) {
				if (e->button==G_MOUSE_LEFT)
		 			hscrollbar[i].is += 5;
		  		else	hscrollbar[i].is += 1;
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

	for (i=0; i<MAX_ONOFF_POINTS; i++)
		if (w==on_off_point[i].w) is_point = 1;
	for (i=0; i<MAX_TOUCH_POINTS; i++)
		if (w==touch_point[i].w) is_point = 1;
	for (i=0; i<MAX_RADIO_POINTS; i++)
		if (w==radio_point[i].w) is_point = 1;

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
/*  Scrollbar handling 						      */
/*--------------------------------------------------------------------*/


/*  General scrollbar actions with scaling 1
 *  ----------------------------------------
 *  The general scrollbar actions for bars that have a scaling of 1, i.e.
 *  produce values 0, 2 ..., 40.
 */


#ifdef ANSI_C
static void read_40sc_scrollbar(int val,int i)
#else
static void read_40sc_scrollbar(val,i)
int val;
int i;
#endif
{
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= hscrollbar[i].len) 
		val = hscrollbar[i].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,hscrollbar[i].wt,val,0,SCROLLBAR_LEN,6);
	hscrollbar[i].is = 0 + 39*val/(hscrollbar[i].len-SCROLLBAR_LEN);
}


#ifdef ANSI_C
static void set_40sc_scrollbar(int i)
#else
static void set_40sc_scrollbar(i)
int i;
#endif
{
	int val;

	if (hscrollbar[i].is<0)  hscrollbar[i].is = 0;
	if (hscrollbar[i].is>39) hscrollbar[i].is = 39;
	val =  (hscrollbar[i].is)*(hscrollbar[i].len-SCROLLBAR_LEN)/39;
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= hscrollbar[i].len) 
		val = hscrollbar[i].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display, hscrollbar[i].wt,val,0,SCROLLBAR_LEN,6);
}




/*  General scrollbar actions with scaling 5
 *  ----------------------------------------
 *  The general scrollbar actions for bars that have a scaling of 5, i.e.
 *  produce values 0, 5, 10, ..., 325.
 */

#ifdef ANSI_C
static void read_5sc_scrollbar(int val,int i)
#else
static void read_5sc_scrollbar(val,i)
int val;
int i;
#endif
{
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= hscrollbar[i].len) 
		val = hscrollbar[i].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,hscrollbar[i].wt,val,0,SCROLLBAR_LEN,6);
	hscrollbar[i].is = 5*val;
}

#ifdef ANSI_C
static void set_5sc_scrollbar(int i)
#else
static void set_5sc_scrollbar(i)
int i;
#endif
{
	int val;

	if (hscrollbar[i].is<0)  hscrollbar[i].is = 0;
	if (hscrollbar[i].is>325) hscrollbar[i].is = 325;
	val =  hscrollbar[i].is/5;
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= hscrollbar[i].len) 
		val = hscrollbar[i].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display, hscrollbar[i].wt,val,0,SCROLLBAR_LEN,6);
}



/*  General scrollbar actions with scaling 5 and infinite
 *  -----------------------------------------------------
 *  The general scrollbar actions for bars that have a scaling of 5, i.e.
 *  produce values 0, 5, 10, ..., 320, infinite.
 */

#ifdef ANSI_C
static void read_5in_scrollbar(int val,int i)
#else
static void read_5in_scrollbar(val,i)
int val;
int i;
#endif
{
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= hscrollbar[i].len) 
		val = hscrollbar[i].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,hscrollbar[i].wt,val,0,SCROLLBAR_LEN,6);
	hscrollbar[i].is = 5*val;
	if (val == hscrollbar[i].len - SCROLLBAR_LEN) hscrollbar[i].is = MAXINT;
}

#ifdef ANSI_C
static void set_5in_scrollbar(int i)
#else
static void set_5in_scrollbar(i)
int i;
#endif
{
	int val;

	if (hscrollbar[i].is<0)    hscrollbar[i].is = 0;
	if (hscrollbar[i].is>=325) hscrollbar[i].is = MAXINT;
	val =  hscrollbar[i].is/5;
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= hscrollbar[i].len) 
		val = hscrollbar[i].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display, hscrollbar[i].wt,val,0,SCROLLBAR_LEN,6);
}



/*  The instances of the scrollbars actions
 *  ---------------------------------------
 */

#ifdef ANSI_C
static void read_downfacscrollbar(int val)
#else
static void read_downfacscrollbar(val)
int val;
#endif
{
	read_40sc_scrollbar(val,DOWNFAC);
}

#ifdef ANSI_C
static void set_downfacscrollbar(void)
#else
static void set_downfacscrollbar()
#endif
{
	set_40sc_scrollbar(DOWNFAC);
}

#ifdef ANSI_C
static void read_upfacscrollbar(int val)
#else
static void read_upfacscrollbar(val)
int val;
#endif
{
	read_40sc_scrollbar(val,UPFAC);
}

#ifdef ANSI_C
static void set_upfacscrollbar(void)
#else
static void set_upfacscrollbar()
#endif
{
	set_40sc_scrollbar(UPFAC);
}

#ifdef ANSI_C
static void read_nearfacscrollbar(int val)
#else
static void read_nearfacscrollbar(val)
int val;
#endif
{
	read_40sc_scrollbar(val,NEARFAC);
}

#ifdef ANSI_C
static void set_nearfacscrollbar(void)
#else
static void set_nearfacscrollbar()
#endif
{
	set_40sc_scrollbar(NEARFAC);
}

#ifdef ANSI_C
static void read_xbasescrollbar(int val)
#else
static void read_xbasescrollbar(val)
int val;
#endif
{
	read_5sc_scrollbar(val,XBASESCR);
}

#ifdef ANSI_C
static void set_xbasescrollbar(void)
#else
static void set_xbasescrollbar()
#endif
{
	set_5sc_scrollbar(XBASESCR);
}

#ifdef ANSI_C
static void read_ybasescrollbar(int val)
#else
static void read_ybasescrollbar(val)
int val;
#endif
{
	read_5sc_scrollbar(val,YBASESCR);
}

#ifdef ANSI_C
static void set_ybasescrollbar(void)
#else
static void set_ybasescrollbar()
#endif
{
	set_5sc_scrollbar(YBASESCR);
}

#ifdef ANSI_C
static void read_xspacescrollbar(int val)
#else
static void read_xspacescrollbar(val)
int val;
#endif
{
	read_5sc_scrollbar(val,XSPACESCR);
}

#ifdef ANSI_C
static void set_xspacescrollbar(void)
#else
static void set_xspacescrollbar()
#endif
{
	set_5sc_scrollbar(XSPACESCR);
}

#ifdef ANSI_C
static void read_xlspacescrollbar(int val)
#else
static void read_xlspacescrollbar(val)
int val;
#endif
{
	read_5sc_scrollbar(val,XLSPACESCR);
}

#ifdef ANSI_C
static void set_xlspacescrollbar(void)
#else
static void set_xlspacescrollbar()
#endif
{
	set_5sc_scrollbar(XLSPACESCR);
}

#ifdef ANSI_C
static void read_yspacescrollbar(int val)
#else
static void read_yspacescrollbar(val)
int val;
#endif
{
	read_5sc_scrollbar(val,YSPACESCR);
}

#ifdef ANSI_C
static void set_yspacescrollbar(void)
#else
static void set_yspacescrollbar()
#endif
{
	set_5sc_scrollbar(YSPACESCR);
}

#ifdef ANSI_C
static void read_baryscrollbar(int val)
#else
static void read_baryscrollbar(val)
int val;
#endif
{
	read_5in_scrollbar(val,BARYSCR);
}

#ifdef ANSI_C
static void set_baryscrollbar(void)
#else
static void set_baryscrollbar()
#endif
{
	set_5in_scrollbar(BARYSCR);
}

#ifdef ANSI_C
static void read_mediumscrollbar(int val)
#else
static void read_mediumscrollbar(val)
int val;
#endif
{
	read_5in_scrollbar(val,MEDIUMSCR);
}

#ifdef ANSI_C
static void set_mediumscrollbar(void)
#else
static void set_mediumscrollbar()
#endif
{
	set_5in_scrollbar(MEDIUMSCR);
}

#ifdef ANSI_C
static void read_centerscrollbar(int val)
#else
static void read_centerscrollbar(val)
int val;
#endif
{
	read_5in_scrollbar(val,CENTERSCR);
}

#ifdef ANSI_C
static void set_centerscrollbar(void)
#else
static void set_centerscrollbar()
#endif
{
	set_5in_scrollbar(CENTERSCR);
}

#ifdef ANSI_C
static void read_mbaryscrollbar(int val)
#else
static void read_mbaryscrollbar(val)
int val;
#endif
{
	read_5sc_scrollbar(val,MBARYSCR);
}

#ifdef ANSI_C
static void set_mbaryscrollbar(void)
#else
static void set_mbaryscrollbar()
#endif
{
	set_5sc_scrollbar(MBARYSCR);
}

#ifdef ANSI_C
static void read_mmediumscrollbar(int val)
#else
static void read_mmediumscrollbar(val)
int val;
#endif
{
	read_5sc_scrollbar(val,MMEDIUMSCR);
}

#ifdef ANSI_C
static void set_mmediumscrollbar(void)
#else
static void set_mmediumscrollbar()
#endif
{
	set_5sc_scrollbar(MMEDIUMSCR);
}

#ifdef ANSI_C
static void read_mcenterscrollbar(int val)
#else
static void read_mcenterscrollbar(val)
int val;
#endif
{
	read_5sc_scrollbar(val,MCENTERSCR);
}

#ifdef ANSI_C
static void set_mcenterscrollbar(void)
#else
static void set_mcenterscrollbar()
#endif
{
	set_5sc_scrollbar(MCENTERSCR);
}

#ifdef ANSI_C
static void read_bendscrollbar(int val)
#else
static void read_bendscrollbar(val)
int val;
#endif
{
	read_5in_scrollbar(val,BENDSCR);
}

#ifdef ANSI_C
static void set_bendscrollbar(void)
#else
static void set_bendscrollbar()
#endif
{
	set_5in_scrollbar(BENDSCR);
}

#ifdef ANSI_C
static void read_strascrollbar(int val)
#else
static void read_strascrollbar(val)
int val;
#endif
{
	read_5in_scrollbar(val,STRASCR);
}

#ifdef ANSI_C
static void set_strascrollbar(void)
#else
static void set_strascrollbar()
#endif
{
	set_5in_scrollbar(STRASCR);
}


#ifdef ANSI_C
static void read_splinescrollbar(int val)
#else
static void read_splinescrollbar(val)
int val;
#endif
{
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= hscrollbar[SPLINESCR].len) 
		val = hscrollbar[SPLINESCR].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,hscrollbar[SPLINESCR].wt,
			val,0,SCROLLBAR_LEN,6);
	hscrollbar[SPLINESCR].is = 
		1 + 99*val/(hscrollbar[SPLINESCR].len-SCROLLBAR_LEN);
}

#ifdef ANSI_C
static void set_splinescrollbar(void)
#else
static void set_splinescrollbar()
#endif
{
	int val;

	if (hscrollbar[SPLINESCR].is<1)   hscrollbar[SPLINESCR].is = 1;
	if (hscrollbar[SPLINESCR].is>100) hscrollbar[SPLINESCR].is = 100;
	val =  (hscrollbar[SPLINESCR].is-1)*
			(hscrollbar[SPLINESCR].len-SCROLLBAR_LEN)/99;
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= hscrollbar[SPLINESCR].len) 
		val = hscrollbar[SPLINESCR].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display, hscrollbar[SPLINESCR].wt,
			val,0,SCROLLBAR_LEN,6);
}

#ifdef ANSI_C
static void read_tlimitscrollbar(int val)
#else
static void read_tlimitscrollbar(val)
int val;
#endif
{
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= hscrollbar[TLIMITSCR].len) 
		val = hscrollbar[TLIMITSCR].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display,hscrollbar[TLIMITSCR].wt,
		val,0,SCROLLBAR_LEN,6);
	hscrollbar[TLIMITSCR].is = 5+5*val;
	if (val == hscrollbar[TLIMITSCR].len - SCROLLBAR_LEN) 
		hscrollbar[TLIMITSCR].is = 0;
}

#ifdef ANSI_C
static void set_tlimitscrollbar(void)
#else
static void set_tlimitscrollbar()
#endif
{
	int val;

	if (   (hscrollbar[TLIMITSCR].is!=0) 
	    && (hscrollbar[TLIMITSCR].is<5))    hscrollbar[TLIMITSCR].is = 5;
	if (hscrollbar[TLIMITSCR].is>=325) hscrollbar[TLIMITSCR].is = 0;
	val =  (hscrollbar[TLIMITSCR].is-5)/5;
	if (val<0) val = 0;
	if (val+SCROLLBAR_LEN >= hscrollbar[TLIMITSCR].len) 
		val = hscrollbar[TLIMITSCR].len - SCROLLBAR_LEN;
	if (hscrollbar[TLIMITSCR].is==0)
		val = hscrollbar[TLIMITSCR].len - SCROLLBAR_LEN;
	XMoveResizeWindow(root_display, hscrollbar[TLIMITSCR].wt,
		val,0,SCROLLBAR_LEN,6);
}


/*--------------------------------------------------------------------*/

#endif /* X11 */

