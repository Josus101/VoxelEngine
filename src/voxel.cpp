#include "voxel.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

GLfloat Voxel::voxelVertices[48] = {
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

Voxel::Voxel() 
    : Voxel(glm::vec3(0.0f, 0.0f, 0.0f)) {}

Voxel::Voxel(glm::vec3 pos, glm::vec3 color) 
    : Voxel(pos,glm::vec3(0.0f, 0.0f, 0.0f), color) {}

Voxel::Voxel(glm::vec3 position, glm::vec3 rotation, glm::vec3 color) 
    : position(position), rotation(rotation), color(color) {

    // Initialize model matrix as an identity matrix
    modelMatrix = glm::mat4(1.0f);

    // Set the initial position and update the model matrix
    setPosition(position);

    updateModelMatrix();
    updateVertexColors();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Vertex Buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(voxelVertices), voxelVertices, GL_STATIC_DRAW);

    // Element Buffer (Index Buffer)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(voxelIndices), voxelIndices, GL_STATIC_DRAW);

    // Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // Color Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Voxel::~Voxel() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


void Voxel::updateModelMatrix() {
    modelMatrix = glm::mat4(1.0f);
    // Apply translation first
    modelMatrix = glm::translate(modelMatrix, position);
    // Apply rotations around x, y, and z axes
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    // std::cout << "Model Matrix for voxel at position (" << position.x << ", " << position.y << ", " << position.z << "):\n";
    for(int i = 0; i < 4; ++i) {
        std::cout << modelMatrix[i][0] << " " << modelMatrix[i][1] << " " 
                  << modelMatrix[i][2] << " " << modelMatrix[i][3] << "\n";
    }
}


void Voxel::updateVertexColors() {
    for(int i = 0; i < 8; ++i) {
        voxelVertices[i * 6 + 3] = color.r / 255;
        voxelVertices[i * 6 + 4] = color.g / 255;
        voxelVertices[i * 6 + 5] = color.b / 255;
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(voxelVertices), voxelVertices);
}

// getters
glm::mat4 Voxel::getModelMatrix() const {
    return modelMatrix;
}

glm::vec3 Voxel::getPosition() const {
    return position;
}

glm::vec3 Voxel::getRotation() const {
    return rotation;
}

glm::vec3 Voxel::getColor() const {
    return color;
}

// setters
void Voxel::setPosition(glm::vec3 newPoition) {
    position = newPoition;
    updateModelMatrix();
}

void Voxel::setColor(glm::vec3 newColor) {
    color = newColor;
    updateVertexColors();
}

void Voxel::rotateBy(float x, float y, float z) {
    rotation += glm::vec3(x, y, z);  // Update rotation vector
    updateModelMatrix();
}

void Voxel::render(GLuint shaderProgram) {
    GLint modelLoc = glGetUniformLocation(shaderProgram, "modelMatrix");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
