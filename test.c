#include "gpiolib_addr.h"
#include "gpiolib_reb.h"
#include "gpiolib_reg.c"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h> 


int main(void){
	
	GPIO_Handle gpio;
	gpio = gpiolib_init_gpio();
	if(gpio == NULL)
	{
		perror("Could not initialize GPIO");
	}
	return gpio;

	//Set pin 17 as an output pin - Light 1
	uint32_t sel_reg = gpiolib_read_reg(gpio, GPFSEL(1));
	sel_reg |= 1  << 21;
	gpiolib_write_reg(gpio, GPFSEL(1), sel_reg);
	
	//Set pin 22 as an output pin - Light 2
	uint32_t sel_reg1 = gpiolib_read_reg(gpio, GPFSEL(2));
	sel_reg1 |= 1  << 6;
	gpiolib_write_reg(gpio, GPFSEL(2), sel_reg1);

	//inputs
	uint32_t level_reg = gpiolib_read_reg(gpio, GPLEV(0));
	int laser1 = level_reg & (1 << 4);
	usleep(1000);

	uint32_t level_reg = gpiolib_read_reg(gpio, GPLEV(0));
	int laser2 = level_reg & (1 << 3);
	usleep(1000);

	time_t StartTime = time(NULL);
	time_t enteringTime;
	time_t travelTime;
	float speed = 0;
	while((time(NULL)-StartTime)<30){
		if(!laser1)
			enteringTime = time(NULL);

		if(!laser2){
			travelTime = time(NULL) - enteringtime;
		}
	}
	speed = 10/travelTime;
	printf("SPEEEEEEED %d cm/s \n", speed);

}



