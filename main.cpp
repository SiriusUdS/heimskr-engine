/// \file

#include <iostream>
#include <imgui.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    IMGUI_CHECKVERSION();
    std::cout << "And what does the Empire do? Nothing! Nay, worse than nothing" << ImGui::GetVersion() << std::endl;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 800, "HeimskrEngine - Window", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "noob";
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, 800, 800);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}