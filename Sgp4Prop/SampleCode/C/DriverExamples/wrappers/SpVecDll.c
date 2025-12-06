// This wrapper file was generated automatically by the GenDllWrappers program.

#include "../services/DllUtils.h"
#include "SpVecDll.h"


// SpVecDll's function pointers definition
fnPtrSpVecInit                      SpVecInit;
fnPtrSpVecGetInfo                   SpVecGetInfo;
fnPtrSpVecLoadFile                  SpVecLoadFile;
fnPtrSpVecSaveFile                  SpVecSaveFile;
fnPtrSpVecRemoveSat                 SpVecRemoveSat;
fnPtrSpVecRemoveAllSats             SpVecRemoveAllSats;
fnPtrSpVecGetCount                  SpVecGetCount;
fnPtrSpVecGetLoaded                 SpVecGetLoaded;
fnPtrSpVecAddSatFrLines             SpVecAddSatFrLines;
fnPtrSpVecAddSatFrLinesML           SpVecAddSatFrLinesML;
fnPtrSpVecAddSatFrFields            SpVecAddSatFrFields;
fnPtrSpVecAddSatFrFieldsML          SpVecAddSatFrFieldsML;
fnPtrSpVecUpdateSatFrFields         SpVecUpdateSatFrFields;
fnPtrSpVecGetField                  SpVecGetField;
fnPtrSpVecSetField                  SpVecSetField;
fnPtrSpVecGetAllFields              SpVecGetAllFields;
fnPtrSpVecParse                     SpVecParse;
fnPtrSpVecLinesToArray              SpVecLinesToArray;
fnPtrSpVecGetLines                  SpVecGetLines;
fnPtrSpVecFieldsToLines             SpVecFieldsToLines;
fnPtrSpVecArrayToLines              SpVecArrayToLines;
fnPtrSpVecGetSatKey                 SpVecGetSatKey;
fnPtrSpVecGetSatKeyML               SpVecGetSatKeyML;
fnPtrSpVecFieldsToSatKey            SpVecFieldsToSatKey;
fnPtrSpVecFieldsToSatKeyML          SpVecFieldsToSatKeyML;
fnPtrSpVecAddSatFrArray             SpVecAddSatFrArray;
fnPtrSpVecAddSatFrArrayML           SpVecAddSatFrArrayML;
fnPtrSpVecUpdateSatFrArray          SpVecUpdateSatFrArray;
fnPtrSpVecDataToArray               SpVecDataToArray;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadSpVecDll()
{
   if(hLib != NULL) {
      printf("Warning: %s already loaded.\n", SpVecDll);
      return;
   }
   // Explicitly load the dll
   hLib = LoadLib(SpVecDll);


   // Assign function pointers to the appropriate dll functions
   SpVecInit = (fnPtrSpVecInit)GetFnPtr(hLib, (char*)"SpVecInit");
   SpVecGetInfo = (fnPtrSpVecGetInfo)GetFnPtr(hLib, (char*)"SpVecGetInfo");
   SpVecLoadFile = (fnPtrSpVecLoadFile)GetFnPtr(hLib, (char*)"SpVecLoadFile");
   SpVecSaveFile = (fnPtrSpVecSaveFile)GetFnPtr(hLib, (char*)"SpVecSaveFile");
   SpVecRemoveSat = (fnPtrSpVecRemoveSat)GetFnPtr(hLib, (char*)"SpVecRemoveSat");
   SpVecRemoveAllSats = (fnPtrSpVecRemoveAllSats)GetFnPtr(hLib, (char*)"SpVecRemoveAllSats");
   SpVecGetCount = (fnPtrSpVecGetCount)GetFnPtr(hLib, (char*)"SpVecGetCount");
   SpVecGetLoaded = (fnPtrSpVecGetLoaded)GetFnPtr(hLib, (char*)"SpVecGetLoaded");
   SpVecAddSatFrLines = (fnPtrSpVecAddSatFrLines)GetFnPtr(hLib, (char*)"SpVecAddSatFrLines");
   SpVecAddSatFrLinesML = (fnPtrSpVecAddSatFrLinesML)GetFnPtr(hLib, (char*)"SpVecAddSatFrLinesML");
   SpVecAddSatFrFields = (fnPtrSpVecAddSatFrFields)GetFnPtr(hLib, (char*)"SpVecAddSatFrFields");
   SpVecAddSatFrFieldsML = (fnPtrSpVecAddSatFrFieldsML)GetFnPtr(hLib, (char*)"SpVecAddSatFrFieldsML");
   SpVecUpdateSatFrFields = (fnPtrSpVecUpdateSatFrFields)GetFnPtr(hLib, (char*)"SpVecUpdateSatFrFields");
   SpVecGetField = (fnPtrSpVecGetField)GetFnPtr(hLib, (char*)"SpVecGetField");
   SpVecSetField = (fnPtrSpVecSetField)GetFnPtr(hLib, (char*)"SpVecSetField");
   SpVecGetAllFields = (fnPtrSpVecGetAllFields)GetFnPtr(hLib, (char*)"SpVecGetAllFields");
   SpVecParse = (fnPtrSpVecParse)GetFnPtr(hLib, (char*)"SpVecParse");
   SpVecLinesToArray = (fnPtrSpVecLinesToArray)GetFnPtr(hLib, (char*)"SpVecLinesToArray");
   SpVecGetLines = (fnPtrSpVecGetLines)GetFnPtr(hLib, (char*)"SpVecGetLines");
   SpVecFieldsToLines = (fnPtrSpVecFieldsToLines)GetFnPtr(hLib, (char*)"SpVecFieldsToLines");
   SpVecArrayToLines = (fnPtrSpVecArrayToLines)GetFnPtr(hLib, (char*)"SpVecArrayToLines");
   SpVecGetSatKey = (fnPtrSpVecGetSatKey)GetFnPtr(hLib, (char*)"SpVecGetSatKey");
   SpVecGetSatKeyML = (fnPtrSpVecGetSatKeyML)GetFnPtr(hLib, (char*)"SpVecGetSatKeyML");
   SpVecFieldsToSatKey = (fnPtrSpVecFieldsToSatKey)GetFnPtr(hLib, (char*)"SpVecFieldsToSatKey");
   SpVecFieldsToSatKeyML = (fnPtrSpVecFieldsToSatKeyML)GetFnPtr(hLib, (char*)"SpVecFieldsToSatKeyML");
   SpVecAddSatFrArray = (fnPtrSpVecAddSatFrArray)GetFnPtr(hLib, (char*)"SpVecAddSatFrArray");
   SpVecAddSatFrArrayML = (fnPtrSpVecAddSatFrArrayML)GetFnPtr(hLib, (char*)"SpVecAddSatFrArrayML");
   SpVecUpdateSatFrArray = (fnPtrSpVecUpdateSatFrArray)GetFnPtr(hLib, (char*)"SpVecUpdateSatFrArray");
   SpVecDataToArray = (fnPtrSpVecDataToArray)GetFnPtr(hLib, (char*)"SpVecDataToArray");
}



// Free SpVecDll
void FreeSpVecDll()
{
   if(hLib == NULL) {
      printf("Warning: %s already freed.\nUse after free averted.\n", SpVecDll);
      return;
   }
   FreeLib(hLib, SpVecDll);
   hLib = NULL;
   SpVecInit = NULL;
   SpVecGetInfo = NULL;
   SpVecLoadFile = NULL;
   SpVecSaveFile = NULL;
   SpVecRemoveSat = NULL;
   SpVecRemoveAllSats = NULL;
   SpVecGetCount = NULL;
   SpVecGetLoaded = NULL;
   SpVecAddSatFrLines = NULL;
   SpVecAddSatFrLinesML = NULL;
   SpVecAddSatFrFields = NULL;
   SpVecAddSatFrFieldsML = NULL;
   SpVecUpdateSatFrFields = NULL;
   SpVecGetField = NULL;
   SpVecSetField = NULL;
   SpVecGetAllFields = NULL;
   SpVecParse = NULL;
   SpVecLinesToArray = NULL;
   SpVecGetLines = NULL;
   SpVecFieldsToLines = NULL;
   SpVecArrayToLines = NULL;
   SpVecGetSatKey = NULL;
   SpVecGetSatKeyML = NULL;
   SpVecFieldsToSatKey = NULL;
   SpVecFieldsToSatKeyML = NULL;
   SpVecAddSatFrArray = NULL;
   SpVecAddSatFrArrayML = NULL;
   SpVecUpdateSatFrArray = NULL;
   SpVecDataToArray = NULL;
}
// ========================= End of auto generated code ==========================
