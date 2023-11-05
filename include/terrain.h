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

    int rows;
    int cols;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;





};


#endif
