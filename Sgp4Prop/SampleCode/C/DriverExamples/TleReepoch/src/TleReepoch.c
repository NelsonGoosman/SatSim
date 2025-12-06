/*
Purpose:
   This program shows how a Fortran program can call the Astrodynamic Standard Dlls to reepoch
   the input TLEs to a new epoch 

Usage: Command line format
   TleReepoch inFile outFile newEpoch
   inFile   : The name of an input file that contains the input TLEs
   outFile  : The name of an output file that stores the newly reepoched TLEs
   newEpoch : The new epoch time in YYDDDHHMMSS.SSS or YYYY/DDD.DDDDDDD
   
*/


#include <stdio.h>
#include <math.h>    // Without this the fabs returns wrong results


// Compiler directive that allows C++ code to use the C header files
// Begin
#ifdef __cplusplus
extern "C" 
{
#endif

#include "../../services/DllMainDll_Service.h" 
#include "../../services/TimeFuncDll_Service.h"
#include "../../wrappers/DllMainDll.h"
#include "../../wrappers/EnvConstDll.h"
#include "../../wrappers/AstroFuncDll.h"
#include "../../wrappers/TimeFuncDll.h"
#include "../../wrappers/TleDll.h"
#include "../../wrappers/Sgp4PropDll.h"

// End
#ifdef __cplusplus
}
#endif

// Function prototypes
void  LoadAstroStdDlls();
void  FreeAstroStdDlls();

int main(int argc, char* argv[])
{
   CommandLineArgs cla;
   FILE* fpOutFile;	   

   char  newEpochDTG[21];

   char  line1[INPUTCARDLEN];
   char  line2[INPUTCARDLEN];

   int   errCode;
   int   numSats;
   int   i;

   double ds50UTC;

   __int64* pSatKeys;

   clock_t start, finish;

   // This program is getting input parameters from the command line.
   // Follow the instruction to pass parameters in the right order.
   if (argc >= 3 )
   {
      strcpy(newEpochDTG, argv[3]);
   }
   else 
   {
      printf("Error in number of parameters passed. Please see the usage.\n\n\n");
      printf("Usage    : TleReepoch inFile outFile newEpoch\n\n");
      printf("inFile   : The name of an input file that contains the input TLEs\n");
      printf("outFile  : The name of an output file that stores the newly reepoched TLEs\n");
      printf("newEpoch : The new epoch time in YYDDDHHMMSS.SSS or YYYY/DDD.DDDDDDD\n");
      printf("Example: C_TleReepoch oldtles.inp newtles.out 2014/001.0000000\n");
      exit(1);
   }

   printf("Program starts.\n");
   start = clock();

   // Get input parameters from the command line
   GetCommandLineArgs(argc, argv, "C_TleReepoch", "SGP4", &cla);

   // Load all the dlls being used in the program from the specified path (PATH env on Windows or LD_LIBRARY_PATH on Linux)
   LoadAstroStdDlls();

   // Load Tles from the input file
   if (TleLoadFile(cla.inFile))
      ShowMsgAndTerminate();

   // Count number of satellites currently loaded in memory
   numSats = TleGetCount();
   if (numSats == 0)
   {
      printf("No TLEs were found in the input file\n");
      ShowMsgAndTerminate();
   }
   
   // Using dinamic array
   pSatKeys = (__int64*) malloc(numSats * sizeof(__int64));
   
   // Get all the satellites' ids from memory and store them in the local array
   TleGetLoaded(2, pSatKeys);  // Get the satKeys in the order they were read

   fpOutFile = FileOpen(cla.outFile, "wt");

   // convert the input string to days since 1950 UTC, the input value that Sgp4ReepochTLE requests 
   ds50UTC = DTGToUTC(newEpochDTG);

   // Loop through all the TLEs in the input file
   for (i = 0; i < numSats; i++) 
   {
      // Initialize the satellite before propagating it
      if (Sgp4InitSat(pSatKeys[i]) != 0)
         ShowMsgAndTerminate();

      // reepoch the TLE to the requested time
      errCode = Sgp4ReepochTLE(pSatKeys[i], ds50UTC, line1, line2);

      if (errCode == 0)
      {
         line1[80] = 0;
         line2[80] = 0;
         fprintf(fpOutFile, "%s\n%s\n", line1, line2);
      }
   }
   
   free(pSatKeys);

   // Free loaded AstroStd dlls
   FreeAstroStdDlls();

   //Calculate the whole run time
   printf("Program completed successfully.\n");
   finish = clock();
   printf("Total run time = %10.2lf seconds.\n\n\n\n", (double)(finish - start) / CLOCKS_PER_SEC);

   // Close all output files
   fclose(fpOutFile);
   //getchar();

   exit(0);
}


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

   // Load Tle dll and assign function pointers
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

   // Free Tle dll
   FreeTleDll();

   // Free Sgp4Prop dll
   FreeSgp4PropDll();
}

