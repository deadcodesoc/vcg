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
static char *gs_ide1016 ="$Id: step3.c,v 3.12 1995/02/08 11:11:14 sander Exp $"; /*;*a*b
*a*b;*/ 
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "globals.h"
#include "alloc.h"
#include "main.h"
#include "options.h"
#include "folding.h"
#include "drawlib.h"
#include "steps.h"
#include "timelim.h"
#include "timing.h"
#undef DRAWDEBUG
#ifdef DRAWDEBUG
extern void debug_display_part _PP((void)); extern void display_part _PP((void)); /*;*a*b
*a*b;*/ static void drawdebug_show_graph _PP((char *m,int i,int j,int k));
#else
#define		drawdebug_show_graph(a,b,c,d)		
#endif
static void gs_ide1017 _PP((void)); static void gs_ide1001 _PP((void)); /*;*a*b
*gs_ide1016 = $Id: step3.c,v 3.12 1995*;*/ static void gs_ide1043 _PP((void)); static void gs_ide1045 _PP((void)); /*;isplay_part _PP((void));
PP((void));;*/ static void gs_ide1042 _PP((int t)); static void gs_ide1044 _PP((GNODE node, int i)); /*;_PP((char *m,int i,int j,int k));
static void gs_ide1017 _PP((void));;*/ static void gs_ide1027 _PP((GNODE node)); static void gs_ide1041 _PP((void)); /*;void gs_ide1001 _PP((void));
_ide1043 _PP((void));;*/ static void gs_ide1004 _PP((GNODE v)); static void gs_ide1051 _PP((GNODE v)); /*;5 _PP((void));
int t));;*/ static void gs_ide1048 _PP((void)); static int gs_ide1008 _PP((GNODE v)); /*;ode, int i));
atic void gs_ide1027 _PP((/N;D+ node));;*/ static int gs_ide1014 _PP((GNODE sw, int sxpos, int dir)); static void gs_ide1049 _PP((GNODE sw, int sxpos, int dir)); /*;id gs_ide1041 _PP((void));
de1004 _PP((/N;D+ v));;*/ static void gs_ide1022 _PP((void)); static int gs_ide1010 _PP((int f)); /*;_PP((/N;D+ v));
id));;*/ static void gs_ide1021 _PP((void)); static int gs_ide1003 _PP((void)); /*;ic int gs_ide1014 _PP((/N;D+ sw, int sx
gs_ide1049 _PP((/N;D+ sw, int sxpos, i;*/  static int gs_ide1036 _PP((int i,int dir)); static int gs_ide1034 _PP((int i,int dir)); /*; gs_ide1049 _PP((/N;D+ sw, int sxpos, i
1022 _PP((void));;*/ static int gs_ide1032 _PP((int i,int dir)); static int gs_ide1050 _PP((int i,int dir)); /*;((int f));
));;*/ static int gs_ide1039 _PP((int i,int dir)); static int gs_ide1005 _PP((int i)); /*;static int gs_ide1003 _PP((void));
int gs_ide1036 _PP((int i,int dir));;*/ static int gs_ide1002 _PP((void)); static int gs_ide1000 _PP((int i)); /*; _PP((int i,int dir));
nt i,int dir));;*/  static int gs_ide1006 _PP((int i)); static int gs_ide1007 _PP((int i)); /*;nt i,int dir));
t dir));;*/ static int gs_ide1030 _PP((GNODE node)); static int gs_ide1031 _PP((GNODE node,GNODE lnode, GNODE rnode)); /*;atic int gs_ide1005 _PP((int i));
t gs_ide1002 _PP((void));;*/ static int gs_ide1012 _PP((GEDGE edge)); static int gs_ide1035 _PP((GNODE node)); /*;e1000 _PP((int i));
PP((int i));;*/ static int gs_ide1011 _PP((GEDGE edge)); static int gs_ide1033 _PP((GNODE node)); /*; i));
));;*/ static void gs_ide1040 _PP((int i)); static int gs_ide1046 ;  static int *gs_ide1025 =NULL; /*;gs_ide1012 _PP((/+D/+ edge));
035 _PP((/N;D+ node));;*/ static int *gs_ide1026 =NULL; static GNODE *gs_ide1047 = NULL; GNLIST *tpred_connection1 = NULL; /*; node));
static void gs_ide1040 _PP((int i));;*/ GNLIST *tpred_connection2 = NULL;
#define forward_connection1(c)  (((( c )->edge)  )&& ((( (( c )->edge)   )->end)  ==(( c )->target)  ))
#define forward_connection2(c)  (((( c )->edge2)  )&&((( (( c )->edge2)   )->end)  ==(( c )->target2)  ))
#define backward_connection1(c) (((( c )->edge)  )&& ((( (( c )->edge)   )->end)  !=(( c )->target)  ))
#define backward_connection2(c) (((( c )->edge2)  )&&((( (( c )->edge2)   )->end)  !=(( c )->target2)  ))
#define TMINX(x) (( x ).cross)  
#ifdef DRAWDEBUG
static int gs_ide1013 = 1;
#endif
#ifdef ANSI_C
void step3_main(void)
#else
void step3_main()
#endif
{ start_time(); ; assert((layer));
#ifdef DRAWDEBUG
if (gs_ide1013 ) { gs_ide1013 = 0; PRINTF("Enter ` ` into the drawwindow\n"); /*;{
ime();;*/ display_part(); return; }
#endif
calc_all_ports(0); calc_all_node_sizes(); gs_ide1017 (); gs_ide1001 (); /*;;
return;;*/ alloc_levelshift(); gs_ide1022 (); gs_ide1021 (); if (straight_phase==1) gs_ide1048 (); /*;sizes();
gs_ide1017 ();;*/ gs_ide1043 (); gs_ide1045 ();  gs_ide1041 (); calc_all_ports(1); stop_time("step3_main"); /*;021 ();
hase==1) gs_ide1048 ();;*/ }
#ifdef ANSI_C
void alloc_levelshift(void)
#else
void alloc_levelshift()
#endif
{ ; if (sizeof(GNLIST)<sizeof(GNODE)) Fatal_error("Assertion 1 about structs is wrong.",""); /*;}
loc_levelshift(void);*/ if (sizeof(GNLIST)<sizeof(int)) Fatal_error("Assertion 2 about structs is wrong.",""); /*;elshift()
{;*/ 
#ifdef TESTLAYOUT
PRINTF("Maximal nodes per layer: %d\n", max_nodes_per_layer); PRINTF("Maximal layers: %d\n", maxdepth); /*;;
eof(/NLIST)<sizeof(/N;D+));*/ 
#endif
if (max_nodes_per_layer+2 > gs_ide1046 ) { if (gs_ide1025 ) free(gs_ide1025 ); /*;ssertion 1 about structs is wrong. ,  )
zeof(int));*/ if (tpred_connection1) free(tpred_connection1); if (tpred_connection2) free(tpred_connection2); /*;ut structs is wrong. ,  );
zn , max_nodes_per_layer);;*/ gs_ide1025 = (int *)malloc((max_nodes_per_layer+2) * sizeof(int)); tpred_connection1 = (GNLIST *)malloc((max_nodes_per_layer+2) /*;odes_per_layer+2 > gs_ide1046 ) {
free(gs_ide1025 );;*/ * sizeof(GNLIST)); tpred_connection2 = (GNLIST *)malloc((max_nodes_per_layer+2) /*;free(tpred_connection1);
red_connection2);;*/ * sizeof(GNLIST)); gs_ide1026 = (int *)tpred_connection1; gs_ide1047 = (GNODE *)tpred_connection2; /*;zeof(int));
ction1 = (/NLIST *)malloc((max_nodes_pe;*/ if ((!gs_ide1025 )||(!gs_ide1026 )||(!gs_ide1047 )) Fatal_error("memory exhausted",""); /*;
ST *)malloc((max_nodes_per_layer+2);*/ gs_ide1046 = max_nodes_per_layer+2;
#ifdef DEBUG
PRINTF("Sizeof tables `levelshift',`levelweight',`slayer_array': %ld Bytes\n", /*;* sizeof(/NLIST));
026 = (int *)tpred_connection1;;*/ (max_nodes_per_layer+2)*sizeof(int));
#endif
} }
#ifdef ANSI_C
void calc_all_node_sizes(void)
#else
void calc_all_node_sizes()
#endif
{ GNODE v; int h,hh,hhh; ADJEDGE a; ; v = nodelist; while (v) { calc_node_size(v); /*;;
int h,hh,hhh;;*/ if ( (G_orientation==1 /*;int h,hh,hhh;;*/ )  ||(G_orientation==2 /*;
a;;*/ )) { h = (( v )->width) /*;;;*/ ; (( v )->width) /*;elist;;*/ = (( v )->height) /*;
elist;;*/ ; (( v )->height) /*;while (v) {;*/ = h; } v = (( v )->next) /*;
ation==1 /+;R/SC;yy+NT ) ;*/ ; } if ( (G_orientation==1 /*;y+NT ;;*/ )  /*;y+NT ;
)->height) /+;R/SC;yy+NT ;;*/ ||(G_orientation==2 /*; )->height) /+;R/SC;yy+NT ;;*/ )) { v = labellist; /*; v )->height) /+;R/SC;yy+NT = h;
};*/ while (v) { h = (( v )->width) /*;v )->next) /+;R/SC;yy+NT ;;*/ ; (( v )->width) /*;
};*/ = (( v )->height) /*;};*/ ; (( v )->height) /*;_orientation==1 /+;
R/SC;yy+NT ) ;*/ = h; v = (( v )->next) /*;on==2 /+;R/SC;yy+NT )) {;
*/ ; } } v = dummylist; while (v) { if ((( v )->anchordummy) /*;T = h;
;*/ ) { a = (( v )->pred) /*;v = (( v )->next) /+;R/SC;yy+NT ;;*/ ; h = 0; /*;}
};*/ while (a) { a=(( a )->next) /*;};*/ ; h++; } a = (( v )->succ) /*;mylist;
;*/ ; hh = 0; while (a) { a=(( a )->next) /*;v )->anchordummy) /+;R/SC;
yy+NT ) {;*/ ; hh++; } hhh = h; if (hh>h) hhh = hh; assert(((( v )->connection) /*;
a) { a=(( a )->next) /+;R/SC;yy+NT ; h+;*/ )); (( v )->height) /*;cc) /+;
R/SC;yy+NT ;;*/ = (( (( (( v )->connection) /*;cc) /+;R/SC;yy+NT ;;*/ )->target) /*;
cc) /+;R/SC;yy+NT ;;*/ )->height) /*;cc) /+;R/SC;yy+NT ;;*/ ; (( v )->width) /*;
hh = 0;;*/ = (hhh+1)*G_xspace; if (manhatten_edges==1) {  if ((h<=1)&&(hh==0)) (( v )->width) /*;
hhh = h;;*/ = 0; if ((h==0)&&(hh<=1)) (( v )->width) /*;h) hhh = hh;
;*/ = 0; } } else { (( v )->width) /*;if (manhatten_edges==1) { ;*/ = 0; /*;if (manhatten_edges==1) { 
=1)&&(hh==0)) (( v )->width) /+;R/SC;yy;*/   (( v )->height) /*;=1)&&(hh==0)) (( v )->width) /+;R/SC;yy;*/ = 0; /*;h<=1)) (( v )->width) /+;R/SC;yy+NT = 0
};*/  }  if ( (G_orientation==1 /*;};*/ )  ||(G_orientation==2 /*;};*/ )) { /*;else {
>width) /+;R/SC;yy+NT = 0; ;*/  h = (( v )->width) /*;else {;*/ ; (( v )->width) /*;>width) /+;R/SC;
yy+NT = 0; ;*/ = (( v )->height) /*;>width) /+;R/SC;yy+NT = 0; ;*/ ; /*;) /+;R/SC;yy+NT = 0;
} ;*/  (( v )->height) /*;) /+;R/SC;yy+NT = 0;;*/ = h; } v = (( v )->next) /*;
_orientation==1 /+;R/SC;yy+NT ) ;*/ ; } }
#define xralign(a)  ((((a)+G_xraster-1)/G_xraster)*G_xraster)
#define yralign(a)  ((((a)+G_yraster-1)/G_yraster)*G_yraster)
#define dxralign(a) ((((a)+G_dxraster-1)/G_dxraster)*G_dxraster)
#define dyralign(a) ((((a)+G_dyraster-1)/G_dyraster)*G_dyraster)
#define xllalign(a)  ((((a)-G_xraster+1)/G_xraster)*G_xraster)
#define xlalign(a)  ((((a))/G_xraster)*G_xraster)
#define ylalign(a)  ((((a))/G_yraster)*G_yraster)
#define dxlalign(a) ((((a))/G_dxraster)*G_dxraster)
#define dylalign(a) ((((a))/G_dyraster)*G_dyraster)
#ifdef ANSI_C
static void gs_ide1017 (void)
#else
static void gs_ide1017 ()
#endif
{ int actxpos, actypos; int maxboxheight; GNLIST li; GNODE v; int i; /*;xpos, actypos;
ht;;*/  ; if (G_yspace<5) G_yspace=5; if (G_xspace<5) G_xspace=5; if (G_dspace==0) { /*;/NLIST li;
;;*/ if (G_spline) G_dspace = 4*G_xspace/5; else G_dspace = G_xspace/2; } /*;space<5) /_yspace=5;
) /_xspace=5;;*/  if (G_flat_factor<1) G_flat_factor = 1; if (G_flat_factor>100) G_flat_factor = 100; /*;) /_xspace=5;
if (/_dspace==0) {;*/ actypos = G_ybase; actypos = yralign(actypos); for (i=0; i<=maxdepth+1; /*;= /_xspace*2;
};*/  i++) { actxpos = G_xbase; maxboxheight = 0; li = (( layer[i] ).succlist) /*;
tor>100) /_flat_factor = 100;;*/ ; while (li) { v = (( li )->node) /*;
= yralign(actypos);;*/ ; if (((( v )->width) /*;axdepth+1; i++) {;*/ ==0)&&((( v )->height) /*;
axdepth+1; i++) {;*/ ==0)) (( v )->xloc) /*;actxpos = /_xbase;;*/ = dxralign(actxpos+(( v )->width) /*;
actxpos = /_xbase;;*/ /2)- (( v )->width) /*;actxpos = /_xbase;;*/ /2; /*;eight = 0;
i] ).succlist) /+;R/SC;yy+NT ;;*/  else (( v )->xloc) /*;eight = 0;;*/ = xralign(actxpos+(( v )->width) /*;
eight = 0;;*/ /2)- (( v )->width) /*;eight = 0;;*/ /2; (( v )->yloc) /*;
i] ).succlist) /+;R/SC;yy+NT ;;*/ = actypos; actxpos = (( v )->xloc) /*;
while (li) {;*/ + (( v )->width) /*;while (li) {;*/ + G_xspace; if (maxboxheight<(( v )->height) /*;
li )->node) /+;R/SC;yy+NT ;;*/ )  maxboxheight = (( v )->height) /*;
idth) /+;R/SC;yy+NT ==0)&&((( v )->heig;*/ ; li = (( li )->next) /*;
;yy+NT = dxralign(actxpos+(( v )->width;*/ ; } if (G_yalign==1 /*;os;
;*/ ) { li = (( layer[i] ).succlist) /*;txpos = (( v )->xloc) /+;R/SC;
yy+NT + (;*/ ; while (li) { (( (( li )->node) /*;( v )->height) /+;R/SC;
yy+NT ;;*/ )->yloc) /*;( v )->height) /+;R/SC;yy+NT ;;*/ += (maxboxheight- /*;( v )->height) /+;R/SC;yy+NT ;
R/SC;yy+NT ;;*/ (( (( li )->node) /*;R/SC;yy+NT ;;*/ )->height) /*;R/SC;yy+NT ;;*/ )/2; /*;R/SC;yy+NT ;
};*/ li = (( li )->next) /*;};*/ ; } } else if (G_yalign==2 /*;while (li) {
;*/ ) { li = (( layer[i] ).succlist) /*;i )->node) /+;R/SC;yy+NT )->yloc) /+;
R/;*/ ; while (li) { (( (( li )->node) /*;+;R/SC;yy+NT ;;*/ )->yloc) /*;
+;R/SC;yy+NT ;;*/ += (maxboxheight- (( (( li )->node) /*;};*/ )->height) /*;
};*/ ); li = (( li )->next) /*;};*/ ; } } actypos += (maxboxheight + G_yspace); /*;while (li) {
i )->node) /+;R/SC;yy+NT )->yloc) /+;R/;*/ actypos = yralign(actypos); } }
#ifdef ANSI_C
static void gs_ide1001 (void)
#else
static void gs_ide1001 ()
#endif
{ GNLIST li; int i; int shift_value; ; for (i=0; i<=maxdepth+1; i++) { /*;{
li;;*/  li = (( layer[i] ).predlist) /*;{;*/ ;  if (li) { assert(((( layer[i] ).succlist) /*;
int i;;*/ )); shift_value = ((( (( li )->node) /*;ft_value;;*/ )->xloc) /*;
ft_value;;*/ +(( (( li )->node) /*;ft_value;;*/ )->width) /*;ft_value;
;*/ )/2;  shift_value = xlalign(shift_value); while (li) { (( (( li )->node) /*;
i] ).predlist) /+;R/SC;yy+NT ; ;*/ )->xloc) /*;i] ).predlist) /+;R/SC;
yy+NT ; ;*/ -= shift_value; li = (( li )->next) /*;if (li) {;*/ ; } } /*;(shift_value);
while (li) {;*/  } }
#ifdef ANSI_C
static void gs_ide1043 (void)
#else
static void gs_ide1043 ()
#endif
{ GNLIST li; int i; int minx,miny; ; minx = miny = MAXINT; for (i=0; /*;{
li;;*/  i<=maxdepth+1; i++) { li = (( layer[i] ).succlist) /*;li;;*/ ; while (li) { /*;int i;
x,miny;;*/ if ((( (( li )->node) /*;x,miny;;*/ )->xloc) /*;x,miny;;*/ <minx) minx = (( (( li )->node) /*;
x,miny;;*/ )->xloc) /*;x,miny;;*/ ; if ((( (( li )->node) /*;;;*/ )->yloc) /*;
;;*/ <miny) miny = (( (( li )->node) /*;;;*/ )->yloc) /*;;;*/ ; li = (( li )->next) /*;
miny = yAXINT;;*/ ; } } minx = minx - G_xbase; miny = miny - G_ybase; /*;->node) /+;R/SC;yy+NT )->yloc) /+;R/SC;
+;R/SC;yy+NT ;;*/  minx = xlalign(minx); miny = xlalign(miny); for (i=0; i<=maxdepth+1; /*;}
};*/  i++) { li = (( layer[i] ).succlist) /*;};*/ ; while (li) { (( (( li )->node) /*;
/_ybase;;*/ )->xloc) /*;/_ybase;;*/ -= minx; (( (( li )->node) /*;;*/ )->yloc) /*;
;*/ -= miny; li = (( li )->next) /*;miny = xlalign(miny);;*/ ; } } } /*;i )->node) /+;R/SC;yy+NT )->xloc) /+;R/
de) /+;R/SC;yy+NT )->yloc) /+;R/SC;yy+N;*/  static int gs_ide1015 ;
#ifdef ANSI_C
static void gs_ide1045 (void)
#else
static void gs_ide1045 ()
#endif
{ GNLIST li; int i; int minx, part_is_missing;  GNODE node; ; for (i=0; /*;{
li;;*/  i<=maxdepth+1; i++) { li = (( layer[i] ).succlist) /*;li;;*/ ; while (li) { /*;int i;
x, part_is_missing; ;*/ (( (( li )->node) /*;x, part_is_missing; ;*/ )->markiert) /*;x, part_is_missing;
;*/ = 0; li = (( li )->next) /*;/N;D+ node;;*/ ; } } gs_ide1015 = G_xbase-G_xspace-5; /*;i] ).succlist) /+;R/SC;yy+NT ;
while (li) {;*/ part_is_missing = 1; while (part_is_missing) { part_is_missing =0; minx = MAXINT; /*;}
};*/ node = (GNODE)0; for (i=0; i<=maxdepth+1; i++) { li = (( layer[i] ).succlist) /*;
g = 1;;*/ ; while (li) { if ((( (( li )->node) /*;part_is_missing =0;
;*/ )->markiert) /*;part_is_missing =0;;*/ == 0) { if (minx > (( (( li )->node) /*;
yAXINT;;*/ )->xloc) /*;yAXINT;;*/ ) { node = (( li )->node) /*;0;;*/ ; /*;+1; i++) {
/+;R/SC;yy+NT ;;*/  minx = (( node )->xloc) /*;+1; i++) {;*/ ; } break; } li = (( li )->next) /*;
(( li )->node) /+;R/SC;yy+NT )->xloc) /;*/ ; } } if (node) { assert(((( node )->markiert) /*;
break;;*/ ==0)); part_is_missing =1; if (minx>gs_ide1015 +G_xspace+5) { /*; li )->next) /+;R/SC;yy+NT ;
};*/ i = minx- gs_ide1015 -G_xspace-5; i = xlalign(i); gs_ide1044 (node,i); /*;e )->markiert) /+;R/SC;yy+NT ==0));
part_is_missing =1;;*/  gs_ide1042 (i); } gs_ide1027 (node); }
#ifdef DRAWDEBUG
#ifdef NEVER
PRINTF("After one shift left together\n"); PRINTF("Enter CR into the text window\n"); /*;044 (node,i);
;;*/ step4_main(); debug_display_part(); fgetc(stdin);
#endif
#endif
} }
#ifdef ANSI_C
static void gs_ide1042 (int t)
#else
static void gs_ide1042 (t) int t;
#endif
{ int i, intermixed_part_found; GNLIST li; GNODE node; intermixed_part_found = 1; /*;_ide1042 (t)
int t;;*/ while (intermixed_part_found) { intermixed_part_found = 0; node = NULL; /*;intermixed_part_found;
/NLIST li;;*/ for (i=0; i<=maxdepth+1; i++) { li = (( layer[i] ).succlist) /*;ode;
;*/ ; while (li) { if ((( (( li )->node) /*;t_found) {;*/ )->markiert) /*;
t_found) {;*/ == 0) { if ( ((( li )->next) /*;intermixed_part_found = 0;
;*/ ) &&((( (( (( li )->next) /*;NULL;;*/ )->node) /*;NULL;;*/ )->markiert) /*;
NULL;;*/ )) { node = (( li )->node) /*;axdepth+1; i++) {;*/ ; intermixed_part_found = 1; /*;cclist) /+;R/SC;yy+NT ;
while (li) {;*/ break; } } li = (( li )->next) /*;t) /+;R/SC;yy+NT )->node) /+;R/SC;
yy+NT;*/ ; } if (intermixed_part_found) break; } if (intermixed_part_found) { /*;}
};*/ assert(((( node )->markiert) /*;};*/ ==0)); gs_ide1044 (node,t); gs_ide1027 (node); /*;}
ermixed_part_found) break;;*/ } } }
#ifdef ANSI_C
static void gs_ide1044 (GNODE node, int i)
#else
static void gs_ide1044 (node, i) GNODE node; int i;
#endif
{ ADJEDGE e; ; if ((( node )->markiert) /*;_ide1044 (node, i);*/ ) return; /*;_ide1044 (node, i)
/N;D+ node;;*/ (( node )->markiert) /*;/N;D+ node;;*/ = 1; (( node )->xloc) /*;int i;
;*/ -= i; if ((( node )->connection) /*;{;*/ ) { if ((( (( node )->connection) /*;
e;;*/ )->target) /*; e;;*/ ) gs_ide1044 ((( (( node )->connection) /*;
;;*/ )->target) /*;;;*/ ,i); if ((( (( node )->connection) /*;node )->markiert) /+;
R/SC;yy+NT ) retur;*/ )->target2) /*;node )->markiert) /+;R/SC;yy+NT ) retur;
*/ ) gs_ide1044 ((( (( node )->connection) /*;kiert) /+;R/SC;yy+NT = 1;
;*/ )->target2) /*;kiert) /+;R/SC;yy+NT = 1;;*/ ,i); } e = (( node )->succ) /*;
+;R/SC;yy+NT ) {;*/ ; while (e) { gs_ide1044 (((( (( e )->kante) /*;
_ide1044 ((( (( node )->connection) /+;;*/ )->end) /*;_ide1044 ((( (( node )->connection) /+;
;*/ ) /*;_ide1044 ((( (( node )->connection) /+;;*/ ,i); e = (( e )->next) /*;
node )->connection) /+;R/SC;yy+NT )->t;*/ ; } e = (( node )->pred) /*;
};*/ ; while (e) { gs_ide1044 (((( (( e )->kante) /*;while (e) {;*/ )->start) /*;
while (e) {;*/ ) /*;while (e) {;*/ ,i); e = (( e )->next) /*;044 (((( (( e )->kante) /+;
R/SC;yy+NT );*/ ; } }
#ifdef ANSI_C
static void gs_ide1027 (GNODE node)
#else
static void gs_ide1027 (node) GNODE node;
#endif
{ ADJEDGE e; ; if ((( node )->markiert) /*;void gs_ide1027 (/N;D+ node);
*/ ==2) return; (( node )->markiert) /*;_ide1027 (node);*/ = 2; if ((( node )->xloc) /*;
/N;D+ node;;*/ +(( node )->width) /*;/N;D+ node;;*/ >gs_ide1015 )  gs_ide1015 = (( node )->xloc) /*;
{;*/ +(( node )->width) /*;{;*/ ; if ((( node )->connection) /*; e;;
*/ ) { if ((( (( node )->connection) /*;;;*/ )->target) /*;;;*/ ) gs_ide1027 ((( (( node )->connection) /*;
node )->markiert) /+;R/SC;yy+NT ==2) re;*/ )->target) /*;node )->markiert) /+;
R/SC;yy+NT ==2) re;*/ ); if ((( (( node )->connection) /*;kiert) /+;
R/SC;yy+NT = 2;;*/ )->target2) /*;kiert) /+;R/SC;yy+NT = 2;;*/ ) gs_ide1027 ((( (( node )->connection) /*;
/+;R/SC;yy+NT +(( node )->width) /+;R/S;*/ )->target2) /*;/+;R/SC;yy+NT +(( node )->width) /+;
R/S;*/ ); } e = (( node )->succ) /*;yy+NT ) {;*/ ; while (e) { gs_ide1027 (((( (( e )->kante) /*;
7 ((( (( node )->connection) /+;R/SC;yy;*/ )->end) /*;7 ((( (( node )->connection) /+;
R/SC;yy;*/ ) /*;7 ((( (( node )->connection) /+;R/SC;yy;*/ ); e = (( e )->next) /*;
->connection) /+;R/SC;yy+NT )->target2);*/ ; } e = (( node )->pred) /*;
};*/ ; while (e) { gs_ide1027 (((( (( e )->kante) /*;while (e) {;*/ )->start) /*;
while (e) {;*/ ) /*;while (e) {;*/ ); e = (( e )->next) /*;027 (((( (( e )->kante) /+;
R/SC;yy+NT );*/ ; } }
#ifdef ANSI_C
static void gs_ide1041 (void)
#else
static void gs_ide1041 ()
#endif
{ GNLIST li; int i; int weight, found; GNODE node; CONNECT c; ; for (i=0; /*;li;
int i;;*/  i<=maxdepth+1; i++) { li = (( layer[i] ).succlist) /*;int i;;*/ ; while (li) { /*;ght, found;
/N;D+ node;;*/ weight = 0; node = (( li )->node) /*; c;;*/ ; c = (( node )->connection) /*;
;;*/ ; found = 0; if (c) { if ((( c )->target) /*;while (li) {;*/ ) { /*;= 0;
->node) /+;R/SC;yy+NT ;;*/   if ((( (( c )->target) /*;= 0;;*/ )->xloc) /*;= 0;;*/ <(( node )->xloc) /*;
= 0;;*/ ) { weight = (( (( c )->edge) /*;->node) /+;R/SC;yy+NT ;;*/ )->priority) /*;
->node) /+;R/SC;yy+NT ;;*/ ; weight *= layout_nearfactor; if (weight==0) found = 1; /*;found = 0;
{;*/   } } if ((( c )->target2) /*;) /+;R/SC;yy+NT )->xloc) /+;R/SC;yy+NT ;
*/ ) { if ((( (( c )->target2) /*;;R/SC;yy+NT )->priority) /+;R/SC;yy+NT ;
*/ )->xloc) /*;;R/SC;yy+NT )->priority) /+;R/SC;yy+NT ;*/ <(( node )->xloc) /*;
;R/SC;yy+NT )->priority) /+;R/SC;yy+NT ;*/ ) { weight = (( (( c )->edge2) /*;
weight *= layout_nearfactor;;*/ )->priority) /*;weight *= layout_nearfactor;
;*/ ; weight *= layout_nearfactor; if (weight==0) found = 1;  } } } if (found) gs_ide1004 (node); /*;dge2) /+;R/SC;yy+NT )->priority) /+;R/S
;*/ li = (( li )->next) /*;;*/ ; } } }
#ifdef ANSI_C
static void gs_ide1004 (GNODE v)
#else
static void gs_ide1004 (v) GNODE v;
#endif
{ GNLIST li; int i; int mindist, found; ; for (i=0; i<=maxdepth+1; i++) { /*;/N;D+ v;
{;*/ li = (( layer[i] ).succlist) /*;{;*/ ; (( layer[i] ).actx) /*;li;;*/ = MAXINT; /*;li;
int i;;*/ TMINX(layer[i]) = MAXINT; (( layer[i] ).refnode) /*;dist, found;;*/ = NULL; /*;dist, found;
;;*/ while (li) { (( (( li )->node) /*;0; i<=maxdepth+1; i++) {;*/ )->markiert) /*;
0; i<=maxdepth+1; i++) {;*/ = 0; li = (( li )->next) /*;i] ).succlist) /+;
R/SC;yy+NT ;;*/ ; } } gs_ide1051 (v); mindist = MAXINT; for (i=0; i<=maxdepth+1; /*;i )->node) /+;R/SC;yy+NT )->markiert) /
next) /+;R/SC;yy+NT ;;*/  i++) { if ((( layer[i] ).actx) /*;next) /+;R/SC;yy+NT ;;*/ <mindist) mindist = (( layer[i] ).actx) /*;
next) /+;R/SC;yy+NT ;;*/ ;  } if ((mindist>0) && (mindist!=MAXINT)) { /*;051 (v);
NT;;*/  for (i=0; i<=maxdepth+1; i++) { li = (( layer[i] ).succlist) /*;NT;
;*/ ; found = 0; while (li) { if ((( li )->node) /*;};*/ ==(( layer[i] ).refnode) /*;
};*/ ) found = 1; if (found) (( (( li )->node) /*;ndist>0) && (mindist!=yAXINT)) {
;*/ )->xloc) /*;ndist>0) && (mindist!=yAXINT)) {;*/ -= mindist; li = (( li )->next) /*;
axdepth+1; i++) {;*/ ; } } }  }
#ifdef ANSI_C
static void gs_ide1051 (GNODE v)
#else
static void gs_ide1051 (v) GNODE v;
#endif
{ int level, weight; GNLIST li; ADJEDGE e; CONNECT c; ; if (!v) return; /*;{
el, weight;;*/ if ((( v )->markiert) /*;el, weight;;*/ ) return; (( v )->markiert) /*;
/NLIST li;;*/ = 1; level = (( v )->tiefe) /*; e;;*/ ; if ((( v )->xloc) /*;
C;NN+CT c;;*/ < TMINX(layer[level])) { (( layer[level] ).refnode) /*;
;;*/ = v; TMINX(layer[level]) = (( v )->xloc) /*; return;;*/ ; li = (( layer[level] ).predlist) /*;
rkiert) /+;R/SC;yy+NT ) return;;*/ ; while (li) { if ((( li )->node) /*;
SC;yy+NT ;;*/ ==v) break; li = (( li )->next) /*;yINX(layer[level])) {
;*/ ; } assert((li)); li = (( li )->next) /*;vel] ).predlist) /+;R/SC;
yy+NT ;;*/ ; if (li) { (( layer[level] ).actx) /*;li )->node) /+;R/SC;
yy+NT ==v) break;;*/ = (( v )->xloc) /*;li )->node) /+;R/SC;yy+NT ==v) break;
;*/ - G_xspace  - (( (( li )->node) /*;next) /+;R/SC;yy+NT ;;*/ )->xloc) /*;
next) /+;R/SC;yy+NT ;;*/ - (( (( li )->node) /*;next) /+;R/SC;yy+NT ;
;*/ )->width) /*;next) /+;R/SC;yy+NT ;;*/ ; } else (( layer[level] ).actx) /*;
(li));;*/ = (( v )->xloc) /*;(li));;*/ - G_xbase; } c = (( v )->connection) /*;
if (li) {;*/ ; if (c) { if ((( c )->target) /*;node) /+;R/SC;yy+NT )->xloc) /+;
R/SC;yy;*/ ) { if ((( (( c )->target) /*;};*/ )->xloc) /*;};*/ >(( v )->xloc) /*;
};*/ ) weight = 1;  else weight = (( (( c )->edge) /*; layer[level] ).actx) /+;
R/SC;yy+NT = (;*/ )->priority) /*; layer[level] ).actx) /+;R/SC;yy+NT = (;
*/ * layout_nearfactor; if (weight!=0)  gs_ide1051 ((( c )->target) /*;
v )->connection) /+;R/SC;yy+NT ;;*/ ); } if ((( c )->target2) /*;c )->target) /+;
R/SC;yy+NT ) {;*/ ) { if ((( (( c )->target2) /*;>target) /+;R/SC;yy+NT )->xloc) /+;
R/SC;*/ )->xloc) /*;>target) /+;R/SC;yy+NT )->xloc) /+;R/SC;*/ >(( v )->xloc) /*;
>target) /+;R/SC;yy+NT )->xloc) /+;R/SC;*/ ) weight = 1;  else weight = (( (( c )->edge2) /*;
)->edge) /+;R/SC;yy+NT )->priority) /+;*/ )->priority) /*; )->edge) /+;
R/SC;yy+NT )->priority) /+;*/ * layout_nearfactor; if (weight!=0)  gs_ide1051 ((( c )->target2) /*;
051 ((( c )->target) /+;R/SC;yy+NT );;*/ ); } } e = (( v )->succ) /*;
>target2) /+;R/SC;yy+NT )->xloc) /+;R/S;*/ ; while (e) { gs_ide1051 (((( (( e )->kante) /*;
if (weight!=0) ;*/ )->end) /*;if (weight!=0) ;*/ ) /*;if (weight!=0) ;
*/ ); e = (( e )->next) /*;051 ((( c )->target2) /+;R/SC;yy+NT );;*/ ; /*;}
};*/  } e = (( v )->pred) /*;};*/ ; while (e) { gs_ide1051 (((( (( e )->kante) /*;
while (e) {;*/ )->start) /*;while (e) {;*/ ) /*;while (e) {;*/ ); e = (( e )->next) /*;
051 (((( (( e )->kante) /+;R/SC;yy+NT );*/ ; } } static int gs_ide1009 ; /*;v )->pred) /+;R/SC;yy+NT ;
while (e) {;*/ static int gs_ide1037 = MAXINT; static int gs_ide1028 = MAXINT; static int gs_ide1038 = MAXINT; /*;xt) /+;R/SC;yy+NT ;
};*/ static int gs_ide1029 = MAXINT; static int gs_ide1023 = 0; static int gs_ide1024 = 0; /*;int gs_ide1009 ;
ide1037 = yAXINT;;*/ 
#ifdef ANSI_C
static void gs_ide1022 (void)
#else
static void gs_ide1022 ()
#endif
{ int count; int changed; int tryout; ; gs_ide1037 = MAXINT; gs_ide1028 = MAXINT; /*;{
nt;;*/ gs_ide1038 = MAXINT; gs_ide1029 = MAXINT; gs_ide1023 = 0; gs_ide1024 = 0; /*;;
037 = yAXINT;;*/ count = 0; tryout = 2; gs_ide1009 = 2; while (1) { if (count%5==0) { /*;gs_ide1024 = 0;
0;;*/  gs_wait_message('m'); gs_ide1043 ();  } count++; drawdebug_show_graph("dump mediumshift",count,0,tryout); /*;while (1) {
nt%5==0) {;*/ changed = gs_ide1010 (0);  changed += gs_ide1010 (1); gs_ide1009 = 1; /*;}
;;*/  if ((!changed)&&(count>=min_mediumshifts)) break; if (count>=max_mediumshifts) { /*;;
_graph( dump mediumshift ,count,0,tryou;*/ gs_wait_message('t'); break;  } if (G_timelimit>0) if (test_timelimit(85)) { /*;&&(count>=min_mediumshifts)) break;
shifts) {;*/ gs_wait_message('t'); break; } if (count>=min_mediumshifts) { if (!gs_ide1003 ()) { /*;imelimit>0)
imit(85)) {;*/ tryout--; if (tryout==0) break; }  else tryout = 2; } }  }
#ifdef ANSI_C
static int gs_ide1003 (void)
#else
static int gs_ide1003 () 
#endif
{ int i, nwval1, nwval2, k; int changed; GNLIST li; ; changed = nwval1 = nwval2 = 0; /*;ide1003 () 
{;*/ for (i=0; i<=maxdepth+1; i++) { li = (( layer[i] ).succlist) /*;nwval1, nwval2, k;
;*/ ;  while (li) { k = gs_ide1035 ((( li )->node) /*;li;;*/ );  if (k<0) k = -k; /*;;
= nwval1 = nwval2 = 0;;*/ nwval1 += k;  k = gs_ide1033 ((( li )->node) /*;axdepth+1; i++) {;*/ ); /*;axdepth+1; i++) {
cclist) /+;R/SC;yy+NT ; ;*/   if (k<0) k = -k; nwval2 += k;  li = (( li )->next) /*;ide1035 ((( li )->node) /+;
R/SC;yy+NT );*/ ; } } if (nwval1<gs_ide1028 ) {  changed = 1; gs_ide1037 = gs_ide1028 = nwval1; /*;nwval2 += k; 
li )->next) /+;R/SC;yy+NT ;;*/ gs_ide1023 = 0; } else { if (nwval1<gs_ide1037 ) { changed = 1; gs_ide1037 = nwval1; /*;037 = gs_ide1028 = nwval1;
;;*/ } if (gs_ide1023 < 1) { gs_ide1037 = nwval1; gs_ide1023 ++; } } if (nwval2<gs_ide1029 ) { /*;}
ide1023 < 1) {;*/   changed = 1; gs_ide1038 = gs_ide1029 = nwval2; gs_ide1024 = 0; } else { /*;}
al2<gs_ide1029 ) { ;*/ if (nwval2<gs_ide1038 ) { changed = 1; gs_ide1038 = nwval2; } if (gs_ide1024 < 1) { /*;}
else {;*/ gs_ide1038 = nwval2; gs_ide1024 ++; } }
#ifdef DRAWDEBUG
printf("Graph Weight: minimal: %d %d old: %d %d actual: %d %d\n",  gs_ide1028 , gs_ide1029 , gs_ide1037 , gs_ide1038 , nwval1, nwval2); /*;ide1024 < 1) {
wval2;;*/ 
#endif
return(changed); }
#ifdef ANSI_C
static int gs_ide1010 (int first)
#else
static int gs_ide1010 (first) int first;
#endif
{ int i; int layer_changed; int dir; ; layer_changed = 0; dir = 0; if (first) { /*;int i;
er_changed;;*/ for (i=1; i<=maxdepth+1; i++) { dir = 1-dir; layer_changed += gs_ide1034 (i,dir); /*;;
hanged = 0;;*/ dir = 1-dir; layer_changed += gs_ide1034 (i,dir); } if (prio_phase==1) { /*;axdepth+1; i++) {
dir = 1-dir;;*/ for (i=0; i<=maxdepth+1; i++)  layer_changed += gs_ide1005 (i); } } for (i=maxdepth; /*;}
o_phase==1) {;*/  i>=0; i--) { dir = 1-dir; layer_changed += gs_ide1036 (i,dir); dir = 1-dir; /*;de1005 (i);
};*/ layer_changed += gs_ide1036 (i,dir); } if (prio_phase==1) { for (i=0; /*;dir = 1-dir;
hanged += gs_ide1036 (i,dir);;*/  i<=maxdepth+1; i++)  layer_changed += gs_ide1005 (i); } if (!first) { /*;}
o_phase==1) {;*/  for (i=1; i<=maxdepth+1; i++) { dir = 1-dir; layer_changed += gs_ide1034 (i,dir); /*;axdepth+1; i++) 
de1005 (i);;*/ dir = 1-dir; layer_changed += gs_ide1034 (i,dir); } if (prio_phase==1) { /*;axdepth+1; i++) {
dir = 1-dir;;*/ for (i=0; i<=maxdepth+1; i++)  layer_changed += gs_ide1005 (i); } } if (nwdumping_phase) { /*;}
o_phase==1) {;*/ for (i=maxdepth; i>=0; i--) { dir = 1-dir; layer_changed += gs_ide1032 (i,dir); /*;de1005 (i);
};*/ dir = 1-dir; layer_changed += gs_ide1032 (i,dir); } if (prio_phase==1) { /*;h; i>=0; i--) {
dir = 1-dir;;*/ for (i=0; i<=maxdepth+1; i++)  layer_changed += gs_ide1005 (i); } } if (layer_changed) return(1); /*;}
o_phase==1) {;*/ return(0); }
#ifdef ANSI_C
static int gs_ide1018 (GNODE v) 
#else
static int gs_ide1018 (v)  GNODE v;
#endif
{ int nr_edges; int pr; ADJEDGE a; if (!v) return(0); pr = 1; a = (( v )->succ) /*;
{;*/ ; nr_edges = 0; while (a) { nr_edges ++; a = (( a )->next) /*;(0);
;*/ ; } if (nr_edges>1) pr = 0; a = (( v )->pred) /*;nr_edges = 0;;*/ ; /*;nr_edges = 0;
a) {;*/ nr_edges = 0; while (a) { nr_edges ++; a = (( a )->next) /*;};*/ ; } /*;ed) /+;R/SC;yy+NT ;
nr_edges = 0;;*/  if (nr_edges>1) pr = 0; return(pr); }
#ifdef ANSI_C
static int gs_ide1020 (GNODE v) 
#else
static int gs_ide1020 (v)  GNODE v;
#endif
{ int nr_edges; ADJEDGE a; if (!v) return(0); a = (( v )->succ) /*;ide1020 (v) ;
*/ ; nr_edges = 0; while (a) { nr_edges ++; a = (( a )->next) /*;ADJ+D/+ a;
;*/ ; } return((nr_edges == 1)); }
#ifdef ANSI_C
static int gs_ide1019 (GNODE v) 
#else
static int gs_ide1019 (v)  GNODE v;
#endif
{ int nr_edges; ADJEDGE a; if (!v) return(0); a = (( v )->pred) /*;ide1019 (v) ;
*/ ; nr_edges = 0; while (a) { nr_edges ++; a = (( a )->next) /*;ADJ+D/+ a;
;*/ ; } return((nr_edges == 1)); }
#ifdef ANSI_C
static int gs_ide1036 (int i,int dir)
#else
static int gs_ide1036 (i,dir) int i; int dir;
#endif
{ GNLIST li; int j; int sign; ; assert((i<=maxdepth)); gs_ide1040 (i); /*;li;
int j;;*/  li = (( layer[i] ).succlist) /*;li;;*/ ; j = 0;  sign = 1; while (li) { /*;;
(i<=maxdepth));;*/ gs_ide1025 [j] = gs_ide1035 ((( li )->node) /*;(i<=maxdepth));;*/ ); /*;;
cclist) /+;R/SC;yy+NT ;;*/   if ((sign<0) && (gs_ide1025 [j]>=0)) gs_ide1026 [j]=1;  else gs_ide1026 [j]= MAXINT; /*;cclist) /+;R/SC;yy+NT ;
j = 0; ;*/ if (gs_ide1025 [j]<0) sign = -1; else sign = 1;  j++; li = (( li )->next) /*;
while (li) {;*/ ; } gs_ide1026 [0]= 1; if (prio_phase==1) { li = (( layer[i] ).succlist) /*;
-1; else sign = 1; ;*/ ; while (li) { (( (( li )->node) /*; li )->next) /+;
R/SC;yy+NT ;;*/ )->dfsnum) /*; li )->next) /+;R/SC;yy+NT ;;*/ = gs_ide1020 ((( li )->node) /*;
li )->next) /+;R/SC;yy+NT ;;*/ );  li = (( li )->next) /*;};*/ ; } return(gs_ide1039 (i,dir)); /*;==1) {
cclist) /+;R/SC;yy+NT ;;*/ } return(gs_ide1050 (i,dir)); }
#ifdef ANSI_C
static int gs_ide1034 (int i,int dir)
#else
static int gs_ide1034 (i,dir) int i; int dir;
#endif
{ GNLIST li; int j; int sign; ; assert((i>0)); gs_ide1040 (i); li = (( layer[i] ).succlist) /*;
li;;*/ ; j = 0;  sign = 1; while (li) { gs_ide1025 [j] = gs_ide1033 ((( li )->node) /*;
(i>0));;*/ );  if ((sign<0) && (gs_ide1025 [j]>=0)) gs_ide1026 [j]=1; /*;cclist) /+;R/SC;yy+NT ;
j = 0; ;*/   else gs_ide1026 [j]= MAXINT; if (gs_ide1025 [j]<0) sign = -1; else sign = 1; /*;j = 0; 
1;;*/   j++; li = (( li )->next) /*;while (li) {;*/ ; } gs_ide1026 [0]= 1; /*;yAXINT;
-1; else sign = 1; ;*/  if (prio_phase==1) { li = (( layer[i] ).succlist) /*; -1; else sign = 1;
;*/ ; while (li) { (( (( li )->node) /*; li )->next) /+;R/SC;yy+NT ;
;*/ )->dfsnum) /*; li )->next) /+;R/SC;yy+NT ;;*/ = gs_ide1019 ((( li )->node) /*;
li )->next) /+;R/SC;yy+NT ;;*/ );  li = (( li )->next) /*;};*/ ; } return(gs_ide1039 (i,dir)); /*;==1) {
cclist) /+;R/SC;yy+NT ;;*/ } return(gs_ide1050 (i,dir)); }
#ifdef ANSI_C
static int gs_ide1032 (int i,int dir)
#else
static int gs_ide1032 (i,dir) int i; int dir;
#endif
{ GNLIST li, li1; int j; int sign; GNODE lnode, node, rnode; ; assert((i<=maxdepth)); /*;{
li, li1;;*/ gs_ide1040 (i); li = (( layer[i] ).succlist) /*;int j;;*/ ; j = 0;  sign = 1; /*;ode, rnode;
;;*/ lnode = NULL; while (li) { node = (( li )->node) /*;;;*/ ; if ((( node )->width) /*;
cclist) /+;R/SC;yy+NT ;;*/ ==0) { li1 = (( li )->next) /*;j = 0; ;*/ ; /*;1;
lnode = NULL;;*/  rnode = NULL; while (li1) { if ((( (( li1 )->node) /*;li) {;*/ )->width) /*;
li) {;*/ !=0) { rnode = (( li1 )->node) /*;->node) /+;R/SC;yy+NT ;;*/ ; /*;->node) /+;R/SC;yy+NT ;
/+;R/SC;yy+NT ==0) {;*/ break; } li1 = (( li1 )->next) /*;rnode = NULL;;*/ ; } gs_ide1025 [j] = gs_ide1031 (node,lnode,rnode); /*;)->node) /+;R/SC;yy+NT )->width) /+;R/S
e) /+;R/SC;yy+NT ;;*/ } else { gs_ide1025 [j] = gs_ide1030 (node);  lnode = node; } if ((sign<0) && (gs_ide1025 [j]>=0)) gs_ide1026 [j]=1; /*;}
025 [j] = gs_ide1031 (node,lnode,rnode);*/   else gs_ide1026 [j]= MAXINT; if (gs_ide1025 [j]<0) sign = -1; else sign = 1; /*;}
gs_ide1025 [j] = gs_ide1030 (node); ;*/   j++; li = (( li )->next) /*;lnode = node;;*/ ; } gs_ide1026 [0]= 1; /*;6 [j]= yAXINT;
sign = -1; else sign = 1; ;*/  return(gs_ide1050 (i,dir)); }
#define touching(v,w)  (  ((( v )->xloc)  +(( v )->width)  +G_xspace >= (( w )->xloc)  )       			||((( w )->xloc)  - (( v )->xloc)  - (( v )->width)  <=2*G_xraster)) 
#ifdef ANSI_C
static int gs_ide1050 (int i,int dir)
#else
static int gs_ide1050 (i,dir) int i; int dir;
#endif
{ GNLIST li; int j; int changed; int oldpos,sum,nrnodes; GNODE v,w; ; /*;li;
int j;;*/  li = (( layer[i] ).succlist) /*;li;;*/ ; j = 0;  while (li) { v = (( li )->node) /*;
,nrnodes;;*/ ; if ((( li )->next) /*;/N;D+ v,w;;*/ ) { w = (( (( li )->next) /*;
;;*/ )->node) /*;;;*/ ;  if (!touching(v,w))  gs_ide1026 [j+1]=1;  } /*;ode) /+;R/SC;yy+NT ;
;R/SC;yy+NT ) {;*/   j++; li = (( li )->next) /*;;R/SC;yy+NT ) {;*/ ; } changed = 1; while (changed) { /*;026 [j+1]=1; 
} ;*/ changed = 0; li = (( layer[i] ).succlist) /*;j++;;*/ ; j = 0;  oldpos = -1; /*;}
= 1;;*/ nrnodes = 1;  while (li) { if (gs_ide1026 [j]!=MAXINT) { if (oldpos!= -1) gs_ide1026 [oldpos] = sum/nrnodes; /*; layer[i] ).succlist) /+;R/SC;yy+NT ;
j = 0; ;*/ sum = gs_ide1025 [j]; nrnodes = 1; oldpos = j;  } else { sum += gs_ide1025 [j]; /*; [j]!=yAXINT) {
de1026 [oldpos] = sum*nrnodes;;*/  nrnodes++; } j++; li = (( li )->next) /*;sum = gs_ide1025 [j];;*/ ; /*;oldpos = j; 
};*/  } if (oldpos!= -1) gs_ide1026 [oldpos] = sum/nrnodes; li = (( layer[i] ).succlist) /*;
};*/ ; j = 0;  sum = 0; while (li) { if (gs_ide1026 [j]!=MAXINT) sum = gs_ide1026 [j]; /*;}
pos!= -1) gs_ide1026 [oldpos] = sum*nrn;*/ if ((( li )->next) /*;pos!= -1) gs_ide1026 [oldpos] = sum*nrn;*/ &&(gs_ide1026 [j+1]!=MAXINT)) { /*;pos!= -1) gs_ide1026 [oldpos] = sum*nrn
i] ).succlist) /+;R/SC;yy+NT ;;*/ v = (( li )->node) /*;i] ).succlist) /+;R/SC;yy+NT ;;*/ ; w = (( (( li )->next) /*;
j = 0; ;*/ )->node) /*;j = 0; ;*/ ;  if (touching(v,w)) { if ( (sum>=0)&&(gs_ide1026 [j+1]>=0) /*;while (li) {
ide1026 [j]!=yAXINT) sum = gs_ide1026 [;*/ &&(sum>=gs_ide1026 [j+1])) { gs_ide1026 [j+1] = MAXINT; changed = 1; /*;if (touching(v,w)) {
um>=0)&&(gs_ide1026 [j+1]>=0);*/  } if ( (sum<0)&&(gs_ide1026 [j+1]<0) &&(sum>=gs_ide1026 [j+1])) { gs_ide1026 [j+1] = MAXINT; /*;1026 [j+1])) {
XINT;;*/ changed = 1; } if ( (sum>0)&&(gs_ide1026 [j+1]<0)) { gs_ide1026 [j+1] = MAXINT; /*;um<0)&&(gs_ide1026 [j+1]<0)
1026 [j+1])) {;*/ changed = 1; } }  } j++; li = (( li )->next) /*;1] = yAXINT;;*/ ; } } /*;} 
};*/  li = (( layer[i] ).succlist) /*;} ;*/ ; j = 0;  assert((gs_ide1026 [0]!=MAXINT)); /*;j++;
li )->next) /+;R/SC;yy+NT ;;*/ while (li) { if (gs_ide1026 [j]!=MAXINT) sum = gs_ide1009 * gs_ide1026 [j]; /*;}
};*/ gs_ide1025 [j] = sum; gs_ide1026 [j]= 1; j++; li = (( li )->next) /*;
(gs_ide1026 [0]!=yAXINT));;*/ ; } if (dir) { changed = gs_ide1007 (i); /*;gs_ide1026 [j]= 1;
j++;;*/  changed += gs_ide1006 (i); } else { changed = gs_ide1006 (i); changed += gs_ide1007 (i); /*;) {
de1007 (i);;*/ } return(changed); }
#ifdef ANSI_C
static int gs_ide1039 (int i,int dir)
#else
static int gs_ide1039 (i,dir) int i; int dir;
#endif
{ GNLIST li; int j; int changed; int oldpos,sum,nrnodes; int priosum, nrprionodes, lprio, rprio; /*;;
{;*/ GNODE v,w; ; li = (( layer[i] ).succlist) /*;int j;;*/ ; j = 0;  while (li) { /*;,nrnodes;
des, lprio, rprio;;*/ v = (( li )->node) /*;des, lprio, rprio;;*/ ; if ((( li )->next) /*;
/N;D+ v,w;;*/ ) { w = (( (( li )->next) /*;;;*/ )->node) /*;;;*/ ;  if (!touching(v,w))  /*; layer[i] ).succlist) /+;R/SC;yy+NT ;
j = 0; ;*/ gs_ide1026 [j+1]=1;  }  j++; li = (( li )->next) /*;;R/SC;yy+NT ) {;
*/ ; } changed = 1; while (changed) { changed = 0; li = (( layer[i] ).succlist) /*;
j++;;*/ ; j = 0; while (li) { if ((( (( li )->node) /*; = 1;;*/ )->dfsnum) /*;
= 1;;*/ &&(gs_ide1025 [j]==0)) { gs_ide1026 [j] = 1; gs_ide1026 [j+1] = 1; /*;changed = 0;
layer[i] ).succlist) /+;R/SC;yy+NT ;;*/ } j++; li = (( li )->next) /*;li) {;*/ ; } li = (( layer[i] ).succlist) /*;
gs_ide1026 [j] = 1;;*/ ; j = 0;  oldpos = -1; nrnodes = 1;  priosum = 0; /*; li )->next) /+;R/SC;yy+NT ;
};*/ lprio = 0; rprio = 0; nrprionodes = 0; while (li) { if (gs_ide1026 [j]!=MAXINT) { /*;nrnodes = 1; 
= 0;;*/ if (oldpos!= -1) { gs_ide1026 [oldpos] = sum/nrnodes; if (nrprionodes !=0) { /*; 0;
0;;*/ if (priosum>0) { gs_ide1026 [oldpos]=lprio; } else { gs_ide1026 [oldpos]=rprio; /*; sum*nrnodes;
if (nrprionodes !=0) {;*/ } } } lprio = 0; rprio = 0; priosum = 0; nrprionodes = 0; sum = 0; nrnodes = 0; /*;}
0;;*/ oldpos = j;  } if ((( (( li )->node) /*; = 0;;*/ )->dfsnum) /*; = 0;
;*/ ) { priosum += gs_ide1025 [j]; if (lprio==0) lprio = gs_ide1025 [j]; /*;sum = 0;
= 0;;*/ rprio = gs_ide1025 [j]; nrprionodes++; } sum += gs_ide1025 [j];  nrnodes++; /*;ide1025 [j];
gs_ide1025 [j];;*/   j++; li = (( li )->next) /*;rprio = gs_ide1025 [j];;*/ ; } if (oldpos!= -1) gs_ide1026 [oldpos] = sum/nrnodes; /*;}
gs_ide1025 [j]; ;*/ li = (( layer[i] ).succlist) /*;gs_ide1025 [j]; ;*/ ; j = 0;  sum = 0; /*; li )->next) /+;R/SC;yy+NT ;
};*/  while (li) { if (gs_ide1026 [j]!=MAXINT) sum = gs_ide1026 [j]; if ((( li )->next) /*;
pos!= -1) gs_ide1026 [oldpos] = sum*nrn;*/ &&(gs_ide1026 [j+1]!=MAXINT)) { /*;pos!= -1) gs_ide1026 [oldpos] = sum*nrn
i] ).succlist) /+;R/SC;yy+NT ;;*/ v = (( li )->node) /*;i] ).succlist) /+;R/SC;yy+NT ;;*/ ; w = (( (( li )->next) /*;
j = 0; ;*/ )->node) /*;j = 0; ;*/ ;  if ( (touching(v,w))  && (!(( v )->dfsnum) /*;
while (li) {;*/ ) && (!(( w )->dfsnum) /*;while (li) {;*/ )) { if ( (sum>=0)&&(gs_ide1026 [j+1]>=0) /*;ide1026 [j]!=yAXINT) sum = gs_ide1026 [
ext) /+;R/SC;yy+NT &&(gs_ide1026 [j+1]!;*/ &&(sum>=gs_ide1026 [j+1])) { gs_ide1026 [j+1] = MAXINT; changed = 1; /*; v )->dfsnum) /+;R/SC;yy+NT ) && (!(( w
&(gs_ide1026 [j+1]>=0);*/  } if ( (sum<0)&&(gs_ide1026 [j+1]<0) &&(sum>=gs_ide1026 [j+1])) { gs_ide1026 [j+1] = MAXINT; /*;+1])) {
gs_ide1026 [j+1] = yAXINT;;*/ changed = 1; } if ( (sum>0)&&(gs_ide1026 [j+1]<0)) { gs_ide1026 [j+1] = MAXINT; /*;um<0)&&(gs_ide1026 [j+1]<0)
1026 [j+1])) {;*/ changed = 1; } }  } j++; li = (( li )->next) /*;1] = yAXINT;;*/ ; } } /*;} 
};*/  li = (( layer[i] ).succlist) /*;} ;*/ ; j = 0;  assert((gs_ide1026 [0]!=MAXINT)); /*;j++;
li )->next) /+;R/SC;yy+NT ;;*/ while (li) { if (gs_ide1026 [j]!=MAXINT) sum = gs_ide1009 * gs_ide1026 [j]; /*;}
};*/ gs_ide1025 [j] = sum; gs_ide1026 [j]= 1; j++; li = (( li )->next) /*;
(gs_ide1026 [0]!=yAXINT));;*/ ; } if (dir) { changed = gs_ide1007 (i); /*;gs_ide1026 [j]= 1;
j++;;*/  changed += gs_ide1006 (i); } else { changed = gs_ide1006 (i); changed += gs_ide1007 (i); /*;) {
de1007 (i);;*/ } return(changed); }
#ifdef ANSI_C
static int gs_ide1005 (int i)
#else
static int gs_ide1005 (i) int i;
#endif
{ GNLIST li; int j, k, changed; int ldiff, rdiff; int smove, pmove; GNODE v,w,oldv; /*;int i;
{;*/ int dist; ; assert((i>=0));
#ifdef DRAWDEBUG
#ifdef NEVER
PRINTF("Before correct priority nodes line %d\n", i); PRINTF("Enter CR into the text window\n"); /*;ve, pmove;
;;*/ step4_main(); debug_display_part(); fgetc(stdin);
#endif
#endif
gs_ide1040 (i); k = 5; changed = 1; while (changed) { k--; if (k<0) break; /*;fgetc(stdin);
040 (i);;*/ changed = 0; j = 0; oldv = NULL; li = (( layer[i] ).succlist) /*;) {
;*/ ; while (li) { gs_ide1025 [j] = 0; gs_ide1026 [j] = 1; v = (( li )->node) /*;
j = 0;;*/ ; rdiff = ldiff = MAXINT; if ((( li )->next) /*;i] ).succlist) /+;
R/SC;yy+NT ;;*/ ) { dist = G_xspace; if (((( v )->width) /*;025 [j] = 0;
;*/ ==0) && ((( v )->height) /*;025 [j] = 0;;*/ ==0)) dist = G_dspace; /*; = 1;
;R/SC;yy+NT ;;*/  w = (( (( li )->next) /*; = 1;;*/ )->node) /*; = 1;;*/ ; if (((( w )->width) /*;
;R/SC;yy+NT ;;*/ ==0) && ((( w )->height) /*;;R/SC;yy+NT ;;*/ ==0)) dist = G_dspace; /*;;R/SC;yy+NT ;
rdiff = ldiff = yAXINT;;*/ rdiff = (( w )->xloc) /*;rdiff = ldiff = yAXINT;;*/ - ((( v )->xloc) /*;
rdiff = ldiff = yAXINT;;*/ + (( v )->width) /*;rdiff = ldiff = yAXINT;
;*/ + dist); } if (oldv) { dist = G_xspace; if (((( v )->width) /*;C;
yy+NT )->node) /+;R/SC;yy+NT ;;*/ ==0) && ((( v )->height) /*;C;yy+NT )->node) /+;
R/SC;yy+NT ;;*/ ==0)) dist = G_dspace; w = oldv; if (((( w )->width) /*;
iff = (( w )->xloc) /+;R/SC;yy+NT - (((;*/ ==0) && ((( w )->height) /*;
iff = (( w )->xloc) /+;R/SC;yy+NT - (((;*/ ==0)) dist = G_dspace; ldiff = (( v )->xloc) /*;
};*/ - ((( w )->xloc) /*;};*/ + (( w )->width) /*;};*/ + dist); } if (gs_ide1020 (v) && gs_ide1019 (v)) { /*;e;
+;R/SC;yy+NT ==0) && ((( v )->height) /;*/ smove = gs_ide1035 (v);  pmove = gs_ide1033 (v);  if ((pmove > 0) && (smove!=0) && (pmove<=rdiff)) { /*; w )->width) /+;R/SC;yy+NT ==0) && ((( 
->xloc) /+;R/SC;yy+NT - ((( w )->xloc) ;*/ gs_ide1025 [j] = pmove; } else if ((pmove < 0) && (smove!=0) && (-pmove<=ldiff)) { /*;ide1020 (v) && gs_ide1019 (v)) {
1035 (v); ;*/ gs_ide1025 [j] = pmove; } else if ((smove > 0) && (pmove!=0) && (smove<=rdiff)) { /*;) && (pmove<=rdiff)) {
gs_ide1025 [j] = pmove;;*/ gs_ide1025 [j] = smove; } else if ((smove < 0) && (pmove!=0) && (-smove<=ldiff)) { /*; ((pmove < 0) && (smove!=0) && (-pmove<
= pmove;;*/ gs_ide1025 [j] = smove; } } else if (gs_ide1020 (v) && ((( v )->pred) /*;
= smove;;*/ ==NULL)) { smove = gs_ide1035 (v);  if ((smove > 0) && (smove<=rdiff)) { /*; ((smove < 0) && (pmove!=0) && (-smove<
= smove;;*/ gs_ide1025 [j] = smove; } else if ((smove < 0) && (-smove<=ldiff)) { /*; (gs_ide1020 (v) && ((( v )->pred) /+;R
1035 (v); ;*/  gs_ide1025 [j] = smove; } } else if (gs_ide1019 (v) && ((( v )->succ) /*;
gs_ide1025 [j] = smove;;*/ ==NULL)) { pmove = gs_ide1033 (v);  if ((pmove > 0) && (pmove<=rdiff)) { /*; ((smove < 0) && (-smove<=ldiff)) {
= smove;;*/ gs_ide1025 [j] = pmove; } else if ((pmove < 0) && (-pmove<=ldiff)) { /*; (gs_ide1019 (v) && ((( v )->succ) /+;R
1033 (v); ;*/  gs_ide1025 [j] = pmove; } } oldv = v; li = (( li )->next) /*;};*/ ; /*; ((pmove < 0) && (-pmove<=ldiff)) {
= pmove;;*/  j++; } changed += gs_ide1007 (i); changed += gs_ide1006 (i); }
#ifdef DRAWDEBUG
#ifdef NEVER
PRINTF("After correct priority nodes line %d\n", i); PRINTF("Enter CR into the text window\n"); /*;j++;
};*/ step4_main(); debug_display_part(); fgetc(stdin);
#endif
#endif
return(changed); }
#ifdef ANSI_C
static void gs_ide1048 (void)
#else
static void gs_ide1048 ()
#endif
{ int i, count; int changed; GNLIST li; ; count = 0; changed = 1; while (changed) { /*;count;
int changed;;*/ count++; gs_wait_message('S'); if (count>max_straighttune) { gs_wait_message('t'); /*; 0;
changed = 1;;*/ return; } if (G_timelimit>0) if (test_timelimit(90)) { gs_wait_message('t'); /*;straighttune) {
;*/ return;  } changed = 0; for (i=0; i<=maxdepth+1; i++) { li = (( layer[i] ).succlist) /*;
imit(90)) {;*/ ; while (li) { if (gs_ide1018 ((( li )->node) /*;return;
;*/ )) { changed += gs_ide1008 ((( li )->node) /*;};*/ ); } li = (( li )->next) /*;
axdepth+1; i++) {;*/ ; } } } }
#ifdef ANSI_C
static int gs_ide1008 (GNODE v)
#else
static int gs_ide1008 (v) GNODE v;
#endif
{ GNODE w, sw, tw, minw, maxw; ADJEDGE a; int sx, tx, sminx, smaxx, diff; /*;int gs_ide1008 (/N;D+ v)
ide1008 (v);*/ int possible, allzero, h2; int changed; ; sminx = smaxx = sx = tx = (( v )->xloc) /*;
, sw, tw, minw, maxw;;*/ + (( v )->width) /*;, sw, tw, minw, maxw;;*/ /2; /*;, sw, tw, minw, maxw;
ADJ+D/+ a;;*/ sw = tw = minw = maxw = v; w = v; while (w && (gs_ide1018 (w))) { (( layer[(( w )->tiefe) /*;
int changed;;*/ ] ).actx) /*;int changed;;*/ = (( w )->xloc) /*;int changed;
;*/ ; sw = w; sx = (( w )->xloc) /*; smaxx = sx = tx = (( v )->xloc) /+;
R/S;*/ + (( w )->width) /*; smaxx = sx = tx = (( v )->xloc) /+;R/S;*/ /2; /*; smaxx = sx = tx = (( v )->xloc) /+;R/S
= maxw = v;;*/ if (sx<sminx) { sminx = sx; minw = w; } if (sx>smaxx) { smaxx = sx; maxw = w; /*;w = v;
w && (gs_ide1018 (w))) {;*/  } a = (( w )->pred) /*;w && (gs_ide1018 (w))) {;*/ ; if (a) w = ((( (( a )->kante) /*;
)->tiefe) /+;R/SC;yy+NT ] ).actx) /+;R/;*/ )->start) /*;)->tiefe) /+;
R/SC;yy+NT ] ).actx) /+;R/;*/ ) /*;)->tiefe) /+;R/SC;yy+NT ] ).actx) /+;
R/;*/ ; else w = NULL; } w = v; while (w && (gs_ide1018 (w))) { (( layer[(( w )->tiefe) /*;
+NT ;;*/ ] ).actx) /*;+NT ;;*/ = (( w )->xloc) /*;+NT ;;*/ ; tw = w; /*;se w = NULL;
};*/  tx = (( w )->xloc) /*;se w = NULL;;*/ + (( w )->width) /*;se w = NULL;
;*/ /2; if (tx<sminx) { sminx = tx; minw = w; } if (tx>smaxx) { smaxx = tx; /*;w = v;
w && (gs_ide1018 (w))) {;*/  maxw = w; } a = (( w )->succ) /*;w && (gs_ide1018 (w))) {;*/ ; if (a) w = ((( (( a )->kante) /*;
)->tiefe) /+;R/SC;yy+NT ] ).actx) /+;R/;*/ )->end) /*;)->tiefe) /+;R/SC;
yy+NT ] ).actx) /+;R/;*/ ) /*;)->tiefe) /+;R/SC;yy+NT ] ).actx) /+;R/;
*/ ; else w = NULL; } if (sw==tw) return(0); possible = gs_ide1014 (sw, sx, 0); /*; = tx; maxw = w; }
+NT ;;*/ possible &= gs_ide1014 (sw, sx, 1); if (possible) { allzero = 1; w = sw; /*;}
=tw) return(0);;*/ while (w && (gs_ide1018 (w))) { diff = sx - (( w )->xloc) /*;ide1014 (sw, sx, 0);
;*/ - (( w )->width) /*;ide1014 (sw, sx, 0);;*/ /2; h2 = (( w )->xloc) /*;
4 (sw, sx, 1);;*/ +diff; if (diff < 0) {  if ((( w )->width) /*; = 1;
;*/ ==0)  h2 = dxlalign(h2+(( w )->width) /*;w = sw;;*/ /2)- (( w )->width) /*;
w = sw;;*/ /2; else h2 = xlalign( h2+(( w )->width) /*;w && (gs_ide1018 (w))) {
;*/ /2)- (( w )->width) /*;w && (gs_ide1018 (w))) {;*/ /2; (( w )->xloc) /*;
w )->xloc) /+;R/SC;yy+NT - (( w )->wid;*/ = h2; allzero = 0; } else if (diff > 0) { /*;w )->width) /+;R/SC;yy+NT ==0) 
h2+(( w )->width) /+;R/SC;yy+NT *2)- ((;*/ if ((( w )->width) /*;h2+(( w )->width) /+;R/SC;yy+NT *2)- ((;*/ ==0)  h2 = dxralign(h2+(( w )->width) /*;
+(( w )->width) /+;R/SC;yy+NT *2)- (( w;*/ /2)- (( w )->width) /*;+(( w )->width) /+;
R/SC;yy+NT *2)- (( w;*/ /2; else h2 = xralign( h2+(( w )->width) /*;
= h2;;*/ /2)- (( w )->width) /*;= h2;;*/ /2; (( w )->xloc) /*;allzero = 0;
;*/ = h2; allzero = 0; } a = (( w )->pred) /*;dth) /+;R/SC;yy+NT ==0) ;
*/ ; if (a) w = ((( (( a )->kante) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;
*/ )->start) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;*/ ) /*; )->width) /+;
R/SC;yy+NT *2)- (( w )->w;*/ ; else w = NULL; } w = sw; while (w && (gs_ide1018 (w))) { /*;}
w )->pred) /+;R/SC;yy+NT ;;*/ diff = sx - (( w )->xloc) /*;w )->pred) /+;R/SC;yy+NT ;;*/ - (( w )->width) /*;
w )->pred) /+;R/SC;yy+NT ;;*/ /2; h2 = (( w )->xloc) /*; (( a )->kante) /+;
R/SC;yy+NT )->start);*/ +diff; if (diff < 0) {  if ((( w )->width) /*;
};*/ ==0)  h2 = dxlalign(h2+(( w )->width) /*;;*/ /2)- (( w )->width) /*;
;*/ /2; else h2 = xlalign( h2+(( w )->width) /*;s_ide1018 (w))) {;*/ /2)- (( w )->width) /*;
s_ide1018 (w))) {;*/ /2; (( w )->xloc) /*;loc) /+;R/SC;yy+NT - (( w )->width) /+;
;*/ = h2; allzero = 0; } else if (diff > 0) { if ((( w )->width) /*;
h2+(( w )->width) /+;R/SC;yy+NT *2)- ((;*/ ==0)  h2 = dxralign(h2+(( w )->width) /*;
+(( w )->width) /+;R/SC;yy+NT *2)- (( w;*/ /2)- (( w )->width) /*;+(( w )->width) /+;
R/SC;yy+NT *2)- (( w;*/ /2; else h2 = xralign( h2+(( w )->width) /*;
= h2;;*/ /2)- (( w )->width) /*;= h2;;*/ /2; (( w )->xloc) /*;allzero = 0;
;*/ = h2; allzero = 0; } a = (( w )->succ) /*;dth) /+;R/SC;yy+NT ==0) ;
*/ ; if (a) w = ((( (( a )->kante) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;
*/ )->end) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;*/ ) /*; )->width) /+;
R/SC;yy+NT *2)- (( w )->w;*/ ; else w = NULL; } return(1-allzero); } /*;w )->succ) /+;R/SC;yy+NT ;
(( a )->kante) /+;R/SC;yy+NT )->end) /;*/  possible = gs_ide1014 (tw, tx, 0); possible &= gs_ide1014 (tw, tx, 1); /*; (( a )->kante) /+;R/SC;yy+NT )->end) /
else w = NULL;;*/ if (possible) { allzero = 1; w = tw; while (w && (gs_ide1018 (w))) { /*;e = gs_ide1014 (tw, tx, 0);
_ide1014 (tw, tx, 1);;*/  diff = tx - (( w )->xloc) /*;e = gs_ide1014 (tw, tx, 0);;*/ - (( w )->width) /*;
e = gs_ide1014 (tw, tx, 0);;*/ /2; h2 = (( w )->xloc) /*;_ide1014 (tw, tx, 1);
;*/ +diff; if (diff < 0) {  if ((( w )->width) /*; = 1;;*/ ==0)  h2 = dxlalign(h2+(( w )->width) /*;
w = tw;;*/ /2)- (( w )->width) /*;w = tw;;*/ /2; else h2 = xlalign( h2+(( w )->width) /*;
w && (gs_ide1018 (w))) {;*/ /2)- (( w )->width) /*;w && (gs_ide1018 (w))) {
;*/ /2; (( w )->xloc) /*; w )->xloc) /+;R/SC;yy+NT - (( w )->wid;*/ = h2; /*; w )->xloc) /+;R/SC;yy+NT - (( w )->wid
;R/SC;yy+NT +diff;;*/ allzero = 0; } else if (diff > 0) { if ((( w )->width) /*;h2+(( w )->width) /+;
R/SC;yy+NT *2)- ((;*/ ==0)  h2 = dxralign(h2+(( w )->width) /*;+(( w )->width) /+;
R/SC;yy+NT *2)- (( w;*/ /2)- (( w )->width) /*;+(( w )->width) /+;R/SC;
yy+NT *2)- (( w;*/ /2; else h2 = xralign( h2+(( w )->width) /*;= h2;
;*/ /2)- (( w )->width) /*;= h2;;*/ /2; (( w )->xloc) /*;allzero = 0;
;*/ = h2; allzero = 0; } a = (( w )->pred) /*;dth) /+;R/SC;yy+NT ==0) ;
*/ ; if (a) w = ((( (( a )->kante) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;
*/ )->start) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;*/ ) /*; )->width) /+;
R/SC;yy+NT *2)- (( w )->w;*/ ; else w = NULL; } w = tw; while (w && (gs_ide1018 (w))) { /*;}
w )->pred) /+;R/SC;yy+NT ;;*/ diff = tx - (( w )->xloc) /*;w )->pred) /+;R/SC;yy+NT ;;*/ - (( w )->width) /*;
w )->pred) /+;R/SC;yy+NT ;;*/ /2; h2 = (( w )->xloc) /*; (( a )->kante) /+;
R/SC;yy+NT )->start);*/ +diff; if (diff < 0) {  if ((( w )->width) /*;
};*/ ==0)  h2 = dxlalign(h2+(( w )->width) /*;;*/ /2)- (( w )->width) /*;
;*/ /2; else h2 = xlalign( h2+(( w )->width) /*;s_ide1018 (w))) {;*/ /2)- (( w )->width) /*;
s_ide1018 (w))) {;*/ /2; (( w )->xloc) /*;loc) /+;R/SC;yy+NT - (( w )->width) /+;
;*/ = h2; allzero = 0; } else if (diff > 0) { if ((( w )->width) /*;
h2+(( w )->width) /+;R/SC;yy+NT *2)- ((;*/ ==0)  h2 = dxralign(h2+(( w )->width) /*;
+(( w )->width) /+;R/SC;yy+NT *2)- (( w;*/ /2)- (( w )->width) /*;+(( w )->width) /+;
R/SC;yy+NT *2)- (( w;*/ /2; else h2 = xralign( h2+(( w )->width) /*;
= h2;;*/ /2)- (( w )->width) /*;= h2;;*/ /2; (( w )->xloc) /*;allzero = 0;
;*/ = h2; allzero = 0; } a = (( w )->succ) /*;dth) /+;R/SC;yy+NT ==0) ;
*/ ; if (a) w = ((( (( a )->kante) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;
*/ )->end) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;*/ ) /*; )->width) /+;
R/SC;yy+NT *2)- (( w )->w;*/ ; else w = NULL; } return(1-allzero); } /*;w )->succ) /+;R/SC;yy+NT ;
(( a )->kante) /+;R/SC;yy+NT )->end) /;*/  possible = gs_ide1014 (minw, sminx, 0); possible &= gs_ide1014 (minw, sminx, 1); /*; (( a )->kante) /+;R/SC;yy+NT )->end) /
else w = NULL;;*/ if (possible) { allzero = 1; w = minw; while (w && (gs_ide1018 (w))) { /*;e = gs_ide1014 (minw, sminx, 0);
_ide1014 (minw, sminx, 1);;*/  diff = sminx - (( w )->xloc) /*;e = gs_ide1014 (minw, sminx, 0);;*/ - (( w )->width) /*;
e = gs_ide1014 (minw, sminx, 0);;*/ /2; h2 = (( w )->xloc) /*;_ide1014 (minw, sminx, 1);
;*/ +diff; if (diff < 0) {  if ((( w )->width) /*; = 1;;*/ ==0)  h2 = dxlalign(h2+(( w )->width) /*;
w = minw;;*/ /2)- (( w )->width) /*;w = minw;;*/ /2; else h2 = xlalign( h2+(( w )->width) /*;
w && (gs_ide1018 (w))) {;*/ /2)- (( w )->width) /*;w && (gs_ide1018 (w))) {
;*/ /2; (( w )->xloc) /*; (( w )->xloc) /+;R/SC;yy+NT - (( w )->;*/ = h2; /*; (( w )->xloc) /+;R/SC;yy+NT - (( w )->
;R/SC;yy+NT +diff;;*/ allzero = 0; } else if (diff > 0) { if ((( w )->width) /*;h2+(( w )->width) /+;
R/SC;yy+NT *2)- ((;*/ ==0)  h2 = dxralign(h2+(( w )->width) /*;+(( w )->width) /+;
R/SC;yy+NT *2)- (( w;*/ /2)- (( w )->width) /*;+(( w )->width) /+;R/SC;
yy+NT *2)- (( w;*/ /2; else h2 = xralign( h2+(( w )->width) /*;= h2;
;*/ /2)- (( w )->width) /*;= h2;;*/ /2; (( w )->xloc) /*;allzero = 0;
;*/ = h2; allzero = 0; } a = (( w )->pred) /*;dth) /+;R/SC;yy+NT ==0) ;
*/ ; if (a) w = ((( (( a )->kante) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;
*/ )->start) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;*/ ) /*; )->width) /+;
R/SC;yy+NT *2)- (( w )->w;*/ ; else w = NULL; } w = minw; while (w && (gs_ide1018 (w))) { /*;}
w )->pred) /+;R/SC;yy+NT ;;*/ diff = sminx - (( w )->xloc) /*;w )->pred) /+;R/SC;yy+NT ;;*/ - (( w )->width) /*;
w )->pred) /+;R/SC;yy+NT ;;*/ /2; h2 = (( w )->xloc) /*; (( a )->kante) /+;
R/SC;yy+NT )->start);*/ +diff; if (diff < 0) {  if ((( w )->width) /*;
};*/ ==0)  h2 = dxlalign(h2+(( w )->width) /*;w;;*/ /2)- (( w )->width) /*;
w;;*/ /2; else h2 = xlalign( h2+(( w )->width) /*;s_ide1018 (w))) {;
*/ /2)- (( w )->width) /*;s_ide1018 (w))) {;*/ /2; (( w )->xloc) /*;
->xloc) /+;R/SC;yy+NT - (( w )->width) ;*/ = h2; allzero = 0; } else if (diff > 0) { /*;w )->width) /+;R/SC;yy+NT ==0) 
h2+(( w )->width) /+;R/SC;yy+NT *2)- ((;*/ if ((( w )->width) /*;h2+(( w )->width) /+;R/SC;yy+NT *2)- ((;*/ ==0)  h2 = dxralign(h2+(( w )->width) /*;
+(( w )->width) /+;R/SC;yy+NT *2)- (( w;*/ /2)- (( w )->width) /*;+(( w )->width) /+;
R/SC;yy+NT *2)- (( w;*/ /2; else h2 = xralign( h2+(( w )->width) /*;
= h2;;*/ /2)- (( w )->width) /*;= h2;;*/ /2; (( w )->xloc) /*;allzero = 0;
;*/ = h2; allzero = 0; } a = (( w )->succ) /*;dth) /+;R/SC;yy+NT ==0) ;
*/ ; if (a) w = ((( (( a )->kante) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;
*/ )->end) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;*/ ) /*; )->width) /+;
R/SC;yy+NT *2)- (( w )->w;*/ ; else w = NULL; } return(1-allzero); } /*;w )->succ) /+;R/SC;yy+NT ;
(( a )->kante) /+;R/SC;yy+NT )->end) /;*/  possible = gs_ide1014 (maxw, smaxx, 0); possible &= gs_ide1014 (maxw, smaxx, 1); /*; (( a )->kante) /+;R/SC;yy+NT )->end) /
else w = NULL;;*/ if (possible) { allzero = 1; w = maxw; while (w && (gs_ide1018 (w))) { /*;e = gs_ide1014 (maxw, smaxx, 0);
_ide1014 (maxw, smaxx, 1);;*/  diff = smaxx - (( w )->xloc) /*;e = gs_ide1014 (maxw, smaxx, 0);;*/ - (( w )->width) /*;
e = gs_ide1014 (maxw, smaxx, 0);;*/ /2; h2 = (( w )->xloc) /*;_ide1014 (maxw, smaxx, 1);
;*/ +diff; if (diff < 0) {  if ((( w )->width) /*; = 1;;*/ ==0)  h2 = dxlalign(h2+(( w )->width) /*;
w = maxw;;*/ /2)- (( w )->width) /*;w = maxw;;*/ /2; else h2 = xlalign( h2+(( w )->width) /*;
w && (gs_ide1018 (w))) {;*/ /2)- (( w )->width) /*;w && (gs_ide1018 (w))) {
;*/ /2; (( w )->xloc) /*; (( w )->xloc) /+;R/SC;yy+NT - (( w )->;*/ = h2; /*; (( w )->xloc) /+;R/SC;yy+NT - (( w )->
;R/SC;yy+NT +diff;;*/ allzero = 0; } else if (diff > 0) { if ((( w )->width) /*;h2+(( w )->width) /+;
R/SC;yy+NT *2)- ((;*/ ==0)  h2 = dxralign(h2+(( w )->width) /*;+(( w )->width) /+;
R/SC;yy+NT *2)- (( w;*/ /2)- (( w )->width) /*;+(( w )->width) /+;R/SC;
yy+NT *2)- (( w;*/ /2; else h2 = xralign( h2+(( w )->width) /*;= h2;
;*/ /2)- (( w )->width) /*;= h2;;*/ /2; (( w )->xloc) /*;allzero = 0;
;*/ = h2; allzero = 0; } a = (( w )->pred) /*;dth) /+;R/SC;yy+NT ==0) ;
*/ ; if (a) w = ((( (( a )->kante) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;
*/ )->start) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;*/ ) /*; )->width) /+;
R/SC;yy+NT *2)- (( w )->w;*/ ; else w = NULL; } w = maxw; while (w && (gs_ide1018 (w))) { /*;}
w )->pred) /+;R/SC;yy+NT ;;*/ diff = smaxx - (( w )->xloc) /*;w )->pred) /+;R/SC;yy+NT ;;*/ - (( w )->width) /*;
w )->pred) /+;R/SC;yy+NT ;;*/ /2; h2 = (( w )->xloc) /*; (( a )->kante) /+;
R/SC;yy+NT )->start);*/ +diff; if (diff < 0) {  if ((( w )->width) /*;
};*/ ==0)  h2 = dxlalign(h2+(( w )->width) /*;w;;*/ /2)- (( w )->width) /*;
w;;*/ /2; else h2 = xlalign( h2+(( w )->width) /*;s_ide1018 (w))) {;
*/ /2)- (( w )->width) /*;s_ide1018 (w))) {;*/ /2; (( w )->xloc) /*;
->xloc) /+;R/SC;yy+NT - (( w )->width) ;*/ = h2; allzero = 0; } else if (diff > 0) { /*;w )->width) /+;R/SC;yy+NT ==0) 
h2+(( w )->width) /+;R/SC;yy+NT *2)- ((;*/ if ((( w )->width) /*;h2+(( w )->width) /+;R/SC;yy+NT *2)- ((;*/ ==0)  h2 = dxralign(h2+(( w )->width) /*;
+(( w )->width) /+;R/SC;yy+NT *2)- (( w;*/ /2)- (( w )->width) /*;+(( w )->width) /+;
R/SC;yy+NT *2)- (( w;*/ /2; else h2 = xralign( h2+(( w )->width) /*;
= h2;;*/ /2)- (( w )->width) /*;= h2;;*/ /2; (( w )->xloc) /*;allzero = 0;
;*/ = h2; allzero = 0; } a = (( w )->succ) /*;dth) /+;R/SC;yy+NT ==0) ;
*/ ; if (a) w = ((( (( a )->kante) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;
*/ )->end) /*; )->width) /+;R/SC;yy+NT *2)- (( w )->w;*/ ) /*; )->width) /+;
R/SC;yy+NT *2)- (( w )->w;*/ ; else w = NULL; } return(1-allzero); } /*;w )->succ) /+;R/SC;yy+NT ;
(( a )->kante) /+;R/SC;yy+NT )->end) /;*/  gs_ide1049 (minw, sminx, 0); gs_ide1049 (minw, sminx, 1); gs_ide1049 (maxw, smaxx, 0); /*;else w = NULL;
};*/ gs_ide1049 (maxw, smaxx, 1); gs_ide1049 (tw, tx, 0); gs_ide1049 (tw, tx, 1); /*;}
049 (minw, sminx, 0);;*/ gs_ide1049 (sw, sx, 0); gs_ide1049 (sw, sx, 1); changed = 0; w = v; while (w && (gs_ide1018 (w))) { /*;gs_ide1049 (tw, tx, 0);
049 (tw, tx, 1);;*/ if ((( layer[(( w )->tiefe) /*;049 (tw, tx, 1);;*/ ] ).actx) /*;049 (tw, tx, 1);
;*/ != (( w )->xloc) /*;049 (tw, tx, 1);;*/ ) changed = 1; a = (( w )->pred) /*;
, sx, 0);;*/ ; if (a) w = ((( (( a )->kante) /*;);;*/ )->start) /*;);
;*/ ) /*;);;*/ ; else w = NULL; } w = v; while (w && (gs_ide1018 (w))) { /*;( w )->tiefe) /+;R/SC;yy+NT ] ).actx) /
R/SC;yy+NT ;;*/ if ((( layer[(( w )->tiefe) /*;R/SC;yy+NT ;;*/ ] ).actx) /*;R/SC;yy+NT ;
;*/ != (( w )->xloc) /*;R/SC;yy+NT ;;*/ ) changed = 1; a = (( w )->succ) /*;
) /+;R/SC;yy+NT )->start) /+;R/SC;yy+NT;*/ ; if (a) w = ((( (( a )->kante) /*;
else w = NULL;;*/ )->end) /*;else w = NULL;;*/ ) /*;else w = NULL;;*/ ; /*;else w = NULL;
};*/ else w = NULL; } return(changed); }
#ifdef ANSI_C
static int gs_ide1014 (GNODE sw, int sxpos, int dir)
#else
static int gs_ide1014 (sw, sxpos, dir) GNODE sw; int sxpos; int dir;
#endif
{ GNODE w, gs_ide1030 ; GNLIST li; ADJEDGE a; int diff; int sxpos_possible, h1, h2; /*;int dir;
{;*/ ; sxpos_possible = 1; w = sw; while (w && (gs_ide1018 (w))) { if (!sxpos_possible) break; /*;int diff;
os_possible, h1, h2;;*/ diff = sxpos - (( w )->xloc) /*;os_possible, h1, h2;;*/ - (( w )->width) /*;
os_possible, h1, h2;;*/ /2; h2 = (( w )->xloc) /*;;;*/ +diff; if (diff < 0) li = (( layer[(( w )->tiefe) /*;
ossible = 1;;*/ ] ).predlist) /*;ossible = 1;;*/ ; else li = (( layer[(( w )->tiefe) /*;
w = sw;;*/ ] ).succlist) /*;w = sw;;*/ ; while (li) { if ((( li )->node) /*;
sible) break;;*/ ==w) break; li = (( li )->next) /*;->xloc) /+;R/SC;
yy+NT - (( w )->width) ;*/ ; } assert((li)); li = (( li )->next) /*;
se li = (( layer[(( w )->tiefe) /+;R/SC;*/ ; if (diff < 0) {  if (li) { /*;e) /+;R/SC;yy+NT ==w) break;
R/SC;yy+NT ;;*/  gs_ide1030 = (( li )->node) /*;e) /+;R/SC;yy+NT ==w) break;;*/ ; if (((( w )->width) /*;
R/SC;yy+NT ;;*/ ==0)||((( gs_ide1030 )->width) /*;R/SC;yy+NT ;;*/ ==0))  /*;R/SC;yy+NT ;
};*/ h1 = (( gs_ide1030 )->xloc) /*;};*/ + (( gs_ide1030 )->width) /*;};*/ + G_dspace; /*;}
(li));;*/ else h1 = (( gs_ide1030 )->xloc) /*;(li));;*/ + (( gs_ide1030 )->width) /*;
(li));;*/ + G_xspace; if ((( w )->width) /*;next) /+;R/SC;yy+NT ;;*/ ==0)  /*;next) /+;R/SC;yy+NT ;
if (diff < 0) { ;*/ h2 = dxlalign(h2+(( w )->width) /*;if (diff < 0) { ;*/ /2)- (( w )->width) /*;
if (diff < 0) { ;*/ /2; else h2 = xlalign( h2+(( w )->width) /*; { gs_ide1030 = (( li )->node) /+;
R/SC;;*/ /2)- (( w )->width) /*; { gs_ide1030 = (( li )->node) /+;R/SC;
;*/ /2; if (h2<h1) sxpos_possible = 0; } } else if (diff > 0) { if (li) { /*; = dxlalign(h2+(( w )->width) /+;R/SC;y
xlalign( h2+(( w )->width) /+;R/SC;yy+;*/  gs_ide1030 = (( li )->node) /*; = dxlalign(h2+(( w )->width) /+;R/SC;
y;*/ ; if (((( w )->width) /*; xlalign( h2+(( w )->width) /+;R/SC;yy+;
*/ ==0)||((( gs_ide1030 )->width) /*; xlalign( h2+(( w )->width) /+;
R/SC;yy+;*/ ==0))  h1 = (( gs_ide1030 )->xloc) /*;_possible = 0;;*/ - G_dspace - (( w )->width) /*;
_possible = 0;;*/ ; else h1 = (( gs_ide1030 )->xloc) /*;};*/ - G_xspace - (( w )->width) /*;
};*/ ; if ((( w )->width) /*;};*/ ==0)  h2 = dxralign(h2+(( w )->width) /*;
(diff > 0) {;*/ /2)- (( w )->width) /*; (diff > 0) {;*/ /2; else h2 = xralign( h2+(( w )->width) /*;
de1030 = (( li )->node) /+;R/SC;yy+NT ;;*/ /2)- (( w )->width) /*;de1030 = (( li )->node) /+;
R/SC;yy+NT ;;*/ /2; if (h2>h1) sxpos_possible = 0; } } if (dir) { a = (( w )->pred) /*;
lign(h2+(( w )->width) /+;R/SC;yy+NT *2;*/ ; if (a) w = ((( (( a )->kante) /*;
n( h2+(( w )->width) /+;R/SC;yy+NT *2)-;*/ )->start) /*;n( h2+(( w )->width) /+;
R/SC;yy+NT *2)-;*/ ) /*;n( h2+(( w )->width) /+;R/SC;yy+NT *2)-;*/ ; /*;le = 0;
};*/  else w = NULL; } else { a = (( w )->succ) /*;};*/ ; if (a) w = ((( (( a )->kante) /*;
) {;*/ )->end) /*;) {;*/ ) /*;) {;*/ ; else w = NULL; } } return(sxpos_possible); /*;}
a = (( w )->succ) /+;R/SC;yy+NT ;;*/ }
#ifdef ANSI_C
static void gs_ide1049 (GNODE sw, int sxpos, int dir)
#else
static void gs_ide1049 (sw, sxpos, dir) GNODE sw; int sxpos; int dir;
#endif
{ GNODE w, gs_ide1030 ; GNLIST li; ADJEDGE a; int diff; int sxpos_possible, h1, h2; /*;int dir;
{;*/ ; sxpos_possible = 1; w = sw; while (w && (gs_ide1018 (w))) { if (!sxpos_possible) break; /*;int diff;
os_possible, h1, h2;;*/ diff = sxpos - (( w )->xloc) /*;os_possible, h1, h2;;*/ - (( w )->width) /*;
os_possible, h1, h2;;*/ /2; h2 = (( w )->xloc) /*;;;*/ +diff; if (diff < 0) li = (( layer[(( w )->tiefe) /*;
ossible = 1;;*/ ] ).predlist) /*;ossible = 1;;*/ ; else li = (( layer[(( w )->tiefe) /*;
w = sw;;*/ ] ).succlist) /*;w = sw;;*/ ; while (li) { if ((( li )->node) /*;
sible) break;;*/ ==w) break; li = (( li )->next) /*;->xloc) /+;R/SC;
yy+NT - (( w )->width) ;*/ ; } assert((li)); li = (( li )->next) /*;
se li = (( layer[(( w )->tiefe) /+;R/SC;*/ ; if (diff < 0) { if ((( w )->width) /*;
e) /+;R/SC;yy+NT ==w) break;;*/ ==0)  h2 = dxlalign(h2); else h2 = xlalign( h2+(( w )->width) /*;
};*/ /2)- (( w )->width) /*;};*/ /2; if (!li) { (( w )->xloc) /*;(li));
;*/ = h2; }  else { gs_ide1030 = (( li )->node) /*;next) /+;R/SC;yy+NT ;
;*/ ; if (((( w )->width) /*;if (diff < 0) {;*/ ==0)||((( gs_ide1030 )->width) /*;
if (diff < 0) {;*/ ==0))  h1 = (( gs_ide1030 )->xloc) /*;w )->width) /+;
R/SC;yy+NT ==0) ;*/ + (( gs_ide1030 )->width) /*;w )->width) /+;R/SC;
yy+NT ==0) ;*/ + G_dspace; else h1 = (( gs_ide1030 )->xloc) /*;h2);;
*/ + (( gs_ide1030 )->width) /*;h2);;*/ + G_xspace; if (h2>=h1) { (( w )->xloc) /*;
+(( w )->width) /+;R/SC;yy+NT *2)- (( w;*/ = h2; } else sxpos_possible = 0; /*;R/SC;yy+NT = h2; } 
/+;R/SC;yy+NT ;;*/ } } else if (diff > 0) { if ((( w )->width) /*;ide1030 )->xloc) /+;R/SC;
yy+NT + (( gs_;*/ ==0)  h2 = dxralign(h2); else h2 = xralign( h2+(( w )->width) /*;
else sxpos_possible = 0;;*/ /2)- (( w )->width) /*;else sxpos_possible = 0;
;*/ /2; if (!li) { (( w )->xloc) /*;};*/ = h2; }  else { gs_ide1030 = (( li )->node) /*;
};*/ ; if (((( w )->width) /*; (diff > 0) {;*/ ==0)||((( gs_ide1030 )->width) /*;
(diff > 0) {;*/ ==0))  h1 = (( gs_ide1030 )->xloc) /*;dth) /+;R/SC;
yy+NT ==0) ;*/ - G_dspace - (( w )->width) /*;dth) /+;R/SC;yy+NT ==0) ;
*/ ; else h1 = (( gs_ide1030 )->xloc) /*;h2 = dxralign(h2);;*/ - G_xspace - (( w )->width) /*;
h2 = dxralign(h2);;*/ ; if (h2<=h1) { (( w )->xloc) /*; = xralign( h2+(( w )->width) /+;
R/SC;y;*/ = h2; } else sxpos_possible = 0; } } if (dir) { a = (( w )->pred) /*;
se h1 = (( gs_ide1030 )->xloc) /+;R/SC;;*/ ; if (a) w = ((( (( a )->kante) /*;
1) { (( w )->xloc) /+;R/SC;yy+NT = h2; ;*/ )->start) /*;1) { (( w )->xloc) /+;
R/SC;yy+NT = h2; ;*/ ) /*;1) { (( w )->xloc) /+;R/SC;yy+NT = h2; ;*/ ; /*;ble = 0;
};*/  else w = NULL; } else { a = (( w )->succ) /*;};*/ ; if (a) w = ((( (( a )->kante) /*;
) {;*/ )->end) /*;) {;*/ ) /*;) {;*/ ; else w = NULL; } } }
#ifdef ANSI_C
static void gs_ide1021 (void)
#else
static void gs_ide1021 ()
#endif
{ int i,count; int weight,h; int second_try; ; if (prio_phase==1) return; /*;_ide1021 ()
{;*/ weight = gs_ide1002 (); second_try = 2; count=0; while (1) { if (count%5==0) gs_wait_message('c'); /*;;
o_phase==1) return;;*/ count++; if (count>=max_centershifts) {  gs_wait_message('t'); break; /*;while (1) {
nt%5==0) gs_wait_message('c');;*/   } if (G_timelimit>0) if (test_timelimit(90)) { gs_wait_message('t'); /*;e('t');
break; ;*/  break; } for (i=0; i<=maxdepth+1; i++) gs_ide1000 (i); for (i=maxdepth+1; /*;imelimit>0)
imit(90)) {;*/  i>=0; i--) gs_ide1000 (i); h = gs_ide1002 (); drawdebug_show_graph("centershift",count,h,weight); /*;
break;;*/ if (count>=min_centershifts) { if (h<weight) { weight = h; second_try = 2; /*;h+1; i>=0; i--) gs_ide1000 (i);
h = gs_ide1002 ();;*/ } else if (h==weight) { second_try--; if (second_try<=0) break;  } else break; /*;;
};*/   } } }
#ifdef ANSI_C
static int gs_ide1002 (void)
#else
static int gs_ide1002 ()
#endif
{ int i; GNLIST li; ADJEDGE a; int weight,h; ; weight = 0; for (i=0; /*;int i;
li;;*/  i<=maxdepth+1; i++) { li = (( layer[i] ).succlist) /*;li;;*/ ; while (li) { /*;ADJ+D/+ a;
ght,h;;*/ h = 0; a = (( (( li )->node) /*;;;*/ )->succ) /*;;;*/ ; while (a) { h += gs_ide1012 ((( a )->kante) /*;
axdepth+1; i++) {;*/ ); a = (( a )->next) /*;cclist) /+;R/SC;yy+NT ;
;*/ ; } a = (( (( li )->node) /*;h = 0;;*/ )->pred) /*;h = 0;;*/ ; while (a) { /*;(( li )->node) /+;R/SC;yy+NT )->succ) /
while (a) {;*/ h += gs_ide1011 ((( a )->kante) /*;while (a) {;*/ ); a = (( a )->next) /*;
_ide1012 ((( a )->kante) /+;R/SC;yy+NT ;*/ ; } if (h<0) h = -h;  weight += h; /*;(( li )->node) /+;R/SC;yy+NT )->pred) /
while (a) {;*/ li = (( li )->next) /*;while (a) {;*/ ; } } return(weight); }
#ifdef ANSI_C
static int gs_ide1000 (int i)
#else
static int gs_ide1000 (i) int i;
#endif
{ GNLIST li, li1; int j; int changed; int dir; GNODE lnode, node, rnode; /*;int i;
{;*/ ; gs_ide1040 (i); li = (( layer[i] ).succlist) /*;int j;;*/ ; j = 0; /*;int dir;
node, node, rnode;;*/   dir = 0; lnode = NULL; while (li) { node = (( li )->node) /*;040 (i);
;*/ ; if ((( node )->width) /*;i] ).succlist) /+;R/SC;yy+NT ;;*/ ==0) { /*;i] ).succlist) /+;R/SC;yy+NT ;
j = 0; ;*/ li1 = (( li )->next) /*;j = 0; ;*/ ; rnode = NULL; while (li1) { if ((( (( li1 )->node) /*;
li) {;*/ )->width) /*;li) {;*/ !=0) { rnode = (( li1 )->node) /*;->node) /+;
R/SC;yy+NT ;;*/ ; break; }  li1 = (( li1 )->next) /*;rnode = NULL;;*/ ; /*;rnode = NULL;
li1) {;*/ } gs_ide1025 [j] = gs_ide1031 (node,lnode,rnode); } else { gs_ide1025 [j] = gs_ide1030 (node); /*;break;
} ;*/ lnode = node; } dir += gs_ide1025 [j]; gs_ide1026 [j++]= 1; li = (( li )->next) /*;
};*/ ; } if (dir>=0) { changed = gs_ide1007 (i); changed += gs_ide1006 (i); /*;gs_ide1025 [j];
+]= 1;;*/ } else { changed = gs_ide1006 (i); changed += gs_ide1007 (i); } return(changed); /*; (i);
};*/ }
#ifdef ANSI_C
static int gs_ide1006 (int i)
#else
static int gs_ide1006 (i) int i;
#endif
{ int j; int diff; int oldx; GNODE node,lnode; int changed; assert((i>=0) && (i<=maxdepth+1)); /*;{
int j;;*/ lnode = NULL; for (j=0; j<(( layer[i] ).anz) /*;f;;*/ ; j++) { if (gs_ide1026 [j]) diff = gs_ide1025 [j]/gs_ide1026 [j]; /*;int oldx;
ode,lnode;;*/ else diff = 0; node = gs_ide1047 [j]; if (diff<0) { oldx = (( node )->xloc) /*;
lnode = NULL;;*/ ; (( node )->xloc) /*;0; j<(( layer[i] ).anz) /+;R/SC;
yy+NT ;;*/ = oldx + diff; if (lnode) {  if (((( node )->width) /*;else diff = 0;
;*/ ==0)||((( lnode )->width) /*;else diff = 0;;*/ ==0)) { if ((( node )->xloc) /*;
gs_ide1047 [j];;*/ <(( lnode )->xloc) /*;gs_ide1047 [j];;*/  +(( lnode )->width) /*;
if (diff<0) {;*/ +G_dspace) (( node )->xloc) /*;(( node )->xloc) /+;
R/SC;yy+NT ;;*/ = (( lnode )->xloc) /*;(( node )->xloc) /+;R/SC;yy+NT ;
;*/  +(( lnode )->width) /*;c) /+;R/SC;yy+NT = oldx + diff;;*/ +G_dspace; /*;c) /+;R/SC;yy+NT = oldx + diff;
if (lnode) { ;*/ } else { if ((( node )->xloc) /*;>xloc) /+;R/SC;yy+NT <(( lnode )->xloc);
*/ <(( lnode )->xloc) /*;>xloc) /+;R/SC;yy+NT <(( lnode )->xloc);*/  +(( lnode )->width) /*;
+;R/SC;yy+NT +/_dspace);*/ +G_xspace) (( node )->xloc) /*;NT = (( lnode )->xloc) /+;
R/SC;yy+NT ;*/ = (( lnode )->xloc) /*;NT = (( lnode )->xloc) /+;R/SC;
yy+NT ;*/  +(( lnode )->width) /*;/_dspace;;*/ +G_xspace; } } if (((( node )->width) /*;
node )->xloc) /+;R/SC;yy+NT <(( lnode );*/ ==0)&&((( node )->height) /*;
node )->xloc) /+;R/SC;yy+NT <(( lnode );*/ ==0)) (( node )->xloc) /*;
idth) /+;R/SC;yy+NT +/_xspace);*/ = dxralign((( node )->xloc) /*;idth) /+;
R/SC;yy+NT +/_xspace);*/ +(( node )->width) /*;idth) /+;R/SC;yy+NT +/_xspace);
*/ /2) - (( node )->width) /*;/SC;yy+NT = (( lnode )->xloc) /+;R/SC;
y;*/ /2; else (( node )->xloc) /*;yy+NT +/_xspace;;*/ = xralign((( node )->xloc) /*;
yy+NT +/_xspace;;*/ +(( node )->width) /*;yy+NT +/_xspace;;*/ /2) - (( node )->width) /*;
};*/ /2; if ((( node )->xloc) /*;};*/ <oldx) changed = 1; } lnode = node; /*;c) /+;R/SC;yy+NT = dxralign((( node )->
+;R/SC;yy+NT *2;;*/ } return(changed); }
#ifdef ANSI_C
static int gs_ide1007 (int i)
#else
static int gs_ide1007 (i) int i;
#endif
{ int j; int diff; int oldx; GNODE node,rnode; int changed; assert((i>=0) && (i<=maxdepth+1)); /*;{
int j;;*/ rnode = NULL; changed = 0; for (j=(( layer[i] ).anz) /*;int oldx;;*/ -1; /*;int oldx;
ode,rnode;;*/  j>=0; j--) { if (gs_ide1026 [j]) diff = gs_ide1025 [j]/gs_ide1026 [j]; /*;ode,rnode;
int changed;;*/ else diff = 0; node = gs_ide1047 [j]; if (diff>0) { oldx = (( node )->xloc) /*;
= 0;;*/ ; (( node )->xloc) /*;r[i] ).anz) /+;R/SC;yy+NT -1; j>=0; j--;
*/ = oldx + diff; if (rnode) {  if (((( node )->width) /*;else diff = 0;
;*/ ==0)||((( rnode )->width) /*;else diff = 0;;*/ ==0)) { if ((( node )->xloc) /*;
gs_ide1047 [j];;*/ +(( node )->width) /*;gs_ide1047 [j];;*/ +G_dspace >(( rnode )->xloc) /*;
if (diff>0) {;*/ ) (( node )->xloc) /*;(( node )->xloc) /+;R/SC;yy+NT ;
;*/ = (( rnode )->xloc) /*;(( node )->xloc) /+;R/SC;yy+NT ;;*/  - (( node )->width) /*;
c) /+;R/SC;yy+NT = oldx + diff;;*/ -G_dspace; } else { if ((( node )->xloc) /*;
>xloc) /+;R/SC;yy+NT +(( node )->width);*/ +(( node )->width) /*;>xloc) /+;
R/SC;yy+NT +(( node )->width);*/ +G_xspace >(( rnode )->xloc) /*;;R/SC;
yy+NT );*/ ) (( node )->xloc) /*;NT = (( rnode )->xloc) /+;R/SC;yy+NT ;
*/ = (( rnode )->xloc) /*;NT = (( rnode )->xloc) /+;R/SC;yy+NT ;*/  - (( node )->width) /*;
/_dspace;;*/ -G_xspace; } } if (((( node )->width) /*;node )->xloc) /+;
R/SC;yy+NT +(( node )-;*/ ==0)&&((( node )->height) /*;node )->xloc) /+;
R/SC;yy+NT +(( node )-;*/ ==0)) (( node )->xloc) /*;loc) /+;R/SC;yy+NT );
*/ = dxlalign((( node )->xloc) /*;loc) /+;R/SC;yy+NT );*/ +(( node )->width) /*;
loc) /+;R/SC;yy+NT );*/ /2) - (( node )->width) /*;/SC;yy+NT = (( rnode )->xloc) /+;
R/SC;y;*/ /2; else (( node )->xloc) /*;yy+NT -/_xspace;;*/ = xlalign((( node )->xloc) /*;
yy+NT -/_xspace;;*/ +(( node )->width) /*;yy+NT -/_xspace;;*/ /2) - (( node )->width) /*;
};*/ /2; if ((( node )->xloc) /*;};*/ >oldx) changed = 1; } rnode = node; /*;c) /+;R/SC;yy+NT = dxlalign((( node )->
+;R/SC;yy+NT *2;;*/ } return(changed); }
#ifdef ANSI_C
static int gs_ide1012 (GEDGE edge)
#else
static int gs_ide1012 (edge) GEDGE edge;
#endif
{ GNODE start, ende; int x1,x2; start = (( edge )->start) /*;int gs_ide1012 (/+D/+ edge);
*/ ; ende = (( edge )->end) /*;ide1012 (edge);*/ ;  x1 = (( ende )->xloc) /*;
/+D/+ edge;;*/ + ((( ende )->width) /*;/+D/+ edge;;*/ *(( edge )->weightp) /*;
/+D/+ edge;;*/ /((( ende )->weightp) /*;/+D/+ edge;;*/ +1)); x2 = (( start )->xloc) /*;
{;*/ + ((( start )->width) /*;{;*/ *(( edge )->weights) /*;{;*/ /((( start )->weights) /*;
{;*/ +1)); return(x1-x2); }
#ifdef ANSI_C
static int gs_ide1011 (GEDGE edge)
#else
static int gs_ide1011 (edge) GEDGE edge;
#endif
{ GNODE start, ende; int x1,x2; ende = (( edge )->end) /*;int gs_ide1011 (/+D/+ edge);
*/ ; start = (( edge )->start) /*;ide1011 (edge);*/ ; x1 = (( ende )->xloc) /*;
/+D/+ edge;;*/ + ((( ende )->width) /*;/+D/+ edge;;*/ *(( edge )->weightp) /*;
/+D/+ edge;;*/ /((( ende )->weightp) /*;/+D/+ edge;;*/ +1)); x2 = (( start )->xloc) /*;
{;*/ + ((( start )->width) /*;{;*/ *(( edge )->weights) /*;{;*/ /((( start )->weights) /*;
{;*/ +1)); return(x2-x1); }
#ifdef ANSI_C
static int gs_ide1035 (GNODE node)
#else
static int gs_ide1035 (node) GNODE node;
#endif
{ int h; int weight; int nr_edges; ADJEDGE a; CONNECT c; a = (( node )->succ) /*;
{;*/ ; weight = 0;  nr_edges = 0; while (a) { h = ((( (( a )->kante) /*;
a;;*/ )->priority) /*; a;;*/ *layout_downfactor) * gs_ide1012 ((( a )->kante) /*;
a;;*/ ); weight += h; nr_edges += ((( (( a )->kante) /*;node )->succ) /+;
R/SC;yy+NT ;;*/ )->priority) /*;node )->succ) /+;R/SC;yy+NT ;;*/ *layout_downfactor); /*;node )->succ) /+;R/SC;yy+NT ;
weight = 0; ;*/ a = (( a )->next) /*;weight = 0; ;*/ ; } c = (( node )->connection) /*;
while (a) {;*/ ; if (c) { if ((( c )->target) /*;weight += h;;*/ ) { /*;s += ((( (( a )->kante) /+;R/SC;yy+NT )
xt) /+;R/SC;yy+NT ;;*/  if ((( (( c )->target) /*;s += ((( (( a )->kante) /+;R/SC;yy+NT );*/ )->xloc) /*;
s += ((( (( a )->kante) /+;R/SC;yy+NT );*/ <(( node )->xloc) /*;s += ((( (( a )->kante) /+;
R/SC;yy+NT );*/ ) weight -= ((( (( c )->edge) /*;xt) /+;R/SC;yy+NT ;
;*/ )->priority) /*;xt) /+;R/SC;yy+NT ;;*/ *layout_nearfactor * ((( node )->xloc) /*;
};*/ - ((( (( c )->target) /*;};*/ )->xloc) /*;};*/  +(( (( c )->target) /*;
node )->connection) /+;R/SC;yy+NT ;;*/ )->width) /*;node )->connection) /+;
R/SC;yy+NT ;;*/ +G_xspace))); else weight += ((( (( c )->edge) /*;if (c) {
;*/ )->priority) /*;if (c) {;*/ *layout_nearfactor * ((( (( c )->target) /*;
c )->target) /+;R/SC;yy+NT ) {;*/ )->xloc) /*;c )->target) /+;R/SC;yy+NT ) {
;*/ - ((( node )->xloc) /*;c )->target) /+;R/SC;yy+NT ) {;*/  +(( node )->width) /*;
>target) /+;R/SC;yy+NT )->xloc) /+;R/SC;*/ +G_xspace)));  nr_edges += ((( (( c )->edge) /*;
>edge) /+;R/SC;yy+NT )->priority) /+;R/;*/ )->priority) /*;>edge) /+;
R/SC;yy+NT )->priority) /+;R/;*/ *layout_nearfactor); } if ((( c )->target2) /*;
->width) /+;R/SC;yy+NT +/_xspace)));;*/ ) { if ((( (( c )->target2) /*;
se weight += ((( (( c )->edge) /+;R/SC;;*/ )->xloc) /*;se weight += ((( (( c )->edge) /+;
R/SC;;*/ <(( node )->xloc) /*;se weight += ((( (( c )->edge) /+;R/SC;
;*/ ) weight -= ((( (( c )->edge2) /*;)->target) /+;R/SC;yy+NT )->xloc) /+;
R/;*/ )->priority) /*;)->target) /+;R/SC;yy+NT )->xloc) /+;R/;*/ *layout_nearfactor * /*;)->target) /+;R/SC;yy+NT )->xloc) /+;R/
h) /+;R/SC;yy+NT +/_xspace))); ;*/ ((( node )->xloc) /*;h) /+;R/SC;yy+NT +/_xspace))); ;*/ - ((( (( c )->target2) /*;
h) /+;R/SC;yy+NT +/_xspace))); ;*/ )->xloc) /*;h) /+;R/SC;yy+NT +/_xspace)));
;*/  +(( (( c )->target2) /*;>edge) /+;R/SC;yy+NT )->priority) /+;R/;
*/ )->width) /*;>edge) /+;R/SC;yy+NT )->priority) /+;R/;*/ +G_xspace))); /*;>edge) /+;R/SC;yy+NT )->priority) /+;R/
};*/ else weight += ((( (( c )->edge2) /*;};*/ )->priority) /*;};*/ *layout_nearfactor * /*;}
c )->target2) /+;R/SC;yy+NT ) {;*/ ((( (( c )->target2) /*;c )->target2) /+;R/SC;yy+NT ) {;*/ )->xloc) /*;
c )->target2) /+;R/SC;yy+NT ) {;*/ - ((( node )->xloc) /*;c )->target2) /+;
R/SC;yy+NT ) {;*/  +(( node )->width) /*;>target2) /+;R/SC;yy+NT )->xloc) /+;
R/S;*/ +G_xspace)));  nr_edges += ((( (( c )->edge2) /*;>edge2) /+;R/SC;
yy+NT )->priority) /+;R;*/ )->priority) /*;>edge2) /+;R/SC;yy+NT )->priority) /+;
R;*/ *layout_nearfactor); } } if (nr_edges) return(weight/nr_edges); /*;)->target2) /+;R/SC;yy+NT )->xloc) /+;R
h) /+;R/SC;yy+NT +/_xspace))); ;*/  else return(0); }
#ifdef ANSI_C
static int gs_ide1033 (GNODE node)
#else
static int gs_ide1033 (node) GNODE node;
#endif
{ int h; int weight; int nr_edges; ADJEDGE a; CONNECT c; a = (( node )->pred) /*;
{;*/ ; weight = 0;  nr_edges = 0; while (a) { h = ((( (( a )->kante) /*;
a;;*/ )->priority) /*; a;;*/ *layout_upfactor) * gs_ide1011 ((( a )->kante) /*;
a;;*/ ); weight += h; nr_edges += ((( (( a )->kante) /*;node )->pred) /+;
R/SC;yy+NT ;;*/ )->priority) /*;node )->pred) /+;R/SC;yy+NT ;;*/ *layout_upfactor); /*;node )->pred) /+;R/SC;yy+NT ;
weight = 0; ;*/ a = (( a )->next) /*;weight = 0; ;*/ ; } c = (( node )->connection) /*;
while (a) {;*/ ; if (c) { if ((( c )->target) /*;weight += h;;*/ ) { /*;s += ((( (( a )->kante) /+;R/SC;yy+NT )
xt) /+;R/SC;yy+NT ;;*/  if ((( (( c )->target) /*;s += ((( (( a )->kante) /+;R/SC;yy+NT );*/ )->xloc) /*;
s += ((( (( a )->kante) /+;R/SC;yy+NT );*/ <(( node )->xloc) /*;s += ((( (( a )->kante) /+;
R/SC;yy+NT );*/ ) weight -= ((( (( c )->edge) /*;xt) /+;R/SC;yy+NT ;
;*/ )->priority) /*;xt) /+;R/SC;yy+NT ;;*/ *layout_nearfactor * ((( node )->xloc) /*;
};*/ - ((( (( c )->target) /*;};*/ )->xloc) /*;};*/  +(( (( c )->target) /*;
node )->connection) /+;R/SC;yy+NT ;;*/ )->width) /*;node )->connection) /+;
R/SC;yy+NT ;;*/ +G_xspace))); else weight += ((( (( c )->edge) /*;if (c) {
;*/ )->priority) /*;if (c) {;*/ *layout_nearfactor * ((( (( c )->target) /*;
c )->target) /+;R/SC;yy+NT ) {;*/ )->xloc) /*;c )->target) /+;R/SC;yy+NT ) {
;*/ - ((( node )->xloc) /*;c )->target) /+;R/SC;yy+NT ) {;*/  +(( node )->width) /*;
>target) /+;R/SC;yy+NT )->xloc) /+;R/SC;*/ +G_xspace)));  nr_edges += ((( (( c )->edge) /*;
>edge) /+;R/SC;yy+NT )->priority) /+;R/;*/ )->priority) /*;>edge) /+;
R/SC;yy+NT )->priority) /+;R/;*/ *layout_nearfactor); } if ((( c )->target2) /*;
->width) /+;R/SC;yy+NT +/_xspace)));;*/ ) { if ((( (( c )->target2) /*;
se weight += ((( (( c )->edge) /+;R/SC;;*/ )->xloc) /*;se weight += ((( (( c )->edge) /+;
R/SC;;*/ <(( node )->xloc) /*;se weight += ((( (( c )->edge) /+;R/SC;
;*/ ) weight -= ((( (( c )->edge2) /*;)->target) /+;R/SC;yy+NT )->xloc) /+;
R/;*/ )->priority) /*;)->target) /+;R/SC;yy+NT )->xloc) /+;R/;*/ *layout_nearfactor * /*;)->target) /+;R/SC;yy+NT )->xloc) /+;R/
h) /+;R/SC;yy+NT +/_xspace))); ;*/ ((( node )->xloc) /*;h) /+;R/SC;yy+NT +/_xspace))); ;*/ - ((( (( c )->target2) /*;
h) /+;R/SC;yy+NT +/_xspace))); ;*/ )->xloc) /*;h) /+;R/SC;yy+NT +/_xspace)));
;*/  +(( (( c )->target2) /*;>edge) /+;R/SC;yy+NT )->priority) /+;R/;
*/ )->width) /*;>edge) /+;R/SC;yy+NT )->priority) /+;R/;*/ +G_xspace))); /*;>edge) /+;R/SC;yy+NT )->priority) /+;R/
};*/ else weight += ((( (( c )->edge2) /*;};*/ )->priority) /*;};*/ *layout_nearfactor * /*;}
c )->target2) /+;R/SC;yy+NT ) {;*/ ((( (( c )->target2) /*;c )->target2) /+;R/SC;yy+NT ) {;*/ )->xloc) /*;
c )->target2) /+;R/SC;yy+NT ) {;*/ - ((( node )->xloc) /*;c )->target2) /+;
R/SC;yy+NT ) {;*/  +(( node )->width) /*;>target2) /+;R/SC;yy+NT )->xloc) /+;
R/S;*/ +G_xspace)));  nr_edges += ((( (( c )->edge2) /*;>edge2) /+;R/SC;
yy+NT )->priority) /+;R;*/ )->priority) /*;>edge2) /+;R/SC;yy+NT )->priority) /+;
R;*/ *layout_nearfactor); } } if (nr_edges) return(weight/nr_edges); /*;)->target2) /+;R/SC;yy+NT )->xloc) /+;R
h) /+;R/SC;yy+NT +/_xspace))); ;*/  else return(0); }
#ifdef ANSI_C
static int gs_ide1030 (GNODE node)
#else
static int gs_ide1030 (node) GNODE node;
#endif
{ int weight; int dx1, dx2, dy1, dy2; int nr_edges,p1,p2; GEDGE edge; /*;/N;D+ node;
{;*/  GNODE v; ADJEDGE a; CONNECT c; weight = 0;  nr_edges = 0; if ( (layout_downfactor==1)&&(layout_upfactor==1) /*;dge;
/N;D+ v;;*/ && (( node )->succ) /*;/N;D+ v;;*/ && ((( (( node )->succ) /*;/N;D+ v;
;*/ )->next) /*;/N;D+ v;;*/ ==0) && (( node )->pred) /*; a;;*/ && ((( (( node )->pred) /*;
a;;*/ )->next) /*; a;;*/ ==0) && ((( (( (( node )->succ) /*;C;NN+CT c;
;*/ )->kante) /*;C;NN+CT c;;*/ )->priority) /*;C;NN+CT c;;*/ ==(( (( (( node )->pred) /*;
C;NN+CT c;;*/ )->kante) /*;C;NN+CT c;;*/ )->priority) /*;C;NN+CT c;;
*/ ) && (( node )->connection) /*;= 0; ;*/ ==NULL) { edge = (( (( node )->pred) /*;
nr_edges = 0;;*/ )->kante) /*;nr_edges = 0;;*/ ; v = (( edge )->start) /*;
ayout_downfactor==1)&&(layout_upfactor=;*/ ; p1 = (( node )->xloc) /*;
succ) /+;R/SC;yy+NT && ((( (( node )->s;*/ +((( node )->width) /*;succ) /+;
R/SC;yy+NT && ((( (( node )->s;*/ *(( edge )->weightp) /*;succ) /+;R/SC;
yy+NT && ((( (( node )->s;*/ /((( node )->weightp) /*;succ) /+;R/SC;
yy+NT && ((( (( node )->s;*/ +1)); p2 = (( v )->xloc) /*;+;R/SC;yy+NT && ((( (( node )->pred) /+;
*/ + ((( v )->width) /*;+;R/SC;yy+NT && ((( (( node )->pred) /+;*/ *(( edge )->weights) /*;
+;R/SC;yy+NT && ((( (( node )->pred) /+;*/ /((( v )->weights) /*;+;R/SC;
yy+NT && ((( (( node )->pred) /+;*/ +1)); dx1 = p1 - p2;  edge = (( (( node )->succ) /*;
y+NT ==NULL) {;*/ )->kante) /*;y+NT ==NULL) {;*/ ; v = (( edge )->end) /*;
ge = (( (( node )->pred) /+;R/SC;yy+NT ;*/ ; p1 = (( node )->xloc) /*;
ge )->start) /+;R/SC;yy+NT ;;*/ +((( node )->width) /*;ge )->start) /+;
R/SC;yy+NT ;;*/ *(( edge )->weights) /*;ge )->start) /+;R/SC;yy+NT ;
;*/ /((( node )->weights) /*;ge )->start) /+;R/SC;yy+NT ;;*/ +1)); p2 = (( v )->xloc) /*;
xloc) /+;R/SC;yy+NT +((( node )->width);*/ + ((( v )->width) /*;xloc) /+;
R/SC;yy+NT +((( node )->width);*/ *(( edge )->weightp) /*;xloc) /+;R/SC;
yy+NT +((( node )->width);*/ /((( v )->weightp) /*;xloc) /+;R/SC;yy+NT +((( node )->width);
*/ +1)); dx2 = p2 - p1; p1 = (( node )->yloc) /*;dx1 = p1 - p2; ;*/ +(( node )->height) /*;
dx1 = p1 - p2; ;*/ /2; p2 = (( ((( (( (( node )->pred) /*;(( (( node )->succ) /+;
R/SC;yy+NT )->ka;*/ )->kante) /*;(( (( node )->succ) /+;R/SC;yy+NT )->ka;
*/ )->start) /*;(( (( node )->succ) /+;R/SC;yy+NT )->ka;*/ ) /*;(( (( node )->succ) /+;
R/SC;yy+NT )->ka;*/ )->yloc) /*;(( (( node )->succ) /+;R/SC;yy+NT )->ka;
*/ +(( ((( (( (( node )->pred) /*;(( (( node )->succ) /+;R/SC;yy+NT )->ka;
*/ )->kante) /*;(( (( node )->succ) /+;R/SC;yy+NT )->ka;*/ )->start) /*;
(( (( node )->succ) /+;R/SC;yy+NT )->ka;*/ ) /*;(( (( node )->succ) /+;
R/SC;yy+NT )->ka;*/ )->height) /*;(( (( node )->succ) /+;R/SC;yy+NT )->ka;
*/ /2; dy1 = p1 - p2; p2 = (( ((( (( (( node )->succ) /*; /+;R/SC;yy+NT +((( node )->width) /+;
R;*/ )->kante) /*; /+;R/SC;yy+NT +((( node )->width) /+;R;*/ )->end) /*;
/+;R/SC;yy+NT +((( node )->width) /+;R;*/ ) /*; /+;R/SC;yy+NT +((( node )->width) /+;
R;*/ )->yloc) /*; /+;R/SC;yy+NT +((( node )->width) /+;R;*/ +(( ((( (( (( node )->succ) /*;
/+;R/SC;yy+NT +((( node )->width) /+;R;*/ )->kante) /*; /+;R/SC;yy+NT +((( node )->width) /+;
R;*/ )->end) /*; /+;R/SC;yy+NT +((( node )->width) /+;R;*/ ) /*; /+;
R/SC;yy+NT +((( node )->width) /+;R;*/ )->height) /*; /+;R/SC;yy+NT +((( node )->width) /+;
R;*/ /2; dy2 = p2 - p1; weight = (dx2*dy1-dx1*dy2)/(dy1+dy2); return(weight); /*; node )->yloc) /+;R/SC;yy+NT +(( node )
(( node )->pred) /+;R/SC;yy+NT )->kant;*/ } a = (( node )->succ) /*;dy1 = p1 - p2;;*/ ; while (a) { weight += (gs_ide1012 ((( a )->kante) /*;
;*/ )*(( (( a )->kante) /*;;*/ )->priority) /*;;*/  *layout_downfactor); /*;*dy2)*(dy1+dy2);
return(weight);;*/ nr_edges += ((( (( a )->kante) /*;return(weight);;*/ )->priority) /*;
return(weight);;*/ *layout_downfactor); a = (( a )->next) /*;};*/ ; } /*;while (a) {
+= (gs_ide1012 ((( a )->kante) /+;R/SC;;*/  a = (( node )->pred) /*;while (a) {;*/ ; while (a) { weight += (gs_ide1011 ((( a )->kante) /*;
ctor);;*/ )*(( (( a )->kante) /*;ctor);;*/ )->priority) /*;ctor);;*/  *layout_upfactor); /*;)->kante) /+;R/SC;yy+NT )->priority) /+
+NT ;;*/ nr_edges += ((( (( a )->kante) /*;+NT ;;*/ )->priority) /*;+NT ;;*/ *layout_upfactor); /*;+NT ;
};*/ a = (( a )->next) /*;};*/ ; } c = (( node )->connection) /*;while (a) {
;*/ ; if (c) { if ((( c )->target) /*;or);;*/ ) { if ((( (( c )->target) /*;
)->kante) /+;R/SC;yy+NT )->priority) /+;*/ )->xloc) /*;)->kante) /+;
R/SC;yy+NT )->priority) /+;*/ <(( node )->xloc) /*;)->kante) /+;R/SC;
yy+NT )->priority) /+;*/ ) weight -= ((( (( c )->edge) /*;+NT ;;*/ )->priority) /*;
+NT ;;*/ *layout_nearfactor * ((( node )->xloc) /*;};*/ - ((( (( c )->target) /*;
};*/ )->xloc) /*;};*/  +(( (( c )->target) /*;node )->connection) /+;
R/SC;yy+NT ;;*/ )->width) /*;node )->connection) /+;R/SC;yy+NT ;;*/ +G_xspace))); /*;node )->connection) /+;R/SC;yy+NT ;
if (c) {;*/ else weight += ((( (( c )->edge) /*;if (c) {;*/ )->priority) /*;if (c) {
;*/ *layout_nearfactor * ((( (( c )->target) /*;c )->target) /+;R/SC;
yy+NT ) {;*/ )->xloc) /*;c )->target) /+;R/SC;yy+NT ) {;*/ - ((( node )->xloc) /*;
c )->target) /+;R/SC;yy+NT ) {;*/  +(( node )->width) /*;>target) /+;
R/SC;yy+NT )->xloc) /+;R/SC;*/ +G_xspace)));  nr_edges += ((( (( c )->edge) /*;
>edge) /+;R/SC;yy+NT )->priority) /+;R/;*/ )->priority) /*;>edge) /+;
R/SC;yy+NT )->priority) /+;R/;*/ *layout_nearfactor); } if ((( c )->target2) /*;
->width) /+;R/SC;yy+NT +/_xspace)));;*/ ) { if ((( (( c )->target2) /*;
se weight += ((( (( c )->edge) /+;R/SC;;*/ )->xloc) /*;se weight += ((( (( c )->edge) /+;
R/SC;;*/ <(( node )->xloc) /*;se weight += ((( (( c )->edge) /+;R/SC;
;*/ ) weight -= ((( (( c )->edge2) /*;)->target) /+;R/SC;yy+NT )->xloc) /+;
R/;*/ )->priority) /*;)->target) /+;R/SC;yy+NT )->xloc) /+;R/;*/ *layout_nearfactor * /*;)->target) /+;R/SC;yy+NT )->xloc) /+;R/
h) /+;R/SC;yy+NT +/_xspace))); ;*/ ((( node )->xloc) /*;h) /+;R/SC;yy+NT +/_xspace))); ;*/ - ((( (( c )->target2) /*;
h) /+;R/SC;yy+NT +/_xspace))); ;*/ )->xloc) /*;h) /+;R/SC;yy+NT +/_xspace)));
;*/  +(( (( c )->target2) /*;>edge) /+;R/SC;yy+NT )->priority) /+;R/;
*/ )->width) /*;>edge) /+;R/SC;yy+NT )->priority) /+;R/;*/ +G_xspace))); /*;>edge) /+;R/SC;yy+NT )->priority) /+;R/
};*/ else weight += ((( (( c )->edge2) /*;};*/ )->priority) /*;};*/ *layout_nearfactor * /*;}
c )->target2) /+;R/SC;yy+NT ) {;*/ ((( (( c )->target2) /*;c )->target2) /+;R/SC;yy+NT ) {;*/ )->xloc) /*;
c )->target2) /+;R/SC;yy+NT ) {;*/ - ((( node )->xloc) /*;c )->target2) /+;
R/SC;yy+NT ) {;*/  +(( node )->width) /*;>target2) /+;R/SC;yy+NT )->xloc) /+;
R/S;*/ +G_xspace)));  nr_edges += ((( (( c )->edge2) /*;>edge2) /+;R/SC;
yy+NT )->priority) /+;R;*/ )->priority) /*;>edge2) /+;R/SC;yy+NT )->priority) /+;
R;*/ *layout_nearfactor); } } if (nr_edges) return(weight/nr_edges); /*;)->target2) /+;R/SC;yy+NT )->xloc) /+;R
h) /+;R/SC;yy+NT +/_xspace))); ;*/  else return(0); }
#ifdef ANSI_C
static int gs_ide1031 (GNODE node,GNODE lnode,GNODE rnode)
#else
static int gs_ide1031 (node, lnode, rnode) GNODE node, lnode, rnode;
#endif
{ GNODE pred, succ; int ax,ay,mx,my,bx,by,kx,h, dist; int act_nw; act_nw = gs_ide1030 (node); /*;ide1031 (node, lnode, rnode)
ode;;*/ if ((( node )->pred) /*;ode;;*/ ) pred = ((( (( (( node )->pred) /*;
ode;;*/ )->kante) /*;ode;;*/ )->start) /*;ode;;*/ ) /*;ode;;*/ ; else return(act_nw); /*;{
red, succ;;*/ if ((( node )->succ) /*;red, succ;;*/ ) succ = ((( (( (( node )->succ) /*;
red, succ;;*/ )->kante) /*;red, succ;;*/ )->end) /*;red, succ;;*/ ) /*;
red, succ;;*/ ; else return(act_nw); ax = (( pred )->xloc) /*;int act_nw;
;*/ ; ay = (( pred )->yloc) /*;= gs_ide1030 (node);;*/ ; mx = (( node )->xloc) /*;
>pred) /+;R/SC;yy+NT ) pred = ((( (( ((;*/ ; my = (( node )->yloc) /*;
else return(act_nw);;*/ ; bx = (( succ )->xloc) /*;node )->succ) /+;
R/SC;yy+NT ) succ = ((;*/ ; by = (( succ )->yloc) /*;t_nw);;*/ ; if ((ax<mx)&&(bx<mx)) return(act_nw); /*; /+;R/SC;yy+NT ;
C;yy+NT ;;*/ if ((ax>mx)&&(bx>mx)) return(act_nw); if (ax<bx) { if (rnode && act_nw>0) { /*; = (( node )->yloc) /+;R/SC;yy+NT ;
ucc )->xloc) /+;R/SC;yy+NT ;;*/   kx = (( rnode )->xloc) /*;ucc )->xloc) /+;R/SC;yy+NT ;;*/ ; h = (( rnode )->yloc) /*;
yloc) /+;R/SC;yy+NT ;;*/ +(( rnode )->height) /*;yloc) /+;R/SC;yy+NT ;
;*/ -my; if (h-by+my==0) return(act_nw); dist = (bx*h - kx*(by-my))/(h-by+my) - mx; /*;ct_nw);
if (ax<bx) {;*/ if (dist<act_nw) act_nw = dist; } else if (lnode && act_nw<0) {  kx = (( lnode )->xloc) /*;
/+;R/SC;yy+NT +(( rnode )->height) /+;;*/ +(( lnode )->width) /*; /+;
R/SC;yy+NT +(( rnode )->height) /+;;*/ ; h = (( lnode )->yloc) /*;w);
;*/ -my; if (h-ay+my==0) return(act_nw); dist = (ax*h - kx*(ay-my))/(h-ay+my) - mx; /*; (dist<act_nw) act_nw = dist;
};*/ if (dist>act_nw) act_nw = dist; } } else if (ax>bx) { if (lnode && act_nw<0) { /*;w);
) - mx;;*/   kx = (( lnode )->xloc) /*;) - mx;;*/ +(( lnode )->width) /*;) - mx;
;*/ ; h = (( lnode )->yloc) /*; (dist>act_nw) act_nw = dist;;*/ +(( lnode )->height) /*;
(dist>act_nw) act_nw = dist;;*/ -my; if (h-by+my==0) return(act_nw); /*;}
(ax>bx) {;*/  dist = (bx*h - kx*(by-my))/(h-by+my) - mx; if (dist>act_nw) act_nw = dist; /*; (ax>bx) {
ct_nw<0) { ;*/ } else if (rnode && act_nw>0) {  kx = (( rnode )->xloc) /*;C;yy+NT +(( lnode )->height) /+;
R/SC;yy;*/ ; h = (( rnode )->yloc) /*;if (h-by+my==0) return(act_nw);
;*/ -my; if (h-ay+my==0) return(act_nw); dist = (ax*h - kx*(ay-my))/(h-ay+my) - mx; /*;w) act_nw = dist;
};*/ if (dist<act_nw) act_nw = dist; } } return(act_nw); }
#ifdef ANSI_C
static void gs_ide1040 (int i)
#else
static void gs_ide1040 (i) int i;
#endif
{ int j; GNLIST hn; ; j = 0; hn = (( layer[i] ).succlist) /*;int i;;
*/ ; while (hn) { assert(((( (( hn )->node) /*;int j;;*/ )->position) /*;
int j;;*/ ==j)); gs_ide1047 [j] = (( hn )->node) /*;hn;;*/ ; gs_ide1025 [j] = 0; /*;;
j = 0;;*/ gs_ide1026 [j++] = 0; hn = (( hn )->next) /*; layer[i] ).succlist) /+;
R/SC;yy+NT ;;*/ ; } assert(j==(( layer[i] ).anz) /*;((( (( hn )->node) /+;
R/SC;yy+NT )->pos;*/ ); }
#ifdef DRAWDEBUG
#ifdef ANSI_C
static void drawdebug_show_graph(char *m,int i,int j,int k)
#else
static void drawdebug_show_graph(m,i,j,k) char *m; int i,j,k;
#endif
{ PRINTF("%s %d (%d %d)\n",m,i,j,k); PRINTF("Enter CR into the text window\n"); /*;void drawdebug_show_graph(char *m,int i
awdebug_show_graph(m,i,j,k);*/ gs_ide1043 (); step4_main(); debug_display_part(); fgetc(stdin); }
#endif
