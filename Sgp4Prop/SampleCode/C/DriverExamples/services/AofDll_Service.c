#include "DllUtils.h"
#include "DllMainDll_Service.h"
#include "AofDll_Service.h"
#include "TimeFuncDll_Service.h"
#include "SatStateDll_Service.h"
#include <math.h>

#include "../wrappers/DllMainDll.h"
#include "../wrappers/AofDll.h"
#include "../wrappers/TimeFuncDll.h"
#include "../wrappers/SensorDll.h"
#include "../wrappers/SatStateDll.h"
#include "../wrappers/LamodDll.h"


// Retrieve Aof control data from the dll
void GetAofCtrlPara(AofCtrl* aofCtrl)
{
}

void PrintAofCtrl(FILE* fpOut, double xa_aofCtrl[16])
{
   fprintf(fpOut, "                    AOF OPTIONS:\n");
   fprintf(fpOut, " ===============================================================================\n");
   fprintf(fpOut, " |  A.  TIME OF INTEREST, START:    %20s (UTC)                 |\n", UTCToDtg20Str(xa_aofCtrl[XA_AOFCTRL_START]));
   fprintf(fpOut, " |  B.  TIME OF INTEREST, END:      %20s (UTC)                 |\n", UTCToDtg20Str(xa_aofCtrl[XA_AOFCTRL_STOP]));
   fprintf(fpOut, " |  C.  OVERFLIGHT SEARCH INTERVAL  %7.3f min                                |\n", xa_aofCtrl[XA_AOFCTRL_INTERVAL]);
   //fprintf(fpOut, " |  D.  DEFENDED AREAS TO PROCESS:   1111,  2222,     0,     0,     0          |\n");
   //fprintf(fpOut, " |  E.  INPUT SATELLITES(s):        all elsets input from ELSETS               |\n");
   //fprintf(fpOut, " |  E.  INPUT SATELLITES(s):        26481,     0,     0,     0,     0          |\n");
   //fprintf(fpOut, " |  F.  PRINTED OUTPUT OPTION:      initial conditions and penetrations        |\n");
   //fprintf(fpOut, " |  H.  SEARCH METHOD FOR POINTS:   brute-force                                |\n");
   //fprintf(fpOut, " |  I.  SORTED OUTPUT OPTION:       sort by time, then satellite               |\n");
   //fprintf(fpOut, " |  J.  SORTED OUTPUT FILE:         AOF output file                            |\n");
   fprintf(fpOut, " ===============================================================================\n");
}


void PrintAreaData(FILE* fpOut, double xa_aofArea[16])
{
   char   dashLine[] = "-------------------------------------------------------------------------------";
   char   ddashLine[] = "===============================================================================";
   char   areaTypeStrs[][7] = { "Box", "Circle", "Point" };
   int    areaType;


   fprintf(fpOut, " %s\n", ddashLine);
   fprintf(fpOut, " |                           DEFENDED AREA %4d DATA                           |\n", (int)xa_aofArea[XA_AOFAREA_NUM]);
   fprintf(fpOut, " %s\n", dashLine);

   areaType = (int)xa_aofArea[XA_AOFAREA_TYPE];

   fprintf(fpOut, " |  Area type:   %-62s|\n", areaTypeStrs[areaType - 1]);
   fprintf(fpOut, " |  Latitude :   %8.4f deg N%48s|\n", xa_aofArea[XA_AOFAREA_ELEM1], " ");
   fprintf(fpOut, " |  Longitude:   %8.4f deg E%48s|\n", xa_aofArea[XA_AOFAREA_ELEM2], " ");
   if (areaType == AOF_AREATYPE_BOX)
   {
      fprintf(fpOut, " |  Latitude :   %8.4f deg N%48s|\n", xa_aofArea[XA_AOFAREA_ELEM3], " ");
      fprintf(fpOut, " |  Longitude:   %8.4f deg E%48s|\n", xa_aofArea[XA_AOFAREA_ELEM4], " ");
   }
   else if (areaType == AOF_AREATYPE_POINT)
   {
      fprintf(fpOut, " |  Height   :   %8.4f meters%47s|\n", xa_aofArea[XA_AOFAREA_ELEM3], " ");
   }
   fprintf(fpOut, " %s\n", ddashLine);
}

void PrintEntryExit(FILE* fpOut, double xa_aofArea[16], int satNum, __int64 satKey, int numOfPasses, double xa_entExitTimes[])
{
   double xa_look[8];
   double llh[3];
   int printLook;
   int i, j;
   int darkness;


   char enterExitStrs[][7] = { "ENTERS", "EXITS " };
   char darknessStrs[][19] = { "(entirely sunlit)",
      "(total area dark)",
      "(partial sunlight)" };

   printLook = (xa_aofArea[XA_AOFAREA_TYPE] == AOF_AREATYPE_CIRCLE || xa_aofArea[XA_AOFAREA_TYPE] == AOF_AREATYPE_POINT);
   fprintf(fpOut, "\n   Satellite no.    %05d                    Area no.     %04d\n", satNum, (int)xa_aofArea[XA_AOFAREA_NUM]);

   for (i = 0; i < numOfPasses; i++)
   {
      for (j = 0; j < 2; j++)
      {
         darkness = AofGetDarknessLevel(xa_entExitTimes[i*2+j], xa_aofArea);
         fprintf(fpOut, " SAT %s AREA AT %s  %-18s    ", enterExitStrs[j], UTCToDtg20Str(TAIToUTC(xa_entExitTimes[i * 2 + j])), darknessStrs[darkness]);

         if (printLook)
         {
            llh[0] = xa_aofArea[XA_AOFAREA_ELEM1];
            llh[1] = xa_aofArea[XA_AOFAREA_ELEM2];
            llh[2] = xa_aofArea[XA_AOFAREA_ELEM3];

            // compute look angle from the location llh to the overfly satellite at the specified time
            AofGetLook(xa_entExitTimes[i * 2 + j], llh, satKey, xa_look);

            fprintf(fpOut, "%05d  AZ= %5.1f  EL= %4.1f  RNG= %5.0f  (km)\n", satNum, xa_look[XA_LOOK_AZIM], xa_look[XA_LOOK_ELEV], xa_look[XA_LOOK_RNG]);
         }
         else
         {
            fprintf(fpOut, "\n");
         }
      }
   }
   fprintf(fpOut, " Satellite %5d: %3d pass(es) over defended area %4d\n", satNum, numOfPasses, (int)xa_aofArea[XA_AOFAREA_NUM]);
   fprintf(fpOut, "\n\n");
}
