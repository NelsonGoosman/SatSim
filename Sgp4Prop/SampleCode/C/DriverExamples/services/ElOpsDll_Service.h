#ifndef ELOPSDLL_SERVICE_H
#define ELOPSDLL_SERVICE_H

#include "DllUtils.h"

#include "../wrappers/TleDll.h"
#include "../wrappers/SpVecDll.h"
#include "../wrappers/VcmDll.h"
#include "../wrappers/ExtEphemDll.h"


// Elest file types
static const int
   FILETYPE_TLE    = 1,
   FILETYPE_SPVEC  = 2,
   FILETYPE_VCM    = 3,
   FILETYPE_EXTEPH = 4;


// Satellite parameters structure
typedef struct
{
   int    errCode;
   double epochUTC;    // satellite's epoch in days since 1950, UTC
   double mnAnom;      // satellite's mean anomaly (deg)
   double node;        // satellite's right ascension of the asending node (deg) 
   double omega;       // satellite's argument of perigee (deg) 
   double period;      // satellite's period (min)
   double eccen;       // satellite's eccentricity (unitless)    
   double inclin;      // satellite's inclination (deg)
   double mnMotion;    // satellite's mean motion (revs/day)
   double bField;      // satellite's either SGP4 bStar (1/er) or SP bTerm (m2/kg)
   double perigeeHt;   // satellite's perigee height (km) 
   double apogeeHt;    // satellite's apogee height (km) 
   double perigee;     // satellite's perigee (km)
   double apogee;      // satellite's apogee (km)
   double A;           // satellite's semi major axis (km)
   int    satCat;      // satellite's category (1=Synchronous, 2=Deep space, 3=Decaying, 4=Routine)
   double cmOffset;    // satellite's center of mass offset (m)
   double lonE;        // satellite's east longitude east subpoint (deg) - only for synchronous orbits
   double drift;       // satellite's longitude drift rate (deg East/day) - only for synchronous orbits
   double omegaDot;    // satellite's omega rate of change (deg/day)
   double raDot;       // satellite's nodal precession rate (deg/day)
   double nodalPrd;    // satellite's nodal period (min)
   double nodalX;      // satellite's nodal crossing time prior to its epoch (ds50UTC)
   int    isGeo;       // satellite is GEO: 0=no, 1=yes
   double relEnergy;   // satellite's relative energy - only for GOBS
   int    satNum;      // satellite's relative energy - only for GOBS
   int    oet;         // satellite's orbital elset type - see OET_xxx for list of available values
   int    propType;    // satellite's propagation type - see PROPTYPE_xxx for list of available values
   int    elsetNum;    // satellite's element number
} SatParms;


void GetCurrLoadedSatKeys(int fileType, __int64** pSatKeys, int* numSats);
void SatKeysFrFile(int fileType, char* inputFile, __int64** newSatKeys, int* newNumSats);
double ComputePerigeeHt(double mnMotion, double eccen);
void RetrieveSatParms(__int64 satKey, SatParms* satParms);



#endif


