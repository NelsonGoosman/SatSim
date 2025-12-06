// This wrapper file was generated automatically by the GenDllWrappers program.

#include "../services/DllUtils.h"
#include "RotasDll.h"


// RotasDll's function pointers definition
fnPtrRotasInit                      RotasInit;
fnPtrRotasGetInfo                   RotasGetInfo;
fnPtrRotasLoadFile                  RotasLoadFile;
fnPtrRotasLoadFileAll               RotasLoadFileAll;
fnPtrRotasLoadCard                  RotasLoadCard;
fnPtrRotasSaveFile                  RotasSaveFile;
fnPtrRotasGetPCard                  RotasGetPCard;
fnPtrRotasGetPAll                   RotasGetPAll;
fnPtrRotasSetPAll                   RotasSetPAll;
fnPtrRotasGetPField                 RotasGetPField;
fnPtrRotasSetPField                 RotasSetPField;
fnPtrRotasGetAssocMultipliers       RotasGetAssocMultipliers;
fnPtrRotasSetAssocMultipliers       RotasSetAssocMultipliers;
fnPtrRotasResetAll                  RotasResetAll;
fnPtrRotasHasASTAT                  RotasHasASTAT;
fnPtrRotasHasASTAT_MT               RotasHasASTAT_MT;
fnPtrRotasHasASTATMultp_MT          RotasHasASTATMultp_MT;
fnPtrRotasComputeObsResiduals       RotasComputeObsResiduals;
fnPtrRotasComputeObsResiduals_MT    RotasComputeObsResiduals_MT;
fnPtrRotasComputeObsResidualsMultp_MT RotasComputeObsResidualsMultp_MT;
fnPtrRotasComputeTrackResiduals     RotasComputeTrackResiduals;
fnPtrRotasComputeTrackResiduals_MT  RotasComputeTrackResiduals_MT;
fnPtrRotasCompObResDirect           RotasCompObResDirect;
fnPtrRotasGetRetagObsFile           RotasGetRetagObsFile;
fnPtrRotasSetRetagObsFile           RotasSetRetagObsFile;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadRotasDll()
{
   if(hLib != NULL) {
      printf("Warning: %s already loaded.\n", RotasDll);
      return;
   }
   // Explicitly load the dll
   hLib = LoadLib(RotasDll);


   // Assign function pointers to the appropriate dll functions
   RotasInit = (fnPtrRotasInit)GetFnPtr(hLib, (char*)"RotasInit");
   RotasGetInfo = (fnPtrRotasGetInfo)GetFnPtr(hLib, (char*)"RotasGetInfo");
   RotasLoadFile = (fnPtrRotasLoadFile)GetFnPtr(hLib, (char*)"RotasLoadFile");
   RotasLoadFileAll = (fnPtrRotasLoadFileAll)GetFnPtr(hLib, (char*)"RotasLoadFileAll");
   RotasLoadCard = (fnPtrRotasLoadCard)GetFnPtr(hLib, (char*)"RotasLoadCard");
   RotasSaveFile = (fnPtrRotasSaveFile)GetFnPtr(hLib, (char*)"RotasSaveFile");
   RotasGetPCard = (fnPtrRotasGetPCard)GetFnPtr(hLib, (char*)"RotasGetPCard");
   RotasGetPAll = (fnPtrRotasGetPAll)GetFnPtr(hLib, (char*)"RotasGetPAll");
   RotasSetPAll = (fnPtrRotasSetPAll)GetFnPtr(hLib, (char*)"RotasSetPAll");
   RotasGetPField = (fnPtrRotasGetPField)GetFnPtr(hLib, (char*)"RotasGetPField");
   RotasSetPField = (fnPtrRotasSetPField)GetFnPtr(hLib, (char*)"RotasSetPField");
   RotasGetAssocMultipliers = (fnPtrRotasGetAssocMultipliers)GetFnPtr(hLib, (char*)"RotasGetAssocMultipliers");
   RotasSetAssocMultipliers = (fnPtrRotasSetAssocMultipliers)GetFnPtr(hLib, (char*)"RotasSetAssocMultipliers");
   RotasResetAll = (fnPtrRotasResetAll)GetFnPtr(hLib, (char*)"RotasResetAll");
   RotasHasASTAT = (fnPtrRotasHasASTAT)GetFnPtr(hLib, (char*)"RotasHasASTAT");
   RotasHasASTAT_MT = (fnPtrRotasHasASTAT_MT)GetFnPtr(hLib, (char*)"RotasHasASTAT_MT");
   RotasHasASTATMultp_MT = (fnPtrRotasHasASTATMultp_MT)GetFnPtr(hLib, (char*)"RotasHasASTATMultp_MT");
   RotasComputeObsResiduals = (fnPtrRotasComputeObsResiduals)GetFnPtr(hLib, (char*)"RotasComputeObsResiduals");
   RotasComputeObsResiduals_MT = (fnPtrRotasComputeObsResiduals_MT)GetFnPtr(hLib, (char*)"RotasComputeObsResiduals_MT");
   RotasComputeObsResidualsMultp_MT = (fnPtrRotasComputeObsResidualsMultp_MT)GetFnPtr(hLib, (char*)"RotasComputeObsResidualsMultp_MT");
   RotasComputeTrackResiduals = (fnPtrRotasComputeTrackResiduals)GetFnPtr(hLib, (char*)"RotasComputeTrackResiduals");
   RotasComputeTrackResiduals_MT = (fnPtrRotasComputeTrackResiduals_MT)GetFnPtr(hLib, (char*)"RotasComputeTrackResiduals_MT");
   RotasCompObResDirect = (fnPtrRotasCompObResDirect)GetFnPtr(hLib, (char*)"RotasCompObResDirect");
   RotasGetRetagObsFile = (fnPtrRotasGetRetagObsFile)GetFnPtr(hLib, (char*)"RotasGetRetagObsFile");
   RotasSetRetagObsFile = (fnPtrRotasSetRetagObsFile)GetFnPtr(hLib, (char*)"RotasSetRetagObsFile");
}



// Free RotasDll
void FreeRotasDll()
{
   if(hLib == NULL) {
      printf("Warning: %s already freed.\nUse after free averted.\n", RotasDll);
      return;
   }
   FreeLib(hLib, RotasDll);
   hLib = NULL;
   RotasInit = NULL;
   RotasGetInfo = NULL;
   RotasLoadFile = NULL;
   RotasLoadFileAll = NULL;
   RotasLoadCard = NULL;
   RotasSaveFile = NULL;
   RotasGetPCard = NULL;
   RotasGetPAll = NULL;
   RotasSetPAll = NULL;
   RotasGetPField = NULL;
   RotasSetPField = NULL;
   RotasGetAssocMultipliers = NULL;
   RotasSetAssocMultipliers = NULL;
   RotasResetAll = NULL;
   RotasHasASTAT = NULL;
   RotasHasASTAT_MT = NULL;
   RotasHasASTATMultp_MT = NULL;
   RotasComputeObsResiduals = NULL;
   RotasComputeObsResiduals_MT = NULL;
   RotasComputeObsResidualsMultp_MT = NULL;
   RotasComputeTrackResiduals = NULL;
   RotasComputeTrackResiduals_MT = NULL;
   RotasCompObResDirect = NULL;
   RotasGetRetagObsFile = NULL;
   RotasSetRetagObsFile = NULL;
}
// ========================= End of auto generated code ==========================
