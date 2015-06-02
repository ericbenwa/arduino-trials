<?php 

$to = "testing@gmail.com";
$subject = "make stuff and send email test";
$from = "testing@gmail.com";
$message = "Be clean!";

mail($to, $subject, $message, $from);

echo "I mailed " . $to . "<br>";
echo $from . "<br>";
echo $subject . "<br><br>";
echo $message;

?>