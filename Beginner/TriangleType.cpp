#include <iostream>

#include <stdlib.h>

#include <cmath>

using namespace std;

int main(const int argc, const char *argv[]) 
{

	int rc = 0;

	float x1 = atof(argv[1]);
	float y1 = atof(argv[2]);
	float x2 = atof(argv[3]);
	float y2 = atof(argv[4]);
	float x3 = atof(argv[5]);
	float y3 = atof(argv[6]);
	
	float s1 = sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
	float s2 = sqrt(pow(x3-x2, 2) + pow(y3-y2, 2));
	float s3 = sqrt(pow(x3-x1, 2) + pow(y3-y1, 2));
	float s = (0.5*(s1+s2+s3));
	
	
	float a = sqrt(s*(s-s1)*(s-s2)*(s-s3));
	
	if (abs(s1-s2)/s2 > 0.00001 && abs(s2-s3)/s2 > 0.00001 && abs(s1-s3)/s3 > 0.00001) //scalene
	{
		if (s1>s2 && s1>s3) // side 1 largest
		{
			if ((pow(s2, 2) + pow(s3, 2) )-pow(s1, 2) < 0.01 && (pow(s2, 2) + pow(s3, 2) )-pow(s1, 2) > -0.01) // right
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "scalene right" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}
			else if ((pow(s2, 2) + pow(s3, 2) )-pow(s1, 2) > 0.00001) // acute
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "scalene acute" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}
			else if ((pow(s2, 2) + pow(s3, 2) )-pow(s1, 2) < -0.00001) // obtuse
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "scalene obtuse" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}
		}
		else if (s2>s1 && s2>s3) // side 2 largest
			{
			if ((pow(s1, 2) + pow(s3, 2) )-pow(s2, 2) < 0.01 && (pow(s1, 2) + pow(s3, 2) )-pow(s2, 2) > -0.01) // right
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "scalene right" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}
			
			else if ((pow(s1, 2) + pow(s3, 2) )-pow(s2, 2) > 0.00001) // acute
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "scalene acute" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}
			
			else if ((pow(s1, 2) + pow(s3, 2) )-pow(s2, 2) < -0.00001) // obtuse
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "scalene obtuse" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}
			}
		else if (s3>s1 && s3>s2) // side 3 largest
			{
			if ((pow(s1, 2) + pow(s2, 2) )-pow(s3, 2) < 0.01 && (pow(s1, 2) + pow(s2, 2) )-pow(s3, 2) > -0.01) // right
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "scalene right" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}
			else if ((pow(s1, 2) + pow(s2, 2) )-pow(s3, 2) > 0.00001) // acute
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "scalene acute" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}
			else if ((pow(s1, 2) + pow(s2, 2) )-pow(s3, 2) < -0.00001) // obtuse
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "scalene obtuse" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}
			}			
	}
	else if ((abs(s1-s2)/s2 < 0.00001 && abs(s2-s3)/s2 > 0.00001) || (abs(s2-s3)/s2 < 0.00001 && abs(s1-s3)/s1 > 0.00001) || (abs(s1-s3)/s1 < 0.00001 && abs(s2-s1)/s1 > 0.00001))	//isosceles	
	{
		if ((abs(s1-s2)/s2 < 0.00001 && abs(s2-s3)/s2 > 0.00001) && (s3 > s1)) //s3 is the larger
		{
			if ((pow(s2, 2) + pow(s1, 2) )-pow(s3, 2) < 0.01 && (pow(s2, 2) + pow(s1, 2) )-pow(s3, 2) > -0.01) // right
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "isosceles right" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}
			else 
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "isosceles obtuse" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}		
		}
		else if ((abs(s1-s2)/s2 < 0.00001 && abs(s2-s3)/s2 > 0.00001) && (s3 < s1))// diff side smaller
		{
			cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "isosceles acute" << endl;
			cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
		}
		
		
		if ((abs(s2-s3)/s2 < 0.00001 && abs(s1-s3)/s1 > 0.00001) && (s1 > s2)) //s1 is the larger
		{
			if ((pow(s2, 2) + pow(s3, 2) )-pow(s1, 2) < 0.00001 && (pow(s2, 2) + pow(s3, 2) )-pow(s1, 2) > -0.00001) // right
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "isosceles right" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}
			else 
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "isosceles obtuse" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}		
		}
		else if ((abs(s2-s3)/s2 < 0.00001 && abs(s1-s3)/s1 > 0.00001) && (s1 < s2))
		{
			cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "isosceles acute" << endl;
			cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
		}
		
		if ((abs(s1-s3)/s1 < 0.00001 && abs(s2-s1)/s1 > 0.00001) && (s2 > s3)) //s2 is the larger
		{
			if ((pow(s1, 2) + pow(s3, 2) )-pow(s2, 2) < 0.00001 && (pow(s1, 2) + pow(s3, 2) )-pow(s2, 2) > -0.00001) // right
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "isosceles right" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}
			else 
			{
				cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "isosceles obtuse" << endl;
				cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
			}		
		}
		else if ((abs(s1-s3)/s1 < 0.00001 && abs(s2-s1)/s1 > 0.00001) && (s2 < s3))
		{
			cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "isosceles acute" << endl;
			cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
		}
	}
	
	else if ((abs(s1-s2))/s2 < 0.00001 &&  (abs(s2-s3)/s2 < 0.00001 && (abs(s1-s3)/s1 < 0.00001 )))	//equilateral
	
	{
		cout << "The triangle formed by points ("<<x1<<"," <<y1<<"), ("<< x2 <<","<< y2 <<"), and ("<<x3<< "," <<y3<< ") is: "<< "equilateral acute" << endl;
		cout<<"The area of the triangle formed by points ("<<x1<<","<<y1<<"), ("<<x2<<","<<y2<<"), and ("<<x3<<","<<y3<<") is: "<< a <<endl;
		
	}
	return rc;
}
