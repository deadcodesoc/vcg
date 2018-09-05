/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*                                                                    */
/*              VCG : Visualization of Compiler Graphs                */
/*              --------------------------------------                */
/*                                                                    */
/*   file:         pbmrot90.c                                         */
/*   version:      1.00.00                                            */
/*   creation:     15.11.93                                           */
/*   author:       G. Sander (Version 1.00.00-...)                    */  
/*                 Universitaet des Saarlandes, 66041 Saarbruecken    */
/*                 ESPRIT Project #5399 Compare                       */
/*   description:  Rotate a pbm-file by 90 degree                     */
/*   status:       in work                                            */
/*                                                                    */
/*--------------------------------------------------------------------*/

/* $Id: pbmrot90.c,v 1.6 1995/02/08 18:48:50 sander Exp $ */

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


/* $Log: pbmrot90.c,v $
 * Revision 1.6  1995/02/08  18:48:50  sander
 * setbit renamed into mysetbit.
 *
 * Revision 1.5  1995/02/08  11:21:41  sander
 * Distribution Version 1.3
 *
 * Revision 1.4  1994/03/02  14:29:05  sander
 * Gnu License message added.
 *
 * Revision 1.3  1994/01/21  20:05:00  sander
 * Signal handling adapted for Sys V.
 * Some portability problems solved for Silicon Graphics IRIS and IBM R6000.
 *
 * Revision 1.2  1994/01/03  17:43:24  sander
 * Remarks added.
 *
 * Revision 1.1  1993/12/06  11:23:59  sander
 * Initial revision
 *
 */


/*--------------------------------------------------------------------*
 * There are excellent standard utilities for pbm-Files by Jef Poskanzer.
 * The reason I wrote this rotation utility is that this is much faster
 * on large files.
 *
 * This utility rotates a pbm-P4-file by 90 degree and produces a new
 * pbm-P4-file. Synopsis:       pbmrot90 <infile> <outfile>
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
void writepbm		_PP((void));
void rotatepbm		_PP((void));
void mysetbit		_PP((int x,int y,int color));

/* Global Variables
 * ----------------
 */

FILE *f = NULL;
char *infile;
char *outfile;

unsigned char *bitmap1=NULL;
unsigned char *bitmap2=NULL;

int width1, height1;
int width2, height2;

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

	if (argc != 3) {
		PRINTF("Usage: pbmrot90 <infile> <outfile>\n");
		return(-1);
	}

	infile = argv[1];
	outfile = argv[2];

	PRINTF("Rotate %s -> %s\n",infile,outfile);
	readpbm();
	rotatepbm();
	writepbm();
	
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

	/* Allocate bitmap 2, where the rotated image comes in */
	width2 = ((height1+7)/8)*8;
	height2 = width1; 
	bitmap2 = (unsigned char *)malloc(width2/8*(height2+1));
	if (!bitmap2) fatalerror("Memory exhausted","");

	for (i=0; i<height1; i++) fread(&(bitmap1[i*width1/8]),1,width1/8,f);
	if (f) FCLOSE(f);
}

/*--------------------------------------------------------------------*/
/*   Write a pbm-file                                                 */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
void writepbm(void)
#else
void writepbm()
#endif
{
	int i;

	f = fopen(outfile,"w");
	if (!f) fatalerror("Cannot open",outfile);

	FPRINTF(f,"P4\n");
        FPRINTF(f,"%d %d\n",width2,height2);
	for (i=0; i<height2; i++) fwrite(&(bitmap2[i*width2/8]),1,width2/8,f);
	if (f) FCLOSE(f);
}

/*--------------------------------------------------------------------*/
/*   Rotate bitmap1 -> bitmap2                                        */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
void rotatepbm(void)
#else
void rotatepbm()
#endif
{
	int i,j;
	unsigned char mbyte;
	for (i=0; i<height2; i++) 
		for (j=0; j<width2/8; j++) bitmap2[i*width2/8+j]=0;

	for (i=0; i<height1; i++) {
		for (j=0; j<width1/8; j++) {
			mbyte = bitmap1[i*width1/8+j];
			mysetbit(height1-1-i,j*8,  0x80&mbyte);
			mysetbit(height1-1-i,j*8+1,0x40&mbyte);
			mysetbit(height1-1-i,j*8+2,0x20&mbyte);
			mysetbit(height1-1-i,j*8+3,0x10&mbyte);
			mysetbit(height1-1-i,j*8+4,0x08&mbyte);
			mysetbit(height1-1-i,j*8+5,0x04&mbyte);
			mysetbit(height1-1-i,j*8+6,0x02&mbyte);
			mysetbit(height1-1-i,j*8+7,0x01&mbyte);
		}
	}	
}


/* Set a bit in bitmap2. Color!=0  means black, color=0 means white. 
 */

#ifdef ANSI_C
void mysetbit(int x, int y, int color)
#else
void mysetbit(x,y,color)
int x;
int y;
int color;
#endif
{
	unsigned char mask,*cc;

        cc = bitmap2+y*(width2/8)+x/8;
        switch (x%8) {
        case 0: mask = 0x80; break;
        case 1: mask = 0x40; break;
        case 2: mask = 0x20; break;
        case 3: mask = 0x10; break;
        case 4: mask = 0x08; break;
        case 5: mask = 0x04; break;
        case 6: mask = 0x02; break;
        case 7: mask = 0x01; break;
        }

        if (color==0) {
                mask = ~mask;
                *cc = (*cc) & mask;
        }
        else {
                *cc = (*cc) | mask;
        }
}

