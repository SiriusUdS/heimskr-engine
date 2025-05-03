///**
// * @file EngineTimer.h
// * @brief Method implementations for the EngineTimer class.
// */
//
//#include "EngineTimer.h"
//
//namespace HeimskrEngine {
//
//  /**
//   * @brief Initializes the engine timer
//   */
//  void EngineTimer::Initialize() {
//
//  }
//
//
//  /**
//    * @brief Updates the engine timer
//    */
//  void EngineTimer::Update() {
//    deltaTime = glfwGetTime() - lastFrame;
//    lastFrame = glfwGetTime();
//  }
//
//
//  /**
//    * @brief Returns the delta time of the engine timer
//    * @return Delta time as double
//    */
//  double EngineTimer::DeltaTime() const {
//    return deltaTime;
//  }
//}