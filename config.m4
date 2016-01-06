dnl $Id$

PHP_ARG_ENABLE(ons_sender, whether to enable ons_sender support,
Make sure that the comment is aligned:
[  --enable-ons_sender           Enable ons_sender support])

if test "$PHP_ONS_SENDER" == "yes"; then

  AC_DEFINE(HAVE_ONS_SENDER,1,[ ])
  PHP_REQUIRE_CXX()
  PHP_ADD_LIBRARY(stdc++, "", EXTRA_LDFLAGS)

  LDFLAGS="$LDFLAGS -lonsclient4cpp"

  PHP_NEW_EXTENSION(ons_sender, ons_sender.cpp, $ext_shared)

fi