/**
 * @file Window.cpp
 * @brief Method implementations for the Window class.
 */

#include "Window.h"

namespace HeimskrEngine {
  /**
   * \brief Constructor for the Window class
   * \param dispatcher The event dispatcher to use for the window
   * \param width The width of the window
   * \param height The height of the window
   * \param title The title of the window
   */
  Window::Window(EventDispatcher* dispatcher, int32_t width, int32_t height, const char* title) {
    if (!glfwInit()) {
      HEIMSKR_CRITICAL("Failed to initialize GLFW");
      exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    const GLFWvidmode* displayMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwWindowHint(GLFW_REFRESH_RATE, displayMode->refreshRate);
    glfwWindowHint(GLFW_GREEN_BITS, displayMode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, displayMode->blueBits);
    glfwWindowHint(GLFW_RED_BITS, displayMode->redBits);
    glfwWindowHint(GLFW_SAMPLES, 4); // Enable 4x MSAA (Multisample Anti-Aliasing)

    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    windowHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!windowHandle) {
      HEIMSKR_CRITICAL("Failed to create GLFW window");
      glfwTerminate();
      exit(EXIT_FAILURE);
    }

    glfwSetWindowUserPointer(windowHandle, this);
    glfwSetWindowMaximizeCallback(windowHandle, OnMaximize);
    glfwSetFramebufferSizeCallback(windowHandle, OnResize);
    glfwSetWindowIconifyCallback(windowHandle, OnIconify);
    glfwSetMouseButtonCallback(windowHandle, OnMouse);
    glfwSetWindowCloseCallback(windowHandle, OnClose);
    glfwSetCursorPosCallback(windowHandle, OnMotion);
    glfwSetScrollCallback(windowHandle, OnWheel);
    glfwSetKeyCallback(windowHandle, OnKey);
    glfwSetErrorCallback(OnError);

    glfwMakeContextCurrent(windowHandle);
    glfwSwapInterval(1);
  }


  /**
   * \brief Destructor for the Window class
   */
  Window::~Window() {
    glfwDestroyWindow(windowHandle);
    glfwTerminate();
  }


  /**
   * \brief Polls the events for the window from the dispatcher and glfw
   * \return True if the window should continue running, false if it should close
   */
  bool Window::PollEvents() const {
    glfwPollEvents();
    dispatcher->PollEvents();
    glfwSwapBuffers(windowHandle); // Swap the front buffer and back buffer for rendering the back buffer. See double-buffered rendering for more details.
    return !glfwWindowShouldClose(windowHandle);
  }


  /**
   * \brief Checks if a key is pressed
   * \param key The key to check
   * \return True if the key is pressed, false otherwise
   */
  bool Window::IsKey(int32_t key) const {
    if (key < 0 || key >= GLFW_KEY_LAST) {
      return false;
    }
    return inputs.Keys.test(key);
  }


  /**
   * \brief Checks if a mouse button is pressed
   * \param button The mouse button to check
   * \return True if the mouse button is pressed, false otherwise
   */
  bool Window::IsMouse(int32_t button) const {
    if (button < 0 || button >= GLFW_MOUSE_BUTTON_LAST) {
      return false;
    }
    return inputs.Mouse.test(button);
  }

}
