cmake_minimum_required(VERSION 3.31)
project(vulkan_tutorial)

set(CMAKE_CXX_STANDARD 23)

add_executable(vulkan_tutorial main.cpp
        application.cpp
        Application.h
)

find_package(Vulkan REQUIRED)
target_link_libraries(vulkan_tutorial PRIVATE Vulkan::Vulkan)

find_package(glm CONFIG REQUIRED)
target_link_libraries(vulkan_tutorial PRIVATE glm::glm)

find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(vulkan_tutorial PRIVATE glfw)
