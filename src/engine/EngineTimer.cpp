/**
 * @file EngineTimer.h
 * @brief Method implementations for the EngineTimer class.
 */

#include "EngineTimer.h"

namespace HeimskrEngine {

  EngineTimer::~EngineTimer() {
  }

  void EngineTimer::Initialize() {
    lastFrame = static_cast<float>(glfwGetTime());
  }

  void EngineTimer::Update() {
    deltaTime = glfwGetTime() - lastFrame;
    lastFrame = glfwGetTime();
  }

  double EngineTimer::DeltaTime() const {
    return deltaTime;
  }
}