#ifndef SPPROPDLL_SERVICE_H
#define SPPROPDLL_SERVICE_H

#include <stdio.h>

void PrintSpAppCtrl(FILE* fp);
void PrintPredCtrl(FILE* fp);
const char* GeoIdxToStr(int geoIdx);
void PrintSpIntegCtrl(FILE* fp);


// Indexes represent coordinate systems
static const int
   IDX_OUTCOORD_DATE  = 0, 
   IDX_OUTCOORD_EPOCH = 1,  
   IDX_OUTCOORD_J2000 = 2;

// Indexes of Integration mode
static const int
   INTEG_NONE       = 0, 
   INTEG_NUMERICAL  = 1, 
   INTEG_ANALYTIC   = 2;


#endif
