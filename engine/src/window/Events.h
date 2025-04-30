/**
 * @file Events.h
 * @brief Contains the events structures for peripheral inputs.
 */

#pragma once

#include "../common/Event.h"

namespace HeimskrEngine {

  struct WindowMaximizeEvent {  };

  struct WindowIconifyEvent {  };

  struct WindowRestoreEvent {  };

  struct WindowCloseEvent {  };

  struct WindowResizeEvent {
    WindowResizeEvent(int32_t width, int32_t height) : Width(width), Height(height) {  }
    int32_t Width;
    int32_t Height;
  };

  struct KeyReleaseEvent {
    KeyReleaseEvent(int32_t key) : Key(key) {  }
    int32_t Key = -1;
  };

  struct KeyPressEvent {
    KeyPressEvent(int32_t key) : Key(key) {  }
    int32_t Key = -1;
  };

  struct KeyRepeatEvent {
    KeyRepeatEvent(int32_t key) : Key(key) {  }
    int32_t Key = -1;
  };

  struct MouseReleaseEvent {
    MouseReleaseEvent(int32_t button) : Button(button) {  }
    int32_t Button = -1;
  };

  struct MouseDownEvent {
    MouseDownEvent(int32_t button) : Button(button) {  }
    int32_t Button = -1;
  };

  struct MouseDragEvent {
    MouseDragEvent(double deltaX, double deltaY) : DeltaX(deltaX), DeltaY(deltaY) {  }
    double DeltaX = 0.0;
    double DeltaY = 0.0;
  };

  struct MouseMotionEvent {
    MouseMotionEvent(double targetX, double targetY) : TargetX(targetX), TargetY(targetY) {  }
    double TargetX = 0.0;
    double TargetY = 0.0;
  };

  struct MouseWheelEvent {
    MouseWheelEvent(double scrollX, double scrollY) : ScrollX(scrollX), ScrollY(scrollY) {  }
    double ScrollX = 0.0;
    double ScrollY = 0.0;
  };

}
