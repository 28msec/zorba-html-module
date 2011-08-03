(: csv-to-xml example with 1 row :)

import module namespace csv = "http://www.zorba-xquery.com/modules/converters/csv";

csv:parse("f1, f2, f3, f4", ())
