<?php
/* 
+----------------------------------------------------------------------+
| (c) Copyright IBM Corporation 2005.                                  |
| All Rights Reserved.                                                 |
+----------------------------------------------------------------------+
|                                                                      |
| Licensed under the Apache License, Version 2.0 (the "License"); you  |
| may not use this file except in compliance with the License. You may |
| obtain a copy of the License at                                      |
| http://www.apache.org/licenses/LICENSE-2.0                           |
|                                                                      |
| Unless required by applicable law or agreed to in writing, software  |
| distributed under the License is distributed on an "AS IS" BASIS,    |
| WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
| implied. See the License for the specific language governing         |
| permissions and limitations under the License.                       |
+----------------------------------------------------------------------+
| Author: Matthew Peters                                               |
+----------------------------------------------------------------------+
$Id: 1cde-C.php,v 1.2 2007/02/07 11:26:06 cem Exp $
*/

require_once 'SDO/DAS/Relational.php';
require_once 'company_metadata.inc.php';

/**
 * Scenario - Various creates
 *
 */
$dbh = new PDO(PDO_DSN,DATABASE_USER,DATABASE_PASSWORD);
$count = $dbh->exec('DELETE FROM company');
$count = $dbh->exec('DELETE FROM department');
$count = $dbh->exec('DELETE FROM employee');

$das = new SDO_DAS_Relational ($database_metadata,'company',$SDO_reference_metadata);
$root = $das -> createRootDataObject();
$acme = $root -> createDataObject('company');
$acme -> name = "Acme";
$shoe = $acme->createDataObject('department');
$it = $acme->createDataObject('department');
$shoe->name = 'Shoe';
$shoe->location = 'A-block';
$it -> name = 'IT';
$sue = $shoe->createDataObject('employee');
$sue->name = 'Sue';
$ron = $it->createDataObject('employee');
$ron->name = 'Ron';

$acme->employee_of_the_month=$ron;

$dbh = new PDO(PDO_DSN,DATABASE_USER,DATABASE_PASSWORD);
$das -> applyChanges($dbh, $acme);
echo "company, departments, and employees all written to the database\n";



?>
