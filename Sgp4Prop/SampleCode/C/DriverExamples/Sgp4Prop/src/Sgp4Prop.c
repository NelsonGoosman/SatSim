/*
   Purpose:
      This program shows how a C program can call the Astrodynamic Standard Dlls to propagate
      satellites to the requested time using SGP4 method.

      The program reads in user's input and output files. The program generates an 
      ephemeris of position and velocity for each satellite read in. In addition, the program 
      also generates other sets of orbital elements such as osculating Keplerian elements, 
      mean Keplerian elements, latitude/longitude/height/pos, and nodal period/apogee/perigee/pos. 
      Totally, the program prints results to five different output files. 
      

   Usage: Command line format
      Sgp4Prop inFile outFile [-Dlogfile]
      inFile   : File contains TLEs and 6P-Card (which controls start, stop times and step size)
      outFile  : Base name for five output files
      -DlogFile : Optional logFile to enable writing debug data to the specified file
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
void  CalcStartStopTime(double epoch, double* tStart, double* tStop, double* tStep);
void  PrinTitle(FILE* fp, char* infoStr, char* inFile);
void  PrintHeader(FILE* fp, int fileType);

void  PrintPosVel(FILE* fp, double mse, double* pos, double* vel);
void  PrintOscEls(FILE* fp, double mse, double* oscKep);
void  PrintMeanEls(FILE* fp, double mse, double* meanKep);
void  PrintLLH(FILE* fp, double mse, double* llh, double* pos);
void  PrintNodalApPer(FILE* fp, double mse, double n, double* nodalApPer);
void  RunOneSgp4Job(char* inFile, FILE* fpOscState, FILE* fpOscElem, FILE* fpMeanElem, FILE* fpLLH, FILE* fpnodalApPer);

const int FT_OSC_STATE = 0;
const int FT_OSC_ELEM = 1;
const int FT_MEAN_ELEM = 2;
const int FT_LLH_ELEM = 3;
const int FT_NODAL_AP_PER = 4;

int main(int argc, char* argv[])
{
   char OSC_STATE[]     = "_OscState.out";
   char OSC_ELEM[]      = "_OscElem.out";
   char MEAN_ELEM[]     = "_MeanElem.out";
   char LLH_ELEM[]      = "_LatLonHeight.out";
   char NODAL_AP_PER[]  = "_NodalApPer.out";

   CommandLineArgs cla;

   FILE* fpInputFile;
   FILE* fpOscState;	   // Osculating state vector
   FILE* fpOscElem;	   // Osculating Keplerian elements
   FILE* fpMeanElem;	   // Mean Keplerian Elements				
   FILE* fpLLH;	      // Latitude,longitude,height,pos
   FILE* fpnodalApPer;	// Nodal period,apogee,perigee,pos

   char* oneSgp4JobTmpFile;
   char  outputFileName[1024];
   char  sgp4DllInfo[INFOSTRLEN];

   int  order = 2;   // Get the satKeys in the order they were read
   int  jobNum, errCode, isEndAll;

   clock_t start, finish;

   printf("Program starts.\n");
   start = clock();

   // Get input parameters from the command line
   GetCommandLineArgs(argc, argv, "Sgp4Prop", "SGP4", &cla);

   // Load all the dlls being used in the program from the specified path (PATH env on Windows or LD_LIBRARY_PATH on Linux)
   LoadAstroStdDlls();

   // Get information about the current DLL
   Sgp4GetInfo(sgp4DllInfo);
   sgp4DllInfo[INFOSTRLEN-1] = 0;
   printf("%s\n", sgp4DllInfo);


   // Record diagnostic information in a log file. This is optional
   // -------------------------------------------------------------
   if(cla.logFile[0] != 0)
   {
      errCode = OpenLogFile(cla.logFile);

      if (errCode != 0)
      {
         printf("Fatal Error: Cannot open log file \"%s\" - Program will now exit.\n", cla.logFile);
         exit(1);
      }
   }

   // Open input file for reading
   fpInputFile = FileOpen(cla.inFile, "r");

   // Open output files. Check to see if error occurs
   strcat(strcpy(outputFileName, cla.outFile), OSC_STATE);
   fpOscState = FileOpen(outputFileName, "wt");
   PrinTitle(fpOscState, sgp4DllInfo, cla.inFile);

   strcat(strcpy(outputFileName, cla.outFile), OSC_ELEM);
   fpOscElem = FileOpen(outputFileName, "wt");
   PrinTitle(fpOscElem, sgp4DllInfo, cla.inFile);

   strcat(strcpy(outputFileName, cla.outFile), MEAN_ELEM);
   fpMeanElem = FileOpen(outputFileName, "wt");
   PrinTitle(fpMeanElem, sgp4DllInfo, cla.inFile);

   strcat(strcpy(outputFileName, cla.outFile), LLH_ELEM);
   fpLLH = FileOpen(outputFileName, "wt");
   PrinTitle(fpLLH, sgp4DllInfo, cla.inFile);

   strcat(strcpy(outputFileName, cla.outFile), NODAL_AP_PER);
   fpnodalApPer = FileOpen(outputFileName, "wt");
   PrinTitle(fpnodalApPer, sgp4DllInfo, cla.inFile);

 
   jobNum = 0;


   // Process batch input file
   while (1)
   {
      // Auto generate a temporary unique file name for each job
      oneSgp4JobTmpFile = GetOneJob(fpInputFile, &isEndAll);

      // Check to see if there is a job to run
      if (oneSgp4JobTmpFile[0] == 0)
         break;

      jobNum++;
      printf("\n\n");
      printf("Processing Job #: %2d\n\n", jobNum);

      RunOneSgp4Job(oneSgp4JobTmpFile, fpOscState, fpOscElem, fpMeanElem, fpLLH, fpnodalApPer);

      // Remove the temporay file 
      remove(oneSgp4JobTmpFile);
      if (isEndAll)
         break;
   }


   //Calculate the whole run time
   printf("\n\nProgram completed successfully.\n");
   finish = clock();
   printf("Total run time = %10.2lf seconds.\n\n\n\n", (double)(finish - start) / CLOCKS_PER_SEC);
   fprintf(fpOscState, "Total run time = %10.2lf seconds.\n", (double)(finish - start) / CLOCKS_PER_SEC);


   // Close all output files
   fclose(fpOscState); 
   fclose(fpOscElem);
   fclose(fpMeanElem); 
   fclose(fpLLH);
   fclose(fpnodalApPer);

   // Close log file if needed
   CloseLogFile();
   
   // Free loaded AstroStd dlls
   FreeAstroStdDlls();

   exit(0);
}

// Run one Lamod job at a time
void RunOneSgp4Job(char* inFile, FILE* fpOscState, FILE* fpOscElem, FILE* fpMeanElem, FILE* fpLLH, FILE* fpnodalApPer)
{
   const double EPSI = 0.00050;	/*	TIME TOLERANCE IN SEC.	*/

   double startTime;
   double stopTime;
   double stepSize;

   char  errMsg[LOGMSGLEN];
   char  valueStr[GETSETSTRLEN];

   char  line1[INPUTCARDLEN];
   char  line2[INPUTCARDLEN];

   int   errCode;
   int   numSats;
   int   i;
   int   step;
   int  order = 2;   // Get the satKeys in the order they were read

   double mse, ds50UTC, epochDs50UTC;
   double meanMotion;

   __int64* pSatKeys;
   //__int64 satKeys[100];   // for static array

   // Arrays that store propagator output data
   double
      pos[3],           //Position (km)
      vel[3],           //Velocity (km/s)
      llh[3],           // Latitude(deg), Longitude(deg), Height above Geoid (km)
      meanKep[6],       //Mean Keplerian elements
      oscKep[6],        //Osculating Keplerian elements
      nodalApPer[3];    //Nodal period, apogee, perigee

   // Load all SGP4-related data in one call - use this instead of two separate calls above
   Sgp4LoadFileAll(inFile);

   // Count number of satellites currently loaded in memory
   numSats = TleGetCount();
   if (numSats == 0)
   {
      printf("No TLEs were found in the input file\n");
      exit(1);
   }


   // Print header with output field names to files
   PrintHeader(fpOscState, FT_OSC_STATE);
   PrintHeader(fpOscElem, FT_OSC_ELEM);
   PrintHeader(fpMeanElem, FT_MEAN_ELEM);
   PrintHeader(fpLLH, FT_LLH_ELEM);
   PrintHeader(fpnodalApPer, FT_NODAL_AP_PER);


   // Using dinamic array
   pSatKeys = (__int64*)malloc(numSats * sizeof(__int64));

   // Get all the satellites' ids from memory and store them in the local array
   TleGetLoaded(order, pSatKeys);

   // Loop through all the TLEs in the input file
   for (i = 0; i < numSats; i++)
   {
      // Return the two strings, line1 line2, representing the TLE
      TleGetLines(pSatKeys[i], line1, line2);
      line1[INPUTCARDLEN - 1] = 0;
      line2[INPUTCARDLEN - 1] = 0;

      // Print TLE for each satellite
      fprintf(fpOscState, "\n\n %s\n %s\n\n", line1, line2);
      fprintf(fpOscElem, "\n\n %s\n %s\n\n", line1, line2);
      fprintf(fpMeanElem, "\n\n %s\n %s\n\n", line1, line2);
      fprintf(fpLLH, "\n\n %s\n %s\n\n", line1, line2);
      fprintf(fpnodalApPer, "\n\n %s\n %s\n\n", line1, line2);

      // Initialize the satellite before propagating it
      if (Sgp4InitSat(pSatKeys[i]) != 0)
         ShowMsgAndTerminate();

      TleGetField(pSatKeys[i], XF_TLE_EPOCH, valueStr);
      valueStr[GETSETSTRLEN - 1] = 0;
      epochDs50UTC = DTGToUTC(valueStr); // Convert epoch string to days since 1950 UTC

      // Compute start/stop times and step size from the input 6P card
      CalcStartStopTime(epochDs50UTC, &startTime, &stopTime, &stepSize);

      step = 0;
      ds50UTC = startTime;

      // Loop through all the time steps
      while (1)
      {
         if (stepSize >= 0 && ds50UTC >= stopTime)
            break;
         else if (stepSize < 0 && ds50UTC <= stopTime)
            break;

         ds50UTC = startTime + (step * stepSize / 1440.0);

         if ((stepSize >= 0 && ds50UTC + (EPSI / 86400) > stopTime) ||
            (stepSize < 0 && ds50UTC - (EPSI / 86400) < stopTime))
            ds50UTC = stopTime;

         // Propagate the current satellite to the time specified in days since 1950 UTC
         errCode = Sgp4PropDs50UTC(pSatKeys[i], ds50UTC, &mse, pos, vel, llh);

         // Error or decay condition
         if (errCode != 0)
         {
            GetLastErrMsg(errMsg);
            errMsg[LOGMSGLEN - 1] = 0;

            // Display error message to screen
            printf("%s\n", errMsg);

            // Write error message to files
            fprintf(fpOscState, "%s\n", errMsg);
            fprintf(fpOscElem, "%s\n", errMsg);
            fprintf(fpMeanElem, "%s\n", errMsg);
            fprintf(fpLLH, "%s\n", errMsg);
            fprintf(fpnodalApPer, "%s\n", errMsg);

            break; // Move to the next satellite
         }


         //Compute/Retrieve other propagator output data
         //----------------------------------------------------------------
         Sgp4GetPropOut(pSatKeys[i], XF_SGP4OUT_OSC_KEP, oscKep);
         Sgp4GetPropOut(pSatKeys[i], XF_SGP4OUT_MEAN_KEP, meanKep);
         Sgp4GetPropOut(pSatKeys[i], XF_SGP4OUT_NODAL_AP_PER, nodalApPer);

         // Print position and velocity
         PrintPosVel(fpOscState, mse, pos, vel);

         // Print lat lon height and position
         PrintLLH(fpLLH, mse, llh, pos);

         // Print osculating Keplerian elements
         PrintOscEls(fpOscElem, mse, oscKep);

         // Print mean Keplerian elements
         PrintMeanEls(fpMeanElem, mse, meanKep);

         // Print nodal period, apogee, perigee, and others
         meanMotion = AToN(meanKep[0]);
         PrintNodalApPer(fpnodalApPer, mse, meanMotion, nodalApPer);

         // Height is below 100km - Skip the satellite
         if (llh[2] < 100.0)
         {
            if (llh[2] < 0)
               sprintf(errMsg, "Warning: Decay condition. Distance from the Geoid (Km) = %10.3lf\n", llh[2]);
            else
               sprintf(errMsg, "Warning: Height is low. HT (Km) = %10.3lf\n", llh[2]);

            // Write error message to files
            fprintf(fpOscState, "%s\n", errMsg);
            fprintf(fpOscElem, "%s\n", errMsg);
            fprintf(fpMeanElem, "%s\n", errMsg);
            fprintf(fpLLH, "%s\n", errMsg);
            fprintf(fpnodalApPer, "%s\n", errMsg);

            break; // Move to the next satellite
         }

         step++;
      }

      // Remove this satellite if no longer needed
      if (Sgp4RemoveSat(pSatKeys[i]) != 0)
         ShowMsgAndTerminate();
   }

   // Clean up after each job
   TleRemoveAllSats();
   Sgp4RemoveAllSats();
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

// Print title for the output files
void PrinTitle(FILE* fp, char* infoStr, char* inFile)
{
   fprintf(fp, "%s\n\n\n", infoStr);

   fprintf(fp, "%s\n", "EPHEMERIS GENERATED BY SGP4 USING THE WGS-72 EARTH MODEL");
   fprintf(fp, "%s\n", "COORDINATE FRAME=TRUE EQUATOR AND MEAN EQUINOX OF EPOCH");
   fprintf(fp, "%s\n\n", "USING THE FK5 MEAN OF J2000 TIME AND REFERENCE FRAME");
   fprintf(fp, "%s%s\n", "INPUT FILE = ", inFile);
}

// Print header for the output files
void PrintHeader(FILE* fp, int fileType)
{
   int startFrEpoch, stopFrEpoch;
   double startTime, stopTime, stepSize;

   startFrEpoch = stopFrEpoch = 0;
   startTime = stopTime = stepSize = 0;

   // Get prediction control data 
   Get6P(&startFrEpoch, &stopFrEpoch, &startTime, &stopTime, &stepSize);
   if(startFrEpoch)
      fprintf(fp, "%s%14.4f%s\n", "Start Time = ", startTime, " min from epoch");
   else
      fprintf(fp, "%s%s\n", "Start Time = ", UTCToDtg20Str(startTime));


   if(stopFrEpoch)
      fprintf(fp, "%s%14.4f%s\n", "Stop Time  = ", stopTime,  " min from epoch");
   else
      fprintf(fp, "%s%s\n", "Stop Time  = ", UTCToDtg20Str(stopTime));

   fprintf(fp, "%s%14.4f%s\n\n\n", "Step size  = ", stepSize,  " min");

   if (fileType == FT_OSC_STATE)
   {
      fprintf(fp, "%s\n",
         "     TSINCE (MIN)           X (KM)           Y (KM)           Z (KM)      XDOT (KM/S)       YDOT(KM/S)    ZDOT (KM/SEC)");
   }
   else if (fileType == FT_OSC_ELEM)
   {
      fprintf(fp, "%s\n",
         "     TSINCE (MIN)           A (KM)          ECC (-)        INC (DEG)       NODE (DEG)      OMEGA (DEG)   TRUE ANOM(DEG)");
   }
   else if (fileType == FT_MEAN_ELEM)
   {
      fprintf(fp, "%s\n",
         "     TSINCE (MIN)     N (REVS/DAY)          ECC (-)        INC (DEG)       NODE (DEG)      OMEGA (DEG)         MA (DEG)");
   }
   else if (fileType == FT_LLH_ELEM)
   {
      fprintf(fp, "%s\n",
         "     TSINCE (MIN)         LAT(DEG)        LON (DEG)          HT (KM)           X (KM)           Y (KM)           Z (KM)");
   }
   else if (fileType == FT_NODAL_AP_PER)
   {
      fprintf(fp, "%s\n",
         "     TSINCE (MIN)   NODAL PER(MIN)1/NODAL(REVS/DAY)       N(REVS/DY)    ANOM PER(MIN)      APOGEE (KM)      PERIGEE(KM)");
   }
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


// Calculate start/stop times and step size from 6P card (TimeFunc dll)
void CalcStartStopTime(double epoch, double* tStart, double* tStop, double* tStep)
{
   int startFrEpoch, stopFrEpoch;
   double startTime, stopTime, stepSize;

   startFrEpoch = stopFrEpoch = 0;
   startTime = stopTime = stepSize = 0;

   // Get prediction control data from 6P card
   Get6P(&startFrEpoch, &stopFrEpoch, &startTime, &stopTime, &stepSize);

   // Compute start/stop times - using days since 1950 UTC
   // user selects start time in minutes since epoch
   if (startFrEpoch == 1) 
      *tStart = epoch + (startTime / 1440);
   else // user selects start time in days since 1950 UTC
      *tStart = startTime;
   
   // user selects stop time in minutes since epoch
   if (stopFrEpoch == 1)
      *tStop = epoch + (stopTime / 1440);
   else // user selects stop time in days since 1950 UTC
      *tStop = stopTime;

   if(*tStart > *tStop)
      *tStep = -fabs(stepSize);
   else
      *tStep = fabs(stepSize);
}
