#include "terrain_heightmap.h"
#include "utils.h"
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION_H
#include "stb_image.h"

TerrainHeightMap::TerrainHeightMap(const std::string& path):Terrain(){
    int channels;
    unsigned char* data = stbi_load(path.c_str(), &cols, &rows, &channels, 0);

    init_x_z();

    float y_scale = 64.0f / 256.0f;
    float y_shift = 16.0f;


    LinearInterpolator interpolator(0.0f, 255.0f, 0.0f, 0.1f);


    for(int z = 0; z < rows; z += 1) {
        for(int x = 0; x < cols; x += 1) {
            unsigned char* texel = data + (x + cols * z) * channels;
            float y = (float)texel[0];
            Vertex vertex = get_vertex(x, z);
            vertex.position.y = interpolator.map(y);
            set_vertex(x, z, vertex);

        }

    }

    init_mesh();

}

TerrainHeightMap::~TerrainHeightMap() {

}

void TerrainHeightMap::init_height() {
}


