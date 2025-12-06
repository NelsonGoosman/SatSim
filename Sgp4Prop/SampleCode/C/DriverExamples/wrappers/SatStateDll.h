// This wrapper file was generated automatically by the GenDllWrappers program.

#ifndef SATSTATEDLL_H
#define SATSTATEDLL_H

#include "../services/DllUtils.h"

// Provide the path to the dll/so/dylib
#if defined (_WIN32) || defined (__CYGWIN__)
  #define SatStateDll "SatState.dll"
#elif __APPLE__
  #define SatStateDll "libsatstate.dylib"
#else
  #define SatStateDll "libsatstate.so"
#endif


// Notes: This function has been deprecated since v9.0. 
// Initializes SatState DLL for use in the program
// If this function returns an error, it is recommended that the users stop the program immediately. 
// The error occurs if the users forget to load and initialize all the prerequisite DLLs, 
// as listed in the DLL Prerequisite section, before using this DLL.
// apAddr             The handle that was returned from DllMainInit() (in-Long)
// returns 0 if SatState.dll is initialized successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateInit)(__int64 apAddr);


// Returns information about the current version of SatState DLL. 
// The information is placed in the string parameter passed in.
// The returned string provides information about the version number, build date, and the platform of the SatState DLL. 
// infoStr            A string to hold the information about SatState.dll (out-Character[128])
typedef void (STDCALL *fnPtrSatStateGetInfo)(char infoStr[128]);


// Loads any orbital element types (TLE's/SPVEC's/VCM's), EXTEPHEM's, and/or propagator controls from an input text file
// Internally, if taskMode = 1, this function calls SpProp.SpLoadFile(); 
// and if taskMode = 2, this function calls Tle.TleLoadFile(), SpVec.SpVecLoadFile(), Vcm.VcmLoadFile(), ExtEphem.ExtEphLoadFile(); 
// if taskMode = 3, both tasks (1 and 2) are executed.
// inputFile          The name of the input file to load (in-Character[512])
// xf_Task            Specified task mode: 1=load SP control parameters, 2=load elsets only, 3=both 1 + 2 (in-Integer)
// returns 0 if the input file is read successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateLoadFile)(char inputFile[512], int xf_Task);


// Saves currently loaded orbital element types (TLE's/SPVEC's/VCM's), EXTEPHEM's, and/or propagator controls to a file
// The purpose of this function is to save the current SatState-related settings, usually used in GUI applications, for future use.
// 
// Internally, if taskMode = 1, this function calls SpProp.SpSaveFile(); 
// and if taskMode = 2, this function calls Tle.TleSaveFile(), SpVec.SpVecSavedFile(), Vcm.VcmSaveFile(), ExtEphem.ExtEphSaveFile(); 
// if taskMode = 3, both tasks (1 and 2) are executed.
// outFile            The name of the file in which to save the settings (in-Character[512])
// saveMode           Specifies whether to create a new file or append to an existing one (0 = create, 1= append) (in-Integer)
// saveForm           Specifies the mode in which to save the file (0 = text format, 1 = not yet implemented, reserved for future) (in-Integer)
// xf_Task            Specified task mode: 1=Only save propagator control parameters, 2=Only save orbital elements/external ephemeris data,	3=Save both 1 + 2 (in-Integer)
// returns 0 if the data is successfully saved to the file, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateSaveFile)(char outFile[512], int saveMode, int saveForm, int xf_Task);


// Removes a satellite from the appropriate elset DLL's set of loaded satellites. 
// The function will automatically choose the proper set of elsets from which to remove the satellite. 
// The choices are: Tle.dll, SpVec.dll, Vcm.dll, or ExtEphem.dll   
// If the users enter an invalid satKey (a satKey that does not exist in memory), the function will return a non-zero value indicating an error.
// satKey             The unique key of the satellite to be removed (in-Long)
// returns 0 if the satellite is successfully removed from memory, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateRemoveSat)(__int64 satKey);


// Removes a satellite from the appropriate sets of loaded satellites (elset dll and propagator dll). 
// The function will remove the satellite from the elset DLL's sets as in SatStateRemoveSat() and 
// from the appropriate propagator's set of initialized satellites if it exists there.
// satKey             The unique key of the satellite to be removed (in-Long)
// returns 0 if the satellite is successfully removed from memory, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateRemoveSatAll)(__int64 satKey);


// Removes all satellites from all of the loaded data sets. 
// It will remove all satellites from the following sets: Tle, SpVec, Vcm, ExtEphem, Sgp4Prop, and SpProp
// returns 0 if all of the data sets are cleared successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateRemoveAllSats)();


// Resets propagator settings back to their default values
typedef void (STDCALL *fnPtrSatStateReset)();


// Returns the total number of satellites (TLE's, SPVEC's, VCM's, and EXTEPHEM's) currently loaded in memory
// See SatStateGetLoaded for example.
// This function is useful for dynamically allocating memory for the array that is passed to the function SatStateGetLoaded.
// returns The total number of currently loaded satellites
typedef int (STDCALL *fnPtrSatStateGetCount)();


// Retrieves all of the currently loaded satKeys. 
// These satKeys can be used to access the internal data for the satellites.
// It is recommended that SatStateGetCount() is used to count how many satellites are currently loaded in memory. 
// The user can then use this number to dynamically allocate the satKeys array and pass it to this function.
// 
// If the user prefers to pass a static array to the function, make sure it is big enough to store all the satKeys in memory.
// order              Specifies the order in which the satKeys should be returned:	0=ascending order, 1=descending order, 2=order in which the satKeys were loaded in memory (in-Integer)
// satKeys            The array in which to store the satKeys (out-Long[*])
typedef void (STDCALL *fnPtrSatStateGetLoaded)(int order, __int64 satKeys[]);


// Returns the first satKey that contains the specified satellite number in all sets of loaded satellites. 
// These sets will be searched: Tle, SpVec, Vcm, and ExtEphem.
// This function is useful when a satellite is used in applications that require only one record for one 
// satellite and the applications refer to that satellite by its satellite number. 
// However, the Astrodynamic Standard Shared library is only working with satKeys, this function helps to return the associated satKey of that satellite.
// satNum             The satellite number to search for (in-Integer)
// returns The satKey of the matching satellite if one is found, a negative value indicating an error if not
typedef __int64 (STDCALL *fnPtrSatStateNumToKey)(int satNum);


// Retrieves the data which is common to all satellite types. 
// All common fields are retrieved with a single function call.
// The apogee height and perigee height are defined as the distance above an ellipsoid 
// created using the earth flattening factor from the selected geopotential model.
// Note:  When using SP elsets (TLE type 6, SPVEC, or VCM), calling SatStateGetSatDataAll 
// will implicitly call SpInit in order to extract the mu value from the GEO file the elset is tied to.  
// The elset must have a valid GEO directory available or an error will be returned.
// satKey             The satellite's unique key (in-Long)
// satNum             Satellite number (out-Integer)
// satName            Satellite international designator (out-Character[8])
// eltType            Element type (see ELTTYPE_?) (out-Integer)
// revNum             Revolution number at epoch (out-Integer)
// epochDs50UTC       Epoch time time in days since 1950 UTC (out-Double)
// bField             Ballistic coefficient (m^2/kg) (out-Double)
// elsetNum           Element set number (out-Integer)
// incli              Inclination (deg) (out-Double)
// node               Right ascension of ascending node (deg) (out-Double)
// eccen              Eccentricity (out-Double)
// omega              Argument of perigee (deg) (out-Double)
// mnAnomaly          Mean anomaly (deg) (out-Double)
// mnMotion           Mean motion (rev/day) (out-Double)
// period             Satellite period (min) (out-Double)
// perigeeHt          Satellite perigee height (km) above the ellipsoid (out-Double)
// apogeeHt           Satellite apogee height (km) above the ellipsoid (out-Double)
// perigee            Satellite perigee height from the center of the earth (km) (out-Double)
// apogee             Satellite apogee height from the center of the earth (km) (out-Double)
// a                  Semi-major axis (km) (out-Double)
// returns 0 if all satellite data fields are retrieved successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateGetSatDataAll)(__int64 satKey, int* satNum, char satName[8], int* eltType, int* revNum, double* epochDs50UTC, double* bField, int* elsetNum, double* incli, double* node, double* eccen, double* omega, double* mnAnomaly, double* mnMotion, double* period, double* perigeeHt, double* apogeeHt, double* perigee, double* apogee, double* a);


// Retrieves an individual field of a satellite. 
// satKey             The satellite's unique key (in-Long)
// xf_Sat             Predefined number specifying which field to retrieve (see XF_SAT_?) (in-Integer)
// retVal             A string to contain the value of the requested field (out-Character[512])
// returns 0 if the satellite data is successfully retrieved, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateGetSatDataField)(__int64 satKey, int xf_Sat, char retVal[512]);


// Initializes a TLE, SPVEC, or VCM in preparation for propagation, or an EXTEPHEM in preparation for interpolation
// satKey             The satellite's unique key (in-Long)
// returns 0 if the satellite is successfully initialized, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateInitSat)(__int64 satKey);


// Propagates a TLE/SPVEC/VCM, or interpolates an EXTEPHEM. 
// The satellite is propagated/interpolated to the specified time calculated in minutes since the satellite's epoch time
// satKey             The satellite's unique key (in-Long)
// mse                The time to propagate to, specified in minutes since the satellite's epoch time (in-Double)
// ds50UTC            Resulting time in days since 1950, UTC (out-Double)
// revNum             Revolution number (out-Integer)
// pos                Resulting ECI position vector (km) in True Equator and Mean Equinox of Epoch (out-Double[3])
// vel                Resulting ECI velocity vector (km/s) in True Equator and Mean Equinox of Epoch (out-Double[3])
// llh                Resulting geodetic latitude (deg), longitude(deg), and height (km) (out-Double[3])
// returns 0 if the satellite is propagated/interpolated successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateMse)(__int64 satKey, double mse, double* ds50UTC, int* revNum, double pos[3], double vel[3], double llh[3]);


// Propagates a TLE/SPVEC/VCM, or interpolates an EXTEPHEM. 
// The satellite is propagated/interpolated to the specified time calculated in days since 1950, UTC.
// satKey             The satellite's unique key (in-Long)
// ds50UTC            The time to propagate to, specified in days since 1950, UTC (in-Double)
// mse                Resulting time in minutes since the satellite's epoch time (out-Double)
// revNum             Revolution number (out-Integer)
// pos                Resulting ECI position vector (km) in True Equator and Mean Equinox of Epoch (out-Double[3])
// vel                Resulting ECI velocity vector (km/s) in True Equator and Mean Equinox of Epoch (out-Double[3])
// llh                Resulting geodetic latitude (deg), longitude(deg), and height (km) (out-Double[3])
// returns 0 if the satellite is propagated/interpolated successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateDs50UTC)(__int64 satKey, double ds50UTC, double* mse, int* revNum, double pos[3], double vel[3], double llh[3]);


// Returns additional propagated/interpolated results (reserved for future implementation)
// Reserved for future implementation
// Use this function immediately after the call to SatStateMse or SatStateDs50UTC. 
// satKey             the satellite's unique key (in-Long)
// index              type of returned data (in-Integer)
// destArr            the resulting array (out-Double[128])
// returns 0 if successful, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateGetPropOut)(__int64 satKey, int index, double destArr[128]);


// Returns various ephemeris comparison results between two satellite states.
// 
// The "in-track" is NOT the velocity direction, but is defined as completing the right handed coordinate system 
// defined by the position vector (radial) and the angular momentum vector (cross-track).
// primSatKey         The primary satellite's unique key (in-Long)
// secSatKey          The secondary satellite's unique key (in-Long)
// ds50UTC            Requested time in days since 1950 UTC (in-Double)
// uvwFlag            UVW coordinate system flag: 0=use rotating UVW, 1=use inertial UVW (in-Integer)
// xa_Delta           The resulting ephemeris comparison deltas (see XA_DELTA_?) (out-Double[100])
// returns 0 if the comparison results are computed successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateEphCom)(__int64 primSatKey, __int64 secSatKey, double ds50UTC, int uvwFlag, double xa_Delta[100]);


// Returns various ephemeris comparison results between two satellite states (_OS one step) .
// 
// The "in-track" is NOT the velocity direction, but is defined as completing the right handed coordinate system 
// defined by the position vector (radial) and the angular momentum vector (cross-track).
// priPosVel          The primary satellite's state (TEME of Date) in an array (position(1st-3rd, km), velocity(4th-6th, km/s)) (in-Double[6])
// secPosVel          The secondary satellite's state (TEME of Date) in an array (position(1st-3rd, km), velocity(4th-6th, km/s)) (in-Double[6])
// ds50UTC            Requested time in days since 1950 UTC (in-Double)
// uvwFlag            UVW coordinate system flag: 0=use rotating UVW, 1=use inertial UVW (in-Integer)
// xa_Delta           The resulting ephemeris comparison deltas (see XA_DELTA_?) (out-Double[100])
typedef void (STDCALL *fnPtrSatStateEphCom_OS)(double priPosVel[6], double secPosVel[6], double ds50UTC, int uvwFlag, double xa_Delta[100]);


// Determines if a satellite contains covariance matrix. 
// 0=no, 1=yes
// satKey             the satellite's unique key (in-Long)
// returns 0=sat doesn't have cov mtx, 1=sat has cov mtx
typedef int (STDCALL *fnPtrSatStateHasCovMtx)(__int64 satKey);


// Propagates/Interpolates UVW covariance matrix from VCM/External ephemeris to the time in days since 1950
// satKey             The satellite's unique key (in-Long)
// ds50UTC            The input time in days since 1950 UTC (in-Double)
// covUVW             6x6 UVW covariance matrix (out-Double[6, 6])
// returns 0 if the UVW covariance matrix is propagated/interpolated successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateGetCovUVW)(__int64 satKey, double ds50UTC, double covUVW[6][6]);


// Generate external ephemeris file for the specified satellite (via its unique satKey) 
// Note: No need to initialize the satellite before this call. If it was intialized, it will be removed after this call
// satKey             The satellite's unique key (in-Long)
// startDs50UTC       Start time in days since 1950 UTC (in-Double)
// stopDs50UTC        Stop time in days since 1950 UTC (in-Double)
// stepSizeSecs       Step size in seconds. Set to zero if natural integration step size (auto adjust) is desired for SP propagator (in-Double)
// ephFileName        The generated external ephemeris file name (in-Character[512])
// ephFileType        External ephemeris file type (see EPHFILETYPE_?) (in-Integer)
// returns 0 if the external ephemeris file was generated successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSatStateGenEphFile)(__int64 satKey, double startDs50UTC, double stopDs50UTC, double stepSizeSecs, char ephFileName[512], int ephFileType);


// Finds the time of ascending nodal crossing of the specified satellite prior to an input time in days since 1950 TAI
// satKey             The satellite's unique key (in-Long)
// ds50TAI            Input time in ds50TAI (in-Double)
// returns Time at nodal crossing ds50TAI
typedef double (STDCALL *fnPtrGetNodalCrossingPriorToTime)(__int64 satKey, double ds50TAI);


// Get the Gobs parameters for a TLE
// satKey             The satellite's unique key (in-Long)
// ds50UTC            Propagation in days since 1950 UTC (in-Double)
// xa_gobs            (See XA_GOBS_?) (out-Double[32])
// errCode            Error code (out-Integer)
typedef void (STDCALL *fnPtrGetGobsParams)(__int64 satKey, double ds50UTC, double xa_gobs[32], int* errCode);


// Does an XP GOBS comparison
// primSatKey         The primary satellite's unique key (in-Long)
// secSatKey          The secondary satellite's unique key (in-Long)
// ds50UTC            Common epoch to compare in days since 1950 UTC (in-Double)
// xa_gobs_lim        The gobs comparison limits (see XA_GOBS_LIM?) (in-Double[16])
// xa_gobs_delta      The resulting gobs comparison deltas (see XA_GOBS_DELTA_?) (out-Double[16])
// returns 0 if the comparison results are computed successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrGobsCom)(__int64 primSatKey, __int64 secSatKey, double ds50UTC, double xa_gobs_lim[16], double xa_gobs_delta[16]);


// Does an XP GOBS comparison using gobs arrays
// xa_gobs_prim       Primary sat GOBS parameters (see XA_GOBS_?) (in-Double[32])
// xa_gobs_sec        Secondary sat GOBS parameters (see XA_GOBS_?) (in-Double[32])
// xa_gobs_lim        The gobs comparison limits (see XA_GOBS_LIM_?) (in-Double[16])
// xa_gobs_delta      The resulting gobs comparison deltas (see XA_GOBS_DELTA_?) (out-Double[16])
typedef void (STDCALL *fnPtrGobsComArr)(double xa_gobs_prim[32], double xa_gobs_sec[32], double xa_gobs_lim[16], double xa_gobs_delta[16]);
  
  // Indexes of available satellite data fields
  static const int  
     XF_SATFIELD_EPOCHUTC =  1,    // Satellite epoch time in days since 1950 UTC
     XF_SATFIELD_MNANOM   =  2,    // Mean anomaly (deg)
     XF_SATFIELD_NODE     =  3,    // Right ascension of asending node (deg) 
     XF_SATFIELD_OMEGA    =  4,    // Argument of perigee (deg)
     XF_SATFIELD_PERIOD   =  5,    // Satellite's period (min)
     XF_SATFIELD_ECCEN    =  6,    // Eccentricity
     XF_SATFIELD_INCLI    =  7,    // Orbit inclination (deg)
     XF_SATFIELD_MNMOTION =  8,    // Mean motion (rev/day)
     XF_SATFIELD_BFIELD   =  9,    // GP B* drag term (1/er)  or SP Radiation Pressure Coefficient
     XF_SATFIELD_PERIGEEHT= 10,    // Perigee height above the geoid (km)
     XF_SATFIELD_APOGEEHT = 11,    // Apogee height above the geoid (km)
     XF_SATFIELD_PERIGEE  = 12,    // Perigee height above the center of the earth (km)
     XF_SATFIELD_APOGEE   = 13,    // Apogee height above the center of the earth (km)
     XF_SATFIELD_A        = 14,    // Semimajor axis (km)
     XF_SATFIELD_NDOT     = 15,    // Mean motion derivative (rev/day**2 /2)
     XF_SATFIELD_SATCAT   = 16,    // Satellite category (Synchronous, Deep space, Decaying, Routine)
     XF_SATFIELD_HTM3     = 17,    // Astat 3 Height multiplier
     XF_SATFIELD_CMOFFSET = 18,    // Center of mass offset (m)
     XF_SATFIELD_N2DOT    = 19,    // Unused
     XF_SATFIELD_NODEDOT  = 20,    // GP node dot (deg/s)
     XF_SATFIELD_ERRORTIME= 21,    // GP only - the last time when propagation has error
     XF_SATFIELD_MU       = 22;    // value of mu
  
    
  //*******************************************************************************
  
  // Indexes of available deltas
  static const int  
     XA_DELTA_POS         =  0,     // delta position (km)
     XA_DELTA_TIME        =  1,     // delta time (sec)
     XA_DELTA_PRADIAL     =  2,     // delta position in radial direction (km)
     XA_DELTA_PINTRCK     =  3,     // delta position in in-track direction (km)
     XA_DELTA_PCRSSTRCK   =  4,     // delta position in cross-track direction (km)
     XA_DELTA_VEL         =  5,     // delta velocity (km/sec)
     XA_DELTA_VRADIAL     =  6,     // delta velocity in radial direction (km/sec)
     XA_DELTA_VINTRCK     =  7,     // delta velocity in in-track direction (km/sec)
     XA_DELTA_VCRSSTRCK   =  8,     // delta velocity in cross-track direction (km/sec)
     XA_DELTA_BETA        =  9,     // delta Beta (deg)
     XA_DELTA_HEIGHT      = 10,     // delta height (km)
     XA_DELTA_ANGMOM      = 11,     // delta angular momentum (deg)
     XA_DELTA_MHLNBS_UVW  = 12,     // 3D position Mahalanobis distance in UVW Space (Bubble Covariance, only if covariance propagation is available or turned on)
     XA_DELTA_MHLNBS_HTB  = 13,     // 3D position Mahalanobis distance in Height-Time_Beta Space (Banana Covariance, only if covariance propagation is available or turned on)
     
     XA_DELTA_SIZE        =100; 
     
  // Indexes of Satellite data fields
  static const int  
     XF_SAT_NUM      =  1,      // Satellite number I5
     XF_SAT_NAME     =  2,      // Satellite international designator A8
     XF_SAT_ELTTYPE  =  3,      // Element type I1 (old name XF_SAT_EPHTYPE)
     XF_SAT_EPHTYPE  =  3,      // Obsolete - should use new name XF_SAT_ELTTYPE instead
     XF_SAT_REVNUM   =  4,      // Epoch revolution number I6
     XF_SAT_EPOCH    =  5,      // Epoch time in days since 1950
     XF_SAT_BFIELD   =  6,      // BStar drag component (GP) or Ballistic coefficient-BTerm (SP) (m^2/kg)
     XF_SAT_ELSETNUM =  7,      // Element set number
     XF_SAT_INCLI    =  8,      // Inclination (deg)
     XF_SAT_NODE     =  9,      // Right ascension of ascending node (deg)
     XF_SAT_ECCEN    = 10,      // Eccentricity
     XF_SAT_OMEGA    = 11,      // Argument of perigee (deg)
     XF_SAT_MNANOM   = 12,      // Mean anomaly (deg)
     XF_SAT_MNMOTN   = 13,      // Mean motion (revs/day)
     XF_SAT_PERIOD   = 14,      // Satellite period (min)
     XF_SAT_PERIGEEHT= 15,      // Perigee Height(km)
     XF_SAT_APOGEEHT = 16,      // Apogee Height (km)
     XF_SAT_PERIGEE  = 17,      // Perigee(km)
     XF_SAT_APOGEE   = 18,      // Apogee (km)
     XF_SAT_A        = 19;      // Semi-major axis (km)
  
  
  // Indexes of SatState's load/save file task mode
  static const int  
     XF_TASK_CTRLONLY = 1,     // Only load/save propagator control parameters
     XF_TASK_SATONLY  = 2,     // Only load/save orbital elements/external ephemeris data
     XF_TASK_BOTH     = 3;     // Load/Save both 1 and 2
     
  
  // Different external ephemeris file types
  static const int  
     EPHFILETYPE_ITC         =  1,     // ITC file format
     EPHFILETYPE_ITC_WOCOV   =  2;     // ITC compact (without covariance matrix) file format
     
  
  // Gobs records
  static const int  
     XA_GOBS_SATNUM    =  0,   // Satellite number
     XA_GOBS_LONE      =  1,   // East Longitude
     XA_GOBS_DRIFT     =  2,   // Longitude Drift Rate
     XA_GOBS_RELENERGY =  3,   // satellite's relative energy (deg^2/sec^2) - only for GOBS
     XA_GOBS_WX        =  4,   // sin(incl)*sin(r.a. node)
     XA_GOBS_WY        =  5,   // -sin(incl)*cos(r.a. node)
     XA_GOBS_WZ        =  6,   // cos(incl)
     XA_GOBS_ABARX     =  7,   // abar x
     XA_GOBS_ABARY     =  8,   // abar y 
     XA_GOBS_ABARZ     =  9,   // abar z
     XA_GOBS_AGOM      = 10,   // AGOM
     XA_GOBS_TROUGH    = 11,   // Trough/Drift Flag, 0 - 75 deg trough, 1 - 255 deg trough, 2 - both troughs, 3 - unstable point, 4 - East drift, 5 - West drift
     XA_GOBS_TOTENERGY = 12,   // Total Energy of sat (-mu/(2*a))
     XA_GOBS_INCL      = 13,   // Inclination of sat
  
     XA_GOBS_SIZE      = 32; 
  
  
  // Indexes of GOBS limits
  static const int  
     XA_GOBS_LIM_TROUGH      =  0,     // 0 - ignore trough logic, 1 - implement trough logic
     XA_GOBS_LIM_PCP         =  1,     // Primary satellite is plane changer
     XA_GOBS_LIM_PCS         =  2,     // Secondary satellite is plane changer
     XA_GOBS_LIM_ACTIVEP     =  3,     // Primary satellite is plane changer
     XA_GOBS_LIM_ACTIVES     =  4,     // Secondary satellite is plane changer
     XA_GOBS_LIM_LONGMIN     =  5,     // Min Longitude of sat
     XA_GOBS_LIM_LONGMAX     =  6,     // Max Longitude of sat
     XA_GOBS_LIM_AGOMMIN     =  7,     // Min Agom of sat
     XA_GOBS_LIM_AGOMMAX     =  8,     // Max Agom of sat
     XA_GOBS_LIM_INCLMAX     =  9,     // Max Inclination of sat
  
     XA_GOBS_LIM_SIZE        = 16; 
  
  
  // Indexes of available deltas
  static const int  
     XA_GOBS_DELTA_PRIMESAT     =  0,     // Primary satellite number 
     XA_GOBS_DELTA_SECONDARYSAT =  1,     // Secondary satellite number 
     XA_GOBS_DELTA_ASTAT        =  2,     // GOBS correlation score
     XA_GOBS_DELTA_DOP          =  3,     // delta orbital plane
     XA_GOBS_DELTA_DABAR        =  4,     // delta shape
     XA_GOBS_DELTA_DRELENERGY   =  5,     // delta Relative Energy (deg^2/day^2)
     XA_GOBS_DELTA_LONGP        =  6,     // Longitude of Primary
     XA_GOBS_DELTA_LONGMIN      =  7,     // Minimum Longitude of Secondary
     XA_GOBS_DELTA_LONGMAX      =  8,     // Maximum Longitude of Secondary
     XA_GOBS_DELTA_TROUGH       =  9,     // 0 - opposite throughs or drift rates, 1 - trough or drift rates match
     XA_GOBS_DELTA_PLANE        = 10,     // 0|1    Plane Match Flag
     XA_GOBS_DELTA_SHAPE        = 11,     // 0|1    Shape Match Flag
     XA_GOBS_DELTA_ENERGY       = 12,     // 0|1    Relative Energy Match Flag
     XA_GOBS_DELTA_LONG         = 13,     // 0|1|2  Longitude Match Flag (2 is fuzzy match)
     XA_GOBS_DELTA_AGOM         = 14,     // 0|1    Agom Match Flag
     XA_GOBS_DELTA_INCL         = 15,     // 0|1    Incl Match Flag
  
     XA_GOBS_DELTA_SIZE         = 16; 
  
  
  //*******************************************************************************
  
// SatStateDll's function pointers declaration
extern fnPtrSatStateInit                   SatStateInit;
extern fnPtrSatStateGetInfo                SatStateGetInfo;
extern fnPtrSatStateLoadFile               SatStateLoadFile;
extern fnPtrSatStateSaveFile               SatStateSaveFile;
extern fnPtrSatStateRemoveSat              SatStateRemoveSat;
extern fnPtrSatStateRemoveSatAll           SatStateRemoveSatAll;
extern fnPtrSatStateRemoveAllSats          SatStateRemoveAllSats;
extern fnPtrSatStateReset                  SatStateReset;
extern fnPtrSatStateGetCount               SatStateGetCount;
extern fnPtrSatStateGetLoaded              SatStateGetLoaded;
extern fnPtrSatStateNumToKey               SatStateNumToKey;
extern fnPtrSatStateGetSatDataAll          SatStateGetSatDataAll;
extern fnPtrSatStateGetSatDataField        SatStateGetSatDataField;
extern fnPtrSatStateInitSat                SatStateInitSat;
extern fnPtrSatStateMse                    SatStateMse;
extern fnPtrSatStateDs50UTC                SatStateDs50UTC;
extern fnPtrSatStateGetPropOut             SatStateGetPropOut;
extern fnPtrSatStateEphCom                 SatStateEphCom;
extern fnPtrSatStateEphCom_OS              SatStateEphCom_OS;
extern fnPtrSatStateHasCovMtx              SatStateHasCovMtx;
extern fnPtrSatStateGetCovUVW              SatStateGetCovUVW;
extern fnPtrSatStateGenEphFile             SatStateGenEphFile;
extern fnPtrGetNodalCrossingPriorToTime    GetNodalCrossingPriorToTime;
extern fnPtrGetGobsParams                  GetGobsParams;
extern fnPtrGobsCom                        GobsCom;
extern fnPtrGobsComArr                     GobsComArr;



void LoadSatStateDll();
void FreeSatStateDll();




#endif
// ========================= End of auto generated code ==========================
