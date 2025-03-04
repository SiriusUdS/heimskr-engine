/**
 * @file ComponentVector.h
 * @brief Wrapper class for std::vector to store components with methods for easy manipulations.
 */

#pragma once
#include <vector>

#include "ECSTypes.h"

namespace ECS {

  // TODO: Check if this is necessary for ComponentVector
  //class IComponentVector {
  //public:
  //  IComponentVector() = default;
  //  virtual ~IComponentVector() = default;
  //  virtual void Erase(const EntityID entity) {}
  //};

  /**
   * \brief Vector wrapper class for components.
   * \tparam T Type of the component.
   */
  template<typename T>
  class ComponentVector {
  public:
    ComponentVector() = default;
    virtual ~ComponentVector() = default;

    /**
     * \brief Add a component to the vector if the vector doesnt contain it since an entity cannot have duplicate components attched to it
     * \param[in] component component to add.
     */
    void Add(const T& component);

    /**
     * \brief Gets a component from the vector.
     * \param[in] entity EntityID of the component to get.
     * \return Reference to the component.
     */
    T& Get(const EntityID entity);

    /**
     * \brief Erase a component from the vector.
     * \param[in] entity EntityID of the component to erase.
     */
    void Erase(const EntityID entity);

    std::vector<T> components;
  };
}
