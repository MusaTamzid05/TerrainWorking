#include "terrain.h"
#include <iostream>
#include <algorithm>
#include <glad/glad.h>
#include "shader.h"
#include "camera.h"
#include "utils.h"
#include "glm/gtc/matrix_transform.hpp"



Terrain::Terrain(int size):rows(size), cols(size) {
    m_shader = new Shader("../shaders/triangle.vs", "../shaders/triangle.fs");
    vertices.resize(rows * cols);

    int vertex_index = 0;

    LinearInterpolator interpolator(0.0f, size, -1.0f, 1.0f);

    for(int row = 0; row < rows; row += 1) {
        for(int col = 0; col < cols; col += 1) {

            Vertex vertex;

            float x = (float)col;
            float z = (float)row;



            x = interpolator.map(x);
            z = interpolator.map(z);


            glm::vec3 position = glm::vec3(x, 0.0f, z);

            vertex.position = position;

            vertices[vertex_index] = vertex;
            vertex_index += 1;
        }
    }

    for(int i = 0; i < vertices.size() - (rows + 2); i +=1) {
        glm::uvec3 top_triangle = glm::uvec3(i, i + 1, i + rows);
        glm::uvec3 bottom_triangle = glm::uvec3(i + 1, i + rows, i + rows + 1);

        triangle_indices.push_back(top_triangle);
        triangle_indices.push_back(bottom_triangle);

    }



    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);


    glGenBuffers(1, &EBO);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangle_indices.size() * sizeof(glm::uvec3), triangle_indices.data(), GL_STATIC_DRAW);


    

    for(int i = 0; i < 30; i += 1) {
        Vertex vertex = vertices[i];
        std::cout << vertex.position.x << " " << vertex.position.y << " " << vertex.position.z <<  "\n";

    }



}

Terrain::~Terrain() {

}


void Terrain::render() {
    m_shader->use();

    glm::mat4 projection = Camera::get_instance()->projection;
    glm::mat4 view = Camera::get_instance()->get_view_matrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
    //model = glm::scale(model, glm::vec3(5.0, 5.0, 5.0));


    m_shader->setMat4("projection", projection);
    m_shader->setMat4("view", view);
    m_shader->setMat4("model", model);

    glBindVertexArray(VAO);
    //glDrawArrays(GL_POINTS, 0, vertices.size());
    //glDrawElements(GL_POINTS, triangle_indices.size() * 3, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLES, triangle_indices.size() * 3, GL_UNSIGNED_INT, 0);


}
