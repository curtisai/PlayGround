<?php
$dbhost = "localhost";
$dbuser = "notadish";
$dbpass = "notadish";
$dbname = "assignment_try";

mysql_connect($dbhost, $dbuser, $dbpass) or die('Cannot connect to the server');
mysql_connect($dbname) or die('Cannot select the database');

?>