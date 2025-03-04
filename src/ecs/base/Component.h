/**
 * @file Component.h
 * @brief Base class for components.
 */

#pragma once

#include "ECSTypes.h"

namespace ECS {
  class Component {

  public:
    Component() = default;
    virtual ~Component() = default;

    /**
     * \brief Returns the entity ID of the component.
     * \return The entity ID of the component.
     */
    EntityID GetEntityID() const {
      return entityID;
    }

  private:
    friend class Manager; // Manager can read and write the entityID attribute.
    EntityID entityID;
  };
}
