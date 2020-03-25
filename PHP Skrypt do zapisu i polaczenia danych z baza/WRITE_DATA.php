<html>
 <head>
  <title>PHP </title>
 </head>
 <body>
 <?php 
	ini_set('display_errors', 1);
	$con = mysqli_init();
	if (!$con) {
	  die("mysqli_init failed");
	}
	$dbusername = "root";  
    $dbpassword = "haslo”;
    $server = "localhost"; 
    $database = "SAVE_DATA";
	$conn = mysqli_connect($server, $dbusername, $dbpassword, $database);
	
	if(!$conn)
    {
		 echo "Connection failed.";
		exit();
    }	
	$sql = "INSERT INTO SAVE (Value_1, Value_2, Value_3, Value_4, Value_5, Value_6, Value_7, Value_8) VALUES ('".$_GET["data1"]."','".$_GET["data2"]."','".$_GET["data3"]."','".$_GET["data4"]."','".$_GET["data5"]."','".$_GET["data6"]."','".$_GET["data7"]."','".$_GET["data8"]."')";                    

    mysqli_query($conn, $sql);	
?>
 </body>
</html>
