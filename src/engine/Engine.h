/**
 * @file Engine.h
 * @brief Core of the engine.
 */

#pragma once

#include <memory>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace Core {

  constexpr int ENGINE_WINDOW_WIDTH = 800;
  constexpr int ENGINE_WINDOW_HEIGHT = 600;
  constexpr const char* ENGINE_WINDOW_TITLE = "Heimskr Engine";

  /**
   * @brief Custom deleter for GLFWwindow unique_ptr since GLFWwindow is written in C.
   */
  struct DestroyableGLFWwindow {
    void operator()(GLFWwindow* ptr) const {
      glfwDestroyWindow(ptr);
    }
  };
  typedef std::unique_ptr<GLFWwindow, DestroyableGLFWwindow> UniqueGLFWwindow;

  class Engine {

  public:
    Engine(const Engine& other) = delete;
    Engine& operator=(const Engine&) = delete;
    ~Engine();

    static Engine& GetInstance() {
      static Engine instance;
      return instance;
    }

	void Run();
    void Stop();
    void Initialize();

    bool IsRunning() const;
    GLFWwindow& GetWindow() const;
    int GetWindowWidth() const;
    int GetWindowHeight() const;

  private:
    Engine();

    void Update();

    bool isRunning;
    UniqueGLFWwindow window;
    int windowWidth;
    int windowHeight;
  };

  static Engine& Heimskr = Engine::GetInstance();
}
