/**
 * @file EngineEvents.h
 * @brief Method implementations for the EngineEvents class.
 */

#include "EngineEvents.h"

namespace HeimskrEngine {

  /**
   * @brief Callback function for when the window should close
   */
  void WindowShouldCloseCallback(GLFWwindow* window);


  /**
   * @brief Initializes the engine events
   */
  void EngineEvents::Initialize() {
    GLFWwindow& window = Core.GetWindow();
    glfwSetWindowCloseCallback(&window, WindowShouldCloseCallback);
  }


  /**
   * @brief Updates the engine events with glfw
   */
  void EngineEvents::Update() {
    glfwPollEvents();
  }


  /**
   * @brief Callback function for when the window should close
   * @param window The window that should close
   */
  void WindowShouldCloseCallback(GLFWwindow* window) {
    Core.Stop();
  }
}