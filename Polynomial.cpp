#include <iostream>
#include <math.h>

using namespace std;

// The polynomial struct keeps the most significant coeff
// in the first coeff[] element, the second in the second
// and so on.

struct Polynomial {
  int degree;
  float* coeff;
};

float evaluate(const Polynomial p, const float x) {
  //(x) =A0+x(A1+x(A2+. . . x(An−2+x(An−1+xAn)). . .))
  if (p.degree < 0)
    return NAN;
  int i = 0;
  float num = 0;
  
  while (i <= p.degree){
    num = num*x + p.coeff[i];
    i++;
  }
  return num; 
}


Polynomial add(const Polynomial p1, const Polynomial p2) {
  // Add coefficients (A01+A02)
  Polynomial pAdd;
  int i = 0;
  int diff = 0;

  if (p1.degree <= 0 && p2.degree <= 0){
    pAdd.degree = -1;
    pAdd.coeff = new float[0];
    return pAdd;
  } 
  //BOTH SAME
  if (p1.degree == p2.degree){
    pAdd.coeff = new float[p1.degree+1];
    pAdd.degree = p1.degree;
    while (i <= p1.degree){
      pAdd.coeff[i] = p1.coeff[i] + p2.coeff[i];
      i++;
      }
    }
  if (p1.degree > p2.degree){
    pAdd.coeff = new float[p1.degree+1];
    pAdd.degree = p1.degree;
    i = 0;
    diff = p1.degree - p2.degree;
    while (i < diff){
      pAdd.coeff[i] = p1.coeff[i];
      i++;
    }
    while (i <= p1.degree){
      pAdd.coeff[i] = p1.coeff[i] + p2.coeff[i-diff];
      i++;
    }
  }
  if (p2.degree > p1.degree){
    pAdd.coeff = new float[p2.degree+1];
    pAdd.degree = p2.degree;
    i = 0;
    diff = p2.degree - p1.degree;
    while (i < diff){
      pAdd.coeff[i] = p2.coeff[i];
      i++;
    }
    while (i <= p2.degree){
      pAdd.coeff[i] = p2.coeff[i] + p1.coeff[i-diff];
      i++;
    }
  }
  return pAdd;
}

Polynomial derivative(const Polynomial pIn) {
  Polynomial pDer;
  if (pIn.degree < 0){
    pDer.degree = -1;
    pDer.coeff = new float[0];
    return pDer;
  }
  if(pIn.degree == 0){
    pDer.degree = 0;
    pDer.coeff = new float[1];
    pDer.coeff[0] = 0;
    return pDer;
  }

  pDer.degree = pIn.degree -1;
  pDer.coeff = new float[pIn.degree];
  int i = 0;

  while (i <= pIn.degree){
    pDer.coeff[i] = pIn.coeff[i]*(pIn.degree-i);
    i++;
  }
  return pDer;
}

int displayPolynomial(const Polynomial p) {
  if (p.degree < 0) {
    cerr << "Parameter p is not a polynomial; p.degree = " << p.degree << endl;
    return -1;
  }
  cout << "\"";
  for (int i = 0; i < p.degree; ++i) {
    if (p.coeff[i] == 1) 
      cout << "x";
    else
      cout << p.coeff[i] << "x";
    if ((p.degree - i) > 1) 
      cout <<  "^" <<  (p.degree - i);
    cout << " + ";
  }
  cout << p.coeff[p.degree] << "\"";
  return 0;
  }

#ifndef MARMOSET_TESTING

int main() {
  float coeff[] = {1, 2, 3};   // x^2 + 2x + 3

  //and so on...

  int degree = 2;
  Polynomial p0;
  Polynomial p1;
  Polynomial p2;
  
  p0.degree = 0;
  p0.coeff = coeff;
  p1.degree = 1;
  p1.coeff = coeff;
  p2.degree = 2;
  p2.coeff = coeff;

  cout << "When x = 2.2, ";
  displayPolynomial(p0);
  cout << " evalates to: " << evaluate(p0,2.2) << endl << endl;

  cout << "When x = 2.2, ";
  displayPolynomial(p1);
  cout << " evalates to: " << evaluate(p1,2.2) << endl << endl;

  cout << "When x = 2.2, ";
  displayPolynomial(p2);
  cout << " evalates to: " << evaluate(p2,2.2) << endl << endl;


  Polynomial p = add(p0,p1);
  cout << "p1 + p2 =  ";
  displayPolynomial(p);
  cout << endl;
 
  Polynomial pDer = derivative(p);
  cout << "dp/dx =  ";
  displayPolynomial(pDer);
  cout << endl;
 
  return 0;
}

#endif
