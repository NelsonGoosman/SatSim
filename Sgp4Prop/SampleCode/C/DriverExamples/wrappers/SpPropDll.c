// This wrapper file was generated automatically by the GenDllWrappers program.

#include "../services/DllUtils.h"
#include "SpPropDll.h"


// SpPropDll's function pointers definition
fnPtrSpInit                         SpInit;
fnPtrSpGetInfo                      SpGetInfo;
fnPtrSpLoadFile                     SpLoadFile;
fnPtrSpLoadFileAll                  SpLoadFileAll;
fnPtrSpSaveFile                     SpSaveFile;
fnPtrSpInitSat                      SpInitSat;
fnPtrSpInitSat_MT                   SpInitSat_MT;
fnPtrSpRemoveSat                    SpRemoveSat;
fnPtrSpRemoveAllSats                SpRemoveAllSats;
fnPtrSpGetCount                     SpGetCount;
fnPtrSpReset                        SpReset;
fnPtrSpGetApCtrl                    SpGetApCtrl;
fnPtrSpGetApCtrlAll                 SpGetApCtrlAll;
fnPtrSpSetApCtrl                    SpSetApCtrl;
fnPtrSpSetApCtrlAll                 SpSetApCtrlAll;
fnPtrSpGet4P                        SpGet4P;
fnPtrSpSet4P                        SpSet4P;
fnPtrSpGetPredCtrl                  SpGetPredCtrl;
fnPtrSpSetPredCtrl                  SpSetPredCtrl;
fnPtrSpGetSatData                   SpGetSatData;
fnPtrSpGetSatDataAll                SpGetSatDataAll;
fnPtrSpPropMse                      SpPropMse;
fnPtrSpPropDs50UTC                  SpPropDs50UTC;
fnPtrSpPropDs50UtcLLH               SpPropDs50UtcLLH;
fnPtrSpPropDs50UtcPos               SpPropDs50UtcPos;
fnPtrSpPropAll                      SpPropAll;
fnPtrSpGetStateDs50UTC              SpGetStateDs50UTC;
fnPtrSpSetStateDs50UTC              SpSetStateDs50UTC;
fnPtrSpSetAndProp                   SpSetAndProp;
fnPtrSpGetPropOut                   SpGetPropOut;
fnPtrSpGetCovMtx                    SpGetCovMtx;
fnPtrSpCompCovSigma                 SpCompCovSigma;
fnPtrSpSet4pAll                     SpSet4pAll;
fnPtrSpGet4pAll                     SpGet4pAll;
fnPtrSpSet4PCard                    SpSet4PCard;
fnPtrSpGet4PCard                    SpGet4PCard;
fnPtrSpAddFluxRec                   SpAddFluxRec;
fnPtrSpGetEphemTimes                SpGetEphemTimes;
fnPtrSpGenEphems                    SpGenEphems;
fnPtrSpGenEphemsCov                 SpGenEphemsCov;
fnPtrSpGenEphemsVcm_OS              SpGenEphemsVcm_OS;
fnPtrSpGenEphemsVcmCov_OS           SpGenEphemsVcmCov_OS;
fnPtrSpPropAllSats                  SpPropAllSats;
fnPtrSpPropAllExt                   SpPropAllExt;
fnPtrSpLoadFluxFile                 SpLoadFluxFile;
fnPtrSpLoadDCAFile                  SpLoadDCAFile;
fnPtrAtmspDensity                   AtmspDensity;
fnPtrGetDcaRec                      GetDcaRec;
fnPtrSpRemoveFlux                   SpRemoveFlux;
fnPtrSpRemoveDCAFile                SpRemoveDCAFile;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadSpPropDll()
{
   if(hLib != NULL) {
      printf("Warning: %s already loaded.\n", SpPropDll);
      return;
   }
   // Explicitly load the dll
   hLib = LoadLib(SpPropDll);


   // Assign function pointers to the appropriate dll functions
   SpInit = (fnPtrSpInit)GetFnPtr(hLib, (char*)"SpInit");
   SpGetInfo = (fnPtrSpGetInfo)GetFnPtr(hLib, (char*)"SpGetInfo");
   SpLoadFile = (fnPtrSpLoadFile)GetFnPtr(hLib, (char*)"SpLoadFile");
   SpLoadFileAll = (fnPtrSpLoadFileAll)GetFnPtr(hLib, (char*)"SpLoadFileAll");
   SpSaveFile = (fnPtrSpSaveFile)GetFnPtr(hLib, (char*)"SpSaveFile");
   SpInitSat = (fnPtrSpInitSat)GetFnPtr(hLib, (char*)"SpInitSat");
   SpInitSat_MT = (fnPtrSpInitSat_MT)GetFnPtr(hLib, (char*)"SpInitSat_MT");
   SpRemoveSat = (fnPtrSpRemoveSat)GetFnPtr(hLib, (char*)"SpRemoveSat");
   SpRemoveAllSats = (fnPtrSpRemoveAllSats)GetFnPtr(hLib, (char*)"SpRemoveAllSats");
   SpGetCount = (fnPtrSpGetCount)GetFnPtr(hLib, (char*)"SpGetCount");
   SpReset = (fnPtrSpReset)GetFnPtr(hLib, (char*)"SpReset");
   SpGetApCtrl = (fnPtrSpGetApCtrl)GetFnPtr(hLib, (char*)"SpGetApCtrl");
   SpGetApCtrlAll = (fnPtrSpGetApCtrlAll)GetFnPtr(hLib, (char*)"SpGetApCtrlAll");
   SpSetApCtrl = (fnPtrSpSetApCtrl)GetFnPtr(hLib, (char*)"SpSetApCtrl");
   SpSetApCtrlAll = (fnPtrSpSetApCtrlAll)GetFnPtr(hLib, (char*)"SpSetApCtrlAll");
   SpGet4P = (fnPtrSpGet4P)GetFnPtr(hLib, (char*)"SpGet4P");
   SpSet4P = (fnPtrSpSet4P)GetFnPtr(hLib, (char*)"SpSet4P");
   SpGetPredCtrl = (fnPtrSpGetPredCtrl)GetFnPtr(hLib, (char*)"SpGetPredCtrl");
   SpSetPredCtrl = (fnPtrSpSetPredCtrl)GetFnPtr(hLib, (char*)"SpSetPredCtrl");
   SpGetSatData = (fnPtrSpGetSatData)GetFnPtr(hLib, (char*)"SpGetSatData");
   SpGetSatDataAll = (fnPtrSpGetSatDataAll)GetFnPtr(hLib, (char*)"SpGetSatDataAll");
   SpPropMse = (fnPtrSpPropMse)GetFnPtr(hLib, (char*)"SpPropMse");
   SpPropDs50UTC = (fnPtrSpPropDs50UTC)GetFnPtr(hLib, (char*)"SpPropDs50UTC");
   SpPropDs50UtcLLH = (fnPtrSpPropDs50UtcLLH)GetFnPtr(hLib, (char*)"SpPropDs50UtcLLH");
   SpPropDs50UtcPos = (fnPtrSpPropDs50UtcPos)GetFnPtr(hLib, (char*)"SpPropDs50UtcPos");
   SpPropAll = (fnPtrSpPropAll)GetFnPtr(hLib, (char*)"SpPropAll");
   SpGetStateDs50UTC = (fnPtrSpGetStateDs50UTC)GetFnPtr(hLib, (char*)"SpGetStateDs50UTC");
   SpSetStateDs50UTC = (fnPtrSpSetStateDs50UTC)GetFnPtr(hLib, (char*)"SpSetStateDs50UTC");
   SpSetAndProp = (fnPtrSpSetAndProp)GetFnPtr(hLib, (char*)"SpSetAndProp");
   SpGetPropOut = (fnPtrSpGetPropOut)GetFnPtr(hLib, (char*)"SpGetPropOut");
   SpGetCovMtx = (fnPtrSpGetCovMtx)GetFnPtr(hLib, (char*)"SpGetCovMtx");
   SpCompCovSigma = (fnPtrSpCompCovSigma)GetFnPtr(hLib, (char*)"SpCompCovSigma");
   SpSet4pAll = (fnPtrSpSet4pAll)GetFnPtr(hLib, (char*)"SpSet4pAll");
   SpGet4pAll = (fnPtrSpGet4pAll)GetFnPtr(hLib, (char*)"SpGet4pAll");
   SpSet4PCard = (fnPtrSpSet4PCard)GetFnPtr(hLib, (char*)"SpSet4PCard");
   SpGet4PCard = (fnPtrSpGet4PCard)GetFnPtr(hLib, (char*)"SpGet4PCard");
   SpAddFluxRec = (fnPtrSpAddFluxRec)GetFnPtr(hLib, (char*)"SpAddFluxRec");
   SpGetEphemTimes = (fnPtrSpGetEphemTimes)GetFnPtr(hLib, (char*)"SpGetEphemTimes");
   SpGenEphems = (fnPtrSpGenEphems)GetFnPtr(hLib, (char*)"SpGenEphems");
   SpGenEphemsCov = (fnPtrSpGenEphemsCov)GetFnPtr(hLib, (char*)"SpGenEphemsCov");
   SpGenEphemsVcm_OS = (fnPtrSpGenEphemsVcm_OS)GetFnPtr(hLib, (char*)"SpGenEphemsVcm_OS");
   SpGenEphemsVcmCov_OS = (fnPtrSpGenEphemsVcmCov_OS)GetFnPtr(hLib, (char*)"SpGenEphemsVcmCov_OS");
   SpPropAllSats = (fnPtrSpPropAllSats)GetFnPtr(hLib, (char*)"SpPropAllSats");
   SpPropAllExt = (fnPtrSpPropAllExt)GetFnPtr(hLib, (char*)"SpPropAllExt");
   SpLoadFluxFile = (fnPtrSpLoadFluxFile)GetFnPtr(hLib, (char*)"SpLoadFluxFile");
   SpLoadDCAFile = (fnPtrSpLoadDCAFile)GetFnPtr(hLib, (char*)"SpLoadDCAFile");
   AtmspDensity = (fnPtrAtmspDensity)GetFnPtr(hLib, (char*)"AtmspDensity");
   GetDcaRec = (fnPtrGetDcaRec)GetFnPtr(hLib, (char*)"GetDcaRec");
   SpRemoveFlux = (fnPtrSpRemoveFlux)GetFnPtr(hLib, (char*)"SpRemoveFlux");
   SpRemoveDCAFile = (fnPtrSpRemoveDCAFile)GetFnPtr(hLib, (char*)"SpRemoveDCAFile");
}



// Free SpPropDll
void FreeSpPropDll()
{
   if(hLib == NULL) {
      printf("Warning: %s already freed.\nUse after free averted.\n", SpPropDll);
      return;
   }
   FreeLib(hLib, SpPropDll);
   hLib = NULL;
   SpInit = NULL;
   SpGetInfo = NULL;
   SpLoadFile = NULL;
   SpLoadFileAll = NULL;
   SpSaveFile = NULL;
   SpInitSat = NULL;
   SpInitSat_MT = NULL;
   SpRemoveSat = NULL;
   SpRemoveAllSats = NULL;
   SpGetCount = NULL;
   SpReset = NULL;
   SpGetApCtrl = NULL;
   SpGetApCtrlAll = NULL;
   SpSetApCtrl = NULL;
   SpSetApCtrlAll = NULL;
   SpGet4P = NULL;
   SpSet4P = NULL;
   SpGetPredCtrl = NULL;
   SpSetPredCtrl = NULL;
   SpGetSatData = NULL;
   SpGetSatDataAll = NULL;
   SpPropMse = NULL;
   SpPropDs50UTC = NULL;
   SpPropDs50UtcLLH = NULL;
   SpPropDs50UtcPos = NULL;
   SpPropAll = NULL;
   SpGetStateDs50UTC = NULL;
   SpSetStateDs50UTC = NULL;
   SpSetAndProp = NULL;
   SpGetPropOut = NULL;
   SpGetCovMtx = NULL;
   SpCompCovSigma = NULL;
   SpSet4pAll = NULL;
   SpGet4pAll = NULL;
   SpSet4PCard = NULL;
   SpGet4PCard = NULL;
   SpAddFluxRec = NULL;
   SpGetEphemTimes = NULL;
   SpGenEphems = NULL;
   SpGenEphemsCov = NULL;
   SpGenEphemsVcm_OS = NULL;
   SpGenEphemsVcmCov_OS = NULL;
   SpPropAllSats = NULL;
   SpPropAllExt = NULL;
   SpLoadFluxFile = NULL;
   SpLoadDCAFile = NULL;
   AtmspDensity = NULL;
   GetDcaRec = NULL;
   SpRemoveFlux = NULL;
   SpRemoveDCAFile = NULL;
}
// ========================= End of auto generated code ==========================
