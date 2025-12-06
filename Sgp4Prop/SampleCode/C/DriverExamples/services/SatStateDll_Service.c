#include "DllUtils.h"
#include "SatStateDll_Service.h"
#include "TimeFuncDll_Service.h"
#include "DllMainDll_Service.h"


#include "../wrappers/DllMainDll.h"
#include "../wrappers/ElOpsDll.h"
#include "../wrappers/SatStateDll.h"
#include "../wrappers/TimeFuncDll.h"


// Retrieve value of a field of satellite data
double GetSatDataField(__int64 satKey, int idx)
{
   char valueStr[GETSETSTRLEN];

   SatStateGetSatDataField(satKey, idx, valueStr); 
   valueStr[GETSETSTRLEN - 1] = 0;

   return atof(valueStr);
}

// Return full string description of the orbital element type
char* GetSatTypeString(int orbEltType)
{
   static char typeStr[16];

   strcpy(typeStr, EltTypeStr[orbEltType]);

   return typeStr;
}


// Return short string description of the orbital element type
char* GetRecTypeString(int orbEltType)
{
   static char typeStr[7];
   strcpy(typeStr, RecTypeStr[orbEltType - 1]);

   return typeStr;
}

// Count number of loaded satellites of the specified type
int SatStateGetTypeCount(int type, __int64* satKeys, int satCount)
{
   int count = 0;
   int orbEltType;
   int i;

   for(i = 0; i < satCount; i++)
   {
      orbEltType = (int)(satKeys[i] % 10);
      if (orbEltType == type)
         count ++;
   }

   return count;
}

// Print satellite common data
void PrintSatelliteData(FILE* fp, __int64 satKey)
{
   char   dashLine[]  = "-------------------------------------------------------------------------------";
   char   ddashLine[] = "===============================================================================";

   int    satNum;
   char   satName[9];
   int    elsetNum;
   int    ephType;
   int    revNum; 
   double epochDs50UTC;
   double mnAnomaly;
   double node;
   double omega;
   double period;
   double eccen;
   double incli;
   double mnMotion;
   double bField;
   double perigeeHt;
   double apogeeHt;
   double perigee;
   double apogee;
   double A;

   int    errCode;

   // Retrieve data from the dll
   errCode = SatStateGetSatDataAll(satKey, &satNum, satName, &ephType, &revNum, 
                                   &epochDs50UTC, &bField, &elsetNum, &incli, &node, &eccen, &omega,  
                                   &mnAnomaly, &mnMotion, &period, &perigeeHt, &apogeeHt,
                                   &perigee, &apogee, &A); 

   satName[8] = 0;

   if (errCode != 0)
      return;

   fprintf(fp, " %s\n", ddashLine);
   fprintf(fp, " |                           SATELLITE %5d DATA                              |\n", satNum);
   fprintf(fp, " %s\n", dashLine);
   
   fprintf(fp, " |  ELEMENT NUMBER :        %5d%45s |\n", elsetNum, " ");
   fprintf(fp, " |  INT. DESIGNATOR:        %-50s |\n", satName);
   fprintf(fp, " |  EPHEMERIS TYPE:         %-50s |\n", EltTypeStr[ephType-1]);
   fprintf(fp, " |  EPOCH REVOLUION #:      %5d%45s |\n", revNum, " ");
   fprintf(fp, " |  EPOCH TIME:             %-50s |\n", UTCToDtg20Str(epochDs50UTC));
   fprintf(fp, " |  MEAN ANOMALY (deg):     %9.4f%-41s |\n", mnAnomaly, " ");
   fprintf(fp, " |  RIGHT ASCENSION (deg):  %9.4f%-41s |\n", node, " ");
   fprintf(fp, " |  ARG. OF PERIGEE (deg):  %9.4f%-41s |\n", omega, " ");
   fprintf(fp, " |  PERIOD (min):           %9.4f%-41s |\n", period, " ");
   fprintf(fp, " |  ECCENTRICITY:           %9.7f%-41s |\n", eccen, " ");
   fprintf(fp, " |  INCLINATION (deg):      %9.4f%-41s |\n", incli, " ");
   fprintf(fp, " |  MEAN MOTION (rev/day):  %13.9f%-37s |\n", mnMotion, " ");
   if(ephType == ELTTYPE_TLE_SGP || ephType == ELTTYPE_TLE_SGP4)
      fprintf(fp, " |  BSTAR (1./er)           %12.9f%-38s |\n", bField, " ");
   else if(ephType == ELTTYPE_TLE_SP || ephType == ELTTYPE_SPVEC_B1P || ephType == ELTTYPE_VCM)
      fprintf(fp, " |  BTERM (m**2/Kg)         %12.9f%-38s |\n", bField, " ");

   fprintf(fp, " |  PERIGEE HEIGHT (km):    %10.3f%-40s |\n", perigeeHt, " ");
   fprintf(fp, " |  APOGEE HEIGHT(km):      %10.3f%-40s |\n", apogeeHt, " ");
   fprintf(fp, " %s\n\n", ddashLine);
}

