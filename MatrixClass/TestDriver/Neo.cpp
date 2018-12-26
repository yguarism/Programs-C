////////////////////////////////////////////////////////////////////////////////
// Yrina Guarisma
// Neo.cpp
// Test Driver for SafeMatrix class
// Inputs:  none
// Outputs: Results of testing SafeMatrix Class, displayed to cout
// Operation: test all methods of SafeMatrix class
//
// Change History
// 26 November 2018; PASW; Initial version: only implements
//                                          (1) basic test setup
//                                          (2) testing of ...
//                                          (3) display of results
//

#include <iostream>
#include "SafeMatrix.h"
#include "TestCase.h"

using namespace std;


////////////////////////////////////////////////////////////////////////////////
//
// Testcases for appendRow()
// Uses class TestCase
//
class TestAppendRow : public TestCase {
public:
  bool testBasicAppend();
  bool testMismatchAppend();
  bool testNaMAppend();

  bool run();
  int  setup() { return 0; } ;

#define NUM_COLS 3
  TestAppendRow() : data1(0,NUM_COLS), data2(-1,0) {};
private:
  SafeMatrix data1;
  SafeMatrix data2;             // Should be NaM
};

bool TestAppendRow::run() {
  setup();
  if (!testBasicAppend() ||
      !testMismatchAppend() ||
      !testNaMAppend()) 
    return false;
  return true;
}

//Tests if append row is attempted to the bottom of the matrix

bool TestAppendRow::testBasicAppend() {
  float data[] = {1.1, 2.2, 3.3};
  bool retVal = false;
  const char desc[] = "Append Row: Basic Append";
  if (!data1.appendRow(NUM_COLS, data) ||
      (data1(0,0) != data[0]) ||
      (data1(0,1) != data[1]) ||
      (data1(0,2) != data[2]))
    retVal = false;
  else
    retVal = true;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}
//Tests if append row is attempted in the matrix

bool TestAppendRow::testMismatchAppend() {
  float data[] = { 1.1, 2.2, 3.3 };
  bool retVal = true;
  const char desc[] = "Append Row: Mismatch Append";
  if (data1.appendRow(NUM_COLS-1, data))
    retVal = false;
  if (((data1.dimensions()).rows != 1) || 
      ((data1.dimensions()).cols != NUM_COLS)) 
    retVal = false;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}

//Tests if append row is attempted with not a matrix
bool TestAppendRow::testNaMAppend() {
  float data1[] = { 1.1, 2.2, 3.3 };
  bool retVal = true;
  const char desc[] = "Append Row: NaM Append";
  if (data2.appendRow(0, data1))
    retVal = false;
  if (!data2.isNaM())
    retVal = false;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}

////////////////////////////////////////////////////////////////////////////////
//
// Testcases for appendColumn
// Uses class TestCase
//
class TestAppendColumn : public TestCase {
public:
  bool testBasicAppend();
  bool testMismatchAppend();
  bool testNaMAppend();

  bool run();
  int  setup() { return 0; } ;

#define NUM_ROWS 3
  TestAppendColumn() : data3(NUM_ROWS,1), data4(-1,0) {};
private:
  SafeMatrix data3;
  SafeMatrix data4;             // Should be NaM
};


bool TestAppendColumn::run() {
  setup();
  if (!testBasicAppend()||!testMismatchAppend()||!testNaMAppend()) 
    return false;
  return true;
}


//Tests if append Column is attempted to the end
bool TestAppendColumn::testBasicAppend() {
  float data[] = {1.1, 2.2, 3.3};
  bool retVal = false;
  const char desc[] = "Append Column: Basic Append";

  if (!data3.appendColumn(NUM_ROWS, data) ||
      (data3(0,1) != data[0]) ||
      (data3(1,1) != data[1]) ||
      (data3(2,1) != data[2])){
    retVal = false;
  }
  else
    retVal = true;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}
//Tests if append column is attempted in the middle of the matrix
bool TestAppendColumn::testMismatchAppend() {
  float data[] = { 1.1, 2.2, 3.3 };
  bool retVal = true;
  const char desc[] = "Append Column: Mismatch Append";
  if (data3.appendColumn(NUM_ROWS-1, data))

    retVal = false;
  if (((data3.dimensions()).cols != 1) || 
      ((data3.dimensions()).rows != NUM_COLS)) 
    retVal = false;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}
//Tests if append column is given an invalid matrix
bool TestAppendColumn::testNaMAppend() {
  float data1[] = { 1.1, 2.2, 3.3 };
  bool retVal = true;
  const char desc[] = "Append Column: NaM Append";
  if (data4.appendColumn(0, data1))
    retVal = false;
  if (!data4.isNaM())
    retVal = false;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}
////////////////////////////////////////////////////////////////////////////////
//
// Testcases for Not-A-Matrix
// Uses class TestCase
//
class TestisNaM : public TestCase {
public:
  bool testBasicisNaM();
  bool testisaM();

  bool run();
  int  setup() { return 0; } ;

#define NUM_ROWS 3
#define NUM_COLS 3
  TestisNaM() : data5(NUM_ROWS,NUM_COLS), data6(-1,0) {};
private:
  SafeMatrix data5;
  SafeMatrix data6;             // Should be NaM
};

bool TestisNaM::run() {
  setup();
  if (!testBasicisNaM()||!testisaM()) 
    return false;
  return true;
}
//test if input is not matrix
bool TestisNaM::testBasicisNaM() {
  bool retVal = false;
  const char desc[] = "isNaM: Basic NaM";
  if (data5.isNaM())
    retVal = false;
  else
    retVal = true;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}
//Tests if input is a matrix
bool TestisNaM::testisaM() {
  bool retVal = false;
  const char desc[] = "isNaM: Basic aM";
  if (!data6.isNaM())
    retVal = false;
  else
    retVal = true;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}

////////////////////////////////////////////////////////////////////////////////
//
// Testcases for OperatorEquals
// Uses class TestCase
//
class testOperatorEquals : public TestCase {
public:
  bool testOperatorEqualsBasic();
  bool testOperatorEqualsNot();
  bool testOperatorEqualsInvalid();

  bool run();
  int  setup() { return 0; } ;

#define NUM_ROWS 3
#define NUM_COLS 3
#define CONSTANT 2.3
#define CONSTANT1 3.2
  testOperatorEquals() : data5(NUM_ROWS,NUM_COLS,CONSTANT), data6(-1,-1), data7(NUM_ROWS, NUM_COLS, CONSTANT1), data8(NUM_ROWS, NUM_COLS, CONSTANT){};
private:
  SafeMatrix data5;              //ORIGINAL
  SafeMatrix data6;             // Should be NaM
  SafeMatrix data8;             //Equal to Original
  SafeMatrix data7;             //not equal to original
};

bool testOperatorEquals::run() {
  setup();
  if (!testOperatorEqualsBasic() ||
      !testOperatorEqualsNot() ||
      !testOperatorEqualsInvalid()) 
    return false;
  return true;
}
//Tests if operator equals returns false if the two matrices are equal
bool testOperatorEquals::testOperatorEqualsBasic() {
  bool retVal = false;
  const char desc[] = "testOperatorEquals: Equals Basic";
  if (!(data5 == data8))
    retVal = false;
  else
    retVal = true;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}
//Tests if operator equals returns false if two not equal matrices return true
bool testOperatorEquals::testOperatorEqualsNot() {
  bool retVal = false;
  const char desc[] = "testOperatorEquals: Not Equals";
  if (data5 == data7)
    retVal = false;
  else
    retVal = true;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}

//Tests if operator equals returns false if invalid matrix is inputted
bool testOperatorEquals::testOperatorEqualsInvalid() {
  bool retVal = false;
  const char desc[] = "testOperatorEquals: Invalid";
  if ((data8 == data6))
    retVal = false;
  else
    retVal = true;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}
////////////////////////////////////////////////////////////////////////////////
//
// Testcases for OperatorNotEquals
// Uses class TestCase
//
class testOperatorNotEquals : public TestCase {
public:
  bool testOperatorNotEqualsBasic();
  bool testOperatorNotEqualsNot();
  bool testOperatorNotEqualsInvalid();

  bool run();
  int  setup() { return 0; } ;

#define NUM_ROWS 3
#define NUM_COLS 3
#define CONSTANT 2.3
#define CONSTANT1 3.2
  testOperatorNotEquals() : data5(NUM_ROWS,NUM_COLS,CONSTANT), data6(-1,-1), data7(NUM_ROWS, NUM_COLS, CONSTANT1), data8(NUM_ROWS, NUM_COLS, CONSTANT){};
private:
  SafeMatrix data5;              //ORIGINAL
  SafeMatrix data6;             // Should be NaM
  SafeMatrix data8;             //Equal to Original
  SafeMatrix data7;             //not equal to original
};
bool testOperatorNotEquals::run() {
  setup();
  if (!testOperatorNotEqualsBasic() ||
      !testOperatorNotEqualsNot() ||
      !testOperatorNotEqualsInvalid()) 
    return false;
  return true;
}
//Returns false if two matrices that are equal are compared
bool testOperatorNotEquals::testOperatorNotEqualsBasic() {
  bool retVal = false;
  const char desc[] = "testOperatorNotEquals: Not Equals Basic";
  if (data5 != data8)
    retVal = false;
  else
    retVal = true;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}
//Tests if operator not equals returns true if the two matrices are not equals
bool testOperatorNotEquals::testOperatorNotEqualsNot() {
  bool retVal = false;
  const char desc[] = "testOperatorNotEquals: Not Equals Equal";
  if (data5 != data7)
    retVal = true;
  else
    retVal = false;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}
//Tests if operator not equals returns false if invalid matrix is inputted

bool testOperatorNotEquals::testOperatorNotEqualsInvalid() {
  bool retVal = false;
  const char desc[] = "testOperatorNotEquals: Not Equals Invalid";
  if ((data8 != data6))
    retVal = false;
  else
    retVal = true;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}

////////////////////////////////////////////////////////////////////////////////
//
// Testcases for Dimensions
// Uses class TestCase
//

class testDimensions : public TestCase {
public:
  bool testDimValid();
  bool testDimInvalid();

  bool run();
  int  setup() { return 0; } ;

#define NUM_ROWS 3
#define NUM_COLS 3

  testDimensions() : data5(NUM_ROWS,NUM_COLS), data6(-1,-1) {};
private:
  SafeMatrix data5;              //ORIGINAL
  SafeMatrix data6;             // Should be NaM
};

bool testDimensions::run() {
  setup();
  if (!testDimValid() ||
      !testDimInvalid() ) 
    return false;
  return true;
}
//Tests if a valid matrix returns proper dimensions
bool testDimensions::testDimValid(){
  bool retVal = false;
  const char desc[] = "testDimensions: testDimValid";
  Dimensions d5 = data5.dimensions();
  if (d5.rows == NUM_ROWS && d5.cols == NUM_COLS) 
    retVal = true;
  else
    retVal = false;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}
// Tests if an invalid matrix returns proper dimensions
bool testDimensions::testDimInvalid(){
  bool retVal = false;
  const char desc[] = "testDimensions: testDimInvalid";
  Dimensions d6 = data6.dimensions();
  if (d6.rows == NUM_ROWS && d6.cols == NUM_COLS) 
    retVal = false;
  else
    retVal = true;
  _perTestCaseResults[_testcaseNumber] = retVal;
  output(desc);
  cleanup();
  return retVal;
}

////////////////////////////////////////////////////////////////////////////////
//
//

int main() {

  TestCase t0;
  t0.run();

  TestAppendRow t1;
  t1.run();

  TestisNaM t2;
  t2.run(); 

  TestAppendColumn t3;
  t3.run();

  testOperatorEquals t4;
  t4.run();

  testOperatorNotEquals t5;
  t5.run();

  testDimensions t6;
  t6.run();

  t0.terminate();
  
  return 0;
}