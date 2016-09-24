#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAXTIMINGS 83
#define DHTPIN 7


#define relay1 2
#define relay2 3

int main(void)
{
	printf("relay pi\n") ;
	if (wiringPiSetup() == -1) exit(1) ;

	pinMode(relay1, OUTPUT);
	pinMode(relay2, OUTPUT);
	digitalWrite(relay1, 1);
	digitalWrite(relay2, 1);

	delay(1000);

	int i = 0;
	for(i = 0; i < 3; i++)
	{
		printf("true\n");
		digitalWrite(relay1, 0);
		digitalWrite(relay2, 1);
		delay(5000);

		printf("false\n");
		digitalWrite(relay1, 1);
		digitalWrite(relay2, 0);
		delay(5000);

	}



	return 0 ;
}
