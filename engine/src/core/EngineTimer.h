/**
 * @file EngineTimer.h
 * @brief Class that calcules the delta time value.
 */

#pragma once

#include <GLFW/glfw3.h>

namespace HeimskrEngine {

  class EngineTimer {
  public:
    EngineTimer(const EngineTimer& other) = delete;
    EngineTimer& operator=(const EngineTimer&) = delete;
    ~EngineTimer() = default;

    static EngineTimer& GetInstance() {
      static EngineTimer instance;
      return instance;
    }

    void Initialize();
    void Update();
    double DeltaTime() const;

  private:
    EngineTimer() = default;

    double deltaTime;
    double lastFrame;
  };

  static EngineTimer& Timer = EngineTimer::GetInstance();
}