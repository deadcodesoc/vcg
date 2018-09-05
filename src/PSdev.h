/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*                                                                    */
/*              VCG : Visualization of Compiler Graphs                */
/*              --------------------------------------                */
/*                                                                    */
/*   file:         PSDev.h                                            */
/*   version:      1.00.00                                            */
/*   creation:     14.4.93                                            */
/*   author:       G. Sander (Version 1.00.00-...)                    */
/*                 Universitaet des Saarlandes, 66041 Saarbruecken    */
/*                 ESPRIT Project #5399 Compare                       */
/*   description:  PostScript Device: Print bitmap into a file in     */
/*                 PostScript format                                  */
/*   status:       in work                                            */
/*                                                                    */
/*--------------------------------------------------------------------*/


/* $Id: PSdev.h,v 1.2 1995/02/08 11:11:14 sander Exp $ */

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
 * $Log: PSdev.h,v $
 * Revision 1.2  1995/02/08  11:11:14  sander
 * Distribution version 1.3.
 *
 * Revision 1.1  1994/04/27  16:05:19  sander
 * Initial revision
 *
 */

#ifndef PSDEV_H
#define PSDEV_H

/*--------------------------------------------------------------------*/

/* See PSdev.c for explanation
 * ---------------------------
 */


void print_all_ps _PP((char *fn,int a,int b,int c,int d));

/*--------------------------------------------------------------------*/

#endif /* PSDEV_H  */


