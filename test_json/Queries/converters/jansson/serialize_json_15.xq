import module namespace json = "http://www.zorba-xquery.com/modules/converters/json";
import schema namespace html-options="http://www.zorba-xquery.com/modules/converters/json-options";

declare variable $local:json :=<json type="object">
  <pair name="servlet" type="array">
    <item type="object">
    </item>
  </pair>
</json>;

json:serialize($local:json,<options xmlns="http://www.zorba-xquery.com/modules/converters/json-options" >
              <json-param name="mapping" value="simple-json" />
            </options>)
