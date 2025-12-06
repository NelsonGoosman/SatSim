#include "DllUtils.h"

#include "TimeFuncDll_Service.h"
#include "ObsDll_Service.h"

#include "../wrappers/TimeFuncDll.h"
#include "../wrappers/ObsDll.h"


int GetObsData(__int64 obsKey, ObsRecord* obs)
{
   int  errCode;
   
   char     secClass;
   int      satNum;
   int      senNum;
   double   obsTimeDs50UTC;
   double   elOrDec;
   double   azOrRA;
   double   range;
   double   rangeRate;
   double   elRate;
   double   azRate;
   double   rangeAccel;
   char     obsType;
   int      trackInd;
   int      ASTAT;
   int      siteTag;
   int      spadocTag;
   double   pos[3];
   double   vel[3];
   double   extArr[128];


   errCode = ObsGetAllFields(obsKey, &secClass, &satNum, &senNum, &obsTimeDs50UTC, 
                             &elOrDec, &azOrRA, &range, &rangeRate, &elRate, &azRate, 
                             &rangeAccel, &obsType, &trackInd, &ASTAT, &siteTag, &spadocTag, pos, vel, extArr);

   obs->secClass        = secClass;
   obs->satNum          = satNum;
   obs->senNum          = senNum;
   obs->obsTimeDs50UTC  = obsTimeDs50UTC;
   obs->elOrDec         = elOrDec;
   obs->azOrRA          = azOrRA;
   obs->range           = range;
   obs->rangeRate       = rangeRate;
   obs->elRate          = elRate;
   obs->azRate          = azRate;
   obs->rangeAccel      = rangeAccel;
   obs->obsType         = obsType;
   obs->trackInd        = trackInd;
   obs->astat           = ASTAT;
   obs->siteTag         = siteTag;
   obs->spadocTag       = spadocTag;
   obs->pos[0]          = pos[0];
   obs->pos[1]          = pos[1];
   obs->pos[2]          = pos[2];

   return errCode;
}


// Print ob header 
void PrintObsHeader(FILE* fpOut, char obsType)
{
   if (obsType == 'P' || obsType == 'V')
   {
      fprintf(fpOut, "  OBS A  TAG  SEN         TIME         OB       X          Y        Z  \n");
      fprintf(fpOut, "  NO. S  NO.  NO.  YY DDD HHMM SS.SSS CL/TP    (km)       (km)     (km)\n");
      fprintf(fpOut, " ======================================================================\n");
   }
   else
   {
      fprintf(fpOut, "  OBS A  TAG  SEN         TIME         OB    AZ/RT.A.   EL/DECL   RANGE    RG-RT\n");
      fprintf(fpOut, "  NO. S  NO.  NO.  YY DDD HHMM SS.SSS CL/TP   (deg)      (deg)     (km)   (km/s)\n");
      fprintf(fpOut, " ===============================================================================\n");
   }
}

// Print ob data
void PrintObsData(FILE* fpOut, int obsNum, ObsRecord* obs)
{
   char obsType;

   obsType = obs->obsType;

   fprintf(fpOut, " %4d %1d %5d %3d  %18s %c %c", obsNum, obs->astat, obs->satNum, obs->senNum, 
      UTCToDtg18Str(obs->obsTimeDs50UTC), obs->secClass, obsType);

   if ((obsType >= '1' && obsType <= '5') || obsType == '8' || obsType == '9' || obsType == 'M' || obsType == 'O')
      fprintf(fpOut, "   %8.4f%10.4f", obs->azOrRA, obs->elOrDec);
   else if (obsType == 'P' || obsType == 'V')
      fprintf(fpOut, "%11.3f%11.3f%11.3f", obs->pos[0], obs->pos[1], obs->pos[2]);

   if (obs->range != 0)
      fprintf(fpOut, "%11.3f", obs->range);

   if (obs->rangeRate != 0)
      fprintf(fpOut, "%7.4f", obs->rangeRate);

   fprintf(fpOut, "\n");
}

