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
# /*   description:  Makefile for the examples                          */
# /*   status:       in work                                            */
# /*                                                                    */
# /*--------------------------------------------------------------------*/
# 
# $Id$
#
# $Log$
#

#========================= CHANGE AREA =========================

# Please update the change area according to your system, if you
# want to call this Makefile directly

# RCS check out shellscript
CHECKOUT = co

# RCS check edit shellscript
CHECKEDIT = ce

# RCS check in shellscript
CHECKIN  = ci 

# Remove File
RM       = /bin/rm 

# Copy Files 
CP       = /bin/cp

#==================== END OF CHANGE AREA ======================


#-------------------------- Files ------------------------------

SOURCES	=  README anchors.vcg annot1.vcg annot2.vcg ccmir.vcg \
		civ.vcg colors.vcg forms.vcg tstree.vcg levels.vcg \
		hsort.vcg hunsort.vcg forms2.vcg shells.vcg xerox.vcg\
		softmain.vcg tree1.vcg tree2.vcg morecol.vcg \
	        fishex2a.vcg fishex2b.vcg fishex3a.vcg fishex3b.vcg \
	        softmain2.vcg fishex3c.vcg charset.vcg flchrt.vcg \
	        cfg.vcg structs.vcg pshar1.vcg pshar2.vcg pshar3.vcg \
		pshar4.vcg

#-------------------------- Rules ------------------------------

all: install 

$(SOURCES):
	$(CHECKOUT) $@


install:

makefiles: Makefile

# Cleanup rules
#
clean: makefiles

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
	tar -cf expl.tar Makefile $(SOURCES)

dist: tar

# DO NOT DELETE THIS LINE -- make depend depends on it.

