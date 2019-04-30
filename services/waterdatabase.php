<?Php
    $servername = "localhost";
    $username = "root";
    $password = "";
    $db = "test";

    $connect = mysqli_connect($servername, $username, $password, $db);
   
    
    if ($connect->connect_error) {
        echo "Failed to connect to MySQL: " . $connect->connect_error;
    } else {
        echo "Database connect successfully";
    }
    
    // Execute SQL statement
    $query1 = "INSERT INTO testing (time,value,status)
        VALUES (NOW(),'".$_GET["value"]."','".$_GET["status"]."')";

    if ($connect->query($query1) == TRUE) {
        echo "Table testing created successfully";
    } else {
        echo "Error creating table: " . $connect->error;
    }
    
    $connect->close();    
?>