<?php

if (isset($_FILES)) {
	$fileName = $_FILES['file']['name'];
	$fileTempName = $_FILES['file']['tmp_name'];
	$fileType = $_FILES['file']['type'];
	$fileSize = $_FILES['file']['size'];
	$fileError = $_FILES['file']['error'];

	if (($fileType == "image/jpeg") && ($fileSize < 100000)) {
		if ($fileError > 0) {
			echo "Return Code: " . $fileError . "<br>";
		} else {
			echo "Upload: " . $fileName . "<br>";
			echo "Type: " . $fileType . "<br>";
			echo "Size: " . ($fileSize / 1024) . " Kb<br>";
			echo "Temp file: " . $fileTempName . "<br>";

			if (file_exists($fileName)) {
				unlink($fileName);
			}

			move_uploaded_file($fileTempName, $fileName);
			echo "Uploaded file stored as: " .$fileName;
		}
	}

	else {
		echo "File too damn big or not a jpeg.";
	}
}

?>

<html>
<head>
	<title></title>
</head>
<body>
	<form action="save2web.php" method="post" enctype="multipart/form-data">
		<label for="file">Filename:</label>
		<input type="file" name="file" id="file" />
		<br>
		<input type="submit" name="submit" value="upload" />
	</form>
</body>
</html>