#include <iostream>

#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[]) {
	
	int rc = 0; // return value
	int sz = 1; // size of array
	int v1 = 0; //Valid inputs counter
	int Num = 0;
	int j = 1;
	int mid = 0;
	int mid1 = 0;
	float x = 0;
	float medO = 0;
	float volt = atof (argv[sz]);
	float Ar[argc-1];
	
	if (argc < 2){ // not enough arguments
		cerr<<"Error: Not enough data provided to calculate"<<endl; 
		return -1;
	}
	
	if (argc >= 2){
		// inputs: volt > 0 , volt < 150, array to store all values
		
		while(sz < argc){
			volt = atof (argv[sz]);
			if (volt < 0){
				break;
			}
			if (volt > 0 && volt < 150){
			
				Ar[j] = volt;
				v1++;
				j= j +1;
			}
			if (volt == 0 || volt >= 150){
				cout<<"Warning: Invalid Voltage Reading " << volt << " exiting" << endl; 
				rc = 1;
			}
			sz++;
		}
	
		sz = j -1;
	
		int somethingChanged = 1;
	
		while (somethingChanged) {
			somethingChanged = 0;
			int i = 0;
   
			while (i < sz) {
				if (Ar[i] > Ar[i+1]) {   // Wrong order, swap them
					float tmp;
					tmp = Ar[i];
					Ar[i] = Ar[i+1];
					Ar[i+1] = tmp;
					somethingChanged = 1;
				}
				++i;
			}
		}
	
	/*int i = 1;
	
	while (i < sz) {
		cout << i << ": " << Ar[i+1] << endl;
		++i;
	}*/
	
		if (sz%2 ==0){
		
			mid = sz/2;
			Num = mid;
		
			cout << "Number of Voltage Readings: "<< sz << endl;
		
			mid1 = mid + 1;
		
			medO = (Ar[mid1] + Ar[Num])/2;
		
			cout << "Median voltage: "<<medO << endl;
			
		}
		
	
		else{
			mid = sz/2 + 1;
			Num = mid;
			x = Ar[Num];
			cout << "Number of Voltage Readings: "<< sz << endl;
			cout << "Median voltage: "<< x << endl;
		
		}
	
		if (atof (argv [argc-1])> 0){
		
			cerr<<"Error: Missing Terminator "<<endl; 
			return -1;
		}
		if (v1 == 0){
		
			cerr<<"Error: Unable to compute statistics over data set because there are no valid data points" << endl;
			return -1;
		}
	}
	
	return rc;
	
	
	
}