TESTS = check_basic
check_PROGRAMS = check_basic
check_basic_SOURCES = check_basic.c $(top_builddir)/src/basic/au_basic.h
check_basic_CFLAGS = @CHECK_CFLAGS@
check_basic_LDADD = \
	$(top_builddir)/src/basic/libaubasic.la \
	@CHECK_LIBS@
