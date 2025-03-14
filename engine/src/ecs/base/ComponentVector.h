/**
 * @file ComponentVector.h
 * @brief Wrapper class for std::vector to store components with methods for easy manipulations.
 */

#pragma once
#include <vector>

#include "../../common/src/utility/AssertMsgFormat.h"
#include "ECSTypes.h"

namespace ECS {

  // TODO: Check if this is necessary for ComponentVector
  class IComponentVector {
  public:
    IComponentVector() = default;
    virtual ~IComponentVector() = default;
    virtual void Erase(const EntityID entity) {}
  };


  /**
   * \brief Vector wrapper class for components.
   * \tparam T Type of the component.
   */
  template<typename T>
  class ComponentVector : public IComponentVector {
  public:
    ComponentVector() = default;
    ~ComponentVector() override = default;


    /**
     * \brief Add a component to the vector if the vector doesnt contain it since an entity cannot have duplicate components attched to it.
     * \param[in] component component to add.
     */
    template<typename T>
    void Add(const T& component) {
      auto componentIterator = std::find_if(components.begin(), components.end(), [&](const T& comp) {
        return comp.GetEntityID() == component.GetEntityID();
      });
      if (componentIterator != components.end()) {
        components.push_back(component);
      }
    }


    /**
     * \brief Gets a component from the vector.
     * \param[in] entity EntityID of the component to get.
     * \return Reference to the component.
     */
    template<typename T>
    T& Get(const EntityID entity) {
      auto componentIterator = std::find_if(components.begin(), components.end(), [&](const T& comp) {
        return comp.GetID() == entity;
      });
      ASSERT(componentIterator != components.end(), "Entity " << entity << " does not exist within the component vector.");
      return *componentIterator;
    }


    /**
     * \brief Erase a component from the vector.
     * \param[in] entity EntityID of the component to erase.
     */
    template<typename T>
    void Erase(const EntityID entity) {
      auto componentIterator = std::find_if(components.begin(), components.end(), [&](const T& comp) {
        return comp.GetID() == entity;
      });
      if (componentIterator != components.end()) {
        components.erase(componentIterator);
      }
    }

    std::vector<T> components;
  };
}
