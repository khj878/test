<?php 
	header('Content-Type: text/html; charset=UTF-8');
	$mode_flag = urldecode($_POST['mode_flag']);
	$userid = urldecode($_POST['userid']);
	$password = urldecode($_POST['password']);
	$auto_tmp = urldecode($_POST['auto_tmp']);
	$auto_feed = urldecode($_POST['auto_feed']);
	$min_tmp = urldecode($_POST['min_tmp']);
	$max_tmp = urldecode($_POST['max_tmp']);
	$btn_fan = urldecode($_POST['btn_fan']);
	$btn_heatpad = urldecode($_POST['btn_heatpad']);
	$btn_feed = urldecode($_POST['btn_feed']);
	$set_feed_time1 = urldecode($_POST['set_feed_time1']);
	$set_feed_time2 = urldecode($_POST['set_feed_time2']);
	$set_feed_time3 = urldecode($_POST['set_feed_time3']);
	
	$mysql_hostname = 'localhost';
	$mysql_username = 'root';
	$mysql_password = 'gmlwns12';
	$mysql_database = 'petmonitor';
	$mysql_port = '3306';
	$mysql_charset = 'utf8';
	mysql_query(' SET NAMES '.$mysql_charset);

	$connect = @mysql_connect($mysql_hostname.':'.$mysql_port, $mysql_username, $mysql_password); 
	@mysql_select_db($mysql_database, $connect) or die('DB 선택 실패');
	
	if(strcmp($mode_flag, "1") == 0) {
		$query = "update test set auto_tmp = ".$auto_tmp.";";
		$result = mysql_query($query);
		$query = "update test set auto_feed = ".$auto_feed.";";
		$result = mysql_query($query);
		
		if(strlen($min_tmp) != 0) {	
			$query = "update test set min_tmp = ".$min_tmp.";";
			$result = mysql_query($query);}
		if(strlen($max_tmp) != 0) {	
			$query = "update test set max_tmp = ".$max_tmp.";";
			$result = mysql_query($query);}
		
		if(strlen($set_feed_time1) != 0) {$query = "update test set set_feed_time1 = '".$set_feed_time1."';";
		$result = mysql_query($query);}
		if(strlen($set_feed_time2) != 0) {$query = "update test set set_feed_time2 = '".$set_feed_time2."';";
		$result = mysql_query($query);}
		if(strlen($set_feed_time3) != 0) {$query = "update test set set_feed_time3 = '".$set_feed_time3."';";
		$result = mysql_query($query);}
	}
	
	else if(strcmp($mode_flag, "2") == 0) {
		$query = "update test set fan_btn = ".$btn_fan.";";
		$result = mysql_query($query);
	}
	else if(strcmp($mode_flag, "3") == 0) {
		$query = "update test set heatpad_btn = ".$btn_heatpad.";";
		$result = mysql_query($query);
	}
	else if(strcmp($mode_flag, "4") == 0) {
		$query = "update test set feed_btn = ".$btn_feed.";";
		$result = mysql_query($query);
	}
	mysql_close($connect);
 ?>