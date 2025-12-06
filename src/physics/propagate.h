#pragma once

#include <vector>
#include <string>
#include "../dataLoader/entity.h"

/* propagate all sats to a given date*/
void batch_propagate_sgp4(std::vector<Entity>& sats, double ds50);



