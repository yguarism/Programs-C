#include <iostream>
#include <stdlib.h> // srandom(), random()
#include <math.h>

using namespace std;

float stringToFloat(const char input[]) {
    enum State {START, DONE, GOT_DEC, GOT_EXP, GOT_NEG, GOT_DIGIT};
    State s = START;
    
    int i = 0;
    int neg = 0;
    int numDec = 0;
    float decCount = 0;
    float expNum = 0;
    int expSign = 0;
    float num = 0;
    int notDone = 1;

    while (notDone) {
       
        switch(s) {

        case START:
            if (input[i] == '-'){
                s = GOT_NEG;
                neg = 1;
            } else if (input[i] == '+') {
                neg = 0;
                s = GOT_DIGIT;
            } else if (input[i]<= '9' && input[i]>= '0'){
                s = GOT_DIGIT;
                neg = 0;
            } else if (input[i] == '.'){
                s= GOT_DEC;
            } else {
                return NAN;
            } 
            break;

        case GOT_DEC:
            
            if (input[i]<= '9' && input[i] >= '0'){
                s = GOT_DEC;
                decCount++;
                num = num + ((input[i] - '0') * pow(10,((-1)*decCount)));
                i++;
            } else if (input[i] == '.'){
                s= GOT_DEC;
                numDec++;
                i++;
                if (input[i] == '\0'){
                    return NAN;
                }
                if (numDec > 1){
                    return NAN;
                }
            } else if (input[i] == 'e' || input[i] =='E'){
                s = GOT_EXP;
                i++;
            } else if (input[i] == '\0'){
                s= DONE;
            } else {
                return NAN;
            }
            break;

        case GOT_EXP:
            if (input [i] == '-'){
                s = GOT_EXP;
                expSign = 1;
                i++;
            } else if (input[i] == 'e' || input[i] == 'E'){
                s = GOT_EXP;
                i++;
                if (input[i] == '\0'){
                    return NAN;
                }
            } else if (input[i] <= '9' &&  input[i] >= '0') {
                s = GOT_EXP; 
                expNum = (expNum*10) + (input[i]-'0');
                i++;
            } else if (input[i] == '\0'){
                s= DONE;
            } else {
                return NAN;
            }
            break;
        
        case GOT_NEG:
            
            if (input[i] <= '9' && input[i] >= '0'){
                s = GOT_DIGIT;
            } else if (input[i] == '-'){
                s = GOT_NEG;
                i++;
            } else if (input[i] == '\0'){
                s= DONE;
            } else {
                return NAN;
            }
            break;

        case GOT_DIGIT:
            
           if (i == 0 && (input[i] == '+' || input[i] == '-')){
                s = GOT_DIGIT;
                i++; 
            } else if (input[i] <= '9' && input[i] >= '0'){
                s = GOT_DIGIT;
                num = (num*10) + (input[i]-'0');
                i++;
            } else if (input[i]== '.'){
                s = GOT_DEC;
                numDec++;
                i++;
            } else if (input[i] == 'e' || input[i] == 'E'){
                s = GOT_EXP;
            } else if (input[i] == '\0'){
                s= DONE;
            } else {
                return NAN;
            }
            break; 

        case DONE:
            if (neg == 1){
                num = num * -1.0;
            } if (expNum > 0){
                if (expSign > 0){
                    expNum = expNum * -1.0;
                } 
                num = num * pow(10, expNum);
            }
            if (num == -0){
                num = 0;
            }
            notDone = 0;
            break;

        default:
            cerr << "An unknown error occurred." << endl;
            exit(-1);
            break;
        }
    }  

    return num;
}

#ifndef MARMOSET_TESTING
        
int main(){

    float z = stringToFloat("-2e-267");

    cout << z << endl;


    return 0;
}

#endif
