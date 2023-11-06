#include "terrain_heightmap.h"
#include "utils.h"
#include <fstream>
#include <iostream>

TerrainHeightMap::TerrainHeightMap(const std::string& path):Terrain(){

    std::ifstream input_file(path, std::ios::in);

    if(!input_file.is_open()) {
        std::cerr << "Failed to open " << path << "\n";
        exit(1);
    }

    std::string line;
    std::getline(input_file, line);
    std::vector<std::string> info = split(line, ' ');

    rows = stoi(info[0]);
    cols = stoi(info[1]);
    init_x_z();
    std::cout << rows << " " << cols << "\n";

    LinearInterpolator interpolator(0.0f, 255, 0.0f, 0.75f);

    int row = 0;

    while(std::getline(input_file, line)) {

        std::getline(input_file, line);
        std::vector<std::string> data = split(line, ' ');

        for(int col = 0; col < cols; col += 1) {
            Vertex vertex = get_vertex(col, row);;
            int y = stoi(data[col]);
            vertex.position.y = interpolator.map(y);
            set_vertex(col, row, vertex);

        }






        row += 1;
    }






    init_mesh();
}

TerrainHeightMap::~TerrainHeightMap() {

}

void TerrainHeightMap::init_height() {
}


