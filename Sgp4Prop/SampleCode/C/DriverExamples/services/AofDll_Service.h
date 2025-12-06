#ifndef AOFDLL_SERVICE_H
#define AOFDLL_SERVICE_H

#include "../wrappers/DllMainDll.h"

// Aof control parameters structure
typedef struct
{
   int a;
} AofCtrl;


void GetAofCtrlPara(AofCtrl* fovCtrl);
void PrintAofCtrl(FILE* fpOut, double xa_aofCtrl[16]);
void PrintAreaData(FILE* fpOut, double xa_aofArea[16]);
void PrintEntryExit(FILE* fpOut, double xa_aofArea[16], int satNum, __int64 satKey, int numOfPens, double xa_entExitTimes[]);
#endif
