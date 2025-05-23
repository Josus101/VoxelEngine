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
    glm::vec3 color;

    void updateModelMatrix();
    void updateVertexColors();

    // GLfloat voxelVertices[48] = {
    //     // Positions        // Colors
    //     -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // 0: Bottom-left (back)
    //      0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // 1: Bottom-right (back)
    //      0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // 2: Top-right (back)
    //     -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // 3: Top-left (back)

    //     -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // 4: Bottom-left (front)
    //      0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // 5: Bottom-right (front)
    //      0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // 6: Top-right (front)
    //     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f   // 7: Top-left (front)
    // };

    static GLfloat voxelVertices[48];

    static constexpr GLuint voxelIndices[36] = {
        0, 1, 2,  2, 3, 0,  // Back face
        4, 5, 6,  6, 7, 4,  // Front face
        0, 4, 7,  7, 3, 0,  // Left face
        1, 5, 6,  6, 2, 1,  // Right face
        3, 7, 6,  6, 2, 3,  // Top face
        0, 4, 5,  5, 1, 0   // Bottom face
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
