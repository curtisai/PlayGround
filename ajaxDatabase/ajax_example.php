<?php
ini_set('display_errors', 1);
error_reporting(~0);
error_reporting(E_ALL);
$host = "localhost";
$usr = "notadish";
$pas = "notadish";
$db = "assignment_try";

mysql_connect($host, $usr, $pas);

mysql_select_db($db) or die(mysql_error());

$age = mysql_real_escape_string($_GET['age']);
$sex = mysql_real_escape_string($_GET['sex']);
$wpm = mysql_real_escape_string($_GET['wpm']);

$query = "SELECT * FROM ajax_example WHERE sex = '$sex'";
if(is_numeric($age))
	$query .= " AND age <= $age";
if(is_numeric($wpm))
	$query .= " AND wpm <= $wpm";

$qry_result = mysql_query($query) or die(mysql_error());
//Build Result String 
$display_string = "<table>"; 
$display_string .= "<tr>"; 
$display_string .= "<th>Name</th>"; 
$display_string .= "<th>Age</th>"; 
$display_string .= "<th>Sex</th>"; 
$display_string .= "<th>WPM</th>"; 
$display_string .= "</tr>";
// Insert a new row in the table for each person returned 
while($row = mysql_fetch_array($qry_result)){
$display_string .= "<tr>"; 
$display_string .= "<td>$row[name]</td>"; 
$display_string .= "<td>$row[age]</td>"; 
$display_string .= "<td>$row[sex]</td>"; 
$display_string .= "<td>$row[wpm]</td>"; 
$display_string .= "</tr>";
}
echo "Query: " . $query . "<br />";
$display_string .= "</table>";
echo $display_string;
?>