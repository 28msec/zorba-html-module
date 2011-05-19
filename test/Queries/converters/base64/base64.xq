import module namespace base64 = "http://www.zorba-xquery.com/modules/converters/base64";

base64:decode(base64:encode("This is a test"))
