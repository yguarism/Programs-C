#include <iostream> // ERROR: SAMPLEINVALID is wrong

#include <stdlib.h>

#include <math.h>

using namespace std;

int main(const int argc, const char *argv[]) {
	
	int rc = 0; // return value
	int sz = 1; // size of array
	int vi = 0; //Valid inputs counter
	int j = 1; // counter for adding into array
	int i = 1; //counter for stddev calculations
	float popstdev = 0;
	float avg = 0; // x bar
	float N = 0; //Number of values in data set 
	float sum = 0; // sum for avg calc
	float summa = 0; // summation xi - xbar
	float sampstdev = 0;
	float Num[argc-2]; //Array of size of all numbers inputted
	
	if (argc < 2){ // not enough arguments
		cerr<< "Error: Unable to compute standard deviations over data set because there are not enough arguments" <<endl; 
		return -1;
	}
	
	if (argc >= 2){
		// inputs: volt > 0 , volt < 150, array to store all values
		
		while(sz < argc){
			float volt = atof (argv[sz]); // inputting values 
			if (volt < 0){
				break;
			}
			if (volt > 0 && volt < 150){
			
				Num[j] = volt;
				vi++;
				j= j +1;
			}
			if (volt == 0 || volt >= 150){
				cout<<"Warning: Invalid Voltage Reading " << volt << " exiting" << endl; 
				rc = 1;
			}
			sz++;
		}
		
		if (vi == 0) {
			
			cerr<<"Error: Unable to compute standard deviations over data set because there are no valid data points" << endl;
			return -1;
		}
		
		i = 0;
		
		sz = j -1; // change sz of array to total number of valid numbers there are
		
		while (i <= sz){
			sum = sum + Num[i+1];
			i++;
		}
		
		avg = sum/sz;
		
		i = 0;
		
		while (i < sz){ // calculate popstdev
			
			summa = summa + pow ((Num[i+1] - avg), 2.0);
			i++;
		}
		
		N = sz; // i need a float value for calculations
		
		popstdev = sqrt((1/N)*summa); 
		sampstdev = sqrt((1/(N-1)) * summa); 	
		if (atof (argv [argc-1])> 0){
		
			cerr<<"Error: Unable to compute standard deviations over data set because of a missing terminator "<<endl; 
			return -1;
		}
		else if (N > 1) {
			cout << "Number of voltage readings: " << sz << endl;
			cout << "Population standard deviation: " << popstdev << endl;
			cout << "Sample standard deviation: " << sampstdev << endl;	
		}
		else if ((1/N)*summa < 0){
			cout << "Number of voltage readings: " << sz << endl;
			cout << "Population standard deviation: undefined" << endl;
			cout << "Sample standard deviation: " << sampstdev << endl;	
		}
		else if ((1/(N-1)*summa < 0)){
			cout << "Number of voltage readings: " << sz << endl;
			cout << "Population standard deviation: "<< popstdev << endl;
			cout << "Sample standard deviation: undefined" << endl;	
		}
		
		else if (vi > 0 && N == 0){ 
		
			cout << "Number of voltage readings: " << sz << endl;
			cout << "Population standard deviation: infinity" << endl;
			cout << "Sample standard deviation: " << sampstdev << endl;
		}
		else if (vi > 0 && N == 1){
			cout << "Number of voltage readings: " << sz << endl;
			cout << "Population standard deviation: " << popstdev << endl;
			cout << "Sample standard deviation: undefined" << endl;
		}
		
	}

	return rc;	
}
