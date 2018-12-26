#ifndef CARTESIAN_H
#define CARTESIAN_H

class CartesianPoint {

public:
  // distance between two points
  float distance(CartesianPoint const &p) const;

  // are two points equal within relative precision?
  bool operator==(CartesianPoint const &p) const;
  // assignment operator
  void operator=(CartesianPoint const &p);

  // constructors + destructor
  CartesianPoint(CartesianPoint const &p);
  CartesianPoint(float x, float y);
  ~CartesianPoint();

private:
  // precision to use when comparing
#define COMPARE_DELTA 1e-5

  float m_x;
  float m_y;

  // prints a point in the form (x, y)
  friend std::ostream &operator<<(std::ostream &os, CartesianPoint const &p);
};

#endif /* CARTESIAN_H */
