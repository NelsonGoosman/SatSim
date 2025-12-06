// This wrapper file was generated automatically by the GenDllWrappers program.

#include "../services/DllUtils.h"
#include "ComboDll.h"


// ComboDll's function pointers definition
fnPtrComboInit                      ComboInit;
fnPtrComboGetInfo                   ComboGetInfo;
fnPtrComboLoadFile                  ComboLoadFile;
fnPtrComboLoadFileAll               ComboLoadFileAll;
fnPtrComboLoadCard                  ComboLoadCard;
fnPtrComboSaveFile                  ComboSaveFile;
fnPtrComboGetNumOfPriSecSats        ComboGetNumOfPriSecSats;
fnPtrComboGetPriSatNums             ComboGetPriSatNums;
fnPtrComboGetSecSatNums             ComboGetSecSatNums;
fnPtrComboGet7pCard                 ComboGet7pCard;
fnPtrComboGet7pAll                  ComboGet7pAll;
fnPtrComboSet7pAll                  ComboSet7pAll;
fnPtrComboGet7pField                ComboGet7pField;
fnPtrComboSet7pField                ComboSet7pField;
fnPtrComboCompPriSec                ComboCompPriSec;
fnPtrComboCompPriSec_MT             ComboCompPriSec_MT;
fnPtrComboPOC                       ComboPOC;
fnPtrComboCSMPOC                    ComboCSMPOC;


static void* hLib = NULL; // handle to the dll

// Load and assign function pointers
void LoadComboDll()
{
   if(hLib != NULL) {
      printf("Warning: %s already loaded.\n", ComboDll);
      return;
   }
   // Explicitly load the dll
   hLib = LoadLib(ComboDll);


   // Assign function pointers to the appropriate dll functions
   ComboInit = (fnPtrComboInit)GetFnPtr(hLib, (char*)"ComboInit");
   ComboGetInfo = (fnPtrComboGetInfo)GetFnPtr(hLib, (char*)"ComboGetInfo");
   ComboLoadFile = (fnPtrComboLoadFile)GetFnPtr(hLib, (char*)"ComboLoadFile");
   ComboLoadFileAll = (fnPtrComboLoadFileAll)GetFnPtr(hLib, (char*)"ComboLoadFileAll");
   ComboLoadCard = (fnPtrComboLoadCard)GetFnPtr(hLib, (char*)"ComboLoadCard");
   ComboSaveFile = (fnPtrComboSaveFile)GetFnPtr(hLib, (char*)"ComboSaveFile");
   ComboGetNumOfPriSecSats = (fnPtrComboGetNumOfPriSecSats)GetFnPtr(hLib, (char*)"ComboGetNumOfPriSecSats");
   ComboGetPriSatNums = (fnPtrComboGetPriSatNums)GetFnPtr(hLib, (char*)"ComboGetPriSatNums");
   ComboGetSecSatNums = (fnPtrComboGetSecSatNums)GetFnPtr(hLib, (char*)"ComboGetSecSatNums");
   ComboGet7pCard = (fnPtrComboGet7pCard)GetFnPtr(hLib, (char*)"ComboGet7pCard");
   ComboGet7pAll = (fnPtrComboGet7pAll)GetFnPtr(hLib, (char*)"ComboGet7pAll");
   ComboSet7pAll = (fnPtrComboSet7pAll)GetFnPtr(hLib, (char*)"ComboSet7pAll");
   ComboGet7pField = (fnPtrComboGet7pField)GetFnPtr(hLib, (char*)"ComboGet7pField");
   ComboSet7pField = (fnPtrComboSet7pField)GetFnPtr(hLib, (char*)"ComboSet7pField");
   ComboCompPriSec = (fnPtrComboCompPriSec)GetFnPtr(hLib, (char*)"ComboCompPriSec");
   ComboCompPriSec_MT = (fnPtrComboCompPriSec_MT)GetFnPtr(hLib, (char*)"ComboCompPriSec_MT");
   ComboPOC = (fnPtrComboPOC)GetFnPtr(hLib, (char*)"ComboPOC");
   ComboCSMPOC = (fnPtrComboCSMPOC)GetFnPtr(hLib, (char*)"ComboCSMPOC");
}



// Free ComboDll
void FreeComboDll()
{
   if(hLib == NULL) {
      printf("Warning: %s already freed.\nUse after free averted.\n", ComboDll);
      return;
   }
   FreeLib(hLib, ComboDll);
   hLib = NULL;
   ComboInit = NULL;
   ComboGetInfo = NULL;
   ComboLoadFile = NULL;
   ComboLoadFileAll = NULL;
   ComboLoadCard = NULL;
   ComboSaveFile = NULL;
   ComboGetNumOfPriSecSats = NULL;
   ComboGetPriSatNums = NULL;
   ComboGetSecSatNums = NULL;
   ComboGet7pCard = NULL;
   ComboGet7pAll = NULL;
   ComboSet7pAll = NULL;
   ComboGet7pField = NULL;
   ComboSet7pField = NULL;
   ComboCompPriSec = NULL;
   ComboCompPriSec_MT = NULL;
   ComboPOC = NULL;
   ComboCSMPOC = NULL;
}
// ========================= End of auto generated code ==========================
