//
// Created by Evan Luo on 5/18/25.
//

#include "Application.h"

#include <GLFW/glfw3.h>
#include <iostream>

void Application::run()
{
    initWindow();
    initVulkan();
    mainLoop();
}

void Application::initWindow()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void Application::mainLoop() const
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
}

bool Application::checkValidationLayerSupport()
{
    const auto availableLayers = vkContext.enumerateInstanceLayerProperties();

    return std::ranges::all_of(validationLayers, [&](const char *layerName) {
        return std::ranges::any_of(availableLayers, [&](const VkLayerProperties &prop) {
            return std::strcmp(layerName, prop.layerName) == 0;
        });
    });
}

void Application::initVulkan()
{
    createInstance();
}

void Application::createInstance()
{
#ifdef ENABLE_VALIDATION_LAYERS
    if (enableValidationLayers && !checkValidationLayerSupport())
    {
        throw std::runtime_error("Validation layers requested, but not available!");
    }
#endif
    constexpr vk::ApplicationInfo applicationInfo{"Vulkan Triangle", VK_MAKE_VERSION(1, 0, 0), "Vulkan.hpp",
                                                  VK_MAKE_VERSION(1, 0, 0), VK_API_VERSION_1_1};

    constexpr vk::InstanceCreateFlags flags = vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR;
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char *> extensions;
    extensions.reserve(glfwExtensionCount);
    for (uint32_t i = 0; i < glfwExtensionCount; i++)
    {
        extensions.emplace_back(glfwExtensions[i]);
    }

    extensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

    vk::InstanceCreateInfo instanceCreateInfo;

    if (enableValidationLayers)
    {
        instanceCreateInfo = vk::InstanceCreateInfo{flags,
                                                    &applicationInfo,
                                                    static_cast<uint32_t>(validationLayers.size()),
                                                    validationLayers.data(),
                                                    static_cast<uint32_t>(extensions.size()),
                                                    extensions.data()};
    }
    else
    {
        instanceCreateInfo = vk::InstanceCreateInfo{
            flags, &applicationInfo, 0, nullptr, static_cast<uint32_t>(extensions.size()), extensions.data()};
    }

    const vk::raii::Instance instance{vkContext, instanceCreateInfo};
    this->vkInstance = instance;
}
