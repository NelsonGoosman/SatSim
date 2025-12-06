
#include "DllUtils.h"
#include "BatchDCDll_Service.h"
#include "DllMainDll_Service.h"
#include "TimeFuncDll_Service.h"
#include "RotasDll_Service.h"


#include "../wrappers/DllMainDll.h"
#include "../wrappers/EnvConstDll.h"
#include "../wrappers/AstroFuncDll.h"
#include "../wrappers/BatchDCDll.h"
#include "../wrappers/TimeFuncDll.h"
#include "../wrappers/SpVecDll.h"
#include "../wrappers/TleDll.h"
#include "../wrappers/SpPropDll.h"
#include "../wrappers/ElOpsDll.h"
 

// Retrieve BatchDC control data from the dll
void GetBatchDCCtrlPara(BatchDCCtrl* batchDCCtrl)
{
   int xai_ctrl[MAX_PARAMS];
   double xar_ctrl[MAX_PARAMS];
   char xas_ctrl[INPUTCARDLEN];

   BatchDCGetParams(xai_ctrl, xar_ctrl, xas_ctrl);

   batchDCCtrl->printOption    = xai_ctrl[XAI_CTRL_PRINTOPTION  ];
   batchDCCtrl->debiasObs      = xai_ctrl[XAI_CTRL_DEBIASOBS    ];
   batchDCCtrl->weightedDC     = xai_ctrl[XAI_CTRL_WEIGHTEDDC   ];
   batchDCCtrl->epochOption    = xai_ctrl[XAI_CTRL_EPOCHOPTION  ];
   batchDCCtrl->correct_ag     = xai_ctrl[XAI_CTRL_CORRECT_AG   ];
   batchDCCtrl->correct_af     = xai_ctrl[XAI_CTRL_CORRECT_AF   ];
   batchDCCtrl->correct_psi    = xai_ctrl[XAI_CTRL_CORRECT_PSI  ];
   batchDCCtrl->correct_chi    = xai_ctrl[XAI_CTRL_CORRECT_CHI  ];
   batchDCCtrl->correct_l      = xai_ctrl[XAI_CTRL_CORRECT_L    ];
   batchDCCtrl->correct_n      = xai_ctrl[XAI_CTRL_CORRECT_N    ];
   batchDCCtrl->correct_b      = xai_ctrl[XAI_CTRL_CORRECT_B    ];
   batchDCCtrl->correct_agom   = xai_ctrl[XAI_CTRL_CORRECT_AGOM ]; 
   batchDCCtrl->correctOrder   = xai_ctrl[XAI_CTRL_CORRECTORDER ]; 
   batchDCCtrl->for1IterOnly   = xai_ctrl[XAI_CTRL_FOR1ITERONLY ]; 
   batchDCCtrl->corrType       = xai_ctrl[XAI_DCELTS_CORRTYPE];
   batchDCCtrl->residSelect    = xai_ctrl[XAI_CTRL_RESIDSELECT  ];
   batchDCCtrl->senPerform     = xai_ctrl[XAI_CTRL_SENPERFORM   ];
   batchDCCtrl->dwObsPerTrck   = xai_ctrl[XAI_CTRL_DWOBSPERTRCK ]; 
   batchDCCtrl->iterSumOpt     = xai_ctrl[XAI_CTRL_ITERSUMOPT   ];
   batchDCCtrl->partialMeth    = xai_ctrl[XAI_CTRL_PARTIALMETH  ];
   batchDCCtrl->ltc            = xai_ctrl[XAI_CTRL_LTC          ];
   batchDCCtrl->bruce          = xai_ctrl[XAI_CTRL_BRUCE        ];
   batchDCCtrl->propMethod     = xai_ctrl[XAI_CTRL_PROPMETHOD   ];
   batchDCCtrl->correctBVsX    = xai_ctrl[XAI_CTRL_CORRECTBVSX  ];
   batchDCCtrl->maxOfIters     = xai_ctrl[XAI_CTRL_MAXOFITERS   ];
   batchDCCtrl->usePredRMS     = xai_ctrl[XAI_CTRL_USEPREDRMS   ];

   batchDCCtrl->rmsMult        = xar_ctrl[XAR_CTRL_RMSMULT      ];
   batchDCCtrl->userEpoch      = xar_ctrl[XAR_CTRL_USEREPOCH    ];
   batchDCCtrl->frstPasDeltat  = xar_ctrl[XAR_CTRL_1STPASDELTAT];
   batchDCCtrl->cnvCritOnT     = xar_ctrl[XAR_CTRL_CNVCRITONT];
   batchDCCtrl->cnvcriton7elt  = xar_ctrl[XAR_CTRL_CNVCRITON7ELT];  
   batchDCCtrl->bReset         = xar_ctrl[XAR_CTRL_BRESET       ];

}

void PrintBatchDCCtrls(FILE* fpOut, BatchDCCtrl* batchDCCtrl, int isSpectr)
{
   char epochOptionStrs[][37] = {"nodal X-ing nearest/before latest ob", 
                                 "exactly at time of last ob", 
                                 "nodal X-ing nearest date specified", 
                                 "do not change epoch time", 
                                 "exactly at date to be specified", 
                                 "middle of obs span", 
                                 "time of earliest ob"};
      
   char printOptionStrs[][21] = {"first/best & summary", 
                                 "every pass & summary",
                                 "summary only", 
                                 "output elts only", 
                                 "print nothing"};

   char iterSumOptStrs[][20] = {"no Iter. Summary", 
                                 "Iter Sum (Kep elts)", 
                                 "Iter Sum (Eqn elts)"};

   char yesNo[][4] = { "no", "yes" };

   char correctOrderStrs[][32] = {"correct 7-elt only",
                                    "correct time, then 7-elt",                                  
                                    "correct time, plane, then 7-elt",                           
                                    "correct plane, time, then 7-elt",                           
                                    "correct plane, then 7-elt",                                 
                                    "correct n, then 7-elt",                                     
                                    "correct L, then 7-elt",                                     
                                    "correct L & n, then 7-elt",                                 
                                    "correct Af/Ag/L/n, then 7-elt",                             
                                    "correct 6-elt, then 7-elt",                                 
                                    "correct 7-elt only",                                        
                                    "correct L, n, & B, then 7-elt",                             
                                    "cor 7-elt (pht/pi vs. Af/Ag)",                              
                                    "cor 7-elt (e/pi vs. Af/Ag)",                                
                                    "cor L,n,B, then 7elt (pht/pi)"};

   char for1IterOnlyStrs[][38] = {"iterate subset to convergence",
                                    "correct subset for one iteration only"};

   char usePredRMSStrs[][34] = {"use previous rms for convergence",
                                 "use predicted rms for convergence"};

   char ltcStrs[][29] = { "will not be applied", 
                           "will be applied analytically",
                           "will be applied exactly" };

   char resComMethStrs[][11] = {"SPADOC 4",
                                "DELTA/427M"};
   int corrOrdIdx;
   int isSP;
   int isXP;

   isSP = (batchDCCtrl->propMethod == 99);
   isXP = (batchDCCtrl->propMethod == 4);


   fprintf(fpOut, "%s BATCH DC OPTIONS\n", isSP ? "SP" : "SGP4");
   fprintf(fpOut, "===============================================================================\n");
   fprintf(fpOut, " A.  PRINTOUT CONTROL FLAG        : %-40s\n", printOptionStrs[batchDCCtrl->printOption]);
   fprintf(fpOut, " C.  DEBIAS & WEIGHTED DC FLAGS   : %s debias obs; %sweighted DC\n", batchDCCtrl->debiasObs ? "" : "do not", batchDCCtrl->weightedDC ? "" : "un");
   if (batchDCCtrl->bruce == 0)
      fprintf(fpOut, "     %sWEIGHTED 1st PASS REJ. CRIT: %10.2f km\n", batchDCCtrl->weightedDC ? "" : "UN", 100.0);
   

   fprintf(fpOut, " D.  RMS MULTIPLIER               : %5.2f\n", batchDCCtrl->rmsMult);
   fprintf(fpOut, " E.  EPOCH PLACEMENT              : %s\n", epochOptionStrs[batchDCCtrl->epochOption]);
   if (batchDCCtrl->epochOption == 2 || batchDCCtrl->epochOption == 4 && batchDCCtrl->userEpoch > 0)
      fprintf(fpOut, "        SPECIFIED EPOCH           : %s (YYDDDHHMMSS.SSS)\n", UTCToDtg15Str(batchDCCtrl->userEpoch));


   fprintf(fpOut, " F.  ITER. or PERFORMANCE AN.SUMM : %s; %sPerf Anal Summary\n", iterSumOptStrs[batchDCCtrl->iterSumOpt], batchDCCtrl->senPerform ? "" : "no ");
   fprintf(fpOut, " G.  ELT CORRECTION FLAGS       L : %s\n", yesNo[batchDCCtrl->correct_l]);
   fprintf(fpOut, " H.                             N : %s\n", yesNo[batchDCCtrl->correct_n]);
   fprintf(fpOut, " I.                         %5s : %s\n", (isSP || isXP) ? "BTERM" : "BSTAR", yesNo[batchDCCtrl->correct_b]);
   fprintf(fpOut, " J.                     CHI & PSI : %s\n", yesNo[batchDCCtrl->correct_chi]);
   fprintf(fpOut, " K.                       AF & AG : %s\n", yesNo[batchDCCtrl->correct_psi]);

   // print subset order/control flags
   if (isSP && batchDCCtrl->correctOrder < 5)
      corrOrdIdx = batchDCCtrl->correctOrder + 10;
   else
      corrOrdIdx = batchDCCtrl->correctOrder;
   fprintf(fpOut, " L.  SUBSET/CORRECTION ORDER      : %s\n", correctOrderStrs[corrOrdIdx]);

   if (batchDCCtrl->correctOrder > 0)
      fprintf(fpOut, " M.  SUBSET CONTROL FLAG          : %s\n", for1IterOnlyStrs[batchDCCtrl->for1IterOnly]);

   fprintf(fpOut, " N.  1st-PASS delta-T REJECT CRIT : %6.2f min\n", batchDCCtrl->frstPasDeltat);

   // print BRUCE(no rejection) flag
   fprintf(fpOut, " O.  DO NOT REJECT RESIDUALS FOR  : %2d iterations\n", batchDCCtrl->bruce);

   if (isSP)
      fprintf(fpOut, " P.  PARTIALS COMPUTATION METHOD  : %s\n", batchDCCtrl->partialMeth ? "numerical" : "analytical");

   // print convergence criteria
   fprintf(fpOut, " R.  TIME/7-ELT CONVERGENCE CRIT  : %4.2f / %4.2f percent\n", batchDCCtrl->cnvCritOnT, batchDCCtrl->cnvcriton7elt);

   // print max iterations to convergence
   fprintf(fpOut, " S.  MAX # ITERATIONS TO CONVERGE : %2d iterations\n", batchDCCtrl->maxOfIters);

   // print predicted RMS control
   fprintf(fpOut, " T.  PREDICTED RMS CONTROL        : %s\n", usePredRMSStrs[batchDCCtrl->usePredRMS]);

   // print track-deweighting flag
   fprintf(fpOut, " U.  TRACK DEWEIGHTING ?          : %s\n", yesNo[batchDCCtrl->dwObsPerTrck]);

   // print alternate drag correction controls
   if (isSP || isXP)
      fprintf(fpOut, " V.  CORRECT  AGOM ?              : %s\n", yesNo[batchDCCtrl->correct_agom]);
   else
   {
      if (batchDCCtrl->correct_b)
         fprintf(fpOut, " V.  CORRECT X or DRAG TERM ?     : %s\n", batchDCCtrl->correctBVsX == 1 ? "DRAG TERM" : "X");
      else
         fprintf(fpOut, " V.  CORRECT X or DRAG TERM ?     : neither\n");

   }

   // print light-time correction control
   fprintf(fpOut, " W.  LIGHT-TIME CORRECTION        : %s\n", ltcStrs[batchDCCtrl->ltc]);

   fprintf(fpOut, " X.  RESIDs COMPUTATION METHOD    : %s\n", resComMethStrs[isSpectr]);

   fprintf(fpOut, "===============================================================================\n\n");


   return; 

}



void PrintBatchDCHeader(FILE* fpOut)
{
}


// Get resulting DC data by calling the BatchDC DLL and use that data to populate the dcElts structure
int GetDCElts(__int64 satKey, DcElts* dcElts)
{
   int errCode;
   int xai_dcElts[256];
   double xar_dcElts[256];
   char xas_dcElts[512];
   IterationData itDat; // iteration data won't be used


   // Calling the BatchDC dll
   errCode = BatchDCSolve(satKey, xai_dcElts, xar_dcElts, xas_dcElts);

   if (errCode != IDX_ERR_ERROR)
   {
      PopulateDcElts(xai_dcElts, xar_dcElts, xas_dcElts, dcElts, &itDat);
   }

   return errCode;
}


void PopulateDcElts(int xai_dcElts[], double xar_dcElts[], char dcElStrs[], DcElts* dcElts, IterationData* itDat)
{
   dcElts->satNum = xai_dcElts[XAI_DCELTS_SATNUM];
   dcElts->elsetNum = xai_dcElts[XAI_DCELTS_ELSETNUM];
   dcElts->orbType = xai_dcElts[XAI_DCELTS_ORBTYPE];
   dcElts->propType = xai_dcElts[XAI_DCELTS_PROPTYPE];
   dcElts->spectr = xai_dcElts[XAI_DCELTS_SPECTR];
   dcElts->revNum = xai_dcElts[XAI_DCELTS_REVNUM];
   dcElts->iterCount = xai_dcElts[XAI_DCELTS_ITERCOUNT];

   dcElts->epochDs50utc = xar_dcElts[XAR_DCELTS_EPOCHDS50UTC];
   dcElts->ndot = xar_dcElts[XAR_DCELTS_NDOT];
   dcElts->n2dot = xar_dcElts[XAR_DCELTS_N2DOT];
   dcElts->bfield = xar_dcElts[XAR_DCELTS_BFIELD];
   dcElts->agom = xar_dcElts[XAR_DCELTS_AGOM];
   dcElts->ogParm = xar_dcElts[XAR_DCELTS_OGPARM];
   dcElts->a = xar_dcElts[XAR_DCELTS_KEP_A];
   dcElts->e = xar_dcElts[XAR_DCELTS_KEP_E];
   dcElts->incli = xar_dcElts[XAR_DCELTS_KEP_INCLI];
   dcElts->ma = xar_dcElts[XAR_DCELTS_KEP_MA];
   dcElts->node = xar_dcElts[XAR_DCELTS_KEP_NODE];
   dcElts->omega = xar_dcElts[XAR_DCELTS_KEP_OMEGA];
   dcElts->af = xar_dcElts[XAR_DCELTS_EQNX_AF];
   dcElts->ag = xar_dcElts[XAR_DCELTS_EQNX_AG];
   dcElts->chi = xar_dcElts[XAR_DCELTS_EQNX_CHI];
   dcElts->psi = xar_dcElts[XAR_DCELTS_EQNX_PSI];
   dcElts->l = xar_dcElts[XAR_DCELTS_EQNX_L];
   dcElts->n = xar_dcElts[XAR_DCELTS_EQNX_N];
   dcElts->posX = xar_dcElts[XAR_DCELTS_POSX];
   dcElts->posY = xar_dcElts[XAR_DCELTS_POSY];
   dcElts->posZ = xar_dcElts[XAR_DCELTS_POSZ];
   dcElts->velX = xar_dcElts[XAR_DCELTS_VELX];
   dcElts->velY = xar_dcElts[XAR_DCELTS_VELY];
   dcElts->velZ = xar_dcElts[XAR_DCELTS_VELZ];

   // iteration data
   itDat->subIter = xai_dcElts[XAI_DCELTS_SUBITER];
   itDat->numResAccepted = xai_dcElts[XAI_DCELTS_RESACC];
   itDat->numResRejected = xai_dcElts[XAI_DCELTS_RESREJ];
   itDat->corrType = xai_dcElts[XAI_DCELTS_CORRTYPE];
   memcpy(itDat->idc, &xai_dcElts[XAI_DCELTS_CORRFLGS], sizeof(itDat->idc));


   itDat->RMS = xar_dcElts[XAR_DCELTS_RMS];

   itDat->unweightedRMS = xar_dcElts[XAR_DCELTS_RMSUNWTD]; //unweighted RMS(km)
   itDat->deltaTRMS = xar_dcElts[XAR_DCELTS_DELTATRMS];    //delta T RMS(min)
   itDat->betaRMS = xar_dcElts[XAR_DCELTS_BETARMS];        //beta RMS(deg)
   itDat->deltaHRMS = xar_dcElts[XAR_DCELTS_DELTAHTRMS];   //delta height RMS(km)
   itDat->convValue = xar_dcElts[XAR_DCELTS_CONVQLTY];     //convergence value(km)
   itDat->predRMS = xar_dcElts[XAR_DCELTS_RMSPD];          //predicted RMS


   memcpy(itDat->xMatrix, &xar_dcElts[XAR_DCELTS_COVL], 9 * sizeof(double));

   itDat->xmax  = xar_dcElts[XAR_DCELTS_XMAX];
   itDat->xmax2 = xar_dcElts[XAR_DCELTS_XMAX2];
   itDat->xmax3 = xar_dcElts[XAR_DCELTS_XMAX3];
   itDat->xmax4 = xar_dcElts[XAR_DCELTS_XMAX4];
   itDat->patcl = xar_dcElts[XAR_DCELTS_PATCL];
   itDat->patch = xar_dcElts[XAR_DCELTS_PATCH];
   memcpy(itDat->eqnxCovMtx, &xar_dcElts[XAR_DCELTS_EQNXCOVMTX], 45 * sizeof(double));

   strncpy(dcElts->satName, dcElStrs, 8); 
   dcElts->satName[8] = 0;
}

void PopulateAccptCrit(double xa_ac[], AcceptanceCriteria* ac)
{
   ac->std_deltaEpoch = xa_ac[XA_AC_STD_EPOCH];
   ac->std_numRes = (int)xa_ac[XA_AC_STD_NORES];
   ac->std_acptPct = xa_ac[XA_AC_STD_PRCNTRES];
   ac->std_RMS = xa_ac[XA_AC_STD_RMS];
   ac->std_obsSpan = xa_ac[XA_AC_STD_OBSSPAN];
   ac->std_deltaW = xa_ac[XA_AC_STD_DELTAW];
   ac->std_deltaAbar = xa_ac[XA_AC_STD_DELTAABAR];
   ac->std_deltaN = xa_ac[XA_AC_STD_DELTAN];
   ac->std_deltaBTerm = xa_ac[XA_AC_STD_DELTAB];

   ac->act_deltaEpoch = xa_ac[XA_AC_ACT_EPOCH];
   ac->act_numRes = (int)xa_ac[XA_AC_ACT_NORES];
   ac->act_acptPct = xa_ac[XA_AC_ACT_PRCNTRES];
   ac->act_RMS = xa_ac[XA_AC_ACT_RMS];
   ac->act_obsSpan = xa_ac[XA_AC_ACT_OBSSPAN];
   ac->act_deltaW = xa_ac[XA_AC_ACT_DELTAW];
   ac->act_deltaAbar = xa_ac[XA_AC_ACT_DELTAABAR];
   ac->act_deltaN = xa_ac[XA_AC_ACT_DELTAN];
   ac->act_deltaBTerm = xa_ac[XA_AC_ACT_DELTAB];
}

void ObsRejFlgsToStruct(int obsRejFlgs[], ObsRejectionData* obsRej)
{
   obsRej->decayed    = obsRejFlgs[XA_REJFLG_DECAYED];
   obsRej->error      = obsRejFlgs[XA_REJFLG_ERROR];
   obsRej->azimuth    = obsRejFlgs[XA_REJFLG_RA];
   obsRej->beta       = obsRejFlgs[XA_REJFLG_BETA];
   obsRej->elevation  = obsRejFlgs[XA_REJFLG_DEC];
   obsRej->height     = obsRejFlgs[XA_REJFLG_HEIGHT];
   obsRej->range      = obsRejFlgs[XA_REJFLG_RANGE];
   obsRej->rangeRate  = obsRejFlgs[XA_REJFLG_RR];
   obsRej->time       = obsRejFlgs[XA_REJFLG_TIME];
}


void PrintResidualsHeader(FILE* fpOut)
{
   //               1     2          3           4    6   7    8     9    10    11    12:10  13    14:10  15 16:8    17 18:8    19  20:8       21:12  22 23    
   fprintf(fpOut, " TAG  STA  DATE   TIME        REV  U   R   DELTA  R    BETA  R     DELTA  R    RANGE   R    RA    R   DEC    R  RR RES      VECTOR RJ O\n");
   fprintf(fpOut, " NO.  NO. YY DDD HHMM SS.SSS  NO. DEG  J   T MIN  J    DEG   J     H  KM  J    RES KM  J RES DEG  J RES DEG  J  KM/SEC      MAG KM FL T\n");
   //fprintf(fpOut, "================================================================================================================================\n");
}

void PrintObResiduals(FILE* fpOut, BatchDCCtrl* batchDCCtrl, ObsRecord* obs, Residuals* residuals, ObsRejectionData* obsRej)
{

   char  rejFlg[3]; // rejection flag: '*': rejected, 'X': residual error, ' ': no rejection/no error
   char* formatStr;
   char  obRejErrStr[][28] = { "Sensor data retrieval error", "No sensor location found", "Residual computation error" };

   int obsType = residuals->obsType;

   // no residual data avaialable due to error
   if (obsRej->error != 0)
   {
      fprintf(fpOut, " %5d %3d %s  **** %s ****\n",
         obs->satNum,                                    // 1. tag no.
         obs->senNum,                                    // 2. sta no.
         UTCToDtg18Str(obs->obsTimeDs50UTC),             // 3. date time YY/DDD HHMM SS.SSS)
         obRejErrStr[obsRej->error - 1]);
      return;
   }


   if (batchDCCtrl->bruce != 0 || obs->obsType == 'P' || obs->obsType == 'V')
      strcpy(rejFlg, "NR");
   else if (obsRej->error == 100)
      strcpy(rejFlg, "XX");
   else if (obsRej->azimuth + obsRej->elevation + obsRej->range + obsRej->rangeRate > 0)
      sprintf(rejFlg, "*%1d", obsRej->azimuth + obsRej->elevation + obsRej->range + obsRej->rangeRate);
   else
      strcpy(rejFlg, "  ");


   //             1   2  3   4   6    7/8      9/10     11/12     13/14     15/16    17/18    19/20   21     22 23
   formatStr = "%5d %3d %s %5d %3.0f  %c%8.4f  %c%8.4f  %c%10.3f  %c%10.3f  %c%8.3f  %c%8.3f  %c%8.4f %11.3f %s %1d\n";

   fprintf(fpOut, formatStr,
      obs->satNum,                                    // 1. tag no.
      obs->senNum,                                    // 2. sta no.
      UTCToDtg18Str(obs->obsTimeDs50UTC),             // 3. date time YY/DDD HHMM SS.SSS
      (int)residuals->revNum,                         // 4. rev no. 
      residuals->satArgOfLatitude,                    // 6. u deg
      obsRej->time == 1 ? '*' : ' ',                  // 7. time rejection
      NonNegativeZero(residuals->deltaT, 4),          // 8. delta t (min)
      obsRej->beta == 1 ? '*' : ' ',                  // 9. delta beta rejection flag
      NonNegativeZero(residuals->beta, 4),            //10. beta (deg)
      obsRej->height == 1 ? '*' : ' ',                //11. delta height rejection flag 
      NonNegativeZero(residuals->height, 3),          //12. delta height (km)
      obsRej->range == 1 ? '*' : ' ',                 //13. range residual rejection flag
      NonNegativeZero(residuals->range, 3),           //14. range residual (km)
      obsRej->azimuth == 1 ? '*' : ' ',               //15. azimuth or RA residual rejection flag
      NonNegativeZero(residuals->rightAscension, 3),  //16. azimuth or RA residual (deg)
      obsRej->elevation == 1 ? '*' : ' ',             //17. elevation or declination residual rejection flag
      NonNegativeZero(residuals->declination, 3),     //18. elevation or declination residual (deg)
      obsRej->rangeRate == 1 ? '*' : ' ',             //19. range rate residual rejection flag
      NonNegativeZero(residuals->rangeRate, 4),       //20. range rate residual (km/sec)
      NonNegativeZero(residuals->vmag, 3),            //21. vector magnitude (km)
      rejFlg,                                         //22. rejection flag: 'NR'=no rejection
      residuals->obsType);                            //23. obs type      
}

void PrintAllObResiduals(FILE* fpOut, BatchDCCtrl* batchDCCtrl, int iterCount, __int64 satKey, __int64* pObsKeys, int numObs, double (*obsResArr)[100], int (*obsRejFlags)[32])
{
   Residuals residuals;
   ObsRejectionData obsRej;
   ObsRecord obs;
   int errCode;
   int i;


   fprintf(fpOut, "SATELLITE NO. %5d ---------------------------   BATCH    ITERATION NO.%3d\n", SatNumOf(satKey), iterCount);
   PrintResidualsHeader(fpOut);

   // print obs residuals
   for (i = 0; i < numObs; i++)
   {
      // Reset residual structure 
      memset(&residuals, 0, sizeof(Residuals));

      // populate obs residual structure using data received from the DC dll
      ResidualArrToStruct(pObsKeys[i], satKey, obsResArr[i], &residuals);


      ObsRejFlgsToStruct(obsRejFlags[i], &obsRej);

      errCode = GetObsData(pObsKeys[i], &obs);
      PrintObResiduals(fpOut, batchDCCtrl, &obs, &residuals, &obsRej);
   }

}


// Print DC iteration summary for each iteration
void PrintIterSum(FILE* fpOut, int satNum, BatchDCCtrl* batchDCCtrl, DcElts* updatedDcElts, DcElts* dcElts, IterationData* itDat)
{
   char* epochDays;
   char correctionType[6][7] = { "TIME ", "PLANE", "7-ELT", "IN-TRK", "8-ELT", "SUBELT" };
   char corrTypeStr[45];

   fprintf(fpOut, "\n");
   fprintf(fpOut, "X MATRIX:\n");
   fprintf(fpOut, "        L               N             CHI             PSI              AF              AG             BTERM           (n/a)           AGOM\n");
   fprintf(fpOut, "%15.8E %15.8E %15.8E %15.8E %15.8E %15.8E %15.8E %15.8E %15.8E \n",
      itDat->xMatrix[0],
      itDat->xMatrix[1],
      itDat->xMatrix[2],
      itDat->xMatrix[3],
      itDat->xMatrix[4],
      itDat->xMatrix[5],
      itDat->xMatrix[6],
      itDat->xMatrix[7],
      itDat->xMatrix[8]);

   fprintf(fpOut, "\n\n");
   fprintf(fpOut, "SATELLITE NO. %5d ---------------------------   BATCH    ITERATION NO.%3d\n", satNum, dcElts->iterCount);

   fprintf(fpOut, "%5d Residuals Accepted, %5d Residuals Rejected, RMS = %9.3f, Predicted RMS = %9.3f", 
      itDat->numResAccepted, itDat->numResRejected, itDat->RMS, itDat->predRMS);

   // DHN 25Jul2022 - this value has already been displayed in previous statement
   //if (batchDCCtrl->usePredRMS)
   //   fprintf(fpOut, ", Predicted RMS = %9.3f", itDat->predRMS);

   if (batchDCCtrl->weightedDC)
      fprintf(fpOut, ", Unweighted RMS = %9.3f km", itDat->unweightedRMS);
   fprintf(fpOut, "\n");

   fprintf(fpOut, "      (convergence quality indicator: %12.3f km)\n", itDat->convValue);
   
   GetCorrTypeStr(corrTypeStr, itDat->idc);
   fprintf(fpOut, "%s ITERATION NO.%3d CORRECTED THE FOLLOWING ELTS: %s\n\n", correctionType[itDat->corrType], itDat->subIter, corrTypeStr);

   epochDays = UTCToDtg17Str(dcElts->epochDs50utc);
   if (batchDCCtrl->iterSumOpt == ITER_SUM_KEP)
   {

      fprintf(fpOut, "ELEMENTS    EPOCH         RMS         E          I       NODE      OMEGA       M          N        BTERM      PERIOD    AGOM\n");
      fprintf(fpOut, "             DAY           KM                 DEGREES   DEGREES   DEGREES   DEGREES    REV/DAY     m**2/kg     MIN     m**2/kg\n");
      PrintKeplerianElts(fpOut, "UPDATED", &epochDays[5], 0, updatedDcElts);
      PrintKeplerianElts(fpOut, "CURRENT", &epochDays[5], itDat->RMS, dcElts);
   }
   else
   {
      fprintf(fpOut, "ELEMENTS    EPOCH         RMS       L        N      CHI         PSI         AF          AG         BTERM      PERIOD    AGOM\n");
      fprintf(fpOut, "             DAY           KM    DEGREES   REV/DAY                                                 m**2/kg     MIN     m**2/kg\n");
      PrintEquinoctialElts(fpOut, "UPDATED", &epochDays[5], 0, updatedDcElts);
      PrintEquinoctialElts(fpOut, "CURRENT", &epochDays[5], itDat->RMS, dcElts);
   }


   fprintf(fpOut, "\n\n");
}

void GetCorrTypeStr(char corrTypeStr[], int idc[])
{
   int i;
   char corrFlgStrs[][5] = { "L", "N", "CHI", "PSI", "AF", "AG", "B", "NA", "AGOM" };
   
   corrTypeStr[0] = 0;

   for (i = 0; i < 9; i++)
   {
      if (idc[i] > 0)
      {
         strcat(corrTypeStr, corrFlgStrs[i]);
         strcat(corrTypeStr, "  ");
      }
   }
}


void PrintKeplerianElts(FILE* fpOut, char* element, char* epochDays, double rms, DcElts* dcElts)
{
   fprintf(fpOut, "%7s  %12s %10.3f%11.7f%10.4f%10.4f%10.4f%10.4f %12.8f%12.8f%8.1f %12.8f\n", 
      element,
      epochDays, 
      rms,
      dcElts->e,
      dcElts->incli,
      dcElts->node,
      dcElts->omega,
      dcElts->ma,
      dcElts->n,
      dcElts->bfield,
      1440.0 / dcElts->n,
      dcElts->agom);
}

void PrintEquinoctialElts(FILE* fpOut, char* element, char* epochDays, double rms, DcElts* dcElts)
{
   fprintf(fpOut, "%7s  %12s %10.3f%9.4f%8.4f %11.8f %11.8f %11.8f %11.8f%11.8f%8.1f %12.8f\n",
      element,
      epochDays,
      rms,
      dcElts->l,
      dcElts->n,
      dcElts->chi,
      dcElts->psi,
      dcElts->af,
      dcElts->ag,
      dcElts->bfield,
      1440.0 / dcElts->n,
      dcElts->agom);
}

void PrintOutputElements(FILE* fpOut, DcElts* dcElts)
{
   char  line1[INPUTCARDLEN];
   char  line2[INPUTCARDLEN];
   char  card4P[INPUTCARDLEN];

   if (dcElts->propType == PROPTYPE_GP)
   {
      // TLE type 0 - GP
      CreateNewGpTle(dcElts, line1, line2);
      printf("%s\n%s\n", line1, line2);
      fprintf(fpOut, "%s\n", line1);
      fprintf(fpOut, "%s\n", line2);

      // TLE type 2 - SGP4
      //CreateNewSgp4Tle(dcElts, line1, line2);
      //fprintf(fpOut, "%s\n", line1);
      //fprintf(fpOut, "%s\n", line2);
   }
   else
   {
      // TLE type 6 - SP
      CreateNewSpTle(dcElts, line1, line2);
      printf("%s\n%s\n", line1, line2);
      fprintf(fpOut, "%s\n", line1);
      fprintf(fpOut, "%s\n", line2);

      // SP vector
      CreateNewSpVec(dcElts, line1, line2, card4P);
      printf("%s\n%s\n%s\n", line1, line2, card4P);
      fprintf(fpOut, "%s\n", line1);
      fprintf(fpOut, "%s\n", line2);
      fprintf(fpOut, "%s\n", card4P);
   }

}

// Create GP TLE (ephType = 0) by using the data stored in the dcELts structure
void CreateNewGpTle(DcElts* dcElts, char line1[], char line2[])
{
   int ephType;
   int year;
   double daysOfYear;
   double n;
   double agomOrNdotsqr;

   UTCToYrDays(dcElts->epochDs50utc, &year, &daysOfYear);

   n = dcElts->n; // Brouwer mean motion
   

   if (dcElts->orbType == ELTTYPE_TLE_XP) // XP
   {
      ephType = 4; // SGP4-XP DC
      agomOrNdotsqr = dcElts->agom;
   }
   else
   {
      ephType = 0; // SGP4 DC
      agomOrNdotsqr = dcElts->n2dot;
      n = BrouwerToKozai(dcElts->e, dcElts->incli, dcElts->n); // Kozai mean motion
   }

   // generate SP TLE from data fields
   TleGPFieldsToLines(dcElts->satNum, 'U', dcElts->satName, year, daysOfYear, dcElts->ndot, agomOrNdotsqr, dcElts->bfield, ephType, dcElts->elsetNum,
      dcElts->incli, dcElts->node, dcElts->e, dcElts->omega, dcElts->ma, n, dcElts->revNum, line1, line2);
   line1[80] = 0;
   line2[80] = 0;
}

// Create SGP4 TLE (ephType = 2) by using the data stored in the dcELts stucture
void CreateNewSgp4Tle(DcElts* dcElts, char line1[], char line2[])
{
   int year;
   double daysOfYear;

   UTCToYrDays(dcElts->epochDs50utc, &year, &daysOfYear);

   // generate SP TLE from data fields
   TleGPFieldsToLines(dcElts->satNum, 'U', dcElts->satName, year, daysOfYear, dcElts->ndot, dcElts->n2dot, dcElts->bfield, 2, dcElts->elsetNum,
      dcElts->incli, dcElts->node, dcElts->e, dcElts->omega, dcElts->ma, dcElts->n, dcElts->revNum, line1, line2);
   line1[80] = 0;
   line2[80] = 0;

}


// Create SP TLE (ephType = 6) by using the data stored in the dcELts stucture
void CreateNewSpTle(DcElts* dcElts, char line1[], char line2[])
{
   int year;
   double daysOfYear;


   UTCToYrDays(dcElts->epochDs50utc, &year, &daysOfYear);

   // generate SP TLE from data fields
   TleSPFieldsToLines(dcElts->satNum, 'U', dcElts->satName, year, daysOfYear, dcElts->bfield, dcElts->ogParm, dcElts->agom, dcElts->elsetNum,
      dcElts->incli, dcElts->node, dcElts->e, dcElts->omega, dcElts->ma, dcElts->n, dcElts->revNum, line1, line2);
   line1[80] = 0;
   line2[80] = 0;

}

// Create SPVEC by using the data stored in the dcElts structure
void CreateNewSpVec(DcElts* dcElts, char line1[], char line2[], char card4P[])
{
   double pos[3];
   double velMPS[3];

   pos[0] = dcElts->posX;
   pos[1] = dcElts->posY;
   pos[2] = dcElts->posZ;

   // SpVec takes velocity in m/s, need to convert vel from km/s to m/s
   velMPS[0] = dcElts->velX * 1000;
   velMPS[1] = dcElts->velY * 1000;
   velMPS[2] = dcElts->velZ * 1000;

   // generate osculating vector 1P/2P format
   SpVecFieldsToLines(pos, velMPS, 'U', dcElts->satNum, dcElts->satName, UTCToYYYYDDDHHMMSSsssStr(dcElts->epochDs50utc),
      dcElts->revNum, dcElts->elsetNum, dcElts->bfield, dcElts->agom, dcElts->ogParm, "TMDAT", line1, line2);
   line1[80] = 0;
   line2[80] = 0;

   SpGet4PCard(card4P);
   card4P[80] = 0;
}

// Print acceptance criteria
void PrintAcceptCrit(FILE* fpOut, __int64 satKey)
{
   int acpt = 3;
   double obsSpan = 5.3;
   double xa_ca[64];
   AcceptanceCriteria ac;

   BatchDCGetAccptCrit(satKey, xa_ca);

   PopulateAccptCrit(xa_ca, &ac);

   fprintf(fpOut, " ACCEPTANCE    NEW      NO.   PERCENT   RMS     OBSPAN     CHANGE      CHANGE      CHANGE               CHANGE\n");
   fprintf(fpOut, "  CRITERIA    EPOCH     RES     RES              DAYS     IN PLANE     IN ABAR      IN N                IN BTERM\n");
   fprintf(fpOut, "  STANDARD  %4.1f DAY %6d     %3.0f %6.1f KM   %5.1f    %6.3f DEG  %8.4f    %9.2e REV/DAY    %10.3e   m**2/kg\n",
      ac.std_deltaEpoch, ac.std_numRes, ac.std_acptPct, ac.std_RMS, ac.std_obsSpan, ac.std_deltaW, ac.std_deltaAbar, ac.std_deltaN, ac.std_deltaBTerm);
   fprintf(fpOut, "  ACTUAL    %4.1f DAY %6d     %3.0f %6.1f KM   %5.1f    %6.3f DEG  %8.4f    %9.2e REV/DAY    %10.3e   m**2/kg\n\n",
      ac.act_deltaEpoch, ac.act_numRes, ac.act_acptPct, ac.act_RMS, ac.act_obsSpan, ac.act_deltaW, ac.act_deltaAbar, ac.act_deltaN, ac.act_deltaBTerm);
}
