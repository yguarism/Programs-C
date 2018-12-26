#include <iostream>

#include <stdlib.h>

#include <cmath>

using namespace std;

int main(const int argc, const char *argv[]) {
	
	int rc = 0;
	int i = 1;
	float sum = 0;
	float avg = 0;
	float max = 0;
	float min = 150;

	int x = 0;
	
	if (argc < 2){
		
		cerr<< "Error: Unable to compute statistics over data set because there are not enough data points" << endl;
		return -1;
	}
	
	while (i < argc){ // check the counter is less than the total inputs
		// put number in spot
		// add number inputted to sum
		float num = atof (argv[i]);
		
		if (num > 150){
		
			cout<< "Warning: invalid voltage reading " << num << " ignored in calculation" << endl;
			rc = 1;
		}
		
		else if (num > -1 && num < 150) {
			
			if (num > max){
				
				max = num;
			}
			
			if (num < min){
				
				min = num;
			}
			
			sum = sum + num; 
			x++;
		
		}
		
		else if (num < 0){
			
			i = i + argc;
		}
		
		
		i = i +1; // increase counter by one
	}
	
	if (x>0){
		
		avg = (sum)/x;
		cout<< "Number of voltage readings: " << x << endl;
		cout<< "Minimum voltage: " << min << endl;
		cout<< "Average voltage: " << avg << endl;
		cout<< "Maximum voltage: " << max << endl;
		
	}
	
	if (x == 0){
		
		cerr<< "Error: Unable to compute statistics over data set because there are no valid data points" << endl;
		return -1;
	}
	
	return rc;
	
}