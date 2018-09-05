
$ on error then continue
$ on severe_error then continue
$!CC/DEBUG 	syntax.c
$!CC/DEBUG 	lexical.c
$!CC/DEBUG 	main.c
$!CC/DEBUG 	options.c
$!CC/DEBUG 	alloc.c
$!CC/DEBUG 	step0.c
$!CC/DEBUG 	step1.c
$!CC/DEBUG 	step2.c
$!CC/DEBUG 	step3.c
$!CC/DEBUG 	step4.c
$!CC/DEBUG 	prepare.c
$!CC/DEBUG 	folding.c
$!CC/DEBUG 	draw.c
$!CC/DEBUG 	drawlib.c
$!CC/DEBUG 	drawstr.c
$!CC/DEBUG 	usrsignal.c
$!CC/DEBUG 	grprint.c
$!CC/DEBUG 	grprint2.c
$!CC/DEBUG 	grprintstr.c
$!CC/DEBUG 	X11dev.c
$!CC/DEBUG 	X11devpb.c
$!CC/DEBUG 	X11devla.c
$!CC/DEBUG 	X11devcl.c
$!CC/DEBUG 	X11devst.c
$!CC/DEBUG 	X11devti.c
$!CC/DEBUG 	X11devfs.c
$!CC/DEBUG 	X11devfe.c
$!CC/DEBUG 	X11devvw.c
$!CC/DEBUG 	PSdev.c
$!CC/DEBUG 	PSdevstr.c
$!CC/DEBUG 	tree.c
$!CC/DEBUG 	timelim.c
$!CC/DEBUG 	fisheye.c
$!CC/DEBUG 	infobox.c
$!CC/DEBUG 	alloca.c
$LINK/EXE=XVCG.EXE syntax.obj, lexical.obj, main.obj, options.o, -
alloc.obj, step0.obj, step1.obj, step2.obj, step3.obj, step4.obj, -
prepare.obj, folding.obj, draw.obj, drawlib.obj, drawstr.obj, -
usrsignal.obj, grprint.obj, grprint2.obj, grprintstr.obj, X11dev.obj, -
X11devpb.obj, X11devla.obj, X11devcl.obj, X11devst.obj, X11devti.obj, -
X11devfs.obj, X11devfe.obj, X11devvw.obj, PSdev.obj, PSdevstr.obj, -
tree.obj, timelim.obj, fisheye.obj, infobox.obj, alloca.obj, -
VCG$SRC:dxm_link.opt/options
$!/bin/touch stamp-src	

