(: type attribute missing :)

import module namespace json = "http://www.zorba-xquery.com/modules/converters/json";
import schema namespace html-options="http://www.zorba-xquery.com/modules/converters/json-options";

json:serialize((<json type="object">
      <pair name="name">value</pair>
  </json>),<options xmlns="http://www.zorba-xquery.com/modules/converters/json-options" >
              <json-param name="mapping" value="simple-json" />
            </options>)
