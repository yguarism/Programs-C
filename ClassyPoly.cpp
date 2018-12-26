#include <iostream>
#include <math.h>
#include "ClassyPoly.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////
//
// Public operators and methods

Polynomial Polynomial::dx() const {
	return Polynomial::derivative();
}

float Polynomial::operator()(const float x) const {
	return Polynomial::evaluate(x);
}

Polynomial Polynomial::operator+(const Polynomial& p) const {
	return Polynomial::add(p);
}

Polynomial Polynomial::operator*(const Polynomial& p) const {
	if (_degree < 0 || p._degree < 0){
		float temp[1] = {0}; 
		int deg = -1;
		Polynomial pMult(deg, temp); // ME CALLING THE CONSTRUCTOR TO BUILD ANOTHER POLYNOMIAL 
		return pMult;
	}

	int deg = _degree + p._degree;
	float temp[deg+1];
	

	for(int i = 0; i <= deg; i++){
		temp[i] = 0;
	}
	
	if(p._degree == 0 && _degree != 0){
		for(int i = 0; i < p._coeff[0]; i++){
			for(int i=0; i<= deg; i++){
				temp[i]+=_coeff[i];
			}
		}
		Polynomial pMult (deg, temp);
		return pMult;
	}
	if(_degree == 0 && p._degree != 0){
		for(int i = 0; i < _coeff[0]; i++){
			for(int i=0; i<= deg; i++){
				temp[i]+= p._coeff[i];
			}
		}
		Polynomial pMult (deg, temp);
		return pMult;
	}


	for(int i=0; i<= _degree;++i){
		for(int j=0; j<= p._degree;++j){
			temp[i+j] += _coeff[i]*p._coeff[j];
		}
	}

	Polynomial pMult(deg, temp); // ME CALLING THE CONSTRUCTOR TO BUILD ANOTHER POLYNOMIAL 
	return pMult;
}

void Polynomial::operator=(const Polynomial& p) {
	_degree = p._degree;
	delete[] _coeff;
	
	_coeff = new float[_degree+1];

	for(int i=0; i< _degree;++i){
		_coeff[i] = p._coeff[i];
	}
}

bool Polynomial::operator==(const Polynomial& p) const {
	
	if (p._degree < 0 || _degree < 0){
		return false;
	} 
	if(_degree != p._degree){
		return false;
	}
	else{
		for(int i=0; i< _degree;++i){
			if(fabs(_coeff[i]-p._coeff[i])>pow(10,-5)){
				return false;
			}
		}
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////
//
// Constructors and Destructor
//
// Note: no default constructor
//

Polynomial::Polynomial(const Polynomial& p) {
	if (p._degree < 0){
		_coeff = new float[1];
		_coeff[0]=0; 
		_degree = -1;
		return;
	} 
	_degree = p._degree;
	_coeff = new float[_degree+1];

	for (int i = 0; i<= _degree;i++){
		_coeff[i] = p._coeff[i];
	}
}

Polynomial::Polynomial(const int degree, const float coeff[]) {
	if (degree < 0){
		_coeff = new float[1];
		_coeff[0]=0; 
		_degree = -1;
		return;
	} 
	_degree = degree;
	_coeff = new float[_degree+1];

	for (int i = 0; i<= degree;i++){
		_coeff[i] = coeff[i];
	}
}

Polynomial::~Polynomial() {
	
	for (int i = 0; i <= _degree;i++){
		_coeff[i] = 0;
	}
	
	delete [] _coeff;
	_degree = 0;
}

///////////////////////////////////////////////////////////////////////////
//
// Private Methods
//

float Polynomial::evaluate(const float x) const {
	if (_degree < 0)
		return NAN;

	int i = 1;
	float num = _coeff[0];
	while (i <= _degree){
		num = num*x + _coeff[i];
		i++;
	}
	return num; 
}

Polynomial Polynomial::add(const Polynomial& pIn) const {
	int i = 0;
	int diff=0;
	int deg = 0;
	if (_degree < 0 || pIn._degree < 0){
		float temp[]={0}; 
		deg = -1;
		Polynomial pAdd(deg, temp); // ME CALLING THE CONSTRUCTOR TO BUILD ANOTHER POLYNOMIAL 
		return pAdd;
	} 
	
	if (_degree == pIn._degree){
		float temp [_degree+1];
		deg = _degree;
		while (i <= _degree){
			temp[i] = _coeff[i] + pIn._coeff[i];
			i++;
		}
		Polynomial pAdd(deg,temp);
		return pAdd;
	}
	if (_degree > pIn._degree){
		float temp [_degree+1];
		deg = _degree;
		i = 0;
		diff = _degree - pIn._degree;
		while (i < diff){
			temp[i] = _coeff[i];
			i++;
		}
		while (i <= _degree){
			temp[i] = _coeff[i] + pIn._coeff[i-diff];
			i++;
		}
		Polynomial pAdd(deg,temp);
		return pAdd;
	}
	if (pIn._degree > _degree){
		float temp[_degree+1];
		deg = pIn._degree;
		i = 0;
		diff = pIn._degree - _degree;
		while (i < diff){
			temp[i] = pIn._coeff[i];
			i++;
		}
		while (i <= pIn._degree){
			temp[i] = pIn._coeff[i] + _coeff[i-diff];
			i++;
		}
		Polynomial pAdd(deg,temp);
		return pAdd;
	}
	float temp[]={0}; 
	deg = -1;
	Polynomial pAdd(deg, temp);
	return pAdd;
}

Polynomial Polynomial::derivative() const {
	int i = 0;
	int deg = 0;

	if (_degree < 0){
		float temp[]={0}; 
		deg = -1;
		Polynomial pDer(deg, temp);
		return pDer;
	}

	if(_degree == 0){
		float temp [deg+1];
		deg = 0;
		Polynomial pDer(deg,temp);
		return pDer;
	}
	deg = _degree -1;
	float temp[deg];
	i = 0;
	while (i <= _degree){
		temp[i] = _coeff[i]*(_degree-i);
		i++;
	}
	Polynomial pDer(deg,temp);
	return pDer;
}


///////////////////////////////////////////////////////////////////////////
//
// Test driver
// Some very limited testing; should test ==
// 

#ifndef MARMOSET_TESTING

int main() {
	float coeff[] = {1,-3};
	float coeff1[] = {1,-3};
	float coeff2[] = {2};
	Polynomial p0(1,coeff);
	Polynomial p1(1,coeff1);
	Polynomial p2(0,coeff2);
	//Polynomial p2(3,coeff);
	cout << "When x = 2, \"" << p0 << "\" evalates to: " << p0(2) << endl << endl;
	cout << "When x = 2.2, \"" << p1 << "\" evalates to: " << p1(2.2) << endl << endl;
	//cout << "When x = 2.2, \"" << p2 << "\" evalates to: " << p2(2.2) << endl << endl;
	Polynomial p = p1 + p0;
	Polynomial q = p1 * p2;
	cout << p1<< " and " << p0 << endl;											
	cout << "p1 + p0 =  " << p << endl << endl;
	cout << "p1 * p0 =  " << q << endl << endl;
	cout << "dp/dx =  " << p.dx() << endl;
	cout << "dq/dx =  " << q.dx() << endl;
	return 0;
}

#endif


