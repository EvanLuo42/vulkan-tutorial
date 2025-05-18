//
// Created by Evan Luo on 5/18/25.
//

#include "Application.h"

#include <GLFW/glfw3.h>
#include <iostream>

void Application::run() {
    initWindow();
    initVulkan();
    mainLoop();
}

void Application::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void Application::mainLoop() const {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

void Application::initVulkan() {
    createInstance();
}

void Application::createInstance() {
    try {
        const vk::raii::Context context;
        vk::ApplicationInfo applicationInfo{"Vulkan Triangle", VK_MAKE_VERSION(1, 0, 0), "Vulkan.hpp",
                                            VK_MAKE_VERSION(1, 0, 0), VK_API_VERSION_1_1};

        constexpr vk::InstanceCreateFlags flags = vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR;
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        std::vector<const char*> extensions;
        extensions.reserve(glfwExtensionCount);
        for(uint32_t i = 0; i < glfwExtensionCount; i++) {
            extensions.emplace_back(glfwExtensions[i]);
        }

        extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

        const vk::InstanceCreateInfo instanceCreateInfo{flags, &applicationInfo, 0, nullptr, static_cast<uint32_t>(extensions.size()), extensions.data()};
        const vk::raii::Instance instance{context, instanceCreateInfo};
        this->vkInstance = instance;
    } catch (vk::SystemError &err) {
        std::cerr << "vk::SystemError: " << err.what() << std::endl;
        exit(-1);
    } catch ( std::exception & err ) {
        std::cerr << "std::exception: " << err.what() << std::endl;
        exit( -1 );
    } catch ( ... ) {
        std::cerr << "unknown error\n";
        exit( -1 );
    }
}

