#include "terrain.h"
#include <iostream>
#include <algorithm>
#include <glad/glad.h>
#include "shader.h"
#include "camera.h"
#include "utils.h"
#include "glm/gtc/matrix_transform.hpp"



Terrain::Terrain(int size):rows(size), cols(size) {
    m_shader = new Shader("../shaders/terrain.vs", "../shaders/terrain.fs");

    if(size == -1)
        return;

    init_x_z();
    init_mesh();



}

Terrain::~Terrain() {

}


void Terrain::init_x_z() {
    vertices.resize(rows * cols);
    int size = rows; // row and col are same so it does not matter

    int vertex_index = 0;

    LinearInterpolator interpolator_row(0.0f, rows, -1.0f, 1.0f);
    LinearInterpolator interpolator_col(0.0f, cols, -1.0f, 1.0f);

    for(int row = 0; row < rows; row += 1) {
        for(int col = 0; col < cols; col += 1) {

            Vertex vertex;

            float x = (float)col;
            float z = (float)row;



            x = interpolator_col.map(x);
            z = interpolator_row.map(z);


            glm::vec3 position = glm::vec3(x, 0.0f, z);


            vertex.position = position;

            vertices[vertex_index] = vertex;
            vertex_index += 1;
        }
    }







    indices.resize((rows- 1) * (cols - 1) * 6 );
    int index = 0;

    for(int z = 0; z < rows - 1; z += 1) {
        for(int x = 0; x < cols - 1; x += 1) {
            unsigned int index_bottom_left = z * cols + x;
            unsigned int index_top_left =  (z + 1) * cols + x;
            unsigned int index_top_right =  (z + 1) * cols + x + 1;
            unsigned int index_bottom_right =  z  * cols + x + 1;


            // top left
            indices[index++] = index_bottom_left;
            indices[index++] = index_top_left;
            indices[index++] = index_top_right;


            // top right
            indices[index++] = index_bottom_left;
            indices[index++] = index_top_right;
            indices[index++] = index_bottom_right;

        }

    }








}

void Terrain::init_mesh() {
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);


    glGenBuffers(1, &EBO);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int ), indices.data(), GL_STATIC_DRAW);


}

void Terrain::set_vertex(int col, int row, const Vertex& vertex) {
    vertices[(row * cols) + col] = vertex;


}

Vertex Terrain::get_vertex(int col, int row) const {
    return vertices[(row * cols) + col];
}



void Terrain::render() {
    m_shader->use();

    glm::mat4 projection = Camera::get_instance()->projection;
    glm::mat4 view = Camera::get_instance()->get_view_matrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
    //model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
    model = glm::scale(model, glm::vec3(5.0, 5.0, 5.0));


    m_shader->setMat4("projection", projection);
    m_shader->setMat4("view", view);
    m_shader->setMat4("model", model);

    glBindVertexArray(VAO);
    //glDrawArrays(GL_POINTS, 0, vertices.size());
    //glDrawElements(GL_POINTS, triangle_indices.size() * 3, GL_UNSIGNED_INT, 0);
    //glDrawElements(GL_POINTS, (rows - 1) * (cols -1) * 6, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, (rows - 1) * (cols -1) * 6, GL_UNSIGNED_INT, 0);


}
