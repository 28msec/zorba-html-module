(: csv-to-xml example with utf8 characters :)

import module namespace csv = "http://www.zorba-xquery.com/modules/converters/csv";

csv:parse("ü,ö,ä, ă,î,ș,ț,â", ())
