#include <glad/glad.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "projectsetup/projset.h"

bool window_manager_open = true;
static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {
  if (!glfwInit()) {
    std::cerr << "GLFW could not initialize!" << std::endl;
    exit(EXIT_FAILURE);
  }

  GLFWwindow * window = glfwCreateWindow(800, 600, "MAGE", NULL, NULL);
  if (!window) {
    std::cerr << "GLFW window creation failed!" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cerr << "Failed to initialize OpenGL loader!" << std::endl;
    exit(EXIT_FAILURE);
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Project Manager", &window_manager_open, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("New Project")) {
          ImGui::OpenPopup("New Project");
        }
        if (ImGui::MenuItem("Open Project")) {}
        ImGui::EndMenu();
      }
      ImGui::EndMenuBar();
    }

    if (ImGui::BeginPopup("New Project")) {
      ImGui::Text("This is a simple popup!");
      if (ImGui::Button("Close")) {
        ImGui::CloseCurrentPopup(); 
      }
      ImGui::EndPopup();
    }

    if (ImGui::Button("Exit")) glfwSetWindowShouldClose(window, GLFW_TRUE);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
