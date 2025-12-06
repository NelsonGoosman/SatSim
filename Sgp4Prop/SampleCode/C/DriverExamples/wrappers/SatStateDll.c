// This wrapper file was generated automatically by the GenDllWrappers program.

#include "../services/DllUtils.h"
#include "SatStateDll.h"


// SatStateDll's function pointers definition
fnPtrSatStateInit                   SatStateInit;
fnPtrSatStateGetInfo                SatStateGetInfo;
fnPtrSatStateLoadFile               SatStateLoadFile;
fnPtrSatStateSaveFile               SatStateSaveFile;
fnPtrSatStateRemoveSat              SatStateRemoveSat;
fnPtrSatStateRemoveSatAll           SatStateRemoveSatAll;
fnPtrSatStateRemoveAllSats          SatStateRemoveAllSats;
fnPtrSatStateReset                  SatStateReset;
fnPtrSatStateGetCount               SatStateGetCount;
fnPtrSatStateGetLoaded              SatStateGetLoaded;
fnPtrSatStateNumToKey               SatStateNumToKey;
fnPtrSatStateGetSatDataAll          SatStateGetSatDataAll;
fnPtrSatStateGetSatDataField        SatStateGetSatDataField;
fnPtrSatStateInitSat                SatStateInitSat;
fnPtrSatStateMse                    SatStateMse;
fnPtrSatStateDs50UTC                SatStateDs50UTC;
fnPtrSatStateGetPropOut             SatStateGetPropOut;
fnPtrSatStateEphCom                 SatStateEphCom;
fnPtrSatStateEphCom_OS              SatStateEphCom_OS;
fnPtrSatStateHasCovMtx              SatStateHasCovMtx;
fnPtrSatStateGetCovUVW              SatStateGetCovUVW;
fnPtrSatStateGenEphFile             SatStateGenEphFile;
fnPtrGetNodalCrossingPriorToTime    GetNodalCrossingPriorToTime;
fnPtrGetGobsParams                  GetGobsParams;
fnPtrGobsCom                        GobsCom;
fnPtrGobsComArr                     GobsComArr;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadSatStateDll()
{
   if(hLib != NULL) {
      printf("Warning: %s already loaded.\n", SatStateDll);
      return;
   }
   // Explicitly load the dll
   hLib = LoadLib(SatStateDll);


   // Assign function pointers to the appropriate dll functions
   SatStateInit = (fnPtrSatStateInit)GetFnPtr(hLib, (char*)"SatStateInit");
   SatStateGetInfo = (fnPtrSatStateGetInfo)GetFnPtr(hLib, (char*)"SatStateGetInfo");
   SatStateLoadFile = (fnPtrSatStateLoadFile)GetFnPtr(hLib, (char*)"SatStateLoadFile");
   SatStateSaveFile = (fnPtrSatStateSaveFile)GetFnPtr(hLib, (char*)"SatStateSaveFile");
   SatStateRemoveSat = (fnPtrSatStateRemoveSat)GetFnPtr(hLib, (char*)"SatStateRemoveSat");
   SatStateRemoveSatAll = (fnPtrSatStateRemoveSatAll)GetFnPtr(hLib, (char*)"SatStateRemoveSatAll");
   SatStateRemoveAllSats = (fnPtrSatStateRemoveAllSats)GetFnPtr(hLib, (char*)"SatStateRemoveAllSats");
   SatStateReset = (fnPtrSatStateReset)GetFnPtr(hLib, (char*)"SatStateReset");
   SatStateGetCount = (fnPtrSatStateGetCount)GetFnPtr(hLib, (char*)"SatStateGetCount");
   SatStateGetLoaded = (fnPtrSatStateGetLoaded)GetFnPtr(hLib, (char*)"SatStateGetLoaded");
   SatStateNumToKey = (fnPtrSatStateNumToKey)GetFnPtr(hLib, (char*)"SatStateNumToKey");
   SatStateGetSatDataAll = (fnPtrSatStateGetSatDataAll)GetFnPtr(hLib, (char*)"SatStateGetSatDataAll");
   SatStateGetSatDataField = (fnPtrSatStateGetSatDataField)GetFnPtr(hLib, (char*)"SatStateGetSatDataField");
   SatStateInitSat = (fnPtrSatStateInitSat)GetFnPtr(hLib, (char*)"SatStateInitSat");
   SatStateMse = (fnPtrSatStateMse)GetFnPtr(hLib, (char*)"SatStateMse");
   SatStateDs50UTC = (fnPtrSatStateDs50UTC)GetFnPtr(hLib, (char*)"SatStateDs50UTC");
   SatStateGetPropOut = (fnPtrSatStateGetPropOut)GetFnPtr(hLib, (char*)"SatStateGetPropOut");
   SatStateEphCom = (fnPtrSatStateEphCom)GetFnPtr(hLib, (char*)"SatStateEphCom");
   SatStateEphCom_OS = (fnPtrSatStateEphCom_OS)GetFnPtr(hLib, (char*)"SatStateEphCom_OS");
   SatStateHasCovMtx = (fnPtrSatStateHasCovMtx)GetFnPtr(hLib, (char*)"SatStateHasCovMtx");
   SatStateGetCovUVW = (fnPtrSatStateGetCovUVW)GetFnPtr(hLib, (char*)"SatStateGetCovUVW");
   SatStateGenEphFile = (fnPtrSatStateGenEphFile)GetFnPtr(hLib, (char*)"SatStateGenEphFile");
   GetNodalCrossingPriorToTime = (fnPtrGetNodalCrossingPriorToTime)GetFnPtr(hLib, (char*)"GetNodalCrossingPriorToTime");
   GetGobsParams = (fnPtrGetGobsParams)GetFnPtr(hLib, (char*)"GetGobsParams");
   GobsCom = (fnPtrGobsCom)GetFnPtr(hLib, (char*)"GobsCom");
   GobsComArr = (fnPtrGobsComArr)GetFnPtr(hLib, (char*)"GobsComArr");
}



// Free SatStateDll
void FreeSatStateDll()
{
   if(hLib == NULL) {
      printf("Warning: %s already freed.\nUse after free averted.\n", SatStateDll);
      return;
   }
   FreeLib(hLib, SatStateDll);
   hLib = NULL;
   SatStateInit = NULL;
   SatStateGetInfo = NULL;
   SatStateLoadFile = NULL;
   SatStateSaveFile = NULL;
   SatStateRemoveSat = NULL;
   SatStateRemoveSatAll = NULL;
   SatStateRemoveAllSats = NULL;
   SatStateReset = NULL;
   SatStateGetCount = NULL;
   SatStateGetLoaded = NULL;
   SatStateNumToKey = NULL;
   SatStateGetSatDataAll = NULL;
   SatStateGetSatDataField = NULL;
   SatStateInitSat = NULL;
   SatStateMse = NULL;
   SatStateDs50UTC = NULL;
   SatStateGetPropOut = NULL;
   SatStateEphCom = NULL;
   SatStateEphCom_OS = NULL;
   SatStateHasCovMtx = NULL;
   SatStateGetCovUVW = NULL;
   SatStateGenEphFile = NULL;
   GetNodalCrossingPriorToTime = NULL;
   GetGobsParams = NULL;
   GobsCom = NULL;
   GobsComArr = NULL;
}
// ========================= End of auto generated code ==========================
