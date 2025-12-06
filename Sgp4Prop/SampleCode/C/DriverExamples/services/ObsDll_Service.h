#ifndef OBSDLL_SERVICE_H
#define OBSDLL_SERVICE_H

// Structure of an observation 
typedef struct
{
   char     secClass;            // classification: 'U', 'C', 'S'
   int      satNum;              // tag number (0-99999)
   int      senNum;              // sensor number (1-998)
   char     obsType;             // ob type (0-11;16;18;19)
   int      trackInd;            // track position indicator
                                 // Start Track Ob  In Track Ob = 4; End Track Ob = 5
   int      astat;               // association status (ASTAT; 1-4)
   int      siteTag;             // Original satellite number
   double   obsTimeDs50UTC;      // ob time in ds50UTC 
   double   elOrDec;             // elevation/declination (deg)
   double   azOrRA;              // azimuth/right-ascension (deg)
   double   range;               // slant range (km)
   double   rangeRate;           // range-rate (km/sec)
   double   elRate;              // elevation-rate (deg/sec)
   double   azRate;              // azimuth-rate (deg/sec)
   double   rangeAccel;          // range-acceleration (deg/sec^2)
   int      spadocTag;
   double   pos[3];              // EFG position vector for obstype 8; 9 (m)
   //double XYZPos(3)            // ECI position vector for obstype V; P (m)
} ObsRecord;


int  GetObsData(__int64 obsKey, ObsRecord* obs);
void PrintObsHeader(FILE* fpOut, char obsType);
void PrintObsData(FILE* fpOut, int obsNum, ObsRecord* obs);

#endif
