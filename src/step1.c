/* SCCS-info %W% %E% */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*              VCG : Visualization of Compiler Graphs                */
/*              --------------------------------------                */
/*                                                                    */
/*   file:         This file is uglified by UGLIFIER V 1.0            */
/*   version:      1.00.00                                            */
/*   author:       I. Lemke  (...-Version 0.99.99)                    */
/*                 G. Sander (Version 1.00.00-...)                    */
/*                 Universitaet des Saarlandes, 66041 Saarbruecken    */
/*                 ESPRIT Project #5399 Compare                       */
/*--------------------------------------------------------------------*/


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


/*--------------------------------------------------------------------*/


#ifndef lint
static char *gs_ide26 ="$Id: step1.c,v 3.11 1995/02/08 11:11:14 sander Exp $"; /*;*a*b
*a*b;*/ 
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "alloc.h"
#include "main.h"
#include "options.h"
#include "timelim.h"
#include "folding.h"
#include "steps.h"
#include "timing.h"
#ifdef DEBUG
static void gs_ide18 _PP((GNODE node)); static void gs_ide16 _PP((GEDGE edge)); /*;*a*b
*a*b;*/ static void gs_ide17 _PP((void)); static void gs_ide19 _PP((char *fn)); /*;*a*b
*a*b;*/ 
#endif
static void gs_ide30 _PP((GNODE node)); static void gs_ide28 _PP((GNODE node)); /*;*gs_ide26 = $Id: step1.c,v 3.11 1995*02
8 _PP((/N;D+ node));;*/ static void gs_ide35 _PP((void)); static void gs_ide34 _PP((GEDGE edge)); /*;/+D/+ edge));
;*/ static void gs_ide29 _PP((void)); static void gs_ide27 _PP((void)); static int gs_ide8 _PP((GNODE v,GNODE w,GNODE z)); /*;void gs_ide30 _PP((/N;D+ node));
_ide28 _PP((/N;D+ node));;*/ static void gs_ide33 _PP((void)); static void gs_ide20 _PP((GNODE node)); /*;_PP((void));
D/+ edge));;*/ static void gs_ide5 _PP((GNODE node)); static void gs_ide43 _PP((ADJEDGE edge,GNODE node,int prio)); /*;static void gs_ide29 _PP((void));
void gs_ide27 _PP((void));;*/ static void gs_ide46 _PP((void)); static void gs_ide4 _PP((GNODE v)); /*;_PP((void));
;D+ node));;*/  static GNODE gs_ide24 _PP((void)); static int gs_ide49 _PP((GNODE node1,GNODE node2)); /*;;D+ node));
));;*/ static void gs_ide50 _PP((GNODE node1,GNODE node2,int l)); static void gs_ide47 _PP((GNODE node1,GNODE node2)); /*;atic void gs_ide43 _PP((ADJ+D/+ edge,/N
id gs_ide46 _PP((void));;*/ static int gs_ide48 _PP((GNODE node1,GNODE node2)); static void gs_ide3 _PP((GNODE v, GNLIST *l)); /*;de4 _PP((/N;D+ v));
PP((void));;*/ static GNODE gs_ide23 _PP((GNLIST *l)); static void gs_ide37 _PP((void)); /*; node1,/N;D+ node2));
,/N;D+ node2,int l));;*/ static void gs_ide7 _PP((GNLIST *nlist)); static int gs_ide12 _PP((GNLIST nlist)); /*;ic void gs_ide47 _PP((/N;D+ node1,/N;D+
gs_ide48 _PP((/N;D+ node1,/N;D+ node2));*/ static int gs_ide39 _PP((GNODE v, GNODE w, int prio)); static int gs_ide40 _PP((GNODE v, GNODE w)); /*;3 _PP((/N;D+ v, /NLIST *l));
((/NLIST *l));;*/ static int gs_ide38 _PP((GNODE v, GNODE w)); static void gs_ide36 _PP((GNODE v, GNODE w)); /*;;
);;*/ static void gs_ide41 _PP((GNODE n, long *d, GNLIST *p)); static void gs_ide2 _PP((void)); /*; int gs_ide12 _PP((/NLIST nlist));
_ide39 _PP((/N;D+ v, /N;D+ w, int prio);*/ static void gs_ide52 _PP((void)); static int gs_ide51 _PP((GNODE v,int lab)); /*;_PP((/N;D+ v, /N;D+ w));
;D+ v, /N;D+ w));;*/ static void gs_ide13 _PP((void)); static void gs_ide11 _PP((void)); static void gs_ide6 _PP((GNODE v, GNODE w, GNODE predw)); /*;tatic void gs_ide41 _PP((/N;D+ n, long 
oid gs_ide2 _PP((void));;*/ static void gs_ide32 _PP((void)); static void gs_ide10 _PP((GNODE n, ADJEDGE e, int l)); /*;ide52 _PP((void));
P((/N;D+ v,int lab));;*/ static void gs_ide31 _PP((void)); static void gs_ide9 _PP((ADJEDGE e)); /*;d));
static void gs_ide11 _PP((void));;*/ static GNODE gs_ide14 _PP((int t)); static ADJEDGE gs_ide15 _PP((GNODE x, GNODE y,GEDGE e,int t)); /*;void gs_ide6 _PP((/N;D+ v, /N;D+ w, /N;
_ide32 _PP((void));;*/ int maxindeg;  int maxoutdeg;  DEPTH *layer = NULL;  int maxdepth = 0; /*;);
atic /N;D+ gs_ide14 _PP((int t));;*/   static int gs_ide42 = 0; 
#define forward_connection1(c)  (((( c )->edge)  )&& ((( (( c )->edge)   )->end)  ==(( c )->target)  ))
#define forward_connection2(c)  (((( c )->edge2)  )&&((( (( c )->edge2)   )->end)  ==(( c )->target2)  ))
#define backward_connection1(c) (((( c )->edge)  )&& ((( (( c )->edge)   )->end)  !=(( c )->target)  ))
#define backward_connection2(c) (((( c )->edge2)  )&&((( (( c )->edge2)   )->end)  !=(( c )->target2)  ))
#ifdef ANSI_C
void step1_main(void)
#else
void step1_main()
#endif
{ int i; start_time(); ; assert((dummylist==NULL)); prepare_back_edges(); /*;void step1_main()
{;*/ gs_ide35 (); insert_anchor_edges(); gs_ide29 (); gs_ide27 (); if (layout_flag==3) gs_ide46 (); /*;(dummylist==NULL));
dges();;*/ else if (layout_flag==0) gs_ide37 (); else gs_ide33 (); if (edge_label_phase == 1) gs_ide2 (); /*;anchor_edges();
gs_ide29 ();;*/ if (fine_tune_layout==1) gs_ide52 (); if (maxdepth+2 > gs_ide42 ) { if (layer) free(layer); /*;g==3) gs_ide46 ();
=0) gs_ide37 ();;*/ layer = (DEPTH *)malloc((maxdepth+2)*sizeof(struct depth_entry)); if (!layer) Fatal_error("memory exhausted",""); /*;else gs_ide33 ();
e_label_phase == 1) gs_ide2 ();;*/ gs_ide42 = maxdepth+2;
#ifdef DEBUG
PRINTF("Maxdepth of this layout: %d \n",maxdepth); PRINTF("Sizeof table `layer': %ld Bytes\n", /*;de42 ) {
if (layer) free(layer);;*/ (maxdepth+2)*sizeof(struct depth_entry));
#endif
} for (i=0; i<maxdepth+2; i++) { (( layer[i] ).anz) /*;;;*/ = 0; (( layer[i] ).predlist) /*;
out: %d zn ,maxdepth);;*/ = NULL; (( layer[i] ).succlist) /*;yteszn ,;
*/ = NULL; (( layer[i] ).resort_necessary) /*;axdepth+2)*sizeof(struct depth_entry));
;*/ = 1; } gs_ide13 (); gs_ide32 (); gs_ide31 (); if (layout_flag == TREE_LAYOUT) { /*;/SC;yy+NT = NULL;
R/SC;yy+NT = 1;;*/ stop_time("step1_main"); layout_flag = tree_main(); if (layout_flag != TREE_LAYOUT) { /*;3 ();
gs_ide32 ();;*/   FPRINTF(stderr,"\nThis is not a downward tree. "); FPRINTF(stderr,"Continuing with normal layout\n"); /*;1 ();
g == TR++_LAY;UT) {;*/ } } calc_number_reversions(); if (layout_flag != TREE_LAYOUT) { gs_ide11 (); /*;, znThis is not a downward tree.  );
nuing with normal layoutzn );;*/ stop_time("step1_main"); } } static GNODE gs_ide44 ; static GNODE gs_ide45 ; /*;g != TR++_LAY;UT) {
gs_ide11 ();;*/ 
#ifdef ANSI_C
static void gs_ide30 (GNODE node)
#else
static void gs_ide30 (node) GNODE node;
#endif
{ GNODE h,*hp; assert((node)); ; if ((( node )->next) /*;static void gs_ide30 (node);
*/ ) (( (( node )->next) /*;static void gs_ide30 (node);*/ )->before) /*;
static void gs_ide30 (node);*/ = (( node )->before) /*;static void gs_ide30 (node);
*/ ; else nodelistend = (( node )->before) /*;ode;;*/ ; if ((( node )->before) /*;
{;*/ ) (( (( node )->before) /*;{;*/ )->next) /*;{;*/ = (( node )->next) /*;
{;*/ ; else nodelist = (( node )->next) /*;,*hp;;*/ ; h = gs_ide44 ; /*;;
node )->next) /+;R/SC;yy+NT ) (( (( nod;*/  hp = &gs_ide44 ; while (h) { if ((( h )->refnum) /*;nd = (( node )->before) /+;
R/SC;yy+NT ;;*/ >=(( node )->refnum) /*;nd = (( node )->before) /+;R/SC;
yy+NT ;;*/ ) break; hp = &((( h )->next) /*;) /+;R/SC;yy+NT ) (( (( node )->before);
*/ ); h = (( h )->next) /*;ext) /+;R/SC;yy+NT ;;*/ ; } *hp = node; if (h) (( node )->before) /*;
while (h) {;*/ = (( h )->before) /*;while (h) {;*/ ; else (( node )->before) /*;
h )->refnum) /+;R/SC;yy+NT >=(( node )-;*/ = gs_ide45 ;  (( node )->next) /*;
>next) /+;R/SC;yy+NT );;*/ = h; if (h) (( h )->before) /*;R/SC;yy+NT ;
;*/ = node; else gs_ide45 = node; } static GNODE gs_ide21 ; static GNODE gs_ide22 ; /*;e) /+;R/SC;yy+NT = gs_ide45 ; 
NT = h;;*/ 
#ifdef ANSI_C
static void gs_ide28 (GNODE node)
#else
static void gs_ide28 (node) GNODE node;
#endif
{ GNODE h,*hp; assert((node)); ; if ((( node )->next) /*;static void gs_ide28 (node);
*/ ) (( (( node )->next) /*;static void gs_ide28 (node);*/ )->before) /*;
static void gs_ide28 (node);*/ = (( node )->before) /*;static void gs_ide28 (node);
*/ ; else nodelistend = (( node )->before) /*;ode;;*/ ; if ((( node )->before) /*;
{;*/ ) (( (( node )->before) /*;{;*/ )->next) /*;{;*/ = (( node )->next) /*;
{;*/ ; else nodelist = (( node )->next) /*;,*hp;;*/ ; h = gs_ide21 ; /*;;
node )->next) /+;R/SC;yy+NT ) (( (( nod;*/  hp = &gs_ide21 ; while (h) { if ((( h )->refnum) /*;nd = (( node )->before) /+;
R/SC;yy+NT ;;*/ >=(( node )->refnum) /*;nd = (( node )->before) /+;R/SC;
yy+NT ;;*/ ) break; hp = &((( h )->next) /*;) /+;R/SC;yy+NT ) (( (( node )->before);
*/ ); h = (( h )->next) /*;ext) /+;R/SC;yy+NT ;;*/ ; } *hp = node; if (h) (( node )->before) /*;
while (h) {;*/ = (( h )->before) /*;while (h) {;*/ ; else (( node )->before) /*;
h )->refnum) /+;R/SC;yy+NT >=(( node )-;*/ = gs_ide22 ;  (( node )->next) /*;
>next) /+;R/SC;yy+NT );;*/ = h; if (h) (( h )->before) /*;R/SC;yy+NT ;
;*/ = node; else gs_ide22 = node; }
#ifdef ANSI_C
static void gs_ide35 (void)
#else
static void gs_ide35 ()
#endif
{ GNODE node,nxt_node; ; gs_ide44 = NULL; gs_ide45 = NULL; gs_ide21 = NULL; /*;_ide35 ()
{;*/ gs_ide22 = NULL; node = nodelist; while (node) { nxt_node = (( node )->next) /*;
4 = NULL;;*/ ; if (!(( node )->pred) /*;L;;*/ ) gs_ide30 (node); else if (!(( node )->succ) /*;
gs_ide21 = NULL;;*/ ) gs_ide28 (node); node = nxt_node; } if (gs_ide44 ) { /*;while (node) {
e = (( node )->next) /+;R/SC;yy+NT ;;*/ if (nodelist) (( nodelist )->before) /*;e = (( node )->next) /+;R/SC;
yy+NT ;;*/ = gs_ide45 ; (( gs_ide45 )->next) /*;->pred) /+;R/SC;yy+NT ) gs_ide30 (node);
*/ = nodelist; nodelist = gs_ide44 ; if (!nodelistend) nodelistend = gs_ide45 ; /*;node = nxt_node;
};*/ } if (gs_ide21 ) { if (nodelistend) (( nodelistend )->next) /*;(( nodelist )->before) /+;
R/SC;yy+NT = ;*/ = gs_ide21 ; (( gs_ide21 )->before) /*;/+;R/SC;yy+NT = nodelist;
;*/ = nodelistend; nodelistend = gs_ide22 ; if (!nodelist) nodelist = gs_ide21 ; /*;delistend) nodelistend = gs_ide45 ;
};*/ } } 
#ifdef ANSI_C
void insert_anchor_edges(void)
#else
void insert_anchor_edges()
#endif
{ GEDGE edge; ; assert((dummylist==NULL)); edge = edgelist; while (edge) { /*;chor_edges()
{;*/ if ( ((( edge )->anchor) /*;{;*/ <=64) && ((( edge )->anchor) /*;{;*/ >0) /*;{
dge;;*/ &&(!(( edge )->invisible) /*;dge;;*/ ))  gs_ide34 (edge); edge = (( edge )->next) /*;
(dummylist==NULL));;*/ ; } edge = tmpedgelist; while (edge) { if ( ((( edge )->anchor) /*;
>invisible) /+;R/SC;yy+NT )) ;*/ <=64) && ((( edge )->anchor) /*;>invisible) /+;
R/SC;yy+NT )) ;*/ >0) &&(!(( edge )->invisible) /*;gs_ide34 (edge);;
*/ ))  gs_ide34 (edge); edge = (( edge )->internal_next) /*;};*/ ; } }
#ifdef ANSI_C
static void gs_ide34 (GEDGE edge)
#else
static void gs_ide34 (edge) GEDGE edge;
#endif
{ GEDGE h; GNODE v; CONNECT c1,c2; ; if ((G_orientation==1 /*;/+D/+ edge;
;*/ )||(G_orientation==2 /*;/+D/+ edge;;*/ )) { G_orientation= 0 /*;
{;*/ ; if (!silent) {  FPRINTF(stderr,"Orientation ignored, because"); /*; c1,c2;
;;*/  FPRINTF(stderr," edge attribute `anchor' used !\n"); } } c1 = (( (( edge )->start) /*;
0 /+;R/SC;yy+NT ;;*/ )->connection) /*; 0 /+;R/SC;yy+NT ;;*/ ; if (!c1) { /*;if (!silent) { 
(stderr, ;rientation ignored, because );*/   v = gs_ide14 (-1); (( v )->invisible) /*;,  edge attribute `anchor' used !zn );
;*/ = 0; (( v )->level) /*;};*/ = (( (( edge )->start) /*;};*/ )->level) /*;
};*/ ; (( v )->nhorder) /*;};*/ = (( (( edge )->start) /*;};*/ )->nhorder) /*;
};*/ ; (( v )->anchordummy) /*; (( edge )->start) /+;R/SC;yy+NT )->con;
*/ = 1; h = tmpedgealloc( (( edge )->linestyle) /*;ide14 (-1);;*/ ,  (( edge )->thickness) /*;
ble) /+;R/SC;yy+NT = 0;;*/ ,  (( edge )->eclass) /*;C;yy+NT = (( (( edge )->start) /+;
R/SC;;*/ , 200, (( edge )->color) /*;= 1;;*/ ,  (( edge )->labelcolor) /*;
= tmpedgealloc(;*/ ,  0, (( edge )->arrowsize2) /*;ness) /+;R/SC;yy+NT , ;
*/ ,  0 /*;/SC;yy+NT ,;*/ ,  (( edge )->arrowstyle2) /*;200,;*/ ,  (( edge )->arrowcolor1) /*;
)->color) /+;R/SC;yy+NT , ;*/ ,  (( edge )->arrowcolor2) /*;elcolor) /+;
R/SC;yy+NT , ;*/ ,  (( edge )->horder) /*;0,;*/ ); (( h )->anchor) /*;
)->arrowsize2) /+;R/SC;yy+NT , ;*/ = 66; (( h )->start) /*;T , ;*/ = (( edge )->start) /*;
T , ;*/ ; (( h )->end) /*;2) /+;R/SC;yy+NT , ;*/ = v; (( h )->label) /*;
/SC;yy+NT , ;*/ = NULL; c1 = connectalloc((( h )->start) /*;NT , ;*/ ); /*;NT , 
edge )->horder) /+;R/SC;yy+NT );;*/ (( c1 )->target) /*; edge )->horder) /+;R/SC;yy+NT );;*/ = v; (( c1 )->edge) /*;
nchor) /+;R/SC;yy+NT = 66;;*/ = h; c2 = connectalloc(v); (( c2 )->target) /*;
+NT = v;;*/ = (( h )->start) /*;+NT = v;;*/ ; (( c2 )->edge) /*; NULL;
;*/ = h; } v = (( c1 )->target) /*;1 )->target) /+;R/SC;yy+NT = v;;*/ ; /*;1 )->target) /+;R/SC;yy+NT = v;
ge) /+;R/SC;yy+NT = h;;*/   assert((v)); assert(((( v )->anchordummy) /*;v);;*/ )); h = tmpedgealloc( /*;yy+NT = (( h )->start) /+;R/SC;yy+NT ;
;;*/ (( edge )->linestyle) /*;;;*/ , (( edge )->thickness) /*;};*/ , (( edge )->eclass) /*;
c1 )->target) /+;R/SC;yy+NT ; ;*/ , (( edge )->priority) /*;assert((v));
;*/ , (( edge )->color) /*;((( v )->anchordummy) /+;R/SC;yy+NT ));;*/ , /*;((( v )->anchordummy) /+;R/SC;yy+NT ));
oc(;*/ (( edge )->labelcolor) /*;oc(;*/ , (( edge )->arrowsize1) /*; /+;R/SC;
yy+NT ,;*/ , (( edge )->arrowsize2) /*;C;yy+NT ,;*/ , (( edge )->arrowstyle1) /*;
(( edge )->eclass) /+;R/SC;yy+NT ,;*/ , (( edge )->arrowstyle2) /*; )->priority) /+;
R/SC;yy+NT ,;*/ , (( edge )->arrowcolor1) /*;or) /+;R/SC;yy+NT ,;*/ , (( edge )->arrowcolor2) /*;
) /+;R/SC;yy+NT ,;*/ , (( edge )->horder) /*;SC;yy+NT ,;*/ ); (( h )->anchor) /*;
T ,;*/ = - (( edge )->anchor) /*;T ,;*/ ; (( h )->start) /*; edge )->arrowstyle1) /+;
R/SC;yy+NT ,;*/ = v; (( h )->end) /*;->arrowstyle2) /+;R/SC;yy+NT ,;
*/ = (( edge )->end) /*;->arrowstyle2) /+;R/SC;yy+NT ,;*/ ; (( h )->label) /*;
color1) /+;R/SC;yy+NT ,;*/ = (( edge )->label) /*;color1) /+;R/SC;yy+NT ,;
*/ ; delete_adjedge(edge); (( edge )->invisible) /*;NT );;*/ = 0; create_adjedge(h); /*;edge )->anchor) /+;R/SC;yy+NT ;
)->start) /+;R/SC;yy+NT = v;;*/ }
#ifdef ANSI_C
void prepare_back_edges(void)
#else
void prepare_back_edges()
#endif
{ ADJEDGE e; ADJEDGE a1, a2; ; e = back_edge_list; while (e) { if (!(( (( e )->kante) /*;
{;*/ )->invisible) /*;{;*/ ) revert_edge((( e )->kante) /*;{;*/ ); else if ((( (( e )->kante) /*;
e;;*/ )->labelnode) /*; e;;*/ ) { a1 = (( (( (( e )->kante) /*;;;*/ )->labelnode) /*;
;;*/ )->succ) /*;;;*/ ; a2 = (( (( (( e )->kante) /*;;;*/ )->labelnode) /*;
;;*/ )->pred) /*;;;*/ ; if (a1)  if (!(( (( a1 )->kante) /*;while (e) {
;*/ )->invisible) /*;while (e) {;*/ )  revert_edge((( a1 )->kante) /*;
(( e )->kante) /+;R/SC;yy+NT )->invisi;*/ ); if (a2)  if (!(( (( a2 )->kante) /*;
nte) /+;R/SC;yy+NT )->labelnode) /+;R/S;*/ )->invisible) /*;nte) /+;
R/SC;yy+NT )->labelnode) /+;R/S;*/ )  revert_edge((( a2 )->kante) /*;
;R/SC;yy+NT )->labelnode) /+;R/SC;yy+NT;*/ ); } e = (( e )->next) /*;
(( a1 )->kante) /+;R/SC;yy+NT )->invis;*/ ; } }
#ifdef ANSI_C
static void gs_ide27 (void)
#else
static void gs_ide27 ()
#endif
{ GNODE v; ADJEDGE edge1; ADJEDGE edge; CONNECT c1,c2; int connection_possible, invisible; /*;_ide27 ()
{;*/ ; edge1 = bent_near_edge_list; while (edge1) { invisible = (( (( edge1 )->kante) /*;
ADJ+D/+ edge;;*/ )->invisible) /*;ADJ+D/+ edge;;*/ ; v = (( (( edge1 )->kante) /*;
c1,c2;;*/ )->labelnode) /*; c1,c2;;*/ ; if (v) { edge = (( v )->succ) /*;
;;*/ ; if (!edge) invisible = 1; else invisible = (( (( edge )->kante) /*;
{;*/ )->invisible) /*;{;*/ ; edge = (( v )->pred) /*;e1 )->kante) /+;
R/SC;yy+NT )->invisible;*/ ; if (!edge) invisible |= 1; else invisible |= (( (( edge )->kante) /*;
if (v) {;*/ )->invisible) /*;if (v) {;*/ ; }  else if (!invisible) { /*;( edge )->kante) /+;R/SC;yy+NT )->invis
;yy+NT ;;*/  if (G_displayel==1 /*;( edge )->kante) /+;R/SC;yy+NT )->invis;*/ )  v = create_labelnode((( edge1 )->kante) /*;
;yy+NT ;;*/ ); else { v = gs_ide14 (-1); (( v )->invisible) /*;visible |= (( (( edge )->kante) /+;
R/SC;*/ = 0; } (( v )->level) /*; (!invisible) {;*/ = (( ((( (( edge1 )->kante) /*;
(!invisible) {;*/ )->start) /*; (!invisible) {;*/ ) /*; (!invisible) {
;*/ )->level) /*; (!invisible) {;*/ ; (( v )->nhorder) /*;l==1 /+;R/SC;
yy+NT ) ;*/ = (( ((( (( edge1 )->kante) /*;l==1 /+;R/SC;yy+NT ) ;*/ )->start) /*;
l==1 /+;R/SC;yy+NT ) ;*/ ) /*;l==1 /+;R/SC;yy+NT ) ;*/ )->nhorder) /*;
l==1 /+;R/SC;yy+NT ) ;*/ ; edge = gs_ide15 (v,((( (( edge1 )->kante) /*;
(( edge1 )->kante) /+;R/SC;yy+NT );;*/ )->end) /*;(( edge1 )->kante) /+;
R/SC;yy+NT );;*/ ) /*;(( edge1 )->kante) /+;R/SC;yy+NT );;*/ ,(( edge1 )->kante) /*;
(( edge1 )->kante) /+;R/SC;yy+NT );;*/ ,1); (( (( edge )->kante) /*;
else { v = gs_ide14 (-1);;*/ )->label) /*;else { v = gs_ide14 (-1);;
*/ = NULL; edge = gs_ide15 (((( (( edge1 )->kante) /*;>invisible) /+;
R/SC;yy+NT = 0;;*/ )->start) /*;>invisible) /+;R/SC;yy+NT = 0;;*/ ) /*;
>invisible) /+;R/SC;yy+NT = 0;;*/ ,v,(( edge1 )->kante) /*;>invisible) /+;
R/SC;yy+NT = 0;;*/ ,0); (( (( edge )->kante) /*;};*/ )->label) /*;};
*/ = NULL; (( (( edge )->kante) /*;>level) /+;R/SC;yy+NT = (( ((( (( edge1;
*/ )->priority) /*;>level) /+;R/SC;yy+NT = (( ((( (( edge1;*/ = 0; delete_adjedge((( edge1 )->kante) /*;
r) /+;R/SC;yy+NT = (( ((( (( edge1 )->k;*/ ); (( (( edge1 )->kante) /*;
( (( edge1 )->kante) /+;R/SC;yy+NT )->e;*/ )->invisible) /*;( (( edge1 )->kante) /+;
R/SC;yy+NT )->e;*/ = 0; } if (!invisible) { c1 = (( ((( (( edge )->kante) /*;
(( edge )->kante) /+;R/SC;yy+NT )->lab;*/ )->start) /*; (( edge )->kante) /+;
R/SC;yy+NT )->lab;*/ ) /*; (( edge )->kante) /+;R/SC;yy+NT )->lab;*/ )->connection) /*;
(( edge )->kante) /+;R/SC;yy+NT )->lab;*/ ; c2 = (( ((( (( edge )->kante) /*;
e )->kante) /+;R/SC;yy+NT )->priority) ;*/ )->end) /*;e )->kante) /+;
R/SC;yy+NT )->priority) ;*/ ) /*;e )->kante) /+;R/SC;yy+NT )->priority) ;
*/ )->connection) /*;e )->kante) /+;R/SC;yy+NT )->priority) ;*/ ; connection_possible = 1; /*;( edge1 )->kante) /+;R/SC;yy+NT );
+;R/SC;yy+NT )->invisible) /+;R/SC;yy+N;*/ if ((c1) && ((( c1 )->target) /*;+;R/SC;yy+NT )->invisible) /+;R/SC;
yy+N;*/ ) && ((( c1 )->target2) /*;+;R/SC;yy+NT )->invisible) /+;R/SC;
yy+N;*/ ))  connection_possible = 0; if ((c2) && ((( c2 )->target) /*;
visible) {;*/ ) && ((( c2 )->target2) /*;visible) {;*/ ))  connection_possible = 0; /*; edge )->kante) /+;R/SC;yy+NT )->start)
->kante) /+;R/SC;yy+NT )->end) /+;R/SC;;*/ if (gs_ide8 (((( (( edge )->kante) /*;->kante) /+;R/SC;yy+NT )->end) /+;
R/SC;;*/ )->end) /*;->kante) /+;R/SC;yy+NT )->end) /+;R/SC;;*/ ) /*;
->kante) /+;R/SC;yy+NT )->end) /+;R/SC;;*/ ,NULL, ((( (( edge )->kante) /*;
connection_possible = 1;;*/ )->start) /*;connection_possible = 1;;*/ ) /*;
connection_possible = 1;;*/ ))  connection_possible = 0; if (connection_possible) { /*;sible = 0;
>target) /+;R/SC;yy+NT ) && ((( c2 )->t;*/ if (!c1) { c1 = connectalloc(((( (( edge )->kante) /*;connection_possible = 0;
;*/ )->start) /*;connection_possible = 0;;*/ ) /*;connection_possible = 0;
;*/ ); (( c1 )->target) /*;ide8 (((( (( edge )->kante) /+;R/SC;yy+;*/ = ((( (( edge )->kante) /*;
ide8 (((( (( edge )->kante) /+;R/SC;yy+;*/ )->end) /*;ide8 (((( (( edge )->kante) /+;
R/SC;yy+;*/ ) /*;ide8 (((( (( edge )->kante) /+;R/SC;yy+;*/ ; (( c1 )->edge) /*;
>kante) /+;R/SC;yy+NT )->start) /+;R/SC;*/ = (( edge )->kante) /*;>kante) /+;
R/SC;yy+NT )->start) /+;R/SC;*/ ; } else if (!(( c1 )->target2) /*;if (connection_possible) {
;*/ ) { (( c1 )->target2) /*;) {;*/ = ((( (( edge )->kante) /*;) {;*/ )->end) /*;
) {;*/ ) /*;) {;*/ ; (( c1 )->edge2) /*;loc(((( (( edge )->kante) /+;
R/SC;yy+NT;*/ = (( edge )->kante) /*;loc(((( (( edge )->kante) /+;R/SC;
yy+NT;*/ ; } if (!c2) { c2 = connectalloc(((( (( edge )->kante) /*;}
;*/ )->end) /*;};*/ ) /*;};*/ ); (( c2 )->target) /*; (!(( c1 )->target2) /+;
R/SC;yy+NT ) {;*/ = ((( (( edge )->kante) /*; (!(( c1 )->target2) /+;
R/SC;yy+NT ) {;*/ )->start) /*; (!(( c1 )->target2) /+;R/SC;yy+NT ) {
;*/ ) /*; (!(( c1 )->target2) /+;R/SC;yy+NT ) {;*/ ; (( c2 )->edge) /*;
t2) /+;R/SC;yy+NT = ((( (( edge )->kant;*/ = (( edge )->kante) /*;t2) /+;
R/SC;yy+NT = ((( (( edge )->kant;*/ ; } else if (!(( c2 )->target2) /*;
};*/ ) { (( c2 )->target2) /*;) {;*/ = ((( (( edge )->kante) /*;) {;
*/ )->start) /*;) {;*/ ) /*;) {;*/ ; (( c2 )->edge2) /*;loc(((( (( edge )->kante) /+;
R/SC;yy+NT;*/ = (( edge )->kante) /*;loc(((( (( edge )->kante) /+;R/SC;
yy+NT;*/ ; } delete_adjedge((( edge )->kante) /*; = (( edge )->kante) /+;
R/SC;yy+NT ;;*/ ); (( (( edge )->kante) /*;};*/ )->invisible) /*;};*/ = 0; /*;}
(!(( c2 )->target2) /+;R/SC;yy+NT ) {;*/ } else if (!silent) { FPRINTF(stderr,"Nearedge connection ("); if ((( ((( (( edge )->kante) /*;
};*/ )->start) /*;};*/ ) /*;};*/ )->title) /*;};*/ [0]) FPRINTF(stderr,"%s",(( ((( (( edge )->kante) /*;
adjedge((( edge )->kante) /+;R/SC;yy+NT;*/ )->start) /*;adjedge((( edge )->kante) /+;
R/SC;yy+NT;*/ ) /*;adjedge((( edge )->kante) /+;R/SC;yy+NT;*/ )->title) /*;
adjedge((( edge )->kante) /+;R/SC;yy+NT;*/ ); FPRINTF(stderr," , "); /*;}
(!silent) {;*/  if ((( ((( (( edge )->kante) /*;};*/ )->end) /*;};*/ ) /*;};*/ )->title) /*;
};*/ [0]) FPRINTF(stderr,"%s",(( ((( (( edge )->kante) /*; (!silent) {
;*/ )->end) /*; (!silent) {;*/ ) /*; (!silent) {;*/ )->title) /*; (!silent) {
;*/ ); FPRINTF(stderr,") ignored ! Sorry !\n"); } } edge1 = (( edge1 )->next) /*;
FPRINTF(stderr,  ,  );;*/ ; } }
#ifdef ANSI_C
static void gs_ide29 (void)
#else
static void gs_ide29 ()
#endif
{ ADJEDGE edge; CONNECT c1,c2; int connection_possible; ; edge = near_edge_list; /*;_ide29 ()
{;*/ while (edge) { if (!(( (( edge )->kante) /*; edge;;*/ )->invisible) /*;
edge;;*/ ) {  c1 = (( ((( (( edge )->kante) /*;;*/ )->start) /*;;*/ ) /*;
;*/ )->connection) /*;;*/ ; c2 = (( ((( (( edge )->kante) /*;le;;*/ )->end) /*;
le;;*/ ) /*;le;;*/ )->connection) /*;le;;*/ ; connection_possible = 1; /*;near_edge_list;
;*/  if ((c1) && ((( c1 )->target) /*;near_edge_list;;*/ ) && ((( c1 )->target2) /*;
near_edge_list;;*/ ))  connection_possible = 0; if ((c2) && ((( c2 )->target) /*;
nte) /+;R/SC;yy+NT )->invisible) /+;R/S;*/ ) && ((( c2 )->target2) /*;
nte) /+;R/SC;yy+NT )->invisible) /+;R/S;*/ ))  connection_possible = 0; /*;) /+;R/SC;yy+NT )->start) /+;R/SC;yy+NT
SC;yy+NT )->end) /+;R/SC;yy+NT ) /+;R/S;*/ if (gs_ide8 (((( (( edge )->kante) /*;SC;yy+NT )->end) /+;R/SC;yy+NT ) /+;
R/S;*/ )->end) /*;SC;yy+NT )->end) /+;R/SC;yy+NT ) /+;R/S;*/ ) /*;SC;
yy+NT )->end) /+;R/SC;yy+NT ) /+;R/S;*/ ,NULL, ((( (( edge )->kante) /*;
nnection_possible = 1;;*/ )->start) /*;nnection_possible = 1;;*/ ) /*;
nnection_possible = 1;;*/ ))  connection_possible = 0; if (connection_possible) { /*;ble = 0;
arget) /+;R/SC;yy+NT ) && ((( c2 )->tar;*/ if (!c1) { c1 = connectalloc(((( (( edge )->kante) /*;connection_possible = 0;
;*/ )->start) /*;connection_possible = 0;;*/ ) /*;connection_possible = 0;
;*/ ); (( c1 )->target) /*;ide8 (((( (( edge )->kante) /+;R/SC;yy+;*/ = ((( (( edge )->kante) /*;
ide8 (((( (( edge )->kante) /+;R/SC;yy+;*/ )->end) /*;ide8 (((( (( edge )->kante) /+;
R/SC;yy+;*/ ) /*;ide8 (((( (( edge )->kante) /+;R/SC;yy+;*/ ; (( c1 )->edge) /*;
>kante) /+;R/SC;yy+NT )->start) /+;R/SC;*/ = (( edge )->kante) /*;>kante) /+;
R/SC;yy+NT )->start) /+;R/SC;*/ ; } else if (!(( c1 )->target2) /*;if (connection_possible) {
;*/ ) { (( c1 )->target2) /*;) {;*/ = ((( (( edge )->kante) /*;) {;*/ )->end) /*;
) {;*/ ) /*;) {;*/ ; (( c1 )->edge2) /*;loc(((( (( edge )->kante) /+;
R/SC;yy+NT;*/ = (( edge )->kante) /*;loc(((( (( edge )->kante) /+;R/SC;
yy+NT;*/ ; } if (!c2) { c2 = connectalloc(((( (( edge )->kante) /*;}
;*/ )->end) /*;};*/ ) /*;};*/ ); (( c2 )->target) /*; (!(( c1 )->target2) /+;
R/SC;yy+NT ) {;*/ = ((( (( edge )->kante) /*; (!(( c1 )->target2) /+;
R/SC;yy+NT ) {;*/ )->start) /*; (!(( c1 )->target2) /+;R/SC;yy+NT ) {
;*/ ) /*; (!(( c1 )->target2) /+;R/SC;yy+NT ) {;*/ ; (( c2 )->edge) /*;
t2) /+;R/SC;yy+NT = ((( (( edge )->kant;*/ = (( edge )->kante) /*;t2) /+;
R/SC;yy+NT = ((( (( edge )->kant;*/ ; } else if (!(( c2 )->target2) /*;
};*/ ) { (( c2 )->target2) /*;) {;*/ = ((( (( edge )->kante) /*;) {;
*/ )->start) /*;) {;*/ ) /*;) {;*/ ; (( c2 )->edge2) /*;loc(((( (( edge )->kante) /+;
R/SC;yy+NT;*/ = (( edge )->kante) /*;loc(((( (( edge )->kante) /+;R/SC;
yy+NT;*/ ; } if ( ((( ((( (( edge )->kante) /*; = (( edge )->kante) /+;
R/SC;yy+NT ;;*/ )->start) /*; = (( edge )->kante) /+;R/SC;yy+NT ;;*/ ) /*;
= (( edge )->kante) /+;R/SC;yy+NT ;;*/ )->level) /*; = (( edge )->kante) /+;
R/SC;yy+NT ;;*/ >=0)  &&((( ((( (( edge )->kante) /*;};*/ )->end) /*;
};*/ ) /*;};*/ )->level) /*;};*/ >=0)  &&((( ((( (( edge )->kante) /*;
(!(( c2 )->target2) /+;R/SC;yy+NT ) {;*/ )->start) /*; (!(( c2 )->target2) /+;
R/SC;yy+NT ) {;*/ ) /*; (!(( c2 )->target2) /+;R/SC;yy+NT ) {;*/ )->level) /*;
(!(( c2 )->target2) /+;R/SC;yy+NT ) {;*/ != (( ((( (( edge )->kante) /*;
t2) /+;R/SC;yy+NT = ((( (( edge )->kant;*/ )->end) /*;t2) /+;R/SC;yy+NT = ((( (( edge )->kant;
*/ ) /*;t2) /+;R/SC;yy+NT = ((( (( edge )->kant;*/ )->level) /*;t2) /+;
R/SC;yy+NT = ((( (( edge )->kant;*/ >=0) ) { if (!silent) { FPRINTF(stderr,"Nearedge connection ("); /*;}
( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ if ((( ((( (( edge )->kante) /*;( ((( (( edge )->kante) /+;R/SC;yy+NT );
*/ )->start) /*;( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ ) /*;( ((( (( edge )->kante) /+;
R/SC;yy+NT );*/ )->title) /*;( ((( (( edge )->kante) /+;R/SC;yy+NT );
*/ [0]) FPRINTF(stderr,"%s",(( ((( (( edge )->kante) /*;dge )->kante) /+;
R/SC;yy+NT )->end) /+;;*/ )->start) /*;dge )->kante) /+;R/SC;yy+NT )->end) /+;
;*/ ) /*;dge )->kante) /+;R/SC;yy+NT )->end) /+;;*/ )->title) /*;dge )->kante) /+;
R/SC;yy+NT )->end) /+;;*/ ); FPRINTF(stderr," , "); if ((( ((( (( edge )->kante) /*;
R/SC;yy+NT )->end) /+;R/SC;yy+NT ) /+;R;*/ )->end) /*;R/SC;yy+NT )->end) /+;
R/SC;yy+NT ) /+;R;*/ ) /*;R/SC;yy+NT )->end) /+;R/SC;yy+NT ) /+;R;*/ )->title) /*;
R/SC;yy+NT )->end) /+;R/SC;yy+NT ) /+;R;*/ [0]) FPRINTF(stderr,"%s",(( ((( (( edge )->kante) /*;
if (!silent) {;*/ )->end) /*;if (!silent) {;*/ ) /*;if (!silent) {;*/ )->title) /*;
if (!silent) {;*/ ); FPRINTF(stderr,"): level of target ignored ! Sorry !\n"); /*;(stderr, Nearedge connection ( );
edge )->kante) /+;R/SC;yy+NT )->start) ;*/ } } if ((( ((( (( edge )->kante) /*;FPRINTF(stderr,  ,  );;*/ )->start) /*;
FPRINTF(stderr,  ,  );;*/ ) /*;FPRINTF(stderr,  ,  );;*/ )->level) /*;
FPRINTF(stderr,  ,  );;*/ >=0) { (( ((( (( edge )->kante) /*;((( (( edge )->kante) /+;
R/SC;yy+NT )->;*/ )->end) /*;((( (( edge )->kante) /+;R/SC;yy+NT )->;
*/ ) /*;((( (( edge )->kante) /+;R/SC;yy+NT )->;*/ )->level) /*;((( (( edge )->kante) /+;
R/SC;yy+NT )->;*/ =  (( ((( (( edge )->kante) /*;, %s ,(( ((( (( edge )->kante) /+;
R/SC;;*/ )->start) /*;, %s ,(( ((( (( edge )->kante) /+;R/SC;;*/ ) /*;
, %s ,(( ((( (( edge )->kante) /+;R/SC;;*/ )->level) /*;, %s ,(( ((( (( edge )->kante) /+;
R/SC;;*/ ;  }  if ((( ((( (( edge )->kante) /*;};*/ )->end) /*;};*/ ) /*;
};*/ )->level) /*;};*/ >=0) { (( ((( (( edge )->kante) /*;};*/ )->start) /*;
};*/ ) /*;};*/ )->level) /*;};*/ =  (( ((( (( edge )->kante) /*;((( (( edge )->kante) /+;
R/SC;yy+NT )->;*/ )->end) /*;((( (( edge )->kante) /+;R/SC;yy+NT )->;
*/ ) /*;((( (( edge )->kante) /+;R/SC;yy+NT )->;*/ )->level) /*;((( (( edge )->kante) /+;
R/SC;yy+NT )->;*/ ;  }  delete_adjedge((( edge )->kante) /*;te) /+;R/SC;
yy+NT )->start) /+;R/SC;yy+;*/ ); (( (( edge )->kante) /*;} ;*/ )->invisible) /*;
} ;*/ = 0; } else if (!silent) { FPRINTF(stderr,"Nearedge connection ("); /*;te) /+;R/SC;yy+NT )->end) /+;R/SC;yy+NT
} ;*/ if ((( ((( (( edge )->kante) /*;} ;*/ )->start) /*;} ;*/ ) /*;} ;*/ )->title) /*;
} ;*/ [0]) FPRINTF(stderr,"%s",(( ((( (( edge )->kante) /*;adjedge((( edge )->kante) /+;
R/SC;yy+NT;*/ )->start) /*;adjedge((( edge )->kante) /+;R/SC;yy+NT;*/ ) /*;
adjedge((( edge )->kante) /+;R/SC;yy+NT;*/ )->title) /*;adjedge((( edge )->kante) /+;
R/SC;yy+NT;*/ ); FPRINTF(stderr," , "); if ((( ((( (( edge )->kante) /*;
};*/ )->end) /*;};*/ ) /*;};*/ )->title) /*;};*/ [0]) FPRINTF(stderr,"%s",(( ((( (( edge )->kante) /*;
(!silent) {;*/ )->end) /*; (!silent) {;*/ ) /*; (!silent) {;*/ )->title) /*;
(!silent) {;*/ ); FPRINTF(stderr,") ignored ! Sorry !\n"); } } edge = (( edge )->next) /*;
FPRINTF(stderr,  ,  );;*/ ; } }
#ifdef ANSI_C
static int gs_ide8 (GNODE v, GNODE w, GNODE z)
#else
static int gs_ide8 (v,w,z) GNODE v; GNODE w; GNODE z;
#endif
{ CONNECT c; int r; ; if (!near_edge_layout) return(1); if (!v) return(0); /*;/N;D+ z;
{;*/ if (v==z) return(1); r = 0; c = (( v )->connection) /*;int r;;*/ ; if (!c) return(0); /*;;
ar_edge_layout) return(1);;*/ if ((( c )->target) /*;ar_edge_layout) return(1);;*/ && ((( c )->target) /*;
ar_edge_layout) return(1);;*/ !=w))  r |= gs_ide8 ((( c )->target) /*;
(0);;*/ ,v,z); if ((( c )->target2) /*;if (v==z) return(1);;*/ && ((( c )->target2) /*;
if (v==z) return(1);;*/ !=w))  r |= gs_ide8 ((( c )->target2) /*;r = 0;
;*/ ,v,z); return(r); } static long gs_ide0 ;  static int gs_ide1 ; 
#ifdef ANSI_C
static void gs_ide33 (void)
#else
static void gs_ide33 ()
#endif
{ GNODE node; int depth1; ; gs_ide0 = 1L; maxdepth = 0;  gs_wait_message('p'); /*;{
ode;;*/ node = nodelist; while (node) { if ( !(( node )->markiert) /*;;;*/ ) { /*; = 1L;
;*/  gs_ide1 = 0;  gs_ide20 (node); } node = (( node )->next) /*;node = nodelist;
;*/ ; } 
#ifdef CHECK_ASSERTIONS
node = labellist; while (node) { if ( !(( node )->markiert) /*;0 (node);
;*/ ) assert((0)); node = (( node )->next) /*;};*/ ; } 
#endif
if (layout_flag==12) return; if (layout_flag==TREE_LAYOUT) return; if (G_timelimit>0)  /*;
iert) /+;R/SC;yy+NT ) assert((0));;*/ if (test_timelimit(30)) { gs_wait_message('t'); return;  } depth1 = maxdepth; /*;g==TR++_LAY;UT) return;
if (/_timelimit>0) ;*/ gs_wait_message('p'); node = nodelist; while (node) { (( node )->markiert) /*;
return; ;*/ = 0;  node = (( node )->next) /*;};*/ ; }  node = labellist; /*;e('p');
node = nodelist;;*/ while (node) { (( node )->markiert) /*;node) {;*/ = 0;  node = (( node )->next) /*;
kiert) /+;R/SC;yy+NT = 0; ;*/ ; }  node = dummylist; while (node) { (( node )->markiert) /*;
;*/ = 0;  node = (( node )->next) /*;/+;R/SC;yy+NT = 0; ;*/ ; }  gs_ide0 = 1L; /*;} 
dummylist;;*/ maxdepth = 0;  node = nodelist; while (node) { if ( !(( node )->markiert) /*;
/SC;yy+NT ;;*/ ) { gs_ide1 = 0;  gs_ide5 (node); } node = (( node )->next) /*;
node = nodelist;;*/ ; } 
#ifdef CHECK_ASSERTIONS
node = labellist; while (node) { if ( !(( node )->markiert) /*; (node);
;*/ ) assert((0)); node = (( node )->next) /*;};*/ ; } 
#endif
if ((layout_flag== 1)&&(depth1 <= maxdepth)) return; if ((layout_flag== 2)&&(depth1 >= maxdepth)) return; /*;labellist;
;*/ gs_wait_message('p'); node = nodelist; while (node) { (( node )->markiert) /*;
} ;*/ = 0;  node = (( node )->next) /*;yout_flag== 1)&&(depth1 <= maxdepth)) r;
*/ ; }  node = labellist; while (node) { (( node )->markiert) /*;node) {
;*/ = 0;  node = (( node )->next) /*;kiert) /+;R/SC;yy+NT = 0; ;*/ ; /*;t) /+;R/SC;yy+NT ;
} ;*/  }  node = dummylist; while (node) { (( node )->markiert) /*;;*/ = 0; /*;/+;R/SC;yy+NT = 0; 
/SC;yy+NT ;;*/   node = (( node )->next) /*;/+;R/SC;yy+NT = 0; ;*/ ; }  gs_ide0 = 1L; /*;dummylist;
;*/  maxdepth = 0;  node = nodelist; while (node) { if ( !(( node )->markiert) /*;
/SC;yy+NT ;;*/ ) { gs_ide1 = 0;  gs_ide20 (node); } node = (( node )->next) /*;
node = nodelist;;*/ ; } 
#ifdef CHECK_ASSERTIONS
node = labellist; while (node) { if ( !(( node )->markiert) /*;0 (node);
;*/ ) assert((0)); node = (( node )->next) /*;};*/ ; } 
#endif
}
#ifdef ANSI_C
static void gs_ide20 (GNODE node)
#else
static void gs_ide20 (node) GNODE node;
#endif
{ GNODE kn; ADJEDGE edge; int priority; assert((node)); ; if ((( node )->markiert) /*;
{;*/ ) return; (( node )->markiert) /*;n;;*/ = 1; (( node )->dfsnum) /*;
ADJ+D/+ edge;;*/ = gs_ide0 ++; if ((( node )->level) /*;ority;;*/ >=0) gs_ide1 = (( node )->level) /*;
ority;;*/ ; (( node )->tiefe) /*;;;*/ = gs_ide1 ; maxdepth = (gs_ide1 >maxdepth) ? gs_ide1 : maxdepth; /*;;
node )->markiert) /+;R/SC;yy+NT ) retur;*/ if ((( node )->connection) /*;node )->markiert) /+;R/SC;yy+NT ) retur;
*/ ) { if ((( (( node )->connection) /*;kiert) /+;R/SC;yy+NT = 1;;*/ )->target) /*;
kiert) /+;R/SC;yy+NT = 1;;*/ )  gs_ide20 ((( (( node )->connection) /*;
;R/SC;yy+NT = gs_ide0 ++;;*/ )->target) /*;;R/SC;yy+NT = gs_ide0 ++;
;*/ ); if ((( (( node )->connection) /*;C;yy+NT >=0) gs_ide1 = (( node )->level;
*/ )->target2) /*;C;yy+NT >=0) gs_ide1 = (( node )->level;*/ )  gs_ide20 ((( (( node )->connection) /*;
s_ide1 ;;*/ )->target2) /*;s_ide1 ;;*/ ); } priority = 1; while (priority>-1) { /*;->connection) /+;R/SC;yy+NT )->target) 
>connection) /+;R/SC;yy+NT )->target) /;*/ priority = -1; edge = (( node )->succ) /*;/+;R/SC;yy+NT )->target2) /+;
R/SC;yy+NT;*/ ; while (edge) { assert((((( (( edge )->kante) /*;};*/ )->start) /*;
};*/ ) /*;};*/ ==node)); kn = ((( (( edge )->kante) /*;y = 1;;*/ )->end) /*;
y = 1;;*/ ) /*;y = 1;;*/ ; if ((!(( kn )->markiert) /*;y>-1) {;*/ ) && ((( (( edge )->kante) /*;
y>-1) {;*/ )->priority) /*;y>-1) {;*/ >priority))  priority = (( (( edge )->kante) /*;
priority = -1;;*/ )->priority) /*;priority = -1;;*/ ; edge = (( edge )->next) /*;
(( node )->succ) /+;R/SC;yy+NT ;;*/ ; } if (priority== -1) break; edge = (( node )->succ) /*;
+;R/SC;yy+NT )->end) /+;R/SC;yy+NT ) /+;*/ ; while (edge) { if ((( (( edge )->kante) /*;
iority = (( (( edge )->kante) /+;R/SC;y;*/ )->priority) /*;iority = (( (( edge )->kante) /+;
R/SC;y;*/ !=priority) { edge = (( edge )->next) /*; edge )->next) /+;
R/SC;yy+NT ;;*/ ; continue; } assert((((( (( edge )->kante) /*; )->succ) /+;
R/SC;yy+NT ;;*/ )->start) /*; )->succ) /+;R/SC;yy+NT ;;*/ ) /*; )->succ) /+;
R/SC;yy+NT ;;*/ ==node)); kn = ((( (( edge )->kante) /*;while (edge) {
;*/ )->end) /*;while (edge) {;*/ ) /*;while (edge) {;*/ ; if ( !(( kn )->markiert) /*;
(( edge )->kante) /+;R/SC;yy+NT )->prio;*/ ) { gs_ide1 ++; gs_ide20 (kn); /*;continue;
};*/ gs_ide1 = (( node )->tiefe) /*;};*/ ; } else {  if (kn == node) ((( (( edge )->kante) /*;
rt) /+;R/SC;yy+NT ) {;*/ )->kantenart) /*;rt) /+;R/SC;yy+NT ) {;*/ ) /*;
rt) /+;R/SC;yy+NT ) {;*/ = 'S'; } edge = (( edge )->next) /*;0 (kn);
;*/ ; } }  }
#ifdef ANSI_C
static void gs_ide5 (GNODE node)
#else
static void gs_ide5 (node) GNODE node;
#endif
{ GNODE kn; ADJEDGE edge; int priority; assert((node)); ; if ((( node )->markiert) /*;
{;*/ ) return; (( node )->markiert) /*;n;;*/ = 1; (( node )->dfsnum) /*;
ADJ+D/+ edge;;*/ = gs_ide0 ++; if ((( node )->level) /*;ority;;*/ >=0) gs_ide1 = (( node )->level) /*;
ority;;*/ ; (( node )->tiefe) /*;;;*/ = gs_ide1 ; maxdepth = (gs_ide1 >maxdepth) ? gs_ide1 : maxdepth; /*;;
node )->markiert) /+;R/SC;yy+NT ) retur;*/ if ((( node )->connection) /*;node )->markiert) /+;R/SC;yy+NT ) retur;
*/ ) { if ((( (( node )->connection) /*;kiert) /+;R/SC;yy+NT = 1;;*/ )->target) /*;
kiert) /+;R/SC;yy+NT = 1;;*/ )  gs_ide5 ((( (( node )->connection) /*;
;R/SC;yy+NT = gs_ide0 ++;;*/ )->target) /*;;R/SC;yy+NT = gs_ide0 ++;
;*/ ); if ((( (( node )->connection) /*;C;yy+NT >=0) gs_ide1 = (( node )->level;
*/ )->target2) /*;C;yy+NT >=0) gs_ide1 = (( node )->level;*/ )  gs_ide5 ((( (( node )->connection) /*;
s_ide1 ;;*/ )->target2) /*;s_ide1 ;;*/ ); } priority = 1; while (priority>-1) { /*;->connection) /+;R/SC;yy+NT )->target) 
connection) /+;R/SC;yy+NT )->target) /+;*/ priority = -1; edge = (( node )->succ) /*;/+;R/SC;yy+NT )->target2) /+;
R/SC;yy+NT;*/ ; while (edge) { assert((((( (( edge )->kante) /*;};*/ )->start) /*;
};*/ ) /*;};*/ ==node)); kn = ((( (( edge )->kante) /*;y = 1;;*/ )->end) /*;
y = 1;;*/ ) /*;y = 1;;*/ ; if ((!(( kn )->markiert) /*;y>-1) {;*/ ) && ((( (( edge )->kante) /*;
y>-1) {;*/ )->priority) /*;y>-1) {;*/ >priority))  priority = (( (( edge )->kante) /*;
priority = -1;;*/ )->priority) /*;priority = -1;;*/ ; edge = (( edge )->next) /*;
(( node )->succ) /+;R/SC;yy+NT ;;*/ ; } if (priority== -1) break; gs_ide43 ((( node )->succ) /*;
+;R/SC;yy+NT )->end) /+;R/SC;yy+NT ) /+;*/ ,node,priority); } }
#ifdef ANSI_C
static void gs_ide43 ( ADJEDGE edge, GNODE node, int priority)
#else
static void gs_ide43 (edge,node,priority) ADJEDGE edge; GNODE node; int priority; /*;ADJ+D/+ edge,
ode,;*/ 
#endif
{ GNODE kn; ; if (!edge) return; gs_ide43 ((( edge )->next) /*;ode;;
*/ ,node,priority); if ((( (( edge )->kante) /*;int priority;;*/ )->priority) /*;
int priority;;*/ !=priority) return; kn = ((( (( edge )->kante) /*;{
;*/ )->end) /*;{;*/ ) /*;{;*/ ; if ( !(( kn )->markiert) /*;n;;*/ ) { /*;;
ge) return;;*/  gs_ide1 ++; gs_ide5 (kn); gs_ide1 = (( node )->tiefe) /*;dge )->next) /+;
R/SC;yy+NT ,node,priori;*/ ; } else {  if (kn == node) ((( (( edge )->kante) /*;
+NT ) {;*/ )->kantenart) /*;+NT ) {;*/ ) /*;+NT ) {;*/ = 'S'; } } static GNLIST gs_ide54 ; /*;e )->tiefe) /+;R/SC;yy+NT ;
};*/   static GNLIST gs_ide53 ; 
#ifdef ANSI_C
static void gs_ide4 (GNODE v)
#else
static void gs_ide4 (v) GNODE v;
#endif
{ GNLIST h; ; if (gs_ide53 ) { h = gs_ide53 ; gs_ide53 = (( gs_ide53 )->next) /*;
;;*/ ; } else h = tmpnodelist_alloc(); (( h )->node) /*;;;*/ = v; (( h )->next) /*;
ide53 ) {;*/ = gs_ide54 ; gs_ide54 = h; }
#ifdef ANSI_C
static GNODE gs_ide24 (void)
#else
static GNODE gs_ide24 ()
#endif
{ GNLIST h; ; h = gs_ide54 ; if (h) { gs_ide54 = (( h )->next) /*;s_ide24 ();
*/ ; (( h )->next) /*;{;*/ = gs_ide53 ; gs_ide53 = h; return((( h )->node) /*;
;;*/ ); } return(NULL); }
#ifdef ANSI_C
static void gs_ide46 (void)
#else
static void gs_ide46 ()
#endif
{ GNODE v; int not_ready, actlevel; ; gs_ide54 = NULL; gs_ide53 = NULL; /*;_ide46 ()
{;*/   v = nodelist; while (v) { if (gs_ide48 (v,v)==0) gs_ide4 (v); v = (( v )->next) /*;
;;*/ ; } maxdepth = 0;  gs_wait_message('p'); not_ready = 1; while (not_ready) { /*;v,v)==0) gs_ide4 (v);
R/SC;yy+NT ;;*/ while ((v = gs_ide24 ())!=NULL) { actlevel = gs_ide49 (v,v); if ((( v )->level) /*;
h = 0; ;*/ >=0) actlevel = (( v )->level) /*;h = 0; ;*/ ; if (maxdepth<actlevel) maxdepth = actlevel; /*;e('p');
not_ready = 1;;*/ gs_ide50 (v,v,actlevel); gs_ide47 (v,v); } gs_wait_message('p'); not_ready = 0; /*;y+NT >=0) actlevel = (( v )->level) /+;
ctlevel;;*/   v = nodelist; while (v && !not_ready) { if (!(( v )->markiert) /*;
(v,v);;*/ ) { gs_ide4 (v); not_ready = 1; } v = (( v )->next) /*; ;*/ ; /*; 
v = nodelist;;*/ } v = labellist; while (v && !not_ready) { if (!(( v )->markiert) /*;
y = 1;;*/ ) { gs_ide4 (v); not_ready = 1; } v = (( v )->next) /*;};*/ ; /*;}
ellist;;*/ } v = dummylist; while (v && !not_ready) { if (!(( v )->markiert) /*;
gs_ide4 (v); not_ready = 1;;*/ ) { gs_ide4 (v); not_ready = 1; } v = (( v )->next) /*;
};*/ ; } } }
#ifdef ANSI_C
static int gs_ide49 (GNODE node1, GNODE node2)
#else
static int gs_ide49 (node1,node2) GNODE node1; GNODE node2;
#endif
{ int result, h; ADJEDGE a; CONNECT c; ; result = 0; a = (( node1 )->pred) /*;
{;*/ ; while (a) { if (((( (( a )->kante) /*;ADJ+D/+ a;;*/ )->start) /*;
ADJ+D/+ a;;*/ ) /*;ADJ+D/+ a;;*/ ==node1) ((( (( a )->kante) /*;ADJ+D/+ a;
;*/ )->kantenart) /*;ADJ+D/+ a;;*/ ) /*;ADJ+D/+ a;;*/ = 'S'; else if ((( ((( (( a )->kante) /*;
c;;*/ )->start) /*; c;;*/ ) /*; c;;*/ )->markiert) /*; c;;*/ ) { if ((( ((( (( a )->kante) /*;
;;*/ )->start) /*;;;*/ ) /*;;;*/ )->tiefe) /*;;;*/ >=result) result = (( ((( (( a )->kante) /*;
= 0;;*/ )->start) /*;= 0;;*/ ) /*;= 0;;*/ )->tiefe) /*;= 0;;*/ +1; } /*;while (a) {
(( a )->kante) /+;R/SC;yy+NT )->start);*/  a = (( a )->next) /*;while (a) {;*/ ; } c = (( node1 )->connection) /*;
( (( a )->kante) /+;R/SC;yy+NT )->start;*/ ; if (c && (( c )->target) /*;
nte) /+;R/SC;yy+NT )->start) /+;R/SC;yy;*/ && ((( c )->target) /*;nte) /+;
R/SC;yy+NT )->start) /+;R/SC;yy;*/ !=node2)) {  h = gs_ide49 ((( c )->target) /*;
e) /+;R/SC;yy+NT )->start) /+;R/SC;yy+N;*/ ,node1); if (h>result) result = h; /*;}
a )->next) /+;R/SC;yy+NT ;;*/ } if (c && (( c )->target2) /*;};*/ && ((( c )->target2) /*;};*/ !=node2)) { /*;}
node1 )->connection) /+;R/SC;yy+NT ;;*/   h = gs_ide49 ((( c )->target2) /*;node1 )->connection) /+;R/SC;yy+NT ;
;*/ ,node1); if (h>result) result = h; } return(result); }
#ifdef ANSI_C
static void gs_ide50 (GNODE node1,GNODE node2,int level)
#else
static void gs_ide50 (node1,node2,level) GNODE node1; GNODE node2; int level; /*;result);
};*/ 
#endif
{ CONNECT c; ; if (((( node1 )->level) /*;/N;D+ node1;;*/ >=0)&&(level!=(( node1 )->level) /*;
/N;D+ node1;;*/ )) { if (!silent) {  FPRINTF(stderr,"Level specification ignored, "); /*;int level;
{;*/ FPRINTF(stderr,"because nearedge was specified !\n"); } } (( node1 )->tiefe) /*;
node1 )->level) /+;R/SC;yy+NT >=0)&&(l;*/ = level; (( node1 )->markiert) /*;
;*/ = 1; c = (( node1 )->connection) /*; specification ignored,  );
;*/ ; if (c && (( c )->target) /*;edge was specified !zn );;*/ && ((( c )->target) /*;
edge was specified !zn );;*/ !=node2))  gs_ide50 ((( c )->target) /*;
};*/ ,node1,level); if (c && (( c )->target2) /*;};*/ && ((( c )->target2) /*;
};*/ !=node2))  gs_ide50 ((( c )->target2) /*;1 )->tiefe) /+;R/SC;yy+NT = level;
;*/ ,node1,level); }
#ifdef ANSI_C
static void gs_ide47 (GNODE node1, GNODE node2)
#else
static void gs_ide47 (node1,node2) GNODE node1; GNODE node2;
#endif
{ ADJEDGE a; CONNECT c; ; a = (( node1 )->succ) /*;/N;D+ node1;;*/ ; /*;ode2;
{;*/  while (a) { if ( (gs_ide48 (((( (( a )->kante) /*;{;*/ )->end) /*;{
;*/ ) /*;{;*/ ,((( (( a )->kante) /*;{;*/ )->end) /*;{;*/ ) /*;{;*/ )==0) /*;{
a;;*/ &&(!(( ((( (( a )->kante) /*; a;;*/ )->end) /*; a;;*/ ) /*; a;;*/ )->markiert) /*;
a;;*/ ) )  gs_ide4 (((( (( a )->kante) /*;C;NN+CT c;;*/ )->end) /*;
C;NN+CT c;;*/ ) /*;C;NN+CT c;;*/ ); a = (( a )->next) /*;;;*/ ; } c = (( node1 )->connection) /*;
while (a) {;*/ ; if (c && (( c )->target) /*;s_ide48 (((( (( a )->kante) /+;
R/SC;yy+;*/ && ((( c )->target) /*;s_ide48 (((( (( a )->kante) /+;R/SC;
yy+;*/ !=node2))  gs_ide47 ((( c )->target) /*;a )->kante) /+;R/SC;yy+NT )->end) /+;
R/;*/ ,node1); if (c && (( c )->target2) /*;kante) /+;R/SC;yy+NT )->end) /+;
R/SC;yy;*/ && ((( c )->target2) /*;kante) /+;R/SC;yy+NT )->end) /+;R/SC;
yy;*/ !=node2))  gs_ide47 ((( c )->target2) /*;+NT ;;*/ ,node1); }
#ifdef ANSI_C
static int gs_ide48 (GNODE node1,GNODE node2)
#else
static int gs_ide48 (node1,node2) GNODE node1; GNODE node2;
#endif
{ int result; ADJEDGE a; CONNECT c; ; result = 0; a = (( node1 )->pred) /*;
{;*/ ; while (a) { if ( !(( ((( (( a )->kante) /*;ADJ+D/+ a;;*/ )->start) /*;
ADJ+D/+ a;;*/ ) /*;ADJ+D/+ a;;*/ )->markiert) /*;ADJ+D/+ a;;*/ ) result++; /*;ADJ+D/+ a;
c;;*/ a = (( a )->next) /*; c;;*/ ; } c = (( node1 )->connection) /*;= 0;;
*/ ; if (c && (( c )->target) /*;->pred) /+;R/SC;yy+NT ;;*/ && ((( c )->target) /*;
->pred) /+;R/SC;yy+NT ;;*/ !=node2))  result += gs_ide48 ((( c )->target) /*;
while (a) {;*/ ,node1); if (c && (( c )->target2) /*;( ((( (( a )->kante) /+;
R/SC;yy+NT )->s;*/ && ((( c )->target2) /*;( ((( (( a )->kante) /+;R/SC;
yy+NT )->s;*/ !=node2))  result += gs_ide48 ((( c )->target2) /*;xt) /+;
R/SC;yy+NT ;;*/ ,node1); return(result); } static GNLIST gs_ide25 ; 
#ifdef ANSI_C
static void gs_ide3 (GNODE v, GNLIST *l)
#else
static void gs_ide3 (v, l) GNODE v; GNLIST *l;
#endif
{ GNLIST h; ; if (gs_ide53 ) { h = gs_ide53 ; gs_ide53 = (( gs_ide53 )->next) /*;
*l;;*/ ; } else h = tmpnodelist_alloc(); (( h )->node) /*;;;*/ = v; (( h )->next) /*;
ide53 ) {;*/ = *l; *l = h; }
#ifdef ANSI_C
static GNODE gs_ide23 (GNLIST *l)
#else
static GNODE gs_ide23 (l) GNLIST *l;
#endif
{ GNLIST h; ; h = *l; if (h) { *l = (( h )->next) /*;/NLIST *l;;*/ ; /*;{
h;;*/  (( h )->next) /*;{;*/ = gs_ide53 ; gs_ide53 = h; return((( h )->node) /*;
;;*/ ); } return(NULL); }
#ifdef ANSI_C
static void gs_ide37 (void)
#else
static void gs_ide37 ()
#endif
{ GNODE v; ; gs_ide53 = NULL;  gs_ide25 = NULL;  maxdepth = 1;  v = nodelist; /*;{
;;*/ while (v) { if (!(( v )->invisible) /*;;;*/ ) gs_ide3 (v, &gs_ide25 ); /*;;
3 = NULL; ;*/  (( v )->tiefe) /*;;;*/ = 1; v = (( v )->next) /*;3 = NULL; ;*/ ; } v = labellist; /*;maxdepth = 1; 
elist;;*/ while (v) { gs_ide3 (v, &gs_ide25 ); (( v )->tiefe) /*; (!(( v )->invisible) /+;
R/SC;yy+NT ) g;*/ = 1; v = (( v )->next) /*;C;yy+NT = 1;;*/ ; } v = dummylist; /*;}
ellist;;*/ while (v) { gs_ide3 (v, &gs_ide25 ); (( v )->tiefe) /*;_ide3 (v, &gs_ide25 );
;*/ = 1; v = (( v )->next) /*;C;yy+NT = 1;;*/ ; } gs_ide7 (&gs_ide25 ); /*;}
mylist;;*/ }
#ifdef ANSI_C
static void gs_ide7 (GNLIST *nlist)
#else
static void gs_ide7 (nlist) GNLIST *nlist;
#endif
{ GNODE v; GNLIST h; GNLIST open_scc_list; long mydfsnum; ;
#ifdef SCCDEBUG
PRINTF("Calc SCC:\n");
#endif
h = *nlist; while (h) { v = (( h )->node) /*;open_scc_list;;*/ ; (( v )->markiert) /*;
;*/ = (( v )->tiefe) /*;;*/ = 0; (( v )->weights) /*;;;*/ = (( v )->weightp) /*;
;;*/ = 0L;
#ifdef SCCDEBUG
PRINTF("[%ld|%s] ", v,((( v )->title) /*; Calc SCC:zn );;*/ ?(( v )->title) /*;
Calc SCC:zn );;*/ :"null"));
#endif
h = (( h )->next) /*;h = *nlist;;*/ ; }
#ifdef SCCDEBUG
PRINTF("\n");
#endif
open_scc_list = NULL; mydfsnum = 0; gs_wait_message('p'); v = gs_ide23 (nlist); /*;= (( h )->next) /+;R/SC;yy+NT ;
};*/ while (v) { gs_ide41 (v,&mydfsnum,&open_scc_list); v = gs_ide23 (nlist); /*;= NULL;
mydfsnum = 0;;*/ } }
#ifdef ANSI_C
static void gs_ide41 (GNODE node, long *dfsnum, GNLIST *open_sccp)
#else
static void gs_ide41 (node, dfsnum, open_sccp) GNODE node; long *dfsnum; /*;nlist);
};*/ GNLIST *open_sccp;
#endif
{ GNODE kn; GNLIST h; GNLIST closed_scc_list; ADJEDGE edge; int mylevel; /*;ccp;
{;*/ GNODE actrev; int degree; int minindeg; int maxoutdeg; int maxpreindeg; /*;ADJ+D/+ edge;
evel;;*/ int minlevel; assert((node)); ; if ((( node )->markiert) /*;int minindeg;
;*/ ) return; (( node )->markiert) /*;outdeg;;*/ = 1; (( node )->weightp) /*;
g;;*/ = 1L; (( node )->dfsnum) /*;int minlevel;;*/ = *dfsnum; (( node )->weights) /*;
(node));;*/ = *dfsnum; (*dfsnum)++; gs_ide3 (node, open_sccp); if ((( node )->connection) /*;
kiert) /+;R/SC;yy+NT = 1;;*/ ) { if ((( (( node )->connection) /*;+;
R/SC;yy+NT = 1L;;*/ )->target) /*;+;R/SC;yy+NT = 1L;;*/ ) { kn = (( (( node )->connection) /*;
y+NT = *dfsnum;;*/ )->target) /*;y+NT = *dfsnum;;*/ ; gs_ide41 (kn,dfsnum,open_sccp); /*; *dfsnum;
dfsnum)++;;*/ if (((( kn )->weightp) /*;dfsnum)++;;*/ ) && ((( kn )->weights) /*;dfsnum)++;
;*/ <(( node )->weights) /*;dfsnum)++;;*/ ))  (( node )->weights) /*;
node, open_sccp);;*/ = (( kn )->weights) /*;node, open_sccp);;*/ ; } /*;ction) /+;R/SC;yy+NT )->target) /+;R/SC
/+;R/SC;yy+NT )->target) /+;R/SC;yy+NT;*/  if ((( (( node )->connection) /*;ction) /+;R/SC;yy+NT )->target) /+;
R/SC;*/ )->target2) /*;ction) /+;R/SC;yy+NT )->target) /+;R/SC;*/ ) { /*; /+;R/SC;yy+NT )->target) /+;R/SC;yy+NT
gs_ide41 (kn,dfsnum,open_sccp);;*/  kn = (( (( node )->connection) /*; /+;R/SC;yy+NT )->target) /+;R/SC;
yy+NT;*/ )->target2) /*; /+;R/SC;yy+NT )->target) /+;R/SC;yy+NT;*/ ; /*;gs_ide41 (kn,dfsnum,open_sccp);
kn )->weightp) /+;R/SC;yy+NT ) && ((( ;*/  gs_ide41 (kn,dfsnum,open_sccp); if (((( kn )->weightp) /*; kn )->weightp) /+;
R/SC;yy+NT ) && ((( ;*/ ) && ((( kn )->weights) /*; kn )->weightp) /+;
R/SC;yy+NT ) && ((( ;*/ <(( node )->weights) /*; kn )->weightp) /+;R/SC;
yy+NT ) && ((( ;*/ ))  (( node )->weights) /*;ghts) /+;R/SC;yy+NT = (( kn )->weights);
*/ = (( kn )->weights) /*;ghts) /+;R/SC;yy+NT = (( kn )->weights);*/ ; /*;}
(( node )->connection) /+;R/SC;yy+NT )-;*/  } } edge = (( node )->pred) /*;e )->connection) /+;R/SC;yy+NT )->targe;
*/ ; while (edge) { assert((((( (( edge )->kante) /*;SC;yy+NT ) && ((( kn )->weights) /+;
R/S;*/ )->end) /*;SC;yy+NT ) && ((( kn )->weights) /+;R/S;*/ ) /*;SC;
yy+NT ) && ((( kn )->weights) /+;R/S;*/ ==node)); kn = ((( (( edge )->kante) /*;
(( kn )->weights) /+;R/SC;yy+NT ;;*/ )->start) /*; (( kn )->weights) /+;
R/SC;yy+NT ;;*/ ) /*; (( kn )->weights) /+;R/SC;yy+NT ;;*/ ; if ((( kn )->tiefe) /*;
};*/ ==0) { gs_ide41 (kn,dfsnum,open_sccp); if (((( kn )->weightp) /*;
(( node )->pred) /+;R/SC;yy+NT ;;*/ ) && ((( kn )->weights) /*;(( node )->pred) /+;
R/SC;yy+NT ;;*/ <(( node )->weights) /*;(( node )->pred) /+;R/SC;yy+NT ;
;*/ ))  (( node )->weights) /*;;*/ = (( kn )->weights) /*;;*/ ; } edge = (( edge )->next) /*;
+;R/SC;yy+NT )->start) /+;R/SC;yy+NT ) ;*/ ; } if ((( node )->weights) /*;
_ide41 (kn,dfsnum,open_sccp);;*/ == (( node )->dfsnum) /*;_ide41 (kn,dfsnum,open_sccp);
;*/ ) { h = closed_scc_list = *open_sccp; assert((h)); kn = (( h )->node) /*;
};*/ ; while (kn!=node) { (( kn )->weightp) /*;};*/ = 0L; h = (( h )->next) /*;
node )->weights) /+;R/SC;yy+NT == (( no;*/ ; assert((h)); kn = (( h )->node) /*;
assert((h));;*/ ; } assert((kn==node)); (( node )->weightp) /*;R/SC;
yy+NT = 0L;;*/ = 0L; *open_sccp = (( h )->next) /*;+NT ;;*/ ; (( h )->next) /*;
assert((h));;*/ = 0;
#ifdef SCCDEBUG
PRINTF("Test SCC:\n"); h = closed_scc_list; while (h) { kn = (( h )->node) /*;
ghtp) /+;R/SC;yy+NT = 0L;;*/ ; PRINTF("[%ld|%s] ", kn,((( kn )->title) /*;
next) /+;R/SC;yy+NT ;;*/ ?(( kn )->title) /*;next) /+;R/SC;yy+NT ;;*/ :"null")); /*;next) /+;R/SC;yy+NT ;
= 0;;*/ h = (( h )->next) /*;= 0;;*/ ; }
#endif
minlevel = -1; h = closed_scc_list; while (h) { node = (( h )->node) /*;
s]  , kn,((( kn )->title) /+;R/SC;yy+NT;*/ ; edge = (( node )->pred) /*;
R/SC;yy+NT ;;*/ ; while (edge) { kn = ((( (( edge )->kante) /*;l = -1;
;*/ )->start) /*;l = -1;;*/ ) /*;l = -1;;*/ ; mylevel = (( kn )->tiefe) /*;
_list;;*/ ;  if (mylevel > minlevel) minlevel = mylevel; edge = (( edge )->next) /*;
(( h )->node) /+;R/SC;yy+NT ;;*/ ; } h = (( h )->next) /*;while (edge) {
;*/ ; }
#ifdef SCCDEBUG
PRINTF(" minlevel: %d\n",minlevel);
#endif
assert((closed_scc_list)); degree = gs_ide12 (closed_scc_list); if (degree) { /*;}
h )->next) /+;R/SC;yy+NT ;;*/ 
#ifdef SCCDEBUG
PRINTF("Next complete SCC:\n");
#endif
minlevel++; kn = gs_ide23 (&closed_scc_list); while (kn) { if ((( kn )->level) /*;
osed_scc_list);;*/ >=0) (( kn )->tiefe) /*;osed_scc_list);;*/ = (( kn )->level) /*;
osed_scc_list);;*/ ; else (( kn )->tiefe) /*;if (degree) {;*/ = minlevel; /*;if (degree) {
Next complete SCC:zn );;*/ maxdepth = ((( kn )->tiefe) /*; Next complete SCC:zn );;*/ >maxdepth) ?  /*; Next complete SCC:zn );
minlevel++;;*/ (( kn )->tiefe) /*;minlevel++;;*/ : maxdepth;
#ifdef SCCDEBUG
PRINTF("[%ld|%s] (%d) (max %d)\n", kn, ((( kn )->title) /*;while (kn) {
;*/ ?(( kn )->title) /*;while (kn) {;*/ :"null"), (( kn )->tiefe) /*;
kn )->level) /+;R/SC;yy+NT >=0) (( kn );*/ , maxdepth);
#endif
kn = gs_ide23 (&closed_scc_list); } return; } h = closed_scc_list; while (h) { /*;tiefe) /+;R/SC;yy+NT , maxdepth);
closed_scc_list);;*/ (( (( h )->node) /*;closed_scc_list);;*/ )->tiefe) /*;closed_scc_list);
;*/ = MAXINT; h = (( h )->next) /*;};*/ ; } actrev = (( closed_scc_list )->node) /*;
};*/ ; minindeg = MAXINT; maxoutdeg = 0; maxpreindeg = 0; h = closed_scc_list; /*;xt) /+;R/SC;yy+NT ;
};*/ while (h) { node = (( h )->node) /*;= (( closed_scc_list )->node) /+;
R/SC;y;*/ ; degree = gs_ide39 (node, NULL, 1);  if (degree < minindeg) { /*;maxoutdeg = 0;
ndeg = 0;;*/ minindeg = degree; actrev = node; h = (( h )->next) /*;while (h) {;*/ ; /*;while (h) {
(( h )->node) /+;R/SC;yy+NT ;;*/ continue; } else if (degree > minindeg) { h = (( h )->next) /*;minindeg = degree;
;*/ ; continue; } degree = gs_ide38 (node, NULL);  if (degree > maxoutdeg) { /*;}
(degree > minindeg) {;*/ maxoutdeg = degree; actrev = node; h = (( h )->next) /*;continue;;*/ ; /*;}
= gs_ide38 (node, NULL); ;*/  continue; } else if (degree < maxoutdeg) { h = (( h )->next) /*;maxoutdeg = degree;
;*/ ; continue; } degree = gs_ide40 (node, NULL);  if (degree > maxpreindeg) { /*;}
(degree < maxoutdeg) {;*/ maxpreindeg = degree; actrev = node; } h = (( h )->next) /*;};*/ ; }
#ifdef SCCDEBUG
PRINTF("Revert Preds on [%d|%s] %d %d %d\n", actrev, ((( actrev )->title) /*;
;*/ ?(( actrev )->title) /*;;*/ :"null"), minindeg, maxoutdeg, maxpreindeg); /*;actrev = node;
};*/ 
#endif
gs_ide36 (actrev, NULL); gs_ide7 (&closed_scc_list); } }
#ifdef ANSI_C
static int gs_ide12 (GNLIST nlist)
#else
static int gs_ide12 (nlist) GNLIST nlist;
#endif
{ GNODE v; GNLIST h; int res, count; CONNECT c; ; assert((nlist)); count = 0; /*;;
/NLIST h;;*/ res = 1; h = nlist; while (h) { count++; if ((( (( h )->node) /*;(nlist));
;*/ )->level) /*;(nlist));;*/ <0) res = 0; h = (( h )->next) /*;count = 0;
;*/ ; } if (res) return(1); if (count==1) return(1); h = nlist; while (h) { /*;(( h )->node) /+;R/SC;yy+NT )->level) /
xt) /+;R/SC;yy+NT ;;*/ assert(((( (( h )->node) /*;xt) /+;R/SC;yy+NT ;;*/ )->markiert) /*;xt) /+;
R/SC;yy+NT ;;*/ ==1)); (( (( h )->node) /*;};*/ )->markiert) /*;};*/ = 0; /*;}
) return(1);;*/ h = (( h )->next) /*;) return(1);;*/ ; } count = 1; (( (( nlist )->node) /*;
h) {;*/ )->markiert) /*;h) {;*/ = 1; while (count) { count = 0; h = nlist; /*;+NT ;
};*/ while (h) { v = (( h )->node) /*; 1;;*/ ; if ((( v )->markiert) /*;>node) /+;
R/SC;yy+NT )->markiert) /+;R/;*/ ) { c = (( v )->connection) /*;while (count) {
;*/ ; if ((c)&&(( c )->edge) /*; 0;;*/ ) { if (!(( (( (( c )->edge) /*;
h = nlist;;*/ )->start) /*;h = nlist;;*/ )->markiert) /*;h = nlist;;
*/ ) count++; if (!(( (( (( c )->edge) /*;h) {;*/ )->end) /*;h) {;*/ )->markiert) /*;
h) {;*/ ) count++; (( (( (( c )->edge) /*;de) /+;R/SC;yy+NT ;;*/ )->start) /*;
de) /+;R/SC;yy+NT ;;*/ )->markiert) /*;de) /+;R/SC;yy+NT ;;*/ = 1; (( (( (( c )->edge) /*;
/+;R/SC;yy+NT ) {;*/ )->end) /*; /+;R/SC;yy+NT ) {;*/ )->markiert) /*;
/+;R/SC;yy+NT ) {;*/ = 1; } if ((c)&&(( c )->edge2) /*;T ) {;*/ ) { /*; (!(( (( (( c )->edge) /+;R/SC;yy+NT )-
( (( c )->edge) /+;R/SC;yy+NT )->end) /;*/  if (!(( (( (( c )->edge2) /*; (!(( (( (( c )->edge) /+;R/SC;yy+NT )-;
*/ )->start) /*; (!(( (( (( c )->edge) /+;R/SC;yy+NT )-;*/ )->markiert) /*;
(!(( (( (( c )->edge) /+;R/SC;yy+NT )-;*/ ) count++; if (!(( (( (( c )->edge2) /*;
( (( c )->edge) /+;R/SC;yy+NT )->end) /;*/ )->end) /*;( (( c )->edge) /+;
R/SC;yy+NT )->end) /;*/ )->markiert) /*;( (( c )->edge) /+;R/SC;yy+NT )->end) /;
*/ ) count++; (( (( (( c )->edge2) /*;ge) /+;R/SC;yy+NT )->start) /+;
R/SC;yy+;*/ )->start) /*;ge) /+;R/SC;yy+NT )->start) /+;R/SC;yy+;*/ )->markiert) /*;
ge) /+;R/SC;yy+NT )->start) /+;R/SC;yy+;*/ = 1; (( (( (( c )->edge2) /*;
R/SC;yy+NT )->end) /+;R/SC;yy+NT )->mar;*/ )->end) /*;R/SC;yy+NT )->end) /+;
R/SC;yy+NT )->mar;*/ )->markiert) /*;R/SC;yy+NT )->end) /+;R/SC;yy+NT )->mar;
*/ = 1; } }  h = (( h )->next) /*;c )->edge2) /+;R/SC;yy+NT )->start) /+;
;*/ ; }  } res = 1; h = nlist; while (h) { if (!(( (( h )->node) /*;
h )->next) /+;R/SC;yy+NT ;;*/ )->markiert) /*;h )->next) /+;R/SC;yy+NT ;
;*/ ) { res = 0; break; } h = (( h )->next) /*;} ;*/ ; } h = nlist; while (h) { /*;h = nlist;
h) {;*/ (( (( h )->node) /*;h) {;*/ )->markiert) /*;h) {;*/ = 1; h = (( h )->next) /*;
->node) /+;R/SC;yy+NT )->markiert) /+;R;*/ ; } return(res);  }
#ifdef ANSI_C
static int gs_ide39 (GNODE v, GNODE w, int prio) 
#else
static int gs_ide39 (v, w, prio) GNODE v; GNODE w;  int prio;
#endif
{ int degree; ADJEDGE e; CONNECT c; degree = 0; e = (( v )->succ) /*;
int prio;;*/ ; while (e) { if ((( ((( (( e )->kante) /*;ree;;*/ )->end) /*;
ree;;*/ ) /*;ree;;*/ )->tiefe) /*;ree;;*/ ==MAXINT) { if (prio) degree+=(( (( e )->kante) /*;
c;;*/ )->priority) /*; c;;*/ ; else degree++; } e = (( e )->next) /*;
while (e) {;*/ ; } c = (( v )->connection) /*;if (prio);*/ ; if (!c) return(degree); /*;=(( (( e )->kante) /+;R/SC;yy+NT )->pri
;*/ if ((( c )->target) /*;;*/ && (w!=(( c )->target) /*;;*/ ))  degree += gs_ide39 ((( c )->target) /*;
};*/ ,v, prio); if ((( c )->target2) /*;e )->next) /+;R/SC;yy+NT ;;*/ && (w!=(( c )->target2) /*;
e )->next) /+;R/SC;yy+NT ;;*/ ))  degree += gs_ide39 ((( c )->target2) /*;
};*/ ,v, prio); return(degree); }
#ifdef ANSI_C
static int gs_ide40 (GNODE v, GNODE w) 
#else
static int gs_ide40 (v, w) GNODE v; GNODE w; 
#endif
{ int degree; ADJEDGE e; CONNECT c; degree = 0; e = (( v )->succ) /*;
; ;*/ ; while (e) { if ((( ((( (( e )->kante) /*;ree;;*/ )->end) /*;
ree;;*/ ) /*;ree;;*/ )->tiefe) /*;ree;;*/ ==MAXINT) { degree += gs_ide39 (((( (( e )->kante) /*;
ADJ+D/+ e;;*/ )->start) /*;ADJ+D/+ e;;*/ ) /*;ADJ+D/+ e;;*/ ,NULL,0); /*; c;
degree = 0;;*/  } e = (( e )->next) /*;degree = 0;;*/ ; } c = (( v )->connection) /*;
while (e) {;*/ ; if (!c) return(degree); if ((( c )->target) /*;de39 (((( (( e )->kante) /+;
R/SC;yy+NT ;*/ && (w!=(( c )->target) /*;de39 (((( (( e )->kante) /+;
R/SC;yy+NT ;*/ ))  degree += gs_ide40 ((( c )->target) /*;};*/ ,v); if ((( c )->target2) /*;
e )->next) /+;R/SC;yy+NT ;;*/ && (w!=(( c )->target2) /*;e )->next) /+;
R/SC;yy+NT ;;*/ ))  degree += gs_ide40 ((( c )->target2) /*;};*/ ,v); /*;v )->connection) /+;R/SC;yy+NT ;
(degree);;*/  return(degree); }
#ifdef ANSI_C
static int gs_ide38 (GNODE v, GNODE w) 
#else
static int gs_ide38 (v, w) GNODE v; GNODE w; 
#endif
{ int degree; ADJEDGE e; CONNECT c; degree = 0; e = (( v )->pred) /*;
; ;*/ ; while (e) { if ((( ((( (( e )->kante) /*;ree;;*/ )->start) /*;
ree;;*/ ) /*;ree;;*/ )->tiefe) /*;ree;;*/ ==MAXINT) { degree++; } e = (( e )->next) /*;
degree = 0;;*/ ; } c = (( v )->connection) /*;while (e) {;*/ ; if (!c) return(degree); /*;((( (( e )->kante) /+;R/SC;yy+NT )->sta
degree++;;*/ if ((( c )->target) /*;degree++;;*/ && (w!=(( c )->target) /*;degree++;
;*/ ))  degree += gs_ide38 ((( c )->target) /*;};*/ ,v); if ((( c )->target2) /*;
e )->next) /+;R/SC;yy+NT ;;*/ && (w!=(( c )->target2) /*;e )->next) /+;
R/SC;yy+NT ;;*/ ))  degree += gs_ide38 ((( c )->target2) /*;};*/ ,v); /*;v )->connection) /+;R/SC;yy+NT ;
(degree);;*/  return(degree); }
#ifdef ANSI_C
static void gs_ide36 (GNODE v, GNODE w) 
#else
static void gs_ide36 (v, w) GNODE v; GNODE w; 
#endif
{ ADJEDGE e, en; CONNECT c; e = (( v )->succ) /*;_ide36 (v, w);*/ ; while (e) { /*;/N;D+ v;
; ;*/ en = (( e )->next) /*;; ;*/ ; if ((( ((( (( e )->kante) /*;{;*/ )->end) /*;
{;*/ ) /*;{;*/ )->tiefe) /*;{;*/ ==MAXINT) { revert_edge((( e )->kante) /*;
e, en;;*/ ); } e = en; } c = (( v )->connection) /*; e )->next) /+;
R/SC;yy+NT ;;*/ ; if (!c) return; if ((( c )->target) /*;ante) /+;R/SC;
yy+NT );;*/ && (w!=(( c )->target) /*;ante) /+;R/SC;yy+NT );;*/ ))  gs_ide36 ((( c )->target) /*;
};*/ ,v); if ((( c )->target2) /*;;*/ && (w!=(( c )->target2) /*;;*/ ))  /*;
};*/ gs_ide36 ((( c )->target2) /*;};*/ ,v); }
#ifdef ANSI_C
static void gs_ide2 (void)
#else
static void gs_ide2 ()
#endif
{ GNODE v, vl, vt; ADJEDGE edge, edgenext; ; v = nodelist; while (v) { /*;_ide2 ()
{;*/  (( v )->markiert) /*;_ide2 ();*/ = 0; v = (( v )->next) /*;_ide2 ();
*/ ; } v = dummylist; while (v) { (( v )->markiert) /*;, vl, vt;;*/ = 0; /*;, vl, vt;
edgenext;;*/  v = (( v )->next) /*;, vl, vt;;*/ ; } v = labellist; while (v) { (( v )->markiert) /*;
;;*/ = 0; v = (( v )->next) /*;;;*/ ; } maxdepth = 2*maxdepth; v = nodelist; /*; v )->markiert) /+;R/SC;yy+NT = 0; v = 
v = dummylist;;*/ while (v) { if (!(( v )->markiert) /*;v) { (( v )->markiert) /+;R/SC;
yy+NT = ;*/ ) { (( v )->tiefe) /*;v) { (( v )->markiert) /+;R/SC;yy+NT = ;
*/ = 2* (( v )->tiefe) /*;v) { (( v )->markiert) /+;R/SC;yy+NT = ;*/ ; /*;v) { (( v )->markiert) /+;R/SC;yy+NT = 
;*/  (( v )->markiert) /*;v) { (( v )->markiert) /+;R/SC;yy+NT = ;*/ = 1; /*;v) { (( v )->markiert) /+;R/SC;yy+NT = 
;*/  } else assert((0));; v = (( v )->next) /*;arkiert) /+;R/SC;yy+NT = 0;
v = (( v )-;*/ ; }  v = dummylist; while (v) { if (!(( v )->markiert) /*;
v )->markiert) /+;R/SC;yy+NT ) { (( v ;*/ ) { (( v )->tiefe) /*; v )->markiert) /+;
R/SC;yy+NT ) { (( v ;*/ = 2* (( v )->tiefe) /*; v )->markiert) /+;R/SC;
yy+NT ) { (( v ;*/ ; (( v )->markiert) /*; v )->markiert) /+;R/SC;yy+NT ) {
(( v ;*/ = 1; } else assert((0));; v = (( v )->next) /*;R/SC;yy+NT ;
;*/ ; }  v = labellist; while (v) { if (!(( v )->markiert) /*; v )->markiert) /+;
R/SC;yy+NT ) { (( v ;*/ ) { (( v )->tiefe) /*; v )->markiert) /+;R/SC;
yy+NT ) { (( v ;*/ = 2* (( v )->tiefe) /*; v )->markiert) /+;R/SC;yy+NT ) {
(( v ;*/ ; (( v )->markiert) /*; v )->markiert) /+;R/SC;yy+NT ) { (( v ;
*/ = 1; } else assert((0));; v = (( v )->next) /*;R/SC;yy+NT ;;*/ ; } /*;ellist;
while (v) {;*/   v = nodelist; while (v) { edge = (( v )->succ) /*; v )->markiert) /+;
R/SC;yy+NT ) { (( v ;*/ ;  while (edge) { edgenext = (( edge )->next) /*;
R/SC;yy+NT ;;*/ ; if ((( (( edge )->kante) /*;} ;*/ )->label) /*;} ;
*/ ) { vl = create_labelnode((( edge )->kante) /*;elist;;*/ ); vt = ((( (( edge )->kante) /*;
while (v) {;*/ )->end) /*;while (v) {;*/ ) /*;while (v) {;*/ ; (( vl )->tiefe) /*;
(( v )->succ) /+;R/SC;yy+NT ; ;*/ = ( (( ((( (( edge )->kante) /*;(( v )->succ) /+;
R/SC;yy+NT ; ;*/ )->start) /*;(( v )->succ) /+;R/SC;yy+NT ; ;*/ ) /*;
(( v )->succ) /+;R/SC;yy+NT ; ;*/ )->tiefe) /*;(( v )->succ) /+;R/SC;
yy+NT ; ;*/  +(( ((( (( edge )->kante) /*;;*/ )->end) /*;;*/ ) /*;;*/ )->tiefe) /*;
;*/ )/2; (void)gs_ide15 (v,vl,(( edge )->kante) /*;>next) /+;R/SC;yy+NT ;
;*/ ,0); (void)gs_ide15 (vl,vt,(( edge )->kante) /*;R/SC;yy+NT )->label) /+;
R/SC;yy+NT ) {;*/ ,1); delete_adjedge((( edge )->kante) /*;nte) /+;R/SC;
yy+NT );;*/ ); } edge = edgenext; } v = (( v )->next) /*; edge )->kante) /+;
R/SC;yy+NT ,0);;*/ ; }  v = tmpnodelist; while (v) { edge = (( v )->succ) /*;
edgenext;;*/ ;  while (edge) { edgenext = (( edge )->next) /*;v )->next) /+;
R/SC;yy+NT ;;*/ ; if ((( (( edge )->kante) /*;} ;*/ )->label) /*;} ;
*/ ) { vl = create_labelnode((( edge )->kante) /*;nodelist;;*/ ); vt = ((( (( edge )->kante) /*;
while (v) {;*/ )->end) /*;while (v) {;*/ ) /*;while (v) {;*/ ; (( vl )->tiefe) /*;
(( v )->succ) /+;R/SC;yy+NT ; ;*/ = ( (( ((( (( edge )->kante) /*;(( v )->succ) /+;
R/SC;yy+NT ; ;*/ )->start) /*;(( v )->succ) /+;R/SC;yy+NT ; ;*/ ) /*;
(( v )->succ) /+;R/SC;yy+NT ; ;*/ )->tiefe) /*;(( v )->succ) /+;R/SC;
yy+NT ; ;*/  +(( ((( (( edge )->kante) /*;;*/ )->end) /*;;*/ ) /*;;*/ )->tiefe) /*;
;*/ )/2; (void)gs_ide15 (v,vl,(( edge )->kante) /*;>next) /+;R/SC;yy+NT ;
;*/ ,0); (void)gs_ide15 (vl,vt,(( edge )->kante) /*;R/SC;yy+NT )->label) /+;
R/SC;yy+NT ) {;*/ ,1); delete_adjedge((( edge )->kante) /*;nte) /+;R/SC;
yy+NT );;*/ ); } edge = edgenext; } v = (( v )->next) /*; edge )->kante) /+;
R/SC;yy+NT ,0);;*/ ; }  }
#ifdef ANSI_C
static void gs_ide52 (void)
#else
static void gs_ide52 ()
#endif
{ GNODE v; int changed,count; ; count = 0; changed = 1; while (changed) { /*;{
;;*/ changed = 0; gs_wait_message('p'); if (G_timelimit>0)  if (test_timelimit(30)) { /*; 0;
changed = 1;;*/ gs_wait_message('t'); return;  } v = nodelist; while (v) { if (!(( v )->connection) /*;
)) {;*/ ) changed += gs_ide51 (v,0);  v = (( v )->next) /*;gs_wait_message('t');
;*/ ; }  v = labellist; while (v) { if (!(( v )->connection) /*;while (v) {
;*/ ) changed += gs_ide51 (v,1);  v = (( v )->next) /*; v )->connection) /+;
R/SC;yy+NT ) chang;*/ ; }  count++; if (count>=50) return; } } 
#ifdef ANSI_C
static int gs_ide51 (GNODE v,int lab)
#else
static int gs_ide51 (v, lab) GNODE v; int lab;
#endif
{  int nodelevel,leveldiff,nr_edges, nr_redges, changed, delta, hdelta; /*;} 
int gs_ide51 (/N;D+ v,int lab);*/ ADJEDGE edge, hedge; GNODE hh; ; if ((( v )->level) /*;;;*/ >=0) return(0); /*;;
{ ;*/ nr_redges = nr_edges = leveldiff = 0; nodelevel = (( v )->tiefe) /*;
elevel,leveldiff,nr_edges, nr_redges, c;*/ ; if ((!(( v )->succ) /*;
hedge;;*/ ) || (!(( v )->pred) /*;hedge;;*/ )) delta = 1; else delta = 0; /*;/N;D+ hh;
;;*/ edge = (( v )->pred) /*;;;*/ ; while (edge) { nr_edges += (( (( edge )->kante) /*;
_edges = leveldiff = 0;;*/ )->priority) /*;_edges = leveldiff = 0;;*/ ; /*;_edges = leveldiff = 0;
iefe) /+;R/SC;yy+NT ;;*/ nr_redges++; if ((( ((( (( edge )->kante) /*;yy+NT ) || (!(( v )->pred) /+;
R/SC;yy+N;*/ )->start) /*;yy+NT ) || (!(( v )->pred) /+;R/SC;yy+N;*/ ) /*;
yy+NT ) || (!(( v )->pred) /+;R/SC;yy+N;*/ )->tiefe) /*;yy+NT ) || (!(( v )->pred) /+;
R/SC;yy+N;*/ !=nodelevel) leveldiff += ((( (( edge )->kante) /*;else delta = 0;
;*/ )->priority) /*;else delta = 0;;*/ * ((( ((( (( edge )->kante) /*;
(( v )->pred) /+;R/SC;yy+NT ;;*/ )->start) /*;(( v )->pred) /+;R/SC;
yy+NT ;;*/ ) /*;(( v )->pred) /+;R/SC;yy+NT ;;*/ )->tiefe) /*;(( v )->pred) /+;
R/SC;yy+NT ;;*/ -nodelevel+delta)); edge = (( edge )->next) /*;;*/ ; /*;nr_redges++;
((( (( edge )->kante) /+;R/SC;yy+NT )->;*/  } edge = (( v )->succ) /*;nr_redges++;;*/ ; while (edge) { nr_edges += (( (( edge )->kante) /*;
(( (( edge )->kante) /+;R/SC;yy+NT )->p;*/ )->priority) /*;(( (( edge )->kante) /+;
R/SC;yy+NT )->p;*/ ; nr_redges++; if ((( ((( (( edge )->kante) /*;/SC;
yy+NT ;;*/ )->end) /*;/SC;yy+NT ;;*/ ) /*;/SC;yy+NT ;;*/ )->tiefe) /*;
/SC;yy+NT ;;*/ !=nodelevel) leveldiff += ((( (( edge )->kante) /*;};
*/ )->priority) /*;};*/ * ((( ((( (( edge )->kante) /*;(( v )->succ) /+;
R/SC;yy+NT ;;*/ )->end) /*;(( v )->succ) /+;R/SC;yy+NT ;;*/ ) /*;(( v )->succ) /+;
R/SC;yy+NT ;;*/ )->tiefe) /*;(( v )->succ) /+;R/SC;yy+NT ;;*/ -nodelevel-delta)); /*;(( v )->succ) /+;R/SC;yy+NT ;
;*/ edge = (( edge )->next) /*;;*/ ; } if (nr_redges==0) { (( v )->tiefe) /*;
((( (( edge )->kante) /+;R/SC;yy+NT )->;*/ = 0; return(0); } if (nr_edges==0) return(0); /*;/SC;yy+NT ;
};*/ changed = 0; if (leveldiff/nr_edges <= -2) { changed = 1; nodelevel += (leveldiff/nr_edges); /*;return(0);
};*/ } else if (leveldiff/nr_edges > 0) {  changed = 1; nodelevel += (leveldiff/nr_edges); /*;eldiff*nr_edges <= -2) {
changed = 1;;*/ }
#ifdef TUNEDEBUG
PRINTF("Wish %sto move \"%s\" from level %d to level %d\n", (changed? "" : "not "), ((( v )->title) /*;
};*/ ?(( v )->title) /*;};*/ :"(null)"), (( v )->tiefe) /*; (leveldiff*nr_edges > 0) {
;*/ , nodelevel);
#endif
if (!changed) return(0); if ((layout_flag == 3) || (layout_flag == 0)) { /*;el += (leveldiff*nr_edges);
};*/ if (near_edge_layout) delta = 0; else delta = 1; if (nodelevel > (( v )->tiefe) /*;
Wish %sto move z %sz  from level %d to;*/ ) { edge = (( v )->succ) /*;
not  ), ((( v )->title) /+;R/SC;yy+NT;*/ ; while (edge) { if ( ((( ((( (( edge )->kante) /*;
if (!changed) return(0);;*/ )->end) /*;if (!changed) return(0);;*/ ) /*;
if (!changed) return(0);;*/ )->tiefe) /*;if (!changed) return(0);;*/ >(( v )->tiefe) /*;
if (!changed) return(0);;*/ )  && (nodelevel>=(( ((( (( edge )->kante) /*;
yout_flag == 3) || (layout_flag == 0)) ;*/ )->end) /*;yout_flag == 3) || (layout_flag == 0)) ;
*/ ) /*;yout_flag == 3) || (layout_flag == 0)) ;*/ )->tiefe) /*;yout_flag == 3) || (layout_flag == 0)) ;
*/ )) nodelevel = (( ((( (( edge )->kante) /*;layout) delta = 0; else delta = 1;
;*/ )->end) /*;layout) delta = 0; else delta = 1;;*/ ) /*;layout) delta = 0;
else delta = 1;;*/ )->tiefe) /*;layout) delta = 0; else delta = 1;;
*/ -delta;  edge = (( edge )->next) /*;)->tiefe) /+;R/SC;yy+NT ) {;*/ ; /*;)->tiefe) /+;R/SC;yy+NT ) {
;yy+NT ;;*/ } edge = (( v )->pred) /*;while (edge) {;*/ ; while (edge) { if ( ((( ((( (( edge )->kante) /*;
=(( ((( (( edge )->kante) /+;R/SC;yy+NT;*/ )->start) /*;=(( ((( (( edge )->kante) /+;
R/SC;yy+NT;*/ ) /*;=(( ((( (( edge )->kante) /+;R/SC;yy+NT;*/ )->tiefe) /*;
=(( ((( (( edge )->kante) /+;R/SC;yy+NT;*/ >(( v )->tiefe) /*;=(( ((( (( edge )->kante) /+;
R/SC;yy+NT;*/ )  && (nodelevel>=(( ((( (( edge )->kante) /*; edge )->kante) /+;
R/SC;yy+NT )->end) /;*/ )->start) /*; edge )->kante) /+;R/SC;yy+NT )->end) /;
*/ ) /*; edge )->kante) /+;R/SC;yy+NT )->end) /;*/ )->tiefe) /*; edge )->kante) /+;
R/SC;yy+NT )->end) /;*/ )) nodelevel = (( ((( (( edge )->kante) /*;/SC;
yy+NT ;;*/ )->start) /*;/SC;yy+NT ;;*/ ) /*;/SC;yy+NT ;;*/ )->tiefe) /*;
/SC;yy+NT ;;*/ -delta;  edge = (( edge )->next) /*;};*/ ; } if (nodelevel <= (( v )->tiefe) /*;
;*/ ) return(0); } if (nodelevel < (( v )->tiefe) /*;e )->kante) /+;
R/SC;yy+NT )->start) /+;;*/ ) { edge = (( v )->succ) /*;) /+;R/SC;yy+NT )->start) /+;
R/SC;yy+NT;*/ ; while (edge) { if ( ((( ((( (( edge )->kante) /*;};*/ )->end) /*;
};*/ ) /*;};*/ )->tiefe) /*;};*/ <(( v )->tiefe) /*;};*/ )  && (nodelevel<=(( ((( (( edge )->kante) /*;
elevel <= (( v )->tiefe) /+;R/SC;yy+NT ;*/ )->end) /*;elevel <= (( v )->tiefe) /+;
R/SC;yy+NT ;*/ ) /*;elevel <= (( v )->tiefe) /+;R/SC;yy+NT ;*/ )->tiefe) /*;
elevel <= (( v )->tiefe) /+;R/SC;yy+NT ;*/ )) nodelevel = (( ((( (( edge )->kante) /*;
};*/ )->end) /*;};*/ ) /*;};*/ )->tiefe) /*;};*/ +delta;  edge = (( edge )->next) /*;
elevel < (( v )->tiefe) /+;R/SC;yy+NT );*/ ; } edge = (( v )->pred) /*;
while (edge) {;*/ ; while (edge) { if ( ((( ((( (( edge )->kante) /*;
=(( ((( (( edge )->kante) /+;R/SC;yy+NT;*/ )->start) /*;=(( ((( (( edge )->kante) /+;
R/SC;yy+NT;*/ ) /*;=(( ((( (( edge )->kante) /+;R/SC;yy+NT;*/ )->tiefe) /*;
=(( ((( (( edge )->kante) /+;R/SC;yy+NT;*/ <(( v )->tiefe) /*;=(( ((( (( edge )->kante) /+;
R/SC;yy+NT;*/ )  && (nodelevel<=(( ((( (( edge )->kante) /*; edge )->kante) /+;
R/SC;yy+NT )->end) /;*/ )->start) /*; edge )->kante) /+;R/SC;yy+NT )->end) /;
*/ ) /*; edge )->kante) /+;R/SC;yy+NT )->end) /;*/ )->tiefe) /*; edge )->kante) /+;
R/SC;yy+NT )->end) /;*/ )) nodelevel = (( ((( (( edge )->kante) /*;/SC;
yy+NT ;;*/ )->start) /*;/SC;yy+NT ;;*/ ) /*;/SC;yy+NT ;;*/ )->tiefe) /*;
/SC;yy+NT ;;*/ +delta;  edge = (( edge )->next) /*;};*/ ; } if (nodelevel >= (( v )->tiefe) /*;
;*/ ) return(0); } edge = (( v )->pred) /*;e )->kante) /+;R/SC;yy+NT )->start) /+;
;*/ ; while (edge) { if (((( (( edge )->kante) /*;ge = (( edge )->next) /+;
R/SC;yy+NT ;;*/ )->kantenart) /*;ge = (( edge )->next) /+;R/SC;yy+NT ;
;*/ ) /*;ge = (( edge )->next) /+;R/SC;yy+NT ;;*/ !='R') { if ( (nodelevel< (( ((( (( edge )->kante) /*;
};*/ )->start) /*;};*/ ) /*;};*/ )->tiefe) /*;};*/ )  &&((( v )->tiefe) /*;
elevel >= (( v )->tiefe) /+;R/SC;yy+NT ;*/ >=(( ((( (( edge )->kante) /*;
elevel >= (( v )->tiefe) /+;R/SC;yy+NT ;*/ )->start) /*;elevel >= (( v )->tiefe) /+;
R/SC;yy+NT ;*/ ) /*;elevel >= (( v )->tiefe) /+;R/SC;yy+NT ;*/ )->tiefe) /*;
elevel >= (( v )->tiefe) /+;R/SC;yy+NT ;*/ ) ) return(0); } edge = (( edge )->next) /*;
;*/ ; } edge = (( v )->succ) /*;dge )->kante) /+;R/SC;yy+NT )->start) /;
*/ ; while (edge) { if (((( (( edge )->kante) /*;turn(0);;*/ )->kantenart) /*;
turn(0);;*/ ) /*;turn(0);;*/ !='R') { if ( (nodelevel> (( ((( (( edge )->kante) /*;
};*/ )->end) /*;};*/ ) /*;};*/ )->tiefe) /*;};*/ )  &&((( v )->tiefe) /*;
(( edge )->next) /+;R/SC;yy+NT ;;*/ <=(( ((( (( edge )->kante) /*;(( edge )->next) /+;
R/SC;yy+NT ;;*/ )->end) /*;(( edge )->next) /+;R/SC;yy+NT ;;*/ ) /*;
(( edge )->next) /+;R/SC;yy+NT ;;*/ )->tiefe) /*;(( edge )->next) /+;
R/SC;yy+NT ;;*/ ) ) return(0); } edge = (( edge )->next) /*;;*/ ; } } /*;( ((( (( edge )->kante) /+;R/SC;yy+NT )
turn(0);;*/  else {  edge = (( v )->pred) /*;turn(0);;*/ ; while (edge) { if (nodelevel==(( ((( (( edge )->kante) /*;
(( edge )->next) /+;R/SC;yy+NT ;;*/ )->start) /*;(( edge )->next) /+;
R/SC;yy+NT ;;*/ ) /*;(( edge )->next) /+;R/SC;yy+NT ;;*/ )->tiefe) /*;
(( edge )->next) /+;R/SC;yy+NT ;;*/ ) return(0); edge = (( edge )->next) /*;
};*/ ; } edge = (( v )->succ) /*;;*/ ; while (edge) { if (nodelevel==(( ((( (( edge )->kante) /*;
while (edge) {;*/ )->end) /*;while (edge) {;*/ ) /*;while (edge) {;*/ )->tiefe) /*;
while (edge) {;*/ ) return(0); edge = (( edge )->next) /*;elevel==(( ((( (( edge )->kante) /+;
R/S;*/ ; } } delta = 0; edge = (( v )->pred) /*;;*/ ; while (edge) { /*;/SC;yy+NT ;
};*/  hh = ((( (( edge )->kante) /*;/SC;yy+NT ;;*/ )->start) /*;/SC;yy+NT ;
;*/ ) /*;/SC;yy+NT ;;*/ ; if (nodelevel==(( hh )->tiefe) /*;};*/ ) { /*;}
0;;*/  delta++; if ((( hh )->connection) /*; 0;;*/ ) return(0); hdelta = 0; /*;while (edge) {
( (( edge )->kante) /+;R/SC;yy+NT )->st;*/  hedge = (( hh )->pred) /*;while (edge) {;*/ ; while (hedge) { if ((( hh )->tiefe) /*;
=(( hh )->tiefe) /+;R/SC;yy+NT ) {;*/ ==(( ((( (( hedge )->kante) /*;
=(( hh )->tiefe) /+;R/SC;yy+NT ) {;*/ )->start) /*;=(( hh )->tiefe) /+;
R/SC;yy+NT ) {;*/ ) /*;=(( hh )->tiefe) /+;R/SC;yy+NT ) {;*/ )->tiefe) /*;
=(( hh )->tiefe) /+;R/SC;yy+NT ) {;*/ ) hdelta++; hedge = (( hedge )->next) /*;
delta++;;*/ ; } hedge = (( hh )->succ) /*;hdelta = 0;;*/ ; while (hedge) { /*; (( hh )->pred) /+;R/SC;yy+NT ;
{;*/ if ((( hh )->tiefe) /*;{;*/ ==(( ((( (( hedge )->kante) /*;{;*/ )->end) /*;
{;*/ ) /*;{;*/ )->tiefe) /*;{;*/ ) hdelta++; hedge = (( hedge )->next) /*;
+;R/SC;yy+NT ==(( ((( (( hedge )->kante;*/ ; } if (hdelta>1) return(0); /*;}
(( hh )->succ) /+;R/SC;yy+NT ;;*/ } edge = (( edge )->next) /*;{;*/ ; } edge = (( v )->succ) /*;;R/SC;
yy+NT ;;*/ ; while (edge) { hh = ((( (( edge )->kante) /*;lta>1) return(0);
;*/ )->end) /*;lta>1) return(0);;*/ ) /*;lta>1) return(0);;*/ ; if (nodelevel==(( hh )->tiefe) /*;
};*/ ) { delta++; if ((( hh )->connection) /*;};*/ ) return(0); hdelta = 0; /*;(( v )->succ) /+;R/SC;yy+NT ;
;*/ hedge = (( hh )->pred) /*;;*/ ; while (hedge) { if ((( hh )->tiefe) /*;
e) /+;R/SC;yy+NT ) {;*/ ==(( ((( (( hedge )->kante) /*;e) /+;R/SC;yy+NT ) {
;*/ )->start) /*;e) /+;R/SC;yy+NT ) {;*/ ) /*;e) /+;R/SC;yy+NT ) {;*/ )->tiefe) /*;
e) /+;R/SC;yy+NT ) {;*/ ) hdelta++; hedge = (( hedge )->next) /*;delta++;
;*/ ; } hedge = (( hh )->succ) /*;hdelta = 0;;*/ ; while (hedge) { if ((( hh )->tiefe) /*;
{;*/ ==(( ((( (( hedge )->kante) /*;{;*/ )->end) /*;{;*/ ) /*;{;*/ )->tiefe) /*;
{;*/ ) hdelta++; hedge = (( hedge )->next) /*;+;R/SC;yy+NT ==(( ((( (( hedge )->kante;
*/ ; } if (hdelta>1) return(0); } edge = (( edge )->next) /*;{;*/ ; } /*;;R/SC;yy+NT ;
};*/  if (delta>2) return(0); if (nodelevel<0) return(0); if (nodelevel>maxdepth) return(0); /*;lta>1) return(0);
};*/ 
#ifdef TUNEDEBUG
PRINTF("Move \"%s\" from level %d to level %d\n", ((( v )->title) /*;
(( edge )->next) /+;R/SC;yy+NT ;;*/ ?(( v )->title) /*;(( edge )->next) /+;
R/SC;yy+NT ;;*/ :"(null)"), (( v )->tiefe) /*;(( edge )->next) /+;R/SC;
yy+NT ;;*/ , nodelevel);
#endif
if ((( v )->tiefe) /*;};*/ !=nodelevel) changed = 1; (( v )->tiefe) /*;
ta>2) return(0);;*/ = nodelevel; return(changed); }
#ifdef ANSI_C
static void gs_ide13 (void)
#else
static void gs_ide13 ()
#endif
{ GNODE h; GNLIST hl; int t; ; h = nodelist; while (h) { t = (( h )->tiefe) /*;
;;*/ ; assert((t<=maxdepth)); hl = tmpnodelist_alloc(); (( hl )->next) /*;
;;*/ = (( layer[t] ).succlist) /*;;;*/ ; (( layer[t] ).succlist) /*;
elist;;*/ = hl; (( hl )->node) /*;while (h) {;*/ = h; h = (( h )->next) /*;
h )->tiefe) /+;R/SC;yy+NT ;;*/ ; } h = labellist; while (h) { t = (( h )->tiefe) /*;
NT = hl;;*/ ; assert((t<=maxdepth+1)); hl = tmpnodelist_alloc(); (( hl )->next) /*;
};*/ = (( layer[t] ).succlist) /*;};*/ ; (( layer[t] ).succlist) /*;
ellist;;*/ = hl; (( hl )->node) /*;while (h) {;*/ = h; h = (( h )->next) /*;
h )->tiefe) /+;R/SC;yy+NT ;;*/ ; } h = dummylist; while (h) { t = (( h )->tiefe) /*;
NT = hl;;*/ ; assert((t<=maxdepth+1)); hl = tmpnodelist_alloc(); (( hl )->next) /*;
};*/ = (( layer[t] ).succlist) /*;};*/ ; (( layer[t] ).succlist) /*;
mylist;;*/ = hl; (( hl )->node) /*;while (h) {;*/ = h; h = (( h )->next) /*;
h )->tiefe) /+;R/SC;yy+NT ;;*/ ; } }
#ifdef ANSI_C
static void gs_ide11 (void)
#else
static void gs_ide11 ()
#endif
{ int i; GNLIST n,hl; GNODE node; ADJEDGE edge; int backward_connection; /*;_ide11 ()
{;*/ int forward_connection; CONNECT c; ; maxindeg = maxoutdeg = 0; for (i=0; /*; edge;
onnection;;*/  i<=maxdepth+1; i++) { n = (( layer[i] ).succlist) /*;onnection;;*/ ; /*;n;
C;NN+CT c;;*/  while (n) { (( (( n )->node) /*;C;NN+CT c;;*/ )->markiert) /*;C;NN+CT c;
;*/ =0; n = (( n )->next) /*;;;*/ ; } n = (( layer[i] ).succlist) /*;
axdepth+1; i++) {;*/ ; assert(((( layer[i] ).predlist) /*;clist) /+;
R/SC;yy+NT ;;*/ ==NULL)); while (n) { node = (( n )->node) /*; )->node) /+;
R/SC;yy+NT )->markiert) /+;*/ ; edge = (( node )->succ) /*;xt) /+;R/SC;
yy+NT ;;*/ ; backward_connection = 0; forward_connection = 0; c = (( node )->connection) /*;
er[i] ).predlist) /+;R/SC;yy+NT ==NULL);*/ ; if (c) { if (backward_connection1(c)) /*;(( n )->node) /+;R/SC;yy+NT ;
)->succ) /+;R/SC;yy+NT ;;*/ backward_connection = 1; if (backward_connection2(c)) backward_connection = 1; /*;forward_connection = 0;
node )->connection) /+;R/SC;yy+NT ;;*/ if (forward_connection1(c)) forward_connection = 1; if (forward_connection2(c)) /*;kward_connection1(c))
ction = 1;;*/ forward_connection = 1; } if ( (forward_connection)&&(!backward_connection) /*;backward_connection = 1;
ward_connection1(c));*/ &&((( (( n )->node) /*;ward_connection1(c));*/ )->markiert) /*;ward_connection1(c));
*/ ==0))  gs_ide6 (node,node,NULL); if ( (!backward_connection)&&((( (( n )->node) /*;
n2(c));*/ )->markiert) /*;n2(c));*/ ==0)) { hl = tmpnodelist_alloc(); /*;}
orward_connection)&&(!backward_connecti;*/  (( hl )->next) /*;};*/ = (( layer[i] ).predlist) /*;};*/ ; (( layer[i] ).predlist) /*;
orward_connection)&&(!backward_connecti;*/ = hl; (( hl )->node) /*;node) /+;
R/SC;yy+NT )->markiert) /+;R/S;*/ = node; } edge = (( node )->succ) /*;
&((( (( n )->node) /+;R/SC;yy+NT )->mar;*/ ; while (edge) { (( node )->outdegree) /*;
->next) /+;R/SC;yy+NT = (( layer[i] ).p;*/ ++; assert(((( ((( (( edge )->kante) /*;
predlist) /+;R/SC;yy+NT = hl;;*/ )->end) /*;predlist) /+;R/SC;yy+NT = hl;
;*/ ) /*;predlist) /+;R/SC;yy+NT = hl;;*/ )->tiefe) /*;predlist) /+;
R/SC;yy+NT = hl;;*/ >=i)); edge = (( edge )->next) /*;C;yy+NT = node;
;*/ ; } edge = (( node )->pred) /*;(( node )->succ) /+;R/SC;yy+NT ;;
*/ ; while (edge) { (( node )->indegree) /*; /+;R/SC;yy+NT ++;;*/ ++; /*;nte) /+;R/SC;yy+NT )->end) /+;R/SC;yy+N
NT ;;*/  edge = (( edge )->next) /*;nte) /+;R/SC;yy+NT )->end) /+;R/SC;yy+N;
*/ ; } if ((( node )->outdegree) /*;};*/ > maxoutdeg) maxoutdeg = (( node )->outdegree) /*;
(( node )->pred) /+;R/SC;yy+NT ;;*/ ; if ((( node )->indegree) /*;;*/ > maxindeg) /*;
/+;R/SC;yy+NT ++;;*/ maxindeg = (( node )->indegree) /*;/+;R/SC;yy+NT ++;;*/ ; n = (( n )->next) /*;
/SC;yy+NT ;;*/ ; } } }
#ifdef ANSI_C
static void gs_ide6 (GNODE v,GNODE w, GNODE predw)
#else
static void gs_ide6 (v,w,predw) GNODE v; GNODE w; GNODE predw;
#endif
{ ADJEDGE edge; CONNECT c; ; if (v!=w) (( w )->markiert) /*;;;*/ =1; /*;/N;D+ predw;
{;*/  if (v==w) { (( w )->savesucc) /*;{;*/ = (( w )->succ) /*;{;*/ ; (( v )->savepred) /*;
edge;;*/ = (( v )->pred) /*; edge;;*/ ; } edge = (( w )->succ) /*;;
;*/ ; if (v==w) (( v )->succ) /*;w) (( w )->markiert) /+;R/SC;yy+NT =1;
;*/ = NULL; while (edge) { succedgealloc(v,(( edge )->kante) /*;>savesucc) /+;
R/SC;yy+NT = (( w )->succ;*/ ); ((( (( edge )->kante) /*;ed) /+;R/SC;
yy+NT = (( v )->pred) /+;R/;*/ )->start) /*;ed) /+;R/SC;yy+NT = (( v )->pred) /+;
R/;*/ ) /*;ed) /+;R/SC;yy+NT = (( v )->pred) /+;R/;*/ = v; edge = (( edge )->next) /*;
};*/ ; } edge = (( w )->pred) /*; )->succ) /+;R/SC;yy+NT = NULL;;*/ ; /*;while (edge) {
ealloc(v,(( edge )->kante) /+;R/SC;yy+N;*/  if (v==w) (( v )->pred) /*;while (edge) {;*/ = NULL; while (edge) { /*;>kante) /+;R/SC;yy+NT )->start) /+;R/SC
t) /+;R/SC;yy+NT ;;*/  prededgealloc(v,(( edge )->kante) /*;>kante) /+;R/SC;yy+NT )->start) /+;
R/SC;*/ ); ((( (( edge )->kante) /*;t) /+;R/SC;yy+NT ;;*/ )->end) /*;
t) /+;R/SC;yy+NT ;;*/ ) /*;t) /+;R/SC;yy+NT ;;*/ = v; edge = (( edge )->next) /*;
};*/ ; } c = (( w )->connection) /*; )->pred) /+;R/SC;yy+NT = NULL;;
*/ ; if (!c) return; if ((( c )->target) /*;ealloc(v,(( edge )->kante) /+;
R/SC;yy+N;*/ && ((( c )->target) /*;ealloc(v,(( edge )->kante) /+;R/SC;
yy+N;*/ !=predw))  gs_ide6 (v,(( c )->target) /*;>kante) /+;R/SC;yy+NT )->end) /+;
R/SC;y;*/ ,w); if ((( c )->target2) /*;t) /+;R/SC;yy+NT ;;*/ && ((( c )->target2) /*;
t) /+;R/SC;yy+NT ;;*/ !=predw))  gs_ide6 (v,(( c )->target2) /*;};*/ ,w); /*;}
w )->connection) /+;R/SC;yy+NT ;;*/ }
#ifdef ANSI_C
static void gs_ide32 (void)
#else
static void gs_ide32 ()
#endif
{ int i; GNLIST li; GNODE node; ADJEDGE edge,nextedge; GNODE d1, d2; /*;{
int i;;*/   ADJEDGE e1,e2,e3,e4;  GEDGE a1, a2; ; for (i=0; i<=maxdepth; i++) { /*; edge,nextedge;
;*/  li = (( layer[i] ).succlist) /*; edge,nextedge;;*/ ; while (li) { node = (( li )->node) /*;
;*/ ; edge = (( node )->succ) /*;/+D/+ a1, a2;;*/ ; while (edge) { assert((((( (( edge )->kante) /*;
0; i<=maxdepth; i++) {;*/ )->start) /*;0; i<=maxdepth; i++) {;*/ ) /*;
0; i<=maxdepth; i++) {;*/ ==node)); nextedge = (( edge )->next) /*;i] ).succlist) /+;
R/SC;yy+NT ;;*/ ; gs_ide10 (node,edge,i); edge = nextedge; } li = (( li )->next) /*;
while (edge) {;*/ ; } } node = labellist; while (node) { edge = (( node )->succ) /*;
};*/ ; if (edge && ((( edge )->next) /*; li )->next) /+;R/SC;yy+NT ;
;*/ )) { a1 = (( edge )->kante) /*;};*/ ; a2 = (( (( edge )->next) /*;
};*/ )->kante) /*;};*/ ; d1 = gs_ide14 ((( node )->tiefe) /*;labellist;
;*/ ); d2 = gs_ide14 ((( node )->tiefe) /*;;*/ ); e1 = gs_ide15 (node,d1,a1,0); /*;c) /+;R/SC;yy+NT ;
) /+;R/SC;yy+NT )) {;*/ e2 = gs_ide15 (d1,(( a1 )->end) /*;) /+;R/SC;yy+NT )) {;*/ ,a1,1); e3 = gs_ide15 (node,d2,a2,0); /*;T ;
= (( (( edge )->next) /+;R/SC;yy+NT )-;*/ e4 = gs_ide15 (d2,(( a2 )->end) /*; = (( (( edge )->next) /+;R/SC;yy+NT )-;
*/ ,a2,1); gs_ide10 (((( (( e1 )->kante) /*;de14 ((( node )->tiefe) /+;
R/SC;yy+NT );*/ )->start) /*;de14 ((( node )->tiefe) /+;R/SC;yy+NT );
*/ ) /*;de14 ((( node )->tiefe) /+;R/SC;yy+NT );*/ ,e1,(( node )->tiefe) /*;
de14 ((( node )->tiefe) /+;R/SC;yy+NT );*/ ); gs_ide10 (((( (( e2 )->kante) /*;
( node )->tiefe) /+;R/SC;yy+NT );;*/ )->start) /*;( node )->tiefe) /+;
R/SC;yy+NT );;*/ ) /*;( node )->tiefe) /+;R/SC;yy+NT );;*/ ,e2,(( node )->tiefe) /*;
( node )->tiefe) /+;R/SC;yy+NT );;*/ ); gs_ide10 (((( (( e3 )->kante) /*;
a1,0);;*/ )->start) /*;a1,0);;*/ ) /*;a1,0);;*/ ,e3,(( node )->tiefe) /*;
a1,0);;*/ ); gs_ide10 (((( (( e4 )->kante) /*;) /+;R/SC;yy+NT ,a1,1);
;*/ )->start) /*;) /+;R/SC;yy+NT ,a1,1);;*/ ) /*;) /+;R/SC;yy+NT ,a1,1);
;*/ ,e4,(( node )->tiefe) /*;) /+;R/SC;yy+NT ,a1,1);;*/ ); delete_adjedge(a1); /*;e3 = gs_ide15 (node,d2,a2,0);
_ide15 (d2,(( a2 )->end) /+;R/SC;yy+NT ;*/ delete_adjedge(a2); } edge = (( node )->pred) /*;->kante) /+;R/SC;yy+NT )->start) /+;
R/S;*/ ; if (edge && ((( edge )->next) /*;) /+;R/SC;yy+NT )->start) /+;
R/SC;yy+NT;*/ )) { a1 = (( edge )->kante) /*;SC;yy+NT )->start) /+;R/SC;
yy+NT ) /+;R;*/ ; a2 = (( (( edge )->next) /*;lete_adjedge(a1);;*/ )->kante) /*;
lete_adjedge(a1);;*/ ; d1 = gs_ide14 ((( node )->tiefe) /*;jedge(a2);
;*/ ); d2 = gs_ide14 ((( node )->tiefe) /*;};*/ ); e1 = gs_ide15 (d1,node,a1,1); /*;(( node )->pred) /+;R/SC;yy+NT ;
( edge )->next) /+;R/SC;yy+NT )) {;*/ e2 = gs_ide15 ((( a1 )->start) /*;( edge )->next) /+;R/SC;yy+NT )) {
;*/ ,d1,a1,0); e3 = gs_ide15 (d2,node,a2,1); e4 = gs_ide15 ((( a2 )->start) /*;
R/SC;yy+NT )->kante) /+;R/SC;yy+NT ;;*/ ,d2,a2,0); gs_ide10 (((( (( e1 )->kante) /*;
;R/SC;yy+NT );;*/ )->start) /*;;R/SC;yy+NT );;*/ ) /*;;R/SC;yy+NT );
;*/ ,e1,(( node )->tiefe) /*;;R/SC;yy+NT );;*/ ); gs_ide10 (((( (( e2 )->kante) /*;
= gs_ide14 ((( node )->tiefe) /+;R/SC;;*/ )->start) /*; = gs_ide14 ((( node )->tiefe) /+;
R/SC;;*/ ) /*; = gs_ide14 ((( node )->tiefe) /+;R/SC;;*/ ,e2,(( node )->tiefe) /*;
= gs_ide14 ((( node )->tiefe) /+;R/SC;;*/ -1); gs_ide10 (((( (( e3 )->kante) /*;
de15 (d1,node,a1,1);;*/ )->start) /*;de15 (d1,node,a1,1);;*/ ) /*;de15 (d1,node,a1,1);
;*/ ,e3,(( node )->tiefe) /*;de15 (d1,node,a1,1);;*/ ); gs_ide10 (((( (( e4 )->kante) /*;
( a1 )->start) /+;R/SC;yy+NT ,d1,a1,0);;*/ )->start) /*;( a1 )->start) /+;
R/SC;yy+NT ,d1,a1,0);;*/ ) /*;( a1 )->start) /+;R/SC;yy+NT ,d1,a1,0);
;*/ ,e4,(( node )->tiefe) /*;( a1 )->start) /+;R/SC;yy+NT ,d1,a1,0);
;*/ -1); delete_adjedge(a1); delete_adjedge(a2); } node = (( node )->next) /*;
de10 (((( (( e2 )->kante) /+;R/SC;yy+NT;*/ ; } }
#ifdef ANSI_C
static void gs_ide10 (GNODE node,ADJEDGE edge,int level)
#else
static void gs_ide10 (node,edge,level) GNODE node; ADJEDGE edge; int level; /*;}
};*/ 
#endif
{ int edgelen;  int i,j; GNODE d1, d2;  ADJEDGE e1,e2,e3;  CONNECT c1,c2; /*;int level;
{;*/ int connection_possible, lab_set; ; assert((node)); assert((edge)); assert(((( edge )->kante) /*;
e3; ;*/ )); assert(((( node )->tiefe) /*;C;NN+CT c1,c2;;*/ ==level)); /*;nection_possible, lab_set;
;;*/  assert((((( (( edge )->kante) /*;nection_possible, lab_set;;*/ )->start) /*;
nection_possible, lab_set;;*/ ) /*;nection_possible, lab_set;;*/ ==node)); /*;nection_possible, lab_set;
;;*/ edgelen = ((( (( (( edge )->kante) /*;;;*/ )->end) /*;;;*/ )->tiefe) /*;
;;*/ ) /*;;;*/ - level; if (edgelen < 0) {  e1 = revert_edge((( edge )->kante) /*;
;;*/ ); gs_ide10 (((( (( e1 )->kante) /*;nte) /+;R/SC;yy+NT ));;*/ )->start) /*;
nte) /+;R/SC;yy+NT ));;*/ ) /*;nte) /+;R/SC;yy+NT ));;*/ ,e1,(( ((( (( e1 )->kante) /*;
nte) /+;R/SC;yy+NT ));;*/ )->start) /*;nte) /+;R/SC;yy+NT ));;*/ ) /*;
nte) /+;R/SC;yy+NT ));;*/ )->tiefe) /*;nte) /+;R/SC;yy+NT ));;*/ ); } /*;SC;yy+NT )->start) /+;R/SC;yy+NT ) /+;R
gelen = ((( (( (( edge )->kante) /+;R/S;*/  else if (edgelen == 0) {  if (((( (( edge )->kante) /*;gelen = ((( (( (( edge )->kante) /+;
R/S;*/ )->kantenart) /*;gelen = ((( (( (( edge )->kante) /+;R/S;*/ ) /*;
gelen = ((( (( (( edge )->kante) /+;R/S;*/ =='R') { e1 = revert_edge((( edge )->kante) /*;
en < 0) { ;*/ ); gs_ide10 (((( (( e1 )->kante) /*;((( edge )->kante) /+;
R/SC;yy+NT );;*/ )->start) /*;((( edge )->kante) /+;R/SC;yy+NT );;*/ ) /*;
((( edge )->kante) /+;R/SC;yy+NT );;*/ ,e1,(( ((( (( e1 )->kante) /*;
((( edge )->kante) /+;R/SC;yy+NT );;*/ )->start) /*;((( edge )->kante) /+;
R/SC;yy+NT );;*/ ) /*;((( edge )->kante) /+;R/SC;yy+NT );;*/ )->tiefe) /*;
((( edge )->kante) /+;R/SC;yy+NT );;*/ ); } else if (((( (( edge )->kante) /*;
};*/ )->start) /*;};*/ ) /*;};*/ == ((( (( edge )->kante) /*;};*/ )->end) /*;
};*/ ) /*;};*/ ) {  assert((((( (( edge )->kante) /*; (edgelen == 0) {
;*/ )->end) /*; (edgelen == 0) { ;*/ ) /*; (edgelen == 0) { ;*/ ==node)); /*; (edgelen == 0) { 
e )->kante) /+;R/SC;yy+NT )->kantenart);*/ assert((level<=maxdepth)); d1 = gs_ide14 (level+1); d2 = gs_ide14 (level+1); /*;) /+;R/SC;yy+NT )->start) /+;R/SC;yy+NT
};*/ (( d1 )->nhorder) /*;};*/ = (( d2 )->nhorder) /*;};*/ = (( (( edge )->kante) /*;
};*/ )->horder) /*;};*/ ; e1 = gs_ide15 (node,d1,(( edge )->kante) /*;
(((( (( edge )->kante) /+;R/SC;yy+NT );*/ ,0); e2 = gs_ide15 (d1,d2, (( edge )->kante) /*;
edge )->kante) /+;R/SC;yy+NT )->end) /;*/ ,2); e3 = gs_ide15 (d2,node,(( edge )->kante) /*;
th));;*/ ,1); (( (( e2 )->kante) /*;d1 = gs_ide14 (level+1);;*/ )->label) /*;
d1 = gs_ide14 (level+1);;*/ = (( (( edge )->kante) /*;d1 = gs_ide14 (level+1);
;*/ )->label) /*;d1 = gs_ide14 (level+1);;*/ ; gs_ide10 (((( (( e2 )->kante) /*;
_ide14 (level+1);;*/ )->start) /*;_ide14 (level+1);;*/ ) /*;_ide14 (level+1);
;*/ ,e2,(( ((( (( e2 )->kante) /*;_ide14 (level+1);;*/ )->start) /*;
_ide14 (level+1);;*/ ) /*;_ide14 (level+1);;*/ )->tiefe) /*;_ide14 (level+1);
;*/ ); gs_ide10 (((( (( e3 )->kante) /*;er) /+;R/SC;yy+NT = (( d2 )->nhorder) /;
*/ )->start) /*;er) /+;R/SC;yy+NT = (( d2 )->nhorder) /;*/ ) /*;er) /+;
R/SC;yy+NT = (( d2 )->nhorder) /;*/ ,e3,(( ((( (( e3 )->kante) /*;er) /+;
R/SC;yy+NT = (( d2 )->nhorder) /;*/ )->start) /*;er) /+;R/SC;yy+NT = (( d2 )->nhorder) /;
*/ ) /*;er) /+;R/SC;yy+NT = (( d2 )->nhorder) /;*/ )->tiefe) /*;er) /+;
R/SC;yy+NT = (( d2 )->nhorder) /;*/ ); delete_adjedge((( edge )->kante) /*;
1,(( edge )->kante) /+;R/SC;yy+NT ,0);;*/ ); } else {  c1 = (( node )->connection) /*;
(( e2 )->kante) /+;R/SC;yy+NT )->label;*/ ; c2 = (( ((( (( edge )->kante) /*;
(((( (( e2 )->kante) /+;R/SC;yy+NT )->s;*/ )->end) /*;(((( (( e2 )->kante) /+;
R/SC;yy+NT )->s;*/ ) /*;(((( (( e2 )->kante) /+;R/SC;yy+NT )->s;*/ )->connection) /*;
(((( (( e2 )->kante) /+;R/SC;yy+NT )->s;*/ ; connection_possible = 1; /*;)->kante) /+;R/SC;yy+NT );
};*/  if ((c1) && ((( c1 )->target) /*;)->kante) /+;R/SC;yy+NT );;*/ ) && ((( c1 )->target2) /*;
)->kante) /+;R/SC;yy+NT );;*/ ))  connection_possible = 0; if ((c2) && ((( c2 )->target) /*;
;*/ ) && ((( c2 )->target2) /*;;*/ ))  connection_possible = 0; if (gs_ide8 (((( (( edge )->kante) /*;
->kante) /+;R/SC;yy+NT )->end) /+;R/SC;;*/ )->end) /*;->kante) /+;R/SC;
yy+NT )->end) /+;R/SC;;*/ ) /*;->kante) /+;R/SC;yy+NT )->end) /+;R/SC;
;*/ ,NULL, ((( (( edge )->kante) /*;connection_possible = 1;;*/ )->start) /*;
connection_possible = 1;;*/ ) /*;connection_possible = 1;;*/ ))  connection_possible = 0; /*;) && ((( c1 )->target) /+;R/SC;yy+NT ) 
sible = 0;;*/ if (connection_possible) { if (!c1) { c1 = connectalloc(node); (( c1 )->target) /*;
ide8 (((( (( edge )->kante) /+;R/SC;yy+;*/ = ((( (( edge )->kante) /*;
ide8 (((( (( edge )->kante) /+;R/SC;yy+;*/ )->end) /*;ide8 (((( (( edge )->kante) /+;
R/SC;yy+;*/ ) /*;ide8 (((( (( edge )->kante) /+;R/SC;yy+;*/ ; (( c1 )->edge) /*;
>kante) /+;R/SC;yy+NT )->start) /+;R/SC;*/ = (( edge )->kante) /*;>kante) /+;
R/SC;yy+NT )->start) /+;R/SC;*/ ; } else if (!(( c1 )->target2) /*;if (connection_possible) {
;*/ ) { (( c1 )->target2) /*;) {;*/ = ((( (( edge )->kante) /*;) {;*/ )->end) /*;
) {;*/ ) /*;) {;*/ ; (( c1 )->edge2) /*;loc(node);;*/ = (( edge )->kante) /*;
loc(node);;*/ ; } if (!c2) { c2 = connectalloc(((( (( edge )->kante) /*;
};*/ )->end) /*;};*/ ) /*;};*/ ); (( c2 )->target) /*; (!(( c1 )->target2) /+;
R/SC;yy+NT ) {;*/ = node; (( c2 )->edge) /*;t2) /+;R/SC;yy+NT = ((( (( edge )->kant;
*/ = (( edge )->kante) /*;t2) /+;R/SC;yy+NT = ((( (( edge )->kant;*/ ; /*;SC;yy+NT = (( edge )->kante) /+;R/SC;yy
};*/  } else if (!(( c2 )->target2) /*;};*/ ) { (( c2 )->target2) /*;) {;
*/ = node; (( c2 )->edge2) /*;loc(((( (( edge )->kante) /+;R/SC;yy+NT;
*/ = (( edge )->kante) /*;loc(((( (( edge )->kante) /+;R/SC;yy+NT;*/ ; /*;/SC;yy+NT = node;
= (( edge )->kante) /+;R/SC;yy+NT ;;*/  } delete_adjedge((( edge )->kante) /*; = (( edge )->kante) /+;R/SC;
yy+NT ;;*/ ); (( (( edge )->kante) /*;};*/ )->invisible) /*;};*/ = 0; /*; (!(( c2 )->target2) /+;R/SC;yy+NT ) {
t2) /+;R/SC;yy+NT = node;;*/  } else { if (level<=maxdepth)  d1 = gs_ide14 (level+1); else if (level>0)  /*;adjedge((( edge )->kante) /+;R/SC;yy+NT
kante) /+;R/SC;yy+NT )->invisible) /+;R;*/ d1 = gs_ide14 (level-1); else { assert((0)); } (( d1 )->nhorder) /*;
else {;*/ = (( (( edge )->kante) /*;else {;*/ )->horder) /*;else {;*/ ; /*;else {
el<=maxdepth) ;*/ e1 = gs_ide15 (node,d1,(( edge )->kante) /*;el<=maxdepth) ;*/ ,0); e2 = gs_ide15 (d1,((( (( edge )->kante) /*;
(level+1);;*/ )->end) /*;(level+1);;*/ ) /*;(level+1);;*/ ,(( edge )->kante) /*;
(level+1);;*/ ,1); (( (( e2 )->kante) /*;else if (level>0) ;*/ )->label) /*;
else if (level>0) ;*/ = (( (( edge )->kante) /*;else if (level>0) ;*/ )->label) /*;
else if (level>0) ;*/ ; gs_ide10 (((( (( e1 )->kante) /*;_ide14 (level-1);
;*/ )->start) /*;_ide14 (level-1);;*/ ) /*;_ide14 (level-1);;*/ ,e1,(( ((( (( e1 )->kante) /*;
_ide14 (level-1);;*/ )->start) /*;_ide14 (level-1);;*/ ) /*;_ide14 (level-1);
;*/ )->tiefe) /*;_ide14 (level-1);;*/ ); gs_ide10 (((( (( e2 )->kante) /*;
(0)); };*/ )->start) /*;(0)); };*/ ) /*;(0)); };*/ ,e2,(( ((( (( e2 )->kante) /*;
(0)); };*/ )->start) /*;(0)); };*/ ) /*;(0)); };*/ )->tiefe) /*;(0));
};*/ ); delete_adjedge((( edge )->kante) /*;R/SC;yy+NT = (( (( edge )->kante) /+;
R/;*/ ); } } } else if (edgelen == 1) {  } else if (edgelen > 1) {  d1 = node; /*;}
};*/ j = lab_set = 0; for (i=1; i<edgelen; i++) { d2 = gs_ide14 (level+i); /*;}
(edgelen > 1) { ;*/  (( d2 )->nhorder) /*;};*/ = (( (( edge )->kante) /*;};*/ )->horder) /*;
};*/ ; e1 = gs_ide15 (d1,d2,(( edge )->kante) /*; (edgelen > 1) { ;*/ ,j); /*; (edgelen > 1) { 
d1 = node;;*/ if (i==(edgelen+1)/2) { (( (( e1 )->kante) /*;_set = 0;;*/ )->label) /*;
_set = 0;;*/ = (( (( edge )->kante) /*;_set = 0;;*/ )->label) /*;_set = 0;
;*/ ; lab_set = 1; } d1 = d2; j = 2; } e1 = gs_ide15 (d1,((( (( edge )->kante) /*;
)->kante) /+;R/SC;yy+NT )->label) /+;R/;*/ )->end) /*;)->kante) /+;R/SC;
yy+NT )->label) /+;R/;*/ ) /*;)->kante) /+;R/SC;yy+NT )->label) /+;R/;
*/ ,(( edge )->kante) /*;)->kante) /+;R/SC;yy+NT )->label) /+;R/;*/ ,1); /*;)->kante) /+;R/SC;yy+NT )->label) /+;R/
lab_set = 1;;*/ if (!lab_set) (( (( e1 )->kante) /*;lab_set = 1;;*/ )->label) /*;lab_set = 1;
;*/ = (( (( edge )->kante) /*;lab_set = 1;;*/ )->label) /*;lab_set = 1;
;*/ ; delete_adjedge((( edge )->kante) /*;};*/ ); } }
#ifdef ANSI_C
ADJEDGE revert_edge(GEDGE edge)
#else
ADJEDGE revert_edge(edge) GEDGE edge;
#endif
{ GNODE h; char hh; ; delete_adjedge(edge); h = (( edge )->start) /*;
/+D/+ edge;;*/ ;  (( edge )->start) /*;{;*/ = (( edge )->end) /*;{;*/ ; /*;{
;;*/ (( edge )->end) /*;;;*/ = h; if ((( edge )->kantenart) /*;char hh;;*/ == 'R') (( edge )->kantenart) /*;
char hh;;*/ = 'U'; else if ((( edge )->kantenart) /*;;;*/ == 'S') (( edge )->kantenart) /*;
;;*/ = 'S'; else (( edge )->kantenart) /*;adjedge(edge);;*/ = 'R'; hh = (( edge )->arrowsize1) /*;
>start) /+;R/SC;yy+NT ; ;*/ ; (( edge )->arrowsize1) /*;R/SC;yy+NT = (( edge )->end) /+;
R/SC;yy;*/ = (( edge )->arrowsize2) /*;R/SC;yy+NT = (( edge )->end) /+;
R/SC;yy;*/ ; (( edge )->arrowsize2) /*;T = h;;*/ = hh; hh = (( edge )->arrowcolor1) /*;
y+NT == 'R') (( edge )->kantenart) /+;R;*/ ; (( edge )->arrowcolor1) /*;
se if ((( edge )->kantenart) /+;R/SC;yy;*/ = (( edge )->arrowcolor2) /*;
se if ((( edge )->kantenart) /+;R/SC;yy;*/ ; (( edge )->arrowcolor2) /*;
dge )->kantenart) /+;R/SC;yy+NT = 'R';;*/ = hh; hh = (( edge )->arrowstyle1) /*;
arrowsize1) /+;R/SC;yy+NT ;;*/ ; (( edge )->arrowstyle1) /*;/+;R/SC;
yy+NT = (( edge )->arrowsize2) ;*/ = (( edge )->arrowstyle2) /*;/+;R/SC;
yy+NT = (( edge )->arrowsize2) ;*/ ; (( edge )->arrowstyle2) /*;;yy+NT = hh;
;*/ = hh; create_adjedge(edge); return((( (( edge )->start) /*;dge )->arrowcolor1) /+;
R/SC;yy+NT = (( ;*/ )->succ) /*;dge )->arrowcolor1) /+;R/SC;yy+NT = (( ;
*/ ); }
#ifdef ANSI_C
static ADJEDGE gs_ide15 (GNODE start,GNODE end,GEDGE edge,int arrow)
#else
static ADJEDGE gs_ide15 (start, end, edge,arrow) GNODE start; GNODE end; /*;create_adjedge(edge);
(( (( edge )->start) /+;R/SC;yy+NT )->s;*/ GEDGE edge; int arrow;
#endif
{ GEDGE h; h = tmpedgealloc( (( edge )->linestyle) /*;nd;;*/ , (( edge )->thickness) /*;
/+D/+ edge;;*/ , (( edge )->eclass) /*;ow;;*/ , (( edge )->priority) /*;
{;*/ , (( edge )->color) /*;;;*/ , (( edge )->labelcolor) /*;oc(;*/ , (( edge )->arrowsize1) /*;
/+;R/SC;yy+NT ,;*/ , (( edge )->arrowsize2) /*;C;yy+NT ,;*/ , (( edge )->arrowstyle1) /*;
(( edge )->eclass) /+;R/SC;yy+NT ,;*/ , (( edge )->arrowstyle2) /*; )->priority) /+;
R/SC;yy+NT ,;*/ , (( edge )->arrowcolor1) /*;or) /+;R/SC;yy+NT ,;*/ , (( edge )->arrowcolor2) /*;
) /+;R/SC;yy+NT ,;*/ , (( edge )->horder) /*;SC;yy+NT ,;*/ ); (( h )->label) /*;
T ,;*/ = (( edge )->label) /*;T ,;*/ ; (( h )->anchor) /*; edge )->arrowstyle1) /+;
R/SC;yy+NT ,;*/ = (( edge )->anchor) /*; edge )->arrowstyle1) /+;R/SC;
yy+NT ,;*/ ; (( h )->start) /*;->arrowstyle2) /+;R/SC;yy+NT ,;*/ = start; /*;->arrowstyle2) /+;R/SC;yy+NT ,
color1) /+;R/SC;yy+NT ,;*/ (( h )->end) /*;color1) /+;R/SC;yy+NT ,;*/ = end; switch (arrow) { case 0: (( h )->arrowstyle1) /*;
NT );;*/ = 0 /*;NT );;*/ ; (( h )->arrowsize1) /*;e )->label) /+;R/SC;
yy+NT ;;*/ = 0; (( h )->label) /*; )->anchor) /+;R/SC;yy+NT = (( edge )->;
*/ = NULL; break; case 1: (( h )->arrowstyle2) /*;SC;yy+NT = end;;*/ = 0 /*;
SC;yy+NT = end;;*/ ; (( h )->arrowsize2) /*;switch (arrow) {;*/ = 0; /*; (( h )->arrowstyle1) /+;R/SC;yy+NT = 0
ize1) /+;R/SC;yy+NT = 0;;*/  (( h )->label) /*; (( h )->arrowstyle1) /+;R/SC;yy+NT = 0;*/ = NULL; /*;ize1) /+;R/SC;yy+NT = 0;
C;yy+NT = NULL;;*/  break; case 2: (( h )->arrowstyle1) /*;C;yy+NT = NULL;;*/ = 0 /*;C;
yy+NT = NULL;;*/ ; (( h )->arrowsize1) /*;break;;*/ = 0; (( h )->label) /*;
(( h )->arrowstyle2) /+;R/SC;yy+NT = 0;*/ = NULL; (( h )->arrowstyle2) /*;
ize2) /+;R/SC;yy+NT = 0;;*/ = 0 /*;ize2) /+;R/SC;yy+NT = 0;;*/ ; (( h )->arrowsize2) /*;
C;yy+NT = NULL;;*/ = 0; (( h )->label) /*;break;;*/ = NULL; break; } /*;C;yy+NT = NULL;
;yy+NT = 0 /+;R/SC;yy+NT ;;*/  if ((( edge )->kantenart) /*;C;yy+NT = NULL;;*/ =='S') (( h )->kantenart) /*;
C;yy+NT = NULL;;*/ = 'U'; else (( h )->kantenart) /*;;yy+NT = 0 /+;R/SC;
yy+NT ;;*/ = (( edge )->kantenart) /*;;yy+NT = 0 /+;R/SC;yy+NT ;;*/ ; /*; 0;
h )->label) /+;R/SC;yy+NT = NULL;;*/  if (start==end) (( h )->kantenart) /*; 0;;*/ = 'S'; create_adjedge(h); /*; h )->label) /+;R/SC;yy+NT = NULL;
break;;*/ return((( (( h )->start) /*;break;;*/ )->succ) /*;break;;*/ ); }
#ifdef ANSI_C
static GNODE gs_ide14 (int t)
#else
static GNODE gs_ide14 (t) int t;
#endif
{ GNLIST hl; GNODE v; ; assert((t<=maxdepth+1)); v = tmpnodealloc(0 /*;
int t;;*/ ,-1,-1,0,-1,G_color,G_color,G_color,1,1,-1); (( v )->title) /*;
{;*/ = ""; (( v )->label) /*;hl;;*/ = ""; (( v )->tiefe) /*;/N;D+ v;
;*/ = t; (( v )->nhorder) /*;;;*/ = -1; (( v )->before) /*;(t<=maxdepth+1));
;*/ = NULL; (( v )->next) /*;oc(0 /+;R/SC;yy+NT ,-1,-1,0,-1,/_color,;
*/ = dummylist; if (dummylist) (( dummylist )->before) /*;C;yy+NT =   ;
;*/ = v; dummylist = v; dummyanz++; if (t<0) return(v); hl = tmpnodelist_alloc(); /*;) /+;R/SC;yy+NT = NULL;
;yy+NT = dummylist;;*/ (( hl )->next) /*;;yy+NT = dummylist;;*/ = (( layer[t] ).succlist) /*;
;yy+NT = dummylist;;*/ ; (( layer[t] ).succlist) /*;)->before) /+;R/SC;
yy+NT = v;;*/ = hl; (( hl )->node) /*;dummylist = v;;*/ = v; return(v); /*;z++;
n(v);;*/ }
#ifdef ANSI_C
static void gs_ide31 (void)
#else
static void gs_ide31 ()
#endif
{ int i; GNLIST li; GNODE node; ADJEDGE edge,nextedge; ; for (i=0; i<=maxdepth; /*;{
int i;;*/  i++) { li = (( layer[i] ).succlist) /*;int i;;*/ ; while (li) { node = (( li )->node) /*;
/N;D+ node;;*/ ; edge = (( node )->succ) /*; edge,nextedge;;*/ ; while (edge) { /*;;
0; i<=maxdepth; i++) {;*/ assert((((( (( edge )->kante) /*;0; i<=maxdepth; i++) {;*/ )->start) /*;
0; i<=maxdepth; i++) {;*/ ) /*;0; i<=maxdepth; i++) {;*/ ==node)); nextedge = (( edge )->next) /*;
i] ).succlist) /+;R/SC;yy+NT ;;*/ ; gs_ide9 (edge); edge = nextedge; /*;while (edge) {
(((( (( edge )->kante) /+;R/SC;yy+NT )-;*/  } li = (( li )->next) /*;while (edge) {;*/ ; } } }
#ifdef ANSI_C
static void gs_ide9 (ADJEDGE edge)
#else
static void gs_ide9 (edge) ADJEDGE edge;
#endif
{ ADJEDGE l, lnext; GNODE d1;  ADJEDGE e1;  GEDGE f1, f2; int ide, aside1, aside2, tide; /*;ADJ+D/+ edge;
{;*/ ; f1 = (( edge )->kante) /*; l, lnext;;*/ ; l = (( ((( (( edge )->kante) /*;
/N;D+ d1; ;*/ )->start) /*;/N;D+ d1; ;*/ ) /*;/N;D+ d1; ;*/ )->succ) /*;
/N;D+ d1; ;*/ ; while (l) { lnext = (( l )->next) /*;/+D/+ f1, f2;;*/ ; /*;/+D/+ f1, f2;
, aside1, aside2, tide;;*/ f2 = (( l )->kante) /*;, aside1, aside2, tide;;*/ ; if (f1!=f2) { tide = ide = aside1 = aside2 = 1; /*;;
edge )->kante) /+;R/SC;yy+NT ;;*/  } else { tide = ide = aside1 = aside2 = 0; } if ((( f1 )->start) /*;
edge )->kante) /+;R/SC;yy+NT )->start) ;*/ != (( f2 )->start) /*;edge )->kante) /+;
R/SC;yy+NT )->start) ;*/ ) tide=0; if ((( f1 )->end) /*;while (l) {;
*/ != (( f2 )->end) /*;while (l) {;*/ ) tide=0; if ((( f1 )->linestyle) /*;
(( l )->next) /+;R/SC;yy+NT ;;*/ != (( f2 )->linestyle) /*; (( l )->next) /+;
R/SC;yy+NT ;;*/ ) ide=0; if ((( f1 )->thickness) /*;ante) /+;R/SC;yy+NT ;
;*/ > (( f2 )->thickness) /*;ante) /+;R/SC;yy+NT ;;*/ ) ide=0; if ((( f1 )->priority) /*;
ide = aside1 = aside2 = 1; };*/ > (( f2 )->priority) /*;ide = aside1 = aside2 = 1;
};*/ ) ide=0; if ((( f1 )->horder) /*; aside2 = 0; };*/ != (( f2 )->horder) /*;
aside2 = 0; };*/ ) ide=0; if ((( f1 )->eclass) /*;= (( f2 )->start) /+;
R/SC;yy+NT ) tide=;*/ != (( f2 )->eclass) /*;= (( f2 )->start) /+;R/SC;
yy+NT ) tide=;*/ ) ide=0; if ((( f1 )->color) /*; ((( f1 )->end) /+;
R/SC;yy+NT != (( f2 ;*/ != (( f2 )->color) /*; ((( f1 )->end) /+;R/SC;
yy+NT != (( f2 ;*/ ) ide=0; if ((( f1 )->arrowsize1) /*; )->linestyle) /+;
R/SC;yy+NT != (( f2 );*/ != (( f2 )->arrowsize1) /*; )->linestyle) /+;
R/SC;yy+NT != (( f2 );*/ ) aside1=0; if ((( f1 )->arrowsize2) /*;ckness) /+;
R/SC;yy+NT > (( f2 )->thickn;*/ != (( f2 )->arrowsize2) /*;ckness) /+;
R/SC;yy+NT > (( f2 )->thickn;*/ ) aside2=0; if ((( f1 )->arrowstyle1) /*;
/+;R/SC;yy+NT > (( f2 )->priority) /+;R;*/ != (( f2 )->arrowstyle1) /*;
/+;R/SC;yy+NT > (( f2 )->priority) /+;R;*/ ) aside1=0; if ((( f1 )->arrowstyle2) /*;
y+NT != (( f2 )->horder) /+;R/SC;yy+NT ;*/ != (( f2 )->arrowstyle2) /*;
y+NT != (( f2 )->horder) /+;R/SC;yy+NT ;*/ ) aside2=0; if ((( f1 )->arrowcolor1) /*;
(( f2 )->eclass) /+;R/SC;yy+NT ) ide=0;*/ != (( f2 )->arrowcolor1) /*;
(( f2 )->eclass) /+;R/SC;yy+NT ) ide=0;*/ ) aside1=0; if ((( f1 )->arrowcolor2) /*;
(( f1 )->color) /+;R/SC;yy+NT != (( f2 ;*/ != (( f2 )->arrowcolor2) /*;
(( f1 )->color) /+;R/SC;yy+NT != (( f2 ;*/ ) aside2=0; if ((( f1 )->anchor) /*;
->arrowsize1) /+;R/SC;yy+NT != (( f2 )-;*/ != (( f2 )->anchor) /*;->arrowsize1) /+;
R/SC;yy+NT != (( f2 )-;*/ ) ide=0; if (tide && ide && aside1&&aside2 && summarize_double_edges) { /*;size2) /+;R/SC;yy+NT != (( f2 )->arrows
/+;R/SC;yy+NT != (( f2 )->arrowstyle1);*/   delete_adjedge(f1);  return;  } if (tide) { d1 = gs_ide14 ((( ((( (( l )->kante) /*;
anchor) /+;R/SC;yy+NT != (( f2 )->ancho;*/ )->end) /*;anchor) /+;R/SC;
yy+NT != (( f2 )->ancho;*/ ) /*;anchor) /+;R/SC;yy+NT != (( f2 )->ancho;
*/ )->tiefe) /*;anchor) /+;R/SC;yy+NT != (( f2 )->ancho;*/ ); (( d1 )->nhorder) /*;
side1&&aside2 && summarize_double_edges;*/ = (( f1 )->horder) /*;side1&&aside2 && summarize_double_edges;
*/ ; e1 = gs_ide15 (((( (( edge )->kante) /*;delete_adjedge(f1); ;*/ )->start) /*;
delete_adjedge(f1); ;*/ ) /*;delete_adjedge(f1); ;*/ ,d1,f1,0); gs_ide10 (((( (( e1 )->kante) /*;
;*/ )->start) /*; ;*/ ) /*; ;*/ ,e1,(( ((( (( e1 )->kante) /*; ;*/ )->start) /*;
;*/ ) /*; ;*/ )->tiefe) /*; ;*/ ); e1 = gs_ide15 (d1,((( (( edge )->kante) /*;
};*/ )->end) /*;};*/ ) /*;};*/ ,(( edge )->kante) /*;};*/ ,1); (( (( e1 )->kante) /*;
e) {;*/ )->label) /*;e) {;*/ = (( f1 )->label) /*;e) {;*/ ; gs_ide10 (((( (( e1 )->kante) /*;
((( ((( (( l )->kante) /+;R/SC;yy+NT )-;*/ )->start) /*;((( ((( (( l )->kante) /+;
R/SC;yy+NT )-;*/ ) /*;((( ((( (( l )->kante) /+;R/SC;yy+NT )-;*/ ,e1,(( ((( (( e1 )->kante) /*;
((( ((( (( l )->kante) /+;R/SC;yy+NT )-;*/ )->start) /*;((( ((( (( l )->kante) /+;
R/SC;yy+NT )-;*/ ) /*;((( ((( (( l )->kante) /+;R/SC;yy+NT )-;*/ )->tiefe) /*;
((( ((( (( l )->kante) /+;R/SC;yy+NT )-;*/ ); delete_adjedge(f1);  return; /*;->kante) /+;R/SC;yy+NT )->start) /+;R/S
SC;yy+NT )->start) /+;R/SC;yy+NT ) /+;R;*/   } l = lnext; } } int number_reversions;
#ifdef ANSI_C
void calc_number_reversions(void)
#else
void calc_number_reversions()
#endif
{ GNODE v; ADJEDGE e; ; number_reversions = 0; v = nodelist; while (v) { /*;{
;;*/ e = (( v )->pred) /*;;;*/ ; while (e) { if (((( (( e )->kante) /*;;;
*/ )->kantenart) /*;;;*/ ) /*;;;*/ =='R') number_reversions++; e = (( e )->next) /*;
reversions = 0;;*/ ; } v = (( v )->next) /*;v) {;*/ ; } v = labellist; /*; (( e )->kante) /+;R/SC;yy+NT )->kanten
xt) /+;R/SC;yy+NT ;;*/  while (v) { e = (( v )->pred) /*;xt) /+;R/SC;yy+NT ;;*/ ; while (e) { /*;v )->next) /+;R/SC;yy+NT ;
};*/  if (((( (( e )->kante) /*;v )->next) /+;R/SC;yy+NT ;;*/ )->kantenart) /*;
v )->next) /+;R/SC;yy+NT ;;*/ ) /*;v )->next) /+;R/SC;yy+NT ;;*/ =='R') number_reversions++; /*;v )->next) /+;R/SC;yy+NT ;
};*/ e = (( e )->next) /*;};*/ ; } v = (( v )->next) /*;while (v) {;*/ ; } /*;while (e) {
(( e )->kante) /+;R/SC;yy+NT )->kanten;*/  v = dummylist; while (v) { e = (( v )->pred) /*;xt) /+;R/SC;yy+NT ;
;*/ ; while (e) { if (((( (( e )->kante) /*;v )->next) /+;R/SC;yy+NT ;
;*/ )->kantenart) /*;v )->next) /+;R/SC;yy+NT ;;*/ ) /*;v )->next) /+;
R/SC;yy+NT ;;*/ =='R') number_reversions++; e = (( e )->next) /*;};*/ ; /*;}
mylist;;*/ } v = (( v )->next) /*;while (v) {;*/ ; } }
#ifdef DEBUG
#ifdef ANSI_C
void db_output_graph(void)
#else
void db_output_graph()
#endif
{ PRINTF("Nodes:\n"); gs_ide18 (nodelist); PRINTF("Labels:\n"); gs_ide18 (labellist); /*;_output_graph(void)
_graph();*/ PRINTF("Dummynodes:\n"); gs_ide18 (dummylist); PRINTF("\n\n"); PRINTF("Edges:\n"); /*;list);
PRINTF( Labels:zn );;*/ gs_ide16 (edgelist);  PRINTF("Temporary edges:\n"); gs_ide16 (tmpedgelist); /*;odes:zn );
;*/   }
#endif
#ifdef DEBUG
#ifdef ANSI_C
static void gs_ide18 (GNODE n)
#else
static void gs_ide18 (n) GNODE n;
#endif
{ if (!n) return;  gs_ide18 ((( n )->next) /*;};*/ ); PRINTF("%s, ", (( n )->title) /*;
void gs_ide18 (/N;D+ n);*/ ); }
#endif
#ifdef DEBUG
#ifdef ANSI_C
static void gs_ide16 (GEDGE e)
#else
static void gs_ide16 (e) GEDGE e;
#endif
{ if (!e) return;  gs_ide16 ((( e )->next) /*;};*/ ); if ((( e )->invisible) /*;
void gs_ide16 (/+D/+ e);*/ ==0) PRINTF("(%s -> %s)\n", (( e )->start) /*;
_ide16 (e);*/ ->title, (( e )->end) /*;_ide16 (e);*/ ->title); }
#endif
#ifdef DEBUG
#ifdef ANSI_C
void db_output_adjacencies(void)
#else
void db_output_adjacencies()
#endif
{ GNODE node; ADJEDGE edge; PRINTF("\n\nAdjacency lists: "); node = nodelist; /*;_output_adjacencies(void)
_adjacencies();*/ while (node) { PRINTF("\n%s(%d)%ld\n", (( node )->title) /*;{;*/ , (( node )->tiefe) /*;
{;*/ ,node); PRINTF("(in:%d,out:%d)\n", (( node )->indegree) /*;ode;
;*/ , (( node )->outdegree) /*;ode;;*/ ); PRINTF("Succs:"); edge = (( node )->succ) /*;
znznAdjacency lists:  );;*/ ; while (edge) { PRINTF("|%s(%ld) ", (( ((( (( edge )->kante) /*;
while (node) {;*/ )->end) /*;while (node) {;*/ ) /*;while (node) {;*/ )->title) /*;
while (node) {;*/ , ((( (( edge )->kante) /*;while (node) {;*/ )->end) /*;
while (node) {;*/ ) /*;while (node) {;*/ ); edge = (( edge )->next) /*;
zn%s(%d)%ldzn , (( node )->title) /+;R;*/ ; } PRINTF("\nPreds:"); edge = (( node )->pred) /*;
(( node )->succ) /+;R/SC;yy+NT ;;*/ ; while (edge) { PRINTF("|%s(%ld) ", (( ((( (( edge )->kante) /*;
( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ )->start) /*;( ((( (( edge )->kante) /+;
R/SC;yy+NT );*/ ) /*;( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ )->title) /*;
( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ , ((( (( edge )->kante) /*;
( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ )->start) /*;( ((( (( edge )->kante) /+;
R/SC;yy+NT );*/ ) /*;( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ ); edge = (( edge )->next) /*;
/SC;yy+NT ;;*/ ;  } node = (( node )->next) /*; znPreds: );;*/ ; } node = labellist; /*;while (edge) {
|%s(%ld)  , (( ((( (( edge )->kante) /;*/ while (node) { PRINTF("\n%s(%d)%ld\n", (( node )->title) /*; )->next) /+;
R/SC;yy+NT ; ;*/ , (( node )->tiefe) /*; )->next) /+;R/SC;yy+NT ; ;*/ ,node); /*; )->next) /+;R/SC;yy+NT ; 
};*/ PRINTF("(in:%d,out:%d)\n", (( node )->indegree) /*;};*/ , (( node )->outdegree) /*;
};*/ ); PRINTF("Succs:"); edge = (( node )->succ) /*;};*/ ; while (edge) { /*;labellist;
;*/ PRINTF("|%s(%ld) ", (( ((( (( edge )->kante) /*;;*/ )->end) /*;;*/ ) /*;
;*/ )->title) /*;;*/ , ((( (( edge )->kante) /*;;*/ )->end) /*;;*/ ) /*;
;*/ ); edge = (( edge )->next) /*; , (( node )->title) /+;R/SC;yy+NT , ((;
*/ ; } PRINTF("\nPreds:"); edge = (( node )->pred) /*;(( node )->succ) /+;
R/SC;yy+NT ;;*/ ; while (edge) { PRINTF("|%s(%ld) ", (( ((( (( edge )->kante) /*;
( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ )->start) /*;( ((( (( edge )->kante) /+;
R/SC;yy+NT );*/ ) /*;( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ )->title) /*;
( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ , ((( (( edge )->kante) /*;
( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ )->start) /*;( ((( (( edge )->kante) /+;
R/SC;yy+NT );*/ ) /*;( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ ); edge = (( edge )->next) /*;
/SC;yy+NT ;;*/ ;  } node = (( node )->next) /*; znPreds: );;*/ ; } node = dummylist; /*;while (edge) {
|%s(%ld)  , (( ((( (( edge )->kante) /;*/ while (node) { PRINTF("\n%s(%d)%ld\n", (( node )->title) /*; )->next) /+;
R/SC;yy+NT ; ;*/ , (( node )->tiefe) /*; )->next) /+;R/SC;yy+NT ; ;*/ ,node); /*; )->next) /+;R/SC;yy+NT ; 
};*/ PRINTF("(in:%d,out:%d)\n", (( node )->indegree) /*;};*/ , (( node )->outdegree) /*;
};*/ ); PRINTF("Succs:"); edge = (( node )->succ) /*;};*/ ; while (edge) { /*;dummylist;
;*/ PRINTF("|%s(%ld) ", (( ((( (( edge )->kante) /*;;*/ )->end) /*;;*/ ) /*;
;*/ )->title) /*;;*/ , ((( (( edge )->kante) /*;;*/ )->end) /*;;*/ ) /*;
;*/ ); edge = (( edge )->next) /*; , (( node )->title) /+;R/SC;yy+NT , ((;
*/ ; } PRINTF("\nPreds:"); edge = (( node )->pred) /*;(( node )->succ) /+;
R/SC;yy+NT ;;*/ ; while (edge) { PRINTF("|%s(%ld) ", (( ((( (( edge )->kante) /*;
( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ )->start) /*;( ((( (( edge )->kante) /+;
R/SC;yy+NT );*/ ) /*;( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ )->title) /*;
( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ , ((( (( edge )->kante) /*;
( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ )->start) /*;( ((( (( edge )->kante) /+;
R/SC;yy+NT );*/ ) /*;( ((( (( edge )->kante) /+;R/SC;yy+NT );*/ ); edge = (( edge )->next) /*;
/SC;yy+NT ;;*/ ;  } node = (( node )->next) /*; znPreds: );;*/ ; } PRINTF("\n"); /*;while (edge) {
|%s(%ld)  , (( ((( (( edge )->kante) /;*/ }
#endif
#ifdef DEBUG
#define gtitle(v)  ((( v )->title)  ?(( v )->title)  :"??")
#ifdef ANSI_C
void db_output_adjacency(GNODE node,int f)
#else
void db_output_adjacency(node,f) GNODE node; int f;
#endif
{ ADJEDGE edge; PRINTF("\n\nAdjacency lists: "); PRINTF("\n%ld %s(%d)\n", node, gtitle(node), (( node )->tiefe) /*;
_adjacency(node,f);*/ ); if (f!=1) { PRINTF("Succs:"); edge = (( node )->succ) /*;
{;*/ ; while (edge) { PRINTF("%ld %c:",edge,((( (( edge )->kante) /*;
jacency lists:  );;*/ )->kantenart) /*;jacency lists:  );;*/ ) /*;jacency lists:  );
;*/ ); PRINTF("(%ld)%s-", ((( (( edge )->kante) /*;n , node, gtitle(node), (( node )->tief;
*/ )->start) /*;n , node, gtitle(node), (( node )->tief;*/ ) /*;n , node, gtitle(node), (( node )->tief;
*/ ,gtitle(((( (( edge )->kante) /*;n , node, gtitle(node), (( node )->tief;
*/ )->start) /*;n , node, gtitle(node), (( node )->tief;*/ ) /*;n , node, gtitle(node), (( node )->tief;
*/ )); PRINTF("(%ld)%s ", ((( (( edge )->kante) /*;if (f!=1) {;*/ )->end) /*;
if (f!=1) {;*/ ) /*;if (f!=1) {;*/ ,gtitle(((( (( edge )->kante) /*;
if (f!=1) {;*/ )->end) /*;if (f!=1) {;*/ ) /*;if (f!=1) {;*/ )); edge = (( edge )->next) /*;
Succs: );;*/ ; } } if (f!=0) { PRINTF("\nPreds:"); edge = (( node )->pred) /*;
( (( edge )->kante) /+;R/SC;yy+NT )->en;*/ ; while (edge) { PRINTF("%ld %c:",edge,((( (( edge )->kante) /*;
};*/ )->kantenart) /*;};*/ ) /*;};*/ ); PRINTF("(%ld)%s-", ((( (( edge )->kante) /*;
};*/ )->start) /*;};*/ ) /*;};*/ ,gtitle(((( (( edge )->kante) /*;};
*/ )->start) /*;};*/ ) /*;};*/ ));  PRINTF("(%ld)%s ", ((( (( edge )->kante) /*;
0) {;*/ )->end) /*;0) {;*/ ) /*;0) {;*/ ,gtitle(((( (( edge )->kante) /*;
0) {;*/ )->end) /*;0) {;*/ ) /*;0) {;*/ )); edge = (( edge )->next) /*;
s: );;*/ ;  } node = (( node )->next) /*;while (edge) {;*/ ; PRINTF("End\n"); /*; %ld %c: ,edge,((( (( edge )->kante) /+
s- , ((( (( edge )->kante) /+;R/SC;yy+N;*/ } }
#endif
#ifdef DEBUG
#define mtitle(v)  ((( v )->title)  ?(( v )->title)  :"??")
#ifdef ANSI_C
static void gs_ide17 (void)
#else
static void gs_ide17 ()
#endif
{ int i; GNLIST li; GNODE node; for (i=0; i<=maxdepth+1; i++) { PRINTF("Layer %d:\n",i); /*;_ide17 ()
{;*/ li = (( layer[i] ).succlist) /*;{;*/ ; while (li) { node = (( li )->node) /*;
li;;*/ ; PRINTF("\n%ld %s(%d)\n",node, mtitle(node),(( node )->tiefe) /*;
/N;D+ node;;*/ ); li = (( li )->next) /*;0; i<=maxdepth+1; i++) {;*/ ; /*;%d:zn ,i);
cclist) /+;R/SC;yy+NT ;;*/  } PRINTF("-----------------\n"); } }
#endif
#ifdef DEBUG
#ifdef ANSI_C
static void gs_ide19 (char *fn)
#else
static void gs_ide19 (fn) char *fn;
#endif
{ int i, j; GNLIST li; GNODE node; ADJEDGE edge; CONNECT c1; FILE *f; /*;j;
/NLIST li;;*/  f = fopen(fn,"w"); FPRINTF(f, "graph: { title: \"db_%s\" \n",fn); for (i=0; /*;ode;
ADJ+D/+ edge;;*/  i<=maxdepth+1; i++) { li = (( layer[i] ).succlist) /*;ADJ+D/+ edge;
;*/ ; j = 1; while (li) { node = (( li )->node) /*;en(fn, w );;*/ ; FPRINTF(f, "\nnode: { title: \"%ld\" ",node ); /*;aph: { title: z db_%sz  zn ,fn);
+1; i++) {;*/ if (((( node )->title) /*;+1; i++) {;*/ ) && ((( node )->title) /*;+1;
i++) {;*/ [0])) FPRINTF(f, "label: \"%s\" ", (( node )->title) /*; /+;
R/SC;yy+NT ;;*/ ); FPRINTF(f, "level: %d ", i); FPRINTF(f, "horizontal_order: %d ", j); /*;li) {
->node) /+;R/SC;yy+NT ;;*/ FPRINTF(f, "loc: { x: %d y: %d } ", 10+j*80, 10+i*60); FPRINTF(f, "}\n"); /*; title: z %ldz   ,node );
SC;yy+NT ) && ((( node )->title) /+;R/S;*/ edge = (( node )->succ) /*;SC;yy+NT ) && ((( node )->title) /+;R/S;*/ ; /*;SC;yy+NT ) && ((( node )->title) /+;R/S
e )->title) /+;R/SC;yy+NT );;*/ while (edge) { FPRINTF(f,"edge: { "); FPRINTF(f,"sourcename: \"%ld\" ",((( (( edge )->kante) /*;
,  horizontal_order: %d  , j);;*/ )->start) /*;,  horizontal_order: %d  , j);
;*/ ) /*;,  horizontal_order: %d  , j);;*/ ); FPRINTF(f,"targetname: \"%ld\" ",((( (( edge )->kante) /*;
{ x: %d y: %d }  , 10+j*80, 10+i*60);;*/ )->end) /*; { x: %d y: %d }
, 10+j*80, 10+i*60);;*/ ) /*; { x: %d y: %d }  , 10+j*80, 10+i*60);
;*/ ); FPRINTF(f,"}\n"); edge = (( edge )->next) /*;(( node )->succ) /+;
R/SC;yy+NT ;;*/ ; } c1 = (( node )->connection) /*;;;*/ ; if (c1) { if (((( c1 )->target) /*;
( (( edge )->kante) /+;R/SC;yy+NT )->en;*/ ) && ((( c1 )->target) /*;
( (( edge )->kante) /+;R/SC;yy+NT )->en;*/ !=node)) {  FPRINTF(f,"edge: { "); /*;RINTF(f, }zn );
edge )->next) /+;R/SC;yy+NT ;;*/ FPRINTF(f,"sourcename: \"%ld\" ",node); FPRINTF(f,"targetname: \"%ld\" ", /*;}
node )->connection) /+;R/SC;yy+NT ;;*/ (( c1 )->target) /*; node )->connection) /+;R/SC;yy+NT ;;*/ ); FPRINTF(f, "linestyle: dashed }\n"); /*;if (c1) {
c1 )->target) /+;R/SC;yy+NT ) && ((( c;*/ } if (((( c1 )->target2) /*;e: {  );;*/ ) && ((( c1 )->target2) /*;e: {
);;*/ !=node)) {  FPRINTF(f,"edge: { "); FPRINTF(f,"sourcename: \"%ld\" ",node); /*;z   ,
(( c1 )->target) /+;R/SC;yy+NT );;*/ FPRINTF(f,"targetname: \"%ld\" ", (( c1 )->target2) /*;(f,  linestyle: dashed }
zn );;*/ ); FPRINTF(f, "linestyle: dashed }\n"); } } j++; li = (( li )->next) /*;
z   ,;*/ ; } } FPRINTF(f, "}\n"); fclose(f); }
#endif
