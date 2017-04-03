<?php
$link = mysqli_connect("127.0.0.1", "root", "test1234", "multigame");
mysqli_set_charset($link, 'utf8');

if(!$link) {
	echo "Debug: errno: " . mysqli_connect_errno() . "<br/>";
	echo "Debug: error: " . mysqli_connect_error() . "<br/>";
	exit;
}

$loginid = $_GET["login_id"];
$loginpwd = $_GET["login_passwd"];
//$loginid = $_POST["login_id"];
//$loginpwd = $_POST["login_passwd"];

//echo "loginid: " . $loginid . "<br/>";
//echo "loginpwd: " . $loginpwd . "<br/>";

$query = "SELECT ac_aid,ac_name,ac_point,ac_grade-1 ac_grade,ac_login_time,ac_logout_time FROM account WHERE ac_loginid='" . $loginid . "' and ac_passwd = password('" . $loginpwd . "');";

//echo $query . "<br/>";

$result = mysqli_query($link, $query);

$row = mysqli_fetch_array($result, MYSQLI_ASSOC);
$count = mysqli_num_rows($result);

if(0 < $count) {
	// 한번만 실행하면 됨.
	//$row = mysqli_fetch_array($result, MYSQLI_NUM);
	//$ac_aid = $row[0];
	//$ac_name = $row[1];
	//$ac_point = $row[2];
	//$ac_grade = $row[3];
	//$ac_login_time = $row[4];
	//$ac_logout_time = $row[5];

	// row가 여러개 일때.
	//while($row = mysqli_fetch_array($result, MYSQLI_ASSOC)) {
	//	$ac_aid = $row["ac_aid"];
	//	$ac_name = $row["ac_name"];
	//	$ac_point = $row["ac_point"];
	//	$ac_grade = $row["ac_grade"];
	//	$ac_login_time = $row["ac_login_time"];
	//	$ac_logout_time = $row["ac_logout_time"];
	//}

	//echo "ac_aid:" . $ac_aid . "<br/>";
	//echo "ac_name:" . $ac_name . "<br/>";
	//echo "ac_point:" . $ac_point . "<br/>";
	//echo "ac_grade:" . $ac_grade . "<br/>";
	//echo "ac_login_time:" . $ac_login_time . "<br/>";
	//echo "ac_logout_time:" . $ac_logout_time . "<br/>";

	$json = json_encode($row, JSON_UNESCAPED_UNICODE);
	echo $json;
} else {
	$array = array("ac_aid" => 0);

	//var_dump($array);

	$json = json_encode($array, JSON_UNESCAPED_UNICODE);

	echo $json;
}

mysqli_free_result($result);
mysqli_close($link);
?>

