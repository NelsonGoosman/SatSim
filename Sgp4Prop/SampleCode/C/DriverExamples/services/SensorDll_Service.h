#ifndef SENSORDLL_SERVICE_H
#define SENSORDLL_SERVICE_H

#include <stdio.h>

static char SenOptVisFlgStr[4][43] = {"0- Accept All Passes",
                                      "1- Optical Visible Passes Only", 
                                      "2- Passes If Solar Aspect Angle < Max", 
                                      "3- Sen In Dark/No Restrctn on Sat (IR sen)"};

static char SenPlntryRstrtnStr[6][26] = {"0- All (sun, moon, earth)", 
                                         "1- Earth Only",
                                         "2- Moon Only", 
                                         "3- Sun Only", 
                                         "4- Sun, Moon Only", 
                                         "5- None"};


// Sensor location (S-Card) structure
typedef struct
{
   int      senNum;  
   double   astroLat;
   double   astroLon;
   double   senPos[3]; // sensor position ECR/EFG (km) or sensor LLH (deg/deg/km)
   char     senDesc[25];
   int      orbSatNum;
   char     secClass;
   int      senLocType; // sensor location type: 1=ECR, 2=EFG, 3=LLH
} SensorLocation;



// Sensor limits (1L-Card) structure
typedef struct
{
   int      senNum;           // sensor number/sensor key
   char     viewType;         // sensor viewing type
   char     obsType;          // sensor's observation type
   int      rngUnits;         // sensor's observation units
   double   maxRngLim;        // maximum range (km)
   double   minRngLim;        // minimum range (km)
   double   rrLim;            // range-rate limit (km/sec)
   char     boresight1;       // orbiting sensor boresight vector (U,V,W) for limits interval #1
   double   elLim1;           // first lower elevation limit (deg)
   double   elLim2;           // first upper elevation limit (deg)
   double   azLim1;           // first lower azimuth limit (deg)
   double   azLim2;           // first upper azimuth limit (deg)
   double   interval;         // look-angle interval (min)

   int      visFlg;           // flag; if set, select visual passes only
   int      rngLimFlg;        // flag; if set, check max range
   int      maxPPP;           // maximum number of looks per pass
   int      plntryRes;        // orbiting sensor planetary restrictions flag
   int      isSpecialSensor;  // special mobile sensor flag
} SensorLimits1L;


// Sensor limits (2L-Card) structure
typedef struct
{
   int      senNum;           // sensor number/sensor key

   char     boresight2;       // orbiting sensor boresight vector (U,V,W) for limits interval #1
   double   elLim3;           // second lower elevation limit (deg)
   double   elLim4;           // second upper elevation limit (deg)
   double   azLim3;           // second lower azimuth limit (deg)
   double   azLim4;           // second upper azimuth limit (deg)
   int      earthBckgrnd;     // flag; when set, allow earth in background (orbiting sensor only)
   double   earthLimb;        // orbiting sensor; earth limb exclusion distance (km)
   double   solarXAngle;      // orbiting sensor; sun/satellite exclusion angle (deg)
   double   lunarXAngle;      // orbiting sensor; moon/satellite exclusion angle (deg)
   double   minIlum;          // orbiting sensor min illumination angle (deg)
   double   twilit;           // ground site twilight offset angle (deg)
} SensorLimits2L;

const char* GetViewTypeStr(char viewType);
const char* GetObsTypeStr(char obsType);
const char* GetSenBoreVecStr(char boreVec);
int GetSensorData(__int64 senKey, SensorLocation* senLoc, SensorLimits1L* senLim1L, SensorLimits2L* senLim2L);
int GetSensorLocation(__int64 senKey, SensorLocation* senLoc);
int GetSensorLimits1L(__int64 senKey, SensorLimits1L* senLim1L);
int GetSensorLimits2L(__int64 senKey, SensorLimits2L* senLim2L);
int PrintSensorData(FILE* fp, __int64 senKey);




#endif
