/**
 * @file Window.h
 * @brief Contains the window abstraction after the GLFW window with our custom event dispatcher.
 */

#pragma once

#include "Events.h"
#include "Inputs.h"
#include "../logging/Logger.h"

namespace HeimskrEngine {
  class Window {
  public:
    Window(EventDispatcher* dispatcher, int32_t width, int32_t height, const char* title);
    ~Window();

    bool PollEvents() const;
    bool IsKey(int32_t key) const;
    bool IsMouse(int32_t button) const;
    GLFWwindow* GetWindowHandle() const { return windowHandle; }

    /**
     * \brief Gets the window user data pointer.
     * \details
     * Retrieves the pointer to the Window instance associated with a given GLFWwindow.
     * This is necessary because GLFW callbacks are static and do not support member functions.
     * By using glfwSetWindowUserPointer() during window initialization, we can recover the
     * original Window* instance from within static callbacks using this function.
     * \param window The GLFW window handle
     * \return The user pointer of the window
     */
    static Window* GetWindowUserPointer(GLFWwindow* window) {
      return static_cast<Window*>(glfwGetWindowUserPointer(window));
    }


    /**
     * \brief Callback function for OnKey event.
     * \param window The GLFW window handle
     * \param key The key that was pressed or released
     * \param action The action that was performed (pressed or released)
     */
    static void OnKey(GLFWwindow* window, int32_t key, int32_t, int32_t action, int32_t) {
      if (key < 0 || key >= GLFW_KEY_LAST) {
        HEIMSKR_ERROR(fmt::format("Provided key code is not supported: {}", key));
        return;
      }

      Window* win = GetWindowUserPointer(window);
      switch (action) {
        case GLFW_PRESS:
          win->dispatcher->PostEvent<KeyPressEvent>(key);
          win->inputs.Keys.set(key);
          break;
        case GLFW_RELEASE:
          win->dispatcher->PostEvent<KeyReleaseEvent>(key);
          win->inputs.Keys.reset(key);
          break;
        case GLFW_REPEAT:
          win->dispatcher->PostEvent<KeyRepeatEvent>(key);
          win->inputs.Keys.set(key);
          break;
        default:
          HEIMSKR_WARN(fmt::format("Unknown key action: {}", action));
      }
    }


    /**
     * \brief Callback function for OnMouse event.
     * \param window The GLFW window handle
     * \param button The mouse button that was pressed or released
     * \param action The action that was performed (pressed or released)
     */
    static void OnMouse(GLFWwindow* window, int32_t button, int32_t action, int32_t) {
      if (button < 0 || button >= GLFW_MOUSE_BUTTON_LAST) {
        HEIMSKR_ERROR(fmt::format("Provided mouse button code is not supported: {}", button));
        return;
      }

      Window* win = GetWindowUserPointer(window);
      switch (action) {
        case GLFW_PRESS:
          win->dispatcher->PostEvent<MouseDownEvent>(button);
          win->inputs.Mouse.set(button);
          break;
        case GLFW_RELEASE:
          win->dispatcher->PostEvent<MouseReleaseEvent>(button);
          win->inputs.Mouse.reset(button);
          break;
        default:
          HEIMSKR_WARN(fmt::format("Unknown mouse action: {}", action));
      }
    }


    /**
     * \brief Callback function for OnResize event.
     * \param window The GLFW window handle
     * \param width The new width of the window
     * \param height The new height of the window
     */
    static void OnResize(GLFWwindow* window, int32_t width, int32_t height) {
      const Window* win = GetWindowUserPointer(window);
      win->dispatcher->PostEvent<WindowResizeEvent>(width, height);
    }


    /**
     * \brief Callback function for OnMotion event.
     * \param window The GLFW window handle
     * \param targetX The new X coordinate of the mouse
     * \param targetY The new Y coordinate of the mouse
     */
    static void OnMotion(GLFWwindow* window, double targetX, double targetY) {
      Window* win = GetWindowUserPointer(window);
      win->dispatcher->PostEvent<MouseMotionEvent>(targetX, targetY);

      if (win->inputs.Mouse.test(GLFW_MOUSE_BUTTON_LEFT)) {
        win->dispatcher->PostEvent<MouseDragEvent>(win->inputs.MouseX - targetX, win->inputs.MouseY - targetY);
      }

      win->inputs.MouseX = targetX;
      win->inputs.MouseY = targetY;
    }


    /**
     * \brief Callback function for OnWheel event.
     * \param window The GLFW window handle
     * \param scrollX The amount of horizontal scroll
     * \param scrollY The amount of vertical scroll
     */
    static void OnWheel(GLFWwindow* window, double scrollX, double scrollY) {
      const Window* win = GetWindowUserPointer(window);
      win->dispatcher->PostEvent<MouseWheelEvent>(scrollX, scrollY);
    }


    /**
     * \brief Callback function for OnMaximize event.
     * \param window The GLFW window handle
     * \param action The action that was performed (maximized or restored)
     */
    static void OnMaximize(GLFWwindow* window, int32_t action) {
      const Window* win = GetWindowUserPointer(window);
      if (action) {
        win->dispatcher->PostEvent<WindowMaximizeEvent>();
      } else {
        win->dispatcher->PostEvent<WindowRestoreEvent>();
      }
    }


    /**
     * \brief Callback function for OnIconify event.
     * \param window The GLFW window handle
     * \param action The action that was performed (iconified or restored)
     */
    static void OnIconify(GLFWwindow* window, int32_t action) {
      const Window* win = GetWindowUserPointer(window);
      if (action) {
        win->dispatcher->PostEvent<WindowIconifyEvent>();
      } else {
        win->dispatcher->PostEvent<WindowRestoreEvent>();
      }
    }


    /**
     * \brief Callback function for OnClose event.
     * \param window The GLFW window handle
     */
    static void OnClose(GLFWwindow* window) {
      const Window* win = GetWindowUserPointer(window);
      win->dispatcher->PostEvent<WindowCloseEvent>();
    }


    /**
     * \brief Callback function for OnError event.
     * \param code The error code
     * \param description The error description
     */
    static void OnError(int32_t code, const char* description) {
      HEIMSKR_ERROR(fmt::format("[GLFW]: {} {}", code, description));
    }

  private:
    EventDispatcher* dispatcher;
    WindowInputs inputs;
    GLFWwindow* windowHandle;
  };
}
