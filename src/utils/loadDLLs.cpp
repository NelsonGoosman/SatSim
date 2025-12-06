#include "loadDLLs.h"

namespace utils {
// Load all the dlls being used in the program
void LoadAstroStdDlls()
{
   // Load MainDll dll
   LoadDllMainDll();

   // Load EnvConst dll and assign function pointers
   LoadEnvConstDll();

   // Load TimeFunc dll and assign function pointers
   LoadTimeFuncDll();

   // Load AstroFunc dll and assign function pointers
   LoadAstroFuncDll();

   // Load TLE dll and assign function pointers
   LoadTleDll();

   // Load Sgp4Prop dll and assign function pointers
   LoadSgp4PropDll();
}


// Free all the dlls being used in the program
void FreeAstroStdDlls()
{
   // Free MainDll dll
   FreeDllMainDll();

   // Free EnvConst dll
   FreeEnvConstDll();

   // Free AstroFunc dll
   FreeAstroFuncDll();

   // Free TimeFunc dll
   FreeTimeFuncDll();

   // Free TLE dll
   FreeTleDll();

   // Free Sgp4Prop dll
   FreeSgp4PropDll();
}

} // namespace utils