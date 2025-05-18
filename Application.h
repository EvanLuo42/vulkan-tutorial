//
// Created by Evan Luo on 5/18/25.
//

#pragma once

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_raii.hpp>

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class Application {
public:
    void run();
    ~Application() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
private:
    GLFWwindow *window = nullptr;
    vk::Instance vkInstance = nullptr;
    vk::raii::Context vkContext;

    void initWindow();
    void initVulkan();
    void createInstance();
    void mainLoop() const;
};
