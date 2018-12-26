////////////////////////////////////////////////////////////////////////////////
//
// TestCase.h
//
// Defines Class TestCase
// Base test-case class for SafeMatrix Class
// This base class verifies that the following methods work:
// - SafeMatrix()
// - ~SafeMatrix()
// - dimensions()
// - SafeMatrix(const Dimensions& d,initVal)
// - operator() with valid index on RHS
//
// If these methods (appear to) work, then run() will return "true"
// Otherwise it will return false
// If run() returns false, it is expected that the rest of the test-case
// driver will not be executed, and all testing will be terminated at
// that point
// _m is a pointer, not an object, because we want the run() method to be
// able to output messages prior to invoking any SafeMatrix method.
//
// Change history
// 25-Nov-2018; PASW; Initial version
// 30-Nov-2018; PASW; Comment code
//

#ifndef TESTCASE_H
#define TESTCASE_H

#include "SafeMatrix.h"

#define VALIDATE_TESTCASE_NUMBER do {					\
    if (_testcaseNumber >= MAX_TESTCASES) {				\
      std::cerr << "Exceeded Maximum Number of Testcases; fix MAX_TESTCASES in TestCase.h; terminating" << endl; \
      this->terminate();						\
    }									\
  } while (0)


class TestCase {
public:
  virtual bool run();                    // Execute this testcase (should invoke setup(), output(), and cleanup())
  static  void terminate();              // Terminate the driver

  TestCase() : _m(0) {};
protected:
  virtual int  setup();                  // Setup this particular testcase
  virtual void output(const char description[]);
  virtual void cleanup();                // Cleanup this particular testcase

  static const int MAX_TESTCASES = 200;  // Maximum number of testcases
  
  static int  _testcaseNumber;           // One per class, including derived classes
  static int  _numberPassed;             // One per class, including derived classes
  static bool _perTestCaseResults[MAX_TESTCASES];

                                         // Use a pointer so that compilation and initial execution
                                         // is more likely to work, and we can output some messages
  SafeMatrix* _m;                        // Setup uses this to determine that basic functionality works
};


#endif
