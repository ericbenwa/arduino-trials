<?php 

$to = "testing@gmail.com";
$subject = "Meow";
$from = "testing@gmail.com";
$message = "The cat is on the mat at http://www.testing.com/client/EJB/catcam .";

mail($to, $subject, $message, "From: $from");

echo "TO: " . $to;
echo "\nFROM: " . $from;
echo "\nSUBJECT: " . $subject;
echo "\n\n" . $message . "\n\n";

?>