AC_INIT([gems],[0.0.1],[hutchiep190@potsdam.edu])

AM_INIT_AUTOMAKE([-Wall -Werror foreign color-tests silent-rules])

AM_SILENT_RULES([yes])

AC_PROG_CC

AC_CONFIG_FILES([
Makefile
src/Makefile
tests/Makefile
])

AM_PATH_SDL(1.2.0,
            CPPFLAGS="$CPPFLAGS $SDL_CFLAGS" LIBS="$LIBS $SDL_LIBS",
            AC_MSG_ERROR([SDL not found]))

AC_OUTPUT