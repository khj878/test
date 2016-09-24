<?php 
	header('Content-Type: text/html; charset=UTF-8');
	$userid = urldecode($_POST['userid']);
	$password = urldecode($_POST['password']);
	
	$mysql_hostname = 'localhost';
	$mysql_username = 'root';
	$mysql_password = 'gmlwns12';
	$mysql_database = 'petmonitor';
	$mysql_port = '3306';
	$mysql_charset = 'utf8';
	mysql_query(' SET NAMES '.$mysql_charset);

	$connect = @mysql_connect($mysql_hostname.':'.$mysql_port, $mysql_username, $mysql_password); 
	@mysql_select_db($mysql_database, $connect) or die('DB 선택 실패');
	
	// $query = "select * from test where userid = ".$data ;
	$query = "select * from test where userid = '".$userid."'"." and password = '".$password."'" ;
	//echo $query;
	$result = mysql_query($query);
	$jsonData      = array();
	$jsonTempData  = array();
	
	while($row = mysql_fetch_array($result)){
		$jsonTempData['userid'] = $row[userid];
		$jsonTempData['password'] = $row[password];
		$jsonTempData['auto_tmp'] = $row[auto_tmp];
		$jsonTempData['auto_feed'] = $row[auto_feed];
		$jsonTempData['min_tmp'] = $row[min_tmp];
		$jsonTempData['max_tmp'] = $row[max_tmp];
		$jsonTempData['cur_tmp'] = $row[cur_tmp];
		$jsonTempData['feed_btn'] = $row[feed_btn];
		$jsonTempData['fan_btn'] = $row[fan_btn];
		$jsonTempData['heatpad_btn'] = $row[heatpad_btn];
		$jsonTempData['set_feed_time1'] = $row[set_feed_time1];
		$jsonTempData['set_feed_time2'] = $row[set_feed_time2];
		$jsonTempData['set_feed_time3'] = $row[set_feed_time3];
		$jsonData[] = $jsonTempData;
	} 
	
	$outputArr = array();
	$outputArr['result'] = $jsonData;
	 
	print_r(json_encode($outputArr));

	mysql_close($connect);
 ?>