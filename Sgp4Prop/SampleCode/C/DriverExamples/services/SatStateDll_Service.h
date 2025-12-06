#ifndef SATSTATEDLL_SERVICE_H
#define SATSTATEDLL_SERVICE_H

#include <stdio.h>
#include "DllUtils.h"

#include "../wrappers/TleDll.h"
#include "../wrappers/SpVecDll.h"
#include "../wrappers/VcmDll.h"
#include "../wrappers/ExtEphemDll.h"
#include "../wrappers/ElOpsDll.h"

static char EltTypeStr[6][16] = {"TLE (SGP)", 
                                 "TLE (SGP4)", 
                                 "TLE (SP)", 
                                 "SP Vector (B1P)", 
                                 "VCM", 
                                 "EXT EPHEMERIS"};
static char RecTypeStr[8][7] = {"TLE", 
                                "TLE", 
                                "SPTLE", 
                                "SPVEC", 
                                "VCM", 
                                "EXTEPH", 
                                "TLEXP",
                                "PPT3"};

double GetSatDataField(__int64 satKey, int idx);
int SatStateGetTypeCount(int type, __int64* satKeys, int satCount);
void PrintSatelliteData(FILE* fp, __int64 satKey);
char* GetSatTypeString(int orbEltType);
char* GetRecTypeString(int orbEltType);

#endif
