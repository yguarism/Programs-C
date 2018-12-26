#include "gpiolib_addr.h"
#include "gpiolib_reg.h"
#include "gpiolib_reg.c"

#include <stdint.h>
#include <stdio.h>		//for the printf() function
#include <fcntl.h>
#include <linux/watchdog.h> 	//needed for the watchdog specific constants
#include <unistd.h> 		//needed for sleep
#include <sys/ioctl.h> 		//needed for the ioctl function
#include <stdlib.h> 		//for atoi
#include <time.h> 		//for time_t and the time() function
#include <sys/time.h>           //for gettimeofday()

//Below is a macro that had been defined to output appropriate logging messages
//You can think of it as being similar to a function
//file        - will be the file pointer to the log file
//time        - will be the current time at which the message is being printed
//programName - will be the name of the program, in this case it will be Lab4Sample
//str         - will be a string that contains the message that will be printed to the file.
#define PRINT_MSG(file, time, programName, sev, str) \
	do{ \
			fprintf(logFile, "%s : %s : %s : %s", time, programName, sev, str); \
			fflush(logFile); \
	}while(0)

#define PRINT_VALUE(file, val)	\
	do{	\
		fprintf(logFile, " %f\n", val);	\
		fflush(logFile);	\
	}while(0)


#define FLT_MAX 3.402823466e+38F 
#define LASER1_PIN_NUM 4
#define LASER2_PIN_NUM 17 
#define WARNING_LED_PIN 27


//This is the max amount of time, in seconds, a person is allowed to remain in the hallway before a warning is issued
#define MAX_TIME_IN_HALL 10

//These define the different levels of severity to easily be accessed by PRINT_MSG later on
#define SEVERITY_DEBUG "severity"
#define SEVERITY_INFO "info"
#define SEVERITY_WARNING "warning"
#define SEVERITY_ERROR "error"
#define SEVERITY_CRITICAL "critical"

GPIO_Handle initializeGPIO();

int laserDiodeStatus(GPIO_Handle gpio, int diodeNumber);

void measureSpeed(GPIO_Handle gpio, int watchdog, const int duration, const int speedLimit, const int distance, FILE* logFile);

void readConfig(FILE* configFile, int* timeout, char* logFileName, int* duration, int* speedLimit, int* distanceBetweenLasers);

void getTime(char* buffer);

int main(const int argc, const char* const argv[])	{

	//Create a string that contains the program name
	const char* argName = argv[0];

	//These variables will be used to count how long the name of the program is
	int i = 0;
	int namelength = 0;

	while(argName[i] != 0)	{
		namelength++;
		i++;
	} 

	char programName[namelength];

	i = 0;

	//Copy the name of the program without the ./ at the start
	//of argv[0]
	while(argName[i + 2] != 0)	{
		programName[i] = argName[i + 2];
		i++;
	} 
	
	const char* configFileName = "/home/pi/selfDirected.cfg";

	FILE* configFile;
	configFile = fopen(configFileName, "r");

	//Output a warning message if the file cannot be openned
	if(!configFile)	{
		perror("The config file could not be opened");
		return -1;
	}

	//Declare the variables that will be passed to the readConfig function
	int timeout = 0;
	char logFileName[50];
	int duration = 0;
	int speedLimit = 0;
	int distanceBetweenLasers = 0;

	//Call the readConfig function to read from the config file
	readConfig(configFile, &timeout, logFileName, &duration, &speedLimit, &distanceBetweenLasers);

	//Close the configFile now that we have finished reading from it
	fclose(configFile);

	//Create a new file pointer to point to the log file
	FILE* logFile;
	//Set it to point to the file from the config file and make it append to
	//the file when it writes to it.
	logFile = fopen(logFileName, "a");

	//Check that the file opens properly.
	if(!configFile)	{
		perror("The log file could not be opened");
		return -1;
	}

	printf("Timeout Time: %d Log File Name: %s Duration: %d Speed Limit: %d Distance Between Lasers: %d \n\n", timeout, logFileName, duration, speedLimit, distanceBetweenLasers);

	//Create a char array that will be used to hold the time values
	char time[30];
	getTime(time);

	//Initialize the GPIO pins
	GPIO_Handle gpio = initializeGPIO();
	//Get the current time
	getTime(time);
	//Log that the GPIO pins have been initialized
	PRINT_MSG(logFile, time, programName, SEVERITY_INFO, "The GPIO pins have been initialized\n\n");
	printf("Successful initialization of the GPIO pins\n");

	//This variable will be used to access the /dev/watchdog file, similar to how
	//the GPIO_Handle works
	int watchdog;

	//We use the open function here to open the /dev/watchdog file. If it does
	//not open, then we output an error message. We do not use fopen() because we
	//do not want to create a file if it doesn't exist
	if ((watchdog = open("/dev/watchdog", O_RDWR | O_NOCTTY)) < 0) {
		printf("Error: Couldn't open watchdog device! %d\n", watchdog);
		return -1;
	} 
	//Get the current time
	getTime(time);
	//Log that the watchdog file has been opened
	PRINT_MSG(logFile, time, programName, SEVERITY_INFO, "The Watchdog file has been opened\n\n");

	//This line uses the ioctl function to set the time limit of the watchdog
	//timer to 15 seconds. The time limit can not be set higher that 15 seconds
	//so please make a note of that when creating your own programs.
	//If we try to set it to any value greater than 15, then it will reject that
	//value and continue to use the previously set time limit
	ioctl(watchdog, WDIOC_SETTIMEOUT, &timeout);
	
	//Get the current time
	getTime(time);
	//Log that the Watchdog time limit has been set
	PRINT_MSG(logFile, time, programName, SEVERITY_INFO, "The Watchdog time limit has been set\n\n");

	//The value of timeout will be changed to whatever the current time limit of the
	//watchdog timer is
	ioctl(watchdog, WDIOC_GETTIMEOUT, &timeout);

	//This print statement will confirm to us if the time limit has been properly
	//changed. The \n will create a newline character similar to what endl does.
	printf("The watchdog timeout is %d seconds.\n\n", timeout);

	//Calls the main function which monitors the hall activity
	measureSpeed(gpio, watchdog, duration, speedLimit, distanceBetweenLasers, logFile);

	//Writing a V to the watchdog file will disable to watchdog and prevent it from
	//resetting the system
	write(watchdog, "V", 1);
	getTime(time);
	//Log that the Watchdog was disabled
	PRINT_MSG(logFile, time, programName, SEVERITY_INFO, "The Watchdog was disabled\n\n");

	//Close the watchdog file so that it is not accidentally tampered with
	close(watchdog);
	getTime(time);
	//Log that the Watchdog was closed
	PRINT_MSG(logFile, time, programName, SEVERITY_INFO, "The Watchdog was closed\n\n");

	//Free the gpio pins
	gpiolib_free_gpio(gpio);
	getTime(time);
	//Log that the GPIO pins were freed
	PRINT_MSG(logFile, time, programName, SEVERITY_INFO, "The GPIO pins have been freed\n\n");

	return 0;
}

GPIO_Handle initializeGPIO()	{													//This function initializes the GPIO and outputs an error if the GPIO has any issues initializing
	GPIO_Handle gpio;
	gpio = gpiolib_init_gpio();
	if(gpio == NULL)	
		perror("Could not initialize GPIO");

	return gpio;	
}

//This function should accept the diode number (1 or 2) and output
//a 0 if the laser beam is not reaching the diode, a 1 if the laser
//beam is reaching the diode or -1 if an error occurs.

int laserDiodeStatus(GPIO_Handle gpio, int diodeNumber)	{						//This function checks the status of the given laser diode. Outputs a 1 if the diode is receiving the laser beam and 0 if it is not. 	

	if(gpio == NULL)
		return -1;

	if(diodeNumber == 1)	{
		//If the photodiode is receiving a laser signal, return 1, else, return 0
		uint32_t level_reg = gpiolib_read_reg(gpio, GPLEV(0));

		if(level_reg & (1 << LASER1_PIN_NUM))
			return 1;

		else
			return 0;
	}
	if(diodeNumber == 2)	{

		//If the photodiode is receiving a laser signal, return 1, else, return 0
		uint32_t level_reg = gpiolib_read_reg(gpio, GPLEV(0));

		if(level_reg & (1 << LASER2_PIN_NUM))
			return 1;

		else
			return 0;
	}
	else
		return -1;
}

//This function will change the appropriate pins value in the select register
//so that the pin can function as an output
void setToOutput(GPIO_Handle gpio, int pinNumber)
{
	//Check that the gpio is functional
	if(gpio == NULL)
	{
		printf("The GPIO has not been intitialized properly \n");
		return;
	}

	//Check that we are trying to set a valid pin number
	if(pinNumber < 2 || pinNumber > 27)
	{
		printf("Not a valid pinNumer \n");
		return;
	}

	//This will create a variable that has the appropriate select
	//register number. For more information about the registers
	//look up BCM 2835.
	int registerNum = pinNumber / 10;

	//This will create a variable that is the appropriate amount that 
	//the 1 will need to be shifted by to set the pin to be an output
	int bitShift = (pinNumber % 10) * 3;

	//This is the same code that was used in Lab 2, except that it uses
	//variables for the register number and the bit shift
	uint32_t sel_reg = gpiolib_read_reg(gpio, GPFSEL(registerNum));
	sel_reg |= 1  << bitShift;
	gpiolib_write_reg(gpio, GPFSEL(1), sel_reg);
}

//This function will make an output pin output 3.3V. It is the same
//as what was done in Lab 2 to make the pin output 3.3V
void outputOn(GPIO_Handle gpio, int pinNumber)
{
	gpiolib_write_reg(gpio, GPSET(0), 1 << pinNumber);
}

//This function will make an output pin turn off. It is the same
//as what was done in Lab 2 to make the pin turn off
void outputOff(GPIO_Handle gpio, int pinNumber)
{
	gpiolib_write_reg(gpio, GPCLR(0), 1 << pinNumber);
}

//This is a function used to read from the config file. It is not implemented very
//well, so when you create your own you should try to create a more effective version
void readConfig(FILE* configFile, int* timeout, char* logFileName, int* duration, int* speedLimit, int* distanceBetweenLasers)	{
	//Loop counter
	int i = 0;
	
	//A char array to act as a buffer for the file
	char buffer[255];

	//The value of the timeout variable is set to zero at the start
	*timeout = 0;

	//The value of duration is set to zero at the start
	*duration = 0;

	//The value of the numBlinks variable is set to zero at the start
	*speedLimit = 0;

	//The value of distanceBetweenLasers is set to zero at the start
	*distanceBetweenLasers = 0;

	//This is a variable used to track which input we are currently looking
	//for (timeout, logFileName or numBlinks)
	int input = 0;

	//This will 
	//fgets(buffer, 255, configFile);
	//This will check that the file can still be read from and if it can,
	//then the loop will check to see if the line may have any useful 
	//information.
	while(fgets(buffer, 255, configFile) != NULL)	{
		i = 0;
		//If the starting character of the string is a '#', 
		//then we can ignore that line
		if(buffer[i] != '#')	{
			while(buffer[i] != 0)	{
				//This if will check the value of timeout
				if(buffer[i] == '=' && input == 0)	{
					//The loop runs while the character is not null
					while(buffer[i] != 0)	{
						//If the character is a number from 0 to 9
						if(buffer[i] >= '0' && buffer[i] <= '9')	{
							//Move the previous digits up one position and add the
							//new digit
							*timeout = (*timeout * 10) + (buffer[i] - '0');
						}
						i++;
					}
					input++;
				}
				else if(buffer[i] == '=' && input == 1)	{ //This will find the name of the log file
					int j = 0;
					//Loop runs while the character is not a newline or null
					while(buffer[i] != 0  && buffer[i] != '\n')	{
						//If the characters after the equal sign are not spaces or
						//equal signs, then it will add that character to the string
						if(buffer[i] != ' ' && buffer[i] != '=')	{
							logFileName[j] = buffer[i];
							j++;
						}
						i++;
					}
					//Add a null terminator at the end
					logFileName[j] = 0;
					input++;
				}
				else if(buffer[i] == '=' && input == 2)	{ //This will find the value of duration
					//The loop runs while the character is not null
					while(buffer[i] != 0)	{
						//If the character is a number from 0 to 9
						if(buffer[i] >= '0' && buffer[i] <= '9')	{
							//Move the previous digits up one position and add the
							//new digit
							*duration = (*duration * 10) + (buffer[i] - '0');
						}
						i++;
					}
					input++;
				}
				else if(buffer[i] == '=' && input == 3)	{ //This will find the value of speedLimit
					//The loop runs while the character is not null
					while(buffer[i] != 0)	{
						
						//If the character is a number from 0 to 9
						if(buffer[i] >= '0' && buffer[i] <= '9')	{
							//Move the previous digits up one position and add the
							//new digit
							*speedLimit = (*speedLimit * 10) + (buffer[i] - '0');				
						}
						i++;
					}
					input++;
				}
				else if(buffer[i] == '=' && input == 4)	{ //This will find the value of distanceBetweenLasers				
					//The loop runs while the character is not null
					while(buffer[i] != 0)	{
						//If the character is a number from 0 to 9
						if(buffer[i] >= '0' && buffer[i] <= '9')	{
							//Move the previous digits up one position and add the
							//new digit
							*distanceBetweenLasers = (*distanceBetweenLasers * 10) + (buffer[i] - '0');
						}
						i++;
					}
					input++;
				}
				else
					i++;
			}
		}
	}
}

//This function will get the current time using the gettimeofday function
void getTime(char* buffer)	{
	//Create a timeval struct named tv
  	struct timeval tv;

	//Create a time_t variable named curtime
  	time_t curtime;

	//Get the current time and store it in the tv struct
  	gettimeofday(&tv, NULL); 

	//Set curtime to be equal to the number of seconds in tv
  	curtime=tv.tv_sec;

	//This will set buffer to be equal to a string that in
	//equivalent to the current date, in a month, day, year and
	//the current time in 24 hour notation.
  	strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime));
} 

void measureSpeed(GPIO_Handle gpio, int watchdog, const int duration, const int speedLimit, const int distance, FILE* logFile)	{

	char curTime[30];
	float distanceBetweenLasers = distance / 100.0;
	printf("Distance: %.2f, Laser1: %d, Laser2: %d\n", distanceBetweenLasers, laserDiodeStatus(gpio, 1), laserDiodeStatus(gpio, 2));

	//If, initially either of the 2 photodiodes are disconnected, wait 1 second then check again. If either or both are still disconnected, exit the program
	if(!laserDiodeStatus(gpio, 1) || !laserDiodeStatus(gpio, 2))	{
		sleep(1);
		if(!laserDiodeStatus(gpio, 1) || !laserDiodeStatus(gpio, 2))	{
			getTime(curTime);
			PRINT_MSG(logFile, curTime, "measureSpeed", SEVERITY_ERROR, "There are no lasers connected to one or more of the photodiodes, exiting.\n\n");
			perror("No lasers connected! Exiting!\n");
			return;
		}
	}

	//If the given speedLimit is less than 0, exit with an error code
	if(speedLimit < 0)	{
		
		getTime(curTime);
		perror("Received an invalid speedLimit; exiting\n");
		PRINT_MSG(logFile, curTime, "measureSpeed", SEVERITY_ERROR, "The measureSpeed function was given an invalid speed\n\n");
		return;
	}

	//If the given speedLimit is 0, allow the program to precede
	if(!speedLimit)	{
		getTime(curTime);
		perror("Received a speedLimit as 0; running program but flagging all objects walking through hall\n");
		PRINT_MSG(logFile, curTime, "measureSpeed", SEVERITY_WARNING, "The requested speedLimit is 0. Flagging any objects moving through hall\n\n");
	}

	enum objectLocation { NOONE_IN_HALL, IN_HALL_MOVE_LEFT, IN_HALL_MOVE_RIGHT, EXITED_HALL };
	enum objectLocation currentLocation = NOONE_IN_HALL;

	float objectSpeed = 0;
	float objectSpeeds[1000];
	
	for(int i = 0; i < 1000; i++)
		objectSpeeds[i] = 0;

	int enteringNewState = 0;
	int peoplePassedThrough = 0;
	int numberOfSpeeders = 0;
	int warningIssued = 1;

	time_t startTime = time(NULL);
	time_t enteringTime = time(NULL);
	time_t exitingTime = time(NULL);
	time_t timeInState = time(NULL);



	while((time(NULL) - startTime) < duration)	{
		int laser1Status = laserDiodeStatus(gpio, 1);
		int laser2Status = laserDiodeStatus(gpio, 2);
		// printf("Laser1: %d \t Laser 2: %d\n", laser1Status, laser2Status);

		//This ioctl call will write to the watchdog file and prevent 
		ioctl(watchdog, WDIOC_KEEPALIVE, 0);

		usleep(1000);

		switch(currentLocation)	{

			case NOONE_IN_HALL:
				if(laser1Status && laser2Status)	{
					break;

				}	//If left laser breaks, a person is entering the hall from the left
				else if(!laser1Status)	{
					while(!laser1Status)	{
						usleep(1000);
						laser1Status = laserDiodeStatus(gpio, 1);
						ioctl(watchdog, WDIOC_KEEPALIVE, 0);
					}

					currentLocation = IN_HALL_MOVE_RIGHT;
					enteringNewState = 1;
					enteringTime = time(NULL);

				}	//If right laser breaks, a person is entering the hall from the right
				else if(!laser2Status)	{
					while(!laser2Status)	{
						usleep(1000);
						laser2Status = laserDiodeStatus(gpio, 2);
						ioctl(watchdog, WDIOC_KEEPALIVE, 0);
					}

					currentLocation = IN_HALL_MOVE_LEFT;
					enteringNewState = 1;
					enteringTime = time(NULL);
				}



				break;

			case IN_HALL_MOVE_LEFT:
				
				//The first time a person enters the state, this basically starts a timer. 
				if(enteringNewState)	{
					timeInState = time(NULL);
					enteringNewState = 0;
				}

				//If someone enters the hall but does not leave
				if((time(NULL) - timeInState) > MAX_TIME_IN_HALL && !warningIssued)	{
					getTime(curTime);
					printf("Hey! Watch out! You are blocking the hallway!\n");
					PRINT_MSG(logFile, curTime, "measureSpeed", SEVERITY_WARNING, "Someone is blocking the hallway!\n\n");
					warningIssued = 1;
				}
								
				//Person is leaving the hall in the right direction
				if(!laser1Status)	{
					while(!laser1Status)	{
						usleep(1000);
						laser1Status = laserDiodeStatus(gpio, 1);
						ioctl(watchdog, WDIOC_KEEPALIVE, 0);
					}

					int travelTime = time(NULL) - enteringTime;
					if(!travelTime)	
						objectSpeed = -1;
					else	
						objectSpeed = distanceBetweenLasers / travelTime;
					// printf("ObjectSpeed: %.2f\n", objectSpeed);
					currentLocation = EXITED_HALL;
					peoplePassedThrough++;
					warningIssued = 0;
				}

				//Person leaves the hall in the wrong direction
				if(!laser2Status)	{
					while(!laser2Status)	{
						usleep(1000);
						laser2Status = laserDiodeStatus(gpio, 2);
						ioctl(watchdog, WDIOC_KEEPALIVE, 0);
					}

					currentLocation = NOONE_IN_HALL;
					enteringTime = 0;
					getTime(curTime);
					printf("This hallway is one way only! Pick a direction to walk, buddy!\n");
					PRINT_MSG(logFile, curTime, "measureSpeed", SEVERITY_INFO, "A person turned around in the hallway and walked back out!\n\n");
					enteringNewState = 1;
				}

				break;

			case IN_HALL_MOVE_RIGHT:
				
				//The first time a person enters the state, this basically starts a timer. 
				if(enteringNewState)	{
					timeInState = time(NULL);
					enteringNewState = 0;
				}

				//If someone enters the hall but does not leave
				if((time(NULL) - timeInState) > MAX_TIME_IN_HALL && !warningIssued)	{
					getTime(curTime);
					printf("Hey! Watch out! You are blocking the hallway!\n");
					PRINT_MSG(logFile, curTime, "measureSpeed", SEVERITY_WARNING, "Someone is blocking the hallway!\n\n");
					warningIssued = 1;
				}
				
				//Person leaves the hall in the wrong direction
				if(!laser1Status)	{
					while(!laser1Status)	{
						usleep(1000);
						laser1Status = laserDiodeStatus(gpio, 1);
						ioctl(watchdog, WDIOC_KEEPALIVE, 0);
					}
					
					currentLocation = NOONE_IN_HALL;
					enteringTime = 0;
					getTime(curTime);
					printf("This hallway is one way only! Pick a direction to walk, buddy!\n");
					PRINT_MSG(logFile, curTime, "measureSpeed", SEVERITY_INFO, "A person turned around in the hallway and walked back out!\n\n");
				}
				
				//Person is leaving the hall in the right direction
				if(!laser2Status)	{
					while(!laser2Status)	{
						usleep(1000);
						laser2Status = laserDiodeStatus(gpio, 2);
						ioctl(watchdog, WDIOC_KEEPALIVE, 0);
					}

					int travelTime = time(NULL) - enteringTime;
					if(!travelTime)
						objectSpeed = -1;
					// printf("time(NULL): %d \t enteringTime: %d \t travelTime: %d\n", time(NULL), enteringTime, travelTime);
					else
						objectSpeed = distanceBetweenLasers / travelTime;
					// printf("ObjectSpeed: %.2f\n", objectSpeed);
					currentLocation = EXITED_HALL;
					peoplePassedThrough++;
					warningIssued = 0;
				}

				break;

			case EXITED_HALL:
				if(objectSpeed < 0)	{
					getTime(curTime);
					printf("Is that even a person? The speed was off the charts!!\n");
					
					for(int i = 0; i < 3; i++)	{
						outputOn(WARNING_LED_PIN);
						usleep(200000);
						outputOff(WARNING_LED_PIN);
						usleep(200000);
					}

					PRINT_MSG(logFile, curTime, "measureSpeed", SEVERITY_INFO, "An extremely fast... thing just went through the hall\n");
				}
				else if(objectSpeed > speedLimit)	{
					getTime(curTime);
					printf("SLOW DOWN! You are travelling at %.2f m/s over the speed limit!\n", (objectSpeed - speedLimit));

					for(int i = 0; i < 3; i++)	{
						outputOn(WARNING_LED_PIN);
						usleep(200000);
						outputOff(WARNING_LED_PIN);
						usleep(200000);
					}
					
					PRINT_MSG(logFile, curTime, "measureSpeed", SEVERITY_WARNING, "A person just speed through the hall at a speed of: ");
					PRINT_VALUE(logFile, objectSpeed);
					objectSpeeds[peoplePassedThrough - 1] = objectSpeed;
					numberOfSpeeders++;
				}
				else	{
					getTime(curTime);
					printf("The speed of the person passing through the hall was: %.2f\n", objectSpeed);
					PRINT_MSG(logFile, curTime, "measureSpeed", SEVERITY_INFO, "A person just passed through the hall with a speed of: ");
					PRINT_VALUE(logFile, objectSpeed);
					objectSpeeds[peoplePassedThrough - 1] = objectSpeed;
				}

				objectSpeed = 0;
				currentLocation = NOONE_IN_HALL;
				break;
		}
	}

	float maxSpeed = 0;
	float minSpeed = FLT_MAX;
	float sumOfSpeeds = 0;
	for(int i = 0; i < peoplePassedThrough; i++)	{
		if(objectSpeeds[i] > maxSpeed)
			maxSpeed = objectSpeeds[i];
		if(objectSpeeds[i] < minSpeed)
			minSpeed = objectSpeeds[i];

		sumOfSpeeds += objectSpeeds[i];
	}
	float averageSpeed = sumOfSpeeds / peoplePassedThrough;

	printf("The number of people that passed through the hall in the last %d seconds was %d\n", duration, peoplePassedThrough);
	if(peoplePassedThrough)	{
		printf("The fastest person that went through the hall travelled at a speed of approximately %.2f m/s\n", maxSpeed);
		printf("The slowest person that went through the hall travelled at a speed of approximately %.2f m/s\n", minSpeed);
		printf("The average speed of the people passing through the hall was %.2f m/s\n", averageSpeed);
		getTime(curTime);
		PRINT_MSG(logFile, curTime, "measureSpeed", "The fastest person that went through the hall travelled at a speed of approximately");
		PRINT_VALUE(logFile, maxSpeed);
		PRINT_MSG(logFile, curTime, "measureSpeed", "The slowest person that went through the hall travelled at a speed of approximately");
		PRINT_VALUE(logFIle, minSpeed);
		PRINT_MSG(logFIle, curTime, "measureSpeed", "The average speed of the people passing through the hall was approximately");
		PRINT_VALUE(logFile, averageSpeed);
	}
}
