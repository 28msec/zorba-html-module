import module namespace json = "http://www.zorba-xquery.com/modules/converters/json";
import schema namespace html-options="http://www.zorba-xquery.com/modules/converters/json-options";


declare variable $local:json :=
   '{ "special-chars": {
         "quote": "\"",
         "backslash": "\\",
         "backspace": "\b",
         "formfeed": "\f",
         "newline": "\n",
         "carriage return": "\r",
         "horizontal tab": "\t",
         "solidus": "\/"
      }
    }';

json:serialize((json:parse(($local:json),<options xmlns="http://www.zorba-xquery.com/modules/converters/json-options" >
              <json-param name="mapping" value="simple-json" />
            </options>)),<options xmlns="http://www.zorba-xquery.com/modules/converters/json-options" >
              <json-param name="mapping" value="simple-json" />
            </options>)

