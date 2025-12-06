// This wrapper file was generated automatically by the GenDllWrappers program.

#ifndef OBSDLL_H
#define OBSDLL_H

#include "../services/DllUtils.h"

// Provide the path to the dll/so/dylib
#if defined (_WIN32) || defined (__CYGWIN__)
  #define ObsDll "Obs.dll"
#elif __APPLE__
  #define ObsDll "libobs.dylib"
#else
  #define ObsDll "libobs.so"
#endif


// Notes: This function has been deprecated since v9.0. 
// Initializes Obs DLL for use in the program
// apAddr             The handle that was returned from DllMainInit() (in-Long)
// returns 0 if Obs.dll is initialized successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrObsInit)(__int64 apAddr);


// Returns information about the current version of Obs DLL. 
// The information is placed in the string parameter passed in.
// infoStr            A string to hold the information about Obs.dll (out-Character[128])
typedef void (STDCALL *fnPtrObsGetInfo)(char infoStr[128]);


// Sets the year for transmission observation format (TTY) input files
// ttyYear            2 or 4 digits year (in-Integer)
typedef void (STDCALL *fnPtrObsSetTTYYear)(int ttyYear);


// Loads observation data from an input text file
// obsFile            The name of the file containing obs-related data (in-Character[512])
// returns 0 if the input file is read successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrObsLoadFile)(char obsFile[512]);


// Saves the currently loaded obs data to a file
// obsFile            The name of the file in which to save the loaded obs (in-Character[512])
// saveMode           Specifies whether to create a new file or append to an existing one (0 = create, 1= append) (in-Integer)
// obsForm            Specifies the mode in which to save the file (0 = B3 format, 1 = TTY, 2 = CSV) (in-Integer)
// returns 0 if the data is successfully saved to the file, non-0 if there is an error
typedef int (STDCALL *fnPtrObsSaveFile)(char obsFile[512], int saveMode, int obsForm);


// Removes an obs, represented by the obsKey, from the set of currently loaded observations
// obsKey             The observation's unique key (in-Long)
// returns 0 if the observation is successfully removed, non-0 if there is an error
typedef int (STDCALL *fnPtrObsRemove)(__int64 obsKey);


// Removes all currently loaded observations from memory
// returns 0 if all the loaded observations are removed successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrObsRemoveAll)();


// Returns the number of observations currently loaded
// returns the number of observations currently loaded
typedef int (STDCALL *fnPtrObsGetCount)();


// Retrieves all of the currently loaded obsKeys. These obsKeys can be used to access the internal data for the observations
// Sort options (order):
// (+/-)1 = (descending/ascending) time, sensor, obsType, elev
// (+/-)2 = (descending/ascending) time, elevation
// (+/-)3 = (descending/ascending) time, sensor, otype, el, satno
// (+/-)4 = (descending/ascending) sensor, satno, time, elev
// (+/-)5 = (descending/ascending) sensor, time, elevation
// (+/-)6 = (descending/ascending) sensor, satno, obsType, time, elev
// (+/-)7 = (descending/ascending) satno, time, sensor, otype, el
// (+/-)8 = (reversed/same)        order as obs were read
// 9 : as is in the tree
// order              Specifies the order in which the obsKeys should be returned (in-Integer)
// obsKeys            The array in which to store the obsKeys (out-Long[*])
typedef void (STDCALL *fnPtrObsGetLoaded)(int order, __int64 obsKeys[]);


// Loads a single observation-typed card
// card               Any single observation-typed card (B3, B3E, TTY, ...) but not OBSFIL= (in-Character[512])
// returns 0 if the input card is read successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrObsLoadCard)(char card[512]);


// Loads a one-line or two-line observation 
// card1              Any single observation-typed card (B3, B3E, TTY, ...) or Card #1 of TTY obs type 4, 7, 8, 9 (in-Character[512])
// card2              Card #2 of TTY obs type 4, 7, 8, 9 (in-Character[512])
// returns 0 if the input card1/card2 are read successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrObsLoadTwoCards)(char card1[512], char card2[512]);


// Adds an observation from a string in B3 observation format
// card               The input string in B3 observation format (in-Character[512])
// returns The obsKey of the newly added observation on success, a negative value on error
typedef __int64 (STDCALL *fnPtrObsAddFrB3Card)(char card[512]);


// Works like ObsAddFrB3Card but designed for Matlab
// card               The input string in B3 observation format (in-Character[512])
// obsKey             The obsKey of the newly added observation on success, a negative value on error (out-Long)
typedef void (STDCALL *fnPtrObsAddFrB3CardML)(char card[512], __int64* obsKey);


// Converts B3 format to csv format without loading B3 obs into memory
// card               The input string in B3 observation format (in-Character[512])
// csvLine            The output string in csv observation format (out-Character[512])
// returns 0 if the conversion is successful, non-0 if there is an error
typedef int (STDCALL *fnPtrObsB3ToCsv)(char card[512], char csvLine[512]);


// Converts CSV format to B3 format without loading CSV obs into memory
// csvLine            The input string in csv observation format (in-Character[512])
// newSatno           New satellite number to replace what's in CSV obs if desired (value of zero does not renumber) (in-Integer)
// card               The output string in B3 observation format (out-Character[512])
// returns 0 if the conversion is successful, non-0 if there is an error
typedef int (STDCALL *fnPtrObsCsvToB3)(char csvLine[512], int newSatno, char card[512]);


// Adds an observation from a TTY (1 line or 2 lines) observation format
// card1              Card #1 of a TTY obs (in-Character[512])
// card2              Card #2 of TTY obs type 4, 7, 8, 9 or an empty string for other TTY obs types (in-Character[512])
// returns The obsKey of the newly added observation on success, a negative value on error
typedef __int64 (STDCALL *fnPtrObsAddFrTTYCards)(char card1[512], char card2[512]);


// Works like ObsAddFrTTYCards but designed for Matlab
// card1              Card #1 of a TTY obs (in-Character[512])
// card2              Card #2 of TTY obs type 4, 7, 8, 9 or an empty string for other TTY obs types (in-Character[512])
// obsKey             The obsKey of the newly added observation on success, a negative value on error (out-Long)
typedef void (STDCALL *fnPtrObsAddFrTTYCardsML)(char card1[512], char card2[512], __int64* obsKey);


// Converts TTY format to CSV format without loading TTY obs into memory
// card1              Card #1 of a TTY obs (in-Character[512])
// card2              Card #2 of TTY obs type 4, 7, 8, 9 or an empty string for other TTY obs types (in-Character[512])
// csvLine            The obs in csv format (out-Character[512])
// returns 0 if the conversion is successful, non-0 if there is an error
typedef int (STDCALL *fnPtrObsTTYToCsv)(char card1[512], char card2[512], char csvLine[512]);


// Converts CSV format to TTY format without loading CSV obs into memory
// csvLine            The obs in csv format (in-Character[512])
// newSatno           New satellite number to replace what's in CSV obs if desired (value of zero does not renumber) (in-Integer)
// card1              Card #1 of a TTY obs (out-Character[512])
// card2              Card #2 of TTY obs type 4, 7, 8, 9 or an empty string for other TTY obs types (out-Character[512])
// returns 0 if the conversion is successful, non-0 if there is an error
typedef int (STDCALL *fnPtrObsCsvToTTY)(char csvLine[512], int newSatno, char card1[512], char card2[512]);


// Adds one observation using csv obs string 
// csvLine            Input csv obs string (in-Character[512])
// returns The obsKey of the newly added observation on success, a negative value on error
typedef __int64 (STDCALL *fnPtrObsAddFrCsv)(char csvLine[512]);


// Adds one observation using csv obs string - for MatLab
// csvLine            Input csv obs string (in-Character[512])
// obsKey             The obsKey of the newly added observation on success, a negative value on error (out-Long)
typedef void (STDCALL *fnPtrObsAddFrCsvML)(char csvLine[512], __int64* obsKey);


// Adds one observation using RF TDOA/FDOA obs string 
// Notes: Sensors listed in the input RF obs have to be loaded prior to this call
// rfObsLine          Input RF obs string (in-Character[512])
// returns The obsKey of the newly added observation on success, a negative value on error
typedef __int64 (STDCALL *fnPtrObsAddFrRfCard)(char rfObsLine[512]);


// Adds one observation using RF TDOA/FDOA obs string - for MatLab
// rfObsLine          Input RF obs string (in-Character[512])
// obsKey             The obsKey of the newly added observation on success, a negative value on error (out-Long)
typedef void (STDCALL *fnPtrObsAddFrRfCardML)(char rfObsLine[512], __int64* obsKey);


// Adds one observation using its input data. Depending on the observation type, some input data might be unavailable and left blank
// secClass           security classification (in-Character)
// satNum             satellite number (in-Integer)
// senNum             sensor number (in-Integer)
// obsTimeDs50utc     observation time in days since 1950 UTC (in-Double)
// elOrDec            elevation or declination (deg) (in-Double)
// azOrRA             azimuth or right-ascension (deg) (in-Double)
// slantRange         range (km) (in-Double)
// rangeRate          range rate (km/s), or equinox indicator (0-3) for obs type 5/9 (in-Double)
// elRate             elevation rate (deg/s) (in-Double)
// azRate             azimuth rate (deg/s) (in-Double)
// rangeAccel         range acceleration (km/s^2) (in-Double)
// obsType            observation type (in-Character)
// trackInd           track position indicator (3=start track ob, 4=in track ob, 5=end track ob) (in-Integer)
// astat              association status assigned by SPADOC (in-Integer)
// siteTag            original satellite number (in-Integer)
// spadocTag          SPADOC-asssigned tag number (in-Integer)
// pos                position XYZ (km) (ECI or EFG) (in-Double[3])
// vel                velocity XYZ (km/s) (ECI or EFG) (in-Double[3])
// extArr             extra array - future use (in-Double[128])
// returns The obsKey of the newly added observation on success, a negative value on error
typedef __int64 (STDCALL *fnPtrObsAddFrFields)(char secClass, int satNum, int senNum, double obsTimeDs50utc, double elOrDec, double azOrRA, double slantRange, double rangeRate, double elRate, double azRate, double rangeAccel, char obsType, int trackInd, int astat, int siteTag, int spadocTag, double pos[3], double vel[3], double extArr[128]);


// Works like ObsAddFrFields but designed for Matlab
// secClass           security classification (in-Character)
// satNum             satellite number (in-Integer)
// senNum             sensor number (in-Integer)
// obsTimeDs50utc     observation time in days since 1950 UTC (in-Double)
// elOrDec            elevation or declination (deg) (in-Double)
// azOrRA             azimuth or right-ascension (deg) (in-Double)
// slantRange         range (km) (in-Double)
// rangeRate          range rate (km/s), or equinox indicator (0-3) for obs type 5/9 (in-Double)
// elRate             elevation rate (deg/s) (in-Double)
// azRate             azimuth rate (deg/s) (in-Double)
// rangeAccel         range acceleration (km/s^2) (in-Double)
// obsType            observation type (in-Character)
// trackInd           track position indicator (3=start track ob, 4=in track ob, 5=end track ob) (in-Integer)
// astat              association status assigned by SPADOC (in-Integer)
// siteTag            original satellite number (in-Integer)
// spadocTag          SPADOC-asssigned tag number (in-Integer)
// pos                position XYZ (km) (ECI or EFG) (in-Double[3])
// vel                velocity XYZ (km/s) (ECI or EFG) (in-Double[3])
// extArr             extra array - future use (in-Double[128])
// obsKey             The obsKey of the newly added observation on success, a negative value on error (out-Long)
typedef void (STDCALL *fnPtrObsAddFrFieldsML)(char secClass, int satNum, int senNum, double obsTimeDs50utc, double elOrDec, double azOrRA, double slantRange, double rangeRate, double elRate, double azRate, double rangeAccel, char obsType, int trackInd, int astat, int siteTag, int spadocTag, double pos[3], double vel[3], double extArr[128], __int64* obsKey);


// Adds one observation using its input data stored in an array. Depending on the observation type, some input data might be unavailable and left blank
// xa_obs             Array containing observation data (see XA_OBS_?) (in-Double[64])
// returns The obsKey of the newly added observation on success, a negative value on error
typedef __int64 (STDCALL *fnPtrObsAddFrArray)(double xa_obs[64]);


// Works like ObsAddFrArray but designed for Matlab
// xa_obs             Array containing observation data (see XA_OBS_?) (in-Double[64])
// obsKey             The obsKey of the newly added observation on success, a negative value on error (out-Long)
typedef void (STDCALL *fnPtrObsAddFrArrayML)(double xa_obs[64], __int64* obsKey);


// Retrieves all observation data in a single function call. Depending on the observation type, some input data might be unavailable
// obsKey             The unique key of the requested observation (in-Long)
// secClass           security classification (out-Character)
// satNum             satellite number (out-Integer)
// senNum             sensor number (out-Integer)
// obsTimeDs50utc     observation time in days since 1950 UTC (out-Double)
// elOrDec            elevation or declination (deg) (out-Double)
// azOrRA             azimuth or right-ascension (deg) (out-Double)
// slantRange         range (km) (out-Double)
// rangeRate          range rate (km/s) (out-Double)
// elRate             elevation rate (deg/s) (out-Double)
// azRate             azimuth rate (deg/s) (out-Double)
// rangeAccel         range acceleration (km/s^2) (out-Double)
// obsType            observation type (out-Character)
// trackInd           track position indicator (3=start track ob, 4=in track ob, 5=end track ob) (out-Integer)
// astat              association status assigned by SPADOC (out-Integer)
// siteTag            original satellite number (out-Integer)
// spadocTag          SPADOC-asssigned tag number (out-Integer)
// pos                position XYZ (km) (ECI or EFG) (out-Double[3])
// vel                velocity XYZ (km/s) (ECI or EFG) (out-Double[3])
// extArr             extra array - future use (out-Double[128])
// returns 0 if all values are retrieved successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrObsGetAllFields)(__int64 obsKey, char* secClass, int* satNum, int* senNum, double* obsTimeDs50utc, double* elOrDec, double* azOrRA, double* slantRange, double* rangeRate, double* elRate, double* azRate, double* rangeAccel, char* obsType, int* trackInd, int* astat, int* siteTag, int* spadocTag, double pos[3], double vel[3], double extArr[128]);


// Retrieves observation data and stored it in the passing array. Depending on the observation type, some data fields might be unavailable
// See ObsGetField for description of xa_obs elements
// obsKey             The unique key of the requested observation (in-Long)
// xa_obs             The array containing observation data (see XA_OBS_?) (out-Double[64])
// returns 0 if all values are retrieved successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrObsDataToArray)(__int64 obsKey, double xa_obs[64]);


// Updates existing observation data with the provided new data
// obsKey             The unique key of the requested observation (in-Long)
// secClass           security classification (in-Character)
// elOrDec            elevation or declination (deg) (in-Double)
// azOrRA             azimuth or right-ascension (deg) (in-Double)
// slantRange         range (km) (in-Double)
// rangeRate          range rate (km/s), or equinox indicator (0-3) for obs type 5/9 (in-Double)
// elRate             elevation rate (deg/s) (in-Double)
// azRate             azimuth rate (deg/s) (in-Double)
// rangeAccel         range acceleration (km/s^2) (in-Double)
// obsType            observation type (in-Character)
// trackInd           track position indicator (3=start track ob, 4=in track ob, 5=end track obs) (in-Integer)
// astat              association status assigned by SPADOC (in-Integer)
// siteTag            original satellite number (in-Integer)
// spadocTag          SPADOC-asssigned tag number (in-Integer)
// pos                position XYZ (km) (ECI or EFG) (in-Double[3])
// vel                velocity XYZ (km/s) (ECI or EFG) (in-Double[3])
// extArr             extra array - future use (in-Double[128])
// returns 0 if the requested observation is successfully updated, non-0 if there is an error
typedef int (STDCALL *fnPtrObsUpdateFrFields)(__int64 obsKey, char secClass, double elOrDec, double azOrRA, double slantRange, double rangeRate, double elRate, double azRate, double rangeAccel, char obsType, int trackInd, int astat, int siteTag, int spadocTag, double pos[3], double vel[3], double extArr[128]);


// Retrieves the value of a specific field of an observation
// obsKey             The observation's unique key (in-Long)
// xf_Obs             The predefined number specifying which field to retrieve (see XF_OBS_?) (in-Integer)
// strValue           A string to contain the value of the requested field (out-Character[512])
// returns 0 if the observation data is successfully retrieved, non-0 if there is an error
typedef int (STDCALL *fnPtrObsGetField)(__int64 obsKey, int xf_Obs, char strValue[512]);


// Updates the value of a field of an observation
// See ObsGetField for a description of the xf_Obs parameter.
// Satellite number, sensor number, and observation time are not allowed to be updated.
// obsKey             The observation's unique key (in-Long)
// xf_Obs             The predefined number specifying which field to update (see XF_OBS_?) (in-Integer)
// strValue           The new value of the specified field, expressed as a string (in-Character[512])
// returns 0 if the observation is successfully updated, non-0 if there is an error
typedef int (STDCALL *fnPtrObsSetField)(__int64 obsKey, int xf_Obs, char strValue[512]);


// Returns observation in B3-card string
// obsKey             The observation's unique key (in-Long)
// b3Card             A string to hold the B3 observation format (out-Character[512])
// returns 0 if successful, non-0 on error
typedef int (STDCALL *fnPtrObsGetB3Card)(__int64 obsKey, char b3Card[512]);


// Returns observation in TTY-card string
// obsKey             The observation's unique key (in-Long)
// ttyCard1           first line of a TTY card (out-Character[512])
// ttyCard2           second line of a TTY card (might be unavailable for certain obs type) (out-Character[512])
// returns 0 if successful, non-0 on error
typedef int (STDCALL *fnPtrObsGetTTYCard)(__int64 obsKey, char ttyCard1[512], char ttyCard2[512]);


// Returns observation in CSV-format string
// obsKey             The observation's unique key (in-Long)
// csvline            A string to hold the CSV observation format (out-Character[512])
// returns 0 if successful, non-0 on error
typedef int (STDCALL *fnPtrObsGetCsv)(__int64 obsKey, char csvline[512]);


// Returns observation in RF obs format, a string 
// obsKey             The observation's unique key (in-Long)
// rfCard             A string to hold the Rf observation format (out-Character[512])
// returns 0 if successful, non-0 on error
typedef int (STDCALL *fnPtrObsGetRfCard)(__int64 obsKey, char rfCard[512]);


// Constructs a B3-card string from the input observation data fields
// secClass           security classification (in-Character)
// satNum             satellite number (in-Integer)
// senNum             sensor number (in-Integer)
// obsTimeDs50utc     observation time in days since 1950 UTC (in-Double)
// elOrDec            elevation or declination (deg) (in-Double)
// azOrRA             azimuth or right-ascension (deg) (in-Double)
// slantRange         range (km) (in-Double)
// rangeRate          range rate (km/s), or equinox indicator (0-3) for obs type 5/9 (in-Double)
// elRate             elevation rate (deg/s) (in-Double)
// azRate             azimuth rate (deg/s) (in-Double)
// rangeAccel         range acceleration (km/s^2) (in-Double)
// obsType            observation type (in-Character)
// trackInd           track position indicator (3=start track ob, 4=in track ob, 5=end track ob) (in-Integer)
// astat              association status assigned by SPADOC (in-Integer)
// siteTag            original satellite number (in-Integer)
// spadocTag          SPADOC-asssigned tag number (in-Integer)
// pos                position XYZ (km) (ECI or EFG) (in-Double[3])
// b3Card             A string to hold the B3 observation format (out-Character[512])
typedef void (STDCALL *fnPtrObsFieldsToB3Card)(char secClass, int satNum, int senNum, double obsTimeDs50utc, double elOrDec, double azOrRA, double slantRange, double rangeRate, double elRate, double azRate, double rangeAccel, char obsType, int trackInd, int astat, int siteTag, int spadocTag, double pos[3], char b3Card[512]);


// Constructs a csv string from the input observation data fields
// secClass           security classification (in-Character)
// satNum             satellite number (in-Integer)
// senNum             sensor number (in-Integer)
// obsTimeDs50utc     observation time in days since 1950 UTC (in-Double)
// elOrDec            elevation or declination (deg) (in-Double)
// azOrRA             azimuth or right-ascension (deg) (in-Double)
// slantRange         range (km) (in-Double)
// rangeRate          range rate (km/s), or equinox indicator (0-3) for obs type 5/9 (in-Double)
// elRate             elevation rate (deg/s) (in-Double)
// azRate             azimuth rate (deg/s) (in-Double)
// rangeAccel         range acceleration (km/s^2) (in-Double)
// obsType            observation type (in-Character)
// trackInd           track position indicator (3=start track ob, 4=in track ob, 5=end track ob) (in-Integer)
// astat              association status assigned by SPADOC (in-Integer)
// siteTag            original satellite number (in-Integer)
// spadocTag          SPADOC-asssigned tag number (in-Integer)
// pos                position XYZ (km) (ECI or EFG) (in-Double[3])
// csvLine            A string to hold the csv observation format (out-Character[512])
typedef void (STDCALL *fnPtrObsFieldsToCsv)(char secClass, int satNum, int senNum, double obsTimeDs50utc, double elOrDec, double azOrRA, double slantRange, double rangeRate, double elRate, double azRate, double rangeAccel, char obsType, int trackInd, int astat, int siteTag, int spadocTag, double pos[3], char csvLine[512]);


// Constructs a TTY-card string from the input observation data fields
// secClass           security classification (in-Character)
// satNum             satellite number (in-Integer)
// senNum             sensor number (in-Integer)
// obsTimeDs50utc     observation time in days since 1950 UTC (in-Double)
// elOrDec            elevation or declination (deg) (in-Double)
// azOrRA             azimuth or right-ascension (deg) (in-Double)
// slantRange         range (km) (in-Double)
// rangeRate          range rate (km/s), or equinox indicator (0-3) for obs type 5/9 (in-Double)
// elRate             elevation rate (deg/s) (in-Double)
// azRate             azimuth rate (deg/s) (in-Double)
// rangeAccel         range acceleration (km/s^2) (in-Double)
// obsType            observation type (in-Character)
// pos                position XYZ (km) (ECI or EFG) (in-Double[3])
// ttyCard1           first line of a TTY card (out-Character[512])
// ttyCard2           second line of a TTY card (might be unavailable for certain obs type) (out-Character[512])
typedef void (STDCALL *fnPtrObsFieldsToTTYCard)(char secClass, int satNum, int senNum, double obsTimeDs50utc, double elOrDec, double azOrRA, double slantRange, double rangeRate, double elRate, double azRate, double rangeAccel, char obsType, double pos[3], char ttyCard1[512], char ttyCard2[512]);


// Computes an obsKey from individually provided fields
// satNum             input satellite's number (in-Integer)
// senNum             input sensor's number (in-Integer)
// obsTimeDs50utc     input observation time in days since 1950, UTC (in-Double)
// returns The newly created observation Key
typedef __int64 (STDCALL *fnPtrObsFieldsToObsKey)(int satNum, int senNum, double obsTimeDs50utc);


// Works like ObsFieldsToObsKey but designed for Matlab
// satNum             input satellite's number (in-Integer)
// senNum             input sensor's number (in-Integer)
// obsTimeDs50utc     input observation time in days since 1950, UTC (in-Double)
// obsKey             The newly created observation Key (out-Long)
typedef void (STDCALL *fnPtrObsFieldsToObsKeyML)(int satNum, int senNum, double obsTimeDs50utc, __int64* obsKey);


// Parses observation data from a B3-card (or B3E) string / one-line TTY / or CSV - Converts obs data to TEME of Date if neccessary
// b3ObsCard          input observation-typed string (in-Character[512])
// secClass           security classification (out-Character)
// satNum             satellite number (out-Integer)
// senNum             sensor number (out-Integer)
// obsTimeDs50utc     observation time in days since 1950 UTC (out-Double)
// elOrDec            elevation or declination (deg) (out-Double)
// azOrRA             azimuth or right-ascension (deg) (out-Double)
// slantRange         range (km) (out-Double)
// rangeRate          range rate (km/s) (out-Double)
// elRate             elevation rate (deg/s) (out-Double)
// azRate             azimuth rate (deg/s) (out-Double)
// rangeAccel         range acceleration (km/s^2) (out-Double)
// obsType            observation type (out-Character)
// trackInd           track position indicator (3=start track ob, 4=in track ob, 5=end track ob) (out-Integer)
// astat              association status assigned by SPADOC (out-Integer)
// siteTag            original satellite number (out-Integer)
// spadocTag          SPADOC-asssigned tag number (out-Integer)
// pos                position XYZ (km) (ECI or EFG) (out-Double[3])
// returns 0 if the data is successfully parsed, non-0 if there is an error
typedef int (STDCALL *fnPtrObsB3Parse)(char b3ObsCard[512], char* secClass, int* satNum, int* senNum, double* obsTimeDs50utc, double* elOrDec, double* azOrRA, double* slantRange, double* rangeRate, double* elRate, double* azRate, double* rangeAccel, char* obsType, int* trackInd, int* astat, int* siteTag, int* spadocTag, double pos[3]);


// Parses any observation data format (B3-card (or B3E) string / one or two line TTY / CSV / RF obs - No conversion takes place
// line1              input observation string 1 (B3/B3E/line 1 TTY/CSV) (in-Character[512])
// line2              input observation string 2 (line 2 of two-line TTY) (in-Character[512])
// xa_obs             The array containing observation data (see XA_OBS_?) (out-Double[64])
// returns 0 if the data is successfully parsed, non-0 if there is an error
typedef int (STDCALL *fnPtrObsParse)(char line1[512], char line2[512], double xa_obs[64]);


// Loads observation data from an input text file and group them together in the specified groupd id (gid).
// This allows the users to easily manage (load/retrieve/remove/save) a group of observations using the group id (gid)
// obsFile            The name of the file containing obs-related data (in-Character[512])
// gid                user specified group id (in-Integer)
// returns 0 if the input file is read successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrObsLoadFileGID)(char obsFile[512], int gid);


// Saves the currently loaded obs data belong to the specified group id (gid) to a file 
// obsFile            The name of the file in which to save the settings (in-Character[512])
// gid                Group ID number (in-Integer)
// saveMode           Specifies whether to create a new file or append to an existing one (0 = create, 1= append) (in-Integer)
// obsForm            Specifies the obs format in which to save the file (0 = B3 format, 1 = TTY, 2 = CSV) (in-Integer)
// returns 0 if the data is successfully saved to the file, non-0 if there is an error
typedef int (STDCALL *fnPtrObsSaveFileGID)(char obsFile[512], int gid, int saveMode, int obsForm);


// Removes all observations belong to the specified group id (gid) from the set of currently loaded observations
// gid                Group ID number (in-Integer)
// returns 0 if the observations are successfully removed, non-0 if there is an error
typedef int (STDCALL *fnPtrObsRemoveGID)(int gid);


// Returns the number of observations currently loaded that have the same gid
// gid                Group ID number (in-Integer)
// returns The number of observations currently loaded that have the same group id
typedef int (STDCALL *fnPtrObsGetCountGID)(int gid);


// Retrieves all of the currently loaded obsKeys that have the same gid. These obsKeys can be used to access the internal data for the observations
// Sort options (order):
// (+/-)1 = (descending/ascending) time, sensor, obsType, elev
// (+/-)2 = (descending/ascending) time, elevation
// (+/-)3 = (descending/ascending) time, sensor, otype, el, satno
// (+/-)4 = (descending/ascending) sensor, satno, time, elev
// (+/-)5 = (descending/ascending) sensor, time, elevation
// (+/-)6 = (descending/ascending) sensor, satno, obsType, time, elev
// (+/-)7 = (descending/ascending) satno, time, sensor, otype, el
// (+/-)8 = (reversed/same)        order as obs were read
// 9 : as is in the tree
// gid                Group ID number (in-Integer)
// order              Specifies the order in which the obsKeys should be returned (in-Integer)
// obsKeys            The array in which to store the obsKeys (out-Long[*])
typedef void (STDCALL *fnPtrObsGetLoadedGID)(int gid, int order, __int64 obsKeys[]);


// Converts obs type from character to integer
// obsTypeChar        The input obs type character (in-Character)
// returns The resulting obs type integer
typedef int (STDCALL *fnPtrObsTypeCToI)(char obsTypeChar);


// Converts obs type from integer to character
// obsTypeInt         The input obs type integer (in-Integer)
// returns The resulting obs type character
typedef char (STDCALL *fnPtrObsTypeIToC)(int obsTypeInt);


// Resets obs selection settings
typedef void (STDCALL *fnPtrObsResetSelObs)();


// Computes other states of the input observation
// 
// The table below indicates which index values correspond to which fields in the xa_obState array.
// 
// table
// 
// Index
// Index Interpretation
// 
// 0Satellite number
// 1Sensor number
// 2Observation time in DS50UTC
// 10Position X/ECI (km)
// 11Position Y/ECI (km)
// 12Position Z/ECI (km)
// 13Velocity X/ECI (km/s)
// 14Velocity Y/ECI (km/s)
// 15Velocity Z/ECI (km/s)
// 16Geodetic latitude (deg)
// 17Geodetic longitude (deg)
// 18Geodetic height (km)
// 19Position X/EFG (km)
// 20Position Y/EFG (km)
// 21Position Z/EFG (km)
// 
// obsKey             The observation's unique key (in-Long)
// range_km           Use this default range (km) for angle only obs (in-Double)
// xa_obState         Data derived from the obs data (see XA_OBSTATE_?) (out-Double[64])
// returns 0 if the observation states are successfully computed
typedef int (STDCALL *fnPtrObsGetStates)(__int64 obsKey, double range_km, double xa_obState[64]);


// Computes observation states from the observation data
// See ObsGetStates for a list of the values for the xa_obState parameter.
// xa_obs             Array containing observation data (see XA_OBS_?) (in-Double[64])
// xa_obState         Data derived from the obs data (see XA_OBSTATE_?) (out-Double[64])
// returns 0 if the observation states are successfully computed
typedef int (STDCALL *fnPtrObsDataToStates)(double xa_obs[64], double xa_obState[64]);


// Reconstructs obs string (B3-card/one or two line TTY/CSV) from obs data in the input array xa_obs
// xa_obs             The array containing observation data (see XA_OBS_?) (in-Double[64])
// obsForm            Desired obs string format (B3 = 0, TTY=1, CSV=2) (in-Integer)
// line1              output observation string 1 (B3/B3E/line 1 TTY/CSV) (out-Character[512])
// line2              output observation string 2 (line 2 of two-line TTY if obsForm = 1) (out-Character[512])
// returns 0 if the data is successfully , non-0 if there is an error
typedef int (STDCALL *fnPtrObsArrToLines)(double xa_obs[64], int obsForm, char line1[512], char line2[512]);


// Sets OBS key mode
// This mode can also be turned on if the user loads an input text file that includes this line - "AS_DMA_OBS_ON" -
// and is currently calling any of these methods: DllMainLoadFile(), or ObsLoadFile()
// obs_keyMode        Desired obs key mode (see OBS_KEYMODE_?) (in-Integer)
// returns 0 if the set is successful, non-0 if there is an error.
typedef int (STDCALL *fnPtrSetObsKeyMode)(int obs_keyMode);


// Gets current OBS key mode
// returns Current obs key mode (see OBS_KEYMODE_?)
typedef int (STDCALL *fnPtrGetObsKeyMode)();


// Returs the satellite number associated with the input obsKey
// obsKey             The observation's unique key (in-Long)
// returns The satellite number associated with the input obsKey (satNum = -1 if obsKey doesn't exist)
typedef int (STDCALL *fnPtrSatNumFrObsKey)(__int64 obsKey);


// Returs the sensor number associated with the input obsKey
// obsKey             The observation's unique key (in-Long)
// returns The satellite number associated with the input obsKey (senNum = -1 if obsKey doesn't exist)
typedef int (STDCALL *fnPtrSenNumFrObsKey)(__int64 obsKey);


// Retrieves only obs that match the selection criteria
// xa_selob           Obs secletion criteria (see XA_SELOB_?) (in-Double[128])
// order              Specifies the order in which the obsKeys should be returned (in-Integer)
// numMatchedObss     Number of obs that match the obs selection criteria (out-Integer)
// obsKeys            The array in which to store the matching obs' obsKey - make sure the array is big enough to store all the returning obsKeys (<= ObsGetCount()) (out-Long[*])
typedef void (STDCALL *fnPtrObsGetSelected)(double xa_selob[128], int order, int* numMatchedObss, __int64 obsKeys[]);
  
  // Equinox indicator
  static const int  
     EQUINOX_OBSTIME = 0,       // time of observation
     EQUINOX_OBSYEAR = 1,       // time @ 0 Jan Year of Date
     EQUINOX_J2K     = 2,       // J2000
     EQUINOX_B1950   = 3;       // B1950
     
  // Indexes for sorting ob
  // Sort options:
  // (+/-) 1 = (descending/ascending) time, sensor, obsType, elev
  // (+/-) 2 = (descending/ascending) time, elevation
  // (+/-) 3 = (descending/ascending) time, sensor, otype, el, satno
  // (+/-) 4 = (descending/ascending) sensor, satno, time, elev
  // (+/-) 5 = (descending/ascending) sensor, time, elevation
  // (+/-) 6 = (descending/ascending) sensor, satno, obsType, time, elev
  // (+/-) 7 = (descending/ascending) satno, time, sensor, otype, el
  // (+/-)10 = (descending/ascending) satno, sensor, time     
     
  static const int  
     SORT_TIMESENTYPEEL      =  1,   // sort order is time, sensor, obsType, elev (negative value for reverse order)
     SORT_TIMEEL             =  2,   // sort order is time, elevation (negative value for reverse order)
     SORT_TIMESENTYPEELSAT   =  3,   // sort order is time, sensor, otype, el, satno (negative value for reverse order)
     SORT_SENSATTIMEEL       =  4,   // sort order is sensor, satno, time, elev (negative value for reverse order)
     SORT_SENTIMEEL          =  5,   // sort order is sensor, time, elevation (negative value for reverse order)
     SORT_SENSATTYPETIMEEL   =  6,   // sort order is sensor, satno, obsType, time, elev (negative value for reverse order)
     SORT_SATTIMESENTYPEEL   =  7,   // sort order is satno, time, sensor, otype, el (negative value for reverse order)
     SORT_ORDERASREAD        =  8,   // sort order is the order of obs when they were loaded 
     SORT_SATSENTIME         = 10;   // sort order is satno, sensor, time (negative value for reverse order)    
     
     
  // Indexes of different obs file format
  static const int  
     OBSFORM_B3   = 0,   // B3 obs format
     OBSFORM_TTY  = 1,   // Transmission obs format
     OBSFORM_CSV  = 2,    // CSV obs format
     OBSFORM_RF   = 3;    // Radio Frequency (TDOA/FDOA) observations
     
  static const int BADOBSKEY = -1;   
  static const int DUPOBSKEY = 0;
  
  
  // Different key mode options for obsKey
  static const int  
     OBS_KEYMODE_NODUP  = 0,    // Default - duplicate obs can not be loaded in binary tree                           
     OBS_KEYMODE_DMA    = 1;    // Allow duplicate obs to be loaded and have direct memory access (DMA - no duplication check and no binary tree)   
  
  // CSV sigma type indicator
  static const int CSVSIGMATYPE = 7;
  
  // Indexes of Observation data fields
  static const int  
     XF_OBS_SECCLASS     =  1,     // security classification
     XF_OBS_SATNUM       =  2,     // satellite number
     XF_OBS_SENNUM       =  3,     // sensor number
     XF_OBS_DS50UTC      =  4,     // observation time in days since 1950 UTC
     XF_OBS_ELEVATION    =  5,     // elevation (deg)
     XF_OBS_DECLINATION  =  6,     // declination (deg)
     XF_OBS_AZIMUTH      =  7,     // azimuth (deg)
     XF_OBS_RA           =  8,     // right-ascension (deg)
     XF_OBS_RANGE        =  9,     // range (km)
     XF_OBS_RANGERATE    = 10,     // range rate (km/s)
     XF_OBS_ELRATE       = 11,     // elevation rate (deg/s)
     XF_OBS_AZRATE       = 12,     // azimuth rate (deg/s)
     XF_OBS_RANGEACCEL   = 13,     // range acceleration (km/s^2)
     XF_OBS_OBSTYPE      = 14,     // observation type
     XF_OBS_TRACKIND     = 15,     // track position indicator (3=start track ob, 4=in track ob, 5=end track ob)
     XF_OBS_ASTAT        = 16,     // association status assigned by SPADOC
     XF_OBS_SITETAG      = 17,     // original satellite number
     XF_OBS_SPADOCTAG    = 18,     // SPADOC-asssigned tag number
     XF_OBS_POSE         = 19,     // position X/EFG (km)
     XF_OBS_POSF         = 20,     // position Y/EFG (km)
     XF_OBS_POSG         = 21,     // position Z/EFG (km)
     XF_OBS_POSX         = 22,     // position X/ECI (km)
     XF_OBS_POSY         = 23,     // position Y/ECI (km)
     XF_OBS_POSZ         = 24,     // position Z/ECI (km)
  
     XF_OBS_RCS_PP       = 25,     // Principal Polarization RCS
     XF_OBS_RCS_OP       = 26,     // Orthogonal Polarization RCS
     XF_OBS_RCS_PPS      = 27,     // Principal Polarization RCS sigma
     XF_OBS_RCS_OPS      = 28,     // Orthogonal Polarization RCS sigma
     XF_OBS_SNR          = 29,     // Radar Signal to Noise Ratio
     XF_OBS_BORE_AZ      = 30,     // Azimuth of Boresite
     XF_OBS_BORE_EL      = 31,     // Elevation of Boresite
     XF_OBS_VISMAG       = 32,     // Apparent Visual magnitude
     XF_OBS_VISMAG_NORM  = 33,     // GEO Normalized Visual magnitude
     XF_OBS_SOL_PHASE    = 34,     // Solar Phase Angle
     XF_OBS_FRAME        = 35,     // Frame Number
     XF_OBS_ABERRATION   = 36,     // Aberration correction indicator (0=YES, 1=NO)
     XF_OBS_ASTAT_METHOD = 37;     // Either R" or T  ROTAS=General Perturbations, TRACK=Special Perturbations
  
  // Indexes of observation data in an array
  static const int  
     XA_OBS_SECCLASS     =  0,     // security classification, 1 = Unclassified, 2 = Confidential, 3 = Secret
     XA_OBS_SATNUM       =  1,     // satellite number
     XA_OBS_SENNUM       =  2,     // sensor number
     XA_OBS_DS50UTC      =  3,     // observation time in days since 1950 UTC
     XA_OBS_OBSTYPE      = 11,     // observation type   
     
     
     XA_OBS_ELORDEC      =  4,     // elevation (for ob type 1, 2, 3, 4, 8) or declination (for ob type 5, 9) (deg)
     XA_OBS_AZORRA       =  5,     // azimuth (for ob type 1, 2, 3, 4, 8) or right ascesion (for ob type 5, 9) (deg)
     XA_OBS_RANGE        =  6,     // range (km)
     XA_OBS_RANGERATE    =  7,     // range rate (km/s) for non-optical obs type
     XA_OBS_ELRATE       =  8,     // elevation rate (deg/s)
     XA_OBS_AZRATE       =  9,     // azimuth rate (deg/s)
     XA_OBS_RANGEACCEL   = 10,     // range acceleration (km/s^2)
     XA_OBS_TRACKIND     = 12,     // track position indicator (3=start track ob, 4=in track ob, 5=end track ob)
     XA_OBS_ASTAT        = 13,     // association status assigned by SPADOC
     XA_OBS_SITETAG      = 14,     // original satellite number
     XA_OBS_SPADOCTAG    = 15,     // SPADOC-asssigned tag number
     XA_OBS_POSX         = 16,     // position X/ECI or X/EFG (km)
     XA_OBS_POSY         = 17,     // position Y/ECI or Y/EFG (km)
     XA_OBS_POSZ         = 18,     // position Z/ECI or Z/EFG (km)   
     XA_OBS_VELX         = 19,     // velocity X/ECI (km/s)  (or Edot/EFG (km) for ob type 7 TTY)
     XA_OBS_VELY         = 20,     // velocity Y/ECI (km/s)  (or Fdot/EFG (km) for ob type 7 TTY)
     XA_OBS_VELZ         = 21,     // velocity Z/ECI (km/s)  (or Gdot/EFG (km) for ob type 7 TTY)
     XA_OBS_YROFEQNX     = 22,     // year of equinox indicator for obs type 5/9 (0= Time of obs, 1= 0 Jan of date, 2= J2000, 3= B1950)
     XA_OBS_ABERRATION   = 23,     // aberration indicator, 0-not corrected, 1-corrceted
     
     // for RF obs only - some indexes are reused but with different field names that only applies to RF obs
     XA_OBS_SENNUM1      =  2,     // Sensor number of site #1 (for RF obs only)
     XA_OBS_SENNUM2      =  4,     // Sensor number of site #2 (for RF obs only)
     XA_OBS_DELRNG       =  5,     // Delta range (m)
     XA_OBS_DELRNGSIGM   =  6,     // The uncertainty of the delta range measurement (m). This value may be 0 if the uncertainty in the measurement is unknown.
     XA_OBS_DELRRATE     =  7,     // Delta range rate (m/s)
     XA_OBS_DELRRATESIGM =  8,     // The uncertainty of the delta range-rate measurement (m/s). This value may be 0 if the uncertainty in the measurement is unknown.
     XA_OBS_DELAY1       =  9,     // Site 1 equipment path delay (m). This value may be zero
     XA_OBS_DELAY2       = 10,     // Site 2 equipment path delay (m). This value may be zero
     XA_OBS_FREQ         = 12,     // Frequency of transmitted signal (Hz)
     XA_OBS_PROCTIME     = 13,     // Process time (days since 1950 UTC)
     XA_OBS_SNR          = 14,     // Signal to noise ratio
     XA_OBS_FLG          = 15,     // Flag for dianostic use
     XA_OBS_FDOADOT      = 16,     // FDOA rate for diagnostics
     XA_OBS_RESVD        = 17,     // Reserved  
     // end of RF obs 
     
     
     XA_OBS_AZORRABIAS   = 33,     // AZ/RA bias (deg)
     XA_OBS_ELORDECBIAS  = 34,     // EL/DEC bias (deg)
     XA_OBS_RGBIAS       = 35,     // Range bias (km)
     XA_OBS_RRBIAS       = 36,     // Range-rate bias (km/sec)
     XA_OBS_TIMEBIAS     = 37,     // Time bias (sec)
     XA_OBS_RAZORRABIAS  = 38,     // AZ/RA rate bias (deg/sec) 
     XA_OBS_RELORDECBIAS = 39,     // EL/DEC rate bias (deg/sec)
  
     XA_OBS_SIGMATYPE    = 40,     // individual obs's sigmas type (0: N/A, 6: 6 elements, 21: 21 elements, 7: this is CSV obs)
     XA_OBS_SIGMAEL1     = 41,     // sigma - covariance element 1 - 6 elemens - Az sigma
     XA_OBS_SIGMAEL2     = 42,     // sigma - covariance element 2 - 6 elemens - El sigma
     XA_OBS_SIGMAEL3     = 43,     // sigma - covariance element 3 - 6 elemens - Range sigma
     XA_OBS_SIGMAEL4     = 44,     // sigma - covariance element 4 - 6 elemens - Range rate sigma
     XA_OBS_SIGMAEL5     = 45,     // sigma - covariance element 5 - 6 elemens - Az rate sigma
     XA_OBS_SIGMAEL6     = 46,     // sigma - covariance element 6 - 6 elemens - El rate sigma
     XA_OBS_SIGMAEL7     = 47,     // sigma - covariance element 7 
     XA_OBS_SIGMAEL8     = 48,     // sigma - covariance element 8
     XA_OBS_SIGMAEL9     = 49,     // sigma - covariance element 9
     XA_OBS_SIGMAEL10    = 50,     // sigma - covariance element 10
     XA_OBS_SIGMAEL11    = 51,     // sigma - covariance element 11
     XA_OBS_SIGMAEL12    = 52,     // sigma - covariance element 12
     XA_OBS_SIGMAEL13    = 53,     // sigma - covariance element 13
     XA_OBS_SIGMAEL14    = 54,     // sigma - covariance element 14
     XA_OBS_SIGMAEL15    = 55,     // sigma - covariance element 15
     XA_OBS_SIGMAEL16    = 56,     // sigma - covariance element 16
     XA_OBS_SIGMAEL17    = 57,     // sigma - covariance element 17
     XA_OBS_SIGMAEL18    = 58,     // sigma - covariance element 18
     XA_OBS_SIGMAEL19    = 59,     // sigma - covariance element 19
     XA_OBS_SIGMAEL20    = 60,     // sigma - covariance element 20
     XA_OBS_SIGMAEL21    = 61,     // sigma - covariance element 21
  
     XA_OBS_SIZE         = 64;
     
  // Indexes of observation data in an array (Obs Type CSV specific)
  static const int  
     XA_OTCSV_SECCLASS     =  0,     // security classification, 1 = Unclassified, 2 = Confidential, 3 = Secret
     XA_OTCSV_SATNUM       =  1,     // satellite number
     XA_OTCSV_SENNUM       =  2,     // sensor number
     XA_OTCSV_DS50UTC      =  3,     // observation time in days since 1950 UTC
     XA_OTCSV_ELORDEC      =  4,     // elevation (for ob type 1, 2, 3, 4, 8) or declination (for ob type 5, 9) (deg)
     XA_OTCSV_AZORRA       =  5,     // azimuth (for ob type 1, 2, 3, 4, 8) or right ascesion (for ob type 5, 9) (deg)
     XA_OTCSV_RANGE        =  6,     // range (km)
     XA_OTCSV_RANGERATE    =  7,     // range rate (km/s) for non-optical obs type
     XA_OTCSV_ELRATE       =  8,     // elevation rate (deg/s)
     XA_OTCSV_AZRATE       =  9,     // azimuth rate (deg/s)
     XA_OTCSV_RANGEACCEL   = 10,     // range acceleration (km/s^2)
     XA_OTCSV_OBSTYPE      = 11,     // observation type   
     XA_OTCSV_TRACKIND     = 12,     // track position indicator (3=start track ob, 4=in track ob, 5=end track ob)
     XA_OTCSV_ASTAT        = 13,     // association status assigned by SPADOC
     XA_OTCSV_SITETAG      = 14,     // original satellite number
     XA_OTCSV_SPADOCTAG    = 15,     // SPADOC-asssigned tag number
     XA_OTCSV_POSX         = 16,     // position X/ECI or X/EFG (km)
     XA_OTCSV_POSY         = 17,     // position Y/ECI or Y/EFG (km)
     XA_OTCSV_POSZ         = 18,     // position Z/ECI or Z/EFG (km)   
     XA_OTCSV_VELX         = 19,     // velocity X/ECI (km/s)  (or Edot/EFG (km) for ob type 7 TTY)
     XA_OTCSV_VELY         = 20,     // velocity Y/ECI (km/s)  (or Fdot/EFG (km) for ob type 7 TTY)
     XA_OTCSV_VELZ         = 21,     // velocity Z/ECI (km/s)  (or Gdot/EFG (km) for ob type 7 TTY)
     XA_OTCSV_YROFEQNX     = 22,     // year of equinox indicator for obs type 5/9 (0= Time of obs, 1= 0 Jan of date, 2= J2000, 3= B1950)
  
     XA_OTCSV_RCS_PP       = 23,     // Principal Polarization RCS
     XA_OTCSV_RCS_OP       = 24,     // Orthogonal Polarization RCS
     XA_OTCSV_RCS_PPS      = 25,     // Principal Polarization RCS sigma
     XA_OTCSV_RCS_OPS      = 26,     // Orthogonal Polarization RCS sigma
     XA_OTCSV_SNR          = 27,     // Radar Signal to Noise Ratio
     XA_OTCSV_BORE_AZ      = 28,     // Azimuth of Boresite
     XA_OTCSV_BORE_EL      = 29,     // Elevation of Boresite
     XA_OTCSV_VISMAG       = 30,     // Apparent Visual magnitude
     XA_OTCSV_VISMAG_NORM  = 31,     // GEO Normalized Visual magnitude
     XA_OTCSV_SOL_PHASE    = 32,     // Solar Phase Angle
     XA_OTCSV_FRAME        = 33,     // Frame Number
     XA_OTCSV_ABERRATION   = 34,     // Aberration correction indicator (0=YES, 1=NO)
     XA_OTCSV_ASTAT_METHOD = 35,     // 0 = ROTAS, 1 = TRACK
     
     XA_OTCSV_SIGMATYPE    = 40,     // must equal to 7 to signify this is CSV format
     XA_OTCSV_SIGMAEL1     = 41,     // sigma - covariance element 1 - Az sigma
     XA_OTCSV_SIGMAEL2     = 42,     // sigma - covariance element 2 - El sigma
     XA_OTCSV_SIGMAEL3     = 43,     // sigma - covariance element 3 - Range sigma
     XA_OTCSV_SIGMAEL4     = 44,     // sigma - covariance element 4 - Range rate sigma
     XA_OTCSV_SIGMAEL5     = 45,     // sigma - covariance element 5 - Az rate sigma
     XA_OTCSV_SIGMAEL6     = 46,     // sigma - covariance element 6 - El rate sigma
     XA_OTCSV_SIGMAEL7     = 47,     // sigma - covariance element 7 - Time sigma 
     XA_OTCSV_BIAS1        = 48,     // AZ/RA bias
     XA_OTCSV_BIAS2        = 49,     // EL/DEC bias
     XA_OTCSV_BIAS3        = 50,     // Range bias
     XA_OTCSV_BIAS4        = 51,     // Range-rate bias
     XA_OTCSV_BIAS5        = 52,     // Time bias
  
     
     XA_OTCSV_SIZE         = 64;   
     
  // Indexes of observation data in an array
  static const int  
     XA_OBSTATE_SATNUM       =  0,     // satellite number
     XA_OBSTATE_SENNUM       =  1,     // sensor number
     XA_OBSTATE_DS50UTC      =  2,     // observation time in days since 1950 UTC
     
     XA_OBSTATE_POSX         = 10,     // position X/ECI (km)
     XA_OBSTATE_POSY         = 11,     // position Y/ECI (km)
     XA_OBSTATE_POSZ         = 12,     // position Z/ECI (km)   
     XA_OBSTATE_VELX         = 13,     // velocity X/ECI (km/s)
     XA_OBSTATE_VELY         = 14,     // velocity Y/ECI (km/s)
     XA_OBSTATE_VELZ         = 15,     // velocity Z/ECI (km/s)   
     XA_OBSTATE_LAT          = 16,     // geodetic latitude (deg)
     XA_OBSTATE_LON          = 17,     // geodetic longitude (deg)
     XA_OBSTATE_HGHT         = 18,     // geodetic height (km)   
     XA_OBSTATE_POSE         = 19,     // position X/EFG (km)
     XA_OBSTATE_POSF         = 20,     // position Y/EFG (km)   
     XA_OBSTATE_POSG         = 21,     // position Z/EFG (km)
  
     
     XA_OBSTATE_SIZE         = 64;   
     
  // Indexes of observation data available for each obs type (OT0: obs type 0, OT1: obs type 1, ...)
  // All obs types have these common data fields  XA_OBS_SECCLASS = 0, XA_OBS_SATNUM = 1, XA_OBS_SENNUM = 2, XA_OBS_DS50UTC = 3, and XA_OBS_OBSTYPE = 11
  static const int     
     XA_OT0_RANGERATE =  7,     // range rate (km/s)  
    
     XA_OT1_ELEVATION =  4,     // elevation (deg)
     XA_OT1_AZIMUTH   =  5,     // azimuth (deg)
  
     XA_OT2_ELEVATION =  4,     // elevation (deg)
     XA_OT2_AZIMUTH   =  5,     // azimuth (deg)
     XA_OT2_RANGE     =  6,     // range (km)
  
     XA_OT3_ELEVATION =  4,     // elevation (deg)
     XA_OT3_AZIMUTH   =  5,     // azimuth (deg)
     XA_OT3_RANGE     =  6,     // range (km)
     XA_OT3_RANGERATE =  7,     // range rate (km/s) 
  
     XA_OT4_ELEVATION =  4,     // elevation (deg)
     XA_OT4_AZIMUTH   =  5,     // azimuth (deg)
     XA_OT4_RANGE     =  6,     // range (km)
     XA_OT4_RANGERATE =  7,     // range rate (km/s) 
     XA_OT4_ELRATE    =  8,     // elevation rate (deg/s)
     XA_OT4_AZRATE    =  9,     // azimuth rate (deg/s)
     XA_OT4_RANGEACCEL= 10,     // range acceleration (km/s^2)
  
     XA_OT5_DECL      =  4,     // declination (deg)
     XA_OT5_RIGHTASC  =  5,     // right ascesion (deg)
     XA_OT5_YROFEQNX  = 22,     // year of equinox indicator (0= Time of obs, 1= 0 Jan of date, 2= J2000, 3= B1950)
     XA_OT5_ABERRATION= 23,     // ABERRATION INDICATOR, 0-NOT CORRECTED, 1-CORRCETED
  
     XA_OT6_RANGE     =  6,     // range (km)
  
     XA_OT8_ELEVATION =  4,     // elevation (deg)
     XA_OT8_AZIMUTH   =  5,     // azimuth (deg)
     XA_OT8_RANGE     =  6,     // optional - range (km)
     XA_OT8_POSE      = 16,     // orbiting sensor position X/EFG (km)
     XA_OT8_POSF      = 17,     // orbiting sensor position Y/EFG (km)
     XA_OT8_POSG      = 18,     // orbiting sensor position Z/EFG (km)   
  
     XA_OT9_DECL      =  4,     // declination (deg)
     XA_OT9_RIGHTASC  =  5,     // right ascesion (deg)
     XA_OT9_RANGE     =  6,     // optional - range (km)
     XA_OT9_POSE      = 16,     // orbiting sensor position X/EFG (km)
     XA_OT9_POSF      = 17,     // orbiting sensor position Y/EFG (km)
     XA_OT9_POSG      = 18,     // orbiting sensor position Z/EFG (km)   
     XA_OT9_YROFEQNX  = 22,     // year of equinox indicator (0= Time of obs, 1= 0 Jan of date, 2= J2000, 3= B1950)  
     XA_OT9_ABERRATION= 23,     // ABERRATION INDICATOR, 0-NOT CORRECTED, 1-CORRCETED
  
     // Position only obs
     XA_OTP_POSX      = 16,     // position X/ECI or X/EFG (km)
     XA_OTP_POSY      = 17,     // position Y/ECI or Y/EFG (km)
     XA_OTP_POSZ      = 18,     // position Z/ECI or Z/EFG (km)   
     
     // Position/Velocity obs
     XA_OTV_POSX      = 16,     // position X/ECI or X/EFG (km)
     XA_OTV_POSY      = 17,     // position Y/ECI or Y/EFG (km)
     XA_OTV_POSZ      = 18,     // position Z/ECI or Z/EFG (km)   
     XA_OTV_VELX      = 19,     // velocity X/ECI (km/s)  (or Edot/EFG (km) for ob type 7 TTY)
     XA_OTV_VELY      = 20,     // velocity Y/ECI (km/s)  (or Fdot/EFG (km) for ob type 7 TTY)
     XA_OTV_VELZ      = 21,     // velocity Z/ECI (km/s)  (or Gdot/EFG (km) for ob type 7 TTY)
     
     // RF obs
     XA_OTRF_SENNUM1      =  2,     // Sensor number of site #1 (for RF obs only)
     XA_OTRF_SENNUM2      =  4,     // Sensor number of site #2 (for RF obs only)
     XA_OTRF_DELRNG       =  5,     // Delta range (m)
     XA_OTRF_DELRNGSIGM   =  6,     // The uncertainty of the delta range measurement (m). This value may be 0 if the uncertainty in the measurement is unknown.
     XA_OTRF_DELRRATE     =  7,     // Delta range rate (m/s)
     XA_OTRF_DELRRATESIGM =  8,     // The uncertainty of the delta range-rate measurement (m/s). This value may be 0 if the uncertainty in the measurement is unknown.
     XA_OTRF_DELAY1       =  9,     // Site equipment path delay. This value may be zero
     XA_OTRF_DELAY2       = 10,     // Site equipment path delay. This value may be zero
     XA_OTRF_FREQ         = 12,     // Frequency of transmitted signal
     XA_OTRF_PROCTIME     = 13,     // Process time (days since 1950 UTC)
     XA_OTRF_SNR          = 14,     // Signal to noise ratio
     XA_OTRF_FLG          = 15,     // Flag for dianostic use
     XA_OTRF_FDOADOT      = 16,     // FDOA rate for diagnostics
     XA_OTRF_RESVD        = 17,     // Reserved
     
     
     XA_OT_SIZE         = 64;   
  
  // Obs selection criteria
  static const int  
     XA_SELOB_MODE        =  0,        // Seclection mode (unused for now)
        
     XA_SELOB_FRTIME      =  1,        // From time
     XA_SELOB_TOTIME      =  2,        // To time 
     
     XA_SELOB_FRIDX       =  3,        // From time
     XA_SELOB_TOIDX       =  4,        // To time 
        
     XA_SELOB_SAT1        = 11,        // Select any obs that match this satellite number #1
     XA_SELOB_SAT2        = 12,        // Select any obs that match this satellite number #2
     XA_SELOB_SAT3        = 13,        // Select any obs that match this satellite number #3
     XA_SELOB_SAT4        = 14,        // Select any obs that match this satellite number #4
     XA_SELOB_SAT5        = 15,        // Select any obs that match this satellite number #5
     XA_SELOB_SAT6        = 16,        // Select any obs that match this satellite number #6
     XA_SELOB_SAT7        = 17,        // Select any obs that match this satellite number #7
     XA_SELOB_SAT8        = 18,        // Select any obs that match this satellite number #8
     XA_SELOB_SAT9        = 19,        // Select any obs that match this satellite number #9
     XA_SELOB_SAT10       = 20,        // Select any obs that match this satellite number #10
        
     XA_SELOB_SEN1        = 21,        // Select any obs that are obtained by this sensor site #1
     XA_SELOB_SEN2        = 22,        // Select any obs that are obtained by this sensor site #2
     XA_SELOB_SEN3        = 23,        // Select any obs that are obtained by this sensor site #3
     XA_SELOB_SEN4        = 24,        // Select any obs that are obtained by this sensor site #4
     XA_SELOB_SEN5        = 25,        // Select any obs that are obtained by this sensor site #5
     XA_SELOB_SEN6        = 26,        // Select any obs that are obtained by this sensor site #6
     XA_SELOB_SEN7        = 27,        // Select any obs that are obtained by this sensor site #7
     XA_SELOB_SEN8        = 28,        // Select any obs that are obtained by this sensor site #8
     XA_SELOB_SEN9        = 29,        // Select any obs that are obtained by this sensor site #9
     XA_SELOB_SEN10       = 30,        // Select any obs that are obtained by this sensor site #10
        
     XA_SELOB_OT1         = 31,        // Select any obs that match this obs type #1, use OT_RRATE_SELOB for type 0/range rate only
     XA_SELOB_OT2         = 32,        // Select any obs that match this obs type #2
     XA_SELOB_OT3         = 33,        // Select any obs that match this obs type #3
     XA_SELOB_OT4         = 34,        // Select any obs that match this obs type #4
     XA_SELOB_OT5         = 35,        // Select any obs that match this obs type #5
     XA_SELOB_OT6         = 36,        // Select any obs that match this obs type #6
     XA_SELOB_OT7         = 37,        // Select any obs that match this obs type #7
     XA_SELOB_OT8         = 38,        // Select any obs that match this obs type #8
     XA_SELOB_OT9         = 39,        // Select any obs that match this obs type #9
     XA_SELOB_OT10        = 40,        // Select any obs that match this obs type #10
        
     XA_SELOB_FRAZ        = 41,        // From azimuth
     XA_SELOB_TOAZ        = 42,        // To azimuth
     XA_SELOB_FREL        = 43,        // From elevation 
     XA_SELOB_TOEL        = 44,        // To elevation
     XA_SELOB_FRRA        = 45,        // From right ascension
     XA_SELOB_TORA        = 46,        // To right ascension
     XA_SELOB_FRDEC       = 47,        // From declincation
     XA_SELOB_TODEC       = 48,        // To declination
     XA_SELOB_FRRNG       = 49,        // From range
     XA_SELOB_TORNG       = 50,        // To range
     XA_SELOB_FRRNGRT     = 51,        // From range rate
     XA_SELOB_TORNGRT     = 52,        // To range rate
     XA_SELOB_FRAZRT      = 53,        // From azimuth rate
     XA_SELOB_TOAZRT      = 54,        // To azimuth rate
     XA_SELOB_FRELRT      = 55,        // From elevation rate
     XA_SELOB_TOELRT      = 56,        // To elevation rate
     XA_SELOB_FRASTAT     = 57,        // From ASTAT (0 to 4)
     XA_SELOB_TOASTAT     = 58,        // To ASTAT (0 to 4) (0 < val < 1.0 if want to retrieve ASTAT 0)
  
     XA_SELOB_SIZE        = 128;
  
  
// ObsDll's function pointers declaration
extern fnPtrObsInit                        ObsInit;
extern fnPtrObsGetInfo                     ObsGetInfo;
extern fnPtrObsSetTTYYear                  ObsSetTTYYear;
extern fnPtrObsLoadFile                    ObsLoadFile;
extern fnPtrObsSaveFile                    ObsSaveFile;
extern fnPtrObsRemove                      ObsRemove;
extern fnPtrObsRemoveAll                   ObsRemoveAll;
extern fnPtrObsGetCount                    ObsGetCount;
extern fnPtrObsGetLoaded                   ObsGetLoaded;
extern fnPtrObsLoadCard                    ObsLoadCard;
extern fnPtrObsLoadTwoCards                ObsLoadTwoCards;
extern fnPtrObsAddFrB3Card                 ObsAddFrB3Card;
extern fnPtrObsAddFrB3CardML               ObsAddFrB3CardML;
extern fnPtrObsB3ToCsv                     ObsB3ToCsv;
extern fnPtrObsCsvToB3                     ObsCsvToB3;
extern fnPtrObsAddFrTTYCards               ObsAddFrTTYCards;
extern fnPtrObsAddFrTTYCardsML             ObsAddFrTTYCardsML;
extern fnPtrObsTTYToCsv                    ObsTTYToCsv;
extern fnPtrObsCsvToTTY                    ObsCsvToTTY;
extern fnPtrObsAddFrCsv                    ObsAddFrCsv;
extern fnPtrObsAddFrCsvML                  ObsAddFrCsvML;
extern fnPtrObsAddFrRfCard                 ObsAddFrRfCard;
extern fnPtrObsAddFrRfCardML               ObsAddFrRfCardML;
extern fnPtrObsAddFrFields                 ObsAddFrFields;
extern fnPtrObsAddFrFieldsML               ObsAddFrFieldsML;
extern fnPtrObsAddFrArray                  ObsAddFrArray;
extern fnPtrObsAddFrArrayML                ObsAddFrArrayML;
extern fnPtrObsGetAllFields                ObsGetAllFields;
extern fnPtrObsDataToArray                 ObsDataToArray;
extern fnPtrObsUpdateFrFields              ObsUpdateFrFields;
extern fnPtrObsGetField                    ObsGetField;
extern fnPtrObsSetField                    ObsSetField;
extern fnPtrObsGetB3Card                   ObsGetB3Card;
extern fnPtrObsGetTTYCard                  ObsGetTTYCard;
extern fnPtrObsGetCsv                      ObsGetCsv;
extern fnPtrObsGetRfCard                   ObsGetRfCard;
extern fnPtrObsFieldsToB3Card              ObsFieldsToB3Card;
extern fnPtrObsFieldsToCsv                 ObsFieldsToCsv;
extern fnPtrObsFieldsToTTYCard             ObsFieldsToTTYCard;
extern fnPtrObsFieldsToObsKey              ObsFieldsToObsKey;
extern fnPtrObsFieldsToObsKeyML            ObsFieldsToObsKeyML;
extern fnPtrObsB3Parse                     ObsB3Parse;
extern fnPtrObsParse                       ObsParse;
extern fnPtrObsLoadFileGID                 ObsLoadFileGID;
extern fnPtrObsSaveFileGID                 ObsSaveFileGID;
extern fnPtrObsRemoveGID                   ObsRemoveGID;
extern fnPtrObsGetCountGID                 ObsGetCountGID;
extern fnPtrObsGetLoadedGID                ObsGetLoadedGID;
extern fnPtrObsTypeCToI                    ObsTypeCToI;
extern fnPtrObsTypeIToC                    ObsTypeIToC;
extern fnPtrObsResetSelObs                 ObsResetSelObs;
extern fnPtrObsGetStates                   ObsGetStates;
extern fnPtrObsDataToStates                ObsDataToStates;
extern fnPtrObsArrToLines                  ObsArrToLines;
extern fnPtrSetObsKeyMode                  SetObsKeyMode;
extern fnPtrGetObsKeyMode                  GetObsKeyMode;
extern fnPtrSatNumFrObsKey                 SatNumFrObsKey;
extern fnPtrSenNumFrObsKey                 SenNumFrObsKey;
extern fnPtrObsGetSelected                 ObsGetSelected;



void LoadObsDll();
void FreeObsDll();




#endif
// ========================= End of auto generated code ==========================
