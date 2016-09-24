<html>
	<head>
		<meta charset="utf-8">
		<title>라즈베리파이 아파치 웹서버</title>
	</head>
	<body>
		<h1>라즈베리파이 아파치 웹서버 정상가동 </h1>
		<p>아파치를 설치하면 웹서버를 가동할 수 있습니다.</p>
		<p>펫모니터팀 아파치 웹서버 - 포트번호 : 11111 </p>

	</body>
</html>

<?php
	$mysql_hostname = 'localhost';
	$mysql_username = 'root';
	$mysql_password = 'gmlwns12';
	$mysql_database = 'petmoniter';
	$mysql_port = '3306';
	$mysql_charset = 'utf8';
	mysql_query(' SET NAMES '.$mysql_charset);

	$connect = @mysql_connect($mysql_hostname.':'.$mysql_port, $mysql_username, $mysql_password); 
	if(!$connect){
		echo '[연결실패] : '.mysql_error().'<br>'; 
		die('MySQL 서버에 연결할 수 없습니다.');
	}
	else {echo '[연결성공]<br>';}
		@mysql_select_db($mysql_database, $connect) or die('DB 선택 실패');


	$query = "select * from test";
	$result = mysql_query($query);

	while($row = mysql_fetch_array($result)){
		echo "사용자 ID : ".$row[userid].'<br>';
		if(strcmp($row[auto_tmp], "1") echo "자동 온도 조절 모드, ";
		else "수동 온도 조절 모드, ";
		if(strcmp($row[auto_feed], "1") echo "자동 먹이 급식 모드, ";
		else "수동 먹이 급식 모드, ";
		echo "현재 온도 : ".$row[cur_tmp].", 설정 최소온도 : ".$row[min_tmp].", 설정 최대온도 : ".$row[max_tmp].'<br>';		
	}


	mysql_close($connect);
?>