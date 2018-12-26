#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <math.h>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//
// Function declarations
//

float helocFinalBalance(const int lineOfCreditMaximum, const float interestRate, const int initialBalance, const int numberOfYears, const int payments[]);
	
	
float totalInterestPaid(const int lineOfCreditMaximum, const float interestRate, const int initialBalance, const int numberOfYears, const int payments[]);
	

#ifndef MARMOSET_TESTING

////////////////////////////////////////////////////////////////////////////////
//
// Test driver
// Command line arguments (Inputs):
// argv[1]: line of credit maximum
// argv[2]: nominal annual interest rate
// argv[3]: initial balance
// argv[4]: number of year the LOC agreement lasts
// argv[5] - argv[5+argv[3]*12-1]: payments
//

// Support functions

const int FIXED_PARMS = 4;

const int ERROR_INSUFFICIENT_FIXED_PARMS = -1;
const int ERROR_TOO_FEW_YEARS = -2;

const int CMD_ARG_MAXIMUM = 1;
const int CMD_ARG_INTEREST = 2;
const int CMD_ARG_INITIAL = 3;
const int CMD_ARG_YEARS = 4;

int processInputs(const int argc, const char* const argv[],
                  int&   lineOfCreditMaximum,
                  float& interestRate,
                  int&   initialBalance,
                  int&   numberOfYears,
                  int*&  payments) {
  int rc = 0;
  
  // Initial argc test
  if (argc < (FIXED_PARMS + 1))
    return ERROR_INSUFFICIENT_FIXED_PARMS;
  
  lineOfCreditMaximum = atoi(argv[CMD_ARG_MAXIMUM]);
  interestRate = atof(argv[CMD_ARG_INTEREST]);
  initialBalance = atoi(argv[CMD_ARG_INITIAL]);
  numberOfYears = atoi(argv[CMD_ARG_YEARS]);

  if (numberOfYears < 1)
    return ERROR_TOO_FEW_YEARS;
  
  // Based on number of years, argc should be 3 + numberOfYears * 12
  if (argc < (FIXED_PARMS + numberOfYears * 12))
    return -argc;
  if (argc > (FIXED_PARMS + numberOfYears * 12))
    rc = argc - (1 + FIXED_PARMS + numberOfYears * 12);

  payments = new int[numberOfYears*12];
  
  int i = 0;
  while (i < numberOfYears*12) {
    payments[i] = atoi(argv[i+1+FIXED_PARMS]);
    ++i;
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
//
// Driver main():
//   read command line inputs
//   call functions and output results accordingly
// Example usage:
//
// bash-3.2$ ./lineOfCredit 1200 10.0 1200 1 100 100 0 0 0 0 0 0 0 0 0 0
// ./lineOfCredit 1200 10.0 1200 1 100 100 0 0 0 0 0 0 0 0 0 0
// Initial Balance: $1200
// Interest Rate: 10.00%
// Contract Length: 1 years
// Final Outstanding Balance: $1107.44
// Total Interest Paid: $107.44
//

int main(const int argc, const char* const argv[]) {
  int rc = 0;

  int   maximum;           // Maximum amount on the line-of-credit mortgage before 1% per month penalty
  float interestRate;      // Nominal annual interest rate for the LoC
  int   initialBalance;    // Initial balance (should be less than the maximum)
  int   numberOfYears;     // Number of years that the interest rate is fixed
  int*  payments;          // Payments made each month over those years

  rc = processInputs(argc, argv, maximum, interestRate, initialBalance, numberOfYears, payments);
  if (rc < 0) {
    cerr << "Usage error: " << argv[0] << " <initial balance> <interest rate> <number of years> < ... payments (12 per year ...>" << endl;
    return rc;
  }
  else if (rc > 0) {
    cerr << "Usage warning: " << argv[0] << " <initial balance> <interest rate> <number of years> < ... payments (12 per year ...>" << endl
         << "Received " << rc << " extraneous command-line arguments" << endl;
  }

  float outstandingBalance = helocFinalBalance(maximum, interestRate, initialBalance, numberOfYears, payments);
  float interestPaid = totalInterestPaid(maximum, interestRate, initialBalance, numberOfYears, payments);

  cout << setprecision(2) << fixed;
  
  cout << "Initial Balance: $" << initialBalance << endl
       << "Interest Rate: " << interestRate << "%" << endl
       << "Contract Length: " << numberOfYears << " years" << endl
       << "Final Outstanding Balance: $" << outstandingBalance << endl
       << "Total Interest Paid: $" << interestPaid << endl;
  
  return rc;
}

#endif

////////////////////////////////////////////////////////////////////////////////
//
// Your solution here ....
//

/*float helocFinalBalance(const int lineOfCreditMaximum, const float interestRate, const int initialBalance, const int numberOfYears, const int payments[]) {
	
	float amountOwing = initialBalance; // How much I owe
	float monthlyInterestRate = (interestRate/12.0)/100.0; //Calculate monthly interest rate
	int numOfMonths = numberOfYears*12;
	int i = 0; // COUNTER
		
	if (numberOfYears <= 0) 
		return NAN;
	if (interestRate < 0)
		return NAN;
	if (lineOfCreditMaximum <= 0)
		return NAN;
	if (initialBalance > lineOfCreditMaximum)
		return NAN;
		
	while (i < numOfMonths){
			
		if (payments [i] < 0)
			return NAN;
			
		if (amountOwing <= 0){
			amountOwing = amountOwing - payments[i];	
		}
			
		if (amountOwing > 0) {
				
			amountOwing = amountOwing + (amountOwing* monthlyInterestRate) - payments[i];	
				
			if (amountOwing > lineOfCreditMaximum){
				amountOwing = amountOwing + amountOwing*0.01;
				}
			}
		i++;
	}
		
	return amountOwing;
}

float totalInterestPaid(const int lineOfCreditMaximum, const float interestRate,
                        const int initialBalance, const int numberOfYears,
                        const int payments[]) {
	int i = 0; //COUNTER
	float amountOwing = initialBalance;
	float monthlyInterestRate = (interestRate/12.0)/100.0; //Calculate monthly interest rate
	int numOfMonths = numberOfYears*12;
	float totalInterest = 0;
	
	if (numberOfYears <= 0) 
		return NAN;
	if (interestRate < 0)
		return NAN;
	if (lineOfCreditMaximum <= 0)
		return NAN;
	if(initialBalance > lineOfCreditMaximum)
		return NAN;
	
	while (i < numOfMonths){
			
		if (payments [i] < 0)
			return NAN;
		
		if (amountOwing <= 0){
			amountOwing = amountOwing - payments[i];	
		}
			
		if (amountOwing > 0) {
			totalInterest = totalInterest + (amountOwing*monthlyInterestRate);
			amountOwing = amountOwing + amountOwing* monthlyInterestRate - payments[i];	
	
			if (amountOwing > lineOfCreditMaximum){
				amountOwing = amountOwing + amountOwing*0.01;
				totalInterest = totalInterest + (amountOwing*0.01);
			}
			
		}
			
		i++;
	}	
		
	return totalInterest;
}*/

float helocFinalBalance(const int lineOfCreditMaximum,
  const float interestRate,
    const int initialBalance,
      const int numberOfYears,
        const int payments[]) {

  float amountOwing = initialBalance; // How much I owe
  float monthlyInterestRate = (interestRate / 12.0) / 100.0; //Calculate monthly interest rate
  int numOfMonths = numberOfYears * 12;
  int i = 0; // COUNTER

  if (numberOfYears <= 0)
    return NAN;
  if (interestRate < 0)
    return NAN;
  if (lineOfCreditMaximum <= 0)
    return NAN;
  if (initialBalance > lineOfCreditMaximum)
    return NAN;

  while (i < numOfMonths) {

    if (payments[i] < 0)
      return NAN;

    if (amountOwing <= 0) {
      amountOwing = amountOwing - payments[i];
    }

    if (amountOwing > 0) {

      amountOwing = amountOwing + (amountOwing * monthlyInterestRate) - payments[i];

      if (amountOwing > lineOfCreditMaximum) {
        amountOwing = amountOwing + amountOwing * 0.01;
      }
    }
    i++;
  }

  return amountOwing;
}

float totalInterestPaid(const int lineOfCreditMaximum,
  const float interestRate,
    const int initialBalance,
      const int numberOfYears,
        const int payments[]) {
  int i = 0; //COUNTER
  float amountOwing = initialBalance;
  float monthlyInterestRate = (interestRate / 12.0) / 100.0; //Calculate monthly interest rate
  int numOfMonths = numberOfYears * 12;
  float totalInterest = 0;

  if (numberOfYears <= 0)
    return NAN;
  if (interestRate < 0)
    return NAN;
  if (lineOfCreditMaximum <= 0)
    return NAN;
  if (initialBalance > lineOfCreditMaximum)
    return NAN;

  while (i < numOfMonths) {

    if (payments[i] < 0)
      return NAN;

    if (amountOwing <= 0) {
      amountOwing = amountOwing - payments[i];
    }

    if (amountOwing > 0) {
      totalInterest = totalInterest + (amountOwing * monthlyInterestRate);
      amountOwing = amountOwing + amountOwing * monthlyInterestRate - payments[i];

      if (amountOwing > lineOfCreditMaximum) {
        totalInterest = totalInterest + (amountOwing * 0.01);
        amountOwing = amountOwing + amountOwing * 0.01;
      }

    }

    i++;
  }

  return totalInterest;
}
