
<?php
   if( $_GET["name"] || $_GET["age"] ) {
      echo "Welcome ". $_GET['name']. "<br />";
      echo "You are ". $_GET['age']. " years old.";
      
    
   }

  if( $_GET["gcodeOf"]) {
	 $txt = $_GET['gcodeOf'];
      echo "Gcode of  ". $txt. "<br />";
     
      
    
   }

  if( $_GET["gcodeOfImage"]) {
	 $image_txt = $_GET['gcodeOf'];
      echo "Image file name received ". $image_txt. "<br />";   
    
   }
$servername = "localhost";
$username = "omkar";
$password = "helloworld2";
$dbname = "GcodeGenerator";

$count =0;

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
echo "Connected successfully";

echo $txt;
//$sql = "SELECT * FROM aphabets where alphabet_value='".$txt."'";
$sql = "INSERT INTO dbrequest2 (id, data, status) VALUES (".$count.",'".$txt."', '1')";

$sql_image = "INSERT INTO dbrequest2 (id, data, status) VALUES (".$count.",'".$image_txt."', '2')";
//$count = $count +1
if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();


?>

