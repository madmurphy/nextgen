# Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	"-DPACKAGE_LOCALE_DIR=\"$(localedir)\"" \
	"-DPACKAGE_SRC_DIR=\"$(srcdir)\"" \
	"-DPACKAGE_DATA_DIR=\"$(pkgdatadir)\"" \
	"-DG_LOG_DOMAIN=\"Nautilus__REPL_TITLECASE_PACKAGENAME__\""

AM_CFLAGS = \
	-Wall\
	-g \
	-pedantic \
	$(WARN_CFLAGS) \
	$(NAUTILUS_CFLAGS) \
	$(GLIB_CFLAGS) \
	$(NAUTILUS___REPL_UPPERCASE_PACKAGENAME___CFLAGS)

nautilus_extensiondir = $(NAUTILUS_EXTENSION_DIR)

nautilus_extension_LTLIBRARIES = \
	libnautilus___REPL_LOWERCASE_PACKAGENAME__.la

libnautilus___REPL_LOWERCASE_PACKAGENAME___la_SOURCES = \
	nautilus-__REPL_IDCASE_PACKAGENAME__.c

libnautilus___REPL_LOWERCASE_PACKAGENAME___la_LDFLAGS = \
	-module \
	-avoid-version

libnautilus___REPL_LOWERCASE_PACKAGENAME___la_LIBADD = \
	$(NAUTILUS___REPL_UPPERCASE_PACKAGENAME___LIBS)

# EOF

