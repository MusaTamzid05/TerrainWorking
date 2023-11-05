#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <cstdlib>
#include <glm/glm.hpp>


class Shader;

struct Vertex {
    glm::vec3 position;
};



struct Terrain {

    Terrain(int size);
    virtual ~Terrain();

    void render();

    Shader* m_shader;
    

    std::vector<Vertex> vertices;
    std::vector<glm::uvec3> triangle_indices;

    int rows;
    int cols;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;





};


#endif
