SUBDIRS = src po
# rpm 16x16

ACLOCAL_AMFLAGS = -I m4

bin_SCRIPTS = xmlTableView.sh

LATERAL_FILES = COMMENTS LICENSE README.md

lateraldir = $(pkgdatadir)
lateral_DATA = $(LATERAL_FILES)

EXTRA_DIST = autogen.sh GTKxmlTableView.sh xmlTableView.sh \
 $(LATERAL_FILES)
# rpm

CLEANFILES =

# desktop files
desktopdir = $(datadir)/applications
desktop_DATA = xmlTableView.desktop

# convenience command for doing Makefile variable substitutions in non-Makefile
# files (scripts, service files, etc.)
do_subst = sed -e 's|@abs_top_srcdir[@]|$(abs_top_srcdir)|g' \
	-e 's|@abs_top_builddir[@]|$(abs_top_builddir)|g' \
	-e 's|@localedir[@]|$(localedir)|g' \
	-e 's|@bindir[@]|$(bindir)|g' \
	-e 's|@libexecdir[@]|$(libexecdir)|g' \
	-e 's|@pkglibdir[@]|$(pkglibdir)|g' \
	-e 's|@pkgdatadir[@]|$(pkgdatadir)|g' \
	-e 's|@have_libnotify[@]|$(HAVE_LIBNOTIFY)|g' \
	-e 's|@have_libsoup[@]|$(HAVE_LIBSOUP)|g' \
	-e 's|@have_cheese[@]|$(HAVE_CHEESE)|g'

xmlTableView.sh: xmlTableView.sh.in
	$(AM_V_GEN) $(do_subst) $< > $@
	chmod +x $@

xmlTableView.desktop: xmlTableView.desktop.in
	$(AM_V_GEN) $(do_subst) $< > $@
	chmod +x $@

CLEANFILES += xmlTableView.sh
EXTRA_DIST += xmlTableView.desktop.in xmlTableView.sh.in

# application icon 512x512
appicondir = $(datadir)/pixmaps
appicon_DATA = xmlTableView.svg

EXTRA_DIST += xmlTableView.desktop xmlTableView.svg

