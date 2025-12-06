// This wrapper file was generated automatically by the GenDllWrappers program.

#ifndef SPVECDLL_H
#define SPVECDLL_H

#include "../services/DllUtils.h"

// Provide the path to the dll/so/dylib
#if defined (_WIN32) || defined (__CYGWIN__)
  #define SpVecDll "SpVec.dll"
#elif __APPLE__
  #define SpVecDll "libspvec.dylib"
#else
  #define SpVecDll "libspvec.so"
#endif


// Notes: This function has been deprecated since v9.0. 
// Initializes SpVec DLL for use in the program
// If this function returns an error, it is recommended that the users stop the program immediately. The error occurs if the users forget to load and initialize all the prerequisite DLLs, as listed in the DLL Prerequisites section, before using this DLL.
// apAddr             The handle that was returned from DllMainInit() (in-Long)
// returns 0 if SpVec.dll is initialized successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSpVecInit)(__int64 apAddr);


// Returns information about the current version of SpVec DLL. The information is placed in the string parameter you pass in
// The returned string provides information about the version number, build date, and the platform of the SpVec DLL. 
// infoStr            A string to hold the information about SpVec.dll (out-Character[128])
typedef void (STDCALL *fnPtrSpVecGetInfo)(char infoStr[128]);


// Loads a text file containing SpVec's
// The users can use this function repeatedly to load B1P records from different input files. However, only unique satKeys are stored in the binary tree. Duplicated satKeys won't be stored. 
// 
// B1P records can be included directly in the main input file or they can be read from a separate file identified with "ELTFIL=[pathname\filename]" or "VECFIL=[path/filename]".
// 
// This function only reads B1P records from the main input file or B1P records from the file identified with ELTFIL or VECFIL in the input file. It won't read anything else.
// spVecFile          The name of the file containing osculating vectors (SpVecs) to be loaded (in-Character[512])
// returns 0 if the input file is read successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSpVecLoadFile)(char spVecFile[512]);


// Saves the currently loaded SpVecs's to a file
// If the users call this routine immediately after SpVecLoadFile. The SPVECs contents in the two file should be the same (minus duplicated SPVECs or bad SPVECs).
// 
// The purpose of this function is to save the current state of the loaded SPVECs, usually used in GUI applications, for future use.
// spVecFile          The name of the file in which to save the settings (in-Character[512])
// saveMode           Specifies whether to create a new file or append to an existing one (0 = create, 1= append) (in-Integer)
// saveForm           Specifies the mode in which to save the file (0 = text format, 1 = not yet implemented, reserved for future) (in-Integer)
// returns 0 if the data is successfully saved to the file, non-0 if there is an error
typedef int (STDCALL *fnPtrSpVecSaveFile)(char spVecFile[512], int saveMode, int saveForm);


// Removes an SpVec represented by the satKey from memory
// If the users enter an invalid satKey, a non-existing satKey in memory, the function will return a non-zero value indicating an error.
// satKey             The unique key of the satellite to be removed (in-Long)
// returns 0 if the SpVec is removed successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSpVecRemoveSat)(__int64 satKey);


// Removes all SpVec's from memory
// returns 0 if all SpVec's are removed successfully from memory, non-0 if there is an error
typedef int (STDCALL *fnPtrSpVecRemoveAllSats)();


// Retrieves all of the currently loaded satKeys. These satKeys can be used to access the internal data for the SpVec's
// See SpVecGetLoaded for example.
// This function is useful for dynamically allocating memory for the array that is passed to the function SpVecGetLoaded().
// returns The number of SpVec's currently loaded
typedef int (STDCALL *fnPtrSpVecGetCount)();


// Retrieves all of the currently loaded satKeys. These satKeys can be used to access the internal data for the SpVec's
// It is recommended that SpVecGetCount() is used to count how many satellites are currently loaded in the SpVec DLL's binary tree. The users then use this number to dynamically allocate the satKeys array and pass it to this function. 
// 
// If the users prefer to pass a static array to the function, make sure it is big enough to store all the satKeys in memory.
// order              Specifies the order in which the satKeys should be returned: 0=ascending, 1=descending, 2=order as loaded (in-Integer)
// satKeys            The array in which to store the satKeys (out-Long[*])
typedef void (STDCALL *fnPtrSpVecGetLoaded)(int order, __int64 satKeys[]);


// Adds an SpVec using its directly specified first and second lines
// If the satellite was previously added to the SpVec DLL's binary tree, the function also returns a negative value indicating an error. 
// 
// The users can use this function repeatedly to add many satellites (one satellite at a time) to the SpVec DLL's binary tree. 
// line1              The first input line of the two line element set (in-Character[512])
// line2              The second input line of the two line element set (in-Character[512])
// returns The satKey of the newly added SpVec on success, a negative value on error
typedef __int64 (STDCALL *fnPtrSpVecAddSatFrLines)(char line1[512], char line2[512]);


// Works like SpVecAddSatFrLines but designed for Matlab
// line1              The first input line of the two line element set (in-Character[512])
// line2              The second input line of the two line element set (in-Character[512])
// satKey             The satKey of the newly added SpVec on success, a negative value on error (out-Long)
typedef void (STDCALL *fnPtrSpVecAddSatFrLinesML)(char line1[512], char line2[512], __int64* satKey);


// Adds an SpVec using its individually provided field values
// pos                position vector (km) (in-Double[3])
// vel                velocity vector (m/s) (in-Double[3])
// secClass           Security classification: U=Unclass, C=Confidential, S=Secret (in-Character)
// satNum             Satellite number (in-Integer)
// satName            Satellite name A8 (in-Character[8])
// epochDtg           Satellite's epoch A17 (YYYYDDDHHMMSS.SSS) (in-Character[17])
// revNum             Revolution number (in-Integer)
// elsetNum           Element set number (in-Integer)
// bterm              Bterm m^2/kg (in-Double)
// agom               Agom  m^2/kg (in-Double)
// ogParm             Outgassing parameter (km/s^2) (in-Double)
// coordSys           Input coordinate system A5 - TMDAT/TMEPO: Epoch, MMB50/MMJ2K: J2000 (in-Character[5])
// returns The satKey of the newly added SpVec on success, a negative value on error
typedef __int64 (STDCALL *fnPtrSpVecAddSatFrFields)(double pos[3], double vel[3], char secClass, int satNum, char satName[8], char epochDtg[17], int revNum, int elsetNum, double bterm, double agom, double ogParm, char coordSys[5]);


// Works like SpVecAddSatFrFields but designed for Matlab 
// pos                position vector (km) (in-Double[3])
// vel                velocity vector (m/s) (in-Double[3])
// secClass           Security classification: U=Unclass, C=Confidential, S=Secret (in-Character)
// satNum             Satellite number (in-Integer)
// satName            Satellite name A8 (in-Character[8])
// epochDtg           Satellite's epoch A17 (YYYYDDDHHMMSS.SSS) (in-Character[17])
// revNum             Revolution number (in-Integer)
// elsetNum           Element set number (in-Integer)
// bterm              Bterm m^2/kg (in-Double)
// agom               Agom  m^2/kg (in-Double)
// ogParm             Outgassing parameter (km/s^2) (in-Double)
// coordSys           Input coordinate system A5 - TMDAT/TMEPO: Epoch, MMB50/MMJ2K: J2000 (in-Character[5])
// satKey             The satKey of the newly added SpVec on success, a negative value on error (out-Long)
typedef void (STDCALL *fnPtrSpVecAddSatFrFieldsML)(double pos[3], double vel[3], char secClass, int satNum, char satName[8], char epochDtg[17], int revNum, int elsetNum, double bterm, double agom, double ogParm, char coordSys[5], __int64* satKey);


// Updates an SpVec satellite's data in memory using individually provided field values. Note: satNum, epoch string can't be updated.
// The satellite's unique key will not be changed in this function call. 
// satKey             The sattelite's unique key (in-Long)
// pos                position vector (km) (in-Double[3])
// vel                velocity vector (m/s) (in-Double[3])
// secClass           Security classification: U=Unclass, C=Confidential, S=Secret (in-Character)
// satName            Satellite name A8 (in-Character[8])
// revNum             Revolution number (in-Integer)
// elsetNum           Element set number (in-Integer)
// bterm              Bterm m^2/kg (in-Double)
// agom               Agom  m^2/kg (in-Double)
// ogParm             Outgassing parameter (km/s^2) (in-Double)
// coordSys           Input coordinate system A5 - TMDAT/TMEPO: Epoch, MMB50/MMJ2K: J2000 (in-Character[5])
// returns 0 if the SpVec is successfully updated, non-0 if there is an error
typedef int (STDCALL *fnPtrSpVecUpdateSatFrFields)(__int64 satKey, double pos[3], double vel[3], char secClass, char satName[8], int revNum, int elsetNum, double bterm, double agom, double ogParm, char coordSys[5]);


// Retrieves the value of a specific field of an SpVec
// 
// The table below shows the values for the xf_SpVec parameter:
// 
// table
// 
// Index
// Index Interpretation
// 
//  1-3First 3 elements of 1P
//  4-6Second 3 elements of 1P
//  7Security classification
//  9Satellite number
// 10Satellite common name
// 11Epoch date
// 12Epoch revolution number
// 13Elset number
// 14Ballistic coefficient
// 15Radiation pressure coefficient
// 16Outgassing parameter
// 17Input coordinate system
// 
// satKey             The satellite's unique key (in-Long)
// xf_SpVec           Predefined number specifying which field to set (in-Integer)
// valueStr           A string to contain the value of the requested field (out-Character[512])
// returns 0 if the SpVec is successfully retrieved, non-0 if there is an error
typedef int (STDCALL *fnPtrSpVecGetField)(__int64 satKey, int xf_SpVec, char valueStr[512]);


// Updates the value of a field of an SpVec
// See SpVecGetField for a description of the xf_SpVec parameter.  satNum (9) and epoch date (11) cannot be altered.
// The set value type was intentionally chosen as a character string because it allows the users to set value for different data types.
// satKey             The satellite's unique key (in-Long)
// xf_SpVec           Predefined number specifying which field to set (in-Integer)
// valueStr           The new value of the specified field, expressed as a string (in-Character[512])
// returns 0 if the SpVec is successfully updated, non-0 if there is an error
typedef int (STDCALL *fnPtrSpVecSetField)(__int64 satKey, int xf_SpVec, char valueStr[512]);


// Retrieves all of the data for an SpVec satellite in a single function call
// satKey             The satellite's unique key (in-Long)
// pos                position vector (km) (out-Double[3])
// vel                velocity vector (m/s) (out-Double[3])
// secClass           Security classification U: unclass, C: confidential, S: Secret (out-Character)
// satNum             Satellite number (out-Integer)
// satName            Satellite name A8 (out-Character[8])
// epochDtg           Satellite's epoch A17 (YYYYDDDHHMMSS.SSS) (out-Character[17])
// revNum             Revolution number (out-Integer)
// elsetNum           Element set number (out-Integer)
// bterm              Bterm m^2/kg (out-Double)
// agom               Agom  m^2/kg (out-Double)
// ogParm             Outgassing parameter (km/s^2) (out-Double)
// coordSys           Input coordinate system A5 - TMDAT/TMEPO: Epoch, MMB50/MMJ2K: J2000 (out-Character[5])
// returns 0 if the SpVec is successfully retrieved, non-0 if there is an error
typedef int (STDCALL *fnPtrSpVecGetAllFields)(__int64 satKey, double pos[3], double vel[3], char* secClass, int* satNum, char satName[8], char epochDtg[17], int* revNum, int* elsetNum, double* bterm, double* agom, double* ogParm, char coordSys[5]);


// Retrieves all of the data for an SpVec satellite in a single function call
// line1              the first input line of a 1P/2P card (in-Character[512])
// line2              the second input line of a 1P/2P card (in-Character[512])
// pos                position vector (km) (out-Double[3])
// vel                velocity vector (m/s) (out-Double[3])
// secClass           Security classification U: unclass, C: confidential, S: Secret (out-Character)
// satNum             Satellite number (out-Integer)
// satName            Satellite name A8 (out-Character[8])
// epochDtg           Satellite's epoch A17 (YYYYDDDHHMMSS.SSS) (out-Character[17])
// revNum             Revolution number (out-Integer)
// elsetNum           Element set number (out-Integer)
// bterm              Bterm m^2/kg (out-Double)
// agom               Agom  m^2/kg (out-Double)
// ogParm             Outgassing parameter (km/s^2) (out-Double)
// coordSys           Input coordinate system A5 - TMDAT/TMEPO: Epoch, MMB50/MMJ2K: J2000 (out-Character[5])
// returns 0 if the SpVec data is successfully parsed, non-0 if there is an error
typedef int (STDCALL *fnPtrSpVecParse)(char line1[512], char line2[512], double pos[3], double vel[3], char* secClass, int* satNum, char satName[8], char epochDtg[17], int* revNum, int* elsetNum, double* bterm, double* agom, double* ogParm, char coordSys[5]);


// Parses SPVEC data from the input first and second lines of an 1P/2P state vector and store that data back into the output parameters.
// This function only parses data from the input SPVEC but DOES NOT load/add the input SPVEC to memory.
// line1              The first line of the two line element set. (in-Character[512])
// line2              The second line of the two line element set (in-Character[512])
// xa_spVec           Array containing SPVEC's numerical fields (see XA_SPVEC_?) (out-Double[512])
// xs_spVec           Output string that contains all SPVEC's text fields (see XS_SPVEC_?) (out-Character[512])
// returns 0 if the SPVEC is parsed successfully, non-0 if there is an error.
typedef int (STDCALL *fnPtrSpVecLinesToArray)(char line1[512], char line2[512], double xa_spVec[512], char xs_spVec[512]);


// Returns the first and second lines of the 1P/2P representation of an SpVec
// satKey             The satellite's unique key (in-Long)
// line1              The resulting first line of a 1P/2P card (out-Character[512])
// line2              The resulting second line of a 1P/2P card (out-Character[512])
// returns 0 if successful, non-0 on error
typedef int (STDCALL *fnPtrSpVecGetLines)(__int64 satKey, char line1[512], char line2[512]);


// Constructs 1P/2P cards from individually provided SpVec data fields
// Returned line1 and line2 are empty if the function fails to construct the lines as requested.
// pos                position vector (km) (in-Double[3])
// vel                velocity vector (m/s) (in-Double[3])
// secClass           Security classification U: unclass, C: confidential, S: Secret (in-Character)
// satNum             Satellite number (in-Integer)
// satName            Satellite name A8 (in-Character[8])
// epochDtg           Satellite's epoch A17 (YYYYDDDHHMMSS.SSS) (in-Character[17])
// revNum             Revolution number (in-Integer)
// elsetNum           Element set number (in-Integer)
// bterm              Bterm m^2/kg (in-Double)
// agom               Agom  m^2/kg (in-Double)
// ogParm             Outgassing parameter (km/s^2) (in-Double)
// coordSys           Input coordinate system A5 - TMDAT/TMEPO: Epoch, MMB50/MMJ2K: J2000 (in-Character[5])
// line1              The resulting first line of a 1P/2P card (out-Character[512])
// line2              The resulting second line of a 1P/2P card (out-Character[512])
typedef void (STDCALL *fnPtrSpVecFieldsToLines)(double pos[3], double vel[3], char secClass, int satNum, char satName[8], char epochDtg[17], int revNum, int elsetNum, double bterm, double agom, double ogParm, char coordSys[5], char line1[512], char line2[512]);


// Constructs 1P/2P cards from SPVEC data stored in the input arrays.
// This function only parses data from the input data but DOES NOT load/add the SPVEC to memory.
// Returned line1 and line2 will be empty if the function fails to construct the lines as requested.
// xa_spVec           Array containing SPVEC's numerical fields (see XA_SPVEC_?) (in-Double[512])
// xs_spVec           Input string that contains all SPVEC's text fields (see XS_SPVEC_?) (in-Character[512])
// line1              Returned first line of an SPVEC. (out-Character[512])
// line2              Returned second line of an SPVEC (out-Character[512])
typedef void (STDCALL *fnPtrSpVecArrayToLines)(double xa_spVec[512], char xs_spVec[512], char line1[512], char line2[512]);


// Returns the first satKey from the currently loaded set of SpVec's that contains the specified satellite number
// This function is useful when SpVec DLL is used in applications that requires only one record (one SpVec entry) for one satellite and the applications refer to that SpVec by its satellite number. However, the Standardized Astrodynamic Algorithms library is only working with satKeys, this function helps to return the associated satKey of that satellite.
// satNum             The input satellite number (in-Integer)
// returns The satellite's unique key
typedef __int64 (STDCALL *fnPtrSpVecGetSatKey)(int satNum);


// This function is similar to SpVecGetSatKey but designed to be used in Matlab. 
// This function is useful when SpVec DLL is used in applications that requires only one record (one SpVec entry) for one satellite and the applications refer to that SpVec by its satellite number. However, the Standardized Astrodynamic Algorithms library is only working with satKeys, this function helps to return the associated satKey of that satellite.
// satNum             The input satellite number (in-Integer)
// satKey             The satellite's unique key (out-Long)
typedef void (STDCALL *fnPtrSpVecGetSatKeyML)(int satNum, __int64* satKey);


// Computes a satKey from the input data
// This is the proper way to reconstruct a satKey from its fields. If the users use their own routine to do this, the computed satKey might be different.
// satNum             The input satellite number (in-Integer)
// epochDtg           [yy]yydddhhmmss.sss or [yy]yyddd.ddddddd or DTG15, DTG17, DTG20 (in-Character[20])
// returns The resulting satellite key
typedef __int64 (STDCALL *fnPtrSpVecFieldsToSatKey)(int satNum, char epochDtg[20]);


// This function is similar to SpVecFieldsToSatKey but designed to be used in Matlab. 
// This is the proper way to reconstruct a satKey from its fields. If the users use their own routine to do this, the computed satKey might be different.
// satNum             The input satellite number (in-Integer)
// epochDtg           [yy]yydddhhmmss.sss or [yy]yyddd.ddddddd or DTG15, DTG17, DTG20 (in-Character[20])
// satKey             The resulting satellite key (out-Long)
typedef void (STDCALL *fnPtrSpVecFieldsToSatKeyML)(int satNum, char epochDtg[20], __int64* satKey);


// Adds an SpVec using its individually provided field values
// xa_spVec           Array containing SPVEC's numerical fields (see XA_SPVEC_?) (in-Double[512])
// xs_spVec           Input string that contains all SPVEC's text fields (see XS_SPVEC_?) (in-Character[512])
// returns The satKey of the newly added SPVEC on success, a negative value on error.
typedef __int64 (STDCALL *fnPtrSpVecAddSatFrArray)(double xa_spVec[512], char xs_spVec[512]);


// Adds an SpVec using its individually provided field values
// xa_spVec           Array containing SPVEC's numerical fields (see XA_SPVEC_?) (in-Double[512])
// xs_spVec           Input string that contains all SPVEC's text fields (see XS_SPVEC_?) (in-Character[512])
// satKey             The satKey of the newly added SPVEC on success, a negative value on error. (out-Long)
typedef void (STDCALL *fnPtrSpVecAddSatFrArrayML)(double xa_spVec[512], char xs_spVec[512], __int64* satKey);


// Updates existing SPVEC data with the provided new data stored in the input parameters. Note: satNum, epoch string can't be updated.
// satKey             The satellite's unique key (in-Long)
// xa_spVec           Array containing SPVEC's numerical fields (see XA_SPVEC_?) (in-Double[512])
// xs_spVec           Input string that contains all SPVEC's text fields (see XS_SPVEC_?) (in-Character[512])
// returns 0 if the SPVEC is successfully updated, non-0 if there is an error.
typedef int (STDCALL *fnPtrSpVecUpdateSatFrArray)(__int64 satKey, double xa_spVec[512], char xs_spVec[512]);


// Retrieves SPVEC data and stored it in the passing parameters
// satKey             The satellite's unique key (in-Long)
// xa_spVec           Array containing SPVEC's numerical fields (see XA_SPVEC_?) (out-Double[512])
// xs_spVec           Output string that contains all SPVEC's text fields (see XS_SPVEC_?) (out-Character[512])
// returns 0 if all values are retrieved successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSpVecDataToArray)(__int64 satKey, double xa_spVec[512], char xs_spVec[512]);
  
  // Indexes of SPVEC data fields
  static const int  
     XF_SPVEC_POS1     =  1,      // X component of satellite's position (km)
     XF_SPVEC_POS2     =  2,      // Y component of satellite's position (km)
     XF_SPVEC_POS3     =  3,      // Z component of satellite's position (km)
     XF_SPVEC_VEL1     =  4,      // X component of satellite's velocity (m/s)
     XF_SPVEC_VEL2     =  5,      // Y component of satellite's velocity (m/s)
     XF_SPVEC_VEL3     =  6,      // Z component of satellite's velocity (m/s)
     XF_SPVEC_SECCLASS =  7,      // Security classification
     XF_SPVEC_SATNUM   =  9,      // Satellite number
     XF_SPVEC_SATNAME  = 10,      // Satellite common name
     XF_SPVEC_EPOCH    = 11,      // Epoch date
     XF_SPVEC_REVNUM   = 12,      // Epoch revolution number
     XF_SPVEC_ELSETNUM = 13,      // Elset number
     XF_SPVEC_BTERM    = 14,      // Ballistic coefficient (m^2/kg)
     XF_SPVEC_AGOM     = 15,      // Radiation pressure coefficient (m^2/kg)
     XF_SPVEC_OGPARM   = 16,      // Outgassing parameter (km/s^2)
     XF_SPVEC_INPCOORD = 17;      // Inpute coordinate system
     
     
  // Indexes of SPVEC numerical data in an array
  static const int  
     XA_SPVEC_SATNUM   =   0,      // Satellite number
     XA_SPVEC_EPOCH    =   1,      // Epoch date in days since 1950 UTC
     XA_SPVEC_REVNUM   =   2,      // Epoch revolution number
     XA_SPVEC_ELSETNUM =   3,      // Elset number
     XA_SPVEC_BTERM    =   4,      // Ballistic coefficient (m^2/kg)
     XA_SPVEC_AGOM     =   5,      // Radiation pressure coefficient (m^2/kg)
     XA_SPVEC_OGPARM   =   6,      // Outgassing parameter (km/s^2)
     XA_SPVEC_INPCOORD =   7,      // Inpute coordinate systemm, see SPVEC_INPCOORD_? for available options
  
     XA_SPVEC_POS1     =  20,      // X component of satellite's position (km)
     XA_SPVEC_POS2     =  21,      // Y component of satellite's position (km)
     XA_SPVEC_POS3     =  22,      // Z component of satellite's position (km)
     XA_SPVEC_VEL1     =  23,      // X component of satellite's velocity (m/s)
     XA_SPVEC_VEL2     =  24,      // Y component of satellite's velocity (m/s)
     XA_SPVEC_VEL3     =  25,      // Z component of satellite's velocity (m/s)
     
     XA_SPVEC_HASOWNCRL=  70,      // Flag to indicate SP vec has its own numerical integration control (vs global 4P settings)
     XA_SPVEC_GEOIDX   =  71,      // Geopotential model to use
     XA_SPVEC_BULGEFLG =  72,      // Earth gravity pertubations flag
     XA_SPVEC_DRAGFLG  =  73,      // Drag pertubations flag 
     XA_SPVEC_RADFLG   =  74,      // Radiation pressure pertubations flag
     XA_SPVEC_LUNSOLFLG=  75,      // Lunar/Solar pertubations flag
     XA_SPVEC_F10      =  76,      // F10 value
     XA_SPVEC_F10AVG   =  77,      // F10 average value
     XA_SPVEC_AP       =  78,      // Ap value
     XA_SPVEC_TRUNC    =  79,      // Geopotential truncation order/degree/zonals
     XA_SPVEC_CONVERG  =  80,      // Corrector step convergence criterion, exponent of 1/10, default = 10
     XA_SPVEC_OGFLG    =  81,      // Outgassing pertubations flag
     XA_SPVEC_TIDESFLG =  82,      // Solid earth and ocean tide pertubations flag
     XA_SPVEC_NTERMS   =  84,      // Nutation terms
     XA_SPVEC_REEVAL   =  85,      // Recompute pertubations at each corrector step
     XA_SPVEC_INTEGCTRL=  86,      // Variable of intergration control
     XA_SPVEC_VARSTEP  =  87,      // Variable step size control
     XA_SPVEC_INITSTEP =  88,      // Initial step size
     
     XA_SPVEC_RMS      =  99,      // weighted RM of last DC on the satellite 
     XA_SPVEC_COVELEMS = 100,      // the lower triangle portion of the full cov matrix (100-120: 6x6 covmtx, ..., 100-154: 10x10 covmtx)
     
     XA_SPVEC_SIZE     = 512;
     
  
  // Indexes of SPVEC text data in an array of chars
  static const int     
     XS_SPVEC_SECCLASS_1 =  0,      // Security classification
     XS_SPVEC_SATNAME_8  =  1,      // Satellite common name
     
     XS_SPVEC_SIZE       = 512;
  
  // SPVEC's text data fields - new convention (start index, string length)
  static const int     
     XS_SPVEC_SECCLASS_0_1 =  0,      // Security classification
     XS_SPVEC_SATNAME_1_8  =  1,      // Satellite common name
     
     XS_SPVEC_LENGTH     = 512;
  
     
  // Different input coordinate for SpVec
  static const int     
     SPVEC_INPCOORD_4P    =  0,      // Use input coordinate specified in 4P-card
     SPVEC_INPCOORD_TMDAT =  1,      // Input coordinate systems is coordinates of epoch
     SPVEC_INPCOORD_MMJ2K =  2;      // Input coordinate systems is coordinates of J2000
  
// SpVecDll's function pointers declaration
extern fnPtrSpVecInit                      SpVecInit;
extern fnPtrSpVecGetInfo                   SpVecGetInfo;
extern fnPtrSpVecLoadFile                  SpVecLoadFile;
extern fnPtrSpVecSaveFile                  SpVecSaveFile;
extern fnPtrSpVecRemoveSat                 SpVecRemoveSat;
extern fnPtrSpVecRemoveAllSats             SpVecRemoveAllSats;
extern fnPtrSpVecGetCount                  SpVecGetCount;
extern fnPtrSpVecGetLoaded                 SpVecGetLoaded;
extern fnPtrSpVecAddSatFrLines             SpVecAddSatFrLines;
extern fnPtrSpVecAddSatFrLinesML           SpVecAddSatFrLinesML;
extern fnPtrSpVecAddSatFrFields            SpVecAddSatFrFields;
extern fnPtrSpVecAddSatFrFieldsML          SpVecAddSatFrFieldsML;
extern fnPtrSpVecUpdateSatFrFields         SpVecUpdateSatFrFields;
extern fnPtrSpVecGetField                  SpVecGetField;
extern fnPtrSpVecSetField                  SpVecSetField;
extern fnPtrSpVecGetAllFields              SpVecGetAllFields;
extern fnPtrSpVecParse                     SpVecParse;
extern fnPtrSpVecLinesToArray              SpVecLinesToArray;
extern fnPtrSpVecGetLines                  SpVecGetLines;
extern fnPtrSpVecFieldsToLines             SpVecFieldsToLines;
extern fnPtrSpVecArrayToLines              SpVecArrayToLines;
extern fnPtrSpVecGetSatKey                 SpVecGetSatKey;
extern fnPtrSpVecGetSatKeyML               SpVecGetSatKeyML;
extern fnPtrSpVecFieldsToSatKey            SpVecFieldsToSatKey;
extern fnPtrSpVecFieldsToSatKeyML          SpVecFieldsToSatKeyML;
extern fnPtrSpVecAddSatFrArray             SpVecAddSatFrArray;
extern fnPtrSpVecAddSatFrArrayML           SpVecAddSatFrArrayML;
extern fnPtrSpVecUpdateSatFrArray          SpVecUpdateSatFrArray;
extern fnPtrSpVecDataToArray               SpVecDataToArray;



void LoadSpVecDll();
void FreeSpVecDll();




#endif
// ========================= End of auto generated code ==========================
