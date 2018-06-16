
<?php
   if( $_GET["name"] || $_GET["age"] ) {
      echo "Welcome ". $_GET['name']. "<br />";
      echo "You are ". $_GET['age']. " years old.";
      
    
   }

  if( $_GET["gcodeOf"]) {
	 $txt = $_GET['gcodeOf'];
      echo "Gcode of  ". $txt. "<br />";
     
      
    
   }
$servername = "localhost";
$username = "omkar";
$password = "helloworld2";
$dbname = "GcodeGenerator";


// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
echo "Connected successfully";

echo $txt;
$sql = "SELECT * FROM aphabets where alphabet_value='".$txt."'";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        echo "id: " . $row["id"]. " - Alphabet: " . $row["alphabet_value"]. " " . $row["gcode"]. "<br>";
    }
} else {
    echo "0 results";
}
$conn->close();



?>

