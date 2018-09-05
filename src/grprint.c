/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */ 
/*		--------------------------------------		      */ 
/*								      */
/*   file:	   grprint.c					      */
/*   version:	   1.00.00					      */
/*   creation:	   14.4.93					      */
/*   author:	   G. Sander (Version 1.00.00-...)		      */ 
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */ 
/*   description:  Print layout into a file   			      */ 
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/


#ifndef lint
static char *id_string="$Id: grprint.c,v 3.8 1995/02/08 11:11:14 sander Exp $";
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
 * $Log: grprint.c,v $
 * Revision 3.8  1995/02/08  11:11:14  sander
 * Distribution version 1.3.
 *
 * Revision 3.7  1994/12/23  18:12:45  sander
 * Manhatten layout added.
 * Option interface cleared.
 * infobox behaviour improved.
 * First version of fisheye (carthesian).
 * Options Noedge and nonode.
 *
 * Revision 3.6  1994/08/03  13:58:44  sander
 * Horizontal order mechanism changed.
 * Attribute horizontal_order for edges added.
 *
 * Revision 3.5  1994/06/07  14:09:59  sander
 * Splines implemented.
 * HP-UX, Linux, AIX, Sun-Os, IRIX compatibility tested.
 * The tool is now ready to be distributed.
 *
 * Revision 3.4  1994/05/17  16:39:10  sander
 * attribute node_align added to allow nodes to be centered in the levels.
 *
 * Revision 3.3  1994/05/16  08:56:03  sander
 * shape attribute (boxes, rhombs, ellipses, triangles) added.
 *
 * Revision 3.2  1994/05/05  08:20:30  sander
 * Small corrections.
 *
 * Revision 3.1  1994/03/01  10:59:55  sander
 * Copyright and Gnu Licence message added.
 * Problem with "nearedges: no" and "selfloops" solved.
 *
 * Revision 2.2  1994/01/21  19:33:46  sander
 * VCG Version tested on Silicon Graphics IRIX, IBM R6000 AIX and Sun 3/60.
 * Option handling improved. Option -grabinputfocus installed.
 * X11 Font selection scheme implemented. The user can now select a font
 * during installation.
 * Sun K&R C (a nonansi compiler) tested. Some portabitility problems solved.
 *
 * Revision 2.1  1993/12/08  21:20:09  sander
 * Reasonable fast and stable version
 *
 *
 */

/************************************************************************
 *  This file allows to write a layouted graph into a file in
 *  such a way that this file can be reloaded.
 *
 *  This file here provides the following functions:
 *    print_graph	      prints the full graph in ASCII form to a
 *			      file
 *    color_text	      converts a color into a text
 *    textmode_text	      converts a textmode into a text
 *    linestyle_text	      converts a linestyle into a text
 ************************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "main.h"
#include "options.h"
#include "alloc.h"
#include "folding.h"
#include "steps.h"
#include "fisheye.h"
#include "grprint.h"

/*  Prototypes
 *  ---------- 
 */

static void open_graph  _PP(( FILE *f));
static void print_node	_PP(( FILE *f, GNODE v));
static void bbend_node  _PP(( FILE *f, GEDGE e, int k));
static void tbend_node  _PP(( FILE *f, GEDGE e, int k));
static void print_edge  _PP(( FILE *f, GEDGE e));


/* For indentation */

static int actindent;

/*--------------------------------------------------------------------*/
/*   Print all nodes and edges		         		      */
/*--------------------------------------------------------------------*/

/* Macro for indentation */

#define INDPRINT(f,fmt,arg) {{ int i;\
 for (i=0; i<actindent; i++) FPRINTF(f,"  "); FPRINTF(f,fmt,arg); }}

/* Macro to detect backward connections */

#define backward_connection1(c) ((CEDGE(c))&& (EEND(CEDGE(c)) ==v))
#define backward_connection2(c) ((CEDGE2(c))&&(EEND(CEDGE2(c))==v))


#ifdef ANSI_C
int print_graph(char *fname)
#else
int print_graph(fname)
char *fname;
#endif
{
	GNODE v;
	ADJEDGE li;
	CONNECT c;
	FILE *f;

	actindent = 0;

	f = fopen(fname,"r");
	if (f!=NULL) return(0);
	if (f) fclose(f);
	f = fopen(fname,"w");
	if (f==NULL) return(0);

	open_graph(f);
	v = nodelist;
	while (v) { print_node(f,v); v = NNEXT(v); }
	v = labellist;
	while (v) { print_node(f,v); v = NNEXT(v); }
	v = dummylist;
	while (v) { 
		if (!NANCHORNODE(v)) print_node(f,v); v = NNEXT(v); }

	v = nodelist;
	while (v) {
                c = NCONNECT(v);
                if (c) {
                        if (backward_connection1(c)) 
                                print_edge(f,CEDGE(c));
                        if (backward_connection2(c)) 
                                print_edge(f,CEDGE2(c));
                }
                li = NPRED(v);
                while (li) {
                        print_edge(f,AKANTE(li));
                        li = ANEXT(li);
                }
                v = NNEXT(v);
	}	

	v = labellist;
	while (v) {
                c = NCONNECT(v);
                if (c) {
                        if (backward_connection1(c)) 
                                print_edge(f,CEDGE(c));
                        if (backward_connection2(c)) 
                                print_edge(f,CEDGE2(c));
                }
                li = NPRED(v);
                while (li) {
                        print_edge(f,AKANTE(li));
                        li = ANEXT(li);
                }
                v = NNEXT(v);
	}	

	v = dummylist;
	while (v) {
                c = NCONNECT(v);
                if (c) {
                        if (backward_connection1(c)) 
                                print_edge(f,CEDGE(c));
                        if (backward_connection2(c)) 
                                print_edge(f,CEDGE2(c));
                }
                li = NPRED(v);
                while (li) {
                        print_edge(f,AKANTE(li));
                        li = ANEXT(li);
                }
                v = NNEXT(v);
	}	

	actindent--;
	INDPRINT(f,"}%s\n","");
	if (f) fclose(f);

	return(1);	
}



/*--------------------------------------------------------------------*/
/*   Open a graph 			         		      */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
static void open_graph(FILE *f)
#else
static void open_graph(f)
FILE *f;
#endif
{
	int k;

	INDPRINT(f,"graph: {%s\n","");
	actindent++;
	if (G_title) INDPRINT(f,"title: \"%s\"\n",G_title);
	INDPRINT(f,"color: %s\n",    color_text(G_color));
	INDPRINT(f,"width: %d\n",    G_width);
	INDPRINT(f,"height: %d\n",   G_height);
	INDPRINT(f,"xmax: %d\n",     G_xmax);
	INDPRINT(f,"ymax: %d\n",     G_ymax);
	INDPRINT(f,"xbase: %ld\n",   G_xbase);
	INDPRINT(f,"ybase: %ld\n",   G_ybase);
	INDPRINT(f,"xspace: %d\n",   G_xspace);
	INDPRINT(f,"xlspace: %d\n",  G_dspace);
	INDPRINT(f,"yspace: %d\n",   G_yspace);
	INDPRINT(f,"xraster: %d\n",  G_xraster);
	INDPRINT(f,"xlraster: %d\n", G_dxraster);
	INDPRINT(f,"yraster: %d\n",  G_yraster);
	INDPRINT(f,"x: %ld \n", G_x );
	INDPRINT(f,"y: %ld\n",  G_y);
	INDPRINT(f,"shrink:  %d\n",  G_shrink);
	INDPRINT(f,"stretch: %d\n",  G_stretch);
	INDPRINT(f,"layout_downfactor: %d\n",  layout_downfactor);
	INDPRINT(f,"layout_upfactor: %d\n",    layout_upfactor);
	INDPRINT(f,"layout_nearfactor: %d\n",  layout_nearfactor);
	INDPRINT(f,"layout_splinefactor: %d\n",G_flat_factor);
	INDPRINT(f,"spreadlevel: %d\n",spread_level);
	INDPRINT(f,"treefactor: %f\n", tree_factor);
	INDPRINT(f,"bmax: %d\n",max_edgebendings);
	INDPRINT(f,"cmin: %d\n",min_baryiterations);
	INDPRINT(f,"cmax: %d\n",max_baryiterations);
	INDPRINT(f,"pmin: %d\n",min_mediumshifts);
	INDPRINT(f,"pmax: %d\n",max_mediumshifts);
	INDPRINT(f,"rmin: %d\n",min_centershifts);
	INDPRINT(f,"rmax: %d\n",max_centershifts);
	INDPRINT(f,"smax: %d\n",max_straighttune);

	switch (G_yalign) {
	case AL_TOP:	
		INDPRINT(f,"node_alignment: top%s\n","");    break;
	case AL_BOTTOM:	
		INDPRINT(f,"node_alignment: bottom%s\n",""); break;
	case AL_CENTER:	
		INDPRINT(f,"node_alignment: center%s\n",""); break;
	}
	switch (G_orientation) {
	case TOP_TO_BOTTOM:
		INDPRINT(f,"orientation: top_to_bottom%s\n",""); break;
	case BOTTOM_TO_TOP:
		INDPRINT(f,"orientation: bottom_to_top%s\n",""); break;
	case LEFT_TO_RIGHT:
		INDPRINT(f,"orientation: left_to_right%s\n",""); break;
	case RIGHT_TO_LEFT:
		INDPRINT(f,"orientation: right_to_left%s\n",""); break;
	}
	switch (edge_label_phase) {
	case 1: INDPRINT(f,"late_edge_labels: yes%s\n",""); break;
	default:INDPRINT(f,"late_edge_labels: no%s\n",""); break;
	}
	switch (G_displayel) {
	case 1: INDPRINT(f,"display_edge_labels: yes%s\n",""); break;
	default:INDPRINT(f,"display_edge_labels: no%s\n",""); break;
	}
	switch (G_dirtyel) {
	case 1: INDPRINT(f,"dirty_edge_labels: yes%s\n",""); break;
	default:INDPRINT(f,"dirty_edge_labels: no%s\n",""); break;
	}
	switch (fine_tune_layout) {
	case 1: INDPRINT(f,"finetuning: yes%s\n",""); break;
	default:INDPRINT(f,"finetuning: no%s\n",""); break;
	}
	switch (near_edge_layout) {
	case 1: INDPRINT(f,"nearedges: yes%s\n",""); break;
	default:INDPRINT(f,"nearedges: no%s\n",""); break;
	}
	switch (G_spline) {
	case 1: INDPRINT(f,"splines: yes%s\n",""); break;
	default:INDPRINT(f,"splines: no%s\n",""); break;
	}
	switch (hide_single_nodes) {
	case 1: INDPRINT(f,"ignoresingles: yes%s\n",""); break;
	default:INDPRINT(f,"ignoresingles: no%s\n",""); break;
	}
	switch (straight_phase) {
	case 1:  INDPRINT(f,"straight_phase: yes%s\n",""); break;
	default: INDPRINT(f,"straight_phase: no%s\n",""); break;
	}
	switch (prio_phase) {
	case 1:  INDPRINT(f,"priority_phase: yes%s\n",""); break;
	default: INDPRINT(f,"priority_phase: no%s\n",""); break;
	}
	switch (manhatten_edges) {
	case 1:  INDPRINT(f,"manhatten_edges: yes%s\n",""); break;
	default: INDPRINT(f,"manhatten_edges: no%s\n",""); break;
	}
	switch (one_line_manhatten) {
	case 1:  INDPRINT(f,"smanhatten_edges: yes%s\n",""); break;
	default: INDPRINT(f,"smanhatten_edges: no%s\n",""); break;
	}
	switch (G_portsharing) {
	case 1:  INDPRINT(f,"port_sharing: yes%s\n",""); break;
	default: INDPRINT(f,"port_sharing: no%s\n",""); break;
	}
	switch (skip_baryphase2) {
	case 1:  INDPRINT(f,"crossingphase2: yes%s\n",""); break;
	default: INDPRINT(f,"crossingphase2: no%s\n",""); break;
	}
	switch (local_unwind) {
	case 1:  INDPRINT(f,"crossingoptimization: yes%s\n",""); break;
	default: INDPRINT(f,"crossingoptimization: no%s\n",""); break;
	}
	switch (crossing_heuristics) {
	case 0:  INDPRINT(f,"crossingweight: bary%s\n",""); break;
	case 1:  INDPRINT(f,"crossingweight: median%s\n",""); break;
	case 2:  INDPRINT(f,"crossingweight: barymedian%s\n",""); break;
	case 3:  INDPRINT(f,"crossingweight: medianbary%s\n",""); break;
	}
	switch (crossing_heuristics) {
	case CSCF_VIEW:  INDPRINT(f,"view: cfish%s\n","");  break;
	case PSCF_VIEW:  INDPRINT(f,"view: pfish%s\n","");  break;
	case FCSCF_VIEW: INDPRINT(f,"view: fcfish%s\n",""); break;
	case FPSCF_VIEW: INDPRINT(f,"view: fpfish%s\n",""); break;
	}
	switch (G_arrowmode) {
	case AMFIXED:  INDPRINT(f,"arrow_mode: fixed%s\n",""); break;
	case AMFREE:   INDPRINT(f,"arrow_mode: free%s\n",""); break;
	}
	switch (layout_flag) {
	case 1: INDPRINT(f,"layoutalgorithm: maxdepth%s\n","");     break;
	case 2: INDPRINT(f,"layoutalgorithm: mindepth%s\n","");     break;
	case 3: INDPRINT(f,"layoutalgorithm: minbackward%s\n","");  break;
	case 4: INDPRINT(f,"layoutalgorithm: maxdepthslow%s\n",""); break;
	case 5: INDPRINT(f,"layoutalgorithm: mindepthslow%s\n",""); break;
	case 6: INDPRINT(f,"layoutalgorithm: minindegree%s\n","");  break;
	case 7: INDPRINT(f,"layoutalgorithm: maxindegree%s\n","");  break;
	case 8: INDPRINT(f,"layoutalgorithm: minoutdegree%s\n",""); break;
	case 9: INDPRINT(f,"layoutalgorithm: maxoutdegree%s\n",""); break;
	case 10:INDPRINT(f,"layoutalgorithm: mindegree%s\n","");    break;
	case 11:INDPRINT(f,"layoutalgorithm: maxdegree%s\n","");    break;
	case 12:INDPRINT(f,"layoutalgorithm: dfs%s\n","");    	    break;
	}
	if (info_name_available) {
		for (k=0; k<3; k++) {
			if (info_names[k]) {
				INDPRINT(f,"infoname %d : ", k+1 );
				FPRINTF(f,"\"%s\"\n", info_names[k]);
			}
		}
	}
	for (k=0; k<max_nr_classes; k++) {
		if (hide_class[k]) {
			INDPRINT(f,"hidden: %d\n", k+1);
		}
	}
	for (k=0; k<cmap_size-1; k++) {
			INDPRINT(f,"colorentry %d : ", k);
			FPRINTF( f," %d %d %d\n", 
				redmap[k], greenmap[k], bluemap[k]);
	}
	if (class_name_available) {
		for (k=0; k<max_nr_classes; k++) {
			if (class_names[k]) {
				INDPRINT(f,"classname %d : ", k+1);
				FPRINTF(f,"\"%s\"\n", class_names[k]);
			}
		}
	}
}


/*--------------------------------------------------------------------*/
/*   Print a node 			         		      */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
static void print_node(FILE *f, GNODE v)
#else
static void print_node(f,v)
FILE *f;
GNODE v;
#endif
{
	INDPRINT(f,"node: {%s\n","");
	actindent++;
	if (!NTITLE(v)||!NTITLE(v)[0]) {
	               INDPRINT(f,"title: \"_internal_%ld\"\n",(long)v);
	}
	else           { INDPRINT(f,"title: \"%s\"\n",NTITLE(v)); }
	if (NLABEL(v)) INDPRINT(f,"label: \"%s\"\n",NLABEL(v));
	if (NINFO1(v)) INDPRINT(f,"info1: \"%s\"\n",NINFO1(v));
	if (NINFO2(v)) INDPRINT(f,"info2: \"%s\"\n",NINFO2(v));
	if (NINFO3(v)) INDPRINT(f,"info3: \"%s\"\n",NINFO3(v));
	INDPRINT(f,"color: %s\n",      color_text(NCOLOR(v)));
	INDPRINT(f,"textcolor: %s\n",  color_text(NTCOLOR(v)));
	INDPRINT(f,"bordercolor: %s\n",color_text(NBCOLOR(v)));
	INDPRINT(f,"width: %d\n",        NWIDTH(v));
	INDPRINT(f,"height: %d\n",       NHEIGHT(v));
	INDPRINT(f,"borderwidth: %d\n",  NBORDERW(v));
	INDPRINT(f,"loc: { x: %ld \n",    NX(v));
	INDPRINT(f,"       y: %ld }\n",   NY(v));
	INDPRINT(f,"shrink:  %d\n",  NSHRINK(v));
	INDPRINT(f,"stretch: %d\n",  NSTRETCH(v));
	INDPRINT(f,"textmode: %s\n", textmode_text(NTEXTMODE(v)));
	INDPRINT(f,"shape: %s\n",    shape_text(NSHAPE(v)));
	INDPRINT(f,"level: %d\n",            NTIEFE(v));
	INDPRINT(f,"horizontal_order: %d\n", NPOS(v));
	actindent--;
	INDPRINT(f,"}%s\n","");
}


#ifdef ANSI_C
static void tbend_node(FILE *f, GEDGE e, int k)
#else
static void tbend_node(f,e,k)
FILE *f;
GEDGE e;
int k;
#endif
{
	INDPRINT(f,"node: {%s\n","");
	actindent++;
        INDPRINT(f,"title: \"_inttbend%d",k);
        FPRINTF(f,"_%ld\"\n",(long)e);
        INDPRINT(f,"label: \"%s\"\n","");
	INDPRINT(f,"color: %s\n",      color_text(ECOLOR(e)));
	INDPRINT(f,"width: %d\n", 0);
	INDPRINT(f,"height:%d\n", 0);
	INDPRINT(f,"borderwidth: %d\n", 0);
	INDPRINT(f,"loc: { x: %ld \n",    ETBENDX(e)+(k-1)*5);
	INDPRINT(f,"       y: %ld }\n",   ETBENDY(e) );
	actindent--;
	INDPRINT(f,"}%s\n","");
}


#ifdef ANSI_C
static void bbend_node(FILE *f, GEDGE e, int k)
#else
static void bbend_node(f,e,k)
FILE *f;
GEDGE e;
int k;
#endif
{
	INDPRINT(f,"node: {%s\n","");
	actindent++;
        INDPRINT(f,"title: \"_intbbend%d",k);
        FPRINTF(f,"_%ld\"\n",(long)e);
        INDPRINT(f,"label: \"%s\"\n","");
	INDPRINT(f,"color: %s\n",      color_text(ECOLOR(e)));
	INDPRINT(f,"width: %d\n", 0);
	INDPRINT(f,"height:%d\n", 0);
	INDPRINT(f,"borderwidth: %d\n", 0);
	INDPRINT(f,"loc: { x: %ld \n",    EBBENDX(e)+(k-1)*5);
	INDPRINT(f,"       y: %ld }\n",   EBBENDY(e) );
	actindent--;
	INDPRINT(f,"}%s\n","");
}

/*--------------------------------------------------------------------*/
/*   Print an edge			         		      */
/*--------------------------------------------------------------------*/

static char lastnode[128];
static char nextnode[128];

#ifdef ANSI_C
static void print_edge(FILE *f, GEDGE e)
#else
static void print_edge(f,e)
FILE *f;
GEDGE e;
#endif
{
	GNODE vs,ve;
	char  topbend;
	char  botbend;
	int   x1,x2,x3,x4,y1,y2,y3,y4,s;
	char *lasttitle;
	char *nexttitle;
	int  anchored;

	if (EANCHOR(e)==66) return;

	vs = ESTART(e);
	if (NANCHORNODE(vs)) {
		vs = ESTART(CEDGE(NCONNECT(vs)));
	}
	ve = EEND(e);

	x1 = ESTARTX(e);
	y1 = ESTARTY(e);
	x2 = EENDX(e);
	y2 = EENDY(e);
	x3 = ETBENDX(e);
	y3 = ETBENDY(e);
	x4 = EBBENDX(e);
	y4 = EBBENDY(e);
	s  = EARROWSIZE(e);
	
	topbend = 0;
	if ((y3!=y1)||(x3!=x1)) topbend = 1; 
	if ((x1<x3) && (x1+s*8/10>x3)) topbend = 0;
	if ((x1>x3) && (x1-s*8/10<x3)) topbend = 0;
	if ((y1<y3) && (y1+s*8/10>y3)) topbend = 0;
	if ((y1>y3) && (y1-s*8/10<y3)) topbend = 0;
	botbend = 0;
	if ((y4!=y2)||(x4!=x2)) botbend = 1; 
	if ((x2<x4) && (x2+s*8/10>x4)) botbend = 0;
	if ((x2>x4) && (x2-s*8/10<x4)) botbend = 0;
	if ((y2<y4) && (y2+s*8/10>y4)) botbend = 0;
	if ((y2>y4) && (y2-s*8/10<y4)) botbend = 0;

	if (topbend) tbend_node(f,e,1);
	if (botbend) bbend_node(f,e,1);

	anchored = 0;
	if (!NTITLE(vs)||!NTITLE(vs)[0]) {
		SPRINTF(lastnode,"_internal_%ld",(long)vs);
		lasttitle = lastnode;
	}
	else 	lasttitle = NTITLE(vs);

	if (topbend) {
		SPRINTF(nextnode,"_inttbend1_%ld",(long)e);
		nexttitle = nextnode;
		INDPRINT(f,"edge: {%s\n","");
		actindent++;
	        INDPRINT(f,"sourcename: \"%s\"\n",lasttitle);
		INDPRINT(f,"targetname: \"%s\"\n",nexttitle);
		if ((!anchored) && (EANCHOR(e)<0))
			{ INDPRINT(f,"anchor: %d\n",    -EANCHOR(e)); }
		anchored = 1;
		INDPRINT(f,"color: %s\n",     color_text(ECOLOR(e)));
		INDPRINT(f,"textcolor: %s\n", color_text(ELABELCOL(e)));
		INDPRINT(f,"arrowcolor: %s\n", color_text(EARROWCOL(e)));
		INDPRINT(f,"backarrowcolor: %s\n", color_text(EARROWBCOL(e)));
		INDPRINT(f,"linestyle: %s\n", linestyle_text(ELSTYLE(e)));
		INDPRINT(f,"thickness: %d\n",     ETHICKNESS(e));
		INDPRINT(f,"class: %d\n",         ECLASS(e));
		INDPRINT(f,"horizontal_order: %d\n",EHORDER(e));
		INDPRINT(f,"arrowsize: %d\n",     0);
		INDPRINT(f,"backarrowsize: %d\n", EARROWBSIZE(e));
		INDPRINT(f,"arrowstyle: none%s\n", "");
		switch (EARROWSIZE(e)) {
		case ASNONESPEC: 
		case ASNONE: INDPRINT(f,"backarrowstyle:none%s\n", ""); break;
		case ASSOLID:INDPRINT(f,"backarrowstyle:solid%s\n",""); break;
		case ASLINE: INDPRINT(f,"backarrowstyle:line%s\n", ""); break;
		}
		actindent--;
		INDPRINT(f,"}%s\n","");
		strcpy(lastnode,nextnode);
		lasttitle = lastnode;
	}
	if (botbend) {
		SPRINTF(nextnode,"_intbbend1_%ld",(long)e);
		nexttitle = nextnode;
		INDPRINT(f,"edge: {%s\n","");
		actindent++;
	        INDPRINT(f,"sourcename: \"%s\"\n",lasttitle);
		INDPRINT(f,"targetname: \"%s\"\n",nexttitle);
		if ((!anchored) && (EANCHOR(e)<0))
			{ INDPRINT(f,"anchor: %d\n",    -EANCHOR(e)); }
		anchored = 1;
		INDPRINT(f,"color: %s\n",     color_text(ECOLOR(e)));
		INDPRINT(f,"textcolor: %s\n", color_text(ELABELCOL(e)));
		INDPRINT(f,"arrowcolor: %s\n", color_text(EARROWCOL(e)));
		INDPRINT(f,"backarrowcolor: %s\n", color_text(EARROWBCOL(e)));
		INDPRINT(f,"linestyle: %s\n", linestyle_text(ELSTYLE(e)));
		INDPRINT(f,"thickness: %d\n",     ETHICKNESS(e));
		INDPRINT(f,"class: %d\n",         ECLASS(e));
		INDPRINT(f,"horizontal_order: %d\n",EHORDER(e));
		INDPRINT(f,"arrowsize: %d\n",     0);
		if (!topbend) {
			INDPRINT(f,"backarrowsize: %d\n", EARROWBSIZE(e));
		}
		else	INDPRINT(f,"backarrowsize: %d\n", 0);
		INDPRINT(f,"arrowstyle: none%s\n", "");
		if (!topbend) {
			switch (EARROWSIZE(e)) {
			case ASNONESPEC: 
			case ASNONE: INDPRINT(f,"backarrowstyle:none%s\n", "");
				     break;
			case ASSOLID:INDPRINT(f,"backarrowstyle:solid%s\n","");
				     break;
			case ASLINE: INDPRINT(f,"backarrowstyle:line%s\n", "");
				     break;
			}
		}
		else INDPRINT(f,"backarrowstyle: none%s\n", "");
		actindent--;
		INDPRINT(f,"}%s\n","");
		strcpy(lastnode,nextnode);
		lasttitle = lastnode;
	}
	if (!NTITLE(ve)||!NTITLE(ve)[0]) {
		SPRINTF(nextnode,"_internal_%ld",(long)ve);
		nexttitle = nextnode;
	}
	else 	nexttitle = NTITLE(ve);
	INDPRINT(f,"edge: {%s\n","");
	actindent++;
	INDPRINT(f,"sourcename: \"%s\"\n",lasttitle);
	INDPRINT(f,"targetname: \"%s\"\n",nexttitle);
	if ((!anchored) && (EANCHOR(e)<0))
		{ INDPRINT(f,"anchor: %d\n",    -EANCHOR(e)); }
	INDPRINT(f,"color: %s\n",     color_text(ECOLOR(e)));
	INDPRINT(f,"textcolor: %s\n", color_text(ELABELCOL(e)));
	INDPRINT(f,"arrowcolor: %s\n", color_text(EARROWCOL(e)));
	INDPRINT(f,"backarrowcolor: %s\n", color_text(EARROWBCOL(e)));
	INDPRINT(f,"label: \"%s\"\n", ELABEL(e));
	INDPRINT(f,"linestyle: %s\n", linestyle_text(ELSTYLE(e)));
	INDPRINT(f,"thickness: %d\n",     ETHICKNESS(e));
	INDPRINT(f,"class: %d\n",         ECLASS(e));
	INDPRINT(f,"horizontal_order: %d\n",EHORDER(e));
	INDPRINT(f,"arrowsize: %d\n",     EARROWSIZE(e));
	if (!topbend && !botbend) {
		INDPRINT(f,"backarrowsize: %d\n", EARROWBSIZE(e));
	}
	else	INDPRINT(f,"backarrowsize: %d\n", 0);
	switch (EARROWSIZE(e)) {
	case ASNONESPEC: 
	case ASNONE:  INDPRINT(f,"arrowstyle: none%s\n", ""); break;
	case ASSOLID: INDPRINT(f,"arrowstyle: solid%s\n",""); break;
	case ASLINE:  INDPRINT(f,"arrowstyle: line%s\n", ""); break;
	}
	if (!topbend && !botbend) {
		switch (EARROWSIZE(e)) {
		case ASNONESPEC: 
		case ASNONE:  INDPRINT(f,"backarrowstyle: none%s\n", ""); break;
		case ASSOLID: INDPRINT(f,"backarrowstyle: solid%s\n",""); break;
		case ASLINE:  INDPRINT(f,"backarrowstyle: line%s\n", ""); break;
		}
	}
	else INDPRINT(f,"backarrowstyle: none%s\n", "");
	actindent--;
	INDPRINT(f,"}%s\n","");
}

/*--------------------------------------------------------------------*/
/*   Convert a color into its name				      */
/*--------------------------------------------------------------------*/

static char mycolbuf[10];

#ifdef ANSI_C
char *color_text(int c)
#else
char *color_text(c)
int c;
#endif
{
	switch (c) {
	case BLACK       : return("black");
	case BLUE        : return("blue");
	case RED         : return("red");
	case GREEN       : return("green");
	case YELLOW      : return("yellow");
	case MAGENTA     : return("magenta");
	case CYAN        : return("cyan");
	case WHITE       : return("white");
	case DARKGREY    : return("darkgrey");
	case DARKBLUE    : return("darkblue");
	case DARKRED     : return("darkred");
	case DARKGREEN   : return("darkgreen");
	case DARKYELLOW  : return("darkyellow");
	case DARKMAGENTA : return("darkmagenta");
	case DARKCYAN    : return("darkcyan");
	case GOLD        : return("gold");
	case LIGHTGREY   : return("lightgrey");
	case LIGHTBLUE   : return("lightblue");
	case LIGHTRED    : return("lightred");
	case LIGHTGREEN  : return("lightgreen");
	case LIGHTYELLOW : return("lightyellow");
	case LIGHTMAGENTA: return("lightmagenta");
	case LIGHTCYAN   : return("lightcyan");
	case LILAC       : return("lilac");
	case TURQUOISE   : return("turquoise");
	case AQUAMARINE  : return("aquamarine");
	case KHAKI       : return("khaki");
	case PURPLE      : return("purple");
	case YELLOWGREEN : return("yellowgreen");
	case PINK        : return("pink");
	case ORANGE      : return("orange");
	case ORCHID      : return("orchid");
	}

	SPRINTF(mycolbuf,"%d",c);
	return(mycolbuf);
}



/*--------------------------------------------------------------------*/
/*   Convert a textmode into its name				      */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
char *textmode_text(int t)
#else
char *textmode_text(t)
int t;
#endif
{
	switch (t) {
	case CENTER: return("center");
	case LEFT:   return("left_justify");
	case RIGHT:  return("right_justify");
	}
	return("none");
}

/*--------------------------------------------------------------------*/
/*   Convert a shape into its name				      */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
char *shape_text(int t)
#else
char *shape_text(t)
int t;
#endif
{
	switch (t) {
	case BOX:      return("box");
	case RHOMB:    return("rhomb");
	case ELLIPSE:  return("ellipse");
	case TRIANGLE: return("triangle");
	}
	return("none");
}



/*--------------------------------------------------------------------*/
/*   Convert a linestyle into its name				      */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
char *linestyle_text(int t)
#else
char *linestyle_text(t)
int t;
#endif
{
	switch (t) {
	case SOLID:     return("continuous");
	case DOTTED:    return("dotted");
	case DASHED:    return("dashed");
	case UNVISIBLE: return("invisible");
	}
	return("none");
}


