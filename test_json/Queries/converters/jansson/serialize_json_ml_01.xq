import module namespace json = "http://www.zorba-xquery.com/modules/converters/json";
import schema namespace html-options="http://www.zorba-xquery.com/modules/converters/json-options";

declare variable $tmp :=<ul>
  <li style="color:red">First Item</li>
  <li title="Some hover text." style="color:green">Second Item</li>
  <li><span class="code-example-third">Third</span>Item</li>
</ul>;

json:serialize($tmp,<options xmlns="http://www.zorba-xquery.com/modules/converters/json-options" >
              <json-param name="mapping" value="json-ml" />
            </options>)