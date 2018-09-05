%{


#line 2 "/RW/esprit/users/sander/src/PARSEGEN/scan.skel"

/*--------------------------------------------------------------------*/
/*            A flex scanner specification made by parsegen           */
/*--------------------------------------------------------------------*/
 
#ifndef lint
static char *scanskel_id_string="$Id: scan.skel,v 1.6 1994/04/13 10:23:44 sander Exp sander $";
#endif




#line 32000 "/RW/esprit/users/sander/src/PARSEGEN/parse.skel"
typedef struct stree_node *syntaxtree;
#undef yysyntaxtree
#define yysyntaxtree syntaxtree


#line 580 "grammar.pgs"

#define BISONGEN
#undef  YACCGEN

#include <stdio.h>

#include <string.h>

#include "y.tab.h"


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
 



#line 580 "grammar.pgs"

#ifdef ANSI_C
char * ParseMalloc(int x);
#else
char * ParseMalloc();
#endif
#undef PARSEGENSTD
#define PARSEGENSTD


#line 1 "/RW/esprit/users/sander/src/PARSEGEN/stdth.skel"
 
#ifndef STDHASH
#define STDHASH

/* $Id: stdth.skel,v 1.3 1994/01/07 19:35:32 sander Exp sander $ */

#undef  HASHGENSTD
#define HASHGENSTD


/*--------------------------------------------------------------------*/
/*  Standard Hash Table Routines                                      */
/*--------------------------------------------------------------------*/

/* Global Variables */
/*------------------*/

extern long   table_size;

#ifndef PARSEGENSTD

#ifndef ALIGN
#define ALIGN 8
#define IALIGN (ALIGN-1)
#endif
#ifndef STRINGBLOCKSIZE
#define STRINGBLOCKSIZE 5000
#endif

#ifdef ANSI_C
char *StringHeapMalloc(int x);
void StringHeapFree(void);
else
char *StringHeapMalloc();
void StringHeapFree();
#endif

#endif /* PARSEGENSTD */

#ifndef hash_size
#define hash_size 211
#endif
#ifndef hashtable_size
#define hashtable_size 10000L
#endif


#ifdef ANSI_C
void FreeHash(void);
long HashInsert(register char *s);
long HashTableSize(void);
char *Decode(long x);
#else
void FreeHash();
long HashInsert();
long HashTableSize();
char *Decode();
#endif /* ANSI_C */

#endif /* STDHASH */

/*-- end of standard hash table interface ----------------------------*/
 


#line 12 "/RW/esprit/users/sander/src/PARSEGEN/scan.skel"


/*--------------------------------------------------------------------*/

/* Global Variables */
/*------------------*/

int line_nr;
int pos_nr;
extern int nr_errors;  /* from Scanner */

/* Local Variables */
/*-----------------*/

static char message[256];

#define SKIPYYTEXT { char *c; c = yytext; while (*c) { \
     if (*c == '\n') { pos_nr = 1; line_nr++; }  \
     else pos_nr++; c++; }}
  

/*--------------------------------------------------------------------*/
/*   Character classes                                                */
/*--------------------------------------------------------------------*/


#line 188 "grammar.pgs"
%}


LETTER		[a-zA-Z]
DIGIT		[0-9]
INT		(\-)?{DIGIT}+
REAL		{INT}\.{INT}([E](\+|\-)?{INT})?
CHAR            '([^\\\']|\\.)+'
STRQ		[^\\\"]|\\.
STRING		\"({STRQ}*)\"
COMM		\/\*[^\*]*\*+([^\*\/][^\*]*\*+)*\/
COMME		\/\/[^\n]*
WSPACE          [ \t\f]*
LINEDIR1        {WSPACE}#{WSPACE}"line"?{WSPACE}{INT}{WSPACE}{STRING}.*\n
LINEDIR2        {WSPACE}#{WSPACE}"line"?{WSPACE}{INT}[^\"]*\n
PRAGMADIR       {WSPACE}#{WSPACE}"pragma".*\n



%{



#line 44 "/RW/esprit/users/sander/src/PARSEGEN/scan.skel"

#ifndef yywrap
/* Changed for flex 2.4.6 (static removed) */
int yywrap() { return (1); }
#endif

#ifndef RETURN
#ifndef YYLTYPE
#define RETURN(x) { 	pos_nr += strlen(yytext); \
			return(x); }
#else
extern YYLTYPE yylloc;
#define RETURN(x) { 	pos_nr += strlen(yytext); \
			yylloc.first_line = yylloc.last_line = line_nr; \
			yylloc.first_column = pos_nr-strlen(yytext);    \
			yylloc.last_column  = pos_nr;                   \
			return(x); }
#endif
#endif

#ifndef yysyntaxerror 
#define yysyntaxerror(l,p,m) {(void)printf("Line %d Pos %d: %s !\n",l,p,m);\
	nr_errors++;}
#endif

/*--------------------------------------------------------------------*/
/*   Token rules                                                      */
/*--------------------------------------------------------------------*/


#line 203 "grammar.pgs"
%}

%%


"above"			{
#line 209 "grammar.pgs"
		 RETURN(LEXWORD_ABOVE);               }
"anchor_points"		{
#line 210 "grammar.pgs"
		 RETURN(LEXWORD_ANCHORPOINTS);        }
"anchorpoints"		{
#line 211 "grammar.pgs"
		 RETURN(LEXWORD_ANCHORPOINTS);        }
"anchor"		{
#line 212 "grammar.pgs"
		 RETURN(LEXWORD_ANCHOR);              }
"aquamarine"		{
#line 213 "grammar.pgs"
		 RETURN(LEXWORD_AQUAMARINE);          }
"around"		{
#line 214 "grammar.pgs"
		 RETURN(LEXWORD_AROUND);              }
"arrow_mode"		{
#line 215 "grammar.pgs"
		 RETURN(LEXWORD_ARROWMODE);           }
"arrowmode"		{
#line 216 "grammar.pgs"
		 RETURN(LEXWORD_ARROWMODE);           }
"arrow_height"		{
#line 217 "grammar.pgs"
		 RETURN(LEXWORD_ARROWHEIGHT);         }
"arrowheight"		{
#line 218 "grammar.pgs"
		 RETURN(LEXWORD_ARROWHEIGHT);         }
"arrow_width"		{
#line 219 "grammar.pgs"
		 RETURN(LEXWORD_ARROWWIDTH);          }
"arrowwidth"		{
#line 220 "grammar.pgs"
		 RETURN(LEXWORD_ARROWWIDTH);          }
"arrow_color"		{
#line 221 "grammar.pgs"
		 RETURN(LEXWORD_ARROWCOLOR);          }
"arrowcolor"		{
#line 222 "grammar.pgs"
		 RETURN(LEXWORD_ARROWCOLOR);          }
"arrow_style"		{
#line 223 "grammar.pgs"
		 RETURN(LEXWORD_ARROWSTYLE);          }
"arrowstyle"		{
#line 224 "grammar.pgs"
		 RETURN(LEXWORD_ARROWSTYLE);          }
"arrow_size"		{
#line 225 "grammar.pgs"
		 RETURN(LEXWORD_ARROWSIZE);           }
"arrowsize"		{
#line 226 "grammar.pgs"
		 RETURN(LEXWORD_ARROWSIZE);           }
"back_arrow_color"	{
#line 227 "grammar.pgs"
		 RETURN(LEXWORD_BARROWCOLOR);         }
"backarrow_color"	{
#line 228 "grammar.pgs"
		 RETURN(LEXWORD_BARROWCOLOR);         }
"backarrowcolor"	{
#line 229 "grammar.pgs"
		 RETURN(LEXWORD_BARROWCOLOR);         }
"back_arrow_style"	{
#line 230 "grammar.pgs"
		 RETURN(LEXWORD_BARROWSTYLE);         }
"backarrow_style"	{
#line 231 "grammar.pgs"
		 RETURN(LEXWORD_BARROWSTYLE);         }
"backarrowstyle"	{
#line 232 "grammar.pgs"
		 RETURN(LEXWORD_BARROWSTYLE);         }
"back_arrow_size"	{
#line 233 "grammar.pgs"
		 RETURN(LEXWORD_BARROWSIZE);          }
"backarrow_size"	{
#line 234 "grammar.pgs"
		 RETURN(LEXWORD_BARROWSIZE);          }
"backarrowsize"		{
#line 235 "grammar.pgs"
		 RETURN(LEXWORD_BARROWSIZE);          }
"back_edge:"		{
#line 236 "grammar.pgs"
		 RETURN(LEXWORD_BACKEDGE);            }
"backedge:"		{
#line 237 "grammar.pgs"
		 RETURN(LEXWORD_BACKEDGE);            }
"bary_center"		{
#line 238 "grammar.pgs"
		 RETURN(LEXWORD_BARYCENTER);          }
"barycenter"		{
#line 239 "grammar.pgs"
		 RETURN(LEXWORD_BARYCENTER);          }
"bary"			{
#line 240 "grammar.pgs"
		 RETURN(LEXWORD_BARY);                }
"barymedian"   	 	{
#line 241 "grammar.pgs"
		 RETURN(LEXWORD_BARYMEDIAN);          } 
"behind"		{
#line 242 "grammar.pgs"
		 RETURN(LEXWORD_BEHIND);              }
"below"			{
#line 243 "grammar.pgs"
		 RETURN(LEXWORD_BELOW);               }
"black"			{
#line 244 "grammar.pgs"
		 RETURN(LEXWORD_BLACK);               }
"blue"			{
#line 245 "grammar.pgs"
		 RETURN(LEXWORD_BLUE);                }
"bmax"			{
#line 246 "grammar.pgs"
		 RETURN(LEXWORD_BMAX);                }
"border_color"		{
#line 247 "grammar.pgs"
		 RETURN(LEXWORD_BORDERCOLOR);         }
"bordercolor"		{
#line 248 "grammar.pgs"
		 RETURN(LEXWORD_BORDERCOLOR);         }
"border_width"		{
#line 249 "grammar.pgs"
		 RETURN(LEXWORD_BORDERWIDTH);         }
"borderwidth"		{
#line 250 "grammar.pgs"
		 RETURN(LEXWORD_BORDERWIDTH);         }
"bottom_margin"		{
#line 251 "grammar.pgs"
		 RETURN(LEXWORD_BOTTOM_MARGIN);       }
"bottommargin"		{
#line 252 "grammar.pgs"
		 RETURN(LEXWORD_BOTTOM_MARGIN);       }
"bottomtotop"		{
#line 253 "grammar.pgs"
		 RETURN(LEXWORD_BOTTOM_TO_TOP);       }
"bottom_to_top"		{
#line 254 "grammar.pgs"
		 RETURN(LEXWORD_BOTTOM_TO_TOP);       }
"bottom"		{
#line 255 "grammar.pgs"
		 RETURN(LEXWORD_BOTTOM);              }
"box"			{
#line 256 "grammar.pgs"
		 RETURN(LEXWORD_BOX);                 }
"bent_near_edge:"	{
#line 257 "grammar.pgs"
		 RETURN(LEXWORD_BENTNEAREDGE);        }
"bent_nearedge:"	{
#line 258 "grammar.pgs"
		 RETURN(LEXWORD_BENTNEAREDGE);        }
"bentnearedge:"		{
#line 259 "grammar.pgs"
		 RETURN(LEXWORD_BENTNEAREDGE);        }
"center"		{
#line 260 "grammar.pgs"
		 RETURN(LEXWORD_CENTER);              }
"cfish"			{
#line 261 "grammar.pgs"
		 RETURN(LEXWORD_CFISH);               }
"class_name"		{
#line 262 "grammar.pgs"
		 RETURN(LEXWORD_CLASSNAME);           }
"classname"		{
#line 263 "grammar.pgs"
		 RETURN(LEXWORD_CLASSNAME);           }
"class"			{
#line 264 "grammar.pgs"
		 RETURN(LEXWORD_CLASS);               }
"cluster"		{
#line 265 "grammar.pgs"
		 RETURN(LEXWORD_CLUSTER);             }
"cmin"			{
#line 266 "grammar.pgs"
		 RETURN(LEXWORD_CMIN);                }
"cmax"			{
#line 267 "grammar.pgs"
		 RETURN(LEXWORD_CMAX);                }
"color_entry"		{
#line 268 "grammar.pgs"
		 RETURN(LEXWORD_COLORENTRY);          }
"colorentry"		{
#line 269 "grammar.pgs"
		 RETURN(LEXWORD_COLORENTRY);          }
"color"			{
#line 270 "grammar.pgs"
		 RETURN(LEXWORD_COLOR);               }
"constraints"		{
#line 271 "grammar.pgs"
		 RETURN(LEXWORD_CONSTRAINTS);         }
"constraint:"		{
#line 272 "grammar.pgs"
		 RETURN(LEXWORD_CONSTRAINT);          }
"continuous"		{
#line 273 "grammar.pgs"
		 RETURN(LEXWORD_CONTINUOUS);          }
"crossing_weight"       {
#line 274 "grammar.pgs"
		 RETURN(LEXWORD_CROSSING_WEIGHT);     }
"crossingweight"        {
#line 275 "grammar.pgs"
		 RETURN(LEXWORD_CROSSING_WEIGHT);     }
"crossing_optimization" {
#line 276 "grammar.pgs"
		 RETURN(LEXWORD_CROSSING_OPT);        }
"crossingoptimization"  {
#line 277 "grammar.pgs"
		 RETURN(LEXWORD_CROSSING_OPT);        }
"crossing_phase2" 	{
#line 278 "grammar.pgs"
		 RETURN(LEXWORD_CROSSING_P2);         }
"crossingphase2"  	{
#line 279 "grammar.pgs"
		 RETURN(LEXWORD_CROSSING_P2);         }
"cyan"			{
#line 280 "grammar.pgs"
		 RETURN(LEXWORD_CYAN);                }
"darkblue"		{
#line 281 "grammar.pgs"
		 RETURN(LEXWORD_DARKBLUE);            }
"darkcyan"		{
#line 282 "grammar.pgs"
		 RETURN(LEXWORD_DARKCYAN);            }
"darkgreen"		{
#line 283 "grammar.pgs"
		 RETURN(LEXWORD_DARKGREEN);           }
"darkgray"		{
#line 284 "grammar.pgs"
		 RETURN(LEXWORD_DARKGREY);            }
"darkgrey"		{
#line 285 "grammar.pgs"
		 RETURN(LEXWORD_DARKGREY);            }
"darkmagenta"		{
#line 286 "grammar.pgs"
		 RETURN(LEXWORD_DARKMAGENTA);         }
"darkred"		{
#line 287 "grammar.pgs"
		 RETURN(LEXWORD_DARKRED);             }
"darkyellow"		{
#line 288 "grammar.pgs"
		 RETURN(LEXWORD_DARKYELLOW);          }
"dashed"		{
#line 289 "grammar.pgs"
		 RETURN(LEXWORD_DASHED);              } 
"depth_first_search"	{
#line 290 "grammar.pgs"
		 RETURN(LEXWORD_DFS);   	       } 
"depthfirstsearch"	{
#line 291 "grammar.pgs"
		 RETURN(LEXWORD_DFS);   	       } 
"dfs"			{
#line 292 "grammar.pgs"
		 RETURN(LEXWORD_DFS);   	       } 
"dimension"		{
#line 293 "grammar.pgs"
		 RETURN(LEXWORD_DIMENSION);           }
"dirtyedgelabels"	{
#line 294 "grammar.pgs"
		 RETURN(LEXWORD_DIRTY_EDGE_LABELS);   }
"dirty_edge_labels"	{
#line 295 "grammar.pgs"
		 RETURN(LEXWORD_DIRTY_EDGE_LABELS);   }
"displayedgelabels"	{
#line 296 "grammar.pgs"
		 RETURN(LEXWORD_DISPLAY_EDGE_LABELS); }
"display_edge_labels"	{
#line 297 "grammar.pgs"
		 RETURN(LEXWORD_DISPLAY_EDGE_LABELS); }
"dotted"		{
#line 298 "grammar.pgs"
		 RETURN(LEXWORD_DOTTED);              }
"edge."			{
#line 299 "grammar.pgs"
		 RETURN(LEXWORD_EDGE1);               }
"edge:"			{
#line 300 "grammar.pgs"
		 RETURN(LEXWORD_EDGE2);               }
"edges"			{
#line 301 "grammar.pgs"
		 RETURN(LEXWORD_EDGES);               }
"ellipse"		{
#line 302 "grammar.pgs"
		 RETURN(LEXWORD_ELLIPSE);             }
"equalcolumn"		{
#line 303 "grammar.pgs"
		 RETURN(LEXWORD_EQUAL_COLUMN);        }
"equal_column"		{
#line 304 "grammar.pgs"
		 RETURN(LEXWORD_EQUAL_COLUMN);        }
"equalposition"		{
#line 305 "grammar.pgs"
		 RETURN(LEXWORD_EQUAL_POSITION);      }
"equal_position"	{
#line 306 "grammar.pgs"
		 RETURN(LEXWORD_EQUAL_POSITION);      }
"equalrow"		{
#line 307 "grammar.pgs"
		 RETURN(LEXWORD_EQUAL_ROW);           }
"equal_row"		{
#line 308 "grammar.pgs"
		 RETURN(LEXWORD_EQUAL_ROW);           }
"equal"			{
#line 309 "grammar.pgs"
		 RETURN(LEXWORD_EQUAL);               }
"every"			{
#line 310 "grammar.pgs"
		 RETURN(LEXWORD_EVERY);               }
"fcfish"		{
#line 311 "grammar.pgs"
		 RETURN(LEXWORD_FCFISH);              }
"fpfish"		{
#line 312 "grammar.pgs"
		 RETURN(LEXWORD_FPFISH);              }
"fixed"			{
#line 313 "grammar.pgs"
		 RETURN(LEXWORD_FIXED);               }
"free"			{
#line 314 "grammar.pgs"
		 RETURN(LEXWORD_FREE);                }
"fine_tuning"		{
#line 315 "grammar.pgs"
		 RETURN(LEXWORD_FINETUNING);          }
"finetuning"		{
#line 316 "grammar.pgs"
		 RETURN(LEXWORD_FINETUNING);          }
"fold_edge."		{
#line 317 "grammar.pgs"
		 RETURN(LEXWORD_FOLDEDGE);            }
"foldedge."		{
#line 318 "grammar.pgs"
		 RETURN(LEXWORD_FOLDEDGE);            }
"fold_node."		{
#line 319 "grammar.pgs"
		 RETURN(LEXWORD_FOLDNODE);            }
"foldnode."		{
#line 320 "grammar.pgs"
		 RETURN(LEXWORD_FOLDNODE);            }
"folding"		{
#line 321 "grammar.pgs"
		 RETURN(LEXWORD_FOLDING);             }
"font_name"		{
#line 322 "grammar.pgs"
		 RETURN(LEXWORD_FONTNAME);            }
"fontname"		{
#line 323 "grammar.pgs"
		 RETURN(LEXWORD_FONTNAME);            }
"gold"			{
#line 324 "grammar.pgs"
		 RETURN(LEXWORD_GOLD);                }
"graph:"		{
#line 325 "grammar.pgs"
		 RETURN(LEXWORD_GRAPH);               }
"greater"		{
#line 326 "grammar.pgs"
		 RETURN(LEXWORD_GREATER);             }
"green"			{
#line 327 "grammar.pgs"
		 RETURN(LEXWORD_GREEN);               }
"gray"			{
#line 328 "grammar.pgs"
		 RETURN(LEXWORD_GREY);                }
"grey"			{
#line 329 "grammar.pgs"
		 RETURN(LEXWORD_GREY);                }
"height"		{
#line 330 "grammar.pgs"
		 RETURN(LEXWORD_HEIGHT);              }
"hidesingles"		{
#line 331 "grammar.pgs"
		 RETURN(LEXWORD_HIDESINGLES);         }
"hide_singles"		{
#line 332 "grammar.pgs"
		 RETURN(LEXWORD_HIDESINGLES);         }
"highmargin"		{
#line 333 "grammar.pgs"
		 RETURN(LEXWORD_HIGH_MARGIN);         }
"high_margin"		{
#line 334 "grammar.pgs"
		 RETURN(LEXWORD_HIGH_MARGIN);         }
"high"			{
#line 335 "grammar.pgs"
		 RETURN(LEXWORD_HIGH);		       }
"hidden"		{
#line 336 "grammar.pgs"
		 RETURN(LEXWORD_HIDDEN);              }
"horizontalorder"	{
#line 337 "grammar.pgs"
		 RETURN(LEXWORD_HORDER);              }
"horizontal_order"	{
#line 338 "grammar.pgs"
		 RETURN(LEXWORD_HORDER);              }
"icon_file"		{
#line 339 "grammar.pgs"
		 RETURN(LEXWORD_ICONFILE);            }
"iconfile"		{
#line 340 "grammar.pgs"
		 RETURN(LEXWORD_ICONFILE);            }
"icon_height"		{
#line 341 "grammar.pgs"
		 RETURN(LEXWORD_ICONHEIGHT);          }
"iconheight"		{
#line 342 "grammar.pgs"
		 RETURN(LEXWORD_ICONHEIGHT);          }
"icon_style"		{
#line 343 "grammar.pgs"
		 RETURN(LEXWORD_ICONSTYLE);           }
"iconstyle"		{
#line 344 "grammar.pgs"
		 RETURN(LEXWORD_ICONSTYLE);           }
"icon_width"		{
#line 345 "grammar.pgs"
		 RETURN(LEXWORD_ICONWIDTH);           }
"iconwidth"		{
#line 346 "grammar.pgs"
		 RETURN(LEXWORD_ICONWIDTH);           }
"ignore_singles"	{
#line 347 "grammar.pgs"
		 RETURN(LEXWORD_HIDESINGLES);         }
"ignoresingles"		{
#line 348 "grammar.pgs"
		 RETURN(LEXWORD_HIDESINGLES);         }
"include"		{
#line 349 "grammar.pgs"
		 RETURN(LEXWORD_INCLUDE);             }
"infoname"		{
#line 350 "grammar.pgs"
		 RETURN(LEXWORD_INFONAME);            }
"info1"			{
#line 351 "grammar.pgs"
		 RETURN(LEXWORD_INFO1);               }
"info2"			{
#line 352 "grammar.pgs"
		 RETURN(LEXWORD_INFO2);               }
"info3"			{
#line 353 "grammar.pgs"
		 RETURN(LEXWORD_INFO3);               }
"input_function"	{
#line 354 "grammar.pgs"
		 RETURN(LEXWORD_INPUTFUNCTION);       }
"inputfunction"		{
#line 355 "grammar.pgs"
		 RETURN(LEXWORD_INPUTFUNCTION);       }
"interval"		{
#line 356 "grammar.pgs"
		 RETURN(LEXWORD_INTERVAL);            }
"invisible"		{
#line 357 "grammar.pgs"
		 RETURN(LEXWORD_INVISIBLE);           }
"in_front"		{
#line 358 "grammar.pgs"
		 RETURN(LEXWORD_IN_FRONT);            }
"isi"			{
#line 359 "grammar.pgs"
		 RETURN(LEXWORD_ISI);                 }
"khaki"			{
#line 360 "grammar.pgs"
		 RETURN(LEXWORD_KHAKI);               }
"label_color"		{
#line 361 "grammar.pgs"
		 RETURN(LEXWORD_TEXTCOLOR);           }
"labelcolor"		{
#line 362 "grammar.pgs"
		 RETURN(LEXWORD_TEXTCOLOR);           }
"label"			{
#line 363 "grammar.pgs"
		 RETURN(LEXWORD_LABEL);               }
"lateedgelabels"     	{
#line 364 "grammar.pgs"
		 RETURN(LEXWORD_LATE_LABELS);         }
"late_edge_labels"     	{
#line 365 "grammar.pgs"
		 RETURN(LEXWORD_LATE_LABELS);         }
"layout_algorithm"	{
#line 366 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTALGORITHM);     }
"layoutalgorithm"	{
#line 367 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTALGORITHM);     }
"layout_frequency"	{
#line 368 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTFREQUENCY);     }
"layoutfrequency"	{
#line 369 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTFREQUENCY);     }
"layout_parameter"	{
#line 370 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTPARAMETER);     }
"layoutparameter"	{
#line 371 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTPARAMETER);     }
"layoutdownfactor"	{
#line 372 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTDOWNFACTOR);    }
"layout_downfactor"	{
#line 373 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTDOWNFACTOR);    }
"layoutupfactor"	{
#line 374 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTUPFACTOR);      }
"layout_upfactor"	{
#line 375 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTUPFACTOR);      }
"layoutnearfactor"	{
#line 376 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTNEARFACTOR);    }
"layout_nearfactor"	{
#line 377 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTNEARFACTOR);    }
"layoutsplinefactor"	{
#line 378 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTSPLINEFACTOR);  }
"layout_splinefactor"	{
#line 379 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTSPLINEFACTOR);  }
"leftjustify"		{
#line 380 "grammar.pgs"
		 RETURN(LEXWORD_LEFT_JUSTIFY);        } 
"left_justify"		{
#line 381 "grammar.pgs"
		 RETURN(LEXWORD_LEFT_JUSTIFY);        } 
"leftmargin"		{
#line 382 "grammar.pgs"
		 RETURN(LEXWORD_LEFT_MARGIN);         } 
"left_margin"		{
#line 383 "grammar.pgs"
		 RETURN(LEXWORD_LEFT_MARGIN);         } 
"leftneighbor"		{
#line 384 "grammar.pgs"
		 RETURN(LEXWORD_LEFT_NEIGHBOR);       }
"left_neighbor"		{
#line 385 "grammar.pgs"
		 RETURN(LEXWORD_LEFT_NEIGHBOR);       }
"lefttoright"		{
#line 386 "grammar.pgs"
		 RETURN(LEXWORD_LEFT_TO_RIGHT);       } 
"left_to_right"		{
#line 387 "grammar.pgs"
		 RETURN(LEXWORD_LEFT_TO_RIGHT);       } 
"left"			{
#line 388 "grammar.pgs"
		 RETURN(LEXWORD_LEFT);                }
"level"			{
#line 389 "grammar.pgs"
		 RETURN(LEXWORD_LEVEL);               }
"verticalorder"		{
#line 390 "grammar.pgs"
		 RETURN(LEXWORD_VORDER);              }
"vertical_order"	{
#line 391 "grammar.pgs"
		 RETURN(LEXWORD_VORDER);              }
"lightblue"		{
#line 392 "grammar.pgs"
		 RETURN(LEXWORD_LIGHTBLUE);           }
"lightcyan"		{
#line 393 "grammar.pgs"
		 RETURN(LEXWORD_LIGHTCYAN);           }
"lightgreen"		{
#line 394 "grammar.pgs"
		 RETURN(LEXWORD_LIGHTGREEN);          }
"lightgray"		{
#line 395 "grammar.pgs"
		 RETURN(LEXWORD_LIGHTGREY);           }
"lightgrey"		{
#line 396 "grammar.pgs"
		 RETURN(LEXWORD_LIGHTGREY);           }
"lightmagenta"		{
#line 397 "grammar.pgs"
		 RETURN(LEXWORD_LIGHTMAGENTA);        }
"lightred"		{
#line 398 "grammar.pgs"
		 RETURN(LEXWORD_LIGHTRED);            }
"lightyellow"		{
#line 399 "grammar.pgs"
		 RETURN(LEXWORD_LIGHTYELLOW);         }
"lilac"			{
#line 400 "grammar.pgs"
		 RETURN(LEXWORD_LILAC);               }
"limit"			{
#line 401 "grammar.pgs"
		 RETURN(LEXWORD_LIMIT);               } 
"line"			{
#line 402 "grammar.pgs"
		 RETURN(LEXWORD_LINE);                } 
"line_style"		{
#line 403 "grammar.pgs"
		 RETURN(LEXWORD_LINESTYLE);           } 
"linestyle"		{
#line 404 "grammar.pgs"
		 RETURN(LEXWORD_LINESTYLE);           } 
"loc:"			{
#line 405 "grammar.pgs"
		 RETURN(LEXWORD_LOC);                 }
"lowerneighbor"		{
#line 406 "grammar.pgs"
		 RETURN(LEXWORD_LOWER_NEIGHBOR);      }
"lower_neighbor"	{
#line 407 "grammar.pgs"
		 RETURN(LEXWORD_LOWER_NEIGHBOR);      }
"lowmargin"		{
#line 408 "grammar.pgs"
		 RETURN(LEXWORD_LOW_MARGIN);          } 
"low_margin"		{
#line 409 "grammar.pgs"
		 RETURN(LEXWORD_LOW_MARGIN);          } 
"low"			{
#line 410 "grammar.pgs"
		 RETURN(LEXWORD_LOW);                 } 
"magenta"		{
#line 411 "grammar.pgs"
		 RETURN(LEXWORD_MAGENTA);             }
"manhattenedges"	{
#line 412 "grammar.pgs"
		 RETURN(LEXWORD_MANHATTEN);           } 
"manhattanedges"	{
#line 413 "grammar.pgs"
		 RETURN(LEXWORD_MANHATTEN);           } 
"manhatten_edges"	{
#line 414 "grammar.pgs"
		 RETURN(LEXWORD_MANHATTEN);           } 
"manhattan_edges"	{
#line 415 "grammar.pgs"
		 RETURN(LEXWORD_MANHATTEN);           } 
"manual"		{
#line 416 "grammar.pgs"
		 RETURN(LEXWORD_MANUAL);              } 
"maxdepthslow"		{
#line 417 "grammar.pgs"
		 RETURN(LEXWORD_MAXDEPTHSLOW);        } 
"maxdepth"		{
#line 418 "grammar.pgs"
		 RETURN(LEXWORD_MAXDEPTH);            } 
"maxdegree"		{
#line 419 "grammar.pgs"
		 RETURN(LEXWORD_MAXDEGREE);           } 
"maxindegree"		{
#line 420 "grammar.pgs"
		 RETURN(LEXWORD_MAXINDEGREE);         } 
"maxoutdegree"		{
#line 421 "grammar.pgs"
		 RETURN(LEXWORD_MAXOUTDEGREE);        } 
"median"      	 	{
#line 422 "grammar.pgs"
		 RETURN(LEXWORD_MEDIAN);              } 
"medianbary"   	 	{
#line 423 "grammar.pgs"
		 RETURN(LEXWORD_MEDIANBARY);          } 
"mindepthslow"		{
#line 424 "grammar.pgs"
		 RETURN(LEXWORD_MINDEPTHSLOW);        } 
"mindepth"		{
#line 425 "grammar.pgs"
		 RETURN(LEXWORD_MINDEPTH);            } 
"mindegree"		{
#line 426 "grammar.pgs"
		 RETURN(LEXWORD_MINDEGREE);           } 
"minindegree"		{
#line 427 "grammar.pgs"
		 RETURN(LEXWORD_MININDEGREE);         } 
"minoutdegree"		{
#line 428 "grammar.pgs"
		 RETURN(LEXWORD_MINOUTDEGREE);        } 
"minbackward"		{
#line 429 "grammar.pgs"
		 RETURN(LEXWORD_MINBACK);             } 
"name"			{
#line 430 "grammar.pgs"
		 RETURN(LEXWORD_NAME);                } 
"near_edge:"		{
#line 431 "grammar.pgs"
		 RETURN(LEXWORD_NEAREDGE);            }
"nearedge:"		{
#line 432 "grammar.pgs"
		 RETURN(LEXWORD_NEAREDGE);            }
"neighbors"		{
#line 433 "grammar.pgs"
		 RETURN(LEXWORD_NEIGHBORS);           } 
"near_edges"		{
#line 434 "grammar.pgs"
		 RETURN(LEXWORD_NEAREDGES);           }
"nearedges"		{
#line 435 "grammar.pgs"
		 RETURN(LEXWORD_NEAREDGES);           }
"nonearedges"		{
#line 436 "grammar.pgs"
		 RETURN(LEXWORD_NONEAREDGES);         }
"no_near_edges"		{
#line 437 "grammar.pgs"
		 RETURN(LEXWORD_NONEAREDGES);         }
"no_nearedges"		{
#line 438 "grammar.pgs"
		 RETURN(LEXWORD_NONEAREDGES);         }
"node."			{
#line 439 "grammar.pgs"
		 RETURN(LEXWORD_NODE1);               }
"node:"			{
#line 440 "grammar.pgs"
		 RETURN(LEXWORD_NODE2);               }
"nodes"			{
#line 441 "grammar.pgs"
		 RETURN(LEXWORD_NODES);               }
"nodealignment"     	{
#line 442 "grammar.pgs"
		 RETURN(LEXWORD_NODE_ALIGN);          }
"node_alignment"     	{
#line 443 "grammar.pgs"
		 RETURN(LEXWORD_NODE_ALIGN);          }
"none"			{
#line 444 "grammar.pgs"
		 RETURN(LEXWORD_NONE);                }
"no"			{
#line 445 "grammar.pgs"
		 RETURN(LEXWORD_NO);                  }
"orange"		{
#line 446 "grammar.pgs"
		 RETURN(LEXWORD_ORANGE);              }
"orchid"		{
#line 447 "grammar.pgs"
		 RETURN(LEXWORD_ORCHID);              }
"orientation"		{
#line 448 "grammar.pgs"
		 RETURN(LEXWORD_ORIENTATION);         } 
"output_function"	{
#line 449 "grammar.pgs"
		 RETURN(LEXWORD_OUTPUTFUNCTION);      }
"outputfunction"	{
#line 450 "grammar.pgs"
		 RETURN(LEXWORD_OUTPUTFUNCTION);      }
"pfish"			{
#line 451 "grammar.pgs"
		 RETURN(LEXWORD_PFISH);               }
"pink"			{
#line 452 "grammar.pgs"
		 RETURN(LEXWORD_PINK);                }
"planar"		{
#line 453 "grammar.pgs"
		 RETURN(LEXWORD_PLANAR);              }
"pmin"			{
#line 454 "grammar.pgs"
		 RETURN(LEXWORD_PMIN);                }
"pmax"			{
#line 455 "grammar.pgs"
		 RETURN(LEXWORD_PMAX);                }
"portsharing"		{
#line 456 "grammar.pgs"
		 RETURN(LEXWORD_PORTSHARING);         } 
"port_sharing"		{
#line 457 "grammar.pgs"
		 RETURN(LEXWORD_PORTSHARING);         } 
"priorityphase"		{
#line 458 "grammar.pgs"
		 RETURN(LEXWORD_PRIORITYPHASE);       }
"priority_phase"	{
#line 459 "grammar.pgs"
		 RETURN(LEXWORD_PRIORITYPHASE);       }
"priority"		{
#line 460 "grammar.pgs"
		 RETURN(LEXWORD_PRIORITY);            }
"purple"		{
#line 461 "grammar.pgs"
		 RETURN(LEXWORD_PURPLE);              } 
"range"			{
#line 462 "grammar.pgs"
		 RETURN(LEXWORD_RANGE);               } 
"red"			{
#line 463 "grammar.pgs"
		 RETURN(LEXWORD_RED);                 }
"rhomb"			{
#line 464 "grammar.pgs"
		 RETURN(LEXWORD_RHOMB);               }
"rightjustify"		{
#line 465 "grammar.pgs"
		 RETURN(LEXWORD_RIGHT_JUSTIFY);       }
"right_justify"		{
#line 466 "grammar.pgs"
		 RETURN(LEXWORD_RIGHT_JUSTIFY);       }
"rightmargin"		{
#line 467 "grammar.pgs"
		 RETURN(LEXWORD_RIGHT_MARGIN);        }
"right_margin"		{
#line 468 "grammar.pgs"
		 RETURN(LEXWORD_RIGHT_MARGIN);        }
"rightneighbor"		{
#line 469 "grammar.pgs"
		 RETURN(LEXWORD_RIGHT_NEIGHBOR);      }
"right_neighbor"	{
#line 470 "grammar.pgs"
		 RETURN(LEXWORD_RIGHT_NEIGHBOR);      }
"righttoleft"		{
#line 471 "grammar.pgs"
		 RETURN(LEXWORD_RIGHT_TO_LEFT);       }
"right_to_left"		{
#line 472 "grammar.pgs"
		 RETURN(LEXWORD_RIGHT_TO_LEFT);       }
"right"			{
#line 473 "grammar.pgs"
		 RETURN(LEXWORD_RIGHT);               }
"rmin"			{
#line 474 "grammar.pgs"
		 RETURN(LEXWORD_RMIN);                }
"rmax"			{
#line 475 "grammar.pgs"
		 RETURN(LEXWORD_RMAX);                }
"scaling"		{
#line 476 "grammar.pgs"
		 RETURN(LEXWORD_SCALING);             }
"shape"			{
#line 477 "grammar.pgs"
		 RETURN(LEXWORD_SHAPE);               }
"shrink"		{
#line 478 "grammar.pgs"
		 RETURN(LEXWORD_SHRINK);              }
"smax"			{
#line 479 "grammar.pgs"
		 RETURN(LEXWORD_SMAX);                }
"smanhattenedges"	{
#line 480 "grammar.pgs"
		 RETURN(LEXWORD_SMANHATTEN);          } 
"smanhattanedges"	{
#line 481 "grammar.pgs"
		 RETURN(LEXWORD_SMANHATTEN);          } 
"smanhatten_edges"	{
#line 482 "grammar.pgs"
		 RETURN(LEXWORD_SMANHATTEN);          } 
"smanhattan_edges"	{
#line 483 "grammar.pgs"
		 RETURN(LEXWORD_SMANHATTEN);          } 
"size"			{
#line 484 "grammar.pgs"
		 RETURN(LEXWORD_SIZE);                }
"smaller"		{
#line 485 "grammar.pgs"
		 RETURN(LEXWORD_SMALLER);             }
"solid"			{
#line 486 "grammar.pgs"
		 RETURN(LEXWORD_SOLID);               }
"source_name"		{
#line 487 "grammar.pgs"
		 RETURN(LEXWORD_SOURCENAME);          }
"sourcename"		{
#line 488 "grammar.pgs"
		 RETURN(LEXWORD_SOURCENAME);          }
"splines"		{
#line 489 "grammar.pgs"
		 RETURN(LEXWORD_SPLINES);             }
"spline_factor"		{
#line 490 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTSPLINEFACTOR);  }
"splinefactor"		{
#line 491 "grammar.pgs"
		 RETURN(LEXWORD_LAYOUTSPLINEFACTOR);  }
"spread_level"		{
#line 492 "grammar.pgs"
		 RETURN(LEXWORD_SPREADLEVEL);         }
"spreadlevel"		{
#line 493 "grammar.pgs"
		 RETURN(LEXWORD_SPREADLEVEL);         }
"status"		{
#line 494 "grammar.pgs"
		 RETURN(LEXWORD_STATUS);              }
"stretch"		{
#line 495 "grammar.pgs"
		 RETURN(LEXWORD_STRETCH);             }
"straightphase"		{
#line 496 "grammar.pgs"
		 RETURN(LEXWORD_STRAIGHTPHASE);       }
"straight_phase"	{
#line 497 "grammar.pgs"
		 RETURN(LEXWORD_STRAIGHTPHASE);       }
"target_name"		{
#line 498 "grammar.pgs"
		 RETURN(LEXWORD_TARGETNAME);          }
"targetname"		{
#line 499 "grammar.pgs"
		 RETURN(LEXWORD_TARGETNAME);          }
"text_color"		{
#line 500 "grammar.pgs"
		 RETURN(LEXWORD_TEXTCOLOR);           }
"textcolor"		{
#line 501 "grammar.pgs"
		 RETURN(LEXWORD_TEXTCOLOR);           }
"text_mode"		{
#line 502 "grammar.pgs"
		 RETURN(LEXWORD_TEXTMODE);            }
"textmode"		{
#line 503 "grammar.pgs"
		 RETURN(LEXWORD_TEXTMODE);            }
"thickness"		{
#line 504 "grammar.pgs"
		 RETURN(LEXWORD_THICKNESS);           }
"title"			{
#line 505 "grammar.pgs"
		 RETURN(LEXWORD_TITLE);               } 
"top_sort"              {
#line 506 "grammar.pgs"
		 RETURN(LEXWORD_TOPSORT);             }
"topsort"               {
#line 507 "grammar.pgs"
		 RETURN(LEXWORD_TOPSORT);             }
"topmargin"		{
#line 508 "grammar.pgs"
		 RETURN(LEXWORD_TOP_MARGIN);          }
"top_margin"		{
#line 509 "grammar.pgs"
		 RETURN(LEXWORD_TOP_MARGIN);          }
"toptobottom"		{
#line 510 "grammar.pgs"
		 RETURN(LEXWORD_TOP_TO_BOTTOM);       }
"top_to_bottom"		{
#line 511 "grammar.pgs"
		 RETURN(LEXWORD_TOP_TO_BOTTOM);       }
"top"			{
#line 512 "grammar.pgs"
		 RETURN(LEXWORD_TOP);                 } 
"tree"			{
#line 513 "grammar.pgs"
		 RETURN(LEXWORD_TREE);                }
"tree_factor"		{
#line 514 "grammar.pgs"
		 RETURN(LEXWORD_TREEFACTOR);          }
"treefactor"		{
#line 515 "grammar.pgs"
		 RETURN(LEXWORD_TREEFACTOR);          }
"triangle"		{
#line 516 "grammar.pgs"
		 RETURN(LEXWORD_TRIANGLE);            }
"turquoise"		{
#line 517 "grammar.pgs"
		 RETURN(LEXWORD_TURQUOISE);           }
"type_name"		{
#line 518 "grammar.pgs"
		 RETURN(LEXWORD_TYPENAME);            }
"typename"		{
#line 519 "grammar.pgs"
		 RETURN(LEXWORD_TYPENAME);            }
"upperneighbor"		{
#line 520 "grammar.pgs"
		 RETURN(LEXWORD_UPPER_NEIGHBOR);      }
"upper_neighbor"	{
#line 521 "grammar.pgs"
		 RETURN(LEXWORD_UPPER_NEIGHBOR);      }
"view"			{
#line 522 "grammar.pgs"
		 RETURN(LEXWORD_VIEW);                }
"white"			{
#line 523 "grammar.pgs"
		 RETURN(LEXWORD_WHITE);               }
"width"			{
#line 524 "grammar.pgs"
		 RETURN(LEXWORD_WIDTH);               }
"xbase"			{
#line 525 "grammar.pgs"
		 RETURN(LEXWORD_XBASE);               }
"xmax"			{
#line 526 "grammar.pgs"
		 RETURN(LEXWORD_XMAX);                }
"xraster"		{
#line 527 "grammar.pgs"
		 RETURN(LEXWORD_XRASTER);             }
"xlraster"		{
#line 528 "grammar.pgs"
		 RETURN(LEXWORD_XLRASTER);            }
"xscrollbar"		{
#line 529 "grammar.pgs"
		 RETURN(LEXWORD_XSCROLLBAR);          }
"xspace"		{
#line 530 "grammar.pgs"
		 RETURN(LEXWORD_XSPACE);              }
"xlspace"		{
#line 531 "grammar.pgs"
		 RETURN(LEXWORD_XLSPACE);             }
"ybase"			{
#line 532 "grammar.pgs"
		 RETURN(LEXWORD_YBASE);               }
"yellowgreen"		{
#line 533 "grammar.pgs"
		 RETURN(LEXWORD_YELLOWGREEN);         }
"yellow"		{
#line 534 "grammar.pgs"
		 RETURN(LEXWORD_YELLOW);              }
"yes"			{
#line 535 "grammar.pgs"
		 RETURN(LEXWORD_YES);                 }
"ymax"			{
#line 536 "grammar.pgs"
		 RETURN(LEXWORD_YMAX);                }
"yraster"		{
#line 537 "grammar.pgs"
		 RETURN(LEXWORD_YRASTER);             }
"yscrollbar"		{
#line 538 "grammar.pgs"
		 RETURN(LEXWORD_YSCROLLBAR);          }
"yspace"		{
#line 539 "grammar.pgs"
		 RETURN(LEXWORD_YSPACE);              }

{LINEDIR1}              {
#line 541 "grammar.pgs"
		 line_directive(yytext);       }
{LINEDIR2}              {
#line 542 "grammar.pgs"
		 line_directive(yytext);       }
{PRAGMADIR}             {
#line 543 "grammar.pgs"
		 /* ignore pragma directive */ }

[\f ]+			{
#line 545 "grammar.pgs"
		 pos_nr+=strlen(yytext); }
[\t]			{
#line 546 "grammar.pgs"
		 pos_nr++;               }
[\n]			{
#line 547 "grammar.pgs"
		 line_nr++; pos_nr=1;    }

{INT}			{
#line 549 "grammar.pgs"
		 yylval.lnum = long_atoi(yytext); 
			  RETURN(LEX_INT); 
			}
{REAL}			{
#line 552 "grammar.pgs"
		 yylval.lrealnum = atof(yytext); 
			  RETURN(LEX_FLOAT); 
			}
{CHAR}     	     	{
#line 555 "grammar.pgs"
		 yylval.byte = yytext[1];
               		  RETURN(LEX_CHAR);
                	}
{STRING}                {
#line 558 "grammar.pgs"
		 yytext[strlen(yytext)-1] = '\0';
			  escape_transl(&(yytext[1]));
	                  yylval.lnum = HashInsert(&(yytext[1]));
			  SKIPYYTEXT;
                          RETURN(LEX_STRING);
                        }
{COMM}			{
#line 564 "grammar.pgs"
		 SKIPYYTEXT; }
{COMME}			{
#line 565 "grammar.pgs"
		 SKIPYYTEXT; }

"{"			{
#line 567 "grammar.pgs"
		 RETURN('{'); }
"}"			{
#line 568 "grammar.pgs"
		 RETURN('}'); }
":"			{
#line 569 "grammar.pgs"
		 RETURN(':'); }
"x"			{
#line 570 "grammar.pgs"
		 RETURN('x'); }
"y"			{
#line 571 "grammar.pgs"
		 RETURN('y'); }
"z"			{
#line 572 "grammar.pgs"
		 RETURN('z'); }
"*"			{
#line 573 "grammar.pgs"
		 RETURN('*'); }
"["			{
#line 574 "grammar.pgs"
		 RETURN('['); }
"]"			{
#line 575 "grammar.pgs"
		 RETURN(']'); }
"-"			{
#line 576 "grammar.pgs"
		 RETURN('-'); }



.              { 


#line 80 "/RW/esprit/users/sander/src/PARSEGEN/scan.skel"
		 (void)sprintf(message,
			"scanner reads unexpected %c",yytext[0]);
		 yysyntaxerror(line_nr,pos_nr,message);
                 RETURN(' '); }

%%



#line 88 "/RW/esprit/users/sander/src/PARSEGEN/scan.skel"

/*--------------------------------------------------------------------*/
/*   Initialize scanner                                               */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
void init_lex(void)
#else
void init_lex()
#endif
{
	yy_init = 1;
}



#line 1 "/RW/esprit/users/sander/src/PARSEGEN/stdtc.skel"

/*--------------------------------------------------------------------*/
/*  Standard Hash Table Routines                                      */
/*--------------------------------------------------------------------*/
 
#ifdef HASHGENSTD 

#ifndef lint
static char *stdtc_id_string="$Id: stdtc.skel,v 1.7 1994/11/25 17:23:13 sander Exp sander $";
#endif


#include <stdio.h>
#include <string.h>
#include <malloc.h>

/* Global Variables */
/*------------------*/

static char **decode = NULL;
long   table_size = 0L;

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
/* Memory allocation for single strings                               */
/*--------------------------------------------------------------------*/

#ifndef ALIGN
#define ALIGN 8
#define IALIGN (ALIGN-1)
#endif

#ifndef STRINGBLOCKSIZE 
#define STRINGBLOCKSIZE 5000 
#endif 
 

#ifndef PARSEGENSTD

/* If we include already the standard parser library, this is not
 * necessary
 */


static char *parseheap = (char *)0;             /* the heap */ 
static char *parseheapstart;                    /* the base */
static char *parseheaptop;                      /* the top  */
static char *parseheapend;                      /* the end  */
static int  parseheapsize = STRINGBLOCKSIZE; /* the size of one block */


#ifdef ANSI_C
static void alloc_block(void)
#else
static void alloc_block()
#endif
{
        char * help, *help2;

	help =(char *)malloc(parseheapsize*sizeof(long));
        if (!help) fatal_error("memory exhausted");
	help2  = (char **)help;
	*help2 = (char *)parseheap;
	parseheap = help;
	parseheapstart = parseheaptop =
		(char *)((long)parseheap + (long)sizeof(char *));
	parseheapend = parseheap;
	parseheapend += (parseheapsize-2);
        if ((long)parseheaptop&IALIGN) 
		parseheaptop = (char *)
			(((long)parseheaptop+(long)IALIGN)&(long)(~IALIGN));
}


/*  allocate x bytes */

#ifdef ANSI_C
static char * ParseMalloc(int x)
#else
static char * ParseMalloc(x)
int x;
#endif
{
        char * help;
        int  y;

	if (!parseheap) alloc_block();

        y = x;
        if (y&IALIGN) y = (y+IALIGN)&(~IALIGN);

        help = parseheaptop;
        parseheaptop = (char *)((long)parseheaptop+(long)y);

        if (parseheaptop > parseheapend) {

		/* heap too small -> allocate new heap block */

		alloc_block();
                help = parseheaptop;
                parseheaptop = (char *)((long)parseheaptop+(long)y);
        	if (parseheaptop > parseheapend) 
			fatal_error("string node too large");
        }
        return (help);
}


/* Global: allocate x bytes */

#ifdef ANSI_C
char *StringHeapMalloc(int x)
#else
char *StringHeapMalloc(x)
int x;
#endif
{
	return(ParseMalloc(x));
}


/* global deallocate the complete syntax tree heap */

#ifdef ANSI_C
void StringHeapFree(void)
#else
void StringHeapFree()
#endif
{
        char *help, help2;

        help = parseheap;
        while (help) {
                help2 = *(char **)help;
                (void)free(help);
                help = help2;
        }

        parseheap = (char *)0;
}

#endif /* PARSEGENSTD */


/*--------------------------------------------------------------------*/
/* Memory allocation for decode table and hash table                  */
/*--------------------------------------------------------------------*/

#ifndef hash_size
#define hash_size 211
#endif
#ifndef hashtable_size
#define hashtable_size 10000L
#endif

/* We use a hash table with linked lists */

typedef struct hash_node {
        long              num;
        struct hash_node *next;
} *hashentry;


/* The hash table */

static hashentry *hashtable = NULL;
static long hashtop = 1;

#ifdef ANSI_C
static void init_hash(void)
#else
static void init_hash()
#endif
{
	char *h;

        if (!hashtable) {

		/* no hash table present -> allocate table */

                hashtable  = (hashentry *) 
				calloc((size_t) (hash_size+1),
                				 sizeof(hashentry));
        	if (!hashtable) fatal_error("memory exhausted");
	}

        if (!decode) {

		/* no decode table present -> allocate table */

		hashtop = 1;
		table_size = hashtable_size;
                decode   = (char **) 
				calloc((size_t) (table_size+1L),
                   				sizeof(char *));
	        if (!decode) fatal_error("memory exhausted");
                h = ParseMalloc(strlen("$!+-#Start of Hash#+-!$")+1);
                decode[0]    = strcpy(h,"$!+-#Start of Hash#+-!$");
	}
}


#ifdef ANSI_C
static void increase_decode(void)
#else
static void increase_decode()
#endif
{
	char **help,**a,**b;
	long   mysize, j;

	mysize = table_size * 2L;
	help = (char **) calloc((size_t) (mysize+1), sizeof(char *));
	if (!help) fatal_error("memory exhausted");
 
	a = help;
	b = decode;
	for (j=0; j<table_size; j++) *a++ = *b++;
	if (decode) (void)free((char *)decode);
	
	decode   = help; 
	table_size = mysize;
}

#ifdef ANSI_C
void FreeHash(void)
#else
void FreeHash()
#endif
{
	if (decode) (void)free((char *)decode);
	decode   = (char **)0; 
	if (hashtable) (void)free((char *)hashtable);
        hashtable  = (hashentry *)0;
}


/*--------------------------------------------------------------------*/
/* Hash table for identifers and strings                              */
/*--------------------------------------------------------------------*/


/* the hash function */

#ifdef ANSI_C
static int hash(register char *string)
#else
static int hash(string)
char *string;
#endif
{
        register int   hashval = 0 ;
        register char *s = string;

        for(hashval=0; *s != '\0';)
                hashval = (10*hashval - 48 + *s++) % hash_size;
        hashval = ((hashval<0 ) ? -hashval : hashval);

        return(hashval % hash_size);
        /* Modulo calculation because of table range */
}



/*--------------------------------------------------------------------*/
/* Hash table: visible from outside                                   */
/*--------------------------------------------------------------------*/

#ifdef ANSI_C
long HashInsert(register char *s)
#else
long HashInsert(s)
char *s;
#endif
{
        register  hashentry new_node;
        register  int       hashval;
        register  long      look;
        char *h;

        if (!hashtable) init_hash();

        hashval  = hash(s);
	new_node = hashtable[hashval];
	look = -1L;
        while (new_node != NULL) {
                if ( strcmp(s,decode[new_node->num]) == 0L) {
			look = new_node->num;
			break;
		}
                new_node=new_node->next;
        }

        if (look == -1L) {
                if (hashtop == table_size-1) increase_decode();
                new_node = (hashentry)ParseMalloc(sizeof(struct hash_node));
                look = hashtop++;
                new_node->num  = look;
                new_node->next = hashtable[hashval];

                h = ParseMalloc(strlen(s)+1);
                decode[look]    = strcpy(h,s);
                hashtable[hashval] = new_node;
        }
        return(look);
}

#ifdef ANSI_C
long HashTableSize(void)
#else
long HashTableSize()
#endif
{
        if (!hashtable) init_hash();
	return(hashtop);
}

#ifdef ANSI_C
char *Decode(long x)
#else
char *Decode(x)
long x;
#endif
{
        if (!hashtable) init_hash();
	if (x<0)       return(decode[0]);
	if (x<hashtop) return(decode[x]);
	return(decode[0]);
}


#endif /* HASHGENSTD */

/*--------------------------------------------------------------------*/
 



#line 580 "grammar.pgs"
