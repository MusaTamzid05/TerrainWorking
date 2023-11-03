#include "triangle.h"
#include "shader.h"
#include "camera.h"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>

TriangleMesh::TriangleMesh() {
	
	float vertices[] = {
		 -0.5f, -0.5f, 0.f,  // bottom right
		  0.5f, -0.5f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f   // top left
	}; 

    std::vector<float> test(vertices, vertices + sizeof(vertices) / sizeof(vertices[0]));

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, test.size() * sizeof(float), &test[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


}

void TriangleMesh::render() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

}


Triangle::Triangle() {
    m_shader = new Shader("../shaders/triangle.vs", "../shaders/triangle.fs");
}

Triangle::~Triangle() {
    delete m_shader;
}

void Triangle::render() {
    m_shader->use();

    glm::mat4 projection = Camera::get_instance()->projection;
    glm::mat4 view = Camera::get_instance()->get_view_matrix();
    glm::mat4 position = glm::mat4(1.0f);
    position = glm::translate(position, glm::vec3(0.0f));


    m_shader->setMat4("projection", projection);
    m_shader->setMat4("view", view);
    m_shader->setMat4("model", position);

    mesh.render();


}
