/*
   Purpose:
      This program shows how a C program can call the Astrodynamic Standard Dlls to propagate
      satellites to the requested time using SGP4 propagator.

      The program is simplified to show only the core functionalities of the involved dlls. 
      File I/O and other output statements are intentionally not included for this purpose.

      Steps to implement the SGP4 propagator:
      1. Load all the required dlls  (LoadAstroStdDlls)  
      2. Load TLE(s) (TleAddSatFrLines, TleLoadFile, TleAddSatFrFieldsGP)
      3. Initialize the loaded TLE(s) (Sgp4InitSat)
      4. Propagate the initialized TLE(s) to the requested time 
         (either minutes since epoch: Sgp4PropMse, or specific date: Sgp4PropDs50UTC, Sgp4PropDs50UtcPos, Sgp4PropDs50UtcLLH)
      5. Deallocate loaded dlls (FreeAstroStdDlls)
	  
   Author:
      HQ AFSPC/A2/3/6Z
*/


#include <stdio.h>
#include <math.h>    


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
   int     errCode;
   double  mse, ds50UTC, startTime, endTime;
   __int64 satKey;

   // Arrays that store propagation data
   double pos[3];   // Position (km) in TEME of Epoch
   double vel[3];   // Velocity (km/s) in TEME of Epoch
   double llh[3];   // Latitude(deg), Longitude(deg), Height above Geoid (km)

   // Load all the dlls being used in the program from the specified path (PATH env on Windows or LD_LIBRARY_PATH on Linux)
   LoadAstroStdDlls();
   
   // load a TLE using strings (see TLE dll document)
   satKey = TleAddSatFrLines("1 90021U RELEAS14 00051.47568104 +.00000184 +00000+0 +00000-4 0 0814",
                             "2 90021   0.0222 182.4923 0000720  45.6036 131.8822  1.00271328 1199");
   
   // other ways to load TLEs into memory to work with
   //TleLoadFile(fileName);  // load TLEs from a text file
   //TleAddSatFrFieldsGP();  // load a TLE by passing its data fields

   // initialize the loaded TLE before it can be propagated (see Sgp4Prop dll document)
   // This is important!!!
   errCode = Sgp4InitSat(satKey);
   
   // check to see if initialization was successful
   if (errCode != 0)
      exit(1);

   // propagate using specific date, days since 1950 UTC (for example using "2000 051.051.47568104" as a start time)
   startTime = DTGToUTC("00051.47568104"); // convert date time group string "YYDDD.DDDDDDDD" to days since 1950, UTC (see TimeFunc dll document)
   endTime = startTime + 10;               // from start time propagate for 10 days 

   // propagate for 10 days from start time with 0.5 day step size
   for (ds50UTC = startTime; ds50UTC < endTime; ds50UTC += 0.5)
   {
      Sgp4PropDs50UTC(satKey, ds50UTC, &mse, pos, vel, llh); // see Sgp4Prop dll document
      // other available propagation methods
      //Sgp4PropDs50UtcLLH(satKey, ds50UTC, llh);
      //Sgp4PropDs50UtcPos(satKey, ds50UTC, pos);
   }

   // propagate using minutes since satellite's epoch
   // propagate for 30 days since satellite's epoch with 1 day (1440 minutes) step size
   for (mse = 0; mse < (30 * 1440); mse += 1440)
   {
      // propagate the initialized TLE to the specified time in minutes since epoch
      Sgp4PropMse(satKey, mse, &ds50UTC, pos, vel, llh); // see Sgp4Prop dll document
   }

   // Remove loaded satellites if no longer needed
   TleRemoveSat(satKey);   // remove loaded TLE from memory
   Sgp4RemoveSat(satKey);  // remove initialized TLE from memory
   //TleRemoveAllSats();   // remove all loaded TLEs from memory
   //Sgp4RemoveAllSats();  // remove all initialized TLEs from memory

   // Deallocate loaded AstroStd dlls
   FreeAstroStdDlls();

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


