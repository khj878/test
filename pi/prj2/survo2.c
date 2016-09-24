#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <softPwm.h>

#define SURVO 0
#define SW 1

int main()
{
	int s = 0;
	int pos = 180;
	if(wiringPiSetup() == -1)
		exit(1);
	pinMode(SURVO, OUTPUT);
	digitalWrite(SURVO, LOW);
	pinMode(SW, INPUT);
	softPwmCreate(0, 0, 200);
	while(1) {
		if(digitalRead(SW) == 0 && s == 0) 
		{	
			pos = 5;
			softPwmWrite(SURVO, pos);
			printf("%d\n", pos);
			s = 1;
			delay(500);
		}
		else if(digitalRead(SW) == 0 && s == 1)
		{
			pos = 27;
			softPwmWrite(SURVO, pos);
			printf("%d\n", pos);
			s = 0;
			delay(500);
		}
	}
	return 0;
}
