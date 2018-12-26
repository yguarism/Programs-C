#include <iostream> 

#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[]) {
	
	int rc = 0;
	int sz = 10;
	int i = 1;
	int v1= 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int e = 0;
	int f = 0;
	int g = 0;
	int h = 0;
	int k = 0;
	int l = 0;
	
	
	
	
	if (argc < 2) { // not enough arguments
		cerr<< "Error: Unable to compute histogram over data set because there are not enough arguments" <<endl; 
		return -1;
	}
	
	
	if (argc >= 2){
		
		int Histo[sz];
		float Num [argc-2];
		while (i < argc-1){
			float volt = atof (argv[i]);
			
			Num[i-1] = volt;
			i++;
		}
		
		i =1;
		
		while (i < argc-1){
			
			float volt = Num[i-1];
			
			if (volt < 106 && volt > 0){
				
				a++;
				v1++;
					
			}
			else if (volt < 109 && volt >= 106){
				
				b++;
				v1++;
			}
			else if (volt < 112 && volt >= 109){
				
				c++;
				v1++;
			}	
			else if (volt < 115 && volt >= 112){
				
				d++;
				v1++;
			}
			else if (volt < 118 && volt >= 115){
				
				e++;
				v1++;
				
			}
			else if (volt < 121 && volt >= 118){
				
				f++;
				v1++;
			}
			else if (volt < 124 && volt >= 121){
				
				g++;
				v1++;
			}
			else if (volt <= 127 && volt >= 124){
				
				h++;
				v1++;
			}
			else if (volt < 150 && volt > 127){
					
				k++;
				v1++;
			}
			else if (volt >= 150 || volt ==0){
				
				cout<<"Warning: invalid voltage reading " << volt << " ignored in calculation" << endl; 
				rc = 1;
				l++;
			}
				
			i = i+1;
		
		}
			
		Histo [0] = a;
		Histo [1] = b;
		Histo [2] = c;
		Histo [3] = d;
		Histo [4] = e;
		Histo [5] = f;
		Histo [6] = g;
		Histo [7] = h;
		Histo [8] = k;
		Histo [9] = l;
		
		if (atof (argv [argc-1])> 0){
			cerr<<"Error: Unable to compute histogram over data set because of a missing terminator" <<endl; 
			return -1;
		}	
		
		if (v1 == 0){
			cerr<<"Error: Unable to compute histogram over data set because of invalid voltage entries" <<endl; 
			return -1;
		}
		
		cout << "Number of voltage readings: " << v1 << endl;
		cout << "Voltage readings (0-106): " << Histo[0] << endl;
		cout << "Voltage readings [106-109): " << Histo[1] << endl;
		cout << "Voltage readings [109-112): " << Histo[2] << endl;
		cout << "Voltage readings [112-115): " << Histo[3] << endl;
		cout << "Voltage readings [115-118): " << Histo[4] << endl;
		cout << "Voltage readings [118-121): " << Histo[5] << endl;
		cout << "Voltage readings [121-124): " << Histo[6] << endl;
		cout << "Voltage readings [124-127]: " << Histo[7] << endl;
		cout << "Voltage readings (127-150): " << Histo[8]<< endl;
		cout << "Invalid readings: " << Histo[9] << endl;
	}
		
	
	return rc;
}