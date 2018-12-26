#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

extern float f(float t);
int main(const int argc, const char *argv[]) 
{
	if (argc < 2)
	{
		cerr<<"Error: Expected 1 arguments; received "<<argc-1<<"; exiting"<<endl; 
		return -1;
	}
	
	if (argc > 2)
	{
		cerr<<"Warning: Expected 1 arguments; received " <<argc-1<<"; ignoring extraneous arguments"<<endl; 
		rc = 1;
	}
		
	int rc = 0;
	float t = atof(argv[1]);
	float s = (f(t+0.0001) - f(t-0.0001))/ (0.0002);
	
	cout << "The slope of f(t) at t = " << t << "is "<< s << endl; 
	
	
	
	return rc;
	
}