/**
 * @file Types.h
 * @brief Contains common type definitions and utility functions for these types.
 */

#pragma once
#include <cstdint>

namespace HeimskrEngine {
  /**
   * \brief Allows for the conversion of a type to a unique identifier.
   * \tparam T The specified type (Can be any type)
   * \return The unique identifier for the specified type
   */
  template<typename T>
  uint32_t TypeID() {
    return static_cast<uint32_t>(reinterpret_cast<uintptr_t>(&typeid(T)));
  }
}
