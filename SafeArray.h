////////////////////////////////////////////////////////////////////////////////
//
// SafeArray.h
// Defines class SafeArray
// This is an array that
// (a) Does array-bounds checking
// (b) Does deleted-array checking
//
// Change History:
// 21 Nov 2018: Initial Code Created; PASW
//

#ifndef SAFE_ARRAY_H
#define SAFE_ARRAY_H

#include <iostream>

#define NOT_AN_ARRAY  -1
#define ARRAY_DELETED -2

#define isNaN(X) (X != X)

// Reset NaN is neccessary in case someone changed it

#define RESET_NAN do {							\
    if (!isNaN(_nan)) {							\
      errorMsg("Warning: _nan was set to something other than NaN; resetting");	\
      _nan = 0.0/0.0;							\
    }									\
  } while (0)

class SafeArray {
public:
  float& operator()(const int i);                   // index into an array
  void   operator=(const SafeArray& a);             // assignment
  
  SafeArray();                                      // Create a size-0 array
  SafeArray(const SafeArray& a);                    // Copy constructor
  SafeArray(const int size);                        // Create size "size" array
  SafeArray(const int size, const float initVal);   // Create size "size" array initialized to "initVal"
  SafeArray(const int size, const float data[]);    // Create size "size" array with contents "data"
 ~SafeArray();
  
private:
  friend std::ostream& operator<<(std::ostream& os, SafeArray& a);
  void errorMsg(const char msg[]) const;            // Display error message to std::cerr
  
  int    _size;                                // Array size (-2 (or less) means deleted)
  float  _nan = 0.0/0.0;                       // Used for returning a float& when array bounds exceeded
  float* _data;                                // Array data
};


#endif
