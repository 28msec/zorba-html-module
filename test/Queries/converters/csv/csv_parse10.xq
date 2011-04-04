import schema namespace csv-options="http://www.zorba-xquery.com/modules/converters/csv-options";
import module namespace zorba-csv = "http://www.zorba-xquery.com/modules/converters/csv";
import module namespace file="http://www.zorba-xquery.com/modules/file";

zorba-csv:parse(file:read-text(fn:resolve-uri("NAWQA.swmaster.CROSSTAB_COUNT.1260179451247.csv")), 
                    validate{
                    <csv-options:options>
                      <first-row-is-header/>
                      <csv separator=","
                           quote-char=""
                           quote-escape=""/>
                      <xml-nodes>
                        <row>
                          <column/>
                        </row>
                      </xml-nodes>
                    </csv-options:options>}                    
                    )
