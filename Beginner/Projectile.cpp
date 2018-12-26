#include <math.h> // NAN and sin/cos

float projectileDestination(const float initialHeight, const float initialVelocity, const float mass, const float initialAngle)
{
	float initialAngRad = initialAngle * (3.1415926/180);
	float vy = initialVelocity * sin (initialAngRad); // initial velocity in the y
	float vx = initialVelocity * cos(initialAngRad); // initial velocity in the x
	float t = 0; // time
	float g = 9.8;
	
	if (initialHeight <= 0){
		
		return NAN;
	}
	if (initialVelocity<=0){
		
		return NAN;
	}
	if (mass <=0){
		return NAN;
	}
	if (initialAngle <= -90 || initialAngle>= 90){
		return NAN;
	}
	
	t = (vy + sqrt(pow(vy,2.0) - 2*g*(-1)*initialHeight))/g;
	
	if(t == NAN || t <= 0){
		
		t = (vy - sqrt(pow(vy,2.0) - 2*g*(-1)*initialHeight))/g;
		
		if (t == NAN || t <= 0){
			return NAN;
		}
	}
	
	float d = vx*t; 
	
	
	return d; // Must return value of distance away from building
}

/*#ifndef MARMOSET_TESTING



#include <cstdlib>  // atof
#include <iostream> // cout, endl


using namespace std;

int main(const int argc, const char* const argv[])
{ 
	if (argc < 4)    // incorrect number of arguments
		return -1;
 
 
	float height = atof(argv[1]); // atof = string to float
	float velocity = atof(argv[2]);
	float masss = atof (argv[3]);
	float angle = atof (argv[4]);
	
	
	float projectile = projectileDestination(height, velocity, masss, angle);
	if (projectile == -1){
		cerr << "Error: Unable to compute projectile because invalid input" << endl;
	}
	if (projectile > -1){
		cout <<"The projectile lands " << projectile << " m away." << endl; 
	}
	return 0;
}

#endif*/
