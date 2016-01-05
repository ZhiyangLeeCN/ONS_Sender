# Aliyun ONS SKD for PHP7 (only send) 

Allow you send message to Aliyun ONS on PHP7 
>让您可以在PHP7上发送消息到阿里云的ONS(开发消息服务)中

## Requirement
- PHP 7.0 +
- Aliyun ONS C/C++ SDK

### Compile ONS_Sender in Linux

Import "/aliyun-ons-c++-sdk-path/include/" path And lib file "/aliyun-ons-c++-sdk-path/lib/x64(or x86)/libonsclient4cpp.so" to environment variables

```
$/path/to/phpize
$./configure
$make && make install
```
### Compile ONS_Sender in Windows

Import "/php-path/;/php-path/main/;/php-path/Zend/;/php-path/TSRM/;/aliyun-ons-c++-sdk-path/include/" paths and lib file "/aliyun-ons-c++-sdk-path/lib/x64(or x86)/ONSClient4CPP.lib" to Visual Studio

Now use Visual Studio Compile!

## Configuration
in PHP.ini(在您的PHP.ini中配置):
```
ons_sender.publish_topics= PublishTopics in you aliyun ons console 
ons_sender.producer_id= ProducerId in you aliyun ons console 
ons_sender.access_key= AccessKey in you aliyun ons console
ons_sender.secret_key= SecretKey in you aliyun ons console

```

## Use
```
$msg_id = ons_send(msg_body, tag, msg_key(optional));

```
