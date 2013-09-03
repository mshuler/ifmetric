# -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# $Id: configure.ac 17 2004-01-23 23:25:07Z lennart $

# This file is part of ifmetric.
#
# ifmetric is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# ifmetric is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with ifmetric; if not, write to the Free Software Foundation,
# Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.

AC_PREREQ(2.59)
AC_INIT([ifmetric],[0.3],[mzvszrgevp (at) 0pointer (dot) de])
AC_CONFIG_SRCDIR([src/ifmetric.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign -Wall])

AC_SUBST(PACKAGE_URL, [http://0pointer.de/lennart/projects/ifmetric/])

if type -p stow > /dev/null && test -d /usr/local/stow ; then
   AC_MSG_NOTICE([*** Found /usr/local/stow: default install prefix set to /usr/local/stow/${PACKAGE_NAME}-${PACKAGE_VERSION} ***])
   ac_default_prefix="/usr/local/stow/${PACKAGE_NAME}-${PACKAGE_VERSION}"
fi

# Checks for programs.
AC_PROG_CC

# If using GCC specifiy some additional parameters
if test "x$GCC" = "xyes" ; then
   CFLAGS="$CFLAGS -pipe -Wall"
fi

AC_CHECK_FUNCS([memset socket strerror strrchr])
AC_CHECK_HEADERS([stdlib.h string.h sys/socket.h unistd.h])
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_HEADER_STDC
AC_PROG_LN_S
AC_TYPE_PID_T

AC_CHECK_HEADER([linux/version.h],, [AC_MSG_ERROR([*** Sorry, you have to install the kernel header files ***])])

# LYNX documentation generation
AC_ARG_ENABLE(lynx,
        AS_HELP_STRING(--disable-lynx,Turn off lynx usage for documentation generation),
[case "${enableval}" in
  yes) lynx=yes ;;
  no)  lynx=no ;;
  *) AC_MSG_ERROR(bad value ${enableval} for --disable-lynx) ;;
esac],[lynx=yes])

if test x$lynx = xyes ; then
   AC_CHECK_PROG(have_lynx, lynx, yes, no)

   if test x$have_lynx = xno ; then
     AC_MSG_ERROR([*** Sorry, you have to install lynx or use --disable-lynx ***])
   fi
fi

AM_CONDITIONAL([USE_LYNX], [test "x$lynx" = xyes])

# XMLTOMAN manpage generation
AC_ARG_ENABLE(xmltoman,
        AS_HELP_STRING(--disable-xmltoman,Disable rebuilding of man pages with xmltoman),
[case "${enableval}" in
  yes) xmltoman=yes ;;
  no)  xmltoman=no ;;
  *) AC_MSG_ERROR([bad value ${enableval} for --disable-xmltoman]) ;;
esac],[xmltoman=yes])

if test x$xmltoman = xyes ; then
   AC_CHECK_PROG(have_xmltoman, xmltoman, yes, no)

   if test x$have_xmltoman = xno ; then
     AC_MSG_WARN([*** Not rebuilding man pages as xmltoman is not found ***])
     xmltoman=no
   fi
fi

AM_CONDITIONAL([USE_XMLTOMAN], [test "x$xmltoman" = xyes])

AC_CONFIG_FILES([src/Makefile Makefile man/Makefile doc/Makefile doc/README.html])
AC_OUTPUT
