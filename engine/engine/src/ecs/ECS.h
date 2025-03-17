///**
// * @file ECS.h
// * @brief ECS (Entity component system) settings and utility functions.
// */
//
//#pragma once
//
//#include <cstdint>
//#include <set>
//
//namespace ECS {
//
//  class System;
//  class Component;
//
//  constexpr uint16_t MAX_ENTITIES   = 5000;
//  constexpr uint16_t MAX_COMPONENTS = 32;
//
//  using EntityID = uint16_t;
//  using SystemTypeID = uint16_t;
//  using ComponentTypeID = uint16_t;
//  using EntitySignature = std::set<ComponentTypeID>;
//
//  /**
//   * @brief Get the next component type ID.
//   * @return The next component type ID.
//   */
//  static const ComponentTypeID GetNextComponentTypeID() {
//    static ComponentTypeID typeID = 0u;
//    return typeID++;
//  }
//
//  /**
//   * @brief Get the next system type ID.
//   * @return The next system type ID.
//   */
//  static const SystemTypeID GetNextSystemTypeID() {
//    static SystemTypeID typeID = 0u;
//    return typeID++;
//  }
//
//  /**
//   * @brief Creates an ID if T inherits Component. If it hasn't been created yet for this component, the ID will created.
//   * @details Since this function is static, it will always return the same ID for the same component.
//   * @tparam T The type of the component.
//   * @return The new component type ID.
//   */
//  template <typename T>
//  static const ComponentTypeID GetComponentTypeID() {
//    static_assert((std::is_base_of<Component, T>::value && !std::is_same<Component, T>::value), "T must inherit from the Component class.");
//    static const ComponentTypeID typeID = GetNextComponentTypeID();
//    return typeID;
//  }
//
//  /**
//   * @brief Creates an ID if T inherits System. If it hasn't been created yet for this system, the ID will created.
//   * @details Since this function is static, it will always return the same ID for the same system.
//   * @tparam T The type of the system.
//   * @return The new system type ID.
//   */
//  template <typename T>
//  static const SystemTypeID GetSystemTypeID() {
//    static_assert((std::is_base_of<System, T>::value && !std::is_same<System, T>::value), "T must inherit from the System class.");
//    static const SystemTypeID typeID = GetNextSystemTypeID();
//    return typeID;
//  }
//}