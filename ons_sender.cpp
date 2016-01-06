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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C"
{
#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_ons_sender.h"
}

#ifdef PHP_WIN32
#include <atomic>
#endif

#include "ONSFactory.h"
#include "ONSClientException.h"

using namespace ons;

ZEND_DECLARE_MODULE_GLOBALS(ons_sender)

/* True global resources - no need for thread safety here */
static int le_ons_sender;

/*ONS工厂类
*/
ONSFactoryProperty factoryInfo;

/*ONS消息队列生产者实例
*/
Producer *pProducer;

/* {{{ PHP_INI
 */

PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("ons_sender.publish_topics", "PID_TEST", PHP_INI_SYSTEM, OnUpdateString, publish_topics, zend_ons_sender_globals, ons_sender_globals)
    STD_PHP_INI_ENTRY("ons_sender.producer_id", "TEST", PHP_INI_SYSTEM, OnUpdateString, producer_id, zend_ons_sender_globals, ons_sender_globals)
	STD_PHP_INI_ENTRY("ons_sender.access_key", "0000", PHP_INI_SYSTEM, OnUpdateString, access_key, zend_ons_sender_globals, ons_sender_globals)
	STD_PHP_INI_ENTRY("ons_sender.secret_key", "0000", PHP_INI_SYSTEM, OnUpdateString, secret_key, zend_ons_sender_globals, ons_sender_globals)
PHP_INI_END()

/* }}} */
PHP_FUNCTION(ons_send)
{
	char *msg_body, *tags, *msg_key = NULL;
	size_t msg_body_len, tags_len, msg_key_len;
	zend_string *rt_str;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "ss|s", &msg_body, &msg_body_len, &tags, &tags_len, &msg_key, &msg_key_len) == FAILURE) {
		return;
	}

	Message msg(factoryInfo.getPublishTopics(), tags, msg_body);

	if (msg_key) {

		msg.setKey(msg_key);

	}

	try
	{
		SendResultONS sendResult = pProducer->send(msg);

#ifdef PHP_WIN32
		rt_str = zend_string_init(sendResult.getMessageId(), strlen(sendResult.getMessageId()) + 1, 0);
#else
		rt_str = zend_string_init(sendResult.getMessageId().c_str(), sendResult.getMessageId().length() + 1, 0);
#endif

	}
	catch (ONSClientException & e)
	{
		ons_sender_php_fatal_error(E_WARNING, "ons_sender->send(msg):Send Fail!");
	}

	RETURN_STR(rt_str);
}
/* }}} */

/** {{{ PHP_GINIT_FUNCTION
*/
PHP_GINIT_FUNCTION(ons_sender)
{
	memset(ons_sender_globals, 0, sizeof(*ons_sender_globals));
}
/* }}} */


/* {{{ php_ons_sender_init_globals
 */
static void php_ons_sender_init_globals(zend_ons_sender_globals *ons_sender_globals)
{
	ons_sender_globals->producer_id = "PID_TEST";
	ons_sender_globals->publish_topics = "TEST";
	ons_sender_globals->access_key = "0000";
	ons_sender_globals->secret_key = "0000";
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(ons_sender)
{
	ZEND_INIT_MODULE_GLOBALS(ons_sender, php_ons_sender_init_globals, NULL);

	REGISTER_INI_ENTRIES();

	factoryInfo.setFactoryProperty(ONSFactoryProperty::ProducerId, ONS_SENDER_G(producer_id));
	factoryInfo.setFactoryProperty(ONSFactoryProperty::PublishTopics, ONS_SENDER_G(publish_topics));
	factoryInfo.setFactoryProperty(ONSFactoryProperty::AccessKey, ONS_SENDER_G(access_key));
	factoryInfo.setFactoryProperty(ONSFactoryProperty::SecretKey, ONS_SENDER_G(secret_key));

	pProducer = ONSFactory::getInstance()->createProducer(factoryInfo);
	pProducer->start();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(ons_sender)
{
	UNREGISTER_INI_ENTRIES();

	pProducer->shutdown();

	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(ons_sender)
{
#if defined(COMPILE_DL_ONS_SENDER) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(ons_sender)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(ons_sender)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "ons_sender settings", "value");
	php_info_print_table_row(2, "Version", PHP_ONS_SENDER_VERSION);
	php_info_print_table_row(2, "ProducerId", ONS_SENDER_G(producer_id));
	php_info_print_table_row(2, "PublishTopics", ONS_SENDER_G(publish_topics));
	php_info_print_table_row(2, "AccessKey", ONS_SENDER_G(access_key));
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ ons_sender_functions[]
 *
 * Every user visible function must have an entry in ons_sender_functions[].
 */
const zend_function_entry ons_sender_functions[] = {
	PHP_FE(ons_send,	NULL)		
	PHP_FE_END	
};
/* }}} */

/* {{{ ons_sender_module_entry
 */
zend_module_entry ons_sender_module_entry = {
	STANDARD_MODULE_HEADER,
	"ons_sender",
	ons_sender_functions,
	PHP_MINIT(ons_sender),
	PHP_MSHUTDOWN(ons_sender),
	PHP_RINIT(ons_sender),		
	PHP_RSHUTDOWN(ons_sender),	
	PHP_MINFO(ons_sender),
	PHP_ONS_SENDER_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ONS_SENDER
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(ons_sender)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
