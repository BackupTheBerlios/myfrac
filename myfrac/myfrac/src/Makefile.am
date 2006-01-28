SUBDIRS = pics

INCLUDES = $(all_includes)

noinst_HEADERS = myfrac.h generator.h genthread.h gradbutton.h \
	gradeditor.h gradient.h gradlist.h gradwidget.h presets.h spline.h \
	view2d.h view3d.h

METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/myfrac.pot

KDE_ICON = myfrac

bin_PROGRAMS = myfrac

myfrac_SOURCES = main.cpp myfrac.cpp generator.cpp genthread.cpp \
	gradbutton.cpp gradeditor.cpp gradient.cpp gradlist.cpp gradwidget.cpp \
	presets.cpp spline.cpp view2d.cpp view3d.cpp

myfrac_LDFLAGS = $(KDE_RPATH) $(all_libraries)

myfrac_LDADD = $(GLLIB) $(LIB_KDEUI) $(LIB_KFILE)

shelldesktopdir   = $(kde_appsdir)/Utilities
shelldesktop_DATA = myfrac.desktop

shellrcdir   = $(kde_datadir)/myfrac
shellrc_DATA = myfracui.rc

kde_conf_DATA = myfracrc
