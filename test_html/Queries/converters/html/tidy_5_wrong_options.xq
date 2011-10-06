(: tidy a html using wrong tidy option for a value :)

import module namespace html="http://www.zorba-xquery.com/modules/converters/html";
import schema namespace html-options="http://www.zorba-xquery.com/modules/converters/html-options";

html:parse('<title>Foo</title><p>Foo!',
            <options xmlns="http://www.zorba-xquery.com/modules/converters/html-options" >
              <tidyParam name="output-xml" value="maybe" />
            </options>)