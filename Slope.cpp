#include <iostream>                   // cout, cerr, endl
#include <math.h>                     // fabs
#include <stdlib.h>                   // atof

using namespace std;

#define EXPECTED_ARG_COUNT 4          // Two Cartesian points
#define FLOAT_ACCURACY 0.0001         // 0.01% relative accuracy

int main(const int argc, const char* const argv[]) {

  // return code: default 0
  
  int rc = 0;

  // Check argument count:
  
  if (argc < EXPECTED_ARG_COUNT+1) {  // Plus 1 for program name (argv[0])
    cerr << argv[0] << " error: Expected " << EXPECTED_ARG_COUNT << " arguments; received " << argc-1 << "; exiting" << endl;
    return -1;
  }
  if (argc > EXPECTED_ARG_COUNT+1) {
    cerr << argv[0] << " error: Expected " << EXPECTED_ARG_COUNT << " arguments; received " << argc-1 << "; ignoring extraneous arguments" << endl;
    rc = +1;
  }

  // Form the Cartesian points
  
  float x1 = atof(argv[1]);
  float y1 = atof(argv[2]);
  float x2 = atof(argv[3]);
  float y2 = atof(argv[4]);

  // Determine deltaX and deltaY
  
  // deltaX = x2 - x1
  float deltaX = x2 - x1;
  // deltaY = y2 - y1
  float deltaY = y2 - y1;

  // Determine if points are "identical"
  
  if ((fabs(deltaX/x1) < FLOAT_ACCURACY) &&
      (fabs(deltaY/y1) < FLOAT_ACCURACY)) {
    cout << "The points (" << x1 << "," << y1 << ") and (" << x2 << "," << y2 << ") are within " << FLOAT_ACCURACY*100 << "% of each other; no slope computed." << endl;
    return rc;
  }

  // Compute and output slope
  
  float slope = deltaY / deltaX;

  cout << "The slope of the line formed by points (" << x1 << "," << y1 << ") and (" << x2 << "," << y2 << ") is: " << slope << endl;

  return rc;
}
