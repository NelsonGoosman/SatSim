#include "DllUtils.h"
#include "AstroFuncDll_Service.h"

#include "../wrappers/AstroFuncDll.h"
#include "../wrappers/TimeFuncDll.h"


// Compute LLH from position vector
double* PosToLLH(double ds50UT1, double* pos, fAddr envFkPtr)
{
   static double llh[3];
   double thetaG;

   // Reset LLH array to zeros
   memset(llh, 0, 3 * sizeof(double));

   thetaG = ThetaGrnwch(ds50UT1, envFkPtr);
   XYZToLLH(thetaG, pos, llh);

   return llh;
}


// Compute position XYZ from LLH
double* LLHToPos(double ds50UT1, double* llh, fAddr envFkPtr)
{
   static double pos[3];
   double thetaG;

   // Reset LLH array to zeros
   memset(pos, 0, 3 * sizeof(double));

   thetaG = ThetaGrnwch(ds50UT1, envFkPtr);
   LLHToXYZ(thetaG, llh, pos);

   return pos;
}
