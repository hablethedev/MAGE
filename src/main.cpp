#include <glad/glad.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW could not initialize!" << std::endl;
        exit(EXIT_FAILURE);
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "MEGA", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW window creation failed!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    auto startTime = std::chrono::steady_clock::now();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        auto elapsed = std::chrono::steady_clock::now() - startTime;
        float timeInSeconds = std::chrono::duration<float>(elapsed).count();

        float r = (std::sin(timeInSeconds) + 1.0f) / 2.0f;
        float g = (std::sin(timeInSeconds + 2.0f) + 1.0f) / 2.0f;
        float b = (std::sin(timeInSeconds + 4.0f) + 1.0f) / 2.0f;

        ImGui::Begin("MAGE");
        if (ImGui::Button("Exit")) glfwSetWindowShouldClose(window, GLFW_TRUE);
        ImGui::End();

        ImGui::Render();
        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}
