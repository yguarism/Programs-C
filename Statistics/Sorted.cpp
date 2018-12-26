#include <iostream>

using namespace std;

//FIX THE CHECKING OF LENGTH OF STRING
/*int allLowerCase(const char str1[], const char str2[]){
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
}*/

/*int capitalCase(const char str1[], const char str2[]){
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
}*/

/*int lowCheck(const char str[]){
  int i = 0;
  int lowCount = 0;
  while (str[i] != '\0'){
    if(str[i] >= 'a' && str[i] <= 'z'){
      lowCount++;
    }
    i++;
  }
  return lowCount;
}*/


/*int compare(const char str1[], const char str2[]){
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
} */

int compare(const char str1[], const char str2[]) {
  
  int i = 0;
  int j = 0;
  char word1 = str1[0];
  char word2 = str2[0];
  int symCount1 = 0;
  int symCount2 = 0;
  int SymbolLoc1 = 0;
  int SymbolLoc2 = 0;
 

  while(word1 != '\0' && word2 != '\0') {

    word1 = str1[i];
    word2 = str2[j];

    if((word1 < 'A' || word1 > 'z') && word1 != '\0' && word1 != ' ' && (int) word1 != 39 && word1 != '-'){
      return -9;
    }
    
    if((word2 < 'A' || word2 > 'z') && word2 != '\0' && word2 != ' ' && (int) word2 != 39 && word2 != '-'){
      return -9;
    }

    if(word1 > 'A' && word1 < 'Z')
      word1 += 32;

    if(word2 > 'A' && word2 < 'Z')
      word2 += 32;

    if(word1 == ' ' || word1 == '-' || (int) word1 == 39)  {
      i++;
      word1 = str1[i];
      symCount1++;
      SymbolLoc1 = i - 1;
    }

    if(word2 == ' ' || word2 == '-' || (int) word2 == 39)  {
      j++;
      word2 = str2[j];
      symCount2++;
      SymbolLoc2 = j - 1;
    }

    if(word1 < word2)
      return -1;

    if(word2 < word1)
      return 1;

    i++;
    j++;
  }
  /*if (leng1 > leng2)
    return -1;
  if (leng2 > leng1)
    return 1;*/

  if(symCount1 && !symCount2)  // DEALING WITH SYMBOLS
    return -1;
  
  if(symCount2 && !symCount1) 
    return 1;

  if(symCount1 && symCount2)  {
  
    if(symCount1 > symCount2)
      return -1;

    else if(symCount2 > symCount1)
      return 1;

    else {
      if(SymbolLoc1 < SymbolLoc2)
        return -1;

      if(SymbolLoc2 < SymbolLoc1)
        return 1;

      if(str1[SymbolLoc1] < str2[SymbolLoc2])
        return -1;
      
      if(str1[SymbolLoc1] > str2[SymbolLoc2])
        return 1;
    }
  }

  i = 0;
  j = 0;
  word1 = str1[i];
  word2 = str2[j];

  while(word1 != '\0' && word2 != '\0'){
    word1 = str1[i];
    word2 = str2[j];

    if(word1 == ' ' || word1 == '-' || (int) word1 == 39)  {
      i++;
      word1 = str1[i];
    }

    if(word2 == ' ' || word2 == '-' || (int) word2 == 39)  {
      j++;
      word2 = str2[j];
    }

    if(word1 > word2)

      return -1;

    if(word2 > word1)
      return 1;

    i++;
    j++;
  }

  return 0;


}




// names["abcd", "ab-cd", "0"]
//State machine to determine if sequence of names is sorted

int isSorted(const char* const names[]) {
  enum sortType {START, UNKNOWN, ASCENDING, DESCENDING, DONE, UNSORTED};

  sortType s = START;
  const char* prev = names[0];
  int i = 1;
  int usortPlace = -1;
  
  if (names[0] == 0)
    return -1;
  
  while (names[i] != NULL) {
    
    const char* const input = names[i];
    // Process transitions
    if (compare(prev, input) == -9)
      return -1;

    switch(s) {
      case START:
        if (input[0] == '\0')
          s = DONE;
        else {
          s = UNKNOWN;
          i--;
        }
        break;

      case UNKNOWN:
        if (input[0] == '\0')
          s = DONE;
        if (compare(prev, input) == -1){
          s = ASCENDING;
        }
            
        if (compare(prev, input) == 1) {
          s = DESCENDING;
        }

        prev = input;
            
        break;

      case ASCENDING:
          
        if (input[0] == '\0'){
          s = DONE;
        }
            
        else if (compare (prev, input) == 1){
          s = UNSORTED;
          usortPlace = i;
        }
          
        prev = input;

        break;

      case DESCENDING:
          
        if (input[0]== '\0') {
          s = DONE;
        }
          
        else if (compare (prev, input) == -1){
          s = UNSORTED;
          usortPlace = i;
        }
          
        prev = input;
        break;

      case DONE:
        return 0;
        break;

      case UNSORTED: 
        return usortPlace + 1;
        break;

      default:
        return -1;
      }

    i++;

  }
  if(s == DONE) 
    return 0;
  if(s == UNSORTED)
    return usortPlace + 1;

  return 0;
}


#ifndef MARMOSET_TESTING

int main() {

  const char* const names[4] = {"Abbott", "abbott", ""};
  //const char* const x = getNextName(names);
  //const char* const y = getNextName(names);
  
  int z = compare (names[0], names[1]);

  //int z = isSorted(names);
  cout << z << endl;
  /*if (z == 1)
    cout << "Name two is first" << endl;
  else if (z == -1)
    cout << "Name one is first" << endl;
  else if (z == 0){
    cout << "The same" << endl;
  }*/

  return 0;
}

#endif
