#include "DllUtils.h"
#include "DllMainDll_Service.h"
#include "ElOpsDll_Service.h"
#include "LamodDll_Service.h"
#include "TimeFuncDll_Service.h"
#include "SatStateDll_Service.h"
#include <math.h>

#include "../wrappers/DllMainDll.h"
#include "../wrappers/EnvConstDll.h"
#include "../wrappers/LamodDll.h"
#include "../wrappers/TimeFuncDll.h"
#include "../wrappers/SensorDll.h"
#include "../wrappers/SatStateDll.h"



// Retrieve Lamod control data from the dll
void GetLamodCtrlPara(LamodCtrl* lamodCtrl)
{
   char schedMode;
   int timeFlg, prtOpt, punchObs, visFlg, stepMode, diagMode;
   double startTime, stopTime, stepSize, solAspAngle;


   // Call Lamod dll's function
   LamodGet1pAll(&timeFlg, &startTime, &stopTime, &stepSize, &prtOpt,
      &punchObs, &visFlg, &stepMode, &schedMode, &diagMode, &solAspAngle);

   lamodCtrl->timeFlg = timeFlg;
   lamodCtrl->startTime = startTime;
   lamodCtrl->stopTime = stopTime;
   lamodCtrl->stepSize = stepSize;
   lamodCtrl->prtOpt = prtOpt;
   lamodCtrl->punchObs = punchObs;
   lamodCtrl->visFlg = visFlg;
   lamodCtrl->stepMode = stepMode;
   lamodCtrl->schedMode = schedMode;
   lamodCtrl->diagMode = diagMode;
   lamodCtrl->solAspAngle = solAspAngle;
}


// Print LAMOD control parameters
void PrintLamodCtrls(FILE* fpOut, LamodCtrl* lamodCtrl)
{
   char dashLine[] = "-------------------------------------------------------------------------------";
   char ddashLine[] = "===============================================================================";
   char modes[][17] = { "Culmination Mode",
      "Step Mode",
      "Task Mode" };


   fprintf(fpOut, " %s\n", ddashLine);
   fprintf(fpOut, " |                          L A M O D   O P T I O N S                          |\n");
   fprintf(fpOut, " %s\n", dashLine);


   fprintf(fpOut, " |  A.  PROCESSING MODE: %-54s|\n",
      lamodCtrl->schedMode == IDX_SCHED_OBS ? "OBSCHED (all sensors vs all satellites)" : "PASCHED (all satellites vs all sensors)");
   if (lamodCtrl->timeFlg == CARD_1P_FRDATE)
   {
      fprintf(fpOut, " |  B.  TIME OF INTEREST START, UTC:   %-40s|\n", UTCToDtg20Str(lamodCtrl->startTime));
      fprintf(fpOut, " |  C.  TIME OF INTEREST END  , UTC:   %-40s|\n", UTCToDtg20Str(lamodCtrl->stopTime));
   }
   else
   {
      fprintf(fpOut, " |  B.  TIME OF INTEREST START, MSE:   %10.3f%30s|\n", lamodCtrl->startTime, " ");
      fprintf(fpOut, " |  C.  TIME OF INTEREST END  , MSE:   %10.3f%30s|\n", lamodCtrl->stopTime, " ");
   }

   fprintf(fpOut, " |  F.  PRINTED OUTPUT OPTION:         %-40s|\n", lamodCtrl->prtOpt == 0 ? "Look Angles" : "Look Angles & Initial Conditions");

   // condition/output output interval
   if (lamodCtrl->stepSize == 0)
      fprintf(fpOut, " |  H.  LOOK ANGLE OUTPUT INTERVAL     %-40s|\n", "Use Sensor's Output Interval Value");
   else
   {
      fprintf(fpOut, " |  H.  LOOK ANGLE OUTPUT INTERVAL     %7.2f min%29s|\n", lamodCtrl->stepSize, " ");
      fprintf(fpOut, " |      (Note: This output interval overwrites sensor's output interval)       |\n");
   }


   // condition/output optical visibility flag
   fprintf(fpOut, " |  I.  OPTICAL VISIBILITY OPTION:     %-40s|\n", SenOptVisFlg[lamodCtrl->visFlg]);

   // overwrite visibility flag of sensor's limit card
   if (lamodCtrl->visFlg != 9)
      fprintf(fpOut, " |      (Note: This flag overwrites sensor's visual pass control flag)         |\n");

   // condition/output solar aspect angle
   if (lamodCtrl->solAspAngle == 0)
      fprintf(fpOut, " |  J.  SOLAR ASPECT ANGLE:            %-40s|\n", "(computed value)");
   else
      fprintf(fpOut, " |  J.  SOLAR ASPECT ANGLE:            %7.2f deg%29s|\n", lamodCtrl->solAspAngle, " ");

   // condition/output step mode flag
   fprintf(fpOut, " |  K.  STEP/CULMINATION/TASK MODE:    %-40s|\n", modes[lamodCtrl->stepMode]);

   // condition/output observation generation flag
   fprintf(fpOut, " |  O.  OBSERVATION GENERATION:        %-40s|\n", GenObsFlg[lamodCtrl->punchObs]);


   fprintf(fpOut, " |  R.  DIAGNOSTICS FLAG:              %-40s|\n", NosticFlg[lamodCtrl->diagMode]);

   fprintf(fpOut, " |  S.  EARTH SHAPE:                   %-40s|\n", EnvGetEarthShape() == 1 ? "Oblate" : "Spherical");

   fprintf(fpOut, " %s\n\n", ddashLine);
}

// Retrieve initialized sensor/satellite data
int GetSenSatData(__int64 senSatKey, __int64 senKey, __int64 satKey, SenSatData* senSatData)
{
   int errCode;
   double xa_senSat[32];

   // Call Lamod dll's function
   errCode = LamodSenSatDataToArray(senSatKey, xa_senSat);

   if (errCode == 0)
   {
      senSatData->senKey       = senKey; 
      senSatData->satKey       = satKey;
      senSatData->senSatKey    = senSatKey;
      senSatData->senNum       = (int)xa_senSat[XA_SENSAT_SENNUM];
      senSatData->satNum       = (int)xa_senSat[XA_SENSAT_SATNUM];
      senSatData->viewType     = (char)((int)xa_senSat[XA_SENSAT_VIEWTYPE]);
      senSatData->obsType      = (char)((int)xa_senSat[XA_SENSAT_OBSTYPE]);
      senSatData->maxPtsPerPass= (int)xa_senSat[XA_SENSAT_PTSPERPAS];
      senSatData->stepMode     = (int)xa_senSat[XA_SENSAT_STEPMODE];
      senSatData->optVisFlg    = (int)xa_senSat[XA_SENSAT_OPTVISFLAG];
      senSatData->startDs50TAI = xa_senSat[XA_SENSAT_STARTAI];
      senSatData->stopDs50TAI  = xa_senSat[XA_SENSAT_STOPTAI];
      senSatData->interval     = xa_senSat[XA_SENSAT_INTERVAL];
      senSatData->period       = xa_senSat[XA_SENSAT_PERIOD];
   }

   return errCode;

}

// Retrieve look angle data
void GetLookAngleData(SenSatData* senSatData, double currDs50TAI, LookAngle* look)
{
   double xa_lv[128];

   look->errCode = LamodComputeLookView(senSatData->senSatKey, currDs50TAI, xa_lv);

   if (look->errCode != 0)
   {
      return;
   }

   memcpy(look->senPos, &xa_lv[XA_LV_SENPOSX], 3 * sizeof(double));
   memcpy(look->senVel, &xa_lv[XA_LV_SENVELX], 3 * sizeof(double));
   memcpy(look->senLLH, &xa_lv[XA_LV_SENLAT], 3 * sizeof(double));

   memcpy(look->satPos, &xa_lv[XA_LV_SATPOSX], 3 * sizeof(double));
   memcpy(look->satVel, &xa_lv[XA_LV_SATVELX], 3 * sizeof(double));
   memcpy(look->satLLH, &xa_lv[XA_LV_SATLAT], 3 * sizeof(double));

   look->lookCode = (int)xa_lv[XA_LV_LOOKCODE];
   look->lookTimeDs50UTC = xa_lv[XA_LV_DS50UTC];
   look->lookTimeMSE = xa_lv[XA_LV_MSE];
   look->azimuth_deg = xa_lv[XA_LV_AZIM];
   look->elevation_deg = xa_lv[XA_LV_ELEV];
   look->range_km = xa_lv[XA_LV_RNG];
   look->rangeRate_kmps = xa_lv[XA_LV_RNGRT];
   look->azRate_degps = xa_lv[XA_LV_AZRATE];
   look->elRate_degps = xa_lv[XA_LV_ELRATE];
   //look->satNum = senSatData->satNum;
   look->satKey = senSatData->satKey;
   //look->senNum = senSatData->senNum;

   look->relVel = xa_lv[XA_LV_RELVEL];

   look->passVisual = (int)xa_lv[XA_LV_OPTVIS];
   look->passAzLim = (int)xa_lv[XA_LV_AZLIM];
   look->passElLim = (int)xa_lv[XA_LV_ELLIM];
   look->passEarthBkgr = (int)xa_lv[XA_LV_EARTHBK];
   look->passEarthOb = (int)xa_lv[XA_LV_EARTHOB];
   look->passLunExcl = (int)xa_lv[XA_LV_LUNEXCL];
   look->passMaxRange = (int)xa_lv[XA_LV_MAXRANGE];
   look->passMinRange = (int)xa_lv[XA_LV_MINRANGE];
   look->passPenEclip = (int)xa_lv[XA_LV_PENECLIP];
   look->passRVelLim = (int)xa_lv[XA_LV_RVELLIM];
   look->passSAALim = (int)xa_lv[XA_LV_SAALIM];
   look->passSolExcl = (int)xa_lv[XA_LV_SOLEXCL];
   look->passUmbEclip = (int)xa_lv[XA_LV_UMBECLIP];


   look->sunSenSat_deg = xa_lv[XA_LV_SUSESA];
   look->sunEarthSat_deg = xa_lv[XA_LV_SUEASA];
   look->sunEarthSen_deg = xa_lv[XA_LV_SUEASE];
   look->moonSenSat_deg = xa_lv[XA_LV_MOSESA];
   look->moonEarthSat_deg = xa_lv[XA_LV_MOEASA];
   look->moonEarthSen_deg = xa_lv[XA_LV_MOEASE];
   look->SAA_deg = xa_lv[XA_LV_SOLAA];

   memcpy(look->unitRangeVec, &xa_lv[XA_LV_RUVECX], 3 * sizeof(double));
   memcpy(look->senPosEFG, &xa_lv[XA_LV_SENPOSE], 3 * sizeof(double));

   look->illumination = (int)xa_lv[XA_LV_VIS];

   look->nBore1 = (int)xa_lv[XA_LV_NBORE1];
   look->nBore2 = (int)xa_lv[XA_LV_NBORE2];
   look->offBoreElev1_deg = xa_lv[XA_LV_OBEL1];
   look->offBoreAzim1_deg = xa_lv[XA_LV_OBAZ1];
   look->offBoreElev2_deg = xa_lv[XA_LV_OBEL2];
   look->offBoreAzim2_deg = xa_lv[XA_LV_OBAZ1];

   memcpy(look->sunVec, &xa_lv[XA_LV_USUNX], 3 * sizeof(double));
   memcpy(look->moonVec, &xa_lv[XA_LV_UMOONX], 3 * sizeof(double));
}



// Print header for sensor/satellite look angles
void PrintSenSatHeader(FILE* fpOut, SenSatData* senSatData) 
{
   char CSAT[30];
   char* CUN;
   char dash[] = "-------------------------------------------------------------------------------------"
      "-------------------------------------------------------------------------------------";
   int lineLen;
   int units;
   char testStr[256];
   int  stepModeReq;
   SatParms satParms;


   // Retrieve processing mode
   stepModeReq = GetIntegerField(LamodGet1pField, XF_1P_STEPMODE);

   if (stepModeReq == STEPMODE_STEP)
      fprintf(fpOut, "\n\n+++++ STEP-MODE REQUESTED BY USER +++++\n\n");
   else if (stepModeReq == STEPMODE_CULM)
      fprintf(fpOut, "\n\n+++++ CULMINATION-MODE REQUESTED BY USER +++++\n\n");
   else if (stepModeReq == STEPMODE_TASK)
      fprintf(fpOut, "\n\n+++++ TASK-MODE REQUESTED BY USER +++++\n\n");

   // The stepmode has been changed from what has requested
   if (stepModeReq != senSatData->stepMode && stepModeReq == STEPMODE_CULM)
   {
      if (senSatData->viewType == '9')
         fprintf(fpOut, "+++++ STEP-MODE INVOKED FOR ORBITING SENSOR +++++\n\n");
      else
         fprintf(fpOut, "+++++ STEP-MODE INVOKED FOR LARGE PERIOD ORBIT +++++\n\n");
   }

   strcpy(CSAT, " ");

   if (senSatData->viewType == '9')
   {
      sprintf(CSAT, "%s%5d", "SAT #", senSatData->satNum);
   }


   units = GetKey64IntegerField((fnPtrGetKey64Field)SensorGetLimField, senSatData->senKey, XF_SENLIM_UNIT);

   CUN = "km";
   if (units != 0)
      CUN = "nm";


   fprintf(fpOut, "LOOK ANGLES FOR SATELLITE %5d%14sSENSOR %3d\n", senSatData->satNum, " ", senSatData->senNum);

   RetrieveSatParms(senSatData->satKey, &satParms);

   fprintf(fpOut, "EPOCH TIME %s     ELEMENT SET NO.%4d\n", UTCToDtg20Str(satParms.epochUTC), satParms.elsetNum);

   if (senSatData->obsType == '8' || senSatData->obsType == 'M')
   {
      fprintf(fpOut, "TIME                  ELEV    AZ         RNG      RelVel.  OB        SENSOR POSITION\n");
      fprintf(fpOut, "YY DDD HHMM SS.SSS    deg     deg        %2s       km/sec       E km      F km      G km\n", CUN);
      lineLen = 91;
   }
   else if (senSatData->obsType == '9' || senSatData->obsType == 'O')
   {
      fprintf(fpOut, "TIME                  ELEV    AZ         RNG      RelVel. RT.ASCEN.     DECLINATION   SOLAR PHASE I OB        SENSOR POSITION\n");
      fprintf(fpOut, "YY DDD HHMM SS.SSS    deg     deg        %2s       km/sec  HR MN SEC     deg MA SA     ANGLE (deg) L       E km      F km      G km\n", CUN);
      lineLen = 132;
   }
   else if (senSatData->obsType == '5')
   {
      fprintf(fpOut, "TIME                  ELEV    AZ         RNG      RNG-RT  RT.ASCEN.     DECLINATION   SOLAR PHASE  I OB\n");
      fprintf(fpOut, "YY DDD HHMM SS.SSS    deg     deg        %2s       %2s/sec  HR MN SEC     deg MA SA     ANGLE (deg)  L   \n", CUN, CUN);
      lineLen = 103;
   }
   else
   {
      // DHN 15Aug11 - Add azimuth and elevation rates for obsType 4
      if (senSatData->obsType == '4')
      {
         fprintf(fpOut, "TIME                  ELEV    AZ         RNG      RNG-RT   OB   AZ-RT       EL-RT\n");
         fprintf(fpOut, "YY DDD HHMM SS.SSS    deg     deg        %2s       %2s/sec        deg/sec     deg/sec\n", CUN, CUN);
         lineLen = 85;
      }
      else
      {
         fprintf(fpOut, "TIME                  ELEV    AZ         RNG      RNG-RT   OB\n");
         fprintf(fpOut, "YY DDD HHMM SS.SSS    deg     deg        %2s       %2s/sec   \n", CUN, CUN);
         lineLen = 61;
      }
   }

   strncpy(testStr, dash, lineLen);
   testStr[lineLen] = 0;
   fprintf(fpOut, "%s\n", testStr);
}


// Determine if the current print step is rise: 'r', set: 's', culmination: 'c', pass: 'p', or normal step ' '
char CurrPrintStep(double currDs50TAI, double* rcs, double interval, double stopDs50TAI)
{
   char currStep = ' ';

   if (fabs(currDs50TAI - rcs[2]) <= EPSTIMEDAYS)
      currStep = 's';
   else if (fabs(currDs50TAI - rcs[1]) <= EPSTIMEDAYS)
      currStep = 'c';
   else if (fabs(currDs50TAI - rcs[0]) <= EPSTIMEDAYS)
      currStep = 'r';
   else if (currDs50TAI + (interval / MINSPERDAY) > stopDs50TAI)
      currStep = 'p';

   return currStep;
}


// Print one look angle
void PrintLook(FILE* fpOut, SenSatData* senSatData, char currStep, char* cobp, LookAngle* la)
{
   char* formatStr;

   double elevation, rangeRate;
   double rasc, decl;

   int raHr, raMin, decliDeg, decliMin;
   double raSec, decliSec;
   char currTimeStr[19];
   char decSignStr[4];

   elevation = la->elevation_deg;

   // Avoid printing -0.000
   if (PrintAsZero(elevation))
      elevation = 0;

   rangeRate = la->rangeRate_kmps;

   // Avoid printing -0.000
   if (PrintAsZero(rangeRate))
      rangeRate = 0;

   formatStr = "";

   if (senSatData->obsType == '5' || senSatData->obsType == '9' || senSatData->obsType == 'O')
   {
      LamodCompRaDec(la->unitRangeVec, &rasc, &decl, &raHr, &raMin, &raSec, &decliDeg, &decliMin, &decliSec);
      if (decliDeg == 0 && decl < 0)
         strcpy(decSignStr, " -0");
      else
         sprintf(decSignStr, "%3d", decliDeg);
   }


   cobp = "  ";

   strcpy(currTimeStr, UTCToDtg18Str(la->lookTimeDs50UTC));

   if (senSatData->obsType == '8' || senSatData->obsType == 'M')
   {
      formatStr = "%20s  %7.3f  %7.3f %10.3f %8.4f  %2s %10.3f%10.3f%10.3f\n";
      fprintf(fpOut, formatStr, currTimeStr, elevation, la->azimuth_deg, la->range_km, la->relVel, cobp, la->senPosEFG[0], la->senPosEFG[1], la->senPosEFG[2]);
   }
   else if (senSatData->obsType == '9' || senSatData->obsType == 'O')
   {
      formatStr = "%18s  %7.3f  %7.3f %10.3f %8.3f  %2d %2d %6.3f  %s %2d %5.2f"
         "   %8.3f  %c%c %2s%10.3f%10.3f%10.3f\n";

      fprintf(fpOut, formatStr,
         currTimeStr, elevation, la->azimuth_deg, la->range_km, la->relVel, raHr, raMin, raSec, decSignStr, decliMin, decliSec,
         la->SAA_deg, ' ', la->illumination, cobp, la->senPosEFG[0], la->senPosEFG[1], la->senPosEFG[2]);
   }
   else if (senSatData->obsType == '5')
   {
      formatStr = "%s  %7.3f  %7.3f %10.3f %8.3f  %2d %2d %6.3f  %s %2d %5.2f"
         " %c %8.3f    %c %2s\n";
      fprintf(fpOut, formatStr,
         currTimeStr, elevation, la->azimuth_deg, la->range_km, rangeRate, raHr, raMin, raSec, decSignStr, decliMin, decliSec,
         currStep, la->SAA_deg, la->illumination, cobp);
   }
   else
   {
      // DHN 15Aug11 - Add azimuth and elevation rates for obsType 4
      if (senSatData->obsType == '4')
      {
         formatStr = "%s  %7.3f  %7.3f %10.3f %8.3f %c %2s  %10.7f  %10.7f\n";
         fprintf(fpOut, formatStr, currTimeStr, elevation, la->azimuth_deg, la->range_km, rangeRate, currStep, cobp, la->azRate_degps, la->elRate_degps);
      }
      else
      {
         formatStr = "%s  %7.3f  %7.3f %10.3f %8.3f %c %2s\n";
         fprintf(fpOut, formatStr, currTimeStr, elevation, la->azimuth_deg, la->range_km, rangeRate, currStep, cobp);
      }
   }
}


// Print look angle summary for the sensor/satellite pair
void PrintSummary(FILE* fpOut, int senNum, int satNum, int numLooks, int numPasses)
{
   fprintf(fpOut, "      SUMMARY FOR SATELLITE %5d and SENSOR %03d:\n", satNum, senNum);
   fprintf(fpOut, "      ------------------------------------------\n");
   if (numLooks == 0)
      fprintf(fpOut, "      *** NO LOOK ANGLES FOUND ***\n");
   else
   {
      fprintf(fpOut, "      %6d look angle(s) printed\n", numLooks);
      fprintf(fpOut, "        %4d pass(es) computed\n", numPasses);
   }

   fprintf(fpOut, "      ------------------------------------------\n\n\n");
}


// Print various diagnostic information 
void PrintNosticData(FILE* fp, SenSatData* senSatData, int nosticFlg, LookAngle* la)
{
   // DHN 19May11 - Only print pass by pass nostic if nostic flag >= 2
   if (nosticFlg >= 2)
   {
      // Print sensor/satellite number at each step
      fprintf(fp, "\n");
      fprintf(fp, "   >>> Sensor: %3d - Satellite: %6d - Time: %20s - Mse: %14.6f\n",
         senSatData->senNum,
         senSatData->satNum,
         UTCToDtg20Str(la->lookTimeDs50UTC),
         la->lookTimeMSE);

      if (la->lookCode == LOOK_VALID)
         fprintf(fp, "    +++ The sensor/satellite PASSED all limit tests +++\n");
      else if (la->lookCode == LOOK_HTEST)
         fprintf(fp, "    --- The sensor/satellite FAILED horizon break test ---\n");
      else
      {
         //check for ground-based optical illumination: sat must be in sunlight & sensor in darkness
         if (la->illumination == 'N')
            fprintf(fp, "    --- The sensor/satellite FAILED illumination test (sensor isn't in darkness & sensor isn't sunlit)---\n");
         else if (la->illumination == 'A')
            fprintf(fp, "    --- The sensor/satellite FAILED illumination test (satellite isn't sunlit)---\n");
         else if (la->illumination == 'E')
            fprintf(fp, "    --- The sensor/satellite FAILED illumination test (sensor isn't in darkness)---\n");
         PrintPassByPassNostic(fp, senSatData->viewType, la);
      }
   }

   // Print sensor/satellite position at each look if requested
   if (la->lookCode == LOOK_VALID && (nosticFlg == 1 || nosticFlg == 3))
      PrintSenSatPosition(fp, senSatData->viewType, la);
}


// Print pass-by-pass diagnostics
void PrintPassByPassNostic(FILE* fp, char viewType, LookAngle* la)
{
   char msgStrFormat[] = "    --- The sensor/satellite FAILED %s test ---\n";

   // check for failed range limits
   if (la->passMinRange == 0)
      fprintf(fp, msgStrFormat, "minimum range");

   if (la->passMaxRange == 0)
      fprintf(fp, msgStrFormat, "max range");

   /*
   // visibility checks: earth-based sensors...
   if (limFlgArr[XA_LIMFLG_Visual] == 0)
   fprintf(fp, msgStrFormat, "illumination");
   */


   // orbiting sensors: check for eclipse conditions
   if (viewType == '9')
      if (la->passUmbEclip == 0)
         fprintf(fp, msgStrFormat, "umbral eclipse");
      else if (la->passPenEclip == 0)
         fprintf(fp, msgStrFormat, "penum. eclipse");

   // pass failed sensor azimuth limit
   if (la->passAzLim == 0)
      fprintf(fp, msgStrFormat, "azimuth/ra limit");

   // pass failed sensor el limit
   if (la->passElLim == 0)
      fprintf(fp, msgStrFormat, "el/dec limit");


   // pass failed solar aspect angle test
   if (la->passSAALim == 0)
      fprintf(fp, msgStrFormat, "solar aspect angle");

   // pass failed range-rate/relative velocity limit
   if (la->passRVelLim == 0)
      fprintf(fp, msgStrFormat, "rge-rt/rel-vel limit");

   // for sat-to-sat, check for planetary obstructions: earth first
   //!CVIS2 = " "
   if (la->passEarthOb == 0)
      fprintf(fp, msgStrFormat, "earth obstruction");
   else if (la->passEarthOb == 0)
      fprintf(fp, msgStrFormat, "earth in background");
   //!else
   //   CVIS2 = "E" 

   // ..., check for sun too close to observed satellite
   if (la->passSolExcl == 0)
      fprintf(fp, msgStrFormat, "solar exclusion");

   // ...finally, check for moon too close to observation
   if (la->passLunExcl == 0)
      fprintf(fp, msgStrFormat, "lunar exclusion");

   //// for optical ground, check for moon too close to observation 10DEC04
   //if (limFlgArr[XA_LIMFLG_LUNEXCL] == 0)
   //   fprintf(fp, msgStrFormat, "lunar exclusion");
}


// Print sensor/satellite positions at the time the look is computed
void PrintSenSatPosition(FILE* fp, char viewType, LookAngle* la)
{
   fprintf(fp, "    Sensor Position: X   =%10.3f km;  Y   =%10.3f km;  Z   =%10.3f km \n", la->senPos[0], la->senPos[1], la->senPos[2]);
   fprintf(fp, "           Velocity: XD  =%10.5f k/s; YD  =%10.5f k/s; ZD  =%10.5f k/s\n", la->senVel[0], la->senVel[1], la->senVel[2]);
   fprintf(fp, "           Geod    : nLat=%10.5f deg; eLon=%10.5f deg; Hght=%10.3f km \n", la->senLLH[0], la->senLLH[1], la->senLLH[2]);
   fprintf(fp, "    Sat Position   : X   =%10.3f km;  Y   =%10.3f km;  Z   =%10.3f km \n", la->satPos[0], la->satPos[1], la->satPos[2]);
   fprintf(fp, "        Velocity   : XD  =%10.5f k/s; YD  =%10.5f k/s; ZD  =%10.5f k/s\n", la->satVel[0], la->satVel[1], la->satVel[2]);
   fprintf(fp, "        Geod       : nLat=%10.5f deg; eLon=%10.5f deg; Hght=%10.3f km \n", la->satLLH[0], la->satLLH[1], la->satLLH[2]);


   // For orbiting sensors
   if (viewType == '9')
   {
      fprintf(fp, "    Solar Unit Vec : X   =%14.8f      Y   =%14.8f      Z   =%14.8f\n", la->sunVec[0], la->sunVec[1], la->sunVec[2]);
      fprintf(fp, "    Lunar Unit Vec : X   =%14.8f      Y   =%14.8f      Z   =%14.8f\n", la->moonVec[0], la->moonVec[1], la->moonVec[2]);
      fprintf(fp, "    Angles (deg): Sun/sen/sat =%8.3f; Sun/earth/sat =%8.3f; Sun/earth/sen =%8.3f; Moon/sen/sat =%8.3f\n",
         la->sunSenSat_deg, la->sunEarthSat_deg, la->sunEarthSen_deg, la->moonSenSat_deg);

      if (la->nBore1 > 0)
      {
         fprintf(fp, "    Off-boresight & clock angles (#1) =%8.3f & %8.3f deg\n",
            la->offBoreElev1_deg, la->offBoreAzim1_deg);

         if (la->nBore2 > 0 && la->nBore2 < 7)
            fprintf(fp, "    Off-boresight & clock angles (#2) =%8.3f & %8.3f deg\n",
               la->offBoreElev2_deg, la->offBoreAzim2_deg);
      }
   }
   fprintf(fp, "\n");

}



// Print generated obs to file
void PrintObs(FILE* fpObsFile, __int64 senSatKey, int punchObs)
{
   char obsLine1[INPUTCARDLEN];
   char obsLine2[INPUTCARDLEN];
   int numLines;

   LamodGenObs(senSatKey, punchObs, 'U', obsLine1, obsLine2, &numLines);
   obsLine1[INPUTCARDLEN - 1] = 0;
   obsLine2[INPUTCARDLEN - 1] = 0;

   fprintf(fpObsFile, "%s\n", obsLine1);
   if (numLines == 2)
      fprintf(fpObsFile, "%s\n", obsLine2);
}
