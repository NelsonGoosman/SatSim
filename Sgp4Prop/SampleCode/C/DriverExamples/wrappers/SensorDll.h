// This wrapper file was generated automatically by the GenDllWrappers program.

#ifndef SENSORDLL_H
#define SENSORDLL_H

#include "../services/DllUtils.h"

// Provide the path to the dll/so/dylib
#if defined (_WIN32) || defined (__CYGWIN__)
  #define SensorDll "Sensor.dll"
#elif __APPLE__
  #define SensorDll "libsensor.dylib"
#else
  #define SensorDll "libsensor.so"
#endif


// Notes: This function has been deprecated since v9.0. 
// Initializes Sensor DLL for use in the program
// If this function returns an error, it is recommended that the users stop the program immediately. 
// The error occurs if the users forget to load and initialize all the prerequisite dlls, as listed 
// in the DLL Prerequisite section, before using this DLL.
// apAddr             The handle that was returned from DllMainInit() (in-Long)
// returns 0 if Sensor.dll is initialized successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorInit)(__int64 apAddr);


// Returns information about the current version of Sensor DLL. 
// The information is placed in the string parameter passed in.
// The returned string provides information about the version number, build date, and the platform of the Sensor DLL.
// infoStr            A string to hold the information about Sensor.dll (out-Character[128])
typedef void (STDCALL *fnPtrSensorGetInfo)(char infoStr[128]);


// Loads sensor data, contained in a text file, into the set of loaded sensors
// The users can use this function repeatedly to load sensor data from different input files. 
// However, only unique senKeys are stored in the binary tree.  New sensor data will overwrite the existing data. 
// 
// Sensor data can be included directly in the main input file or they can be read from a separate file 
// identified with "SENFIL=[pathname\filename]".
// 
// This function only reads sensor data from the main input file or the file identified with SENFIL in the input file. 
// It won't read anything else.
// senFile            The name of the file containing sensor data (in-Character[512])
// returns 0 if the input file is read successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorLoadFile)(char senFile[512]);


// Loads a single sensor-typed card
// card               Any single sensor-typed card (in-Character[512])
// returns 0 if the input card is read successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorLoadCard)(char card[512]);


// Saves the currently loaded sensor data to a file
// If the users call this routine immediately after the SensorLoadFile(). 
// The sensor data contents in the two file should be the same (minus duplicated sensors or bad sensors).
// 
// The purpose of this function is to save the current state of the loaded sensors, usually used in GUI applications, for future use.
// sensorFile         The name of the file in which to save the settings (in-Character[512])
// saveMode           Specifies whether to create a new file or append to an existing one (0 = create, 1= append) (in-Integer)
// saveForm           Specifies the mode in which to save the file (0 = text format, 1 = not yet implemented, reserved for future) (in-Integer)
// returns 0 if the data is successfully saved to the file, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorSaveFile)(char sensorFile[512], int saveMode, int saveForm);


// Removes a sensor, represented by the senKey, from the set of currently loaded sensors
// If the users enter an invalid senKey - a non-existing senKey, the function will return a non-zero value indicating an error.
// senKey             The sensor's unique key (in-Long)
// returns 0 if the sensor is successfully removed, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorRemove)(__int64 senKey);


// Removes all currently loaded sensors from memory
// The function returns zero if all the loaded sensors are removed successfully from the SENSOR DLL's binary tree. Other values indicate an error.
// returns 0 if all the loaded sensors are removed successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorRemoveAll)();


// Returns the number of sensors currently loaded
// See SensorGetLoaded for example.
// This function is useful for dynamically allocating memory for the array that is passed to the function SensorGetLoaded().
// returns the number of sensors currently loaded
typedef int (STDCALL *fnPtrSensorGetCount)();


// Retrieves all of the currently loaded senKeys. 
// These senKeys can be used to access the internal data for the sensors.
// It is recommended that SensorGetCount() is used to count how many sensors are currently loaded in the SENSOR DLL's binary tree. 
// The user can then use this number to dynamically allocate the senKeys array and pass it to this function. 
// 
// If the users prefer to pass a static array to the function, make sure it is big enough to store all the senKeys in memory.
// order              Specifies the order in which the senKeys should be returned:0=Sort in ascending order, 1=Sort in descending order, 2=Sort in the order in which the senKeys were loaded in memory (in-Integer)
// senKeys            The array in which to store the senKeys (out-Long[*])
typedef void (STDCALL *fnPtrSensorGetLoaded)(int order, __int64 senKeys[]);


// Retrieves sensor location data for a sensor
// senKey             The sensor's unique key (in-Long)
// astroLat           Astronomical Latitude (deg): astroLat[-90, 90], (+ = North; - = South) (out-Double)
// astroLon           Astronomical Longitude (deg): astroLon[-360, 360], (+ = West; - = East) (out-Double)
// senPos             Sensor XYZ geocentric position (meters) (out-Double[3])
// senDesc            Sensor location description (out-Character[24])
// orbSatNum          For orbiting sensors, this is the associated satellite number. For ground sensors, orbSatNum = 0 (out-Integer)
// secClass           Sensor classification: U = Unclassified, C = Confidential, S = Secret (out-Character)
// returns 0 if all sensor location data fields are retrieved successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorGetLocAll)(__int64 senKey, double* astroLat, double* astroLon, double senPos[3], char senDesc[24], int* orbSatNum, char* secClass);


// Adds/updates sensor location data (non DMA) for a sensor using individually provided field values
// This function is shared between ground sensors and orbiting sensors. The users need to provide the proper data fields for each sensor type.
// 
// If the function is invoked with a senKey that already exists in the SENSOR DLL's binary tree, the senKey's associated data will be updated with the provided data.
// 
// If it is an orbiting sensor, the users need to provide the associated satellite number.
// senKey             The sensor's unique key (in-Long)
// astroLat           Astronomical Latitude (deg): astroLat[-90, 90], (+ = North; - = South) (in-Double)
// astroLon           Astronomical Longitude (deg): astroLon[-360, 360], (+ = West; - = East) (in-Double)
// senPos             Sensor XYZ geocentric position (meters) (in-Double[3])
// senDesc            Sensor location description (in-Character[24])
// orbSatNum          For orbiting sensors, this is the associated satellite number. For ground sensors, orbSatNum = 0 (in-Integer)
// secClass           Sensor classification: U = Unclassified, C = Confidential, S = Secret (in-Character)
// returns 0 if the sensor location data is added/updated successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorSetLocAll)(__int64 senKey, double astroLat, double astroLon, double senPos[3], char senDesc[24], int orbSatNum, char secClass);


// Retrieves the value of an individual field of sensor location data
// 
// Make sure to use the appropriate field index for ground sensors and orbiting sensors.
// 
// The table below shows the values for the xf_SenLoc parameter:
// 
// table
// 
// Index
// Index Interpretation
// 
// 1Sensor number
// 2Sensor astronomical latitude (deg)
// 3Sensor astronomical longitude (deg)
// 4Sensor position X (km)
// 5Sensor position Y (km)
// 6Sensor position Z (km)
// 7Sensor description
// 8Orbiting sensor's number (satNum)   
// 9Sensor classification    
//    
// senKey             The sensor's unique key (in-Long)
// xf_SenLoc          Predefined number specifying which field to retrieve (in-Integer)
// strValue           A string to contain the value of the requested field (out-Character[512])
// returns 0 if the sensor location data is successfully retrieved, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorGetLocField)(__int64 senKey, int xf_SenLoc, char strValue[512]);


// Updates the value of an individual field of sensor location data
// See SensorGetLocField for a description of the xf_SenLoc values.
// The set value type was intentionally chosen as a character string because it allows the users to set value for different data types.
// 
// Make sure to use the appropriate field index for ground sensors and orbiting sensors.
// senKey             The sensor's unique key (in-Long)
// xf_SenLoc          Predefined number specifying which field to retrieve (in-Integer)
// strValue           The new value of the specified field, expressed as a string (in-Character[512])
// returns 0 if the sensor location data is successfully updated, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorSetLocField)(__int64 senKey, int xf_SenLoc, char strValue[512]);


// Retrieves sensor limits data
// This function is shared between ground sensors and orbiting sensors. Make sure to interpret the data correctly.
// senKey             The sensor's unique key (in-Long)
// viewType           Sensor viewing type (out-Character)
// obsType            Sensor observation type (out-Character)
// rngUnits           Units of range and range rate: 0=km, km/sec, 1=nm, nm/sec (out-Integer)
// maxRngLim          Maximum observable range limit (km) (out-Double)
// boresight1         Orbiting sensor boresight1 vector (out-Character)
// elLim1             Elevation limit #1 (low, deg) OR orbiting sensor off-boresight angle (out-Double)
// elLim2             Elevation limit #2 (high, deg) OR orbiting sensor off-boresight angle (out-Double)
// azLim1             Azimuth limit #1 (left, deg) OR orbiting sensor clock angle (out-Double)
// azLim2             Azimuth limit #2 (right, deg) OR orbiting sensor clock angle (out-Double)
// interval           ouput interval (min) (out-Double)
// visFlg             Visual pass control flag (out-Integer)
// rngLimFlg          Range limits control flag (out-Integer)
// maxPPP             Max number of points per pass (0=unlimited) (out-Integer)
// minRngLim          Minimum observable range limit (km) (out-Double)
// plntryRes          Orbiting sensor planetary restrictions (out-Integer)
// rrLim              Range rate/relative velocity limit (km/sec) (out-Double)
// returns 0 if all sensor limits data fields are retrieved successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorGet1L)(__int64 senKey, char* viewType, char* obsType, int* rngUnits, double* maxRngLim, char* boresight1, double* elLim1, double* elLim2, double* azLim1, double* azLim2, double* interval, int* visFlg, int* rngLimFlg, int* maxPPP, double* minRngLim, int* plntryRes, double* rrLim);


// Adds/updates sensor limits data (non DMA) via individually provided field values
// This function is shared between ground sensors and orbiting sensors. The users need to provide the proper data fields for each sensor type.
// 
// If the function is invoked with a senKey that already exists in the SENSOR DLL's binary tree, the senKey's associated data will be updated with the provided data.
// 
// If it is an orbiting sensor, the users need to provide the associated satellite number.
// senKey             The sensor's unique key (in-Long)
// viewType           Sensor viewing type (in-Character)
// obsType            Sensor observation type (in-Character)
// rngUnits           Units of range and range rate: 0=km, km/sec, 1=nm, nm/sec (in-Integer)
// maxRngLim          Maximum observable range limit (km) (in-Double)
// boresight1         Orbiting sensor boresight1 vector (in-Character)
// elLim1             Elevation limit #1 (low, deg) OR orbiting sensor off-boresight angle (in-Double)
// elLim2             Elevation limit #2 (high, deg) OR orbiting sensor off-boresight angle (in-Double)
// azLim1             Azimuth limit #1 (left, deg) OR orbiting sensor clock angle (in-Double)
// azLim2             Azimuth limit #2 (right, deg) OR orbiting sensor clock angle (in-Double)
// interval           ouput interval (min) (in-Double)
// visFlg             Visual pass control flag (in-Integer)
// rngLimFlg          Range limits control flag (in-Integer)
// maxPPP             Max number of points per pass (0=unlimited) (in-Integer)
// minRngLim          Minimum observable range limit (km) (in-Double)
// plntryRes          Orbiting sensor planetary restrictions (in-Integer)
// rrLim              Range rate/relative velocity limit (km/sec) (in-Double)
// returns 0 if the sensor limits data is added/updated successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorSet1L)(__int64 senKey, char viewType, char obsType, int rngUnits, double maxRngLim, char boresight1, double elLim1, double elLim2, double azLim1, double azLim2, double interval, int visFlg, int rngLimFlg, int maxPPP, double minRngLim, int plntryRes, double rrLim);


// Retrieves additional sensor limits data
// This function is shared between ground sensors and orbiting sensors. Make sure to interpret the data correctly.
// senKey             The sensor's unique key (in-Long)
// boresight2         Orbiting sensor boresight2 vector (out-Character)
// elLim3             Elevation limit #3 (low, deg) OR orbiting sensor off-boresight angle (out-Double)
// elLim4             Elevation limit #4 (high, deg) OR orbiting sensor off-boresight angle (out-Double)
// azLim3             Azimuth limit #3 (left, deg) OR orbiting sensor clock angle (out-Double)
// azLim4             Azimuth limit #4 (right, deg) OR orbiting sensor clock angle (out-Double)
// earthBckgrnd       Flag; if set, allow orb sensor to view satellite against earth background (out-Integer)
// earthLimb          Orbiting sensor earth limb exclusion distance (km) (out-Double)
// solarXAngle        Orbiting sensor solar exclusion angle (deg) (out-Double)
// lunarXAngle        Orbiting sensor lunar exclusion angle (deg) (out-Double)
// minIllum           Orbiting sensor minimum illumination angle (deg) (out-Double)
// twilit             Ground site twilight offset angle (deg) (out-Double)
// returns 0 if all optional/additional sensor limits data fields are retrieved successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorGet2L)(__int64 senKey, char* boresight2, double* elLim3, double* elLim4, double* azLim3, double* azLim4, int* earthBckgrnd, double* earthLimb, double* solarXAngle, double* lunarXAngle, double* minIllum, double* twilit);


// Adds/updates additional sensor limits data
// This function is shared between ground sensors and orbiting sensors. The users need to provide the proper data fields for each sensor type.
// 
// If the function is invoked with a senKey that already exists in the SENSOR DLL's binary tree, the senKey's associated data will be updated with the provided data.	
// senKey             The sensor's unique key (in-Long)
// boresight2         Orbiting sensor boresight2 vector (in-Character)
// elLim3             Elevation limit #3 (low, deg) OR orbiting sensor off-boresight angle (in-Double)
// elLim4             Elevation limit #4 (high, deg) OR orbiting sensor off-boresight angle (in-Double)
// azLim3             Azimuth limit #3 (left, deg) OR orbiting sensor clock angle (in-Double)
// azLim4             Azimuth limit #4 (right, deg) OR orbiting sensor clock angle (in-Double)
// earthBckgrnd       Flag; if set, allow orb sensor to view satellite against earth background (in-Integer)
// earthLimb          Orbiting sensor earth limb exclusion distance (km) (in-Double)
// solarXAngle        Orbiting sensor solar exclusion angle (deg) (in-Double)
// lunarXAngle        Orbiting sensor lunar exclusion angle (deg) (in-Double)
// minIllum           Orbiting sensor minimum illumination angle (deg) (in-Double)
// twilit             Ground site twilight offset angle (deg) (in-Double)
// returns 0 if the optional/additional sensor limits data is added/updated successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorSet2L)(__int64 senKey, char boresight2, double elLim3, double elLim4, double azLim3, double azLim4, int earthBckgrnd, double earthLimb, double solarXAngle, double lunarXAngle, double minIllum, double twilit);


// Retrieves an individual field of sensor limits data
// 
// Make sure to use the appropriate field index for ground sensors and orbiting sensors.
// 
// The table below shows the values for the xf_SenLim parameter:
// 
// table
// 
// Index
// Index Interpretation
// 
// 11 Sensor view type
// 12 Sensor observation type
// 13 Unit on range/range rate
// 14 Max observable range (km)
// 15 Min observable range (km)
// 16 Output interval (min)
// 17 Visual pass control flag
// 18 Range limit control flag 
// 19 Max number of points per pass
// 20 Range rate/relative velocity limit (km/sec)
// 31 Elevation limits (deg) 1, 2, 3, 4 or Sensor off-boresight angle (deg)
// 32 
// 33 
// 34 
// 35 Azimuth limits (deg) 1, 2,3, 4 or Sensor clock angle (deg)
// 36 
// 37 
// 38 
// 52 Orbiting sensor planetary restriction
// 53 Orbiting sensor boresight vector 1
// 54 Orbiting sensor boresight vector 2
// 55 Allow orbiting sensor to view sat against earth background
// 56 Orbiting sensor earth limb exclusion distance (km)
// 57 Orbiting sensor solar exclusion angle (deg)   
// 58 Orbiting sensor lunar exclusion angle (deg)
// 59 Orbiting sensor min illumination angle (deg)
// 60 Ground site twilight offset angle (deg)    
//    
// senKey             The sensor's unique key (in-Long)
// xf_SenLim          Predefined number specifying which field to retrieve (in-Integer)
// strValue           A string to contain the value of the requested field (out-Character[512])
// returns 0 if the sensor limits data is retrieved successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorGetLimField)(__int64 senKey, int xf_SenLim, char strValue[512]);


// Updates an individual field of sensor limits data
// See SensorGetLimField for a description of the xf_SenLim parameter.
// The set value type was intentionally chosen as a character string because it allows the users to set value for different data types.
// 
// Make sure to use the appropriate field index for ground sensors and orbiting sensors.
// senKey             The sensor's unique key (in-Long)
// xf_SenLim          Predefined number specifying which field to retrieve (in-Integer)
// strValue           The new value of the specified field, expressed as a string (in-Character[512])
// returns Returns zero indicating the sensor limits data has been successfully updated. Other values indicate an error
typedef int (STDCALL *fnPtrSensorSetLimField)(__int64 senKey, int xf_SenLim, char strValue[512]);


// Retrieves sensor sigma/bias data
// senKey             The sensor's unique key (in-Long)
// xaf_senbs          sensor's sigma and biases (see XAF_SENBS_?) (out-Double[16])
// returns 0 if all sensor sigma/bias data fields are retrieved successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorGetBS)(__int64 senKey, double xaf_senbs[16]);


// Adds/updates sensor sigma/bias data (non DMA)
// senKey             The sensor's unique key (in-Long)
// xaf_senbs          sensor's sigmas and biases (see XAF_SENBS_?) (in-Double[16])
// returns 0 if the sensor sigma/bias data is added/updated successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorSetBS)(__int64 senKey, double xaf_senbs[16]);


// Retrieves an individual field of sensor sigma/bias data
// senKey             The sensor's unique key (in-Long)
// xaf_senbs          Index number of the field the user wants to retrieve (see XAF_SENBS_?) (in-Integer)
// strValue           A string to contain the value of the requested field (out-Character[512])
// returns 0 if the sensor sigma/bias data is retrieved successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorGetBSField)(__int64 senKey, int xaf_senbs, char strValue[512]);


// Updates an individual field of sensor sigma/bias data
// senKey             The sensor's unique key (in-Long)
// xaf_senbs          Index number of the field the user wants to set (see XAF_SENBS_?) (in-Integer)
// strValue           The new value of the specified field, expressed as a string (in-Character[512])
// returns Returns zero indicating the sensor sigma/bias data has been successfully updated. Other values indicate an error
typedef int (STDCALL *fnPtrSensorSetBSField)(__int64 senKey, int xaf_senbs, char strValue[512]);


// Retrieves the sensor data in form of S-Card, L1-Card, and L2-Card of the sensor
// senKey             The sensor's unique key (in-Long)
// sCard              S-Card string of the sensor (out-Character[512])
// l1Card             L1-Card string of the sensor (out-Character[512])
// l2Card             L2-Card string of the sensor (out-Character[512])
// returns 0 on success, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorGetLines)(__int64 senKey, char sCard[512], char l1Card[512], char l2Card[512]);


// Retrieves the sensor Bias/Sigma card
// senKey             The sensor's unique key (in-Long)
// bsCard             BS-Card string of the sensor (out-Character[512])
// returns 0 on success, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorGetBSLine)(__int64 senKey, char bsCard[512]);


// Gets sensor's orbiting satellite's satKey
// senKey             The sensor's unique key (in-Long)
// orbSatKey          The orbiting satellite's unique key (out-Long)
// returns 0 on success, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorGetOrbSatKey)(__int64 senKey, __int64* orbSatKey);


// Sets sensor's orbiting satellite's satKey
// senKey             The sensor's unique key (in-Long)
// orbSatKey          The orbiting satellite's unique key (in-Long)
// returns 0 on success, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorSetOrbSatKey)(__int64 senKey, __int64 orbSatKey);


// Loads Space Fence's detailed azimuth-elevation definition table
// senKey             The sensor's unique key (in-Long)
// azElTableFile      The name of the file containing Space Fence's az/el definition table (in-Character[512])
// returns 0 if the input file is read successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorLoadAzElTable)(__int64 senKey, char azElTableFile[512]);


// Adds a new sensor segment whose limits defined by the input parameters - a cone or a dome portion 
// senKey             The sensor's unique key (in-Long)
// segType            Input segment type (bounded-cone = 1, dome = 2) (in-Integer)
// xa_seg             sensor segment data (see XA_SEG_DOME_? and see XA_SEG_BCONE_? (in-Double[16])
// returns 0 if the new sensor segment is added successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorAddSegment)(__int64 senKey, int segType, double xa_seg[16]);


// Retrieves sensor segment data of the specified segment (segNum)
// senKey             The sensor's unique key (in-Long)
// segNum             The segment number of the sensor segment whose data is returned (in-Integer)
// segType            The output segment type (bounded-cone = 1, dome = 2) (out-Integer)
// xa_seg             The resulting sensor segment data (see XA_SEG_DOME_? and see XA_SEG_BCONE_?) (out-Double[16])
// returns 0 if the sensor segment data is returned successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorGetSegment)(__int64 senKey, int segNum, int* segType, double xa_seg[16]);


// Sets sensor key mode
// This mode can also be turned on if the user loads an input text file that includes this line - "AS_DMA_SEN_ON" -
// and is currently calling any of these methods: DllMainLoadFile(), or SenLoadFile()
// sen_keyMode        Desired sen key mode (see SEN_KEYMODE_?) (in-Integer)
// returns 0 if the set is successful, non-0 if there is an error.
typedef int (STDCALL *fnPtrSetSenKeyMode)(int sen_keyMode);


// Gets current sensor key mode
// returns Current sen key mode (see SEN_KEYMODE_?)
typedef int (STDCALL *fnPtrGetSenKeyMode)();


// Returs the sensor number associated with the input senKey
// senKey             The input senKey (in-Long)
// returns The sensor number associated with the input senKey (senNum = -1 if senKey doesn't exist)
typedef int (STDCALL *fnPtrSenNumOf)(__int64 senKey);


// Returns the first senKey from the currently loaded set of sensors that contains the specified sensor number.
// A negative value will be returned if there is an error.
// senNum             Satellite number (in-Integer)
// returns The senellite's unique key
typedef __int64 (STDCALL *fnPtrSensorGetSenKey)(int senNum);


// This function is similar to SensorGetSenKey but designed to be used in Matlab. 
// Matlab doesn't correctly return the 19-digit satellite key using SensorGetSenKey. This method is an alternative way to return the senKey output.
// A negative value will be returned in senKey if there is an error.
// senNum             Senellite number (in-Integer)
// senKey             The senKey of the sensor if a sensor with the requested number is found in the set of loaded sensor, a negative value if there is an error. (out-Long)
typedef void (STDCALL *fnPtrSensorGetSenKeyML)(int senNum, __int64* senKey);


// Adds a sensor (location, limits, sigmas/biases), using its data stored in the input arrays.
// xa_sen             Array containing sensor's numerical fields (see XA_SEN_?) (in-Double[128])
// xs_sen             Input string that contains all sensor's text fields (see XS_SEN_?) (in-Character[512])
// returns The senKey of the newly added sensor on success, a negative value on error.
typedef __int64 (STDCALL *fnPtrSensorAddFrArray)(double xa_sen[128], char xs_sen[512]);


// Retrieves sensor data (location, limits, sigmas/biases) and stores it in the passing arrays.
// senKey             The sensor's unique key (in-Long)
// xa_sen             Array containing sensor's numerical fields (see XA_SEN_?) (out-Double[128])
// xs_sen             Input string that contains all sensor's text fields (see XS_SEN_?) (out-Character[512])
// returns 0 if all values are retrieved successfully, non-0 if there is an error
typedef int (STDCALL *fnPtrSensorDataToArray)(__int64 senKey, double xa_sen[128], char xs_sen[512]);
     
  // Sensor segment types
  static const int  
     SEG_BCONE = 1,      // bounded-cone-typed limit: Boresight Az/El, Min/Max halfcone angle/Range, minimum cut-off elevation
     SEG_DOME  = 2;      // dome-typed limit: Min/Max Az/El/Range
     
  
  
  // Indexes of dome segment parameters
  static const int  
     XA_SEG_DOME_AZFR   =  0,   // start azimuth (deg)          
     XA_SEG_DOME_AZTO   =  1,   // end azimuth (deg)            
     XA_SEG_DOME_ELFR   =  2,   // lower-bound elevation (deg)  
     XA_SEG_DOME_ELTO   =  3,   // higher-bound elevation (deg) 
     XA_SEG_DOME_MINRNG =  4,   // minimum range (km)           
     XA_SEG_DOME_MAXRNG =  5,   // maximum range (km)           
     
     XA_SEG_DOME_SIZE   = 16;
     
  
  // Indexes of bounded-cone segment parameters
  static const int  
     XA_SEG_BCONE_BSAZ   =  0,   // boresight azimuth (deg)
     XA_SEG_BCONE_BSEL   =  1,   // boresight elevation (deg)          
     XA_SEG_BCONE_ANGFR  =  2,   // offboresight lower angle (deg)
     XA_SEG_BCONE_ANGTO  =  3,   // offboresight higher angle (deg)
     XA_SEG_BCONE_MINRNG =  4,   // minimum range (km)
     XA_SEG_BCONE_MAXRNG =  5,   // maximum range (km)
     XA_SEG_BCONE_MINEL  =  6,   // minimum cut-off elevation (deg)
     
     XA_SEG_BCONE_SIZE   = 16;
     
     
  // Different key mode options for senKey
  static const int  
     SEN_KEYMODE_NODUP  = 0,    // Default - duplicate sensor can not be loaded in binary tree                           
     SEN_KEYMODE_DMA    = 1;    // Allow duplicate obs to be loaded and have direct memory access (DMA - no duplication check and no binary tree)   
     
  // sensor key possible errors
  static const int  
     BADSENKEY = -1,      // Bad sensor key
     DUPSENKEY =  0;      // Duplicate sensor key
  
  // Different sensor types   
  static const int  
     VT_BCT =   2,     // bounded-cone tracker
     VT_CON =   3,     // conventional tracker
     VT_OPT =   4,     // optical tracker
     VT_FAN =   7,     // constant azimuth fan sweeping vertical plane
     VT_ORB =   9,     // orbiting sensor (same as 'M' or 'O')
     VT_FOR  = 82,     // space fence's field of regard FOR ('R' = 86)
     VT_FOV  = 86;     // space fence's surveillance fan FOV ('V' = 82)
     
  // Different sensor location types 
  static const int  
     SENLOC_TYPE_ECR =  1,     // Sensor location is in ECR
     SENLOC_TYPE_EFG =  2,     // Sensor location is in EFG
     SENLOC_TYPE_LLH =  3,     // Sensor location is in LLH
     SENLOC_TYPE_ECI =  4;     // Sensor location is in ECI (TEME of Date) (associated with time of ECI position)
     
     
     
  // Sensor Data - 
  static const int  
     //*******************************************************************************
     // generic data for all sensor types
     //*******************************************************************************
     XA_SEN_GEN_SENNUM    =  0,    // sensor number
     XA_SEN_GEN_MINRNG    =  3,    // sensor minimum range (km) (=0 no minimum range check)
     XA_SEN_GEN_MAXRNG    =  4,    // sensor maxinmum range (km) (=0 no maximum range check) 
     XA_SEN_GEN_RRLIM     =  5,    // range rate/relative velocity limit (km/sec) (=0 no range rate check) 
     XA_SEN_GEN_RNGLIMFLG =  6,    // min/max range check (=0 apply min/max range limits, =1 accept all passes regardless of range)
     XA_SEN_GEN_SMSEN     =  7,    // is special ground-based mobil sensor flag / column 9 in 1L card (=0 non mobile sensor, =1 mobile sensor) {0, 1}
     
  
     //*******************************************************************************
     
     // sensor location - for all ground-based (or fixed point) sensor types (non-orbiting) 
     XA_SEN_GRN_LOCTYPE   = 10,    // location type (see SENLOC_TYPE_? for available types) 
     XA_SEN_GRN_POS1      = 11,    // sensor location ECR/EFG/ECI X component (km) or LLH/Lat (deg)
     XA_SEN_GRN_POS2      = 12,    // sensor location ECR/EFG/ECI Y component (km) or LLH/Lon (+: East/-: West) (deg)
     XA_SEN_GRN_POS3      = 13,    // sensor location ECR/EFG/ECI Z component (km) or LLH/Height (km)
     XA_SEN_GRN_ASTROLAT  = 14,    // astronomical latitude (deg) (+: North, -: South) [-90, 90]
     XA_SEN_GRN_ASTROLON  = 15,    // astronomical longitude (deg) (+: West, -: East) [-360, 360] 
     XA_SEN_GRN_ECITIME   = 16,    // time of ECI position (ds50UTC) - only when location type = SENLOC_TYPE_ECI
     
     
     //*******************************************************************************
     // sensor limits - for LAMOD only (not needed by Rotas/BatchDC)
     //*******************************************************************************
     // Bounded cone tracker (conical sensor) (VT_BCT)
     XA_SEN_BCT_BRSGHTAZ  = 20,    // conical sensor boresight azimuth angle (deg) [-360, 360]
     XA_SEN_BCT_BRSGHTEL  = 21,    // conical sensor boresight elevation angle (deg) [-90, 90]
     XA_SEN_BCT_HALFANG   = 22,    // coninal sensor off-boresight angle/half cone angle (deg) [0, 90]
     XA_SEN_BCT_MINEL     = 23,    // conical sensor minimum elevation angle (deg) [0, 90] 
     
     //*******************************************************************************
     // Conventinoal tracker (VT_CON)
     XA_SEN_CON_SMSEN     =  7,    // is special mobil sensor flag / column 9 in 1L card (=0 non mobile sensor, =1 mobile sensor) {0, 1}
     XA_SEN_CON_ELFR1     = 20,    // low elevation limit #1 (deg) [
     XA_SEN_CON_ELTO1     = 21,    // high elevation limit #1 (deg)
     XA_SEN_CON_AZFR1     = 22,    // low azimuth limit #1 (deg)
     XA_SEN_CON_AZTO1     = 23,    // high azimuth limit #1 (deg)
     XA_SEN_CON_ELFR2     = 24,    // low elevation limit #2 (deg)
     XA_SEN_CON_ELTO2     = 25,    // high elevation limit #2 (deg)
     XA_SEN_CON_AZFR2     = 26,    // low azimuth limit #2 (deg)
     XA_SEN_CON_AZTO2     = 27,    // high azimuth limit #2 (deg)
        
     //*******************************************************************************
     // Optical tracker (VT_OPT)
     XA_SEN_OPT_ELFR1     = 20,    // low elevation limit #1 (deg)
     XA_SEN_OPT_ELTO1     = 21,    // high elevation limit #1 (deg)
     XA_SEN_OPT_AZFR1     = 22,    // low azimuth limit #1 (deg)
     XA_SEN_OPT_AZTO1     = 23,    // high azimuth limit #1 (deg)
     XA_SEN_OPT_ELFR2     = 24,    // low elevation limit #2 (deg)
     XA_SEN_OPT_ELTO2     = 25,    // high elevation limit #2 (deg)
     XA_SEN_OPT_AZFR2     = 26,    // low azimuth limit #2 (deg)
     XA_SEN_OPT_AZTO2     = 27,    // high azimuth limit #2 (deg)
     
     XA_SEN_OPT_SEA       = 40,    // optical sensor solar exclusion angle (to check for solar aspect angle limit)
     XA_SEN_OPT_TWILGHT   = 41,    // ground site twilight offset angle (deg) [0, 20)
     XA_SEN_OPT_VISCHK    = 42,    // visual pass check (sensor in dark, satellite illuminated)
     
     //*******************************************************************************
     // Constant azimuth fan (VT_FAN)
     XA_SEN_FAN_AZ        = 20,    // fan's constant azimuth (deg) - fan sweeps a vertical plane  [0, 180)
     XA_SEN_FAN_TILTANGLE = 21,    // fan's tilt angle (deg)  (-: North/West tilt, +: South/East tilt) [-90, 90]
     XA_SEN_FAN_OBSANGLE  = 23,    // fan's off-boresight angle (deg) [0, 90]
     
     
     //*******************************************************************************
     // Orbiting sensor (VT_ORB)
     XA_SEN_ORB_SATNUM    = 10,    // orbiting sensor's satellite number
  
     XA_SEN_ORB_ELMIN1    = 20,    // orbiting sensor's off-boresight angle - low elevation limit #1 (deg) [0, 180]
     XA_SEN_ORB_ELMAX1    = 21,    // orbiting sensor's off-boresight angle - high elevation limit #1 (deg) [0, 180]
     XA_SEN_ORB_AZMIN1    = 22,    // orbiting sensor's off-boresight clock angle - low azimuth limit #1 (deg) [-360, 360]
     XA_SEN_ORB_AZMAX1    = 23,    // orbiting sensor's off-boresight clock angle - high azimuth limit #1 (deg) [-360, 360]
     XA_SEN_ORB_ELMIN2    = 24,    // orbiting sensor's off-boresight angle - low elevation limit #2 (deg) [0, 180]
     XA_SEN_ORB_ELMAX2    = 25,    // orbiting sensor's off-boresight angle - high elevation limit #2 (deg) [0, 180]
     XA_SEN_ORB_AZMIN2    = 26,    // orbiting sensor's off-boresight clock angle - low azimuth limit #2 (deg) [-360, 360]
     XA_SEN_ORB_AZMAX2    = 27,    // orbiting sensor's off-boresight clock angle - high azimuth limit #2 (deg) [-360, 360]
     
     XA_SEN_ORB_EARTHLIMB = 40,    // orbiting sensor earth limb exclusion distance (km)
     XA_SEN_ORB_SEA       = 41,    // orbiting sensor solar exclusion angle (deg)
     XA_SEN_ORB_LEA       = 42,    // orbiting sensor lunar exclusion angle (deg)
     XA_SEN_ORB_MINILLUM  = 43,    // orbiting sensor minimum illumination angle (deg) [0, 180)
     XA_SEN_ORB_EARTHBRND = 44,    // orbiting sensor allow earth in the back ground {0, 1}
     XA_SEN_ORB_PLNTRYRES = 45,    // orbiting sensor planetary restriction {0, 1}
     
     //*******************************************************************************
     
     // Space fence Field Of Regard (VT_FOR)
     // Sensor limits are defined in the az/el table file (using XS_SEN_FOR_AZFILE_255_256)
     
     
     //*******************************************************************************
     
     // Space fence Field Of View (VT_FOV)
     XA_SEN_FOV_BEAMWIDTH = 20,    // north/south beam width (deg)
     XA_SEN_FOV_TILTANGLE = 21,    // fence tilt angle (deg)
  
  
     //*******************************************************************************
  
     // Output control parameters (shouldn't be part of sensor data - just for backward compatibility)
     XA_SEN_GEN_UNIT      = 90,    // unit on range/range rate (0= km, km/sec, 1=nm, nm/sec) {0, 1}
     XA_SEN_GEN_INTERVAL  = 91,    // output interval (min)
     XA_SEN_GEN_PTSPERPAS = 92,    // max number of points per pass
  
  
     // sensor sigmas/biases - ROTAS/BATCHDC
     XA_SEN_GEN_AZSIGMA =  110,    // azimuth sigma (deg)
     XA_SEN_GEN_ELSIGMA =  111,    // elevation sigma (deg)
     XA_SEN_GEN_RGSIGMA =  112,    // range sigma (km)
     XA_SEN_GEN_RRSIGMA =  113,    // range-rate sigma (km/sec) 
     XA_SEN_GEN_ARSIGMA =  114,    // az rate sigma (deg/sec)
     XA_SEN_GEN_ERSIGMA =  115,    // el rate sigma (deg/sec)
     XA_SEN_GEN_AZBIAS  =  116,    // azimuth bias (deg)
     XA_SEN_GEN_ELBIAS  =  117,    // elevation bias (deg)
     XA_SEN_GEN_RGBIAS  =  118,    // range bias (km)
     XA_SEN_GEN_RRBIAS  =  119,    // range-rate bias (km/sec)
     XA_SEN_GEN_TIMEBIAS=  120,    // time bias (sec)
     
     
     XA_SEN_SIZE          = 128; 
     
  // Indexes of SENSOR text data in an array of chars 
  // The last two numbers in the field name are the zero-based starting character position and the number of characters in the text field
  static const int     
     XS_SEN_SECCLASS_0_1      =   0,      // sensor security classification (1-character length)
     XS_SEN_VIEWTYPE_1_1      =   1,      // sensor viewing type (1-character length)
     XS_SEN_OBSTYPE_2_1       =   2,      // sensor observation type (1-character length)
     XS_SEN_DSCRPTN_3_24      =   3,      // sensor description/narrative/notes (24-character length)
     XS_SEN_ORB_BSVEC1_27_1   =  27,      // orbiting sensor's boresight vector #1 (1-character length) {'N', 'D', 'U', 'F', 'V', 'A', 'B', 'W', 'L'. 'R'}
     XS_SEN_ORB_BSVEC2_28_1   =  28,      // orbiting sensor's boresight vector #2 (1-character length) {'N', 'D', 'U', 'F', 'V', 'A', 'B', 'W', 'L'. 'R'}
     XS_SEN_FOR_AZFILE_255_256= 255,      // for VT_FOR only, az/el table file path (256-character length)
     
     XS_SEN_LENGTH            = 512;
  
  // Indexes of Sensor data fields
  static const int  
     XF_SENLOC_NUM  = 1,             // Sensor number
     XF_SENLOC_LAT  = 2,             // Sensor location - astronomical longitude (deg) (+=West/-=East)
     XF_SENLOC_LON  = 3,             // Sensor location - astronomical latitude (deg)  (+=North/-=South)
     XF_SENLOC_POSX = 4,             // Sensor ECR position X (km)
     XF_SENLOC_POSY = 5,             // Sensor ECR position Y (km)
     XF_SENLOC_POSZ = 6,             // Sensor ECR position Z (km)
     XF_SENLOC_DESC = 7,             // Sensor description
     XF_SENLOC_ORBSATNUM = 8,        // Orbiting sensor's number (satNum)   
     XF_SENLOC_SECCLASS  = 9,        // Sensor classification   
     
     XF_SENLIM_VIEWTYPE  = 11,       // Sensor view type
     XF_SENLIM_OBSTYPE   = 12,       // Sensor observation type
     XF_SENLIM_UNIT      = 13,       // Unit on range/range rate
     XF_SENLIM_MAXRNG    = 14,       // Max observable range (km)
     XF_SENLIM_MINRNG    = 15,       // Min observable range (km)
     XF_SENLIM_INTERVAL  = 16,       // Output interval (min)
     XF_SENLIM_OPTVISFLG = 17,       // Visual pass control flag
     XF_SENLIM_RNGLIMFLG = 18,       // Range limit control flag 
     XF_SENLIM_PTSPERPAS = 19,       // Max number of points per pass
     XF_SENLIM_RRLIM     = 20,       // Range rate/relative velocity limit (km/sec)
     
     XF_SENLIM_ELLIM1    = 31,       // Elevation limits #1 (low, deg) or orbiting sensor off-boresight angle (low, deg) or conical sensor boresight elvation (deg)
     XF_SENLIM_ELLIM2    = 32,       // Elevation limits #2 (high, deg) or orbiting sensor off-boresight angle (high, deg) or conical sensor boresight minimum angle (deg)
     XF_SENLIM_ELLIM3    = 33,       // Elevation limits #3 (low, deg) or orbiting sensor off-boresight angle (low, deg) or 
     XF_SENLIM_ELLIM4    = 34,       // Elevation limits #4 (high, deg) or orbiting sensor off-boresight angle (high, deg)
     XF_SENLIM_AZLIM1    = 35,       // Azimuth limits #1 (low, deg) or orbiting sensor clock angle (from, deg) or conical sensor boresight azimuth (deg)
     XF_SENLIM_AZLIM2    = 36,       // Azimuth limits #2 (high, deg) or orbiting sensor clock angle (to, deg) or conical sensor off-boresight azimuth angle (deg)
     XF_SENLIM_AZLIM3    = 37,       // Azimuth limits #3 (low, deg) or orbiting sensor clock angle (from, deg)
     XF_SENLIM_AZLIM4    = 38,       // Azimuth limits #4 (high, deg) or orbiting sensor clock angle (to, deg)
     
     
     XF_SENLIM_PLNTRYRES = 52,       // Orbiting sensor planetary restriction
     XF_SENLIM_BOREVEC1  = 53,       // Orbiting sensor boresight vector 1
     XF_SENLIM_BOREVEC2  = 54,       // Orbiting sensor boresight vector 2
     XF_SENLIM_KEARTH    = 55,       // Allow orbiting sensor to view sat against earth background
     XF_SENLIM_ELIMB     = 56,       // Orbiting sensor earth limb exclusion distance (km)
     XF_SENLIM_SOLEXCANG = 57,       // Orbiting sensor solar exclusion angle (deg)   
     XF_SENLIM_LUNEXCANG = 58,       // Orbiting sensor lunar exclusion angle (deg)
     
     
     XF_SENLIM_MINIL     = 59,       // Orbiting sensor min illumination angle (deg)
     XF_SENLIM_TWILIT    = 60,       // Ground site twilight offset angle (deg) 
     XF_SENLIM_SMSEN     = 61,       // Is special mobil sensor flag / column 9 in 1L card
     XF_SENLIM_NUMSEGS   = 62,       // Number of additional segments added to sensor limits
     XF_SENLIM_FILE      = 63,       // Space fence FOR's Az/El table file name
     XF_SENLIM_AZELROWS  = 64;       // Number of rows in space fence FOR's Az/El table 
  
  //*******************************************************************************
     
  // Indexes of sensor location data
  static const int     
     XA_SENLOC_NUM     =  0,       // Sensor nubmer
     XA_SENLOC_LAT     =  1,       // Sensor location - astronomical latitude (deg)  (+=North/-=South)
     XA_SENLOC_LON     =  2,       // Sensor location - astronomical longitude (deg) (+=West/-=East)
     XA_SENLOC_POSX    =  3,       // Sensor ECR position X (km)
     XA_SENLOC_POSY    =  4,       // Sensor ECR position Y (km)
     XA_SENLOC_POSZ    =  5,       // Sensor ECR position Z (km)
     
     XA_SENLOC_SIZE    = 16;   
     
  //*******************************************************************************
     
  // Indexes of Sensor's sigmas   biases data fields
  static const int  
     XAF_SENBS_AZSIGMA =  0,    // azimuth sigma (deg)
     XAF_SENBS_ELSIGMA =  1,    // elevation sigma (deg)
     XAF_SENBS_RGSIGMA =  2,    // range sigma (km)
     XAF_SENBS_RRSIGMA =  3,    // range-rate sigma (km/sec) 
     XAF_SENBS_ARSIGMA =  4,    // az rate sigma (deg/sec)
     XAF_SENBS_ERSIGMA =  5,    // el rate sigma (deg/sec)
  
     XAF_SENBS_AZBIAS  =  8,    // azimuth bias (deg)
     XAF_SENBS_ELBIAS  =  9,    // elevation bias (deg)
     XAF_SENBS_RGBIAS  = 10,    // range bias (km)
     XAF_SENBS_RRBIAS  = 11,    // range-rate bias (km/sec)
     XAF_SENBS_TIMEBIAS= 15,    // time bias (sec)
     
     XAF_SENBS_SIZE    = 16;
  
  // Named constants for different obs types
  static const int  
     OT_RRATE          =  0,    // obs contains range rate only data
     OT_AZEL           =  1,    // obs contains azimuth, elevation data
     OT_AZEL_RNG       =  2,    // obs contains azimuth, elevation, and range data
     OT_AZEL_RNGRRATE  =  3,    // obs contains azimuth, elevation, range, and range rate data
     OT_AZEL_ALL       =  4,    // obs contains azimuth, elevation, range, range rate, azimuth rate, elevation rate, and range acceleration data
     OT_RADEC          =  5,    // obs contains right ascention and declination data
     OT_RNGONLY        =  6,    // obs contains range only data
     OT_AZEL_SENPOS    =  8,    // obs contains azimuth, elevation, and sensor location data
     OT_RADEC_SENPOS   =  9,    // obs contains right ascension, declination, and sensor location data
     OT_VEL            = 10,    // obs contains ECI position and velocity data
     OT_POS            = 11,    // obs contains ECI position data
     OT_STAR           = 12,    // internal use only - new obs type for RA/Dec or Star to be used in FOV/targets
     OT_RF             = 13,    // obs contains TDOA/FDOA data   
     OT_SLR            = 16,    // obs contains Satellite Laser Ranging (SLR) - range only, with tropospheric refraction term data
     OT_M              = 18,    // obs contains azimuth, elevation, sensor location, and range data 
     OT_O              = 19,    // obs contains right ascension, declination, sensor location, and range data
     OT_RRATE_SELOB    =999;    // obs contains range rate only data - for use in obs selection criteria
  
     
// SensorDll's function pointers declaration
extern fnPtrSensorInit                     SensorInit;
extern fnPtrSensorGetInfo                  SensorGetInfo;
extern fnPtrSensorLoadFile                 SensorLoadFile;
extern fnPtrSensorLoadCard                 SensorLoadCard;
extern fnPtrSensorSaveFile                 SensorSaveFile;
extern fnPtrSensorRemove                   SensorRemove;
extern fnPtrSensorRemoveAll                SensorRemoveAll;
extern fnPtrSensorGetCount                 SensorGetCount;
extern fnPtrSensorGetLoaded                SensorGetLoaded;
extern fnPtrSensorGetLocAll                SensorGetLocAll;
extern fnPtrSensorSetLocAll                SensorSetLocAll;
extern fnPtrSensorGetLocField              SensorGetLocField;
extern fnPtrSensorSetLocField              SensorSetLocField;
extern fnPtrSensorGet1L                    SensorGet1L;
extern fnPtrSensorSet1L                    SensorSet1L;
extern fnPtrSensorGet2L                    SensorGet2L;
extern fnPtrSensorSet2L                    SensorSet2L;
extern fnPtrSensorGetLimField              SensorGetLimField;
extern fnPtrSensorSetLimField              SensorSetLimField;
extern fnPtrSensorGetBS                    SensorGetBS;
extern fnPtrSensorSetBS                    SensorSetBS;
extern fnPtrSensorGetBSField               SensorGetBSField;
extern fnPtrSensorSetBSField               SensorSetBSField;
extern fnPtrSensorGetLines                 SensorGetLines;
extern fnPtrSensorGetBSLine                SensorGetBSLine;
extern fnPtrSensorGetOrbSatKey             SensorGetOrbSatKey;
extern fnPtrSensorSetOrbSatKey             SensorSetOrbSatKey;
extern fnPtrSensorLoadAzElTable            SensorLoadAzElTable;
extern fnPtrSensorAddSegment               SensorAddSegment;
extern fnPtrSensorGetSegment               SensorGetSegment;
extern fnPtrSetSenKeyMode                  SetSenKeyMode;
extern fnPtrGetSenKeyMode                  GetSenKeyMode;
extern fnPtrSenNumOf                       SenNumOf;
extern fnPtrSensorGetSenKey                SensorGetSenKey;
extern fnPtrSensorGetSenKeyML              SensorGetSenKeyML;
extern fnPtrSensorAddFrArray               SensorAddFrArray;
extern fnPtrSensorDataToArray              SensorDataToArray;



void LoadSensorDll();
void FreeSensorDll();




#endif
// ========================= End of auto generated code ==========================
