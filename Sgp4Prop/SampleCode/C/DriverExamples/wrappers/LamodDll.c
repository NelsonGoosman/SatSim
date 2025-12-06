// This wrapper file was generated automatically by the GenDllWrappers program.

#include "../services/DllUtils.h"
#include "LamodDll.h"


// LamodDll's function pointers definition
fnPtrLamodInit                      LamodInit;
fnPtrLamodGetInfo                   LamodGetInfo;
fnPtrLamodLoadFile                  LamodLoadFile;
fnPtrLamodLoadFileAll               LamodLoadFileAll;
fnPtrLamodLoadCard                  LamodLoadCard;
fnPtrLamodSaveFile                  LamodSaveFile;
fnPtrLamodGetNumOfSensSats          LamodGetNumOfSensSats;
fnPtrLamodGetSenNums                LamodGetSenNums;
fnPtrLamodGetSatNums                LamodGetSatNums;
fnPtrLamodGet1pCard                 LamodGet1pCard;
fnPtrLamodGet1pAll                  LamodGet1pAll;
fnPtrLamodSet1pAll                  LamodSet1pAll;
fnPtrLamodGet1pField                LamodGet1pField;
fnPtrLamodSet1pField                LamodSet1pField;
fnPtrLamodGet3pAll                  LamodGet3pAll;
fnPtrLamodSet3pAll                  LamodSet3pAll;
fnPtrLamodGetObsFileName            LamodGetObsFileName;
fnPtrLamodSetObsFileName            LamodSetObsFileName;
fnPtrLamodSenSatVisible             LamodSenSatVisible;
fnPtrLamodInitSenSat                LamodInitSenSat;
fnPtrLamodInitSenSat_MT             LamodInitSenSat_MT;
fnPtrLamodGetSenSatDataAll          LamodGetSenSatDataAll;
fnPtrLamodGetSenSatDataField        LamodGetSenSatDataField;
fnPtrLamodSenSatDataToArray         LamodSenSatDataToArray;
fnPtrLamodGetNumPasses              LamodGetNumPasses;
fnPtrLamodGetRiseCulmSetTimes       LamodGetRiseCulmSetTimes;
fnPtrLamodComputeLookAngle          LamodComputeLookAngle;
fnPtrLamodComputeLookView           LamodComputeLookView;
fnPtrLamodFindExactIOTime           LamodFindExactIOTime;
fnPtrLamodGetOrbSenViewdata         LamodGetOrbSenViewdata;
fnPtrLamodGetViewDataField          LamodGetViewDataField;
fnPtrLamodCompRaDec                 LamodCompRaDec;
fnPtrLamodGenObs                    LamodGenObs;
fnPtrLamodGenObsAtTime              LamodGenObsAtTime;
fnPtrLamodGenRfObs                  LamodGenRfObs;
fnPtrLamodRemoveSenSat              LamodRemoveSenSat;
fnPtrLamodRemoveAllSenSats          LamodRemoveAllSenSats;
fnPtrLamodReset                     LamodReset;
fnPtrLamodSenSatDirect_OS           LamodSenSatDirect_OS;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadLamodDll()
{
   if(hLib != NULL) {
      printf("Warning: %s already loaded.\n", LamodDll);
      return;
   }
   // Explicitly load the dll
   hLib = LoadLib(LamodDll);


   // Assign function pointers to the appropriate dll functions
   LamodInit = (fnPtrLamodInit)GetFnPtr(hLib, (char*)"LamodInit");
   LamodGetInfo = (fnPtrLamodGetInfo)GetFnPtr(hLib, (char*)"LamodGetInfo");
   LamodLoadFile = (fnPtrLamodLoadFile)GetFnPtr(hLib, (char*)"LamodLoadFile");
   LamodLoadFileAll = (fnPtrLamodLoadFileAll)GetFnPtr(hLib, (char*)"LamodLoadFileAll");
   LamodLoadCard = (fnPtrLamodLoadCard)GetFnPtr(hLib, (char*)"LamodLoadCard");
   LamodSaveFile = (fnPtrLamodSaveFile)GetFnPtr(hLib, (char*)"LamodSaveFile");
   LamodGetNumOfSensSats = (fnPtrLamodGetNumOfSensSats)GetFnPtr(hLib, (char*)"LamodGetNumOfSensSats");
   LamodGetSenNums = (fnPtrLamodGetSenNums)GetFnPtr(hLib, (char*)"LamodGetSenNums");
   LamodGetSatNums = (fnPtrLamodGetSatNums)GetFnPtr(hLib, (char*)"LamodGetSatNums");
   LamodGet1pCard = (fnPtrLamodGet1pCard)GetFnPtr(hLib, (char*)"LamodGet1pCard");
   LamodGet1pAll = (fnPtrLamodGet1pAll)GetFnPtr(hLib, (char*)"LamodGet1pAll");
   LamodSet1pAll = (fnPtrLamodSet1pAll)GetFnPtr(hLib, (char*)"LamodSet1pAll");
   LamodGet1pField = (fnPtrLamodGet1pField)GetFnPtr(hLib, (char*)"LamodGet1pField");
   LamodSet1pField = (fnPtrLamodSet1pField)GetFnPtr(hLib, (char*)"LamodSet1pField");
   LamodGet3pAll = (fnPtrLamodGet3pAll)GetFnPtr(hLib, (char*)"LamodGet3pAll");
   LamodSet3pAll = (fnPtrLamodSet3pAll)GetFnPtr(hLib, (char*)"LamodSet3pAll");
   LamodGetObsFileName = (fnPtrLamodGetObsFileName)GetFnPtr(hLib, (char*)"LamodGetObsFileName");
   LamodSetObsFileName = (fnPtrLamodSetObsFileName)GetFnPtr(hLib, (char*)"LamodSetObsFileName");
   LamodSenSatVisible = (fnPtrLamodSenSatVisible)GetFnPtr(hLib, (char*)"LamodSenSatVisible");
   LamodInitSenSat = (fnPtrLamodInitSenSat)GetFnPtr(hLib, (char*)"LamodInitSenSat");
   LamodInitSenSat_MT = (fnPtrLamodInitSenSat_MT)GetFnPtr(hLib, (char*)"LamodInitSenSat_MT");
   LamodGetSenSatDataAll = (fnPtrLamodGetSenSatDataAll)GetFnPtr(hLib, (char*)"LamodGetSenSatDataAll");
   LamodGetSenSatDataField = (fnPtrLamodGetSenSatDataField)GetFnPtr(hLib, (char*)"LamodGetSenSatDataField");
   LamodSenSatDataToArray = (fnPtrLamodSenSatDataToArray)GetFnPtr(hLib, (char*)"LamodSenSatDataToArray");
   LamodGetNumPasses = (fnPtrLamodGetNumPasses)GetFnPtr(hLib, (char*)"LamodGetNumPasses");
   LamodGetRiseCulmSetTimes = (fnPtrLamodGetRiseCulmSetTimes)GetFnPtr(hLib, (char*)"LamodGetRiseCulmSetTimes");
   LamodComputeLookAngle = (fnPtrLamodComputeLookAngle)GetFnPtr(hLib, (char*)"LamodComputeLookAngle");
   LamodComputeLookView = (fnPtrLamodComputeLookView)GetFnPtr(hLib, (char*)"LamodComputeLookView");
   LamodFindExactIOTime = (fnPtrLamodFindExactIOTime)GetFnPtr(hLib, (char*)"LamodFindExactIOTime");
   LamodGetOrbSenViewdata = (fnPtrLamodGetOrbSenViewdata)GetFnPtr(hLib, (char*)"LamodGetOrbSenViewdata");
   LamodGetViewDataField = (fnPtrLamodGetViewDataField)GetFnPtr(hLib, (char*)"LamodGetViewDataField");
   LamodCompRaDec = (fnPtrLamodCompRaDec)GetFnPtr(hLib, (char*)"LamodCompRaDec");
   LamodGenObs = (fnPtrLamodGenObs)GetFnPtr(hLib, (char*)"LamodGenObs");
   LamodGenObsAtTime = (fnPtrLamodGenObsAtTime)GetFnPtr(hLib, (char*)"LamodGenObsAtTime");
   LamodGenRfObs = (fnPtrLamodGenRfObs)GetFnPtr(hLib, (char*)"LamodGenRfObs");
   LamodRemoveSenSat = (fnPtrLamodRemoveSenSat)GetFnPtr(hLib, (char*)"LamodRemoveSenSat");
   LamodRemoveAllSenSats = (fnPtrLamodRemoveAllSenSats)GetFnPtr(hLib, (char*)"LamodRemoveAllSenSats");
   LamodReset = (fnPtrLamodReset)GetFnPtr(hLib, (char*)"LamodReset");
   LamodSenSatDirect_OS = (fnPtrLamodSenSatDirect_OS)GetFnPtr(hLib, (char*)"LamodSenSatDirect_OS");
}



// Free LamodDll
void FreeLamodDll()
{
   if(hLib == NULL) {
      printf("Warning: %s already freed.\nUse after free averted.\n", LamodDll);
      return;
   }
   FreeLib(hLib, LamodDll);
   hLib = NULL;
   LamodInit = NULL;
   LamodGetInfo = NULL;
   LamodLoadFile = NULL;
   LamodLoadFileAll = NULL;
   LamodLoadCard = NULL;
   LamodSaveFile = NULL;
   LamodGetNumOfSensSats = NULL;
   LamodGetSenNums = NULL;
   LamodGetSatNums = NULL;
   LamodGet1pCard = NULL;
   LamodGet1pAll = NULL;
   LamodSet1pAll = NULL;
   LamodGet1pField = NULL;
   LamodSet1pField = NULL;
   LamodGet3pAll = NULL;
   LamodSet3pAll = NULL;
   LamodGetObsFileName = NULL;
   LamodSetObsFileName = NULL;
   LamodSenSatVisible = NULL;
   LamodInitSenSat = NULL;
   LamodInitSenSat_MT = NULL;
   LamodGetSenSatDataAll = NULL;
   LamodGetSenSatDataField = NULL;
   LamodSenSatDataToArray = NULL;
   LamodGetNumPasses = NULL;
   LamodGetRiseCulmSetTimes = NULL;
   LamodComputeLookAngle = NULL;
   LamodComputeLookView = NULL;
   LamodFindExactIOTime = NULL;
   LamodGetOrbSenViewdata = NULL;
   LamodGetViewDataField = NULL;
   LamodCompRaDec = NULL;
   LamodGenObs = NULL;
   LamodGenObsAtTime = NULL;
   LamodGenRfObs = NULL;
   LamodRemoveSenSat = NULL;
   LamodRemoveAllSenSats = NULL;
   LamodReset = NULL;
   LamodSenSatDirect_OS = NULL;
}
// ========================= End of auto generated code ==========================
