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
# /*   description:  Makefile for the demos                             */
# /*   status:       in work                                            */
# /*                                                                    */
# /*--------------------------------------------------------------------*/
# 
# $Id: Makefile,v 1.2 1994/01/21 20:06:38 sander Exp sander $
#
# $Log: Makefile,v $
# Revision 1.2  1994/01/21  20:06:38  sander
# Install problem for Sys V solved.
#
# Revision 1.1  1994/01/03  15:36:21  sander
# Initial revision
#

#========================= CHANGE AREA =========================

# Please update the change area according to your system, if you
# want to call this Makefile directly

# where the binaries go
# BINDIR   = /usr/local/bin/
BINDIR   = /RW/esprit/users/sander/PUBLIC/CMD/

# how the VCG tool should be called
# For the Sunview version I use the name vcg.
# For the X11 version I prefer the name xvcg.
# VCGTOOL = vcg
VCGTOOL = xvcg

# Used during the demoanimations:
# where the vcg is during the tests.
# Please enter the absolute path to the vcg-tool.  
# VCGCALL   = /usr/local/bin/vcg
VCGCALL  = /RW/esprit/users/sander/PUBLIC/CMD/xvcg

#-------------------------- Flags ------------------------------

# Flags for the C compiler 
# Important: Do not use -Dlint with gcc. This causes confusion
# during linking (!!!), e.g. some undefined messages. 
CFLAGS 	 = -O -finline-functions -c
#CFLAGS 	 = -g -finline-functions  -Wall 

# Flags for the C linker. The last flag should always be -o
CLINKFLAGS = -o

# Flags for the C linker
CLIBFLAGS = -o

# Flags for debugging
DFLAGS 	 =

# Include directories
INCLUDES =

#-------------------------- Tools ------------------------------

# C compiler
CC 	= gcc

# C linker 
#CCLINK  = gcc -static
CCLINK  = gcc 

# Install software. You can use /bin/cp instead of /bin/install.
# I prefer that binaries are stripped.
# For directories:
INSTALLDIR = /bin/install -d -m 755

# For binary files:
# assume that you want to install a file called dummy.
INSTALL = /bin/install -s -m 755 dummy $(BINPATH)/dummy

# RCS check out shellscript
CHECKOUT = co

# RCS check edit shellscript
CHECKEDIT = ce

# RCS check in shellscript
CHECKIN  = ci 

# MakeDepend (should understand the -f option)
DEPEND   = makedepend

# Remove File
RM       = /bin/rm 

#==================== END OF CHANGE AREA ======================


#-------------------------- Files ------------------------------

# C - Files
CFILES	= animation1.c animation2.c pbmrot90.c pbmshift.c vcgdemomaker.c \
	  animation3.c vcgcount.c pbm2hp.c

# Generated C - Files
GCFILES	 = 

# Header - Files
HFILES 	= 

# Generated Header - Files
GHFILES	= 

# Generated Other - Files
GOFILES  = animfile1.vcg animfile2.vcg rbtree.vcg
 
# Object - Files
OFILES	= animation1.o animation2.o pbmrot90.o pbmshift.o vcgdemomaker.o \
	  animation3.o vcgcount.o pbm2hp.o

# Files we want to install by `make install'
INSTALLBINARIES = pbmrot90 pbmshift pbm2hp vcgdemomaker

SOURCES	= $(CFILES) $(HFILES) demo.csh.tpl README

#-------------------------- Rules ------------------------------

all: animation1 animation2 animation3 pbmrot90 pbmshift vcgdemomaker pbm2hp \
	vcgcount

animation1: animation1.o
	$(CCLINK) $(CLINKFLAGS) animation1 animation1.o 

animation2: animation2.o
	$(CCLINK) $(CLINKFLAGS) animation2 animation2.o 

animation3: animation3.o
	$(CCLINK) $(CLINKFLAGS) animation3 animation3.o 

vcgcount: vcgcount.o
	$(CCLINK) $(CLINKFLAGS) vcgcount vcgcount.o 

vcgdemomaker: vcgdemomaker.o
	$(CCLINK) $(CLINKFLAGS) vcgdemomaker vcgdemomaker.o 

pbmrot90: pbmrot90.o
	$(CCLINK) $(CLINKFLAGS) pbmrot90 pbmrot90.o 

pbmshift: pbmshift.o
	$(CCLINK) $(CLINKFLAGS) pbmshift pbmshift.o 

pbm2hp: pbm2hp.o
	$(CCLINK) $(CLINKFLAGS) pbm2hp pbm2hp.o 

.SUFFIXES: .c .o 

# Standard rule:
#
.c.o:  
	$(CC) $(CFLAGS) $(DFLAGS) $(INCLUDES) -DBINDIR=\"$(BINDIR)\" \
         -DVCGTOOL=\"$(VCGTOOL)\" -DVCGCALL=\"$(VCGCALL)\" $<

$(SOURCES):
	$(CHECKOUT) $@


# We do not install everything but only the useful tools
#
install: $(INSTALLBINARIES)
	- $(INSTALLDIR) $(BINDIR)
	for i in $(INSTALLBINARIES) ;\
	do \
	m=`echo $(INSTALL) | $(SED) -e "s/dummy/$$i/g"`; \
	$$m; \
	done


makefiles: Makefile

# Cleanup rules
#
clean: makefiles
	$(RM) -f $(OFILES) y.tab.cy *.output *.vcg stamp-*

veryclean: makefiles clean targetclean 
	$(RM) -f core $(OFILES) $(GCFILES) $(GHFILES) $(GOFILES)

targetclean: makefiles
	$(RM) -f animation1 animation2 animation3 vcgcount \
		pbmrot90 pbmshift pbm2hp vcgdemomaker

distclean: veryclean targetclean
	$(RM) -f core demo.csh 

# Auxiliary rules
#
depend: Makefile $(CFILES) $(HFILES) $(GCFILES) $(GHFILES)
	$(DEPEND) $(INCLUDES) -fMakefile $(CFILES) $(GCFILES) 

checkout: Makefile $(SOURCES)

checkedit: Makefile
	$(CHECKEDIT) $(SOURCES)

checkin: Makefile
	$(CHECKIN) $(SOURCES)

tar: Makefile $(SOURCES)
	tar -cf demo.tar Makefile $(SOURCES)

dist: tar 

# DO NOT DELETE THIS LINE -- make depend depends on it.

