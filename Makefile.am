## Process this file with automake to produce Makefile.in

dist_doc_DATA = \
	AUTHORS \
	ChangeLog.md \
	COPYING \
	README

nextgendir = $(datadir)/@PACKAGE_TARNAME@
dist_nextgen_DATA = \
	VERSION

dist_nextgen_SCRIPTS = \
	nextgen.sh

exttempldir = $(nextgendir)/extension-template
dist_exttempl_DATA = \
	extension-template/PKGBUILD

pkgtempldir = $(exttempldir)/package
dist_pkgtempl_DATA = \
	extension-template/package/bootstrap \
	extension-template/package/README \
	extension-template/package/NEWS \
	extension-template/package/ChangeLog \
	extension-template/package/.editorconfig \
	extension-template/package/ChangeLog.md \
	extension-template/package/package.json \
	extension-template/package/Makefile.am \
	extension-template/package/README.md \
	extension-template/package/INSTALL \
	extension-template/package/AUTHORS \
	extension-template/package/COPYING \
	extension-template/package/configure.ac

pkgtemplpodir = $(pkgtempldir)/po
dist_pkgtemplpo_DATA = \
	extension-template/package/po/LINGUAS \
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
	`$(FIND) -L . -type f -name 'Makefile.in'`


# Supplementary targets for GNU Automake

install-exec-hook:
	$(MKDIR_P) '$(DESTDIR)$(bindir)' && rm -f \
	'$(DESTDIR)$(bindir)/nextgen' && $(LN_S) \
	'$(nextgendir)/nextgen.sh' '$(DESTDIR)$(bindir)/nextgen'

uninstall-local:
	-rm -rf '$(DESTDIR)$(nextgendir)' '$(DESTDIR)$(docdir)';
	-rm -f '$(DESTDIR)$(bindir)/nextgen'


# Novel targets

# Make the source directory depend on Autotools and a `bootstrap` script
.PHONY: bootstrap-clean
bootstrap-clean: maintainer-clean
	-rm -rf $(_bootstrapclean_dirs_) && rm -f $(_bootstrapclean_files_) \
	&& (cd '$(srcdir)' && rm -rf $(_bootstrapclean_dirs_) && \
	rm -f $(_bootstrapclean_files_));

## EOF

