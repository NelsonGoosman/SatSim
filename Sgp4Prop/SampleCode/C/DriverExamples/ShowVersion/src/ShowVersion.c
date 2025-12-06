#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char missingLibList[256];

// Compiler directive that allows C++ code to use the C header files
// Begin
#ifdef __cplusplus
extern "C" 
{
#endif

#ifdef WIN32
   const char PATH_DELIMITER = ';';
   const char* ENV_VAR_TO_CHECK = "PATH";
   const char DIRECTORY_SEPARATOR = '\\';
   const char* LIBRARY_FILENAME = "DllMain.dll";
#elif defined(__APPLE__)
   const char PATH_DELIMITER = ':';
   const char* ENV_VAR_TO_CHECK = "LD_LIBRARY_PATH";
   const char DIRECTORY_SEPARATOR = '/';
   const char* LIBRARY_FILENAME = "libdllmain.dylib";
#else
   const char PATH_DELIMITER = ':';
   const char* ENV_VAR_TO_CHECK = "LD_LIBRARY_PATH";
   const char DIRECTORY_SEPARATOR = '/';
   const char* LIBRARY_FILENAME = "libdllmain.so";
#endif

#include "../../wrappers/AofDll.h"
#include "../../wrappers/AstroFuncDll.h"
#include "../../wrappers/BamDll.h"
#include "../../wrappers/BatchDCDll.h"
#include "../../wrappers/ComboDll.h"
#include "../../wrappers/DllMainDll.h"
#include "../../wrappers/ElCompDll.h"
#include "../../wrappers/ElOpsDll.h"
#include "../../wrappers/EnvConstDll.h"
#include "../../wrappers/ExtEphemDll.h"
#include "../../wrappers/FovDll.h"
#include "../../wrappers/LamodDll.h"
#include "../../wrappers/ObsDll.h"
#include "../../wrappers/ObsOpsDll.h"
#include "../../wrappers/RotasDll.h"
#include "../../wrappers/SaasDll.h"
#include "../../wrappers/SatStateDll.h"
#include "../../wrappers/SensorDll.h"
#include "../../wrappers/Sgp4PropDll.h"
#include "../../wrappers/SpPropDll.h"
#include "../../wrappers/SpVecDll.h"
#include "../../wrappers/TimeFuncDll.h"
#include "../../wrappers/TleDll.h"
#include "../../wrappers/VcmDll.h"

// End
#ifdef __cplusplus
}
#endif

bool file_exists(char* filename) {
   struct stat buffer;
   return (stat (filename, &buffer) == 0 );
}

char** str_split(char* a_str, const char a_delim) {
   char** result = 0;
   size_t count = 0;
   char* tmp = a_str;
   char* last_comma = 0;
   char delim[2];
   delim[0] = a_delim;
   delim[1] = 0;

   /* count how many elements will be extracted. */
   while (*tmp) {
      if (a_delim == *tmp) {
         count++;
         last_comma = tmp;
      }
      tmp++;
   }

   /* Add space for trailing token. */
   count += last_comma < (a_str + strlen(a_str) - 1);

   /* Add space for eerminating null strin gtso caller
   knows where the list of returned strings ends. */
   count++;

   result = malloc(sizeof(char*) * count);

   if (result)
   {
      size_t idx = 0;
      char* token = strtok(a_str, delim);

      while (token)
      {
         assert(idx < count);
         *(result + idx++) = strdup(token);
         token = strtok(0, delim);
      }
      assert(idx == count - 1);
      *(result + idx) = 0;
   }

   return result;

}

bool isLibraryInPath() {
   char* env = getenv(ENV_VAR_TO_CHECK);
   if (env == NULL) {
      printf("%s environment variable needs to be defined and include the path to your Astro Standards libraries\n", ENV_VAR_TO_CHECK);
      exit(-1);
   }

   bool libraryFound = false;
   char buf[1024];
   char** tokens = str_split(env, PATH_DELIMITER);
   if (tokens) {
      int i;
      for (i = 0; *(tokens + i); i++)
      {
         if (!libraryFound) {
            memset(buf, '\0', sizeof(buf));
            sprintf(buf, "%s%c%s", *(tokens + i), DIRECTORY_SEPARATOR, LIBRARY_FILENAME);
            if (file_exists(buf)) {
               libraryFound = true;
            }
         }
         free(*(tokens + i));
      }
      free(tokens);
   }

   return libraryFound;
}

// Explicitly load the dll
void* LoadLib(const char* dllName)
{
   void* hLib = NULL;

#ifdef _WIN32
   hLib = LoadLibraryA(dllName);
#else
   hLib = dlopen(dllName, RTLD_LAZY);
#endif

   return hLib;
}

//Return the function pointer to the DLL function. Check to see if
//it is located successfully.
void* GetFnPtr(void* hLib, char* fName)
{
   void* fnctPtr;

#ifdef _WIN32
   fnctPtr = (void*)GetProcAddress((HMODULE)hLib, fName);
#else
   // Unix-family operating systems create all-lowecase function name
   // DHN 18Feb14 - Unix-family OSs' Astro Stds dlls now have the same function names as Windows PC platform's (Pascal notation)
   // fnctPtr = dlsym(hLib, ToStrLower(fName));
   fnctPtr = dlsym(hLib, fName);
#endif

   return fnctPtr;
}

// Free the specified library
void FreeLib(void* hLib, const char* dllName)
{
   int ok;

   if (hLib == NULL) {
      return;
   }

   // Unload the library before leaving the program
#ifdef _WIN32
   ok = FreeLibrary((HMODULE)hLib);
#else
   ok = dlclose(hLib);
#endif
}

void loadLibraries() {
   LoadDllMainDll();
   LoadEnvConstDll();
   LoadTimeFuncDll();
   LoadAstroFuncDll();
   LoadTleDll();
   LoadVcmDll();
   LoadSpVecDll();
   LoadExtEphemDll();
   LoadElOpsDll();
   LoadElCompDll();
   LoadSgp4PropDll();
   LoadSpPropDll();
   LoadSatStateDll();
   LoadSensorDll();
   LoadObsDll();
   LoadObsOpsDll();
   LoadLamodDll();
   LoadRotasDll();

   LoadAofDll();
   LoadBamDll();
   LoadBatchDCDll();
   LoadComboDll();
   LoadFovDll();
   LoadSaasDll();
}

char* substring(char* str, int p1, int p2) {
   if (strlen(str) < p2 - p1 + 1) {
      return str;
   }

   char* ss = malloc(p2 - p1);

   memcpy(ss, &str[p1], p2 - p1 - 1);
   ss[p2 - p1 - 1] = '\0';

   return ss;
}

int indexOf(char *str, char ch) {
   int ii = 0;
   for (ii = 0; ii < strlen(str); ii++) {
      if (str[ii] == ch) {
         return ii;
      }
   }

   return -1;
}

void trim(char *str) {
	char *p1 = str + strlen(str) - 1;
	while( p1 != str && *p1 == ' ' ) {
		*p1 = '\0';
		p1--;
	}
}

void printInfoFor(void (*fun_ptr)(char *), char *name ) {
   if (fun_ptr == NULL) {
      if (strlen(missingLibList) != 0) {
         strcat(missingLibList, ", ");
      }
      strcat(missingLibList, name);
      return;
   }
   char   info[INFOSTRLEN];
   memset(info, '\0', sizeof(info));
   fun_ptr(info);
   if (strlen(info) == 0) {
      printf("%s info is returning an empty array.\n", name);
      return;
   }
   info[INFOSTRLEN - 1] = '\0';

   char* sub1 = substring(info, 0, 8);
   int p1 = indexOf(info, '-');
   char* sub2 = substring(info, 8, p1);
   char* sub3 = substring(info, p1, (int)strlen(info));
   trim( sub3 );
   printf("%s %10s %s\n", sub1, sub2, sub3);
   free(sub1);
   free(sub2);
   free(sub3);
}

void printInfo() {
   printInfoFor(AofGetInfo,       "Aof");
   printInfoFor(AstroFuncGetInfo, "AstroFunc");
   printInfoFor(BamGetInfo,       "Bam");
   printInfoFor(BatchDCGetInfo,   "BatchDC");
   printInfoFor(ComboGetInfo,     "Combo");
   printInfoFor(DllMainGetInfo,   "DllMain");
   printInfoFor(ElCompGetInfo,    "ElComp");
   printInfoFor(ElOpsGetInfo,     "ElOps");
   printInfoFor(EnvGetInfo,       "EnvConst");
   printInfoFor(ExtEphGetInfo,    "ExtEphem");
   printInfoFor(FovGetInfo,       "Fov");
   printInfoFor(LamodGetInfo,     "Lamod");
   printInfoFor(ObsGetInfo,       "Obs");
   printInfoFor(ObsOpsGetInfo,    "ObsOps");
   printInfoFor(RotasGetInfo,     "Rotas");
   printInfoFor(SaasGetInfo,      "Saas");
   printInfoFor(SatStateGetInfo,  "SatState");
   printInfoFor(SensorGetInfo,    "Sensor");
   printInfoFor(Sgp4GetInfo,      "Sgp4Prop");
   printInfoFor(SpGetInfo,        "SpProp");
   printInfoFor(SpVecGetInfo,     "SpVec");
   printInfoFor(TimeFuncGetInfo,  "TimeFunc");
   printInfoFor(TleGetInfo,       "Tle");
   printInfoFor(VcmGetInfo,       "Vcm");
}

void freeLibraries() {
   FreeAofDll();
   FreeAstroFuncDll();
   FreeBamDll();
   FreeBatchDCDll();
   FreeComboDll();
   FreeDllMainDll();
   FreeElCompDll();
   FreeElOpsDll();
   FreeEnvConstDll();
   FreeExtEphemDll();
   FreeFovDll();
   FreeLamodDll();
   FreeObsDll();
   FreeObsOpsDll();
   FreeRotasDll();
   FreeSaasDll();
   FreeSatStateDll();
   FreeSensorDll();
   FreeSgp4PropDll();
   FreeSpPropDll();
   FreeSpVecDll();
   FreeTimeFuncDll();
   FreeTleDll();
   FreeVcmDll();
}

int main(int argc, char* argv[])
{
   memset(missingLibList, '\0', sizeof(missingLibList));

   if (!isLibraryInPath()) {
      printf("Please set %s to include the directory to the Astro Standards libraries.\n", ENV_VAR_TO_CHECK);
      exit(-1);
   }

   loadLibraries();

   printInfo();

   if (strlen(missingLibList) != 0) {
      printf("The following libraries not available: %s\n", missingLibList);
   }

   // not needed because program is exited but just cleaner programming.
   freeLibraries();


   exit(0);
}
