#include <iostream>

#include <stdlib.h>

#include <cmath>

using namespace std;

int main(const int argc, const char *argv[]) {

	if (argc < 7) 
	{
		cerr<< argv[0]<<"usage error expected 6 arguments; received"<<argc-1<<";exiting"<<endl; 
		return -1;
	}
	
	if (argc > 7) 
	{
		cerr<<argv[0]<<"usage warning expected 6 arguments; received" <<argc-1<<";exiting"<<endl; 
		return -1;
	}

	double x1 = atof(argv[1]);
	double y1 = atof(argv[2]);
	double x2 = atof(argv[3]);
	double y2 = atof(argv[4]);
	double x3 = atof(argv[5]);
	double y3 = atof(argv[6]);

	float s1 = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
	float s2 = sqrt(pow(x3-x2, 2) + pow(y3-y2, 2));
	float s3 = sqrt(pow(x3-x1, 2) + pow(y3-y1, 2));
	
	float s = (0.5*(s1+s2+s3));
	
	
	float a = sqrt(s*(s-s1)*(s-s2)*(s-s3));
	cout << s1 << " " << s2 << " " << s3<< endl;
	cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;

	return 0;
}