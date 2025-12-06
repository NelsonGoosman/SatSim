#ifndef OBSOPSDLL_SERVICE_H
#define OBSOPSDLL_SERVICE_H

#include "ObsDll_Service.h"

// IOMOD control parameters structure
typedef struct
{
   int  printIOHG;
   int  useFirst3Obs;
   int  satNum;
   int  sortOrder;
   char satName[9];
   int  runDC;
   int  runRotas;
} IomodCtrl;


void GetIomodCtrlPara(IomodCtrl* iomodCtrl);
void PrintIomodCtrls(FILE* fpOut, IomodCtrl* iomodCtrl);
void PrintObsPosData(FILE* fpOut, int obsNum, ObsRecord* obs, double pos[]);
void PrintIomodIters(FILE* fpOut, int numObs, ObsRecord obsArr[], int numIters, double xa_iomIter[][8], double arr3Pos[][3]);
#endif
