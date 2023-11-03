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


Terrain::Terrain(int size):size(size) {
    m_shader = new Shader("../shaders/triangle.vs", "../shaders/triangle.fs");


    for(int z = 0; z < size; z += 1) {
        std::vector<Vertex> row;

        for(int x = 0; x < size; x += 1)  {
            Vertex vertex = Vertex(x, 0.0f, z);
            row.push_back(vertex);
        }

        vertices.push_back(row);
    }

    std::cout << "Vertices size " << vertices.size() << "\n";



}

Terrain::~Terrain() {

}

void Terrain::init_mesh() {
    std::vector<float> vertices_list;

    for(int z = 0; z < size; z += 1) {
        for(int x = 0; x < size; x += 1)  {
            Vertex vertex = vertices[z][x];


            vertices_list.push_back(vertex.pos_x);
            vertices_list.push_back(vertex.pos_y);
            vertices_list.push_back(vertex.pos_z);

        }

    }

    for(int i = 0; i < 100; i += 1)  {
        std::cout << vertices_list[i] << " ";

        if((i + 1) % 3 == 0 )
            std::cout << "\n";

    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices_list.size() * sizeof(float), &vertices_list[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


}

void Terrain::render() {

    glm::mat4 projection = Camera::get_instance()->projection;
    glm::mat4 view = Camera::get_instance()->get_view_matrix();
    glm::mat4 position = glm::mat4(1.0f);
    position = glm::translate(position, glm::vec3(0.0f));


    m_shader->setMat4("projection", projection);
    m_shader->setMat4("view", view);
    m_shader->setMat4("model", position);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, size * size);

}
