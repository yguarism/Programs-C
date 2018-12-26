#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[]) 

{
	int rc = 0;

	float s = atof(argv[1]);
	float x0 = 1;
	float x1 = (x0 + (s/x0))/2;
	float err = ((s-(x1*x1))/s);
	
	if (argc > 2) 
	{
		cerr<<"Error: Expected 1 arguments; received "<<argc-1<<"; ignoring extraneous arguments"<<endl; 
	}
	
	if (s < -0.00001) 
	{
		cerr<<"Error: cannot compute square root of a negative number" <<endl; 
		return -1;
	}
	
	while (err > 0.00001 || err< -0.00001)
	{
		x0 = x1;
		x1 = (x0 + (s/x0))/2;
		err = ((s-(x1*x1))/s);
	}
	
	cout << "The square root of " << s << " is " << x1 << endl;
	
	
	return rc;
}
	
	
