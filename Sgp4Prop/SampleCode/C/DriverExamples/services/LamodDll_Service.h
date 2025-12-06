#ifndef LAMODDLL_SERVICE_H
#define LAMODDLL_SERVICE_H

#include "../wrappers/DllMainDll.h"


#define MINSPERDAY       1440.0
#define EPSTIMEDAYS      (0.001 / 1440.0)  // This value is about 1msec


static int
   CARD_1P_FREPOCH = 0,     // Specified time span in minutes since epoch
   CARD_1P_FRDATE = 1;      // Specified time span in UTC  

// Lamod look mode
static int
   STEPMODE_CULM = 0,
   STEPMODE_STEP = 1,
   STEPMODE_TASK = 2;

// Indexes represent schedule modes
static char
   IDX_SCHED_OBS  = 'O',   // Obs schedule mode
   IDX_SCHED_PASS = 'P';   // Pass schedule mode


static char GenObsFlg[3][INPUTCARDLEN] = { "Do Not Form OBS",
                                "B3 OBS From Looks", 
                                "Transmission OBS From Looks"};

static char SenOptVisFlg[10][INPUTCARDLEN] = {"0- Accept All Passes", 
                                    "1- Optical Visible Passes Only", 
                                    "2- Passes If Solar Aspect Angle < Max", 
                                    "3- Sen In Dark/No Restrctn on Sat (IR sen)", 
                                    "","","","","",         /* 4 -> 8 is all null */
                                    "9- Use Limits Record Value"};

static char NosticFlg[4][INPUTCARDLEN] = {"None",
                                "Print sen/sat position at each look", 
                                "Print pass-by-pass diagnostics", 
                                "Print sen/sat position and diagnostics"};

// Lamod control parameters structure
typedef struct
{
   int    timeFlg;      // start/stop time format, 0: From Epoch, 1: From Date
   double startTime;    // start time (DS50, UTC) or MSE depending on timeFlg
   double stopTime;     // stop time (DS50, UTC) or MSE depending on timeFlg
   double stepSize;     // print interval (min)
   int    prtOpt;       // print flag
   int    punchObs;     // obs punch flag
   int    visFlg;       // visible looks flag
   int    stepMode;     // step mode flag, 0: culmination, 1: step
   char   schedMode;    // obsched or passched: Obsched = 'O', PassSched = 'P'
   int    diagMode;     // pass-by-pass diagnostic print flag: 
                        // 0:none, 
                        // 1:print sen/sat position at each look
                        // 2:print pass-by-pass diagnostics
                        // 3: both of 1&2
   double solAspAngle;  // solar aspect angle (only apply when visFlg >= 1)
} LamodCtrl;


// Sensor/Satellite pair data
typedef struct
{
   __int64  senKey;
   __int64  satKey;
   __int64  senSatKey;       // sensor/satellite pair unique key
   int      senNum;          // sensor number
   int      satNum;          // target satellite number
   char     viewType;        // sensor view type
   char     obsType;         // sensor observation type
   int      maxPtsPerPass;   // maximum points per pass
   int      stepMode;        // step mode flag, 0: culmination, 1: step
   int      optVisFlg;       // optical visibility flag
   double   startDs50TAI;    // start time (Ds50, TAI)
   double   stopDs50TAI;     // stop time (Ds50, TAI)
   double   interval;        // output interval (min)
   double   period;          // satellite's period (min)
} SenSatData;

// Look angle data
typedef struct
{
   int errCode;
   int lookCode;
   int satNum;
   __int64 satKey;
   int senNum;
   double lookTimeDs50UTC;
   double lookTimeMSE;
   //public string DDD_ddd
   //public string YYDDDHHMMSS
   double azimuth_deg;
   double elevation_deg;
   double range_km;
   double rangeRate_kmps;
   double RA_deg;
   double declination_degDec;
   double azRate_degps;
   double elRate_degps;
   double SAA_deg;
   char illumination;
   double relVel;

      
   double senPosEFG[3];
   double satPos[3];
   double satVel[3];
   double satLLH[3];
   double senPos[3];
   double senVel[3];
   double senLLH[3];


   int passVisual;
   int passAzLim;
   int passElLim;
   int passEarthBkgr;
   int passEarthOb;
   int passLunExcl;
   int passMaxRange;
   int passMinRange;
   int passPenEclip;
   int passRVelLim;
   int passSAALim;
   int passSolExcl;
   int passUmbEclip;

      
   double unitRangeVec[3];  // slant range unit vector (rho unit vector)

   int raHr;
   int raMin;
   double raSec;
   int decliDeg;
   int decliMin;
   double decliSec;

      
   double sunVec[3];

      
   double moonVec[3];

   double sunSenSat_deg;
   double sunEarthSat_deg;
   double sunEarthSen_deg;
   double moonSenSat_deg;
   double moonEarthSat_deg;
   double moonEarthSen_deg;
   int nBore1;
   int nBore2;
   double offBoreElev1_deg;
   double offBoreAzim1_deg;
   double offBoreElev2_deg;
   double offBoreAzim2_deg;


   int passNum;
} LookAngle;


void GetLamodCtrlPara(LamodCtrl* lamodCtrl);
int  GetSenSatData(__int64 senSatKey, __int64 senKey, __int64 satKey, SenSatData* senSatData);
void GetLookAngleData(SenSatData* senSatData, double currDs50TAI, LookAngle* look);

void PrintLamodCtrls(FILE* fpOut, LamodCtrl* lamodCtrl);
void PrintLook(FILE* fpOut, SenSatData* senSatData, char currStep, char* cobp, LookAngle* la);
void PrintObs(FILE* fpObsFile, __int64 senSatKey, int punchObs);
void PrintNosticData(FILE* fp, SenSatData* senSatData, int nosticFlg, LookAngle* la);
void PrintPassByPassNostic(FILE* fp, char viewType, LookAngle* la);
void PrintSenSatHeader(FILE* fpOut, SenSatData* senSatData); 
char CurrPrintStep(double currDs50TAI, double* rcs, double interval, double stopDs50TAI);
void PrintSummary(FILE* fpOut, int senNum, int satNum, int numLooks, int numPasses);
void PrintSenSatPosition(FILE* fp, char viewType, LookAngle* la);

#endif
