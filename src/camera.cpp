#include "camera.hpp"

Camera::Camera(float view_width, float view_height) {
    viewHeight = view_height;
    viewWidth = view_width;

    cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    cameraDirection = glm::normalize(cameraPosition - cameraTarget);

    cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
    cameraForward = glm::vec3(0.0f, 0.0f, -1.0f);
    
    
    projection = glm::perspective(glm::radians(45.0f), viewWidth / viewHeight, 0.1f, 100.0f);

    view = glm::lookAt(
        cameraPosition, // Camera position
        cameraPosition + cameraForward,   // Look-at point
        cameraUp              // Up direction
    );
}


void Camera::update() {
    cameraDirection = glm::normalize(cameraPosition - cameraTarget);

    cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
    // std::cout << "update in camera" << std::endl;
    view = glm::lookAt(cameraPosition, 
                       cameraPosition + cameraForward, 
                       cameraUp);
}

void Camera::processInput(GLFWwindow *window) {
    // std::cout << "Process incput in camera" << std::endl;
    const float cameraSpeed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition += cameraSpeed * cameraForward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition -= cameraSpeed * cameraForward;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraForward, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraForward, cameraUp)) * cameraSpeed;

    std::cout << "CamPos: " << cameraPosition.x << ", " << cameraPosition.y << ", " << cameraPosition.z << std::endl;
}


// getter functions

glm::vec3 Camera::getPosition() {
    return cameraPosition;
}

glm::vec3 Camera::getRotation() {
    return cameraRotation;
}

glm::mat4 Camera::getView() {
    return view;
}

glm::mat4 Camera::getProjection() {
    return projection;
}


// setter functions

void Camera::setTarget(glm::vec3 target) {
    cameraTarget = target;
    update();
}

void Camera::setPosition(glm::vec3 position) {
    cameraPosition = position;
    update();
}

void Camera::setPosition(float x, float y, float z) {
    setPosition(glm::vec3(x, y, z));
}
