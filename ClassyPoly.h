///////////////////////////////////////////////////////////////////////////
//
// Class: Polynomial
//

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial {
public:
  Polynomial dx() const;                                // Derivative of Polynomial
  
  float operator()(const float x) const;                // Evaluate Polynomial
  Polynomial operator+(const Polynomial& p) const;      // Add 
  Polynomial operator*(const Polynomial& p) const;      // Multiply
  void operator=(const Polynomial& p);                  // Assignment
  bool operator==(const Polynomial& p) const;           // Equality (relative, not exact, since float coeff)
  
  Polynomial(const Polynomial& p);                      // Copy constructor
  Polynomial(const int degree, const float coeff[]);    // Create from an array (coeff from An to A0)
  ~Polynomial();                                        // Destructor: get rid of the coeff array

private:
  // Come from struct and hacked quickly; we don't want to support them, though
  // If you change anything in "private" you will need to submit ClassyPoly.h
  // as well as ClassyPoly.cpp by combining them in a zip file and submitting
  // that
  // Also, if you change the way the data is stored, you will likely want to
  // modify the way the operator<<() function works
  //
  float evaluate(const float x) const;                  // Evaluate Polynomial
  Polynomial add(const Polynomial& p) const;            // Add (from struct)
  Polynomial derivative() const;                        // Derivative (from struct) 

  friend inline std::ostream& operator<<(std::ostream& os, const Polynomial& p);  // Polynomial printing
  
  int    _degree;
  float* _coeff;
};


inline std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
  if (p._degree < 0) {
    std::cerr << "Error: Attempted to output deleted polynomial; exiting";
    exit(-1);
  }
  for (int i = 0; i < p._degree; ++i) {
    if (p._coeff[i] == 1) 
      os << "x";
    else
      os << p._coeff[i] << "x";
    if ((p._degree - i) > 1) 
      os <<  "^" <<  (p._degree - i);
    os << " + ";
  }
  os << p._coeff[p._degree];
  return os;
}

#endif
