/**
 * @file EngineEvents.h
 * @brief Handles the GLFW events.
 */

#pragma once

#include "Engine.h"

namespace HeimskrEngine {

  class EngineEvents {
  public:
    EngineEvents(const EngineEvents& other) = delete;
    EngineEvents& operator=(const EngineEvents&) = delete;
    ~EngineEvents() = default;

    static EngineEvents& GetInstance() {
      static EngineEvents instance;
      return instance;
    }

    void Initialize();
    void Update();

  private:
    EngineEvents() = default;
  };

  static EngineEvents& Events = EngineEvents::GetInstance();
}