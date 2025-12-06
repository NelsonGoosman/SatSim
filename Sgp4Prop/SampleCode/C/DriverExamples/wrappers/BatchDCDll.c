// This wrapper file was generated automatically by the GenDllWrappers program.

#include "../services/DllUtils.h"
#include "BatchDCDll.h"


// BatchDCDll's function pointers definition
fnPtrBatchDCInit                    BatchDCInit;
fnPtrBatchDCGetInfo                 BatchDCGetInfo;
fnPtrBatchDCLoadFile                BatchDCLoadFile;
fnPtrBatchDCLoadFileAll             BatchDCLoadFileAll;
fnPtrBatchDCLoadCard                BatchDCLoadCard;
fnPtrBatchDCGetPCard                BatchDCGetPCard;
fnPtrBatchDCSaveFile                BatchDCSaveFile;
fnPtrBatchDCGetParams               BatchDCGetParams;
fnPtrBatchDCSetParams               BatchDCSetParams;
fnPtrBatchDCGetCtrlArr              BatchDCGetCtrlArr;
fnPtrBatchDCSetCtrlArr              BatchDCSetCtrlArr;
fnPtrBatchDCInitSat                 BatchDCInitSat;
fnPtrBatchDCInitSatObsKeys          BatchDCInitSatObsKeys;
fnPtrBatchDCInitSatObsSel           BatchDCInitSatObsSel;
fnPtrBatchDCSolve                   BatchDCSolve;
fnPtrBatchDCSolveSelObs             BatchDCSolveSelObs;
fnPtrBatchDCRemoveSat               BatchDCRemoveSat;
fnPtrBatchDCIterate                 BatchDCIterate;
fnPtrBatchDCGetVcm                  BatchDCGetVcm;
fnPtrBatchDCGetSpVOut               BatchDCGetSpVOut;
fnPtrBatchDCSetSpVOut               BatchDCSetSpVOut;
fnPtrBatchDCResetAll                BatchDCResetAll;
fnPtrBatchDCGetAccptCrit            BatchDCGetAccptCrit;
fnPtrSpToEGP                        SpToEGP;
fnPtrSpToTle                        SpToTle;
fnPtrSpToTleComb                    SpToTleComb;
fnPtrSpToCsv                        SpToCsv;
fnPtrSpToCsvComb                    SpToCsvComb;
fnPtrExtEphemToEGP                  ExtEphemToEGP;
fnPtrIomodDC                        IomodDC;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadBatchDCDll()
{
   if(hLib != NULL) {
      printf("Warning: %s already loaded.\n", BatchDCDll);
      return;
   }
   // Explicitly load the dll
   hLib = LoadLib(BatchDCDll);


   // Assign function pointers to the appropriate dll functions
   BatchDCInit = (fnPtrBatchDCInit)GetFnPtr(hLib, (char*)"BatchDCInit");
   BatchDCGetInfo = (fnPtrBatchDCGetInfo)GetFnPtr(hLib, (char*)"BatchDCGetInfo");
   BatchDCLoadFile = (fnPtrBatchDCLoadFile)GetFnPtr(hLib, (char*)"BatchDCLoadFile");
   BatchDCLoadFileAll = (fnPtrBatchDCLoadFileAll)GetFnPtr(hLib, (char*)"BatchDCLoadFileAll");
   BatchDCLoadCard = (fnPtrBatchDCLoadCard)GetFnPtr(hLib, (char*)"BatchDCLoadCard");
   BatchDCGetPCard = (fnPtrBatchDCGetPCard)GetFnPtr(hLib, (char*)"BatchDCGetPCard");
   BatchDCSaveFile = (fnPtrBatchDCSaveFile)GetFnPtr(hLib, (char*)"BatchDCSaveFile");
   BatchDCGetParams = (fnPtrBatchDCGetParams)GetFnPtr(hLib, (char*)"BatchDCGetParams");
   BatchDCSetParams = (fnPtrBatchDCSetParams)GetFnPtr(hLib, (char*)"BatchDCSetParams");
   BatchDCGetCtrlArr = (fnPtrBatchDCGetCtrlArr)GetFnPtr(hLib, (char*)"BatchDCGetCtrlArr");
   BatchDCSetCtrlArr = (fnPtrBatchDCSetCtrlArr)GetFnPtr(hLib, (char*)"BatchDCSetCtrlArr");
   BatchDCInitSat = (fnPtrBatchDCInitSat)GetFnPtr(hLib, (char*)"BatchDCInitSat");
   BatchDCInitSatObsKeys = (fnPtrBatchDCInitSatObsKeys)GetFnPtr(hLib, (char*)"BatchDCInitSatObsKeys");
   BatchDCInitSatObsSel = (fnPtrBatchDCInitSatObsSel)GetFnPtr(hLib, (char*)"BatchDCInitSatObsSel");
   BatchDCSolve = (fnPtrBatchDCSolve)GetFnPtr(hLib, (char*)"BatchDCSolve");
   BatchDCSolveSelObs = (fnPtrBatchDCSolveSelObs)GetFnPtr(hLib, (char*)"BatchDCSolveSelObs");
   BatchDCRemoveSat = (fnPtrBatchDCRemoveSat)GetFnPtr(hLib, (char*)"BatchDCRemoveSat");
   BatchDCIterate = (fnPtrBatchDCIterate)GetFnPtr(hLib, (char*)"BatchDCIterate");
   BatchDCGetVcm = (fnPtrBatchDCGetVcm)GetFnPtr(hLib, (char*)"BatchDCGetVcm");
   BatchDCGetSpVOut = (fnPtrBatchDCGetSpVOut)GetFnPtr(hLib, (char*)"BatchDCGetSpVOut");
   BatchDCSetSpVOut = (fnPtrBatchDCSetSpVOut)GetFnPtr(hLib, (char*)"BatchDCSetSpVOut");
   BatchDCResetAll = (fnPtrBatchDCResetAll)GetFnPtr(hLib, (char*)"BatchDCResetAll");
   BatchDCGetAccptCrit = (fnPtrBatchDCGetAccptCrit)GetFnPtr(hLib, (char*)"BatchDCGetAccptCrit");
   SpToEGP = (fnPtrSpToEGP)GetFnPtr(hLib, (char*)"SpToEGP");
   SpToTle = (fnPtrSpToTle)GetFnPtr(hLib, (char*)"SpToTle");
   SpToTleComb = (fnPtrSpToTleComb)GetFnPtr(hLib, (char*)"SpToTleComb");
   SpToCsv = (fnPtrSpToCsv)GetFnPtr(hLib, (char*)"SpToCsv");
   SpToCsvComb = (fnPtrSpToCsvComb)GetFnPtr(hLib, (char*)"SpToCsvComb");
   ExtEphemToEGP = (fnPtrExtEphemToEGP)GetFnPtr(hLib, (char*)"ExtEphemToEGP");
   IomodDC = (fnPtrIomodDC)GetFnPtr(hLib, (char*)"IomodDC");
}



// Free BatchDCDll
void FreeBatchDCDll()
{
   if(hLib == NULL) {
      printf("Warning: %s already freed.\nUse after free averted.\n", BatchDCDll);
      return;
   }
   FreeLib(hLib, BatchDCDll);
   hLib = NULL;
   BatchDCInit = NULL;
   BatchDCGetInfo = NULL;
   BatchDCLoadFile = NULL;
   BatchDCLoadFileAll = NULL;
   BatchDCLoadCard = NULL;
   BatchDCGetPCard = NULL;
   BatchDCSaveFile = NULL;
   BatchDCGetParams = NULL;
   BatchDCSetParams = NULL;
   BatchDCGetCtrlArr = NULL;
   BatchDCSetCtrlArr = NULL;
   BatchDCInitSat = NULL;
   BatchDCInitSatObsKeys = NULL;
   BatchDCInitSatObsSel = NULL;
   BatchDCSolve = NULL;
   BatchDCSolveSelObs = NULL;
   BatchDCRemoveSat = NULL;
   BatchDCIterate = NULL;
   BatchDCGetVcm = NULL;
   BatchDCGetSpVOut = NULL;
   BatchDCSetSpVOut = NULL;
   BatchDCResetAll = NULL;
   BatchDCGetAccptCrit = NULL;
   SpToEGP = NULL;
   SpToTle = NULL;
   SpToTleComb = NULL;
   SpToCsv = NULL;
   SpToCsvComb = NULL;
   ExtEphemToEGP = NULL;
   IomodDC = NULL;
}
// ========================= End of auto generated code ==========================
