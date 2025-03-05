/**
 * @file Entity.h
 * @brief Base class for entities.
 */

#pragma once

#include "ECSTypes.h"
#include "EntityManager.h"

namespace ECS {

  class Entity {
  public:
    Entity() = delete;
    Entity(const EntityID id, EntityManager* manager);
    ~Entity() = default;

    void Destroy() const;

    const EntityID GetID() const;

    template<typename T, typename... Args>
    void AddComponent(Args&&... args);

    template<typename T>
    void AddComponent(T& component);

    template<typename T>
    T& GetComponent();

    template<typename T>
    void RemoveComponent() const;

    template<typename T>
    bool HasComponent() const;

  private:
    EntityID id;
    EntityManager* manager;
  };
}
