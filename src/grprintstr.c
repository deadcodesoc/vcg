/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */ 
/*		--------------------------------------		      */ 
/*								      */
/*   file:	   grprintstr.c					      */
/*   version:	   1.00.00					      */
/*   creation:	   31.1.95					      */
/*   author:	   G. Sander (Version 1.00.00-...)		      */ 
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */ 
/*   description:  Print bitmap into a file, String Character Rout.   */
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/


#ifndef lint
static char *id_string="$Id: grprintstr.c,v 1.1 1995/02/08 11:11:14 sander Exp $";
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
 * $Log: grprintstr.c,v $
 * Revision 1.1  1995/02/08  11:11:14  sander
 * Initial revision
 *
 */

/************************************************************************
 *  This file allows to write the graph bitmap into a file. These routines
 *  are called, if the "export"-menu was selected. The supported formats
 *  are pbm-P4 format and ppm-P6 format.
 *  This is the string character library and is compatible to drawstr.c.
 ************************************************************************/


/* Mapping of global names of draw.c, drawstr.c, and drawlib.c
 * ===========================================================
 */

#define INCLUDE_DRAW

#define draw_main      bm_draw_main
#define draw_one_node  bm_draw_one_node
#define gs_stringw     bm_stringw
#define gs_stringh     bm_stringh
#define gs_boxw        bm_boxw
#define gs_boxh        bm_boxh

#define gs_printstr          bm_printstr         
#define gs_calcstringsize    bm_calcstringsize  
#define gs_setto             bm_setto          
#define gs_setshrink         bm_setshrink        
#define gs_calctextboxsize   bm_calctextboxsize 
#define gs_anchornode        bm_anchornode        
#define gs_textbox           bm_textbox        
#define gs_reverttextbox     bm_reverttextbox 
#define gs_halfreverttextbox bm_halfreverttextbox  
#define gs_stringbox         bm_stringbox         
#define gs_calcrhombsize     bm_calcrhombsize
#define gs_rhomb             bm_rhomb       
#define gs_revertrhomb       bm_revertrhomb
#define gs_halfrevertrhomb   bm_halfrevertrhomb
#define gs_calctrianglesize  bm_calctrianglesize
#define gs_triangle          bm_triangle       
#define gs_reverttriangle    bm_reverttriangle
#define gs_halfreverttriangle bm_halfreverttriangle
#define gs_calcellipsesize   bm_calcellipsesize
#define gs_ellipse           bm_ellipse       
#define gs_revertellipse     bm_revertellipse
#define gs_halfrevertellipse bm_halfrevertellipse
#define gs_solidarrow        bm_solidarrow       
#define gs_dashedarrow       bm_dashedarrow     
#define gs_dottedarrow       bm_dottedarrow    
#define gs_line              bm_line
#define gs_rectangle         bm_rectangle
#define gs_actbackground     bm_actbackground

#define mystretch            bm_mystretch
#define myshrink             bm_myshrink
#define myxpos               bm_myxpos
#define myypos               bm_myypos
#define gs_stlimit           bm_stlimit
#define gs_shlimit           bm_shlimit


/* Includes, Prototypes, Variables
 * ===============================
 * We must include globals.h before everything, otherwise we cannot
 * define the prototypes.
 * Even if globals.h is included in draw.c and drawlib.c again, this
 * is correct, because of the include-security mechanism, that prevents
 * second inclusion of a file from having ugly effects.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include "globals.h"

void    bm_line      _PP((int fx,int fy,int tx,int ty,int c));

#include "drawstr.c"
#include "grprint.h"

/*--------------------------------------------------------------------*/

