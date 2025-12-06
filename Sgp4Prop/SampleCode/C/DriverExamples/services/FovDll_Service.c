#include "DllUtils.h"
#include "DllMainDll_Service.h"
#include "FovDll_Service.h"
#include "TimeFuncDll_Service.h"
#include "SatStateDll_Service.h"
#include <math.h>

#include "../wrappers/DllMainDll.h"
#include "../wrappers/FovDll.h"
#include "../wrappers/TimeFuncDll.h"
#include "../wrappers/SensorDll.h"
#include "../wrappers/SatStateDll.h"
#include "../wrappers/LamodDll.h"


// Retrieve Fov control data from the dll
void GetFovCtrlPara(FovCtrl* fovCtrl)
{

}

// Print FOV control parameters
void PrintFovCtrls(FILE* fpOut, double xa_fovCtrl[8], int numOfWindows, double startStopTimes[256], 
   int numOfSources, double xa_fovSrc_2D[][8], int numOfTargets, double xa_fovTgt_2D[][8])
{
   int i;
   char srcTypeStr[5][21] = {"",
                             "SSN sensor          ",
                             "geodetic lat/long/ht",
                             "rotating EFG        ",
                             "ECI XYZ at a TIME   "};

   char tgtTypeStr[4][27] = { "",
                              "satellite                 ",
                              "constant az/el from source",
                              "constant ra/dec (ie, star)" };

   char prtOptStr[5][37] = { "victim information only             ",
                             "victim info & source/target descrip.",
                             "victim info & source/target/sec info",
                             "detailed, maximum information       ",
                             "detailed, max info + range to target"};
   int id, srcType, tgtType;


   fprintf(fpOut, "\n\n");
   fprintf(fpOut, " ===============================================================================\n");
   fprintf(fpOut, " |                  FIELD-OF-VIEW (FOV) OPTIONS:                               |\n");
   fprintf(fpOut, " ===============================================================================\n");

   if (numOfWindows == 1)
   {
      fprintf(fpOut, " |  A.  START/STOP TIMES:               From %20s (UTC)        |\n", UTCToDtg20Str(startStopTimes[0]));
      fprintf(fpOut, " |                                      To   %20s (UTC)        |\n", UTCToDtg20Str(startStopTimes[1]));
      fprintf(fpOut, " |                                      For %8.2f minutes duration          |\n", (startStopTimes[1] - startStopTimes[0]) * 1440.0);
   }
   else
   {
      for (i = 0; i < numOfWindows; i++)
      {
         if ( i == 0)
            fprintf(fpOut, " |  A.  START/STOP TIMES:           %2d: From %20s (UTC)        |\n", i + 1, UTCToDtg20Str(startStopTimes[i * 2]));
         else
            fprintf(fpOut, " |                                  %2d: From %20s (UTC)        |\n", i + 1, UTCToDtg20Str(startStopTimes[i * 2]));
         fprintf(fpOut, " |                                      To   %20s (UTC)        |\n", UTCToDtg20Str(startStopTimes[i * 2 + 1]));
         fprintf(fpOut, " |                                      For %8.2f minutes duration          |\n", (startStopTimes[i*2+1] - startStopTimes[i*2]) * 1440.0);
      }

   }

   if (numOfSources == 1)
   {
      id = (int)xa_fovSrc_2D[0][XA_FOVSRC_ID];
      srcType = (int)xa_fovSrc_2D[0][XA_FOVSRC_TYPE];
      fprintf(fpOut, " |  B.  SOURCES TO PROCESS:             %7d  %20s          |\n", id, srcTypeStr[srcType]);
   }
   else
   {
      for (i = 0; i < numOfSources; i++)
      {
         id = (int)xa_fovSrc_2D[i][XA_FOVSRC_ID];
         srcType = (int)xa_fovSrc_2D[i][XA_FOVSRC_TYPE];

         if (i == 0)
            fprintf(fpOut, " |  B.  SOURCES TO PROCESS:         %2d:%7d  %20s           |\n", i + 1, id, srcTypeStr[srcType]);
         else
            fprintf(fpOut, " |                                  %2d:%7d  %20s           |\n", i + 1, id, srcTypeStr[srcType]);
      }

   }

   if (numOfTargets == 1)
   {
      id = (int)xa_fovTgt_2D[0][XA_FOVTGT_ID];
      tgtType = (int)xa_fovTgt_2D[0][XA_FOVTGT_TYPE];
      fprintf(fpOut, " |  C.  TARGETS TO PROCESS:             %7d %27s    |\n", id, tgtTypeStr[tgtType]);
   }
   else
   {
      for (i = 0; i < numOfTargets; i++)
      {
         id = (int)xa_fovTgt_2D[i][XA_FOVTGT_ID];
         tgtType = (int)xa_fovTgt_2D[i][XA_FOVTGT_TYPE];

         if (i == 0)
            fprintf(fpOut, " |  C.  TARGETS TO PROCESS:         %2d:%7d %27s     |\n", i + 1, id, tgtTypeStr[tgtType]);
         else
            fprintf(fpOut, " |                                  %2d:%7d %27s     |\n", i + 1, id, tgtTypeStr[tgtType]);
      }

   }
   
   //fprintf(fpOut, " |  E.  SPECIFIED SECONDARY SATs:                                              |\n");

   if (xa_fovCtrl[XA_FOVCTRL_INTERVAL] == 0)
      fprintf(fpOut, " |  G.  SEARCH INTERVAL:             depends on secondary elts                 |\n");
   else
      fprintf(fpOut, " |  G.  SEARCH INTERVAL:             %7.3f min                               |\n", xa_fovCtrl[XA_FOVCTRL_INTERVAL]);

   if (xa_fovCtrl[XA_FOVCTRL_HALFCONE] == 0)
      fprintf(fpOut, " |  H.  CONE ANGLE:                 use auto-cone algorithm                    |\n");
   else
      fprintf(fpOut, " |  H.  CONE ANGLE:                  %7.3f deg                               |\n", xa_fovCtrl[XA_FOVCTRL_HALFCONE]);

   fprintf(fpOut, " |  I.  PRINTED OUTPUT OPTION:       %s      |\n", prtOptStr[(int)xa_fovCtrl[XA_FOVCTRL_PRTOPT]]);
   fprintf(fpOut, " ===============================================================================\n\n");
}


void PrintSourceTargetData(FILE* fpOut, double xa_fovSrc[8], double xa_fovTgt[8])
{
   char srcTypeStr[5][14] = { 
      "",
      "SSN Sensor   ",
      "Geodetic LLH ",
      "Rotating EFG ",
      "ECI XYZ @Time" };

   char tgtTypeStr[4][15] = {
      "",
      "ELSET         ",
      "Constant AZ/EL",
      "RA/DEC (STAR) "};


   int srcId, tgtId;
   int srcType, tgtType;


   tgtId = (int)xa_fovTgt[XA_FOVTGT_ID];
   tgtType = (int)xa_fovTgt[XA_FOVTGT_TYPE];
   srcId = (int)xa_fovSrc[XA_FOVSRC_ID];
   srcType = (int)xa_fovSrc[XA_FOVSRC_TYPE];

   fprintf(fpOut, "\n\n");
   fprintf(fpOut, " ===============================================================================\n");
   fprintf(fpOut, " |              FIELD-OF-VIEW (FOV) SOURCE/TARGET SPECIFICATION                |\n");
   fprintf(fpOut, " -------------------------------------------------------------------------------\n");
   fprintf(fpOut, " | SOURCE TYPE: %s%50s|\n", srcTypeStr[srcType], " ");

   

   switch (srcType)
   {
      case 1: // FOV_TGTTYPE_ELSET:
         fprintf(fpOut, " | SENSOR NUMBER : %3d%57s|\n", srcId, " ");
         break;
      case 2: // FOV_SRCTYPE_LLH
         fprintf(fpOut, " | NORTH LATITUDE: %10.5f deg%46s|\n", xa_fovSrc[XA_FOVSRC_ELEM1], " ");
         fprintf(fpOut, " | EAST LONGITUDE: %10.5f deg%46s|\n", xa_fovSrc[XA_FOVSRC_ELEM2], " ");
         fprintf(fpOut, " | HEIGHT        : %10.0f m%48s|\n", xa_fovSrc[XA_FOVSRC_ELEM3], " ");
         break;
      case 3: // FOV_SRCTYPE_EFG 
         fprintf(fpOut, " | ROTATING E: %9.0f m|\n", xa_fovSrc[XA_FOVSRC_ELEM1]);
         fprintf(fpOut, " | ROTATING F: %9.0f m|\n", xa_fovSrc[XA_FOVSRC_ELEM2]);
         fprintf(fpOut, " | ROTATING G: %9.0f m|\n", xa_fovSrc[XA_FOVSRC_ELEM3]);
         break;
      case 4: // FOV_SRCTYPE_XYZ
         fprintf(fpOut, " | GEOCENTRIC X: %9.0f m%51s|\n", xa_fovSrc[XA_FOVSRC_ELEM1], " ");
         fprintf(fpOut, " | GEOCENTRIC Y: %9.0f m%51s|\n", xa_fovSrc[XA_FOVSRC_ELEM2], " ");
         fprintf(fpOut, " | GEOCENTRIC Z: %9.0f m%51s|\n", xa_fovSrc[XA_FOVSRC_ELEM3], " ");
         break;
   }

   fprintf(fpOut, " |-----------------------------------------------------------------------------|\n");
   fprintf(fpOut, " | TARGET TYPE: %s%49s|\n", tgtTypeStr[tgtType], " ");

   switch (tgtType)
   {
      case 1: // FOV_TGTTYPE_ELSET:
         fprintf(fpOut, " | ELSET NUMBER: %9d%53s|\n", tgtId, " ");
         break;
      case 2: // FOV_TGTTYPE_AZEL
         fprintf(fpOut, " | TARGET ID: %9d%56s|\n", tgtId, " ");
         fprintf(fpOut, " | AZIMUTH  : %8.4f deg%53s|\n", xa_fovTgt[XA_FOVTGT_ELEM1], " ");
         fprintf(fpOut, " | ELEVATION: %8.4f deg%53s|\n", xa_fovTgt[XA_FOVTGT_ELEM2], " ");
         break;
      case 3: // FOV_TGTTYPE_RADEC 
         fprintf(fpOut, " | TARGET ID: %9d%56s|\n", tgtId, " ");
         fprintf(fpOut, " | RT ASCENSION: %8.4f deg%50s|\n", xa_fovTgt[XA_FOVTGT_ELEM1], " ");
         fprintf(fpOut, " | DECLINATION : %8.4f deg%50s|\n", xa_fovTgt[XA_FOVTGT_ELEM2], " ");
         fprintf(fpOut, " | EQUINOX INDICATOR:  %d%55s|\n", (int)xa_fovTgt[XA_FOVTGT_ELEM3], " ");
         break;
   }
   fprintf(fpOut, " ===============================================================================\n\n");
}



void PrintPenetrationTimes(FILE* fpOut, int isNewWindow, int winNum, double xa_fovSrc[], double xa_fovTgt[], __int64 vicSatKey, double xa_emeDat[][3], int numOfPens)
{
   int tgtType;
   double xa_look[8];
   int m;

   double entryDs50TAI, minDs50TAI, exitDs50TAI;

   tgtType = (int)xa_fovTgt[XA_FOVTGT_TYPE];

   if(isNewWindow)
      fprintf(fpOut, "    SUMMARY FOR TIME WINDOW #    %2d, SOURCE  %4d and TARGET %5d:\n", winNum, (int)xa_fovSrc[XA_FOVSRC_ID], (int)xa_fovTgt[XA_FOVTGT_ID]);



   for (m = 0; m < numOfPens; m++)
   {
      entryDs50TAI = xa_emeDat[m][0];
      minDs50TAI   = xa_emeDat[m][1];
      exitDs50TAI  = xa_emeDat[m][2];

      // compute look angle at entry time
      GetLookAngle(tgtType, entryDs50TAI, xa_fovSrc, xa_fovTgt, vicSatKey, xa_look);

      fprintf(fpOut, " SAT = %5d ENTRY TIME = %s AZ =%6.1f EL =%5.1f RG =%8.1f RR =%7.3f\n", 
         SatNumOf(vicSatKey),
         UTCToDtg20Str(xa_look[XA_LOOK_DS50UTC]),
         xa_look[XA_LOOK_AZIM],
         xa_look[XA_LOOK_ELEV],
         xa_look[XA_LOOK_RNG],
         xa_look[XA_LOOK_RNGRT]);

      // compute look angle at minimum time
      GetLookAngle(tgtType, minDs50TAI, xa_fovSrc, xa_fovTgt, vicSatKey, xa_look);

      fprintf(fpOut, "             MINIMUM AT:  %s AZ =%6.1f EL =%5.1f RG =%8.1f RR =%7.3f\n",
         UTCToDtg20Str(xa_look[XA_LOOK_DS50UTC]),
         xa_look[XA_LOOK_AZIM],
         xa_look[XA_LOOK_ELEV],
         xa_look[XA_LOOK_RNG],
         xa_look[XA_LOOK_RNGRT]);

      // compute look angle at exit time
      GetLookAngle(tgtType, exitDs50TAI, xa_fovSrc, xa_fovTgt, vicSatKey, xa_look);

      fprintf(fpOut, " (U)         EXIT  TIME = %s AZ =%6.1f EL =%5.1f RG =%8.1f RR =%7.3f\n",
         UTCToDtg20Str(xa_look[XA_LOOK_DS50UTC]),
         xa_look[XA_LOOK_AZIM],
         xa_look[XA_LOOK_ELEV],
         xa_look[XA_LOOK_RNG],
         xa_look[XA_LOOK_RNGRT]);
   }
}


void PrintDetailLookAngles(FILE* fpOut, double xa_fovRun[], double xa_fovSrc[], double xa_fovTgt[], __int64 tgtSatKey, __int64 vicSatKey)
{
   int tgtType;
   double xa_look_tgt[8];
   double xa_look_vic[8];
   int m;

   double currDs50TAI;
   double startTimeDs50UTC, stopTimeDs50UTC, currDs50UTC, interval, period_min;


   // update only start/stop times for a new run
   startTimeDs50UTC = xa_fovRun[XA_FOVRUN_START];
   stopTimeDs50UTC = xa_fovRun[XA_FOVRUN_STOP];
   interval = xa_fovRun[XA_FOVRUN_INTERVAL];

   // search interval depends on target satellite's period
   if (interval == 0)
   {
      period_min = GetSatDataField(tgtSatKey, XF_SAT_PERIOD);
      if (period_min < 225)
         interval = 2; // 2 minutes for near-earth target satellite
      else
         interval = 15; // 15 minutes for all else
   }


   tgtType = (int)xa_fovTgt[XA_FOVTGT_TYPE];

   fprintf(fpOut, " TARGET SAT (1) = %5d, VICTIM SAT (2) = %5d\n", SatNumOf(tgtSatKey), SatNumOf(vicSatKey));
   fprintf(fpOut, "           TIME          AZ1      EL1         RG1     RR1      AZ2      EL2         RG2     RR2     \n");

   currDs50UTC = startTimeDs50UTC;

   for (m = 0; currDs50UTC <= stopTimeDs50UTC; m++)
   {
      currDs50UTC = startTimeDs50UTC + (m * interval) / 1440.0;
      currDs50TAI = UTCToTAI(currDs50UTC);

      // compute look angle for source vs target satellite
      GetLookAngle(tgtType, currDs50TAI, xa_fovSrc, xa_fovTgt, tgtSatKey, xa_look_tgt);

      // compute look angle for source vs victim satellite
      GetLookAngle(tgtType, currDs50TAI, xa_fovSrc, xa_fovTgt, vicSatKey, xa_look_vic);

      fprintf(fpOut, " %s %9.3f%9.3f%11.2f%9.3f%9.3f%9.3f%11.2f%9.3f\n",
         UTCToDtg20Str(xa_look_tgt[XA_LOOK_DS50UTC]),
         xa_look_tgt[XA_LOOK_AZIM],
         xa_look_tgt[XA_LOOK_ELEV],
         xa_look_tgt[XA_LOOK_RNG],
         xa_look_tgt[XA_LOOK_RNGRT],
         xa_look_vic[XA_LOOK_AZIM],
         xa_look_vic[XA_LOOK_ELEV],
         xa_look_vic[XA_LOOK_RNG],
         xa_look_vic[XA_LOOK_RNGRT]);
   }
}


void GetLookAngle(int tgtType, double ds50TAI, double xa_fovSrc[], double xa_fovTgt[], __int64 vicSatKey, double xa_look[])
{
   int errCode;

   if (tgtType == FOV_TGTTYPE_ELSET)
      errCode = FovTargetElsetLook(ds50TAI, xa_fovSrc, vicSatKey, xa_look);
   else
      errCode = FovTargetVecLook(ds50TAI, xa_fovSrc, xa_fovTgt, vicSatKey, xa_look);
}

 