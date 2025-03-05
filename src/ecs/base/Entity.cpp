/**
 * @file Entity.cpp
 * @brief Method implementations for the Entity class.
 */

#include "Entity.h"

namespace ECS {

  Entity::Entity(const EntityID id, EntityManager* manager): id(id), manager(manager) { }

  void Entity::Destroy() const {
    manager->DestroyEntity(id);
  }

  const EntityID Entity::GetID() const {
    return id;
  }

  template<typename T, typename... Args>
  void Entity::AddComponent(Args&&... args) {
    manager->AddComponent<T>(id, std::forward<Args>(args)...);
  }

  template<typename T>
  void Entity::AddComponent(T& component) {
    manager->AddComponent<T>(id, component);
  }

  template<typename T>
  T& Entity::GetComponent() {
    return manager->GetComponent<T>(id);
  }

  template<typename T>
  void Entity::RemoveComponent() const {
    manager->RemoveComponent<T>(id);
  }

  template<typename T>
  bool Entity::HasComponent() const {
    return manager->HasComponent<T>(id);
  }
}
