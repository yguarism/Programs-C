#include <iostream>
#include "SafeMatrix.h"

using namespace std;

int main() {
  SafeMatrix m(3,4,1.2);
  SafeMatrix m1(-1,0);

  cout << "Matrix m:\n" << m << endl;
  cout << "Matrix m1:\n" << m1 << endl;

  float data[] = {1,2,3,4,5};
  SafeMatrix data1;
  SafeMatrix data2(0,1);
  data2.appendRow(1,data);
  data2.appendRow(1,data+1);
  data2.appendRow(1,data+2);
  data2.appendRow(1,data+3);
  SafeMatrix data3(5,4,1.3);
  SafeMatrix data4;
  data4 = data3;
  data4.appendRow(5,data);

  cout << "data1:\n" << data1 << endl;
  cout << "data2:\n" << data2 << endl;
  cout << "data3:\n" << data3 << endl;
  cout << "data4:\n" << data4 << endl;

  SafeMatrix data5(data3);
  cout << "data5:\n" << data5 << endl;
  data5(3,2) = 4.6;
  cout << "data5:\n" << data5 << endl;
  data5(6,2) = 7.2;
  cout << "data5:\n" << data5 << endl;
  float x = data5(2,2);
  cout << "x: " << x << endl;
  x = data5(6,2);
  cout << "x: " << x << endl;

  cout << "data5 * m:\n" << (data5 * m) << endl;
  cout << "data5 * data2:\n" << (data5 * data2) << endl;

  return 0;
}
