# Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
	"-DPACKAGE_LOCALE_DIR=\"$(localedir)\"" \
	"-DPACKAGE_SRC_DIR=\"$(srcdir)\"" \
	"-DPACKAGE_DATA_DIR=\"$(pkgdatadir)\"" \
	"-DG_LOG_DOMAIN=\"Nautilus__REPL_TITLECASE_EXTNAME__\""

AM_CFLAGS = \
	-Wall \
	-Wextra \
	-g \
	-pedantic \
	$(WARN_CFLAGS) \
	$(NAUTILUS_CFLAGS) \
	$(GLIB_CFLAGS)

nautilus_extensiondir = $(NAUTILUS_EXTENSION_DIR)

nautilus_extension_LTLIBRARIES = \
	libnautilus-__REPL_IDCASE_EXTNAME__.la

libnautilus___REPL_LOWERCASE_EXTNAME___la_SOURCES = \
	nautilus-__REPL_IDCASE_EXTNAME__.c

libnautilus___REPL_LOWERCASE_EXTNAME___la_CFLAGS = \
	$(NAUTILUS___REPL_UPPERCASE_EXTNAME___CFLAGS)

libnautilus___REPL_LOWERCASE_EXTNAME___la_LDFLAGS = \
	-module \
	-avoid-version

libnautilus___REPL_LOWERCASE_EXTNAME___la_LIBADD = \
	$(NAUTILUS___REPL_UPPERCASE_EXTNAME___LIBS)

# EOF

