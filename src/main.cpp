#include <glad/glad.h>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "projectsetup/projset.h"
#include "imgui-filebrowser/imfilebrowser.h"

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

  ImGui::FileBrowser pathDialog(ImGuiFileBrowserFlags_SelectDirectory);
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Project Manager");

    char projName[1024];
    std::string projPath;

    if (ImGui::Button("New Project")) ImGui::OpenPopup("New Project");
    if (ImGui::Button("Exit")) glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (ImGui::BeginPopup("New Project")) {
      ImGui::InputText("Project Name", projName, IM_ARRAYSIZE(projName));
      if (ImGui::Button("Choose Project Folder")) {
        pathDialog.Open();
      }
      ImGui::Text(projPath.c_str());
      if (ImGui::Button("Close")) {
        ImGui::CloseCurrentPopup(); 
      }
      ImGui::EndPopup();
    }
    ImGui::End();

    pathDialog.Display();

    if (pathDialog.HasSelected()) {
      projPath = pathDialog.GetSelected().string();
      pathDialog.ClearSelected();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
