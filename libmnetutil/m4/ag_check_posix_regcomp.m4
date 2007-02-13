dnl @synopsis AG_CHECK_POSIX_REGCOMP
dnl
dnl Check that the POSIX compliant regular expression compiler is
dnl available in the POSIX specified manner, and it works. If it fails,
dnl we have a backup -- use gnu-regex.
dnl
dnl @category C
dnl @author Bruce Korb <bkorb@gnu.org>
dnl @version 2001-12-01
dnl @license GPLWithACException

dnl DO NOT EDIT THIS FILE   (ag_check_posix_regcomp.m4)
dnl
dnl It has been AutoGen-ed  Saturday December  1, 2001 at 09:21:28 PM PST
dnl From the definitions    bkorb.def
dnl and the template file   conftest.tpl
dnl See: http://autogen.sf.net for a description of the AutoGen project

AC_DEFUN([AG_CHECK_POSIX_REGCOMP],[
  AC_MSG_CHECKING([whether POSIX compliant regcomp()/regexec()])
  AC_CACHE_VAL([ag_cv_posix_regcomp],[
  AC_TRY_RUN([#include <sys/types.h>
#include <regex.h>
int main() {
  int flags = REG_EXTENDED|REG_ICASE|REG_NEWLINE;
  regex_t  re;
  if (regcomp( &re, "^.*$", flags ) != 0)
    return 1;
  return regcomp( &re, "|no.*", flags ); }],[ag_cv_posix_regcomp=yes],[ag_cv_posix_regcomp=no],[ag_cv_posix_regcomp=no]
  ) # end of TRY_RUN]) # end of CACHE_VAL

  AC_MSG_RESULT([$ag_cv_posix_regcomp])
  if test x$ag_cv_posix_regcomp = xyes
  then
    AC_DEFINE(HAVE_POSIX_REGCOMP, 1,
       [Define this if POSIX compliant regcomp()/regexec()])
  fi
]) # end of AC_DEFUN of AG_CHECK_POSIX_REGCOMP
