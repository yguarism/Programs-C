#include <iostream>
#include <stdlib.h> // srandom(), random()
#include <math.h>

using namespace std;

int countZerosAndOnes(const int zeroOneData[], const int numSamples, int& zeroCount, int& oneCount) {
    enum State {START, DONE, GOT_ZERO, GOT_ONE};
    State s = START;
    int i = 0;
    if(numSamples<=0) {
        return -1;
    }

    while (s != DONE && i<numSamples) {
        float input = zeroOneData[i];

        if(zeroOneData[i]!= 0 && zeroOneData[i]!= 1) {
            return -1;
        }

        switch(s) {
        case START:
            if (input==0) {
                s = GOT_ZERO;
                zeroCount= 1;
                oneCount = 0;
            } else {
                s = GOT_ONE;
                zeroCount = 0;
                oneCount = 1;
            }
            break;

        case GOT_ONE:
            if (input == 0) {
                s = GOT_ZERO;
                ++zeroCount;
            } else if (i>=numSamples) {
                s = DONE;
            }
            break;

        case GOT_ZERO:
            if (input == 0) {
                s = GOT_ZERO;
            } else if (input == 1) {
                s = GOT_ONE;
                ++oneCount;
            } else if(i>=numSamples)
                s=DONE;
            break;

        case DONE:
            break;

        default:
            cerr << "An unknown error occurred." << endl;
            exit(-1);
            break;
        }
        // Process actions on entering the state
        switch (s) {
          case GOT_ONE:
            ++i;
            break;
        case GOT_ZERO:
            ++i;
            break;
        case DONE:
            return 0;
            break;
          case START:
            break;
        default:
            cerr << "An unknown error occurred." << endl;
            exit(-1);
            break;
        }
    }
    return 0;
}