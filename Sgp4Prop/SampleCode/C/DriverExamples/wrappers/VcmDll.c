// This wrapper file was generated automatically by the GenDllWrappers program.

#include "../services/DllUtils.h"
#include "VcmDll.h"


// VcmDll's function pointers definition
fnPtrVcmInit                        VcmInit;
fnPtrVcmGetInfo                     VcmGetInfo;
fnPtrVcmLoadFile                    VcmLoadFile;
fnPtrVcmSaveFile                    VcmSaveFile;
fnPtrVcmRemoveSat                   VcmRemoveSat;
fnPtrVcmRemoveAllSats               VcmRemoveAllSats;
fnPtrVcmGetCount                    VcmGetCount;
fnPtrVcmGetLoaded                   VcmGetLoaded;
fnPtrVcmAddSatFrLines               VcmAddSatFrLines;
fnPtrVcmAddSatFrLinesML             VcmAddSatFrLinesML;
fnPtrVcmAddSatFrFields              VcmAddSatFrFields;
fnPtrVcmAddSatFrFieldsML            VcmAddSatFrFieldsML;
fnPtrVcmRetrieveAllData             VcmRetrieveAllData;
fnPtrVcmUpdateSatFrFields           VcmUpdateSatFrFields;
fnPtrVcmGetField                    VcmGetField;
fnPtrVcmSetField                    VcmSetField;
fnPtrVcmGetAllFields                VcmGetAllFields;
fnPtrVcmGetLines                    VcmGetLines;
fnPtrVcm1LineToMultiLine            Vcm1LineToMultiLine;
fnPtrVcmMultiLineTo1Line            VcmMultiLineTo1Line;
fnPtrVcmGetSatKey                   VcmGetSatKey;
fnPtrVcmGetSatKeyML                 VcmGetSatKeyML;
fnPtrVcmFieldsToSatKey              VcmFieldsToSatKey;
fnPtrVcmFieldsToSatKeyML            VcmFieldsToSatKeyML;
fnPtrVcmArrayToVcmLines             VcmArrayToVcmLines;
fnPtrVcmArrayToVcm1Line             VcmArrayToVcm1Line;
fnPtrVcmStringToArray               VcmStringToArray;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadVcmDll()
{
   if(hLib != NULL) {
      printf("Warning: %s already loaded.\n", VcmDll);
      return;
   }
   // Explicitly load the dll
   hLib = LoadLib(VcmDll);


   // Assign function pointers to the appropriate dll functions
   VcmInit = (fnPtrVcmInit)GetFnPtr(hLib, (char*)"VcmInit");
   VcmGetInfo = (fnPtrVcmGetInfo)GetFnPtr(hLib, (char*)"VcmGetInfo");
   VcmLoadFile = (fnPtrVcmLoadFile)GetFnPtr(hLib, (char*)"VcmLoadFile");
   VcmSaveFile = (fnPtrVcmSaveFile)GetFnPtr(hLib, (char*)"VcmSaveFile");
   VcmRemoveSat = (fnPtrVcmRemoveSat)GetFnPtr(hLib, (char*)"VcmRemoveSat");
   VcmRemoveAllSats = (fnPtrVcmRemoveAllSats)GetFnPtr(hLib, (char*)"VcmRemoveAllSats");
   VcmGetCount = (fnPtrVcmGetCount)GetFnPtr(hLib, (char*)"VcmGetCount");
   VcmGetLoaded = (fnPtrVcmGetLoaded)GetFnPtr(hLib, (char*)"VcmGetLoaded");
   VcmAddSatFrLines = (fnPtrVcmAddSatFrLines)GetFnPtr(hLib, (char*)"VcmAddSatFrLines");
   VcmAddSatFrLinesML = (fnPtrVcmAddSatFrLinesML)GetFnPtr(hLib, (char*)"VcmAddSatFrLinesML");
   VcmAddSatFrFields = (fnPtrVcmAddSatFrFields)GetFnPtr(hLib, (char*)"VcmAddSatFrFields");
   VcmAddSatFrFieldsML = (fnPtrVcmAddSatFrFieldsML)GetFnPtr(hLib, (char*)"VcmAddSatFrFieldsML");
   VcmRetrieveAllData = (fnPtrVcmRetrieveAllData)GetFnPtr(hLib, (char*)"VcmRetrieveAllData");
   VcmUpdateSatFrFields = (fnPtrVcmUpdateSatFrFields)GetFnPtr(hLib, (char*)"VcmUpdateSatFrFields");
   VcmGetField = (fnPtrVcmGetField)GetFnPtr(hLib, (char*)"VcmGetField");
   VcmSetField = (fnPtrVcmSetField)GetFnPtr(hLib, (char*)"VcmSetField");
   VcmGetAllFields = (fnPtrVcmGetAllFields)GetFnPtr(hLib, (char*)"VcmGetAllFields");
   VcmGetLines = (fnPtrVcmGetLines)GetFnPtr(hLib, (char*)"VcmGetLines");
   Vcm1LineToMultiLine = (fnPtrVcm1LineToMultiLine)GetFnPtr(hLib, (char*)"Vcm1LineToMultiLine");
   VcmMultiLineTo1Line = (fnPtrVcmMultiLineTo1Line)GetFnPtr(hLib, (char*)"VcmMultiLineTo1Line");
   VcmGetSatKey = (fnPtrVcmGetSatKey)GetFnPtr(hLib, (char*)"VcmGetSatKey");
   VcmGetSatKeyML = (fnPtrVcmGetSatKeyML)GetFnPtr(hLib, (char*)"VcmGetSatKeyML");
   VcmFieldsToSatKey = (fnPtrVcmFieldsToSatKey)GetFnPtr(hLib, (char*)"VcmFieldsToSatKey");
   VcmFieldsToSatKeyML = (fnPtrVcmFieldsToSatKeyML)GetFnPtr(hLib, (char*)"VcmFieldsToSatKeyML");
   VcmArrayToVcmLines = (fnPtrVcmArrayToVcmLines)GetFnPtr(hLib, (char*)"VcmArrayToVcmLines");
   VcmArrayToVcm1Line = (fnPtrVcmArrayToVcm1Line)GetFnPtr(hLib, (char*)"VcmArrayToVcm1Line");
   VcmStringToArray = (fnPtrVcmStringToArray)GetFnPtr(hLib, (char*)"VcmStringToArray");
}



// Free VcmDll
void FreeVcmDll()
{
   if(hLib == NULL) {
      printf("Warning: %s already freed.\nUse after free averted.\n", VcmDll);
      return;
   }
   FreeLib(hLib, VcmDll);
   hLib = NULL;
   VcmInit = NULL;
   VcmGetInfo = NULL;
   VcmLoadFile = NULL;
   VcmSaveFile = NULL;
   VcmRemoveSat = NULL;
   VcmRemoveAllSats = NULL;
   VcmGetCount = NULL;
   VcmGetLoaded = NULL;
   VcmAddSatFrLines = NULL;
   VcmAddSatFrLinesML = NULL;
   VcmAddSatFrFields = NULL;
   VcmAddSatFrFieldsML = NULL;
   VcmRetrieveAllData = NULL;
   VcmUpdateSatFrFields = NULL;
   VcmGetField = NULL;
   VcmSetField = NULL;
   VcmGetAllFields = NULL;
   VcmGetLines = NULL;
   Vcm1LineToMultiLine = NULL;
   VcmMultiLineTo1Line = NULL;
   VcmGetSatKey = NULL;
   VcmGetSatKeyML = NULL;
   VcmFieldsToSatKey = NULL;
   VcmFieldsToSatKeyML = NULL;
   VcmArrayToVcmLines = NULL;
   VcmArrayToVcm1Line = NULL;
   VcmStringToArray = NULL;
}
// ========================= End of auto generated code ==========================
