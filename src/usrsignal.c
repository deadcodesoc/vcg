/* SCCS-info %W% %E% */

/*--------------------------------------------------------------------*/
/*                                                                    */
/*              VCG : Visualization of Compiler Graphs                */
/*              --------------------------------------                */
/*                                                                    */
/*   file:         usrsignal.h                                        */
/*   version:      1.00.00                                            */
/*   creation:     15.10.1993                                         */
/*   author:       I. Lemke  (...-Version 0.99.99)                    */
/*                 G. Sander (Version 1.00.00-...)                    */  
/*                 Universitaet des Saarlandes, 66041 Saarbruecken    */
/*                 ESPRIT Project #5399 Compare                       */
/*   description:  Signal handling                                    */
/*   status:       in work                                            */
/*                                                                    */
/*--------------------------------------------------------------------*/

#ifndef lint
static char *id_string="$Id: usrsignal.c,v 3.3 1995/02/08 11:11:14 sander Exp $";
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
 * $Log: usrsignal.c,v $
 * Revision 3.3  1995/02/08  11:11:14  sander
 * Distribution version 1.3.
 *
 * Revision 3.2  1994/12/23  18:12:45  sander
 * Manhatten layout added.
 * Option interface cleared.
 * infobox behaviour improved.
 * First version of fisheye (carthesian).
 * Options Noedge and nonode.
 *
 * Revision 3.1  1994/03/01  10:59:55  sander
 * Copyright and Gnu Licence message added.
 * Problem with "nearedges: no" and "selfloops" solved.
 *
 * Revision 2.2  1994/01/21  19:33:46  sander
 * VCG Version tested on Silicon Graphics IRIX, IBM R6000 AIX and Sun 3/60.
 * Option handling improved. Option -grabinputfocus installed.
 * X11 Font selection scheme implemented. The user can now select a font
 * during installation.
 * Sun K&R C (a nonansi compiler) tested. Some portabitility problems solved.
 *
 * Revision 2.1  1993/12/08  21:20:09  sander
 * Reasonable fast and stable version
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "grammar.h"
#include "alloc.h"
#include "main.h"
#include "options.h"
#include "draw.h"
#include "usrsignal.h"

#ifdef USR_SIGNAL

#include <signal.h>
#ifdef VMS
#include <types.h>
#else
#include <sys/types.h>
#endif

/* define this for debugging */

#undef SIGNAL_DEBUG

/* Local Prototypes */
/*------------------*/

static int  animation_handler   _PP((int signl));
static int windowclose_handler  _PP((int signl));


/* External, device dependent prototypes */
/*---------------------------------------*/

extern void gs_open           _PP((void));
extern void gs_close          _PP((void));
extern void m_reload          _PP((void));
extern int anim_flag;

/*--------------------------------------------------------------------*/

/*  Touch actual specification file         
 *  -------------------------------
 *  This is used to indicate that the specification file is loaded after
 *  a signal. If we cannot touch, the touch_file should be specified
 *  negative. Then we send signals SIGUSR1 to the parent process
 *  instead of touching the file.      
 */

 
static char buffer[1024];

#ifdef ANSI_C
void touch_specification(void)
#else
void touch_specification()
#endif
{
	int parent_pid;

	if (!touch_file) return;
	if (touch_file<0) {
		parent_pid = getppid();
		sleep(1-touch_file);
#ifdef SIGNAL_DEBUG
		PRINTF("kill %d %d\n",- SIGUSR1,parent_pid);
#endif
		SPRINTF(buffer,"kill %d %d\n",- SIGUSR1,parent_pid);
		system(buffer);
		return;
	}
	if (!Dataname[0]) return;
	if (strcmp(Dataname,"-")==0) return;
	sleep(touch_file);
	SPRINTF(buffer,"touch %s\n",Dataname);
	system(buffer);
}


/*--------------------------------------------------------------------*/

/*  Signal Handler for USR1 and USR2        
 *  ================================           
 */


/*
 *  Signal Handler Semaphore
 *  ------------------------
 *  Before all actions changing internal data structures, we have to
 *  disable signals. Afterwards, we enable signals.
 */


static int signal_allowed;

#ifdef ANSI_C
void enable_signal(void)
#else
void enable_signal()
#endif
{
	debugmessage("enable_signal","");
	signal_allowed = 1;
}

#ifdef ANSI_C
void disable_signal(void)
#else
void disable_signal()
#endif
{
	debugmessage("disable_signal","");
	signal_allowed = 0;
}


/*
 *  Signal Handler for Signal USR1
 *  ------------------------------
 */


#ifdef ANSI_C
static int animation_handler(int signl)
#else
static int animation_handler(signl)
int 	signl;
#endif
{
	debugmessage("animation_handler. Incoming signal ",my_itoa(signl));
	set_signal();
	enable_signal();
#ifdef SIGNAL_DEBUG
	PRINTF("Got signal %d\n",signl);
#endif
	if (signal_allowed) {
		disable_signal();
		anim_flag = 1;
		m_reload();
		gs_open();
		anim_flag = 0;
		enable_signal();
		touch_specification();
	}
	else 
		FPRINTF(stderr,"Signal USR1 ignored. Sorry !\n");
	return(0);
}


/*
 *  Signal Handler for Signal USR2
 *  ------------------------------
 */

#ifdef ANSI_C
static int windowclose_handler(int signl)
#else
static int windowclose_handler(signl)
int 	signl;
#endif
{
	debugmessage("windowclose_handler. Incoming signal ",my_itoa(signl));
	set_signal();
	enable_signal();
#ifdef SIGNAL_DEBUG
	PRINTF("Got signal %d\n",signl);
#endif
	if (signal_allowed) {
		disable_signal();
		gs_close();
		enable_signal();
		touch_specification();
	}
	else 
		FPRINTF(stderr,"Signal USR2 ignored. Sorry !\n");
	return(0);
}


/*
 *  Initialisation of Signal Handler
 *  --------------------------------
 *  This has to be done before the first signal is recognized.
 */

 
#ifdef ANSI_C
void set_signal(void)
#else
void set_signal()
#endif
{
	debugmessage("set_signal","");
#ifdef SIGNAL_DEBUG
	PRINTF("Install signals\n");
#endif
	disable_signal();
	if ( (int)signal(SIGUSR1,(void (*)())animation_handler) == -1 ) {
        	FPRINTF(stderr,"Can't set USR1 process signal.\n");
		exit(-1);  /* not gs_exit, because the device is not there */
	}
	if ( (int)signal(SIGUSR2,(void (*)())windowclose_handler) == -1 ) {
        	FPRINTF(stderr,"Can't set USR2 process signal.\n");
		exit(-1);
	}
}


#else

/*  USR_SIGNAL undefined:
 *  If process signals are not available, we use dummy functions.
 */

void touch_specification() {}
void set_signal()     {}
void enable_signal()  {}
void disable_signal() {}

#endif /* USR_SIGNAL */



