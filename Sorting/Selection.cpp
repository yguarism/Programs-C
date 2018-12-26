#include <math.h> // NAN and sin/cos
int maxLocation(const int data[], const int numElements)
{
	int maxPlace = 0;
	int maxNum = 0;
	
	if (numElements < 0)
		return -1;
	
	
	for(int i = 0; i < numElements; i++)	{
		if (data[i] > maxNum){
			maxPlace = i;
			maxNum = data[i];
		}
	}
	
	return maxPlace; //RETURNS location of largest element in the array
}

int selectionSort (int data[], const int numElements)
{
	int temp = 0;
	if (numElements == 1 || numElements == 0)
		return 0;
	
	if (numElements < 0)
		return -1;
	
	
	int max = maxLocation(data, numElements);
	temp = data[max];
	data[max] = data[numElements - 1];
	data[numElements - 1] = temp;
	
	selectionSort(data, numElements - 1);

	return -1;
}

#ifndef MARMOSET_TESTING

#include <cstdlib>  // atof
#include <iostream> // cout, endl


using namespace std;

int main(const int argc, const char* const argv[])
{ 
	if (argc < 4)    // incorrect number of arguments
		return -1;
	int d = 0;	
	int sz = argc-1;
	int loc = 0;
	int dataset[sz];

	
	for (int i = 0; i < sz; ++i)   {   // loop over all inputs, store in array
		dataset[i] = atoi(argv[i + 1]);
	}
	
	loc = maxLocation(dataset, sz);
	d = selectionSort(dataset, sz);
	cout<< loc;
	for(int j = 0; j < sz; j++)	{
		cout<< dataset[j];
	}
	
	

	return 0;
}

#endif