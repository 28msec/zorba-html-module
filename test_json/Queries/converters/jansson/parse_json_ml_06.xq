import module namespace json = "http://www.zorba-xquery.com/modules/converters/json";
import schema namespace html-options="http://www.zorba-xquery.com/modules/converters/json-options";

json:parse('["html" ,"<b>bold</b>"]',<options xmlns="http://www.zorba-xquery.com/modules/converters/json-options" 
             xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">
              <json-param name="mapping" value="json-ml" type="array"/>
            </options>)
