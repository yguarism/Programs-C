#include <iostream>

#include <stdlib.h>

#include <cmath>

using namespace std;

int main(const int argc, const char *argv[]) {
	
	int rc = 0;
	int i = 2;
	int vi = 0;
	float volt = 0;
	float ewma = 0;
	
	if (argc < 3){
		
		cerr<< "Error: Unable to compute statistics over data set because there are not enough data points" << endl;
		return -1;
	}
	
	if (argc >= 3){
		
		float alpha = atof(argv[1]);
		if (alpha > 1 || alpha <= 0){
			
			cerr<< " Error: Unable to compute statistics over data set because there was an invalid weighting parameter" << endl;
			return -1;
		}
		if (atof(argv[2])> 0){
		cout << "Sample Value EWMA" << endl;
		}
		else{
			cerr<< "Error: Unable to compute statistics over data set because there are not enough data points" << endl;
			return -1;
		}
		
		while (i < argc){
			
			volt = atof (argv[i]); 
			if (volt >= 150 || volt == 0){
				cout<< "Warning: invalid voltage reading " << volt << " ignored in calculation" << endl;
					rc = 1;
					
					if (i == 2){
						ewma = atof (argv[i+1]);
					}
				}
			if (i == 2 && volt < 150){
				ewma = volt;
			}
			
			if (volt > 0 && volt < 150) {

				ewma = alpha* volt + (1-alpha)* ewma;
				cout << i-1 << "	" << volt << "	"<< ewma<< "	" << endl;
				vi = vi + 1;
				}
			if (volt < 0){
				i = i + argc;
				}
			i++;
		}
		
			if (volt > 0){
			
				cerr << "Error: Missing Terminator" << endl;
				return -1;
			}
			if (vi == 0){
			
				cerr<< "Error: Unable to compute statistics over data set because there are no valid data points" << endl;
				return -1;
			}
		}
	// Formula is: EWMA = alpha * volt + (1- alpha) * (the EWMA from before)
	
	//Inputs: Alpha, Volt, avg (numbers between 0 and 150)
	//If less than 0 terminate code
	//If Greater than 150 Place Warning message
	//Need terminator message
	
	
	
	// outputs: EWMA, Sample #, Value

	return rc;
}