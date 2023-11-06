#ifndef TERRAIN_HEIGHT_MAP_H
#define TERRAIN_HEIGHT_MAP_H

#include <string>
#include "terrain.h"

struct TerrainHeightMap : Terrain {
    TerrainHeightMap(const std::string& path);
    virtual ~TerrainHeightMap();

    void init_height();



};

#endif

