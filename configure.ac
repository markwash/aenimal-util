AC_PREREQ([2.63])
AC_INIT([aenimal-util], [0.1], [mwashenb@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_LIBTOOL
AC_PROG_CC
AC_CHECK_HEADERS([stdint.h])
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([sys/time.h])
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  src/basic/Makefile
  src/dist/Makefile
  src/perm/Makefile
  src/rand/Makefile
  test/Makefile
  test/basic/Makefile
  test/perm/Makefile
  test/rand/Makefile
])
AC_OUTPUT
