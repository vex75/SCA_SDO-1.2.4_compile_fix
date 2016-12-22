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
$Id: 1c-CRUD.php,v 1.2 2007/02/07 11:26:06 cem Exp $
*/

echo "executing scenario one-company-create/retrieve/update/delete\n";

require_once 'SDO/DAS/Relational.php';
require_once 'company_metadata.inc.php';


/*************************************************************************************
* Use SDO to perform create, retrieve, update, and delete operations on a row of the company table.
*
* See companydb_mysql.sql and companydb_db2.sql for examples of defining the database 
*
* to keep this example shorter, no try/catch blocks
* to make it quite clear that we work disconnected, get a fresh DAS and PDO handle each time
*************************************************************************************/

/*************************************************************************************
 * Empty out the company table
 *************************************************************************************/
$dbh = new PDO(PDO_DSN,DATABASE_USER,DATABASE_PASSWORD);
$count = $dbh->exec('DELETE FROM company;');
echo "Emptied out the company table with DELETE FROM company\n";


/*************************************************************************************
* Create the root data object then a single company object underneath it.
* Set the company name to 'Acme'.
*************************************************************************************/
$das = new SDO_DAS_Relational ($database_metadata,'company',$SDO_reference_metadata);
$dbh = new PDO(PDO_DSN,DATABASE_USER,DATABASE_PASSWORD);

$root 		= $das  -> createRootDataObject();
$company 	= $root -> createDataObject('company');
$company -> name = "Acme";
$company -> employee_of_the_month = null;

$das -> applyChanges($dbh, $root);
echo "Created a company with name Acme and wrote it to the database\n";

/*************************************************************************************
 * Find it again (with its autogenerated id this time).
 * Then update it and write it back again.
 *************************************************************************************/
$das = new SDO_DAS_Relational ($database_metadata,'company',$SDO_reference_metadata);
$dbh = new PDO(PDO_DSN,DATABASE_USER,DATABASE_PASSWORD);

$name = 'Acme';
$pdo_stmt = $dbh->prepare('select name, id, employee_of_the_month from company where name=?');
$root = $das->executePreparedQuery($dbh, $pdo_stmt ,array($name), array('company.name', 'company.id','company.employee_of_the_month'));
$company2 = $root['company'][0];
echo "Looked for Acme and found company with name = " . $company2->name . " and id " . $company2->id . "\n";
assert($company2->name == 'Acme');
assert($company2->employee_of_the_month === null);
$company2->name = 'MegaCorp';
$das -> applyChanges($dbh, $root);
echo "Wrote back Acme with name changed to MegaCorp\n";

/*************************************************************************************
* Find it again under its new name, and delete it. 
* Just for a change, re-use the PDO database handle and prepared statement.
*************************************************************************************/

$name = 'MegaCorp';
$root = $das->executePreparedQuery($dbh, $pdo_stmt ,array($name), array('company.name', 'company.id','company.employee_of_the_month'));
$company3 = $root['company'][0];
echo "Looked for MegaCorp and found company with name = " . $company3->name . " and id " . $company3->id . "\n";
assert($company3->name == 'MegaCorp');
unset($root['company'][0]); // do not make the mistake of doing unset($company3) - this will just destroy the $company3 variable
$das -> applyChanges($dbh, $root);
echo "Deleted the company and wrote the changes back to the database\n";

/*************************************************************************************
* Check the row is really gone
*************************************************************************************/
$dbh = new PDO(PDO_DSN,DATABASE_USER,DATABASE_PASSWORD);

foreach($dbh->query('select * from company') as $row) {
  assert(false); // There had better be no such rows. 
}

echo "Checked that the table was truly empty with SELECT * FROM company. Nothing was found so the delete was successful.\n";

?>
