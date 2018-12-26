#include <math.h> // NAN and sin/cos

float projectileDestinationWithDrag(const float initialHeight, const float initialVelocity, const float mass, const float initialAngle, const float k, const float deltaT)
{
	float initialAngRad = initialAngle * (3.1415926/180);
	float vy = initialVelocity * sin (initialAngRad); // initial velocity in the y
	float vx = initialVelocity * cos(initialAngRad); // initial velocity in the x
	float v = initialVelocity; 
	float g = -9.8; //Gravity
	float ay = g + (-k * vy * v)/mass;
	float ax = (-k * vx * v)/mass; //has to be negative to oppose movement
	float dx = 0;
	float dy = initialHeight;
	float dxt = 0; //position x at deltaT
	float dyt = 0; //position y at deltaT
	float vxt = 0; //velocity x at delta T
	float vyt = 0; //velocity y at deltaT
	
	
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
	if(k < 0)
		return NAN;
	if(deltaT <= 0)	{
		return NAN;
	}
	
	else{
		
		while (dy > 0){
		
			dxt = dx + vx*deltaT+ 0.5*ax*pow(deltaT,2.0);
			dyt = dy + vy*deltaT+ 0.5*ay*pow(deltaT, 2.0);
		
			dy = dyt;
			dx = dxt;
			
			vxt = vx + ax*deltaT;
			vyt = vy + ay*deltaT;
		
			vy = vyt;
			vx = vxt;
			
			v = sqrt(pow(vy, 2.0) + pow(vx, 2.0));
			
			ay = g + (-k * vy * v)/mass;
			ax = (-k * vx * v)/mass;
			
		}
	}
	
	
	/*t = (vy + sqrt(pow(vy,2.0) - 2*g*(-1)*initialHeight))/g;
	
	if(t == NAN || t <= 0){
		
		t = (vy - sqrt(pow(vy,2.0) - 2*g*(-1)*initialHeight))/g;
		
		if (t == NAN || t <= 0){
			return NAN;
		}
	}*/
	 
	
	
	return dx; // Must return value of distance away from building
}

#ifndef MARMOSET_TESTING



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
	float k = atof (argv[5]);
	float dt = atof (argv[6]);
	
	
	
	float projectile = projectileDestinationWithDrag(height, velocity, masss, angle, k, dt);
	
	cout << projectile << " " << endl;
	
	if (projectile == -1){
		cerr << "Error: Unable to compute projectile because invalid input" << endl;
	}
	if (projectile > -1){
		cout <<"The projectile lands " << projectile << " m away." << endl; 
	}
	return 0;
}

#endif

