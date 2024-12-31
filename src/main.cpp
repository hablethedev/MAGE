#include <glad/glad.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

#define DEBUG_LOG(msg) std::cout << "[DEBUG] " << msg << std::endl;

const char* vertexShaderSource = R"(
    #version 330 core
    layout(location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";


const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    uniform vec3 triangleColor;
    void main() {
        FragColor = vec4(triangleColor, 1.0f);
    }
)";

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
    DEBUG_LOG("Initializing GLFW...");
    if (!glfwInit()) {
        std::cerr << "GLFW could not initialize!" << std::endl;
        exit(EXIT_FAILURE);
    }
    DEBUG_LOG("GLFW initialized successfully.");

    GLFWwindow* window = glfwCreateWindow(800, 600, "MAGE Menu", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW window creation failed!" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    DEBUG_LOG("GLFW window created successfully.");

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);
    DEBUG_LOG("Making GLFW context current...");

    DEBUG_LOG("Loading OpenGL loader...");
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
        exit(EXIT_FAILURE);
    }
    DEBUG_LOG("OpenGL loader initialized successfully.");

    DEBUG_LOG("Creating ImGui context...");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    if (ImGui::GetIO().Fonts == nullptr) {
        std::cerr << "ImGui fonts failed to load!" << std::endl;
        exit(EXIT_FAILURE);
    }
    DEBUG_LOG("ImGui context created successfully.");

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    DEBUG_LOG("ImGui initialized successfully for GLFW and OpenGL.");

    float vertices[] = {
        0.0f,  0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int vertexShader, fragmentShader, shaderProgram;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);

    int colorLocation = glGetUniformLocation(shaderProgram, "triangleColor");
    glUniform3f(colorLocation, 1.0f, 0.0f, 0.0f);

    auto startTime = std::chrono::steady_clock::now();
    auto lastFrameTime = std::chrono::steady_clock::now();

    const float targetFPS = 60.0f;
    const float targetFrameTime = 1.0f / targetFPS;
    DEBUG_LOG("Target FPS set to 60.");

    while (!glfwWindowShouldClose(window)) {
        auto currentFrameTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> frameDuration = currentFrameTime - lastFrameTime;
        float frameTime = frameDuration.count();

        if (frameTime < targetFrameTime) {
            std::this_thread::sleep_for(std::chrono::duration<float>(targetFrameTime - frameTime));
        }

        lastFrameTime = std::chrono::steady_clock::now();

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

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    DEBUG_LOG("Shutting down ImGui...");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    DEBUG_LOG("ImGui shut down successfully.");

    glfwDestroyWindow(window);
    glfwTerminate();
    DEBUG_LOG("GLFW terminated successfully.");

    exit(EXIT_SUCCESS);
}
