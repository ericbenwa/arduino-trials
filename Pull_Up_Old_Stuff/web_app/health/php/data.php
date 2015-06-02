<?php
    // Convert MySQL to JSON
    $username = "ebenoitc_fitness"; 
    $password = "silly1";   
    $host = "localhost";
    $database="ebenoitc_pullups";
    
    $server = mysql_connect($host, $username, $password);
    $connection = mysql_select_db($database, $server);

    $myquery = "
SELECT * FROM  `pullups_table` ORDER BY timestamp DESC
";
    $query = mysql_query($myquery);
    
    if ( ! $myquery ) {
        echo mysql_error();
        die;
    }
    
    $data = array();
    
    for ($x = 0; $x < mysql_num_rows($query); $x++) {
        $data[] = mysql_fetch_assoc($query);
    }
    
    echo json_encode($data);     
     
    mysql_close($server);
?>