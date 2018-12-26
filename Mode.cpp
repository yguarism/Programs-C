

int mode(const int dataset[], const int size, int modes[])
{
	int data[size];
	
	if (size < 0){ 
		return -1;
	}
	
	for (int i = 0; i < size; ++i)      // loop over all inputs, store in array
		data[i] = dataset[i];
	
	int somethingChanged = 1;
	
	while (somethingChanged) { // sorts all numbers
		somethingChanged = 0;
		int i = 0;
		while (i < size-1) {
			if (data[i] > data[i+1]) {   // Wrong order, swap them
				int tmp;
				tmp = data[i];
				data[i] = data[i+1];
				data[i+1] = tmp;
				somethingChanged = 1;
				}
			++i;
		}
	}
	int mod = 0;
	int i = 1;
	int k = 0;
	int modecount = 1; //count for the mode (highest amount of repetition)
	int numcount = 1; //count how many of the numbers repeat
	
	if (size == 1){
		modes[k] = data[i];
		k++;
	}

	while (i < size){
		
		int num = data[i-1];
		if (data[i] == num){
			numcount ++;
			
			if (i == size-1){
				
				mod = num;
				modes[k] = mod;
				k++;
			}
		
		}
		else if (modecount > 1 && numcount == modecount){
			mod = num;
			modes[k] = mod;
			k++;
			numcount = 1;

		}		
		
		else if (numcount > modecount){
			modecount = numcount;	
			mod = num;
			numcount = 1;
			modes[k] = mod;
			k++;
				
			}
			
			
		i++;
	}
		
	if (i == size && k == 0){

		return -1;
	}	
	
	if (size == 0){
		
		k = 0;
	}
	
	return k;
}


#ifndef MARMOSET_TESTING

/*
 * Marmoset doesn't see anything in here
 *
 * Use this space to test your code
 */

#include <cstdlib>  // atoi
#include <iostream> // cout, endl

using namespace std;

#define MIN_ARGS 2

int main(const int argc, const char* const argv[]){
	
	/*if (argc<2){// not enough inputs
		cerr << "Error: Unable to compute mode over data set" <<endl;		
		return -1;
	}*/
	int sz = argc - 1;                // 1 for name
	int input[sz];  				  // to hold inputs

	for (int i = 0; i < sz; ++i)      // loop over all inputs, store in array
		input[i] = atoi(argv[i + 1]);   // atoi = string to integer

	int modes[sz];                    // there will be at most as many modes
                                    // as there are numbers

	int ret = mode(input, sz, modes); // call the function
  
	if (ret == -1){
	  
		cerr << "Error: Unable to compute mode over data set" <<endl;
		return -1;
	}

	cout << "Function returned: " << ret << " modes" << endl;
	
	if (ret > 0){
		cout << "Modes were:";
		for (int i = 0; i < ret; ++i)     // loop over and print all modes
			cout << ' ' << modes[i];
		cout << endl;
	}
	return 0;
}

#endif
