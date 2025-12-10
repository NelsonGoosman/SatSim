#pragma once

#include <vector>
#include <string>
#include "../dataLoader/entity.h"

/* propagate all sats to a given date*/
void batch_propagate_sgp4(std::vector<Entity>& sats, double ds50);

void worker_propagate_sgp4(std::vector<Entity>& sats, size_t start, size_t end, double ds50UTC);

