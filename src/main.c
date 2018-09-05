/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*                                                                    */
/*              VCG : Visualization of Compiler Graphs                */
/*              --------------------------------------                */
/*                                                                    */
/*   file:         main.c                                             */
/*   version:      1.00.00                                            */
/*   creation:     1.4.1993                                           */
/*   author:       I. Lemke  (...-Version 0.99.99)                    */
/*                 G. Sander (Version 1.00.00-...)                    */  
/*                 Universitaet des Saarlandes, 66041 Saarbruecken    */
/*                 ESPRIT Project #5399 Compare                       */
/*   description:  Top level program                                  */
/*   status:       in work                                            */
/*                                                                    */
/*--------------------------------------------------------------------*/

#ifndef lint
static char *id_string="$Id: main.c,v 3.17 1995/02/08 11:11:14 sander Exp $";
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
 * $Log: main.c,v $
 * Revision 3.17  1995/02/08  11:11:14  sander
 * Distribution version 1.3.
 *
 * Revision 3.16  1994/12/23  18:12:45  sander
 * Manhatten layout added.
 * Option interface cleared.
 *
 * Revision 3.15  1994/11/25  15:43:29  sander
 * Printer interface added to allow to use VCG as a converter.
 *
 * Revision 3.14  1994/11/23  14:50:47  sander
 * Input behaviour changed. Better behaviour in the case that we have no
 * input file.
 * Option -nocopt added.
 *
 * Revision 3.13  1994/08/08  16:01:47  sander
 * Attributes xraster, xlraster, yraster added.
 *
 * Revision 3.12  1994/08/05  12:13:25  sander
 * Treelayout added. Attributes "treefactor" and "spreadlevel" added.
 * Scaling as abbreviation of "stretch/shrink" added.
 *
 * Revision 3.11  1994/08/03  14:03:59  sander
 * Version Number to 1.1 changed.
 *
 * Revision 3.10  1994/08/02  15:36:12  sander
 * Local crossing unwinding implemented.
 *
 * Revision 3.9  1994/06/07  14:09:59  sander
 * Splines implemented.
 * HP-UX, Linux, AIX, Sun-Os, IRIX compatibility tested.
 * The tool is now ready to be distributed.
 *
 * Revision 3.8  1994/05/17  16:35:59  sander
 * attribute node_align added to allow nodes to be centered in the levels.
 *
 * Revision 3.7  1994/05/16  08:56:03  sander
 * shape attribute (boxes, rhombs, ellipses, triangles) added.
 *
 * Revision 3.6  1994/05/05  08:20:30  sander
 * Algorithm late labels added: If labels are inserted
 * after partitioning, this may yield a better layout.
 *
 * Revision 3.5  1994/04/27  16:05:19  sander
 * Some general changes for the PostScript driver.
 * Horizontal order added. Bug fixes of the folding phases:
 * Folding of nested graphs works now.
 *
 * Revision 3.4  1994/03/04  19:11:24  sander
 * Specification of levels per node added.
 * X11 geometry behaviour (option -geometry) changed such
 * that the window is now opened automatically.
 *
 * Revision 3.3  1994/03/03  14:12:21  sander
 * median centering heuristics added to reduce crossings.
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
 * Revision 2.4  1994/01/21  19:33:46  sander
 * VCG Version tested on Silicon Graphics IRIX, IBM R6000 AIX and Sun 3/60.
 * Option handling improved. Option -grabinputfocus installed.
 * X11 Font selection scheme implemented. The user can now select a font
 * during installation.
 * Sun K&R C (a nonansi compiler) tested. Some portabitility problems solved.
 *
 * Revision 2.3  1994/01/03  15:29:06  sander
 * First complete X11 version.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "grammar.h"
#include "alloc.h"
#include "usrsignal.h"
#include "folding.h"
#include "steps.h"
#include "timelim.h"
#include "main.h"
#include "options.h"
#include "grprint.h"
#include "PSdev.h"
#include "timing.h"

#ifdef X11

#include <X11/Xos.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/Xproto.h>
#include <ctype.h>
#include <math.h>
#include "main.h"
#include "X11devpb.h"

#endif

/*--------------------------------------------------------------------*/

/* Prototypes
 * ==========
 */

/*  These functions are device dependent. Instead including all external
 *  device dependent h-files, we declare them here as external. This
 *  simplifies the selection of the device.
 *  Depending on the device, these functions are implemented in sunvdev.c 
 *  or X11dev.c.
 */

extern void display_part	_PP((void));
extern void setScreenSpecifics  _PP((void));
extern void gs_exit             _PP((int x));

static int   f_is_writable	_PP((char *fname));


/* Global variables
 * ================
 */


char short_banner[128];
char version_str[24]  = "V.1.3";
char date_str[48]     = "$Date: 1995/02/08 11:11:14 $";
char revision_str[48] = "$Revision: 3.17 $";



/*--------------------------------------------------------------------*/
/*  Main routines 						      */
/*--------------------------------------------------------------------*/


/*  The main program
 *  ================
 */


#ifdef ANSI_C
int main(int argc, char *argv[])
#else
int main(argc, argv)
int 	argc;
char	*argv[];
#endif
{
	char testvar;
	int i;

#ifdef NEVER
	printf("%d %d\n",sizeof(struct gnode),sizeof(struct gedge));
#endif

	testvar = -1;
	if (testvar != -1) {
		FPRINTF(stderr,"Warning: On this system, chars are unsigned.\n");
		FPRINTF(stderr,"This may yield problems with the graph folding operation.\n");
	}

	for (i=0; i<48; i++) {
		if (date_str[i]=='$')     date_str[i]=' ';	
		if (revision_str[i]=='$') revision_str[i]=' ';	
	}
	
	SPRINTF(short_banner,"USAAR Visualization Tool VCG/XVCG %s %s", 
			version_str, revision_str);

	set_signal();

	G_xmax = G_ymax = -1;

	if ( argc <= 1) {
		PRINTF("Filename: "); fflush(stdout);
		for (i=0; i<800; i++) {
			Dataname[i] = (char)fgetc(stdin);
			if (Dataname[i]==0) break;
			if (Dataname[i]==10) { Dataname[i] = 0; break; }
			if (Dataname[i]==13) { Dataname[i] = 0; break; }
		}
	}
	else {  /* Get arguments from the command line */

		if (!scanOptions(argc, argv)) print_basic_help(); /* and exit */
	}

	print_version_copyright();
	print_help(); 

	if (!Dataname[0]) {
		PRINTF("Filename: "); fflush(stdout);
		for (i=0; i<800; i++) {
			Dataname[i] = (char)fgetc(stdin);
			if (Dataname[i]==0) break;
			if (Dataname[i]==10) { Dataname[i] = 0; break; }
			if (Dataname[i]==13) { Dataname[i] = 0; break; }
		}
	}
	for (i=0; i<800; i++) { if (Dataname[i]!=' ') break; }
	strncpy(filename,&(Dataname[i]),  800-i);
	filename[ 800] = 0;
	
	for (i=0; i<800; i++) { if (filename[i]!=' ') break; }
	if (i==800)         print_basic_help(); /* and exit */ 
	if (filename[i]==0) print_basic_help(); /* and exit */ 

	if (fastflag) {
		min_baryiterations = 0;
		max_baryiterations = 2;
		min_mediumshifts = 0;
		max_mediumshifts = 2;
		min_centershifts = 0;
		max_centershifts = 2;
		max_edgebendings = 2;
		max_straighttune = 2;
	}

	if (!silent) { FPRINTF(stdout,"Wait "); FFLUSH(stdout); }
	parse_part();
	visualize_part();

	if (exfile) {

		/* Batch conversion mode is called: We initialize the format paramters
		 * and the produce the printout file.
		 */

		set_of_region(0L, 0L, 
			maximal_xpos + (long)G_xbase, 
			maximal_ypos + (long)G_ybase);
		act_output_type = extype; 
		act_paper_type  = expaper; 
		act_paper_num   = expapernum; 
		act_color_type  = excolor; 
		act_ori_type    = exori; 
		act_bbox        = exbbox; 
		set_of_xdpi(exxdpi);
		set_of_ydpi(exydpi);

		if (exscaling>0.0) 
			set_of_scaling(exscaling);
		else if ((exwidth>0.0) && (exheight>0.0))
			fit_of_heightwidth(exheight, exwidth);
		else if (exwidth>0.0)
			set_of_width(exwidth);
		else if (exheight>0.0)
			set_of_height(exheight);
		else set_of_maxspect();

		set_of_centerx();
		set_of_centery();

		if (exleftm >-0.5)   set_of_leftmargin  (exleftm);
		if (exrightm>-0.5)   set_of_rightmargin (exrightm);
		if (extopm >-0.5)    set_of_topmargin   (extopm);
		if (exbottomm >-0.5) set_of_topmargin   (exbottomm);

		if (f_is_writable(exfilename)) {
			switch (act_output_type) {
			case 0: (void)print_graph(exfilename);
				break;
			case 1:
			case 2: (void)print_pbm_or_ppm(
					exfilename, 0, 0,
					maximal_xpos + (long)G_xbase, 
					maximal_ypos + (long)G_ybase);
				break;
			case 3: (void)print_all_ps(
					exfilename, 0, 0,
					maximal_xpos + (long)G_xbase, 
					maximal_ypos + (long)G_ybase);
				break;
			}
		}
  		else {
			FPRINTF(stderr,"Error on writing file %s.", exfilename);
			FPRINTF(stderr," Illegal file name, or");
			FPRINTF(stderr," file may exist or is unwriteable.\n");
		} 
	}
	else {  /* Display part calls the display device driver. This is a 
		 * device dependent function !!!
		 * The device driver is basically a loop that draws the graph and
		 * reacts on interaction, until the FINISHING interaction is 
		 * selected.
		 */
		display_part(); 
	}

	return(0);
}


/*--------------------------------------------------------------------*/

/* Check whether file is writable
 * ==============================
 * Returns 1 if yes. .
 */

#ifdef ANSI_C
static int f_is_writable(char *fname)
#else
static int f_is_writable(fname)
char *fname;
#endif
{
        FILE *f;
        char *c;

        f = NULL;
        c = fname;
        while (*c) c++;
        if (c>fname) c--;
        if (*c=='/')  return(0); 
        if (( strcmp(fname,"-")==0 ) || (*fname==0))  return(0); 
        f = fopen(fname,"r");
        if (f != NULL) { fclose(f); return(0); }
        return(1);
}


/*--------------------------------------------------------------------*/

/*  Fatal Errors 
 *  ============
 *  Note: the parser uses internally the function fatal_error which is
 *  different.
 */


#ifdef ANSI_C
void Fatal_error(char *x,char *y)
#else
void Fatal_error(x,y)
char *x;
char *y;
#endif
{
      	FPRINTF(stderr,"Fatal error: %s %s !\n",x,y);
      	FPRINTF(stderr,"Aborted !\n");
        gs_exit(-1);
}



/*--------------------------------------------------------------------*/

/*  Call of the parser
 *  ==================
 */

#ifdef ANSI_C
void	parse_part(void)
#else
void	parse_part()
#endif
{
	int 	errs,i;

	start_time();
	debugmessage("parse_part","");

	/* We start from the scratch */

	info_name_available = 0;
	for (i=0; i<3; i++) info_names[i]=NULL;

	free_memory();
	yyin = NULL;

	if ( strcmp(Dataname,"-")==0 ) yyin = stdin;
	else {
	 	yyin = fopen(Dataname,"r");
		if (yyin == NULL) Fatal_error("Cannot open",Dataname);
       	}

	free_timelimit();
	if (G_timelimit>0) init_timelimit(G_timelimit);
        errs = parse();

        if ((yyin)&&(yyin!=stdin)) fclose(yyin);

        if (errs>0) Fatal_error("Syntax error","");
	assert((Syntax_Tree!=NULL));

	stop_time("parse_part");
}


/*--------------------------------------------------------------------*/

/*  Call of the visualizer 
 *  ======================
 */

#ifdef X11
static char geom_buffer[128];
#endif

#ifdef ANSI_C
void	visualize_part(void)
#else
void	visualize_part()
#endif
{
	debugmessage("visualize_part","");

	/* Init of the default values */

        G_title         = myalloc(256);
       	strncpy(G_title,Dataname,254);
	G_title[255] = 0;
        G_x             = -1L;
        G_y             = -1L;

	/* Check the output device */
	if (!exfile) {
        	setScreenSpecifics(); 	/* this sets G_width, G_height */
	}
	else {
		G_width = G_height = 700;
	}
	G_width_set  = 0;	/* because they are not set by */
	G_height_set = 0;	/* the specification           */
	if (!G_xymax_final) G_xmax = G_width+10;
        if (!G_xymax_final) G_ymax = G_height+10;
        G_xbase         = 5;
        G_ybase         = 5;
        G_dspace        = 0;
        G_xspace        = 20;
        G_yspace        = 70;
        G_orientation   = TOP_TO_BOTTOM;
        G_folding       = 0;
        G_color         = WHITE;
        G_displayel     = NO;
        G_dirtyel       = NO;
        G_shrink        = 1;
        G_stretch       = 1;
	G_yalign        = AL_CENTER;
	G_portsharing   = YES;
	G_arrowmode     = AMFIXED;
	G_xraster	= 1;
 	G_yraster	= 1;
 	G_dxraster	= 1;

	/* No edge class is hidden: initialize this */

	clear_hide_class();

	/* Check colors */

	if (colored== -1) {
#ifdef VMS
		if (RootWinMaxDepth ==1) colored = 0;
#else
        	if (maxDepth == 1)       colored = 0;
#endif
        	else /* maxDepth == 8 */ colored = 1;
	}

	/*  Analyze specification and allocate graph */

	step0_main();
	if (nr_errors!=0) Fatal_error("Wrong specification","");
	check_graph_consistency();

#ifdef X11
	if (!Xmygeometry) {
		if ((G_width_set)&&(G_height_set)) {
			if ((G_x != -1L) && (G_y != -1L)) 
				SPRINTF(geom_buffer,"%dx%d+%ld+%ld",
					G_width,G_height,G_x,G_y);
			else 	SPRINTF(geom_buffer,"%dx%d",G_width,G_height);
			Xmygeometry   = geom_buffer;
		}
		else if ((G_x != -1) && (G_y != -1)) {
				SPRINTF(geom_buffer,"+%ld+%ld",
					G_x,G_y);
			Xmygeometry   = geom_buffer;
		}
	}
#endif

	/* Set drawing area */

	G_xymax_final = 1;
        V_xmin = V_xmin_initial;
        V_xmax = V_xmin + (long)G_xmax;
        V_ymin = V_ymin_initial;
        V_ymax = V_ymin + (long)(G_ymax + COFFSET);

	relayout();
}


/* Relayout the graph 
 * ------------------
 */


#ifdef ANSI_C
void relayout(void)
#else
void relayout()
#endif
{
	debugmessage("relayout","");
        start_time();

	if (G_timelimit>0) init_timelimit(G_timelimit);
	free_all_lists();
        if (nr_errors==0) folding();
        stop_time("folding");

        if (!locFlag) {

		if (min_mediumshifts>max_mediumshifts)
			max_mediumshifts = min_mediumshifts;
		if (min_centershifts>max_centershifts)
			max_centershifts = min_centershifts;
		if (min_baryiterations>max_baryiterations)
			max_baryiterations = min_baryiterations;
		if (one_line_manhatten==1) manhatten_edges = 1;
		if ((manhatten_edges==1)&&(prio_phase==0)) prio_phase = 1;
		if ((prio_phase==1)&&(straight_phase==0)) straight_phase = 1;
		if ((prio_phase==0)&&(straight_phase==1)) prio_phase = 1;
		if (prio_phase==1)     {
			min_centershifts = 0;
			max_centershifts = 0;
		}
		if (G_dxraster<=0) G_dxraster = 1;
		if (G_xraster<=0)  G_xraster  = 1;
		if (G_xraster % G_dxraster) {
			G_xraster = (G_xraster/G_dxraster) * G_dxraster;
		}
	
		/* Calculate new layout */

                step1_main();
		if (nr_errors!=0) Fatal_error("Wrong specification","");

		/* step1_main calls tree_main, if TREE_LAYOUT.
		 */

		if (layout_flag != TREE_LAYOUT) {
                	step2_main();
			if (nr_errors!=0) Fatal_error("Wrong specification","");
                	step3_main();
			if (nr_errors!=0) Fatal_error("Wrong specification","");
		}
        	step4_main();
		if (nr_errors!=0) Fatal_error("Wrong specification","");
	}
	else {
		/* Prepare given layout: calculate co-ordinate of edges 
 		 * width and height of nodes etc.
		 */ 

		prepare_nodes();
	}
	free_timelimit();
}
	
/*--------------------------------------------------------------------*/
