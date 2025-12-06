#include "DllUtils.h"
#include "ObsOpsDll_Service.h"
#include "ObsDll_Service.h"
#include "TimeFuncDll_Service.h"

#include "../wrappers/ObsOpsDll.h"


// Retrieve Iomod control data from the dll
void GetIomodCtrlPara(IomodCtrl* iomodCtrl)
{
   double extArr[128];
   IomodGetIpAll(&iomodCtrl->printIOHG,
      &iomodCtrl->useFirst3Obs,
      &iomodCtrl->satNum,
      &iomodCtrl->sortOrder,
      iomodCtrl->satName,
      &iomodCtrl->runDC,
      &iomodCtrl->runRotas,
      extArr);

   iomodCtrl->satName[8] = 0; // nullify the satName string
}

void PrintIomodCtrls(FILE* fpOut, IomodCtrl* iomodCtrl)
{
   //Sort options(order) :
   //(+/ -)1 = (descending / ascending) time, sensor, obstype, elev
   //(+/ -)2 = (descending / ascending) time, elevation
   //(+/ -)3 = (descending / ascending) time, sensor, otype, el, satno
   //(+/ -)4 = (descending / ascending) sensor, satno, time, elev
   //(+/ -)5 = (descending / ascending) sensor, time, elevation
   //(+/ -)6 = (descending / ascending) sensor, satno, obstype, time, elev
   //(+/ -)7 = (descending / ascending) satno, time, sensor, otype, el
   //(+/ -)8 = (reversed / same)        order of obs were read
   //9 : as is in the tree (fastest sort time)


   char obSortOrder[][35] = {"time, sensor, obstype, elev",
                             "time, elevation",
                             "time, sensor, otype, el, satno",
                             "sensor, satno, time, elev",
                             "sensor, time, elevation",
                             "sensor, satno, obstype, time, elev",
                             "satno, time, sensor, otype, el",
                             "order of obs were read",
                             "order of obs stored in the memory"};

   char* obsOrderStr;
   int   sortOrder;
   int   len;

   sortOrder = iomodCtrl->sortOrder;

   if (abs(sortOrder) <= 8)
   {
      if (sortOrder < 0)
         obsOrderStr = "ascending";
      else
         obsOrderStr = "descending";
   }
   else if (sortOrder == 8)
      obsOrderStr = "reversed";
   else if (sortOrder == -8)
      obsOrderStr = "same";
   else
      obsOrderStr = "";

   len = 42 - ((int)strlen(obsOrderStr) + (int)strlen(obSortOrder[abs(sortOrder) - 1]));

   fprintf(fpOut, "            INITIAL ORBIT (IOMOD) OPTIONS:\n");
   fprintf(fpOut, " ===============================================================================\n");
   fprintf(fpOut, " |  A.  PRINT IOHG INFORMATION?     %-43s|\n", iomodCtrl->printIOHG == 1 ? "yes" : "no");
   fprintf(fpOut, " |  B.  IOHG OB SELECTION METHOD:   %-43s|\n", iomodCtrl->useFirst3Obs == 1 ? "use first 3 obs" : "automatic selection");
   fprintf(fpOut, " |  C.  OBSERVATION SORT ORDER:     %s %s%*s|\n", obsOrderStr, obSortOrder[abs(sortOrder)-1], len, " ");
   if (iomodCtrl->satNum != 0)
      fprintf(fpOut, " |  D.  OUTPUT ELSET SATELLITE NO:  %7d%36s|\n", iomodCtrl->satNum, " ");
   else
      fprintf(fpOut, " |  D.  OUTPUT ELSET SATELLITE NO:  %-43s|\n", "(from obs used)");

   fprintf(fpOut, " |  E.  OUTPUT ELSET INTL DESIG:    %-43s|\n", iomodCtrl->satName);
   fprintf(fpOut, " |  F.  RUN POST-IOMOD DC?          %-43s|\n", iomodCtrl->runDC == 1 ? "yes" : "no");
   fprintf(fpOut, " |  G.  RUN POST-IOMOD ROTAS?       %-43s|\n", iomodCtrl->runRotas == 1 ? "yes" : "no");
   fprintf(fpOut, " ===============================================================================\n");

}

// Print obs's estimated position data
void PrintObsPosData(FILE* fpOut, int obsNum, ObsRecord* obs, double pos[])
{
   fprintf(fpOut, " %4d   %6d %5d %18s %12.3f%12.3f%12.3f\n", obsNum, obs->satNum, obs->senNum,
      UTCToDtg18Str(obs->obsTimeDs50UTC), pos[0], pos[1], pos[2]);
}

void PrintIomodIters(FILE* fpOut, int numObs, ObsRecord obsArr[], int numIters, double xa_iomIter[][8], double arr3Pos[][3])
{
   int i;

   fprintf(fpOut, "\n");
   fprintf(fpOut, "   HERRICK - GIBBS(IOHG) INITIAL ELEMENT GENERATION\n");

   if (numIters > 0)
   {
      for (i = 0; i < numIters; i++)
      {
         fprintf(fpOut, "%s%2d%s%12.3f%12.3f%12.3f%s%e\n", "IT # ", i + 1, ", RGs =",
            xa_iomIter[i][XA_IOMITER_RNG1], xa_iomIter[i][XA_IOMITER_RNG2], xa_iomIter[i][XA_IOMITER_RNG3], ", EPS= ", xa_iomIter[i][XA_IOMITER_CONV]);
      }

      fprintf(fpOut, "%s%12.3f%12.3f%12.3f\n", " Gauss - Gibbs estimated ranges(km) :",
         xa_iomIter[numIters - 1][XA_IOMITER_RNG1], xa_iomIter[numIters - 1][XA_IOMITER_RNG2], xa_iomIter[numIters - 1][XA_IOMITER_RNG3]);
   }


   // display the 2 or 3 obs that were used in IOMOD
   for (i = 0; i < min_i(numObs, 3); i++)
   {
      if (i == 0)
      {
         fprintf(fpOut, "   OB#    TAG    SEN          TIME             X(km)       Y(km)       Z(km)\n");
      }
      PrintObsPosData(fpOut, i + 1, &obsArr[i], arr3Pos[i]);
   }

   fprintf(fpOut, "\n");
}

