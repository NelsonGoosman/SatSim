// This wrapper file was generated automatically by the GenDllWrappers program.

#ifndef OBSOPSDLL_H
#define OBSOPSDLL_H

#include "../services/DllUtils.h"

// Provide the path to the dll/so/dylib
#if defined (_WIN32) || defined (__CYGWIN__)
  #define ObsOpsDll "ObsOps.dll"
#elif __APPLE__
  #define ObsOpsDll "libobsops.dylib"
#else
  #define ObsOpsDll "libobsops.so"
#endif


// Notes: This function has been deprecated since v9.0.    
// Initializes ObsOps DLL for use in the program
// apAddr             The handle that was returned from DllMainInit() (in-Long)
// returns 0 if ObsOps.dll is initialized successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrObsOpsInit)(__int64 apAddr);


// Returns information about the current version of ObsOps DLL. 
// The information is placed in the string parameter passed in.
// infoStr            A string to hold the information about ObsOps.dll (out-Character[128])
typedef void (STDCALL *fnPtrObsOpsGetInfo)(char infoStr[128]);


// Loads Iomod parameters from an input text file
// iomodInputFile     The name of the file containing IOMOD-related parameters (in-Character[512])
// returns 0 if the input file is read successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrIomodLoadFile)(char iomodInputFile[512]);


// Loads Iomod control parameters and all Iomod related data (environment, time, sensors, obs) from an input text file
// iomodInputFile     The name of the file containing Iomod control parameters and all Iomod related data (in-Character[512])
// returns 0 if the input file is read successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrIomodLoadFileAll)(char iomodInputFile[512]);


// Saves any currently loaded IOMOD-related settings to a file
// iomodFile          The name of the file in which to save the settings (in-Character[512])
// saveMode           Specifies whether to create a new file or append to an existing one (0 = create, 1= append) (in-Integer)
// saveForm           Specifies the mode in which to save the file (0 = text format, 1 = not yet implemented, reserved for future) (in-Integer)
// returns 0 if the data is successfully saved to the file, non-0 if there is an error
typedef int (STDCALL *fnPtrIomodSaveFile)(char iomodFile[512], int saveMode, int saveForm);


// Builds and returns the IOMOD-parameter card (IP-Card) from the current IOMOD settings
// iomodIPCard        the resulting IOMOD IP card (out-Character[512])
typedef void (STDCALL *fnPtrIomodGetIpCard)(char iomodIPCard[512]);


// Retrieves all IOMOD parameters with a single function call
// printIOHG          control flag for IOHG advisory prints: 0=do not print IOHG information, 1=print IOHG (out-Integer)
// useFirst3Obs       use first 3 obs flag (out-Integer)
// satNum             satelite number (out-Integer)
// sortOrder          obs sorting order (out-Integer)
// satName            international designator (out-Character[8])
// runDC              run DC flag: 1=yes, 0=no (out-Integer)
// runRotas           run ROTAS flag: 1=yes, 0=no (out-Integer)
// extArr             the extra array (future use) (out-Double[128])
typedef void (STDCALL *fnPtrIomodGetIpAll)(int* printIOHG, int* useFirst3Obs, int* satNum, int* sortOrder, char satName[8], int* runDC, int* runRotas, double extArr[128]);


// Sets all IOMOD parameters with a single function call
// printIOHG          control flag for IOHG advisory prints: 0=do not print IOHG information, 1=print IOHG (in-Integer)
// useFirst3Obs       use first 3 obs flag (in-Integer)
// satNum             satelite number (in-Integer)
// sortOrder          obs sorting order (in-Integer)
// satName            international designator (in-Character[8])
// runDC              run DC flag: 1=yes, 0=no (in-Integer)
// runRotas           run ROTAS flag: 1=yes, 0=no (in-Integer)
// extArr             the extra array (future use) (in-Double[128])
typedef void (STDCALL *fnPtrIomodSetIpAll)(int printIOHG, int useFirst3Obs, int satNum, int sortOrder, char satName[8], int runDC, int runRotas, double extArr[128]);


// Retrieves the value of a specified IOMOD parameter
// 
// The table below indicates which index values for the xf_IP parameter:
// 
// table
// 
// xf_IP named constants/values
// Interpretation
// 
// XF_IP_PRINTIOHG  = 1control flag for IOHG advisory prints: 0=do not print IOHG information, 1=print
// IOHG
// XF_IP_USE1ST3OBS = 2use first 3 obs flag
// XF_IP_SATNUM     = 3satelite number
// XF_IP_SORTORDER  = 4obs sorting order
// XF_IP_SATNAME    = 5international designator 
// XF_IP_RUNDC      = 6run DC flag: 1=yes, 0=no [deprecated]
// XF_IP_RUNROTAS   = 7run ROTAS flag: 1=yes, 0=no [deprecated]
// 
// xf_IP              Predefined number specifying which IOMOD parameter to retrieve (in-Integer)
// retVal             A string to hold the value of the requested IOMOD parameter (out-Character[512])
typedef void (STDCALL *fnPtrIomodGetIpField)(int xf_IP, char retVal[512]);


// Sets the value of a specified IOMOD parameter
// See IomodGetIpField for a description of the xf_IP parameter.
// xf_IP              Predefined number specifying which IOMOD parameter to set (see XF_IP_?) (in-Integer)
// valueStr           The new value of the specified field, expressed as a string (in-Character[512])
typedef void (STDCALL *fnPtrIomodSetIpField)(int xf_IP, char valueStr[512]);


// Computes initial orbit vector from many observations using Herrick-Gibbs method
// obsKeyArr          the obsKey array contains obsKeys that are available for IOMOD (in-Long[*])
// arrSize            the size of the obsKeyArr (in-Integer)
// timeDs50UTC        the resulting time of the new vector in ds50UTC (out-Double)
// pos                the resulting position vector (km) (out-Double[3])
// vel                the resulting velocity vector (km/s) (out-Double[3])
// arr3ObsKeys        the resulting 3 obsKeys that were auto-selected by IOMOD (out-Long[3])
// returns 0 if the computation is successful, non-0 if there is an error
typedef int (STDCALL *fnPtrManyObsToPosVel)(__int64 obsKeyArr[], int arrSize, double* timeDs50UTC, double pos[3], double vel[3], __int64 arr3ObsKeys[3]);


// Computes initial orbit vector from three selected observations using Herrick-Gibbs method
// arr3ObsKeys        the three input obsKeys (in-Long[3])
// timeDs50UTC        the resulting time of the new vector in ds50UTC (out-Double)
// pos                the resulting position vector (km) (out-Double[3])
// vel                the resulting velocity vector (km/s) (out-Double[3])
// returns 0 if the computation is successful, non-0 if there is an error
typedef int (STDCALL *fnPtrThreeObsToPosVel)(__int64 arr3ObsKeys[3], double* timeDs50UTC, double pos[3], double vel[3]);


// Computes initial orbit vector directly from the input sensor/observation data - thread safe
// xa_senLoc          array contains sensor location data (see XA_SENLOC_?) (in-Double[16])
// numObs             number of input obs in xa_obsArr (in-Integer)
// xa_obsArr          array of input obs (see XA_OBS_?) (in-Double[*, 64])
// timeDs50UTC        the resulting time of the new vector in ds50UTC (out-Double)
// pos                the resulting position vector (km) (out-Double[3])
// vel                the resulting velocity vector (km/s) (out-Double[3])
// returns 0 if the computation is successful, non-0 if there is an error
typedef int (STDCALL *fnPtrIomod_OS)(double xa_senLoc[16], int numObs, double xa_obsArr[][64], double* timeDs50UTC, double pos[3], double vel[3]);


// Computes initial orbit vector from two selected observations using Two-Ob method
// Note: Two-Ob method only works with ob types: 2, 3, 4, P, and V
// arr2ObsKeys        the two input obsKeys (in-Long[2])
// timeDs50UTC        the resulting time of the new vector in ds50UTC (out-Double)
// pos                the resulting position vector (km) (out-Double[3])
// vel                the resulting velocity vector (km/s) (out-Double[3])
// returns 0 if the computation is successful, non-0 if there is an error
typedef int (STDCALL *fnPtrTwoObsToPosVel)(__int64 arr2ObsKeys[2], double* timeDs50UTC, double pos[3], double vel[3]);


// Computes the initial orbit vector from three selected angle-only observations using the Gooding Algorithm.
// arr3ObsKeys        the three input obsKeys (in-Long[3])
// range1             the range guess to first observation (km) (in-Double)
// range3             the range guess to third observation (km) (in-Double)
// nhrev              number of half revolutions (in-Integer)
// ind                solution number (in-Integer)
// maxIt              maximum number of iterations (in-Integer)
// pdInc              partial derivative increment (in-Double)
// criVal             convergence criterion (in-Double)
// timeDs50UTC        the resulting time of the new vector in ds50UTC (out-Double)
// pos                the resulting position vector (km) (out-Double[3])
// vel                the resulting velocity vector (km/s) (out-Double[3])
// returns 0 if the computation is successful, non-0 if there is an error
typedef int (STDCALL *fnPtrAnglesOnlyToPosVel)(__int64 arr3ObsKeys[3], double range1, double range3, int nhrev, int ind, int maxIt, double pdInc, double criVal, double* timeDs50UTC, double pos[3], double vel[3]);


// Computes the track length of a track whose first observation started at the input startIdx.
// This routine can be used in a loop to find all the tracks in the observation list.
// Remember to sort obs in the obsKeyArr in the ascending order of sensor, satno, obsType, time, elev 
// by calling ObsGetLoaded(-6, pObsKeys) before feeding the array to this routine
// obsKeyArr          the input obsKeyArr (in-Long[*])
// arrSize            the size of the obsKeyArr (number of obs) (in-Integer)
// startIdx           the index of the first observation to start computing the track length (in-Integer)
// trackLength        the track length (trackLength = 1 for single obs) (out-Integer)
// returns 0 if the computation is successful, non-0 if there is an error
typedef int (STDCALL *fnPtrFindTrack)(__int64 obsKeyArr[], int arrSize, int startIdx, int* trackLength);


// Computes initial orbit vector from a track of obs. Also returns the three obs in the track that are used by IOMOD
// obsKeys            the input obsKeyArr (in-Long[*])
// trackStartIdx      the index of the first observation that starts the track (in-Integer)
// trackLength        the track length (in-Integer)
// timeDs50UTC        the resulting time of the new vector in ds50UTC (out-Double)
// pos                the resulting position vector (km) (out-Double[3])
// vel                the resulting velocity vector (km/s) (out-Double[3])
// trackObsKeys       obsKeys of the tree obs that are used by IOMOD (out-Long[3])
// returns 0 if the computation is successful, non-0 if there is an error
typedef int (STDCALL *fnPtrATrackToPosVel)(__int64 obsKeys[], int trackStartIdx, int trackLength, double* timeDs50UTC, double pos[3], double vel[3], __int64 trackObsKeys[3]);


// Returns the default values of the triangulation settings
// xa_tri             triangulation parameters (see XA_TRI_?) (out-Double[32])
typedef void (STDCALL *fnPtrTriGetDefParams)(double xa_tri[32]);


// Triangulates the input obs and write generated obs with range data to the specified output file
// obsKeyArr          the input obsKeyArr contains obsKeys that are available for triangulation (in-Long[*])
// arrSize            the size of the obsKeyArr (number of obs) (in-Integer)
// xa_tri             triangulation parameters (see XA_TRI_?) (in-Double[32])
// toFile             output file that stores the generated obs with the computed range data (in-Character[512])
// returns 0 if successful, non-0 if there is an error
typedef int (STDCALL *fnPtrTriComputeToFile)(__int64 obsKeyArr[], int arrSize, double xa_tri[32], char toFile[512]);


// Triangulates the input obs and returns the overlap and polyfit information; creates and loads obs with range data into memory and returns their associated obsKeys
// obsKeyArr          the input obsKeyArr contains obsKeys that are available for triangulation (in-Long[*])
// arrSize            the size of the obsKeyArr (number of obs) (in-Integer)
// xa_tri             triangulation parameters (see XA_TRI_?) (in-Double[32])
// numOvlps           number of overlap tracks (out-Integer)
// xa_ovlp            overlap data (see XA_OVLP_?) (out-Double[*, 8])
// numFits            number of qualified tracks for fitting (out-Integer)
// xa_fit             polyfit data (see XA_FIT_?) (out-Double[*, 32])
// maxGenObs          maximum number of generated obs (in-Integer)
// nGenObs            number of actual obs generated by triangulation process (nGenObs always lt or eq maxGenObs) (out-Integer)
// genObsKeys         generate obs with range, then load them into memory, and return the obsKeys of all generated obs (out-Long[*])
// returns 0 if successful, non-0 if there is an error
typedef int (STDCALL *fnPtrTriCompute1)(__int64 obsKeyArr[], int arrSize, double xa_tri[32], int* numOvlps, double xa_ovlp[][8], int* numFits, double xa_fit[][32], int maxGenObs, int* nGenObs, __int64 genObsKeys[]);


// Triangulates the input obs and returns the overlap and polyfit information 
// obsKeyArr          the input obsKeyArr contains obsKeys that are available for triangulation (in-Long[*])
// arrSize            the size of the obsKeyArr (number of obs) (in-Integer)
// xa_tri             triangulation parameters (see XA_TRI_?) (in-Double[32])
// numOvlps           number of overlap tracks (out-Integer)
// xa_ovlp            overlap data (see XA_OVLP_?) (out-Double[*, 8])
// numFits            number of qualified tracks for fitting (out-Integer)
// xa_fit             polyfit data (see XA_FIT_?) (out-Double[*, 32])
// returns 0 if successful, non-0 if there is an error
typedef int (STDCALL *fnPtrTriCompute2)(__int64 obsKeyArr[], int arrSize, double xa_tri[32], int* numOvlps, double xa_ovlp[][8], int* numFits, double xa_fit[][32]);


// Triangulates the input obs; creates and loads obs with range data (by triangulation) into memory and returns their associated obsKeys
// obsKeyArr          the input obsKeyArr contains obsKeys that are available for triangulation (in-Long[*])
// arrSize            the size of the obsKeyArr (number of obs) (in-Integer)
// xa_tri             triangulation parameters (see XA_TRI_?) (in-Double[32])
// maxGenObs          maximum number of generated obs (in-Integer)
// nGenObs            number of actual obs generated by triangulation process (nGenObs always lt or eq maxGenObs) (out-Integer)
// genObsKeys         generate obs with range, then load them into memory, and return the obsKeys of all generated obs (out-Long[*])
// returns 0 if successful, non-0 if there is an error
typedef int (STDCALL *fnPtrTriCompute3)(__int64 obsKeyArr[], int arrSize, double xa_tri[32], int maxGenObs, int* nGenObs, __int64 genObsKeys[]);


// Returns the default values of the waterfall altitude (km)
// returns The default altitude (km) being used in the Waterfall algorithm
typedef double (STDCALL *fnPtrGetWaterfallAlt)();


// Converts angle-only observation to lat/lon/height positions
// obsKey             The unique key of the angle-only observation that needs to be converted by the waterfall calculation (in-Long)
// assumedAltitude    The input assumed altitude (km) to calculate LLH (set to 0 to indicate default altitude should be used) (in-Double)
// rho                The ouput calculated range to sphere of assumed altitude (out-Double[2])
// llhs               The calculated LLH at sphere of assumed altitude (out-Double[2, 3])
// numSols            Number of Waterfall Solutions (out-Integer)
// returns Returns 0 if the conversion is successful, non-0 if there is an error
typedef int (STDCALL *fnPtrAnglesOnlyToLLH)(__int64 obsKey, double assumedAltitude, double rho[2], double llhs[2][3], int* numSols);


// Calculates length of output arrays for Lomb
// Used to allocated px, py, prob before call to Lomb
// ofac               Oversample factor, typical value is "4" or "5" (in-Double)
// hifac              Ratio of highest frequency to Nyquist frequency (in-Double)
// nSample            Number of samples for x and y (in-Integer)
// returns Used to allocated px, py, prob before call to Lomb
typedef int (STDCALL *fnPtrLombLengthOut)(double ofac, double hifac, int nSample);


// Creates Lomb-Scargle periodogram.  Reference: Numerical Recipes   
// Used to find frequencies in unevenly sampled data, such as Visual Magnitude vs. Time
// x                  array times to input (units don't matter, can be days, seconds, etc...), length of nSample (in-Double[*])
// y                  array of data (such as Visual Magnitude) associated with times to input, length of nSample (in-Double[*])
// nSample            Number of samples for x and y (in-Integer)
// ofac               Oversample factor, typical value is "4" or "5" (in-Double)
// hifac              Ratio of highest frequency to Nyquist frequency (in-Double)
// px                 array of frequencies, should be of length (0.5d0*ofac*hifac*nSample) (out-Double[*])
// py                 array of powers associated with frequencies, should be of length (0.5d0*ofac*hifac*nSample) (out-Double[*])
// prob               array of false alarm probabilities corresponding to py, should be of length (0.5d0*ofac*hifac*nSample) (out-Double[*])
// pxmax              most powerful frequency (out-Double)
// pymax              power of most powerful frequency (out-Double)
// probMax            false alarm probability of most powerful frequency (out-Double)
typedef void (STDCALL *fnPtrLomb)(double x[], double y[], int nSample, double ofac, double hifac, double px[], double py[], double prob[], double* pxmax, double* pymax, double* probMax);


// Find False Alarm Probablility of given Power (lower is less likely to be a false alarm)
// py                 Power (in-Double)
// nout               Number of output frequencies (0.5*ofac*hifac*n) (in-Integer)
// ofac               oversample factor (in-Double)
// returns False Alarm Probability
typedef double (STDCALL *fnPtrLombFalseProb)(double py, int nout, double ofac);


// Find Power of given False Alarm Probablility
// prob               False Alarm Probability (in-Double)
// nout               Number of output frequencies (0.5*ofac*hifac*n) (in-Integer)
// ofac               oversample factor (in-Double)
// returns Power
typedef double (STDCALL *fnPtrLombFalseProbInv)(double prob, int nout, double ofac);


// Calculate length of output for LombWaveFit
// nFreq              Number of frequencies of interest (in-Integer)
// returns Returned number of coefficients to use in LombWaveFit and LombCalcValueFromTime, use to allocate coeffs
typedef int (STDCALL *fnPtrLombLengthCoef)(int nFreq);


// Fits user defined frequencies to data to find the magnitudes
// Solves the equation
// y= C + sum( A(i)*sin(2*pi*freq(i)*t) + B(i)*sin(2*pi*freq(i)*t)  )
// For coefficients A and B corresponding to each frequency
// x                  Times, length of nSamples (in-Double[*])
// y                  Data, length of nSamples (in-Double[*])
// nSamples           Number of input samples, length of x and y (in-Integer)
// freq               set of frequencies to fit, should not be same as output of Lomb, lenth of nfreq (in-Double[*])
// nfreq              number of frequencies, length of freq (in-Integer)
// coeffs             resulting coefficients(A(1) B(1) ... A(nfreq) B(nfreq) C), will have length(2*nfreq+1) (out-Double[*])
typedef void (STDCALL *fnPtrLombWaveFit)(double x[], double y[], int nSamples, double freq[], int nfreq, double coeffs[]);


// Calculate value of y given time, x, 
// and frequencies and magnitudes that were gotten from wavefit
// solves the equation
// y= C + sum( A(i)*sin(2*pi*freq(i)*t) + B(i)*sin(2*pi*freq(i)*t)  )
// for y
// x                  Time (in-Double)
// mags               Magnitudes from wavefit, length of (2*nfreq+1) (in-Double[*])
// freq               frequencies of interest, length of nfreq (in-Double[*])
// nfreq              Number of frequencies of interest (in-Integer)
// returns resulting y value
typedef double (STDCALL *fnPtrLombCalcValueFromTime)(double x, double mags[], double freq[], int nfreq);


// Given two observations, calculate the angle between them
// Supports obsType 1,2,3,4,5,8,9,18,19
// obsKey1            1st obsKey (in-Long)
// obsKey2            2nd obsKey (in-Long)
// angSep             Angular Separation(Deg) (out-Double)
// errCode            Error Code, 1 - Obs times not equal (will still do calculation), 2 - Calculation errored out, sensor numbers are different, or unsupported obs type (out-Integer)
typedef void (STDCALL *fnPtrAngleBetweenObs)(__int64 obsKey1, __int64 obsKey2, double* angSep, int* errCode);


// Combines the TwoObs/ThreeObs/ManyObs methods into one while returning intermediate data of the Iomod iterations
// obsKeyArr          the obsKey array contains obsKeys that are available for IOMOD (in-Long[*])
// arrSize            the size of the obsKeyArr (2, 3, or more) (in-Integer)
// xa_iomod           array containing settings for the IOMOD run (unused for now) (in-Double[64])
// timeDs50UTC        the resulting time of the new vector in ds50UTC (out-Double)
// pos                the resulting position vector (km) (out-Double[3])
// vel                the resulting velocity vector (km/s) (out-Double[3])
// arr3ObsKeys        the resulting 3 obsKeys that were auto-selected by IOMOD (if more than 3 obs provided) (out-Long[3])
// numIters           the number of iterations that Iomod took (out-Integer)
// xa_iomIter         Iomod iteration data (see XA_IOMITER_?) (out-Double[25, 8])
// arr3Pos            the three computed position vectors from the selected obs (out-Double[3, 3])
// returns 0 if the computation is successful, non-0 if there is an error
typedef int (STDCALL *fnPtrIomodCombine)(__int64 obsKeyArr[], int arrSize, double xa_iomod[64], double* timeDs50UTC, double pos[3], double vel[3], __int64 arr3ObsKeys[3], int* numIters, double xa_iomIter[25][8], double arr3Pos[3][3]);
  
  // Different obs selection options 
  static const int  
     OBSSELMODE_AUTO   = 0,    // auto select 3 obs among the loaded/selected obs
     OBSSELMODE_1ST3OBS= 1;    // use the first 3 obs in list of loaded/selected obs
  
  
  // Indexes for accessing Iomod control parameters
  static const int  
     XF_IP_PRINTIOHG  = 1,     // control flag for IOHG advisory prints: 0=do not print IOHG information, 1=print IOHG
     XF_IP_USE1ST3OBS = 2,     // use first 3 obs flag
     XF_IP_SATNUM     = 3,     // satelite number
     XF_IP_SORTORDER  = 4,     // obs sorting order
     XF_IP_SATNAME    = 5,     // international designator 
     XF_IP_RUNDC      = 6,     // run DC flag: 1=yes, 0=no
     XF_IP_RUNROTAS   = 7;     // run ROTAS flag: 1=yes, 0=no
     
  // Indexes of TRI configuration parameters
  static const int  
     XA_TRI_USEDEFAULT       =  0,    // I - Flag to specify whether or not to use triangulation's default parameters: =[1]: use them and ignore the rest, =0: not to use them
     XA_TRI_OBSTYPEOUT       =  1,    // I - Output obs type (valid values are 0, 2, 3, 4, 6, 8 and 9)
     XA_TRI_APPLYBIAS        =  2,    // I - Flag to specify whether or not to apply sensor bias: =[1]: apply bias, =0: not apply bias
     XA_TRI_LTC              =  3,    // I - apply light time correction (applyLTC) flag: 0=do no apply LTC, [1]=apply LTC 
     XA_TRI_CREATEOBSSIZE    =  4,    // I - number of obs created for each overlap track
     XA_TRI_DEFANGLEORDER    =  5,    // I - default order of the Polyfit for angle RA/DEC
     XA_TRI_DEFRANGEORDER    =  6,    // I - default order of the Polyfit for range
     XA_TRI_DEFEFGORDER      =  7,    // I - default order of the Polyfit for EFG components
     XA_TRI_AUTOFITANGLE     =  8,    // I - whether or not to use auto mode for angle (increase order if needed when doing Polyfit)
     XA_TRI_AUTOFITRANGE     =  9,    // I - whether or not to use auto for range (increase order if needed when doing Polyfit)
     XA_TRI_ANCHORRADEC      = 10,    // I - anchor order of RA/DEC  
     XA_TRI_SEPSATNO         = 11,    // I - check to see satellite number is different
     XA_TRI_RARMSLIM         = 12,    // D - limit RMS for RA (arcsec)
     XA_TRI_DECRMSLIM        = 13,    // D - limit RMS for Dec (arcsec)
     XA_TRI_RANGERMSLIM      = 14,    // D - limit RMS for Range (km)
     XA_TRI_TRKSEPARATION    = 15,    // D - track separation criteria (minutes)
     XA_TRI_MINSTEREOANGLE   = 16,    // D - minimum stereoscopic angle (deg)
                                      
     XA_TRI_SIZE             = 32;   
  
  // Indexes of overlap track data 
  static const int  
     XA_OVLP_SATNUM       =  0,       // I - Satellite number
     XA_OVLP_SENNUM1      =  1,       // I - Sensor number of track 1
     XA_OVLP_SENNUM2      =  2,       // I - Sensor number of track 2
     XA_OVLP_STARTTIME    =  3,       // D - Overlap track's start time (in DS50UTC)
     XA_OVLP_ENDTIME      =  4,       // D - Overlap track's end time (in DS50UTC)
     
     XA_OVLP_SIZE         =  8;       //
     
  // Indexes of polyfitting track data
  static const int  
     XA_FIT_SATNUM        =  0,       // I - Satellite number
     XA_FIT_SENNUM1       =  1,       // I - Sensor number of track 1
     XA_FIT_SENNUM2       =  2,       // I - Sensor number of track 2
     
     XA_FIT_RAORDER1      =  3,       // I - Right ascension polyfit order of track 1
     XA_FIT_RAORDER2      =  4,       // I - Right ascension polyfit order of track 2
     XA_FIT_RARMS1        =  5,       // D - Right ascension RMS of track 1
     XA_FIT_RARMS2        =  6,       // D - Right ascension RMS of track 2
     
     XA_FIT_DECORDER1     =  7,       // I - Declination polyfit order of track 1
     XA_FIT_DECORDER2     =  8,       // I - Declination polyfit order of track 2
     XA_FIT_DECMS1        =  9,       // D - Declination RMS of track 1
     XA_FIT_DECRMS2       = 10,       // D - Declination RMS of track 2
     
     XA_FIT_RANGEORDER1   = 11,       // I - Declination polyfit order of track 1
     XA_FIT_RANGEORDER2   = 12,       // I - Declination polyfit order of track 2
     XA_FIT_RANGERMS1     = 13,       // D - Declination RMS of track 1
     XA_FIT_RANGERMS2     = 14,       // D - Declination RMS of track 2
     
     XA_FIT_THETA1        = 15,       // D - First stereoscopic angle (deg)
     XA_FIT_THETA2        = 16,       // D - Second stereoscopic angle (deg)
     XA_FIT_THETA3        = 17,       // D - Third stereoscopic angle (deg)
     
     XA_FIT_SIZE          =  32;       //
  
  // Iomod iteration data
  static const int     
     XA_IOMITER_RNG1 = 0,   // Computed estimated range for ob# 1
     XA_IOMITER_RNG2 = 1,   // Computed estimated range for ob# 2
     XA_IOMITER_RNG3 = 2,   // Computed estimated range for ob# 3
     XA_IOMITER_CONV = 3,   // Convergence value
     
     XA_IOMITER_SIZE = 8;
     
  // Iomod maximum number of iterations
  static const int IOMOD_MAXITERS = 25;
     
// ObsOpsDll's function pointers declaration
extern fnPtrObsOpsInit                     ObsOpsInit;
extern fnPtrObsOpsGetInfo                  ObsOpsGetInfo;
extern fnPtrIomodLoadFile                  IomodLoadFile;
extern fnPtrIomodLoadFileAll               IomodLoadFileAll;
extern fnPtrIomodSaveFile                  IomodSaveFile;
extern fnPtrIomodGetIpCard                 IomodGetIpCard;
extern fnPtrIomodGetIpAll                  IomodGetIpAll;
extern fnPtrIomodSetIpAll                  IomodSetIpAll;
extern fnPtrIomodGetIpField                IomodGetIpField;
extern fnPtrIomodSetIpField                IomodSetIpField;
extern fnPtrManyObsToPosVel                ManyObsToPosVel;
extern fnPtrThreeObsToPosVel               ThreeObsToPosVel;
extern fnPtrIomod_OS                       Iomod_OS;
extern fnPtrTwoObsToPosVel                 TwoObsToPosVel;
extern fnPtrAnglesOnlyToPosVel             AnglesOnlyToPosVel;
extern fnPtrFindTrack                      FindTrack;
extern fnPtrATrackToPosVel                 ATrackToPosVel;
extern fnPtrTriGetDefParams                TriGetDefParams;
extern fnPtrTriComputeToFile               TriComputeToFile;
extern fnPtrTriCompute1                    TriCompute1;
extern fnPtrTriCompute2                    TriCompute2;
extern fnPtrTriCompute3                    TriCompute3;
extern fnPtrGetWaterfallAlt                GetWaterfallAlt;
extern fnPtrAnglesOnlyToLLH                AnglesOnlyToLLH;
extern fnPtrLombLengthOut                  LombLengthOut;
extern fnPtrLomb                           Lomb;
extern fnPtrLombFalseProb                  LombFalseProb;
extern fnPtrLombFalseProbInv               LombFalseProbInv;
extern fnPtrLombLengthCoef                 LombLengthCoef;
extern fnPtrLombWaveFit                    LombWaveFit;
extern fnPtrLombCalcValueFromTime          LombCalcValueFromTime;
extern fnPtrAngleBetweenObs                AngleBetweenObs;
extern fnPtrIomodCombine                   IomodCombine;



void LoadObsOpsDll();
void FreeObsOpsDll();




#endif
// ========================= End of auto generated code ==========================
