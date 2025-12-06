// This wrapper file was generated automatically by the GenDllWrappers program.

#include "../services/DllUtils.h"
#include "FovDll.h"


// FovDll's function pointers definition
fnPtrFovInit                        FovInit;
fnPtrFovGetInfo                     FovGetInfo;
fnPtrFovLoadFile                    FovLoadFile;
fnPtrFovLoadFileAll                 FovLoadFileAll;
fnPtrFovLoadCard                    FovLoadCard;
fnPtrFovSaveFile                    FovSaveFile;
fnPtrFovGetDataFrInputFiles         FovGetDataFrInputFiles;
fnPtrFovFindTargetPasses            FovFindTargetPasses;
fnPtrFovTargetElset                 FovTargetElset;
fnPtrFovTargetElsetLook             FovTargetElsetLook;
fnPtrFovTargetElsetLookView         FovTargetElsetLookView;
fnPtrFovTargetVec                   FovTargetVec;
fnPtrFovTargetVecLook               FovTargetVecLook;
fnPtrFovTargetVecLookView           FovTargetVecLookView;
fnPtrFovReset                       FovReset;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadFovDll()
{
   if(hLib != NULL) {
      printf("Warning: %s already loaded.\n", FovDll);
      return;
   }
   // Explicitly load the dll
   hLib = LoadLib(FovDll);


   // Assign function pointers to the appropriate dll functions
   FovInit = (fnPtrFovInit)GetFnPtr(hLib, (char*)"FovInit");
   FovGetInfo = (fnPtrFovGetInfo)GetFnPtr(hLib, (char*)"FovGetInfo");
   FovLoadFile = (fnPtrFovLoadFile)GetFnPtr(hLib, (char*)"FovLoadFile");
   FovLoadFileAll = (fnPtrFovLoadFileAll)GetFnPtr(hLib, (char*)"FovLoadFileAll");
   FovLoadCard = (fnPtrFovLoadCard)GetFnPtr(hLib, (char*)"FovLoadCard");
   FovSaveFile = (fnPtrFovSaveFile)GetFnPtr(hLib, (char*)"FovSaveFile");
   FovGetDataFrInputFiles = (fnPtrFovGetDataFrInputFiles)GetFnPtr(hLib, (char*)"FovGetDataFrInputFiles");
   FovFindTargetPasses = (fnPtrFovFindTargetPasses)GetFnPtr(hLib, (char*)"FovFindTargetPasses");
   FovTargetElset = (fnPtrFovTargetElset)GetFnPtr(hLib, (char*)"FovTargetElset");
   FovTargetElsetLook = (fnPtrFovTargetElsetLook)GetFnPtr(hLib, (char*)"FovTargetElsetLook");
   FovTargetElsetLookView = (fnPtrFovTargetElsetLookView)GetFnPtr(hLib, (char*)"FovTargetElsetLookView");
   FovTargetVec = (fnPtrFovTargetVec)GetFnPtr(hLib, (char*)"FovTargetVec");
   FovTargetVecLook = (fnPtrFovTargetVecLook)GetFnPtr(hLib, (char*)"FovTargetVecLook");
   FovTargetVecLookView = (fnPtrFovTargetVecLookView)GetFnPtr(hLib, (char*)"FovTargetVecLookView");
   FovReset = (fnPtrFovReset)GetFnPtr(hLib, (char*)"FovReset");
}



// Free FovDll
void FreeFovDll()
{
   if(hLib == NULL) {
      printf("Warning: %s already freed.\nUse after free averted.\n", FovDll);
      return;
   }
   FreeLib(hLib, FovDll);
   hLib = NULL;
   FovInit = NULL;
   FovGetInfo = NULL;
   FovLoadFile = NULL;
   FovLoadFileAll = NULL;
   FovLoadCard = NULL;
   FovSaveFile = NULL;
   FovGetDataFrInputFiles = NULL;
   FovFindTargetPasses = NULL;
   FovTargetElset = NULL;
   FovTargetElsetLook = NULL;
   FovTargetElsetLookView = NULL;
   FovTargetVec = NULL;
   FovTargetVecLook = NULL;
   FovTargetVecLookView = NULL;
   FovReset = NULL;
}
// ========================= End of auto generated code ==========================
