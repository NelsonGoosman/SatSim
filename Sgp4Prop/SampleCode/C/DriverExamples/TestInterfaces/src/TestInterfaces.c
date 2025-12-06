/*
   Purpose:
      This program shows how a C program can call the Astrodynamic Standard Dlls with all data types
	  
   Author:
      HQ AFSPC/A2/3/6Z
*/


#include <stdio.h>
#include <stdint.h>
#include <math.h>    


// Compiler directive that allows C++ code to use the C header files
// Begin
#ifdef __cplusplus
extern "C" 
{
#endif

#include "../../services/DllMainDll_Service.h" 
#include "../../wrappers/DllMainDll.h"

// End
#ifdef __cplusplus
}
#endif


// Function prototypes
void  LoadAstroStdDlls();
void  FreeAstroStdDlls();


int main(int argc, char* argv[])
{
   // Arrays that store propagation data
   double pos[3];   // Position (km) in TEME of Epoch
   double vel[3];   // Velocity (km/s) in TEME of Epoch
   double llh[3];   // Latitude(deg), Longitude(deg), Height above Geoid (km)

   // Load all the dlls being used in the program from the specified path (PATH env on Windows or LD_LIBRARY_PATH on Linux)
   LoadAstroStdDlls();
   
 // TestInterface variables 
   char cIn = 'Z', cOut; 
   int32_t intIn = 123, intOut; 
   __int64 longIn = 1234567890123456789LL, longOut; 
   double realIn = 123.45, realOut; 
   char strIn[GETSETSTRLEN] = {'A','s','t','r','o',' ','C','\0'}, strOut[GETSETSTRLEN] = {0}; 
   int int1DIn[3] = {1, 2, 3}, int1DOut[3]; 
   __int64 long1DIn[3] = {1234567890123456789LL, 2LL, 3LL}, long1DOut[3]; 
   double real1DIn[3] = {1.1, 2.2, 3.3}, real1DOut[3]; 
   int int2DIn[2][3] = {{1, 2, 3}, {4, 5, 6}}, int2DOut[2][3]; 
   __int64 long2DIn[2][3] = {{1234567890123456789LL, 2LL, 3LL}, {4LL, 5LL, 6LL}}, long2DOut[2][3]; 
   double real2DIn[2][3] = {{1.1, 2.2, 3.3}, {4.4, 5.5, 6.6}}, real2DOut[2][3]; 
      
   TestInterface(cIn, &cOut, intIn, &intOut, longIn, &longOut, realIn, &realOut, strIn, strOut, int1DIn, int1DOut, long1DIn, long1DOut, real1DIn, real1DOut, int2DIn, int2DOut, long2DIn, long2DOut, real2DIn, real2DOut);   
   
   strOut[sizeof(strOut)-1] = 0;
   
   printf("Testing TestInterface\n");
   printf("cOut = %c\n", cOut); 
   printf("intOut = %d\n", intOut); 
   printf("longOut = %lld\n", longOut); 
   printf("realOut = %.2f\n", realOut); 
   printf("strOut = %s\n", strOut); 
   printf("int1DOut = %d, %d, %d\n", int1DOut[0], int1DOut[1], int1DOut[2]); 
   printf("long1DOut = %lld, %lld, %lld\n", long1DOut[0], long1DOut[1], long1DOut[2]); 
   printf("real1DOut = %.1f, %.1f, %.1f\n", real1DOut[0], real1DOut[1], real1DOut[2]); 
   printf("int2DOut(1,:) = %d, %d, %d\n", int2DOut[0][0], int2DOut[0][1], int2DOut[0][2]); 
   printf("int2DOut(2,:) = %d, %d, %d\n", int2DOut[1][0], int2DOut[1][1], int2DOut[1][2]); 
   printf("long2DOut(1,:) = %lld, %lld, %lld\n", long2DOut[0][0], long2DOut[0][1], long2DOut[0][2]); 
   printf("long2DOut(2,:) = %lld, %lld, %lld\n", long2DOut[1][0], long2DOut[1][1], long2DOut[1][2]); 
   printf("real2DOut(1,:) = %.1f, %.1f, %.1f\n", real2DOut[0][0], real2DOut[0][1], real2DOut[0][2]); 
   printf("real2DOut(2,:) = %.1f, %.1f, %.1f\n", real2DOut[1][0], real2DOut[1][1], real2DOut[1][2]);    
   printf("\n");
   
   
   // TestInterface2
   char cInOut = 'A'; 
   int intInOut = intIn; 
   __int64 longInOut = longIn; 
   double realInOut = realIn; 
   char strInOut[GETSETSTRLEN]; strcpy(strInOut, strIn); 
   int int1DInOut[3]; memcpy(int1DInOut, int1DIn, sizeof(int1DIn)); 
   __int64 long1DInOut[3]; memcpy(long1DInOut, long1DIn, sizeof(long1DIn)); 
   double real1DInOut[3]; memcpy(real1DInOut, real1DIn, sizeof(real1DIn)); 
   int int2DInOut[2][3]; memcpy(int2DInOut, int2DIn, sizeof(int2DIn)); 
   __int64 long2DInOut[2][3]; memcpy(long2DInOut, long2DIn, sizeof(long2DIn)); 
   double real2DInOut[2][3]; memcpy(real2DInOut, real2DIn, sizeof(real2DIn));
   
   TestInterface2(&cInOut, &intInOut, &longInOut, &realInOut, strInOut, int1DInOut, long1DInOut, real1DInOut, int2DInOut, long2DInOut, real2DInOut);   

   strInOut[sizeof(strInOut)-1] = 0;
   
   printf("Testing TestInterface2\n");
   printf("cInOut = %c\n", cInOut); 
   printf("intInOut = %d\n", intInOut); 
   printf("longInOut = %lld\n", longInOut); 
   printf("realInOut = %.2f\n", realInOut); 
   printf("strInOut = %s\n", strInOut); 
   printf("int1DInOut = %d, %d, %d\n", int1DInOut[0], int1DInOut[1], int1DInOut[2]); 
   printf("long1DInOut = %lld, %lld, %lld\n", long1DInOut[0], long1DInOut[1], long1DInOut[2]); 
   printf("real1DInOut = %.1f, %.1f, %.1f\n", real1DInOut[0], real1DInOut[1], real1DInOut[2]); 
   printf("int2DInOut(1,:) = %d, %d, %d\n", int2DInOut[0][0], int2DInOut[0][1], int2DInOut[0][2]); 
   printf("int2DInOut(2,:) = %d, %d, %d\n", int2DInOut[1][0], int2DInOut[1][1], int2DInOut[1][2]); 
   printf("long2DInOut(1,:) = %lld, %lld, %lld\n", long2DInOut[0][0], long2DInOut[0][1], long2DInOut[0][2]); 
   printf("long2DInOut(2,:) = %lld, %lld, %lld\n", long2DInOut[1][0], long2DInOut[1][1], long2DInOut[1][2]); 
   printf("real2DInOut(1,:) = %.1f, %.1f, %.1f\n", real2DInOut[0][0], real2DInOut[0][1], real2DInOut[0][2]); 
   printf("real2DInOut(2,:) = %.1f, %.1f, %.1f\n", real2DInOut[1][0], real2DInOut[1][1], real2DInOut[1][2]);    
   printf("\n");
   
   
 // TestInterface3 
    int size1D = 3, size2D = 2;
    int *Unk1DIn = (int *)malloc(size1D * sizeof(int32_t));
    int *Unk1DOut = (int *)malloc(size1D * sizeof(int32_t));
    int (*Unk2DIn)[3] = (int (*)[3])malloc(size1D * 3 * sizeof(int));
    int (*Unk2DOut)[3] = (int (*)[3])malloc(size1D * 3 * sizeof(int));

    memcpy(Unk1DIn, int1DIn, size1D * sizeof(int32_t));
    for (int i = 0; i < size2D; ++i) {
        for (int j = 0; j < 3; ++j) {
            Unk2DIn[i][j] = int2DIn[i][j];
        }
    }

    // Call the function
    TestInterface3(Unk1DIn, Unk1DOut, Unk2DIn, Unk2DOut);

    // Print the results
    printf("Testing TestInterface3\n");
    printf("Unk1DOut = ");
    for (int i = 0; i < size1D; ++i) {
        printf("%d ", Unk1DOut[i]);
    }
    printf("\n");

    for (int i = 0; i < size2D; ++i) {
        printf("Unk2DOut(%d,:) = ", i+1);
        for (int j = 0; j < 3; ++j) {  // Adjust for the correct number of columns
            printf("%d ", Unk2DOut[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    free(Unk1DIn);
    free(Unk1DOut);
    free(Unk2DIn);
    free(Unk2DOut);   

    FreeDllMainDll();
    FreeAstroStdDlls();
    exit(0);
}


// Load all the dlls being used in the program
void LoadAstroStdDlls()
{
   LoadDllMainDll();
}


// Free all the dlls being used in the program
void FreeAstroStdDlls()
{
   FreeDllMainDll();
}


