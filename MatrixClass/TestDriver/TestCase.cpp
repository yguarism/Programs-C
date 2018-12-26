#include <iostream>
#include <iomanip>
#include "TestCase.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//

int  TestCase::_testcaseNumber = 0;
int  TestCase::_numberPassed = 0;
bool TestCase::_perTestCaseResults[TestCase::MAX_TESTCASES];

////////////////////////////////////////////////////////////////////////////////
//
// setup()
//
// Normally used to set up whatever is necessary for the testcase to run.
// In this base case, there is nothing to do, since the base TestCase
// is simply validating basic methods; if these methods do not work, then
// there is no point in running any of the  rest of the driver.

int TestCase::setup() {
  VALIDATE_TESTCASE_NUMBER;
  if (_testcaseNumber != 0)
    return 1; 
  return 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// Output result from a testcase.
// Output is:
// Test Case <#>: <pass/fail> (<brief test description>)
//

void TestCase::output(const char description[]) {
  cout << "Test Case " << _testcaseNumber << (_perTestCaseResults[_testcaseNumber] ? ": pass (" : ": fail (") << description << ")" << endl;
}

////////////////////////////////////////////////////////////////////////////////
//
// Output result from a testcase.
// Cleanup anything leftover
//

void TestCase::cleanup() {
  if (_perTestCaseResults[_testcaseNumber]) {
      ++_numberPassed;
  }
  ++_testcaseNumber;           // Move on to next testcase
  
  delete _m;
  _m = 0;
}

////////////////////////////////////////////////////////////////////////////////
//
// Run: do whatever the testcase requires.  This base level
// simply creates a default SafeMatrix, determines its dimensions
// and determines if it is NaM.  It then verifies the destructor and
// also the creation of a (0,3) matrix.
// It then cleans up leftovers.
//

bool TestCase::run() {
  const char desc[] = "Very Basic Funcionality";
  if (setup() != 0) {
    _perTestCaseResults[_testcaseNumber] = false;
    cerr << "Attempted to execute base testcase in non-zero testcase number" << endl;
    output(desc);
    cleanup();
    return false;
  }
  else
    cerr << "Starting SafeMatrix TestCase Driver" << endl;

  cerr << "Attempting default constructor" << endl;
  if (!(_m = new SafeMatrix())) {  // Default constructor works ?
    _perTestCaseResults[_testcaseNumber] = false;
    output(desc);
    cleanup();
    return false;
  }
  cerr << "Default constructor executed; confirming dimensions" << endl;
  Dimensions d = _m->dimensions();
  cerr << "Default constructor created matrix with dimensions (" << d.rows << "," << d.cols << ")" << endl;
  cerr << "Attempting destructor" << endl;
  delete _m;
  cerr << "Destructor may have succeeded; attempting to create SafeMatrix(1,3) using Dimensions constructor with initVal" << endl;
  d.rows = 1;
  d.cols = 3;
  float initVal = 3.2;
  if (!(_m = new SafeMatrix(d,initVal))) {  // Constructor(Dimensions) works?
    _perTestCaseResults[_testcaseNumber] = false;
    output(desc);
    cleanup();
    return false;
  }
  cerr << "Constructor may have succeeded; attempting operator(1,1)" << endl;
  if ((*_m)(0,1) != initVal) {
    _perTestCaseResults[_testcaseNumber] = false;
    output(desc);
    cleanup();
    return false;    
  }
  cerr << "Completed very basic SafeMatrix testing; continuing with driver" << endl;
  _perTestCaseResults[_testcaseNumber] = true;
  output(desc);
  cleanup();
  return true;

}  

////////////////////////////////////////////////////////////////////////////////
//
// Terminate
// Output a closing message and exit the driver
//

void TestCase::terminate() {
  // Output a summary of the number of pass/fail
  cerr << "Terminating SafeMatrix TestCase Driver" << endl
       << "Summary of Results:" << endl
       << "- Total Executed:    " << _testcaseNumber << endl
       << "- Passed:            " << _numberPassed << endl
       << "- Failed:            " << (_testcaseNumber - _numberPassed) << endl
       << "- Percentage Passed: " << (100.0*(1.0*_numberPassed)/_testcaseNumber) << endl;
  if (_numberPassed == 0) 
    exit(0);
  exit(1);									    
}
