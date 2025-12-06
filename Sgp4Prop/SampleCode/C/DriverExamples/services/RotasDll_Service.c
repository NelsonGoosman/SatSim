#include "DllUtils.h"
#include "RotasDll_Service.h"
#include "DllMainDll_Service.h"
#include "TimeFuncDll_Service.h"
#include "ElOpsDll_Service.h"
#include "SatStateDll_Service.h"

#include "../wrappers/ObsDll.h"
#include "../wrappers/RotasDll.h"
#include "../wrappers/SatStateDll.h"
#include "../wrappers/DllMainDll.h"



// Retrieve Rotas control data from the dll
void GetRotasCtrlPara(RotasCtrl* rotasCtrl)
{
   double extArr[128];
   RotasGetPAll(rotasCtrl->rotasMode, 
                &rotasCtrl->grossBeta, 
                &rotasCtrl->betaLimit, 
                &rotasCtrl->deltaTLimit, 
                &rotasCtrl->deltaHLimit, 
                &rotasCtrl->astat2Mult, 
                &rotasCtrl->prtFlag, 
                &rotasCtrl->retagFlag, 
                &rotasCtrl->ltcFlag, 
                &rotasCtrl->maxNumAssoc, 
                &rotasCtrl->debiasFlag,
                &rotasCtrl->diagMode, 
                &rotasCtrl->covPrtFlag, 
                &rotasCtrl->isTrackMode, 
                &rotasCtrl->remRetagObs, 
                extArr);

   rotasCtrl->rotasMode[5] = 0;
}

void PrintRotasCtrls(FILE* fpOut, RotasCtrl* rotasCtrl)
{
   char rotasModes[][41] = {"TAG  - associate vs tag on obs (verify) ",
                            "FTAG - force assoc of obs vs all elsets ",
                            "ALLEL - find best associations (RETAG)  "};

   char printModes[][31] = {"print all residuals           ", 
                            "print ASTAT 1 residuals only  ",
                            "print no residuals            ",
                            "print ASTAT 1/2 residuals only"};

   char retagModes[][34] = {"do not retag any obs             ",
                            "retag on ASCII file in B3 format ",
                            "retag on ASCII file in TTY format"};

   char ltcModes[][21]   = {"not applied         ",
                            "applied analytically",
                            "applied exactly     "};

   char debugModes[][24] = {"no debug prints        ",
                            "print debug information"};


   char dashLine[]  = "-------------------------------------------------------------------------------";
   char ddashLine[] = "===============================================================================";
   int  modeIdx, debugIdx;


   fprintf(fpOut, " %s\n", ddashLine);
   fprintf(fpOut, " |                          R O T A S   O P T I O N S                          |\n");
   fprintf(fpOut, " %s\n", dashLine);
   
   modeIdx = 0;

   if(strncmp(rotasCtrl->rotasMode, "TAG", 3) == 0)
      modeIdx = 0;
   else if(strncmp(rotasCtrl->rotasMode, "FTAG", 4) == 0)
      modeIdx = 1;
   else if(strncmp(rotasCtrl->rotasMode, "ALLEL", 5) == 0)
      modeIdx = 2;

   if(rotasCtrl->diagMode > 0)
      debugIdx = 1;
   else
      debugIdx = 0;

   fprintf(fpOut, "%s %-43s|\n",     
      " |  A.  ROTAS MODE:                ", rotasModes[modeIdx]);
   if(modeIdx == 2)
      fprintf(fpOut, "%s %-2d%41s|\n",     
         " |      > MAX # ASSOCIATIONS:      ", rotasCtrl->maxNumAssoc, " ");
   fprintf(fpOut, "%s %7.3f degrees%28s|\n",  
      " |  B.  GROSS BETA LIMIT:          ", rotasCtrl->grossBeta, " "); 
   fprintf(fpOut, "%s %7.3f degrees%28s|\n",  
      " |  C.  ASTAT 0 BETA LIMIT:        ", rotasCtrl->betaLimit, " ");
   fprintf(fpOut, "%s %7.3f minutes%28s|\n",  
      " |  D.  ASTAT 0 DELTA-T LIMIT:     ", rotasCtrl->deltaTLimit, " ");
   fprintf(fpOut, "%s %7.3f km%33s|\n",  
      " |  E.  ASTAT 0 DELTA-H LIMIT:     ", rotasCtrl->deltaHLimit, " ");
   fprintf(fpOut, "%s %1d%42s|\n",     
      " |  F.  ASTAT 2 MULTIPLIER:        ", rotasCtrl->astat2Mult, " ");
   fprintf(fpOut, "%s %-43s|\n",     
      " |  G.  RESIDUAL PRINT FLAG:       ", printModes[rotasCtrl->prtFlag - 1]);
   fprintf(fpOut, "%s %-43s|\n",     
      " |  H.  ASTAT 1 RETAG DISPOSITION: ", retagModes[rotasCtrl->retagFlag]); 
   fprintf(fpOut, "%s %-43s|\n",     
      " |  K.  LIGHT-TIME CORRECTION:     ", ltcModes[rotasCtrl->ltcFlag]); 
   fprintf(fpOut, "%s %-43s|\n",     
      " |  L.  TRACK PROCESSING?          ", rotasCtrl->isTrackMode  == 1 ? "yes" : "no "); 
   fprintf(fpOut, "%s %-43s|\n",     
      " |  M.  PRINT COVARIANCE?          ", rotasCtrl->covPrtFlag == 1 ? "yes" : "no ");  
   fprintf(fpOut, "%s %-43s|\n",     
      " |  Z.  DIAGNOSTIC PRINT OPTION:   ", debugModes[debugIdx]); 

   fprintf(fpOut, " %s\n\n", ddashLine);
}


void PrintAssocMultipliers(FILE* fpOut)
{
   char multStrs[][9] = { "BETA", "DELTA-T", "DELTA-HT" };
   int i, j, k;
   int assocMultArr[12];

   fprintf(fpOut, "              ASTAT 1 ASSOCIATION MULTIPLIERS:\n");
   fprintf(fpOut, " ========================================================\n");
   fprintf(fpOut, "             SYNCHRON    DEEP-SPC    DECAYING     ROUTINE\n");
   fprintf(fpOut, " --------------------------------------------------------\n");

   RotasGetAssocMultipliers(assocMultArr);


   for (i = 0; i < 3; i++)
   {
      k = i;
      fprintf(fpOut, "  %-9s   ", multStrs[i]);
      for (j = 0; j < 4; j++)
      {
         fprintf(fpOut, "%7d     ", assocMultArr[k]);
         k += 3;
      }
      fprintf(fpOut, "\n");
   }
   fprintf(fpOut, " ========================================================\n\n\n");
}


// Populate the obs residuals structure by calling the Rotas dll functions
// and assign the fields to the appropriate elements of the resulting residual array
void GetObsResiduals(__int64 obsKey, __int64 satKey, Residuals* residuals)
{
   double residualArr[100];
   double satElts[9];
   double obElts[9];

   residuals->errCode  = RotasComputeObsResiduals(obsKey, satKey, residualArr, satElts, obElts);
   ResidualArrToStruct(obsKey, satKey, residualArr, residuals);
}


// Populate residual structure from residual array
void ResidualArrToStruct(__int64 obsKey, __int64 satKey, double residualArr[], Residuals* residuals)
{
   residuals->astat              = (int)residualArr[XA_OBSRES_ASTAT];
   if (residuals->errCode != 0 || residuals->astat > 4)
   {
      return;
   }

   residuals->azimuth            = residualArr[XA_OBSRES_AZ];
   residuals->elevation          = residualArr[XA_OBSRES_EL];
   residuals->rightAscension     = residualArr[XA_OBSRES_RA];
   residuals->declination        = residualArr[XA_OBSRES_DEC];
   residuals->range              = residualArr[XA_OBSRES_RANGE];
   residuals->height             = residualArr[XA_OBSRES_HEIGHT];
   residuals->beta               = residualArr[XA_OBSRES_BETA];
   residuals->deltaT             = residualArr[XA_OBSRES_DELTAT];
   residuals->vmag               = residualArr[XA_OBSRES_VMAG];
   residuals->age                = residualArr[XA_OBSRES_AGE];
   residuals->satArgOfLatitude   = residualArr[XA_OBSRES_SU];
   residuals->revNum             = residualArr[XA_OBSRES_REVNUM];
   residuals->rangeRate          = residualArr[XA_OBSRES_RNGRATE];
   residuals->satTrueAnomaly     = residualArr[XA_OBSRES_SATANOM];
   residuals->satElevation       = residualArr[XA_OBSRES_SATELEV];
   residuals->obsType            = (int)residualArr[XA_OBSRES_OBSTYPE]; 
   residuals->astat              = (int)residualArr[XA_OBSRES_ASTAT];
   residuals->satCat             = (int)residualArr[XA_OBSRES_SATCAT];

   residuals->obsKey             = obsKey;
   residuals->satKey             = satKey;
   residuals->obsTimeDs50UTC     = residualArr[XA_OBSRES_OBSTIME];

   residuals->velAngle           = residualArr[XA_OBSRES_VELANG];
   residuals->angularMomentum    = residualArr[XA_OBSRES_ANGMOM];
}


int MaxPrintASTAT(int prtFlag)
{
   if(prtFlag == PRINT_ALL)
      return 4;
   else if(prtFlag == PRINT_ASTAT_01)
      return 1;
   else if(prtFlag == PRINT_ASTAT_012)
      return 2;
   else
      return -1; // print no residuals
}


void PrintRotasHeader(FILE* fpOut, int useNewFormat)
{
   if (useNewFormat) // print more decimal places
   {
      fprintf(fpOut, " A  NEW   OLD  STA  DATE   TIME          REV  U  O    DELTA    BETA      DELTA    RANGE     RA        DEC        VECTOR ORB  AGE   OBS P\n");
      fprintf(fpOut, " S  SAT   SAT  NO.  YY DDD HHMM SS.SSS   NO. DEG T    T MIN     DEG      H  KM   RES KM    RES DEG   RES DEG     MAG KM CLS  DAYS  NO. R\n");
      fprintf(fpOut, "========================================================================================================================================\n");
   }
   else // print less decimal places
   {
      fprintf(fpOut, " A  NEW   OLD  STA  DATE   TIME          REV  U  O    DELTA    BETA      DELTA    RANGE   RA      DEC        VECTOR ORB  AGE   OBS P\n");
      fprintf(fpOut, " S  SAT   SAT  NO.  YY DDD HHMM SS.SSS   NO. DEG T    T MIN     DEG      H  KM   RES KM  RES DEG RES DEG     MAG KM CLS  DAYS  NO. R\n");
      fprintf(fpOut, "====================================================================================================================================\n");
   }
}



void PrintObsResiduals(FILE* fpOut, ObsRecord* obs, int obsNum, Residuals* residuals, int useNewFormat)
{
   char SATCAT[][4] = {"SYN", "D-S", "DEC", "ROU"};

   char* formatStr;

   char propTypeChar;
   int isRangeComputed;
   int obsType = residuals->obsType;
   int isHigherPrecision = 1;
   SatParms satParms;
         
   // DHN 15Apr15 - obsType 18 and 19 are not considered as angle-only obs
   if (obsType == 1 || obsType == 5 || obsType % 10 == 8 || obsType % 10 == 9)
      isRangeComputed = 1;
   else
      isRangeComputed = 0;


   RetrieveSatParms(residuals->satKey, &satParms);

   if (satParms.propType == PROPTYPE_GP)
      propTypeChar = 'G';
   else if (satParms.propType == PROPTYPE_SP)
      propTypeChar = 'S';
   else if (satParms.propType == PROPTYPE_X)
      propTypeChar = 'X';
   else
      propTypeChar = ' ';

   //if(residuals->SatCat < 1 || residuals->SatCat > 4)
   if(residuals->satCat < 0 || residuals->satCat > 4)
   {
      printf("invalid satcat\n");
      exit(1);
   }

   if (useNewFormat)
      formatStr = " %1d %5d %5d %3d  %s %5d %3d %1d%9.4f%9.4f%10.3f%9.1f%c%10.5f%10.5f%11.3f %3s%6.2f%5d %c\n";
   else
      formatStr = " %1d %5d %5d %3d  %s %5d %3d %1d%9.4f%9.4f%10.3f%9.1f%c%8.3f%8.3f%11.3f %3s%6.2f%5d %c\n";

   fprintf(fpOut, formatStr,
      residuals->astat,
      satParms.satNum, // SatNumOf(residuals->SatKey),
      obs->satNum,
      obs->senNum,
      UTCToDtg18Str(obs->obsTimeDs50UTC),
      (int)residuals->revNum,
      (int)residuals->satArgOfLatitude,
      residuals->obsType,
      NonNegativeZero(residuals->deltaT, 4),
      NonNegativeZero(residuals->beta, 4),
      NonNegativeZero(residuals->height, 3),
      NonNegativeZero(residuals->range, 1),
      isRangeComputed ? 'C' : ' ',
      NonNegativeZero(residuals->rightAscension, 5),
      NonNegativeZero(residuals->declination, 5),
      NonNegativeZero(residuals->vmag, 3),
      SATCAT[residuals->satCat - 1],
      NonNegativeZero(residuals->age, 2),
      obsNum,
      propTypeChar);
}



void PrintBadObs(FILE* fpOut, ObsRecord* obs, int obsNum, int useNewFormat)
{
   char* formatStr;

   if (useNewFormat)
      formatStr = " %1d %5d %5d %3d  %s %-90s%5d\n";
   else
      formatStr = " %1d %5d %5d %3d  %s %-86s%5d\n";

   fprintf(fpOut, formatStr,
      4, 
      80000,
      obs->satNum,
      obs->senNum,
      UTCToDtg18Str(obs->obsTimeDs50UTC),
      "*** OB TOO FAR FROM EPOCH ***",
      obsNum);
}

void PrintNotAssociateObs(FILE* fpOut, ObsRecord* obs, int obsNum, int useNewFormat)
{
   char* formatStr;

   if (useNewFormat)
      formatStr = " %1d %5d %5d %3d  %s %-90s%5d\n";
   else
      formatStr = " %1d %5d %5d %3d  %s %-86s%5d\n";


   fprintf(fpOut, formatStr,
      4, 
      80000,
      obs->satNum,
      obs->senNum,
      UTCToDtg18Str(obs->obsTimeDs50UTC),
      "*** DID NOT ASSOCIATE ***",
      obsNum);
}

void PrintRotasError(FILE* fpOut, ObsRecord* obs, int obsNum, int useNewFormat)
{
   char  errMsg[LOGMSGLEN];

   GetLastErrMsg(errMsg);
   errMsg[78] = 0;

   char* formatStr;

   if (useNewFormat)
      formatStr = "   %s %5d %3d  %s <<< %82s >>>%5d\n";
   else
      formatStr = "   %s %5d %3d  %s <<< %78s >>>%5d\n";

   fprintf(fpOut, formatStr,
      "%%%%%",
      obs->satNum,
      obs->senNum,
      UTCToDtg18Str(obs->obsTimeDs50UTC),
      errMsg, 
      obsNum);
}


void PrintNoMatchingElset(FILE* fpOut, ObsRecord* obs, int obsNum, int useNewFormat)
{
   char  errMsg[LOGMSGLEN];

   GetLastErrMsg(errMsg);
   errMsg[78] = 0;

   char* formatStr;

   if (useNewFormat)
      formatStr = "   %s %5d %3d  %s <<< %-82s >>>%5d\n";
   else
      formatStr = "   %s %5d %3d  %s <<< %-78s >>>%5d\n";

   fprintf(fpOut, formatStr,
      "%%%%%",
      obs->satNum,
      obs->senNum,
      UTCToDtg18Str(obs->obsTimeDs50UTC),
      "N O   M A T C H I N G   E L S E T",
      obsNum);
}

// Check to see if the current obs meets the user's request for retag
int OKToRetag(int retagFlag, int ASTAT)
{
   if(retagFlag == RETAG_B3_ASTAT0_1 && ASTAT <= 1)
      return 1;
   else if(retagFlag == RETAG_B3_ASTAT0_2 && ASTAT <= 2)
      return 1;
   else if(retagFlag == RETAG_TTY_ASTAT0_1 && ASTAT <= 1)
      return 1;
   else
      return 0;
}


// Write the retagged obs (modified obs) to the specified output file
void DoRetagObs(FILE* fpOut, __int64 obsKey, int newTag, int retagFlag, int ASTAT)
{
   char ttyCard1[INPUTCARDLEN];
   char ttyCard2[INPUTCARDLEN];
   char b3Card[INPUTCARDLEN];
   char satNumStr[6];

   // new tag
   sprintf(satNumStr, "%05d", newTag);


   // Retag obs in B3 format
   if(retagFlag == RETAG_B3_ASTAT0_1 || retagFlag == RETAG_B3_ASTAT0_2)
   {
      // retrieve B3 card of the obs
      ObsGetB3Card(obsKey, b3Card);

      //.. and change tag
      strncpy(&b3Card[1], satNumStr, 5); 

      //... and change ASTAT
      b3Card[79] = (char)('0' + ASTAT);

      b3Card[90] = 0; // nullify B3 card

      // write modified obs to the output file
      fprintf(fpOut, "%s\n", b3Card);
   }
   // Retag obs in TTY format
   else if(retagFlag == RETAG_TTY_ASTAT0_1)
   {
      // retrieve TTY card of the obs
      ObsGetTTYCard(obsKey, ttyCard1, ttyCard2);
      ttyCard1[90] = 0;
      ttyCard2[90] = 0;

      //... and change tag
      strncpy(&ttyCard1[11], satNumStr, 5); 

      // write modified obs to the output file
      fprintf(fpOut, "%s\n", ttyCard1);

      // if second line is also available, write it to the output file as well
      if(ttyCard2[0] != 0 && ttyCard2[0] != ' ')
         fprintf(fpOut, "%s\n", ttyCard2);
   }
}
