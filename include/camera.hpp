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

        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);
        
        glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
        glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
        glm::vec3 cameraForward = glm::vec3(0.0f, 0.0f, -1.0f);


        glm::mat4 projection;
        glm::mat4 view;

    public:
        Camera(float view_width, float view_height);
        void update();
        void processInput(GLFWwindow *window);


        // getter functions
        glm::vec3 getPosition();
        glm::vec3 getRotation();

        glm::mat4 getView();
        glm::mat4 getProjection();

        
        // setter funcitons
        void setTarget(glm::vec3 target); 
        void setPosition(glm::vec3 position);
        void setPosition(float x, float y, float z);
};
