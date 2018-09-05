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
static char *gs_ide530 ="$Id: step2.c,v 3.12 1995/02/08 11:11:14 sander Exp $"; /*;*a*b
*a*b;*/ 
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "globals.h"
#include "alloc.h"
#include "main.h"
#include "options.h"
#include "folding.h"
#include "steps.h"
#include "timelim.h"
#include "timing.h"
#undef CHECK_CROSSING  
#ifndef ANSI_C
#ifndef const
#define const
#endif
#endif
#ifdef OWN_QUICKSORT
#define quicksort_sort_array(x) { if (x) { gs_ide559  = 211; gs_ide549 (0,x-1);} }
#else
#ifdef ANSI_C
#define quicksort_sort_array(x) { if (x) qsort(gs_ide577 ,x, 	   sizeof(GNODE),(int (*) (const void *, const void *))gs_ide514 ); }
#else
#define quicksort_sort_array(x) { if (x) qsort(gs_ide577 ,x, 	   sizeof(GNODE),gs_ide514 ); }
#endif
#endif
#ifdef ANSI_C
#define quicksort_save_array(x) { if (x) qsort(gs_ide569 ,x, 	   sizeof(GNODE),(int (*) (const void *, const void *))gs_ide515 ); }
#else
#define quicksort_save_array(x) { if (x) qsort(gs_ide569 ,x, 	   sizeof(GNODE),gs_ide515 ); }
#endif
static void gs_ide519 _PP((void)); static void gs_ide581 _PP((void)); /*;*a*b
*a*b;*/  static void gs_ide582 _PP((void)); static void gs_ide556 _PP((void)); /*;*a*b
*gs_ide530 = $Id: step2.c,v 3.12 1995*0;*/  static void gs_ide546 _PP((GNODE node, int i)); static int gs_ide528 _PP((void)); /*;*gs_ide530 = $Id: step2.c,v 3.12 1995*0
19 _PP((void));;*/ static void gs_ide511 _PP((void)); static int gs_ide536 _PP((int level)); /*;(void));
;;*/ static void gs_ide527 _PP((GNODE v)); static void gs_ide526 _PP((GNODE v)); /*;static void gs_ide556 _PP((void));
void gs_ide546 _PP((/N;D+ node, int i));*/ static void gs_ide507 _PP((GNODE n)); static void gs_ide506 _PP((GNODE n)); /*;ide528 _PP((void));
_PP((void));;*/ static void gs_ide522 _PP((DLLIST x)); static void gs_ide521 _PP((DLLIST x)); /*;t level));
);;*/ static void gs_ide542 _PP((int nearedges)); static void gs_ide557 _PP((int level)); /*;atic void gs_ide526 _PP((/N;D+ v));
id gs_ide507 _PP((/N;D+ n));;*/ static int gs_ide540 _PP((int level,int nearedges)); static int gs_ide525 _PP((GNODE C,GNODE D)); /*;de506 _PP((/N;D+ n));
PP((DLLIST x));;*/ static void gs_ide558 _PP((void)); static int gs_ide535 _PP((GNODE v)); /*;IST x));
ges));;*/ static int gs_ide513 _PP((GNODE v1,GNODE v2,int dir)); static void gs_ide523 _PP((GNODE v1,GNODE v2,int dir)); /*;ic void gs_ide557 _PP((int level));
gs_ide540 _PP((int level,int nearedges);*/ static void gs_ide543 _PP((void)); static void gs_ide531 _PP((void)); /*;((void));
v));;*/  static void gs_ide510 _PP((void)); static void gs_ide500 _PP((void)); /*;+ v2,int dir));
void gs_ide523 _PP((/N;D+ v1,/N;D+ v2,;*/  static void gs_ide501 _PP((void)); static void gs_ide502 _PP((void)); /*;s_ide543 _PP((void));
1 _PP((void));;*/  static void gs_ide503 _PP((void)); static int gs_ide561 _PP((int i)); /*;void));
;*/  static int gs_ide564 _PP((int i)); static void gs_ide562 _PP((int level)); /*;
tatic void gs_ide501 _PP((void));;*/ static void gs_ide563 _PP((int level)); static int gs_ide520 _PP((int siz)); /*;oid gs_ide502 _PP((void));
ide503 _PP((void));;*/ static float gs_ide578 _PP((GNODE node)); static float gs_ide554 _PP((GNODE node)); /*;PP((int i));
i));;*/ static float gs_ide579 _PP((GNODE node)); static float gs_ide555 _PP((GNODE node)); /*;));
tic void gs_ide563 _PP((int level));;*/ static void gs_ide541 _PP((int i,int dir)); static void gs_ide509 _PP((int i)); /*; gs_ide520 _PP((int siz));
de578 _PP((/N;D+ node));;*/ static void gs_ide570 _PP((int i));  static void gs_ide565 _PP((int i)); /*;PP((/N;D+ node));
D+ node));;*/ static void gs_ide508 _PP((int i)); static int gs_ide514 _PP((const GNODE *a, const GNODE *b)); /*;));
c void gs_ide541 _PP((int i,int dir));;*/ static int gs_ide515 _PP((const GNODE *a, const GNODE *b)); static void gs_ide518 _PP((DEPTH *l1, DEPTH *l2)); /*;gs_ide509 _PP((int i));
70 _PP((int i)); ;*/ static void gs_ide532 _PP((void)); static void gs_ide533 _PP((int level, GNODE node)); /*;(int i));
);;*/ static void gs_ide512 _PP((int level, GNODE node)); static void gs_ide537 _PP((GNODE v,GNODE w)); /*;static int gs_ide514 _PP((const /N;D+ *
int gs_ide515 _PP((const /N;D+ *a, cons;*/ static void gs_ide566 _PP((GNODE v,GNODE w)); static void gs_ide560 _PP((void)); /*;_ide518 _PP((D+PTH *l1, D+PTH *l2));
_PP((void));;*/ static void gs_ide576 _PP((GNODE v)); static int gs_ide516 _PP((const GEDGE *a, const GEDGE *b)); /*;nt level, /N;D+ node));
l, /N;D+ node));;*/   static int gs_ide517 _PP((const GEDGE *a, const GEDGE *b)); 
#ifdef OWN_QUICKSORT
static void gs_ide549 _PP((int l,int r)); static int gs_ide559 = 211;
#endif
static DEPTH *gs_ide580 =NULL;  static int gs_ide574 = 0;  int max_nodes_per_layer; /*;t /+D/+ *a, const /+D/+ *b)); 
*a, const /+D/+ *b)); ;*/ int nr_crossings; static GNODE *gs_ide504 = NULL; static GEDGE *gs_ide505 = NULL; /*;gs_ide559 = 211;
de580 =NULL; ;*/ static int gs_ide572 = 0; static GNODE *gs_ide577 = NULL; static int gs_ide573 = 0; /*;int max_nodes_per_layer;
crossings;;*/ static GNODE *gs_ide569 = NULL; static int gs_ide550 ;
#ifdef ANSI_C
void step2_main(void)
#else
void step2_main()
#endif
{ int i; int old_nr_crossings; start_time(); ; assert((layer)); gs_ide519 (); /*;{
int i;;*/ if (max_nodes_per_layer+2 > gs_ide573 ) { if (gs_ide577 ) free(gs_ide577 ); /*;_nr_crossings;
start_time();;*/ if (gs_ide569 ) free(gs_ide569 ); gs_ide577 = (GNODE *)malloc((max_nodes_per_layer+2) /*;;
(layer));;*/ * sizeof(GNODE)); gs_ide569 = (GNODE *)malloc((max_nodes_per_layer+2) * sizeof(GNODE)); /*;_nodes_per_layer+2 > gs_ide573 ) {
) free(gs_ide577 );;*/ if ((!gs_ide577 )||(!gs_ide569 ))  Fatal_error("memory exhausted",""); /*;(max_nodes_per_layer+2)
* sizeof(/N;D+));;*/  gs_ide573 = max_nodes_per_layer+2;
#ifdef DEBUG
PRINTF("Sizeof tables `sort_array',`save_array': %ld Bytes\n", (max_nodes_per_layer+2)*sizeof(GNODE)); /*;69 = (/N;D+ *)malloc((max_nodes_per_lay
));;*/ 
#endif
} i = (maxindeg > maxoutdeg ? maxindeg : maxoutdeg); if (i+2 > gs_ide572 ) { /*;d ,  );
gs_ide573 = max_nodes_per_layer+2;;*/ if (gs_ide504 ) free(gs_ide504 ); if (gs_ide505 ) free(gs_ide505 ); gs_ide504 = (GNODE *)malloc((i+2)*sizeof(GNODE)); /*;_layer+2)*sizeof(/N;D+));
};*/ gs_ide505 = (GEDGE *)malloc((i+2)*sizeof(GEDGE)); if ((!gs_ide504 )||(!gs_ide505 ))  /*;xindeg > maxoutdeg ? maxindeg : maxoutd
de572 ) {;*/ Fatal_error("memory exhausted",""); gs_ide572 = i+2;
#ifdef DEBUG
PRINTF("Sizeof table `adjarray[12]': %ld Bytes\n", (i+2)*sizeof(GNODE)); /*;izeof(/N;D+));
_ide505 = (/+D/+ *)malloc((i+2)*sizeof(;*/ 
#endif
} gs_ide581 (); gs_ide556 (); gs_ide582 (); gs_ide511 (); for (i=0; i<=maxdepth+1; /*;N;D+));
};*/  i++) (( layer[i] ).cross) /*;};*/ = (( gs_ide580 [i] ).cross) /*;};
*/ ; nr_crossings = gs_ide528 ();
#ifdef CHECK_CROSSING
PRINTF("Start: nr_crossings %d \n",nr_crossings); 
#endif
gs_ide531 (); old_nr_crossings = -1; gs_ide550 = 0; while (nr_crossings != old_nr_crossings) { /*;cross) /+;R/SC;yy+NT = (( gs_ide580 [i]
528 ();;*/ if (gs_ide550 >=max_baryiterations) { gs_wait_message('t'); break; } /*;
= old_nr_crossings) {;*/  if (G_timelimit>0) if (test_timelimit(60)) { gs_wait_message('t'); break; /*;gs_wait_message('t');
break;;*/ } old_nr_crossings = nr_crossings; gs_ide510 (); gs_ide550 ++; if (gs_ide550 <min_baryiterations)  /*;
break;;*/ nr_crossings = old_nr_crossings+1;  }
#ifdef CHECK_CROSSING
PRINTF("After barycentering: nr_crossings %d \n",nr_crossings); 
#endif
old_nr_crossings = nr_crossings; if (old_nr_crossings>0) gs_ide542 (0); /*;50 ++;
<min_baryiterations) ;*/ gs_wait_message('b'); gs_ide532 (); gs_wait_message('b'); if (old_nr_crossings>0) gs_ide542 (1); /*; After barycentering: nr_crossings %d z
gs = nr_crossings;;*/ 
#ifdef CHECK_CROSSING
gs_ide511 (); nr_crossings = gs_ide528 (); PRINTF("After local optimization: nr_crossings %d \n",nr_crossings); /*;gs_wait_message('b');
32 ();;*/  
#endif
if (local_unwind && (old_nr_crossings>0)) gs_ide543 (); gs_ide511 (); /*;0) gs_ide542 (1);
gs_ide511 ();;*/  nr_crossings = gs_ide528 ();
#ifdef CHECK_CROSSING
PRINTF("Final: nr_crossings %d \n",nr_crossings); 
#endif
gs_ide518 (layer,gs_ide580 );  gs_ide560 (); stop_time("step2_main"); /*;gs_ide511 ();
sings = gs_ide528 ();;*/  }
#ifdef ANSI_C
static void gs_ide519 (void)
#else
static void gs_ide519 ()
#endif
{ int i,j; GNLIST h1, h2; if (maxdepth+2 > gs_ide574 ) { if (gs_ide580 ) free(gs_ide580 ); /*;void gs_ide519 (void)
_ide519 ();*/ gs_ide580 = (DEPTH *)malloc((maxdepth+2)*sizeof(struct depth_entry)); /*;{
;;*/  if (!gs_ide580 ) Fatal_error("memory exhausted",""); gs_ide574 = maxdepth+2; /*;;
;*/ 
#ifdef DEBUG
PRINTF("Sizeof table `tmp_layer': %ld Bytes\n", (maxdepth+2)*sizeof(struct depth_entry)); /*;de574 ) {
80 );;*/ 
#endif
} max_nodes_per_layer = 0; for (i=0; i<=maxdepth+1; i++) { (( gs_ide580 [i] ).cross) /*;
= maxdepth+2;;*/ = 0; (( gs_ide580 [i] ).predlist) /*;able `tmp_layer': %ld Byteszn ,;
*/ = NULL; (( gs_ide580 [i] ).succlist) /*;uct depth_entry));;*/ = NULL; /*;uct depth_entry));
};*/ j = 0; h1 = (( layer[i] ).succlist) /*;es_per_layer = 0;;*/ ; while (h1) { /*;axdepth+1; i++) {
oss) /+;R/SC;yy+NT = 0;;*/ j++; h1 = (( h1 )->next) /*; /+;R/SC;yy+NT = NULL;;*/ ; } if (j > max_nodes_per_layer) max_nodes_per_layer = j; /*;= 0;
ayer[i] ).succlist) /+;R/SC;yy+NT ;;*/ j = 0; h1 = (( layer[i] ).predlist) /*;while (h1) {;*/ ; while (h1) { /*; h1 )->next) /+;R/SC;yy+NT ;
};*/  j++; h2 = tmpnodelist_alloc(); (( h2 )->next) /*; max_nodes_per_layer) max_nodes_per_lay;
*/ = (( gs_ide580 [i] ).succlist) /*; max_nodes_per_layer) max_nodes_per_lay;
*/ ; (( gs_ide580 [i] ).succlist) /*;j = 0;;*/ = h2; (( h2 )->node) /*;
layer[i] ).predlist) /+;R/SC;yy+NT ;;*/ = (( h1 )->node) /*; layer[i] ).predlist) /+;
R/SC;yy+NT ;;*/ ; h1 = (( h1 )->next) /*;while (h1) {;*/ ; } (( gs_ide580 [i] ).anz) /*;
pnodelist_alloc();;*/ = (( layer[i] ).anz) /*;pnodelist_alloc();;*/ = j; /*;pnodelist_alloc();
/+;R/SC;yy+NT = (( gs_ide580 [i] ).suc;*/ (( gs_ide580 [i] ).resort_necessary) /*; /+;R/SC;yy+NT = (( gs_ide580 [i] ).suc;
*/ = (( layer[i] ).resort_necessary) /*; /+;R/SC;yy+NT = (( gs_ide580 [i] ).suc;
*/ ; if (j > max_nodes_per_layer) max_nodes_per_layer = j; (( layer[i] ).succlist) /*;
= (( h1 )->node) /+;R/SC;yy+NT ;;*/ = NULL; h1 = (( layer[i] ).predlist) /*;
;*/ ; while (h1) { h2 = tmpnodelist_alloc(); (( h2 )->next) /*;i] ).resort_necessary) /+;
R/SC;yy+NT = ;*/ = (( layer[i] ).succlist) /*;i] ).resort_necessary) /+;
R/SC;yy+NT = ;*/ ; (( layer[i] ).succlist) /*;_layer) max_nodes_per_layer = j;
;*/ = h2; (( h2 )->node) /*;/SC;yy+NT = NULL;;*/ = (( h1 )->node) /*;
/SC;yy+NT = NULL;;*/ ; h1 = (( h1 )->next) /*;C;yy+NT ;;*/ ; } } }
#ifdef ANSI_C
static void gs_ide581 (void)
#else
static void gs_ide581 ()
#endif
{ GNLIST li; int i, prio; GNODE node; ADJEDGE a; GEDGE e; double maxbary; /*;{
li;;*/ ; for (i=0; i<=maxdepth+1; i++) { li = (( gs_ide580 [i] ).succlist) /*;
ode;;*/ ; while (li) {  assert(((( (( li )->node) /*;;;*/ )->markiert) /*;
;;*/ ==0));  a = (( (( li )->node) /*;;;*/ )->succ) /*;;;*/ ; while (a) { /*;;
0; i<=maxdepth+1; i++) {;*/ (( (( a )->kante) /*;0; i<=maxdepth+1; i++) {;*/ )->weights) /*;0; i<=maxdepth+1;
i++) {;*/ = 0; a = (( a )->next) /*;580 [i] ).succlist) /+;R/SC;yy+NT ;
;*/ ; } li = (( li )->next) /*;((( (( li )->node) /+;R/SC;yy+NT )->mar;
*/ ;  } } for (i=0; i<=maxdepth+1; i++) { for (prio=max_eprio; prio >= 0; /*;xt) /+;R/SC;yy+NT ;
};*/  prio--) { li = (( gs_ide580 [i] ).succlist) /*;};*/ ; while (li) {  a = (( (( li )->node) /*;
};*/ )->succ) /*;};*/ ; while (a) { e = (( a )->kante) /*;0; i<=maxdepth+1;
i++) {;*/ ; if ((( e )->priority) /*;eprio; prio >= 0; prio--) {;*/ ==prio) { /*;eprio; prio >= 0; prio--) {
).succlist) /+;R/SC;yy+NT ;;*/ node = ((( (( a )->kante) /*; ).succlist) /+;R/SC;yy+NT ;;*/ )->end) /*;
).succlist) /+;R/SC;yy+NT ;;*/ ) /*; ).succlist) /+;R/SC;yy+NT ;;*/ ; /*; ).succlist) /+;R/SC;yy+NT ;
while (li) { ;*/   if (!(( node )->markiert) /*;while (li) { ;*/ ) { (( node )->markiert) /*;
(( li )->node) /+;R/SC;yy+NT )->succ) /;*/ = 1; (( e )->weights) /*;
while (a) {;*/ = 1; } }  a = (( a )->next) /*;nte) /+;R/SC;yy+NT )->end) /+;
R/SC;yy+N;*/ ; } li = (( li )->next) /*;= 1;;*/ ;  } } } for (i=1; i<=maxdepth+1; /*;a )->next) /+;R/SC;yy+NT ;
};*/  i++) { gs_ide541 (i,'d'); maxbary = 0.1; li = (( gs_ide580 [i] ).succlist) /*;
};*/ ; while (li) { node = (( li )->node) /*;};*/ ; (( node )->bary) /*;
1; i<=maxdepth+1; i++) {;*/ = gs_ide554 (node);  if ((( node )->bary) /*;
d');;*/ > maxbary) maxbary = (( node )->bary) /*;d');;*/ ; li = (( li )->next) /*;
maxbary = 0.1;;*/ ; } maxbary = maxbary + 1.0; li = (( gs_ide580 [i-1] ).succlist) /*;
(( li )->node) /+;R/SC;yy+NT ;;*/ ; while (li) { a = (( (( li )->node) /*;
/+;R/SC;yy+NT > maxbary) maxbary = (( n;*/ )->succ) /*;/+;R/SC;yy+NT > maxbary) maxbary = (( n;
*/ ; while (a) { e = (( a )->kante) /*;};*/ ; if ((( e )->weights) /*;
= maxbary + 1.0;;*/ ) { node = ((( (( a )->kante) /*;580 [i-1] ).succlist) /+;
R/SC;yy+NT ;;*/ )->end) /*;580 [i-1] ).succlist) /+;R/SC;yy+NT ;;*/ ) /*;
580 [i-1] ).succlist) /+;R/SC;yy+NT ;;*/ ; (( node )->bary) /*;while (li) {
;*/ =(double)((( (( li )->node) /*;while (li) {;*/ )->position) /*;while (li) {
;*/ ) + (( node )->bary) /*;(( li )->node) /+;R/SC;yy+NT )->succ) /;
*/ /maxbary; } a = (( a )->next) /*;a )->kante) /+;R/SC;yy+NT ;;*/ ; /*;nte) /+;R/SC;yy+NT )->end) /+;R/SC;yy+N
NT =(double)((( (( li )->node) /+;R/SC;;*/  } li = (( li )->next) /*;nte) /+;R/SC;yy+NT )->end) /+;R/SC;yy+N;*/ ; /*;NT =(double)((( (( li )->node) /+;R/SC;
axbary;;*/  } quicksort_sort_array((( layer[i] ).anz) /*;axbary;;*/ ); gs_ide509 (i); /*;}
a )->next) /+;R/SC;yy+NT ;;*/ } for (i=0; i<=maxdepth+1; i++) { li = (( gs_ide580 [i] ).succlist) /*;
li )->next) /+;R/SC;yy+NT ;;*/ ; while (li) { (( (( li )->node) /*;
};*/ )->markiert) /*;};*/ = 0; li = (( li )->next) /*;};*/ ; } } gs_ide518 (layer,gs_ide580 ); /*;
};*/   } static int gs_ide547 ;
#ifdef ANSI_C
static void gs_ide556 (void)
#else
static void gs_ide556 ()
#endif
{ GNLIST li; int i, reorder_necessary; GNODE node; ; gs_ide547 = 0; for (i=0; /*;{
li;;*/  i<=maxdepth+1; i++) { li = (( gs_ide580 [i] ).succlist) /*;li;;*/ ; /*;_necessary;
/N;D+ node;;*/  reorder_necessary = 0; while (li) { node = (( li )->node) /*;;;*/ ; /*;47 = 0;
axdepth+1; i++) {;*/  if ((( node )->nhorder) /*;47 = 0;;*/ >= 0) reorder_necessary = 1;  if ((( node )->nhorder) /*;
axdepth+1; i++) {;*/ >gs_ide547 ) gs_ide547 = (( node )->nhorder) /*;
).succlist) /+;R/SC;yy+NT ;;*/ ; li = (( li )->next) /*;reorder_necessary = 0;
;*/ ; } (( gs_ide580 [i] ).resort_necessary) /*;->node) /+;R/SC;yy+NT ;
;*/ =  (( layer[i] ).resort_necessary) /*;r) /+;R/SC;yy+NT >= 0) reorder_necessar;
*/ = reorder_necessary; } }
#ifdef ANSI_C
static void gs_ide582 (void)
#else
static void gs_ide582 ()
#endif
{ GNLIST li; int i,j; int part_is_missing;  GNODE node; int act_graph; /*;{
li;;*/  ; for (i=0; i<=maxdepth+1; i++) { li = (( gs_ide580 [i] ).succlist) /*;
int i,j;;*/ ; while (li) { (( (( li )->node) /*;/N;D+ node;;*/ )->bary) /*;
/N;D+ node;;*/ = 0; li = (( li )->next) /*;_graph;;*/ ; } } act_graph = 1; /*;580 [i] ).succlist) /+;R/SC;yy+NT ;
while (li) {;*/ part_is_missing = 1; while (part_is_missing) { gs_wait_message('u'); /*;}
};*/  part_is_missing =0; node = (GNODE)0; act_graph++; for (i=0; i<=maxdepth+1; /*;g = 1;
g) {;*/  i++) { li = (( layer[i] ).succlist) /*;g) {;*/ ; while (li) { if ((( (( li )->node) /*;
_missing =0;;*/ )->bary) /*;_missing =0;;*/ == 0) { node = (( li )->node) /*;
0;;*/ ; break; } li = (( li )->next) /*;i] ).succlist) /+;R/SC;yy+NT ;
;*/ ; } if (node) break; } if (node) { assert(((( node )->bary) /*;}
;*/ ==0)); part_is_missing =1; gs_ide546 (node, act_graph); } } for (i=0; /*;e) {
e )->bary) /+;R/SC;yy+NT ==0));;*/  i<=maxdepth+1; i++) { li = (( gs_ide580 [i] ).succlist) /*;e )->bary) /+;
R/SC;yy+NT ==0));;*/ ; j = 0; while (li) { gs_ide577 [j++] = (( li )->node) /*;
};*/ ; li = (( li )->next) /*;};*/ ; } quicksort_sort_array((( layer[i] ).anz) /*;
580 [i] ).succlist) /+;R/SC;yy+NT ;;*/ ); gs_ide509 (i); } gs_ide518 (layer,gs_ide580 ); /*;] = (( li )->node) /+;R/SC;yy+NT ;
+;R/SC;yy+NT ;;*/   }
#ifdef ANSI_C
static void gs_ide546 (GNODE node,int i)
#else
static void gs_ide546 (node, i) GNODE node; int i;
#endif
{ ADJEDGE e; ; if ((( node )->bary) /*;_ide546 (node, i);*/ ) return; /*;/N;D+ node;
int i;;*/  if ((( node )->nhorder) /*;/N;D+ node;;*/ >=0)  (( node )->bary) /*;
int i;;*/ = (float)i*(float)(gs_ide547 +1) +(float)(( node )->nhorder) /*;
{;*/ ; else (( node )->bary) /*; e;;*/ = (float)i*(float)(gs_ide547 +1); /*; e;
;;*/ e = (( node )->succ) /*;;;*/ ; while (e) { gs_ide546 (((( (( e )->kante) /*;
>nhorder) /+;R/SC;yy+NT >=0) ;*/ )->end) /*;>nhorder) /+;R/SC;yy+NT >=0) ;
*/ ) /*;>nhorder) /+;R/SC;yy+NT >=0) ;*/ ,i); e = (( e )->next) /*;/SC;
yy+NT = (float)i*(float)(gs_ide547 ;*/ ; } e = (( node )->pred) /*; = (float)i*(float)(gs_ide547 +1);
;*/ ; while (e) { gs_ide546 (((( (( e )->kante) /*; {;*/ )->start) /*;
{;*/ ) /*; {;*/ ,i); e = (( e )->next) /*;( e )->kante) /+;R/SC;yy+NT )->end) /+;
;*/ ; } }
#ifdef ANSI_C
static int gs_ide528 (void)
#else
static int gs_ide528 ()
#endif
{ int i; int sumC; ; assert((gs_ide580 )); sumC = 0; for (i=0; i<=maxdepth; /*;{
int i;;*/  i++) sumC += (( gs_ide580 [i] ).cross) /*;{;*/ ; assert(((( gs_ide580 [maxdepth+1] ).cross) /*;
int i;;*/ ==0)); return(sumC); }
#ifdef ANSI_C
static void gs_ide511 (void)
#else
static void gs_ide511 ()
#endif
{ int i; ; assert((gs_ide580 )); for (i=0; i<=maxdepth; i++)  (( gs_ide580 [i] ).cross) /*;
_ide511 ();*/ =gs_ide536 (i); } static int gs_ide571 ;  static int gs_ide575 ; /*;;
(gs_ide580 ));;*/   static DLLIST gs_ide544 = NULL;  static DLLIST gs_ide545 = NULL;  static DLLIST gs_ide584 = NULL; /*;oss) /+;R/SC;yy+NT =gs_ide536 (i);
};*/   static DLLIST gs_ide585 = NULL;  static int gs_ide551 ; 
#ifdef ANSI_C
static int gs_ide536 (int level)
#else
static int gs_ide536 (level) int level;
#endif
{ GNLIST vl1,vl2; ADJEDGE a; int i; ; assert((gs_ide580 )); assert((gs_ide544 ==NULL)); /*;{
vl1,vl2;;*/ assert((gs_ide584 ==NULL)); assert((level>=0)); assert((level<=maxdepth)); /*;int i;
;;*/   vl1 = (( gs_ide580 [level] ).succlist) /*;;;*/ ; while (vl1) { (( (( vl1 )->node) /*;
544 ==NULL));;*/ )->tmpadj) /*;544 ==NULL));;*/ = (( (( vl1 )->node) /*;
544 ==NULL));;*/ )->succ) /*;544 ==NULL));;*/ ; vl1 = (( vl1 )->next) /*;
ULL));;*/ ; } vl2 = (( gs_ide580 [level+1] ).succlist) /*;(level<=maxdepth));
;*/ ; while (vl2) { (( (( vl2 )->node) /*;while (vl1) {;*/ )->tmpadj) /*;
while (vl1) {;*/ = (( (( vl2 )->node) /*;while (vl1) {;*/ )->pred) /*;
while (vl1) {;*/ ; vl2 = (( vl2 )->next) /*;l1 )->node) /+;R/SC;yy+NT )->tmpadj) /+;
*/ ; } i = 1; vl1 = (( gs_ide580 [level] ).succlist) /*;( gs_ide580 [level+1] ).succlist) /+;
R/;*/ ; while (vl1) { (( (( vl1 )->node) /*;l2 )->node) /+;R/SC;yy+NT )->tmpadj) /+;
*/ )->Vpointer) /*;l2 )->node) /+;R/SC;yy+NT )->tmpadj) /+;*/ = NULL; /*;->next) /+;R/SC;yy+NT ;
};*/  (( (( vl1 )->node) /*;->next) /+;R/SC;yy+NT ;;*/ )->position) /*;->next) /+;
R/SC;yy+NT ;;*/ = i; a = (( (( vl1 )->node) /*;};*/ )->succ) /*;};*/ ; /*;i = 1;
( gs_ide580 [level] ).succlist) /+;R/SC;*/  while (a) { assert(((( ((( (( a )->kante) /*;( gs_ide580 [level] ).succlist) /+;
R/SC;*/ )->end) /*;( gs_ide580 [level] ).succlist) /+;R/SC;*/ ) /*;( gs_ide580 [level] ).succlist) /+;
R/SC;*/ )->tmpadj) /*;( gs_ide580 [level] ).succlist) /+;R/SC;*/ )); /*;while (vl1) {
l1 )->node) /+;R/SC;yy+NT )->Vpointer) ;*/  (( (( ((( (( a )->kante) /*;while (vl1) {;*/ )->end) /*;while (vl1) {
;*/ ) /*;while (vl1) {;*/ )->tmpadj) /*;while (vl1) {;*/ )->kante) /*;
while (vl1) {;*/ = (( a )->kante) /*;while (vl1) {;*/ ; (( ((( (( a )->kante) /*;
l1 )->node) /+;R/SC;yy+NT )->Vpointer) ;*/ )->end) /*;l1 )->node) /+;
R/SC;yy+NT )->Vpointer) ;*/ ) /*;l1 )->node) /+;R/SC;yy+NT )->Vpointer) ;
*/ )->tmpadj) /*;l1 )->node) /+;R/SC;yy+NT )->Vpointer) ;*/ = (( (( ((( (( a )->kante) /*;
l1 )->node) /+;R/SC;yy+NT )->Vpointer) ;*/ )->end) /*;l1 )->node) /+;
R/SC;yy+NT )->Vpointer) ;*/ ) /*;l1 )->node) /+;R/SC;yy+NT )->Vpointer) ;
*/ )->tmpadj) /*;l1 )->node) /+;R/SC;yy+NT )->Vpointer) ;*/ )->next) /*;
l1 )->node) /+;R/SC;yy+NT )->Vpointer) ;*/ ; a = (( a )->next) /*;ode) /+;
R/SC;yy+NT )->position) /+;R/SC;*/ ; } vl1 = (( vl1 )->next) /*;while (a) {
;*/ ; i = i+2; } i = 2; vl2 = (( gs_ide580 [level+1] ).succlist) /*;
+NT ;;*/ ; while (vl2) { (( (( vl2 )->node) /*;( vl1 )->next) /+;R/SC;
yy+NT ;;*/ )->Vpointer) /*;( vl1 )->next) /+;R/SC;yy+NT ;;*/ = NULL; /*;i = i+2;
};*/  (( (( vl2 )->node) /*;i = i+2;;*/ )->position) /*;i = i+2;;*/ = i; a = (( (( vl2 )->node) /*;
};*/ )->pred) /*;};*/ ; while (a) { assert(((( ((( (( a )->kante) /*;
( gs_ide580 [level+1] ).succlist) /+;R/;*/ )->start) /*;( gs_ide580 [level+1] ).succlist) /+;
R/;*/ ) /*;( gs_ide580 [level+1] ).succlist) /+;R/;*/ )->tmpadj) /*;
( gs_ide580 [level+1] ).succlist) /+;R/;*/ )); (( (( ((( (( a )->kante) /*;
while (vl2) {;*/ )->start) /*;while (vl2) {;*/ ) /*;while (vl2) {;*/ )->tmpadj) /*;
while (vl2) {;*/ )->kante) /*;while (vl2) {;*/ = (( a )->kante) /*;while (vl2) {
;*/ ; (( ((( (( a )->kante) /*;l2 )->node) /+;R/SC;yy+NT )->Vpointer) ;
*/ )->start) /*;l2 )->node) /+;R/SC;yy+NT )->Vpointer) ;*/ ) /*;l2 )->node) /+;
R/SC;yy+NT )->Vpointer) ;*/ )->tmpadj) /*;l2 )->node) /+;R/SC;yy+NT )->Vpointer) ;
*/ = (( (( ((( (( a )->kante) /*;l2 )->node) /+;R/SC;yy+NT )->Vpointer) ;
*/ )->start) /*;l2 )->node) /+;R/SC;yy+NT )->Vpointer) ;*/ ) /*;l2 )->node) /+;
R/SC;yy+NT )->Vpointer) ;*/ )->tmpadj) /*;l2 )->node) /+;R/SC;yy+NT )->Vpointer) ;
*/ )->next) /*;l2 )->node) /+;R/SC;yy+NT )->Vpointer) ;*/ ; a = (( a )->next) /*;
ode) /+;R/SC;yy+NT )->position) /+;R/SC;*/ ; } vl2 = (( vl2 )->next) /*;
while (a) {;*/ ; i = i+2; } gs_ide551 = 0; gs_ide575 = gs_ide571 = 0; /*;}
( vl2 )->next) /+;R/SC;yy+NT ;;*/  gs_ide544 = gs_ide545 = NULL; gs_ide584 = gs_ide585 = NULL; vl1 = (( gs_ide580 [level] ).succlist) /*;
i = i+2;;*/ ; vl2 = (( gs_ide580 [level+1] ).succlist) /*;};*/ ; while ((vl1)||(vl2)) { /*;51 = 0;
_ide571 = 0;;*/ if (vl1) { gs_ide527 ((( vl1 )->node) /*; = NULL;;*/ ); vl1 = (( vl1 )->next) /*;
;;*/ ; } if (vl2) { gs_ide526 ((( vl2 )->node) /*;l1)||(vl2)) {;*/ ); /*;if (vl1) {
27 ((( vl1 )->node) /+;R/SC;yy+NT );;*/  vl2 = (( vl2 )->next) /*;if (vl1) {;*/ ; } } assert((gs_ide575 ==0)); /*;) {
vl2 )->node) /+;R/SC;yy+NT );;*/  assert((gs_ide571 ==0)); assert((gs_ide544 ==NULL)); assert((gs_ide584 ==NULL)); /*; /+;R/SC;yy+NT ;
};*/ return(gs_ide551 ); }
#ifdef ANSI_C
static void gs_ide527 (GNODE v)
#else
static void gs_ide527 (v) GNODE v;
#endif
{ ADJEDGE a; DLLIST n,m; int k1;  int k2;  int k3;  ; assert((v)); k1 = k2 = k3 = 0; /*;DLLIST n,m;
;*/ if ((( v )->Vpointer) /*; ;*/ ) { n = gs_ide584 ; while (n) { m = (( n )->succ) /*;
;;*/ ; if ((( n )->node) /*;(v));;*/ == v) { k1++; k3 += k2; gs_ide522 (n); /*;n = gs_ide584 ;
n) {;*/ }  else k2++; if (n==(( v )->Vpointer) /*;R/SC;yy+NT == v) {;*/ ) break; /*;R/SC;yy+NT == v) {
k1++;;*/ n = m; } gs_ide551 += (k1 * gs_ide571 + k3); } a = (( v )->succ) /*;
++;;*/ ; while (a) { if ((( ((( (( a )->kante) /*;n = m;;*/ )->end) /*;
n = m;;*/ ) /*;n = m;;*/ )->position) /*;n = m;;*/ > (( v )->position) /*;
n = m;;*/ ) { gs_ide506 (((( (( a )->kante) /*;};*/ )->end) /*;};*/ ) /*;
};*/ ); (( ((( (( a )->kante) /*;51 += (k1 * gs_ide571 + k3);;*/ )->end) /*;
51 += (k1 * gs_ide571 + k3);;*/ ) /*;51 += (k1 * gs_ide571 + k3);;*/ )->Vpointer) /*;
51 += (k1 * gs_ide571 + k3);;*/ = gs_ide545 ; } a = (( a )->next) /*;
v )->succ) /+;R/SC;yy+NT ;;*/ ; } }
#ifdef ANSI_C
static void gs_ide526 (GNODE v)
#else
static void gs_ide526 (v) GNODE v;
#endif
{ ADJEDGE a; DLLIST n,m; int k1;  int k2;  int k3;  ; assert((v)); k1 = k2 = k3 = 0; /*;DLLIST n,m;
;*/ if ((( v )->Vpointer) /*; ;*/ ) { n = gs_ide544 ; while (n) { m = (( n )->succ) /*;
;;*/ ; if ((( n )->node) /*;(v));;*/ == v) { k1++; k3 += k2; gs_ide521 (n); /*;n = gs_ide544 ;
n) {;*/ }  else k2++; if (n==(( v )->Vpointer) /*;R/SC;yy+NT == v) {;*/ ) break; /*;R/SC;yy+NT == v) {
k1++;;*/ n = m; } gs_ide551 += (k1 * gs_ide575 + k3); } a = (( v )->pred) /*;
++;;*/ ; while (a) { if ((( ((( (( a )->kante) /*;n = m;;*/ )->start) /*;
n = m;;*/ ) /*;n = m;;*/ )->position) /*;n = m;;*/ > (( v )->position) /*;
n = m;;*/ ) { gs_ide507 (((( (( a )->kante) /*;};*/ )->start) /*;};*/ ) /*;
};*/ ); (( ((( (( a )->kante) /*;51 += (k1 * gs_ide575 + k3);;*/ )->start) /*;
51 += (k1 * gs_ide575 + k3);;*/ ) /*;51 += (k1 * gs_ide575 + k3);;*/ )->Vpointer) /*;
51 += (k1 * gs_ide575 + k3);;*/ = gs_ide585 ; } a = (( a )->next) /*;
v )->pred) /+;R/SC;yy+NT ;;*/ ; } }
#ifdef ANSI_C
static void gs_ide507 (GNODE n)
#else
static void gs_ide507 (n) GNODE n;
#endif
{ DLLIST d; assert((n)); ; d = dllist_alloc(n,gs_ide585 ); if (!gs_ide584 ) gs_ide584 = d; /*;/N;D+ n;
{;*/ if (gs_ide585 ) (( gs_ide585 )->succ) /*;{;*/ = d; gs_ide585 = d; gs_ide575 ++; /*;assert((n));
;;*/ }
#ifdef ANSI_C
static void gs_ide506 (GNODE n)
#else
static void gs_ide506 (n) GNODE n;
#endif
{ DLLIST d; assert((n)); ; d = dllist_alloc(n,gs_ide545 ); if (!gs_ide544 ) gs_ide544 = d; /*;/N;D+ n;
{;*/ if (gs_ide545 ) (( gs_ide545 )->succ) /*;{;*/ = d; gs_ide545 = d; gs_ide571 ++; /*;assert((n));
;;*/ }
#ifdef ANSI_C
static void gs_ide522 (DLLIST x)
#else
static void gs_ide522 (x) DLLIST x;
#endif
{ assert((x)); assert(((( x )->node) /*;};*/ )); ; if ((( x )->pred) /*;
_ide522 (x);*/ ) (( (( x )->pred) /*;_ide522 (x);*/ )->succ) /*;_ide522 (x);
*/ = (( x )->succ) /*;_ide522 (x);*/ ; else gs_ide584 = (( x )->succ) /*;
DLLIST x;;*/ ; if ((( x )->succ) /*;{;*/ ) (( (( x )->succ) /*;{;*/ )->pred) /*;
{;*/ = (( x )->pred) /*;{;*/ ; else gs_ide585 = (( x )->pred) /*;(x));
;*/ ; dllist_free(x); gs_ide575 --; }
#ifdef ANSI_C
static void gs_ide521 (DLLIST x)
#else
static void gs_ide521 (x) DLLIST x;
#endif
{ assert((x)); assert(((( x )->node) /*;};*/ )); ; if ((( x )->pred) /*;
_ide521 (x);*/ ) (( (( x )->pred) /*;_ide521 (x);*/ )->succ) /*;_ide521 (x);
*/ = (( x )->succ) /*;_ide521 (x);*/ ; else gs_ide544 = (( x )->succ) /*;
DLLIST x;;*/ ; if ((( x )->succ) /*;{;*/ ) (( (( x )->succ) /*;{;*/ )->pred) /*;
{;*/ = (( x )->pred) /*;{;*/ ; else gs_ide545 = (( x )->pred) /*;(x));
;*/ ; dllist_free(x); gs_ide571 --; }
#ifdef ANSI_C
static void gs_ide557 (int level)
#else
static void gs_ide557 (level) int level;
#endif
{ int i; GNLIST vl; ; if (level>0) { i = 1; vl = (( gs_ide580 [level-1] ).succlist) /*;
{;*/ ; while (vl) { (( (( vl )->node) /*;vl;;*/ )->position) /*;vl;;
*/ = i++; vl = (( vl )->next) /*;;;*/ ; } } if (level<=maxdepth) { i = 1; /*;while (vl) {
l )->node) /+;R/SC;yy+NT )->position) /;*/ vl = (( gs_ide580 [level+1] ).succlist) /*;l )->node) /+;R/SC;yy+NT )->position) /;
*/ ; while (vl) { (( (( vl )->node) /*;};*/ )->position) /*;};*/ = i++; /*;}
};*/ vl = (( vl )->next) /*;};*/ ; } } }
#ifdef ANSI_C
static int gs_ide525 (GNODE C, GNODE D)
#else
static int gs_ide525 (C,D) GNODE C; GNODE D;
#endif
{ GNODE n; DLLIST actlistC, h; ADJEDGE a; int Sum1, Sum2; ; Sum1 = Sum2 = 0; /*;{
;;*/ actlistC = NULL; a = (( C )->pred) /*;C, h;;*/ ; while (a) { actlistC = dllist_alloc(((( (( a )->kante) /*;
1, Sum2;;*/ )->start) /*;1, Sum2;;*/ ) /*;1, Sum2;;*/ ,actlistC); (( actlistC )->succ) /*;
;;*/ = (( actlistC )->pred) /*;;;*/ ;  a = (( a )->next) /*;Sum2 = 0;
;*/ ; } a = (( D )->pred) /*;R/SC;yy+NT ;;*/ ; while (a) { n = ((( (( a )->kante) /*;
C = dllist_alloc(((( (( a )->kante) /+;;*/ )->start) /*;C = dllist_alloc(((( (( a )->kante) /+;
;*/ ) /*;C = dllist_alloc(((( (( a )->kante) /+;;*/ ; h = actlistC; while (h) { /*;R/SC;yy+NT ;
};*/ if ((( n )->position) /*;};*/ <(( (( h )->node) /*;};*/ )->position) /*;
};*/ ) Sum1++; else if ((( n )->position) /*;D )->pred) /+;R/SC;yy+NT ;
;*/ >(( (( h )->node) /*;D )->pred) /+;R/SC;yy+NT ;;*/ )->position) /*;
D )->pred) /+;R/SC;yy+NT ;;*/ ) Sum2++; h = (( h )->succ) /*;while (a) {
;*/ ; } a = (( a )->next) /*;h = actlistC;;*/ ; } dllist_free_all(actlistC); /*;sition) /+;R/SC;yy+NT <(( (( h )->node)
tion) /+;R/SC;yy+NT >(( (( h )->node) /;*/ actlistC = NULL; a = (( C )->succ) /*;+NT ;;*/ ; while (a) { actlistC = dllist_alloc(((( (( a )->kante) /*;
a )->next) /+;R/SC;yy+NT ;;*/ )->end) /*;a )->next) /+;R/SC;yy+NT ;;
*/ ) /*;a )->next) /+;R/SC;yy+NT ;;*/ ,actlistC); (( actlistC )->succ) /*;
};*/ = (( actlistC )->pred) /*;};*/ ;  a = (( a )->next) /*;free_all(actlistC);
;*/ ; } a = (( D )->succ) /*;R/SC;yy+NT ;;*/ ; while (a) { n = ((( (( a )->kante) /*;
C = dllist_alloc(((( (( a )->kante) /+;;*/ )->end) /*;C = dllist_alloc(((( (( a )->kante) /+;
;*/ ) /*;C = dllist_alloc(((( (( a )->kante) /+;;*/ ; h = actlistC; while (h) { /*;R/SC;yy+NT ;
};*/ if ((( n )->position) /*;};*/ <(( (( h )->node) /*;};*/ )->position) /*;
};*/ ) Sum1++; else if ((( n )->position) /*;D )->succ) /+;R/SC;yy+NT ;
;*/ >(( (( h )->node) /*;D )->succ) /+;R/SC;yy+NT ;;*/ )->position) /*;
D )->succ) /+;R/SC;yy+NT ;;*/ ) Sum2++; h = (( h )->succ) /*;while (a) {
;*/ ; } a = (( a )->next) /*;h = actlistC;;*/ ; } dllist_free_all(actlistC); /*;sition) /+;R/SC;yy+NT <(( (( h )->node)
tion) /+;R/SC;yy+NT >(( (( h )->node) /;*/ return(Sum1>Sum2); }
#ifdef ANSI_C
static int gs_ide540 (int level,int nearedges)
#else
static int gs_ide540 (level, nearedges) int level; int nearedges;
#endif
{ int changed, possible; GNLIST vl1, vl2; GNODE n1,n2; ; assert((level>=0)); /*;redges;
{;*/ assert((level<=maxdepth+1)); gs_ide557 (level); changed = 0; vl1 = NULL; /*;/N;D+ n1,n2;
;;*/ vl2 = (( gs_ide580 [level] ).succlist) /*;;;*/ ; while (vl2) { n2 = (( vl2 )->node) /*;
=maxdepth+1));;*/ ; if (vl1) { n1 = (( vl1 )->node) /*; = 0;;*/ ; possible = 1; /*;vl1 = NULL;
( gs_ide580 [level] ).succlist) /+;R/SC;*/ if (nearedges) { if (((( n1 )->connection) /*;while (vl2) {;*/ )||((( n2 )->connection) /*;
while (vl2) {;*/ )) possible = 0; } if ( (possible) &&(gs_ide525 (n1,n2))) { /*;possible = 1;
redges) {;*/ (( vl1 )->node) /*;redges) {;*/ = n2; (( vl2 )->node) /*;connection) /+;
R/SC;yy+NT )||((( n2 )->;*/ = n1;  changed = 1; } } vl1 = vl2; vl2 = (( vl2 )->next) /*;
SC;yy+NT = n2;;*/ ; } return(changed); }
#ifdef ANSI_C
static void gs_ide542 (int nearedges)
#else
static void gs_ide542 (nearedges) int nearedges;
#endif
{ int i; ; if (!local_unwind) return; if (G_timelimit>0) if (test_timelimit(60)) { /*;int nearedges;
{;*/ gs_wait_message('t'); return; } gs_wait_message('l'); for (i=0; i<=maxdepth+1; /*;t>0)
)) {;*/  i++)  while (gs_ide540 (i, nearedges)); }
#ifdef ANSI_C
static void gs_ide558 (void)
#else
static void gs_ide558 ()
#endif
{ GNLIST h1; int i,j; ; for (i=0; i<=maxdepth+1; i++) {  h1 = (( gs_ide580 [i] ).succlist) /*;
_ide558 ();*/ ; j = 0; while (h1) { (( (( h1 )->node) /*;int i,j;;*/ )->position) /*;
int i,j;;*/ = j++; h1 = (( h1 )->next) /*;;;*/ ; } } }
#ifdef ANSI_C
static int gs_ide535 (GNODE v)
#else
static int gs_ide535 (v) GNODE v;
#endif
{ ADJEDGE a; ; if ((( v )->connection) /*;int gs_ide535 (/N;D+ v);*/ ) return(1); /*;int gs_ide535 (/N;D+ v)
ide535 (v);*/ a = (( v )->succ) /*;ide535 (v);*/ ; if (!a) return(1); if ((( a )->next) /*;
{;*/ ) return(1); a = (( v )->pred) /*; a;;*/ ; if (!a) return(1); if ((( a )->next) /*;
v )->connection) /+;R/SC;yy+NT ) return;*/ ) return(1); return(0); }
#ifdef ANSI_C
static int gs_ide513 (GNODE v1,GNODE v2,int dir)
#else
static int gs_ide513 (v1,v2,dir) GNODE v1; GNODE v2; int dir;
#endif
{ int d1,d2; GNODE n1,n2; ; if (gs_ide535 (v1)) return(0); if (gs_ide535 (v2)) return(0); /*;int dir;
{;*/ d1 = (( v1 )->position) /*;{;*/ - (( v2 )->position) /*;{;*/ ; if (d1*d1!=1) return(0); /*;d2;
/N;D+ n1,n2;;*/ if (dir=='S') { n1 = ((( (( (( v1 )->succ) /*;;;*/ )->kante) /*;;;*/ )->end) /*;
;;*/ ) /*;;;*/ ; n2 = ((( (( (( v2 )->succ) /*;ide535 (v1)) return(0);
;*/ )->kante) /*;ide535 (v1)) return(0);;*/ )->end) /*;ide535 (v1)) return(0);
;*/ ) /*;ide535 (v1)) return(0);;*/ ; } else {  n1 = ((( (( (( v1 )->pred) /*;
if (d1*d1!=1) return(0);;*/ )->kante) /*;if (d1*d1!=1) return(0);;*/ )->start) /*;
if (d1*d1!=1) return(0);;*/ ) /*;if (d1*d1!=1) return(0);;*/ ; n2 = ((( (( (( v2 )->pred) /*;
=='S') {;*/ )->kante) /*;=='S') {;*/ )->start) /*;=='S') {;*/ ) /*;=='S') {
;*/ ; } d2 = (( n1 )->position) /*;succ) /+;R/SC;yy+NT )->kante) /+;
R/SC;y;*/ - (( n2 )->position) /*;succ) /+;R/SC;yy+NT )->kante) /+;R/SC;
y;*/ ; if (d1*d2<0) return(1); return(gs_ide513 (n1,n2,dir)); }
#ifdef ANSI_C
static void gs_ide523 (GNODE v1,GNODE v2,int dir)
#else
static void gs_ide523 (v1,v2,dir) GNODE v1; GNODE v2; int dir;
#endif
{ int d1,d2,h; GNODE n1,n2; GNLIST vl1, vl2, vl3; ; if (gs_ide535 (v1)) return; /*;int dir;
{;*/ if (gs_ide535 (v2)) return; d1 = (( v1 )->position) /*;d2,h;;*/ - (( v2 )->position) /*;
d2,h;;*/ ; if (d1*d1!=1) return; assert(((( v1 )->tiefe) /*;vl1, vl2, vl3;
;*/ ==(( v2 )->tiefe) /*;vl1, vl2, vl3;;*/ )); vl1 = vl2 = NULL; vl3 = (( gs_ide580 [(( v1 )->tiefe) /*;
ide535 (v1)) return;;*/ ] ).succlist) /*;ide535 (v1)) return;;*/ ; while (vl3) { /*;(v2)) return;
n) /+;R/SC;yy+NT - (( v2 )->position) /;*/ if ((( vl3 )->node) /*;n) /+;R/SC;yy+NT - (( v2 )->position) /;*/ ==v1) vl1 = vl3; /*;n) /+;R/SC;yy+NT - (( v2 )->position) /
if (d1*d1!=1) return;;*/ if ((( vl3 )->node) /*;if (d1*d1!=1) return;;*/ ==v2) vl2 = vl3; vl3 = (( vl3 )->next) /*;
((( v1 )->tiefe) /+;R/SC;yy+NT ==(( v2 ;*/ ; } assert((vl1)); assert((vl2)); /*;while (vl3) {
vl3 )->node) /+;R/SC;yy+NT ==v1) vl1 = ;*/ (( vl1 )->node) /*;vl3 )->node) /+;R/SC;yy+NT ==v1) vl1 = ;*/ = v2; (( vl2 )->node) /*;
node) /+;R/SC;yy+NT ==v2) vl2 = vl3;;*/ = v1;  h = (( v1 )->position) /*;
/+;R/SC;yy+NT ;;*/ ;  (( v1 )->position) /*;};*/ = (( v2 )->position) /*;
};*/ ; (( v2 )->position) /*;(vl1));;*/ = h;  if (dir=='S') { n1 = ((( (( (( v1 )->succ) /*;
SC;yy+NT = v2;;*/ )->kante) /*;SC;yy+NT = v2;;*/ )->end) /*;SC;yy+NT = v2;
;*/ ) /*;SC;yy+NT = v2;;*/ ; n2 = ((( (( (( v2 )->succ) /*;T = v1; ;
*/ )->kante) /*;T = v1; ;*/ )->end) /*;T = v1; ;*/ ) /*;T = v1; ;*/ ; /*;T ; 
v1 )->position) /+;R/SC;yy+NT = (( v2 ;*/  } else {  n1 = ((( (( (( v1 )->pred) /*;position) /+;R/SC;yy+NT = h;
;*/ )->kante) /*;position) /+;R/SC;yy+NT = h; ;*/ )->start) /*;position) /+;
R/SC;yy+NT = h; ;*/ ) /*;position) /+;R/SC;yy+NT = h; ;*/ ; n2 = ((( (( (( v2 )->pred) /*;
if (dir=='S') {;*/ )->kante) /*;if (dir=='S') {;*/ )->start) /*;if (dir=='S') {
;*/ ) /*;if (dir=='S') {;*/ ; } d2 = (( n1 )->position) /*; v2 )->succ) /+;
R/SC;yy+NT )->kante) /+;*/ - (( n2 )->position) /*; v2 )->succ) /+;R/SC;
yy+NT )->kante) /+;*/ ; if (d1*d2<0) return; gs_ide523 (n1,n2,dir); }
#ifdef ANSI_C
static void gs_ide583 (GNODE v)
#else
static void gs_ide583 (v) GNODE v;
#endif
{ ADJEDGE a1,a2; ; a1 = (( v )->succ) /*;void gs_ide583 (/N;D+ v);*/ ; /*;_ide583 (v)
/N;D+ v;;*/  while (a1) { a2 = (( v )->succ) /*;/N;D+ v;;*/ ; while (a2) { if (gs_ide513 (((( (( a1 )->kante) /*;
a1,a2;;*/ )->end) /*; a1,a2;;*/ ) /*; a1,a2;;*/ ,((( (( a2 )->kante) /*;
a1,a2;;*/ )->end) /*; a1,a2;;*/ ) /*; a1,a2;;*/ ,'S')) { gs_ide523 (((( (( a1 )->kante) /*;
;;*/ )->end) /*;;;*/ ) /*;;;*/ ,((( (( a2 )->kante) /*;;;*/ )->end) /*;
;;*/ ) /*;;;*/ ,'S'); } a2 = (( a2 )->next) /*;while (a1) {;*/ ; } a1 = (( a1 )->next) /*;
while (a2) {;*/ ; } a1 = (( v )->pred) /*; (( a1 )->kante) /+;R/SC;yy+NT )->end) ;
*/ ; while (a1) { a2 = (( v )->pred) /*; a2 )->next) /+;R/SC;yy+NT ;
;*/ ; while (a2) { if (gs_ide513 (((( (( a1 )->kante) /*; a1 )->next) /+;
R/SC;yy+NT ;;*/ )->start) /*; a1 )->next) /+;R/SC;yy+NT ;;*/ ) /*; a1 )->next) /+;
R/SC;yy+NT ;;*/ ,((( (( a2 )->kante) /*; a1 )->next) /+;R/SC;yy+NT ;
;*/ )->start) /*; a1 )->next) /+;R/SC;yy+NT ;;*/ ) /*; a1 )->next) /+;
R/SC;yy+NT ;;*/ ,'P')) { gs_ide523 (((( (( a1 )->kante) /*;};*/ )->start) /*;
};*/ ) /*;};*/ ,((( (( a2 )->kante) /*;};*/ )->start) /*;};*/ ) /*;}
;*/ ,'P'); } a2 = (( a2 )->next) /*;while (a1) {;*/ ; } a1 = (( a1 )->next) /*;
while (a2) {;*/ ; } }
#ifdef ANSI_C
static void gs_ide543 (void)
#else
static void gs_ide543 ()
#endif
{ GNODE v; ; if (G_timelimit>0) if (test_timelimit(60)) { gs_wait_message('t'); /*;_ide543 ()
{;*/ return; } gs_wait_message('l'); gs_ide558 (); v = nodelist; while (v) { /*;
return;;*/ gs_ide583 (v); v = (( v )->next) /*;};*/ ; } } static int gs_ide529 ; /*;while (v) {
83 (v);;*/  static int gs_ide552 ;
#ifdef ANSI_C
static void gs_ide531 (void)
#else
static void gs_ide531 ()
#endif
{ gs_ide529 = 0; gs_ide552 = 1; }
#define tmp_layer_is_better() {          	changed = 1;		         	copy_tmp_layer_to_layer();       	nr_crossings = cross;            	alt_startlevel = tmp_startlevel; } 
#define tmp_layer_is_worser() {          	copy_layer_to_tmp_layer();       	tmp_startlevel = alt_startlevel; }
#define	copy_tmp_layer_to_layer()  { gs_ide518 (layer,gs_ide580 ); }
#define	copy_layer_to_tmp_layer()  { gs_ide518 (gs_ide580 ,layer); }
static int gs_ide553 ;
#ifdef ANSI_C
static void gs_ide510 (void)
#else
static void gs_ide510 ()
#endif
{ int alt;  int cross;  int changed; int tmp_startlevel,alt_startlevel; /*;_ide510 (void)
();*/ ; assert(gs_ide580 ); tmp_startlevel = alt_startlevel = 0; changed = 1; /*;int cross; 
nged;;*/ while (gs_ide552 && changed) { gs_ide550 ++; if (gs_ide550 >=max_baryiterations) { /*;;
gs_ide580 );;*/ gs_wait_message('t'); break; } if (G_timelimit>0) if (test_timelimit(60)) { /*;gs_ide550 ++;
ide550 >=max_baryiterations) {;*/ gs_wait_message('t'); break; } changed = 0; gs_ide500 (); cross = gs_ide528 (); /*;imit(60)) {
;*/ alt = 0; if ( (cross < nr_crossings)  ||(gs_ide550 <min_baryiterations)) { /*;}
= 0;;*/   tmp_layer_is_better();  }  else if (gs_ide529 ) { copy_layer_to_tmp_layer(); /*;alt = 0;
ross < nr_crossings) ;*/ gs_ide500 (); cross = gs_ide528 (); if (cross < nr_crossings) { tmp_layer_is_better(); /*;; 
} ;*/  } else if (cross > nr_crossings) { tmp_layer_is_worser(); } else alt = 1; /*; (gs_ide529 ) {
tmp_layer();;*/ } else if (cross == nr_crossings) alt = 1; else { tmp_layer_is_worser(); /*; gs_ide528 ();
_crossings) { tmp_layer_is_better(); };*/  } gs_ide529 = alt; gs_ide501 (); cross = gs_ide528 (); alt = 0; if ( (cross < nr_crossings)  /*; (cross == nr_crossings) alt = 1;
er_is_worser(); };*/ ||(gs_ide550 <min_baryiterations)) {  tmp_layer_is_better();  }  else if (gs_ide529 ) { /*;528 ();
alt = 0;;*/ copy_layer_to_tmp_layer(); gs_ide501 (); cross = gs_ide528 (); if (cross < nr_crossings) { /*;; 
} ;*/  tmp_layer_is_better(); } else if (cross > nr_crossings) { tmp_layer_is_worser(); /*;} 
(gs_ide529 ) {;*/  } else alt = 1; } else if (cross == nr_crossings) alt = 1; else { tmp_layer_is_worser(); /*; gs_ide528 ();
_crossings) { tmp_layer_is_better(); };*/  } gs_ide529 = alt; if (nr_crossings==0) return;  } if (nr_crossings==0) return; /*;}
(cross == nr_crossings) alt = 1;;*/   if (skip_baryphase2) return; gs_ide552 = 0;  tmp_startlevel = alt_startlevel = 0; /*;gs_ide529 = alt;
crossings==0) return; ;*/ changed = 1; while (changed) { gs_ide550 ++; if (gs_ide550 >=max_baryiterations) { /*;hase2) return;
gs_ide552 = 0; ;*/ gs_wait_message('t'); break; } if (G_timelimit>0) if (test_timelimit(60)) { /*;gs_ide550 ++;
ide550 >=max_baryiterations) {;*/ gs_wait_message('t'); break; } changed = 0; gs_ide553 = tmp_startlevel; /*;imelimit>0)
imit(60)) {;*/ gs_ide502 (); tmp_startlevel = gs_ide553 ; if (tmp_startlevel > maxdepth) tmp_startlevel = 0; /*;break;
};*/ cross = gs_ide528 (); alt = 0; if (cross < nr_crossings) { tmp_layer_is_better(); /*;p_startlevel;
gs_ide502 ();;*/  }  else if (gs_ide529 ) { copy_layer_to_tmp_layer(); gs_ide553 = tmp_startlevel = alt_startlevel; /*;evel > maxdepth) tmp_startlevel = 0;
;*/ gs_ide502 (); tmp_startlevel = gs_ide553 ; if (tmp_startlevel > maxdepth) tmp_startlevel = 0; /*;ss < nr_crossings) { tmp_layer_is_bette
e529 ) {;*/ cross = gs_ide528 (); if (cross < nr_crossings) { tmp_layer_is_better(); /*;er();
alt_startlevel;;*/  } else if (cross > nr_crossings) { tmp_layer_is_worser(); } else alt = 1; /*;gs_ide502 ();
rtlevel = gs_ide553 ;;*/ } else if (cross == nr_crossings) alt = 1; else { tmp_layer_is_worser(); /*;
tmp_layer_is_better(); };*/  } gs_ide529 = alt; if (nr_crossings==0) return; } tmp_startlevel = alt_startlevel = maxdepth+1; /*;}
(cross == nr_crossings) alt = 1;;*/ changed = 1; while (changed) { gs_ide550 ++; if (gs_ide550 >=max_baryiterations) { /*;crossings==0) return;
};*/ gs_wait_message('t'); break; } if (G_timelimit>0) if (test_timelimit(60)) { /*;gs_ide550 ++;
ide550 >=max_baryiterations) {;*/ gs_wait_message('t'); break; } changed = 0; gs_ide553 = tmp_startlevel; /*;imelimit>0)
imit(60)) {;*/ gs_ide503 (); tmp_startlevel = gs_ide553 ; if (tmp_startlevel < 0) tmp_startlevel = maxdepth; /*;break;
};*/ cross = gs_ide528 (); alt = 0; if (cross < nr_crossings) { tmp_layer_is_better(); /*;p_startlevel;
gs_ide503 ();;*/  }  else if (gs_ide529 ) { copy_layer_to_tmp_layer(); gs_ide553 = tmp_startlevel = alt_startlevel; /*;evel < 0) tmp_startlevel = maxdepth;
;*/ gs_ide503 (); tmp_startlevel = gs_ide553 ; if (tmp_startlevel < 0) tmp_startlevel = maxdepth; /*;ss < nr_crossings) { tmp_layer_is_bette
e529 ) {;*/ cross = gs_ide528 (); if (cross < nr_crossings) { tmp_layer_is_better(); /*;er();
alt_startlevel;;*/  } else if (cross > nr_crossings) { tmp_layer_is_worser(); } else alt = 1; /*;gs_ide503 ();
rtlevel = gs_ide553 ;;*/ } else if (cross == nr_crossings) alt = 1; else { tmp_layer_is_worser(); /*;
tmp_layer_is_better(); };*/  } gs_ide529 = alt; if (nr_crossings==0) return; } }
#ifdef ANSI_C
static void gs_ide500 (void)
#else
static void gs_ide500 ()
#endif
{ int i; ; gs_wait_message('b'); for (i=0; i<=maxdepth; i++) (void)gs_ide561 (i); /*;void gs_ide500 (void)
_ide500 ();*/ 
#ifdef CHECK_CROSSING
i = gs_ide528 (); gs_ide511 (); assert((i==gs_ide528 ())); PRINTF("Phase1_down: nr_crossings old: %d new: %d\n",nr_crossings,i); /*;;
_message('b');;*/  
#endif
}
#ifdef ANSI_C
static void gs_ide501 (void)
#else
static void gs_ide501 ()
#endif
{ int i; ; gs_wait_message('b'); for (i=maxdepth; i>=0; i--) (void)gs_ide564 (i); /*;void gs_ide501 (void)
_ide501 ();*/ 
#ifdef CHECK_CROSSING
i = gs_ide528 (); gs_ide511 (); assert((i==gs_ide528 ())); PRINTF("Phase1_up: nr_crossings old: %d new: %d\n",nr_crossings,i); /*;;
_message('b');;*/  
#endif
}
#ifdef ANSI_C
static int gs_ide561 (int i)
#else
static int gs_ide561 (i) int i;
#endif
{ int c; int j; ; assert((i>=0)); assert((i<=maxdepth));  gs_ide541 (i+1,'d'); /*;{
int c;;*/ switch (crossing_heuristics) { case 0: for (j=0; j<(( layer[i+1] ).anz) /*;
int j;;*/ ; j++) (( gs_ide577 [j] )->bary) /*;;;*/ = gs_ide554 (gs_ide577 [j]); /*;;
(i>=0));;*/ break; case 1: for (j=0; j<(( layer[i+1] ).anz) /*;depth)); ;*/ ; j++) (( gs_ide577 [j] )->bary) /*;
gs_ide541 (i+1,'d');;*/ = gs_ide555 (gs_ide577 [j]); break; case 2: for (j=0; /*;=0; j<(( layer[i+1] ).anz) /+;R/SC;yy+N
ary) /+;R/SC;yy+NT = gs_ide554 (gs_ide5;*/  j<(( layer[i+1] ).anz) /*;=0; j<(( layer[i+1] ).anz) /+;R/SC;yy+N;*/ ; /*;=0; j<(( layer[i+1] ).anz) /+;R/SC;yy+N
ary) /+;R/SC;yy+NT = gs_ide554 (gs_ide5;*/  j++) (( gs_ide577 [j] )->bary) /*;ary) /+;R/SC;yy+NT = gs_ide554 (gs_ide5;
*/ = gs_ide554 (gs_ide577 [j]) + gs_ide555 (gs_ide577 [j])/10000.0; break; /*; for (j=0; j<(( layer[i+1] ).anz) /+;R/
j] )->bary) /+;R/SC;yy+NT = gs_ide555 (;*/ case 3: for (j=0; j<(( layer[i+1] ).anz) /*;j] )->bary) /+;R/SC;yy+NT = gs_ide555 (;
*/ ; j++) (( gs_ide577 [j] )->bary) /*;break;;*/ = gs_ide555 (gs_ide577 [j]) /*;break;
for (j=0; j<(( layer[i+1] ).anz) /+;R/;*/ + gs_ide554 (gs_ide577 [j])/10000.0; break; } quicksort_sort_array((( layer[i+1] ).anz) /*;
break;;*/ ); gs_ide570 (i+1);  gs_ide509 (i+1); if ((( layer[i+1] ).resort_necessary) /*;
7 [j])*10000.0;;*/ ) gs_ide508 (i+1);  c = gs_ide536 (i); if (c <= (( gs_ide580 [i] ).cross) /*;
};*/ ) { (( gs_ide580 [i] ).cross) /*;rt_sort_array((( layer[i+1] ).anz) /+;
R;*/ = c; if (i<maxdepth) (( gs_ide580 [i+1] ).cross) /*;); ;*/ = gs_ide536 (i+1); /*;); 
gs_ide509 (i+1);;*/   return(1); } gs_ide565 (i+1); return(0); }
#ifdef ANSI_C
static int gs_ide564 (int i)
#else
static int gs_ide564 (i) int i;
#endif
{ int c; int j; ; assert((i>=0)); assert((i<=maxdepth));  gs_ide541 (i,'u'); /*;{
int c;;*/ switch (crossing_heuristics) { case 0: for (j=0; j<(( layer[i] ).anz) /*;
int j;;*/ ; j++) (( gs_ide577 [j] )->bary) /*;;;*/ = gs_ide578 (gs_ide577 [j]); /*;;
(i>=0));;*/ break; case 1: for (j=0; j<(( layer[i] ).anz) /*;depth)); ;*/ ; j++) (( gs_ide577 [j] )->bary) /*;
gs_ide541 (i,'u');;*/ = gs_ide579 (gs_ide577 [j]); break; case 2: for (j=0; /*;=0; j<(( layer[i] ).anz) /+;R/SC;yy+NT 
ary) /+;R/SC;yy+NT = gs_ide578 (gs_ide5;*/  j<(( layer[i] ).anz) /*;=0; j<(( layer[i] ).anz) /+;R/SC;yy+NT ;*/ ; /*;=0; j<(( layer[i] ).anz) /+;R/SC;yy+NT 
ary) /+;R/SC;yy+NT = gs_ide578 (gs_ide5;*/  j++) (( gs_ide577 [j] )->bary) /*;ary) /+;R/SC;yy+NT = gs_ide578 (gs_ide5;
*/ = gs_ide578 (gs_ide577 [j]) + gs_ide579 (gs_ide577 [j])/10000.0; break; /*; for (j=0; j<(( layer[i] ).anz) /+;R/SC
j] )->bary) /+;R/SC;yy+NT = gs_ide579 (;*/ case 3: for (j=0; j<(( layer[i] ).anz) /*;j] )->bary) /+;R/SC;yy+NT = gs_ide579 (;
*/ ; j++) (( gs_ide577 [j] )->bary) /*;break;;*/ = gs_ide579 (gs_ide577 [j]) /*;break;
for (j=0; j<(( layer[i] ).anz) /+;R/SC;*/ + gs_ide578 (gs_ide577 [j])/10000.0; break; } quicksort_sort_array((( layer[i] ).anz) /*;
break;;*/ ); gs_ide570 (i);  gs_ide509 (i); if ((( layer[i] ).resort_necessary) /*;
7 [j])*10000.0;;*/ ) gs_ide508 (i);  c = gs_ide536 (i); if (c <= (( gs_ide580 [i] ).cross) /*;
};*/ ) { (( gs_ide580 [i] ).cross) /*;rt_sort_array((( layer[i] ).anz) /+;
R/S;*/ = c; if (i>0) (( gs_ide580 [i-1] ).cross) /*; ;*/ = gs_ide536 (i-1); /*; 
gs_ide509 (i);;*/   return(1); } gs_ide565 (i); return(0); }
#ifdef ANSI_C
static void gs_ide502 (void)
#else
static void gs_ide502 ()
#endif
{ int i,j; int cross; ; gs_wait_message('B'); if (gs_ide553 <= maxdepth) /*;_ide502 ()
{;*/ for (i=gs_ide553 ; i<=maxdepth; i++) { if (G_timelimit>0) if (test_timelimit(60)) { /*;int cross;
;;*/ gs_wait_message('t'); break; } gs_ide541 (i,'u'); switch (crossing_heuristics) { /*;if (/_timelimit>0)
t_timelimit(60)) {;*/ case 0: for (j=0; j<(( layer[i] ).anz) /*;t_timelimit(60)) {;*/ ; j++) (( gs_ide577 [j] )->bary) /*;
e('t');;*/ = gs_ide578 (gs_ide577 [j]); break; case 1: for (j=0; j<(( layer[i] ).anz) /*;
};*/ ; j++) (( gs_ide577 [j] )->bary) /*;41 (i,'u');;*/ = gs_ide579 (gs_ide577 [j]); /*;41 (i,'u');
ng_heuristics) {;*/ break; case 2: for (j=0; j<(( layer[i] ).anz) /*;( layer[i] ).anz) /+;
R/SC;yy+NT ; j++);*/ ; j++) (( gs_ide577 [j] )->bary) /*;;R/SC;yy+NT = gs_ide578 (gs_ide577 [j]);
*/ = gs_ide578 (gs_ide577 [j]) + gs_ide579 (gs_ide577 [j])/10000.0; break; /*; for (j=0; j<(( layer[i] ).anz) /+;R/SC
j] )->bary) /+;R/SC;yy+NT = gs_ide579 (;*/ case 3: for (j=0; j<(( layer[i] ).anz) /*;j] )->bary) /+;R/SC;yy+NT = gs_ide579 (;
*/ ; j++) (( gs_ide577 [j] )->bary) /*;break;;*/ = gs_ide579 (gs_ide577 [j]) /*;break;
for (j=0; j<(( layer[i] ).anz) /+;R/SC;*/ + gs_ide578 (gs_ide577 [j])/10000.0; break; } quicksort_sort_array((( layer[i] ).anz) /*;
break;;*/ ); if (gs_ide520 ((( layer[i] ).anz) /*; for (j=0; j<(( layer[i] ).anz) /+;
R/SC;*/ )) { gs_ide509 (i); if ((( layer[i] ).resort_necessary) /*;7 [j])*10000.0;
;*/ ) gs_ide508 (i);  if (i>0) (( gs_ide580 [i-1] ).cross) /*;break;
;*/ = gs_ide536 (i-1); if (i<=maxdepth) (( gs_ide580 [i] ).cross) /*;
};*/ = gs_ide536 (i); gs_ide563 (i); cross = gs_ide528 (); if (cross < nr_crossings) { /*;gs_ide509 (i);
layer[i] ).resort_necessary) /+;R/SC;yy;*/  
#ifdef CHECK_CROSSING
j = gs_ide528 (); gs_ide511 (); assert((j==gs_ide528 ())); PRINTF("Phase2_down: nr_crossings old: %d new: %d\n",nr_crossings,j); /*;gs_ide563 (i);
gs_ide528 ();;*/  
#endif
gs_ide553 = i+1; return;  }  } } for (i=0; (i<gs_ide553 ) && (i<=maxdepth); /*;nr_crossings old: %d new: %dzn ,nr_cros
gs_ide553 = i+1;;*/  i++) { if (G_timelimit>0) if (test_timelimit(60)) { gs_wait_message('t'); /*;} 
};*/ break; } gs_ide541 (i,'u'); switch (crossing_heuristics) { case 0: for (j=0; /*;)) {
gs_wait_message('t');;*/  j<(( layer[i] ).anz) /*;)) {;*/ ; j++) (( gs_ide577 [j] )->bary) /*;
gs_wait_message('t');;*/ = gs_ide554 (gs_ide577 [j]); break; case 1: for (j=0; /*;}
41 (i,'u');;*/  j<(( layer[i] ).anz) /*;};*/ ; j++) (( gs_ide577 [j] )->bary) /*;41 (i,'u');
;*/ = gs_ide555 (gs_ide577 [j]); break; case 2: for (j=0; j<(( layer[i] ).anz) /*;
( layer[i] ).anz) /+;R/SC;yy+NT ; j++);*/ ; j++) (( gs_ide577 [j] )->bary) /*;
;R/SC;yy+NT = gs_ide554 (gs_ide577 [j]);*/ = gs_ide554 (gs_ide577 [j]) + gs_ide555 (gs_ide577 [j])/10000.0; /*;break;
for (j=0; j<(( layer[i] ).anz) /+;R/SC;*/ break; case 3: for (j=0; j<(( layer[i] ).anz) /*;j] )->bary) /+;R/SC;
yy+NT = gs_ide555 (;*/ ; j++) (( gs_ide577 [j] )->bary) /*;break;;*/ = gs_ide555 (gs_ide577 [j]) /*;break;
for (j=0; j<(( layer[i] ).anz) /+;R/SC;*/ + gs_ide554 (gs_ide577 [j])/10000.0; break; } quicksort_sort_array((( layer[i] ).anz) /*;
break;;*/ ); if (gs_ide520 ((( layer[i] ).anz) /*; for (j=0; j<(( layer[i] ).anz) /+;
R/SC;*/ )) { gs_ide509 (i); if ((( layer[i] ).resort_necessary) /*;7 [j])*10000.0;
;*/ ) gs_ide508 (i);  if (i>0) (( gs_ide580 [i-1] ).cross) /*;break;
;*/ = gs_ide536 (i-1); if (i<=maxdepth) (( gs_ide580 [i] ).cross) /*;
};*/ = gs_ide536 (i); gs_ide563 (i); cross = gs_ide528 (); if (cross < nr_crossings) { /*;gs_ide509 (i);
layer[i] ).resort_necessary) /+;R/SC;yy;*/  
#ifdef CHECK_CROSSING
j = gs_ide528 (); gs_ide511 (); assert((j==gs_ide528 ())); PRINTF("Phase2_down: nr_crossings old: %d new: %d\n",nr_crossings,j); /*;gs_ide563 (i);
gs_ide528 ();;*/  
#endif
gs_ide553 = i+1; return;  }  } }
#ifdef CHECK_CROSSING
i = gs_ide528 (); gs_ide511 (); assert((i==gs_ide528 ())); PRINTF("Phase2_down: nr_crossings old: %d new: %d\n",nr_crossings,i); /*;} 
};*/  
#endif
}
#ifdef ANSI_C
static void gs_ide503 (void)
#else
static void gs_ide503 ()
#endif
{ int i,j; int cross; ; gs_wait_message('B'); if (gs_ide553 > 0) for (i=gs_ide553 ; /*;{
;;*/  i>0; i--) { if (G_timelimit>0) if (test_timelimit(60)) { gs_wait_message('t'); /*;;
_message('B');;*/ break; } gs_ide541 (i,'d'); switch (crossing_heuristics) { case 0: for (j=0; /*;t_timelimit(60)) {
e('t');;*/  j<(( layer[i] ).anz) /*;t_timelimit(60)) {;*/ ; j++) (( gs_ide577 [j] )->bary) /*;
e('t');;*/ = gs_ide554 (gs_ide577 [j]); break; case 1: for (j=0; j<(( layer[i] ).anz) /*;
};*/ ; j++) (( gs_ide577 [j] )->bary) /*;41 (i,'d');;*/ = gs_ide555 (gs_ide577 [j]); /*;41 (i,'d');
ng_heuristics) {;*/ break; case 2: for (j=0; j<(( layer[i] ).anz) /*;( layer[i] ).anz) /+;
R/SC;yy+NT ; j++);*/ ; j++) (( gs_ide577 [j] )->bary) /*;;R/SC;yy+NT = gs_ide554 (gs_ide577 [j]);
*/ = gs_ide554 (gs_ide577 [j]) + gs_ide555 (gs_ide577 [j])/10000.0; break; /*; for (j=0; j<(( layer[i] ).anz) /+;R/SC
j] )->bary) /+;R/SC;yy+NT = gs_ide555 (;*/ case 3: for (j=0; j<(( layer[i] ).anz) /*;j] )->bary) /+;R/SC;yy+NT = gs_ide555 (;
*/ ; j++) (( gs_ide577 [j] )->bary) /*;break;;*/ = gs_ide579 (gs_ide577 [j]) /*;break;
for (j=0; j<(( layer[i] ).anz) /+;R/SC;*/ + gs_ide554 (gs_ide577 [j])/10000.0; break; } quicksort_sort_array((( layer[i] ).anz) /*;
break;;*/ ); if (gs_ide520 ((( layer[i] ).anz) /*; for (j=0; j<(( layer[i] ).anz) /+;
R/SC;*/ )) { gs_ide509 (i); if ((( layer[i] ).resort_necessary) /*;7 [j])*10000.0;
;*/ ) gs_ide508 (i);  if (i>0) (( gs_ide580 [i-1] ).cross) /*;break;
;*/ = gs_ide536 (i-1); if (i<=maxdepth) (( gs_ide580 [i] ).cross) /*;
};*/ = gs_ide536 (i); gs_ide562 (i); cross = gs_ide528 (); if (cross < nr_crossings) { /*;gs_ide509 (i);
layer[i] ).resort_necessary) /+;R/SC;yy;*/  
#ifdef CHECK_CROSSING
j = gs_ide528 (); gs_ide511 (); assert((j==gs_ide528 ())); PRINTF("Phase2_up: nr_crossings old: %d new: %d\n",nr_crossings,j); /*;gs_ide562 (i);
gs_ide528 ();;*/  
#endif
gs_ide553 = i-1; return;  }  } } for (i=maxdepth+1; (i>gs_ide553 ) && (i>0); /*;_crossings old: %d new: %dzn ,nr_crossi
gs_ide553 = i-1;;*/  i--) { if (G_timelimit>0) if (test_timelimit(60)) { gs_wait_message('t'); /*;} 
};*/ break; } gs_ide541 (i,'d'); switch (crossing_heuristics) { case 0: for (j=0; /*;)) {
gs_wait_message('t');;*/  j<(( layer[i] ).anz) /*;)) {;*/ ; j++) (( gs_ide577 [j] )->bary) /*;
gs_wait_message('t');;*/ = gs_ide554 (gs_ide577 [j]); break; case 1: for (j=0; /*;}
41 (i,'d');;*/  j<(( layer[i] ).anz) /*;};*/ ; j++) (( gs_ide577 [j] )->bary) /*;41 (i,'d');
;*/ = gs_ide555 (gs_ide577 [j]); break; case 2: for (j=0; j<(( layer[i] ).anz) /*;
( layer[i] ).anz) /+;R/SC;yy+NT ; j++);*/ ; j++) (( gs_ide577 [j] )->bary) /*;
;R/SC;yy+NT = gs_ide554 (gs_ide577 [j]);*/ = gs_ide554 (gs_ide577 [j]) + gs_ide555 (gs_ide577 [j])/10000.0; /*;break;
for (j=0; j<(( layer[i] ).anz) /+;R/SC;*/ break; case 3: for (j=0; j<(( layer[i] ).anz) /*;j] )->bary) /+;R/SC;
yy+NT = gs_ide555 (;*/ ; j++) (( gs_ide577 [j] )->bary) /*;break;;*/ = gs_ide555 (gs_ide577 [j]) /*;break;
for (j=0; j<(( layer[i] ).anz) /+;R/SC;*/ + gs_ide554 (gs_ide577 [j])/10000.0; break; } quicksort_sort_array((( layer[i] ).anz) /*;
break;;*/ ); if (gs_ide520 ((( layer[i] ).anz) /*; for (j=0; j<(( layer[i] ).anz) /+;
R/SC;*/ )) { gs_ide509 (i); if ((( layer[i] ).resort_necessary) /*;7 [j])*10000.0;
;*/ ) gs_ide508 (i);  if (i>0) (( gs_ide580 [i-1] ).cross) /*;break;
;*/ = gs_ide536 (i-1);  if (i<=maxdepth) (( gs_ide580 [i] ).cross) /*;
};*/ = gs_ide536 (i); gs_ide562 (i); cross = gs_ide528 (); if (cross < nr_crossings) { /*;gs_ide509 (i);
layer[i] ).resort_necessary) /+;R/SC;yy;*/  
#ifdef CHECK_CROSSING
j = gs_ide528 (); gs_ide511 (); assert((j==gs_ide528 ())); PRINTF("Phase2_up: nr_crossings old: %d new: %d\n",nr_crossings,j); /*;gs_ide562 (i);
gs_ide528 ();;*/  
#endif
gs_ide553 = i-1; return;  }  } }
#ifdef CHECK_CROSSING
i = gs_ide528 (); gs_ide511 (); assert((i==gs_ide528 ())); PRINTF("Phase2_up: nr_crossings old: %d new: %d\n",nr_crossings,i); /*;} 
};*/  
#endif
}
#ifdef ANSI_C
static void gs_ide563 (int level)
#else
static void gs_ide563 (level) int level;
#endif
{ int change; int i; ; change = 1; if (level>0) { for (i=level-1;i>=0; /*;{
nge;;*/  i--) { change = gs_ide564 (i); if (!change) break;  } } if (level<=maxdepth) { /*;
i--) {;*/ for (i=level; i<=maxdepth; i++) { change = gs_ide561 (i); if (!change) break; /*;ange) break; 
};*/   } } }
#ifdef ANSI_C
static void gs_ide562 (int level)
#else
static void gs_ide562 (level) int level;
#endif
{ int change; int i; ; change = 1; if (level<=maxdepth) { for (i=level; /*;{
nge;;*/  i<=maxdepth; i++) { change = gs_ide561 (i); if (!change) break;  } } /*;depth) {
epth; i++) {;*/  if (level>0) { for (i=level-1;i>=0; i--) { change = gs_ide564 (i); if (!change) break; /*;ange) break; 
};*/   } } }
#ifdef ANSI_C
static int gs_ide520 (int siz)
#else
static int gs_ide520 (siz) int siz;
#endif
{ int j,k; int original_sit;  int start_region;  GNODE h; ; original_sit = 1; /*;{
;;*/ start_region = -1; for (j=0; j<siz-1; j++) { if ( (( gs_ide577 [j] )->bary) /*;
int start_region; ;*/ == (( gs_ide577 [j+1] )->bary) /*;int start_region;
;*/ ) { if (start_region == -1) start_region = j;  } else if (start_region != -1) { /*;l_sit = 1;
-1;;*/ h = gs_ide577 [j]; for (k=j; k>start_region; k--) gs_ide577 [k] = gs_ide577 [k-1]; /*;y) /+;R/SC;yy+NT == (( gs_ide577 [j+1] 
n = j; ;*/ gs_ide577 [start_region] = h; start_region = -1; original_sit = 0; } /*;ion; k--)
-1];;*/  }  if (start_region != -1) { h = gs_ide577 [j]; for (k=j; k>start_region; /*;egion = -1;
0;;*/  k--) gs_ide577 [k] = gs_ide577 [k-1]; gs_ide577 [start_region] = h; /*;} 
rt_region != -1) {;*/  original_sit = 0; } return(!original_sit); }
#ifdef ANSI_C
static float gs_ide578 (GNODE node)
#else
static float gs_ide578 (node) GNODE node;
#endif
{ int Sum; ADJEDGE w; assert((node)); ; if ((( node )->outdegree) /*;
/N;D+ node;;*/ ==0) return(0.0); Sum = 0; w = (( node )->succ) /*;;;
*/ ; while (w) { Sum += (256 * (( ((( (( w )->kante) /*;(node));;*/ )->end) /*;
(node));;*/ ) /*;(node));;*/ )->position) /*;(node));;*/ ); Sum -= (( (( w )->kante) /*;
;;*/ )->anchor) /*;;;*/ ; w = (( w )->next) /*;node )->outdegree) /+;
R/SC;yy+NT ==0) r;*/ ; } return ( ((float) Sum) / ((float) (256*(( node )->outdegree) /*;
node )->succ) /+;R/SC;yy+NT ;;*/ )) ); }
#ifdef ANSI_C
static float gs_ide554 (GNODE node)
#else
static float gs_ide554 (node) GNODE node;
#endif
{ int Sum; ADJEDGE w; assert((node)); ; if ((( node )->indegree) /*;
/N;D+ node;;*/ ==0) return(0.0); Sum = 0; w = (( node )->pred) /*;;;
*/ ; while (w) { Sum += (256 * (( ((( (( w )->kante) /*;(node));;*/ )->start) /*;
(node));;*/ ) /*;(node));;*/ )->position) /*;(node));;*/ ); Sum += (( (( w )->kante) /*;
;;*/ )->anchor) /*;;;*/ ; w = (( w )->next) /*;node )->indegree) /+;
R/SC;yy+NT ==0) re;*/ ; } return ( ((float) Sum) / ((float) (256*(( node )->indegree) /*;
node )->pred) /+;R/SC;yy+NT ;;*/ )) ); }
#ifdef ANSI_C
static float gs_ide579 (GNODE node)
#else
static float gs_ide579 (node) GNODE node;
#endif
{ int i, leftpart, rightpart; ADJEDGE w; assert((node)); ; switch ((( node )->outdegree) /*;
/N;D+ node;;*/ ) { case 0: return(0.0); case 1: return((float) (( ((( (( (( node )->succ) /*;
leftpart, rightpart;;*/ )->kante) /*;leftpart, rightpart;;*/ )->end) /*;
leftpart, rightpart;;*/ ) /*;leftpart, rightpart;;*/ )->position) /*;
leftpart, rightpart;;*/ - (float)(( (( (( node )->succ) /*;ADJ+D/+ w;
;*/ )->kante) /*;ADJ+D/+ w;;*/ )->anchor) /*;ADJ+D/+ w;;*/ /256.0); case 2:  /*;(node));
;;*/ w = (( node )->succ) /*;;;*/ ; i = (( ((( (( w )->kante) /*;((( node )->outdegree) /+;
R/SC;yy+NT ) ;*/ )->end) /*;((( node )->outdegree) /+;R/SC;yy+NT ) ;
*/ ) /*;((( node )->outdegree) /+;R/SC;yy+NT ) ;*/ )->position) /*;((( node )->outdegree) /+;
R/SC;yy+NT ) ;*/ ; w = (( w )->next) /*;(0.0);;*/ ; i += (( ((( (( w )->kante) /*;
) (( ((( (( (( node )->succ) /+;R/SC;yy;*/ )->end) /*;) (( ((( (( (( node )->succ) /+;
R/SC;yy;*/ ) /*;) (( ((( (( (( node )->succ) /+;R/SC;yy;*/ )->position) /*;
) (( ((( (( (( node )->succ) /+;R/SC;yy;*/ ; return ( ((float) i) / 2.0); /*;) /+;R/SC;yy+NT )->kante) /+;R/SC;yy+NT
case 2: ;*/ } i = 0; w = (( node )->succ) /*;w )->kante) /+;R/SC;yy+NT )->end) /+;
R/;*/ ; while (w) { gs_ide569 [i++] = ((( (( w )->kante) /*;+;R/SC;yy+NT )->end) /+;
R/SC;yy+NT ) /+;*/ )->end) /*;+;R/SC;yy+NT )->end) /+;R/SC;yy+NT ) /+;
*/ ) /*;+;R/SC;yy+NT )->end) /+;R/SC;yy+NT ) /+;*/ ; w = (( w )->next) /*;
return ( ((float) i) * 2.0);;*/ ; } quicksort_save_array(i); if (i % 2) return((float)(( gs_ide569 [i/2] )->position) /*;
node )->succ) /+;R/SC;yy+NT ;;*/ ); leftpart = (( gs_ide569 [i/2-1] )->position) /*;
while (w) {;*/ - (( gs_ide569 [0] )->position) /*;while (w) {;*/ ; rightpart = (( gs_ide569 [i-1] )->position) /*;
69 [i++] = ((( (( w )->kante) /+;R/SC;y;*/ - (( gs_ide569 [i/2] )->position) /*;
69 [i++] = ((( (( w )->kante) /+;R/SC;y;*/ ; return ( ((float)  ((( gs_ide569 [i/2-1] )->position) /*;
};*/ * rightpart +  (( gs_ide569 [i/2] )->position) /*;rt_save_array(i);
;*/ * leftpart))  / ((float) (leftpart+rightpart)) ); }
#ifdef ANSI_C
static float gs_ide555 (GNODE node)
#else
static float gs_ide555 (node) GNODE node;
#endif
{ int i, leftpart, rightpart; ADJEDGE w; assert((node)); ; switch ((( node )->indegree) /*;
/N;D+ node;;*/ ) { case 0: return(0.0); case 1: return((float) (( ((( (( (( node )->pred) /*;
leftpart, rightpart;;*/ )->kante) /*;leftpart, rightpart;;*/ )->start) /*;
leftpart, rightpart;;*/ ) /*;leftpart, rightpart;;*/ )->position) /*;
leftpart, rightpart;;*/ + (float)(( (( (( node )->pred) /*;ADJ+D/+ w;
;*/ )->kante) /*;ADJ+D/+ w;;*/ )->anchor) /*;ADJ+D/+ w;;*/ /256.0); case 2:  /*;(node));
;;*/ w = (( node )->pred) /*;;;*/ ; i = (( ((( (( w )->kante) /*;((( node )->indegree) /+;
R/SC;yy+NT ) {;*/ )->start) /*;((( node )->indegree) /+;R/SC;yy+NT ) {
;*/ ) /*;((( node )->indegree) /+;R/SC;yy+NT ) {;*/ )->position) /*;
((( node )->indegree) /+;R/SC;yy+NT ) {;*/ ; w = (( w )->next) /*;(0.0);
;*/ ; i += (( ((( (( w )->kante) /*;) (( ((( (( (( node )->pred) /+;
R/SC;yy;*/ )->start) /*;) (( ((( (( (( node )->pred) /+;R/SC;yy;*/ ) /*;
) (( ((( (( (( node )->pred) /+;R/SC;yy;*/ )->position) /*;) (( ((( (( (( node )->pred) /+;
R/SC;yy;*/ ; return ( ((float) i) / 2.0); } i = 0; w = (( node )->pred) /*;
w )->kante) /+;R/SC;yy+NT )->start) /+;;*/ ; while (w) { gs_ide569 [i++] = ((( (( w )->kante) /*;
+;R/SC;yy+NT )->start) /+;R/SC;yy+NT ) ;*/ )->start) /*;+;R/SC;yy+NT )->start) /+;
R/SC;yy+NT ) ;*/ ) /*;+;R/SC;yy+NT )->start) /+;R/SC;yy+NT ) ;*/ ; w = (( w )->next) /*;
return ( ((float) i) * 2.0);;*/ ; } quicksort_save_array(i); if (i % 2) return((float)(( gs_ide569 [i/2] )->position) /*;
node )->pred) /+;R/SC;yy+NT ;;*/ ); leftpart = (( gs_ide569 [i/2-1] )->position) /*;
while (w) {;*/ - (( gs_ide569 [0] )->position) /*;while (w) {;*/ ; rightpart = (( gs_ide569 [i-1] )->position) /*;
69 [i++] = ((( (( w )->kante) /+;R/SC;y;*/ - (( gs_ide569 [i/2] )->position) /*;
69 [i++] = ((( (( w )->kante) /+;R/SC;y;*/ ; return ( ((float)  ((( gs_ide569 [i/2-1] )->position) /*;
};*/ * rightpart +  (( gs_ide569 [i/2] )->position) /*;rt_save_array(i);
;*/ * leftpart))  / ((float) (leftpart+rightpart)) ); }
#ifdef ANSI_C
static int gs_ide514 (const GNODE *a, const GNODE *b)
#else
static int gs_ide514 (a,b) GNODE *a; GNODE *b;
#endif
{  if (((( *a )->bary) /*;};*/ ==0.0) || ((( *b )->bary) /*;};*/ ==0.0)) return(0); /*;}
int gs_ide514 (const /N;D+ *a, const /N;*/ if ((( *a )->bary) /*;int gs_ide514 (const /N;D+ *a, const /N;*/ > (( *b )->bary) /*;
int gs_ide514 (const /N;D+ *a, const /N;*/ ) return(1); if ((( *a )->bary) /*;
ide514 (a,b);*/ < (( *b )->bary) /*;ide514 (a,b);*/ ) return(-1); return(0); /*;/N;D+ *a;
b;;*/ }
#ifdef ANSI_C
static int gs_ide515 (const GNODE *a, const GNODE *b)
#else
static int gs_ide515 (a,b) GNODE *a; GNODE *b;
#endif
{  if ((( *a )->position) /*;};*/ > (( *b )->position) /*;};*/ ) return(1); /*;}
int gs_ide515 (const /N;D+ *a, const /N;*/ if ((( *a )->position) /*;int gs_ide515 (const /N;D+ *a, const /N;*/ < (( *b )->position) /*;
int gs_ide515 (const /N;D+ *a, const /N;*/ ) return(-1); return(0); }
#ifdef OWN_QUICKSORT
#define exchange(a,b) { t=a; a=b; b=t; }
#ifdef ANSI_C
static void gs_ide549 (int l, int r)
#else
static void gs_ide549 (l, r) int l, r;
#endif
{ int i, j, k; GNODE v, t; k = r-l; if (k>5) {  j = l + (gs_ide559 % k); /*;int l, r;
{;*/   gs_ide559 = (gs_ide559 + 10891) % MAXINT; exchange(gs_ide577 [l],gs_ide577 [j]); /*;j, k;
/N;D+ v, t;;*/   } v=gs_ide577 [l]; i=l; j=r+1; if ((( v )->bary) /*;if (k>5) { ;*/ ==0.0) j=l+k/2; /*;if (k>5) { 
(gs_ide559 % k); ;*/   else { while (i<j) { do j--; while ( ((( gs_ide577 [j] )->bary) /*;
],gs_ide577 [j]); ;*/ !=0.0) &&((( gs_ide577 [j] )->bary) /*;};*/ >(( v )->bary) /*;
};*/ )); do i++; while ((i<=j)&&((( gs_ide577 [i] )->bary) /*;e577 [l];
i=l; j=r+1;;*/ !=0.0)  &&((( gs_ide577 [i] )->bary) /*;ry) /+;R/SC;
yy+NT ==0.0) j=l+k*2; ;*/ <(( v )->bary) /*;ry) /+;R/SC;yy+NT ==0.0) j=l+k*2;
;*/ )); if (i<j) exchange(gs_ide577 [j],gs_ide577 [i]);  }; } exchange(gs_ide577 [l],gs_ide577 [j]); /*;->bary) /+;R/SC;yy+NT >(( v )->bary) /+
s_ide577 [i] )->bary) /+;R/SC;yy+NT !=0;*/   if (l<j-1) gs_ide549 (l,j-1); if (j+1<r) gs_ide549 (j+1,r); }
#endif
#ifdef ANSI_C
static void gs_ide541 (int i,int dir)
#else
static void gs_ide541 (i,dir) int i; int dir;
#endif
{ int j; GNLIST hn; ; hn = (( gs_ide580 [i] ).succlist) /*;int i;;*/ ; /*;;
{;*/  j = 0; while (hn) { gs_ide577 [j++] = (( hn )->node) /*;int j;;*/ ; /*;hn;
;;*/  hn = (( hn )->next) /*;hn;;*/ ; } if (dir=='d') { assert((i>0)); hn = (( gs_ide580 [i-1] ).succlist) /*;
hn) {;*/ ; } else { assert((i<maxdepth+1)); hn = (( gs_ide580 [i+1] ).succlist) /*;
=='d') {;*/ ; } j = 1; while (hn) { (( (( hn )->node) /*;else {;*/ )->position) /*;
else {;*/ = j++; hn = (( hn )->next) /*;(i<maxdepth+1));;*/ ; } }
#ifdef ANSI_C
static void gs_ide509 (int i)
#else
static void gs_ide509 (i) int i;
#endif
{ int j; GNLIST hn; ; j = 0; hn = (( gs_ide580 [i] ).succlist) /*;int i;
;*/ ; while (hn) { (( hn )->node) /*;int j;;*/ = gs_ide577 [j++]; hn = (( hn )->next) /*;
hn;;*/ ; } assert(j==(( gs_ide580 [i] ).anz) /*;j = 0;;*/ ); }
#ifdef ANSI_C
static void gs_ide570 (int i)
#else
static void gs_ide570 (i) int i;
#endif
{ int j; GNLIST hn; ; j = 0; hn = (( gs_ide580 [i] ).succlist) /*;int i;
;*/ ; while (hn) { gs_ide569 [j++] = (( hn )->node) /*;int j;;*/ ; hn = (( hn )->next) /*;
hn;;*/ ; } assert(j==(( gs_ide580 [i] ).anz) /*;j = 0;;*/ ); }
#ifdef ANSI_C
static void gs_ide565 (int i)
#else
static void gs_ide565 (i) int i;
#endif
{ int j; GNLIST hn; ; j = 0; hn = (( gs_ide580 [i] ).succlist) /*;int i;
;*/ ; while (hn) { (( hn )->node) /*;int j;;*/ = gs_ide569 [j++]; hn = (( hn )->next) /*;
hn;;*/ ; } assert(j==(( gs_ide580 [i] ).anz) /*;j = 0;;*/ ); }
#ifdef ANSI_C
static void gs_ide508 (int i)
#else
static void gs_ide508 (i) int i;
#endif
{ GNLIST hn; int j; ; hn = (( gs_ide580 [i] ).succlist) /*;_ide508 (i);
*/ ; j = 0; while (hn) { if ((( (( hn )->node) /*;hn;;*/ )->nhorder) /*;
hn;;*/ >=0) {  gs_ide577 [j++] = (( hn )->node) /*;int j;;*/ ; (( (( hn )->node) /*;
;;*/ )->bary) /*;;;*/ = (( (( hn )->node) /*;;;*/ )->nhorder) /*;;;*/ ; /*;;
gs_ide580 [i] ).succlist) /+;R/SC;yy+N;*/ } hn = (( hn )->next) /*;j = 0;;*/ ; } quicksort_sort_array(j); hn = (( gs_ide580 [i] ).succlist) /*;
hn )->node) /+;R/SC;yy+NT ;;*/ ; j = 0; while (hn) { if ((( (( hn )->node) /*;
hn )->next) /+;R/SC;yy+NT ;;*/ )->nhorder) /*; hn )->next) /+;R/SC;
yy+NT ;;*/ >=0)  (( hn )->node) /*;};*/ = gs_ide577 [j++]; hn = (( hn )->next) /*;
rt_sort_array(j);;*/ ; } }
#ifdef ANSI_C
static void gs_ide518 (DEPTH *l1,DEPTH *l2)
#else
static void gs_ide518 (l1,l2) DEPTH *l1; DEPTH *l2;
#endif
{ int i; GNLIST h1,h2; ; for (i=0; i<=maxdepth+1; i++) {  (( l1[i] ).cross) /*;
l2;;*/ = (( l2[i] ).cross) /*;l2;;*/ ; h1 = (( l1[i] ).succlist) /*;
{;*/ ; h2 = (( l2[i] ).succlist) /*;int i;;*/ ; if ((( l1[i] ).anz) /*;
h1,h2;;*/ ==(( l2[i] ).anz) /*;h1,h2;;*/ ) { while (h2) { assert((h1)); /*;0; i<=maxdepth+1; i++) { 
ss) /+;R/SC;yy+NT = (( l2[i] ).cross) /;*/   (( h1 )->node) /*;ss) /+;R/SC;yy+NT = (( l2[i] ).cross) /;*/ = (( h2 )->node) /*;
ss) /+;R/SC;yy+NT = (( l2[i] ).cross) /;*/ ; h1 = (( h1 )->next) /*;
ist) /+;R/SC;yy+NT ;;*/ ; h2 = (( h2 )->next) /*;;R/SC;yy+NT ;;*/ ; } /*;ile (h2) {
1)); ;*/  } else { assert (((( l1[i] ).anz) /*;+;R/SC;yy+NT = (( h2 )->node) /+;
R/SC;y;*/ <(( l2[i] ).anz) /*;+;R/SC;yy+NT = (( h2 )->node) /+;R/SC;
y;*/ )); while (h2) { assert((h1));  (( h1 )->node) /*;};*/ = (( h2 )->node) /*;
};*/ ; h2 = (( h2 )->next) /*;};*/ ; if (h2 && !(( h1 )->next) /*;else {
;*/ )  (( h1 )->next) /*;(((( l1[i] ).anz) /+;R/SC;yy+NT <(( l2[;*/ = tmpnodelist_alloc(); /*;(((( l1[i] ).anz) /+;R/SC;yy+NT <(( l2[
while (h2) {;*/ h1 = (( h1 )->next) /*;while (h2) {;*/ ; } (( l1[i] ).anz) /*; /+;R/SC;
yy+NT = (( h2 )->node) /+;R/SC;*/ = (( l2[i] ).anz) /*; /+;R/SC;yy+NT = (( h2 )->node) /+;
R/SC;*/ ; } } }
#define forward_connection1(c)  (((( c )->edge)  )&& ((( (( c )->edge)   )->end)  ==(( c )->target)  ))
#define forward_connection2(c)  (((( c )->edge2)  )&&((( (( c )->edge2)   )->end)  ==(( c )->target2)  ))
#ifdef ANSI_C
static void gs_ide532 (void)
#else
static void gs_ide532 ()
#endif
{ int i,j; GNLIST hl,hln; CONNECT c; int forward_conn; int changed; ; /*;;
;*/  for (i=0; i<=maxdepth+1; i++) {  hl = (( gs_ide580 [i] ).succlist) /*;
;*/ ; changed = 0; while (hl) { hln = (( hl )->next) /*;int changed;
;*/ ; c = (( (( hl )->node) /*;;;*/ )->connection) /*;;;*/ ; forward_conn = 0; /*;0; i<=maxdepth+1; i++) { 
580 [i] ).succlist) /+;R/SC;yy+NT ;;*/ if (c) { if (forward_connection1(c)) forward_conn = 1; if (forward_connection2(c)) /*;>next) /+;R/SC;yy+NT ;
/+;R/SC;yy+NT )->connection) /+;R/SC;y;*/ forward_conn = 1; } if (forward_conn&&((( (( hl )->node) /*;{;*/ )->markiert) /*;
{;*/ ==0)) { changed = 1; gs_ide512 (i,(( hl )->node) /*;forward_conn = 1;
;*/ );  } hl = hln; } if (changed) { if (i<=maxdepth)  (( gs_ide580 [i] ).cross) /*;
12 (i,(( hl )->node) /+;R/SC;yy+NT ); ;*/ = gs_ide536 (i); for (j=i; /*;}
n;;*/  j<=maxdepth; j++)  (void)gs_ide561 (j); } } } static GNLIST gs_ide538 ; /*;oss) /+;R/SC;yy+NT = gs_ide536 (i);
;*/   static GNLIST gs_ide539 ;  static GNLIST gs_ide567 ;  static GNLIST gs_ide568 ; /*;}
};*/   static GNLIST *gs_ide534 ;  static GNLIST gs_ide548 ;  static GNLIST gs_ide524 ; /*;/NLIST gs_ide538 ; 
gs_ide539 ; ;*/  
#ifdef ANSI_C
static void gs_ide512 (int level,GNODE node)
#else
static void gs_ide512 (level,node) int level; GNODE node;
#endif
{ CONNECT c; int j,clr, crl; ADJEDGE a; ; c = (( node )->connection) /*;
/N;D+ node;;*/ ; (( node )->succ) /*;{;*/ = (( node )->savesucc) /*;
{;*/ ; (( node )->pred) /*; c;;*/ = (( node )->savepred) /*; c;;*/ ; /*;;
ADJ+D/+ a;;*/  j = 0; a = (( node )->succ) /*;ADJ+D/+ a;;*/ ; while (a) { j++; a = (( a )->next) /*;
;;*/ ; } (( node )->outdegree) /*;node )->connection) /+;R/SC;yy+NT ;
;*/ = j; j = 0; a = (( node )->pred) /*;/SC;yy+NT = (( node )->savepred) /+;
R/S;*/ ; while (a) { j++; a = (( a )->next) /*;j = 0;;*/ ; } (( node )->indegree) /*;
node )->succ) /+;R/SC;yy+NT ;;*/ = j; gs_ide538 = gs_ide539 = gs_ide567 = gs_ide568 = NULL; /*;+; a = (( a )->next) /+;R/SC;yy+NT ; }
/+;R/SC;yy+NT = j;;*/ if (forward_connection1(c)) gs_ide537 ((( c )->target) /*; /+;R/SC;yy+NT = j;
;*/ ,node); if (forward_connection2(c)) gs_ide566 ((( c )->target2) /*;
j = 0;;*/ ,node); gs_ide533 (level,node); clr = 0; if (level>0) clr+=gs_ide536 (level-1); /*;/+;R/SC;yy+NT = j;
de567 = gs_ide568 = NULL;;*/ if (level<=maxdepth) clr+=gs_ide536 (level); *gs_ide534 = gs_ide548 ; /*; (forward_connection2(c)) gs_ide566 (((
(level,node);;*/  (( gs_ide548 )->next) /*; (forward_connection2(c)) gs_ide566 (((;*/ = gs_ide524 ; /*; (forward_connection2(c)) gs_ide566 (((
(level,node);;*/ gs_ide538 = gs_ide539 = gs_ide567 = gs_ide568 = NULL; if (forward_connection1(c)) gs_ide566 ((( c )->target) /*;
clr = 0;;*/ ,node); if (forward_connection2(c)) gs_ide537 ((( c )->target2) /*;
el>0) clr+=gs_ide536 (level-1);;*/ ,node); gs_ide533 (level,node); crl = 0; /*;8 ;
C;yy+NT = gs_ide524 ;;*/ if (level>0) crl+=gs_ide536 (level-1); if (level<=maxdepth) crl+=gs_ide536 (level); /*; gs_ide568 = NULL;
(forward_connection1(c)) gs_ide566 (((;*/ if (crl<=clr) return; *gs_ide534 = gs_ide548 ; (( gs_ide548 )->next) /*;
,node);;*/ = gs_ide524 ; gs_ide538 = gs_ide539 = gs_ide567 = gs_ide568 = NULL; /*;crl = 0;
el>0) crl+=gs_ide536 (level-1);;*/ if (forward_connection1(c)) gs_ide537 ((( c )->target) /*;el>0) crl+=gs_ide536 (level-1);
;*/ ,node); if (forward_connection2(c)) gs_ide566 ((( c )->target2) /*;
depth) crl+=gs_ide536 (level);;*/ ,node); gs_ide533 (level,node); }
#ifdef ANSI_C
static void gs_ide533 (int level,GNODE node)
#else
static void gs_ide533 (level,node) int level; GNODE node;
#endif
{ GNLIST hl,*hlp; int j; ; hlp = &(( gs_ide580 [level] ).succlist) /*;
int level;;*/ ; hl = (( gs_ide580 [level] ).succlist) /*;ode;;*/ ; while (hl) { /*;{
hl,*hlp;;*/ if ((( hl )->node) /*;hl,*hlp;;*/ ==node) break; hlp = &(( hl )->next) /*;
int j;;*/ ; hl = (( hl )->next) /*;;;*/ ; } assert((hl));  gs_ide534 = hlp; /*;while (hl) {
hl )->node) /+;R/SC;yy+NT ==node) break;*/ gs_ide548 = hl; gs_ide524 = (( hl )->next) /*;->next) /+;R/SC;yy+NT ;
;*/ ; if (gs_ide538 ) {  *hlp = gs_ide538 ; (( gs_ide539 )->next) /*;
(hl)); ;*/ = hl; } hlp = &(( hl )->next) /*;gs_ide548 = hl;;*/ ; hl = (( hl )->next) /*;
24 = (( hl )->next) /+;R/SC;yy+NT ;;*/ ; if (gs_ide567 ) {  *hlp = gs_ide567 ; /*;*hlp = gs_ide538 ;
de539 )->next) /+;R/SC;yy+NT = hl;;*/ (( gs_ide568 )->next) /*;de539 )->next) /+;R/SC;yy+NT = hl;;*/ = hl; /*;(( hl )->next) /+;R/SC;yy+NT ;
next) /+;R/SC;yy+NT ;;*/  } j = 0; hl = (( gs_ide580 [level] ).succlist) /*;next) /+;R/SC;yy+NT ;
;*/ ; while (hl) { j++; hl = (( hl )->next) /*;->next) /+;R/SC;yy+NT = hl;
;*/ ; } (( gs_ide580 [level] ).anz) /*;j = 0;;*/ = j; }
#ifdef ANSI_C
static void gs_ide537 (GNODE v,GNODE w)
#else
static void gs_ide537 (v,w) GNODE v; GNODE w;
#endif
{ GNLIST h; ADJEDGE e; CONNECT c; ; e = (( v )->succ) /*;;;*/ ; while (e) { /*;{
h;;*/  ((( (( e )->kante) /*;{;*/ )->start) /*;{;*/ ) /*;{;*/ = v; e = (( e )->next) /*;
{;*/ ; } e = (( v )->pred) /*;h;;*/ ; while (e) { ((( (( e )->kante) /*;
ADJ+D/+ e;;*/ )->end) /*;ADJ+D/+ e;;*/ ) /*;ADJ+D/+ e;;*/ = v; e = (( e )->next) /*;
ADJ+D/+ e;;*/ ; } h = tmpnodelist_alloc(); (( h )->node) /*;;;*/ = v; /*;v )->succ) /+;R/SC;yy+NT ;
( (( e )->kante) /+;R/SC;yy+NT )->start;*/  (( h )->next) /*;v )->succ) /+;R/SC;yy+NT ;;*/ = gs_ide538 ; gs_ide538 = h; /*;( (( e )->kante) /+;R/SC;yy+NT )->start
R/SC;yy+NT ;;*/ if (!gs_ide539 ) gs_ide539 = h;  c = (( v )->connection) /*;e) /+;R/SC;
yy+NT )->end) /+;R/SC;yy+NT ;*/ ; if (!c) return; if ((( c )->target) /*;
>node) /+;R/SC;yy+NT = v;;*/ && ((( c )->target) /*;>node) /+;R/SC;yy+NT = v;
;*/ !=w)) gs_ide537 ((( c )->target) /*;>node) /+;R/SC;yy+NT = v;;*/ ,v); /*;>node) /+;R/SC;yy+NT = v;
/+;R/SC;yy+NT = gs_ide538 ;;*/ if ((( c )->target2) /*;/+;R/SC;yy+NT = gs_ide538 ;;*/ && ((( c )->target2) /*;
/+;R/SC;yy+NT = gs_ide538 ;;*/ !=w)) gs_ide537 ((( c )->target2) /*;
/+;R/SC;yy+NT = gs_ide538 ;;*/ ,v); }
#ifdef ANSI_C
static void gs_ide566 (GNODE v,GNODE w)
#else
static void gs_ide566 (v,w) GNODE v; GNODE w;
#endif
{ GNLIST h; ADJEDGE e; CONNECT c; ; e = (( v )->succ) /*;;;*/ ; while (e) { /*;{
h;;*/  ((( (( e )->kante) /*;{;*/ )->start) /*;{;*/ ) /*;{;*/ = v; e = (( e )->next) /*;
{;*/ ; } e = (( v )->pred) /*;h;;*/ ; while (e) { ((( (( e )->kante) /*;
ADJ+D/+ e;;*/ )->end) /*;ADJ+D/+ e;;*/ ) /*;ADJ+D/+ e;;*/ = v; e = (( e )->next) /*;
ADJ+D/+ e;;*/ ; } h = tmpnodelist_alloc(); (( h )->node) /*;;;*/ = v; /*;v )->succ) /+;R/SC;yy+NT ;
( (( e )->kante) /+;R/SC;yy+NT )->start;*/  if (gs_ide568 ) (( gs_ide568 )->next) /*;v )->succ) /+;R/SC;yy+NT ;
;*/ = h; (( h )->next) /*;( (( e )->kante) /+;R/SC;yy+NT )->start;*/ = NULL; /*;( (( e )->kante) /+;R/SC;yy+NT )->start
R/SC;yy+NT ;;*/ gs_ide568 = h; if (!gs_ide567 ) gs_ide567 = h;  c = (( v )->connection) /*;
h = tmpnodelist_alloc();;*/ ; if (!c) return; if ((( c )->target) /*;
) (( gs_ide568 )->next) /+;R/SC;yy+NT =;*/ && ((( c )->target) /*;) (( gs_ide568 )->next) /+;
R/SC;yy+NT =;*/ !=w)) gs_ide566 ((( c )->target) /*;) (( gs_ide568 )->next) /+;
R/SC;yy+NT =;*/ ,v); if ((( c )->target2) /*;;yy+NT = NULL;;*/ && ((( c )->target2) /*;
;yy+NT = NULL;;*/ !=w)) gs_ide566 ((( c )->target2) /*;;yy+NT = NULL;
;*/ ,v); }
#ifdef ANSI_C
static void gs_ide560 (void)
#else
static void gs_ide560 ()
#endif
{ GNLIST h1,h2; int i,j,k; ; for (i=0; i<=maxdepth+1; i++) {  h1 = (( layer[i] ).succlist) /*;
_ide560 ();*/ ; j = 0; while (h1) { (( (( h1 )->node) /*;int i,j,k;;
*/ )->position) /*;int i,j,k;;*/ = j++; h1 = (( h1 )->next) /*;;;*/ ; /*;0; i<=maxdepth+1; i++) { 
i] ).succlist) /+;R/SC;yy+NT ;;*/  } } for (i=0; i<=maxdepth+1; i++) {  h1 = (( layer[i] ).succlist) /*;
h1) {;*/ ; (( layer[i] ).predlist) /*;de) /+;R/SC;yy+NT )->position) /+;
R/SC;;*/ = NULL; k = 0; while (h1) { k++; h2 = tmpnodelist_alloc(); (( h2 )->next) /*;
i] ).succlist) /+;R/SC;yy+NT ;;*/ = (( layer[i] ).predlist) /*;i] ).succlist) /+;
R/SC;yy+NT ;;*/ ; (( layer[i] ).predlist) /*;t) /+;R/SC;yy+NT = NULL;
;*/ = h2; (( h2 )->node) /*;k = 0;;*/ = (( h1 )->node) /*;k = 0;;*/ ; /*;h1) {
k++;;*/  gs_ide576 ((( h1 )->node) /*;h1) {;*/ );  h1 = (( h1 )->next) /*;k++;
;*/ ; } assert(((( layer[i] ).anz) /*; /+;R/SC;yy+NT = (( layer[i] ).predlist;
*/ == k)); } }
#ifdef ANSI_C
static void gs_ide576 (GNODE v)
#else
static void gs_ide576 (v) GNODE v;
#endif
{ int i; ADJEDGE a; ; assert((v)); i = 0; a = (( v )->pred) /*;{;*/ ; /*;int i;
a;;*/  while (a) { gs_ide505 [i++] = (( a )->kante) /*; a;;*/ ; a = (( a )->next) /*;
;;*/ ; }
#ifdef ANSI_C
qsort(gs_ide505 ,(( v )->indegree) /*;i = 0;;*/ ,sizeof(GNODE), (int (*) (const void *, const void *))gs_ide516 ); /*;v )->pred) /+;R/SC;yy+NT ;
while (a) {;*/ 
#else
qsort(gs_ide505 ,(( v )->indegree) /*;while (a) {;*/ ,sizeof(GNODE), gs_ide516 ); /*;while (a) {
05 [i++] = (( a )->kante) /+;R/SC;yy+NT;*/ 
#endif
i = 0; a = (( v )->pred) /*;xt) /+;R/SC;yy+NT ;;*/ ; while (a) { (( a )->kante) /*;
s_ide505 ,(( v )->indegree) /+;R/SC;yy+;*/ = gs_ide505 [i++]; a = (( a )->next) /*;
t void *, const void *))gs_ide516 );;*/ ; } (( v )->predleft) /*;i = 0;
;*/ = (( v )->predright) /*;i = 0;;*/ = 0; if (i) {  (( v )->predleft) /*;
while (a) {;*/ = gs_ide505 [0]; (( v )->predright) /*;>kante) /+;R/SC;
yy+NT = gs_ide505 [i++];*/ = gs_ide505 [i-1]; } i = 0; a = (( v )->succ) /*;
>predleft) /+;R/SC;yy+NT = (( v )->pred;*/ ; while (a) { gs_ide505 [i++] = (( a )->kante) /*;
>predleft) /+;R/SC;yy+NT = gs_ide505 [0;*/ ; a = (( a )->next) /*;ght) /+;
R/SC;yy+NT = gs_ide505 [i-1];;*/ ; }
#ifdef ANSI_C
qsort(gs_ide505 ,(( v )->outdegree) /*;i = 0;;*/ ,sizeof(GNODE), (int (*) (const void *, const void *))gs_ide517 ); /*;v )->succ) /+;R/SC;yy+NT ;
while (a) {;*/ 
#else
qsort(gs_ide505 ,(( v )->outdegree) /*;while (a) {;*/ ,sizeof(GNODE),gs_ide517 ); /*;while (a) {
05 [i++] = (( a )->kante) /+;R/SC;yy+NT;*/ 
#endif
i = 0; a = (( v )->succ) /*;xt) /+;R/SC;yy+NT ;;*/ ; while (a) { (( a )->kante) /*;
s_ide505 ,(( v )->outdegree) /+;R/SC;yy;*/ = gs_ide505 [i++]; a = (( a )->next) /*;
t void *, const void *))gs_ide517 );;*/ ; } (( v )->succleft) /*;i = 0;
;*/ = (( v )->succright) /*;i = 0;;*/ = 0; if (i) {  (( v )->succleft) /*;
while (a) {;*/ = gs_ide505 [0]; (( v )->succright) /*;>kante) /+;R/SC;
yy+NT = gs_ide505 [i++];*/ = gs_ide505 [i-1]; } }
#ifdef ANSI_C
static int gs_ide516 (const GEDGE *a, const GEDGE *b)
#else
static int gs_ide516 (a,b) GEDGE *a; GEDGE *b;
#endif
{  if ((( (( *a )->start) /*;};*/ )->position) /*;};*/ > (( (( *b )->start) /*;
};*/ )->position) /*;};*/ ) return(1); if ((( (( *a )->start) /*;int gs_ide516 (const /+D/+ *a, const /+;
*/ )->position) /*;int gs_ide516 (const /+D/+ *a, const /+;*/ < (( (( *b )->start) /*;
int gs_ide516 (const /+D/+ *a, const /+;*/ )->position) /*;int gs_ide516 (const /+D/+ *a, const /+;
*/ ) return(-1); return(0); }
#ifdef ANSI_C
static int gs_ide517 (const GEDGE *a, const GEDGE *b)
#else
static int gs_ide517 (a,b) GEDGE *a; GEDGE *b;
#endif
{  if ((( (( *a )->end) /*;};*/ )->position) /*;};*/ > (( (( *b )->end) /*;
};*/ )->position) /*;};*/ ) return(1); if ((( (( *a )->end) /*;int gs_ide517 (const /+D/+ *a, const /+;
*/ )->position) /*;int gs_ide517 (const /+D/+ *a, const /+;*/ < (( (( *b )->end) /*;
int gs_ide517 (const /+D/+ *a, const /+;*/ )->position) /*;int gs_ide517 (const /+D/+ *a, const /+;
*/ ) return(-1); return(0); }
#ifdef DEBUG
#ifdef ANSI_C
void db_output_all_layers(void)
#else
void db_output_all_layers()
#endif
{ int i; for (i=0; i<=maxdepth+1; i++) db_output_layer(i);  PRINTF("\n"); /*;}
_output_all_layers(void);*/ }
#endif
#ifdef DEBUG
#ifdef ANSI_C
void db_output_layer(int i)
#else
void db_output_layer(i) int i;
#endif
{ GNLIST li; ADJEDGE li2; PRINTF("layer[%d]: ", i); li = (( gs_ide580 [i] ).succlist) /*;
_layer(i);*/ ; while (li) { if ((( (( li )->node) /*;{;*/ )->title) /*;
{;*/ [0]) PRINTF("%s[", (( (( li )->node) /*;li;;*/ )->title) /*;li;
;*/ ); else PRINTF("?["); li2 = (( (( li )->node) /*; layer[%d]:  , i);
;*/ )->pred) /*; layer[%d]:  , i);;*/ ; while (li2) { if ((( ((( (( li2 )->kante) /*;
while (li) {;*/ )->start) /*;while (li) {;*/ ) /*;while (li) {;*/ )->title) /*;
while (li) {;*/ [0]) PRINTF("%s,", (( ((( (( li2 )->kante) /*;(( li )->node) /+;
R/SC;yy+NT )->title) ;*/ )->start) /*;(( li )->node) /+;R/SC;yy+NT )->title) ;
*/ ) /*;(( li )->node) /+;R/SC;yy+NT )->title) ;*/ )->title) /*;(( li )->node) /+;
R/SC;yy+NT )->title) ;*/ ); else PRINTF("?,"); li2 = (( li2 )->next) /*;
else PRINTF( ?[ );;*/ ; } PRINTF("]["); li2 = (( (( li )->node) /*;((( (( li2 )->kante) /+;
R/SC;yy+NT )->s;*/ )->succ) /*;((( (( li2 )->kante) /+;R/SC;yy+NT )->s;
*/ ; while (li2) { if ((( ((( (( li2 )->kante) /*;else PRINTF( ?, );
;*/ )->end) /*;else PRINTF( ?, );;*/ ) /*;else PRINTF( ?, );;*/ )->title) /*;
else PRINTF( ?, );;*/ [0]) PRINTF("%s,", (( ((( (( li2 )->kante) /*;
( li2 )->next) /+;R/SC;yy+NT ;;*/ )->end) /*;( li2 )->next) /+;R/SC;
yy+NT ;;*/ ) /*;( li2 )->next) /+;R/SC;yy+NT ;;*/ )->title) /*;( li2 )->next) /+;
R/SC;yy+NT ;;*/ ); else PRINTF("?,"); li2 = (( li2 )->next) /*; ][ );
;*/ ; } PRINTF("]"); PRINTF("b(%f)p(%d) ",(( (( li )->node) /*;((( (( li2 )->kante) /+;
R/SC;yy+NT )->e;*/ )->bary) /*;((( (( li2 )->kante) /+;R/SC;yy+NT )->e;
*/ ,(( (( li )->node) /*;((( (( li2 )->kante) /+;R/SC;yy+NT )->e;*/ )->position) /*;
((( (( li2 )->kante) /+;R/SC;yy+NT )->e;*/ ); li = (( li )->next) /*;
(( ((( (( li2 )->kante) /+;R/SC;yy+NT );*/ ; } PRINTF("\n"); }
#endif
#ifdef DEBUG
#ifdef ANSI_C
int db_check_proper(GNODE v,int level)
#else
int db_check_proper(v,level) GNODE v; int level;
#endif
{ int t; char *title,*st,*tt; ADJEDGE li; if ((( v )->title) /*;/N;D+ v;
;*/ [0]) title = (( v )->title) /*;el;;*/ ; else title = "?"; t = (( v )->tiefe) /*;
int t;;*/ ; if (level!=t) PRINTF("%s at level %d, expected %d\n",title,t,level); /*;ADJ+D/+ li;
v )->title) /+;R/SC;yy+NT [0]);*/ li = (( v )->succ) /*;v )->title) /+;R/SC;yy+NT [0]);*/ ; while (li) { /*;else title =  ? ;
v )->tiefe) /+;R/SC;yy+NT ;;*/  if (!(( li )->kante) /*;else title =  ? ;;*/ ) { PRINTF("%s missing edge\n",title); /*;else title =  ? ;
v )->tiefe) /+;R/SC;yy+NT ;;*/  break; } if (!((( (( li )->kante) /*;v )->tiefe) /+;R/SC;yy+NT ;;*/ )->start) /*;
v )->tiefe) /+;R/SC;yy+NT ;;*/ ) /*;v )->tiefe) /+;R/SC;yy+NT ;;*/ ) { /*;v )->tiefe) /+;R/SC;yy+NT ;
if (level!=t);*/   PRINTF("Succedge at %s missing source\n",title);  break;  } if (!((( (( li )->kante) /*;
while (li) {;*/ )->end) /*;while (li) {;*/ ) /*;while (li) {;*/ ) {  PRINTF("Succedge at %s missing source\n",title); /*; li )->kante) /+;R/SC;yy+NT ) { PRINTF(
)->kante) /+;R/SC;yy+NT )->start) /+;R;*/   break;  } if ((( ((( (( li )->kante) /*;break; ;*/ )->start) /*;break;
;*/ ) /*;break; ;*/ )->title) /*;break; ;*/ [0]) st = (( ((( (( li )->kante) /*;
};*/ )->start) /*;};*/ ) /*;};*/ )->title) /*;};*/ ; else st = "?"; if ((( ((( (( li )->kante) /*;
ge at %s missing sourcezn ,title); ;*/ )->end) /*;ge at %s missing sourcezn ,title);
;*/ ) /*;ge at %s missing sourcezn ,title); ;*/ )->title) /*;ge at %s missing sourcezn ,title);
;*/ [0]) tt = (( ((( (( li )->kante) /*;break; ;*/ )->end) /*;break;
;*/ ) /*;break; ;*/ )->title) /*;break; ;*/ ; else tt = "?"; if (((( (( li )->kante) /*;
((( (( li )->kante) /+;R/SC;yy+NT )->st;*/ )->start) /*;((( (( li )->kante) /+;
R/SC;yy+NT )->st;*/ ) /*;((( (( li )->kante) /+;R/SC;yy+NT )->st;*/ !=v) { /*;((( (( li )->kante) /+;R/SC;yy+NT )->st
li )->kante) /+;R/SC;yy+NT )->start) /;*/   PRINTF("Succedge (%s,%s) at %s wrong source\n", st,tt,title);  break; /*;((( (( li )->kante) /+;R/SC;yy+NT )->en
li )->kante) /+;R/SC;yy+NT )->end) /+;;*/   } if ((( ((( (( li )->kante) /*;else tt =  ? ;;*/ )->end) /*;else tt =  ? ;
;*/ ) /*;else tt =  ? ;;*/ )->tiefe) /*;else tt =  ? ;;*/ !=t+1) {  PRINTF("Succedge (%s,%s) depth %d (%d expected)\n", /*; (( li )->kante) /+;R/SC;yy+NT )->start
ge (%s,%s) at %s wrong sourcezn ,;*/ st,tt,(( ((( (( li )->kante) /*;ge (%s,%s) at %s wrong sourcezn ,;*/ )->end) /*;
ge (%s,%s) at %s wrong sourcezn ,;*/ ) /*;ge (%s,%s) at %s wrong sourcezn ,;
*/ )->tiefe) /*;ge (%s,%s) at %s wrong sourcezn ,;*/ ,t+1);  break;  } /*;}
((( (( li )->kante) /+;R/SC;yy+NT )->en;*/  li = (( li )->next) /*;};*/ ; } li = (( v )->pred) /*;ge (%s,%s) depth %d (%d expected)zn ,;
*/ ; while (li) { if (!(( li )->kante) /*;break; ;*/ ) { PRINTF("%s missing edge\n",title); /*;break; 
};*/  break; } if (!((( (( li )->kante) /*;};*/ )->start) /*;};*/ ) /*;};
*/ ) {  PRINTF("Prededge at %s missing source\n",title);  break;  } if (!((( (( li )->kante) /*;
while (li) {;*/ )->end) /*;while (li) {;*/ ) /*;while (li) {;*/ ) {  PRINTF("Prededge at %s missing source\n",title); /*; li )->kante) /+;R/SC;yy+NT ) { PRINTF(
)->kante) /+;R/SC;yy+NT )->start) /+;R;*/   break;  } if ((( ((( (( li )->kante) /*;break; ;*/ )->start) /*;break;
;*/ ) /*;break; ;*/ )->title) /*;break; ;*/ [0]) st = (( ((( (( li )->kante) /*;
};*/ )->start) /*;};*/ ) /*;};*/ )->title) /*;};*/ ; else st = "?"; if ((( ((( (( li )->kante) /*;
ge at %s missing sourcezn ,title); ;*/ )->end) /*;ge at %s missing sourcezn ,title);
;*/ ) /*;ge at %s missing sourcezn ,title); ;*/ )->title) /*;ge at %s missing sourcezn ,title);
;*/ [0]) tt = (( ((( (( li )->kante) /*;break; ;*/ )->end) /*;break;
;*/ ) /*;break; ;*/ )->title) /*;break; ;*/ ; else tt = "?"; if (((( (( li )->kante) /*;
((( (( li )->kante) /+;R/SC;yy+NT )->st;*/ )->end) /*;((( (( li )->kante) /+;
R/SC;yy+NT )->st;*/ ) /*;((( (( li )->kante) /+;R/SC;yy+NT )->st;*/ !=v) { /*;((( (( li )->kante) /+;R/SC;yy+NT )->st
li )->kante) /+;R/SC;yy+NT )->start) /;*/   PRINTF("Prededge (%s,%s) at %s wrong target\n", st,tt,title);  break; /*;((( (( li )->kante) /+;R/SC;yy+NT )->en
li )->kante) /+;R/SC;yy+NT )->end) /+;;*/   } if ((( ((( (( li )->kante) /*;else tt =  ? ;;*/ )->start) /*;else tt =  ? ;
;*/ ) /*;else tt =  ? ;;*/ )->tiefe) /*;else tt =  ? ;;*/ !=t-1) {  PRINTF("Succedge (%s,%s) depth %d (%d expected)\n", /*; (( li )->kante) /+;R/SC;yy+NT )->end) 
ge (%s,%s) at %s wrong targetzn ,;*/ st,tt,(( ((( (( li )->kante) /*;ge (%s,%s) at %s wrong targetzn ,;*/ )->start) /*;
ge (%s,%s) at %s wrong targetzn ,;*/ ) /*;ge (%s,%s) at %s wrong targetzn ,;
*/ )->tiefe) /*;ge (%s,%s) at %s wrong targetzn ,;*/ ,t-1);  break;  } /*;}
((( (( li )->kante) /+;R/SC;yy+NT )->st;*/  li = (( li )->next) /*;};*/ ; } return(1); }
#endif
