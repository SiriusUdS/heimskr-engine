/**
 * @file Engine.cpp
 * @brief Method implementations for the Engine class
 */

#include "Engine.h"

Core::Engine::Engine() {
  isRunning = false;
  Initialize();
}

/**
 * @brief Destructor of the Engine class
 */
Core::Engine::~Engine() {
  glfwDestroyWindow(window.get());
  glfwTerminate();
}

/**
 * @brief Starts the main loop of the engine
 * @return void
 */
void Core::Engine::Run() {
  isRunning = true;
  while (true) {
    Update();
  }
}

/**
 * @brief Stops the main loop of the engine
 * @return void
 */
void Core::Engine::Stop() {
  isRunning = false;
}

/**
 * @brief Updates the engine window and events
 * @details This function is called every frame
 * @return void
 */
void Core::Engine::Update() {
  glfwPollEvents();
  glfwSwapBuffers(window.get());
  isRunning = !glfwWindowShouldClose(window.get());
}

/** 
* @brief Initializes the engine
* @return void
*/ 
void Core::Engine::Initialize() {
  windowWidth = ENGINE_WINDOW_WIDTH;
  windowHeight = ENGINE_WINDOW_HEIGHT;

  if (!glfwInit()) {
    throw std::runtime_error("Could not initialize engine: Failed to initialize GLFW");
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWmonitor* monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* mode = glfwGetVideoMode(monitor);

  glfwWindowHint(GLFW_RED_BITS, mode->redBits);
  glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
  glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
  glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

  window = UniqueGLFWwindow(glfwCreateWindow(mode->width, mode->height, ENGINE_WINDOW_TITLE, monitor, nullptr));
  glfwSetWindowMonitor(window.get(), monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

  //window = UniqueGLFWwindow(glfwCreateWindow(windowWidth, windowHeight, ENGINE_WINDOW_TITLE, nullptr, nullptr));

  if (!window) {
    glfwTerminate();
    throw std::runtime_error("Could not initialize engine: Failed to create window");
  }

  glfwMakeContextCurrent(window.get());
}

/**
 * @brief Checks whether the engine is running or not.
 * @return bool
 */
bool Core::Engine::IsRunning() const {
  return isRunning;
}

/**
 * @brief Gets the window handle of the engine.
 * @return GLFWwindow&
 */
GLFWwindow& Core::Engine::GetWindow() const {
  return *window;
}

/**
 * @brief Gets the window width.
 * @return int
 */
int Core::Engine::GetWindowWidth() const {
  return windowWidth;
}

/**
 * @brief Gets the window height.
 * @return int
 */
int Core::Engine::GetWindowHeight() const {
  return windowHeight;
}