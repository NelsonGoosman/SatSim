#ifndef BATCHDCDLL_SERVICE_H
#define BATCHDCDLL_SERVICE_H

#include "DllUtils.h"
#include "ObsDll_Service.h"
#include "RotasDll_Service.h"



// BatchDC control parameters structure
typedef struct
{
   int printOption;           // DC print option
   int debiasObs;             // Apply biases from sensor file
   int weightedDC;            // Weighed DC flag
   int epochOption;           // Epoch placement control
   int correct_ag;            // Element correction flag - Ag
   int correct_af;            // Element correction flag - Af
   int correct_psi;           // Element correction flag - Psi
   int correct_chi;           // Element correction flag - Chi
   int correct_l;             // Element correction flag - L
   int correct_n;             // Element correction flag - N
   int correct_b;             // Element correction flag - B* (SGP4) B (SP)
   int correct_agom;          // Element correction flag - Agom (SP)
   int correctOrder;          // Correction order
   int corrType;              // See CORT_? for available values
   int for1IterOnly;          // Correct by the specified correction order for 1 iteration only
   int residSelect;           // Flag specifies which residuals are used for RMS calculation   convergence
   int senPerform;            // Flag; if set, produce sensor performance analysis summary
   int dwObsPerTrck;          // Flag; if set, deweight according to # of obs per track 
   int iterSumOpt;            // Iteration summary control
   int partialMeth;           // Partials method 
   int ltc;                   // Light time correction control
   int bruce;                 // Number of iteration to allow no auto rejection of residuals
   int propMethod;            // Propagation method
   int correctBVsX;           // Flag; if set, correct B* vs X
   int maxOfIters;            // Max # of iterations before declaring divergence
   int usePredRMS;            // Use predicted RMS versus previous RMS for convergence testing
   int resCompMethod;         // Residual computation method, 2=SPADOC-4, 1=DELTA/427M

   double rmsMult;            // RMS multiplier
   double userEpoch;          // Time of specified epoch
   double cnvCritOnT;         // Convergence criteria on time correction (%)
   double frstPasDeltat;      // First pass delta-t rejection criteria
   double cnvcriton7elt;      // Convergence criteria on 7-elt correction (%)
   double bReset;             // reset value for B term in subset correction
} BatchDCCtrl;


// Obs residual computation/rejection data
typedef struct
{
   int decayed;               //satellite has decayed at the time of the obs
   int error;                 //obs residual computation error code: 1: no sensor
   int azimuth;               //azimuth residual rejected
   int beta;                  //beta residual rejected
   int elevation;             //elevation residual rejected
   int height;                //delta h residual rejected
   int range;                 //range residual rejected
   int rangeRate;             //range rate residual rejected
   int time;                  //delta t residual rejected

} ObsRejectionData;


// DC iteration data
typedef struct
{
   int    subIter;            // sub iteration number
   int    numResAccepted;     // number of residuals accpeted
   int    numResRejected;     // number of residuals rejected
   int    corrType;           // correction type: 0=TIME, 1=PLANE", 2=7-ELT, 3=IN-TRK, 4=8-ELT, 5=SUBELT
   int    idc[9];             // corrected elts flags


   double RMS;                // RMS
   double unweightedRMS;      // unweighted RMS(km)
   double deltaTRMS;          // delta T RMS(min)
   double betaRMS;            // beta RMS(deg)
   double deltaHRMS;          // delta height RMS(km)
   double convValue;          // convergence value(km)
   double predRMS;            // predicted RMS(km)
   double xMatrix[9];         // X matrix L, N, CHI, PSI, AF, AG, BTERM, (n/a), AGOM
   double eqnxCovMtx[45];     // equinoctial covariance matrix - the lower triangular half 0-44

   double patcl;              // max partial residual (km) 
   double patch;              // max velocity resid (km/sec)
   double xmax;               // max beta residual (deg)
   double xmax2;              // max delta-t residual (min)
   double xmax3;              // low argument of latitude coverage (deg)
   double xmax4;              // high argument of latitude coverage (deg)
} IterationData;

// Acceptance criteria
typedef struct
{
   double std_deltaEpoch;     // standard - delta time (days) from epoch
   int    std_numRes;         // standard - number of residuals
   double std_acptPct;        // standard - residual acceptance percent
   double std_RMS;            // standard - RMS
   double std_obsSpan;        // standard - obs span (days)
   double std_deltaW;         // standard - change in plane (deg)
   double std_deltaAbar;      // standard - change in abar
   double std_deltaN;         // standard - change in N (rev/day)
   double std_deltaBTerm;     // standard - change in BTerm

   double act_deltaEpoch;     // actual - delta time (days) from epoch
   int    act_numRes;         // actual - number of residuals
   double act_acptPct;        // actual - residual acceptance percent
   double act_RMS;            // actual - RMS
   double act_obsSpan;        // actual - obs span (days)
   double act_deltaW;         // actual - change in plane (deg)
   double act_deltaAbar;      // actual - change in abar
   double act_deltaN;         // actual - change in N (rev/day)
   double act_deltaBTerm;     // actual - change in BTerm

} AcceptanceCriteria;


// DC elements 
typedef struct 
{
   int satNum;                // satellite number
   int elsetNum;              // elset number
   int orbType;               // elset's orbital type
   int propType;              // propagation method
   int spectr;                // spectr mode
   int revNum;                // epoch revolution number
   int iterCount;             // total iteration count


   double epochDs50utc;       // elset's epoch time in days since 1950 UTC
   double ndot;               // n-dot/2  (for SGP, eph-type = 0)
   double n2dot;              // n-double-dot/6  (for SGP, eph-type = 0)
   double bfield;             // either SGP4 bStar (1/er) or SP bTerm (m2/kg)
   double agom;               // SP agom (m**2/kg)
   double ogParm;             // SP outgassing parameter (km/s**2)
   double a;                  // semi major axis (km)
   double e;                  // eccentricity 
   double incli;              // inclination (deg)
   double ma;                 // mean anamoly (deg)
   double node;               // right ascension of the ascending node (deg)
   double omega;              // argument of perigee (deg)
   double af;                 // AF
   double ag;                 // AG
   double chi;                // CHI
   double psi;                // PSI
   double l;                  // mean longitude (deg)
   double n;                  // mean motion (revs/day)
   double posX;               // ECI posX (km)
   double posY;               // ECI posY (km)
   double posZ;               // ECI posZ (km)
   double velX;               // ECI velX (km/s)
   double velY;               // ECI velY (km/s)
   double velZ;               // ECI velY (km/s)

   char   satName[9];         // satellite international designator
} DcElts;



void PrintBatchDCHeader(FILE* fpOut);

void GetBatchDCCtrlPara(BatchDCCtrl* batchDCCtrl);
void PrintBatchDCCtrls(FILE* fpOut, BatchDCCtrl* batchDCCtrl, int isSpectr);
void PrintResidualsHeader(FILE* fpOut);
void PrintObResiduals(FILE* fpOut, BatchDCCtrl* batchDCCtrl, ObsRecord* obs, Residuals* residuals, ObsRejectionData* obsRej);
void PrintAllObResiduals(FILE* fpOut, BatchDCCtrl* batchDCCtrl, int iterCount, __int64 satKey, __int64* pObsKeys, int numObs, double (*obsResArr)[100], int (*obsRejFlags)[32]);
void PrintIterSum(FILE* fpOut, int satNum, BatchDCCtrl* batchDCCtrl, DcElts* updatedDcElts, DcElts* dcElts, IterationData* itDat);
void GetCorrTypeStr(char corrTypeStr[], int idc[]);
void PrintKeplerianElts(FILE* fpOut, char* element, char* epochDays, double rms, DcElts* dcElts);
void PrintEquinoctialElts(FILE* fpOut, char* element, char* epochDays, double rms, DcElts* dcElts);
void PrintOutputElements(FILE* fpOut, DcElts* dcElts);
int  GetDCElts(__int64 satKey, DcElts* dcElts);
void PopulateDcElts(int xai_dcElts[], double xar_dcElts[], char dcElStrs[], DcElts* dcElts, IterationData* itDat);
void ObsRejFlgsToStruct(int obsRejFlgs[], ObsRejectionData* obsRej);
void CreateNewGpTle(DcElts* dcElts, char line1[], char line2[]);
void CreateNewSgp4Tle(DcElts* dcElts, char line1[], char line2[]);
void CreateNewSpTle(DcElts* dcElts, char line1[], char line2[]);
void CreateNewSpVec(DcElts* dcElts, char line1[], char line2[], char card4P[]);
void PrintAcceptCrit(FILE* fpOut, __int64 satKey);

#endif

