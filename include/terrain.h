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

    Terrain(int size=-1);
    virtual ~Terrain();

    void init_x_z();
    void init_mesh();


    void set_vertex(int col, int row, const Vertex& vertex);
    Vertex get_vertex(int col, int row) const;




    void render();

    Shader* m_shader;
    

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    int rows;
    int cols;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;





};


#endif
