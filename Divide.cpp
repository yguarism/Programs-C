#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

int main (const int argc, const char*argv[]){
	int rc = 0;
	
	if (argc-1 < 3){
		cerr << "Not Enough Arguments" << endl;
		return -1;
	}
	if (argc-1 > 3){
		cout << "Warning: Too many Args, ignoring the extra" << endl;
		rc = 1;
	}
	
	int base = atoi (argv[1]);
	int exp1 = atoi (argv[2]);
	int exp2 = atoi (argv[3]);
	int exp = 0;
	
	if (base <= 0){
		cerr << "Invalid" << endl;
		return -1;
	}
	
	exp = exp1 - exp2;
	int i = 0;
	if (exp > 0){
		cout << "The Result is: " << pow(base, exp) << endl;
	}
	if (exp == 0){
		cout << "The Result is: 1" << endl;
	}
	if (exp < 0){
		exp *= -1;
		float ans = 1/ pow(base, exp);
		cout << "The Result is: " << ans << endl;
	}
	
	if (base == 2){
		cout << "In Binary the result is: 1";
		
		if (exp < 0){
			exp *= -1;
		}
		while (i < exp){
			cout << 0;
			i++;
		}
		
	}

	return rc;
	
}