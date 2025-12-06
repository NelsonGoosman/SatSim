#pragma once
#include <vector>
#ifdef __cplusplus
extern "C" 
{
#endif
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/services/DllMainDll_Service.h"
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/services/TimeFuncDll_Service.h"
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/wrappers/DllMainDll.h"
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/wrappers/TimeFuncDll.h"
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/wrappers/TleDll.h"
#include "../../Sgp4Prop/SampleCode/C/DriverExamples/wrappers/Sgp4PropDll.h"

#ifdef __cplusplus
}
#endif

#include "../dataLoader/entity.h"

/**
 * @brief Initializes SGP4 propagation for a list of entities by parsing their TLE data
 *        and adding them to the SGP4 propagator using multithreading.
 * @param source A vector of Entity objects containing TLE data to be initialized.
 */
void init_sgp4(std::vector<Entity>& source);

/**
 * @brief Worker function to process a subset of entities for SGP4 initialization.
 * @param in A reference to the vector of Entity objects.
 * @param start The starting index of the subset to process.
 * @param end The ending index of the subset to process.
 */
void worker(std::vector<Entity>& in, size_t start, size_t end);

/**
 * @brief Parses the epoch string from TLE data into year and day of year.
 * @param epoch The epoch string in the format "YYYY-MM-DDTHH:MM:SS.ssssss".
 * @param year Output parameter for the parsed year.
 * @param day_of_year Output parameter for the parsed day of year.
 */

void parse_epoch_to_year_doy(const std::string& epoch, int& year, double& day_of_year);
/**
 * @brief Checks if a given year is a leap year.
 * @param year The year to check.
 */
inline bool is_leap(int year);