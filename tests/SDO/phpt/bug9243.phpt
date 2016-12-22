--TEST--
test for bug #9243 - unnecessary warning messages loading remote schema
--INI--
display_errors=off
--SKIPIF--
<?php

  if (!extension_loaded('sdo'))
      print 'skip - sdo extension not loaded';
  else
    if (
      @fopen(
        'http://examples.oreilly.com/9780596002527/examples/first.xsd', 'r'
      ) === false
    ) print 'skip - remote schema is unreachable'
  ;
?>
--FILE--
<?php

try {
  $xmldas = (
    SDO_DAS_XML::create(
      'http://examples.oreilly.com/9780596002527/examples/first.xsd'
    )
  );
} catch (SDO_Exception $e) {
    print('Problem creating an XML document: ' . $e->getMessage());
}

?>
--EXPECT--
