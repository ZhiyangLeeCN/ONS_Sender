/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: ZhiyangLee                                                   |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_ONS_SENDER_H
#define PHP_ONS_SENDER_H

#define ons_sender_php_error(level, fmt_str, ...)   if (SWOOLE_G(display_errors)) php_error_docref(NULL TSRMLS_CC, level, fmt_str, ##__VA_ARGS__)
#define ons_sender_php_fatal_error(level, fmt_str, ...)   php_error_docref(NULL TSRMLS_CC, level, fmt_str, ##__VA_ARGS__)
#define ons_sender_sys_error(level, fmt_str, ...)  if (SWOOLE_G(display_errors)) php_error_docref(NULL TSRMLS_CC, level, fmt_str" Error: %s[%d].", ##__VA_ARGS__, strerror(errno), errno)
#define ons_sender_efree(p)  if (p) efree(p)

extern PHPAPI void php_var_dump(zval **struc, int level);
extern PHPAPI void php_debug_zval_dump(zval **struc, int level);

extern zend_module_entry ons_sender_module_entry;
#define phpext_ons_sender_ptr &ons_sender_module_entry

#define PHP_ONS_SENDER_VERSION "0.1.0-dev"

#ifdef PHP_WIN32
#	define PHP_ONS_SENDER_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_ONS_SENDER_API __attribute__ ((visibility("default")))
#else
#	define PHP_ONS_SENDER_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(ons_sender)
	char	*publish_topics;
	char	*producer_id;
	char	*access_key;
	char	*secret_key;
ZEND_END_MODULE_GLOBALS(ons_sender)

extern ZEND_DECLARE_MODULE_GLOBALS(ons_sender);

/* Always refer to the globals in your function as ONS_SENDER_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/
#define ONS_SENDER_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(ons_sender, v)

#if defined(ZTS) && defined(COMPILE_DL_ONS_SENDER)
ZEND_TSRMLS_CACHE_EXTERN();
#endif

#endif	/* PHP_ONS_SENDER_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
