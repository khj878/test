#include <stdio.h>
#include <time.h>

int main()
{
	struct tm *t;
	time_t timer;

	timer = time(NULL);
	t = localtime(&timer);
	
	printf("current time : ");
	printf("%dmonth %dday %dhour %dmin. \n", t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min);

	return 0;
}
