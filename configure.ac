AC_PREREQ([2.63])
AC_INIT([aenimal-util], [0.1], [mwashenb@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_LIBTOOL
AC_PROG_CC
AC_CHECK_HEADERS([stdint.h])
AC_CHECK_HEADERS([stdlib.h])
AC_TYPE_UINT32_T
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  src/perm/Makefile
  test/Makefile
  test/perm/Makefile
])
AC_OUTPUT
