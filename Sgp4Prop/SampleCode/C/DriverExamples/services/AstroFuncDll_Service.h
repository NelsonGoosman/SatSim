#ifndef ASTROFUNCDLL_SERVICE_H
#define ASTROFUNCDLL_SERVICE_H

#include "DllUtils.h"

double* PosToLLH(double ds50UT1, double* pos, fAddr envFkPtr);
double* LLHToPos(double ds50UT1, double* llh, fAddr envFkPtr);


#endif
