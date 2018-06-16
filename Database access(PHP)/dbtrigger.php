
<?php


if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
echo "Connected successfully";

	$count =0;

   if( $_GET["name"] || $_GET["age"] ) {

      echo "Welcome ". $_GET['name']. "<br />";
      echo "You are ". $_GET['age']. " years old.";
      
    
   }

  if( $_GET["gcodeOf"]) {



	$servername = "localhost";
	$username = "omkar";
	$password = "helloworld2";
	$dbname = "GcodeGenerator";



	$conn = new mysqli($servername, $username, $password, $dbname);

	 $txt = $_GET['gcodeOf'];
     	 echo "Gcode of  ". $txt. "<br />";
     	$sql = "INSERT INTO dbrequest2 (id, data, status) VALUES (".$count.",'".$txt."', '1')";

     	 if ($conn->query($sql) === TRUE) {
   		 echo "New record created successfully";
	} 
	else {
    		echo "Error: " . $sql . "<br>" . $conn->error;
	}
 
}



  if( $_GET["gcodeOfImage"]) {

	$servername = "localhost";
	$username = "omkar";
	$password = "helloworld2";
	$dbname = "GcodeGenerator";

	

	$conn = new mysqli($servername, $username, $password, $dbname);
	 $image_txt = $_GET['gcodeOfImage'];
      	echo "Image file name received ". $image_txt. "<br />";   
    	$sql_image = "INSERT INTO dbrequest2 (id, data, status) VALUES (".$count.",'".$image_txt."', '1')";

	   if ($conn->query($sql_image) === TRUE) {
   		 echo "New record created successfully";
	} 
	else {
  	  echo "Error: " . $sql . "<br>" . $conn->error;
	 }

$conn->close();
}

//$sql = "SELECT * FROM aphabets where alphabet_value='".$txt."'";


//$count = $count +1



?>
