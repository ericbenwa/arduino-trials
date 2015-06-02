<?php

foreach ($_REQUEST as $key => $value)
{
	if ($key == "pullups_total") {
		$pullups_total = $value;

	
	}
}

echo $pullups_total;

?>

<html>
<body>
	<form action="insert_mysql.php" method="post" enctype="application/x-www-form-urlencoded">
		Pullups Total: <input type="text" name="pullups_total" /><br>
		<input type="submit" name="Submit" />
	</form>
</body>
</html>