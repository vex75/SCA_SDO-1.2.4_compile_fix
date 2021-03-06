<?php
/*
+-----------------------------------------------------------------------------+
| (c) Copyright IBM Corporation 2006, 2007                                    |
| All Rights Reserved.                                                        |
+-----------------------------------------------------------------------------+
| Licensed under the Apache License, Version 2.0 (the "License"); you may not |
| use this file except in compliance with the License. You may obtain a copy  |
| of the License at -                                                         |
|                                                                             |
|                   http://www.apache.org/licenses/LICENSE-2.0                |
|                                                                             |
| Unless required by applicable law or agreed to in writing, software         |
| distributed under the License is distributed on an "AS IS" BASIS, WITHOUT   |
| WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.            |
| See the License for the specific language governing  permissions and        |
| limitations under the License.                                              |
+-----------------------------------------------------------------------------+
| Authors: Graham Charters, Matthew Peters                                    |
|                                                                             |
+-----------------------------------------------------------------------------+
$Id: order_test.php,v 1.3 2007/03/08 18:22:51 mfp Exp $
*/

$xmldas = SDO_DAS_XML::create('../../Schema/Order.xsd');
$doc    = $xmldas->createDocument('urn::orderNS','order');
$order  = $doc->getRootDataObject();

$order->orderId = 1;
$order->status = "RECEIVED";

$newItem = $order->createDataObject('item');
$newItem->itemId = 1;
$newItem->description = "Fork Handles";
$newItem->price = 10;
$newItem->quantity = 2;
$newItem->warehouseId = 3;

$newItem = $order->createDataObject('item');
$newItem->itemId = 2;
$newItem->description = "Candles (pack of 4)";
$newItem->price = 4.99;
$newItem->quantity = 3;
$newItem->warehouseId = 2;

$customer = $order->createDataObject('customer');

echo $xmldas->saveString($doc,2);


?>