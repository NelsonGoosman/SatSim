/*
Purpose:
   This program is to convert osculating state vectors to SGP4 mean Keplerian elements and then
   to TLEs

   The program reads in user specified file which stores data in this format:
   yyDDD.dddddddd X Y Z XDot YDot ZDot

   and then convert these osculating vectors in the file to SGP4/TLEs and store these TLEs in 
   the output file
      

Usage: Command line format
   OscVecToTLE inFile outFile
   inFile   : File contains TLEs
   outFile  : Base name for five output files

Note:
   To see this program correctly in Visual Studio set the tab size to 3 and check 
   insert spaces in Tools/Options/Tabs

Input file format
   YY  DDD.dddddddddd   X                 Y                  Z         XDot                 YDot                ZDot
   11  181.9041666666   -41941.78440      4382.32521         0.51060   -0.32335347          -3.08741884         0.00012461

*/


#include <stdio.h>
#include <math.h>
#include "xyz2sgp4.h"

// Compiler directive that allows C++ code to use the C header files
// Begin



int main(int argc, char* argv[])
{
   FILE* fpOscState;	   // Osculating state vector
   FILE* fpTLE;	   // Osculating Keplerian elements

   char  inFile[100], outFile[100];
   char  sgp4DllInfo[INFOSTRLEN];

   char  line1[INPUTCARDLEN];
   char  line2[INPUTCARDLEN];


   double pos[3], posNew[3];
   double vel[3], velNew[3];
   double kozaiN, ecc, incl, node, MA, omega, ndot, bstar;

   double deltaPosX, deltaPosY, deltaPosZ, deltaVelX, deltaVelY, deltaVelZ;
   double deltaPos, deltaVel;
   double deltaPos1, deltaVel1;

   int yr;
   double day;


   printf("Program starts.\n");

   // This program is getting input parameters from the command line.
   // Follow the instruction to pass parameters in the right order.
   if (argc >= 3)
   {
      
		strcpy(inFile , argv[1] );
      strcpy(outFile, argv[2] );
      printf("Input file  = %s\n", inFile);
      printf("Output file = %s\n", outFile);
	}
	else 
   {
      printf("Error in number of parameters passed. Please see the usage.\n\n\n");
      printf("Usage    : OscVecToTLE inFile outFile\n\n");
      printf("inFile   : Input file containing osculating vector\n");
      printf("outFile  : Output file containing converted TLEs\n");
      exit(1);
   }
   
   // Load all the dlls being used in the program
   // Remember to specify the correct path to the Astro Standards dlls including the forward/backward slash at the end
   LoadAstroStdDlls();

   // Get information about the current DLL
   Sgp4GetInfo(sgp4DllInfo);
   sgp4DllInfo[INFOSTRLEN - 1] = 0;
   printf("\n\n%s\n\n", sgp4DllInfo);


   // Open input file 
   fpOscState = FileOpen(inFile, "rt");

   // Open output file
   fpTLE = FileOpen(outFile, "wt");


   // Read the input file for osculating vectors
   while (!feof(fpOscState))
   {
      // Read yy DDD.dddddddd X Y Z XDot YDot ZDot
	   fscanf(fpOscState, "%2d%lf %lf %lf %lf %lf %lf %lf\n", &yr, &day, &pos[0], &pos[1], &pos[2], &vel[0], &vel[1], &vel[2]);
      fprintf(fpTLE, "%2d%.10f %14.5f %14.5f %14.5f %14.8f %14.8f %14.8f\n", yr, day, pos[0], pos[1], pos[2], vel[0], vel[1], vel[2]);

      xyz2sgp4(yr, day, pos, vel, &kozaiN, &ecc, &incl, &node, &MA, &omega, posNew, velNew);

      // compute initial drag
      GetInitialDrag(NToA(kozaiN), ecc, &ndot, &bstar);


      // GP TLE - ephemeris type 0. Need to convert to Kozai mean motion
      TleGPFieldsToLines(99999, 'U', "MySat", yr, day, ndot, 0.0, bstar, 0, 0, incl, node,
                         ecc, omega, MA, kozaiN, 0, line1, line2);


      line1[80] = 0;
      line2[80] = 0;

      fprintf(fpTLE, "%2d%.10f %14.5f %14.5f %14.5f %14.8f %14.8f %14.8f\n",  yr, day, posNew[0], posNew[1], posNew[2], velNew[0], velNew[1], velNew[2]);
      fprintf(fpTLE, "%s\n%s\n", line1, line2);
      

	  // Compute deltas
	  deltaPos = sqrt(pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2]) - sqrt(posNew[0]*posNew[0] + posNew[1]*posNew[1] + posNew[2]*posNew[2]);	
	  deltaVel = sqrt(vel[0]*vel[0] + vel[1]*vel[1] + vel[2]*vel[2]) - sqrt(velNew[0]*velNew[0] + velNew[1]*velNew[1] + velNew[2]*velNew[2]);

	  // Compute deltas on each component
	  deltaPosX = pos[0] - posNew[0];
	  deltaPosY = pos[1] - posNew[1];
	  deltaPosZ = pos[2] - posNew[2];

	  deltaVelX = vel[0] - velNew[0];
	  deltaVelY = vel[1] - velNew[1];
	  deltaVelZ = vel[2] - velNew[2];

	  deltaPos1 = sqrt((deltaPosX * deltaPosX) + (deltaPosY * deltaPosY) +(deltaPosZ * deltaPosZ));
	  deltaVel1 = sqrt((deltaVelX * deltaVelX) + (deltaVelY * deltaVelY) +(deltaVelZ * deltaVelZ));


     fprintf(fpTLE, "delta pos (m) = %E, delta vel (m/sec) = %E\n", deltaPos * 1000, deltaVel * 1000); 
	  fprintf(fpTLE, "delta pos (m) = %E, delta vel (m/sec) = %E\n", deltaPos1 * 1000, deltaVel1 * 1000); 
     fprintf(fpTLE, "\n");
   }


   // Close all output files
   fclose(fpOscState); 
   fclose(fpTLE);

   // Free loaded AstroStd dlls
   FreeAstroStdDlls();

   //Calculate the whole run time
   printf("\n\nProgram completed successfully.\n\n");

   exit(0);
}




