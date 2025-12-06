#ifndef EXTEPHEMDLL_SERVICE_H
#define EXTEPHEMDLL_SERVICE_H

#include <stdio.h>

void PrintVecEphHeader(FILE* fp, double ke, double er, char* epochStr, char* orbEltType);
void PrintSimObsHeader(FILE* fp, double ke, double er, char* epochStr);
void PrintVecEphPoint(FILE* fp, int satNum, char* ds50UTCStr, double mse, double* pos, double* vel, char* orbEltType);
void PrintSimObsPoint(FILE* fp, int satNum, char* ds50UTCStr, int revNum, double* pos, double* vel, char* orbEltType);


#endif
