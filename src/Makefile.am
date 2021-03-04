ACLOCAL_AMFLAGS = -I m4

installdir = $(datadir)/$(PACKAGE)
install_PROGRAMS = xmlTableView

xmlTableView_SOURCES = about.xpm \
main.cpp \
trackpoint.h trackpoint.cpp \
xmltablewindow.h xmltablewindow.cpp

xmlTableView_CPPFLAGS = $(GTKMM_CFLAGS) $(CAIRO_CFLAGS) $(LIBXMLXX_CFLAGS) \
-DPROGRAMNAME_LOCALEDIR=\"$(PROGRAMNAME_LOCALEDIR)\" \
-DGETTEXT_PACKAGE=\"${GETTEXT_PACKAGE}\" \
-DNLS=1

xmlTableView_LDADD = $(GTKMM_LIBS) $(CAIRO_LIBS) $(LIBXMLXX_LIBS)

