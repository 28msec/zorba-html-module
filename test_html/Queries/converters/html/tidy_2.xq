(: tidy a html using default tidy options :)

import module namespace html="http://www.zorba-xquery.com/modules/converters/html";
import schema namespace html-options="http://www.zorba-xquery.com/modules/converters/html-options";

html:parse('<title>Foo</title><p>Foo!')