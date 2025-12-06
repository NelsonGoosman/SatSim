#include "DllUtils.h"
#include "TleDll_Service.h"

#include "../wrappers/TleDll.h"
#include "../wrappers/TimeFuncDll.h"
#include "../wrappers/EnvConstDll.h"

TleGPRecord LinesToTle(char* line1, char* line2)
{
   TleGPRecord tle;

   int     satNum;
   char    secClass;
   char    satName[9];
   int     epochYr;
   double  epochDays;
   double  bstar;
   int     ephType;
   int     elsetNum;
   double  incli;
   double  node;
   double  eccen;
   double  omega;
   double  mnAnomaly;
   double  mnMotion;
   int     revNum;
   double  nDotO2;
   double  n2DotO6;

   TleParseGP(line1, line2, &satNum, &secClass, satName, &epochYr, &epochDays, &nDotO2, &n2DotO6, 
      &bstar, &ephType, &elsetNum, &incli, &node, &eccen, &omega, &mnAnomaly, &mnMotion, &revNum);

   tle.satNum = satNum;
   tle.secClass = secClass;
   satName[8] = 0;
   strcpy(tle.satName, satName);
   tle.epochYr = epochYr;
   tle.epochDays = epochDays;
   tle.nDotO2 = nDotO2;
   tle.n2DotO6 = n2DotO6;
   tle.bstar = bstar;
   tle.ephType = ephType;
   tle.elsetNum = elsetNum;
   tle.incli = incli;
   tle.node = node;
   tle.eccen = eccen;
   tle.omega = omega;
   tle.mnAnomaly = mnAnomaly;
   tle.mnMotion = mnMotion;
   tle.revNum = revNum;
   tle.epochDs50UTC = YrDaysToUTC(epochYr, epochDays);

   return tle;
}


void GetTlesFrFile(char* fileName, TleGPRecord** outTles, int* numTles)
{
   FILE* fpRead;

   TleGPRecord* tles;
   char line1[80];
   char line2[80];
   int  count;

   fpRead = FileOpen(fileName, (char*)"rt");
   count = 0;

   tles = (TleGPRecord*)malloc(MAXNUMTLES * sizeof(TleGPRecord));

   while (1)
   {
      if (!fgets(line1, 80, fpRead))
         break;
      if (!fgets(line2, 80, fpRead))
         break;

      tles[count] = LinesToTle(line1, line2);
      count++;

      if (count >= MAXNUMTLES)
      {
         printf("Warning: The number of TLEs has reach the maximum limit %d", MAXNUMTLES);
         printf("... The program will continue but it will not load any more TLEs\n");
         break;
      }
   }

   *numTles = count;
   *outTles = tles;
   fclose(fpRead);
}



