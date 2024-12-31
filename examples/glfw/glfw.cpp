#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW could not initialize!" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "MEGA", nullptr, nullptr);
    if (!window) {
        std::cerr << "GLFW window creation failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    auto startTime = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window)) {
        auto elapsed = std::chrono::steady_clock::now() - startTime;
        float timeInSeconds = std::chrono::duration<float>(elapsed).count();

        float r = (std::sin(timeInSeconds) + 1.0f) / 2.0f;
        float g = (std::sin(timeInSeconds + 2.0f) + 1.0f) / 2.0f;
        float b = (std::sin(timeInSeconds + 4.0f) + 1.0f) / 2.0f;

        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
