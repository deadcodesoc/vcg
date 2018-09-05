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
# /*   description:  Makefile of the documentation                      */
# /*                 D 3.12.1/1: The visualisation of compiler graphs   */
# /*   status:       in work                                            */
# /*                                                                    */
# /*--------------------------------------------------------------------*/
#
# $Id$
#
# $Log$
#

#========================= CHANGE AREA =========================

SHELL = /bin/sh
RM = /bin/rm 
CP = /bin/cp 

# RCS check out shellscript (normally not used)
CHECKOUT = co

# RCS check edit shellscript (normally not used)
CHECKEDIT = ce

# RCS check in shellscript (normally not used)
CHECKIN  = ci

#==================== END OF CHANGE AREA ======================

#-------------------------------------------------------------------

# The LaTeX source files

SOURCES = README README.SYS README.ANNOUNCE README.ANNOUNCE2 README.ANNOUNCE3

DISTFILES = visual.ps vcg.ps pbm2hp.ps pbmrot90.ps pbmshift.ps \
	    vcgdemomaker.ps \
	    grammar.txt 

#-------------------------------------------------------------------- 

all: 

long: 

short: 


# Please, never do a "make grammar".
# This is only for me. (GS)
#
grammar:
	(cd ../docsrc/docutils; \
 	extract_gramm ../../src/grammar.pgs; \
 	prepare_gramm ../../src/grammar.pgs.txt > ../../doc/grammar.txt)


# RCS Version control stuff
	
$(SOURCES):
	$(CHECKOUT) $@

checkout: Makefile $(SOURCES) 

checkedit: Makefile
	$(CHECKEDIT) $(SOURCES)

checkin: Makefile
	$(CHECKIN) $(SOURCES) 


clean:
	$(RM) -f *.aux *.toc *.log *.lof *.lot *.spell tmp* core
 
veryclean: clean
	$(RM) -f *.dvi 

targetclean: veryclean

distclean: veryclean targetclean 
	$(RM) -f core

install:

depend: 

tar: Makefile $(SOURCES) $(DISTFILES) 
	tar -cf doc.tar Makefile $(SOURCES) $(DISTFILES) 

dist: grammar tar


