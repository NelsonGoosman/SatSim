#include "../../services/DllUtils.h"
#include "../../services/DllMainDll_Service.h"

#include "xyz2sgp4.h"

// Load all the dlls being used in the program
void LoadAstroStdDlls()
{
   // Load MainDll dll
   LoadDllMainDll();

   // Load EnvConst dll and assign function pointers
   LoadEnvConstDll();

   // Load TimeFunc dll and assign function pointers
   LoadTimeFuncDll();

   // Load AstroFunc dll and assign function pointers
   LoadAstroFuncDll();

   // Load Tle dll and assign function pointers
   LoadTleDll();

   // Load Sgp4Prop dll and assign function pointers
   LoadSgp4PropDll();
}


// Free all the dlls being used in the program
void FreeAstroStdDlls()
{
   // Free MainDll dll
   FreeDllMainDll();

   // Free EnvConst dll
   FreeEnvConstDll();

   // Free AstroFunc dll
   FreeAstroFuncDll();

   // Free TimeFunc dll
   FreeTimeFuncDll();

   // Free Tle dll
   FreeTleDll();

   // Free Sgp4Prop dll
   FreeSgp4PropDll();
}


void xyz2sgp4(int yr, double days, double* posIn, double* velIn, double* n, double* ecc, double* incl, 
              double* node, double* MA, double* omega, double* posOut, double* velOut)
{
   double sgp4MeanKep[6];

   // Convert osculating vectors pos, vel to sgp4MeanKep
   Sgp4PosVelToKep(yr, days, posIn, velIn, posOut, velOut, sgp4MeanKep);

   // Convert Brouwer mean motion to Kozai mean motion
   *n     = BrouwerToKozai(sgp4MeanKep[XA_KEP_E], sgp4MeanKep[XA_KEP_INCLI],  AToN(sgp4MeanKep[XA_KEP_A]));
   *ecc   = sgp4MeanKep[XA_KEP_E];
   *incl  = sgp4MeanKep[XA_KEP_INCLI];
   *node  = sgp4MeanKep[XA_KEP_NODE];
   *MA    = sgp4MeanKep[XA_KEP_MA];
   *omega = sgp4MeanKep[XA_KEP_OMEGA];
}

