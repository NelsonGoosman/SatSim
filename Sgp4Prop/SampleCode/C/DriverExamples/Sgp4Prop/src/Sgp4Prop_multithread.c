/*
Purpose:
   This program shows how a C program can call Astrodynamic Standard Dlls to propagate
   satellites to the requested time using SGP4 method.

   The program reads in user specified file, the start, stop time (in minutes since epoch), 
   and time step (in minutes). The program generates an ephemeris of position and velocity 
   for each satellite read in. In addition, the program also generates other sets of orbital 
   elements such as osculating Keplerian elements, mean Keplerian elements, 
   latitude/longitude/height/pos, and nodal period/apogee/perigee/pos. Totally, the program 
   prints results to five different output files. 
      

Usage: Command line format
   Sgp4Prop inFile outFile startTime stopTime stepSize
   inFile   : File contains TLEs
   outFile  : Base name for five output files
   startTime: propagating start time in minutes since epoch
   stopTime : propagating stop time in minutes since ecpoch
   stepSize : propagating step size in minutes
   -IlibPath: Optional path to the Astrodynamics Standards library


Note:
   To see this program correctly in Visual Studio set the tab size to 3 and check 
   insert spaces in Tools/Options/Tabs

*/


#include <stdio.h>
#include <process.h>
#include <windows.h>
#include <math.h>

struct parameters
{
   double startTime;
   double stopTime;
   double stepSize;
   int start;
   int stop;
   __int64* satKeys;
   __int64* satPtrs;
};

typedef struct parameters parameters;

// Compiler directive that allows C++ code to use the C header files
// Begin
#ifdef __cplusplus
extern "C" 
{
#endif

#include "../../services\DllMainDll.h"
#include "../../services\EnvConstDll.h"
#include "../../services\AstroFuncDll.h"
#include "../../services\TimeFuncDll.h"
#include "../../services\TleDll.h"
#include "../../services\Sgp4PropDll.h"

// End
#ifdef __cplusplus
}
#endif


// Predefined output file names
#define  OSC_STATE      "_OscState.txt"
#define  OSC_ELEM       "_OscElem.txt"
#define  MEAN_ELEM      "_MeanElem.txt"
#define  LLH_ELEM       "_LatLonHeight.txt"
#define  NODAL_AP_PER   "_NodalApPer.txt"

// Function prototypes
void  LoadAstroStdDlls(const char*);
void  FreeAstroStdDlls();
void  PrintHeader(FILE* fp, char* infoStr, char* inFile,
                  double startTime, double stopTime, double stepSize);

void  PrintPosVel(FILE* fp, double mse, double* pos, double* vel);
void  PrintOscEls(FILE* fp, double mse, double* oscKep);
void  PrintMeanEls(FILE* fp, double mse, double* meanKep);
void  PrintLLH(FILE* fp, double mse, double* llh, double* pos);
void  PrintNodalApPer(FILE* fp, double mse, double n, double* nodalApPer);
//void DoThread(parameters* para);
unsigned __stdcall DoThread(parameters* para);


int main(int argc, char* argv[])
{
   FILE* fpOscState;	   // Osculating state vector
   FILE* fpOscElem;	   // Osculating Keplerian elements
   FILE* fpMeanElem;	   // Mean Keplerian Elements				
   FILE* fpLLH;	      // Latitude,longitude,height,pos
   FILE* fpnodalApPer;	// Nodal period,apogee,perigee,pos

#ifdef _WIN32
   char  libPath[128] = ".\\";  // Default to the folder where the executable is called
#else
   char  libPath[128] = "./";  // Default to the folder where the executable is called
#endif

   char  inFile[100], outFile[100], outputFileName[100];
   double startTime; 
   double stopTime;
   double stepSize;

   char  logFile[] = "c_sgp4_log.txt";

   char  sgp4DllInfo[128];
   char  errMsg[128];

   char  line1[80];
   char  line2[80];

   int   errCode;
   int   numSats;
   int   i;

   double mse, ds50UTC;
   double meanMotion;

   __int64* pSatKeys;
   __int64* pSatPtrs;
   int numOfThreads, numSatsPerThread;
   DWORD dwWaitReturn;
   int stillActive;

   //__int64 satKeys[100];   // for static array

   // Arrays that store propagator output data
   double 
      pos[3],           //Position (km)
      vel[3],           //Velocity (km/s)
      llh[3],           // Latitude(deg), Longitude(deg), Height above Geoid (km)
      meanKep[6],       //Mean Keplerian elements
      oscKep[6],        //Osculating Keplerian elements
      nodalApPer[3];    //Nodal period, apogee, perigee

   parameters para1, para2, para[100];
   HANDLE hThread[100];

   clock_t start, finish;


   printf("Program starts.\n");
   start = clock();


   // This program is getting input parameters from the command line.
   // Follow the instruction to pass parameters in the right order.
   if (argc >= 6)
   {
      
		strcpy(inFile , argv[1] );
      strcpy(outFile, argv[2] );
		startTime = atof(argv[3]);
		stopTime  = atof(argv[4]);
		stepSize  = atof(argv[5]);
      if (argc == 7 && strncmp(argv[6], "-I", 2) == 0) // optional -IlibPath provided
         strcpy(libPath, &argv[6][2]);
      printf("Input file  = %s\n", inFile);
      printf("Output file = %s\n", outFile);
      printf("Start time  = %f\n", startTime);
      printf("Stop time   = %f\n", stopTime);
      printf("Step size   = %f\n", stepSize);
	}
	else 
   {
      printf("Error in number of parameters passed. Please see the usage.\n\n\n");
      printf("Usage    : Sgp4Prop inFile outFile startTime stopTime stepSize\n\n");
      printf("inFile   : File contains TLEs\n");
      printf("outFile  : Base name for five output files\n");
      printf("startTime: propagating start time in minutes since epoch\n");
      printf("stopTime : propagating stop time in minutes since ecpoch\n");
      printf("stepSize : propagating step size in minutes\n");
      printf("-IlibPath : Specified path \"libpath\" to the Astrodynamic Standards library.\n");
      exit(1);
   }
   

   printf("Library Path= %s\n\n", libPath);

   // Load all the dlls being used in the program
   // Remember to specify the correct path to the Astro Standards dlls including the forward/backward slash at the end
   LoadAstroStdDlls(libPath);

   // Log diagno*stic information to a log file. This is optional
   //-----------------------------------------------------------
   //errCode = OpenLogFile(logFile);

   //if (errCode != 0)
   //   ShowMsgAndTerminate();

   
   TleAddSatFrFieldsGP(90028, 'U', "RELEAS14", 2010, 210.70350568, -0.000013568, 0, 377, 72.5158, 110.12453299132176, 0.001143, 124.7615, 235.4297, 12.44396488, 2428);
   
   // Load Tles from the input file
   if (TleLoadFile(inFile))
      return;

   // Count number of satellites currently loaded in memory
   numSats = TleGetCount();
   
   // Using dinamic array
   pSatKeys = (__int64*) malloc(numSats * sizeof(__int64));
   pSatPtrs = (__int64*) malloc(numSats * sizeof(__int64));
   
   // Get all the satellites' ids from memory and store them in the local array
   TleGetLoaded(2, pSatKeys);  // Get the satKeys in the order they were read

   // Get information about the current DLL
   Sgp4GetInfo(sgp4DllInfo);
   sgp4DllInfo[127] = 0;
   printf("%s\n", sgp4DllInfo);


   // Open output files. Check to see if error occurs
   sprintf(outputFileName,"%s%s", outFile, OSC_STATE);
   fpOscState = FileOpen(outputFileName, "wt");

   sprintf(outputFileName,"%s%s", outFile, OSC_ELEM);
   fpOscElem = FileOpen(outputFileName, "wt");

   sprintf(outputFileName,"%s%s", outFile, MEAN_ELEM);
   fpMeanElem = FileOpen(outputFileName, "wt");

   sprintf(outputFileName,"%s%s", outFile, LLH_ELEM);
   fpLLH = FileOpen(outputFileName, "wt");

   sprintf(outputFileName,"%s%s", outFile, NODAL_AP_PER);
   fpnodalApPer = FileOpen(outputFileName, "wt");



   // Print header with output field names to files
   PrintHeader(fpOscState, sgp4DllInfo, inFile, startTime, stopTime, stepSize);
   fprintf(fpOscState, "%s\n", 
   "     TSINCE (MIN)           X (KM)           Y (KM)           Z (KM)      XDOT (KM/S)       YDOT(KM/S)    ZDOT (KM/SEC)");

   PrintHeader(fpOscElem, sgp4DllInfo, inFile, startTime, stopTime, stepSize);
   fprintf(fpOscElem, "%s\n", 
   "     TSINCE (MIN)           A (KM)          ECC (-)        INC (DEG)       NODE (DEG)      OMEGA (DEG)   TRUE ANOM(DEG)");

   PrintHeader(fpMeanElem, sgp4DllInfo, inFile, startTime, stopTime, stepSize);
   fprintf(fpMeanElem, "%s\n",
   "     TSINCE (MIN)     N (REVS/DAY)          ECC (-)        INC (DEG)       NODE (DEG)      OMEGA (DEG)         MA (DEG)");

   PrintHeader(fpLLH, sgp4DllInfo, inFile, startTime, stopTime, stepSize);
   fprintf(fpLLH, "%s\n", 
   "     TSINCE (MIN)         LAT(DEG)        LON (DEG)          HT (KM)           X (KM)           Y (KM)           Z (KM)");

   PrintHeader(fpnodalApPer, sgp4DllInfo, inFile, startTime, stopTime, stepSize);
   fprintf(fpnodalApPer, "%s\n", 
   "     TSINCE (MIN)   NODAL PER(MIN)1/NODAL(REVS/DAY)       N(REVS/DY)    ANOM PER(MIN)      APOGEE (KM)      PERIGEE(KM)");


   // Loop through all the TLEs in the input file
   for (i = 0; i < numSats; i++) 
   {
            // Initialize the satellite before propagating it
      if (Sgp4InitSat(pSatKeys[i]) != 0)
         ShowMsgAndTerminate();

      pSatPtrs[i] = Sgp4GetSatPtr(pSatKeys[i]);

   }

   numOfThreads = 32;
   numSatsPerThread = ceil(1.0 * numSats / numOfThreads);

   for (i = 0; i < numOfThreads; i++)
   {
      para[i].startTime = startTime;
      para[i].stopTime = stopTime;
      para[i].stepSize = stepSize;
      para[i].satKeys = pSatKeys;
      para[i].satPtrs = pSatPtrs;
      para[i].start = numSatsPerThread * i;
      para[i].stop = min_i(numSats, numSatsPerThread * (i + 1));
      printf("Thread # %d - Start idx = %d End idx = %d\n", i + 1, para[i].start, para[i].stop);

      //hThread1 = (HANDLE) _beginthread(DoThread, 0, (void*) &para1);;
      hThread[i] = (HANDLE) _beginthreadex(0, 0, &DoThread, (void*) &para[i], 0, 0);
   }

   while(1)
   {
      stillActive = 0;
      for (i = 0; i < numOfThreads; i++)
      {
         GetExitCodeThread(hThread[i], &dwWaitReturn);
         if(dwWaitReturn == STILL_ACTIVE)
         {
            //printf("Thread %d still active.\n", i);
            stillActive = 1;
         }
         else
            ;//printf("Thread %d ended.\n", i);
      }

      if(!stillActive)
         break;
   }

   for (i = 0; i < numOfThreads; i++)
   {
      CloseHandle(hThread[i]);
   }



   //WaitForSingleObject(hThread1, INFINITE);
   //WaitForSingleObject(hThread2, INFINITE);
   //CloseHandle(hThread2);

   
   //// Loop through all the minute-since-epoch time steps
   //for(mse = startTime; mse <= stopTime; mse += stepSize)
   //{
   //   // Loop through all the TLEs in the input file
   //   for (i = 0; i < numSats; i++) 
   //   {
   //      // Propagate the current satellite to the time specified in mse
		 //  //errCode = Sgp4PropMse(pSatKeys[i], mse, &ds50UTC, pos, vel, llh);
   //      errCode = Sgp4PropMseQuick(pSatKeys[i], pSatPtrs[i], mse, pos, vel);
   //   }
   //}
   

/*
   // Loop through all the TLEs in the input file
   for (i = 0; i < numSats; i++) 
   {
      // Loop through all the minute-since-epoch time steps
      for(mse = startTime; mse <= stopTime; mse += stepSize)
      {
      
         // Propagate the current satellite to the time specified in mse
		   //errCode = Sgp4PropMse(pSatKeys[i], mse, &ds50UTC, pos, vel, llh);
         errCode = Sgp4PropMseQuick(pSatKeys[i], pSatPtrs[i], mse, pos, vel);
      }
   }
*/



   //// Loop through all the TLEs in the input file
   //for (i = 0; i < numSats; i++) 
   //{
   //   // Return the two strings, line1 line2, representing the TLE
   //   TleGetLines(pSatKeys[i], line1, line2);
   //   line1[79] = 0;
   //   line2[79] = 0;

   //   // Print TLE for each satellite
   //   fprintf(fpOscState, "\n\n %s\n %s\n\n", line1, line2);
   //   fprintf(fpOscElem, "\n\n %s\n %s\n\n", line1, line2);
   //   fprintf(fpMeanElem, "\n\n %s\n %s\n\n", line1, line2);
   //   fprintf(fpLLH, "\n\n %s\n %s\n\n", line1, line2);
   //   fprintf(fpnodalApPer, "\n\n %s\n %s\n\n", line1, line2);

   //   // Initialize the satellite before propagating it
   //   if (Sgp4InitSat(pSatKeys[i]) != 0)
   //      ShowMsgAndTerminate();

   //   satPtr = Sgp4GetSatPtr(pSatKeys[i]);

   //   // Loop through all the minute-since-epoch time steps
	  // for(mse = startTime; mse <= stopTime; mse += stepSize)
	  // {
   //      // Propagate the current satellite to the time specified in mse
		 //  //errCode = Sgp4PropMse(pSatKeys[i], mse, &ds50UTC, pos, vel, llh);
   //      errCode = Sgp4PropMseQuick(pSatKeys[i], satPtr, mse, pos, vel);

   //      /*
   //      // Error or decay condition
   //      if (errCode != 0) 
   //      {
   //         GetLastErrMsg(errMsg);
   //         errMsg[127] = 0;

   //         // Display error message to screen
   //         printf("%s\n", errMsg);

   //         // Write error message to files
   //         fprintf(fpOscState, "%s\n", errMsg);
   //         fprintf(fpOscElem, "%s\n", errMsg);
   //         fprintf(fpMeanElem, "%s\n", errMsg);
   //         fprintf(fpLLH, "%s\n", errMsg);
   //         fprintf(fpnodalApPer, "%s\n", errMsg);

   //         break; // Move to the next satellite
   //      }


   //      //Compute/Retrieve other propagator output data
   //      //----------------------------------------------------------------
   //      Sgp4GetPropOut(pSatKeys[i], IDX_SGP4OUT_OSC_KEP, oscKep);
   //      Sgp4GetPropOut(pSatKeys[i], IDX_SGP4OUT_MEAN_KEP, meanKep);
   //      Sgp4GetPropOut(pSatKeys[i], IDX_SGP4OUT_NODAL_AP_PER, nodalApPer);

   //      // Using AstroFunc dll to compute/convert to other propagator output data if needed
   //      //KepToPosVel(oscKep, pos, vel);

   //      // Print position and velocity
   //      PrintPosVel(fpOscState, mse, pos, vel);

   //      // Print lat lon height and position
   //      PrintLLH(fpLLH, mse, llh, pos);

   //      // Print osculating Keplerian elements
   //      PrintOscEls(fpOscElem,  mse, oscKep);

   //      // Print mean Keplerian elements
   //      PrintMeanEls(fpMeanElem, mse, meanKep);

   //      // Print nodal period, apogee, perigee, and others
   //      meanMotion = AToN(meanKep[0]);
   //      PrintNodalApPer(fpnodalApPer, mse, meanMotion, nodalApPer);

   //      // Height is below 100km - Skip the satellite
   //      if (llh[2] < 100.0) 
   //      {
   //         if (llh[2] < 0)
   //            sprintf(errMsg, "Warning: Decay condition. Distance from the Geoid (Km) = %10.3lf\n", llh[2]);
   //         else
   //            sprintf(errMsg, "Warning: Height is low. HT (Km) = %10.3lf\n", llh[2]);

   //         // Write error message to files
   //         fprintf(fpOscState, "%s\n", errMsg);
   //         fprintf(fpOscElem, "%s\n", errMsg);
   //         fprintf(fpMeanElem, "%s\n", errMsg);
   //         fprintf(fpLLH, "%s\n", errMsg);
   //         fprintf(fpnodalApPer, "%s\n", errMsg);

   //         break; // Move to the next satellite
   //      }
   //      */
   //   }

   //   // Remove this satellite if no longer needed
   //   if (Sgp4RemoveSat(pSatKeys[i]) != 0)
   //      ShowMsgAndTerminate();
   //}
   //-------------------------------------------------------------------------
   
   // Remove all the satellites from memory if no longer needed
   //Sgp4RemoveAllSats();

   
   // Close all output files
   fclose(fpOscState); 
   fclose(fpOscElem);
   fclose(fpMeanElem); 
   fclose(fpLLH);
   fclose(fpnodalApPer);


   // Close log file if needed
   //CloseLogFile();
   
   
   // Free loaded AstroStd dlls
   FreeAstroStdDlls();

   //Calculate the whole run time
   printf("Program completed successfully.\n");
   finish = clock();
   printf("Total run time = %10.2lf seconds.\n\n\n\n", (double)(finish - start) / CLOCKS_PER_SEC );

   exit(0);
}


//void DoThread(parameters* para)
unsigned __stdcall DoThread(parameters* para)
{
   int i, errCode;
   double mse, ds50UTC;

   double 
      pos[3],           //Position (km)
      vel[3],           //Velocity (km/s)
      llh[3];           // Latitude(deg), Longitude(deg), Height above Geoid (km)

   //printf("Start idx = %d    End idx = %d\n", para->start, para->stop);

   // Loop through all the minute-since-epoch time steps
   for(mse = para->startTime; mse <= para->stopTime; mse += para->stepSize)
   {
      // Loop through all the TLEs in the input file
      for (i = para->start; i < para->stop; i++) 
      {
         errCode = Sgp4PropMse(para->satKeys[i], mse, &ds50UTC, pos, vel, llh);
         //errCode = Sgp4PropMseQuick(para->satKeys[i], para->satPtrs[i], mse, pos, vel);
      }
   }

   //printf("Thread finished\n");
   _endthreadex(0);
   return(0);
}

// Load all the dlls being used in the program
void LoadAstroStdDlls(const char* libPath)
{
   // Load MainDll dll
   LoadDllMainDll(libPath);

   // Load EnvConst dll and assign function pointers
   LoadEnvConstDll(libPath);

   // Load TimeFunc dll and assign function pointers
   LoadTimeFuncDll(libPath);

   // Load AstroFunc dll and assign function pointers
   LoadAstroFuncDll(libPath);

   // Load Tle dll and assign function pointers
   LoadTleDll(libPath);

   // Load Sgp4Prop dll and assign function pointers
   LoadSgp4PropDll(libPath);
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


// Print header for the output files
void PrintHeader(FILE* fp, char* infoStr, char* inFile,
                 double startTime, double stopTime, double stepSize)
{

   fprintf(fp, "%s\n\n\n", infoStr);
   fprintf(fp, "%s\n",   "EPHEMERIS GENERATED BY SGP4 USING THE WGS-72 EARTH MODEL");
   fprintf(fp, "%s\n",   "COORDINATE FRAME=TRUE EQUATOR AND MEAN EQUINOX OF EPOCH");
   fprintf(fp, "%s\n\n", "USING THE FK5 MEAN OF J2000 TIME AND REFERENCE FRAME");
   fprintf(fp, "%s%s\n", "INPUT FILE = ", inFile);
   fprintf(fp, "%s%14.4f%s\n", "Start Time = ", startTime, " min from epoch");
   fprintf(fp, "%s%14.4f%s\n", "Stop Time  = ", stopTime,  " min from epoch");
   fprintf(fp, "%s%14.4f%s\n\n\n", "Step size  = ", stepSize,  " min");
   
}


// Print position and velocity vectors
void PrintPosVel(FILE* fp, double mse, double* pos, double* vel)
{
   fprintf(fp, " %17.7f%17.7f%17.7f%17.7f%17.7f%17.7f%17.7f\n", 
      mse, pos[0], pos[1], pos[2], vel[0], vel[1], vel[2]);

}



// Print osculating Keplerian elements
void PrintOscEls(FILE* fp, double mse, double* oscKep)
{
   double trueAnomaly = CompTrueAnomaly(oscKep);

   fprintf(fp, " %17.7f%17.7f%17.7f%17.7f%17.7f%17.7f%17.7f\n", 
      mse, oscKep[0], oscKep[1], oscKep[2], oscKep[4], oscKep[5], trueAnomaly);

}


// Print mean Keplerian elements
void PrintMeanEls(FILE* fp, double mse, double* meanKep)
{
   double meanMotion = AToN(meanKep[0]);

   fprintf(fp, " %17.7f%17.7f%17.7f%17.7f%17.7f%17.7f%17.7f\n", 
      mse, meanMotion, meanKep[1], meanKep[2], meanKep[4], meanKep[5], meanKep[3]);

}


// Print geodetic latitude longitude altitude and position vector
void PrintLLH(FILE* fp, double mse, double* llh, double* pos)
{
   fprintf(fp, " %17.7f%17.7f%17.7f%17.7f%17.7f%17.7f%17.7f\n", 
      mse, llh[0], llh[1], llh[2], pos[0], pos[1], pos[2]);

}


// Print nodal perdiod, apogee, perigee
void PrintNodalApPer(FILE* fp, double mse, double n, double* nodalApPer)
{

   fprintf(fp, " %17.7f%17.7f%17.7f%17.7f%17.7f%17.7f%17.7f\n", 
      mse, 
      nodalApPer[0], 
      (1440.0 / nodalApPer[0]), 
      n , 
      1440.0 / n, 
      nodalApPer[1], 
      nodalApPer[2]);
}



