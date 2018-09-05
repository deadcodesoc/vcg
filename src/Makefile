# SCCS-info %W% %E%
#
# /*--------------------------------------------------------------------*/
# /*                                                                    */
# /*              VCG : Visualization of Compiler Graphs                */
# /*              --------------------------------------                */
# /*                                                                    */
# /*   file:         Makefile                                           */
# /*   version:      1.00.00                                            */
# /*   creation:     1.4.1993                                           */
# /*   author:       I. Lemke  (...-Version 0.99.99)                    */
# /*                 G. Sander (Version 1.00.00-...)                    */  
# /*                 Universitaet des Saarlandes, W-66041 Saarbruecken  */
# /*                 ESPRIT Project #5399 Compare                       */
# /*   description:  Makefile for vcg                                   */
# /*   status:       in work                                            */
# /*                                                                    */
# /*--------------------------------------------------------------------*/
# 
# $Id: Makefile,v 2.2 1994/01/21 19:39:53 sander Exp sander $
#
# $Log: Makefile,v $
# Revision 2.2  1994/01/21  19:39:53  sander
# Some portabitility problems solved for IBM R6000, Silicon Graphics IRIX
# and Sun 3/60 K&R C.
#
# Revision 2.1  1993/12/08  21:23:15  sander
# Reasonable fast and stable version
#
#

#========================= CHANGE AREA =========================

# Please update the change area according to your system, if you
# want to call this Makefile directly

# where the binaries go
# BINDIR = /usr/local/bin/
BINDIR 	 = /RW/esprit/users/sander/PUBLIC/CMD/

# how the VCG tool should be called
# For the Sunview version I use the name vcg. 
# For the X11 version I prefer the name xvcg. 
# VCGTOOL = vcg
VCGTOOL = xvcg

#-------------------------- Flags ------------------------------

# Flags for the C compiler 
# Important: Do not use -Dlint with gcc. This causes confusion
# during linking (!!!), e.g. some undefined messages. 
#CFLAGS 	 = -c -O -finline-functions 
CFLAGS 	 = -c -g -finline-functions  -Wall 

# Flags for debugging
DFLAGS 	 =

# Flags for linking
#CLINKFLAGS = -o
CLINKFLAGS = -o

# Include directories
# If you use gcc, it may happen that not all ANSI header files
# are on the right place. Example: we often have problems to
# find stdarg.h. Look for this file and add the directory here,
# e.g.:
# INCLUDES = /usr/local/include/gnuansi/
#
# For Sunview, this should be enough, because on Suns, Sunview
# is normally installed in standard directories:
# INCLUDES = 
#
# For X11, it depends where it is installed. Look for Xlib.h,
# Xproto.h or Xutil.h. 
# For instance, if you find /usr/local/X11/include/X11/Xlib.h
# then please use
# INCLUDES = -I/usr/local/X11/include/
INCLUDES = -I/RW/esprit/X11R5/include/

# Library directories
# For Sunview, this should be enough, because on Suns, Sunview
# is normally installed in standard directories:
# LIBPATH = 
#
# For X11, it depends where it is installed. Look for libX.a,
# or libX11.so.<version_number>, or libXext.a, etc. 
# For instance, if you find /usr/local/X11/lib/libX11.a
# then please use
# INCLUDES = -I/usr/local/X11/lib/
LIBPATH = -L/RW/esprit/X11R5/lib/


# Libraries
# Libraries for SunView
# LIBRARIES = -lsuntool -lsunwindow -lpixrect -lm 
#
# Libraries for X11 
LIBRARIES = -lXext -lX11 -lm 

#-------------------------- Tools ------------------------------

# C compiler
CC 	= gcc 

# C linker 
CCLINK  = gcc 
#CCLINK  = gcc 

# If you use gcc and the sun driver, you need the normal sun
# preprocessor because of incompatibilities of the system libraries
CPP     = cc -E

# If you dont need a special preprocessor, change the .c.o rule or
# define this:
#CPP    = cat

# Install software. You can use /bin/cp instead of /bin/install.
# I prefer that binaries are stripped.
# For directories:
INSTALLDIR = /bin/install -d -m 755

# For binary files:
# Assume that you want to install s file called dummy.
INSTALL = /bin/install -s -m 755 dummy $(BINDIR)/dummy

# RCS check out shellscript
CHECKOUT = co

# RCS check edit shellscript
CHECKEDIT = ce

# RCS check in shellscript
CHECKIN  = ci 

# parser pregenerator. If the files grammar.y and grammar.l
# are available, you don't need this.
PARSEGEN = parsegen

# lex-compatible scanner generator
LEX	= flex

# yacc-compatible parser generator. Currently, it does not work 
# with yacc because some bison features are used directly.
YACC     = /usr/local/bin/bison -ydvt

# MakeDepend (should understand the -f option)
DEPEND   = makedepend

# Streameditor
# SED = /bin/sed
SED = /bin/sed

# Move File
MV       = /bin/mv

#Copy File
CP       = /bin/cp

# Remove File
RM       = /bin/rm 

#==================== END OF CHANGE AREA ======================

#-------------------------- Files ------------------------------

# C - Files
CFILES	= main.c options.c alloc.c step0.c step1.c step2.c step3.c step4.c\
	  prepare.c folding.c draw.c drawlib.c usrsignal.c \
	  grprint.c grprint2.c sunvdev.c X11dev.c X11devpb.c\
	  X11devla.c X11devcl.c X11devti.c X11devfs.c PSdev.c\
	  tree.c timelim.c fisheye.c infobox.c X11devfe.c \
	  X11devvw.c drawstr.c PSdevstr.c grprintstr.c X11devst.c \
	  streedebug.c

# Generated C - Files
GCFILES	 = y.tab.c lex.yy.c

# Header - Files
HFILES 	= main.h options.h alloc.h steps.h folding.h draw.h drawlib.h \
	  usrsignal.h grprint.h timing.h X11devpb.h X11devla.h\
	  X11devcl.h X11devti.h X11devfs.h PSdev.h timelim.h fisheye.h \
	  infobox.h X11devfe.h X11devvw.h drawstr.h drawchr.h

# Generated Header - Files
GHFILES	= y.tab.h grammar.h 

# Generated Other - Files
GOFILES  = grammar.l grammar.y
 
# Object - Files
OFILES	= y.tab.o lex.yy.o main.o options.o alloc.o step0.o folding.o  \
	  step1.o step2.o step3.o step4.o prepare.o draw.o             \
	  drawlib.o usrsignal.o grprint.o grprint2.o        \
	  sunvdev.o X11dev.o X11devpb.o X11devla.o X11devcl.o  \
	  X11devti.o X11devfs.o PSdev.o tree.o \
	  timelim.o fisheye.o infobox.o X11devfe.o X11devvw.o \
	  drawstr.o PSdevstr.o grprintstr.o X11devst.o

# These files are generated, but included into a distribution.
# They are in the directory preconf.
GEN_DISTFILES = $(GCFILES) $(GHFILES) $(GOFILES)


# Files we want to install by `make install'
INSTALLBINARIES = $(VCGTOOL) 


SOURCES	= grammar.pgs globals.h.tpl ultrixpreconf $(CFILES) $(HFILES)


#-------------------------- Rules ------------------------------

all: $(VCGTOOL) 

$(VCGTOOL): $(OFILES)
	$(CCLINK) $(CLINKFLAGS) $(VCGTOOL) $(OFILES) $(LIBPATH) $(LIBRARIES)  

.SUFFIXES: .c .o 

# Standard rule:
#
# If an explicit preprocessor CPP is needed
#.c.o:
#	$(CPP) $(CFLAGS) $(DFLAGS) $(INCLUDES) -DBINDIR=\"$(BINDIR)\"  \
#	  $< > tmp.c
#	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDES) tmp.c
#	$(MV) tmp.o $*.o
#	$(RM) -f tmp.c

# If no explicit preprocessor CPP is needed
.c.o:  
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDES) -DBINDIR=\"$(BINDIR)\" \
         $<

y.tab.c \
y.tab.h : grammar.y
	$(YACC) grammar.y \
	|| $(CP) preconf/y.tab.c preconf/y.tab.h .

lex.yy.c: grammar.l
	$(LEX) grammar.l \
	|| $(CP) preconf/lex.yy.c .


grammar.l \
grammar.y \
grammar.h : grammar.pgs
	$(PARSEGEN) -s -t grammar.pgs \
	|| $(CP) preconf/grammar.l preconf/grammar.y preconf/grammar.h .

pref:	grammar.y grammar.l grammar.h y.tab.c y.tab.h lex.yy.c
	$(CP) grammar.y grammar.l grammar.h y.tab.c y.tab.h lex.yy.c preconf

$(SOURCES):
	$(CHECKOUT) $@

globals.h:
	@ echo "You must configure first. See ../README."
	@ echo " "
	exit 1

# We do not install everything but only the useful tools
#
install: $(INSTALLBINARIES)
	-$(INSTALLDIR) $(BINDIR)
	for i in $(INSTALLBINARIES) ;\
	do \
	m=`echo $(INSTALL) | $(SED) -e "s/dummy/$$i/g"`; \
	$$m; \
	done

makefiles: Makefile

# Cleanup rules
#
clean: makefiles
	$(RM) -f $(OFILES) y.tab.cy *.output stamp-* grammar.pgs.txt

veryclean: makefiles clean 
	$(RM) -f core $(OFILES) $(GCFILES) $(GHFILES) $(GOFILES)

targetclean: makefiles
	$(RM) -f vcg xvcg $(VCGTOOL)

distclean: veryclean targetclean
	$(RM) -f core globals.h

depend: Makefile $(CFILES) $(HFILES) $(GCFILES) $(GHFILES) globals.h
	$(DEPEND) $(INCLUDES) -fMakefile $(CFILES) $(GCFILES) 

checkout: Makefile $(SOURCES)

checkedit: Makefile
	$(CHECKEDIT) $(SOURCES)

checkin: Makefile
	$(CHECKIN) $(SOURCES)

tar: Makefile $(SOURCES) $(GEN_DISTFILES)
	$(RM) -f preconf/*
	$(CP) $(GEN_DISTFILES) preconf
	tar -cf vcg.tar Makefile $(SOURCES) preconf

dist: tar


# DO NOT DELETE THIS LINE -- make depend depends on it.

