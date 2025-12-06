#ifndef TLEDLL_SERVICE_H
#define TLEDLL_SERVICE_H

#include "DllUtils.h"


#define MAXNUMTLES 100000

// Structure of a TLE GP
typedef struct
{
   int     satNum;           // satNum: Satellite number
   char    secClass;         // secClass: Security classification U: unclass, C: confidential, S: Secret
   char    satName[9];       // satName: Satellite name A8
   int     epochYr;          // epochYr: Satellite's epoch year (2 or 4 digits)
   double  epochDays;        // epochDays: Satellite's epoch days
   double  bstar;            // bstar: B* drad term (1/ER)
   int     ephType;          // ephType: Satellite ephemeris type: 0=SGP, 2=SGP4
   int     elsetNum;         // elsetNum: Element set number
   double  incli;            // incli: Orbit inclination (deg)
   double  node;             // node: Right ascension of asending node (deg)
   double  eccen;            // eccen: Eccentricity
   double  omega;            // omega: Argument of perigee (deg)
   double  mnAnomaly;        // mnAnomaly: Mean anomaly (deg)
   double  mnMotion;         // mnMotion: Mean motion (rev/day) (ephType=0: Kozai, ephType=2: Brouwer)
   int     revNum;           // revNum: Revolution number at epoch
   double  nDotO2;           // nDotO2: Mean motion derivative (rev/day2)
   double  n2DotO6;          // n2DotO6: Mean motion second derivative (red/day3)
   double  epochDs50UTC;     // epoch in days since 1950, UTC
} TleGPRecord;


TleGPRecord LinesToTle(char* line1, char* line2);
void GetTlesFrFile(char* fileName, TleGPRecord** outTles, int* numTles);

#endif
