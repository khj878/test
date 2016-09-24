/*

 *
 * Copyright (c) 2012-2013 Gordon Henderson. <projects@drogon.net>
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include "WiringPi.h"
#include "DHT11.h"
#include <stdio.h>

int main(void)
{
    float farenheit;
    int huavg = 0, teavg = 0;
    if(wiringPiSetup() == -1) return 1;
    
    DHT11 dht = DHT11(0);
    printf("Start Sensing Humidiy & Temperature\n");
    
    for(int i = 1; i < 10 ; i++)
    {
        printf("Check count = %d\n",i);
        dht.requestDHT11();
        if(dht.responseDHT11() == PASS)
        {
        	if(dht.calculateDHTValue() == true)
        	{
        		printf("Humidity = %2.1lf\%, Temperature = %2.1lfC, Temperature = %2.1lfF\n", dht.getDHTHumidity(), dht.getDHTTemperatureC(), dht.getDHTTemperatureF());
				
        	}
        }

		delay(1000);
        
    }  
    
    return 0;
}
