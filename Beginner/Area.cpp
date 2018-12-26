#include <iostream>
#include <stdlib.h>

using namespace std;

int main(const int argc, const char *argv[]) 
{
	int rc = 0;
	
	if (argc < 3)
	{
		cerr<<"Error: Expected 2 arguments; received "<<argc-1<<"; exiting"<<endl; 
		return -1;
	}
	
	if (argc > 3)
	{
		cerr<<"Warning: Expected 2 arguments; received " <<argc-1<<"; ignoring extraneous arguments"<<endl; 
		rc = 1;
	}
	
	extern float f(float x);	
	float a = atof(argv[1]);
	float b = atof (argv[2]);
	float x = a;
	float area1 = 0;
	float areat = 0;
	
	if (b<a){
		
		cerr<< "Error: Unable to compute area because bounds are invalid" << endl;
		return -1;
	}
	if (b==a){
		
		areat=0; 
		
	}
	
	while (x < b){
		
		area1 = 0.01* 0.5*(f(x+0.01) + f(x));
		areat = areat + area1;
		x = x +0.01;
		
	}
	
	cout << "The area under f(x) from " << a << "to "<< b << "is " << areat << endl; 
	
	
	return rc;
	
}