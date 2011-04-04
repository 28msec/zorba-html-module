import schema namespace csv-options="http://www.zorba-xquery.com/modules/converters/csv-options";
import module namespace zorba-csv = "http://www.zorba-xquery.com/modules/converters/csv";
import module namespace file="http://www.zorba-xquery.com/modules/file";

let $options := validate{
<csv-options:options>
  <first-row-is-header/>
  <csv separator="&#009;"
       quote-char=""
       quote-escape=""/>
  <xml-nodes>
    <csv:row xmlns:csv="http://www.zorba-xquery.com/modules/converters/csv"/>
  </xml-nodes>
</csv-options:options>}
return 
zorba-csv:serialize(
    zorba-csv:parse(file:read-text(fn:resolve-uri("ME_1_2008_v08.txt")), $options),
    $options) 
