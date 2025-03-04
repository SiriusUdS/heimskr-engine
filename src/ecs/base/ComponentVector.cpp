/**
 * @file ComponentVector.cpp
 * @brief Method implementations for the ComponentVector class
 */

#include "ComponentVector.h"

namespace ECS {

  /**
   * \brief Add a component to the vector if the vector doesnt contain it since an entity cannot have duplicate components attched to it.
   * \param[in] component component to add.
   */
  template<typename T>
  void ComponentVector<T>::Add(const T& component) {
    auto component = std::find_if(components.begin(), components.end(), [&](const T& comp) {
      return comp.GetID() == component.GetID();
    });
    if (component != components.end()) {
      components.push_back(component);
    }
  }

  /**
   * \brief Gets a component from the vector.
   * \param[in] entity EntityID of the component to get.
   * \return Reference to the component.
   */
  template<typename T>
  T& ComponentVector<T>::Get(const EntityID entity) {
    auto component = std::find_if(components.begin(), components.end(), [&](const T& comp) {
      return comp.GetID() == entity;
    });
    assert(component != components.end() && "Entity " && entity && " does not exist within the component vector.");
    return *component;
  }

  /**
   * \brief Erase a component from the vector.
   * \param[in] entity EntityID of the component to erase.
   */
  template<typename T>
  void ComponentVector<T>::Erase(const EntityID entity) {
    auto component = std::find_if(components.begin(), components.end(), [&](const T& comp) {
      return comp.GetID() == entity;
    });
    if (component != components.end()) {
      components.erase(component);
    }
  }
}
