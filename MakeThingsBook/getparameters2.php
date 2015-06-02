<?php

foreach ($_REQUEST as $key => $value)
{
	if ($key == "name") {
		$name = $value;
	}

	if ($key == "age") {
		$age = $value;
	}
}

if (isset($name) && isset($age)) {
	if ($age < 21) {
		echo "<p> $name, You're not old enough to drink.</p>\n";
	} else {
		echo "<p> $name, You can drink!...";
		echo "but do so responsibly!</p>\n";
	}
}

?>

<html>
<body>
	<form action="getparameters2.php" method="post" enctype="application/x-www-form-urlencoded">
		Name: <input type="text" name="name" /><br>
		Age: <input type="age" name="age" /><br>
		<input type="submit" name="Submit" />
	</form>
</body>
</html>