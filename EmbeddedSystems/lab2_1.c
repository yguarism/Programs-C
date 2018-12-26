#include "gpiolib_addr.h"
#include "gpiolib_reg.h"
#include "gpiolib_reg.c"

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

unsigned int* initializeGPIO (){
//Initialize the GPIO pins and check if initialize correctly
	GPIO_Handle gpio;
	gpio = gpiolib_init_gpio();
	if(gpio == NULL)
	{
		perror("Could not initialize GPIO");
	}
	return gpio;

}

void setOutput(unsigned int* gpio){
	//Set pin 17 as an output pin - Light 1
	uint32_t sel_reg = gpiolib_read_reg(gpio, GPFSEL(1));
	sel_reg |= 1  << 21;
	gpiolib_write_reg(gpio, GPFSEL(1), sel_reg);
	
	//Set pin 22 as an output pin - Light 2
	uint32_t sel_reg1 = gpiolib_read_reg(gpio, GPFSEL(2));
	sel_reg1 |= 1  << 6;
	gpiolib_write_reg(gpio, GPFSEL(2), sel_reg1);

	return;

}

void turnOn (int pinNum, unsigned int* gpio){
	gpiolib_write_reg(gpio, GPSET(0), 1 << pinNum);      // Turn -Light  On
	return;
}

void turnOff (int pinNum, unsigned int* gpio){
	gpiolib_write_reg(gpio, GPCLR(0), 1 << pinNum);     // Turn -Light  Off
	return;

}

int buttonState (unsigned int* gpio){
	/*Declare a variable called level_reg of 32-bit size	and assigned the value of the level register*/ 	
	uint32_t level_reg = gpiolib_read_reg(gpio, GPLEV(0));
	/* Declare a variable called pin_state and assign the value of bit 4 from the level_reg*/ 		
	int pin_state = level_reg & (1 << 4);

	return pin_state;

}

void startProg (int pinNum, unsigned int*gpio){
	int buttonp = 1; // loop condition
	int pushed = 0; //counts when button is pushed
	turnOn(pinNum,gpio); // turn on first light
	while (buttonp){		
		
			if(!buttonState(gpio)) //pinstate is false when button is pushed
				{
					pushed = 1;
				}
			if(buttonState(gpio) && pushed){
				buttonp = 0;

			}
		}
	turnOff(pinNum,gp); // turn off to show program has started
	return;
}

void numLightBlinks (int i, const int size, int switchState[], unsigned int*gpio){

	while (i<size){
			usleep (1000);//usleep for 1000 ms = 0.001s * 10000 = 10s total
			int button = buttonState(gpio);
			if(!button){		//If the button is pushed then set a one into my array	
				switchState[i] = 1;
				i++;
			}
			else { //If the button is not pushed then set a 0 into my array
				switchState[i] = 0;
				i++;
			}
		}
	return;
}

void blinkLight(int i, int pinNum, int size, unsigned int*gpio){ // I NEED LIGHT TO TURN ON for the number of 1's in ARRAY
	while (i < size-3){
			if (switchState[i] == 1 && switchState[i+1] ==1 && switchState[i+2] ==1 && switchState[i+3] ==0){ // ensure it has actually been pressed (not just error)
					
				turnOn(pinNum, gpio);
				usleep(1000000);
				turnOff(pinNum, gpio);
				usleep(1000000);
			}

		i++;
	}

	return;
}

int main(void)
{
	// initialize all variables and switch state array
	int sz = 10000;	
	int switchState [sz];
	int pin1 = 17;
	int pin2 = 22;
	int i = 0; //counter

	unsigned int* gp = initializeGPIO();
	
	setOutput(gp);
	
	while (1){
		startProg(pin1, gp);//once pin_state is false (button is pressed) --> Turn off light 1
		usleep(500000);
		numLightBlinks(i, sz, switchState, gp);
		/*for(int j = 0; j < sz; j++)
			printf("%d", switchState[j]);*/ //for testing purposes
		blinkLight(i, sz, pin2, switchState, gp);	
		usleep(5000000);
	}

}

