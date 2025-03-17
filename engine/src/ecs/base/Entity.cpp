/**
 * @file Entity.cpp
 * @brief Method implementations for the Entity class.
 */

#include "Entity.h"

namespace ECS {

  Entity::Entity(const EntityID id, EntityManager* manager): id(id), manager(manager) { }


  /**
   * \brief Destroy the entity.
   */
  void Entity::Destroy() const {
    manager->DestroyEntity(id);
  }


  /**
   * \brief Get the ID of the entity.
   * \return The ID of the entity.
   */
  const EntityID Entity::GetID() const {
    return id;
  }
}
