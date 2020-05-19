##  -*- Mode: M4; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-
##  Process this file with autoconf to produce a configure script.

AC_INIT([NExtGen],
	m4_bregexp(m4_quote(m4_include([VERSION])),
		[[0-9]+\.[0-9]+\.[0-9]+], [\&]),
	[madmurphy333@gmail.com],
	[nextgen],
	[https://github.com/madmurphy/nextgen/])

AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([gnu])

AC_PREREQ([2.65])

AC_MSG_NOTICE(AC_PACKAGE_STRING)

AC_PROG_SED

AC_PROG_LN_S

AC_ARG_VAR([FIND], [Unix find utility])

AS_IF([test "x@S|@{FIND}" = x], [
	AC_PATH_PROG([FIND], [find])
	AS_IF([test "x@S|@{FIND}" = x],
		[AC_MSG_ERROR([Unix find utility not found])])
])

AC_CONFIG_FILES([Makefile])

AC_OUTPUT

##  EOF

