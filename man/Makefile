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
# /*   description:  Makefile for the manual pages                      */
# /*   status:       in work                                            */
# /*                                                                    */
# /*--------------------------------------------------------------------*/
# 
# $Id: Makefile,v 1.3 1994/01/21 19:54:22 sander Exp sander $
#
# $Log: Makefile,v $
# Revision 1.3  1994/01/21  19:54:22  sander
# Manual page extension changed to man.
# Install problems solved for Sys V and IBM R6000.
#
# Revision 1.2  1994/01/04  11:42:04  sander
# vcg.man added.
#
# Revision 1.1  1994/01/03  18:18:23  sander
# Initial revision
#
#

#========================= CHANGE AREA =========================

# Please update the change area according to your system, if you
# want to call this Makefile directly

# where the manual pages go
# MANDIR = /usr/local/man/manl/ 
MANDIR   = /RW/esprit/users/sander/PUBLIC/MAN/

# How the manual pages should be called
MANEXT = l

#-------------------------- Tools ------------------------------

# Install software. You can use /bin/cp instead of /bin/install.
# For directories:
# INSTALLDIR = /bin/install -d -m 755
INSTALLDIR = echo

# For manual pages:
# Assume that you want to install a file called dummy.
INSTALLMAN = /bin/install -m 644 dummy $(MANDIR)/dummy

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

# Link Files (or Copy them)
LN       = /bin/ln -s

# Copy Files 
CP       = /bin/cp

# Stream editor
SED      = sed

#==================== END OF CHANGE AREA ======================


#-------------------------- Files ------------------------------

# Manual Page - Files
MANFILES = pbmrot90.man pbmshift.man pbm2hp.man vcgdemomaker.man vcg.man

# Manual Pages we want to install
INSTALLMANPAGES = pbmrot90 pbmshift pbm2hp vcgdemomaker vcg

SOURCES	= $(MANFILES) 

#-------------------------- Rules ------------------------------

all: install 

$(SOURCES):
	$(CHECKOUT) $@


# We do not install everything but only the useful tools
#
install: $(MANFILES) 
	-$(INSTALLDIR) $(MANDIR)
	$(CP) vcg.man xvcg.man
	for i in $(INSTALLMANPAGES) xvcg;\
	do \
	case "$(MANEXT)" in \
	   man) ;;          \
	   *)   $(RM) -f $$i.$(MANEXT); $(CP) $$i.man $$i.$(MANEXT) ;;\
	esac; \
	m=`echo $(INSTALLMAN) | $(SED) -e "s/dummy/$$i.$(MANEXT)/g"`; \
	$$m; \
	done


makefiles: Makefile

# Cleanup rules
#
clean: makefiles
	$(RM) -f xvcg.man stamp-* 
	case "$(MANEXT)" in \
	   man) ;;          \
	   *)   $(RM) -f *.$(MANEXT);;\
	esac; 
	for i in $(INSTALLMANPAGES);\
	do \
	  $(RM) -f $$i.ps; \
	done

veryclean: clean targetclean 

targetclean: makefiles

distclean: veryclean targetclean
	$(RM) -f core 

# Auxiliary rules
#
depend: 

checkout: Makefile $(SOURCES)

checkedit: Makefile
	$(CHECKEDIT) $(SOURCES)

checkin: Makefile
	$(CHECKIN) $(SOURCES)

tar: Makefile $(SOURCES)
	tar -cf manpages.tar Makefile $(SOURCES)

mandoc: $(MANFILES)
	for i in $(INSTALLMANPAGES);\
	do \
	  myptroff ../docsrc/docutils/tmac.gs -t $$i.man > $$i.ps; \
	  $(CP)  $$i.ps ../doc; \
	done

dist: tar mandoc

# DO NOT DELETE THIS LINE -- make depend depends on it.

