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
# /*   description:  Config Makefile                                    */
# /*   status:       in work                                            */
# /*                                                                    */
# /*--------------------------------------------------------------------*/
#
# $Id$
#
# $Log$
#

SHELL = /bin/sh

#-------------------------- Rules ------------------------------

#all: stamp-all

all: xvcg_gcc xvcg

configure: stamp-config


# Rules to preconfigure very fast

xcompare:
	touch stamp-doc
	touch stamp-shortdoc
	if (test ! -r tMakefile) then \
		(cd preconf/X11; /bin/rm -f Makefile x11setup x11setup2; \
		  xmkmf; make | sed -e "s/^make.*//" > x11setup); \
		(cd preconf; cd X11compare; \
		  /bin/cp tMakefile ../../Make.tmp; \
		  /bin/cp globals.h ../../src; \
		  /bin/cp demo.csh ../../demo/demo.tmp); \
		/bin/rm -f tMakefile demo/demo.csh; \
		cat preconf/X11/x11setup  Make.tmp > tMakefile; \
		cat preconf/X11/x11setup2 demo/demo.tmp > demo/demo.csh; \
	fi   

xvcg_cc:
	if (test ! -r tMakefile) then \
		(cd preconf/X11; /bin/rm -f Makefile x11setup x11setup2; \
		  xmkmf; make | sed -e "s/^make.*//" > x11setup); \
		(cd preconf; cd X11cc`uname -s`; \
		  /bin/cp tMakefile ../../Make.tmp; \
		  /bin/cp globals.h ../../src; \
		  /bin/cp demo.csh ../../demo/demo.tmp); \
		/bin/rm -f tMakefile demo/demo.csh; \
		cat preconf/X11/x11setup  Make.tmp > tMakefile; \
		cat preconf/X11/x11setup2 demo/demo.tmp > demo/demo.csh; \
	fi   

xvcg_gcc:
	if (test ! -r tMakefile) then \
		(cd preconf/X11; /bin/rm -f Makefile x11setup x11setup2; \
		  xmkmf; make | sed -e "s/^make.*//" > x11setup); \
		(cd preconf; cd X11gcc`uname -s`; \
		  /bin/cp tMakefile ../../Make.tmp; \
		  /bin/cp globals.h ../../src; \
		  /bin/cp demo.csh ../../demo/demo.tmp); \
		/bin/rm -f tMakefile demo/demo.csh; \
		cat preconf/X11/x11setup  Make.tmp > tMakefile; \
		cat preconf/X11/x11setup2 demo/demo.tmp > demo/demo.csh; \
	fi   

xvcg_g++:
	if (test ! -r tMakefile) then \
		(cd preconf/X11; /bin/rm -f Makefile x11setup x11setup2; \
		  xmkmf; make | sed -e "s/^make.*//" > x11setup); \
		(cd preconf; cd X11g++`uname -s`; \
		  /bin/cp tMakefile ../../Make.tmp; \
		  /bin/cp globals.h ../../src; \
		  /bin/cp demo.csh ../../demo/demo.tmp); \
		/bin/rm -f tMakefile demo/demo.csh; \
		cat preconf/X11/x11setup  Make.tmp > tMakefile; \
		cat preconf/X11/x11setup2 demo/demo.tmp > demo/demo.csh; \
	fi   

xvcg_c89:
	if (test ! -r tMakefile) then \
		(cd preconf/X11; /bin/rm -f Makefile x11setup x11setup2; \
		  xmkmf; make | sed -e "s/^make.*//" > x11setup); \
		(cd preconf; cd X11c89`uname -s`; \
		  /bin/cp tMakefile ../../Make.tmp; \
		  /bin/cp globals.h ../../src; \
		  /bin/cp demo.csh ../../demo/demo.tmp); \
		/bin/rm -f tMakefile demo/demo.csh; \
		cat preconf/X11/x11setup  Make.tmp > tMakefile; \
		cat preconf/X11/x11setup2 demo/demo.tmp > demo/demo.csh; \
	fi   

xvcg_cc_noxmkmf:
	if (test ! -r tMakefile) then \
		(cd preconf/X11; /bin/cp ../x11setup ../x11setup2 .); \
		(cd preconf; cd X11cc`uname -s`; \
		  /bin/cp tMakefile ../../Make.tmp; \
		  /bin/cp globals.h ../../src; \
		  /bin/cp demo.csh ../../demo/demo.tmp); \
		/bin/rm -f tMakefile demo/demo.csh; \
		cat preconf/X11/x11setup  Make.tmp > tMakefile; \
		cat preconf/X11/x11setup2 demo/demo.tmp > demo/demo.csh; \
	fi   

xvcg_gcc_noxmkmf:
	if (test ! -r tMakefile) then \
		(cd preconf/X11; /bin/cp ../x11setup ../x11setup2 .); \
		(cd preconf; cd X11gcc`uname -s`; \
		  /bin/cp tMakefile ../../Make.tmp; \
		  /bin/cp globals.h ../../src; \
		  /bin/cp demo.csh ../../demo/demo.tmp); \
		/bin/rm -f tMakefile demo/demo.csh; \
		cat preconf/X11/x11setup  Make.tmp > tMakefile; \
		cat preconf/X11/x11setup2 demo/demo.tmp > demo/demo.csh; \
	fi   

xvcg_c89_noxmkmf:
	if (test ! -r tMakefile) then \
		(cd preconf/X11; /bin/cp ../x11setup ../x11setup2 .); \
		(cd preconf; cd X11c89`uname -s`; \
		  /bin/cp tMakefile ../../Make.tmp; \
		  /bin/cp globals.h ../../src; \
		  /bin/cp demo.csh ../../demo/demo.tmp); \
		/bin/rm -f tMakefile demo/demo.csh; \
		cat preconf/X11/x11setup  Make.tmp > tMakefile; \
		cat preconf/X11/x11setup2 demo/demo.tmp > demo/demo.csh; \
	fi   

vcg_gcc:
	if (test ! -r tMakefile) then \
		(cd preconf; cd SunVgcc`uname -s`; \
		  /bin/cp tMakefile ../../tMakefile; \
		  /bin/cp globals.h ../../src; \
		  /bin/cp demo.csh ../../demo/demo.csh); \
	fi   

vcg_cc:
	if (test ! -r tMakefile) then \
		(cd preconf; cd SunVcc`uname -s`; \
		  /bin/cp tMakefile ../../tMakefile; \
		  /bin/cp globals.h ../../src; \
		  /bin/cp demo.csh ../../demo/demo.csh); \
	fi   

prepare_normal:
	/bin/cp tMakefile preconf/	
	/bin/cp src/globals.h preconf/	
	/bin/cp demo/demo.csh preconf/	

prepare_x11gcc:
	/bin/cp tMakefile preconf/X11gcc`uname -s`/	
	/bin/cp src/globals.h preconf/X11gcc`uname -s`/	
	/bin/cp demo/demo.csh preconf/X11gcc`uname -s`/	

prepare_x11cc:
	/bin/cp tMakefile preconf/X11cc`uname -s`/	
	/bin/cp src/globals.h preconf/X11cc`uname -s`/	
	/bin/cp demo/demo.csh preconf/X11cc`uname -s`/	

prepare_x11c89:
	/bin/cp tMakefile preconf/X11c89`uname -s`/	
	/bin/cp src/globals.h preconf/X11c89`uname -s`/	
	/bin/cp demo/demo.csh preconf/X11c89`uname -s`/	

prepare_sungcc:
	/bin/cp tMakefile preconf/SunVgcc`uname -s`/	
	/bin/cp src/globals.h preconf/SunVgcc`uname -s`/	
	/bin/cp demo/demo.csh preconf/SunVgcc`uname -s`/	

prepare_suncc:
	/bin/cp tMakefile preconf/SunVcc`uname -s`/	
	/bin/cp src/globals.h preconf/SunVcc`uname -s`/	
	/bin/cp demo/demo.csh preconf/SunVcc`uname -s`/	

xvcg vcg: tMakefile
	make -f tMakefile

demonstration test: tMakefile 
	make -f tMakefile test

docu documentation: tMakefile
	make -f tMakefile docu

shortdocu: tMakefile 
	make -f tMakefile shortdocu

dist: tMakefile 
	make -f tMakefile dist 

install: tMakefile 
	make -f tMakefile install

clean: tMakefile 
	make -f tMakefile clean
	/bin/rm -f preconf/X11/x11setup preconf/X11/x11setup2 \
		preconf/X11/Makefile
	/bin/rm -f Make.tmp demo/demo.tmp

targetclean: tMakefile 
	make -f tMakefile targetclean

veryclean: tMakefile clean 
	make -f tMakefile veryclean 

distclean: tMakefile clean 
	make -f tMakefile distclean 
	/bin/rm -f tMakefile src/globals.h demo/demo.csh

configclean:
	/bin/rm -rf tMakefile src/globals.h src/lex.yy.c src/y.tab.c \
	 	    src/y.tab.h stamp-all

tMakefile:
	@echo "Please do make    or make configure   to create the tMakefile"
	@echo "Other options to create the tMakefile:"
	@echo "		make xvcg_gcc"
	@echo "		make xvcg_cc"
	@echo "		make xvcg_c89"
	@echo "		make xvcg_gcc_noxmkmf"
	@echo "		make xvcg_cc_noxmkmf"
	@echo "		make xvcg_c89_noxmkmf"
	@echo "		make vcg_gcc"
	@echo "		make vcg_cc"
 
compare: preconf xcompare xvcg install
	/bin/rm $(PROJECTHOME)/../bin/vcg
	ln -s $(PROJECTHOME)/../bin/xvcg $(PROJECTHOME)/../bin/vcg

stamp-config: config
	/bin/sh config
	/bin/touch stamp-config


