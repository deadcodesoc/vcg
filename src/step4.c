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
static char *gs_ide1525 ="$Id: step4.c,v 3.10 1995/02/08 11:11:14 sander Exp $"; /*;*a*b
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
static void gs_ide1508 _PP((void)); static void gs_ide1515 _PP((int le,int mr,int miy,int may)); /*;*a*b
*a*b;*/ static int gs_ide1516 _PP((int level)); static void gs_ide1518 _PP((GNODE v, int xpos)); /*;*a*b
*a*b;*/ static void gs_ide1517 _PP((GNODE v, int xpos)); static void gs_ide1514 _PP((DLLIST x)); /*;*gs_ide1525 = $Id: step4.c,v 3.10 1995*
508 _PP((void));;*/ static void gs_ide1513 _PP((DLLIST x)); static void gs_ide1501 _PP((GEDGE e, GNODE n)); /*;((int le,int mr,int miy,int may));
vel));;*/ static void gs_ide1500 _PP((GEDGE e, GNODE n)); static void gs_ide1503 _PP((void)); /*;static void gs_ide1518 _PP((/N;D+ v, in
void gs_ide1517 _PP((/N;D+ v, int xpos);*/ static void gs_ide1502 _PP((void)); static void gs_ide1537 _PP((void)); /*;_ide1514 _PP((DLLIST x));
3 _PP((DLLIST x));;*/ static int gs_ide1509 _PP((GNLIST li)); static int gs_ide1505 _PP((GNLIST li)); /*;/+D/+ e, /N;D+ n));
, /N;D+ n));;*/ static int gs_ide1507 _PP((GEDGE e,GNLIST li)); static int gs_ide1506 _PP((GEDGE e,GNLIST li)); /*;atic void gs_ide1503 _PP((void));
id gs_ide1502 _PP((void));;*/ static int gs_ide1534 _PP((GNLIST li, int bendp)); static int gs_ide1533 _PP((GNLIST li, int bendp)); /*;de1537 _PP((void));
PP((/NLIST li));;*/ static void gs_ide1504 _PP((void)); static void gs_ide1511 _PP((GEDGE e)); /*;IST li));
LIST li));;*/ static void gs_ide1512 _PP((ADJEDGE a)); static void gs_ide1510 _PP((ADJEDGE a)); /*;ic int gs_ide1506 _PP((/+D/+ e,/NLIST l
gs_ide1534 _PP((/NLIST li, int bendp));;*/ static void gs_ide1521 _PP((void)); static void gs_ide1519 _PP((GNODE v)); /*;533 _PP((/NLIST li, int bendp));
P((void));;*/   static void gs_ide1520 _PP((GEDGE e));  static void gs_ide1524 _PP((void)); /*;+ e));
;;*/ static void gs_ide1522 _PP((GNODE v));  static void gs_ide1523 _PP((GEDGE e)); /*; void gs_ide1510 _PP((ADJ+D/+ a));
s_ide1521 _PP((void));;*/  
#ifdef ANSI_C
void step4_main(void)
#else
void step4_main()
#endif
{ start_time(); ; assert((layer)); gs_ide1503 (); if (manhatten_edges!=1) { /*;void step4_main()
{;*/ gs_ide1502 (); gs_ide1537 ();  } else { gs_ide1508 (); } gs_ide1504 (); /*;gs_ide1502 ();
537 (); ;*/ if ( (G_orientation==3 /*;537 (); ;*/ ) ||(G_orientation==2 /*;};*/ )) gs_ide1524 (); /*;}
else {;*/ if ( (G_orientation==1 /*;else {;*/ ) ||(G_orientation==2 /*;508 ();
;*/ )) gs_ide1521 (); calc_max_xy_pos(); stop_time("step4_main"); }
#ifdef ANSI_C
void calc_all_ports(int xypos_avail)
#else
void calc_all_ports(xypos_avail) int xypos_avail;
#endif
{ GNODE v; ; v = nodelist; while (v) { calc_node_ports(v,xypos_avail); /*;{
;;*/  v = (( v )->next) /*;{;*/ ; } v = labellist; while (v) { calc_node_ports(v,xypos_avail); /*;while (v) {
de_ports(v,xypos_avail);;*/ v = (( v )->next) /*;de_ports(v,xypos_avail);;*/ ; } v = dummylist; while (v) { /*;ellist;
while (v) {;*/ calc_node_ports(v,xypos_avail); v = (( v )->next) /*;de_ports(v,xypos_avail);
;*/ ; } }
#ifdef ANSI_C
void calc_node_ports(GNODE v,int xypos_avail)
#else
void calc_node_ports(v,xypos_avail) GNODE v; int xypos_avail;
#endif
{ int act_port; int act_pcol, act_pstyle, act_psize; int pcol, pstyle, psize; /*;_ports(v,xypos_avail)
/N;D+ v;;*/ int midport,nullport,portpos; ADJEDGE a; ; act_port = 1; if (G_portsharing!=1 /*;
act_pstyle, act_psize;;*/ ) act_port = 0; if ((( v )->anchordummy) /*;
ze;;*/ ) act_port = 0; a = (( v )->succ) /*;;;*/ ; if (a) { act_pstyle = (( (( a )->kante) /*;
;;*/ )->arrowstyle2) /*;;;*/ ; act_pcol = (( (( a )->kante) /*;t = 1;
;*/ )->arrowcolor2) /*;t = 1;;*/ ; act_psize = (( (( a )->kante) /*;
ing!=1 /+;R/SC;yy+NT ) act_port = 0;;*/ )->arrowsize2) /*;ing!=1 /+;
R/SC;yy+NT ) act_port = 0;;*/ ; if (((( (( a )->kante) /*;my) /+;R/SC;
yy+NT ) act_port = 0;;*/ )->kantenart) /*;my) /+;R/SC;yy+NT ) act_port = 0;
;*/ ) /*;my) /+;R/SC;yy+NT ) act_port = 0;;*/ =='r') act_pstyle = -1; /*;+NT ;
if (a) {;*/  else if (((( (( a )->kante) /*;+NT ;;*/ )->kantenart) /*;+NT ;;*/ ) /*;
+NT ;;*/ =='l') act_pstyle = -1; } while (a) { pstyle = (( (( a )->kante) /*;
(( a )->kante) /+;R/SC;yy+NT )->arrowco;*/ )->arrowstyle2) /*;(( a )->kante) /+;
R/SC;yy+NT )->arrowco;*/ ; pcol = (( (( a )->kante) /*;->kante) /+;R/SC;
yy+NT )->arrowsize2) /;*/ )->arrowcolor2) /*;->kante) /+;R/SC;yy+NT )->arrowsize2) /;
*/ ; psize = (( (( a )->kante) /*;SC;yy+NT )->kantenart) /+;R/SC;yy+NT ) ;
*/ )->arrowsize2) /*;SC;yy+NT )->kantenart) /+;R/SC;yy+NT ) ;*/ ; if (((( (( a )->kante) /*;
;yy+NT )->kantenart) /+;R/SC;yy+NT ) /+;*/ )->kantenart) /*;;yy+NT )->kantenart) /+;
R/SC;yy+NT ) /+;*/ ) /*;;yy+NT )->kantenart) /+;R/SC;yy+NT ) /+;*/ =='r') pstyle = -1; /*;;yy+NT )->kantenart) /+;R/SC;yy+NT ) /+
};*/ else if (((( (( a )->kante) /*;};*/ )->kantenart) /*;};*/ ) /*;};*/ =='l') pstyle = -1; /*;}
a) {;*/ if ((( v )->anchordummy) /*;a) {;*/ ) pstyle= 5+(act_pstyle+1)%20; if (G_portsharing!=1 /*;
a )->kante) /+;R/SC;yy+NT )->arrowstyl;*/ ) pstyle= 5+(act_pstyle+1)%20; /*; a )->kante) /+;R/SC;yy+NT )->arrowstyl
te) /+;R/SC;yy+NT )->arrowcolor2) /+;R/;*/ if ((psize==act_psize)&&(pcol==act_pcol)&&(pstyle==act_pstyle)){ if (pstyle!= -1) (( (( a )->kante) /*;
;R/SC;yy+NT )->arrowsize2) /+;R/SC;yy+N;*/ )->weights) /*;;R/SC;yy+NT )->arrowsize2) /+;
R/SC;yy+N;*/ = act_port; } else { act_pstyle = pstyle; act_psize = psize; /*;)->anchordummy) /+;R/SC;yy+NT ) pstyle=
g!=1 /+;R/SC;yy+NT ) pstyle= 5+(act_pst;*/ act_pcol = pcol; if (pstyle!= -1) {  act_port++; (( (( a )->kante) /*;
};*/ )->weights) /*;};*/ = act_port; } } a = (( a )->next) /*;act_pcol = pcol;
;*/ ; } (( v )->weights) /*;act_port++;;*/ = act_port; if (xypos_avail) { /*; )->kante) /+;R/SC;yy+NT )->weights) /+
};*/ switch ((( v )->shape) /*;};*/ ) { case 2 /*;};*/ : case 1 /*;a )->next) /+;
R/SC;yy+NT ;;*/ : midport = 1; nullport = 0; a = (( v )->succ) /*;l) {
;*/ ; while (a) { if ((( ((( (( a )->kante) /*;case 2 /+;R/SC;yy+NT :;
*/ )->end) /*;case 2 /+;R/SC;yy+NT :;*/ ) /*;case 2 /+;R/SC;yy+NT :;
*/ )->xloc) /*;case 2 /+;R/SC;yy+NT :;*/ +(( ((( (( a )->kante) /*;case 2 /+;
R/SC;yy+NT :;*/ )->end) /*;case 2 /+;R/SC;yy+NT :;*/ ) /*;case 2 /+;
R/SC;yy+NT :;*/ )->width) /*;case 2 /+;R/SC;yy+NT :;*/ <(( v )->xloc) /*;
case 2 /+;R/SC;yy+NT :;*/ )  portpos = -1; else if ((( ((( (( a )->kante) /*;
midport = 1;;*/ )->end) /*;midport = 1;;*/ ) /*;midport = 1;;*/ )->xloc) /*;
midport = 1;;*/ >(( v )->xloc) /*;midport = 1;;*/ +(( v )->width) /*;
midport = 1;;*/ )  portpos = 1; else portpos = 0; if (portpos<0) midport = (( (( a )->kante) /*;
while (a) {;*/ )->weights) /*;while (a) {;*/ ; if (portpos==0) { if (!nullport)  /*;portpos = -1;
((( ((( (( a )->kante) /+;R/SC;yy+NT );*/ midport =  nullport = (( (( a )->kante) /*;portpos = 1;;*/ )->weights) /*;
portpos = 1;;*/ ; else midport = ((( (( a )->kante) /*;rtpos = 0;;*/ )->weights) /*;
rtpos = 0;;*/  +nullport)/2;  } else nullport = 0; a = (( a )->next) /*;
midport = ;*/ ; } if (act_port-midport > midport-1)  portpos = 2*act_port-3*midport+1; /*;+nullport)*2; 
};*/ else portpos = midport-1; (( v )->weights) /*;llport = 0;;*/ = 2*(midport+portpos)-1; /*;llport = 0;
xt) /+;R/SC;yy+NT ;;*/   if (portpos) { a = (( v )->succ) /*;};*/ ; while (a) {  (( (( a )->kante) /*;
t_port-3*midport+1;;*/ )->weights) /*;t_port-3*midport+1;;*/ +=portpos; /*;t_port-3*midport+1;
t-1;;*/   a=(( a )->next) /*;t-1;;*/ ;  } }  break; } } act_port = 1; if ((( v )->anchordummy) /*;
};*/ ) act_port = 0; if (G_portsharing!=1 /*;} ;*/ ) act_port = 0; a = (( v )->pred) /*;
break;;*/ ; if (a) { act_pstyle = (( (( a )->kante) /*;};*/ )->arrowstyle1) /*;
};*/ ; act_pcol = (( (( a )->kante) /*;t = 1;;*/ )->arrowcolor1) /*;
t = 1;;*/ ; act_psize = (( (( a )->kante) /*;chordummy) /+;R/SC;yy+NT ) act_port = 0;
*/ )->arrowsize1) /*;chordummy) /+;R/SC;yy+NT ) act_port = 0;*/ ; if (((( (( a )->kante) /*;
/+;R/SC;yy+NT ) act_port = 0;;*/ )->kantenart) /*;/+;R/SC;yy+NT ) act_port = 0;
;*/ ) /*;/+;R/SC;yy+NT ) act_port = 0;;*/ =='r') act_pstyle = -1; else if (((( (( a )->kante) /*;
+NT ;;*/ )->kantenart) /*;+NT ;;*/ ) /*;+NT ;;*/ =='l') act_pstyle = -1; /*;+NT ;
if (a) {;*/ } while (a) { pstyle = (( (( a )->kante) /*;(( a )->kante) /+;R/SC;yy+NT )->arrowco;
*/ )->arrowstyle1) /*;(( a )->kante) /+;R/SC;yy+NT )->arrowco;*/ ; pcol = (( (( a )->kante) /*;
->kante) /+;R/SC;yy+NT )->arrowsize1) /;*/ )->arrowcolor1) /*;->kante) /+;
R/SC;yy+NT )->arrowsize1) /;*/ ; psize = (( (( a )->kante) /*;SC;yy+NT )->kantenart) /+;
R/SC;yy+NT ) ;*/ )->arrowsize1) /*;SC;yy+NT )->kantenart) /+;R/SC;yy+NT ) ;
*/ ; if (((( (( a )->kante) /*;;yy+NT )->kantenart) /+;R/SC;yy+NT ) /+;
*/ )->kantenart) /*;;yy+NT )->kantenart) /+;R/SC;yy+NT ) /+;*/ ) /*;
;yy+NT )->kantenart) /+;R/SC;yy+NT ) /+;*/ =='r') pstyle = -1; else if (((( (( a )->kante) /*;
};*/ )->kantenart) /*;};*/ ) /*;};*/ =='l') pstyle = -1; if ((( v )->anchordummy) /*;
a) {;*/ ) pstyle= 5+(act_pstyle+1)%20; if (G_portsharing!=1 /*; a )->kante) /+;
R/SC;yy+NT )->arrowstyl;*/ ) pstyle= 5+(act_pstyle+1)%20; if ((psize==act_psize)&&(pcol==act_pcol)&&(pstyle==act_pstyle)){ /*;te) /+;R/SC;yy+NT )->arrowcolor1) /+;R/
;R/SC;yy+NT )->arrowsize1) /+;R/SC;yy+N;*/ if (pstyle!= -1) (( (( a )->kante) /*;;R/SC;yy+NT )->arrowsize1) /+;
R/SC;yy+N;*/ )->weightp) /*;;R/SC;yy+NT )->arrowsize1) /+;R/SC;yy+N;
*/ = act_port; } else { act_pstyle = pstyle; act_psize = psize; act_pcol = pcol; /*;g!=1 /+;R/SC;yy+NT ) pstyle= 5+(act_pst
&(pcol==act_pcol)&&(pstyle==act_pstyle);*/ if (pstyle!= -1) {  act_port++; (( (( a )->kante) /*;};*/ )->weightp) /*;
};*/ = act_port; } } a = (( a )->next) /*;act_pcol = pcol;;*/ ; } (( v )->weightp) /*;
act_port++;;*/ = act_port; if (xypos_avail) { switch ((( v )->shape) /*;
};*/ ) { case 2 /*;};*/ : case 3 /*;a )->next) /+;R/SC;yy+NT ;;*/ : case 1 /*;
};*/ : midport = 1; nullport = 0; a = (( v )->pred) /*;) /+;R/SC;yy+NT ) {
;*/ ; while (a) { if ((( ((( (( a )->kante) /*;/+;R/SC;yy+NT :;*/ )->start) /*;
/+;R/SC;yy+NT :;*/ ) /*;/+;R/SC;yy+NT :;*/ )->xloc) /*;/+;R/SC;yy+NT :;
*/ +(( ((( (( a )->kante) /*;/+;R/SC;yy+NT :;*/ )->start) /*;/+;R/SC;
yy+NT :;*/ ) /*;/+;R/SC;yy+NT :;*/ )->width) /*;/+;R/SC;yy+NT :;*/ <(( v )->xloc) /*;
/+;R/SC;yy+NT :;*/ )  portpos = -1; else if ((( ((( (( a )->kante) /*;
midport = 1;;*/ )->start) /*;midport = 1;;*/ ) /*;midport = 1;;*/ )->xloc) /*;
midport = 1;;*/ >(( v )->xloc) /*;midport = 1;;*/ +(( v )->width) /*;
midport = 1;;*/ )  portpos = 1; else portpos = 0; if (portpos<0) midport = (( (( a )->kante) /*;
while (a) {;*/ )->weightp) /*;while (a) {;*/ ; if (portpos==0) { if (!nullport)  /*;portpos = -1;
((( ((( (( a )->kante) /+;R/SC;yy+NT );*/ midport = nullport = (( (( a )->kante) /*;portpos = 1;;*/ )->weightp) /*;
portpos = 1;;*/ ; else midport = ((( (( a )->kante) /*;rtpos = 0;;*/ )->weightp) /*;
rtpos = 0;;*/  +nullport)/2;  } else nullport = 0; a = (( a )->next) /*;
midport =;*/ ; } if (act_port-midport > midport-1)  portpos = 2*act_port-3*midport+1; /*;+nullport)*2; 
};*/ else portpos = midport-1; (( v )->weightp) /*;llport = 0;;*/ = 2*(midport+portpos)-1; /*;llport = 0;
xt) /+;R/SC;yy+NT ;;*/   if (portpos) { a = (( v )->pred) /*;};*/ ; while (a) {  (( (( a )->kante) /*;
t_port-3*midport+1;;*/ )->weightp) /*;t_port-3*midport+1;;*/ +=portpos; /*;t_port-3*midport+1;
t-1;;*/   a=(( a )->next) /*;t-1;;*/ ;  } }  break; } } }
#ifdef ANSI_C
static void gs_ide1503 (void)
#else
static void gs_ide1503 ()
#endif
{ GNODE v; ; v = nodelist; while (v) { calc_edge_xy(v); v = (( v )->next) /*;
{;*/ ; } v = labellist; while (v) { calc_edge_xy(v); v = (( v )->next) /*;
ge_xy(v);;*/ ; } v = dummylist; while (v) { calc_edge_xy(v); v = (( v )->next) /*;
ge_xy(v);;*/ ; } }
#ifdef ANSI_C
void calc_edge_xy(GNODE v)
#else
void calc_edge_xy(v) GNODE v;
#endif
{ int node_x,node_y,node_width,node_height; int node_predports,node_succports, dist, dist1; /*;}
lc_edge_xy(/N;D+ v);*/ CONNECT c; GEDGE e; ADJEDGE a; ; assert((v)); node_width = (( v )->width) /*;
orts,node_succports, dist, dist1;;*/ ; node_height = (( v )->height) /*;
C;NN+CT c;;*/ ; node_x = (( v )->xloc) /*;;;*/ ; node_y = (( v )->yloc) /*;
ADJ+D/+ a;;*/ ; node_predports = (( v )->weightp) /*;;;*/ ; node_succports = (( v )->weights) /*;
(v));;*/ ; switch ((( v )->shape) /*;( v )->width) /+;R/SC;yy+NT ;;*/ ) { /*;( v )->width) /+;R/SC;yy+NT ;
>height) /+;R/SC;yy+NT ;;*/ case 3 /*;>height) /+;R/SC;yy+NT ;;*/ : dist1 = node_width/4; break; /*;T ;
de_predports = (( v )->weightp) /+;R/SC;*/  default: dist1 = 0; } c = (( v )->connection) /*;ports = (( v )->weights) /+;
R/SC;yy+NT ;*/ ; if (c) { if ((( c )->target) /*;dist1 = node_width*4;
;*/ ) { e = (( c )->edge) /*;break;;*/ ; if ((( e )->start) /*;: dist1 = 0;
;*/ ==v) { (( e )->btyloc) /*;};*/ = (( e )->syloc) /*;};*/ = node_y+node_height/2; /*;}
v )->connection) /+;R/SC;yy+NT ;;*/ if ((( (( e )->end) /*;v )->connection) /+;R/SC;yy+NT ;;*/ )->xloc) /*;
v )->connection) /+;R/SC;yy+NT ;;*/ <node_x)  (( e )->btxloc) /*;if (c) {
;*/ = (( e )->sxloc) /*;if (c) {;*/ = node_x+dist1; else (( e )->btxloc) /*;
c )->target) /+;R/SC;yy+NT ) {;*/ = (( e )->sxloc) /*;c )->target) /+;
R/SC;yy+NT ) {;*/ = node_x-dist1+node_width; } else {  (( e )->bbyloc) /*;
T = (( e )->syloc) /+;R/SC;yy+NT = node;*/ = (( e )->eyloc) /*;T = (( e )->syloc) /+;
R/SC;yy+NT = node;*/ = node_y+node_height/2; if ((( (( e )->start) /*;
->xloc) /+;R/SC;yy+NT <node_x) ;*/ )->xloc) /*;->xloc) /+;R/SC;yy+NT <node_x) ;
*/ <node_x)  (( e )->bbxloc) /*; e )->btxloc) /+;R/SC;yy+NT = (( e )->s;
*/ = (( e )->exloc) /*; e )->btxloc) /+;R/SC;yy+NT = (( e )->s;*/ = node_x+dist1; /*; e )->btxloc) /+;R/SC;yy+NT = (( e )->s
)->btxloc) /+;R/SC;yy+NT = (( e )->sxl;*/ else (( e )->bbxloc) /*; )->btxloc) /+;R/SC;yy+NT = (( e )->sxl;*/ = (( e )->exloc) /*;
)->btxloc) /+;R/SC;yy+NT = (( e )->sxl;*/ = node_x-dist1+node_width; /*;}
;*/  } } if ((( c )->target2) /*;) /+;R/SC;yy+NT = (( e )->eyloc) /+;R/S;
*/ ) { e = (( c )->edge2) /*; /+;R/SC;yy+NT )->xloc) /+;R/SC;yy+NT <;
*/ ; if ((( e )->start) /*;T = (( e )->exloc) /+;R/SC;yy+NT = node;*/ ==v) { /*;T = (( e )->exloc) /+;R/SC;yy+NT = node
= (( e )->exloc) /+;R/SC;yy+NT = node_x;*/ (( e )->btyloc) /*;= (( e )->exloc) /+;R/SC;yy+NT = node_x;*/ = (( e )->syloc) /*;
= (( e )->exloc) /+;R/SC;yy+NT = node_x;*/ = node_y+node_height/2; if ((( (( e )->end) /*;
};*/ )->xloc) /*;};*/ <node_x)  (( e )->btxloc) /*;};*/ = (( e )->sxloc) /*;
};*/ = node_x+dist1; else (( e )->btxloc) /*;c )->target2) /+;R/SC;yy+NT ) {
;*/ = (( e )->sxloc) /*;c )->target2) /+;R/SC;yy+NT ) {;*/ = node_x-dist1+node_width; /*;c )->target2) /+;R/SC;yy+NT ) {
ge2) /+;R/SC;yy+NT ;;*/ } else {  (( e )->bbyloc) /*;T = (( e )->syloc) /+;R/SC;yy+NT = node;
*/ = (( e )->eyloc) /*;T = (( e )->syloc) /+;R/SC;yy+NT = node;*/ = node_y+node_height/2; /*;T = (( e )->syloc) /+;R/SC;yy+NT = node
->xloc) /+;R/SC;yy+NT <node_x) ;*/ if ((( (( e )->start) /*;->xloc) /+;R/SC;yy+NT <node_x) ;*/ )->xloc) /*;
->xloc) /+;R/SC;yy+NT <node_x) ;*/ <node_x)  (( e )->bbxloc) /*; e )->btxloc) /+;
R/SC;yy+NT = (( e )->s;*/ = (( e )->exloc) /*; e )->btxloc) /+;R/SC;
yy+NT = (( e )->s;*/ = node_x+dist1; else (( e )->bbxloc) /*; )->btxloc) /+;
R/SC;yy+NT = (( e )->sxl;*/ = (( e )->exloc) /*; )->btxloc) /+;R/SC;
yy+NT = (( e )->sxl;*/ = node_x-dist1+node_width; } } } a = (( v )->succ) /*;
/+;R/SC;yy+NT )->xloc) /+;R/SC;yy+NT <;*/ ; while (a) { e = (( a )->kante) /*;
= (( e )->exloc) /+;R/SC;yy+NT = node_x;*/ ; switch ((( e )->kantenart) /*;
};*/ ) { case 'l': (( e )->btyloc) /*;};*/ = (( e )->syloc) /*;};*/ = node_y+node_height/2; /*;}
};*/ (( e )->btxloc) /*;};*/ = (( e )->sxloc) /*;};*/ = node_x+dist1; break; /*;v )->succ) /+;R/SC;yy+NT ;
while (a) {;*/ case 'r': (( e )->btyloc) /*;while (a) {;*/ = (( e )->syloc) /*;while (a) {
;*/ = node_y+node_height/2; (( e )->btxloc) /*;a )->kante) /+;R/SC;yy+NT ;
;*/ = (( e )->sxloc) /*;a )->kante) /+;R/SC;yy+NT ;;*/ = node_x+node_width-dist1; /*;a )->kante) /+;R/SC;yy+NT ;
->kantenart) /+;R/SC;yy+NT ) {;*/ break; default:  (( e )->btxloc) /*;T = (( e )->sxloc) /+;R/SC;yy+NT = node;
*/ = (( e )->sxloc) /*;T = (( e )->sxloc) /+;R/SC;yy+NT = node;*/ = node_x +  /*;T = (( e )->sxloc) /+;R/SC;yy+NT = node
break;;*/ node_width * (( e )->weights) /*;break;;*/ / (node_succports+1); switch ((( v )->shape) /*;
': (( e )->btyloc) /+;R/SC;yy+NT = (( e;*/ ) { case 1 /*;) /+;R/SC;yy+NT = (( e )->sxloc) /+;
R/S;*/ : if ((( e )->sxloc) /*;break;;*/ -node_x < node_width/2) dist = ((node_width+1)/2 - (( e )->sxloc) /*;
: ;*/  + node_x) * node_height / node_width; else dist = (-(node_width+1)/2 + (( e )->sxloc) /*;
SC;yy+NT ) {;*/  - node_x) * node_height / node_width; (( e )->syloc) /*;
width+1)*2 - (( e )->sxloc) /+;R/SC;yy+;*/ = node_y + node_height - dist; /*;width+1)*2 - (( e )->sxloc) /+;R/SC;yy+
ht;*/ break;  case 2 /*;* node_width;;*/ : dist = node_height/2 - gstoint(sqrt( /*;de_height
* node_width;;*/ (double)(node_height*node_height)/4.0 - (double)(node_height*node_height) /*;>syloc) /+;R/SC;yy+NT = node_y + node_h
break; ;*/ /(double)(node_width*node_width) *((( e )->sxloc) /*;/+;R/SC;yy+NT :;
*/ -node_x-(double)node_width/2.0) *((( e )->sxloc) /*;ight*2 -;*/ -node_x-(double)node_width/2.0))); /*;ight*2 -
gstoint(sqrt(;*/ (( e )->syloc) /*;gstoint(sqrt(;*/ = node_y + node_height - dist; break; /*;)(node_height*node_height)*4.0
e_height*node_height);*/   default:  (( e )->syloc) /*;node_width);*/ = node_y + node_height; /*;e_x-(double)node_width*2.0)));
e )->syloc) /+;R/SC;yy+NT = node_y + n;*/  } (( e )->btyloc) /*;e_x-(double)node_width*2.0)));;*/ = (( e )->syloc) /*;
e_x-(double)node_width*2.0)));;*/ ; } a = (( a )->next) /*;break; ;*/ ; /*;break; 
: ;*/ } a = (( v )->pred) /*; /+;R/SC;yy+NT = node_y + node_height;;*/ ; while (a) { /*;}
>btyloc) /+;R/SC;yy+NT = (( e )->syloc);*/ e = (( a )->kante) /*;>btyloc) /+;R/SC;yy+NT = (( e )->syloc);*/ ; switch ((( e )->kantenart) /*;
};*/ ) { case 'l': (( e )->bbyloc) /*;a )->next) /+;R/SC;yy+NT ;;*/ = (( e )->eyloc) /*;
a )->next) /+;R/SC;yy+NT ;;*/ = node_y+node_height/2; (( e )->bbxloc) /*;
};*/ = (( e )->exloc) /*;};*/ = node_x+node_width-dist1; break; case 'r': (( e )->bbyloc) /*;
while (a) {;*/ = (( e )->eyloc) /*;while (a) {;*/ = node_y+node_height/2; /*;while (a) {
a )->kante) /+;R/SC;yy+NT ;;*/ (( e )->bbxloc) /*;a )->kante) /+;R/SC;yy+NT ;;*/ = (( e )->exloc) /*;
a )->kante) /+;R/SC;yy+NT ;;*/ = node_x+dist1; break; default:  (( e )->bbxloc) /*;
T = (( e )->exloc) /+;R/SC;yy+NT = node;*/ = (( e )->exloc) /*;T = (( e )->exloc) /+;
R/SC;yy+NT = node;*/ = node_x +  node_width * (( e )->weightp) /*;break;
;*/ / (node_predports+1); switch ((( v )->shape) /*;': (( e )->bbyloc) /+;
R/SC;yy+NT = (( e;*/ ) { case 1 /*;) /+;R/SC;yy+NT = (( e )->exloc) /+;
R/S;*/ : if ((( e )->exloc) /*;break;;*/ -node_x < node_width/2) dist = ((node_width+1)/2 - (( e )->exloc) /*;
: ;*/  + node_x) * node_height / node_width; else dist = (-(node_width+1)/2 + (( e )->exloc) /*;
SC;yy+NT ) {;*/  - node_x) * node_height / node_width; (( e )->eyloc) /*;
width+1)*2 - (( e )->exloc) /+;R/SC;yy+;*/ = node_y + dist; break;  case 2 /*;
* node_width;;*/ : dist = node_height/2 - gstoint(sqrt( (double)(node_height*node_height)/4.0 /*;* node_width;
>eyloc) /+;R/SC;yy+NT = node_y + dist;;*/ - (double)(node_height*node_height) /(double)(node_width*node_width) *((( e )->exloc) /*;
/+;R/SC;yy+NT :;*/ -node_x-(double)node_width/2.0) *((( e )->exloc) /*;
ight*2 -;*/ -node_x-(double)node_width/2.0))); (( e )->eyloc) /*;gstoint(sqrt(;
*/ = node_y + dist; break;  case 3 /*;e_height*node_height);*/ : if ((( e )->exloc) /*;
node_width);*/ -node_x < node_width/2) dist = ((node_width+1)/2 - (( e )->exloc) /*;
NT -node_x-(double)node_width*2.0);*/  + node_x) * node_height * 2 / node_width; /*; e )->eyloc) /+;R/SC;yy+NT = node_y + d
break; ;*/ else dist = (-(node_width+1)/2 + (( e )->exloc) /*;break; ;*/  - node_x) * node_height * 2 /*;/+;R/SC;yy+NT :
loc) /+;R/SC;yy+NT -node_x < node_width;*/ / node_width; (( e )->eyloc) /*;)*2 - (( e )->exloc) /+;R/SC;yy+NT ;
*/ = node_y + dist; break;  default:  (( e )->eyloc) /*;(node_width+1)*2 + (( e )->exloc) /+;
R/;*/ = node_y; } (( e )->bbyloc) /*;* node_width;;*/ = (( e )->eyloc) /*;
* node_width;;*/ ; } a = (( a )->next) /*;break; ;*/ ; } }
#ifdef ANSI_C
static void gs_ide1508 (void)
#else
static void gs_ide1508 ()
#endif
{ GNLIST li; int topbendp, botbendp; int maxrow, i; ; assert((layer)); /*;{
li;;*/  for (i=0; i<=maxdepth; i++) { if (i%20==0) gs_wait_message('e'); topbendp = 0; /*;botbendp;
int maxrow, i;;*/ botbendp = MAXINT; li = (( layer[i] ).predlist) /*;;;*/ ; while (li) { /*;axdepth; i++) {
message('e');;*/  tpred_connection1[(( (( li )->node) /*;axdepth; i++) {;*/ )->position) /*;
axdepth; i++) {;*/ ] = li; if ((( (( li )->node) /*;message('e');;*/ )->yloc) /*;
message('e');;*/ +(( (( li )->node) /*;message('e');;*/ )->height) /*;
message('e');;*/ >topbendp) topbendp = (( (( li )->node) /*;topbendp = 0;
;*/ )->yloc) /*;topbendp = 0;;*/ +(( (( li )->node) /*;topbendp = 0;
;*/ )->height) /*;topbendp = 0;;*/ ; li = (( li )->next) /*;p = yAXINT;
;*/ ; } li = (( layer[i+1] ).predlist) /*;while (li) {;*/ ; while (li) { /*;onnection1[(( (( li )->node) /+;R/SC;yy
->node) /+;R/SC;yy+NT )->yloc) /+;R/SC;;*/ tpred_connection2[(( (( li )->node) /*;->node) /+;R/SC;yy+NT )->yloc) /+;
R/SC;;*/ )->position) /*;->node) /+;R/SC;yy+NT )->yloc) /+;R/SC;;*/ ] = li; /*;->node) /+;R/SC;yy+NT )->yloc) /+;R/SC;
->node) /+;R/SC;yy+NT )->yloc) /+;R/SC;;*/ if ((( (( li )->node) /*;->node) /+;R/SC;yy+NT )->yloc) /+;R/SC;;*/ )->yloc) /*;
->node) /+;R/SC;yy+NT )->yloc) /+;R/SC;;*/ <botbendp) botbendp = (( (( li )->node) /*;
yy+NT ;;*/ )->yloc) /*;yy+NT ;;*/ ; li = (( li )->next) /*;};*/ ; } maxrow = gs_ide1516 (i); /*;while (li) {
onnection2[(( (( li )->node) /+;R/SC;yy;*/ if (botbendp-topbendp > 20) { botbendp = botbendp-10; topbendp = topbendp+10; /*;->node) /+;R/SC;yy+NT )->yloc) /+;R/SC;
yy+NT ;;*/ } gs_ide1515 (i, maxrow, topbendp, botbendp); } gs_ide1515 (maxdepth+1, maxrow, topbendp, botbendp); /*;opbendp > 20) {
0;;*/ } static int gs_ide1535 ;  static int gs_ide1536 ;  static int gs_ide1529 ; /*;515 (i, maxrow, topbendp, botbendp);
};*/   static int gs_ide1531 ;  static int gs_ide1530 ;  static DLLIST gs_ide1526 = NULL; /*;}
int gs_ide1535 ; ;*/   static DLLIST gs_ide1527 = NULL;  static DLLIST gs_ide1538 = NULL; /*; ; 
static int gs_ide1531 ; ;*/   static DLLIST gs_ide1539 = NULL;  static int gs_ide1540 ; static int gs_ide1528 ; /*;int gs_ide1530 ; 
gs_ide1526 = NULL; ;*/ 
#ifdef ANSI_C
static int gs_ide1516 (int level)
#else
static int gs_ide1516 (level) int level;
#endif
{ GNLIST li1, li2; ADJEDGE a1, a2; ; assert((level>=0)); assert((level<=maxdepth)); /*;int level;
{;*/   gs_ide1536 = gs_ide1535 = 0; gs_ide1529 = gs_ide1531 = 0; gs_ide1526 = gs_ide1527 = NULL; /*;;
;;*/ gs_ide1538 = gs_ide1539 = NULL; gs_ide1530 = 0; gs_ide1540 = -1; gs_ide1528 = -1; /*;35 = 0;
;*/ li1 = (( layer[level] ).succlist) /*;;*/ ; li2 = (( layer[level+1] ).succlist) /*;
gs_ide1526 = gs_ide1527 = NULL;;*/ ; a1 = NULL; while (li1 && (!a1)) { /*;gs_ide1540 = -1;
528 = -1;;*/  a1 = (( (( li1 )->node) /*;gs_ide1540 = -1;;*/ )->succ) /*;gs_ide1540 = -1;
;*/ ; if (!a1) li1 = (( li1 )->next) /*;528 = -1;;*/ ;  } a2 = NULL; /*;a1 = NULL;
li1 && (!a1)) {;*/  while (li2 && (!a2)) { a2 = (( (( li2 )->node) /*;li1 && (!a1)) {;*/ )->pred) /*;
li1 && (!a1)) {;*/ ; if (!a2) li2 = (( li2 )->next) /*; )->node) /+;
R/SC;yy+NT )->succ) /+;R/S;*/ ;  } while ((li1)||(li2)) { if (a1 && a2) { /*;LL;
(!a2)) {;*/ if ((( (( a1 )->kante) /*;(!a2)) {;*/ )->sxloc) /*;(!a2)) {;*/ < (( (( a2 )->kante) /*;
(!a2)) {;*/ )->exloc) /*;(!a2)) {;*/ ) { gs_ide1518 ((( li1 )->node) /*;
e) /+;R/SC;yy+NT )->pred) /+;R/SC;yy+NT;*/ ,(( (( a1 )->kante) /*;e) /+;
R/SC;yy+NT )->pred) /+;R/SC;yy+NT;*/ )->sxloc) /*;e) /+;R/SC;yy+NT )->pred) /+;
R/SC;yy+NT;*/ ); a1 = (( a1 )->next) /*;t) /+;R/SC;yy+NT ; ;*/ ; } else { /*;(li1)||(li2)) {
{;*/  gs_ide1517 ((( li2 )->node) /*;(li1)||(li2)) {;*/ ,(( (( a2 )->kante) /*;
(li1)||(li2)) {;*/ )->exloc) /*;(li1)||(li2)) {;*/ ); a2 = (( a2 )->next) /*;
{;*/ ; } } else if (a1) { gs_ide1518 ((( li1 )->node) /*;};*/ ,(( (( a1 )->kante) /*;
};*/ )->sxloc) /*;};*/ ); a1 = (( a1 )->next) /*;gs_ide1517 ((( li2 )->node) /+;
R/SC;yy+;*/ ; } else if (a2) { gs_ide1517 ((( li2 )->node) /*;};*/ ,(( (( a2 )->kante) /*;
};*/ )->exloc) /*;};*/ ); a2 = (( a2 )->next) /*; (a1) {;*/ ; } if (!a1) { /*;+;R/SC;yy+NT ;
};*/   if (li1) li1 = (( li1 )->next) /*;};*/ ;  while (li1 && (!a1)) { a1 = (( (( li1 )->node) /*;
li2 )->node) /+;R/SC;yy+NT ,(( (( a2 );*/ )->succ) /*; li2 )->node) /+;
R/SC;yy+NT ,(( (( a2 );*/ ; if (!a1) li1 = (( li1 )->next) /*;+;R/SC;
yy+NT ;;*/ ;  } } if (!a2) {  if (li2) li2 = (( li2 )->next) /*;{;*/ ; /*;{
/SC;yy+NT )->succ) /+;R/SC;yy+NT ;;*/   while (li2 && (!a2)) { a2 = (( (( li2 )->node) /*;/SC;yy+NT ; ;*/ )->pred) /*;
/SC;yy+NT ; ;*/ ; if (!a2) li2 = (( li2 )->next) /*;};*/ ;  } } } return(gs_ide1530 ); /*;{
/SC;yy+NT )->pred) /+;R/SC;yy+NT ;;*/ }
#ifdef ANSI_C
static void gs_ide1518 (GNODE v, int xpos)
#else
static void gs_ide1518 (v, xpos) GNODE v; int xpos;
#endif
{ ADJEDGE a; GEDGE ee; DLLIST n,m; int k; ; assert((v)); k = gs_ide1531 + gs_ide1529 ; /*; a;
/+D/+ ee;;*/ if (k>gs_ide1530 ) gs_ide1530 = k; if (xpos<=gs_ide1540 ) return; gs_ide1540 = xpos; /*;int k;
;;*/ a = (( v )->succ) /*;;;*/ ; while (a) { ee = (( a )->kante) /*; + gs_ide1529 ;
;*/ ; if (((( ee )->sxloc) /*;_ide1530 = k;;*/ ==xpos) && ((( ee )->exloc) /*;
_ide1530 = k;;*/ > (( ee )->sxloc) /*;_ide1530 = k;;*/ )) { gs_ide1500 (ee,((( (( a )->kante) /*;
n;;*/ )->end) /*;n;;*/ ) /*;n;;*/ ); } a = (( a )->next) /*;v )->succ) /+;
R/SC;yy+NT ;;*/ ; } k = gs_ide1531 + gs_ide1529 ; if (k>gs_ide1530 ) gs_ide1530 = k; /*;sxloc) /+;R/SC;yy+NT ==xpos) && ((( ee 
a )->kante) /+;R/SC;yy+NT )->end) /+;R;*/ n = gs_ide1538 ; while (n) { m = (( n )->succ) /*;a )->next) /+;R/SC;
yy+NT ;;*/ ; if ((( n )->dlx) /*;};*/ <= xpos) gs_ide1514 (n); n = m; /*;30 ) gs_ide1530 = k;
n = gs_ide1538 ;;*/  } gs_ide1531 = 0; n = gs_ide1538 ; while (n) { if ((( n )->dlinfo) /*;
/SC;yy+NT <= xpos) gs_ide1514 (n);;*/ > gs_ide1531 ) gs_ide1531 = (( n )->dlinfo) /*;
/SC;yy+NT <= xpos) gs_ide1514 (n);;*/ ; n = (( n )->succ) /*;n = m;;
*/ ; } }
#ifdef ANSI_C
static void gs_ide1517 (GNODE v,int xpos)
#else
static void gs_ide1517 (v, xpos) GNODE v; int xpos;
#endif
{ ADJEDGE a; GEDGE ee; DLLIST n,m; int k; ; assert((v)); k = gs_ide1531 + gs_ide1529 ; /*; a;
/+D/+ ee;;*/ if (k>gs_ide1530 ) gs_ide1530 = k; if (xpos<=gs_ide1528 ) return; gs_ide1528 = xpos; /*;int k;
;;*/ a = (( v )->pred) /*;;;*/ ; while (a) { ee = (( a )->kante) /*; + gs_ide1529 ;
;*/ ; if (((( ee )->exloc) /*;_ide1530 = k;;*/ ==xpos) && ((( ee )->exloc) /*;
_ide1530 = k;;*/ <= (( ee )->sxloc) /*;_ide1530 = k;;*/ )) { gs_ide1501 (ee,((( (( a )->kante) /*;
n;;*/ )->start) /*;n;;*/ ) /*;n;;*/ ); } a = (( a )->next) /*;v )->pred) /+;
R/SC;yy+NT ;;*/ ; } k = gs_ide1531 + gs_ide1529 ; if (k>gs_ide1530 ) gs_ide1530 = k; /*;exloc) /+;R/SC;yy+NT ==xpos) && ((( ee 
a )->kante) /+;R/SC;yy+NT )->start) /+;*/ n = gs_ide1526 ; while (n) { m = (( n )->succ) /*;a )->next) /+;R/SC;
yy+NT ;;*/ ; if ((( n )->dlx) /*;};*/ <= xpos) gs_ide1513 (n); n = m; /*;30 ) gs_ide1530 = k;
n = gs_ide1526 ;;*/  } gs_ide1529 = 0; n = gs_ide1526 ; while (n) { if ((( n )->dlinfo) /*;
/SC;yy+NT <= xpos) gs_ide1513 (n);;*/ > gs_ide1529 ) gs_ide1529 = (( n )->dlinfo) /*;
/SC;yy+NT <= xpos) gs_ide1513 (n);;*/ ; n = (( n )->succ) /*;n = m;;
*/ ; } }
#ifdef ANSI_C
static void gs_ide1501 (GEDGE e, GNODE n)
#else
static void gs_ide1501 (e, n) GEDGE e; GNODE n;
#endif
{ DLLIST d; assert((n)); ; d = dllist_alloc(n,gs_ide1539 ); if (!gs_ide1538 ) gs_ide1538 = d; /*;;
{;*/ if (gs_ide1539 ) (( gs_ide1539 )->succ) /*;{;*/ = d; gs_ide1539 = d; /*;assert((n));
;;*/  gs_ide1536 ++; if ((( e )->sxloc) /*;;;*/ !=(( e )->exloc) /*;;;*/ ) gs_ide1531 ++; /*;;
ist_alloc(n,gs_ide1539 );;*/ (( d )->dlinfo) /*;ist_alloc(n,gs_ide1539 );;*/ = gs_ide1531 ; (( e )->btyloc) /*;
8 ) gs_ide1538 = d;;*/ = gs_ide1531 ; (( d )->dlx) /*;s_ide1539 )->succ) /+;
R/SC;yy+NT = d;;*/ = (( e )->sxloc) /*;s_ide1539 )->succ) /+;R/SC;yy+NT = d;
;*/ ;  }
#ifdef ANSI_C
static void gs_ide1500 (GEDGE e, GNODE n)
#else
static void gs_ide1500 (e, n) GEDGE e; GNODE n;
#endif
{ DLLIST d; assert((n)); ; d = dllist_alloc(n,gs_ide1527 ); if (!gs_ide1526 ) gs_ide1526 = d; /*;;
{;*/ if (gs_ide1527 ) (( gs_ide1527 )->succ) /*;{;*/ = d; gs_ide1527 = d; /*;assert((n));
;;*/  gs_ide1535 ++; if ((( e )->sxloc) /*;;;*/ !=(( e )->exloc) /*;;;*/ ) gs_ide1529 ++; /*;;
ist_alloc(n,gs_ide1527 );;*/ (( d )->dlinfo) /*;ist_alloc(n,gs_ide1527 );;*/ = gs_ide1529 ; (( e )->btyloc) /*;
6 ) gs_ide1526 = d;;*/ = gs_ide1529 ; (( d )->dlx) /*;s_ide1527 )->succ) /+;
R/SC;yy+NT = d;;*/ = (( e )->exloc) /*;s_ide1527 )->succ) /+;R/SC;yy+NT = d;
;*/ ;  }
#ifdef ANSI_C
static void gs_ide1514 (DLLIST x)
#else
static void gs_ide1514 (x) DLLIST x;
#endif
{ assert((x)); assert(((( x )->node) /*;};*/ )); ; if ((( x )->pred) /*;
_ide1514 (x);*/ ) (( (( x )->pred) /*;_ide1514 (x);*/ )->succ) /*;_ide1514 (x);
*/ = (( x )->succ) /*;_ide1514 (x);*/ ; else gs_ide1538 = (( x )->succ) /*;
DLLIST x;;*/ ; if ((( x )->succ) /*;{;*/ ) (( (( x )->succ) /*;{;*/ )->pred) /*;
{;*/ = (( x )->pred) /*;{;*/ ; else gs_ide1539 = (( x )->pred) /*;(x));
;*/ ; dllist_free(x); gs_ide1536 --; }
#ifdef ANSI_C
static void gs_ide1513 (DLLIST x)
#else
static void gs_ide1513 (x) DLLIST x;
#endif
{ assert((x)); assert(((( x )->node) /*;};*/ )); ; if ((( x )->pred) /*;
_ide1513 (x);*/ ) (( (( x )->pred) /*;_ide1513 (x);*/ )->succ) /*;_ide1513 (x);
*/ = (( x )->succ) /*;_ide1513 (x);*/ ; else gs_ide1526 = (( x )->succ) /*;
DLLIST x;;*/ ; if ((( x )->succ) /*;{;*/ ) (( (( x )->succ) /*;{;*/ )->pred) /*;
{;*/ = (( x )->pred) /*;{;*/ ; else gs_ide1527 = (( x )->pred) /*;(x));
;*/ ; dllist_free(x); gs_ide1535 --; }
#ifdef ANSI_C
static void gs_ide1515 (int level, int maxr, int miny, int maxy)
#else
static void gs_ide1515 (level, maxr, miny, maxy) int level, maxr, miny, maxy; /*;ed) /+;R/SC;yy+NT ;
dllist_free(x);;*/ 
#endif
{ GNLIST li; ADJEDGE a; GEDGE ee; GNODE node; int k, k1, k2; ; li = (( layer[level] ).succlist) /*;
li;;*/ ; while (li) { a = (( (( li )->node) /*;e;;*/ )->succ) /*;e;;
*/ ; while (a) { ee = (( a )->kante) /*;k1, k2;;*/ ; if (one_line_manhatten==1) { /*;;
layer[level] ).succlist) /+;R/SC;yy+NT;*/ k = maxy- (maxy-miny) / 2;  } else { if ((( ee )->sxloc) /*;while (a) {
;*/ >= (( ee )->exloc) /*;while (a) {;*/ ) k = maxy- (maxy-miny) *  (maxr+1- (( ee )->btyloc) /*;
anhatten==1) {;*/ ) / (maxr+1); else k = miny+ (maxy-miny) * (maxr+1- (( ee )->btyloc) /*;
};*/ ) / (maxr+1); } (( ee )->btyloc) /*;ee )->sxloc) /+;R/SC;yy+NT >= (( ee )->;
*/ = k; (( ee )->bbyloc) /*;y-miny) * ;*/ = k; a = (( a )->next) /*;
loc) /+;R/SC;yy+NT ) * (maxr+1);;*/ ; } li = (( li )->next) /*;y+NT ) * (maxr+1);
;*/ ; } li = (( layer[level] ).succlist) /*;->btyloc) /+;R/SC;yy+NT = k;
;*/ ; while (li) { node = (( li )->node) /*;R/SC;yy+NT ;;*/ ; if ( ((( node )->width) /*;
};*/ ==0) && ((( node )->height) /*;};*/ ==0) &&((( node )->succ) /*;
li )->next) /+;R/SC;yy+NT ;;*/ ) && ((( (( node )->succ) /*; li )->next) /+;
R/SC;yy+NT ;;*/ )->next) /*; li )->next) /+;R/SC;yy+NT ;;*/ ) &&((( (( (( node )->succ) /*;
};*/ )->next) /*;};*/ )->next) /*;};*/ ==NULL) &&(((( node )->pred) /*;
layer[level] ).succlist) /+;R/SC;yy+NT;*/ )==NULL)) { k1 = (( (( (( node )->succ) /*;
while (li) {;*/ )->kante) /*;while (li) {;*/ )->btyloc) /*;while (li) {
;*/ ; k2 = (( (( (( (( node )->succ) /*;(( li )->node) /+;R/SC;yy+NT ;
;*/ )->next) /*;(( li )->node) /+;R/SC;yy+NT ;;*/ )->kante) /*;(( li )->node) /+;
R/SC;yy+NT ;;*/ )->btyloc) /*;(( li )->node) /+;R/SC;yy+NT ;;*/ ; if (k1<k2) k = k1; /*;)->width) /+;R/SC;yy+NT ==0) && ((( nod
+;R/SC;yy+NT ) && ((( (( node )->succ) ;*/ else k = k2; (( node )->yloc) /*;;R/SC;yy+NT )->next) /+;R/SC;yy+NT )->n;
*/ = k; (( (( (( node )->succ) /*;)==NULL)) {;*/ )->kante) /*;)==NULL)) {
;*/ )->syloc) /*;)==NULL)) {;*/ = k;  (( (( (( (( node )->succ) /*; = (( (( (( node )->succ) /+;
R/SC;yy+NT;*/ )->next) /*; = (( (( (( node )->succ) /+;R/SC;yy+NT;*/ )->kante) /*;
= (( (( (( node )->succ) /+;R/SC;yy+NT;*/ )->syloc) /*; = (( (( (( node )->succ) /+;
R/SC;yy+NT;*/ = k; } if ( ((( node )->width) /*;1;;*/ ==0) && ((( node )->height) /*;
1;;*/ ==0) &&((( node )->pred) /*;else k = k2;;*/ ) && ((( (( node )->pred) /*;
else k = k2;;*/ )->next) /*;else k = k2;;*/ ) &&((( (( (( node )->pred) /*;
)->yloc) /+;R/SC;yy+NT = k;;*/ )->next) /*; )->yloc) /+;R/SC;yy+NT = k;
;*/ )->next) /*; )->yloc) /+;R/SC;yy+NT = k;;*/ ==NULL) &&(((( node )->succ) /*;
)->succ) /+;R/SC;yy+NT )->kante) /+;R/S;*/ )==NULL)) { k1 = (( (( (( node )->pred) /*;
ucc) /+;R/SC;yy+NT )->next) /+;R/SC;yy+;*/ )->kante) /*;ucc) /+;R/SC;
yy+NT )->next) /+;R/SC;yy+;*/ )->bbyloc) /*;ucc) /+;R/SC;yy+NT )->next) /+;
R/SC;yy+;*/ ; k2 = (( (( (( (( node )->pred) /*;};*/ )->next) /*;};*/ )->kante) /*;
};*/ )->bbyloc) /*;};*/ ; if (k1>k2) k = k1; else k = k2; (( node )->yloc) /*;
red) /+;R/SC;yy+NT )->next) /+;R/SC;yy+;*/ = k; (( (( (( node )->pred) /*;
;yy+NT )==NULL)) {;*/ )->kante) /*;;yy+NT )==NULL)) {;*/ )->eyloc) /*;
;yy+NT )==NULL)) {;*/ = k; (( (( (( (( node )->pred) /*;;yy+NT )->kante) /+;
R/SC;yy+NT )->bbylo;*/ )->next) /*;;yy+NT )->kante) /+;R/SC;yy+NT )->bbylo;
*/ )->kante) /*;;yy+NT )->kante) /+;R/SC;yy+NT )->bbylo;*/ )->eyloc) /*;
;yy+NT )->kante) /+;R/SC;yy+NT )->bbylo;*/ = k; } li = (( li )->next) /*;
) k = k1;;*/ ; } }
#ifdef ANSI_C
static void gs_ide1502 (void)
#else
static void gs_ide1502 ()
#endif
{ int i,j; GNLIST li; GNODE node; int h,changed; int topbendp; int botbendp; /*;{
;;*/ int minx, maxx; ; assert((layer)); for (i=0; i<=maxdepth; i++) { if (i%10==0) gs_wait_message('e'); /*;int topbendp;
bendp;;*/ li = (( layer[i] ).succlist) /*;bendp;;*/ ; minx = MAXINT; maxx = 0; /*;(layer));
axdepth; i++) {;*/  while (li) { j = (( (( li )->node) /*;axdepth; i++) {;*/ )->yloc) /*;
axdepth; i++) {;*/ ; if (j<minx) minx = j; j = j + (( (( li )->node) /*;
/+;R/SC;yy+NT ;;*/ )->height) /*; /+;R/SC;yy+NT ;;*/ ; if (j>maxx) maxx = j; /*;minx = yAXINT;
0;;*/ li = (( li )->next) /*;0;;*/ ; } li = (( layer[i] ).succlist) /*;(( li )->node) /+;
R/SC;yy+NT )->yloc) /;*/ ; while (li) { node = (( li )->node) /*;ode) /+;
R/SC;yy+NT )->height) /+;R/SC;y;*/ ; if ( ((( node )->width) /*;if (j>maxx) maxx = j;
;*/ ==0) && ((( node )->height) /*;if (j>maxx) maxx = j;;*/ ==0) &&((( node )->succ) /*;
li )->next) /+;R/SC;yy+NT ;;*/ ) && ((( (( node )->succ) /*; li )->next) /+;
R/SC;yy+NT ;;*/ )->next) /*; li )->next) /+;R/SC;yy+NT ;;*/ ) &&((( (( (( node )->succ) /*;
};*/ )->next) /*;};*/ )->next) /*;};*/ ==NULL) &&(((( node )->pred) /*;
layer[i] ).succlist) /+;R/SC;yy+NT ;;*/ )==NULL)) { (( node )->yloc) /*;
while (li) {;*/ = maxx; (( (( (( node )->succ) /*;(( li )->node) /+;
R/SC;yy+NT ;;*/ )->kante) /*;(( li )->node) /+;R/SC;yy+NT ;;*/ )->syloc) /*;
(( li )->node) /+;R/SC;yy+NT ;;*/ = maxx; (( (( (( node )->succ) /*;
)->width) /+;R/SC;yy+NT ==0) && ((( nod;*/ )->kante) /*;)->width) /+;
R/SC;yy+NT ==0) && ((( nod;*/ )->btyloc) /*;)->width) /+;R/SC;yy+NT ==0) && ((( nod;
*/ = maxx; (( (( (( (( node )->succ) /*;+;R/SC;yy+NT ) && ((( (( node )->succ) ;
*/ )->next) /*;+;R/SC;yy+NT ) && ((( (( node )->succ) ;*/ )->kante) /*;
+;R/SC;yy+NT ) && ((( (( node )->succ) ;*/ )->syloc) /*;+;R/SC;yy+NT ) && ((( (( node )->succ) ;
*/ = maxx; (( (( (( (( node )->succ) /*;;R/SC;yy+NT )->next) /+;R/SC;
yy+NT )->n;*/ )->next) /*;;R/SC;yy+NT )->next) /+;R/SC;yy+NT )->n;*/ )->kante) /*;
;R/SC;yy+NT )->next) /+;R/SC;yy+NT )->n;*/ )->btyloc) /*;;R/SC;yy+NT )->next) /+;
R/SC;yy+NT )->n;*/ = maxx; } if ( ((( node )->width) /*; node )->yloc) /+;
R/SC;yy+NT = maxx;;*/ ==0) && ((( node )->height) /*; node )->yloc) /+;
R/SC;yy+NT = maxx;;*/ ==0) &&((( node )->pred) /*;node )->succ) /+;R/SC;
yy+NT )->kante) /;*/ ) && ((( (( node )->pred) /*;node )->succ) /+;R/SC;
yy+NT )->kante) /;*/ )->next) /*;node )->succ) /+;R/SC;yy+NT )->kante) /;
*/ ) &&((( (( (( node )->pred) /*;>succ) /+;R/SC;yy+NT )->kante) /+;
R/SC;;*/ )->next) /*;>succ) /+;R/SC;yy+NT )->kante) /+;R/SC;;*/ )->next) /*;
>succ) /+;R/SC;yy+NT )->kante) /+;R/SC;;*/ ==NULL) &&(((( node )->succ) /*;
c) /+;R/SC;yy+NT )->next) /+;R/SC;yy+NT;*/ )==NULL)) { (( node )->yloc) /*;
/SC;yy+NT )->next) /+;R/SC;yy+NT )->kan;*/ = minx; (( (( (( node )->pred) /*;
};*/ )->kante) /*;};*/ )->eyloc) /*;};*/ = minx; (( (( (( node )->pred) /*;
( node )->width) /+;R/SC;yy+NT ==0) && ;*/ )->kante) /*;( node )->width) /+;
R/SC;yy+NT ==0) && ;*/ )->bbyloc) /*;( node )->width) /+;R/SC;yy+NT ==0) && ;
*/ = minx; (( (( (( (( node )->pred) /*;pred) /+;R/SC;yy+NT ) && ((( (( node )-;
*/ )->next) /*;pred) /+;R/SC;yy+NT ) && ((( (( node )-;*/ )->kante) /*;
pred) /+;R/SC;yy+NT ) && ((( (( node )-;*/ )->eyloc) /*;pred) /+;R/SC;
yy+NT ) && ((( (( node )-;*/ = minx; (( (( (( (( node )->pred) /*;red) /+;
R/SC;yy+NT )->next) /+;R/SC;yy+;*/ )->next) /*;red) /+;R/SC;yy+NT )->next) /+;
R/SC;yy+;*/ )->kante) /*;red) /+;R/SC;yy+NT )->next) /+;R/SC;yy+;*/ )->bbyloc) /*;
red) /+;R/SC;yy+NT )->next) /+;R/SC;yy+;*/ = minx; } li = (( li )->next) /*;
nx;;*/ ; } topbendp = 0; botbendp = MAXINT; li = (( layer[i] ).predlist) /*;
d) /+;R/SC;yy+NT )->next) /+;R/SC;yy+NT;*/ ; while (li) { tpred_connection1[(( (( li )->node) /*;
li )->next) /+;R/SC;yy+NT ;;*/ )->position) /*; li )->next) /+;R/SC;
yy+NT ;;*/ ] = li; if ((( (( li )->node) /*;};*/ )->yloc) /*;};*/ +(( (( li )->node) /*;
};*/ )->height) /*;};*/ >topbendp) topbendp = (( (( li )->node) /*;p = 0;
;*/ )->yloc) /*;p = 0;;*/ +(( (( li )->node) /*;p = 0;;*/ )->height) /*;
p = 0;;*/ ; li = (( li )->next) /*;INT;;*/ ; } li = (( layer[i+1] ).predlist) /*;
while (li) {;*/ ; while (li) { tpred_connection2[(( (( li )->node) /*;
->node) /+;R/SC;yy+NT )->yloc) /+;R/SC;;*/ )->position) /*;->node) /+;
R/SC;yy+NT )->yloc) /+;R/SC;;*/ ] = li; if ((( (( li )->node) /*;->node) /+;
R/SC;yy+NT )->yloc) /+;R/SC;;*/ )->yloc) /*;->node) /+;R/SC;yy+NT )->yloc) /+;
R/SC;;*/ <botbendp) botbendp = (( (( li )->node) /*;yy+NT ;;*/ )->yloc) /*;
yy+NT ;;*/ ; li = (( li )->next) /*;};*/ ; } j = 1; changed = 1; while (changed) { /*;->node) /+;R/SC;yy+NT )->yloc) /+;R/SC;
->node) /+;R/SC;yy+NT )->yloc) /+;R/SC;;*/ j++; if (j>max_edgebendings) {  gs_wait_message('t'); break; } if (G_timelimit>0) /*;) {
j++;;*/ if (test_timelimit(100)) { gs_wait_message('t'); break; } changed = 0; /*;imelimit>0)
imit(100)) {;*/  li = (( layer[i] ).succlist) /*;imelimit>0);*/ ; while (li) { h = gs_ide1509 (li); /*;
break;;*/ changed += gs_ide1534 (li,h); li = (( li )->next) /*;};*/ ; } li = (( layer[i+1] ).succlist) /*;
i] ).succlist) /+;R/SC;yy+NT ;;*/ ; while (li) { h = gs_ide1505 (li); /*;ide1534 (li,h);
+;R/SC;yy+NT ;;*/  changed += gs_ide1533 (li,h); li = (( li )->next) /*;+;R/SC;yy+NT ;
;*/ ; } } if (changed) { li = (( layer[i] ).succlist) /*;ide1505 (li);
;*/ ; while (li) { (void)gs_ide1534 (li,topbendp); li = (( li )->next) /*;
};*/ ; } li = (( layer[i+1] ).succlist) /*;nged) {;*/ ; while (li) { /*;while (li) {
s_ide1534 (li,topbendp);;*/  (void)gs_ide1533 (li,botbendp); li = (( li )->next) /*;s_ide1534 (li,topbendp);
;*/ ; } } } }
#ifdef ANSI_C
static int gs_ide1534 (GNLIST li,int bendp)
#else
static int gs_ide1534 (li,bendp) GNLIST li; int bendp;
#endif
{ ADJEDGE a; int changed; ; assert((li)); assert(((( li )->node) /*;
dp;;*/ )); changed = 0; a = (( (( li )->node) /*; a;;*/ )->succ) /*;
a;;*/ ; while (a) { if ((( (( a )->kante) /*;;;*/ )->btyloc) /*;;;*/ <bendp) { /*;;
(li));;*/ (( (( a )->kante) /*;(li));;*/ )->btyloc) /*;(li));;*/ = bendp; changed = 1; /*;)->node) /+;R/SC;yy+NT ));
changed = 0;;*/ } a = (( a )->next) /*;(( li )->node) /+;R/SC;yy+NT )->succ) /;*/ ; } /*;(( a )->kante) /+;R/SC;yy+NT )->btyloc)
te) /+;R/SC;yy+NT )->btyloc) /+;R/SC;yy;*/  return(changed); }
#ifdef ANSI_C
static int gs_ide1533 (GNLIST li,int bendp)
#else
static int gs_ide1533 (li,bendp) GNLIST li; int bendp;
#endif
{ ADJEDGE a; int changed; ; assert((li)); assert(((( li )->node) /*;
dp;;*/ )); changed = 0; a = (( (( li )->node) /*; a;;*/ )->pred) /*;
a;;*/ ; while (a) { if ((( (( a )->kante) /*;;;*/ )->bbyloc) /*;;;*/ >bendp) { /*;;
(li));;*/ (( (( a )->kante) /*;(li));;*/ )->bbyloc) /*;(li));;*/ = bendp; changed = 1; /*;)->node) /+;R/SC;yy+NT ));
changed = 0;;*/ } a = (( a )->next) /*;(( li )->node) /+;R/SC;yy+NT )->pred) /;*/ ; } /*;(( a )->kante) /+;R/SC;yy+NT )->bbyloc)
te) /+;R/SC;yy+NT )->bbyloc) /+;R/SC;yy;*/  return(changed); }
#ifdef ANSI_C
static int gs_ide1509 (GNLIST li)
#else
static int gs_ide1509 (li) GNLIST li;
#endif
{ int bendp, h; GEDGE e; ; assert((li)); assert(((( li )->node) /*;/NLIST li;
;*/ )); bendp = 0; e = (( (( li )->node) /*;dp, h;;*/ )->succleft) /*;
dp, h;;*/ ; if (!e) return(bendp); bendp = gs_ide1507 (e,li); e = (( (( li )->node) /*;
(li));;*/ )->succright) /*;(li));;*/ ; assert((e));  if (e==(( (( li )->node) /*;
bendp = 0;;*/ )->succleft) /*;bendp = 0;;*/ ) return(bendp); h = gs_ide1507 (e,li); /*;(( li )->node) /+;R/SC;yy+NT )->succlef
(bendp);;*/ if (h>bendp) bendp = h; return(bendp); }
#define bendformula  ((sx-tx)*(ky-ty))/(kx-tx)+ty
#ifdef ANSI_C
static int gs_ide1507 (GEDGE e,GNLIST li)
#else
static int gs_ide1507 (e,li) GEDGE e; GNLIST li;
#endif
{ int bendp, h; GEDGE e2; int sx,sy,tx,ty;  int kx,ky;  GNODE node; int offset, myoff, cross; /*;{
dp, h;;*/ GNLIST li2; ; bendp = 0; sx = (( e )->sxloc) /*;int kx,ky; ;*/ ; sy = (( e )->syloc) /*;
ode;;*/ ; tx = (( e )->bbxloc) /*;off, cross;;*/ ; ty = (( e )->bbyloc) /*;
/NLIST li2;;*/ ; offset = 7*(( e )->arrowsize2) /*;;;*/ /10+2; if (sx<tx) { /*; 0;
xloc) /+;R/SC;yy+NT ;;*/ li2 = (( li )->next) /*;xloc) /+;R/SC;yy+NT ;;*/ ; while (li2) { node = (( li2 )->node) /*;
;yy+NT ;;*/ ; if (!(( node )->anchordummy) /*;;;*/ ) {  kx = (( node )->xloc) /*;
fset = 7*(( e )->arrowsize2) /+;R/SC;yy;*/ ; if (kx>=tx) break; if ((( node )->shape) /*;
ext) /+;R/SC;yy+NT ;;*/ == 1 /*;ext) /+;R/SC;yy+NT ;;*/ ) { kx -= 3; /*;(( li2 )->node) /+;R/SC;yy+NT ;
->anchordummy) /+;R/SC;yy+NT ) { ;*/  myoff = (kx-sx)*offset/(tx-sx); ky = (( node )->yloc) /*;->anchordummy) /+;
R/SC;yy+NT ) { ;*/ + (( node )->height) /*;->anchordummy) /+;R/SC;yy+NT ) {
;*/ /2 + myoff; if (kx>=sx) { h = bendformula; if (h>bendp) bendp = h; /*;node )->shape) /+;R/SC;yy+NT == 1 /+;R/
kx -= 3;;*/ } kx += (( node )->width) /*; (kx-sx)*offset*(tx-sx);;*/ /2; if (kx>=tx) break; /*;->yloc) /+;R/SC;yy+NT + (( node )->heig
if (kx>=sx) {;*/ myoff = (kx-sx)*offset/(tx-sx); ky = (( node )->yloc) /*;dformula;;*/ + (( node )->height) /*;
dformula;;*/ + myoff; if (kx>=sx) { h = bendformula; if (h>bendp) bendp = h; /*;( node )->width) /+;R/SC;yy+NT *2;
eak;;*/ } } else { myoff = (kx-sx)*offset/(tx-sx); ky = (( node )->yloc) /*;
dformula;;*/ + (( node )->height) /*;dformula;;*/ + myoff; if (kx>=sx) { /*;endp = h;
};*/ h = bendformula; if (h>bendp) bendp = h; } } } e2 = (( node )->succleft) /*;
if (kx>=sx) {;*/ ; if ((e2)&&((( e2 )->btyloc) /*;dformula;;*/ !=(( e2 )->syloc) /*;
dformula;;*/ )) { cross = 0; if ( ((( (( e2 )->start) /*;};*/ )->position) /*;
};*/ <(( (( e )->start) /*;};*/ )->position) /*;};*/ ) &&((( (( e2 )->end) /*;
};*/ )->position) /*;};*/ >(( (( e )->end) /*;};*/ )->position) /*;}
;*/ ) ) cross=1; if ( ((( (( e2 )->start) /*;};*/ )->position) /*;};
*/ >(( (( e )->start) /*;};*/ )->position) /*;};*/ ) &&((( (( e2 )->end) /*;
node )->succleft) /+;R/SC;yy+NT ;;*/ )->position) /*; node )->succleft) /+;
R/SC;yy+NT ;;*/ <(( (( e )->end) /*; node )->succleft) /+;R/SC;yy+NT ;
;*/ )->position) /*; node )->succleft) /+;R/SC;yy+NT ;;*/ ) ) cross=1; /*;e2 )->btyloc) /+;R/SC;yy+NT !=(( e2 )->
cross = 0;;*/  kx = (( e2 )->btxloc) /*;e2 )->btyloc) /+;R/SC;yy+NT !=(( e2 )->;*/ - G_dspace+3; /*;e2 )->btyloc) /+;R/SC;yy+NT !=(( e2 )->
cross = 0;;*/ if (kx>=tx) break; ky = (( e2 )->btyloc) /*;( (( e2 )->start) /+;R/SC;
yy+NT )->posi;*/ ; if ((kx>=sx) && (!cross)) { h = bendformula; if (h>bendp) bendp = h; /*;yy+NT )->position) /+;R/SC;yy+NT <(( ((
- /_dspace+3;;*/ } } li2 = (( li2 )->next) /*;2 )->btyloc) /+;R/SC;yy+NT ;;*/ ; } } else if (tx<sx) { /*;endp) bendp = h;
};*/   li2 = tpred_connection1[(( (( li )->node) /*;};*/ )->position) /*;
};*/ ];  li2 = (( li2 )->next) /*;};*/ ; while (li2) { node = (( li2 )->node) /*;
};*/ ; if (!(( node )->anchordummy) /*;};*/ ) {  kx = (( node )->xloc) /*;
(tx<sx) { ;*/ + (( node )->width) /*; (tx<sx) { ;*/ ; if (kx<=tx) break; /*;nnection1[(( (( li )->node) /+;R/SC;yy+
/+;R/SC;yy+NT ;;*/ if ((( node )->shape) /*; /+;R/SC;yy+NT ;;*/ == 1 /*; /+;R/SC;yy+NT ;
;*/ ) { kx += 3; myoff = (kx-sx)*offset/(tx-sx); ky = (( node )->yloc) /*;
->anchordummy) /+;R/SC;yy+NT ) { ;*/ + (( node )->height) /*;->anchordummy) /+;
R/SC;yy+NT ) { ;*/ /2 + myoff; if (kx<=sx) {  h = bendformula; if (h>bendp) bendp = h; /*;node )->shape) /+;R/SC;yy+NT == 1 /+;R/
kx += 3;;*/ } kx -= (( node )->width) /*; (kx-sx)*offset*(tx-sx);;*/ /2; if (kx<=tx) break; /*;->yloc) /+;R/SC;yy+NT + (( node )->heig
if (kx<=sx) { ;*/ myoff = (kx-sx)*offset/(tx-sx); ky = (( node )->yloc) /*;dformula;;*/ + (( node )->height) /*;
dformula;;*/ + myoff; if (kx<=sx) {  h = bendformula; if (h>bendp) bendp = h; /*;( node )->width) /+;R/SC;yy+NT *2;
eak;;*/ } } else { myoff = (kx-sx)*offset/(tx-sx); ky = (( node )->yloc) /*;
dformula;;*/ + (( node )->height) /*;dformula;;*/ + myoff; if (kx<=sx) { /*;endp = h;
};*/   h = bendformula; if (h>bendp) bendp = h; } } } e2 = (( node )->succright) /*;
if (kx<=sx) { ;*/ ; if ((e2)&&((( e2 )->btyloc) /*;dformula;;*/ !=(( e2 )->syloc) /*;
dformula;;*/ )) { cross = 0; if ( ((( (( e2 )->start) /*;};*/ )->position) /*;
};*/ <(( (( e )->start) /*;};*/ )->position) /*;};*/ ) &&((( (( e2 )->end) /*;
};*/ )->position) /*;};*/ >(( (( e )->end) /*;};*/ )->position) /*;}
;*/ ) ) cross=1; if ( ((( (( e2 )->start) /*;};*/ )->position) /*;};
*/ >(( (( e )->start) /*;};*/ )->position) /*;};*/ ) &&((( (( e2 )->end) /*;
node )->succright) /+;R/SC;yy+NT ;;*/ )->position) /*; node )->succright) /+;
R/SC;yy+NT ;;*/ <(( (( e )->end) /*; node )->succright) /+;R/SC;yy+NT ;
;*/ )->position) /*; node )->succright) /+;R/SC;yy+NT ;;*/ ) ) cross=1; /*; node )->succright) /+;R/SC;yy+NT ;
e2 )->btyloc) /+;R/SC;yy+NT !=(( e2 )->;*/ kx = (( e2 )->btxloc) /*;e2 )->btyloc) /+;R/SC;yy+NT !=(( e2 )->;*/ + G_dspace-3; /*;e2 )->btyloc) /+;R/SC;yy+NT !=(( e2 )->
cross = 0;;*/ if (kx<=tx) break; ky = (( e2 )->btyloc) /*;( (( e2 )->start) /+;R/SC;
yy+NT )->posi;*/ ; if ((kx<=sx) && (!cross)) { h = bendformula; if (h>bendp) bendp = h; /*;yy+NT )->position) /+;R/SC;yy+NT <(( ((
+ /_dspace-3;;*/ } } li2 = (( li2 )->next) /*;2 )->btyloc) /+;R/SC;yy+NT ;;*/ ; } } return(bendp); /*;endp) bendp = h;
};*/ }
#ifdef ANSI_C
static int gs_ide1505 (GNLIST li)
#else
static int gs_ide1505 (li) GNLIST li;
#endif
{ int bendp, h; GEDGE e; ; assert((li)); assert(((( li )->node) /*;/NLIST li;
;*/ )); bendp = MAXINT; e = (( (( li )->node) /*;dp, h;;*/ )->predleft) /*;
dp, h;;*/ ; if (!e) return(bendp); bendp = gs_ide1506 (e,li); e = (( (( li )->node) /*;
(li));;*/ )->predright) /*;(li));;*/ ; assert((e));  if (e==(( (( li )->node) /*;
bendp = yAXINT;;*/ )->predleft) /*;bendp = yAXINT;;*/ ) return(bendp); /*;(( li )->node) /+;R/SC;yy+NT )->predlef
(bendp);;*/  h = gs_ide1506 (e,li); if (h<bendp) bendp = h; return(bendp); }
#ifdef ANSI_C
static int gs_ide1506 (GEDGE e,GNLIST li)
#else
static int gs_ide1506 (e,li) GEDGE e; GNLIST li;
#endif
{ int bendp, h; GEDGE e2; int sx,sy,tx,ty;  int kx,ky;  GNODE node; int offset, myoff, cross; /*;{
dp, h;;*/ GNLIST li2; ; bendp = MAXINT; sx = (( e )->exloc) /*;int kx,ky; ;*/ ; /*;ode;
off, cross;;*/  sy = (( e )->eyloc) /*;ode;;*/ ; tx = (( e )->btxloc) /*;off, cross;
;*/ ; ty = (( e )->btyloc) /*;/NLIST li2;;*/ ; offset = 7*(( e )->arrowsize1) /*;
;;*/ /10+2; if (sx<tx) { li2 = (( li )->next) /*;xloc) /+;R/SC;yy+NT ;
;*/ ; while (li2) { node = (( li2 )->node) /*;;yy+NT ;;*/ ; if (!(( node )->anchordummy) /*;
;;*/ ) {  kx = (( node )->xloc) /*;fset = 7*(( e )->arrowsize1) /+;R/SC;
yy;*/ ; if (kx>=tx) break; if ((( node )->shape) /*;ext) /+;R/SC;yy+NT ;
;*/ ==1 /*;ext) /+;R/SC;yy+NT ;;*/ ) { kx -= 3; myoff = (kx-sx)*offset/(tx-sx); /*;(( li2 )->node) /+;R/SC;yy+NT ;
->anchordummy) /+;R/SC;yy+NT ) { ;*/ ky = (( node )->yloc) /*;->anchordummy) /+;R/SC;yy+NT ) { ;*/ + (( node )->height) /*;
->anchordummy) /+;R/SC;yy+NT ) { ;*/ /2 - myoff; if (kx>=sx) { h = bendformula; /*;if (kx>=tx) break;
node )->shape) /+;R/SC;yy+NT ==1 /+;R/S;*/ if (h<bendp) bendp = h; } kx += (( node )->width) /*; (kx-sx)*offset*(tx-sx);
;*/ /2; if (kx>=tx) break; myoff = (kx-sx)*offset/(tx-sx); ky = (( node )->yloc) /*;
dformula;;*/ - myoff; if (kx>=sx) { h = bendformula; if ((h>0)&&(h<bendp)) bendp = h; /*;( node )->width) /+;R/SC;yy+NT *2;
eak;;*/ } } else if ((( node )->shape) /*;C;yy+NT - myoff;;*/ ==3 /*;C;yy+NT - myoff;
;*/ ) { kx -= 3; myoff = (kx-sx)*offset/(tx-sx); ky = (( node )->yloc) /*;
bendp)) bendp = h;;*/ + (( node )->height) /*;bendp)) bendp = h;;*/ - myoff; /*;bendp)) bendp = h;
};*/ if (kx>=sx) { h = bendformula; if ((h>0)&&(h<bendp)) bendp = h; } kx += (( node )->width) /*;
(kx-sx)*offset*(tx-sx);;*/ /2; if (kx>=tx) break; myoff = (kx-sx)*offset/(tx-sx); /*;if (kx>=sx) {
dformula;;*/ ky = (( node )->yloc) /*;dformula;;*/ - myoff; if (kx>=sx) { h = bendformula; /*;}
( node )->width) /+;R/SC;yy+NT *2;;*/ if ((h>0)&&(h<bendp)) bendp = h; } } else { myoff = (kx-sx)*offset/(tx-sx); /*;if (kx>=sx) {
dformula;;*/ ky = (( node )->yloc) /*;dformula;;*/ - myoff; if (kx>=sx) { h = bendformula; /*;}
};*/ if ((h>0)&&(h<bendp)) bendp = h; } } } e2 = (( node )->predleft) /*;
if (kx>=sx) {;*/ ; if ((e2)&&((( e2 )->bbyloc) /*;dformula;;*/ !=(( e2 )->eyloc) /*;
dformula;;*/ )) { cross = 0; if ( ((( (( e2 )->start) /*;};*/ )->position) /*;
};*/ <(( (( e )->start) /*;};*/ )->position) /*;};*/ ) &&((( (( e2 )->end) /*;
};*/ )->position) /*;};*/ >(( (( e )->end) /*;};*/ )->position) /*;}
;*/ ) ) cross=1; if ( ((( (( e2 )->start) /*;};*/ )->position) /*;};
*/ >(( (( e )->start) /*;};*/ )->position) /*;};*/ ) &&((( (( e2 )->end) /*;
node )->predleft) /+;R/SC;yy+NT ;;*/ )->position) /*; node )->predleft) /+;
R/SC;yy+NT ;;*/ <(( (( e )->end) /*; node )->predleft) /+;R/SC;yy+NT ;
;*/ )->position) /*; node )->predleft) /+;R/SC;yy+NT ;;*/ ) ) cross=1; /*;e2 )->bbyloc) /+;R/SC;yy+NT !=(( e2 )->
cross = 0;;*/  kx = (( e2 )->bbxloc) /*;e2 )->bbyloc) /+;R/SC;yy+NT !=(( e2 )->;*/ - G_dspace+3; /*;e2 )->bbyloc) /+;R/SC;yy+NT !=(( e2 )->
cross = 0;;*/ if (kx>=tx) break; ky = (( e2 )->bbyloc) /*;( (( e2 )->start) /+;R/SC;
yy+NT )->posi;*/ ; if ((kx>=sx) && (!cross)) { h = bendformula; if ((h>0)&&(h<bendp)) bendp = h; /*;yy+NT )->position) /+;R/SC;yy+NT <(( ((
- /_dspace+3;;*/ } } li2 = (( li2 )->next) /*;2 )->bbyloc) /+;R/SC;yy+NT ;;*/ ; } } else if (tx<sx) { /*;0)&&(h<bendp)) bendp = h;
};*/   li2 = tpred_connection2[(( (( li )->node) /*;};*/ )->position) /*;
};*/ ];  li2 = (( li2 )->next) /*;};*/ ; while (li2) { node = (( li2 )->node) /*;
};*/ ; if (!(( node )->anchordummy) /*;};*/ ) {  kx = (( node )->xloc) /*;
(tx<sx) { ;*/ + (( node )->width) /*; (tx<sx) { ;*/ ; if (kx<=tx) break; /*;nnection2[(( (( li )->node) /+;R/SC;yy+
/+;R/SC;yy+NT ;;*/ if ((( node )->shape) /*; /+;R/SC;yy+NT ;;*/ ==1 /*; /+;R/SC;yy+NT ;
;*/ ) { kx += 3; myoff = (kx-sx)*offset/(tx-sx); ky = (( node )->yloc) /*;
->anchordummy) /+;R/SC;yy+NT ) { ;*/ + (( node )->height) /*;->anchordummy) /+;
R/SC;yy+NT ) { ;*/ /2 - myoff; if (kx<=sx) { h = bendformula; if ((h>0)&&(h<bendp)) bendp = h; /*;node )->shape) /+;R/SC;yy+NT ==1 /+;R/S
kx += 3;;*/ } kx -= (( node )->width) /*; (kx-sx)*offset*(tx-sx);;*/ /2; if (kx<=tx) break; /*;->yloc) /+;R/SC;yy+NT + (( node )->heig
if (kx<=sx) {;*/ myoff = (kx-sx)*offset/(tx-sx); ky = (( node )->yloc) /*;dformula;;*/ - myoff; /*;dformula;
bendp)) bendp = h;;*/ if (kx<=sx) { h = bendformula; if ((h>0)&&(h<bendp)) bendp = h; } } else if ((( node )->shape) /*;
C;yy+NT - myoff;;*/ ==3 /*;C;yy+NT - myoff;;*/ ) { kx += 3; myoff = (kx-sx)*offset/(tx-sx); /*;dformula;
bendp)) bendp = h;;*/ ky = (( node )->yloc) /*;bendp)) bendp = h;;*/ + (( node )->height) /*;
bendp)) bendp = h;;*/ - myoff; if (kx<=sx) { h = bendformula; if ((h>0)&&(h<bendp)) bendp = h; /*; ((( node )->shape) /+;R/SC;yy+NT ==3 /
kx += 3;;*/ } kx -= (( node )->width) /*; (kx-sx)*offset*(tx-sx);;*/ /2; if (kx<=tx) break; /*;->yloc) /+;R/SC;yy+NT + (( node )->heig
if (kx<=sx) {;*/ myoff = (kx-sx)*offset/(tx-sx); ky = (( node )->yloc) /*;dformula;;*/ - myoff; /*;dformula;
bendp)) bendp = h;;*/ if (kx<=sx) { h = bendformula; if ((h>0)&&(h<bendp)) bendp = h; } } else { /*;C;yy+NT - myoff;
if (kx<=sx) {;*/ myoff = (kx-sx)*offset/(tx-sx); ky = (( node )->yloc) /*;dformula;;*/ - myoff; /*;dformula;
bendp)) bendp = h;;*/ if (kx<=sx) {  h = bendformula; if ((h>0)&&(h<bendp)) bendp = h; } } /*;if (kx<=sx) { 
dformula;;*/  } e2 = (( node )->predright) /*;if (kx<=sx) { ;*/ ; if ((e2)&&((( e2 )->bbyloc) /*;
dformula;;*/ !=(( e2 )->eyloc) /*;dformula;;*/ )) { cross = 0; if ( ((( (( e2 )->start) /*;
};*/ )->position) /*;};*/ <(( (( e )->start) /*;};*/ )->position) /*;
};*/ ) &&((( (( e2 )->end) /*;};*/ )->position) /*;};*/ >(( (( e )->end) /*;
};*/ )->position) /*;};*/ ) ) cross=1; if ( ((( (( e2 )->start) /*;}
;*/ )->position) /*;};*/ >(( (( e )->start) /*;};*/ )->position) /*;
};*/ ) &&((( (( e2 )->end) /*; node )->predright) /+;R/SC;yy+NT ;;*/ )->position) /*;
node )->predright) /+;R/SC;yy+NT ;;*/ <(( (( e )->end) /*; node )->predright) /+;
R/SC;yy+NT ;;*/ )->position) /*; node )->predright) /+;R/SC;yy+NT ;;
*/ ) ) cross=1; kx = (( e2 )->bbxloc) /*;e2 )->bbyloc) /+;R/SC;yy+NT !=(( e2 )->;
*/ + G_dspace-3; if (kx<=tx) break; ky = (( e2 )->bbyloc) /*;( (( e2 )->start) /+;
R/SC;yy+NT )->posi;*/ ; if ((kx<=sx) && (!cross)) { h = bendformula; /*;yy+NT )->position) /+;R/SC;yy+NT <(( ((
+ /_dspace-3;;*/  if ((h>0)&&(h<bendp)) bendp = h; } } li2 = (( li2 )->next) /*;2 )->bbyloc) /+;
R/SC;yy+NT ;;*/ ; } } return(bendp); }
#ifdef ANSI_C
static void gs_ide1537 (void)
#else
static void gs_ide1537 ()
#endif
{ int i; GNLIST li, li2; GNODE node; GEDGE e1,e2,e3; int ax, ay, mx, my, by, b2y, okay; /*;_ide1537 ()
{;*/ int kx,ky,h; ; assert((layer)); for (i=0; i<=maxdepth+1; i++) { if (i%10==0) gs_wait_message('e'); /*;1,e2,e3;
, my, by, b2y, okay;;*/ li = (( layer[i] ).predlist) /*;, my, by, b2y, okay;;*/ ; while (li) { /*;;
(layer));;*/  tpred_connection1[(( (( li )->node) /*;;;*/ )->position) /*;;;*/ ] = li; /*;;
(layer));;*/ li = (( li )->next) /*;(layer));;*/ ; } li = (( layer[i] ).succlist) /*;
message('e');;*/ ; while (li) { node = (( li )->node) /*;while (li) {
;*/ ; if ( ((( node )->width) /*;onnection1[(( (( li )->node) /+;R/SC;
yy;*/ ==0) &&((( node )->succ) /*;next) /+;R/SC;yy+NT ;;*/ ) && ((( (( node )->succ) /*;
next) /+;R/SC;yy+NT ;;*/ )->next) /*;next) /+;R/SC;yy+NT ;;*/ ==NULL) &&((( node )->pred) /*;
};*/ ) && ((( (( node )->pred) /*;};*/ )->next) /*;};*/ ==NULL)) { e1 = (( (( node )->pred) /*;
layer[i] ).succlist) /+;R/SC;yy+NT ;;*/ )->kante) /*; layer[i] ).succlist) /+;
R/SC;yy+NT ;;*/ ; e2 = (( (( node )->succ) /*;while (li) {;*/ )->kante) /*;
while (li) {;*/ ; my = (( e2 )->syloc) /*;(( li )->node) /+;R/SC;yy+NT ;
;*/ ; by = (( e2 )->btyloc) /*;)->width) /+;R/SC;yy+NT ==0);*/ ; b2y = (( e1 )->bbyloc) /*;
+;R/SC;yy+NT ) && ((( (( node )->succ) ;*/ ; ay = (( e1 )->btyloc) /*;
yy+NT ) && ((( (( node )->pred) /+;R/SC;*/ ; if ( (b2y==(( e1 )->eyloc) /*;
+NT )->kante) /+;R/SC;yy+NT ;;*/ )  &&(by>my) && (by>ay)) { ax = (( e1 )->btxloc) /*;
2 )->syloc) /+;R/SC;yy+NT ;;*/ ; mx = (( e2 )->sxloc) /*;yloc) /+;R/SC;
yy+NT ;;*/ ; okay = 1; if ( ((ax<mx)&&(mx<(( e2 )->bbxloc) /*;yy+NT ;
;*/ )) ||((ax<mx)&&(G_spline))) { li2 = tpred_connection1[(( node )->position) /*;
y>my) && (by>ay)) {;*/ ];  li2 = (( li2 )->next) /*;)->btxloc) /+;R/SC;
yy+NT ;;*/ ; while (li2) { if (okay==0) break; if (!(( (( li2 )->node) /*;
ax<mx)&&(mx<(( e2 )->bbxloc) /+;R/SC;yy;*/ )->anchordummy) /*;ax<mx)&&(mx<(( e2 )->bbxloc) /+;
R/SC;yy;*/ ) {  kx = (( (( li2 )->node) /*;_spline))) {;*/ )->xloc) /*;
_spline))) {;*/ + (( (( li2 )->node) /*;_spline))) {;*/ )->width) /*;
_spline))) {;*/ ; if ((( (( li2 )->node) /*;n1[(( node )->position) /+;
R/SC;yy+NT ];*/ )->width) /*;n1[(( node )->position) /+;R/SC;yy+NT ];
*/ ==0) kx += G_dspace; if (kx<=ax) break; ky = (( (( li2 )->node) /*;
y==0) break;;*/ )->yloc) /*;y==0) break;;*/ - 2; if (kx<=mx) {  h = ((mx-kx)*(ay-by))/(mx-ax)+by; /*;e) /+;R/SC;yy+NT )->xloc) /+;R/SC;yy+NT
SC;yy+NT )->width) /+;R/SC;yy+NT ==0);*/ if (ky<=h) okay = 0; } } e3 = (( (( li2 )->node) /*; )->node) /+;R/SC;
yy+NT )->yloc) /+;R/S;*/ )->predright) /*; )->node) /+;R/SC;yy+NT )->yloc) /+;
R/S;*/ ; if ((e3)&&((( e3 )->bbyloc) /*;if (kx<=mx) { ;*/ !=(( e3 )->eyloc) /*;
if (kx<=mx) { ;*/ )) { kx = (( e3 )->bbxloc) /*;x-kx)*(ay-by))*(mx-ax)+by;
;*/ + G_dspace-3; if (kx<=ax) break; ky = (( e3 )->bbyloc) /*;};*/ ; /*;}
(( li2 )->node) /+;R/SC;yy+NT )->predr;*/  if (kx<=mx) { h = ((mx-kx)*(ay-by))/(mx-ax)+by; if (ky<=h) okay = 0; /*; /+;R/SC;yy+NT + /_dspace-3;
if (kx<=ax) break;;*/  } } li2 = (( li2 )->next) /*; e3 )->bbyloc) /+;R/SC;yy+NT ;;*/ ; } if (okay) { /*;x-kx)*(ay-by))*(mx-ax)+by;
y = 0;;*/ (( e2 )->syloc) /*;y = 0;;*/ = (( e1 )->bbyloc) /*;};*/ = (( e1 )->eyloc) /*;
};*/ =(( e2 )->btyloc) /*;};*/ ; } } else if ( ((ax>mx)&&(mx>(( e2 )->bbxloc) /*;
y) {;*/ )) ||((ax>mx)&&(G_spline))) { li2 = (( li )->next) /*;/SC;yy+NT =;
*/ ; while (li2) { if (okay==0) break; if (!(( (( li2 )->node) /*;};
*/ )->anchordummy) /*;};*/ ) {  kx = (( (( li2 )->node) /*; ( ((ax>mx)&&(mx>(( e2 )->bbxloc) /+;
R/;*/ )->xloc) /*; ( ((ax>mx)&&(mx>(( e2 )->bbxloc) /+;R/;*/ ; if ((( (( li2 )->node) /*;
_spline))) {;*/ )->width) /*;_spline))) {;*/ ==0) kx -= G_dspace; if (kx>=ax) break; /*;while (li2) {
y==0) break;;*/ ky = (( (( li2 )->node) /*;y==0) break;;*/ )->yloc) /*;y==0) break;;
*/ - 2; if (kx>=mx) {  h = ((mx-kx)*(ay-by))/(mx-ax)+by; if (ky<=h) okay = 0; /*;SC;yy+NT )->width) /+;R/SC;yy+NT ==0)
kx -= /_dspace;;*/ } } e3 = (( (( li2 )->node) /*; )->node) /+;R/SC;yy+NT )->yloc) /+;R/S;
*/ )->predleft) /*; )->node) /+;R/SC;yy+NT )->yloc) /+;R/S;*/ ; if ((e3)&&((( e3 )->bbyloc) /*;
if (kx>=mx) { ;*/ !=(( e3 )->eyloc) /*;if (kx>=mx) { ;*/ )) { kx = (( e3 )->bbxloc) /*;
x-kx)*(ay-by))*(mx-ax)+by;;*/ - G_dspace+3; if (kx>=ax) break; ky = (( e3 )->bbyloc) /*;
};*/ ; if (kx>=mx) { h = ((mx-kx)*(ay-by))/(mx-ax)+by; if (ky<=h) okay = 0; /*;e3 )->bbyloc) /+;R/SC;yy+NT !=(( e3 )->
/+;R/SC;yy+NT - /_dspace+3;;*/ } } li2 = (( li2 )->next) /*; e3 )->bbyloc) /+;R/SC;yy+NT ;;*/ ; } if (okay) { /*;x-kx)*(ay-by))*(mx-ax)+by;
y = 0;;*/ (( e2 )->syloc) /*;y = 0;;*/ = (( e1 )->bbyloc) /*;};*/ =  (( e1 )->eyloc) /*;
};*/ =(( e2 )->btyloc) /*;};*/ ; } }  } ay = (( e2 )->bbyloc) /*;) /+;
R/SC;yy+NT =;*/ ; if ( (by==(( e2 )->syloc) /*;/SC;yy+NT = ;*/ )  &&(b2y<my) && (b2y<ay)) { /*;T =(( e2 )->btyloc) /+;R/SC;yy+NT ;
};*/ ax = (( e2 )->bbxloc) /*;};*/ ; mx = (( e2 )->sxloc) /*;} ;*/ ; by = b2y; /*;}
e2 )->bbyloc) /+;R/SC;yy+NT ;;*/   okay = 1; if ( ((ax<mx)&&(mx<(( e1 )->btxloc) /*;2 )->syloc) /+;R/SC;
yy+NT ) ;*/ )) ||((ax<mx)&&(G_spline))) { li2 = tpred_connection1[(( node )->position) /*;
C;yy+NT ;;*/ ];  li2 = (( li2 )->next) /*;;;*/ ; while (li2) { if (okay==0) break; /*;
mx<(( e1 )->btxloc) /+;R/SC;yy+NT ));*/ if (!(( (( li2 )->node) /*;mx<(( e1 )->btxloc) /+;R/SC;yy+NT ));*/ )->anchordummy) /*;
mx<(( e1 )->btxloc) /+;R/SC;yy+NT ));*/ ) {  kx = (( (( li2 )->node) /*;
) {;*/ )->xloc) /*;) {;*/ + (( (( li2 )->node) /*;) {;*/ )->width) /*;
) {;*/ ; if ((( (( li2 )->node) /*;e )->position) /+;R/SC;yy+NT ]; ;
*/ )->width) /*;e )->position) /+;R/SC;yy+NT ]; ;*/ ==0) kx += G_dspace; /*;
e (li2) {;*/ if (kx<=ax) break; ky = (( (( li2 )->node) /*;) break;;*/ )->yloc) /*;
) break;;*/ +(( (( li2 )->node) /*;) break;;*/ )->height) /*;) break;
;*/ +2; if (kx<=mx) {  h = ((mx-kx)*(ay-by))/(mx-ax)+by; if (ky>=h) okay = 0; /*;y+NT )->width) /+;R/SC;yy+NT ==0)
kx += /_dspace;;*/ } } e3 = (( (( li2 )->node) /*; )->node) /+;R/SC;yy+NT )->yloc) /+;R/S;
*/ )->succright) /*; )->node) /+;R/SC;yy+NT )->yloc) /+;R/S;*/ ; if ((e3)&&((( e3 )->btyloc) /*;
if (kx<=mx) { ;*/ !=(( e3 )->syloc) /*;if (kx<=mx) { ;*/ )) { kx = (( e3 )->btxloc) /*;
x-kx)*(ay-by))*(mx-ax)+by;;*/ + G_dspace-3; if (kx<=ax) break; ky = (( e3 )->btyloc) /*;
};*/ ; if (kx<=mx) { h = ((mx-kx)*(ay-by))/(mx-ax)+by; if (ky>=h) okay = 0; /*;e3 )->btyloc) /+;R/SC;yy+NT !=(( e3 )->
/+;R/SC;yy+NT + /_dspace-3;;*/ } } li2 = (( li2 )->next) /*; e3 )->btyloc) /+;R/SC;yy+NT ;;*/ ; } if (okay) { /*;x-kx)*(ay-by))*(mx-ax)+by;
y = 0;;*/ (( e2 )->syloc) /*;y = 0;;*/ = (( e2 )->btyloc) /*;};*/ = (( e1 )->eyloc) /*;
};*/ =(( e1 )->bbyloc) /*;};*/ ; } } else if ( ((ax>mx)&&(mx>(( e1 )->btxloc) /*;
y) {;*/ )) ||((ax>mx)&&(G_spline))) { li2 = (( li )->next) /*;/SC;yy+NT =;
*/ ; while (li2) { if (okay==0) break; if (!(( (( li2 )->node) /*;};
*/ )->anchordummy) /*;};*/ ) {  kx = (( (( li2 )->node) /*; ( ((ax>mx)&&(mx>(( e1 )->btxloc) /+;
R/;*/ )->xloc) /*; ( ((ax>mx)&&(mx>(( e1 )->btxloc) /+;R/;*/ ; if ((( (( li2 )->node) /*;
_spline))) {;*/ )->width) /*;_spline))) {;*/ ==0) kx -= G_dspace; if (kx>=ax) break; /*;while (li2) {
y==0) break;;*/ ky = (( (( li2 )->node) /*;y==0) break;;*/ )->yloc) /*;y==0) break;;
*/ +(( (( li2 )->node) /*;y==0) break;;*/ )->height) /*;y==0) break;
;*/ +2; if (kx>=mx) {  h = ((mx-kx)*(ay-by))/(mx-ax)+by; if (ky>=h) okay = 0; /*;SC;yy+NT )->width) /+;R/SC;yy+NT ==0)
kx -= /_dspace;;*/ } } e3 = (( (( li2 )->node) /*; )->node) /+;R/SC;yy+NT )->yloc) /+;R/S;
*/ )->succleft) /*; )->node) /+;R/SC;yy+NT )->yloc) /+;R/S;*/ ; if ((e3)&&((( e3 )->btyloc) /*;
if (kx>=mx) { ;*/ !=(( e3 )->syloc) /*;if (kx>=mx) { ;*/ )) { kx = (( e3 )->btxloc) /*;
x-kx)*(ay-by))*(mx-ax)+by;;*/ - G_dspace+3; if (kx>=ax) break; ky = (( e3 )->btyloc) /*;
};*/ ; if (kx>=mx) { h = ((mx-kx)*(ay-by))/(mx-ax)+by; if (ky>=h) okay = 0; /*;e3 )->btyloc) /+;R/SC;yy+NT !=(( e3 )->
/+;R/SC;yy+NT - /_dspace+3;;*/ } } li2 = (( li2 )->next) /*; e3 )->btyloc) /+;R/SC;yy+NT ;;*/ ; } if (okay) { /*;x-kx)*(ay-by))*(mx-ax)+by;
y = 0;;*/ (( e2 )->syloc) /*;y = 0;;*/ = (( e2 )->btyloc) /*;};*/ = (( e1 )->eyloc) /*;
};*/ =(( e1 )->bbyloc) /*;};*/ ; } }  } } li = (( li )->next) /*;/SC;
yy+NT =;*/ ; } } }
#ifdef ANSI_C
static void gs_ide1504 (void)
#else
static void gs_ide1504 ()
#endif
{ GNODE v; ; v = nodelist; while (v) { calc_edgearrow(v); v = (( v )->next) /*;
{;*/ ; } v = labellist; while (v) { calc_edgearrow(v); v = (( v )->next) /*;
gearrow(v);;*/ ; } v = dummylist; while (v) { calc_edgearrow(v); v = (( v )->next) /*;
gearrow(v);;*/ ; } }
#ifdef ANSI_C
void calc_edgearrow(GNODE v)
#else
void calc_edgearrow(v) GNODE v;
#endif
{ ADJEDGE a; int act_port, j; CONNECT c; ; c = (( v )->connection) /*;
/N;D+ v;;*/ ; if (c) { if (((( c )->target) /*; a;;*/ )&&((( (( c )->edge) /*;
a;;*/ )->end) /*; a;;*/ ==v))  gs_ide1511 ((( c )->edge) /*;j;;*/ ); /*;C;NN+CT c;
;;*/  if (((( c )->target2) /*;C;NN+CT c;;*/ )&&((( (( c )->edge2) /*;C;NN+CT c;
;*/ )->end) /*;C;NN+CT c;;*/ ==v))  gs_ide1511 ((( c )->edge2) /*;;;
*/ ); } a = (( v )->succ) /*;if (c) {;*/ ; act_port = -1; while (a) { /*; /+;R/SC;yy+NT )&&((( (( c )->edge2) /+
+;R/SC;yy+NT );;*/  if ((((( (( a )->kante) /*; /+;R/SC;yy+NT )&&((( (( c )->edge2) /+;
*/ )->kantenart) /*; /+;R/SC;yy+NT )&&((( (( c )->edge2) /+;*/ ) /*;
/+;R/SC;yy+NT )&&((( (( c )->edge2) /+;*/ =='l')||(((( (( a )->kante) /*;
/+;R/SC;yy+NT )&&((( (( c )->edge2) /+;*/ )->kantenart) /*; /+;R/SC;
yy+NT )&&((( (( c )->edge2) /+;*/ ) /*; /+;R/SC;yy+NT )&&((( (( c )->edge2) /+;
*/ =='r')) ; else if (act_port!=(( (( a )->kante) /*;+;R/SC;yy+NT );
;*/ )->weights) /*;+;R/SC;yy+NT );;*/ ) { act_port = (( (( a )->kante) /*;
};*/ )->weights) /*;};*/ ; gs_ide1512 (a);  } a = (( a )->next) /*;while (a) {
;*/ ; } a = (( v )->pred) /*;ort!=(( (( a )->kante) /+;R/SC;yy+NT )-;
*/ ; act_port = -1; while (a) { if ((((( (( a )->kante) /*;};*/ )->kantenart) /*;
};*/ ) /*;};*/ =='l')||(((( (( a )->kante) /*;};*/ )->kantenart) /*;
};*/ ) /*;};*/ =='r')) gs_ide1511 ((( a )->kante) /*;a )->next) /+;R/SC;
yy+NT ;;*/ ); else if (act_port!=(( (( a )->kante) /*;};*/ )->weightp) /*;
};*/ ) { act_port = (( (( a )->kante) /*;v )->pred) /+;R/SC;yy+NT ;;
*/ )->weightp) /*;v )->pred) /+;R/SC;yy+NT ;;*/ ; gs_ide1510 (a);  } /*;( (( a )->kante) /+;R/SC;yy+NT )->kante
a )->kante) /+;R/SC;yy+NT );;*/  a = (( a )->next) /*;( (( a )->kante) /+;R/SC;yy+NT )->kante;*/ ; } /*; (( a )->kante) /+;R/SC;yy+NT )->weight
/+;R/SC;yy+NT )->weightp) /+;R/SC;yy+N;*/  if ((( v )->anchordummy) /*; (( a )->kante) /+;R/SC;yy+NT )->weight;
*/ ) { c = (( v )->connection) /*; /+;R/SC;yy+NT )->weightp) /+;R/SC;
yy+N;*/ ; assert(c && ((( c )->target) /*;gs_ide1510 (a); ;*/ )); assert(((( (( c )->edge) /*;
};*/ )->end) /*;};*/ ==v)); if ((( (( c )->edge) /*;a )->next) /+;R/SC;
yy+NT ;;*/ )->sxloc) /*;a )->next) /+;R/SC;yy+NT ;;*/ <(( (( c )->edge) /*;
a )->next) /+;R/SC;yy+NT ;;*/ )->exloc) /*;a )->next) /+;R/SC;yy+NT ;
;*/ ) j = 8 /*;};*/ ; else j = 7 /*;v )->anchordummy) /+;R/SC;yy+NT ) {
;*/ ; a = (( v )->succ) /*;nnection) /+;R/SC;yy+NT ;;*/ ; while (a) { /*;R/SC;yy+NT )->end) /+;R/SC;yy+NT ==v));
)->sxloc) /+;R/SC;yy+NT <(( (( c )->edg;*/  (( (( a )->kante) /*;R/SC;yy+NT )->end) /+;R/SC;yy+NT ==v));;*/ )->orientation2) /*;
R/SC;yy+NT )->end) /+;R/SC;yy+NT ==v));;*/ = j; a = (( a )->next) /*;
)->sxloc) /+;R/SC;yy+NT <(( (( c )->edg;*/ ; } a = (( v )->pred) /*;
7 /+;R/SC;yy+NT ;;*/ ; while (a) { (( (( a )->kante) /*;while (a) {;
*/ )->orientation) /*;while (a) {;*/ = j; a = (( a )->next) /*; )->kante) /+;
R/SC;yy+NT )->orientation;*/ ; } if ((( c )->target2) /*;};*/ ) { assert(((( (( c )->edge2) /*;
v )->pred) /+;R/SC;yy+NT ;;*/ )->start) /*;v )->pred) /+;R/SC;yy+NT ;
;*/ ==v)); (( (( c )->edge2) /*;while (a) {;*/ )->orientation2) /*;while (a) {
;*/ = j; } } }
#ifdef ANSI_C
static void gs_ide1511 (GEDGE e)
#else
static void gs_ide1511 (e) GEDGE e;
#endif
{ float fval; ; assert(((( e )->sxloc) /*;void gs_ide1511 (/+D/+ e);
*/ !=(( e )->exloc) /*;void gs_ide1511 (/+D/+ e);*/ )); fval = (float)((( e )->eyloc) /*;
_ide1511 (e);*/ - (( e )->syloc) /*;_ide1511 (e);*/ )/(float)((( e )->exloc) /*;
_ide1511 (e);*/ - (( e )->sxloc) /*;_ide1511 (e);*/ ); if ((( e )->sxloc) /*;
/+D/+ e;;*/ <(( e )->exloc) /*;/+D/+ e;;*/ ) {  if (0.5 <= fval) (( e )->orientation) /*;
{;*/ = 5 /*;{;*/ ;  else if (-0.5 < fval) (( e )->orientation) /*;val;
;*/ = 7 /*;val;;*/ ;  else (( e )->orientation) /*;;;*/ = 2 /*;;;*/ ; /*;((( e )->sxloc) /+;R/SC;yy+NT !=(( e )-
((( e )->eyloc) /+;R/SC;yy+NT - (( e )-;*/   } else {  if (0.5 <= fval) (( e )->orientation) /*;;R/SC;yy+NT <(( e )->exloc) /+;
R/SC;yy+;*/ = 3 /*;;R/SC;yy+NT <(( e )->exloc) /+;R/SC;yy+;*/ ;  else if (-0.5 < fval) (( e )->orientation) /*;
entation) /+;R/SC;yy+NT = 5 /+;R/SC;yy+;*/ = 8 /*;entation) /+;R/SC;
yy+NT = 5 /+;R/SC;yy+;*/ ;  else (( e )->orientation) /*;tation) /+;
R/SC;yy+NT = 7 /+;R/SC;yy+NT;*/ = 6 /*;tation) /+;R/SC;yy+NT = 7 /+;
R/SC;yy+NT;*/ ;  } switch ((( e )->orientation) /*;};*/ ) { case 5 /*;
;*/ : (( e )->orientation2) /*;;*/ = 3 /*;;*/ ; break; case 7 /*;l) (( e )->orientation) /+;
R/SC;yy+NT =;*/ : (( e )->orientation2) /*;l) (( e )->orientation) /+;
R/SC;yy+NT =;*/ = 8 /*;l) (( e )->orientation) /+;R/SC;yy+NT =;*/ ; break; /*;l) (( e )->orientation) /+;R/SC;yy+NT =
(( e )->orientation) /+;R/SC;yy+NT = 8;*/ case 2 /*; (( e )->orientation) /+;R/SC;yy+NT = 8;*/ : (( e )->orientation2) /*;
(( e )->orientation) /+;R/SC;yy+NT = 8;*/ = 6 /*; (( e )->orientation) /+;
R/SC;yy+NT = 8;*/ ; break; case 6 /*;;R/SC;yy+NT = 6 /+;R/SC;yy+NT ;
;*/ : (( e )->orientation2) /*;;R/SC;yy+NT = 6 /+;R/SC;yy+NT ; ;*/ = 2 /*;
;R/SC;yy+NT = 6 /+;R/SC;yy+NT ; ;*/ ; break; case 8 /*;};*/ : (( e )->orientation2) /*;
};*/ = 7 /*;};*/ ; break; case 3 /*;((( e )->orientation) /+;R/SC;yy+NT ) {
;*/ : (( e )->orientation2) /*;((( e )->orientation) /+;R/SC;yy+NT ) {
;*/ = 5 /*;((( e )->orientation) /+;R/SC;yy+NT ) {;*/ ; break; } }
#ifdef ANSI_C
static void gs_ide1512 (ADJEDGE a)
#else
static void gs_ide1512 (a) ADJEDGE a;
#endif
{ int port; int is_north, is_northeast, is_northwest; ADJEDGE b; GEDGE e; /*;_ide1512 (a)
ADJ+D/+ a;;*/ float fval; ; port = (( (( a )->kante) /*;t;;*/ )->weights) /*;t;;*/ ; /*;is_northeast, is_northwest;
ADJ+D/+ b;;*/  b = a; is_north = is_northeast = is_northwest = 1; while (b) { if (port!=(( (( b )->kante) /*;
float fval;;*/ )->weights) /*;float fval;;*/ ) break;  e = (( b )->kante) /*;
;;*/ ; if ((( e )->btyloc) /*;(( (( a )->kante) /+;R/SC;yy+NT )->weig;
*/ !=(( e )->syloc) /*;(( (( a )->kante) /+;R/SC;yy+NT )->weig;*/ )  fval = (float)((( e )->btxloc) /*;
b = a;;*/ - (( e )->sxloc) /*;b = a;;*/ )/ (float)((( e )->btyloc) /*;
h = is_northeast = is_northwest = 1;;*/ - (( e )->syloc) /*;h = is_northeast = is_northwest = 1;
;*/ ); else fval = (float)((( e )->bbxloc) /*;while (b) {;*/ - (( e )->sxloc) /*;
while (b) {;*/ )/ (float)((( e )->bbyloc) /*;t!=(( (( b )->kante) /+;
R/SC;yy+NT )->w;*/ - (( e )->syloc) /*;t!=(( (( b )->kante) /+;R/SC;
yy+NT )->w;*/ ); if (!((-0.5<fval)&&(fval<0.5))) is_north = 0;  if (!(0.1<fval)) is_northwest = 0; /*;+;R/SC;yy+NT !=(( e )->syloc) /+;R/SC;y
c) /+;R/SC;yy+NT - (( e )->sxloc) /+;R/;*/   if (!(fval<-0.1)) is_northeast = 0;  b = (( b )->next) /*;NT - (( e )->syloc) /+;
R/SC;yy+NT );;*/ ; } if (is_north) { b = a; while (b) { if (port!=(( (( b )->kante) /*;
= 0; ;*/ )->weights) /*; = 0; ;*/ ) break;  (( (( b )->kante) /*;b = (( b )->next) /+;
R/SC;yy+NT ;;*/ )->orientation2) /*;b = (( b )->next) /+;R/SC;yy+NT ;
;*/ = 1 /*;b = (( b )->next) /+;R/SC;yy+NT ;;*/ ; b = (( b )->next) /*;
};*/ ; } return; }  if (is_northwest) { b = a; while (b) { if (port!=(( (( b )->kante) /*;
};*/ )->weights) /*;};*/ ) break;  (( (( b )->kante) /*;;*/ )->orientation2) /*;
;*/ = 3 /*;;*/ ; b = (( b )->next) /*;} ;*/ ; } return; }  if (is_northeast) { /*;( b )->kante) /+;R/SC;yy+NT )->weights)
R/SC;yy+NT )->orientation2) /+;R/SC;yy+;*/ b = a; while (b) { if (port!=(( (( b )->kante) /*;};*/ )->weights) /*;
};*/ ) break;  (( (( b )->kante) /*;;*/ )->orientation2) /*;;*/ = 2 /*;
;*/ ; b = (( b )->next) /*;} ;*/ ; } return; }  b = a; while (b) { if (port!=(( (( b )->kante) /*;
+NT ;;*/ )->weights) /*;+NT ;;*/ ) break;  (( (( b )->kante) /*;};*/ )->orientation2) /*;
};*/ = 1 /*;};*/ ; b = (( b )->next) /*;;*/ ; } }
#ifdef ANSI_C
static void gs_ide1510 (ADJEDGE a)
#else
static void gs_ide1510 (a) ADJEDGE a;
#endif
{ int port; int is_south, is_southwest, is_southeast; ADJEDGE b; GEDGE e; /*;_ide1510 (a)
ADJ+D/+ a;;*/ float fval; ; port = (( (( a )->kante) /*;t;;*/ )->weightp) /*;t;;*/ ; /*;is_southwest, is_southeast;
ADJ+D/+ b;;*/  b = a; is_south = is_southeast = is_southwest = 1; while (b) { if (port!=(( (( b )->kante) /*;
float fval;;*/ )->weightp) /*;float fval;;*/ ) break;  e = (( b )->kante) /*;
;;*/ ; if ((( e )->bbyloc) /*;(( (( a )->kante) /+;R/SC;yy+NT )->weig;
*/ !=(( e )->eyloc) /*;(( (( a )->kante) /+;R/SC;yy+NT )->weig;*/ )  fval = (float)((( e )->exloc) /*;
b = a;;*/ - (( e )->bbxloc) /*;b = a;;*/ )/ (float)((( e )->eyloc) /*;
h = is_southeast = is_southwest = 1;;*/ - (( e )->bbyloc) /*;h = is_southeast = is_southwest = 1;
;*/ ); else fval = (float)((( e )->exloc) /*;while (b) {;*/ - (( e )->btxloc) /*;
while (b) {;*/ )/ (float)((( e )->eyloc) /*;t!=(( (( b )->kante) /+;
R/SC;yy+NT )->w;*/ - (( e )->btyloc) /*;t!=(( (( b )->kante) /+;R/SC;
yy+NT )->w;*/ ); if (!((-0.5<fval)&&(fval<0.5))) is_south = 0;  if (!(0.1<fval)) is_southeast = 0; /*;+;R/SC;yy+NT !=(( e )->eyloc) /+;R/SC;y
) /+;R/SC;yy+NT - (( e )->bbxloc) /+;R/;*/   if (!(fval<-0.1)) is_southwest = 0;  b = (( b )->next) /*;T - (( e )->bbyloc) /+;
R/SC;yy+NT );;*/ ; } if (is_south) { b = a; while (b) { if (port!=(( (( b )->kante) /*;
= 0; ;*/ )->weightp) /*; = 0; ;*/ ) break;  (( (( b )->kante) /*;b = (( b )->next) /+;
R/SC;yy+NT ;;*/ )->orientation) /*;b = (( b )->next) /+;R/SC;yy+NT ;
;*/ = 4 /*;b = (( b )->next) /+;R/SC;yy+NT ;;*/ ; b = (( b )->next) /*;
};*/ ; } return; }  if (is_southeast) { b = a; while (b) { if (port!=(( (( b )->kante) /*;
};*/ )->weightp) /*;};*/ ) break;  (( (( b )->kante) /*;;*/ )->orientation) /*;
;*/ = 5 /*;;*/ ; b = (( b )->next) /*;} ;*/ ; } return; }  if (is_southwest) { /*;( b )->kante) /+;R/SC;yy+NT )->weightp)
R/SC;yy+NT )->orientation) /+;R/SC;yy+N;*/ b = a; while (b) { if (port!=(( (( b )->kante) /*;};*/ )->weightp) /*;
};*/ ) break;  (( (( b )->kante) /*;;*/ )->orientation) /*;;*/ = 6 /*;
;*/ ; b = (( b )->next) /*;} ;*/ ; } return; }  b = a; while (b) { if (port!=(( (( b )->kante) /*;
+NT ;;*/ )->weightp) /*;+NT ;;*/ ) break;  (( (( b )->kante) /*;};*/ )->orientation) /*;
};*/ = 4 /*;};*/ ; b = (( b )->next) /*;;*/ ; } }
#ifdef ANSI_C
static void gs_ide1521 (void)
#else
static void gs_ide1521 ()
#endif
{ ; gs_ide1519 (nodelist); gs_ide1519 (labellist); gs_ide1519 (dummylist); /*;void gs_ide1521 (void)
_ide1521 ();*/ }
#define backward_connection1(c) (((( c )->edge)  )&& ((( (( c )->edge)   )->end)   ==v))
#define backward_connection2(c) (((( c )->edge2)  )&&((( (( c )->edge2)   )->end)  ==v))
#ifdef ANSI_C
static void gs_ide1519 (GNODE v)
#else
static void gs_ide1519 (v) GNODE v; 
#endif
{  int h; CONNECT c; ADJEDGE li; ; while (v) { h = (( v )->xloc) /*;
{ ;*/ ; (( v )->xloc) /*;int h;;*/ = (( v )->yloc) /*;int h;;*/ ; (( v )->yloc) /*;
c;;*/ = h; h = (( v )->width) /*;ADJ+D/+ li;;*/ ; (( v )->width) /*;
;;*/ = (( v )->height) /*;;;*/ ; (( v )->height) /*;v) {;*/ = h; c = (( v )->connection) /*;
oc) /+;R/SC;yy+NT ;;*/ ; if (c) { if (backward_connection1(c)) gs_ide1520 ((( c )->edge) /*;
= h;;*/ ); if (backward_connection2(c)) gs_ide1520 ((( c )->edge2) /*;
h = (( v )->width) /+;R/SC;yy+NT ;;*/ ); } li = (( v )->pred) /*;) /+;
R/SC;yy+NT = h;;*/ ; while (li) { gs_ide1520 ((( li )->kante) /*;if (c) {
;*/ ); li = (( li )->next) /*;kward_connection1(c)) gs_ide1520 ((( c ;
*/ ; } v = (( v )->next) /*;};*/ ; } }
#ifdef ANSI_C
static void gs_ide1520 (GEDGE e) 
#else
static void gs_ide1520 (e) GEDGE e; 
#endif
{ int h; ; h = (( e )->sxloc) /*;void gs_ide1520 (/+D/+ e) ;*/ ; (( e )->sxloc) /*;
_ide1520 (e);*/ = (( e )->syloc) /*;_ide1520 (e);*/ ; (( e )->syloc) /*;
/+D/+ e; ;*/ = h; h = (( e )->btxloc) /*;{;*/ ; (( e )->btxloc) /*;int h;
;*/ = (( e )->btyloc) /*;int h;;*/ ; (( e )->btyloc) /*;;;*/ = h; h = (( e )->bbxloc) /*;
e )->sxloc) /+;R/SC;yy+NT ;;*/ ; (( e )->bbxloc) /*; /+;R/SC;yy+NT = (( e )->syloc) /+;
R/SC;*/ = (( e )->bbyloc) /*; /+;R/SC;yy+NT = (( e )->syloc) /+;R/SC;
*/ ; (( e )->bbyloc) /*;C;yy+NT = h;;*/ = h; h = (( e )->exloc) /*;yy+NT ;
;*/ ; (( e )->exloc) /*;e )->btyloc) /+;R/SC;yy+NT ;;*/ = (( e )->eyloc) /*;
e )->btyloc) /+;R/SC;yy+NT ;;*/ ; (( e )->eyloc) /*; e )->btyloc) /+;
R/SC;yy+NT = h;;*/ = h; switch ((( e )->orientation) /*;)->bbxloc) /+;
R/SC;yy+NT ;;*/ ) { case 0 /*;/+;R/SC;yy+NT = (( e )->bbyloc) /+;R/SC;
*/ : break; case 1 /*;;yy+NT = h;;*/ : (( e )->orientation) /*;;yy+NT = h;
;*/ = 8 /*;;yy+NT = h;;*/ ; break; case 2 /*;NT ;;*/ : (( e )->orientation) /*;
NT ;;*/ = 6 /*;NT ;;*/ ; break; case 3 /*;->eyloc) /+;R/SC;yy+NT ;;*/ : (( e )->orientation) /*;
->eyloc) /+;R/SC;yy+NT ;;*/ = 3 /*;->eyloc) /+;R/SC;yy+NT ;;*/ ; break; /*;->eyloc) /+;R/SC;yy+NT ;
)->eyloc) /+;R/SC;yy+NT = h;;*/ case 4 /*; )->eyloc) /+;R/SC;yy+NT = h;;*/ : (( e )->orientation) /*;
)->eyloc) /+;R/SC;yy+NT = h;;*/ = 7 /*; )->eyloc) /+;R/SC;yy+NT = h;
;*/ ; break;  case 5 /*;e )->orientation) /+;R/SC;yy+NT ) {;*/ : (( e )->orientation) /*;
e )->orientation) /+;R/SC;yy+NT ) {;*/ = 5 /*;e )->orientation) /+;R/SC;
yy+NT ) {;*/ ; break; case 6 /*;NT : break;;*/ : (( e )->orientation) /*;
NT : break;;*/ = 2 /*;NT : break;;*/ ; break; case 7 /*; e )->orientation) /+;
R/SC;yy+NT = 8 /+;*/ : (( e )->orientation) /*; e )->orientation) /+;
R/SC;yy+NT = 8 /+;*/ = 4 /*; e )->orientation) /+;R/SC;yy+NT = 8 /+;
*/ ; break;  case 8 /*;rientation) /+;R/SC;yy+NT = 6 /+;R/SC;y;*/ : (( e )->orientation) /*;
rientation) /+;R/SC;yy+NT = 6 /+;R/SC;y;*/ = 1 /*;rientation) /+;R/SC;
yy+NT = 6 /+;R/SC;y;*/ ; break;  } switch ((( e )->orientation2) /*;
/+;R/SC;yy+NT : (( e )->orientation) /;*/ ) { case 0 /*;C;yy+NT : (( e )->orientation) /+;
R/SC;;*/ : break; case 1 /*; : (( e )->orientation) /+;R/SC;yy+NT =;
*/ : (( e )->orientation2) /*; : (( e )->orientation) /+;R/SC;yy+NT =;
*/ = 8 /*; : (( e )->orientation) /+;R/SC;yy+NT =;*/ ; break; case 2 /*;
)->orientation) /+;R/SC;yy+NT = 4 /+;R;*/ : (( e )->orientation2) /*;
)->orientation) /+;R/SC;yy+NT = 4 /+;R;*/ = 6 /*; )->orientation) /+;
R/SC;yy+NT = 4 /+;R;*/ ; break; case 3 /*;entation) /+;R/SC;yy+NT = 1 /+;
R/SC;yy+;*/ : (( e )->orientation2) /*;entation) /+;R/SC;yy+NT = 1 /+;
R/SC;yy+;*/ = 3 /*;entation) /+;R/SC;yy+NT = 1 /+;R/SC;yy+;*/ ; break; /*;
(( e )->orientation2) /+;R/SC;yy+NT ) {;*/  case 4 /*;;*/ : (( e )->orientation2) /*;;*/ = 7 /*;;*/ ; break;  case 5 /*;
(( e )->orientation2) /+;R/SC;yy+NT ) {;*/ : (( e )->orientation2) /*;
(( e )->orientation2) /+;R/SC;yy+NT ) {;*/ = 5 /*;(( e )->orientation2) /+;
R/SC;yy+NT ) {;*/ ; break; case 6 /*;yy+NT : break;;*/ : (( e )->orientation2) /*;
yy+NT : break;;*/ = 2 /*;yy+NT : break;;*/ ; break; case 7 /*; (( e )->orientation2) /+;
R/SC;yy+NT = ;*/ : (( e )->orientation2) /*; (( e )->orientation2) /+;
R/SC;yy+NT = ;*/ = 4 /*; (( e )->orientation2) /+;R/SC;yy+NT = ;*/ ; /*; (( e )->orientation2) /+;R/SC;yy+NT = 
->orientation2) /+;R/SC;yy+NT = 6 /+;R/;*/  break;  case 8 /*;->orientation2) /+;R/SC;yy+NT = 6 /+;R/;*/ : (( e )->orientation2) /*;
->orientation2) /+;R/SC;yy+NT = 6 /+;R/;*/ = 1 /*;->orientation2) /+;
R/SC;yy+NT = 6 /+;R/;*/ ; break;  } } static int gs_ide1532 ;
#ifdef ANSI_C
static void gs_ide1524 (void)
#else
static void gs_ide1524 ()
#endif
{ int i; GNLIST k; ; gs_ide1532 = 0; for (i=maxdepth+1; i>=0; i--) if ((( layer[i] ).succlist) /*;
4 ();*/ ) break; k = (( layer[i] ).succlist) /*;{;*/ ; while (k) { if ((( (( k )->node) /*;
k;;*/ )->yloc) /*;k;;*/ +(( (( k )->node) /*;k;;*/ )->height) /*;k;;
*/ >gs_ide1532 ) gs_ide1532 = (( (( k )->node) /*;;;*/ )->yloc) /*;;
;*/ +(( (( k )->node) /*;;;*/ )->height) /*;;;*/ ; k = (( k )->next) /*;
532 = 0;;*/ ; } gs_ide1532 = gs_ide1532 + G_ybase;  gs_ide1522 (nodelist); /*;while (k) {
(( k )->node) /+;R/SC;yy+NT )->yloc) /+;*/ gs_ide1522 (labellist); gs_ide1522 (dummylist); }
#define backward_connection1(c) (((( c )->edge)  )&& ((( (( c )->edge)   )->end)   ==v))
#define backward_connection2(c) (((( c )->edge2)  )&&((( (( c )->edge2)   )->end)  ==v))
#ifdef ANSI_C
static void gs_ide1522 (GNODE v)
#else
static void gs_ide1522 (v) GNODE v; 
#endif
{  CONNECT c; ADJEDGE li; ; while (v) { (( v )->yloc) /*;/N;D+ v; ;*/ = gs_ide1532 - (( v )->yloc) /*;
/N;D+ v; ;*/ - (( v )->height) /*;/N;D+ v; ;*/ ; c = (( v )->connection) /*;
{ ;*/ ; if (c) { if (backward_connection1(c)) gs_ide1523 ((( c )->edge) /*;
ADJ+D/+ li;;*/ ); if (backward_connection2(c)) gs_ide1523 ((( c )->edge2) /*;
;;*/ ); } li = (( v )->pred) /*;/+;R/SC;yy+NT = gs_ide1532 - (( v )->yl;
*/ ; while (li) { gs_ide1523 ((( li )->kante) /*;if (c) {;*/ ); li = (( li )->next) /*;
kward_connection1(c)) gs_ide1523 ((( c ;*/ ; } v = (( v )->next) /*;
};*/ ; } }
#ifdef ANSI_C
static void gs_ide1523 (GEDGE e) 
#else
static void gs_ide1523 (e) GEDGE e; 
#endif
{ ; (( e )->syloc) /*;};*/ = gs_ide1532 - (( e )->syloc) /*;};*/ ; (( e )->bbyloc) /*;
void gs_ide1523 (/+D/+ e) ;*/ = gs_ide1532 - (( e )->bbyloc) /*;void gs_ide1523 (/+D/+ e) ;
*/ ; (( e )->btyloc) /*;_ide1523 (e);*/ = gs_ide1532 - (( e )->btyloc) /*;
_ide1523 (e);*/ ; (( e )->eyloc) /*;/+D/+ e; ;*/ = gs_ide1532 - (( e )->eyloc) /*;
/+D/+ e; ;*/ ; switch ((( e )->orientation) /*;{;*/ ) { case 0 /*;;;
*/ : break; case 1 /*;>syloc) /+;R/SC;yy+NT = gs_ide1532 - ((;*/ : (( e )->orientation) /*;
>syloc) /+;R/SC;yy+NT = gs_ide1532 - ((;*/ = 4 /*;>syloc) /+;R/SC;yy+NT = gs_ide1532 - ((;
*/ ; break; case 2 /*;) /+;R/SC;yy+NT = gs_ide1532 - (( e )->;*/ : (( e )->orientation) /*;
) /+;R/SC;yy+NT = gs_ide1532 - (( e )->;*/ = 5 /*;) /+;R/SC;yy+NT = gs_ide1532 - (( e )->;
*/ ; break; case 3 /*;SC;yy+NT = gs_ide1532 - (( e )->btyloc);*/ : (( e )->orientation) /*;
SC;yy+NT = gs_ide1532 - (( e )->btyloc);*/ = 6 /*;SC;yy+NT = gs_ide1532 - (( e )->btyloc);
*/ ; break; case 4 /*; = gs_ide1532 - (( e )->eyloc) /+;R/SC;;*/ : (( e )->orientation) /*;
= gs_ide1532 - (( e )->eyloc) /+;R/SC;;*/ = 1 /*; = gs_ide1532 - (( e )->eyloc) /+;
R/SC;;*/ ; break;  case 5 /*;C;yy+NT ) {;*/ : (( e )->orientation) /*;
C;yy+NT ) {;*/ = 2 /*;C;yy+NT ) {;*/ ; break; case 6 /*;se 0 /+;R/SC;
yy+NT : break;;*/ : (( e )->orientation) /*;se 0 /+;R/SC;yy+NT : break;
;*/ = 3 /*;se 0 /+;R/SC;yy+NT : break;;*/ ; break; } switch ((( e )->orientation2) /*;
y+NT : (( e )->orientation) /+;R/SC;yy+;*/ ) { case 0 /*;(( e )->orientation) /+;
R/SC;yy+NT = 6 ;*/ : break; case 1 /*;>orientation) /+;R/SC;yy+NT = 1 /+;
R/SC;*/ : (( e )->orientation2) /*;>orientation) /+;R/SC;yy+NT = 1 /+;
R/SC;*/ = 4 /*;>orientation) /+;R/SC;yy+NT = 1 /+;R/SC;*/ ; break; case 2 /*;
ation) /+;R/SC;yy+NT = 2 /+;R/SC;yy+NT ;*/ : (( e )->orientation2) /*;
ation) /+;R/SC;yy+NT = 2 /+;R/SC;yy+NT ;*/ = 5 /*;ation) /+;R/SC;yy+NT = 2 /+;
R/SC;yy+NT ;*/ ; break; case 3 /*; 6 /+;R/SC;yy+NT : (( e )->orientation);
*/ : (( e )->orientation2) /*; 6 /+;R/SC;yy+NT : (( e )->orientation);
*/ = 6 /*; 6 /+;R/SC;yy+NT : (( e )->orientation);*/ ; break; case 4 /*;
};*/ : (( e )->orientation2) /*;};*/ = 1 /*;};*/ ; break;  case 5 /*;
((( e )->orientation2) /+;R/SC;yy+NT ) ;*/ : (( e )->orientation2) /*;
((( e )->orientation2) /+;R/SC;yy+NT ) ;*/ = 2 /*;((( e )->orientation2) /+;
R/SC;yy+NT ) ;*/ ; break; case 6 /*;;yy+NT : break;;*/ : (( e )->orientation2) /*;
;yy+NT : break;;*/ = 3 /*;;yy+NT : break;;*/ ; break; } } int maximal_xpos; /*;ntation2) /+;R/SC;yy+NT = 6 /+;R/SC;yy+
se 4 /+;R/SC;yy+NT : (( e )->orientatio;*/ int maximal_ypos;
#ifdef ANSI_C
void calc_max_xy_pos(void)
#else
void calc_max_xy_pos()
#endif
{ GNODE v; ; maximal_xpos = 0; maximal_ypos = 0; v = nodelist; while (v) { /*;{
;;*/ if ((( v )->xloc) /*;;;*/ +(( v )->width) /*;;;*/ >maximal_xpos) maximal_xpos = (( v )->xloc) /*;
;;*/ +(( v )->width) /*;;;*/ ; if ((( v )->yloc) /*;_xpos = 0;;*/ +(( v )->height) /*;
_xpos = 0;;*/ >maximal_ypos) maximal_ypos = (( v )->yloc) /*; 0;;*/ +(( v )->height) /*;
0;;*/ ; v = (( v )->next) /*;v = nodelist;;*/ ; } v = labellist; while (v) { /*;->xloc) /+;R/SC;yy+NT +(( v )->width) /
+NT +(( v )->height) /+;R/SC;yy+NT >max;*/ if ((( v )->xloc) /*;+NT +(( v )->height) /+;R/SC;yy+NT >max;*/ +(( v )->width) /*;
+NT +(( v )->height) /+;R/SC;yy+NT >max;*/ >maximal_xpos) maximal_xpos = (( v )->xloc) /*;
C;yy+NT +(( v )->height) /+;R/SC;yy+NT ;*/ +(( v )->width) /*;C;yy+NT +(( v )->height) /+;
R/SC;yy+NT ;*/ ; if ((( v )->yloc) /*;= (( v )->next) /+;R/SC;yy+NT ;
;*/ +(( v )->height) /*;= (( v )->next) /+;R/SC;yy+NT ;;*/ >maximal_ypos) /*;= (( v )->next) /+;R/SC;yy+NT ;
};*/ maximal_ypos = (( v )->yloc) /*;};*/ +(( v )->height) /*;};*/ ; v = (( v )->next) /*;
ellist;;*/ ; } v = dummylist; while (v) { if ((( v )->xloc) /*;R/SC;
yy+NT +(( v )->height) /+;R/SC;yy+;*/ +(( v )->width) /*;R/SC;yy+NT +(( v )->height) /+;
R/SC;yy+;*/ >maximal_xpos) maximal_xpos = (( v )->xloc) /*; /+;R/SC;
yy+NT +(( v )->height) /+;R/SC;*/ +(( v )->width) /*; /+;R/SC;yy+NT +(( v )->height) /+;
R/SC;*/ ; if ((( v )->yloc) /*;v = (( v )->next) /+;R/SC;yy+NT ;;*/ +(( v )->height) /*;
v = (( v )->next) /+;R/SC;yy+NT ;;*/ >maximal_ypos) maximal_ypos = (( v )->yloc) /*;
};*/ +(( v )->height) /*;};*/ ; v = (( v )->next) /*;mylist;;*/ ; } maximal_xpos += G_xbase; /*;v )->xloc) /+;R/SC;yy+NT +(( v )->width
(( v )->xloc) /+;R/SC;yy+NT +(( v )->w;*/ maximal_ypos += G_ybase; ; } int st_nr_vis_nodes; int st_nr_vis_edges; /*;_xpos += /_xbase;
= /_ybase;;*/  int st_nr_vis_nearedges; int st_nr_vis_dummies; int st_nr_vis_labels; /*;}
nr_vis_nodes;;*/  int st_nr_invis_graphs; int st_nr_invis_nodes; int st_nr_invis_edges; /*;es;
int st_nr_vis_dummies;;*/  int st_max_indeg; int st_max_outdeg; int st_max_degree;
#define backward_connection1(c) (((( c )->edge)  )&& ((( (( c )->edge)   )->end)   ==v))
#define backward_connection2(c) (((( c )->edge2)  )&&((( (( c )->edge2)   )->end)  ==v))
#ifdef ANSI_C
void statistics(void)
#else
void statistics()
#endif
{ GNODE v; GEDGE e; ADJEDGE li; CONNECT c; int maxdegree; int maxindeg; /*;{
;;*/ int maxoutdeg; ; st_nr_vis_nodes = 0; st_nr_vis_edges = 0; st_nr_vis_nearedges = 0; /*;degree;
int maxindeg;;*/ st_nr_vis_dummies = 0; st_nr_vis_labels = 0; st_nr_invis_graphs = 0; /*;is_nodes = 0;
s = 0;;*/  st_nr_invis_nodes = 0; st_nr_invis_edges = 0; st_max_indeg = 0; st_max_outdeg = 0; /*;st_nr_vis_dummies = 0;
is_labels = 0;;*/ st_max_degree = 0; v = nodelist; while (v) { c = (( v )->connection) /*;
st_nr_invis_edges = 0;;*/ ; if (c) { if (backward_connection1(c)) st_nr_vis_nearedges++; /*;= 0;
st_max_degree = 0;;*/   if (backward_connection2(c)) st_nr_vis_nearedges++;  } maxdegree = maxindeg = maxoutdeg = 0; /*;while (v) {
v )->connection) /+;R/SC;yy+NT ;;*/ li = (( v )->succ) /*;v )->connection) /+;R/SC;yy+NT ;;*/ ; while (li) { /*;if (c) {
kward_connection1(c)) st_nr_vis_nearedg;*/ maxdegree++; maxoutdeg++; li = (( li )->next) /*;};*/ ; } li = (( v )->pred) /*;
ucc) /+;R/SC;yy+NT ;;*/ ; while (li) { st_nr_vis_edges++;  maxdegree++; /*;maxoutdeg++;
li )->next) /+;R/SC;yy+NT ;;*/ maxindeg++; li = (( li )->next) /*;};*/ ; } if (maxdegree>st_max_degree) st_max_degree=maxdegree; /*;while (li) {
is_edges++; ;*/ if (maxindeg >st_max_indeg) st_max_indeg =maxindeg; if (maxoutdeg>st_max_outdeg) st_max_outdeg=maxoutdeg; /*;maxdegree++;
g++;;*/ st_nr_vis_nodes++; v = (( v )->next) /*;next) /+;R/SC;yy+NT ;;*/ ; } /*;degree>st_max_degree) st_max_degree=max
st_max_indeg) st_max_indeg =maxindeg;;*/  v = labellist; while (v) { c = (( v )->connection) /*;outdeg) st_max_outdeg=maxoutdeg;
;*/ ; if (c) { if (backward_connection1(c)) st_nr_vis_nearedges++;  if (backward_connection2(c)) st_nr_vis_nearedges++; /*;}
ellist;;*/   } maxdegree = maxindeg = maxoutdeg = 0; li = (( v )->succ) /*;v )->connection) /+;
R/SC;yy+NT ;;*/ ; while (li) { maxdegree++; maxoutdeg++; li = (( li )->next) /*;
};*/ ; } li = (( v )->pred) /*;ucc) /+;R/SC;yy+NT ;;*/ ; while (li) { /*;ee++;
maxoutdeg++;;*/  st_nr_vis_edges++;  maxdegree++; maxindeg++; li = (( li )->next) /*;
};*/ ; } if (maxdegree>st_max_degree) st_max_degree=maxdegree; if (maxindeg >st_max_indeg) st_max_indeg =maxindeg; /*;is_edges++; 
maxdegree++;;*/ if (maxoutdeg>st_max_outdeg) st_max_outdeg=maxoutdeg; st_nr_vis_labels++; /*;g++;
next) /+;R/SC;yy+NT ;;*/ v = (( v )->next) /*;next) /+;R/SC;yy+NT ;;*/ ; } v = dummylist; while (v) { /*;st_max_indeg) st_max_indeg =maxindeg;
outdeg) st_max_outdeg=maxoutdeg;;*/ c = (( v )->connection) /*;outdeg) st_max_outdeg=maxoutdeg;;*/ ; if (c) { /*;st_nr_vis_labels++;
v )->next) /+;R/SC;yy+NT ;;*/ if (backward_connection1(c)) st_nr_vis_nearedges++;  if (backward_connection2(c)) st_nr_vis_nearedges++; /*;}
mylist;;*/   } maxdegree = maxindeg = maxoutdeg = 0; li = (( v )->succ) /*;v )->connection) /+;
R/SC;yy+NT ;;*/ ; while (li) { maxdegree++; maxoutdeg++; li = (( li )->next) /*;
};*/ ; } li = (( v )->pred) /*;ucc) /+;R/SC;yy+NT ;;*/ ; while (li) { /*;ee++;
maxoutdeg++;;*/  st_nr_vis_edges++;  maxdegree++; maxindeg++; li = (( li )->next) /*;
};*/ ; } if (maxdegree>st_max_degree) st_max_degree=maxdegree; if (maxindeg >st_max_indeg) st_max_indeg =maxindeg; /*;is_edges++; 
maxdegree++;;*/ if (maxoutdeg>st_max_outdeg) st_max_outdeg=maxoutdeg; st_nr_vis_dummies++; /*;g++;
next) /+;R/SC;yy+NT ;;*/ v = (( v )->next) /*;next) /+;R/SC;yy+NT ;;*/ ; } v = invis_nodes; while (v) { /*;st_max_indeg) st_max_indeg =maxindeg;
outdeg) st_max_outdeg=maxoutdeg;;*/ st_nr_invis_nodes++; v = (( v )->next) /*;st_nr_vis_dummies++;;*/ ; } /*;}
is_nodes;;*/  v = graphlist; while (v) { st_nr_invis_graphs++; v = (( v )->next) /*;
nvis_nodes++;;*/ ; } e = edgelist;  while (e) { if ((( e )->invisible) /*;
while (v) {;*/ ) st_nr_invis_edges++; e = (( e )->next) /*;nvis_graphs++;
;*/ ; } }
