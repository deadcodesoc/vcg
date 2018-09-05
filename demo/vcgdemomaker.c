/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*                                                                    */
/*              VCG : Visualization of Compiler Graphs                */
/*              --------------------------------------                */
/*                                                                    */
/*   file:         vcgdemomaker.c                                     */
/*   version:      1.00.00                                            */
/*   creation:     12.11.93                                           */
/*   author:       G. Sander (Version 1.00.00-...)                    */  
/*                 Universitaet des Saarlandes, 66041 Saarbruecken    */
/*                 ESPRIT Project #5399 Compare                       */
/*   description:  Creates example VCG specifications                 */
/*   status:       in work                                            */
/*                                                                    */
/*--------------------------------------------------------------------*/

/* $Id: vcgdemomaker.c,v 1.2 1995/02/08 11:21:41 sander Exp $ */

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


/* $Log: vcgdemomaker.c,v $
 * Revision 1.2  1995/02/08  11:21:41  sander
 * Distribution Version 1.3
 *
 * Revision 1.1  1994/04/18  08:12:33  sander
 * Initial revision
 *
 *
 */


/*--------------------------------------------------------------------*
 * This tool generates regular example graphs for torture tests of VCG.
 *
 * Synopsis: vcgdemomaker <outfile> <mode> <size>
 *    Modes: -unarytree      Unary tree (a line).
 *    Modes: -binarytree     Binary tree.
 *    Modes: -ternarytree    Ternary tree.
 *    Modes: -leveltree      Level tree.
 *    Modes: -twolevelcross  Cross graph with two levels.
 *    Modes: -allconnect     Graphs where all pairs of node form an edge.
 *    Modes: -randomgraph    4-ary random graph (Version 1).
 *    Modes: -netgraph       4-ary regular network graph (Version 1).
 *    Modes: -random2graph   4-ary random graph (Version 2).
 *    Modes: -net2graph      4-ary regular network graph (Version 2).
 *    Size:  Depth of tree or number of nodes of graph.
 *
 *--------------------------------------------------------------------*/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "../src/globals.h"

/* Prototypes
 * ----------
 */

int  main			 _PP((int argc, char *argv[]));
int  create_node		 _PP((void));
void create_edge		 _PP((int x,int y));
void create_all_graph 		 _PP((int n));
void create_twolevel_cross_graph _PP((int n));
void create_ary_tree		 _PP((int a,int n));
int  create_ary		 	 _PP((int a,int x, int n));
void create_level_tree		 _PP((int a1,int a2,int a3,int n));
int create_level		 _PP((int a1,int a2,int a3,int x,int n));
void create_4ary_randomgraph	 _PP((int n));
void create_4ary_netgraph	 _PP((int n));
void create_4ary_random2graph	 _PP((int n));
void create_4ary_net2graph	 _PP((int n));
void create_nornode		 _PP((int m));
void create_netnode		 _PP((int m));
void create_levedge		 _PP((int x,int y));
void initbuf			 _PP((void));


/* Global Variables
 * ----------------
 */

FILE *f = NULL;

/* See the options: 
 */

char *outfile;
char *mode;
int   size;

#define fatalerror(a,b) { PRINTF("Error: %s %s !\n",a,b); exit(-1); }

/*--------------------------------------------------------------------*/

/* Main routine
 * ------------
 * Option handling and call of the corresponding driver function.
 */

#ifdef ANSI_C
int main(int argc, char *argv[])
#else
int main(argc, argv)
int argc;
char    *argv[];
#endif
{

	if (argc != 4) {
		PRINTF("Usage: vcgdemomaker <outfile> <mode> <size>\n");
		PRINTF("Modes: -unarytree      Unary tree (a line).\n");
		PRINTF("Modes: -binarytree     Binary tree.\n");
		PRINTF("Modes: -ternarytree    Ternary tree.\n");
		PRINTF("Modes: -leveltree      Level tree.\n");
		PRINTF("Modes: -twolevelcross  Cross graph with two levels.\n");
		PRINTF("Modes: -allconnect     Graphs where all pairs of node form an edge.\n");
		PRINTF("Modes: -randomgraph    4-ary random graph (Version 1).\n");
		PRINTF("Modes: -netgraph       4-ary regular network graph (Version 1).\n");
		PRINTF("Modes: -random2graph   4-ary random graph (Version 2).\n");
		PRINTF("Modes: -net2graph      4-ary regular network graph (Version 2).\n");
		PRINTF("Size: Depth of tree or number of nodes of graph.\n");
		return(-1);
	}

	outfile = argv[1];
	mode    = argv[2];
	size    = atoi(argv[3]);
	if (size<1) size=1;

	if (outfile[0]=='-') fatalerror("Illegal filename",outfile);
	f = fopen(outfile,"r");
	if (f) {
		fclose(f);
		fatalerror(outfile," does already exist");
	}
	f = fopen(outfile,"w");	
	if (!f) fatalerror("Cannot open",outfile);

	if (strcmp(mode,"-unarytree")==0)
		create_ary_tree(1,size);
	else if (strcmp(mode,"-binarytree")==0)
		create_ary_tree(2,size);
	else if (strcmp(mode,"-ternarytree")==0)
		create_ary_tree(3,size);
	else if (strcmp(mode,"-leveltree")==0)
		create_level_tree(2,2,2,size);
	else if (strcmp(mode,"-twolevelcross")==0)
		create_twolevel_cross_graph(size);
	else if (strcmp(mode,"-allconnect")==0)
		create_all_graph(size);
	else if (strcmp(mode,"-randomgraph")==0)
		create_4ary_randomgraph(size);
	else if (strcmp(mode,"-netgraph")==0)
		create_4ary_netgraph(size);
	else if (strcmp(mode,"-random2graph")==0)
		create_4ary_random2graph(size);
	else if (strcmp(mode,"-net2graph")==0)
		create_4ary_net2graph(size);
	else { 	PRINTF("Usage: vcgdemomaker <outfile> <mode> <size>\n");
		PRINTF("Type: vcgdemomaker -h for more ...\n");
	} 

	if (f) fclose(f);
	return(0);
}


/*--------------------------------------------------------------------*/
/*   Primitives to create graphs                                      */
/*--------------------------------------------------------------------*/

int edge_class = 2; 	/* Edge class we normally use */
int act_node_nr = 0;	/* Counter for nodes          */


/*  Create a node
 *  -------------
 *  The label and title will be the actual node number which is also returned.
 */

#ifdef ANSI_C
int create_node(void)
#else
int create_node()
#endif
{
       	FPRINTF(f,"node: { title: \"%d\" label: \"%d\" }\n", 
		act_node_nr, act_node_nr); 
	act_node_nr++;	
	return(act_node_nr-1);
}


/*  Create an edge
 *  --------------
 *  from node titled x to node titled y.
 */

#ifdef ANSI_C
void create_edge(int x,int y)
#else
void create_edge(x,y)
int x;
int y;
#endif
{
       	FPRINTF(f,"edge: { sourcename: \"%d\" targetname: \"%d\" ", 
		x, y); 
       	FPRINTF(f,"class: %d }\n",edge_class); 
}


/*  Create a near edge
 *  ------------------
 *  from node titled x to node titled y.
 */

#ifdef ANSI_C
void create_nearedge(int x,int y)
#else
void create_nearedge(x,y)
int x;
int y;
#endif
{
       	FPRINTF(f,"nearedge: { sourcename: \"%d\" targetname: \"%d\" ", 
		x, y); 
       	FPRINTF(f,"class: %d }\n",edge_class); 
}


/*--------------------------------------------------------------------*/
/*   Graph routines                                                   */
/*--------------------------------------------------------------------*/

/* All-graph of size n:
 * ===================
 * all nodes are connected with all nodes, but we
 * avoid self loops and bidirected connections.
 */

#ifdef ANSI_C
void create_all_graph(int n)
#else
void create_all_graph(n)
int n;
#endif
{
	int i,j;

	PRINTF("Generate `allgraph' with %d nodes -> %s\n",n,outfile);

       	FPRINTF(f,"graph: { title:\"test\"\n"); 
       	FPRINTF(f,"layoutalgorithm: minbackward\n"); 
       	FPRINTF(f,"finetuning: no\n"); 
       	FPRINTF(f,"nearedges: no\n"); 
       	FPRINTF(f,"xmax: 700 ymax: 700 x: 30 y: 30 \n"); 
	for (i=0; i<n; i++) (void)create_node();
	for (i=0; i<n; i++) {
		for (j=n-1; j>i; j--) {
			create_edge(i,j);
		}
	}
       	FPRINTF(f,"}\n"); 
}


/* Cross-graph of size n:
 * =====================
 * The graph is bipartit. Each node has two edges.
 * Each 4 nodes are connected like this:
 *           A  B
 *           |\/|     We start with a maximal
 *           |/\|     number of crossings.
 *           D  D 
 */

#ifdef ANSI_C
void create_twolevel_cross_graph(int n)
#else
void create_twolevel_cross_graph(n)
int n;
#endif
{
	int i;

	PRINTF("Generate `twolevel_cross_graph' with %d nodes -> %s\n",
			n,outfile);

	if (n%2) n++;
       	FPRINTF(f,"graph: { title:\"test\"\n"); 
       	FPRINTF(f,"xmax: 700 ymax: 700 x: 30 y: 30 \n"); 
	for (i=0; i<n; i++) create_node();
	for (i=0; i<n/2; i++) {
		create_edge(i,n/2+i);
		create_edge(i,n-i-1);
	}
       	FPRINTF(f,"}\n"); 
}


/* k-ary tree of depth n
 * ======================
 * All nodes have one predecessor and two successors.
 *
 */

#ifdef ANSI_C
void create_ary_tree(int arity,int n)
#else
void create_ary_tree(arity,n)
int arity;
int n;
#endif
{
	PRINTF("Generate `%d-ary tree' with depth %d -> %s\n",
			arity,n,outfile);
       	FPRINTF(f,"graph: { title:\"test\"\n"); 
       	FPRINTF(f,"xmax: 700 ymax: 700 x: 30 y: 30 \n"); 
	FPRINTF(f,"layout_downfactor: 8\n");
	(void)create_ary(arity,0,n);
       	FPRINTF(f,"}\n"); 
}

/* Auxiliary: create nodes and edges of a n-ary tree of 
 * ---------  depth n-x.
 */

#ifdef ANSI_C
int create_ary(int arity,int x,int n)
#else
int create_ary(arity,x,n)
int arity;
int x;
int n;
#endif
{
	int me,son,i;

	me = create_node();
	if (x>=n) return(me);
	for (i=0; i<arity; i++) {
		son = create_ary(arity,x+1,n);
		create_edge(me,son);
	}
	return(me);
}

/* k-ary level tree of depth n
 * ===========================
 * All nodes have one predecessor and a3 lower successors.
 * Additionally, nodes have a1 direct left neighbours and a2
 * direct right neighbours.
 */

#ifdef ANSI_C
void create_level_tree(int a1,int a2,int a3,int n)
#else
void create_level_tree(a1,a2,a3,n)
int a1,a2,a3;
int n;
#endif
{
	PRINTF("Generate `(%d,%d,%d)-ary level tree' with depth %d -> %s\n",
			a1,a2,a3,n,outfile);
       	FPRINTF(f,"graph: { title:\"test\"\n"); 
       	FPRINTF(f,"xmax: 700 ymax: 700 x: 30 y: 30 \n"); 
	FPRINTF(f,"layout_downfactor: 8\n");
	(void)create_level(a1,a2,a3,0,n);
       	FPRINTF(f,"}\n"); 
}

/* Auxiliary: create nodes and edges of a level tree of 
 * ---------  depth n-x.
 */

#ifdef ANSI_C
int create_level(int a1,int a2,int a3,int x,int n)
#else
int create_level(a1,a2,a3,x,n)
int a1,a2,a3;
int x;
int n;
#endif
{
	int me,son,left,right,i;

	me = create_node();
	if (x>=n) return(me);
	if (a1>0) {
		left = create_level(a1-1,0,a3,x,n);
		create_nearedge(me,left);
	}
	if (a2>0) {
		right = create_level(0,a2-1,a3,x,n);
		create_nearedge(me,right);
	}
	if (a1>a2) a2 = a1;
	if (a2>a1) a1 = a2;
	for (i=0; i<a3; i++) {
		son = create_level(a1,a2,a3,x+1,n);
		create_edge(me,son);
	}
	return(me);
}

/*--------------------------------------------------------------------*/

/* 4-ary netgraph and random graph generators */
/*============================================*/

/* Buffer that contains the existing nodes */

char nbuf[50000];
int nrnodes;
int nredges;

#ifdef ANSI_C
void initbuf(void)
#else
void initbuf()
#endif
{
	int i;
	for (i=0; i<50000; i++) nbuf[i]=0;
	i = rand();
	srand(i);
	nrnodes = 0;
	nredges = 0;
}



/*  Create a node for the random graph
 *  ----------------------------------
 *  the node is titled num 
 */


#ifdef ANSI_C
void create_nornode(int num)
#else
void create_nornode(num)
int num;
#endif
{
	int j;

	if (num>10) {
		j = rand();
		if (j % 10 > 7) return;	
	}
       	FPRINTF(f,"node: { title: \"%d\" color: yellow }\n", 
		10000 + (30011 * num) % 90001); 
	nbuf[num] = 1;
	nrnodes++;
}


/*  Create a node for the netgraph
 *  ------------------------------
 *  the node is titled num 
 */


#ifdef ANSI_C
void create_netnode(int num)
#else
void create_netnode(num)
int num;
#endif
{
       	FPRINTF(f,"node: { title: \"%d\" color: yellow }\n", 
		10000 + (30011 * num) % 90001); 
	nbuf[num] = 1;
	nrnodes++;
}




/*  Create an edge
 *  --------------
 *  from node titled x to node titled y.
 */

#ifdef ANSI_C
void create_levedge(int x,int y)
#else
void create_levedge(x,y)
int x;
int y;
#endif
{
	if (!nbuf[x]) return;
	if (!nbuf[y]) return;
       	FPRINTF(f,"edge: { sourcename: \"%d\" targetname: \"%d\" ", 
		10000 + (30011 * y) % 90001,
		10000 + (30011 * x) % 90001); 
       	FPRINTF(f," color: red }\n"); 
	nredges++;
}



/* Create 4 ary regular graph (Version 1)
 * --------------------------------------
 */

#ifdef ANSI_C
void create_4ary_netgraph(int n)
#else
void create_4ary_netgraph(n)
int n;
#endif
{
	int i, j;
	int snode, actlev, nlev;
	int mys, mye, olds;

	if (n>50000) return;
	initbuf();
	PRINTF("Generate `4-ary triangular random graph' with maximal %d nodes -> %s\n",
			n,outfile);
       	FPRINTF(f,"graph: { title:\"test\"\n"); 
       	FPRINTF(f,"xmax: 700 ymax: 700 x: 30 y: 30 \n"); 

	olds = 0;
	nlev = 2;
	snode = 3;
	mys = 1;
	mye = mys + nlev - 1;

	create_netnode(0);
	for (i=1; i<n; i++) {
		if (i>=snode) {
			nlev += 1;
			olds = mys;
			mys = snode;
			mye = mys + nlev - 1;
			snode += nlev;
		}
		if (i==mys) {
			if (nbuf[olds]) create_netnode(i);
			create_levedge(i, olds);
		}
		else if (i==mye) {
			if (nbuf[mys-1]) create_netnode(i);
			create_levedge(i, mys-1); 
		}
		else {  
			if (nbuf[olds + (i-mys-1)] ||
			    nbuf[olds + (i-mys)]) create_netnode(i);
			create_levedge(i, olds + (i-mys-1));
			create_levedge(i, olds + (i-mys));
		}
	}
       	FPRINTF(f,"}\n"); 
	PRINTF("%d nodes, %d edges\n",nrnodes, nredges);
}


/* Create 4 ary random graph (Version 1)
 * -------------------------------------
 */

#ifdef ANSI_C
void create_4ary_randomgraph(int n)
#else
void create_4ary_randomgraph(n)
int n;
#endif
{
	int i, j;
	int snode, actlev, nlev;
	int mys, mye, olds;

	if (n>50000) return;
	initbuf();
	PRINTF("Generate `4-ary triangular random graph' with maximal %d nodes -> %s\n",
			n,outfile);
       	FPRINTF(f,"graph: { title:\"test\"\n"); 
       	FPRINTF(f,"xmax: 700 ymax: 700 x: 30 y: 30 \n"); 

	olds = 0;
	nlev = 2;
	snode = 3;
	mys = 1;
	mye = mys + nlev - 1;

	create_nornode(0);
	for (i=1; i<n; i++) {
		if (i>=snode) {
			nlev += 1;
			olds = mys;
			mys = snode;
			mye = mys + nlev - 1;
			snode += nlev;
		}
		if (i==mys) {
			if (nbuf[olds]) create_nornode(i);
			create_levedge(i, olds);
		}
		else if (i==mye) {
			if (nbuf[mys-1]) create_nornode(i);
			create_levedge(i, mys-1); 
		}
		else {  
			if (nbuf[olds + (i-mys-1)] ||
			    nbuf[olds + (i-mys)]) create_nornode(i);
			create_levedge(i, olds + (i-mys-1));
			create_levedge(i, olds + (i-mys));
		}
	}
       	FPRINTF(f,"}\n"); 
	PRINTF("%d nodes, %d edges\n",nrnodes, nredges);
}

/*--------------------------------------------------------------------*/


/* Create 4 ary random graph (Version 2)
 * -------------------------------------
 */


#ifdef ANSI_C
void create_4ary_random2graph(int n)
#else
void create_4ary_random2graph(n)
int n;
#endif
{
	int i, j;
	int snode, actlev, nlev, maxlev;
	int mys, mye, olds;

	if (n>50000) return;
	initbuf();
	PRINTF("Generate `4-ary rhomb random graph' with maximal %d nodes -> %s\n",
			n,outfile);
       	FPRINTF(f,"graph: { title:\"test\"\n"); 
       	FPRINTF(f,"xmax: 700 ymax: 700 x: 30 y: 30 \n"); 

	olds = 0;
	nlev = 2;
	snode = 3;
	mys = 1;
	mye = mys + nlev - 1;

	create_nornode(0);
	for (i=1; i<n; i++) {
		if (i>=snode) {
			if (i>n/2) break;
			nlev += 1;
			olds = mys;
			mys = snode;
			mye = mys + nlev - 1;
			snode += nlev;
		}
		if (i==mys) {
			if (nbuf[olds]) create_nornode(i);
			create_levedge(i, olds);
		}
		else if (i==mye) {
			if (nbuf[mys-1]) create_nornode(i);
			create_levedge(i, mys-1); 
		}
		else {  
			if (nbuf[olds + (i-mys-1)] ||
			    nbuf[olds + (i-mys)]) create_nornode(i);
			create_levedge(i, olds + (i-mys-1));
			create_levedge(i, olds + (i-mys));
		}
	}
	maxlev = 2 * nlev;
	n = 2 * i - nlev; 
	for (;i<n; i++) {
		if (i>=snode) {
			nlev += 1;
			olds = mys;
			mys = snode;
			mye = mys + maxlev - nlev - 1;
			snode += (maxlev - nlev);
		}
		if (nbuf[olds + (i-mys)] ||
		    nbuf[olds + (i-mys+1)]) create_nornode(i);
		create_levedge(i, olds + (i-mys));
		create_levedge(i, olds + (i-mys+1));
	}
       	FPRINTF(f,"}\n"); 
	PRINTF("%d nodes, %d edges\n",nrnodes, nredges);
}




/* Create 4 ary regular graph (Version 2)
 * --------------------------------------
 */


#ifdef ANSI_C
void create_4ary_net2graph(int n)
#else
void create_4ary_net2graph(n)
int n;
#endif
{
	int i, j;
	int snode, actlev, nlev, maxlev;
	int mys, mye, olds;

	if (n>50000) return;
	initbuf();
	PRINTF("Generate `4-ary rhomb regular network graph' with %d nodes -> %s\n",
			n,outfile);
       	FPRINTF(f,"graph: { title:\"test\"\n"); 
       	FPRINTF(f,"xmax: 700 ymax: 700 x: 30 y: 30 \n"); 

	olds = 0;
	nlev = 2;
	snode = 3;
	mys = 1;
	mye = mys + nlev - 1;

	create_nornode(0);
	for (i=1; i<n; i++) {
		if (i>=snode) {
			if (i>n/2) break;
			nlev += 1;
			olds = mys;
			mys = snode;
			mye = mys + nlev - 1;
			snode += nlev;
		}
		if (i==mys) {
			create_netnode(i);
			create_levedge(i, olds);
		}
		else if (i==mye) {
			create_netnode(i);
			create_levedge(i, mys-1); 
		}
		else {  
			create_netnode(i);
			create_levedge(i, olds + (i-mys-1));
			create_levedge(i, olds + (i-mys));
		}
	}
	maxlev = 2 * nlev;
	n = 2 * i - nlev; 
	for (;i<n; i++) {
		if (i>=snode) {
			nlev += 1;
			olds = mys;
			mys = snode;
			mye = mys + maxlev - nlev - 1;
			snode += (maxlev - nlev);
		}
		if (nlev >= maxlev) break;
		create_netnode(i);
		create_levedge(i, olds + (i-mys));
		create_levedge(i, olds + (i-mys+1));
	}
       	FPRINTF(f,"}\n"); 
	PRINTF("%d nodes, %d edges\n",nrnodes, nredges);
}



