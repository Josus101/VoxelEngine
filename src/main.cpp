#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../include/voxel.hpp"
#include "../include/shader.hpp"
#include "../include/camera.hpp"

#define WIDTH 1920.0f
#define HEIGHT 1080.0f

float lastX = WIDTH  / 2.0f;
float lastY = HEIGHT / 2.0f;

GLboolean firstMouse = true;
static bool mouseLocked = true;


std::unique_ptr<Camera> cam;
std::vector<std::unique_ptr<Voxel>> voxels;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    if(!mouseLocked) return;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    cam->processMouseInput(xoffset, yoffset);
}



int main() {
    // std::cout << "main called" << std::endl;
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

    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, mouseCallback);

    // Capture the mouse input
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);  // Cull back-facing polygons
    glFrontFace(GL_CCW);  // Counter-clockwise vertices define the front face

    // Initialize the camera and voxel after OpenGL context is ready
    cam = std::make_unique<Camera>(WIDTH, HEIGHT);

    int gridSize = 10;
    float spacing = 1.0f;
    for (int x = 0; x < gridSize; x++) {
        for (int y = 0; y < 2; y++) {
            for (int z = 0; z < gridSize; z++) {
                glm::vec3 pos(x * spacing, y * spacing, z * spacing);
                // std::cout << "Voxel Position: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
                voxels.push_back(std::make_unique<Voxel>(pos, glm::vec3(0.0f), glm::vec3(46.0f, 158.0f, 24.0f)));
            }
        }
    }

    GLuint shaderProgram = createShaderProgram("../include/vertex_shader.glsl", "../include/fragment_shader.glsl");
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    if (modelLoc == -1) {
        std::cerr << "Error: modelMatrix uniform not found in shader!" << std::endl;
    }
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLuint projLoc = glGetUniformLocation(shaderProgram, "projection");

    bool isWireframe = false;
    bool wKeyPressed = false;

    float deltaTime = 0.0f;
    float currentFrame = 0.0f;
    float lastFrame = 0.0f;


    glClearColor(15.0f / 255.0f, 68.0f / 255.0f, 191.0f / 255.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // std::cout << "fps: " << 1/deltaTime << std::endl;

        // Handle input for camera
        cam->processKeyboardInput(window, deltaTime);

        // Update camera values
        cam->update();
        

    

        // Toggle wireframe mode using 'W' key
        if(glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && !wKeyPressed) {
            isWireframe = !isWireframe;
            wKeyPressed = true;
        }
        if(glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE) {
            wKeyPressed = false;
        }

        if (isWireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Wireframe mode
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Solid mode
        }

        // Toggle locked/free mouse
        if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) { 
            if (mouseLocked) {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            } else {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                firstMouse = true;
            }
            mouseLocked = !mouseLocked; 
            // Add a small delay to prevent multiple toggles per press
            glfwWaitEventsTimeout(0.2); 
        }


        

        // Set the shader program
        glUseProgram(shaderProgram);
        // Update model, view, and projection matrices
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(cam->getView()));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(cam->getProjection()));

        for (auto& voxel : voxels) {
            // Update the model matrix uniform for each voxel
            glm::mat4 model = voxel->getModelMatrix();
            // for (int i = 0; i < 4; ++i) {
            //     std::cout << model[i][0] << " " << model[i][1] << " " << model[i][2] << " " << model[i][3] << "\n";
            // }            
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glm::vec3 pos = voxel->getPosition();
            std::cout << "Voxel pos: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;

            // Render voxel
            voxel->render(shaderProgram, cam->getCameraForward());
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}