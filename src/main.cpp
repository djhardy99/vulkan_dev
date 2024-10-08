#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;
    VkInstance instance;
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    void initWindow(){
        glfwInit(); // This inits the glfw library
        // GLFW was originally designed for OpenGL, since we're using vulkan we must explicitly tell glfw this
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // Disabling resizing windows since thats a pain
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        //Create the window
        window = glfwCreateWindow(WIDTH, HEIGHT, "Window_Title", nullptr, nullptr);
    } 
    void initVulkan() {
        // Instances connect the application to the vulkan library
        createInstance();
    }
    void createInstance() {
        //Note alot of vulkan info is passed through structs not through function calls
        //This struct is optional
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        //This struct is mandatory
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        //Since Vulkan is platform agnostic, you need extensions for the window system
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }
    void mainLoop() {
        //Poll if window is open
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        //Destroy vulkran instance
        vkDestroyInstance(instance, nullptr);
        // Destroy the window
        glfwDestroyWindow(window);
        //close down glfw
        glfwTerminate();
    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
