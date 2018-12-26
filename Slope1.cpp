#include <iostream>
#include <cmath>
#include<stdlib.h>

using namespace std;

int main(const int argc, const char* argv[]) {

	int rc =0;

	if (argc <= 4) {
		cerr << "Error: Expected 4 arguments; received "<< argc-1<< "; exiting" << endl; 
		return -1;
	}
	if (argc >= 6) {
		cerr << "Warning: Expected 4 arguments; received "<< argc-1<< "; ignoring extraneous arguments" << endl; 
		rc = 1;
	}

	float x1= atof(argv[1]);
	float y1= atof(argv[2]);
	float x2= atof(argv[3]);
	float y2= atof(argv[4]);

	float slope = (y2-y1)/ (x2-x1);

	if (fabs(x1 - x2) < 0.000001 && fabs(y1 - y2) < 0.000001){
		cout << "The points (" << x1 << "," << y1 << ") and (" << x2 << "," << y2 << ") are within " << 0.000001*100 << "% of each other; no slope computed." << endl;
		return rc;
	}

	else
		cout<< "The slope of(" << x1 << "," << y1 << ")-(" << x2 << "," << y2 << ") is " << slope <<endl;
	
	cout << rc << endl;
	return rc;

}
