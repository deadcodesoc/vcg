%{


#line 2 "/RW/esprit/users/sander/src/PARSEGEN/parse.skel"

/*--------------------------------------------------------------------*/
/*            A bison parser specification made by parsegen           */
/*--------------------------------------------------------------------*/

#ifndef lint
static char *parseskel_id_string="$Id: parse.skel,v 1.5 1994/01/20 23:44:31 sander Exp sander $";
#endif

/*--------------------------------------------------------------------*/
/* Prototypes and Externals					      */
/*--------------------------------------------------------------------*/


extern int line_nr;
extern int pos_nr;

/* Error messages */

int nr_errors;

/*--------------------------------------------------------------------*/
/* Tokens from scanner                                                */ 
/*--------------------------------------------------------------------*/



#line 1441 "grammar.pgs"
%}


%token LEXWORD_ABOVE
%token LEXWORD_ANCHORPOINTS
%token LEXWORD_ANCHOR
%token LEXWORD_AQUAMARINE
%token LEXWORD_AROUND
%token LEXWORD_ARROWMODE
%token LEXWORD_ARROWHEIGHT
%token LEXWORD_ARROWWIDTH
%token LEXWORD_ARROWCOLOR
%token LEXWORD_ARROWSTYLE
%token LEXWORD_ARROWSIZE
%token LEXWORD_BARROWCOLOR
%token LEXWORD_BARROWSTYLE
%token LEXWORD_BARROWSIZE
%token LEXWORD_BACKEDGE
%token LEXWORD_BARYCENTER
%token LEXWORD_BARY
%token LEXWORD_BARYMEDIAN
%token LEXWORD_BEHIND
%token LEXWORD_BELOW
%token LEXWORD_BLACK
%token LEXWORD_BLUE
%token LEXWORD_BMAX
%token LEXWORD_BORDERCOLOR
%token LEXWORD_BORDERWIDTH
%token LEXWORD_BOTTOM_MARGIN
%token LEXWORD_BOTTOM_TO_TOP
%token LEXWORD_BOTTOM
%token LEXWORD_BOX
%token LEXWORD_BENTNEAREDGE
%token LEXWORD_CENTER
%token LEXWORD_CFISH
%token LEXWORD_CLASSNAME
%token LEXWORD_CLASS
%token LEXWORD_CLUSTER
%token LEXWORD_CMIN
%token LEXWORD_CMAX
%token LEXWORD_COLORENTRY
%token LEXWORD_COLOR
%token LEXWORD_CONSTRAINTS
%token LEXWORD_CONSTRAINT
%token LEXWORD_CONTINUOUS
%token LEXWORD_CROSSING_WEIGHT
%token LEXWORD_CROSSING_OPT
%token LEXWORD_CROSSING_P2
%token LEXWORD_CYAN
%token LEXWORD_DARKBLUE
%token LEXWORD_DARKCYAN
%token LEXWORD_DARKGREEN
%token LEXWORD_DARKGREY
%token LEXWORD_DARKMAGENTA
%token LEXWORD_DARKRED
%token LEXWORD_DARKYELLOW
%token LEXWORD_DASHED
%token LEXWORD_DFS
%token LEXWORD_DIMENSION
%token LEXWORD_DIRTY_EDGE_LABELS
%token LEXWORD_DISPLAY_EDGE_LABELS
%token LEXWORD_DOTTED
%token LEXWORD_EDGE1
%token LEXWORD_EDGE2
%token LEXWORD_EDGES
%token LEXWORD_ELLIPSE
%token LEXWORD_EQUAL_COLUMN
%token LEXWORD_EQUAL_POSITION
%token LEXWORD_EQUAL_ROW
%token LEXWORD_EQUAL
%token LEXWORD_EVERY
%token LEXWORD_FCFISH
%token LEXWORD_FPFISH
%token LEXWORD_FIXED
%token LEXWORD_FREE
%token LEXWORD_FINETUNING
%token LEXWORD_FOLDEDGE
%token LEXWORD_FOLDNODE
%token LEXWORD_FOLDING
%token LEXWORD_FONTNAME
%token LEXWORD_GOLD
%token LEXWORD_GRAPH
%token LEXWORD_GREATER
%token LEXWORD_GREEN
%token LEXWORD_GREY
%token LEXWORD_HEIGHT
%token LEXWORD_HIDESINGLES
%token LEXWORD_HIGH_MARGIN
%token LEXWORD_HIGH
%token LEXWORD_HIDDEN
%token LEXWORD_HORDER
%token LEXWORD_ICONFILE
%token LEXWORD_ICONHEIGHT
%token LEXWORD_ICONSTYLE
%token LEXWORD_ICONWIDTH
%token LEXWORD_INCLUDE
%token LEXWORD_INFONAME
%token LEXWORD_INFO1
%token LEXWORD_INFO2
%token LEXWORD_INFO3
%token LEXWORD_INPUTFUNCTION
%token LEXWORD_INTERVAL
%token LEXWORD_INVISIBLE
%token LEXWORD_IN_FRONT
%token LEXWORD_ISI
%token LEXWORD_KHAKI
%token LEXWORD_TEXTCOLOR
%token LEXWORD_LABEL
%token LEXWORD_LATE_LABELS
%token LEXWORD_LAYOUTALGORITHM
%token LEXWORD_LAYOUTFREQUENCY
%token LEXWORD_LAYOUTPARAMETER
%token LEXWORD_LAYOUTDOWNFACTOR
%token LEXWORD_LAYOUTUPFACTOR
%token LEXWORD_LAYOUTNEARFACTOR
%token LEXWORD_LAYOUTSPLINEFACTOR
%token LEXWORD_LEFT_JUSTIFY
%token LEXWORD_LEFT_MARGIN
%token LEXWORD_LEFT_NEIGHBOR
%token LEXWORD_LEFT_TO_RIGHT
%token LEXWORD_LEFT
%token LEXWORD_LEVEL
%token LEXWORD_VORDER
%token LEXWORD_LIGHTBLUE
%token LEXWORD_LIGHTCYAN
%token LEXWORD_LIGHTGREEN
%token LEXWORD_LIGHTGREY
%token LEXWORD_LIGHTMAGENTA
%token LEXWORD_LIGHTRED
%token LEXWORD_LIGHTYELLOW
%token LEXWORD_LILAC
%token LEXWORD_LIMIT
%token LEXWORD_LINE
%token LEXWORD_LINESTYLE
%token LEXWORD_LOC
%token LEXWORD_LOWER_NEIGHBOR
%token LEXWORD_LOW_MARGIN
%token LEXWORD_LOW
%token LEXWORD_MAGENTA
%token LEXWORD_MANHATTEN
%token LEXWORD_MANUAL
%token LEXWORD_MAXDEPTHSLOW
%token LEXWORD_MAXDEPTH
%token LEXWORD_MAXDEGREE
%token LEXWORD_MAXINDEGREE
%token LEXWORD_MAXOUTDEGREE
%token LEXWORD_MEDIAN
%token LEXWORD_MEDIANBARY
%token LEXWORD_MINDEPTHSLOW
%token LEXWORD_MINDEPTH
%token LEXWORD_MINDEGREE
%token LEXWORD_MININDEGREE
%token LEXWORD_MINOUTDEGREE
%token LEXWORD_MINBACK
%token LEXWORD_NAME
%token LEXWORD_NEAREDGE
%token LEXWORD_NEIGHBORS
%token LEXWORD_NEAREDGES
%token LEXWORD_NONEAREDGES
%token LEXWORD_NODE1
%token LEXWORD_NODE2
%token LEXWORD_NODES
%token LEXWORD_NODE_ALIGN
%token LEXWORD_NONE
%token LEXWORD_NO
%token LEXWORD_ORANGE
%token LEXWORD_ORCHID
%token LEXWORD_ORIENTATION
%token LEXWORD_OUTPUTFUNCTION
%token LEXWORD_PFISH
%token LEXWORD_PINK
%token LEXWORD_PLANAR
%token LEXWORD_PMIN
%token LEXWORD_PMAX
%token LEXWORD_PORTSHARING
%token LEXWORD_PRIORITYPHASE
%token LEXWORD_PRIORITY
%token LEXWORD_PURPLE
%token LEXWORD_RANGE
%token LEXWORD_RED
%token LEXWORD_RHOMB
%token LEXWORD_RIGHT_JUSTIFY
%token LEXWORD_RIGHT_MARGIN
%token LEXWORD_RIGHT_NEIGHBOR
%token LEXWORD_RIGHT_TO_LEFT
%token LEXWORD_RIGHT
%token LEXWORD_RMIN
%token LEXWORD_RMAX
%token LEXWORD_SCALING
%token LEXWORD_SHAPE
%token LEXWORD_SHRINK
%token LEXWORD_SMAX
%token LEXWORD_SMANHATTEN
%token LEXWORD_SIZE
%token LEXWORD_SMALLER
%token LEXWORD_SOLID
%token LEXWORD_SOURCENAME
%token LEXWORD_SPLINES
%token LEXWORD_SPREADLEVEL
%token LEXWORD_STATUS
%token LEXWORD_STRETCH
%token LEXWORD_STRAIGHTPHASE
%token LEXWORD_TARGETNAME
%token LEXWORD_TEXTMODE
%token LEXWORD_THICKNESS
%token LEXWORD_TITLE
%token LEXWORD_TOPSORT
%token LEXWORD_TOP_MARGIN
%token LEXWORD_TOP_TO_BOTTOM
%token LEXWORD_TOP
%token LEXWORD_TREE
%token LEXWORD_TREEFACTOR
%token LEXWORD_TRIANGLE
%token LEXWORD_TURQUOISE
%token LEXWORD_TYPENAME
%token LEXWORD_UPPER_NEIGHBOR
%token LEXWORD_VIEW
%token LEXWORD_WHITE
%token LEXWORD_WIDTH
%token LEXWORD_XBASE
%token LEXWORD_XMAX
%token LEXWORD_XRASTER
%token LEXWORD_XLRASTER
%token LEXWORD_XSCROLLBAR
%token LEXWORD_XSPACE
%token LEXWORD_XLSPACE
%token LEXWORD_YBASE
%token LEXWORD_YELLOWGREEN
%token LEXWORD_YELLOW
%token LEXWORD_YES
%token LEXWORD_YMAX
%token LEXWORD_YRASTER
%token LEXWORD_YSCROLLBAR
%token LEXWORD_YSPACE
%token LEX_INT
%token LEX_FLOAT
%token LEX_CHAR
%token LEX_STRING

%{


#line 34 "/RW/esprit/users/sander/src/PARSEGEN/parse.skel"

/*--------------------------------------------------------------------*/
/* Includes                                                           */ 
/*--------------------------------------------------------------------*/

#define Y_TAB_H
#ifdef __cplusplus
#include <std.h>
#else
#include <string.h>
#endif /* __cplusplus */

#ifndef YYLTYPE
typedef struct yyltype {
		int timestamp;
		int first_line;
		int first_column;
		int last_line;
		int last_column;
		char *text;
	}  yyltype;

#define YYLTYPE yyltype
#endif



#line 32000 "/RW/esprit/users/sander/src/PARSEGEN/parse.skel"
typedef struct stree_node *syntaxtree;
#undef yysyntaxtree
#define yysyntaxtree syntaxtree

#define BISONGEN
#undef  YACCGEN

#define YYVALGLOBAL


#line 24 "grammar.pgs"

#ifndef lint
static char *id_string="$Id: grammar.pgs,v 3.17 1995/02/08 18:35:02 sander Exp $";
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


/* $Log: grammar.pgs,v $
# Revision 3.17  1995/02/08  18:35:02  sander
# Small bug for K&R C corrected.
#
# Revision 3.16  1995/02/08  11:11:14  sander
# Distribution version 1.3.
#
# Revision 3.15  1994/12/23  18:12:45  sander
# Manhatten layout added.
#
# Revision 3.14  1994/11/23  14:50:47  sander
# Hash table to 22079 expanded. Better string hash function implemented.
#
# Revision 3.13  1994/08/08  16:01:47  sander
# Attributes xraster, xlraster, yraster added.
#
# Revision 3.12  1994/08/05  12:13:25  sander
# Treelayout added. Attributes "treefactor" and "spreadlevel" added.
# Scaling as abbreviation of "stretch/shrink" added.
#
# Revision 3.11  1994/08/04  08:58:20  sander
# Attributes crossing_weight and crossing_optimization added.
#
# Revision 3.10  1994/08/03  13:58:44  sander
# Horizontal order mechanism changed.
# Attribute horizontal_order for edges added.
#
# Revision 3.9  1994/06/07  14:09:59  sander
# Splines implemented.
# HP-UX, Linux, AIX, Sun-Os, IRIX compatibility tested.
# The tool is now ready to be distributed.
#
# Revision 3.8  1994/05/17  16:35:59  sander
# attribute node_align added to allow nodes to be centered in the levels.
#
# Revision 3.7  1994/05/16  08:56:03  sander
# shape attribute (boxes, rhombs, ellipses, triangles) added.
#
# Revision 3.6  1994/05/05  08:20:30  sander
# Algorithm late labels added: If labels are inserted
# after partitioning, this may yield a better layout.
#
# Revision 3.5  1994/04/27  16:05:19  sander
# attributes of graph nodes adapted to the of normal nodes.
#
# Revision 3.4  1994/03/04  19:11:24  sander
# Specification of levels per node added.
# X11 geometry behaviour (option -geometry) changed such
# that the window is now opened automatically.
#
# Revision 3.3  1994/03/03  15:35:39  sander
# Edge line style `invisible' added.
#
# Revision 3.2  1994/03/02  11:48:54  sander
# Layoutalgoritms mindepthslow, maxdepthslow, minindegree, ... mandegree
# added.
# Anchors and nearedges are not anymore allowed to be intermixed.
# Escapes in strings are now allowed.
#
# Revision 3.1  1994/03/01  10:59:55  sander
# Copyright and Gnu Licence message added.
# Problem with "nearedges: no" and "selfloops" solved.
#
# Revision 2.4  1994/02/13  17:25:54  sander
# attribute 'finetuning' added.
#
# Revision 2.3  1994/01/21  19:33:46  sander
# VCG Version tested on Silicon Graphics IRIX, IBM R6000 AIX and Sun 3/60.
# Option handling improved. Option -grabinputfocus installed.
# X11 Font selection scheme implemented. The user can now select a font
# during installation.
# Sun K&R C (a nonansi compiler) tested. Some portabitility problems solved.
#
# Revision 2.1  1993/12/08  21:19:21  sander
# Reasonable fast and stable version
#
 */


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "globals.h"
#include "main.h"
#include "options.h"

#ifndef YY_CHAR
#define YY_CHAR char
extern YY_CHAR *yytext;
#endif

/* the following is added for flex 2.4.6 */

#ifndef YY_MALLOC_DECL
#define YY_MALLOC_DECL
#include <malloc.h>
#endif
 
#undef YYVALGLOBAL
 
extern yysyntaxtree Syntax_Tree;

#define exit(a) gs_exit(a)
extern void gs_exit            _PP((int x));
 
void   line_directive _PP((char *text));
void   escape_transl  _PP((char *text));
char  *my_itoa        _PP((int x));
long   long_atoi      _PP((char *c));
void   syntaxerror    _PP((int line,int pos,char *mesge));
void   warning        _PP((int line,int pos,char *mesge));
 
#ifndef yysyntaxerror
#define yysyntaxerror(l,p,m) syntaxerror(l,p,m)
#endif
 
#ifndef yyerror
#define yyerror(x) { \
        SPRINTF(message,"unexpected %s \"%s\" (%s)", \
                 ((yychar<0)?"(?)":yytokname[YYTRANSLATE(yychar)]),     \
                 (strlen(yytext)<48?yytext:"(?)"),x); \
        syntaxerror(line_nr,pos_nr,message);\
    }
#endif
 
/* Memory Management */

#ifdef MEMBLOCKSIZE
#define PARSEBLOCKSIZE (MEMBLOCKSIZE/sizeof(struct stree_node)+1)
#endif

/* Hash Table */

#define hash_size 22079
 


#ifndef NULL
#define NULL 0
#endif

#ifndef REVERT
#define REVERT(x) Revert(x)
#endif

#ifndef COPY
#define COPY(x) Copy(x)
#endif


#line 1 "/RW/esprit/users/sander/src/PARSEGEN/stdph.skel"

#ifndef STDPARSER
#define STDPARSER

/* $Id: stdph.skel,v 1.8 1994/01/20 23:44:31 sander Exp sander $ */

#undef  PARSEGENSTD
#define PARSEGENSTD

/*--------------------------------------------------------------------*/
/*  Standard Tree Construction Interface   			      */
/*--------------------------------------------------------------------*/

#ifndef ALIGN
#define ALIGN 8
#define IALIGN (ALIGN-1)
#endif
#ifndef PARSEBLOCKSIZE
#define PARSEBLOCKSIZE 10000
#endif

/*-------------------*/
/* syntax tree nodes */
/*-------------------*/

union  special {
        unsigned char      byte;
        short int          snum;
        unsigned short int usnum;
        int                num;
        unsigned int       unum;
        long int           lnum;
        unsigned long int  ulnum;
        float              realnum;
        double             lrealnum;
        char              *string;
};

struct stree_node {
        int  tag_field;
        int  first_line;
        int  first_column;
        int  last_line;
        int  last_column;
#ifdef USERFTYPE
	USERFTYPE user_field;
#endif
        struct stree_node *father;
        union  special     contents;
        struct stree_node *xson[1];
};


/* typedef struct stree_node *syntaxtree; */


#undef yysyntaxtree
#define yysyntaxtree syntaxtree 


#define tag(x)           ((x)->tag_field)
#define nr_of_sons(x)    (ConstructorArity((x)->tag_field))
#define xfirst_line(x)    ((x)->first_line)
#define xfirst_column(x)  ((x)->first_column)
#define xlast_line(x)     ((x)->last_line)
#define xlast_column(x)   ((x)->last_column)
#define xfather(x)        ((x)->father)

#ifdef USERFTYPE
#define	user_field(x)     ((x)->user_field)
#endif

#define get_byte(x)      ((x)->contents.byte)
#define get_snum(x)      ((x)->contents.snum)
#define get_usnum(x)     ((x)->contents.usnum)
#define get_num(x)       ((x)->contents.num)
#define get_unum(x)      ((x)->contents.unum)
#define get_lnum(x)      ((x)->contents.lnum)
#define get_ulnum(x)     ((x)->contents.ulnum)
#define get_realnum(x)   ((x)->contents.realnum)
#define get_lrealnum(x)  ((x)->contents.lrealnum)
#define get_string(x)    ((x)->contents.string)

#define son1(x)    ((x)->xson[0])
#define son2(x)    ((x)->xson[1])
#define son3(x)    ((x)->xson[2])
#define son4(x)    ((x)->xson[3])
#define son5(x)    ((x)->xson[4])
#define son6(x)    ((x)->xson[5])
#define son7(x)    ((x)->xson[6])
#define son8(x)    ((x)->xson[7])
#define son9(x)    ((x)->xson[8])
#define son(x,i)   ((x)->xson[i-1])

#ifndef Y_TAB_H


#line 1441 "grammar.pgs"
#include "y.tab.h"


#line 97 "/RW/esprit/users/sander/src/PARSEGEN/stdph.skel"
#define Y_TAB_H
#endif /* Y_TAB_H */


/*------------*/ 
/* Prototypes */ 
/*------------*/ 


#ifdef ANSI_C

char * ParseMalloc(int x);
void ParseFree(void);

union special *UnionByte(unsigned char x);
union special *UnionSnum(short int x);
union special *UnionUsnum(unsigned short int x);
union special *UnionNum(int x);
union special *UnionUnum(unsigned int x);
union special *UnionLnum(long int x);
union special *UnionUlnum(unsigned long int x);
union special *UnionRealnum(float x);
union special *UnionLrealnum(double x);
union special *UnionString(char *x);

syntaxtree BuildCont(int mtag,union special *x,YYLTYPE *l);
yysyntaxtree BuildTree(int mtag,int len,union special *x,YYLTYPE *l, ...);

syntaxtree Copy(syntaxtree x);
syntaxtree Revert(syntaxtree list);

const char *ConstructorName(int i);
int   ConstructorArity(int i);

#else
char * ParseMalloc();
void ParseFree();

union special *UnionByte();                     
union special *UnionSnum();                     
union special *UnionUsnum();                     
union special *UnionNum();                     
union special *UnionUnum();                     
union special *UnionLnum();                     
union special *UnionUlnum();                     
union special *UnionRealnum();                     
union special *UnionLrealnum();                     
union special *UnionString();                     

syntaxtree BuildCont();
yysyntaxtree BuildTree();

syntaxtree Copy();
syntaxtree Revert();

char *ConstructorName();
int   ConstructorArity();

#ifndef const
#define const
#endif

#endif /* ANSI_C */
 
#undef  yyparseinit
#define yyparseinit() /**/ 

#endif /* STDPARSER */

/*-- end of standard tree construction interface ---------------------*/



#line 1441 "grammar.pgs"

/*--------------------------------------------------------------------*/
/* Static part                                                        */
/*--------------------------------------------------------------------*/

/* Static Global Variables */
/*-------------------------*/


/* Constructors: */

#define T_Co_index_val  0
#define T_Co_stern  1
#define T_Co_range  2
#define T_Co_index  3
#define T_Co_index_value  4
#define T_Co_string  5
#define T_Co_char  6
#define T_Co_float  7
#define T_Co_integer  8
#define T_Co_z  9
#define T_Co_y  10
#define T_Co_x  11
#define T_Co_right_neighbor  12
#define T_Co_left_neighbor  13
#define T_Co_lower_neighbor  14
#define T_Co_upper_neighbor  15
#define T_Co_right_margin  16
#define T_Co_left_margin  17
#define T_Co_bottom_margin  18
#define T_Co_top_margin  19
#define T_Co_equal_column  20
#define T_Co_equal_row  21
#define T_Co_equal_position  22
#define T_Co_behind  23
#define T_Co_in_font  24
#define T_Co_right  25
#define T_Co_left  26
#define T_Co_below  27
#define T_Co_above  28
#define T_Co_limit  29
#define T_Co_cluster  30
#define T_Co_xrange  31
#define T_Co_high_margin  32
#define T_Co_low_margin  33
#define T_Co_neighbors  34
#define T_Co_greater  35
#define T_Co_smaller  36
#define T_Co_equal  37
#define T_Co_string_array  38
#define T_Co_dimension  39
#define T_Co_name  40
#define T_Co_interval  41
#define T_Co_nodes  42
#define T_Co_size  43
#define T_Co_solid  44
#define T_Co_line  45
#define T_Co_none  46
#define T_Co_invisible  47
#define T_Co_dashed  48
#define T_Co_dotted  49
#define T_Co_continuous  50
#define T_Co_anchor  51
#define T_Co_linestyle  52
#define T_Co_barrowstyle  53
#define T_Co_arrowstyle  54
#define T_Co_barrowsize  55
#define T_Co_arrowsize  56
#define T_Co_barrowcolor  57
#define T_Co_arrowcolor  58
#define T_Co_arrowheight  59
#define T_Co_arrowwidth  60
#define T_Co_priority  61
#define T_Co_class  62
#define T_Co_thickness  63
#define T_Co_targetname  64
#define T_Co_sourcename  65
#define T_Co_around  66
#define T_Co_top  67
#define T_Co_bottom  68
#define T_Co_triangle  69
#define T_Co_ellipse  70
#define T_Co_rhomb  71
#define T_Co_box  72
#define T_Co_right_justify  73
#define T_Co_left_justify  74
#define T_Co_center  75
#define T_Co_iconstyle  76
#define T_Co_iconheight  77
#define T_Co_iconwidth  78
#define T_Co_anchorpoints  79
#define T_Co_iconfile  80
#define T_Co_bordercolor  81
#define T_Co_fontname  82
#define T_Co_constraint_attribute  83
#define T_Co_edge_attribute  84
#define T_Co_node_attribute  85
#define T_Co_free  86
#define T_Co_fixed  87
#define T_Co_fpfish  88
#define T_Co_pfish  89
#define T_Co_fcfish  90
#define T_Co_cfish  91
#define T_Co_medianbary  92
#define T_Co_barymedian  93
#define T_Co_median  94
#define T_Co_bary  95
#define T_Co_no  96
#define T_Co_yes  97
#define T_Co_grey  98
#define T_Co_manual  99
#define T_Co_every  100
#define T_Co_depthfirst  101
#define T_Co_minbackwards  102
#define T_Co_minoutdegree  103
#define T_Co_maxoutdegree  104
#define T_Co_minindegree  105
#define T_Co_maxindegree  106
#define T_Co_mindegree  107
#define T_Co_maxdegree  108
#define T_Co_mindepthslow  109
#define T_Co_maxdepthslow  110
#define T_Co_mindepth  111
#define T_Co_maxdepth  112
#define T_Co_tree  113
#define T_Co_constaints  114
#define T_Co_planar  115
#define T_Co_isi  116
#define T_Co_barycenter  117
#define T_Co_right_to_left  118
#define T_Co_left_to_right  119
#define T_Co_bottom_to_top  120
#define T_Co_top_to_bottom  121
#define T_Co_low  122
#define T_Co_high  123
#define T_Co_colindex  124
#define T_Co_yellowgreen  125
#define T_Co_yellow  126
#define T_Co_white  127
#define T_Co_turquoise  128
#define T_Co_red  129
#define T_Co_purple  130
#define T_Co_pink  131
#define T_Co_orchid  132
#define T_Co_orange  133
#define T_Co_magenta  134
#define T_Co_lilac  135
#define T_Co_lightyellow  136
#define T_Co_lightred  137
#define T_Co_lightmagenta  138
#define T_Co_lightgrey  139
#define T_Co_lightgreen  140
#define T_Co_lightcyan  141
#define T_Co_lightblue  142
#define T_Co_khaki  143
#define T_Co_green  144
#define T_Co_gold  145
#define T_Co_darkyellow  146
#define T_Co_darkred  147
#define T_Co_darkmagenta  148
#define T_Co_darkgrey  149
#define T_Co_darkgreen  150
#define T_Co_darkcyan  151
#define T_Co_darkblue  152
#define T_Co_cyan  153
#define T_Co_blue  154
#define T_Co_black  155
#define T_Co_aquamarine  156
#define T_Co_yscrollbar  157
#define T_Co_xscrollbar  158
#define T_Co_outputfunction  159
#define T_Co_inputfunction  160
#define T_Co_topsort  161
#define T_Co_layoutparameter  162
#define T_Co_include  163
#define T_Co_typename  164
#define T_Co_straight_max  165
#define T_Co_rubber_min  166
#define T_Co_rubber_max  167
#define T_Co_pendel_min  168
#define T_Co_pendel_max  169
#define T_Co_cross_min  170
#define T_Co_cross_max  171
#define T_Co_bend_max  172
#define T_Co_view_splines  173
#define T_Co_view_nodes  174
#define T_Co_view_edges  175
#define T_Co_view_method  176
#define T_Co_crossing_weight  177
#define T_Co_crossing_opt  178
#define T_Co_crossing_phase2  179
#define T_Co_treefactor  180
#define T_Co_spreadlevel  181
#define T_Co_arrow_mode  182
#define T_Co_port_sharing  183
#define T_Co_node_alignment  184
#define T_Co_orientation  185
#define T_Co_dummy  186
#define T_Co_nonearedges  187
#define T_Co_smanhatten  188
#define T_Co_manhatten  189
#define T_Co_priophase  190
#define T_Co_straightphase  191
#define T_Co_hidesingles  192
#define T_Co_finetuning  193
#define T_Co_dirty_edge_label  194
#define T_Co_display_edge_label  195
#define T_Co_late_edge_label  196
#define T_Co_splinefactor  197
#define T_Co_nearfactor  198
#define T_Co_upfactor  199
#define T_Co_downfactor  200
#define T_Co_layoutfrequency  201
#define T_Co_layoutalgorithm  202
#define T_Co_colentry  203
#define T_Co_infoname  204
#define T_Co_classname  205
#define T_Co_hidden  206
#define T_Co_yraster  207
#define T_Co_xlraster  208
#define T_Co_xraster  209
#define T_Co_yspace  210
#define T_Co_xlspace  211
#define T_Co_xspace  212
#define T_Co_ybase  213
#define T_Co_xbase  214
#define T_Co_ymax  215
#define T_Co_xmax  216
#define T_Co_status  217
#define T_Co_horizontal_order  218
#define T_Co_level  219
#define T_Co_shape  220
#define T_Co_textmode  221
#define T_Co_stretch  222
#define T_Co_shrink  223
#define T_Co_scaling  224
#define T_Co_folding  225
#define T_Co_loc  226
#define T_Co_ydef  227
#define T_Co_xdef  228
#define T_Co_borderwidth  229
#define T_Co_height  230
#define T_Co_width  231
#define T_Co_colorborder  232
#define T_Co_textcolor  233
#define T_Co_color  234
#define T_Co_info3  235
#define T_Co_info2  236
#define T_Co_info1  237
#define T_Co_label  238
#define T_Co_title  239
#define T_Co_constraint  240
#define T_Co_back_edge  241
#define T_Co_bent_near_edge  242
#define T_Co_near_edge  243
#define T_Co_edge  244
#define T_Co_node  245
#define T_Co_graph  246
#define T_Co_foldedge_defaults  247
#define T_Co_foldnode_defaults  248
#define T_Co_edge_defaults  249
#define T_Co_node_defaults  250
#define T_Co_graph_attribute  251
#define T_Co_graph_entry  252

/* Constructor Names */

static const char * const yyconst_name[] = {
	"T_Co_index_val",
	"T_Co_stern",
	"T_Co_range",
	"T_Co_index",
	"T_Co_index_value",
	"T_Co_string",
	"T_Co_char",
	"T_Co_float",
	"T_Co_integer",
	"T_Co_z",
	"T_Co_y",
	"T_Co_x",
	"T_Co_right_neighbor",
	"T_Co_left_neighbor",
	"T_Co_lower_neighbor",
	"T_Co_upper_neighbor",
	"T_Co_right_margin",
	"T_Co_left_margin",
	"T_Co_bottom_margin",
	"T_Co_top_margin",
	"T_Co_equal_column",
	"T_Co_equal_row",
	"T_Co_equal_position",
	"T_Co_behind",
	"T_Co_in_font",
	"T_Co_right",
	"T_Co_left",
	"T_Co_below",
	"T_Co_above",
	"T_Co_limit",
	"T_Co_cluster",
	"T_Co_xrange",
	"T_Co_high_margin",
	"T_Co_low_margin",
	"T_Co_neighbors",
	"T_Co_greater",
	"T_Co_smaller",
	"T_Co_equal",
	"T_Co_string_array",
	"T_Co_dimension",
	"T_Co_name",
	"T_Co_interval",
	"T_Co_nodes",
	"T_Co_size",
	"T_Co_solid",
	"T_Co_line",
	"T_Co_none",
	"T_Co_invisible",
	"T_Co_dashed",
	"T_Co_dotted",
	"T_Co_continuous",
	"T_Co_anchor",
	"T_Co_linestyle",
	"T_Co_barrowstyle",
	"T_Co_arrowstyle",
	"T_Co_barrowsize",
	"T_Co_arrowsize",
	"T_Co_barrowcolor",
	"T_Co_arrowcolor",
	"T_Co_arrowheight",
	"T_Co_arrowwidth",
	"T_Co_priority",
	"T_Co_class",
	"T_Co_thickness",
	"T_Co_targetname",
	"T_Co_sourcename",
	"T_Co_around",
	"T_Co_top",
	"T_Co_bottom",
	"T_Co_triangle",
	"T_Co_ellipse",
	"T_Co_rhomb",
	"T_Co_box",
	"T_Co_right_justify",
	"T_Co_left_justify",
	"T_Co_center",
	"T_Co_iconstyle",
	"T_Co_iconheight",
	"T_Co_iconwidth",
	"T_Co_anchorpoints",
	"T_Co_iconfile",
	"T_Co_bordercolor",
	"T_Co_fontname",
	"T_Co_constraint_attribute",
	"T_Co_edge_attribute",
	"T_Co_node_attribute",
	"T_Co_free",
	"T_Co_fixed",
	"T_Co_fpfish",
	"T_Co_pfish",
	"T_Co_fcfish",
	"T_Co_cfish",
	"T_Co_medianbary",
	"T_Co_barymedian",
	"T_Co_median",
	"T_Co_bary",
	"T_Co_no",
	"T_Co_yes",
	"T_Co_grey",
	"T_Co_manual",
	"T_Co_every",
	"T_Co_depthfirst",
	"T_Co_minbackwards",
	"T_Co_minoutdegree",
	"T_Co_maxoutdegree",
	"T_Co_minindegree",
	"T_Co_maxindegree",
	"T_Co_mindegree",
	"T_Co_maxdegree",
	"T_Co_mindepthslow",
	"T_Co_maxdepthslow",
	"T_Co_mindepth",
	"T_Co_maxdepth",
	"T_Co_tree",
	"T_Co_constaints",
	"T_Co_planar",
	"T_Co_isi",
	"T_Co_barycenter",
	"T_Co_right_to_left",
	"T_Co_left_to_right",
	"T_Co_bottom_to_top",
	"T_Co_top_to_bottom",
	"T_Co_low",
	"T_Co_high",
	"T_Co_colindex",
	"T_Co_yellowgreen",
	"T_Co_yellow",
	"T_Co_white",
	"T_Co_turquoise",
	"T_Co_red",
	"T_Co_purple",
	"T_Co_pink",
	"T_Co_orchid",
	"T_Co_orange",
	"T_Co_magenta",
	"T_Co_lilac",
	"T_Co_lightyellow",
	"T_Co_lightred",
	"T_Co_lightmagenta",
	"T_Co_lightgrey",
	"T_Co_lightgreen",
	"T_Co_lightcyan",
	"T_Co_lightblue",
	"T_Co_khaki",
	"T_Co_green",
	"T_Co_gold",
	"T_Co_darkyellow",
	"T_Co_darkred",
	"T_Co_darkmagenta",
	"T_Co_darkgrey",
	"T_Co_darkgreen",
	"T_Co_darkcyan",
	"T_Co_darkblue",
	"T_Co_cyan",
	"T_Co_blue",
	"T_Co_black",
	"T_Co_aquamarine",
	"T_Co_yscrollbar",
	"T_Co_xscrollbar",
	"T_Co_outputfunction",
	"T_Co_inputfunction",
	"T_Co_topsort",
	"T_Co_layoutparameter",
	"T_Co_include",
	"T_Co_typename",
	"T_Co_straight_max",
	"T_Co_rubber_min",
	"T_Co_rubber_max",
	"T_Co_pendel_min",
	"T_Co_pendel_max",
	"T_Co_cross_min",
	"T_Co_cross_max",
	"T_Co_bend_max",
	"T_Co_view_splines",
	"T_Co_view_nodes",
	"T_Co_view_edges",
	"T_Co_view_method",
	"T_Co_crossing_weight",
	"T_Co_crossing_opt",
	"T_Co_crossing_phase2",
	"T_Co_treefactor",
	"T_Co_spreadlevel",
	"T_Co_arrow_mode",
	"T_Co_port_sharing",
	"T_Co_node_alignment",
	"T_Co_orientation",
	"T_Co_dummy",
	"T_Co_nonearedges",
	"T_Co_smanhatten",
	"T_Co_manhatten",
	"T_Co_priophase",
	"T_Co_straightphase",
	"T_Co_hidesingles",
	"T_Co_finetuning",
	"T_Co_dirty_edge_label",
	"T_Co_display_edge_label",
	"T_Co_late_edge_label",
	"T_Co_splinefactor",
	"T_Co_nearfactor",
	"T_Co_upfactor",
	"T_Co_downfactor",
	"T_Co_layoutfrequency",
	"T_Co_layoutalgorithm",
	"T_Co_colentry",
	"T_Co_infoname",
	"T_Co_classname",
	"T_Co_hidden",
	"T_Co_yraster",
	"T_Co_xlraster",
	"T_Co_xraster",
	"T_Co_yspace",
	"T_Co_xlspace",
	"T_Co_xspace",
	"T_Co_ybase",
	"T_Co_xbase",
	"T_Co_ymax",
	"T_Co_xmax",
	"T_Co_status",
	"T_Co_horizontal_order",
	"T_Co_level",
	"T_Co_shape",
	"T_Co_textmode",
	"T_Co_stretch",
	"T_Co_shrink",
	"T_Co_scaling",
	"T_Co_folding",
	"T_Co_loc",
	"T_Co_ydef",
	"T_Co_xdef",
	"T_Co_borderwidth",
	"T_Co_height",
	"T_Co_width",
	"T_Co_colorborder",
	"T_Co_textcolor",
	"T_Co_color",
	"T_Co_info3",
	"T_Co_info2",
	"T_Co_info1",
	"T_Co_label",
	"T_Co_title",
	"T_Co_constraint",
	"T_Co_back_edge",
	"T_Co_bent_near_edge",
	"T_Co_near_edge",
	"T_Co_edge",
	"T_Co_node",
	"T_Co_graph",
	"T_Co_foldedge_defaults",
	"T_Co_foldnode_defaults",
	"T_Co_edge_defaults",
	"T_Co_node_defaults",
	"T_Co_graph_attribute",
	"T_Co_graph_entry",
	""
};

/* Constructor Arities */

static const int yyconst_arity[] = {
	0   , /* index_val */
	1   , /* stern */
	2   , /* range */
	2   , /* index */
	2   , /* index_value */
	0   , /* string */
	0   , /* char */
	0   , /* float */
	0   , /* integer */
	0   , /* z */
	0   , /* y */
	0   , /* x */
	0   , /* right_neighbor */
	0   , /* left_neighbor */
	0   , /* lower_neighbor */
	0   , /* upper_neighbor */
	0   , /* right_margin */
	0   , /* left_margin */
	0   , /* bottom_margin */
	0   , /* top_margin */
	0   , /* equal_column */
	0   , /* equal_row */
	0   , /* equal_position */
	0   , /* behind */
	0   , /* in_font */
	0   , /* right */
	0   , /* left */
	0   , /* below */
	0   , /* above */
	0   , /* limit */
	0   , /* cluster */
	0   , /* xrange */
	0   , /* high_margin */
	0   , /* low_margin */
	0   , /* neighbors */
	0   , /* greater */
	0   , /* smaller */
	0   , /* equal */
	2   , /* string_array */
	1   , /* dimension */
	1   , /* name */
	1   , /* interval */
	1   , /* nodes */
	1   , /* size */
	0   , /* solid */
	0   , /* line */
	0   , /* none */
	0   , /* invisible */
	0   , /* dashed */
	0   , /* dotted */
	0   , /* continuous */
	1   , /* anchor */
	1   , /* linestyle */
	1   , /* barrowstyle */
	1   , /* arrowstyle */
	1   , /* barrowsize */
	1   , /* arrowsize */
	1   , /* barrowcolor */
	1   , /* arrowcolor */
	1   , /* arrowheight */
	1   , /* arrowwidth */
	1   , /* priority */
	1   , /* class */
	1   , /* thickness */
	1   , /* targetname */
	1   , /* sourcename */
	0   , /* around */
	0   , /* top */
	0   , /* bottom */
	0   , /* triangle */
	0   , /* ellipse */
	0   , /* rhomb */
	0   , /* box */
	0   , /* right_justify */
	0   , /* left_justify */
	0   , /* center */
	1   , /* iconstyle */
	1   , /* iconheight */
	1   , /* iconwidth */
	1   , /* anchorpoints */
	1   , /* iconfile */
	1   , /* bordercolor */
	1   , /* fontname */
	2   , /* constraint_attribute */
	2   , /* edge_attribute */
	2   , /* node_attribute */
	0   , /* free */
	0   , /* fixed */
	0   , /* fpfish */
	0   , /* pfish */
	0   , /* fcfish */
	0   , /* cfish */
	0   , /* medianbary */
	0   , /* barymedian */
	0   , /* median */
	0   , /* bary */
	0   , /* no */
	0   , /* yes */
	0   , /* grey */
	0   , /* manual */
	0   , /* every */
	0   , /* depthfirst */
	0   , /* minbackwards */
	0   , /* minoutdegree */
	0   , /* maxoutdegree */
	0   , /* minindegree */
	0   , /* maxindegree */
	0   , /* mindegree */
	0   , /* maxdegree */
	0   , /* mindepthslow */
	0   , /* maxdepthslow */
	0   , /* mindepth */
	0   , /* maxdepth */
	0   , /* tree */
	0   , /* constaints */
	0   , /* planar */
	0   , /* isi */
	0   , /* barycenter */
	0   , /* right_to_left */
	0   , /* left_to_right */
	0   , /* bottom_to_top */
	0   , /* top_to_bottom */
	0   , /* low */
	0   , /* high */
	1   , /* colindex */
	0   , /* yellowgreen */
	0   , /* yellow */
	0   , /* white */
	0   , /* turquoise */
	0   , /* red */
	0   , /* purple */
	0   , /* pink */
	0   , /* orchid */
	0   , /* orange */
	0   , /* magenta */
	0   , /* lilac */
	0   , /* lightyellow */
	0   , /* lightred */
	0   , /* lightmagenta */
	0   , /* lightgrey */
	0   , /* lightgreen */
	0   , /* lightcyan */
	0   , /* lightblue */
	0   , /* khaki */
	0   , /* green */
	0   , /* gold */
	0   , /* darkyellow */
	0   , /* darkred */
	0   , /* darkmagenta */
	0   , /* darkgrey */
	0   , /* darkgreen */
	0   , /* darkcyan */
	0   , /* darkblue */
	0   , /* cyan */
	0   , /* blue */
	0   , /* black */
	0   , /* aquamarine */
	1   , /* yscrollbar */
	1   , /* xscrollbar */
	1   , /* outputfunction */
	1   , /* inputfunction */
	1   , /* topsort */
	1   , /* layoutparameter */
	1   , /* include */
	1   , /* typename */
	1   , /* straight_max */
	1   , /* rubber_min */
	1   , /* rubber_max */
	1   , /* pendel_min */
	1   , /* pendel_max */
	1   , /* cross_min */
	1   , /* cross_max */
	1   , /* bend_max */
	1   , /* view_splines */
	1   , /* view_nodes */
	1   , /* view_edges */
	1   , /* view_method */
	1   , /* crossing_weight */
	1   , /* crossing_opt */
	1   , /* crossing_phase2 */
	1   , /* treefactor */
	1   , /* spreadlevel */
	1   , /* arrow_mode */
	1   , /* port_sharing */
	1   , /* node_alignment */
	1   , /* orientation */
	0   , /* dummy */
	0   , /* nonearedges */
	1   , /* smanhatten */
	1   , /* manhatten */
	1   , /* priophase */
	1   , /* straightphase */
	1   , /* hidesingles */
	1   , /* finetuning */
	1   , /* dirty_edge_label */
	1   , /* display_edge_label */
	1   , /* late_edge_label */
	1   , /* splinefactor */
	1   , /* nearfactor */
	1   , /* upfactor */
	1   , /* downfactor */
	1   , /* layoutfrequency */
	1   , /* layoutalgorithm */
	4   , /* colentry */
	2   , /* infoname */
	2   , /* classname */
	1   , /* hidden */
	1   , /* yraster */
	1   , /* xlraster */
	1   , /* xraster */
	1   , /* yspace */
	1   , /* xlspace */
	1   , /* xspace */
	1   , /* ybase */
	1   , /* xbase */
	1   , /* ymax */
	1   , /* xmax */
	1   , /* status */
	1   , /* horizontal_order */
	1   , /* level */
	1   , /* shape */
	1   , /* textmode */
	1   , /* stretch */
	1   , /* shrink */
	1   , /* scaling */
	1   , /* folding */
	2   , /* loc */
	1   , /* ydef */
	1   , /* xdef */
	1   , /* borderwidth */
	1   , /* height */
	1   , /* width */
	1   , /* colorborder */
	1   , /* textcolor */
	1   , /* color */
	1   , /* info3 */
	1   , /* info2 */
	1   , /* info1 */
	1   , /* label */
	1   , /* title */
	1   , /* constraint */
	1   , /* back_edge */
	1   , /* bent_near_edge */
	1   , /* near_edge */
	1   , /* edge */
	1   , /* node */
	1   , /* graph */
	1   , /* foldedge_defaults */
	1   , /* foldnode_defaults */
	1   , /* edge_defaults */
	1   , /* node_defaults */
	1   , /* graph_attribute */
	2   , /* graph_entry */
	0
};

/* Build Macros */

#define T_index_val(s0,l) BuildCont(T_Co_index_val,UnionLnum(s0),l)
#define T_stern(s0,l) BuildTree(T_Co_stern,1,UnionNum(0),l,s0)
#define T_range(s0,s1,l) BuildTree(T_Co_range,2,UnionNum(0),l,s0,s1)
#define T_index(s0,s1,l) BuildTree(T_Co_index,2,UnionNum(0),l,s0,s1)
#define T_index_value(s0,s1,l) BuildTree(T_Co_index_value,2,UnionNum(0),l,s0,s1)
#define T_string(s0,l) BuildCont(T_Co_string,UnionLnum(s0),l)
#define T_char(s0,l) BuildCont(T_Co_char,UnionByte(s0),l)
#define T_float(s0,l) BuildCont(T_Co_float,UnionLrealnum(s0),l)
#define T_integer(s0,l) BuildCont(T_Co_integer,UnionLnum(s0),l)
#define T_z(l) BuildCont(T_Co_z,UnionNum(0),l)
#define T_y(l) BuildCont(T_Co_y,UnionNum(0),l)
#define T_x(l) BuildCont(T_Co_x,UnionNum(0),l)
#define T_right_neighbor(l) BuildCont(T_Co_right_neighbor,UnionNum(0),l)
#define T_left_neighbor(l) BuildCont(T_Co_left_neighbor,UnionNum(0),l)
#define T_lower_neighbor(l) BuildCont(T_Co_lower_neighbor,UnionNum(0),l)
#define T_upper_neighbor(l) BuildCont(T_Co_upper_neighbor,UnionNum(0),l)
#define T_right_margin(l) BuildCont(T_Co_right_margin,UnionNum(0),l)
#define T_left_margin(l) BuildCont(T_Co_left_margin,UnionNum(0),l)
#define T_bottom_margin(l) BuildCont(T_Co_bottom_margin,UnionNum(0),l)
#define T_top_margin(l) BuildCont(T_Co_top_margin,UnionNum(0),l)
#define T_equal_column(l) BuildCont(T_Co_equal_column,UnionNum(0),l)
#define T_equal_row(l) BuildCont(T_Co_equal_row,UnionNum(0),l)
#define T_equal_position(l) BuildCont(T_Co_equal_position,UnionNum(0),l)
#define T_behind(l) BuildCont(T_Co_behind,UnionNum(0),l)
#define T_in_font(l) BuildCont(T_Co_in_font,UnionNum(0),l)
#define T_right(l) BuildCont(T_Co_right,UnionNum(0),l)
#define T_left(l) BuildCont(T_Co_left,UnionNum(0),l)
#define T_below(l) BuildCont(T_Co_below,UnionNum(0),l)
#define T_above(l) BuildCont(T_Co_above,UnionNum(0),l)
#define T_limit(l) BuildCont(T_Co_limit,UnionNum(0),l)
#define T_cluster(l) BuildCont(T_Co_cluster,UnionNum(0),l)
#define T_xrange(l) BuildCont(T_Co_xrange,UnionNum(0),l)
#define T_high_margin(l) BuildCont(T_Co_high_margin,UnionNum(0),l)
#define T_low_margin(l) BuildCont(T_Co_low_margin,UnionNum(0),l)
#define T_neighbors(l) BuildCont(T_Co_neighbors,UnionNum(0),l)
#define T_greater(l) BuildCont(T_Co_greater,UnionNum(0),l)
#define T_smaller(l) BuildCont(T_Co_smaller,UnionNum(0),l)
#define T_equal(l) BuildCont(T_Co_equal,UnionNum(0),l)
#define T_string_array(s0,s1,l) BuildTree(T_Co_string_array,2,UnionNum(0),l,s0,s1)
#define T_dimension(s0,l) BuildTree(T_Co_dimension,1,UnionNum(0),l,s0)
#define T_name(s0,l) BuildTree(T_Co_name,1,UnionNum(0),l,s0)
#define T_interval(s0,l) BuildTree(T_Co_interval,1,UnionNum(0),l,s0)
#define T_nodes(s0,l) BuildTree(T_Co_nodes,1,UnionNum(0),l,s0)
#define T_size(s0,l) BuildTree(T_Co_size,1,UnionNum(0),l,s0)
#define T_solid(l) BuildCont(T_Co_solid,UnionNum(0),l)
#define T_line(l) BuildCont(T_Co_line,UnionNum(0),l)
#define T_none(l) BuildCont(T_Co_none,UnionNum(0),l)
#define T_invisible(l) BuildCont(T_Co_invisible,UnionNum(0),l)
#define T_dashed(l) BuildCont(T_Co_dashed,UnionNum(0),l)
#define T_dotted(l) BuildCont(T_Co_dotted,UnionNum(0),l)
#define T_continuous(l) BuildCont(T_Co_continuous,UnionNum(0),l)
#define T_anchor(s0,l) BuildTree(T_Co_anchor,1,UnionNum(0),l,s0)
#define T_linestyle(s0,l) BuildTree(T_Co_linestyle,1,UnionNum(0),l,s0)
#define T_barrowstyle(s0,l) BuildTree(T_Co_barrowstyle,1,UnionNum(0),l,s0)
#define T_arrowstyle(s0,l) BuildTree(T_Co_arrowstyle,1,UnionNum(0),l,s0)
#define T_barrowsize(s0,l) BuildTree(T_Co_barrowsize,1,UnionNum(0),l,s0)
#define T_arrowsize(s0,l) BuildTree(T_Co_arrowsize,1,UnionNum(0),l,s0)
#define T_barrowcolor(s0,l) BuildTree(T_Co_barrowcolor,1,UnionNum(0),l,s0)
#define T_arrowcolor(s0,l) BuildTree(T_Co_arrowcolor,1,UnionNum(0),l,s0)
#define T_arrowheight(s0,l) BuildTree(T_Co_arrowheight,1,UnionNum(0),l,s0)
#define T_arrowwidth(s0,l) BuildTree(T_Co_arrowwidth,1,UnionNum(0),l,s0)
#define T_priority(s0,l) BuildTree(T_Co_priority,1,UnionNum(0),l,s0)
#define T_class(s0,l) BuildTree(T_Co_class,1,UnionNum(0),l,s0)
#define T_thickness(s0,l) BuildTree(T_Co_thickness,1,UnionNum(0),l,s0)
#define T_targetname(s0,l) BuildTree(T_Co_targetname,1,UnionNum(0),l,s0)
#define T_sourcename(s0,l) BuildTree(T_Co_sourcename,1,UnionNum(0),l,s0)
#define T_around(l) BuildCont(T_Co_around,UnionNum(0),l)
#define T_top(l) BuildCont(T_Co_top,UnionNum(0),l)
#define T_bottom(l) BuildCont(T_Co_bottom,UnionNum(0),l)
#define T_triangle(l) BuildCont(T_Co_triangle,UnionNum(0),l)
#define T_ellipse(l) BuildCont(T_Co_ellipse,UnionNum(0),l)
#define T_rhomb(l) BuildCont(T_Co_rhomb,UnionNum(0),l)
#define T_box(l) BuildCont(T_Co_box,UnionNum(0),l)
#define T_right_justify(l) BuildCont(T_Co_right_justify,UnionNum(0),l)
#define T_left_justify(l) BuildCont(T_Co_left_justify,UnionNum(0),l)
#define T_center(l) BuildCont(T_Co_center,UnionNum(0),l)
#define T_iconstyle(s0,l) BuildTree(T_Co_iconstyle,1,UnionNum(0),l,s0)
#define T_iconheight(s0,l) BuildTree(T_Co_iconheight,1,UnionNum(0),l,s0)
#define T_iconwidth(s0,l) BuildTree(T_Co_iconwidth,1,UnionNum(0),l,s0)
#define T_anchorpoints(s0,l) BuildTree(T_Co_anchorpoints,1,UnionNum(0),l,s0)
#define T_iconfile(s0,l) BuildTree(T_Co_iconfile,1,UnionNum(0),l,s0)
#define T_bordercolor(s0,l) BuildTree(T_Co_bordercolor,1,UnionNum(0),l,s0)
#define T_fontname(s0,l) BuildTree(T_Co_fontname,1,UnionNum(0),l,s0)
#define T_constraint_attribute(s0,s1,l) BuildTree(T_Co_constraint_attribute,2,UnionNum(0),l,s0,s1)
#define T_edge_attribute(s0,s1,l) BuildTree(T_Co_edge_attribute,2,UnionNum(0),l,s0,s1)
#define T_node_attribute(s0,s1,l) BuildTree(T_Co_node_attribute,2,UnionNum(0),l,s0,s1)
#define T_free(l) BuildCont(T_Co_free,UnionNum(0),l)
#define T_fixed(l) BuildCont(T_Co_fixed,UnionNum(0),l)
#define T_fpfish(l) BuildCont(T_Co_fpfish,UnionNum(0),l)
#define T_pfish(l) BuildCont(T_Co_pfish,UnionNum(0),l)
#define T_fcfish(l) BuildCont(T_Co_fcfish,UnionNum(0),l)
#define T_cfish(l) BuildCont(T_Co_cfish,UnionNum(0),l)
#define T_medianbary(l) BuildCont(T_Co_medianbary,UnionNum(0),l)
#define T_barymedian(l) BuildCont(T_Co_barymedian,UnionNum(0),l)
#define T_median(l) BuildCont(T_Co_median,UnionNum(0),l)
#define T_bary(l) BuildCont(T_Co_bary,UnionNum(0),l)
#define T_no(l) BuildCont(T_Co_no,UnionNum(0),l)
#define T_yes(l) BuildCont(T_Co_yes,UnionNum(0),l)
#define T_grey(l) BuildCont(T_Co_grey,UnionNum(0),l)
#define T_manual(l) BuildCont(T_Co_manual,UnionNum(0),l)
#define T_every(l) BuildCont(T_Co_every,UnionNum(0),l)
#define T_depthfirst(l) BuildCont(T_Co_depthfirst,UnionNum(0),l)
#define T_minbackwards(l) BuildCont(T_Co_minbackwards,UnionNum(0),l)
#define T_minoutdegree(l) BuildCont(T_Co_minoutdegree,UnionNum(0),l)
#define T_maxoutdegree(l) BuildCont(T_Co_maxoutdegree,UnionNum(0),l)
#define T_minindegree(l) BuildCont(T_Co_minindegree,UnionNum(0),l)
#define T_maxindegree(l) BuildCont(T_Co_maxindegree,UnionNum(0),l)
#define T_mindegree(l) BuildCont(T_Co_mindegree,UnionNum(0),l)
#define T_maxdegree(l) BuildCont(T_Co_maxdegree,UnionNum(0),l)
#define T_mindepthslow(l) BuildCont(T_Co_mindepthslow,UnionNum(0),l)
#define T_maxdepthslow(l) BuildCont(T_Co_maxdepthslow,UnionNum(0),l)
#define T_mindepth(l) BuildCont(T_Co_mindepth,UnionNum(0),l)
#define T_maxdepth(l) BuildCont(T_Co_maxdepth,UnionNum(0),l)
#define T_tree(l) BuildCont(T_Co_tree,UnionNum(0),l)
#define T_constaints(l) BuildCont(T_Co_constaints,UnionNum(0),l)
#define T_planar(l) BuildCont(T_Co_planar,UnionNum(0),l)
#define T_isi(l) BuildCont(T_Co_isi,UnionNum(0),l)
#define T_barycenter(l) BuildCont(T_Co_barycenter,UnionNum(0),l)
#define T_right_to_left(l) BuildCont(T_Co_right_to_left,UnionNum(0),l)
#define T_left_to_right(l) BuildCont(T_Co_left_to_right,UnionNum(0),l)
#define T_bottom_to_top(l) BuildCont(T_Co_bottom_to_top,UnionNum(0),l)
#define T_top_to_bottom(l) BuildCont(T_Co_top_to_bottom,UnionNum(0),l)
#define T_low(l) BuildCont(T_Co_low,UnionNum(0),l)
#define T_high(l) BuildCont(T_Co_high,UnionNum(0),l)
#define T_colindex(s0,l) BuildTree(T_Co_colindex,1,UnionNum(0),l,s0)
#define T_yellowgreen(l) BuildCont(T_Co_yellowgreen,UnionNum(0),l)
#define T_yellow(l) BuildCont(T_Co_yellow,UnionNum(0),l)
#define T_white(l) BuildCont(T_Co_white,UnionNum(0),l)
#define T_turquoise(l) BuildCont(T_Co_turquoise,UnionNum(0),l)
#define T_red(l) BuildCont(T_Co_red,UnionNum(0),l)
#define T_purple(l) BuildCont(T_Co_purple,UnionNum(0),l)
#define T_pink(l) BuildCont(T_Co_pink,UnionNum(0),l)
#define T_orchid(l) BuildCont(T_Co_orchid,UnionNum(0),l)
#define T_orange(l) BuildCont(T_Co_orange,UnionNum(0),l)
#define T_magenta(l) BuildCont(T_Co_magenta,UnionNum(0),l)
#define T_lilac(l) BuildCont(T_Co_lilac,UnionNum(0),l)
#define T_lightyellow(l) BuildCont(T_Co_lightyellow,UnionNum(0),l)
#define T_lightred(l) BuildCont(T_Co_lightred,UnionNum(0),l)
#define T_lightmagenta(l) BuildCont(T_Co_lightmagenta,UnionNum(0),l)
#define T_lightgrey(l) BuildCont(T_Co_lightgrey,UnionNum(0),l)
#define T_lightgreen(l) BuildCont(T_Co_lightgreen,UnionNum(0),l)
#define T_lightcyan(l) BuildCont(T_Co_lightcyan,UnionNum(0),l)
#define T_lightblue(l) BuildCont(T_Co_lightblue,UnionNum(0),l)
#define T_khaki(l) BuildCont(T_Co_khaki,UnionNum(0),l)
#define T_green(l) BuildCont(T_Co_green,UnionNum(0),l)
#define T_gold(l) BuildCont(T_Co_gold,UnionNum(0),l)
#define T_darkyellow(l) BuildCont(T_Co_darkyellow,UnionNum(0),l)
#define T_darkred(l) BuildCont(T_Co_darkred,UnionNum(0),l)
#define T_darkmagenta(l) BuildCont(T_Co_darkmagenta,UnionNum(0),l)
#define T_darkgrey(l) BuildCont(T_Co_darkgrey,UnionNum(0),l)
#define T_darkgreen(l) BuildCont(T_Co_darkgreen,UnionNum(0),l)
#define T_darkcyan(l) BuildCont(T_Co_darkcyan,UnionNum(0),l)
#define T_darkblue(l) BuildCont(T_Co_darkblue,UnionNum(0),l)
#define T_cyan(l) BuildCont(T_Co_cyan,UnionNum(0),l)
#define T_blue(l) BuildCont(T_Co_blue,UnionNum(0),l)
#define T_black(l) BuildCont(T_Co_black,UnionNum(0),l)
#define T_aquamarine(l) BuildCont(T_Co_aquamarine,UnionNum(0),l)
#define T_yscrollbar(s0,l) BuildTree(T_Co_yscrollbar,1,UnionNum(0),l,s0)
#define T_xscrollbar(s0,l) BuildTree(T_Co_xscrollbar,1,UnionNum(0),l,s0)
#define T_outputfunction(s0,l) BuildTree(T_Co_outputfunction,1,UnionNum(0),l,s0)
#define T_inputfunction(s0,l) BuildTree(T_Co_inputfunction,1,UnionNum(0),l,s0)
#define T_topsort(s0,l) BuildTree(T_Co_topsort,1,UnionNum(0),l,s0)
#define T_layoutparameter(s0,l) BuildTree(T_Co_layoutparameter,1,UnionNum(0),l,s0)
#define T_include(s0,l) BuildTree(T_Co_include,1,UnionNum(0),l,s0)
#define T_typename(s0,l) BuildTree(T_Co_typename,1,UnionNum(0),l,s0)
#define T_straight_max(s0,l) BuildTree(T_Co_straight_max,1,UnionNum(0),l,s0)
#define T_rubber_min(s0,l) BuildTree(T_Co_rubber_min,1,UnionNum(0),l,s0)
#define T_rubber_max(s0,l) BuildTree(T_Co_rubber_max,1,UnionNum(0),l,s0)
#define T_pendel_min(s0,l) BuildTree(T_Co_pendel_min,1,UnionNum(0),l,s0)
#define T_pendel_max(s0,l) BuildTree(T_Co_pendel_max,1,UnionNum(0),l,s0)
#define T_cross_min(s0,l) BuildTree(T_Co_cross_min,1,UnionNum(0),l,s0)
#define T_cross_max(s0,l) BuildTree(T_Co_cross_max,1,UnionNum(0),l,s0)
#define T_bend_max(s0,l) BuildTree(T_Co_bend_max,1,UnionNum(0),l,s0)
#define T_view_splines(s0,l) BuildTree(T_Co_view_splines,1,UnionNum(0),l,s0)
#define T_view_nodes(s0,l) BuildTree(T_Co_view_nodes,1,UnionNum(0),l,s0)
#define T_view_edges(s0,l) BuildTree(T_Co_view_edges,1,UnionNum(0),l,s0)
#define T_view_method(s0,l) BuildTree(T_Co_view_method,1,UnionNum(0),l,s0)
#define T_crossing_weight(s0,l) BuildTree(T_Co_crossing_weight,1,UnionNum(0),l,s0)
#define T_crossing_opt(s0,l) BuildTree(T_Co_crossing_opt,1,UnionNum(0),l,s0)
#define T_crossing_phase2(s0,l) BuildTree(T_Co_crossing_phase2,1,UnionNum(0),l,s0)
#define T_treefactor(s0,l) BuildTree(T_Co_treefactor,1,UnionNum(0),l,s0)
#define T_spreadlevel(s0,l) BuildTree(T_Co_spreadlevel,1,UnionNum(0),l,s0)
#define T_arrow_mode(s0,l) BuildTree(T_Co_arrow_mode,1,UnionNum(0),l,s0)
#define T_port_sharing(s0,l) BuildTree(T_Co_port_sharing,1,UnionNum(0),l,s0)
#define T_node_alignment(s0,l) BuildTree(T_Co_node_alignment,1,UnionNum(0),l,s0)
#define T_orientation(s0,l) BuildTree(T_Co_orientation,1,UnionNum(0),l,s0)
#define T_dummy(l) BuildCont(T_Co_dummy,UnionNum(0),l)
#define T_nonearedges(l) BuildCont(T_Co_nonearedges,UnionNum(0),l)
#define T_smanhatten(s0,l) BuildTree(T_Co_smanhatten,1,UnionNum(0),l,s0)
#define T_manhatten(s0,l) BuildTree(T_Co_manhatten,1,UnionNum(0),l,s0)
#define T_priophase(s0,l) BuildTree(T_Co_priophase,1,UnionNum(0),l,s0)
#define T_straightphase(s0,l) BuildTree(T_Co_straightphase,1,UnionNum(0),l,s0)
#define T_hidesingles(s0,l) BuildTree(T_Co_hidesingles,1,UnionNum(0),l,s0)
#define T_finetuning(s0,l) BuildTree(T_Co_finetuning,1,UnionNum(0),l,s0)
#define T_dirty_edge_label(s0,l) BuildTree(T_Co_dirty_edge_label,1,UnionNum(0),l,s0)
#define T_display_edge_label(s0,l) BuildTree(T_Co_display_edge_label,1,UnionNum(0),l,s0)
#define T_late_edge_label(s0,l) BuildTree(T_Co_late_edge_label,1,UnionNum(0),l,s0)
#define T_splinefactor(s0,l) BuildTree(T_Co_splinefactor,1,UnionNum(0),l,s0)
#define T_nearfactor(s0,l) BuildTree(T_Co_nearfactor,1,UnionNum(0),l,s0)
#define T_upfactor(s0,l) BuildTree(T_Co_upfactor,1,UnionNum(0),l,s0)
#define T_downfactor(s0,l) BuildTree(T_Co_downfactor,1,UnionNum(0),l,s0)
#define T_layoutfrequency(s0,l) BuildTree(T_Co_layoutfrequency,1,UnionNum(0),l,s0)
#define T_layoutalgorithm(s0,l) BuildTree(T_Co_layoutalgorithm,1,UnionNum(0),l,s0)
#define T_colentry(s0,s1,s2,s3,l) BuildTree(T_Co_colentry,4,UnionNum(0),l,s0,s1,s2,s3)
#define T_infoname(s0,s1,l) BuildTree(T_Co_infoname,2,UnionNum(0),l,s0,s1)
#define T_classname(s0,s1,l) BuildTree(T_Co_classname,2,UnionNum(0),l,s0,s1)
#define T_hidden(s0,l) BuildTree(T_Co_hidden,1,UnionNum(0),l,s0)
#define T_yraster(s0,l) BuildTree(T_Co_yraster,1,UnionNum(0),l,s0)
#define T_xlraster(s0,l) BuildTree(T_Co_xlraster,1,UnionNum(0),l,s0)
#define T_xraster(s0,l) BuildTree(T_Co_xraster,1,UnionNum(0),l,s0)
#define T_yspace(s0,l) BuildTree(T_Co_yspace,1,UnionNum(0),l,s0)
#define T_xlspace(s0,l) BuildTree(T_Co_xlspace,1,UnionNum(0),l,s0)
#define T_xspace(s0,l) BuildTree(T_Co_xspace,1,UnionNum(0),l,s0)
#define T_ybase(s0,l) BuildTree(T_Co_ybase,1,UnionNum(0),l,s0)
#define T_xbase(s0,l) BuildTree(T_Co_xbase,1,UnionNum(0),l,s0)
#define T_ymax(s0,l) BuildTree(T_Co_ymax,1,UnionNum(0),l,s0)
#define T_xmax(s0,l) BuildTree(T_Co_xmax,1,UnionNum(0),l,s0)
#define T_status(s0,l) BuildTree(T_Co_status,1,UnionNum(0),l,s0)
#define T_horizontal_order(s0,l) BuildTree(T_Co_horizontal_order,1,UnionNum(0),l,s0)
#define T_level(s0,l) BuildTree(T_Co_level,1,UnionNum(0),l,s0)
#define T_shape(s0,l) BuildTree(T_Co_shape,1,UnionNum(0),l,s0)
#define T_textmode(s0,l) BuildTree(T_Co_textmode,1,UnionNum(0),l,s0)
#define T_stretch(s0,l) BuildTree(T_Co_stretch,1,UnionNum(0),l,s0)
#define T_shrink(s0,l) BuildTree(T_Co_shrink,1,UnionNum(0),l,s0)
#define T_scaling(s0,l) BuildTree(T_Co_scaling,1,UnionNum(0),l,s0)
#define T_folding(s0,l) BuildTree(T_Co_folding,1,UnionNum(0),l,s0)
#define T_loc(s0,s1,l) BuildTree(T_Co_loc,2,UnionNum(0),l,s0,s1)
#define T_ydef(s0,l) BuildTree(T_Co_ydef,1,UnionNum(0),l,s0)
#define T_xdef(s0,l) BuildTree(T_Co_xdef,1,UnionNum(0),l,s0)
#define T_borderwidth(s0,l) BuildTree(T_Co_borderwidth,1,UnionNum(0),l,s0)
#define T_height(s0,l) BuildTree(T_Co_height,1,UnionNum(0),l,s0)
#define T_width(s0,l) BuildTree(T_Co_width,1,UnionNum(0),l,s0)
#define T_colorborder(s0,l) BuildTree(T_Co_colorborder,1,UnionNum(0),l,s0)
#define T_textcolor(s0,l) BuildTree(T_Co_textcolor,1,UnionNum(0),l,s0)
#define T_color(s0,l) BuildTree(T_Co_color,1,UnionNum(0),l,s0)
#define T_info3(s0,l) BuildTree(T_Co_info3,1,UnionNum(0),l,s0)
#define T_info2(s0,l) BuildTree(T_Co_info2,1,UnionNum(0),l,s0)
#define T_info1(s0,l) BuildTree(T_Co_info1,1,UnionNum(0),l,s0)
#define T_label(s0,l) BuildTree(T_Co_label,1,UnionNum(0),l,s0)
#define T_title(s0,l) BuildTree(T_Co_title,1,UnionNum(0),l,s0)
#define T_constraint(s0,l) BuildTree(T_Co_constraint,1,UnionNum(0),l,s0)
#define T_back_edge(s0,l) BuildTree(T_Co_back_edge,1,UnionNum(0),l,s0)
#define T_bent_near_edge(s0,l) BuildTree(T_Co_bent_near_edge,1,UnionNum(0),l,s0)
#define T_near_edge(s0,l) BuildTree(T_Co_near_edge,1,UnionNum(0),l,s0)
#define T_edge(s0,l) BuildTree(T_Co_edge,1,UnionNum(0),l,s0)
#define T_node(s0,l) BuildTree(T_Co_node,1,UnionNum(0),l,s0)
#define T_graph(s0,l) BuildTree(T_Co_graph,1,UnionNum(0),l,s0)
#define T_foldedge_defaults(s0,l) BuildTree(T_Co_foldedge_defaults,1,UnionNum(0),l,s0)
#define T_foldnode_defaults(s0,l) BuildTree(T_Co_foldnode_defaults,1,UnionNum(0),l,s0)
#define T_edge_defaults(s0,l) BuildTree(T_Co_edge_defaults,1,UnionNum(0),l,s0)
#define T_node_defaults(s0,l) BuildTree(T_Co_node_defaults,1,UnionNum(0),l,s0)
#define T_graph_attribute(s0,l) BuildTree(T_Co_graph_attribute,1,UnionNum(0),l,s0)
#define T_graph_entry(s0,s1,l) BuildTree(T_Co_graph_entry,2,UnionNum(0),l,s0,s1)


#line 60 "/RW/esprit/users/sander/src/PARSEGEN/parse.skel"


/* from scanner */

#ifdef ANSI_C
void init_lex(void);
int yylex(void);
#else
void init_lex();
int yylex();
#endif

static char message[1024];
 
/* for error messages */



#line 1441 "grammar.pgs"
static const char * const yytokname[] = {
"<start/end of input>$"
	,"error"
	,"$illegal."
	,"lexem ABOVE"
	,"lexem ANCHORPOINTS"
	,"lexem ANCHOR"
	,"lexem AQUAMARINE"
	,"lexem AROUND"
	,"lexem ARROWMODE"
	,"lexem ARROWHEIGHT"
	,"lexem ARROWWIDTH"
	,"lexem ARROWCOLOR"
	,"lexem ARROWSTYLE"
	,"lexem ARROWSIZE"
	,"lexem BARROWCOLOR"
	,"lexem BARROWSTYLE"
	,"lexem BARROWSIZE"
	,"lexem BACKEDGE"
	,"lexem BARYCENTER"
	,"lexem BARY"
	,"lexem BARYMEDIAN"
	,"lexem BEHIND"
	,"lexem BELOW"
	,"lexem BLACK"
	,"lexem BLUE"
	,"lexem BMAX"
	,"lexem BORDERCOLOR"
	,"lexem BORDERWIDTH"
	,"lexem BOTTOM_MARGIN"
	,"lexem BOTTOM_TO_TOP"
	,"lexem BOTTOM"
	,"lexem BOX"
	,"lexem BENTNEAREDGE"
	,"lexem CENTER"
	,"lexem CFISH"
	,"lexem CLASSNAME"
	,"lexem CLASS"
	,"lexem CLUSTER"
	,"lexem CMIN"
	,"lexem CMAX"
	,"lexem COLORENTRY"
	,"lexem COLOR"
	,"lexem CONSTRAINTS"
	,"lexem CONSTRAINT"
	,"lexem CONTINUOUS"
	,"lexem CROSSING_WEIGHT"
	,"lexem CROSSING_OPT"
	,"lexem CROSSING_P2"
	,"lexem CYAN"
	,"lexem DARKBLUE"
	,"lexem DARKCYAN"
	,"lexem DARKGREEN"
	,"lexem DARKGREY"
	,"lexem DARKMAGENTA"
	,"lexem DARKRED"
	,"lexem DARKYELLOW"
	,"lexem DASHED"
	,"lexem DFS"
	,"lexem DIMENSION"
	,"lexem DIRTY_EDGE_LABELS"
	,"lexem DISPLAY_EDGE_LABELS"
	,"lexem DOTTED"
	,"lexem EDGE1"
	,"lexem EDGE2"
	,"lexem EDGES"
	,"lexem ELLIPSE"
	,"lexem EQUAL_COLUMN"
	,"lexem EQUAL_POSITION"
	,"lexem EQUAL_ROW"
	,"lexem EQUAL"
	,"lexem EVERY"
	,"lexem FCFISH"
	,"lexem FPFISH"
	,"lexem FIXED"
	,"lexem FREE"
	,"lexem FINETUNING"
	,"lexem FOLDEDGE"
	,"lexem FOLDNODE"
	,"lexem FOLDING"
	,"lexem FONTNAME"
	,"lexem GOLD"
	,"lexem GRAPH"
	,"lexem GREATER"
	,"lexem GREEN"
	,"lexem GREY"
	,"lexem HEIGHT"
	,"lexem HIDESINGLES"
	,"lexem HIGH_MARGIN"
	,"lexem HIGH"
	,"lexem HIDDEN"
	,"lexem HORDER"
	,"lexem ICONFILE"
	,"lexem ICONHEIGHT"
	,"lexem ICONSTYLE"
	,"lexem ICONWIDTH"
	,"lexem INCLUDE"
	,"lexem INFONAME"
	,"lexem INFO1"
	,"lexem INFO2"
	,"lexem INFO3"
	,"lexem INPUTFUNCTION"
	,"lexem INTERVAL"
	,"lexem INVISIBLE"
	,"lexem IN_FRONT"
	,"lexem ISI"
	,"lexem KHAKI"
	,"lexem TEXTCOLOR"
	,"lexem LABEL"
	,"lexem LATE_LABELS"
	,"lexem LAYOUTALGORITHM"
	,"lexem LAYOUTFREQUENCY"
	,"lexem LAYOUTPARAMETER"
	,"lexem LAYOUTDOWNFACTOR"
	,"lexem LAYOUTUPFACTOR"
	,"lexem LAYOUTNEARFACTOR"
	,"lexem LAYOUTSPLINEFACTOR"
	,"lexem LEFT_JUSTIFY"
	,"lexem LEFT_MARGIN"
	,"lexem LEFT_NEIGHBOR"
	,"lexem LEFT_TO_RIGHT"
	,"lexem LEFT"
	,"lexem LEVEL"
	,"lexem VORDER"
	,"lexem LIGHTBLUE"
	,"lexem LIGHTCYAN"
	,"lexem LIGHTGREEN"
	,"lexem LIGHTGREY"
	,"lexem LIGHTMAGENTA"
	,"lexem LIGHTRED"
	,"lexem LIGHTYELLOW"
	,"lexem LILAC"
	,"lexem LIMIT"
	,"lexem LINE"
	,"lexem LINESTYLE"
	,"lexem LOC"
	,"lexem LOWER_NEIGHBOR"
	,"lexem LOW_MARGIN"
	,"lexem LOW"
	,"lexem MAGENTA"
	,"lexem MANHATTEN"
	,"lexem MANUAL"
	,"lexem MAXDEPTHSLOW"
	,"lexem MAXDEPTH"
	,"lexem MAXDEGREE"
	,"lexem MAXINDEGREE"
	,"lexem MAXOUTDEGREE"
	,"lexem MEDIAN"
	,"lexem MEDIANBARY"
	,"lexem MINDEPTHSLOW"
	,"lexem MINDEPTH"
	,"lexem MINDEGREE"
	,"lexem MININDEGREE"
	,"lexem MINOUTDEGREE"
	,"lexem MINBACK"
	,"lexem NAME"
	,"lexem NEAREDGE"
	,"lexem NEIGHBORS"
	,"lexem NEAREDGES"
	,"lexem NONEAREDGES"
	,"lexem NODE1"
	,"lexem NODE2"
	,"lexem NODES"
	,"lexem NODE_ALIGN"
	,"lexem NONE"
	,"lexem NO"
	,"lexem ORANGE"
	,"lexem ORCHID"
	,"lexem ORIENTATION"
	,"lexem OUTPUTFUNCTION"
	,"lexem PFISH"
	,"lexem PINK"
	,"lexem PLANAR"
	,"lexem PMIN"
	,"lexem PMAX"
	,"lexem PORTSHARING"
	,"lexem PRIORITYPHASE"
	,"lexem PRIORITY"
	,"lexem PURPLE"
	,"lexem RANGE"
	,"lexem RED"
	,"lexem RHOMB"
	,"lexem RIGHT_JUSTIFY"
	,"lexem RIGHT_MARGIN"
	,"lexem RIGHT_NEIGHBOR"
	,"lexem RIGHT_TO_LEFT"
	,"lexem RIGHT"
	,"lexem RMIN"
	,"lexem RMAX"
	,"lexem SCALING"
	,"lexem SHAPE"
	,"lexem SHRINK"
	,"lexem SMAX"
	,"lexem SMANHATTEN"
	,"lexem SIZE"
	,"lexem SMALLER"
	,"lexem SOLID"
	,"lexem SOURCENAME"
	,"lexem SPLINES"
	,"lexem SPREADLEVEL"
	,"lexem STATUS"
	,"lexem STRETCH"
	,"lexem STRAIGHTPHASE"
	,"lexem TARGETNAME"
	,"lexem TEXTMODE"
	,"lexem THICKNESS"
	,"lexem TITLE"
	,"lexem TOPSORT"
	,"lexem TOP_MARGIN"
	,"lexem TOP_TO_BOTTOM"
	,"lexem TOP"
	,"lexem TREE"
	,"lexem TREEFACTOR"
	,"lexem TRIANGLE"
	,"lexem TURQUOISE"
	,"lexem TYPENAME"
	,"lexem UPPER_NEIGHBOR"
	,"lexem VIEW"
	,"lexem WHITE"
	,"lexem WIDTH"
	,"lexem XBASE"
	,"lexem XMAX"
	,"lexem XRASTER"
	,"lexem XLRASTER"
	,"lexem XSCROLLBAR"
	,"lexem XSPACE"
	,"lexem XLSPACE"
	,"lexem YBASE"
	,"lexem YELLOWGREEN"
	,"lexem YELLOW"
	,"lexem YES"
	,"lexem YMAX"
	,"lexem YRASTER"
	,"lexem YSCROLLBAR"
	,"lexem YSPACE"
	,"lexem INT"
	,"lexem FLOAT"
	,"lexem CHAR"
	,"lexem STRING"
	,"'{'"
	,"'}'"
	,"':'"
	,"'x'"
	,"'y'"
	,"'z'"
	,"'*'"
	,"'['"
	,"'-'"
	,"']'"
	,"graph"
	,"graph_entry_list"
	,"graph_entry"
	,"graph_attribute"
	,"enum_color"
	,"enum_topsort"
	,"enum_orientation"
	,"enum_layoutalgorithm"
	,"enum_layoutfrequency"
	,"enum_status"
	,"enum_yes_no"
	,"enum_cross_weight"
	,"enum_view"
	,"enum_arrow_mode"
	,"foldnode_defaults"
	,"foldedge_defaults"
	,"node_defaults"
	,"edge_defaults"
	,"node"
	,"node_attribute_list"
	,"edge"
	,"nearedge"
	,"bentnearedge"
	,"backedge"
	,"edge_attribute_list"
	,"constraint"
	,"constraint_attribute_list"
	,"node_attribute"
	,"enum_textmode"
	,"enum_shape"
	,"enum_node_align"
	,"enum_iconstyle"
	,"edge_attribute"
	,"enum_linestyle"
	,"enum_arrowstyle"
	,"constraint_attribute"
	,"string_array"
	,"enum_name"
	,"enum_dimension"
	,"attribute_value"
	,"array_value"
	,"index_value_list"
	,"index_value"
	,"range"
	,"index"
	,"int_const"
	,"float_const"
	,"str_const"
	,""
};


#line 77 "/RW/esprit/users/sander/src/PARSEGEN/parse.skel"

#ifndef yyerror
#define yyerror(x) { \
	(void)sprintf(message,"unexpected %s (%s)", \
		 ((yychar<0)?"(?)":yytokname[YYTRANSLATE(yychar)]),x);  \
	(void)printf("Line %d Pos %d: %s !\n",line_nr,pos_nr,message);\
	nr_errors++;\
    }
#endif

#ifdef BISONGEN
#ifndef yylocate
#define yylocate(x) (&(x))
#endif
#endif

#ifdef YACCGEN
static YYLTYPE yystdlocation;

static YYLTYPE *yystdloc(void) 
{   yystdlocation->first_line = yystdlocation->last_line = line_nr; 
    yystdlocation->first_column = yystdlocation->last_column = pos_nr; 
    return(&yystdlocation);
}
#ifndef yylocate
#define yylocate(x) (yystdloc())
#endif
#endif /* YACCGEN */

#ifndef yysyntaxtree
#define yysyntaxtree char*
#endif

#define YY_NEVERNEEDED (@1)
#undef  YY_NEVERNEEDED 

/*-------------------------------------------------------------*/
/*               YACC or BISON Specification                   */
/*-------------------------------------------------------------*/



#line 1441 "grammar.pgs"

%}

%union { 
	unsigned char      byte;
	short int          snum;
	unsigned short int usnum;
	int                num;
	unsigned int       unum;
	long int           lnum;
	unsigned long int  ulnum;
	float              realnum;
	double             lrealnum;
	char              *string;
	yysyntaxtree       tree;
}

%type <tree> error
%type <tree> graph
%type <tree> graph_entry_list
%type <tree> graph_entry
%type <tree> graph_attribute
%type <tree> enum_color
%type <tree> enum_topsort
%type <tree> enum_orientation
%type <tree> enum_layoutalgorithm
%type <tree> enum_layoutfrequency
%type <tree> enum_status
%type <tree> enum_yes_no
%type <tree> enum_cross_weight
%type <tree> enum_view
%type <tree> enum_arrow_mode
%type <tree> foldnode_defaults
%type <tree> foldedge_defaults
%type <tree> node_defaults
%type <tree> edge_defaults
%type <tree> node
%type <tree> node_attribute_list
%type <tree> edge
%type <tree> nearedge
%type <tree> bentnearedge
%type <tree> backedge
%type <tree> edge_attribute_list
%type <tree> constraint
%type <tree> constraint_attribute_list
%type <tree> node_attribute
%type <tree> enum_textmode
%type <tree> enum_shape
%type <tree> enum_node_align
%type <tree> enum_iconstyle
%type <tree> edge_attribute
%type <tree> enum_linestyle
%type <tree> enum_arrowstyle
%type <tree> constraint_attribute
%type <tree> string_array
%type <tree> enum_name
%type <tree> enum_dimension
%type <tree> attribute_value
%type <tree> array_value
%type <tree> index_value_list
%type <tree> index_value
%type <tree> range
%type <tree> index
%type <tree> int_const
%type <tree> float_const
%type <tree> str_const
%type <lnum> LEX_INT
%type <lnum> LEX_STRING
%type <byte> LEX_CHAR
%type <lrealnum> LEX_FLOAT


%start graph 



%%


graph		: LEXWORD_GRAPH '{' graph_entry_list '}'		
					{
#line 833 "grammar.pgs"
		 $$ = REVERT($3); Syntax_Tree = $$; }
		;


graph_entry_list: graph_entry_list graph_entry			
					{
#line 838 "grammar.pgs"
		 $$ = T_graph_entry($2,$1,yylocate(@1));   }
		| graph_entry					
					{
#line 840 "grammar.pgs"
		 $$ = T_graph_entry($1,NULL,yylocate(@1)); }
		;


graph_entry	: graph_attribute	{
#line 844 "grammar.pgs"
		 $$ = T_graph_attribute($1,yylocate(@1)); }
		| node_defaults		{
#line 845 "grammar.pgs"
		 $$ = T_node_defaults($1,yylocate(@1));   }
		| edge_defaults		{
#line 846 "grammar.pgs"
		 $$ = T_edge_defaults($1,yylocate(@1));   }
		| foldnode_defaults	{
#line 847 "grammar.pgs"
		 $$ = T_foldnode_defaults($1,yylocate(@1));}
		| foldedge_defaults	{
#line 848 "grammar.pgs"
		 $$ = T_foldedge_defaults($1,yylocate(@1));}
		| graph			{
#line 849 "grammar.pgs"
		 $$ = T_graph($1,yylocate(@1));           }
		| node			{
#line 850 "grammar.pgs"
		 $$ = T_node($1,yylocate(@1));            }
		| edge			{
#line 851 "grammar.pgs"
		 $$ = T_edge($1,yylocate(@1));            }
		| nearedge		{
#line 852 "grammar.pgs"
		 $$ = T_near_edge($1,yylocate(@1));       }
		| bentnearedge		{
#line 853 "grammar.pgs"
		 $$ = T_bent_near_edge($1,yylocate(@1));  }
		| backedge		{
#line 854 "grammar.pgs"
		 $$ = T_back_edge($1,yylocate(@1));       }
		| constraint		{
#line 855 "grammar.pgs"
		 $$ = T_constraint($1,yylocate(@1));      }
		;


graph_attribute	: LEXWORD_TITLE ':' str_const	
					{
#line 860 "grammar.pgs"
		 $$ = T_title($3,yylocate(@1));              }
		| LEXWORD_LABEL ':' str_const	
					{
#line 862 "grammar.pgs"
		 $$ = T_label($3,yylocate(@1));              }
		| LEXWORD_INFO1 ':' str_const	
					{
#line 864 "grammar.pgs"
		 $$ = T_info1($3,yylocate(@1));              }
		| LEXWORD_INFO2 ':' str_const	
					{
#line 866 "grammar.pgs"
		 $$ = T_info2($3,yylocate(@1));              }
		| LEXWORD_INFO3 ':' str_const	
					{
#line 868 "grammar.pgs"
		 $$ = T_info3($3,yylocate(@1));              }
		| LEXWORD_COLOR ':' enum_color 
					{
#line 870 "grammar.pgs"
		 $$ = T_color($3,yylocate(@1));              }
		| LEXWORD_TEXTCOLOR ':'enum_color 
					{
#line 872 "grammar.pgs"
		 $$ = T_textcolor($3,yylocate(@1));          } 
                | LEXWORD_BORDERCOLOR ':'enum_color 
					{
#line 874 "grammar.pgs"
		 $$ = T_colorborder($3,yylocate(@1));        }
                | LEXWORD_WIDTH ':' int_const 
					{
#line 876 "grammar.pgs"
		 $$ = T_width($3,yylocate(@1));              }
                | LEXWORD_HEIGHT ':' int_const
					{
#line 878 "grammar.pgs"
		 $$ = T_height($3,yylocate(@1));             }
                | LEXWORD_BORDERWIDTH ':' int_const
					{
#line 880 "grammar.pgs"
		 $$ = T_borderwidth($3,yylocate(@1));        }
		| 'x' ':' int_const	{
#line 881 "grammar.pgs"
		 $$ = T_xdef($3,yylocate(@1));               }
		| 'y' ':' int_const	{
#line 882 "grammar.pgs"
		 $$ = T_ydef($3,yylocate(@1));               }
		| LEXWORD_LOC '{' 'x' ':' int_const 'y' ':' int_const '}'
					{
#line 884 "grammar.pgs"
		 $$ = T_loc($5,$8,yylocate(@1));       }        
		| LEXWORD_FOLDING ':' int_const
					{
#line 886 "grammar.pgs"
		 $$ = T_folding($3,yylocate(@1));            }
		| LEXWORD_SCALING ':' float_const	
					{
#line 888 "grammar.pgs"
		 $$ = T_scaling($3,yylocate(@1));            }
		| LEXWORD_SHRINK ':' int_const
					{
#line 890 "grammar.pgs"
		 $$ = T_shrink($3,yylocate(@1));             }
		| LEXWORD_STRETCH ':' int_const
					{
#line 892 "grammar.pgs"
		 $$ = T_stretch($3,yylocate(@1));            }
		| LEXWORD_TEXTMODE ':' enum_textmode		
					{
#line 894 "grammar.pgs"
		 $$ = T_textmode($3,yylocate(@1));           } 
		| LEXWORD_SHAPE ':' enum_shape
					{
#line 896 "grammar.pgs"
		 $$ = T_shape($3,yylocate(@1));    	       }        
                | LEXWORD_LEVEL ':' int_const 
					{
#line 898 "grammar.pgs"
		 $$ = T_level($3,yylocate(@1));              }
                | LEXWORD_VORDER ':' int_const 
					{
#line 900 "grammar.pgs"
		 $$ = T_level($3,yylocate(@1));              }
                | LEXWORD_HORDER ':' int_const 
					{
#line 902 "grammar.pgs"
		 $$ = T_horizontal_order($3,yylocate(@1));   }
                | LEXWORD_STATUS ':' enum_status			
					{
#line 904 "grammar.pgs"
		 $$ = T_status($3,yylocate(@1));             }

                | LEXWORD_XMAX ':' int_const	
					{
#line 907 "grammar.pgs"
		 $$ = T_xmax($3,yylocate(@1));               }
                | LEXWORD_YMAX ':' int_const	
					{
#line 909 "grammar.pgs"
		 $$ = T_ymax($3,yylocate(@1));               }
                | LEXWORD_XBASE ':' int_const	
					{
#line 911 "grammar.pgs"
		 $$ = T_xbase($3,yylocate(@1));              }
                | LEXWORD_YBASE ':' int_const	
					{
#line 913 "grammar.pgs"
		 $$ = T_ybase($3,yylocate(@1));              }
                | LEXWORD_XSPACE ':' int_const
					{
#line 915 "grammar.pgs"
		 $$ = T_xspace($3,yylocate(@1));             }
                | LEXWORD_XLSPACE ':' int_const
					{
#line 917 "grammar.pgs"
		 $$ = T_xlspace($3,yylocate(@1));            }
                | LEXWORD_YSPACE ':' int_const
					{
#line 919 "grammar.pgs"
		 $$ = T_yspace($3,yylocate(@1));             }
                | LEXWORD_XRASTER ':' int_const
					{
#line 921 "grammar.pgs"
		 $$ = T_xraster($3,yylocate(@1));            }
                | LEXWORD_XLRASTER ':' int_const
					{
#line 923 "grammar.pgs"
		 $$ = T_xlraster($3,yylocate(@1));           }
                | LEXWORD_YRASTER ':' int_const
					{
#line 925 "grammar.pgs"
		 $$ = T_yraster($3,yylocate(@1));            }
		| LEXWORD_INVISIBLE ':' int_const
					{
#line 927 "grammar.pgs"
		 $$ = T_hidden($3,yylocate(@1)); 	       }
		| LEXWORD_HIDDEN ':' int_const
					{
#line 929 "grammar.pgs"
		 $$ = T_hidden($3,yylocate(@1)); 	       }
		| LEXWORD_CLASSNAME int_const ':' str_const	
					{
#line 931 "grammar.pgs"
		 $$ = T_classname($2,$4,yylocate(@1));       }
		| LEXWORD_INFONAME int_const ':' str_const	
					{
#line 933 "grammar.pgs"
		 $$ = T_infoname($2,$4,yylocate(@1));        }
                | LEXWORD_COLORENTRY int_const ':' int_const int_const int_const 
					{
#line 935 "grammar.pgs"
		 $$ = T_colentry($2,$4,$5,$6,yylocate(@1));   }

                | LEXWORD_LAYOUTALGORITHM ':' enum_layoutalgorithm	
					{
#line 938 "grammar.pgs"
		 $$ = T_layoutalgorithm($3,yylocate(@1));    }
		| LEXWORD_LAYOUTFREQUENCY ':' enum_layoutfrequency	
					{
#line 940 "grammar.pgs"
		 $$ = T_layoutfrequency($3,yylocate(@1));    }
                | LEXWORD_LAYOUTDOWNFACTOR ':' int_const 
					{
#line 942 "grammar.pgs"
		 $$ = T_downfactor($3,yylocate(@1));         }
                | LEXWORD_LAYOUTUPFACTOR ':' int_const 
					{
#line 944 "grammar.pgs"
		 $$ = T_upfactor($3,yylocate(@1));           }
                | LEXWORD_LAYOUTNEARFACTOR ':' int_const 
					{
#line 946 "grammar.pgs"
		 $$ = T_nearfactor($3,yylocate(@1));         }
                | LEXWORD_LAYOUTSPLINEFACTOR ':' int_const
					{
#line 948 "grammar.pgs"
		 $$ = T_splinefactor($3,yylocate(@1));       }

                | LEXWORD_LATE_LABELS ':' enum_yes_no
					{
#line 951 "grammar.pgs"
		 $$ = T_late_edge_label($3,yylocate(@1));    }
                | LEXWORD_DISPLAY_EDGE_LABELS ':' enum_yes_no
					{
#line 953 "grammar.pgs"
		 $$ = T_display_edge_label($3,yylocate(@1)); }
                | LEXWORD_DIRTY_EDGE_LABELS ':' enum_yes_no
					{
#line 955 "grammar.pgs"
		 $$ = T_dirty_edge_label($3,yylocate(@1));   }
		| LEXWORD_FINETUNING ':' enum_yes_no 
				 	{
#line 957 "grammar.pgs"
		 $$ = T_finetuning($3,yylocate(@1));	       }
                | LEXWORD_HIDESINGLES  ':' enum_yes_no 
					{
#line 959 "grammar.pgs"
		 $$ = T_hidesingles($3,yylocate(@1));        }
		| LEXWORD_STRAIGHTPHASE ':'  enum_yes_no 
				 	{
#line 961 "grammar.pgs"
		 $$ = T_straightphase($3,yylocate(@1));	       }
		| LEXWORD_PRIORITYPHASE ':'  enum_yes_no 
				 	{
#line 963 "grammar.pgs"
		 $$ = T_priophase($3,yylocate(@1));	       }
		| LEXWORD_MANHATTEN ':'  enum_yes_no 
				 	{
#line 965 "grammar.pgs"
		 $$ = T_manhatten($3,yylocate(@1));	       }
		| LEXWORD_SMANHATTEN ':'  enum_yes_no 
				 	{
#line 967 "grammar.pgs"
		 $$ = T_smanhatten($3,yylocate(@1));	       }
		| LEXWORD_NONEAREDGES	{
#line 968 "grammar.pgs"
		 $$ = T_nonearedges(yylocate(@1));	       }
		| LEXWORD_NEAREDGES ':' LEXWORD_NO
					{
#line 970 "grammar.pgs"
		 $$ = T_nonearedges(yylocate(@1));	       }
		| LEXWORD_NEAREDGES ':' LEXWORD_YES 
					{
#line 972 "grammar.pgs"
		 $$ = T_dummy(yylocate(@1));	     	       }
                | LEXWORD_ORIENTATION ':' enum_orientation		
					{
#line 974 "grammar.pgs"
		 $$ = T_orientation($3,yylocate(@1));        }
                | LEXWORD_NODE_ALIGN ':' enum_node_align
					{
#line 976 "grammar.pgs"
		 $$ = T_node_alignment($3,yylocate(@1));     }
                | LEXWORD_PORTSHARING ':' enum_yes_no
					{
#line 978 "grammar.pgs"
		 $$ = T_port_sharing($3,yylocate(@1));       }
                | LEXWORD_ARROWMODE  ':' enum_arrow_mode
					{
#line 980 "grammar.pgs"
		 $$ = T_arrow_mode($3,yylocate(@1));         }

                | LEXWORD_SPREADLEVEL ':' int_const  
					{
#line 983 "grammar.pgs"
		 $$ = T_spreadlevel($3,yylocate(@1));        }
                | LEXWORD_TREEFACTOR ':' float_const  
					{
#line 985 "grammar.pgs"
		 $$ = T_treefactor($3,yylocate(@1));         }

                | LEXWORD_CROSSING_P2 ':' enum_yes_no 
					{
#line 988 "grammar.pgs"
		 $$ = T_crossing_phase2($3,yylocate(@1));    }
                | LEXWORD_CROSSING_OPT ':' enum_yes_no 
					{
#line 990 "grammar.pgs"
		 $$ = T_crossing_opt($3,yylocate(@1));       }
                | LEXWORD_CROSSING_WEIGHT ':' enum_cross_weight 
					{
#line 992 "grammar.pgs"
		 $$ = T_crossing_weight($3,yylocate(@1));    }

                | LEXWORD_VIEW ':'  enum_view 
					{
#line 995 "grammar.pgs"
		 $$ = T_view_method($3,yylocate(@1));       	}
                | LEXWORD_EDGES ':' enum_yes_no 
					{
#line 997 "grammar.pgs"
		 $$ = T_view_edges($3,yylocate(@1));       	}
                | LEXWORD_NODES ':' enum_yes_no 
					{
#line 999 "grammar.pgs"
		 $$ = T_view_nodes($3,yylocate(@1));       	}
		| LEXWORD_SPLINES ':'    enum_yes_no 
				 	{
#line 1001 "grammar.pgs"
		 $$ = T_view_splines($3,yylocate(@1));  	}

                | LEXWORD_BMAX ':' int_const 
					{
#line 1004 "grammar.pgs"
		 $$ = T_bend_max($3,yylocate(@1));   		}
                | LEXWORD_CMAX ':' int_const 
					{
#line 1006 "grammar.pgs"
		 $$ = T_cross_max($3,yylocate(@1));  		}
                | LEXWORD_CMIN ':' int_const 
					{
#line 1008 "grammar.pgs"
		 $$ = T_cross_min($3,yylocate(@1));  		}
                | LEXWORD_PMAX ':' int_const 
					{
#line 1010 "grammar.pgs"
		 $$ = T_pendel_max($3,yylocate(@1)); 		}
                | LEXWORD_PMIN ':' int_const 
					{
#line 1012 "grammar.pgs"
		 $$ = T_pendel_min($3,yylocate(@1));  	}
                | LEXWORD_RMAX ':' int_const 
					{
#line 1014 "grammar.pgs"
		 $$ = T_rubber_max($3,yylocate(@1)); 		}
                | LEXWORD_RMIN ':' int_const 
					{
#line 1016 "grammar.pgs"
		 $$ = T_rubber_min($3,yylocate(@1));  	}
                | LEXWORD_SMAX ':' int_const 
					{
#line 1018 "grammar.pgs"
		 $$ = T_straight_max($3,yylocate(@1)); 	}

                | LEXWORD_TYPENAME ':' str_const	
					{
#line 1021 "grammar.pgs"
		 $$ = T_typename($3,yylocate(@1));           }
                | LEXWORD_INCLUDE ':' str_const
			 		{
#line 1023 "grammar.pgs"
		 $$ = T_include($3,yylocate(@1));            }
		| LEXWORD_LAYOUTPARAMETER ':' array_value	
					{
#line 1025 "grammar.pgs"
		 $$ = T_layoutparameter($3,yylocate(@1));    }
		| LEXWORD_TOPSORT ':' enum_topsort	
					{
#line 1027 "grammar.pgs"
		 $$ = T_topsort($3,yylocate(@1));            }
                | LEXWORD_INPUTFUNCTION ':' str_const
					{
#line 1029 "grammar.pgs"
		 $$ = T_inputfunction($3,yylocate(@1));      }
                | LEXWORD_OUTPUTFUNCTION ':' str_const 
					{
#line 1031 "grammar.pgs"
		 $$ = T_outputfunction($3,yylocate(@1));     }
                | LEXWORD_XSCROLLBAR ':' int_const	
					{
#line 1033 "grammar.pgs"
		 $$ = T_xscrollbar($3,yylocate(@1));         }
                | LEXWORD_YSCROLLBAR ':' int_const
					{
#line 1035 "grammar.pgs"
		 $$ = T_yscrollbar($3,yylocate(@1));         }
		;


enum_color	: LEXWORD_AQUAMARINE	{
#line 1039 "grammar.pgs"
		 $$ = T_aquamarine(yylocate(@1));   }      
		| LEXWORD_BLACK		{
#line 1040 "grammar.pgs"
		 $$ = T_black(yylocate(@1));        }      
		| LEXWORD_BLUE		{
#line 1041 "grammar.pgs"
		 $$ = T_blue(yylocate(@1));         }      
		| LEXWORD_CYAN		{
#line 1042 "grammar.pgs"
		 $$ = T_cyan(yylocate(@1));         }      
		| LEXWORD_DARKBLUE	{
#line 1043 "grammar.pgs"
		 $$ = T_darkblue(yylocate(@1));     }      
		| LEXWORD_DARKCYAN	{
#line 1044 "grammar.pgs"
		 $$ = T_darkcyan(yylocate(@1));     }      
		| LEXWORD_DARKGREEN	{
#line 1045 "grammar.pgs"
		 $$ = T_darkgreen(yylocate(@1));    }      
		| LEXWORD_DARKGREY	{
#line 1046 "grammar.pgs"
		 $$ = T_darkgrey(yylocate(@1));     }      
		| LEXWORD_DARKMAGENTA	{
#line 1047 "grammar.pgs"
		 $$ = T_darkmagenta(yylocate(@1));  }    
		| LEXWORD_DARKRED	{
#line 1048 "grammar.pgs"
		 $$ = T_darkred(yylocate(@1));      }      
		| LEXWORD_DARKYELLOW	{
#line 1049 "grammar.pgs"
		 $$ = T_darkyellow(yylocate(@1));   }      
		| LEXWORD_GOLD		{
#line 1050 "grammar.pgs"
		 $$ = T_gold(yylocate(@1));         }      
		| LEXWORD_GREEN		{
#line 1051 "grammar.pgs"
		 $$ = T_green(yylocate(@1));        }      
		| LEXWORD_KHAKI		{
#line 1052 "grammar.pgs"
		 $$ = T_khaki(yylocate(@1));        }      
		| LEXWORD_LIGHTBLUE	{
#line 1053 "grammar.pgs"
		 $$ = T_lightblue(yylocate(@1));    }      
		| LEXWORD_LIGHTCYAN	{
#line 1054 "grammar.pgs"
		 $$ = T_lightcyan(yylocate(@1));    }      
		| LEXWORD_LIGHTGREEN	{
#line 1055 "grammar.pgs"
		 $$ = T_lightgreen(yylocate(@1));   }      
		| LEXWORD_LIGHTGREY	{
#line 1056 "grammar.pgs"
		 $$ = T_lightgrey(yylocate(@1));    }      
		| LEXWORD_LIGHTMAGENTA	{
#line 1057 "grammar.pgs"
		 $$ = T_lightmagenta(yylocate(@1)); }    
		| LEXWORD_LIGHTRED	{
#line 1058 "grammar.pgs"
		 $$ = T_lightred(yylocate(@1));     }      
		| LEXWORD_LIGHTYELLOW	{
#line 1059 "grammar.pgs"
		 $$ = T_lightyellow(yylocate(@1));  }    
		| LEXWORD_LILAC		{
#line 1060 "grammar.pgs"
		 $$ = T_lilac(yylocate(@1));        }      
		| LEXWORD_MAGENTA	{
#line 1061 "grammar.pgs"
		 $$ = T_magenta(yylocate(@1));      }      
		| LEXWORD_ORANGE	{
#line 1062 "grammar.pgs"
		 $$ = T_orange(yylocate(@1));       }      
		| LEXWORD_ORCHID	{
#line 1063 "grammar.pgs"
		 $$ = T_orchid(yylocate(@1));       }      
		| LEXWORD_PINK		{
#line 1064 "grammar.pgs"
		 $$ = T_pink(yylocate(@1));         }      
		| LEXWORD_PURPLE	{
#line 1065 "grammar.pgs"
		 $$ = T_purple(yylocate(@1));       }      
		| LEXWORD_RED		{
#line 1066 "grammar.pgs"
		 $$ = T_red(yylocate(@1));          }      
		| LEXWORD_TURQUOISE	{
#line 1067 "grammar.pgs"
		 $$ = T_turquoise(yylocate(@1));    }      
		| LEXWORD_WHITE		{
#line 1068 "grammar.pgs"
		 $$ = T_white(yylocate(@1));        }      
		| LEXWORD_YELLOW	{
#line 1069 "grammar.pgs"
		 $$ = T_yellow(yylocate(@1));       }      
		| LEXWORD_YELLOWGREEN	{
#line 1070 "grammar.pgs"
		 $$ = T_yellowgreen(yylocate(@1));  }   
                | int_const 		{
#line 1071 "grammar.pgs"
		 $$ = T_colindex($1,yylocate(@1));   }
		;


enum_topsort	: LEXWORD_HIGH		{
#line 1075 "grammar.pgs"
		 $$ = T_high(yylocate(@1)); 	       } 
		| LEXWORD_LOW 		{
#line 1076 "grammar.pgs"
		 $$ = T_low(yylocate(@1));          }
		;


enum_orientation: LEXWORD_TOP_TO_BOTTOM	{
#line 1080 "grammar.pgs"
		 $$ = T_top_to_bottom(yylocate(@1)); }
		| LEXWORD_BOTTOM_TO_TOP	{
#line 1081 "grammar.pgs"
		 $$ = T_bottom_to_top(yylocate(@1)); }
		| LEXWORD_LEFT_TO_RIGHT	{
#line 1082 "grammar.pgs"
		 $$ = T_left_to_right(yylocate(@1)); }
		| LEXWORD_RIGHT_TO_LEFT	{
#line 1083 "grammar.pgs"
		 $$ = T_right_to_left(yylocate(@1)); }
		;


enum_layoutalgorithm: 
		  LEXWORD_BARYCENTER 	{
#line 1088 "grammar.pgs"
		 $$ = T_barycenter(yylocate(@1));    }
		| LEXWORD_ISI 		{
#line 1089 "grammar.pgs"
		 $$ = T_isi(yylocate(@1));           }
		| LEXWORD_PLANAR 	{
#line 1090 "grammar.pgs"
		 $$ = T_planar(yylocate(@1));        }
		| LEXWORD_CONSTRAINTS 	{
#line 1091 "grammar.pgs"
		 $$ = T_constaints(yylocate(@1));    }

		| LEXWORD_TREE 		{
#line 1093 "grammar.pgs"
		 $$ = T_tree(yylocate(@1));          }
		| LEXWORD_MAXDEPTH	{
#line 1094 "grammar.pgs"
		 $$ = T_maxdepth(yylocate(@1));      }
		| LEXWORD_MINDEPTH	{
#line 1095 "grammar.pgs"
		 $$ = T_mindepth(yylocate(@1));      }
		| LEXWORD_MAXDEPTHSLOW	{
#line 1096 "grammar.pgs"
		 $$ = T_maxdepthslow(yylocate(@1));  }
		| LEXWORD_MINDEPTHSLOW	{
#line 1097 "grammar.pgs"
		 $$ = T_mindepthslow(yylocate(@1));  }
		| LEXWORD_MAXDEGREE   	{
#line 1098 "grammar.pgs"
		 $$ = T_maxdegree(yylocate(@1));     }
		| LEXWORD_MINDEGREE   	{
#line 1099 "grammar.pgs"
		 $$ = T_mindegree(yylocate(@1));     }
		| LEXWORD_MAXINDEGREE  	{
#line 1100 "grammar.pgs"
		 $$ = T_maxindegree(yylocate(@1));   }
		| LEXWORD_MININDEGREE  	{
#line 1101 "grammar.pgs"
		 $$ = T_minindegree(yylocate(@1));   }
		| LEXWORD_MAXOUTDEGREE 	{
#line 1102 "grammar.pgs"
		 $$ = T_maxoutdegree(yylocate(@1));  }
		| LEXWORD_MINOUTDEGREE 	{
#line 1103 "grammar.pgs"
		 $$ = T_minoutdegree(yylocate(@1));  }
		| LEXWORD_MINBACK 	{
#line 1104 "grammar.pgs"
		 $$ = T_minbackwards(yylocate(@1));  }
		| LEXWORD_DFS     	{
#line 1105 "grammar.pgs"
		 $$ = T_depthfirst(yylocate(@1));    }
		;


enum_layoutfrequency: 
		  LEXWORD_EVERY 	{
#line 1110 "grammar.pgs"
		 $$ = T_every(yylocate(@1)); 	}
		| LEXWORD_MANUAL 	{
#line 1111 "grammar.pgs"
		 $$ = T_manual(yylocate(@1)); 	}
		;


enum_status 	: LEXWORD_BLACK 	{
#line 1115 "grammar.pgs"
		 $$ = T_black(yylocate(@1)); 	}
		| LEXWORD_GREY 		{
#line 1116 "grammar.pgs"
		 $$ = T_grey(yylocate(@1)); 		}
		| LEXWORD_WHITE 	{
#line 1117 "grammar.pgs"
		 $$ = T_white(yylocate(@1)); 	}
		;


enum_yes_no	: LEXWORD_YES 		{
#line 1121 "grammar.pgs"
		 $$ = T_yes(yylocate(@1)); 		}
		| LEXWORD_NO 		{
#line 1122 "grammar.pgs"
		 $$ = T_no(yylocate(@1)); 		}
		;

enum_cross_weight : LEXWORD_BARY	{
#line 1125 "grammar.pgs"
		 $$ = T_bary(yylocate(@1)); 	       } 
		  | LEXWORD_MEDIAN	{
#line 1126 "grammar.pgs"
		 $$ = T_median(yylocate(@1));       }
		  | LEXWORD_BARYMEDIAN	{
#line 1127 "grammar.pgs"
		 $$ = T_barymedian(yylocate(@1));   }
		  | LEXWORD_MEDIANBARY	{
#line 1128 "grammar.pgs"
		 $$ = T_medianbary(yylocate(@1));   }
		  ;

enum_view	: LEXWORD_CFISH         {
#line 1131 "grammar.pgs"
		 $$ = T_cfish(yylocate(@1)); 	}
		| LEXWORD_FCFISH	{
#line 1132 "grammar.pgs"
		 $$ = T_fcfish(yylocate(@1));	}
		| LEXWORD_PFISH		{
#line 1133 "grammar.pgs"
		 $$ = T_pfish(yylocate(@1)); 	}
		| LEXWORD_FPFISH	{
#line 1134 "grammar.pgs"
		 $$ = T_fpfish(yylocate(@1));	}
		;

enum_arrow_mode	: LEXWORD_FIXED		{
#line 1137 "grammar.pgs"
		 $$ = T_fixed(yylocate(@1));         }
		| LEXWORD_FREE 		{
#line 1138 "grammar.pgs"
		 $$ = T_free(yylocate(@1));          }
		;

foldnode_defaults: LEXWORD_FOLDNODE node_attribute 	
					{
#line 1142 "grammar.pgs"
		 $$ = $2;              }
		;

foldedge_defaults: LEXWORD_FOLDEDGE edge_attribute 	
					{
#line 1146 "grammar.pgs"
		 $$ = $2;              }
		;

node_defaults	: LEXWORD_NODE1 node_attribute 	
					{
#line 1150 "grammar.pgs"
		 $$ = $2;              }
		;

edge_defaults   : LEXWORD_EDGE1 edge_attribute  
					{
#line 1154 "grammar.pgs"
		 $$ = $2;              }
                ;


node		: LEXWORD_NODE2 '{' node_attribute_list '}'	
					{
#line 1159 "grammar.pgs"
		 $$ = REVERT($3); }
		;

	
node_attribute_list: node_attribute_list node_attribute		
					{
#line 1164 "grammar.pgs"
		 $$ = T_node_attribute($2,$1,yylocate(@1));   }
		   | node_attribute				
					{
#line 1166 "grammar.pgs"
		 $$ = T_node_attribute($1,NULL,yylocate(@1)); }
		   ;


edge            : LEXWORD_EDGE2 '{' edge_attribute_list '}'        
					{
#line 1171 "grammar.pgs"
		 $$ = REVERT($3); }  
                ; 

nearedge	: LEXWORD_NEAREDGE '{' edge_attribute_list '}'
					{
#line 1175 "grammar.pgs"
		 $$ = REVERT($3); }  
                ; 

bentnearedge	: LEXWORD_BENTNEAREDGE '{' edge_attribute_list '}'
					{
#line 1179 "grammar.pgs"
		 $$ = REVERT($3); }  
                ; 

backedge	: LEXWORD_BACKEDGE '{' edge_attribute_list '}'
					{
#line 1183 "grammar.pgs"
		 $$ = REVERT($3); }  
                ; 

         
edge_attribute_list: edge_attribute_list edge_attribute     
		    			{
#line 1188 "grammar.pgs"
		 $$ = T_edge_attribute($2,$1,yylocate(@1));   }
                   | edge_attribute                             
					{
#line 1190 "grammar.pgs"
		 $$ = T_edge_attribute($1,NULL,yylocate(@1)); }
                   ; 


constraint 	: LEXWORD_CONSTRAINT '{' constraint_attribute_list '}'	
					{
#line 1195 "grammar.pgs"
		 $$ = REVERT($3); }  
                ; 
        
 
constraint_attribute_list: 
		  constraint_attribute_list constraint_attribute  	
					{
#line 1201 "grammar.pgs"
		 $$ = T_constraint_attribute($2,$1,yylocate(@1));   }
                | constraint_attribute     		     	
					{
#line 1203 "grammar.pgs"
		 $$ = T_constraint_attribute($1,NULL,yylocate(@1)); }
                   ; 


node_attribute	: LEXWORD_TITLE ':' str_const	
					{
#line 1208 "grammar.pgs"
		 $$ = T_title($3,yylocate(@1));        }        
		| LEXWORD_LABEL ':' str_const	
					{
#line 1210 "grammar.pgs"
		 $$ = T_label($3,yylocate(@1));        }        
		| LEXWORD_INFO1 ':' str_const	
					{
#line 1212 "grammar.pgs"
		 $$ = T_info1($3,yylocate(@1));        }        
		| LEXWORD_INFO2 ':' str_const	
					{
#line 1214 "grammar.pgs"
		 $$ = T_info2($3,yylocate(@1));        }        
		| LEXWORD_INFO3 ':' str_const	
					{
#line 1216 "grammar.pgs"
		 $$ = T_info3($3,yylocate(@1));        }        
                | LEXWORD_FONTNAME ':' str_const
					{
#line 1218 "grammar.pgs"
		 $$ = T_fontname($3,yylocate(@1));     }        
                | LEXWORD_COLOR ':' enum_color
					{
#line 1220 "grammar.pgs"
		 $$ = T_color($3,yylocate(@1));        }        
		| LEXWORD_TEXTCOLOR ':'enum_color 
					{
#line 1222 "grammar.pgs"
		 $$ = T_textcolor($3,yylocate(@1));    }        
                | LEXWORD_BORDERCOLOR ':'enum_color 
					{
#line 1224 "grammar.pgs"
		 $$ = T_bordercolor($3,yylocate(@1));  }        
                | LEXWORD_ICONFILE ':' str_const	
					{
#line 1226 "grammar.pgs"
		 $$ = T_iconfile($3,yylocate(@1));     }        
                | LEXWORD_ANCHORPOINTS ':' str_const
					{
#line 1228 "grammar.pgs"
		 $$ = T_anchorpoints($3,yylocate(@1)); }        
                | LEXWORD_TYPENAME ':' str_const	
					{
#line 1230 "grammar.pgs"
		 $$ = T_typename($3,yylocate(@1));     }        
		| LEXWORD_WIDTH ':' int_const	
					{
#line 1232 "grammar.pgs"
		 $$ = T_width($3,yylocate(@1));        }        
		| LEXWORD_HEIGHT ':' int_const	
					{
#line 1234 "grammar.pgs"
		 $$ = T_height($3,yylocate(@1));       }        
                | LEXWORD_BORDERWIDTH ':' int_const
					{
#line 1236 "grammar.pgs"
		 $$ = T_borderwidth($3,yylocate(@1));  }        
		| LEXWORD_LOC '{' 'x' ':' int_const 'y' ':' int_const '}'
					{
#line 1238 "grammar.pgs"
		 $$ = T_loc($5,$8,yylocate(@1));       }        
		| LEXWORD_FOLDING ':' int_const
					{
#line 1240 "grammar.pgs"
		 $$ = T_folding($3,yylocate(@1));      }        
		| LEXWORD_SCALING ':' float_const	
					{
#line 1242 "grammar.pgs"
		 $$ = T_scaling($3,yylocate(@1));            }
		| LEXWORD_SHRINK ':' int_const	
					{
#line 1244 "grammar.pgs"
		 $$ = T_shrink($3,yylocate(@1));       }        
		| LEXWORD_STRETCH ':' int_const
					{
#line 1246 "grammar.pgs"
		 $$ = T_stretch($3,yylocate(@1));      }        
                | LEXWORD_ICONWIDTH ':' int_const	
					{
#line 1248 "grammar.pgs"
		 $$ = T_iconwidth($3,yylocate(@1));    }        
                | LEXWORD_ICONHEIGHT ':' int_const
					{
#line 1250 "grammar.pgs"
		 $$ = T_iconheight($3,yylocate(@1));   }        
		| LEXWORD_TEXTMODE ':' enum_textmode		
					{
#line 1252 "grammar.pgs"
		 $$ = T_textmode($3,yylocate(@1));     }         
		| LEXWORD_ICONSTYLE ':' enum_iconstyle		
					{
#line 1254 "grammar.pgs"
		 $$ = T_iconstyle($3,yylocate(@1));    }        
		| LEXWORD_SHAPE ':' enum_shape
					{
#line 1256 "grammar.pgs"
		 $$ = T_shape($3,yylocate(@1));    	 }        
                | LEXWORD_LEVEL ':' int_const 
					{
#line 1258 "grammar.pgs"
		 $$ = T_level($3,yylocate(@1));        }
                | LEXWORD_VORDER ':' int_const 
					{
#line 1260 "grammar.pgs"
		 $$ = T_level($3,yylocate(@1));            }
                | LEXWORD_HORDER ':' int_const 
					{
#line 1262 "grammar.pgs"
		 $$ = T_horizontal_order($3,yylocate(@1)); }
		;

enum_textmode	: LEXWORD_CENTER 	{
#line 1265 "grammar.pgs"
		 $$ = T_center(yylocate(@1));        }
		| LEXWORD_LEFT_JUSTIFY 	{
#line 1266 "grammar.pgs"
		 $$ = T_left_justify(yylocate(@1));  }
		| LEXWORD_RIGHT_JUSTIFY	{
#line 1267 "grammar.pgs"
		 $$ = T_right_justify(yylocate(@1)); }
		;

enum_shape	: LEXWORD_BOX		{
#line 1270 "grammar.pgs"
		 $$ = T_box(yylocate(@1)); 		}
		| LEXWORD_RHOMB		{
#line 1271 "grammar.pgs"
		 $$ = T_rhomb(yylocate(@1));		}
		| LEXWORD_ELLIPSE	{
#line 1272 "grammar.pgs"
		 $$ = T_ellipse(yylocate(@1));	}
		| LEXWORD_TRIANGLE	{
#line 1273 "grammar.pgs"
		 $$ = T_triangle(yylocate(@1));	}
		;

enum_node_align	: LEXWORD_BOTTOM	{
#line 1276 "grammar.pgs"
		 $$ = T_bottom(yylocate(@1)); }
		| LEXWORD_TOP 		{
#line 1277 "grammar.pgs"
		 $$ = T_top(yylocate(@1));    }
		| LEXWORD_CENTER 	{
#line 1278 "grammar.pgs"
		 $$ = T_center(yylocate(@1)); }
		;

enum_iconstyle	: LEXWORD_BOTTOM	{
#line 1281 "grammar.pgs"
		 $$ = T_bottom(yylocate(@1)); }
		| LEXWORD_TOP 		{
#line 1282 "grammar.pgs"
		 $$ = T_top(yylocate(@1));    }
		| LEXWORD_AROUND 	{
#line 1283 "grammar.pgs"
		 $$ = T_around(yylocate(@1)); }
		;


edge_attribute  : LEXWORD_SOURCENAME ':' str_const
					{
#line 1288 "grammar.pgs"
		 $$ = T_sourcename($3,yylocate(@1));    }        
		| LEXWORD_TARGETNAME ':' str_const 
					{
#line 1290 "grammar.pgs"
		 $$ = T_targetname($3,yylocate(@1));    }       
                | LEXWORD_LABEL ':' str_const	
					{
#line 1292 "grammar.pgs"
		 $$ = T_label($3,yylocate(@1));         }       
		| LEXWORD_TEXTCOLOR ':'enum_color 
					{
#line 1294 "grammar.pgs"
		 $$ = T_textcolor($3,yylocate(@1));          } 
                | LEXWORD_FONTNAME ':' str_const
					{
#line 1296 "grammar.pgs"
		 $$ = T_fontname($3,yylocate(@1));      }       
                | LEXWORD_COLOR ':' enum_color
					{
#line 1298 "grammar.pgs"
		 $$ = T_color($3,yylocate(@1));         }       
                | LEXWORD_TYPENAME ':' str_const
					{
#line 1300 "grammar.pgs"
		 $$ = T_typename($3,yylocate(@1));      }       
		| LEXWORD_THICKNESS ':' int_const
					{
#line 1302 "grammar.pgs"
		 $$ = T_thickness($3,yylocate(@1));     }       
		| LEXWORD_CLASS ':' int_const	
					{
#line 1304 "grammar.pgs"
		 $$ = T_class($3,yylocate(@1));         }       
		| LEXWORD_PRIORITY ':' int_const
					{
#line 1306 "grammar.pgs"
		 $$ = T_priority($3,yylocate(@1));      }       
		| LEXWORD_ARROWWIDTH ':' int_const
					{
#line 1308 "grammar.pgs"
		 $$ = T_arrowwidth($3,yylocate(@1));    }       
                | LEXWORD_ARROWHEIGHT ':' int_const
					{
#line 1310 "grammar.pgs"
		 $$ = T_arrowheight($3,yylocate(@1));   }       
                | LEXWORD_ARROWCOLOR ':' enum_color
					{
#line 1312 "grammar.pgs"
		 $$ = T_arrowcolor($3,yylocate(@1));    }       
                | LEXWORD_BARROWCOLOR ':' enum_color
					{
#line 1314 "grammar.pgs"
		 $$ = T_barrowcolor($3,yylocate(@1));    }       
		| LEXWORD_ARROWSIZE ':' int_const
					{
#line 1316 "grammar.pgs"
		 $$ = T_arrowsize($3,yylocate(@1));     }       
		| LEXWORD_BARROWSIZE ':' int_const
					{
#line 1318 "grammar.pgs"
		 $$ = T_barrowsize($3,yylocate(@1));     }       
		| LEXWORD_ARROWSTYLE ':' enum_arrowstyle		
					{
#line 1320 "grammar.pgs"
		 $$ = T_arrowstyle($3,yylocate(@1));    }       
		| LEXWORD_BARROWSTYLE ':' enum_arrowstyle		
					{
#line 1322 "grammar.pgs"
		 $$ = T_barrowstyle($3,yylocate(@1));    }       
		| LEXWORD_LINESTYLE ':' enum_linestyle		
					{
#line 1324 "grammar.pgs"
		 $$ = T_linestyle($3,yylocate(@1));     }       
		| LEXWORD_ANCHOR ':' int_const
					{
#line 1326 "grammar.pgs"
		 $$ = T_anchor($3,yylocate(@1));        }
                | LEXWORD_HORDER ':' int_const 
					{
#line 1328 "grammar.pgs"
		 $$ = T_horizontal_order($3,yylocate(@1)); }
		; 


enum_linestyle	: LEXWORD_CONTINUOUS 	{
#line 1332 "grammar.pgs"
		 $$ = T_continuous(yylocate(@1)); }
		| LEXWORD_SOLID 	{
#line 1333 "grammar.pgs"
		 $$ = T_continuous(yylocate(@1)); }      
		| LEXWORD_DOTTED 	{
#line 1334 "grammar.pgs"
		 $$ = T_dotted(yylocate(@1));     }
		| LEXWORD_DASHED 	{
#line 1335 "grammar.pgs"
		 $$ = T_dashed(yylocate(@1));     }
		| LEXWORD_INVISIBLE     {
#line 1336 "grammar.pgs"
		 $$ = T_invisible(yylocate(@1));  } 
		;


enum_arrowstyle	: LEXWORD_NONE 		{
#line 1340 "grammar.pgs"
		 $$ = T_none(yylocate(@1));      }      
		| LEXWORD_LINE 		{
#line 1341 "grammar.pgs"
		 $$ = T_line(yylocate(@1));      }      
		| LEXWORD_SOLID 	{
#line 1342 "grammar.pgs"
		 $$ = T_solid(yylocate(@1));     }      
		;

constraint_attribute  : LEXWORD_TITLE ':' str_const 
					{
#line 1346 "grammar.pgs"
		 $$ = T_title($3,yylocate(@1));     }       
		| LEXWORD_PRIORITY ':' int_const
					{
#line 1348 "grammar.pgs"
		 $$ = T_priority($3,yylocate(@1));  }       
		| LEXWORD_SIZE ':' int_const	
					{
#line 1350 "grammar.pgs"
		 $$ = T_size($3,yylocate(@1));      }       
		| LEXWORD_NODES ':' '{' string_array '}'	
					{
#line 1352 "grammar.pgs"
		 $$ = T_nodes($4,yylocate(@1));     }       
		| LEXWORD_INTERVAL ':' array_value	
					{
#line 1354 "grammar.pgs"
		 $$ = T_interval($3,yylocate(@1));  }       
		| LEXWORD_NAME ':' enum_name			
					{
#line 1356 "grammar.pgs"
		 $$ = T_name($3,yylocate(@1));      }       
		| LEXWORD_DIMENSION ':' enum_dimension		
					{
#line 1358 "grammar.pgs"
		 $$ = T_dimension($3,yylocate(@1)); }       
		; 

string_array	: string_array str_const
					{
#line 1362 "grammar.pgs"
		 $$ = T_string_array($1,$2,yylocate(@1));    }       
		| str_const		{
#line 1363 "grammar.pgs"
		 $$ = T_string_array(NULL,$1,yylocate(@1));  }       
		;

enum_name	: LEXWORD_EQUAL 	{
#line 1366 "grammar.pgs"
		 $$ = T_equal(yylocate(@1));            }      
		| LEXWORD_SMALLER 	{
#line 1367 "grammar.pgs"
		 $$ = T_smaller(yylocate(@1));          }      
		| LEXWORD_GREATER 	{
#line 1368 "grammar.pgs"
		 $$ = T_greater(yylocate(@1));          }      
		| LEXWORD_NEIGHBORS 	{
#line 1369 "grammar.pgs"
		 $$ = T_neighbors(yylocate(@1));        }      
		| LEXWORD_LOW_MARGIN 	{
#line 1370 "grammar.pgs"
		 $$ = T_low_margin(yylocate(@1));       }      
		| LEXWORD_HIGH_MARGIN 	{
#line 1371 "grammar.pgs"
		 $$ = T_high_margin(yylocate(@1));      }      
		| LEXWORD_RANGE 	{
#line 1372 "grammar.pgs"
		 $$ = T_xrange(yylocate(@1));           }      
		| LEXWORD_CLUSTER 	{
#line 1373 "grammar.pgs"
		 $$ = T_cluster(yylocate(@1));          }      
		| LEXWORD_LIMIT 	{
#line 1374 "grammar.pgs"
		 $$ = T_limit(yylocate(@1));            }      
		| LEXWORD_ABOVE 	{
#line 1375 "grammar.pgs"
		 $$ = T_above(yylocate(@1));            }      
		| LEXWORD_BELOW	 	{
#line 1376 "grammar.pgs"
		 $$ = T_below(yylocate(@1));            }      
		| LEXWORD_LEFT 		{
#line 1377 "grammar.pgs"
		 $$ = T_left(yylocate(@1));             }      
		| LEXWORD_RIGHT 	{
#line 1378 "grammar.pgs"
		 $$ = T_right(yylocate(@1));            }      
		| LEXWORD_IN_FRONT 	{
#line 1379 "grammar.pgs"
		 $$ = T_in_font(yylocate(@1));          }      
		| LEXWORD_BEHIND 	{
#line 1380 "grammar.pgs"
		 $$ = T_behind(yylocate(@1));           }      
		| LEXWORD_EQUAL_POSITION{
#line 1381 "grammar.pgs"
		 $$ = T_equal_position(yylocate(@1));   }      
		| LEXWORD_EQUAL_ROW 	{
#line 1382 "grammar.pgs"
		 $$ = T_equal_row(yylocate(@1));        }      
		| LEXWORD_EQUAL_COLUMN 	{
#line 1383 "grammar.pgs"
		 $$ = T_equal_column(yylocate(@1));     }      
		| LEXWORD_TOP_MARGIN 	{
#line 1384 "grammar.pgs"
		 $$ = T_top_margin(yylocate(@1));       }      
		| LEXWORD_BOTTOM_MARGIN {
#line 1385 "grammar.pgs"
		 $$ = T_bottom_margin(yylocate(@1));    }      
		| LEXWORD_LEFT_MARGIN 	{
#line 1386 "grammar.pgs"
		 $$ = T_left_margin(yylocate(@1));      }      
		| LEXWORD_RIGHT_MARGIN 	{
#line 1387 "grammar.pgs"
		 $$ = T_right_margin(yylocate(@1));     }      
		| LEXWORD_UPPER_NEIGHBOR{
#line 1388 "grammar.pgs"
		 $$ = T_upper_neighbor(yylocate(@1));   }      
		| LEXWORD_LOWER_NEIGHBOR{
#line 1389 "grammar.pgs"
		 $$ = T_lower_neighbor(yylocate(@1));   }      
		| LEXWORD_LEFT_NEIGHBOR {
#line 1390 "grammar.pgs"
		 $$ = T_left_neighbor(yylocate(@1));    }      
		| LEXWORD_RIGHT_NEIGHBOR{
#line 1391 "grammar.pgs"
		 $$ = T_right_neighbor(yylocate(@1));   }      
		;

enum_dimension	: 'x' 			{
#line 1394 "grammar.pgs"
		 $$ = T_x(yylocate(@1)); }
		| 'y' 			{
#line 1395 "grammar.pgs"
		 $$ = T_y(yylocate(@1)); }
		| 'z' 			{
#line 1396 "grammar.pgs"
		 $$ = T_z(yylocate(@1)); }
		;

attribute_value	: LEX_INT       	{
#line 1399 "grammar.pgs"
		 $$ = T_integer($1,yylocate(@1)); }  
		| LEX_FLOAT         	{
#line 1400 "grammar.pgs"
		 $$ = T_float($1,yylocate(@1));   }
		| LEX_CHAR          	{
#line 1401 "grammar.pgs"
		 $$ = T_char($1,yylocate(@1));    } 
		| LEX_STRING   		{
#line 1402 "grammar.pgs"
		 $$ = T_string($1,yylocate(@1));  } 
		| array_value		{
#line 1403 "grammar.pgs"
		 $$ = $1; }
		;

array_value	: '{' index_value_list '}'
					{
#line 1407 "grammar.pgs"
		 $$ = REVERT($2); }
		;

index_value_list: index_value_list index_value
					{
#line 1411 "grammar.pgs"
		 $$ = T_index_value($2,$1,yylocate(@1));   }
		| index_value		{
#line 1412 "grammar.pgs"
		 $$ = T_index_value($1,NULL,yylocate(@1)); }
		;

index_value	: attribute_value 	{
#line 1415 "grammar.pgs"
		 $$ = $1;           }
		| index ':' attribute_value			
					{
#line 1417 "grammar.pgs"
		 $$ = T_index($1,$3,yylocate(@1)); }
		| range ':' attribute_value			
					{
#line 1419 "grammar.pgs"
		 $$ = T_range($1,$3,yylocate(@1)); }
		| '*' ':' attribute_value			
					{
#line 1421 "grammar.pgs"
		 $$ = T_stern($3,yylocate(@1));    }
		;

range		: '[' int_const '-' int_const ']'	
					{
#line 1425 "grammar.pgs"
		 $$ = T_range($2,$4,yylocate(@1)); }
		;

index		: LEX_INT		{
#line 1428 "grammar.pgs"
		 $$ = T_index_val($1,yylocate(@1));    }
		;

int_const	: LEX_INT		{
#line 1431 "grammar.pgs"
		 $$ = T_integer($1,yylocate(@1));  }
		;

float_const	: LEX_FLOAT		{
#line 1434 "grammar.pgs"
		 $$ = T_float($1,yylocate(@1));    }
		;

str_const	: LEX_STRING		{
#line 1437 "grammar.pgs"
		 $$ = T_string($1,yylocate(@1));   }
		;



%%



#line 147 "/RW/esprit/users/sander/src/PARSEGEN/parse.skel"

/*----------------------------*/
/* Main entry point of parser */
/*----------------------------*/

#ifndef yyparseinit
#define yyparseinit() /*NOTHING*/
#endif

yysyntaxtree  Syntax_Tree;

/*   returns the number of detected errors and binds the syntaxtree
 *   to the variable syntaxtree.
 */

#ifdef ANSI_C
int parse(void)
#else
int parse()
#endif
{
	nr_errors=0;
        init_lex();
	line_nr = 1;
	pos_nr = 0;
	yyparseinit();	
        yyparse();
#ifdef YYVALGLOBAL
        Syntax_Tree = yyval.tree;
#endif
        return(nr_errors);
}
 



#line 580 "grammar.pgs"


/*--------------------------------------------------------------*/
/*   Line directives                                            */
/*--------------------------------------------------------------*/
 
/*  Handle directive left by the C preprocessor, i.e.
 *
 *    # line 123 "foo.h"
 *    # line 125
 *    # 126 "foo.h" 2
 *
 *  et cetera.
 */
 

#ifdef ANSI_C 
void line_directive(char *text)
#else
void line_directive(text)
char *text;
#endif
{
        char *c,*d;

        c = d = text;
        while ((*c) && (*c!='"')) c++;
        while ((*d) && ((*d<'0') || (*d>'9'))) d++;
 
        if (d<c) { line_nr = atoi(d); pos_nr = 0; }
 
        if (*c) {
                c++;
                d = c;
                while ((*d) && (*d!='"')) d++;
                *d=0;
                strcpy(filename, c);
        }
}


/*--------------------------------------------------------------*/
/*   Translate escape sequences in strings                      */
/*--------------------------------------------------------------*/
 
/*  Translate escape sequences in strings. The result remains
 *  in text, because the result is shorter !
 *
 *   \\ -> \        \" -> "     \n -> CR    
 *
 *  et cetera.
 */
 
#ifdef ANSI_C 
void escape_transl(char *text)
#else
void escape_transl(text)
char *text;
#endif
{
        char *c,*d;
	int i;

        c = d = text;
	while (*c) {
		if (*c == '\\') {
			c++;
			switch (*c) {
#ifdef ANSI_C
			case 'a' : *d++ = '\a'; break;
#endif
			case 'b' : *d++ = '\b'; break;
			case 'f' : *d++ = '\f'; break;
			case 'n' : *d++ = '\n'; break;
			case 'r' : *d++ = '\r'; break;
			case 't' : *d++ = '\t'; break;
			case 'v' : *d++ = '\v'; break;
			case 'x' :
				   c++;
				   i = 0;
				   while (  ((*c>='0')&&(*c<='9')) 
					  ||((*c>='A')&&(*c<='F'))
					  ||((*c>='a')&&(*c<='f')) ) {
					if ((*c>='0')&&(*c<='9')) 
						i = i*16 + (*c)-'0'; 
					else if ((*c>='A')&&(*c<='F')) 
						i = i*16 + (*c)-'A'+10; 
					else if ((*c>='a')&&(*c<='f')) 
						i = i*16 + (*c)-'a'+10; 
					c++;
				   }
				   c--;
				   *d++ = i;
				   break;
			case '0' :
			case '1' :
			case '2' :
			case '3' :
			case '4' :
			case '5' :
			case '6' :
			case '7' :
				  i = (*c) - '0';
				  c++;
				  if ((*c>='0') && (*c<='7')) {
					i = i*8 +(*c)-'0';
				  	c++;
				  	if ((*c>='0') && (*c<='7')) {
						i = i*8 +(*c)-'0';
						c++;
					}
				  }
				  c--;
				  *d++ = i;
				  break;
			default : *d++ = *c; break;
			}
		}
		else *d++ = *c;
		c++;
	}
	*d = 0;
}


/*--------------------------------------------------------------*/
/*   Type conversions                                           */
/*--------------------------------------------------------------*/

/*
 *  Translate integer into string.
 */

static char myprivmessage[16000];  /* Please DON'T reuse this */

#ifdef ANSI_C 
char  *my_itoa(int x)
#else
char  *my_itoa(x)
int x;
#endif
{
	SPRINTF(myprivmessage,"%d",x);
	return(myprivmessage);
}

/*
 *  Translate integer into string.
 *  This is a little bit overcomplex, but in this way, it is more compatible.
 */

#ifdef ANSI_C 
long 	long_atoi(char *c)
#else
long	long_atoi(c)
char *c;
#endif
{
	long res, sign;

	res = 0;
	if (!c) return(0L);
	if (*c=='-')  { sign = -1L; c++; }
	else sign = 1L;
	while (*c) {
		switch (*c) {
		case '0': res = res * 10L;      break;
		case '1': res = res * 10L + 1L; break;
		case '2': res = res * 10L + 2L; break;
		case '3': res = res * 10L + 3L; break;
		case '4': res = res * 10L + 4L; break;
		case '5': res = res * 10L + 5L; break;
		case '6': res = res * 10L + 6L; break;
		case '7': res = res * 10L + 7L; break;
		case '8': res = res * 10L + 8L; break;
		case '9': res = res * 10L + 9L; break;
		default: return(sign * res);
		}
		c++;
	}
	return(sign * res);
}

 
/*====================================================================*/
/*   Errors and Warnings                                              */
/*====================================================================*/

/*
 *   syntaxerror prints an error message with position of the
 *   error place in the specification, and increments the counter of
 *   errors.
 */

static void fatal_error _PP((char *));

#ifdef ANSI_C 
void syntaxerror(int line, int pos, char *mesge)
#else
void syntaxerror(line,pos,mesge)
int line;
int pos;
char *mesge;
#endif
{
        strcpy(myprivmessage,mesge);
        if (islower(*myprivmessage))
                *myprivmessage = toupper(*myprivmessage);
        FPRINTF(stderr,"Syntax error (%s: l:%d p:%d): %s !\n",
                filename,line,pos,myprivmessage);
        nr_errors++;
        if (nr_errors>nr_max_errors)
                fatal_error("Too many syntax errors");
}


/*
 *   warning prints a warning with position of the problematic place
 *   in the specification, but does not increment the counter of
 *   errors.
 */

#ifdef ANSI_C 
void warning(int line, int pos, char *mesge)
#else
void warning(line,pos,mesge)
int line;
int pos;
char *mesge;
#endif
{
        strcpy(myprivmessage,mesge);
        if (islower(*myprivmessage))
                *myprivmessage = toupper(*myprivmessage);
        FPRINTF(stderr,"Warning (%s: l:%d p:%d): %s !\n",
                filename,line,pos,myprivmessage);
}


/*--------------------------------------------------------------*/





#line 182 "/RW/esprit/users/sander/src/PARSEGEN/parse.skel"



#line 1 "/RW/esprit/users/sander/src/PARSEGEN/stdpc.skel"

/*--------------------------------------------------------------------*/
/*  Standard Tree Construction Routines                               */
/*--------------------------------------------------------------------*/

#ifdef PARSEGENSTD 

#ifndef lint
static char *stdpc_id_string="$Id: stdpc.skel,v 1.12 1994/12/05 13:54:37 sander Exp sander $";
#endif


#include <stdio.h>
#include <malloc.h>
#ifdef ANSI_C
#include <stdarg.h>
#else
#include <varargs.h>
#endif

/*--------------------------------------------------------------------*/
/* Fatal error: exit with message                                     */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
static void fatal_error(char *message)
#else
static void fatal_error(message)
char *message;
#endif
{
        (void)fprintf(stderr,"Fatal error: %s !\n",message);
        (void)fprintf(stderr,"Aborted !\n");
        exit(-1);
}

/*--------------------------------------------------------------------*/
/* Memory allocation for syntax tree nodes                            */
/*--------------------------------------------------------------------*/

#ifndef ALIGN
#define ALIGN 8
#define IALIGN (ALIGN-1)
#endif

#ifndef PARSEBLOCKSIZE
#define PARSEBLOCKSIZE 10000
#endif


/*   The following in invisible from outside:        
 *   The heap consists of a list of memory blocks of size parseheapsize.
 *   The parseheap is the actual memory block.
 */ 

static yysyntaxtree parseheap = (yysyntaxtree)0;  /* the heap */ 
static yysyntaxtree parseheapstart;               /* the base */
static yysyntaxtree parseheaptop;                 /* the top  */
static yysyntaxtree parseheapend;                 /* the end  */
static int parseheapsize = PARSEBLOCKSIZE;     /* the size of one block */


#ifdef ANSI_C
static void alloc_block(void)
#else
static void alloc_block()
#endif
{
        yysyntaxtree help, *help2;

	help =(yysyntaxtree)malloc(parseheapsize*sizeof(struct stree_node));
        if (!help) fatal_error("memory exhausted");
	help2  = (yysyntaxtree *)help;
	*help2 = (yysyntaxtree)parseheap;
	parseheap = help;
	parseheapstart = parseheaptop =
		(yysyntaxtree)((long)parseheap + (long)sizeof(yysyntaxtree));
	parseheapend = parseheap;
	parseheapend += (parseheapsize-2);
        if ((long)parseheaptop&IALIGN) 
		parseheaptop = (yysyntaxtree)
			(((long)parseheaptop+(long)IALIGN)&(long)(~IALIGN));
}


/*  allocate x bytes */

#ifdef ANSI_C
static yysyntaxtree parsemalloc(int x)
#else
static yysyntaxtree parsemalloc(x)
int x;
#endif
{
        yysyntaxtree help;
        int  y;

	if (!parseheap) alloc_block();

        y = x;
        if (y&IALIGN) y = (y+IALIGN)&(~IALIGN);

        help = parseheaptop;
        parseheaptop = (yysyntaxtree)((long)parseheaptop+(long)y);

        if (parseheaptop > parseheapend) {

		/* heap too small -> allocate new heap block */

		alloc_block();
                help = parseheaptop;
                parseheaptop = (yysyntaxtree)((long)parseheaptop+(long)y);
        	if (parseheaptop > parseheapend) 
			fatal_error("syntax tree node too large");
        }
        return (help);
}


/* allocate yysyntaxtree node with x sons */

#ifdef ANSI_C
static yysyntaxtree st_malloc(int x)
#else
static yysyntaxtree st_malloc(x)
int x;
#endif
{
        yysyntaxtree help;

        help =parsemalloc(sizeof(struct stree_node)+x*sizeof(yysyntaxtree));
        return (help);
}


/* global allocate x bytes */

#ifdef ANSI_C
char * ParseMalloc(int x)
#else
char * ParseMalloc(x)
int x;
#endif
{
	return((char *)parsemalloc(x));
}

/* global deallocate the complete syntax tree heap */

static union special *stdunion = 0;

#ifdef ANSI_C
void ParseFree(void)
#else
void ParseFree()
#endif
{
        yysyntaxtree help, help2;

	help = parseheap;
	while (help) {
		help2 = *(yysyntaxtree *)help;
		(void)free((char *)help);
		help = help2;
	}	

	parseheap = (yysyntaxtree)0;
	stdunion = 0;
}
 
/*--------------------------------------------------------------------*/
/* Create unions for syntax tree nodes                                */
/*--------------------------------------------------------------------*/


#ifdef ANSI_C
static void freeunion(union special *x)
#else
static void freeunion(x)
union special *x;
#endif
{
	x->string = (char *)stdunion;
	stdunion = x;	
}

#ifdef ANSI_C
static union special *nextunion(void)
#else
static union special *nextunion()
#endif
{
	union special *help;
	if (!stdunion) {
        	stdunion = (union special *)
				parsemalloc(sizeof(union special));
		stdunion->string = 0;
	}
	help = stdunion;
	stdunion = (union special *)stdunion->string;
	return(help);
}

#ifdef ANSI_C
union special *UnionByte(unsigned char x)
#else
union special *UnionByte(x)
unsigned char x;
#endif
{
	union special *help;

	help = nextunion();
	help->byte = x;
	return(help);
}

#ifdef ANSI_C
union special *UnionSnum(short int x)
#else
union special *UnionSnum(x)
short int x;
#endif
{
	union special *help;

	help = nextunion();
	help->snum = x;
	return(help);
}

#ifdef ANSI_C
union special *UnionUsnum(unsigned short int x)
#else
union special *UnionUsnum(x)
unsigned short int x;
#endif
{
	union special *help;

	help = nextunion();
	help->usnum = x;
	return(help);
}

#ifdef ANSI_C
union special *UnionNum(int x)
#else
union special *UnionNum(x)
int x;
#endif
{
	union special *help;

	help = nextunion();
	help->num = x;
	return(help);     
}

#ifdef ANSI_C
union special *UnionUnum(unsigned int x)
#else
union special *UnionUnum(x)
unsigned int x;
#endif
{
	union special *help;

	help = nextunion();
	help->unum = x;
	return(help);     
}

#ifdef ANSI_C
union special *UnionLnum(long int x)
#else
union special *UnionLnum(x)
long int x;
#endif
{
	union special *help;

	help = nextunion();
	help->lnum = x;
	return(help);     
}

#ifdef ANSI_C
union special *UnionUlnum(unsigned long int x)
#else
union special *UnionUlnum(x)
unsigned long int x;
#endif
{
	union special *help;

	help = nextunion();
	help->ulnum = x;
	return(help);     
}

#ifdef ANSI_C
union special *UnionRealnum(float x)
#else
union special *UnionRealnum(x)
float x;
#endif
{
	union special *help;

	help = nextunion();
	help->realnum = x;
	return(help);     
}

#ifdef ANSI_C
union special *UnionLrealnum(double x)
#else
union special *UnionLrealnum(x)
double x;
#endif
{
	union special *help;

	help = nextunion();
	help->lrealnum = x;
	return(help);     
}

#ifdef ANSI_C
union special *UnionString(char *x)
#else
union special *UnionString(x)
char *x;
#endif
{
	union special *help;

	help = nextunion();
	help->string = x;
	return(help);     
}


/*--------------------------------------------------------------------*/
/* Build syntax tree nodes                                            */
/*--------------------------------------------------------------------*/

/* Table for varargs */

static yysyntaxtree TreeTab[1024];

#ifdef USERFTYPE
#ifndef USERFINIT
#define USERFINIT ((USERFTYPE)0)
#endif
#endif

/* without sons */

#ifdef ANSI_C
syntaxtree BuildCont(int mtag,union special *x,YYLTYPE *l)
#else
syntaxtree BuildCont(mtag,x,l)
int mtag;
union special *x;
YYLTYPE *l;
#endif
{
        yysyntaxtree help;
        help = st_malloc(1);

	__yy_bcopy(x,&help->contents, sizeof(union special));
	freeunion(x);
	tag(help)          = mtag;
	xfirst_line(help)   =l->first_line;
	xfirst_column(help) =l->first_column;
	xlast_line(help)    =l->last_line;
	xlast_column(help)  =l->last_column;
	xfather(help)       =(yysyntaxtree)0;
#ifdef USERFTYPE
	user_field(help)    =USERFINIT; 
#endif

	son1(help) = (yysyntaxtree)0; 

        return(help);
}

/* with sons */

#ifdef ANSI_C
yysyntaxtree BuildTree(int mtag,int len,union special *x,YYLTYPE *l, ...)
#else
yysyntaxtree BuildTree(va_alist)
va_dcl
#endif
{
	int i,j;
	va_list pvar;
        yysyntaxtree help;

#ifndef ANSI_C
	int mtag;
	int len;
	union special *x;
	YYLTYPE *l;
	va_start(pvar);
#endif

#ifdef ANSI_C
	va_start(pvar,l);
#endif

#ifndef ANSI_C
	mtag = va_arg(pvar, int);
	len = va_arg(pvar, int);
	x   = va_arg(pvar, union special *);
	l   = va_arg(pvar, YYLTYPE *);
#endif
 
	i = 0;
	help = va_arg(pvar, yysyntaxtree);
	while (i < len) {
		TreeTab[i++] = help;
		help = va_arg(pvar, yysyntaxtree);
	}
	va_end(pvar);

        help = st_malloc((i<1?1:i));

	__yy_bcopy(x,&help->contents, sizeof(union special));
	freeunion(x);
	tag(help)          = mtag;
	xfirst_line(help)   =l->first_line;
	xfirst_column(help) =l->first_column;
	xlast_line(help)    =l->last_line;
	xlast_column(help)  =l->last_column;
	xfather(help)       =(yysyntaxtree)0;
#ifdef USERFTYPE
	user_field(help)    =USERFINIT; 
#endif

	for (j=1; j<=i; j++) {
		son(help,j) = TreeTab[j-1]; 
		if (TreeTab[j-1]!=(yysyntaxtree)0)
			xfather(TreeTab[j-1]) = help;
	}
        return(help);
}


/* copy syntax tree */

#ifdef ANSI_C
yysyntaxtree Copy(yysyntaxtree x)
#else
yysyntaxtree Copy(x)
yysyntaxtree x;
#endif
{
	register int j,len;
        yysyntaxtree help; 

	if (!x) return(x);
	len = nr_of_sons(x);
        help = st_malloc((len<1?1:len));

	__yy_bcopy(&x->contents,&help->contents, sizeof(union special));
	tag(help)          = tag(x);
	xfirst_line(help)   = xfirst_line(x);
	xfirst_column(help) = xfirst_column(x);
	xlast_line(help)    = xlast_line(x);
	xlast_column(help)  = xlast_column(x);
	xfather(help)       = (yysyntaxtree)0;
#ifdef USERFTYPE
	user_field(help)    =user_field(x); 
#endif
	son1(help) = (yysyntaxtree)0; 

	for (j=1; j<=len; j++) {
		son(help,j) = Copy(son(x,j)); 
		if (son(help,j))
			xfather(son(help,j)) = help; 
	}
        return(help);
}

/* revert list */

#ifdef ANSI_C
yysyntaxtree Revert(yysyntaxtree list)
#else
yysyntaxtree Revert(list)
yysyntaxtree list;
#endif
{
        yysyntaxtree last, act, next; 

	last = (yysyntaxtree)0;
	act  = list;
	while (act) {
		next = son2(act);
		son2(act) = last;
		if (last) xfather(last)=act;
		last = act;	
		act = next;
	}
	if (last) xfather(last)=(yysyntaxtree)0;
        return(last);
}

/*--------------------------------------------------------------------*/
/* yield constructor name                                             */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
const char *ConstructorName(int i)
#else
const char *ConstructorName(i)
int i;
#endif
{
	return(yyconst_name[i]);
}

/*--------------------------------------------------------------------*/
/* yield constructor arity                                            */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
int ConstructorArity(int i)
#else
int ConstructorArity(i)
int i;
#endif
{
	return(yyconst_arity[i]);
}


#endif /* PARSEGENSTD */

/*--------------------------------------------------------------------*/



#line 1441 "grammar.pgs"
