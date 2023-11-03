#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <cstdlib>
#include <glm/glm.hpp>


class Shader;

struct Vertex {
    float pos_x;
    float pos_y;
    float pos_z;

    Vertex(float x=0.0f, float y=0.f, float z=0.0f);
};

glm::vec2 generate_random_point(int min, int max);
std::vector<float> generate_terrain(int iteration, int size);
std::vector<float> normalize(std::vector<float>& vertices);

struct TerrainQuad {
    TerrainQuad(float x, float z);

    std::vector<Vertex> vertices;

};

struct Terrain {

    Terrain(int rows, int cols);
    virtual ~Terrain();

    void render();
    void init_mesh();

    void set_vertex(int row, int  col, Vertex vertex);
    Vertex get_vertex(int row, int col);
    int rows;
    int cols;

    std::vector<Vertex> vertices;

    
    unsigned int VAO;
    unsigned int VBO;

    Shader* m_shader;




};


#endif
