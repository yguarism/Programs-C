////////////////////////////////////////////////////////////////////////////////
//
// Program: BitTwiddle
// Usage: ./bitTwiddle <number> <bitPosition>
// Inputs:
// (1) an unsigned int between 0 and UINT_MAX
// (2) an unsigned int between 0 and sizeof(unsigned int) in bits (a bit position)
// Outputs:
// (1) The number in binary, in groups of 4 for readability
// (2) The value of the bit at the bit position specified by the second input
// (3) The result of inverting the bit at the bit position, in binary and decimal
// (4) The result of setting the bit at the bit position, in binary and decimal
// (5) The result of unsetting the bit at the bit position, in binary and decimal
//
// Change history:
// 28 September 2018; PASW: Initial version
// 29 September 2018; PASW: Added comments, checked values in processInputs()
//                          Added errorMessage() and warningMessage()
//                          Added bitFlip in main(); cleaned up main()
//

#include <iostream>
#include <stdlib.h>

using namespace std;

const int EXPECTED_ARG_COUNT = 3;

////////////////////////////////////////////////////////////////////////////////
//
// processInputs()
// Inputs:
// (1) argc: the number of values in argv[]
// (2) argv[]: the command-line arguments
// Outputs:
// (1) bits: the value of the first input, treated as an unsigned int
// (2) bitPosition: the value of the second input, treated as an unsigned int
//
// Function validates bitPosition and argc
//

int processInputs(const int argc, const char* const argv[],
		  unsigned int& bits, unsigned int& bitPosition) {
  int rc = 0;
  if (argc < EXPECTED_ARG_COUNT)
    return -1;
  if (argc > EXPECTED_ARG_COUNT)
    rc = 1;
  bits = atoi(argv[1]);
  bitPosition = atoi(argv[2]);
  if (bitPosition > (8*sizeof(unsigned) - 1))   // No need to check for < 0
    return -1;
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
//
// errorMessage()
//

void errorMessage(const char* progName) {
  cerr << "Usage Error: " << progName << " <number> <bit position>" << endl
       << "<number> must be between 0 and " << UINT_MAX << endl
       << "<bit position> must be between 0 and " << 8*sizeof(unsigned)-1 << endl;
  return;
}

////////////////////////////////////////////////////////////////////////////////
//
// warningMessage()
//

void warningMessage(const char* progName) {
  cerr << "Usage Warning: Expected: " << progName << " <number> <bit position>" << endl
       << "Extrenaous information was added; it is being ignored" << endl;
  return;
}

////////////////////////////////////////////////////////////////////////////////
//
// displayBits()
// Inputs:
// (1) an unsigned int
// Outputs:
// No return value from function; however, it displays on cout the bits that
// form the input number, in groups of four
//

void displayBits(const unsigned int bits) {
  int i = 8*sizeof(unsigned);
  while (i > 0) {
    --i;          
    cout << ((bits >> i) & 0x01);
    if (i%4 == 0)  
      cout << " ";
  }
  return;
}

////////////////////////////////////////////////////////////////////////////////
//
// Per description above
//

int main(const int argc, const char* const argv[]) {
  int rc = 0;
  unsigned int inputNumber;
  unsigned int bitPosition;
  
  rc = processInputs(argc, argv, inputNumber, bitPosition);
  if (rc < 0) {
    errorMessage(argv[0]);
    return rc;
  }
  if (rc > 0) 
    warningMessage(argv[0]);

  cout << "Input number: " << inputNumber << endl
       << "Input number is binary: ";
  displayBits(inputNumber);
  cout << endl;

  int valueAtPosition = (inputNumber >> bitPosition) & 0x01;
  cout << "Bit position " << bitPosition << " has value " << valueAtPosition << endl;

  unsigned int bitMask = 0x01 << bitPosition;         // bit mask is all zeros except 1 at <bit position>
  
  cout << "Flipping bit at position " << bitPosition << " changes input number to " << (inputNumber ^ bitMask) << endl
       << "Which in binary is: ";
  displayBits(inputNumber ^ bitMask);
  cout << endl;

  cout << "Clearing bit at position " << bitPosition << " changes input number to " << (inputNumber  & (~bitMask)) << endl
       << "Which in binary is: ";
  displayBits(inputNumber & (~bitMask));
  cout << endl;

  cout << "Setting bit at position " << bitPosition << " changes input number to " << (inputNumber | bitMask) << endl
       << "Which in binary is: ";
  displayBits(inputNumber | bitMask);
  cout << endl;
  
  return rc;
}
