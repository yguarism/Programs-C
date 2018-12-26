#include <iostream>

#include <stdlib.h>

#include <cmath>

using namespace std;

int main(const int argc, const char *argv[]) {

	int rc = 0;
	
	if (argc < 7) 
	{
		cerr<<"Error: Expected 6 arguments; received "<<argc-1<<"; exiting"<<endl; 
		rc = 0;
	}
	if (argc > 7) 
	{
		cerr<<"Warning: Expected 6 arguments; received " <<argc-1<<"; ignoring extraneous arguments"<<endl; 
		rc = 1;
	}
	
	float x1 = atof(argv[1]);
	float y1 = atof(argv[2]);
	float x2 = atof(argv[3]);
	float y2 = atof(argv[4]);
	float x3 = atof(argv[5]);
	float y3 = atof(argv[6]);
	float slope1 = (y1-y2)/(x1-x2);
	float slope2 = (y2-y3)/(x2-x3);
	float slope3 = (y3-y1)/(x3-x1);
	
	float s1 = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
	float s2 = sqrt(pow(x3-x2, 2) + pow(y3-y2, 2));
	float s3 = sqrt(pow(x3-x1, 2) + pow(y3-y1, 2));
	
	float s = (0.5*(s1+s2+s3));
	
	float a = sqrt(s*(s-s1)*(s-s2)*(s-s3));
	
	if (abs(x2-x1)<0.01 && abs(x3-x1)<0.01 && abs(y2-y1)<0.01 && abs(y3-y1)<0.01)
	{
		cerr<<"The points ("<< x1<< "," <<y1<< "), ("<<x2<<","<<y2<< "), and (" <<x3<<"," <<y3<< ") overlap; they do not form a triangle"<<endl;
		rc = -1;
	}
	
	if (abs (x2-x1)< 0.01 && abs(y2-y1)<0.01 &&!abs(y3-y1)<0.01 &&!abs(x3-x1)<0.01)
	{
		cerr<<"The points ("<<x1<< ","<<y1<<"), ("<<x2<<","<< y2<< "), and ("<< x3<<","<< y3<<") form a line with slope: " << slope2<<endl;
		rc = -1;
	}
	
	if (abs (x2-x3)< 0.01 && abs(y2-y3)<0.01 &&!abs(y3-y1)<0.01&&!abs(x3-x1)<0.01)
	{
		cerr<<"The points ("<<x1<< ","<<y1<<"),("<<x2<<","<< y2<< "), and ("<< x3<<","<< y3<<") form a line with slope: " << slope3<<endl;
		rc = -1;
	}
	
	if (abs (x3-x1)< 0.01 && abs(y3-y1)<0.01 &&!abs(y2-y1)<0.01&&!abs(x2-x1)<0.01)
	{
		cerr<<"The points ("<<x1<< ","<<y1<<"),("<<x2<<","<< y2<< "), and ("<< x3<<","<< y3<<") form a line with slope: " << slope1<<endl;
		rc = -1;
	}
	if (abs(slope1-slope2)<0.01 && abs(slope1-slope3)<0.01)
	{
		cerr<<"The points ("<<x1<< ","<<y1<<"), ("<<x2<<","<< y2<< "), and ("<< x3<<","<< y3<<") form a line with slope: " << slope1<<endl;
		rc = -1;
	}
	else if(a>0.01)
	{	
		cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
	}
	
	return rc;
}