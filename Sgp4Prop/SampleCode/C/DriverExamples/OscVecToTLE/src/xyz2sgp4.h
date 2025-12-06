#ifndef xyz2sgp4__H
#define xyz2sgp4__H


#ifdef __cplusplus
extern "C" 
{
#endif

#include "../../wrappers/DllMainDll.h"
#include "../../wrappers/EnvConstDll.h"
#include "../../wrappers/AstroFuncDll.h"
#include "../../wrappers/TimeFuncDll.h"
#include "../../wrappers/TleDll.h"
#include "../../wrappers/Sgp4PropDll.h"

// End
#ifdef __cplusplus
}
#endif


// Function prototypes
void  LoadAstroStdDlls();
void  FreeAstroStdDlls();
void  xyz2sgp4(int yr, double days, double* posIn, double* velIn, double* n, double* ecc, double* incl, 
               double* node, double* MA, double* omega, double* posOut, double* velOut);

#endif
