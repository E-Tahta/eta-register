<?php
/**
 * Created by yunusem.
 * Developer: Yunusemre Şentürk 
 * Date: 23/6/16
 * Time: 12:06 AM
 */
header('Content-type: application/json');
setlocale(LC_CTYPE, 'nl_BE.utf8');

include "dbConnection.php";

$data = (object) array(
    "request_type" => "",
    "mac_id" => "",
    "result" => "",
    "city" => "",
    "town" => "",
    "school" => "",
    "code" => ""
);

$EXISTS = "0";
$INSERT = "1";

$dbc = new DataBaseConnection();
$servername = $dbc->getServername();
$username = $dbc->getUsername();
$password = $dbc->getPassword();
$dbname = $dbc->getDbname();
$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    echo "DATABASE CONNECTION ERROR";
    die("Connection failed: " . $conn->connect_error);

}

if ($_SERVER['REQUEST_METHOD'] == 'POST') {
    $data = json_decode(file_get_contents("php://input"), true);
    if($data["request_type"]==$EXISTS) {
        $sql = $dbc->getSelectSql($data["mac_id"]);
        $result = $conn->query($sql);
        if ($result->num_rows > 0) {
            $data["result"] = TRUE;
        } else {
            $data["result"] = FALSE;
        }
    } else if($data["request_type"]==$INSERT) {

        $sql = $dbc->getInsertSql($data["city"], $data["town"], $data["school"],
            $data["code"], $data["mac_id"]);
        $data["result"] = mysqli_query($conn,$sql);
    } else {
        $data["result"] = "Unknown Request Type";
    }
    $data["mac_id"] = "";
    echo json_encode($data);
} else {
    http_response_code(405);
}

$conn->close();
?>
