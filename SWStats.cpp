#include <iostream>

#include <stdlib.h>

#include <cmath>

using namespace std;

int main(const int argc, const char *argv[]) {
	// inputs: window size (1st input), 0< voltages < 150, needs a terminator (-1)
	int rc = 0;
	float volt = 0;
	int i = 2;
	int numinwin = 1;
	int vi = 0;
	float min = 150;
	float max = 0;
	
	if (argc < 3){
		cerr<< "Error: Unable to compute statistics over data set because there are not enough data points" << endl;
		return -1;
	}
	
	if (argc >= 3){
		int window = atoi (argv[1]);	// What is my window size? 
		cout << "Window Size: " << window << endl;
		cout << "Sample Value SWMinimum SWMaximum"<< endl;
	
		if (window <= 0){   // window size cant be greater than number of arguments
			cerr<< "Error: Unable to compute statistics over data set because window size is invalid" << endl;
			return -1;
		}
	
		while (numinwin <= window){ //look at first valid input in window calculate all values // look at second valid input in window etc.
			volt = atof (argv[i]);
			
			if (volt < 0){
				numinwin = numinwin + window;
				}	
			else if (volt < 150 && volt > 0){
				vi = vi + 1;
		
			// Calculate Max and Min as each number goes through
				if (volt > max){
					max = volt;
				}
				if (volt < min){
					min = volt;
				}			
				cout << vi << "	" << volt << "	" << min << "	" << max << endl;
			}
			else if (volt >= 150 || volt == 0){
				cout<< "Warning: invalid voltage reading " << volt << " ignored in calculation" << endl;
				vi = vi + 1;
				rc = 1;
			}
			
			numinwin++;
			i++; 
		}// until window is full
		
		i = i -(window-1);
		numinwin = 1;
		min = 150;
		max = 0;
		
		while (i < argc-2){
			while (numinwin <= window){ //look at first valid input in window calculate all values // look at second valid input in window etc.
				volt = atof (argv[i]);
	
				if (volt < 0){
					i = i + argc;
				}	
			
				else if (volt < 150 && volt > 0){

					if (volt > max){
						max = volt;
					}
					if (volt < min){
						min = volt;
					}			
				}
			
				numinwin++;
				i++; 
			}
			
			vi = vi + 1;
		
			if (volt < 150 && volt > 0){
				cout << vi << "	" << volt << "	" << min << "	" << max << endl;
			}
		
			if (volt >= 150 || volt == 0){
				cout<< "Warning: invalid voltage reading " << volt << " ignored in calculation" << endl;
				vi = vi + 1;
				rc = 1;
			}
			
			i = i -(window -1);
			numinwin = 1;
			min = 150;
			max = 0;
		}
	
		if (atof (argv[argc-1]) >= 0){// if volt > 0 terminate code
			cerr << "Error: Missing Terminator" << endl;
			return -1;
		}
	}
	return rc;
}