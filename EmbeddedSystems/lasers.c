#include "gpiolib_addr.h"
#include "gpiolib_reg.h"
#include "gpiolib_reg.c"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

//HARDWARE DEPENDENT CODE BELOW
#ifndef MARMOSET_TESTING

/* You may want to create helper functions for the Hardware Dependent functions*/

//This function should initialize the GPIO pins
GPIO_Handle initializeGPIO()
{
	GPIO_Handle gpio;
	gpio = gpiolib_init_gpio();
	if(gpio == NULL)
	{
		perror("Could not initialize GPIO");
		return gpio;
	}
	return gpio;	
}

//This function should accept the diode number (1 or 2) and output
//a 0 if the laser beam is not reaching the diode, a 1 if the laser
//beam is reaching the diode or -1 if an error occurs.
#define LASER1_PIN_NUM 4
#define LASER2_PIN_NUM 3 

int laserDiodeStatus(GPIO_Handle gpio, int diodeNumber)
{
	if(gpio == NULL)
	{
		return -1;
	}

	if(diodeNumber == 1)
	{
		uint32_t level_reg = gpiolib_read_reg(gpio, GPLEV(0));

		if(level_reg & (1 << LASER1_PIN_NUM))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(diodeNumber == 2)	{
		uint32_t level_reg = gpiolib_read_reg(gpio, GPLEV(0));

		if(level_reg & (1 << LASER2_PIN_NUM))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else 
	{
		return -1;
	}
}

#endif
//END OF HARDWARE DEPENDENT CODE

//This function will output the number of times each laser was broken
//and it will output how many objects have moved into and out of the room.

//laser1Count will be how many times laser 1 is broken (the left laser).
//laser2Count will be how many times laser 2 is broken (the right laser).
//numberIn will be the number  of objects that moved into the room.
//numberOut will be the number of objects that moved out of the room.
void outputMessage(int laser1Count, int laser2Count, int numberIn, int numberOut)
{
	printf("Laser 1 was broken %d times \n", laser1Count);
	printf("Laser 2 was broken %d times \n", laser2Count);
	printf("%d objects entered the room \n", numberIn);
	printf("%d objects exitted the room \n", numberOut);
}

//This function accepts an errorCode. You can define what the corresponding error code
//will be for each type of error that may occur.
void errorMessage(int errorCode)
{
	fprintf(stderr, "An error occured; the error code was %d \n", errorCode);
}

//ERROR CODES:
// -1 - GPIO initialization error!
// -2 - Invalid time given!
// -3 - No time parameter given!

#ifndef MARMOSET_TESTING
	
enum laserState { BOTH_UNBROKEN, LEFT_BROKEN, RIGHT_BROKEN, GOING_IN, GOING_OUT, LEFT_UNBROKEN, RIGHT_UNBROKEN };


int main(const int argc, const char* const argv[])
{
	GPIO_Handle gpio = initializeGPIO();
	
	if(gpio == NULL)	{
		errorMessage(-1);
		return -1;
	}

	if(argc < 2)
	{
		errorMessage(-3);
		return -1;
	}

	time_t startTime = time(NULL);

	int timeLimit = atoi(argv[1]);

	if(timeLimit <= 0)	{
		errorMessage(-2);
		return -1;
	}
	
	enum laserState currentState = BOTH_UNBROKEN;
	int leftLaserBreakCount = 0;
	int rightLaserBreakCount = 0;
	int objectsIn = 0;
	int objectsOut = 0;
	
	while((time(NULL) - startTime) < timeLimit)	{
		

		//NOTE THAT PINSTATE IS FALSE IF THE PHOTODIODE IS RECEIVING A SIGNAL AND TRUE IF IT IS NOT
		//laser1Status corresponds to the left laser and laser2Status corresponds to the right laser.
		//Also important to note that this counts "in" as an object to the right of both lasers and "out" as an object to the left of both lasers. 

		int laser1Status = laserDiodeStatus(gpio, 1);
		int laser2Status = laserDiodeStatus(gpio, 2);

		usleep(10000);

		switch(currentState)	{

			case BOTH_UNBROKEN:
				//if laser 1 breaks
				if(!laser1Status)	{
					leftLaserBreakCount++;
					currentState = LEFT_BROKEN;
				}
				//if laser 2 breaks
				if(!laser2Status)	{
					rightLaserBreakCount++;
					currentState = RIGHT_BROKEN;
				}				

				break;

			case LEFT_BROKEN:
				//if laser 1 unbreaks
				if(laser1Status)	
					currentState = BOTH_UNBROKEN;
				//if laser 2 breaks
				if(!laser2Status)	{
					rightLaserBreakCount++;
					currentState = GOING_IN;
				}

				break;

			case RIGHT_BROKEN:
				//if laser 2 unbreaks
				if(laser2Status)	
					currentState = BOTH_UNBROKEN;
				//if laser 1 breaks
				if(!laser1Status)	{
					leftLaserBreakCount++;
					currentState = GOING_OUT;
				}

				break;

			case GOING_IN:
				//if laser 2 unbreaks
				if(laser2Status)	
					currentState = LEFT_BROKEN;
				//if laser 1 unbreaks
				if(laser1Status)	
					currentState = LEFT_UNBROKEN;

				break;

			case GOING_OUT:
				//if laser 1 unbreaks
				if(laser1Status)	
					currentState = RIGHT_BROKEN;
				//if laser 2 unbreaks
				if(laser2Status)	
					currentState = RIGHT_UNBROKEN;

				break;

			case LEFT_UNBROKEN:
				//if laser 1 breaks
				if(!laser1Status)	{
					leftLaserBreakCount++;
					currentState = GOING_IN;
				}
				//if laser 2 unbreaks
				if(laser2Status)	{
					objectsIn++;
					currentState = BOTH_UNBROKEN;
				}

				break;

			case RIGHT_UNBROKEN:
				//if laser 2 breaks
				if(!laser2Status)	{
					rightLaserBreakCount++;
					currentState = GOING_OUT;
				}
				//if laser 1 unbreaks
				if(laser1Status)	{
					objectsOut++;
					currentState = BOTH_UNBROKEN;
				}

				break;
		}
	}	

	outputMessage(leftLaserBreakCount, rightLaserBreakCount, objectsIn, objectsOut);

	gpiolib_free_gpio(gpio);

	return 0;
}

#endif
