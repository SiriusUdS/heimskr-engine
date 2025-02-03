/**
 * @file EngineEvents.h
 * @brief Method implementations for the EngineEvents class.
 */

#include "EngineEvents.h"

namespace HeimskrEngine {

  void WindowShouldCloseCallback(GLFWwindow* window);

  EngineEvents::~EngineEvents() {
  }

  void EngineEvents::Initialize() {
    GLFWwindow& window = Core.GetWindow();
    glfwSetWindowCloseCallback(&window, WindowShouldCloseCallback);
  }

  void EngineEvents::Update() {
    glfwPollEvents();
  }

  void WindowShouldCloseCallback(GLFWwindow* window) {
    Core.Stop();
  }
}