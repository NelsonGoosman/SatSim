// This wrapper file was generated automatically by the GenDllWrappers program.

#ifndef EXTEPHEMDLL_H
#define EXTEPHEMDLL_H

#include "../services/DllUtils.h"

// Provide the path to the dll/so/dylib
#if defined (_WIN32) || defined (__CYGWIN__)
  #define ExtEphemDll "ExtEphem.dll"
#elif __APPLE__
  #define ExtEphemDll "libextephem.dylib"
#else
  #define ExtEphemDll "libextephem.so"
#endif


// Notes: This function has been deprecated since v9.0. 
// Initializes ExtEphem DLL for use in the program
// If this function returns an error, it is recommended that the users stop the program immediately. 
// The error occurs if the users forget to load and initialize all the prerequisite DLLs, as listed 
// in the DLL Prerequisite section, before using this DLL.
// apAddr             The handle that was returned from DllMainInit() (in-Long)
// returns 0 if ExtEphem DLL is initialized successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphInit)(__int64 apAddr);


// Returns information about the current version of ExtEphem DLL. 
// The information is placed in the string parameter passed in.
// The returned string provides information about the version number, build date, and the platform of the ExtEphem DLL. 
// infoStr            A string to hold the information about ExtEphem.dll (out-Character[128])
typedef void (STDCALL *fnPtrExtEphGetInfo)(char infoStr[128]);


// Loads a file containing EXTEPHEM's
// The users can use this function repeatedly to load EXTEPHEMs from different input files. 
// However, only unique satKeys are stored in the binary tree. Duplicated EXTEPHEMs 
// (determined by same file name, satellite number + epoch) won't be stored.
// 
// EXTEPHEMs can be included directly in the main input file or they can be read from a 
// separate file identified with "EPHFIL =[pathname\filename]".
// 
// This function only reads EXTEPHEMs from the main input file or EXTEPHEMs from the file 
// identified with EPHFIL in the input file. It won't read anything else.
// extEphFile         The name of the file containing external ephemeris data to be loaded (in-Character[512])
// returns 0 if the input file is read successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphLoadFile)(char extEphFile[512]);


// Saves the currently loaded EXTEPHEM's to a file (EPHFIL=input file name)
// extEphFile         The name of the file in which to save the settings (in-Character[512])
// saveMode           Specifies whether to create a new file or append to an existing one (0 = create, 1= append) (in-Integer)
// saveForm           Specifies the mode in which to save the file (0 = text format, 1 = not yet implemented, reserved for future) (in-Integer)
// returns 0 if the data is successfully saved to the file, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphSaveFile)(char extEphFile[512], int saveMode, int saveForm);


// Removes an EXTEPHEM represented by the satKey from memory
// If the users enter an invalid satKey (the satKey does not exist in memory), the function will return a non-zero value indicating an error.
// satKey             The unique key of the satellite to be removed (in-Long)
// returns 0 if the satellite is removed successfully, non-0 if there is an error.
typedef int (STDCALL *fnPtrExtEphRemoveSat)(__int64 satKey);


// Removes all EXTEPHEMS from memory
// returns 0 if all satellites are removed successfully from memory, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphRemoveAllSats)();


// Returns the number of EXTEPHEM's currently loaded
// See ExtEphGetLoaded for example.
// This function is useful for dynamically allocating memory for the array that is passed to the function ExtEphGetLoaded().
// returns The number of EXTEPHEM's currently loaded
typedef int (STDCALL *fnPtrExtEphGetCount)();


// Retrieves all of the currently loaded satKeys. These satKeys can be used to access the external ephemeris data for the EXTEPHEM's
// It is recommended that ExtEphGetCount() is used to count how many satellites are currently loaded in the ExtEphem DLL's binary tree. 
// The users then use this number to dynamically allocate the satKeys array and pass it to this function.
// 
// If the users prefer to pass a static array to the function, ensure that it is big enough to store all the satKeys in memory.
// order              Specifies the order in which the satKeys should be returned: 0=ascending, 1=descending, 2=order as loaded (in-Integer)
// satKeys            The array in which to store the satKeys (out-Long[*])
typedef void (STDCALL *fnPtrExtEphGetLoaded)(int order, __int64 satKeys[]);


// Allows for an EXTEPHEM to be added to memory without using an input file. The function creates a place holder for an EXTEPHEM
// If the same satellite (same satNum and epochDs50UTC) was previously added to the ExtEphem DLL's binary tree, 
// the function will generate a new unique satKey. This is very useful when the users want to compare ephemerides 
// of the same satellite number and same epoch time from different sources. 
// satNum             Satellite number (in-Integer)
// epochDs50UTC       Epoch time in ds50UTC (in-Double)
// ae                 Mean Earth radius (km) (in-Double)
// ke                 Earth gravitational constant (in-Double)
// coordSys           Ephemeris coordinate system (see COORD_?) (in-Integer)
// returns The satKey of the newly added EXTEPHEM on success, a negative value on error
typedef __int64 (STDCALL *fnPtrExtEphAddSat)(int satNum, double epochDs50UTC, double ae, double ke, int coordSys);


// Adds an ephemeris point to the end of an EXTEPHEM's set of ephemeris points
// The new ephemeris point will only be added to the array if its time is greater than the times of all points already in the array. 
// Therefore, the array is always in sorted order (t1 < t2 <... < tn).
// satKey             The satellite's unique key (in-Long)
// ds50UTC            Epoch time in ds50UTC (in-Double)
// pos                Position at cuurent time (km) (in-Double[3])
// vel                Velocity at current time (km/sec) (in-Double[3])
// revNum             The ephemeris point revolution number (in-Integer)
// returns 0 if the ephemeris point is added successfully to the requested satellite, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphAddSatEphem)(__int64 satKey, double ds50UTC, double pos[3], double vel[3], int revNum);


// Adds an ephemeris point (including covariance matrix) to the end of an EXTEPHEM's set of ephemeris points
// satKey             The satellite's unique key (in-Long)
// ds50UTC            Epoch time in ds50UTC (in-Double)
// pos                Position at cuurent time (km) (in-Double[3])
// vel                Velocity at current time (km/sec) (in-Double[3])
// revNum             The ephemeris point revolution number (in-Integer)
// covUVW             The covariance matrix in vector format (21 terms in one-dimensional array) (in-Double[21])
// returns 0 if the ephemeris point is added successfully to the requested satellite, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphAddSatEphemCovMtx)(__int64 satKey, double ds50UTC, double pos[3], double vel[3], int revNum, double covUVW[21]);


// Adds an ephemeris point (including covariance matrix) to the end of an EXTEPHEM's set of ephemeris points
// satKey             The satellite's unique key (in-Long)
// ds50UTC            Epoch time in ds50UTC (in-Double)
// pos                Position at cuurent time (km) (in-Double[3])
// vel                Velocity at current time (km/sec) (in-Double[3])
// revNum             The ephemeris point revolution number (in-Integer)
// extArr             The extra array: 1-21=lower triangle matrix, 22-128=future use (in-Double[128])
// returns 0 if the ephemeris point is added successfully to the requested satellite, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphAddSatEphemExt)(__int64 satKey, double ds50UTC, double pos[3], double vel[3], int revNum, double extArr[128]);


// Loads satellite data from an external ephemeris file (any valid external ephemeris file formats) and returns a satKey on success
// extEphFile         The name of the file containing external ephemeris data to be loaded (in-Character[512])
// returns The satKey of the newly added EXTEPHEM on success, a zero or negative value on error
typedef __int64 (STDCALL *fnPtrExtEphAddSatFrFile)(char extEphFile[512]);


// Gets number of epehemeris points associated with satKey
// satKey             The satellite's unique key (in-Long)
// numOfPts           Number of ephemeris points (out-Integer)
// returns 0 if the data is successfully retrieved, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphGetNumPts)(__int64 satKey, int* numOfPts);


// Retrieves all data for an EXTEPHEM with a single function call
// satKey             The satellite's unique key (in-Long)
// satNum             Satellite number (out-Integer)
// satName            Satellite international designator (out-Character[8])
// recName            Record name (default to source file path, fileLoc) (out-Character[128])
// epochDs50UTC       Satellite epoch time in ds50UTC (out-Double)
// ae                 Mean Earth radius (km) (out-Double)
// ke                 Earth gravitational constant (er**3/2 per minute) (out-Double)
// pos                Position at epoch (km) (out-Double[3])
// vel                Velocity at epoch (km/s) (out-Double[3])
// coordSys           Ephemeris coordinate (see COORD_?) (out-Integer)
// numOfPts           Number of ephemeris points (out-Integer)
// fileLoc            File location (out-Character[512])
// returns 0 if the data is successfully retrieved, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphGetAllFields)(__int64 satKey, int* satNum, char satName[8], char recName[128], double* epochDs50UTC, double* ae, double* ke, double pos[3], double vel[3], int* coordSys, int* numOfPts, char fileLoc[512]);


// Retrieves the value of a specific field of an EXTEPHEM
// 
// When using xf_ExtEph = 11, the input coordinate system is returned as an integer value.  The table below shows the coordinate system values:
// 
// table
// 
// Value
// Coordinate System
// 
// 1  ECI TEME of DATE
// 2  MEME of J2K
// 3  Earth Fixed Greenwich (EFG)
// 4  Earch Centered Rotation (ECR)
// 100Invalid
//    
// satKey             The satellite's unique key (in-Long)
// xf_ExtEph          Predefined number specifying which field to retrieve (see XF_EXTEPH_?) (in-Integer)
// valueStr           A string to contain the value of the requested field (out-Character[512])
// returns 0 if the EXTEPHEM data is successfully retrieved, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphGetField)(__int64 satKey, int xf_ExtEph, char valueStr[512]);


// Updates the value of a specific field of an EXTEPHEM
// satKey             The satellite's unique key (in-Long)
// xf_ExtEph          Predefined number specifying which field to set (see XF_EXTEPH_?) (in-Integer)
// valueStr           The new value of the specified field, expressed as a string (in-Character[512])
// returns 0 if the EXTEPHEM data is successfully updated, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphSetField)(__int64 satKey, int xf_ExtEph, char valueStr[512]);


// Retrieves the times (in days since 1950 UTC) of the start and end ephemeris points of the EXTEPHEM  
// satKey             The satellite's unique key (in-Long)
// startDs50UTC       The ephemeris start time (first ephemeris point) in days since 1950, UTC (out-Double)
// endDs50UTC         The ephemeris end time (last ephemeris point) in days since 1950, UTC (out-Double)
// returns 0 if successful, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphStartEndTime)(__int64 satKey, double* startDs50UTC, double* endDs50UTC);


// Retrieves the data for a specific point within an EXTEPHEM
// It is important to know that the array subscript starts at one (not zero).
// satKey             The satellite's unique key (in-Long)
// index              The position number of the ephemeris point to be retrieved (1=first point) (in-Integer)
// ds50UTC            The resulting time in ds50UTC (out-Double)
// pos                The resulting position (km) (out-Double[3])
// vel                The resulting velocity (km/s) (out-Double[3])
// revNum             The resulting revolution number (out-Integer)
// returns 0 if the ephemeris data is successfully retrieved, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphGetEphemeris)(__int64 satKey, int index, double* ds50UTC, double pos[3], double vel[3], int* revNum);


// Retrieves the data (including the covariance matrix) for a specific point within an EXTEPHEM
// satKey             The satellite's unique key (in-Long)
// index              The position number of the ephemeris point to be retrieved (1=first point) (in-Integer)
// ds50UTC            The resulting time in ds50UTC (out-Double)
// pos                The resulting position (km) (out-Double[3])
// vel                The resulting velocity (km/s) (out-Double[3])
// revNum             The resulting revolution number (out-Integer)
// covMtx             The 6x6 covariance matrix (out-Double[6, 6])
// returns 0 if the ephemeris data is successfully retrieved, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphGetCovMtx)(__int64 satKey, int index, double* ds50UTC, double pos[3], double vel[3], int* revNum, double covMtx[6][6]);


// Interpolates the external ephemeris data to the requested time in minutes since the satellite's epoch time
// The coordinate system of the output position and velocity is the same as the input ephemerides.
// satKey             The satellite's unique key (in-Long)
// mse                The requested time in minutes since the satellite's epoch time (in-Double)
// ds50UTC            The resulting time in ds50UTC (out-Double)
// pos                The resulting position (km) (out-Double[3])
// vel                The resulting velocity (km/s) (out-Double[3])
// revNum             The resulting revolution number (out-Integer)
// returns 0 if the external ephemeris data is successfully interpolated, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphMse)(__int64 satKey, double mse, double* ds50UTC, double pos[3], double vel[3], int* revNum);


// Interpolates the external ephemeris data to the requested time in minutes since the satellite's epoch time
// satKey             The satellite's unique key (in-Long)
// mse                The requested time in minutes since the satellite's epoch time (in-Double)
// ds50UTC            The resulting time in ds50UTC (out-Double)
// pos                The resulting position (km) (out-Double[3])
// vel                The resulting velocity (km/s) (out-Double[3])
// revNum             The resulting revolution number (out-Integer)
// covMtx             The 6x6 covariance matrix (out-Double[6, 6])
// returns 0 if the external ephemeris data is successfully interpolated, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphMseCovMtx)(__int64 satKey, double mse, double* ds50UTC, double pos[3], double vel[3], int* revNum, double covMtx[6][6]);


// Interpolates the external ephemeris data to the requested time in days since 1950, UTC
// The coordinate system of the output position and velocity is the same as the input ephemerides.
// satKey             The satellite's unique key (in-Long)
// ds50UTC            The requested time in ds50UTC (in-Double)
// mse                The resulting time in minutes since the satellite's epoch time (out-Double)
// pos                The resulting position (km) (out-Double[3])
// vel                The resulting velocity (km/s) (out-Double[3])
// revNum             The resulting revolution number (out-Integer)
// returns 0 if the external ephemeris data is successfully interpolated, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphDs50UTC)(__int64 satKey, double ds50UTC, double* mse, double pos[3], double vel[3], int* revNum);


// Interpolates the external ephemeris data to the requested time in days since 1950, UTC
// satKey             The satellite's unique key (in-Long)
// ds50UTC            The requested time in ds50UTC (in-Double)
// mse                The resulting time in minutes since the satellite's epoch time (out-Double)
// pos                The resulting position (km) (out-Double[3])
// vel                The resulting velocity (km/s) (out-Double[3])
// revNum             The resulting revolution number (out-Integer)
// covMtx             The 6x6 covariance matrix (out-Double[6, 6])
// returns 0 if the external ephemeris data is successfully interpolated, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphDs50UTCCovMtx)(__int64 satKey, double ds50UTC, double* mse, double pos[3], double vel[3], int* revNum, double covMtx[6][6]);


// Extensible routine which retrieves/interpolates external ephemeris data based on user's request
// satKey             The satellite's unique key (in-Long)
// xf_getEph          Input type: 1=using MSE, 2=using Ds50UTC, 3=using index (one-based) (in-Integer)
// inVal              Input value as indicated in the input type (in-Double)
// extArr             The resulting array: 1st=mse, 2=ds50UTC, 3-5=pos, 5-8=vel, 9=revNum, 10-30=6x6 covMtx lower triangle (out-Double[128])
// returns 0 if the external ephemeris data is successfully interpolated, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphXten)(__int64 satKey, int xf_getEph, double inVal, double extArr[128]);


// This function returns a string that represents the EXTFIL= directive used to read a particular EXTEPHEM
// satKey             The satellite's unique key (in-Long)
// line               A string representing the directive used to read a particular EXTEPHEM (out-Character[512])
// returns 0 if the line is retrieved successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrExtEphGetLine)(__int64 satKey, char line[512]);


// Returns the first satKey that matches the satNum in the EXTEPHEM binary tree
// This function is useful when ExtEphem DLL is used in applications that requires only one record (one EXTEPHEM entry) 
// for one satellite and the applications refer to that EXTEPHEM by its satellite number. 
// However, the Astrodynamic Standard Shared library only uses satKeys; this function helps to return the associated satKey of that satellite.
// satNum             input satellite number (in-Integer)
// returns The satellite's unique key
typedef __int64 (STDCALL *fnPtrExtEphGetSatKey)(int satNum);


// Creates satKey from EXTEPHEM's satelite number and date time group string
// This is the proper way to reconstruct a satKey from its fields. If the users use their own routine to do this, the computed satKey might be different. 
// satNum             input satellite number (in-Integer)
// epochDtg           input date time group string: [yy]yydddhhmmss.sss or [yy]yyddd.ddddddd or DTG15, DTG17, DTG20 (in-Character[20])
// returns The satellite's unique key
typedef __int64 (STDCALL *fnPtrExtEphFieldsToSatKey)(int satNum, char epochDtg[20]);
  
  // Indexes of coordinate systems
  static const int  
     COORD_ECI   = 1,          // ECI TEME of DATE
     COORD_J2K   = 2,          // MEME of J2K
     COORD_EFG   = 3,          // Earth Fixed Greenwich (EFG)
     COORD_ECR   = 4,          // Earch Centered Rotation (ECR)
     COORD_LLH   = 5,          // Lat Lon Height and a vector offset (range, azimuth, elevation)
     COORD_SEN   = 6,          // Sensor site (ECR) and a vector offset (range, azimuth, elevation)
     
     COORD_ECIFP = 11,         // ECI TEME of DATE, fixed point
     COORD_J2KFP = 12,         // MEME of J2K, fixed point
     COORD_EFGFP = 13,         // Earth Fixed Greenwich (EFG), fixed point
     COORD_ECRFP = 14,         // Earch Centered Rotation (ECR), fixed point
     COORD_LLHOV = 15,         // Lat Lon Height and an offset vector (range, azimuth, elevation)
     COORD_SENOV = 16,         // Sensor site (ECR) and an offset vector (range, azimuth, elevation)
     COORD_HCSRL = 17,         // Current position (LLH), heading (azimuth), and constant speed of an mobile object that travels in a rhumb line course
     COORD_WPTRL = 18,         // List of waypoints (LLH) that describes the movement of an object that travels in a rhumb line course
     COORD_HCSGC = 19,         // Current position (LLH), initial heading (azimuth), and constant speed of an mobile object that travels in a great circle course
     COORD_WPTGC = 20,         // List of waypoints (LLH) that describes the movement of an object that travels in a great circle course
     
     
     COORD_INVALID = 100;      // Invalid coordinate system
  
  static const int   
     COVMTX_UVW_DATE  =  0,   // UVW convariance matrix - TEME of DATE
     COVMTX_XYZ_DATE  = 10,   // Cartesian covariance matrix - TEME of DATE 
     COVMTX_EQNX_DATE = 20,   // Equinoctial covariance matrix - TEME of DATE
     COVMTX_UVW_J2K   = 30,   // UVW convariance matrix - MEME of J2K
     COVMTX_XYZ_J2K   = 40,   // Cartesian covariance matrix - MEME of J2K
     COVMTX_EQNX_J2K  = 50;   // Equinoctial covariance matrix - MEME of J2K   
     
     
  static const int  
     XF_GETEPH_MSE = 1,     // Get ephemeris data using time in minutes since epoch 
     XF_GETEPH_UTC = 2,     // Get ephemeris data using time in days since 1950 UTC
     XF_GETEPH_IDX = 3;     // Get ephemeris data using index of the element in the array 
     
  // Indexes of EXTEPH data fields
  static const int  
     XF_EXTEPH_SATNUM    =  1,      // Satellite number I5
     XF_EXTEPH_EPOCH     =  2,      // Epoch YYDDDHHMMSS.SSS
     XF_EXTEPH_AE        =  3,      // Earth radius (km)
     XF_EXTEPH_KE        =  4,      // Ke
     XF_EXTEPH_POSX      =  5,      // position X (km) F16.8 
     XF_EXTEPH_POSY      =  6,      // position Y (km) F16.8 
     XF_EXTEPH_POSZ      =  7,      // position Z (km) F16.8   
     XF_EXTEPH_VELX      =  8,      // velocity X (km/s) F16.12
     XF_EXTEPH_VELY      =  9,      // velocity Y (km/s) F16.12
     XF_EXTEPH_VELZ      = 10,      // velocity Z (km/s) F16.12
     XF_EXTEPH_COORD     = 11,      // Input coordinate systems
     XF_EXTEPH_NUMOFPTS  = 12,      // Num of ephemeris points
     XF_EXTEPH_FILEPATH  = 13,      // Ephemeris file path
     XF_EXTEPH_SATNAME   = 14,      // International Designator
     XF_EXTEPH_RECNAME   = 15;      // Record name
     
// ExtEphemDll's function pointers declaration
extern fnPtrExtEphInit                     ExtEphInit;
extern fnPtrExtEphGetInfo                  ExtEphGetInfo;
extern fnPtrExtEphLoadFile                 ExtEphLoadFile;
extern fnPtrExtEphSaveFile                 ExtEphSaveFile;
extern fnPtrExtEphRemoveSat                ExtEphRemoveSat;
extern fnPtrExtEphRemoveAllSats            ExtEphRemoveAllSats;
extern fnPtrExtEphGetCount                 ExtEphGetCount;
extern fnPtrExtEphGetLoaded                ExtEphGetLoaded;
extern fnPtrExtEphAddSat                   ExtEphAddSat;
extern fnPtrExtEphAddSatEphem              ExtEphAddSatEphem;
extern fnPtrExtEphAddSatEphemCovMtx        ExtEphAddSatEphemCovMtx;
extern fnPtrExtEphAddSatEphemExt           ExtEphAddSatEphemExt;
extern fnPtrExtEphAddSatFrFile             ExtEphAddSatFrFile;
extern fnPtrExtEphGetNumPts                ExtEphGetNumPts;
extern fnPtrExtEphGetAllFields             ExtEphGetAllFields;
extern fnPtrExtEphGetField                 ExtEphGetField;
extern fnPtrExtEphSetField                 ExtEphSetField;
extern fnPtrExtEphStartEndTime             ExtEphStartEndTime;
extern fnPtrExtEphGetEphemeris             ExtEphGetEphemeris;
extern fnPtrExtEphGetCovMtx                ExtEphGetCovMtx;
extern fnPtrExtEphMse                      ExtEphMse;
extern fnPtrExtEphMseCovMtx                ExtEphMseCovMtx;
extern fnPtrExtEphDs50UTC                  ExtEphDs50UTC;
extern fnPtrExtEphDs50UTCCovMtx            ExtEphDs50UTCCovMtx;
extern fnPtrExtEphXten                     ExtEphXten;
extern fnPtrExtEphGetLine                  ExtEphGetLine;
extern fnPtrExtEphGetSatKey                ExtEphGetSatKey;
extern fnPtrExtEphFieldsToSatKey           ExtEphFieldsToSatKey;



void LoadExtEphemDll();
void FreeExtEphemDll();




#endif
// ========================= End of auto generated code ==========================
