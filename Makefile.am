## Process this file with automake to produce Makefile.in

dist_doc_DATA = \
	AUTHORS \
	ChangeLog.md \
	COPYING \
	README

dist_pkgdata_DATA = \
	VERSION

dist_pkgdata_SCRIPTS = \
	nextgen.sh

exttempldir = $(pkgdatadir)/extension-template
dist_exttempl_DATA = \
	extension-template/PKGBUILD

pkgtempldir = $(exttempldir)/package
dist_pkgtempl_DATA = \
	extension-template/package/README \
	extension-template/package/NEWS \
	extension-template/package/ChangeLog \
	extension-template/package/.editorconfig \
	extension-template/package/package.json \
	extension-template/package/Makefile.am \
	extension-template/package/INSTALL \
	extension-template/package/AUTHORS \
	extension-template/package/COPYING \
	extension-template/package/configure.ac

dist_pkgtempl_SCRIPTS = \
	extension-template/package/bootstrap

pkgtemplpodir = $(pkgtempldir)/po
dist_pkgtemplpo_DATA = \
	extension-template/package/po/LINGUAS \
	extension-template/package/po/Makevars \
	extension-template/package/po/POTFILES.in

pkgtemplsrcdir = $(pkgtempldir)/src
dist_pkgtemplsrc_DATA = \
	extension-template/package/src/extension-template.c \
	extension-template/package/src/Makefile.am

# Shell expansion is supported here
_bootstrapclean_dirs_ = \
	'autom4te.cache' \
	'build-aux' \
	'm4' \
	`$(FIND) -L . -type d -name .deps`

# Shell expansion is supported here
_bootstrapclean_files_ = \
	'aclocal.m4' \
	'config'.* \
	'configure' \
	'configure~' \
	`$(FIND) -L . -type f -name 'Makefile.in'`


# Supplementary targets for GNU Automake

install-exec-hook:
	$(MKDIR_P) '$(DESTDIR)$(bindir)' && rm -f \
	'$(DESTDIR)$(bindir)/nextgen' && $(LN_S) \
	'$(pkgdatadir)/nextgen.sh' '$(DESTDIR)$(bindir)/nextgen';

install-data-hook:
	(cd '$(DESTDIR)$(pkgtempldir)' && $(LN_S) 'README' \
	'README.md' && $(LN_S) 'ChangeLog' 'ChangeLog.md');

uninstall-local:
	-rm -rf '$(DESTDIR)$(pkgdatadir)' '$(DESTDIR)$(docdir)';
	-rm -f '$(DESTDIR)$(bindir)/nextgen';


# Novel targets

# Make the source directory depend on Autotools and `autoreconf`
.PHONY: bootstrap-clean
bootstrap-clean: maintainer-clean
	-rm -rf $(_bootstrapclean_dirs_) && rm -f $(_bootstrapclean_files_) \
	&& (cd '$(srcdir)' && rm -rf $(_bootstrapclean_dirs_) && \
	rm -f $(_bootstrapclean_files_));

## EOF

