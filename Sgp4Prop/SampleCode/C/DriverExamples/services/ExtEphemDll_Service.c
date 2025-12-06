#include "DllUtils.h"
#include "ExtEphemDll_Service.h"

#include "../wrappers/ExtEphemDll.h"


void PrintVecEphHeader(FILE* fp, double ke, double er, char* epochStr, char* orbEltType)
{
   fprintf(fp, "%22.14E%22.14E %15s%14sSP %3s\n", ke, er, epochStr, " ", orbEltType);
}


void PrintSimObsHeader(FILE* fp, double ke, double er, char* epochStr)
{
   fprintf(fp, "%22.14E%22.14E %15s%19sZ\n", ke, er, epochStr, " ");
}


void PrintVecEphPoint(FILE* fp, int satNum, char* ds50UTCStr, double mse, double* pos, double* vel, char* orbEltType)
{
   char vecEphFileType;
   
   if (strcmp(orbEltType, "efg") == 0)
      vecEphFileType = '3';
   else
      vecEphFileType = '1';

   fprintf(fp, " %16.6f %15.6f %15.6f %15.6f %5d %c SP %3s\n", mse, pos[0], pos[1], pos[2], satNum, vecEphFileType, orbEltType);
   fprintf(fp, "  %15s %15.9f %15.9f %15.9f %5d %c SP %3s\n", ds50UTCStr, vel[0], vel[1], vel[2], satNum, vecEphFileType, orbEltType);
}



void PrintSimObsPoint(FILE* fp, int satNum, char* ds50UTCStr, int revNum, double* pos, double* vel, char* orbEltType)
{
   fprintf(fp, " %5d %15s  %5d%46s%3s Z\n", satNum, ds50UTCStr, revNum, " ", orbEltType);
   fprintf(fp, " %21.14E %21.14E %21.14E %8s%3s Z\n", pos[0], pos[1], pos[2], " ", orbEltType);
   fprintf(fp, " %21.14E %21.14E %21.14E %8s%3s Z\n", vel[0], vel[1], vel[2], " ", orbEltType);
}
