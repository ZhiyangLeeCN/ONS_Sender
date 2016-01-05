dnl $Id$
dnl config.m4 for extension ons_sender

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(ons_sender, for ons_sender support,
dnl Make sure that the comment is aligned:
dnl [  --with-ons_sender             Include ons_sender support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(ons_sender, whether to enable ons_sender support,
dnl Make sure that the comment is aligned:
dnl [  --enable-ons_sender           Enable ons_sender support])

if test "$PHP_ONS_SENDER" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-ons_sender -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/ons_sender.h"  # you most likely want to change this
  dnl if test -r $PHP_ONS_SENDER/$SEARCH_FOR; then # path given as parameter
  dnl   ONS_SENDER_DIR=$PHP_ONS_SENDER
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for ons_sender files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       ONS_SENDER_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$ONS_SENDER_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the ons_sender distribution])
  dnl fi

  dnl # --with-ons_sender -> add include path
  dnl PHP_ADD_INCLUDE($ONS_SENDER_DIR/include)

  dnl # --with-ons_sender -> check for lib and symbol presence
  dnl LIBNAME=ons_sender # you may want to change this
  dnl LIBSYMBOL=ons_sender # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $ONS_SENDER_DIR/$PHP_LIBDIR, ONS_SENDER_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_ONS_SENDERLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong ons_sender lib version or lib not found])
  dnl ],[
  dnl   -L$ONS_SENDER_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(ONS_SENDER_SHARED_LIBADD)

  PHP_NEW_EXTENSION(ons_sender, ons_sender.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
