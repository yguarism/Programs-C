#include <iostream> // cout, endl

using namespace std;
int binarySearchHelper(const int data[],const int numElements, const int numberToFind, int start, int end)
{
	int i = 0;
	if (numElements <= 0)
		return -1;
	if (numberToFind < data[0] || numberToFind > data[numElements-1] )
		return -1;
	if ((end - start) <= 1 && numberToFind != data[start] && numberToFind!= data[end])
		return -1;
	
	else{ 
		 // where numTofind is in the array (index)
		
		int mid = (start+end)/2;
		
		if (numElements > 2 && numElements - start == 2){
			
			mid = numElements -1;
			
		}
		if (numElements == 2){
			if (data[mid] == numberToFind){
				i = mid;
				return i;
			}	
			
			else {
				
				return ++i;
			}
			
		}
		
		if (data[mid] == numberToFind){
			i = mid;
			return i;
		}	
	
		if (data[mid] < numberToFind){
			return binarySearchHelper(data, numElements, numberToFind, mid, end);
		}
		if (data[mid] > numberToFind){
			return binarySearchHelper(data, numElements, numberToFind, start, mid);
		}
	
	}

	return 0;
}

int binarySearch(const int data[],const int numElements,const int numberToFind)
{
	if (numElements <= 0){
		return -1;
	}
	int start = 0;
	int end = numElements-1;
	int loc = binarySearchHelper (data, numElements, numberToFind, start, end);
	
	return loc;
	
}


#ifndef MARMOSET_TESTING

/*
 * Marmoset doesn't see anything in here
 *
 * Use this space to test your code
 */

#include <iostream> // cout, endl
#include <stdlib.h> // srandom(), random()
int main(const int arc, const char* const argv[])
{
	
	int rc = 0;
	int Array[7];
	int finNum = atoi (argv[1]);
	int loc = binarySearch(Array, 4, finNum);
	
	cout << "The location is " << loc << endl;
	
	
	return rc;
}

#endif