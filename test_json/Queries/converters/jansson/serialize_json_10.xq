(: object contained in an array is allowed :)

import module namespace json = "http://www.zorba-xquery.com/modules/converters/json";
import schema namespace html-options="http://www.zorba-xquery.com/modules/converters/json-options";

json:serialize((<json type="object">
    <pair name="servlet" type="array">
      <item type="object">
        <pair name="name" type="string">value1</pair>
      </item>
      <item type="string">value2</item>
    </pair>
  </json>),<options xmlns="http://www.zorba-xquery.com/modules/converters/json-options" >
              <jsonParam name="mapping" value="simple-json" />
            </options>)
