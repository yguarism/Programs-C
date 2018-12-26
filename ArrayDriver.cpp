#include <iostream>
#include "SafeArray.h"

using namespace std;

int main() {
  float data[] = {1,2,3,4,5};
  SafeArray data1;
  SafeArray data2(5);
  SafeArray data3(5,1.3);
  SafeArray data4(5,data);

  cout << "data1: " << data1 << endl;
  cout << "data2: " << data2 << endl;
  cout << "data3: " << data3 << endl;
  cout << "data4: " << data4 << endl;

  SafeArray data5(data3);
  cout << "data5: " << data5 << endl;
  data5(3) = 4.6;
  cout << "data5: " << data5 << endl;
  data5(6) = 7.2;
  cout << "data5: " << data5 << endl;
  float x = data5(6);
  cout << "x: " << x << endl;
}
