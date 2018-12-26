int partition(int data[], const int lo, const int hi)
{
	int dataIndex = lo;
	int pivot = data[hi];
	int pivotIndex = lo;
	
	if (hi < 0 || lo < 0){
		return -1;
	}
	if((hi-lo) < 1){
		return -1;
	}
	
	while (dataIndex < hi){
	
		if (data[dataIndex] < pivot){
		
			int temp = data[dataIndex];
			data[dataIndex] = data[pivotIndex];
			data[pivotIndex] = temp;
			pivotIndex++;
		}
	
		dataIndex++; 
	}
	
	int temp = data[hi];
	data[hi] = data[pivotIndex];
	data[pivotIndex] = temp;

  return pivotIndex; 
  }


void quickSortHelper(int data[], const int lo, const int hi)
{
	if((hi-lo) < 1){
		return;
	}
	
	int mid = partition (data, lo, hi);
	quickSortHelper(data, lo, mid-1);
	quickSortHelper(data, mid+1, hi);

}


int quickSort(int data[], const int numElements)
{
	
	if (numElements == 1 || numElements == 0) {
		return 0;
	}
	
	if (numElements < 0){
		return -1;
	}
	
		
	quickSortHelper(data, 0, numElements-1);
  
  return 0;
}


#ifndef MARMOSET_TESTING

/*
 * Marmoset doesn't see anything in here
 *
 * Use this space to test your code
 */

#include <iostream> // cout, endl
#include <stdlib.h> // srandom(), random()

using namespace std;

// print an array in comma separated format
void printArray(const int data[], const int numElements)
{
  int i = 0;
  while (i < numElements-1) {
    cout << data[i] << ", ";
    ++i;
  }
  cout << data[numElements-1] << endl;
}


int main(void)
{
  int sz = 10; // array size

  srandom(0);  // deterministic seed for random()
               // change 0 to a different number to get a different random array 

  int data[sz];
  int i = 0;
  while (i < sz) { // fill array with random values
    data[i] = (int)random();
    ++i;
  }

  cout << "Array is: ";
  printArray(data, sz);

  int ret = quickSort(data, sz); // sort the array

  cout << "After sorting, array is: ";
  printArray(data, sz);

  // check the return code
  if (ret < 0)
    cout << "quickSort() indicated error" << endl;
  else if (ret > 0)
   cout << "quickSort() indicated warning" << endl;

  return 0;
}


#endif