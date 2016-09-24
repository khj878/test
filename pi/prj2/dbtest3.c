#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <softPwm.h>
#include <string.h>
#include <time.h>
#include </usr/include/mysql/mysql.h>

#define MAXTIMINGS 83
#define DHTPIN 7
#define HEATPAD 2
#define FAN 3
#define SURVO 0
#define SW 1

//db variable
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
char *server = "localhost";
char *user = "root";
char *password = "gmlwns12";
char *database = "petmonitor";

int feed_count = 0;
int db_max_tmp, db_min_tmp, db_cur_tmp;
int db_auto_tmp, db_auto_feed;
int db_feed_btn, db_fan_btn, db_heatpad_btn;
char db_set_feed_time[3][7];
int feed_cnt;

//time variable
char current_time[7];
int cur_hour, cur_minute, cur_second;


int dht11_dat[5];
int pos;
int s;

void init();
void read_dht11_dat();
void connect_db();
void survo_control();
void excute_query();
void get_current_time();

int main(void)
{
	init(); 
	while (1) 
	{
	//	survo_control();
		get_current_time();
		excute_query();
		read_dht11_dat(); 
	//	survo_control();
		
		printf("\n");
		delay(1500) ;
	}

	mysql_close(conn);
	return 0 ;
}

void get_current_time()
{
	struct tm *t;
	time_t timer;
	timer = time(NULL);
	t = localtime(&timer);
	cur_hour = t->tm_hour;
	cur_minute = t->tm_min;
	
	if(cur_minute < 10)
		sprintf(current_time, "%d:0%d", cur_hour, cur_minute);
	else
		sprintf(current_time, "%d:%d", cur_hour, cur_minute);
	printf("current time : %s \n", current_time);
}

void init()
{
	struct tm *t;
	time_t timer;
	printf("dht11 Raspberry pi\n");
	pinMode(FAN, OUTPUT);
	pinMode(HEATPAD, OUTPUT);
	pinMode(SURVO, OUTPUT);
	pinMode(SW, INPUT);

	digitalWrite(FAN, 1);
	digitalWrite(HEATPAD, 1);
	digitalWrite(SURVO, 0);

	printf("current time : ");
	printf("%dmonth %dday %dhour %dmin. \n", t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);
	cur_hour = t->tm_hour;
	cur_minute = t->tm_min;
	cur_second = t->tm_sec;

	softPwmCreate(0, 0, 200);

	if (wiringPiSetup() == -1) exit(1);
	connect_db();

}
void read_dht11_dat()
{
	uint8_t laststate = HIGH;
	uint8_t counter = 0;
	uint8_t j = 0, i;
	uint8_t flag = HIGH;
	uint8_t state = 0;
	float f;
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
	pinMode(DHTPIN, OUTPUT);
	digitalWrite(DHTPIN, LOW);
	delay(18);
	digitalWrite(DHTPIN, HIGH);
	delayMicroseconds(30);
	pinMode(DHTPIN, INPUT);
	for (i = 0; i < MAXTIMINGS; i++) {
		counter = 0;
		while (digitalRead(DHTPIN) == laststate) {
			counter++;
			delayMicroseconds(1);
			if (counter == 200) break;
		}
		laststate = digitalRead(DHTPIN);
		if (counter == 200) break; // if while breaked by timer, break for
		if ((i >= 4) && (i % 2 == 0)) {
			dht11_dat[j / 8] <<= 1;
			if (counter > 20) dht11_dat[j / 8] |= 1;
			j++;
		}
	}

	if ((j >= 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] +
		dht11_dat[3]) & 0xff))) {
		//printf("humidity = %d.%d %% Temperature = %d.%d *C \n", dht11_dat[0],
		//	dht11_dat[1], dht11_dat[2], dht11_dat[3]);
		
					
		if(db_auto_tmp) {
			if (db_cur_tmp >= db_max_tmp)
			{
				digitalWrite(HEATPAD, 1);
				digitalWrite(FAN, 0);
				printf("Fan On\n");
			}
	
			else if (db_cur_tmp <= db_min_tmp)
			{
				digitalWrite(HEATPAD, 0);
				digitalWrite(FAN, 1);
				printf("Heatpad On\n");
			}
	
			else
			{
				digitalWrite(HEATPAD, 1);
				digitalWrite(FAN, 1);
				printf("Nothing On\n");
			}
		}
	
		char query[30] = "update test set cur_tmp = ";
		char tmp[3];
		sprintf(tmp, "%d", dht11_dat[2]);
		strcat(query, tmp);
		//printf("query = %s\n", query);
	


		if (mysql_query(conn, query)){
			printf("query fail\n");
			exit(1);
		}


	}

	//	else printf("Data get failed\n") ;
}

void survo_control()
{
	if (feed_count < 3)
	{
		pos = 5;
		softPwmWrite(SURVO, pos);
		delay(50);
		printf("feeder open survo command\n");
		pos = 15;
		softPwmWrite(SURVO, pos);
		delay(50);
	}
}


void connect_db()
{
	if (!(conn = mysql_init((MYSQL*)NULL))){
		printf("init fail\n");
		exit(1);
	}

	printf("mysql_init sucsess.\n");

	if (!mysql_real_connect(conn, server, user, password, NULL, 0, NULL, 0)){
		printf("connect error.\n");     //DB connect (MYSQL*, host, id, pw, null, port, 0)
		exit(1);
	}

	printf("mysql_real_connect suc.\n");

	if (mysql_select_db(conn, database) != 0){
		mysql_close(conn);
		printf("select_db fail.\n");
		exit(1);
	}
	printf("select mydb suc.\n");
}

void excute_query()
{
	if(mysql_query(conn, "select * from test")){
		printf("query fail\n");
		exit(1);
	}

	//printf("query sucsess\n");
	res = mysql_store_result(conn);                 //save res to row
	//printf("res suceese\n");


	//printf("st_num  name    address    tel           age\n");
	while ((row = mysql_fetch_row(res)) != NULL){
		//printf("min tmp = %d, max tmp = %d\n", atoi(row[0]), atoi(row[1]));
		
		db_auto_tmp = atoi(row[2]);
		db_auto_feed = atoi(row[3]);
		db_min_tmp = atoi(row[4]);
		db_max_tmp = atoi(row[5]);
		db_cur_tmp = atoi(row[6]);
		db_feed_btn = atoi(row[7]);
		db_fan_btn = atoi(row[8]);
		db_heatpad_btn = atoi(row[9]);
		for (int i = 0; i < 3; i++)
			strcpy(db_set_feed_time[i], row[10+i]);

		printf("userid : %s\n", row[0]);
		if(db_auto_tmp) printf("auto temperature control mode, ");
		else printf("manual temperature control mode, ");
		if(db_auto_feed) {
			printf("auto feed control mode.\n");
			for (int i = 0; i < 3; i++) {
				if (strcmp(db_set_feed_time[i], "0") != 0) {
					printf("%s ", db_set_feed_time[i]);
					if (strcmp(db_set_feed_time[i], current_time) == 0)
						if (feed_count < 3)
						{
							feed_count++;
							survo_control();
							printf("feeder open \n");
							if(feed_count >= 3)
								feed_count = 0;
						}
					else
						printf("feeder close\n");
				}
			}
			printf("setting time number : %d\n", feed_cnt);
		}
		else 
		{
			(printf("manual feed control mode.\n");
			
			if(db_feed_btn)
			{
				survo_control();
				printf("feeder open \n");
				
		printf("mintmp : %d, maxtmp : %d, curtmp : %d\n", db_min_tmp, db_max_tmp, db_cur_tmp);
		
	}
	mysql_free_result(res);
}
