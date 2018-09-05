/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*                                                                    */
/*              VCG : Visualization of Compiler Graphs                */
/*              --------------------------------------                */
/*                                                                    */
/*   file:         vcgcount.c                                         */
/*   version:      1.00.00                                            */
/*   creation:     18.11.94                                           */
/*   author:       G. Sander (Version 1.00.00-...)                    */  
/*                 Universitaet des Saarlandes, 66041 Saarbruecken    */
/*                 ESPRIT Project #5399 Compare                       */
/*   description:  Count nodes and edges in a specification           */
/*   status:       in work                                            */
/*                                                                    */
/*--------------------------------------------------------------------*/

/* $Id: vcgcount.c,v 1.1 1995/02/08 11:21:41 sander Exp $ */

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


/* $Log: vcgcount.c,v $
 * Revision 1.1  1995/02/08  11:21:41  sander
 * Initial revision
 *
 */


/*--------------------------------------------------------------------*
 * This utility reads a VCG specification from stdin and prints the
 * number of nodes and edges. In fact, it does not really parse the
 * specification. Instead, it looks fo occurences of the substring
 * "node:" and "edge:".
 *--------------------------------------------------------------------*/

#include <stdio.h> 
#include <stdlib.h> 
#include "../src/globals.h"


/* Prototypes
 * ----------
 */

void main		_PP((void));



/* Global Variables
 * ----------------
 */

char line[1035];  /* The input line */

int nrnodes;      /* The number of nodes */
int nredges;      /* The number of edges */


/*--------------------------------------------------------------------*/

/* Main Routine
 * ------------
 */

#ifdef ANSI_C
void main(void)
#else
void main()
#endif
{
	register char *c;

	nrnodes = 0;
	nredges = 0;

	while (!feof(stdin)) {
		fgets(line,1023,stdin);
		if (feof(stdin)) break; 
		line[1023] = 0;
		c = line;
		while (*c) {
			if (  (c[0]=='n') 
			    &&(c[1]=='o') 
			    &&(c[2]=='d') 
			    &&(c[3]=='e')
			    &&(c[4]==':')) {
				nrnodes++;
			}
			if (  (c[0]=='e') 
			    &&(c[1]=='d') 
			    &&(c[2]=='g') 
			    &&(c[3]=='e')
			    &&(c[4]==':')) {
				nredges++;
			}
			c++;
		}
	}
	PRINTF("This graph contains %d nodes and %d edges.\n", 
		nrnodes, nredges);
}


