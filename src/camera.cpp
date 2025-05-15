#include "../include/camera.hpp"

Camera::Camera(float view_width, float view_height) {
    viewWidth = view_width;
    viewHeight = view_height;
    cameraPosition = glm::vec3(0.0f, 0.5f, 3.0f);
    cameraRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    
    pitch = 0.0f;
    yaw = -90.0f;

    movementSpeed = 2.5f;
    mouseSensitivity = 0.1f;

    // Initialize the camera direction
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraForward = glm::normalize(front);

    // also re-calculate the Right and Up vector
    cameraRight = glm::normalize(glm::cross(cameraForward, up));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraForward));

    // Initialize the projection matrix
    projection = glm::perspective(glm::radians(45.0f), viewWidth / viewHeight, 0.1f, 100.0f);

    // Initialize the view matrix
    view = glm::lookAt(
        cameraPosition,
        cameraPosition + cameraForward,
        cameraUp
    );

    // std::cout << "Camera initialized" << std::endl;
}


void Camera::update() {
    // calculate the new Front vector
    // std::cout << "camerea update" << std::endl;
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraForward = glm::normalize(front);
    if (glm::length(cameraForward) == 0.0f) {
        cameraForward = glm::vec3(0.0f, 0.0f, -1.0f); // Default forward direction
    }
    // also re-calculate the Right and Up vector
    cameraRight = glm::length(cameraForward) > 0 ? glm::normalize(glm::cross(cameraForward, up)) : glm::vec3(1.0f, 0.0f, 0.0f);
    cameraUp = glm::length(cameraRight) > 0 ? glm::normalize(glm::cross(cameraRight, cameraForward)) : glm::vec3(0.0f, 1.0f, 0.0f);


    // Update the view matrix with the new orientation
    view = glm::lookAt(cameraPosition, 
                       cameraPosition + cameraForward, 
                       cameraUp);
}


// camera movement - keyboard input
void Camera::processKeyboardInput(GLFWwindow *window, float deltaTime) {
    // std::cout << "Keyboard input" << std::endl;
    const float cameraSpeed = movementSpeed * deltaTime;
    // WASD
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraRight, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraRight, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPosition -= glm::normalize(glm::cross(cameraForward, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPosition += glm::normalize(glm::cross(cameraForward, cameraUp)) * cameraSpeed;

    // UP and DOWN
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPosition += glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPosition -= glm::vec3(0.0f, 1.0f, 0.0f) * cameraSpeed;
    

    // Sprint
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        movementSpeed = 5.0f;  // Run
    else
        movementSpeed = 2.5f;  // Walk


    // std::cout << "CamPos: " << cameraPosition.x << ", " << cameraPosition.y << ", " << cameraPosition.z << std::endl;
}

// camera rotation - mouse input
void Camera::processMouseInput(float xOffset, float yOffset, GLboolean constrainPitch) {
    // std::cout << "mouse input" << std::endl;
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch += yOffset;

    // Constrain the pitch to prevent gimbal lock
    if (constrainPitch) {
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;
    }

    update();  // Update the camera vectors after changing yaw and pitch
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
