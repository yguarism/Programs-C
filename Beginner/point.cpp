#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){
	int a = 5;
	//int *r = a;
	int *p = &a;
	int &x = a;
	//int&y = &a;

	cout << "in Order: " << p << " " << " " << *p << " " << x << " " <<&x << endl;

	return 0;
}