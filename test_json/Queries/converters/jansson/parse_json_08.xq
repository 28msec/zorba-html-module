(: json:parse testing null handling :)

import module namespace json = "http://www.zorba-xquery.com/modules/converters/json";
import schema namespace html-options="http://www.zorba-xquery.com/modules/converters/json-options";

json:parse('{ "web-app": null }',<options xmlns="http://www.zorba-xquery.com/modules/converters/json-options" >
              <jsonParam name="mapping" value="simple-json" />
            </options>)
