// This wrapper file was generated automatically by the GenDllWrappers program.

#include "../services/DllUtils.h"
#include "SaasDll.h"


// SaasDll's function pointers definition
fnPtrSaasInit                       SaasInit;
fnPtrSaasGetInfo                    SaasGetInfo;
fnPtrSaasGetResults                 SaasGetResults;
fnPtrSaasAutoConeSize               SaasAutoConeSize;
fnPtrSaasMissileFlightTime          SaasMissileFlightTime;
fnPtrComputeLnchOrbPlane            ComputeLnchOrbPlane;
fnPtrFindPlanerIntersection         FindPlanerIntersection;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadSaasDll()
{
   if(hLib != NULL) {
      printf("Warning: %s already loaded.\n", SaasDll);
      return;
   }
   // Explicitly load the dll
   hLib = LoadLib(SaasDll);


   // Assign function pointers to the appropriate dll functions
   SaasInit = (fnPtrSaasInit)GetFnPtr(hLib, (char*)"SaasInit");
   SaasGetInfo = (fnPtrSaasGetInfo)GetFnPtr(hLib, (char*)"SaasGetInfo");
   SaasGetResults = (fnPtrSaasGetResults)GetFnPtr(hLib, (char*)"SaasGetResults");
   SaasAutoConeSize = (fnPtrSaasAutoConeSize)GetFnPtr(hLib, (char*)"SaasAutoConeSize");
   SaasMissileFlightTime = (fnPtrSaasMissileFlightTime)GetFnPtr(hLib, (char*)"SaasMissileFlightTime");
   ComputeLnchOrbPlane = (fnPtrComputeLnchOrbPlane)GetFnPtr(hLib, (char*)"ComputeLnchOrbPlane");
   FindPlanerIntersection = (fnPtrFindPlanerIntersection)GetFnPtr(hLib, (char*)"FindPlanerIntersection");
}



// Free SaasDll
void FreeSaasDll()
{
   if(hLib == NULL) {
      printf("Warning: %s already freed.\nUse after free averted.\n", SaasDll);
      return;
   }
   FreeLib(hLib, SaasDll);
   hLib = NULL;
   SaasInit = NULL;
   SaasGetInfo = NULL;
   SaasGetResults = NULL;
   SaasAutoConeSize = NULL;
   SaasMissileFlightTime = NULL;
   ComputeLnchOrbPlane = NULL;
   FindPlanerIntersection = NULL;
}
// ========================= End of auto generated code ==========================
