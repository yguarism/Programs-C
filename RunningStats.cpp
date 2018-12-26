#include <iostream>

#include <stdlib.h>

#include <cmath>

using namespace std;

int main(const int argc, const char *argv[]) {
	
	int rc = 0;
	float min = 150;
	float max = 0;
	float sum = 0;
	float avg = 0;
	float volts = 0;
	int i = 0;
	int vi = 0;
	
	if (argc < 2){
		
		cerr<< "Error: Unable to compute statistics over data set because there are not enough data points" << endl;
		return -1;
	}
	
	cout << "Sample Value Minimum Average Maximum" << endl;
	
	while (i < argc-1){
		volts = atof(argv [i+1]);
		
		if (volts > 150){
			cout<< "Warning: invalid voltage reading " << volts << " ignored in calculation" << endl;
			rc = 1;
		} 
		
		if (volts < 150 && volts >= 0){
			sum = sum + volts;
			vi = vi + 1;
		
		// Calculate Max and Min as each number goes through
			if (volts > max){
				max = volts;
			}
			if (volts < min){
				min = volts;
			}	
			 avg = sum/vi;
			 cout << i + 1 << "	" << atof(argv[i+1]) << "	" << min << "	" << avg << "	" << max << endl;
		}
		
		if (volts < 0){
			i = i + argc;
		}
		
		i++;
		
		}
	if (volts > 0){
		
		cerr << "Error: Missing Terminator" << endl;
		return -1;
	}
	
	if (vi == 0){
		
		cerr<< "Error: Unable to compute statistics over data set because there are no valid data points" << endl;
		return -1;
	}
// inputs: floats of voltages < 150 but > 0 * idk how many there are
// voltages < 0 --> end program
// voltages > 150 --> omitted from calculations but continue

// outputs: Minimum, Maximum and Average as a table of samples
// outputs must come out in streams as eg. first number, first number and second number, first second and third etc. 
	
	

	return rc;
}