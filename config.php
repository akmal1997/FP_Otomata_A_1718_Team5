<?php 
//this is line comment
#more line comment
// hehe
# use this shorter

$server = "127.0.0.1";
$user = "ppdb_data";
$password = "caj.xxx.corp";
$dbname = "ppdb";

$hehe = 69 + 7;

time_sleep_until(10);
echo "echo is more than just echi";

$db = mysqli_connect($server, $user, $password, $dbname);

if(!$db) {
    die("Unable to connect database");
}

?>