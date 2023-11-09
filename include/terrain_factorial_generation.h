#ifndef TERRAIN_FACTORIAL_GENERATION_H
#define TERRAIN_FACTORIAL_GENERATION_H

#include "terrain.h"

struct FactorialTerrainGeneration : Terrain {
    FactorialTerrainGeneration(int cols, int rows, int iterations, float min_height, float max_height);
    virtual ~FactorialTerrainGeneration();




};

#endif
