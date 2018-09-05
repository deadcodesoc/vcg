/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*                                                                    */
/*              VCG : Visualization of Compiler Graphs                */
/*              --------------------------------------                */
/*                                                                    */
/*   file:         pbm2hp.c                                           */
/*   version:      1.00.00                                            */
/*   creation:     15.11.93                                           */
/*   author:       G. Sander (Version 1.00.00-...)                    */  
/*                 Universitaet des Saarlandes, 66041 Saarbruecken    */
/*                 ESPRIT Project #5399 Compare                       */
/*   description:  Printer driver for HP-Laserjet printers            */
/*                 Convert a PBM-file into an HP Laserjet output      */
/*   status:       in work                                            */
/*                                                                    */
/*--------------------------------------------------------------------*/

/* $Id: pbm2hp.c,v 1.4 1995/02/08 11:21:41 sander Exp $ */

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


/* $Log: pbm2hp.c,v $
 * Revision 1.4  1995/02/08  11:21:41  sander
 * Distribution Version 1.3
 *
 * Revision 1.3  1994/03/02  14:29:05  sander
 * Gnu License message added.
 *
 * Revision 1.2  1994/01/21  20:05:00  sander
 * Signal handling adapted for Sys V.
 * Some portability problems solved for Silicon Graphics IRIS and IBM R6000.
 *
 * Revision 1.1  1994/01/06  14:54:20  sander
 * Initial revision
 *
 */


/*--------------------------------------------------------------------*
 * There are excellent standard utilities for pbm-Files by Jef Poskanzer.
 * The reason I wrote this shift utility is that this is much faster
 * on large files.
 *
 * This utility converts a pbm-P4-file into a 300dpi HP Laserjet output.
 * This output can be send to HP Laserjets directly. The output is send
 * to stdout !!!
 *
 * Synopsis:       pbm2hp <infile> 
 *
 * THIS UTILITY DOES NOT WORK WITH THE pbm-P1-format !!! IT IS NOT A
 * GENERAL CONVERSION UTILITY.
 *--------------------------------------------------------------------*/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "../src/globals.h"

/* Prototypes
 * ----------
 */

int  main		_PP((int argc, char *argv[]));
void readpbm		_PP((void));
void printpbm		_PP((void));

/* Global Variables
 * ----------------
 */

FILE *f = NULL;
char *infile;
char *outfile;

unsigned char *bitmap1=NULL;

int width1, height1;

#define fatalerror(a,b) { PRINTF("Error: %s %s !\n",a,b); exit(-1); }

/*--------------------------------------------------------------------*/

#ifdef ANSI_C
int main(int argc, char *argv[])
#else
int main(argc, argv)
int argc;
char    *argv[];
#endif
{

	if (argc != 2) {
		PRINTF("Usage: pbm2hp <infile> \n");
		return(-1);
	}

	infile = argv[1];

	readpbm();
	printpbm();
	
	return(0);
}

/*--------------------------------------------------------------------*/
/*   Read a pbm-file                                                  */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
void readpbm(void)
#else
void readpbm()
#endif
{
	int val,i;

	f = fopen(infile,"r");
	if (!f) fatalerror("Cannot open",infile);

	if (fscanf(f,"P%d",&val)!=1) fatalerror("Format wrong","");	
	if (val!=4)		     fatalerror("Format not P4","");

	if (fscanf(f,"%d %d",&width1,&height1)!=2) 
				     fatalerror("Format wrong","");	
	if (width1%8) 		     fatalerror("Format wrong","");

	/* Allocate bitmap 1 */
	bitmap1 = (unsigned char *)malloc(width1/8*(height1+1));
	if (!bitmap1) fatalerror("Memory exhausted","");

	for (i=0; i<height1; i++) fread(&(bitmap1[i*width1/8]),1,width1/8,f);
	if (f) FCLOSE(f);
}

/*--------------------------------------------------------------------*/
/*   Print a pbm-file, i.e. convert into HP Laser format              */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
void printpbm(void)
#else
void printpbm()
#endif
{
	int i;

	f = stdout;

	FPRINTF(f,"%cE",27);
	FPRINTF(f,"%c*t300R",27);
	FPRINTF(f,"%c&l1X",27);
	FPRINTF(f,"%c*r1A",27);
	for (i=0; i<height1; i++) {
		FPRINTF(f,"%c*b%dW",27,width1/8);
		fwrite(&(bitmap1[i*width1/8]),1,width1/8,f);
	}
	FPRINTF(f,"%c*rB",27);
	FPRINTF(f,"%c",12);
	FFLUSH(f);
}

/*--------------------------------------------------------------------*/

