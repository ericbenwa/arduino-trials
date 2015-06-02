<?php
// Create connection
//$con=mysqli_connect("ebenoit.com","ebenoitc_fitness","silly1","ebenoitc_pullups");

mysql_query("SET time_zone = 'US/New_York'");

foreach ($_REQUEST as $key => $value)
{
	if ($key == "pullups_total") {
		$pullups_total = $value;
	}
}

echo $pullups_total;

$username="ebenoitc_fitness";
$password="silly1";
$database="ebenoitc_pullups";
$localhost="localhost";

// Check connection
if (mysql_connect($localhost, $username, $password))
  {
  	@mysql_select_db($database) or die( "Unable to select database");

  	$query = "INSERT INTO pullups_table VALUES ($pullups_total,'10',now())";
  	$result = mysql_query($query);
  } else {
  	echo('not working');
  }
?>