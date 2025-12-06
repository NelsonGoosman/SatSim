#include "DllMainDll_Service.h"
#include "ElOpsDll_Service.h"
#include "TimeFuncDll_Service.h"
#include "ComboDll_Service.h"
#include "SatStateDll_Service.h"

#include "../wrappers/TimeFuncDll.h"
#include "../wrappers/SpPropDll.h"
#include "../wrappers/SatStateDll.h"
#include "../wrappers/ComboDll.h"
#include "../wrappers/SatStateDll.h"


// Retrieve COMBO control parameters from the COMBO dll
void GetComboCtrlPara(ComboCtrl* comboCtrl)
{
   int      timeFlg;       
   double   startTime;     
   double   stopTime;      
   int      relMinFlg;     
   int      absMinFlg;     
   int      closeProxFlg;  
   int      relEphFlg;     
   double   pocSigma;        
   double   relMinLim;     
   double   closeProxLim;  
   double   relEphInterval;
   int      prtOpt;        
   double   pRadius, sRadius;

   // Reset values of comboCtrl structure's
   memset(comboCtrl, 0, sizeof(ComboCtrl));
  
  
   // Calling Combo dll's function to get data
   ComboGet7pAll(&timeFlg, &startTime, &stopTime, &relMinFlg, &absMinFlg, &closeProxFlg, 
                 &relEphFlg, &pocSigma, &relMinLim, &closeProxLim, &relEphInterval, &prtOpt);

   // Populate comboCtrl
   comboCtrl->timeFlg =          timeFlg;       
   comboCtrl->startTime =        startTime;     
   comboCtrl->stopTime =         stopTime;      
   comboCtrl->relMinFlg =        relMinFlg;     
   comboCtrl->absMinFlg =        absMinFlg;     
   comboCtrl->closeProxFlg =     closeProxFlg;  
   comboCtrl->relEphFlg =        relEphFlg;     
   comboCtrl->pocSigma =           pocSigma;        
   comboCtrl->relMinLim =        relMinLim;     
   comboCtrl->closeProxLim =     closeProxLim;  
   comboCtrl->relEphInterval =   relEphInterval;
   comboCtrl->prtOpt =           prtOpt;        

   pRadius = GetDoubleField(ComboGet7pField, IDX_7P_PRADIUS);
   sRadius = GetDoubleField(ComboGet7pField, IDX_7P_SRADIUS);

   comboCtrl->pRadius = pRadius;
   comboCtrl->sRadius = sRadius;

}


// Print COMBO control paramters
void PrintComboCtrls(FILE* fpOut, ComboCtrl* comboCtrl)
{
   // control for computing relative minima
   char compRelMin[][4] ={"no ", "yes"};

   // print options
   char prtOptStr[][43] = {"relative geometry only                    ",  
                           "rel. geom & position/velocity             ",  
                           "rel. geom, pos/vel, & lat/long/height     ",  
                           "rel. geom, pos/vel, lat/long/ht, rel. pos.",  
                           "none                                      "};

   char dashLine[]  = "-------------------------------------------------------------------------------";
   char ddashLine[] = "===============================================================================";


   fprintf(fpOut, " %s\n", ddashLine);
   fprintf(fpOut, " |                          C O M B O   O P T I O N S                          |\n");
   fprintf(fpOut, " %s\n", dashLine);
   
   
   if (comboCtrl->timeFlg == CARD_7P_FRDATE)
   {
      fprintf(fpOut, " |  A.  TIME OF INTEREST START, UTC:   %-40s|\n", UTCToDtg20Str(comboCtrl->startTime));
      fprintf(fpOut, " |  B.  TIME OF INTEREST END  , UTC:   %-40s|\n", UTCToDtg20Str(comboCtrl->stopTime));
   }
   else
   {
      fprintf(fpOut, " |  A.  TIME OF INTEREST START, MSE:   %10.3f%30s|\n", comboCtrl->startTime, " ");
      fprintf(fpOut, " |  B.  TIME OF INTEREST END  , MSE:   %10.3f%30s|\n", comboCtrl->stopTime, " "); 
   }
   fprintf(fpOut, " |  C.  COMPUTE RELATIVE MINIMA?       %-40s|\n", compRelMin[comboCtrl->relMinFlg]);
   fprintf(fpOut, " |  D.  COMPUTE ABSOLUTE MINIMUM?      %-40s|\n", comboCtrl->absMinFlg == 1 ? "yes" : "no"); 
   fprintf(fpOut, " |  E.  FIND PERIODS CLOSE PROX.?      %-40s|\n", comboCtrl->closeProxFlg == 1 ? "yes" : "no");
   fprintf(fpOut, " |  F.  OUTPUT REL. EPHEMERIS PTs?     %-40s|\n", comboCtrl->relEphFlg == 1 ? "yes" : "no");
   fprintf(fpOut, " |  G.  MAX SEPARATION DISTANCE:       %10.3f km%27s|\n", comboCtrl->relMinLim, " ");
   fprintf(fpOut, " |  H.  CLOSE PROXIMITY LIMIT:         %10.3f km%27s|\n", comboCtrl->closeProxLim, " ");
   fprintf(fpOut, " |  I.  REL EPHEM OUTPUT INTERVAL:     %9.2f min%27s|\n", comboCtrl->relEphInterval, " ");
   fprintf(fpOut, " |  J.  PRINTED OUTPUT OPTION:      %-43s|\n", prtOptStr[comboCtrl->prtOpt]);
   if(comboCtrl->pocSigma == 0)
      fprintf(fpOut, " |  K.  PROBABILITY OF COLLISION:      %-40s|\n", "not requested");
   else
   {
      fprintf(fpOut, " |  K.  PROBABILITY OF COLLISION:   %6.3f sigma %-30s|\n", comboCtrl->pocSigma, " ");
      fprintf(fpOut, " |      PRIMARY EFFECTIVE RADIUS:   %6.1f meters%-30s|\n", comboCtrl->pRadius, " ");
      fprintf(fpOut, " |      SECDARY EFFECTIVE RADIUS:   %6.1f meters%-30s|\n", comboCtrl->sRadius, " ");
   }
   fprintf(fpOut, " %s\n\n", ddashLine);
}



// Get combo ouput data from the dll and store it into ComboOutput structure
void GetComboOutput(__int64 priSatKey, __int64 secSatKey, ComboOutput* comboOut)
{
   // Reset values of comboOutput structure's
   memset(comboOut, 0, sizeof(ComboOutput));

   // Populate comboOutput
   comboOut->priSatKey = priSatKey;
   comboOut->secSatKey = secSatKey;

   // Calling the Combo dll's function to return combo output data
   comboOut->errCode = ComboCompPriSec(priSatKey, secSatKey, 
      &comboOut->absMinDs50UTC, 
      &comboOut->absMinDist, 
      comboOut->relMinDs50UTCs, 
      &comboOut->numOfRelMins,
      comboOut->entryDs50UTCs, 
      comboOut->exitDs50UTCs, 
      &comboOut->numOfEntryExits);
}


// Print primatry/secondary closest approach
void PrintClosestApproach(FILE* fp, ComboCtrl* comboCtrl, ComboOutput* comboOut)
{
   int    priSatNum, secSatNum;
   char   priSatType[7], secSatType[7];
   SatParms priSatParms;
   SatParms secSatParms;

   RetrieveSatParms(comboOut->priSatKey, &priSatParms);
   RetrieveSatParms(comboOut->secSatKey, &secSatParms);

   priSatNum = priSatParms.satNum; // SatNumOf(comboOut->priSatKey);
   secSatNum = secSatParms.satNum; //SatNumOf(comboOut->secSatKey);


   // Primary/secondary passes different filters/tests
   if (comboOut->absMinDs50UTC == 0 || comboOut->absMinDist > 1.0E10)
   {
      fprintf(fp, " ... SECONDARY SATELLITE %5d NO CLOSE APPROACHES FOUND\n", secSatNum);
      return;
   }
   else if(comboOut->absMinDist < comboCtrl->closeProxLim)
   {
      strcpy(priSatType, GetRecTypeString(priSatParms.oet));
      strcpy(secSatType, GetRecTypeString(secSatParms.oet));
      fprintf(fp, " PRIMARY SAT %5d (%s) VS SECONDARY SAT %5d (%s):\n",
              priSatNum, priSatType, secSatNum, secSatType );
      PrintComboHeader(fp, priSatNum);
      if (comboCtrl->absMinFlg == 1 && comboCtrl->relMinFlg == 0)
      {
         fprintf(fp, "  %5d  %23s%11.3f   ****  ABSL MIN ; PRIM. SAT %5d  ****\n",
            secSatNum, UTCToDtg23Str(comboOut->absMinDs50UTC), comboOut->absMinDist, priSatNum);
         fprintf(fp, "___________________________________________________________________________________\n");
         fprintf(fp, "\n");

      }
      else
      {
         PrintRelativeMinima(fp, comboCtrl, comboOut, &priSatParms, &secSatParms);
      }
   }
}


// Print COMBO header
void PrintComboHeader(FILE* fp, int priSatNum)
{
   fprintf(fp,  " %5d            TIME             DISTANCE  REL VEL  DELTA-T  DELTA-BETA  DELTA-HT\n", priSatNum);
   fprintf(fp,  "  vs     YY DDD HH MM SS.SSSSSSS       km     km/sec   minutes   degrees       km   \n");
   fprintf(fp,  "____________________________________________________________________________________\n");
   fprintf(fp, "\n");
}


// Print absolute minimum if requested
void PrintAbsoluteMinimum(FILE* fp, ComboCtrl* comboCtrl, ComboOutput* comboOut)
{
   double absMinDs50UTC;
   int    priSatNum, secSatNum;

   priSatNum = SatNumOf(comboOut->priSatKey);
   secSatNum = SatNumOf(comboOut->secSatKey);

   absMinDs50UTC = comboOut->absMinDs50UTC;

   fprintf(fp, "   %5d  %23s%11.3f   ****  ABSL MIN ; PRIM. SAT %5d  ****",
      secSatNum, UTCToDtg23Str(comboOut->absMinDs50UTC), comboOut->absMinDist, priSatNum);
   fprintf(fp, "___________________________________________________________________________________\n");
   fprintf(fp, "\n");

}

// Print relative minima if requested
void PrintRelativeMinima(FILE* fp, ComboCtrl* comboCtrl, ComboOutput* comboOut, SatParms* priSatParms, SatParms* secSatParms)
{
   double deltas[100];
   double priPos[3];
   double priVel[3];
   double priLLH[3];
   double secPos[3];
   double secVel[3];
   double secLLH[3];

   double mse;
   int    revNum;
   double relMinDs50UTC;
   double ds50UTC;
   double startDs50UTC, stopDs50UTC;
   char   atBoundary;

   int k, count;
   int errCode;

   ComputeStartStopDs50UTC(comboCtrl, priSatParms->epochUTC, &startDs50UTC, &stopDs50UTC);

   count = 0; // number of entry/exit times

   // Loop through the array of times of relative minima
   for (k = 0; k < comboOut->numOfRelMins; k++)
   {
      relMinDs50UTC = comboOut->relMinDs50UTCs[k];

      // Compute deltas of primary/secondary at the current relative minima
      errCode = SatStateEphCom(comboOut->priSatKey, comboOut->secSatKey, relMinDs50UTC, 1, deltas);
      if (errCode != 0)
         ShowErrMsg();

      // Check to see if computing relative minima flag is on
      if(comboCtrl->relMinFlg != 0)
      {
         if(relMinDs50UTC == startDs50UTC || relMinDs50UTC == stopDs50UTC)
            atBoundary = 'B';
         else
            atBoundary = ' ';

         PrintPriSecDeltas(fp, secSatParms->satNum, relMinDs50UTC, deltas, atBoundary);
         
         // Add string to indicate the current relative minimum is the absolute minimum
         if(relMinDs50UTC == comboOut->absMinDs50UTC) 
            fprintf(fp, " ABSL MIN\n");
         else
            fprintf(fp, "\n");
      }

      if(comboCtrl->prtOpt > 0 && comboCtrl->prtOpt < 4)
      {
         // Compute and print primary/secondary position, velocity
         errCode = SatStateDs50UTC(comboOut->priSatKey, relMinDs50UTC, &mse, &revNum, priPos, priVel, priLLH);
         errCode = SatStateDs50UTC(comboOut->secSatKey, relMinDs50UTC, &mse, &revNum, secPos, secVel, secLLH);

         PrintPriSecPosVel(fp, priPos, priVel, secPos, secVel);

         // Print primary/secondary lat, long, height and relative position
         if(comboCtrl->prtOpt == 2 || comboCtrl->prtOpt == 3)
         {

            PrintPriSecLLH(fp, priLLH, secLLH);

            // Print relative position
            if (comboCtrl->prtOpt == 3)
            {
               PrintPriSecRelPosVel(fp, deltas);
            }
         }
      }

      // Check to see if control for computing periods of close proximity flag is on
      if(comboCtrl->closeProxFlg) 
      {
         // Note: the entry/exit times could be zeros which indicates that the entry/exit times are not available

         // Find the correct entry/exit times for this relative minimum
         if (((comboOut->entryDs50UTCs[count] != 0 && comboOut->entryDs50UTCs[count] > relMinDs50UTC) || 
            (comboOut->exitDs50UTCs[count] != 0 && relMinDs50UTC > comboOut->exitDs50UTCs[count])) && 
            count < comboOut->numOfEntryExits)
            count++;

         // If the secondary satellite is in sustained relative geometry, there could be 
         // multiple relative minima within that same entry/exit times
         if (comboOut->entryDs50UTCs[count] <= relMinDs50UTC && relMinDs50UTC <= comboOut->exitDs50UTCs[count] || 
             comboOut->entryDs50UTCs[count] == 0 || comboOut->exitDs50UTCs[count] == 0)
         {
            // Compute deltas at entry time
            memset(deltas, 0, sizeof(deltas));
            ds50UTC = comboOut->entryDs50UTCs[count];
            errCode = SatStateEphCom(comboOut->priSatKey, comboOut->secSatKey, ds50UTC, 1, deltas);
            if (errCode != 0)
               ShowErrMsg();

            if(comboOut->entryDs50UTCs[count] != 0)
               fprintf(fp, "%9s%s  %9.3f     ****  ENTRY TIME  ****\n", " ", 
                  UTCToDtg19aStr(comboOut->entryDs50UTCs[count]), deltas[XA_DELTA_POS]);

            // Compute deltas at exit time
            memset(deltas, 0, sizeof(deltas));
            ds50UTC = comboOut->exitDs50UTCs[count];
            errCode = SatStateEphCom(comboOut->priSatKey, comboOut->secSatKey, ds50UTC, 1, deltas);
            if (errCode != 0)
               ShowErrMsg();
            if(comboOut->exitDs50UTCs[count] != 0) 
               fprintf(fp, "%9s%s  %9.3f     ****  EXIT  TIME  ****\n", " ", 
                  UTCToDtg19aStr(comboOut->exitDs50UTCs[count]), deltas[XA_DELTA_POS]);

            //PrintEphemSpan(fp, comboCtrl, comboOut->priSatKey, comboOut->secSatKey, secSatParms, comboOut->entryDs50UTCs[count], comboOut->exitDs50UTCs[count]);
         }
      }

      // if requesting Probability of Collision, be sure input is compatible
      // Check to see if both primary/secondary satellites are VCMs
      if(comboCtrl->pocSigma != 0 && SatStateHasCovMtx(comboOut->priSatKey) && SatStateHasCovMtx(comboOut->secSatKey))
         CalcAndPrintPOC(fp, relMinDs50UTC, comboCtrl, comboOut);

   }

   fprintf(fp,  "___________________________________________________________________________________\n");
   fprintf(fp, "\n");

}


// Print primary/secondary relative ephemeris points
void PrintRelativeEphemPts(FILE* fp, ComboCtrl* comboCtrl, __int64 priSatKey, __int64 secSatKey, double priEpochUTC, int secSatNum)
{
   double startDs50UTC, stopDs50UTC;

   // No output
   if(comboCtrl->prtOpt == 4)
      return;

   ComputeStartStopDs50UTC(comboCtrl, priEpochUTC, &startDs50UTC, &stopDs50UTC);
   PrintEphemSpan(fp, comboCtrl, priSatKey, secSatKey, secSatNum, startDs50UTC, stopDs50UTC);
}

// Print primary/secondary relative ephemeris points
void PrintMinimaEphemPts(FILE* fp, ComboOutput* comboOut, ComboCtrl* comboCtrl, int secSatNum)
{
   double relMinDs50UTC;
   int count, k;

   // No output
   if (comboCtrl->prtOpt == 4)
      return;


   count = 0;

   // Loop through the array of times of relative minima
   for (k = 0; k < comboOut->numOfRelMins; k++)
   {
      relMinDs50UTC = comboOut->relMinDs50UTCs[k];

      // Check to see if control for computing periods of close proximity flag is on
      if (comboCtrl->closeProxFlg)
      {
         // Note: the entry/exit times could be zeros which indicates that the entry/exit times are not available

         // Find the correct entry/exit times for this relative minimum
         if (((comboOut->entryDs50UTCs[count] != 0 && comboOut->entryDs50UTCs[count] > relMinDs50UTC) ||
            (comboOut->exitDs50UTCs[count] != 0 && relMinDs50UTC > comboOut->exitDs50UTCs[count])) &&
            count < comboOut->numOfEntryExits)
            count++;

         // If the secondary satellite is in sustained relative geometry, there could be 
         // multiple relative minima within that same entry/exit times
         if (comboOut->entryDs50UTCs[count] <= relMinDs50UTC && relMinDs50UTC <= comboOut->exitDs50UTCs[count] ||
            comboOut->entryDs50UTCs[count] == 0 || comboOut->exitDs50UTCs[count] == 0)
         {
            if (comboOut->entryDs50UTCs[count] != 0 && comboOut->exitDs50UTCs[count] != 0)
            {
               PrintEphemSpan(fp, comboCtrl, comboOut->priSatKey, comboOut->secSatKey, secSatNum, comboOut->entryDs50UTCs[count], comboOut->exitDs50UTCs[count]);
            }
         }
      }
   }
}

void PrintEphemSpan(FILE* fp, ComboCtrl* comboCtrl, __int64 priSatKey, __int64 secSatKey, int secSatNum, double startDs50UTC, double stopDs50UTC)
{
   double currDs50UTC;

   double deltas[100];
   double priPos[3];
   double priVel[3];
   double priLLH[3];
   double secPos[3];
   double secVel[3];
   double secLLH[3];
   double mse;
   int    revNum;


   int errCode;

   // No output
   if (comboCtrl->prtOpt == 4)
      return;

   currDs50UTC = startDs50UTC;

   while (1)
   {
      // Compute deltas of primary/secondary at the current relative minima
      errCode = SatStateEphCom(priSatKey, secSatKey, currDs50UTC, 1, deltas);
      if (errCode != 0)
         ShowErrMsg();

      PrintPriSecDeltas(fp, secSatNum, currDs50UTC, deltas, ' ');
      fprintf(fp, "\n");

      // print only relative geometry
      if (comboCtrl->prtOpt != PRT_RELGEOONLY)
      {

         SatStateDs50UTC(priSatKey, currDs50UTC, &mse, &revNum, priPos, priVel, priLLH);
         SatStateDs50UTC(secSatKey, currDs50UTC, &mse, &revNum, secPos, secVel, secLLH);

         if (comboCtrl->prtOpt > PRT_RELGEOONLY)
            PrintPriSecPosVel(fp, priPos, priVel, secPos, secVel);

         if (comboCtrl->prtOpt > PRT_POSVEL)
            PrintPriSecLLH(fp, priLLH, secLLH);

         if (comboCtrl->prtOpt == PRT_RELPOS)
            PrintPriSecRelPosVel(fp, deltas);
      }

      if (currDs50UTC < stopDs50UTC)
      {
         currDs50UTC += (comboCtrl->relEphInterval / 1440.0);
         if (currDs50UTC > stopDs50UTC)
            currDs50UTC = stopDs50UTC;
      }
      else
         break;
   }
}


// Print primary/secondary deltas
void PrintPriSecDeltas(FILE* fp, int secSatNum, double currDs50UTC, double* deltas, char atBoundary)
{
   fprintf(fp,  " %c%5d  %23s%11.3f%8.3f%10.4f%10.4f%13.3f", 
           atBoundary, secSatNum, UTCToDtg23Str(currDs50UTC), deltas[XA_DELTA_POS], deltas[XA_DELTA_VEL],
           deltas[XA_DELTA_TIME] / 60.0, deltas[XA_DELTA_BETA], deltas[XA_DELTA_HEIGHT]);
}

// Print primary/secondary position and velocity
void PrintPriSecPosVel(FILE* fp, double* priPos, double* priVel, double* secPos, double* secVel)
{
   fprintf(fp, "%6sPRI.POS.(km)     X =%14.7f  Y =%14.7f  Z =%14.7f\n", " ", priPos[0], priPos[1], priPos[2]);
   fprintf(fp, "%6sSEC.POS.(km)     X =%14.7f  Y =%14.7f  Z =%14.7f\n", " ", secPos[0], secPos[1], secPos[2]);
   fprintf(fp, "%6sPRI.VEL.(km/sec) XD=%14.9f  YD=%14.9f  ZD=%14.9f\n", " ", priVel[0], priVel[1], priVel[2]);
   fprintf(fp, "%6sSEC.VEL.(km/sec) XD=%14.9f  YD=%14.9f  ZD=%14.9f\n", " ", secVel[0], secVel[1], secVel[2]);
}


// Print primary/secondary lat, long, height
void PrintPriSecLLH(FILE* fp, double* priLLH, double* secLLH)
{
   // Print lat, long, height
   fprintf(fp, "%6sPRI.GRND.TR.     NLT=%13.9f  ELG=%13.9f  HT=%14.7f\n", " ", priLLH[0], priLLH[1], priLLH[2]);
   fprintf(fp, "%6sSEC.GRND.TR.     NLT=%13.9f  ELG=%13.9f  HT=%14.7f\n", " ", secLLH[0], secLLH[1], secLLH[2]);

}
 
// Print primary/secondary relative position
void PrintPriSecRelPosVel(FILE* fp, double* deltas)
{
   fprintf(fp, "%6sREL.POS.(km)     DU=%14.7f  DV=%14.7f  DW=%14.7f\n", " ", 
           deltas[XA_DELTA_PRADIAL], deltas[XA_DELTA_PINTRCK], deltas[XA_DELTA_PCRSSTRCK]);
   fprintf(fp, "%6sREL.VEL.(km/sec) DU=%14.9f  DV=%14.9f  DW=%14.9f\n", " ", 
           deltas[XA_DELTA_VRADIAL], deltas[XA_DELTA_VINTRCK], deltas[XA_DELTA_VCRSSTRCK]);
}


// Compute start/stop time span based on the input times and primary satellite data
void ComputeStartStopDs50UTC(ComboCtrl* comboCtrl, double epochDs50UTC, double* startDs50UTC, double* stopDs50UTC)
{
   // Compute start/stop time in Ds50UTC
   if(comboCtrl->timeFlg == CARD_7P_FRDATE)
   {
      *startDs50UTC = comboCtrl->startTime;
      *stopDs50UTC =  comboCtrl->stopTime;
   }
   else
   {
      *startDs50UTC = MseToDs50UTC(epochDs50UTC, comboCtrl->startTime);
      *stopDs50UTC =  MseToDs50UTC(epochDs50UTC, comboCtrl->stopTime);
   }
}


// Compute and print probability of collision
void CalcAndPrintPOC(FILE* fp, double relMinDs50UTC, ComboCtrl* comboCtrl, ComboOutput* comboOut)
{
   int    revNum;          // Revolution number
   double mse;             // minutes since satellite's epoch
   double priPos[3];       // Position vector (km) 
   double priVel[3];       // Velocity vector (km/s) 
   double secPos[3];       // Position vector (km) 
   double secVel[3];       // Velocity vector (km/s) 

   double priCovXYZ[6][6];     
   double secCovXYZ[6][6];

   double priCovPosXYZ[3][3];
   double secCovPosXYZ[3][3];

   double llh[3];
   double pocArr[4];
   double mult_sqr, prob_sqr, mult_cir, prob_cir;
   int    errCode;
   


   // Propagate pri/sec satellites to the time of close approach
   SatStateDs50UTC(comboOut->priSatKey, relMinDs50UTC, &mse, &revNum, priPos, priVel, llh); 
   SatStateDs50UTC(comboOut->secSatKey, relMinDs50UTC, &mse, &revNum, secPos, secVel, llh); 

   // Retrieve XYZ covariance matrix
   SpGetCovMtx(comboOut->priSatKey, XF_COVMTX_XYZ_DATE, priCovXYZ); 
   SpGetCovMtx(comboOut->secSatKey, XF_COVMTX_XYZ_DATE, secCovXYZ); 


   // Extract the 3x3 matrix from the 6x6 covariance matrix
   CovMtx3x3(priCovXYZ, priCovPosXYZ);
   CovMtx3x3(secCovXYZ, secCovPosXYZ);


   // Compute probability of collision
   errCode = ComboPOC(priPos, priVel, priCovPosXYZ, comboCtrl->pRadius,
                      secPos, secVel, secCovPosXYZ, comboCtrl->sRadius,
                      XF_COVTYPE_ECI, pocArr);
   if (errCode != 0)
   {
      ShowErrMsg();
      return;
   }

   mult_sqr = pocArr[0];
   prob_sqr = pocArr[1] * 100.0;
   mult_cir = pocArr[2];
   prob_cir = pocArr[3] * 100.0;

   fprintf(fp, "Probability of Collision:  probability   n-Sigma    P/F\n");
   fprintf(fp, "                Standard:%13s%10.3f\n", " ", comboCtrl->pocSigma);
   fprintf(fp, "                Circle:  %13.3f%10.3f    %s\n", prob_cir, mult_cir, mult_cir <= comboCtrl->pocSigma ? "PASS" : "FAIL");
   fprintf(fp, "                Square:  %13.3f%10.3f    %s\n", prob_sqr, mult_sqr, mult_sqr <= comboCtrl->pocSigma ? "PASS" : "FAIL");
   fprintf(fp, "\n");
}


// Extract covariance matrix 3x3 from the covariance matrix 6x6
void CovMtx3x3(double covMtx_6x6[6][6], double covMtx_3x3[3][3])
{
   int row, col;

   for(row = 0; row < 3; row++)
      for(col = 0; col < 3; col++)
         covMtx_3x3[row][col] = covMtx_6x6[row][col];

}
