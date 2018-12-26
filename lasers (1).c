
//Joanne Baba, Devinn Doering and Yrina Guarisma -------- LAB GROUP 43


//The purpose of this code is to count the number of objects entering and exiting a room. It works in general by reading whether photodiodes are receiving the light from a laser, if it is not, then an object must be
//blocking the laser. The main function, countObjects, implements a state machine depending which combination of lasers have been broken and in which order in order to accurately count the number of objects that 
//have exited or entered the room.

#include "gpiolib_addr.h"
#include "gpiolib_reg.h"
#include "gpiolib_reg.c"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#ifndef MARMOSET_TESTING

GPIO_Handle initializeGPIO()													//This function initializes the GPIO and outputs an error if the GPIO has any issues initializing
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
#define LASER2_PIN_NUM 17 

int laserDiodeStatus(GPIO_Handle gpio, int diodeNumber)							//This function checks the status of the given laser diode. Outputs a 1 if the diode is receiving the laser beam and 0 if it is not. 	
{
	if(gpio == NULL)
	{
		return -1;
	}

	if(diodeNumber == 1)
	{

		//If the photodiode is receiving a laser signal, return 1, else, return 0
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
	if(diodeNumber == 2)	{

		//If the photodiode is receiving a laser signal, return 1, else, return 0
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

int countObjects(GPIO_Handle gpio, const int duration);													//Main function used to count the objects entering and exiting. Contains a state machine.
																										//Outputs message upon conclusion of time period.
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

	int time = atoi(argv[1]);

	if(time <= 0)	{
		errorMessage(-2);
		return -1;
	}

	int ret = countObjects(gpio, time);

	gpiolib_free_gpio(gpio);

	return ret;
}


int countObjects(GPIO_Handle gpio, const int duration)	{						//Function containing the "bulk" of the code including the main state machine

	if(duration <= 0)	{
		errorMessage(-3);
		return -1;
	}

	time_t startTime = time(NULL);

	int timeLimit = duration;

	if(timeLimit <= 0)	{
		errorMessage(-2);
		return -1;
	}
	
	enum laserState { BOTH_UNBROKEN, LEFT_BROKEN, RIGHT_BROKEN, GOING_IN, GOING_OUT, LEFT_UNBROKEN, RIGHT_UNBROKEN };

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
	//Outputs the message containg the results of the program
	outputMessage(leftLaserBreakCount, rightLaserBreakCount, objectsIn, objectsOut);	
}

#endif
