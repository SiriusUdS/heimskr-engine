/**
 * @file System.cpp
 * @brief Method implementations for the System class.
 */

#include "System.h"

#include <iostream>

namespace ECS {

  /**
   * \brief Add an entity to the system.
   */
  void System::AddEntity(const EntityID entity) {
    entities.insert(entity);
  }

  /**
   * \brief Remove an entity from the system.
   */
  void System::RemoveEntity(const EntityID entity) {
    entities.erase(entity);
  }

  /**
   * \brief Get the signature of the system. This is a set of component types that the system is interested in.
   * \return The signature of the system.
   */
  EntitySignature System::GetSignature() const {
    return signature;
  }

  /**
   * \brief Start and initialize the system. This is called once at the start of the program.
   */
  void System::Start() {
    // Do nothing by default
  }

  /**
   * \brief Update the system once per frame.
   */
  void System::Update() {
    for (const EntityID entity : entities) {
      std::cout << entity << " ";
    }
    std::cout << '\n';
  }

  /**
   * \brief Render the system once per frame.
   */
  void System::Render() {
    // Do nothing by default
  }

  /**
   * \brief Destroy the system. This is called once at the end of the program.
   */
  void System::Destroy() {
    // Do nothing by default
  }
}
