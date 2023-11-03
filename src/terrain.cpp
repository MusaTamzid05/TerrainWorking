#include "terrain.h"
#include <iostream>
#include <algorithm>
#include <glad/glad.h>
#include "shader.h"
#include "camera.h"
#include "glm/gtc/matrix_transform.hpp"


Vertex::Vertex(float x, float y, float z):
    pos_x(x),
    pos_y(y),
    pos_z(z) {

    }


std::vector<float> generate_terrain(int iteration, int size) {

    std::vector<float> vertices;
    vertices.resize(size * size);

    float min_height = 0.0f;
    float max_height = 255.0f;
    float delta_height = max_height - min_height;


    for(int i = 0; i < iteration; i += 1) {
        float iteration_ratio = (float)i / iteration;

        float height = max_height - (iteration_ratio * delta_height);

        glm::vec2 start = generate_random_point(0, size);
        glm::vec2 end = generate_random_point(0, size);
        glm::vec2 dir = end - start;

        for(int z = 0; z < size; z += 1) {
            for(int x = 0; x < size; x += 1) {
                glm::vec2 current_dir = glm::vec2(end.y - z, end.x - x);
                float cross_product = current_dir.x * dir.y - dir.x * current_dir.y;

                if(cross_product > 0.0f) {
                    vertices[(z * size) + x] += height;
                }

            }
        }

    }

    return vertices;

}

std::vector<float> normalize(std::vector<float>& vertices) {
    float max = *std::max_element(vertices.begin(), vertices.end());

    for(int i = 0; i < vertices.size(); i += 1) {
        vertices[i] = vertices[i] / max;

    }

    return vertices;
}


glm::vec2 generate_random_point(int min, int max) {
    return glm::vec2(
            (rand() % max) + min,
            (rand() % max) + min
            );
}


Terrain::Terrain(int rows, int cols):rows(rows), cols(cols) {
    // terrain use nps coordinate system where 0,0 is left bottom,
    // 1,1 is right top
    m_shader = new Shader("../shaders/triangle.vs", "../shaders/triangle.fs");

    for(int i = 0; i < (rows * cols); i += 1)
        vertices.push_back(Vertex());


}

Terrain::~Terrain() {

}

void Terrain::init_mesh() {

    float x = 0.0f;
    float z = 0.0f;


    /*
    vertices[0] = Vertex(x, z,  0.0f);
    vertices[1] = Vertex(x + 1.0f, z,  0.0f);
    vertices[2] = Vertex(x + 1, z + 1,  0.0f);
    */


    for(int col = 0; col < cols; col += 1) {
        for(int row = 0; row < rows; row += 1) {
            Vertex vertex = Vertex((float)col / cols, (float)row / rows, 0.0f);
            set_vertex(row, col, vertex);

        }
    }


    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}

void Terrain::render() {
    m_shader->use();

    glm::mat4 projection = Camera::get_instance()->projection;
    glm::mat4 view = Camera::get_instance()->get_view_matrix();
    glm::mat4 position = glm::mat4(1.0f);
    position = glm::translate(position, glm::vec3(0.0f));


    m_shader->setMat4("projection", projection);
    m_shader->setMat4("view", view);
    m_shader->setMat4("model", position);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);

}

void Terrain::set_vertex(int row, int  col, Vertex vertex) {
    vertices[(col * cols) + row] = vertex;

}

Vertex Terrain::get_vertex(int row, int col) {
    return vertices[(col * cols) + row];
}
