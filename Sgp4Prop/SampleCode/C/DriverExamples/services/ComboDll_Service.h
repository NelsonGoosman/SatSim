// This wrapper file was generated automatically by the A9\GenDllWrappers program.

#ifndef COMBODLL_SERVICE_H
#define COMBODLL_SERVICE_H


static const int 
   CARD_7P_FREPOCH = 0, 
   CARD_7P_FRDATE  = 1;


// Indexes of LAMOD 7P-card fields
static const int
   IDX_7P_TIMEFLAG = 1,       // Input time format : 0: Minutes since epoch, 1: UTC
   IDX_7P_BEGTIME = 2,        // Begin time
   IDX_7P_ENDTIME = 3,        // End time
   IDX_7P_RELMINFLG = 4,      // Control flag for computing relative minima
   IDX_7P_ABSMINFLG = 5,      // Control flag for computing absolute minimum
   IDX_7P_EETIMES = 6,        // Control flag for computing periods of close proximity
   IDX_7P_RELEPHFLG = 7,      // Control flag for computing relative ephemeris
   IDX_7P_POCSIGMA = 8,         // Control flag for computing probability of collision
   IDX_7P_RELMINLIM = 9,      // Maximum separation for relative minima
   IDX_7P_ABSMINLIM = 10,     // Close proximity limit
   IDX_7P_RELEPHINT = 11,     // Relative ephemeris sampling interval 
   IDX_7P_PRTOPT      = 12,   // Print options
   IDX_7P_PRADIUS     = 13,   // Primary satellite effective radius (m)
   IDX_7P_SRADIUS     = 14;   // Secondary satellite effective radius (m)

// Combo print options
static const int
   PRT_RELGEOONLY = 0,
   PRT_POSVEL     = 1,
   PRT_LLH        = 2, 
   PRT_RELPOS     = 3, 
   PRT_NOOUTPUT   = 4;


// Combo control parameters structure
typedef struct
{
   int      timeFlg;             // Input time flag. = 0: minutes from primary's epoch; = 1: input time is ds50UTC
   double   startTime;           // requested start time (MSE or ds50UTC depending on timeFlg)
   double   stopTime;            // requeste stop time (MSE or ds50UTC depending on timeFlg)

   int      relMinFlg;           // control for computing relative minima. 
                                 // 0 = do not compute relative minima
                                 // 1 = use analytical method (GP only)
                                 // 2 = use "brute force" method
   int      absMinFlg;           // control for computing absolute minimum: 0 = don't compute, 1 = compute

   int      closeProxFlg;        // control for computing periods of close proximity: 0 = don't compute, 1 = compute

   int      relEphFlg;           // control for computing relative ephemeris: 0 = don't compute, 1 = compute
   double   relMinLim;           // maximum separation for relative minima (km)
   double   closeProxLim;        // close proximity limit (km)
   double   relEphInterval;      // relative ephemeris sampling interval (min)

   int      prtOpt;              // print options:
                                 // 0 = relative geometry only
                                 // 1 = position/velocity (plus option 0)
                                 // 2 = lat, long, height (plus option 1)
                                 // 3 = relative position (plus option 2)
                                 // 4 = no output
   double   pocSigma;            // probability of collision sigma
   double   pRadius;             // primary satellite effective radius (m)
   double   sRadius;             // secondary satellite effective radius (m)
} ComboCtrl;


// Combo ouput data structure
typedef struct
{
   __int64  priSatKey;              // primary satellite key
   __int64  secSatKey;              // secondary satellite key
   double   absMinDs50UTC;          // time in ds50UTC at absolute minimum 
   double   absMinDist;             // absolute minimum distance in km
   double   relMinDs50UTCs[1000];   // array of times in ds50UTC of relative minima
   int      numOfRelMins;           // number of relative minima
   double   entryDs50UTCs[1000];    // array of entry times in ds50UTC
   double   exitDs50UTCs[1000];     // array of exit times in ds50UTC
   int      numOfEntryExits;        // number of entry/exit times
   int      errCode;                // returned error code
} ComboOutput;

void GetComboCtrlPara(ComboCtrl* comboCtrl);
void GetComboOutput(__int64 priSatKey, __int64 secSatKey, ComboOutput* comboOut);

void PrintComboCtrls(FILE* fpOut, ComboCtrl* comboCtrl);
void PrintClosestApproach(FILE* fp, ComboCtrl* comboCtrl, ComboOutput* comboOut);
void PrintComboHeader(FILE* fp, int priSatNum);
void PrintRelativeMinima(FILE* fp, ComboCtrl* comboCtrl, ComboOutput* comboOut, SatParms* priSatParms, SatParms* secSatParms);
void PrintRelativeEphemPts(FILE* fp, ComboCtrl* comboCtrl, __int64 priSatKey, __int64 secSatKey, double priEpochUTC, int secSatNum);
void PrintPriSecDeltas(FILE* fp, int secSatNum, double currDs50UTC, double* deltas, char atBoundary);
void PrintPriSecPosVel(FILE* fp, double* priPos, double* priVel, double* secPos, double* secVel);
void PrintPriSecLLH(FILE* fp, double* priLLH, double* secLLH);
void PrintPriSecRelPosVel(FILE* fp, double* deltas);
void ComputeStartStopDs50UTC(ComboCtrl* comboCtrl, double epochDs50UTC, double* startDs50UTC, double* stopDs50UTC);
void CalcAndPrintPOC(FILE* fp, double relMinDs50UTC, ComboCtrl* comboCtrl, ComboOutput* comboOut);
void CovMtx3x3(double covPosVelECI[6][6], double covPosECI[3][3]);
void PrintMinimaEphemPts(FILE* fp, ComboOutput* comboOut, ComboCtrl* comboCtrl, int secSatNum);
void PrintEphemSpan(FILE* fp, ComboCtrl* comboCtrl, __int64 priSatKey, __int64 secSatKey, int secSatNum, double startDs50UTC, double stopDs50UTC);


#endif
