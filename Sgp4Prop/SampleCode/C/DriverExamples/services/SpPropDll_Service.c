#include "DllUtils.h"
#include "SpPropDll_Service.h"


#include "../wrappers/DllMainDll.h"
#include "../wrappers/SpPropDll.h"
#include "../wrappers/TimeFuncDll.h"


// Print SP application control parameters
void PrintSpAppCtrl(FILE* fp)
{
   char geoDir[FILEPATHLEN];
   int buffSize;
   int runMode;
   int savePartials;
   int isSpectr;
   double consider;
   int decayAlt;
   int outCoord;
   char truncGeoDir[60];
   char outCoordSys[][40] = {"true equator, mean equinox of date ", 
                             "true equator, mean equinox of Epoch", 
                             "mean equator, mean equinox of FK5  "};


   char dashLine[]  = "-------------------------------------------------------------------------------";
   char ddashLine[] = "===============================================================================";


   // Get SP application control data
   SpGetApCtrlAll(geoDir, &buffSize, &runMode, &savePartials, &isSpectr, &consider, &decayAlt, &outCoord);
   geoDir[FILEPATHLEN-1] = 0;
   strncpy(truncGeoDir, geoDir, 59);
   truncGeoDir[59] = 0;
   

   fprintf(fp, " %s\n", ddashLine);
   fprintf(fp, " |         S P   A P P L I C A T I O N   C O N T R O L   O P T I O N S         |\n");
   fprintf(fp, " %s\n", dashLine);
   fprintf(fp, " | Geo Dir Path   : %59s|\n", truncGeoDir);
   fprintf(fp, " | Buffer size    : %6d%53s|\n", buffSize, " ");
   fprintf(fp, " | Run Mode       : %-59s|\n", runMode == 1 ? "Memory Priority" : "Performance Priority");
   fprintf(fp, " | Specter Mode   : %-59s|\n", isSpectr == 1 ? "Compatible" : "Not Compatible");
   fprintf(fp, " | Consider       : %8.3f%51s|\n", consider, " ");
   fprintf(fp, " | Decay Altitude : %6d km%50s|\n", decayAlt, " ");
   fprintf(fp, " | Output CoordSys: %-59s|\n", outCoordSys[outCoord]);
   fprintf(fp, " | Save Partials  : %-59s|\n", savePartials == 1 ? "Yes" : "No");
   fprintf(fp, " %s\n", ddashLine);
   fprintf(fp, "\n");
}

// Print SP prediction control paramaters
void PrintPredCtrl(FILE* fp)
{
   char dashLine[]  = "-------------------------------------------------------------------------------";
   char ddashLine[] = "===============================================================================";

   int startFrEpoch, stopFrEpoch;
   double startTime, stopTime, stepSize;
   char dtg17[18];

   startFrEpoch = stopFrEpoch = 0;
   startTime = stopTime = stepSize = 0;

   // Get prediction control data 
   SpGetPredCtrl(&startFrEpoch, &stopFrEpoch, &startTime, &stopTime, &stepSize);


   fprintf(fp, " %s\n", ddashLine);
   fprintf(fp, " |           S P   P R E D I C T I O N   C O N T R O L   O P T I O N S         |\n");
   fprintf(fp, " %s\n", dashLine);
   if (startFrEpoch)
      fprintf(fp, " | Start Since Epoch= %12.3lf%45s|\n", startTime, " ");
   else
   {
      UTCToDTG17(startTime, dtg17); 
      dtg17[17] = 0;
      fprintf(fp, " | Start Date       = %-57s|\n", dtg17);
   }

   if (stopFrEpoch)
      fprintf(fp, " | Stop Since Epoch = %12.3lf%45s|\n", stopTime, " ");
   else
   {
      UTCToDTG17(stopTime, dtg17); 
      dtg17[17] = 0;
      fprintf(fp, " | Stop Date        = %-57s|\n", dtg17);
   }

   fprintf(fp, " | Interval (min)   = %12.3lf%45s|\n", stepSize, " ");
   fprintf(fp, " %s\n", ddashLine);
   fprintf(fp, "\n");
}
 
// Convert geo index to geo name
const char* GeoIdxToStr(int geoIdx)
{
   switch(geoIdx)
   {
      case 1:
         return "user-specified ASCII geopotential file";
      case 3: 
         return "SP003 (STEM68R) 6th order";
      case 4: 
         return "SP004 (STEM68R) 8th order";
      case 5: 
         return "WGS72 J2-J5 (zonals) ONLY";
      case 6: 
         return "WGS72 thru (6,6) ONLY";
      case 7: 
         return "WGS72 thru (4,4) ONLY";
      case 8: 
         return "WGS72 thru (8,8) ONLY";
      case 9: 
         return "WGS84 9th order (thru 9,9 only)";
      case 10: 
         return "WGS84 J2-J5 (zonals) ONLY";
      case 11: 
         return "NWL-8C 12th order (thru 12,12)";
      case 12: 
         return "WGS72 12th order (thru 12,12)";
      case 18: 
         return "WGS84 18th order (thru 18,18)";
      case 20: 
         return "WGS72 with user-specified o/d/z";
      case 21: 
         return "WGS84 with user-specified o/d/z";
      case 22: 
         return "GEM5 22nd order (thru 22,16)";            
      case 24: 
         return "WGS72 24th order (thru 24,24)";
      case 25: 
         return "WGS72 12th order & (13,13)-(29,13)";
      case 26: 
         return "WGS72 12th order & (14,14), (15,14)";
      case 27: 
         return "WGS72 12th order";
      case 30: 
         return "GEM9 30th order (thru 30,30)";
      case 40: 
         return "JGM2 41st order (thru 41,41)";
      case 41: 
         return "WGS84 41st order (thru 41,41)";
      case 70: 
         return "WGS84 full 70th order (thru 70,70)";
      case 71: 
         return "EGM-96 70th order (thru 70,70)";
      default: 
         return "WGS72 12th order";
   }
}


// Print SP integration control parameters
void PrintSpIntegCtrl(FILE* fp)
{
   char dashLine[]  = "-------------------------------------------------------------------------------";
   char ddashLine[] = "===============================================================================";
   char tempStr[INPUTCARDLEN];
   char CGNM[42];
   
   char CINT[][41] = {"auto selection (based upon eccentricity)", "forced t (time)", "forced s-integration"};
   char CNAMA[][7] = {"      ", "Jach64", "Jach70", "DCA   "};
   char COM[][7] =   {"SPADOC", "SPECTR"};
   char CVAR[][11] = {"variable", "fixed", "semi-fixed"};
   char noYes[][4] = {"no", "yes", "yes"};
   char lsPertModes[][6] = { "no", "yes", "jpl", "all", "big", "med", "sma" };

   int geoIdx, bulgePert, dragPert, radPresPert, lunSolPert, f10, f10Avg, ap, trunc, incr, ogPert, tidePert, inCoord, nTerms, reEval, integStepMode, stepSizeMethod;
   double initStepSize;
   char dcaFile[FILEPATHLEN];
   char fluxFile[FILEPATHLEN];
   char geoFile[FILEPATHLEN];
   char jplFile[FILEPATHLEN];
   char jplStart[FILEPATHLEN];
   char jplStop[FILEPATHLEN];

   char geoDir[INPUTCARDLEN];
   int bufSize, runMode, savePartials, isSpectr, decayAlt, outCoord;
   double consider;


   SpGetApCtrlAll(geoDir, &bufSize, &runMode, &savePartials, &isSpectr, &consider, &decayAlt, &outCoord);

   // Get SP integration control data
   SpGet4pAll(&geoIdx, &bulgePert, &dragPert, &radPresPert, &lunSolPert, &f10, &f10Avg, &ap, &trunc,
              &incr, &ogPert, &tidePert, &inCoord, &nTerms, &reEval, &integStepMode, &stepSizeMethod, 
              &initStepSize, dcaFile, fluxFile, geoFile, jplFile, jplStart, jplStop);

   dcaFile[FILEPATHLEN-1] = 0;
   fluxFile[FILEPATHLEN-1] = 0;
   geoFile[FILEPATHLEN-1] = 0;
   jplFile[FILEPATHLEN-1] = 0;
   jplStart[FILEPATHLEN-1] = 0;
   jplStop[FILEPATHLEN-1] = 0;


   fprintf(fp, " %s\n", ddashLine);
   fprintf(fp, " |         S P   I N T E G R A T I O N   C O N T R O L   O P T I O N S         |\n");
   fprintf(fp, " %s\n", dashLine);
   fprintf(fp, " | COMPATIBILITY MODE: %-56s|\n", COM[isSpectr]);
   
   // geopotential name
   if (bulgePert == 0)
      strcpy(CGNM, "2-body");
   else
      strcpy(CGNM, GeoIdxToStr(geoIdx));

   // print bulge perts selected
   fprintf(fp, " |  A.  MODEL BULGE (GRAVITY) PERTS?  %-40s |\n", noYes[bulgePert]);
   fprintf(fp, " |      > GEOPOTENTIAL MODEL:         %-40s |\n", CGNM);
   fprintf(fp, " |      > TRUNCATED TO      :         %3dZ, %3dT%30s |\n", trunc, trunc, " ");

   if (dragPert > 0)
      fprintf(fp, " |  B.  DRAG PERTURBATIONS MODELED?   %-3s (%-34s) |\n", "yes" , CNAMA[dragPert]);
   else
      fprintf(fp, " |  B.  DRAG PERTURBATIONS MODELED?   %-3s%-37s |\n", "no", " ");
   fprintf(fp, " |  C.  LUNAR/SOLAR PERTS MODELED?    %-40s |\n", lsPertModes[lunSolPert]);
   fprintf(fp, " |      > EARTH/OCEAN TIDES MODELED?  %-40s |\n", noYes[tidePert]);
   fprintf(fp, " |  D.  RAD. PRESSURE PERTS MODELED?  %-40s |\n", noYes[radPresPert]);
   fprintf(fp, " |  E.  OUTGASSING PERTS MODELED?     %-40s |\n", noYes[ogPert]);
   fprintf(fp, " |  F.  CONSTANT FLUX USED?           %-40s |\n", f10 > 0 ? "yes" : "no");
   if (f10 > 0)
      fprintf(fp, " |      F10, F10avg, Ap:              %6d%6d%7d%21s |\n", f10, f10Avg, ap, " ");
   // if set corrector step convergence criterion to zero, internally that means using the default
   // value instead; default = 14 for SPECTR and default = 10 for non SPECTR
   if(incr == 0)
   {
      if(isSpectr)
         incr = 14;
      else
         incr = 10;
   }

   fprintf(fp, " |  H.  SP INTEGRATOR CONVERG. CRIT.  1.E-%-3d%33s |\n", incr, " ");
   fprintf(fp, " |  I.  INTEGRATION VARIABLE:         %-40s |\n", CINT[integStepMode]);
   fprintf(fp, " |  J.  STEP-SIZE CONTROL:            %-40s |\n", CVAR[stepSizeMethod]);
   if (initStepSize <= 0)
      fprintf(fp, " |  L.  INITIAL STEP-SIZE (min):      %-40s |\n", "computed from a & e");
   else
      fprintf(fp, " |  L.  INITIAL STEP-SIZE (min):      %9.4f%-31s |\n", initStepSize, " ");
   fprintf(fp, " |  O.  OTHER VALUES SUB-MENU:        %-40s |\n", " ");
   fprintf(fp, " |      c. CORRECTOR: RE-EVAL PERTS?  %-40s |\n", noYes[reEval]);
   if (nTerms == 0)
      if (isSpectr == 1)
         strcpy(tempStr, "SPECTR 4-term");
      else
         strcpy(tempStr, "SPADOC compatible");
   else
      sprintf(tempStr, "%5d",  nTerms);

   fprintf(fp, " |      e. NUTATION ALGORITHM USED:   %-40s |\n", tempStr);
   fprintf(fp, " %s\n", ddashLine);
   fprintf(fp, "\n");
}
