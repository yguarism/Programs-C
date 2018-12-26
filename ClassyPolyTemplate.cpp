#include <iostream>
#include <math.h>
#include "ClassyPoly.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////
//
// Public operators and methods


Polynomial Polynomial::dx() const {
}

float Polynomial::operator()(const float x) const {
}

Polynomial Polynomial::operator+(const Polynomial& p) const {
}

Polynomial Polynomial::operator*(const Polynomial& p) const {
}

void Polynomial::operator=(const Polynomial& p) {
}

bool Polynomial::operator==(const Polynomial& p) const {
}

///////////////////////////////////////////////////////////////////////////
//
// Constructors and Destructor
//
// Note: no default constructor
//

Polynomial::Polynomial(const Polynomial& p) {
}

Polynomial::Polynomial(const int degree, const float coeff[]) {
}

Polynomial::~Polynomial() {
}

///////////////////////////////////////////////////////////////////////////
//
// Private Methods
//

float Polynomial::evaluate(const float x) const {
}

Polynomial Polynomial::add(const Polynomial& pIn) const {
}

Polynomial Polynomial::derivative() const {
}


///////////////////////////////////////////////////////////////////////////
//
// Test driver
// Some very limited testing; should test ==
// 

#ifndef MARMOSET_TESTING

int main() {
  float coeff[] = {1, 2, 3, 4};   // x^2 + 2x + 3
  Polynomial p0(1,coeff);
  Polynomial p1(2,coeff);
  Polynomial p2(3,coeff);
  
  cout << "When x = 2.2, \"" << p0 << "\" evalates to: " << p0(2.2) << endl << endl;
  cout << "When x = 2.2, \"" << p1 << "\" evalates to: " << p1(2.2) << endl << endl;
  cout << "When x = 2.2, \"" << p2 << "\" evalates to: " << p2(2.2) << endl << endl;

  Polynomial p = p1 + p2;
  Polynomial q = p1 * p2;											
  cout << "p1 + p2 =  " << p << endl << endl;
  cout << "p1 * p2 =  " << q << endl << endl;
 
  cout << "dp/dx =  " << p.dx() << endl;
  cout << "dq/dx =  " << q.dx() << endl;
 
  return 0;
}

#endif


