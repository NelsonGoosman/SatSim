// This wrapper file was generated automatically by the GenDllWrappers program.

#include "../services/DllUtils.h"
#include "AofDll.h"


// AofDll's function pointers definition
fnPtrAofInit                        AofInit;
fnPtrAofGetInfo                     AofGetInfo;
fnPtrAofLoadFile                    AofLoadFile;
fnPtrAofLoadFileAll                 AofLoadFileAll;
fnPtrAofLoadCard                    AofLoadCard;
fnPtrAofGetDataFrInputFiles         AofGetDataFrInputFiles;
fnPtrAofReset                       AofReset;
fnPtrAofBasic                       AofBasic;
fnPtrAofComplex                     AofComplex;
fnPtrAofGetLook                     AofGetLook;
fnPtrAofGetView                     AofGetView;
fnPtrAofGetDarknessLevel            AofGetDarknessLevel;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadAofDll()
{
   if(hLib != NULL) {
      printf("Warning: %s already loaded.\n", AofDll);
      return;
   }
   // Explicitly load the dll
   hLib = LoadLib(AofDll);


   // Assign function pointers to the appropriate dll functions
   AofInit = (fnPtrAofInit)GetFnPtr(hLib, (char*)"AofInit");
   AofGetInfo = (fnPtrAofGetInfo)GetFnPtr(hLib, (char*)"AofGetInfo");
   AofLoadFile = (fnPtrAofLoadFile)GetFnPtr(hLib, (char*)"AofLoadFile");
   AofLoadFileAll = (fnPtrAofLoadFileAll)GetFnPtr(hLib, (char*)"AofLoadFileAll");
   AofLoadCard = (fnPtrAofLoadCard)GetFnPtr(hLib, (char*)"AofLoadCard");
   AofGetDataFrInputFiles = (fnPtrAofGetDataFrInputFiles)GetFnPtr(hLib, (char*)"AofGetDataFrInputFiles");
   AofReset = (fnPtrAofReset)GetFnPtr(hLib, (char*)"AofReset");
   AofBasic = (fnPtrAofBasic)GetFnPtr(hLib, (char*)"AofBasic");
   AofComplex = (fnPtrAofComplex)GetFnPtr(hLib, (char*)"AofComplex");
   AofGetLook = (fnPtrAofGetLook)GetFnPtr(hLib, (char*)"AofGetLook");
   AofGetView = (fnPtrAofGetView)GetFnPtr(hLib, (char*)"AofGetView");
   AofGetDarknessLevel = (fnPtrAofGetDarknessLevel)GetFnPtr(hLib, (char*)"AofGetDarknessLevel");
}



// Free AofDll
void FreeAofDll()
{
   if(hLib == NULL) {
      printf("Warning: %s already freed.\nUse after free averted.\n", AofDll);
      return;
   }
   FreeLib(hLib, AofDll);
   hLib = NULL;
   AofInit = NULL;
   AofGetInfo = NULL;
   AofLoadFile = NULL;
   AofLoadFileAll = NULL;
   AofLoadCard = NULL;
   AofGetDataFrInputFiles = NULL;
   AofReset = NULL;
   AofBasic = NULL;
   AofComplex = NULL;
   AofGetLook = NULL;
   AofGetView = NULL;
   AofGetDarknessLevel = NULL;
}
// ========================= End of auto generated code ==========================
