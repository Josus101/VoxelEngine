#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "voxel.hpp"
#include "shader.hpp"
#include "camera.hpp"

#define WIDTH 1920.0f
#define HEIGHT 1080.0f

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow((int)WIDTH, (int)HEIGHT, "Voxel Engine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Camera setup
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), WIDTH / HEIGHT, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(
        glm::vec3(3.0f, 2.0f, 3.0f), // Camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // Look-at point
        glm::vec3(0.0f, 1.0f, 0.0f)  // Up direction
    );

    Voxel voxel;
    Camera cam(WIDTH, HEIGHT);

    // cam.setPosition(3.0f, 1.0f, 3.0f);

    GLuint shaderProgram = createShaderProgram("../include/vertex_shader.glsl", "../include/fragment_shader.glsl");
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLuint projLoc = glGetUniformLocation(shaderProgram, "projection");

    bool isWireframe = false;
    bool wKeyPressed = false;  // Tracks W key state
    
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // handle input for camera
        cam.processInput(window);

        // update camera values
        cam.update();

        // Toggle wireframe mode using 'W' key
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !wKeyPressed) {
            isWireframe = !isWireframe;
            wKeyPressed = true;
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
            wKeyPressed = false;
        }

        if (isWireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Wireframe mode
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Solid mode
        }

        glm::mat4 model = glm::mat4(1.0f);
        glUseProgram(shaderProgram);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cam.getView()));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(cam.getProjection()));

        voxel.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }




    glfwTerminate();
    return 0;
}
