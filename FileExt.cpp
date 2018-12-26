#include <iostream>
#include <stdlib.h>

using namespace std;

enum ExtensionType {NO_DOT, CSV_EXT, INVALID_EXT};
enum STATE {START, GotLetter, GotDot, DoneNoExt, GotC, GotS, GotV, DoneWithExt};

ExtensionType filenameType(char const filename[]){
	int i = 0;
	ExtensionType rt = INVALID_EXT;
	STATE s = START;

	while (1){
		switch(s){
			case START: 
				if (filename[i]>='a' && filename[i] <= 'z'){
					s = GotLetter;
				}
				else 
					return INVALID_EXT;
				break;

			case GotLetter:
				if(filename[i]>='a'&& filename[i]<= 'z')
					s = GotLetter;
				if(filename[i] == 0)
					s = DoneNoExt;
				if(filename[i] == '.')
					s = GotDot;
				break;

			case GotDot:
				if (filename[i] == 'c')
					s = GotC;
				else 
					return INVALID_EXT;
				break;

			case GotC:
				if (filename[i] == 's')
					s = GotS;
				else 
					return INVALID_EXT;
				break;

			case GotS:
				if (filename[i] == 'v')
					s = GotV;
				else 
					return INVALID_EXT;
				break;

			case GotV:
				if (filename[i] == 0)
					s = DoneWithExt;
				else 
					return INVALID_EXT;
				break;

			case DoneNoExt:
				rt = NO_DOT;
				return rt;
				break;

			case DoneWithExt:
				rt = CSV_EXT;
				return rt;
				break;
		}
		i++;
	}
	return rt;
}