/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*                                                                    */
/*              VCG : Visualization of Compiler Graphs                */
/*              --------------------------------------                */
/*                                                                    */
/*   file:         X11devpb.h                                         */
/*   version:      1.00.00                                            */
/*   creation:     9.4.93                                             */
/*   author:       I. Lemke  (...-Version 0.99.99)                    */
/*                 G. Sander (Version 1.00.00-...)                    */
/*                 Universitaet des Saarlandes, 66041 Saarbruecken    */
/*                 ESPRIT Project #5399 Compare                       */
/*   description:  Device driver for X11, Export Dialog Box           */
/*   status:       in work                                            */
/*                                                                    */
/*--------------------------------------------------------------------*/

/* $Id: X11devpb.h,v 1.5 1995/02/08 11:11:14 sander Exp $ */

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
 * $Log: X11devpb.h,v $
 * Revision 1.5  1995/02/08  11:11:14  sander
 * Distribution version 1.3.
 *
 * Revision 1.4  1994/12/23  18:12:45  sander
 * Manhatten layout added.
 * Option interface cleared.
 * infobox behaviour improved.
 * First version of fisheye (carthesian).
 * Options Noedge and nonode.
 * Titles in the node title box are now sorted.
 * Timelimit functionality improved.
 *
 * Revision 1.3  1994/11/25  15:43:29  sander
 * Printer interface added to allow to use VCG as a converter.
 *
 * Revision 1.2  1994/05/05  08:20:30  sander
 * Small corrections.
 *
 * Revision 1.1  1994/04/27  16:05:19  sander
 * Initial revision
 *
 */

#ifndef X11DEVPB_H
#define X11DEVPB_H


/*--------------------------------------------------------------------*/

/* See X11devpb.c for explanation
 * ------------------------------
 */

extern int   act_output_type;
extern int   act_paper_type;
extern int   act_color_type;
extern int   act_ori_type;
extern int   act_paper_num;
extern float act_width;
extern float act_height;
extern float act_left_margin;
extern float act_right_margin;
extern float act_top_margin;
extern float act_bottom_margin;
extern int   act_xdpi;
extern int   act_ydpi;
extern float act_scaling;
extern int   act_bbox;

#ifdef X11

void 	x11_init_dialog		_PP((Display *rd, int rs));
void	x11_destroy_dialog	_PP((Display *rd, int rs));
void    x11_print_dialog        _PP((int rminx,int rminy,int rmaxx,int rmaxy));

#endif /* X11 */

void 	set_of_region    _PP((int a, int b, int c, int d));
void 	set_of_xdpi	 _PP((int val));
void 	set_of_ydpi	 _PP((int val));
void    set_of_scaling   _PP((float v));
void    set_of_width     _PP((float v));
void    set_of_height    _PP((float v));
void    fit_of_heightwidth  _PP((float h, float w));
void 	set_of_maxspect     _PP((void));
void 	set_of_centerx      _PP((void));
void 	set_of_centery      _PP((void));
void 	set_of_leftmargin   _PP((float f));
void 	set_of_rightmargin  _PP((float f));
void 	set_of_bottommargin _PP((float f));
void 	set_of_topmargin    _PP((float f));

/*--------------------------------------------------------------------*/

#endif /* X11DEVPB_H */


