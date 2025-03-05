/**
 * @file EntityManager.cpp
 * @brief Method implementation for the EntityManager class.
 */

#include "EntityManager.h"

namespace ECS {

  EntityManager::EntityManager() : entityCount(0) {
    for (EntityID currentEntity = 0; currentEntity < MAX_ENTITIES; currentEntity++) {
      availableEntityIDs.push(currentEntity);
    }
  }

  /**
   * \brief Update all systems.
   */
  void EntityManager::Update() const {
    for (auto& system : registeredSystems) {
      system.second->Update();
    }
  }

  /**
   * \brief Render systems that need rendering.
   */
  void EntityManager::Render() const {
    for (auto& system : registeredSystems) {
      system.second->Render();
    }
  }

  /**
   * \brief Create a new entity with the next available ID in the queue.
   * \return The entity (ID).
   */
  const EntityID EntityManager::CreateEntity() {
    ASSERT(entityCount < MAX_ENTITIES, "Maximum number of entities reached (" << MAX_ENTITIES << ").");
    const EntityID entityID = availableEntityIDs.front();
    AddEntitySignature(entityID);
    availableEntityIDs.pop();
    entityCount++;
    return entityID;
  }

  /**
   * \brief Destroy an entity and removes it from all systems and components.
   * \param[in] entity EntityID of the entity to destroy.
   */
  void EntityManager::DestroyEntity(const EntityID entity) {
    ASSERT(entity < MAX_ENTITIES, "The entity: " << entity << " cannot be destroyed (Out of range)");
    entitySignatures.erase(entity);

    for (auto& component : components) {
      component.second->Erase(entity);
    }

    for (auto& system : registeredSystems) {
      system.second->RemoveEntity(entity);
    }

    entityCount--;
    availableEntityIDs.push(entity);
  }

  /**
   * \brief Add an entity signature to the map.
   * \param[in] entity The entity to add the signature to.
   */
  void EntityManager::AddEntitySignature(const EntityID entity) {
    ASSERT(entitySignatures.find(entity) == entitySignatures.end(), "The signature for entity " << entity << " already exists.");
    entitySignatures[entity] = std::move(std::make_shared<EntitySignature>());
  }

  /**
   * \brief Get an entity signature.
   * \param[in] entity The entity to get the signature from.
   * \return The entity signature.
   */
  std::shared_ptr<EntitySignature> EntityManager::GetEntitySignature(const EntityID entity) {
    ASSERT(entitySignatures.find(entity) != entitySignatures.end(), "The signature for entity " << entity << " was not found.");
    return entitySignatures.at(entity);
  }

  /**
   * \brief Update the target systems of an entity.
   * \param[in] entity The entity to update the target systems of.
   */
  void EntityManager::UpdateEntityTargetSystems(const EntityID entity) {
    for (auto& system : registeredSystems) {
      AddEntityToSystem(entity, system.second.get());
    }
  }

  /**
   * \brief Add an entity to a system.
   * \param[in] entity The entity to add to the system.
   * \param[in] system The system to add the entity to.
   */
  void EntityManager::AddEntityToSystem(const EntityID entity, System* system) {
    if (IsInSystem(entity, system->signature)) {
      system->entities.insert(entity);
    } else {
      system->entities.erase(entity);
    }
  }

  /**
   * \brief Check if an entity is in a system.
   * \param entity The entity to check.
   * \param signatures The signature on which the entity will be checked.
   */
  bool EntityManager::IsInSystem(const EntityID entity, const EntitySignature& signatures) {
    for (const auto& component : signatures) {
      if (GetEntitySignature(entity)->count(component) == 0) {
        return false;
      }
    }
    return true;
  }
}
