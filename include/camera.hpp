#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


class Camera {
    private:
        float viewWidth, viewHeight;

        glm::vec3 cameraPosition;
        glm::vec3 cameraRotation;
        glm::vec3 cameraTarget;

        float pitch;
        float yaw;

        float movementSpeed;
        float mouseSensitivity;

        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 cameraDirection;
        
        glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
        glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
        glm::vec3 cameraForward = glm::vec3(0.0f, 0.0f, -1.0f);


        glm::mat4 projection;
        glm::mat4 view;

        // void updateCameraVectors();

    public:
        Camera(float view_width, float view_height);
        void update();
        
        void processKeyboardInput(GLFWwindow *window, float deltaTime);
        void processMouseInput(float xoffset, float yoffset, GLboolean constrainPitch = true);


        // getter functions
        glm::vec3 getPosition();
        glm::vec3 getRotation();

        glm::vec3 getCameraForward();

        glm::mat4 getView();
        glm::mat4 getProjection();

    

        
        // setter funcitons
        void setTarget(glm::vec3 target); 
        void setPosition(glm::vec3 position);
        void setPosition(float x, float y, float z);
};
