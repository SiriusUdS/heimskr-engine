/**
 * @file EntityManager.h
 * @brief Manager class for entities.
 */

#pragma once

#include <map>
#include <memory>
#include <queue>

#include "../../utility/AssertMsgFormat.h"
#include "Component.h"
#include "ComponentVector.h"
#include "ECSTypes.h"
#include "System.h"

namespace ECS {
  class EntityManager {
  public:
    EntityManager();
    ~EntityManager() = default;

    void Update();
    void Render();

    const EntityID CreateEntity();
    void EntityManager::DestroyEntity(const EntityID entity);

    template<typename T, typename... Args>
    void AddComponent(const EntityID entity, Args&&... args);

    template<typename T>
    void RemoveComponent(const EntityID entity);

    template<typename T>
    T& GetComponent(const EntityID entity);

    template<typename T>
    const bool HasComponent(const EntityID entity) const;

    template<typename T>
    void RegisterSystem();

    template<typename T>
    void UnRegisterSystem();

  private:
    template<typename T>
    void AddComponentVector();

    template<typename T>
    std::shared_ptr<ComponentVector<T>> GetComponentVector();

    void AddEntitySignature(const EntityID entity);
    std::shared_ptr<EntitySignature> GetEntitySignature(const EntityID entity);
    void UpdateEntityTargetSystems(const EntityID entity);
    void AddEntityToSystem(const EntityID entity, System& system);
    bool IsInSystem(const EntityID entity, const EntitySignature& signatures);

  private:
    uint16_t entityCount;
    std::queue<EntityID> availableEntityIDs;
    std::map<EntityID, std::shared_ptr<EntitySignature>> entitySignatures;
    std::map<SystemTypeID, std::shared_ptr<System>> registeredSystems;
    std::map<ComponentTypeID, std::shared_ptr<IComponentVector>> components;
  };
}