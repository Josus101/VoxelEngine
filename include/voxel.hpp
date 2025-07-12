#ifndef VOXEL_HPP
#define VOXEL_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Voxel {
private:
    GLuint VAO, VBO, EBO;
    glm::mat4 modelMatrix;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 color; // switch to texture index in future

    void updateModelMatrix();
    void updateVertexColors();

    static GLfloat voxelVertices[48];

    static constexpr GLuint voxelIndices[36] = {
        0, 2, 1,  0, 3, 2,  // Front face
        4, 7, 6,  4, 6, 5,  // Back face
        3, 4, 5,  3, 5, 2,  // Left face
        7, 0, 1,  7, 1, 6,  // Right face
        7, 4, 3,  7, 3, 0,  // Top face
        2, 5, 6,  2, 6, 1   // Bottom face
    };

public:
    Voxel();
    Voxel(glm::vec3 pos, glm::vec3 color = {46.0f, 158.0f, 24.0f});
    Voxel(glm::vec3 pos, glm::vec3 rot, glm::vec3 color = {46.0f, 158.0f, 24.0f}) ;
    ~Voxel();
    void initialize();
    void render(GLuint shaderProgram);
    void rotateBy(float x, float y, float z);
    void setPosition(glm::vec3 newPoition);
    void setColor(glm::vec3 newColor);
    glm::mat4 getModelMatrix() const;
    glm::vec3 getPosition() const;
    glm::vec3 getRotation() const;
    glm::vec3 getColor() const;
};

#endif // VOXEL_HPP
