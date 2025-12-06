// This wrapper file was generated automatically by the GenDllWrappers program.

#include "../services/DllUtils.h"
#include "BamDll.h"


// BamDll's function pointers definition
fnPtrBamInit                        BamInit;
fnPtrBamGetInfo                     BamGetInfo;
fnPtrBamCompNumTSs                  BamCompNumTSs;
fnPtrBamCompute                     BamCompute;
fnPtrBamGetResults                  BamGetResults;
fnPtrBamGetResultsFull              BamGetResultsFull;
fnPtrBamComputeAll                  BamComputeAll;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadBamDll()
{
   if(hLib != NULL) {
      printf("Warning: %s already loaded.\n", BamDll);
      return;
   }
   // Explicitly load the dll
   hLib = LoadLib(BamDll);


   // Assign function pointers to the appropriate dll functions
   BamInit = (fnPtrBamInit)GetFnPtr(hLib, (char*)"BamInit");
   BamGetInfo = (fnPtrBamGetInfo)GetFnPtr(hLib, (char*)"BamGetInfo");
   BamCompNumTSs = (fnPtrBamCompNumTSs)GetFnPtr(hLib, (char*)"BamCompNumTSs");
   BamCompute = (fnPtrBamCompute)GetFnPtr(hLib, (char*)"BamCompute");
   BamGetResults = (fnPtrBamGetResults)GetFnPtr(hLib, (char*)"BamGetResults");
   BamGetResultsFull = (fnPtrBamGetResultsFull)GetFnPtr(hLib, (char*)"BamGetResultsFull");
   BamComputeAll = (fnPtrBamComputeAll)GetFnPtr(hLib, (char*)"BamComputeAll");
}



// Free BamDll
void FreeBamDll()
{
   if(hLib == NULL) {
      printf("Warning: %s already freed.\nUse after free averted.\n", BamDll);
      return;
   }
   FreeLib(hLib, BamDll);
   hLib = NULL;
   BamInit = NULL;
   BamGetInfo = NULL;
   BamCompNumTSs = NULL;
   BamCompute = NULL;
   BamGetResults = NULL;
   BamGetResultsFull = NULL;
   BamComputeAll = NULL;
}
// ========================= End of auto generated code ==========================
