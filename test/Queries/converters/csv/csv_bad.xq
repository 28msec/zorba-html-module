import schema namespace csv-options="http://www.zorba-xquery.com/modules/converters/csv-options";
import module namespace csv = "http://www.zorba-xquery.com/modules/converters/csv";
import module namespace file="http://expath.org/ns/file";

csv:parse(
file:read-text(fn:resolve-uri("dpl.txt")), 
fn:doc("bad_options.xml")/csv-options:options
)