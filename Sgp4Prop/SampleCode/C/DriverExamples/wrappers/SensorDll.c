// This wrapper file was generated automatically by the GenDllWrappers program.

#include "../services/DllUtils.h"
#include "SensorDll.h"


// SensorDll's function pointers definition
fnPtrSensorInit                     SensorInit;
fnPtrSensorGetInfo                  SensorGetInfo;
fnPtrSensorLoadFile                 SensorLoadFile;
fnPtrSensorLoadCard                 SensorLoadCard;
fnPtrSensorSaveFile                 SensorSaveFile;
fnPtrSensorRemove                   SensorRemove;
fnPtrSensorRemoveAll                SensorRemoveAll;
fnPtrSensorGetCount                 SensorGetCount;
fnPtrSensorGetLoaded                SensorGetLoaded;
fnPtrSensorGetLocAll                SensorGetLocAll;
fnPtrSensorSetLocAll                SensorSetLocAll;
fnPtrSensorGetLocField              SensorGetLocField;
fnPtrSensorSetLocField              SensorSetLocField;
fnPtrSensorGet1L                    SensorGet1L;
fnPtrSensorSet1L                    SensorSet1L;
fnPtrSensorGet2L                    SensorGet2L;
fnPtrSensorSet2L                    SensorSet2L;
fnPtrSensorGetLimField              SensorGetLimField;
fnPtrSensorSetLimField              SensorSetLimField;
fnPtrSensorGetBS                    SensorGetBS;
fnPtrSensorSetBS                    SensorSetBS;
fnPtrSensorGetBSField               SensorGetBSField;
fnPtrSensorSetBSField               SensorSetBSField;
fnPtrSensorGetLines                 SensorGetLines;
fnPtrSensorGetBSLine                SensorGetBSLine;
fnPtrSensorGetOrbSatKey             SensorGetOrbSatKey;
fnPtrSensorSetOrbSatKey             SensorSetOrbSatKey;
fnPtrSensorLoadAzElTable            SensorLoadAzElTable;
fnPtrSensorAddSegment               SensorAddSegment;
fnPtrSensorGetSegment               SensorGetSegment;
fnPtrSetSenKeyMode                  SetSenKeyMode;
fnPtrGetSenKeyMode                  GetSenKeyMode;
fnPtrSenNumOf                       SenNumOf;
fnPtrSensorGetSenKey                SensorGetSenKey;
fnPtrSensorGetSenKeyML              SensorGetSenKeyML;
fnPtrSensorAddFrArray               SensorAddFrArray;
fnPtrSensorDataToArray              SensorDataToArray;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadSensorDll()
{
   if(hLib != NULL) {
      printf("Warning: %s already loaded.\n", SensorDll);
      return;
   }
   // Explicitly load the dll
   hLib = LoadLib(SensorDll);


   // Assign function pointers to the appropriate dll functions
   SensorInit = (fnPtrSensorInit)GetFnPtr(hLib, (char*)"SensorInit");
   SensorGetInfo = (fnPtrSensorGetInfo)GetFnPtr(hLib, (char*)"SensorGetInfo");
   SensorLoadFile = (fnPtrSensorLoadFile)GetFnPtr(hLib, (char*)"SensorLoadFile");
   SensorLoadCard = (fnPtrSensorLoadCard)GetFnPtr(hLib, (char*)"SensorLoadCard");
   SensorSaveFile = (fnPtrSensorSaveFile)GetFnPtr(hLib, (char*)"SensorSaveFile");
   SensorRemove = (fnPtrSensorRemove)GetFnPtr(hLib, (char*)"SensorRemove");
   SensorRemoveAll = (fnPtrSensorRemoveAll)GetFnPtr(hLib, (char*)"SensorRemoveAll");
   SensorGetCount = (fnPtrSensorGetCount)GetFnPtr(hLib, (char*)"SensorGetCount");
   SensorGetLoaded = (fnPtrSensorGetLoaded)GetFnPtr(hLib, (char*)"SensorGetLoaded");
   SensorGetLocAll = (fnPtrSensorGetLocAll)GetFnPtr(hLib, (char*)"SensorGetLocAll");
   SensorSetLocAll = (fnPtrSensorSetLocAll)GetFnPtr(hLib, (char*)"SensorSetLocAll");
   SensorGetLocField = (fnPtrSensorGetLocField)GetFnPtr(hLib, (char*)"SensorGetLocField");
   SensorSetLocField = (fnPtrSensorSetLocField)GetFnPtr(hLib, (char*)"SensorSetLocField");
   SensorGet1L = (fnPtrSensorGet1L)GetFnPtr(hLib, (char*)"SensorGet1L");
   SensorSet1L = (fnPtrSensorSet1L)GetFnPtr(hLib, (char*)"SensorSet1L");
   SensorGet2L = (fnPtrSensorGet2L)GetFnPtr(hLib, (char*)"SensorGet2L");
   SensorSet2L = (fnPtrSensorSet2L)GetFnPtr(hLib, (char*)"SensorSet2L");
   SensorGetLimField = (fnPtrSensorGetLimField)GetFnPtr(hLib, (char*)"SensorGetLimField");
   SensorSetLimField = (fnPtrSensorSetLimField)GetFnPtr(hLib, (char*)"SensorSetLimField");
   SensorGetBS = (fnPtrSensorGetBS)GetFnPtr(hLib, (char*)"SensorGetBS");
   SensorSetBS = (fnPtrSensorSetBS)GetFnPtr(hLib, (char*)"SensorSetBS");
   SensorGetBSField = (fnPtrSensorGetBSField)GetFnPtr(hLib, (char*)"SensorGetBSField");
   SensorSetBSField = (fnPtrSensorSetBSField)GetFnPtr(hLib, (char*)"SensorSetBSField");
   SensorGetLines = (fnPtrSensorGetLines)GetFnPtr(hLib, (char*)"SensorGetLines");
   SensorGetBSLine = (fnPtrSensorGetBSLine)GetFnPtr(hLib, (char*)"SensorGetBSLine");
   SensorGetOrbSatKey = (fnPtrSensorGetOrbSatKey)GetFnPtr(hLib, (char*)"SensorGetOrbSatKey");
   SensorSetOrbSatKey = (fnPtrSensorSetOrbSatKey)GetFnPtr(hLib, (char*)"SensorSetOrbSatKey");
   SensorLoadAzElTable = (fnPtrSensorLoadAzElTable)GetFnPtr(hLib, (char*)"SensorLoadAzElTable");
   SensorAddSegment = (fnPtrSensorAddSegment)GetFnPtr(hLib, (char*)"SensorAddSegment");
   SensorGetSegment = (fnPtrSensorGetSegment)GetFnPtr(hLib, (char*)"SensorGetSegment");
   SetSenKeyMode = (fnPtrSetSenKeyMode)GetFnPtr(hLib, (char*)"SetSenKeyMode");
   GetSenKeyMode = (fnPtrGetSenKeyMode)GetFnPtr(hLib, (char*)"GetSenKeyMode");
   SenNumOf = (fnPtrSenNumOf)GetFnPtr(hLib, (char*)"SenNumOf");
   SensorGetSenKey = (fnPtrSensorGetSenKey)GetFnPtr(hLib, (char*)"SensorGetSenKey");
   SensorGetSenKeyML = (fnPtrSensorGetSenKeyML)GetFnPtr(hLib, (char*)"SensorGetSenKeyML");
   SensorAddFrArray = (fnPtrSensorAddFrArray)GetFnPtr(hLib, (char*)"SensorAddFrArray");
   SensorDataToArray = (fnPtrSensorDataToArray)GetFnPtr(hLib, (char*)"SensorDataToArray");
}



// Free SensorDll
void FreeSensorDll()
{
   if(hLib == NULL) {
      printf("Warning: %s already freed.\nUse after free averted.\n", SensorDll);
      return;
   }
   FreeLib(hLib, SensorDll);
   hLib = NULL;
   SensorInit = NULL;
   SensorGetInfo = NULL;
   SensorLoadFile = NULL;
   SensorLoadCard = NULL;
   SensorSaveFile = NULL;
   SensorRemove = NULL;
   SensorRemoveAll = NULL;
   SensorGetCount = NULL;
   SensorGetLoaded = NULL;
   SensorGetLocAll = NULL;
   SensorSetLocAll = NULL;
   SensorGetLocField = NULL;
   SensorSetLocField = NULL;
   SensorGet1L = NULL;
   SensorSet1L = NULL;
   SensorGet2L = NULL;
   SensorSet2L = NULL;
   SensorGetLimField = NULL;
   SensorSetLimField = NULL;
   SensorGetBS = NULL;
   SensorSetBS = NULL;
   SensorGetBSField = NULL;
   SensorSetBSField = NULL;
   SensorGetLines = NULL;
   SensorGetBSLine = NULL;
   SensorGetOrbSatKey = NULL;
   SensorSetOrbSatKey = NULL;
   SensorLoadAzElTable = NULL;
   SensorAddSegment = NULL;
   SensorGetSegment = NULL;
   SetSenKeyMode = NULL;
   GetSenKeyMode = NULL;
   SenNumOf = NULL;
   SensorGetSenKey = NULL;
   SensorGetSenKeyML = NULL;
   SensorAddFrArray = NULL;
   SensorDataToArray = NULL;
}
// ========================= End of auto generated code ==========================
