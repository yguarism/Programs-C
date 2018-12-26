#include <iostream> // cout, endl
#include <stdlib.h>

using namespace std;

float averageWithoutOutliersHelp (float data[], const int size)
{
	int param = size/3;
	float avg = 0;
	float avgtot = 0;
	int j = 0;
	while (j < param){
		data[j] = 0;
		data[size - 1 - j] = 0;
		j++;
	}
	int k = 0;
	while (k < size-1){
		
		avg = avg + data[k];
		k++;
	}
	avgtot = avg/ (size - (2*j));
	
	return avgtot;
}

float sort (const float data[], const int sz)
{
	int i = 0;
	float dataset[sz];
	while (i < sz){
		dataset[i] = data[i];
		i++;
	}
	int change = 1;
	while (change){
		change = 0;
		int i = 0;
		while (i< sz -1){
			if (dataset[i] < dataset[i+1]){
				int tmp = dataset[i];
				dataset[i] = dataset[i+1];
				dataset[i+1] = tmp;
				change = 1;
			}	
			++i;	
		}
	}
	return averageWithoutOutliersHelp (dataset, sz);
}



float averageWithoutOutliers(const float dataset[], const int size)
{
	
	float avg = sort(dataset, size);
	
	return avg;
}


int main(){
	
	float Ar[7] = {110.223, 0.00, 112.929, 0.00, 111.47, 250941.3, 110.96};
	
	float avg = averageWithoutOutliers(Ar, 7);
	
	cout << "The New Average is " << avg << endl;
	
	return 0;
	
}