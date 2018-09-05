/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*								      */
/*		VCG : Visualization of Compiler Graphs		      */ 
/*		--------------------------------------		      */ 
/*								      */
/*   file:	   PSDevstr.c   				      */
/*   version:	   1.00.00					      */
/*   creation:	   31.1.95					      */
/*   author:	   G. Sander (Version 1.00.00-...)		      */ 
/*		   Universitaet des Saarlandes, 66041 Saarbruecken    */
/*		   ESPRIT Project #5399 Compare 		      */ 
/*   description:  PostScript Device: Print bitmap into a file in     */
/*		   PostScript format, String Character Routines       */
/*   status:	   in work					      */
/*								      */
/*--------------------------------------------------------------------*/


#ifndef lint
static char *id_string="$Id: PSdevstr.c,v 1.1 1995/02/08 11:11:14 sander Exp $";
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
 * $Log: PSdevstr.c,v $
 * Revision 1.1  1995/02/08  11:11:14  sander
 * Initial revision
 *
 */

/************************************************************************
 *  This file allows to write the graph into a PostScript file. These 
 *  routines are called, if the "export"-menu was selected. 
 *  This is the string character library and is compatible to drawstr.c.
 ************************************************************************/


/* Mapping of global names of draw.c, drawstr.c, drawlib.c
 * =======================================================
 */

#define INCLUDE_DRAW
#define POSTSCRIPT_DEVICE

#define draw_main      ps_draw_main
#define draw_one_node  ps_draw_one_node
#define gs_stringw     ps_stringw
#define gs_stringh     ps_stringh
#define gs_boxw        ps_boxw
#define gs_boxh        ps_boxh

#define gs_printstr          ps_printstr         
#define gs_calcstringsize    ps_calcstringsize  
#define gs_setto             ps_setto          
#define gs_setshrink         ps_setshrink        
#define gs_calctextboxsize   ps_calctextboxsize 
#define gs_anchornode        ps_anchornode        
#define gs_textbox           ps_textbox        
#define gs_reverttextbox     ps_reverttextbox 
#define gs_halfreverttextbox ps_halfreverttextbox  
#define gs_stringbox         ps_stringbox         
#define gs_calcrhombsize     ps_calcrhombsize 
#define gs_rhomb             ps_rhomb        
#define gs_revertrhomb       ps_revertrhomb 
#define gs_halfrevertrhomb   ps_halfrevertrhomb  
#define gs_calctrianglesize  ps_calctrianglesize 
#define gs_triangle          ps_triangle        
#define gs_reverttriangle    ps_reverttriangle 
#define gs_halfreverttriangle ps_halfreverttriangle  
#define gs_calcellipsesize   ps_calcellipsesize 
#define gs_ellipse           ps_ellipse        
#define gs_revertellipse     ps_revertellipse 
#define gs_halfrevertellipse ps_halfrevertellipse  
#define gs_solidarrow        ps_solidarrow       
#define gs_dashedarrow       ps_dashedarrow     
#define gs_dottedarrow       ps_dottedarrow    
#define gs_line              ps_line
#define gs_rectangle         ps_rectangle
#define gs_actbackground     ps_actbackground

#define mystretch            ps_mystretch
#define myshrink             ps_myshrink
#define myxpos               ps_myxpos
#define myypos               ps_myypos
#define gs_stlimit           ps_stlimit
#define gs_shlimit           ps_shlimit


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
#include <math.h>
#include "globals.h"

void    ps_line      _PP((int fx,int fy,int tx,int ty,int c));
void    ps_thickline _PP((int fx,int fy,int tx,int ty,int t,int c));


#include "drawstr.c"
#include "PSdev.h"


/*--------------------------------------------------------------------*/

