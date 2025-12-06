#ifndef FOVDLL_SERVICE_H
#define FOVDLL_SERVICE_H

#include "../wrappers/DllMainDll.h"

// Fov control parameters structure
typedef struct
{
   double searchInterval;  //search interval(min) 2 min for near earth or 15 for all else
   double coneSize;        //cone size(deg: 0 - 45) exact zero means use auto - cone algorithm
   int    printOpt;        //print options
                           //0 = print victim information only
                           //1 = print victim info & initial condition of each source / target pair
                           //2 = all above, plus initial conditions of each secondary satellite
                           //3 = all above, plus detailed victim info
                           //4 = all above, plus range to target

   int numOfWindows;                //number of start / stop windows
   double startStopTimes[256];      //odd = start times, even = stop times

   int numOfSources;                //number of sources entered
   double xa_fovSrc_2D[128][8];     //source(of emission) record

   int numOfTargets;                //number of targets entered
   double xa_fovTgt_2D[128][8];     //target(of emission) record

   int numVicSats;                  //number of victim satellites entered
   int vicSatNums[128];             //input potential victim satellite numbers

} FovCtrl;




void GetFovCtrlPara(FovCtrl* fovCtrl);
void PrintFovCtrls(FILE* fpOut, double xa_fovCtrl[8], int numOfWindows, double startStopTimes[256], int numOfSources, double xa_fovSrc_2D[][8], int numOfTargets, double xa_fovTgt_2D[][8]);
void PrintPenetrationTimes(FILE* fpOut, int isNewWindow, int winNum, double xa_fovSrc[], double xa_fovTgt[], __int64 vicSatKey, double xa_emeDat[][3], int numOfPens);
void GetLookAngle(int tgtType, double ds50TAI, double xa_fovSrc[], double xa_fovTgt[], __int64 vicSatKey, double xa_look[]);
void PrintDetailLookAngles(FILE* fpOut, double xa_fovRun[], double xa_fovSrc[], double xa_fovTgt[], __int64 tgtSatKey, __int64 vicSatKey);
void PrintSourceTargetData(FILE* fpOut, double xa_fovSrc[8], double xa_fovTgt[8]);
#endif
