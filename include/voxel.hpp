#ifndef VOXEL_HPP
#define VOXEL_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Voxel {
private:
    GLuint VAO, VBO, EBO; // OpenGL buffers
    glm::mat4 modelMatrix; // Model transformation matrix
    glm::vec3 rotation;    // Rotation vector (x, y, z)

    void updateModelMatrix();

    static constexpr GLfloat voxelVertices[48] = {
        // Positions        // Colors
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // 0: Bottom-left (back)
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // 1: Bottom-right (back)
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // 2: Top-right (back)
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  // 3: Top-left (back)

        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // 4: Bottom-left (front)
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // 5: Bottom-right (front)
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  // 6: Top-right (front)
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f   // 7: Top-left (front)
    };

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
    ~Voxel();
    void render();
    void rotateBy(float x, float y, float z);  // Rotation function
    glm::mat4 getModelMatrix() const;
};

#endif // VOXEL_HPP
