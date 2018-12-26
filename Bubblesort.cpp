#include <iostream>

using namespace std;

int main() {
  int sz = 9;
  int sDA[9] = {5, 1, 0, 3, 2, 14, 101, 37, 3};

  int somethingChanged = 1;

  while (somethingChanged) {
    somethingChanged = 0;
    int i = 0;
    while (i < sz-1) {
      if (sDA[i] > sDA[i+1]) {   // Wrong order, swap them
	int tmp;
	tmp = sDA[i];
	sDA[i] = sDA[i+1];
	sDA[i+1] = tmp;
	somethingChanged = 1;
      }
      ++i;
    }
  }
  int i = 0;
  while (i < sz) {
    cout << i << ": " << sDA[i] << endl;
    ++i;
  }
  return 0;
}
