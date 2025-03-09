cmake_minimum_required(VERSION 3.10)
project(VoxelEngine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Include directories
include_directories(include)
include_directories(/opt/homebrew/include)

# Add executable
add_executable(voxelengine src/main.cpp src/voxel.cpp src/glad.c src/shader.cpp src/camera.cpp)

# Link libraries
target_link_libraries(voxelengine glfw OpenGL::GL)
