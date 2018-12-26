#include <iostream>
#include <stdlib.h>
using namespace std;

void printResults(const float loanAmount, const float payment, const float interestRate, const int numberofMonths){
	cout << "Total amount of loan: $ " << loanAmount << " Repayment amount: $ " << payment << " Interest rate: " << interestRate << " Time to repay loan: " << numberofMonths/12 << " years and " << numberofMonths%12 << " months" << endl;

	return;
}

const int EXPECTED_ARGS=3;

int processInputs(const int argc, const char* const argv[], float& loanAmount, float& payment, float& interestRate){
	if (argc!= EXPECTED_ARGS+1){
		if (argc <= EXPECTED_ARGS){
			return -1;
		}
		else {
			return 1;
		}
	}
		loanAmount = atof(argv[1]);
		payment = atof(argv[2]);
		interestRate = atof(argv[3]);
	
		return 0;
	}

int loan(const float loanAmount, const float payment, const float interestRate){
	float monthlyInterestRate = (interestRate/12.0)/100.0;
	float amountOwing = loanAmount;
	
	//if (loanAmount <= 0 || interestRate < 0 || (payment <= amountOwing*interestRate)) {
		
	
	if (payment <= amountOwing*interestRate)
		return -1;
	
	int number0fMonths = 0;
	while (amountOwing > 0) {
		amountOwing = (amountOwing + amountOwing*monthlyInterestRate) - payment;
		++number0fMonths;
	}
	
	return number0fMonths;
}

int main(const int argc, const char* const argv[]){
	int rc = 0;
	float loanAmount = -1;
	float payment = -1;
	float interestRate = -1;
	
	rc = processInputs(argc, argv, loanAmount, payment, interestRate);
	if (rc < 0) {
		cerr << "Error: BTWH" << endl;
		return rc;
	}
	
	else if (rc > 0) {
		cerr << "Warning: Not so BTWH" << endl;
	}
	
	int number0fMonths = loan(loanAmount, payment, interestRate);
	if (number0fMonths < 0) {
		cerr << "Error: bad parameters" << endl;
		return -1;
	}
	
	printResults(loanAmount, payment, interestRate, number0fMonths);
	
	return rc;
}