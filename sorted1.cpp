#include <iostream>

using namespace std;

//FIX THE CHECKING OF LENGTH OF STRING

int allLowerCase(const char str1[], const char str2[]){
	int notDone = 1;
	int i = 0;
	int fN = 0;
	while (notDone){ // for both same type of letter
    	if (str1[i] == '\0' || str2[i] == '\0') {
          notDone = 0;
      	} 
     	if (str1[i]<str2[i]){
        	fN = -1;
      	} 
      	if (str1[i]>str2[i]){
        	fN = 1;
     	} 
      	i++;
	}
	return fN;
}

int capitalCase(const char str1[], const char str2[]){
	int notDone = 1;
	int i = 0;
	int fN = 0;
	while(notDone){
		if (str1[i] == '\0' && str2[i] == '\0') {
          notDone = 0;
      	} if (str1[i]-32 < str2[i]){
      		fN = -1; 
      	} if (str1[i] < str2[i]){
      		fN = -1;
      	} if (str1[i]>str2[i]-32){
        	fN = 1;
      	} if (str1[i]>str2[i]){
        	fN = 1;
     	} if (str1[i] == str2[i]-32){
     		fN = 1;
      	} if(str1[i]-32 == str2[i]){
      		fN = -1;
      } 
      i++;
	}
	return fN;
}

int lowCheck(const char str[]){
	int i = 0;
	int lowCount = 0;
	while (str[i] != '\0'){
		if(str[i] >= 'a' && str[i] <= 'z'){
			lowCount++;
		}
		i++;
	}
	return lowCount;
}

int LengthCheck (const char str[]){
  int length = 0;
  int j = 0;
  while (str[j] != '\0'){
      length++;
      j++;
  }
  return length;
}

int capCheck(const char str[]){
	int i = 0;
	int CaLCount = 0;
	while (str[i] != '\0'){
		if((int)str[i] >= 65 && (int) str[i] <= 90){
			CaLCount++;
		}
		i++;
	}
	return CaLCount;
}

int compare(const char str1[], const char str2[]){
	int leng1 = LengthCheck(str1);
	int leng2 = LengthCheck(str2);
	int numLC1 = lowCheck(str1);
	int numLC2 = lowCheck(str2);
	
	if (leng1 == numLC1 && leng2 == numLC2){
		return allLowerCase(str1, str2);
	}

	else {
		int numC1 = capCheck(str1);
		int numC2 = capCheck(str2);
		if(numC1+numLC1 == leng1 && numC2+numLC2 == leng2){
			return capitalCase(str1,str2);
		}

		
	}

	return -66;
}


int main() {
  const char* str1[1] = {"chretien"};
  const char* str2[1] = {"LA"};
  
  //const char* const x = getNextName(names);
  //const char* const y = getNextName(names);
  int y = lowCheck(str2[0]);
  int x = capCheck (str2[0]);
  int t = compare (str1[0],str2[0]);
  //int k = Symbols(str1[0]);
  cout << t << endl;

  return 0;
}