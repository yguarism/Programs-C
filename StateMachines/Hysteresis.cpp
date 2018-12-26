#include <iostream>
#include <stdlib.h> // srandom(), random()
#include <math.h>

using namespace std;

int countZerosAndOnes(const int zeroOneData[], const int numSamples,const int kMax, int& zeroCount, int& oneCount) {
    enum State {START, DONE, GOT_ZERO, GOT_ONE, GOT_KTH_ZERO, GOT_KTH_ONE};
    State s = START;
    int i = 0;
    int k = 0;
    if(numSamples<=0 || kMax <0) {
        return -1;
    }
   
    
    while (s != DONE && i<numSamples) {
       
        switch(s) {

        case START: 
            zeroCount= 0;
            oneCount = 1;
            k= 0;
            if (zeroOneData[i] ==0) {
                s = GOT_KTH_ZERO;
                /*i++;
                k++;*/
            } else if(zeroOneData[i] == 1) {
                s = GOT_ONE;
                /*i++;*/
            } else if(zeroOneData[i] != 1 && zeroOneData[i] != 0){
                return -1;
            } else {
                s = DONE;
            }
            break;

        case GOT_KTH_ONE:
            if (zeroOneData[i] == 0) {
                s = GOT_ZERO;
                k=0;
            } else if(zeroOneData[i]  == 1){
                s= GOT_KTH_ONE;
                i++;
                k++;
                if (k>kMax) {
                    s = GOT_ONE;
                    oneCount++;
                    k=0;
                    break;
                }
                
            } else if(i>=numSamples){
                s=DONE;
            } else {
                return -1;
            } 
            break;

        case GOT_KTH_ZERO:
            if (zeroOneData[i]  == 0) {
                s = GOT_KTH_ZERO;
                i++;
                k++; 
                if(k>kMax){
                    s=GOT_ZERO;
                    zeroCount++;
                    k = 0;
                    break;
                }    
            } else if (zeroOneData[i]  == 1) {
                s = GOT_ONE;
                k = 0;
            } else if(i>= numSamples){
                s=DONE;
            } else {
                return -1;
            } 
            break;
        
        case GOT_ZERO:
            if (zeroOneData[i]  == 1) {
                s = GOT_KTH_ONE;
                k=0;
            } else if (zeroOneData[i]  == 0){
                s = GOT_ZERO;
                i++;
                k++;
            } else if (i>=numSamples) {
                s = DONE;
            } else {
                return -1;
            } 
            break;

        case GOT_ONE:
            if (zeroOneData[i]  == 0) {
                s = GOT_KTH_ZERO;
                k = 0;
            } else if(zeroOneData[i]  == 1){
                s = GOT_ONE;
                k++;
                i++;
            } else if (i>= numSamples) {
                s = DONE;
            } else {
                return -1;
            } 
            break;

        case DONE:
            break;

        default:
            cerr << "An unknown error occurred." << endl;
            exit(-1);
            break;
        }
        
       
    }
        
    return 0;
}