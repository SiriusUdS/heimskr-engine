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
   * \brief Add a component to an entity.
   * \tparam T The component type.
   * \tparam Args The arguments to pass to the component constructor.
   * \param[in] entity The entity to add the component to.
   * \param[in] args The arguments to pass to the component constructor.
   */
  template<typename T, typename... Args>
  void EntityManager::AddComponent(const EntityID entity, Args&&... args) {
    ASSERT(entity < MAX_ENTITIES, "This entity (" << entity << ") is out of range.");
    ASSERT(GetEntitySignature(entity)->size() < MAX_COMPONENTS, "The entity (" << entity << " has the maximum amount of component (" << MAX_COMPONENTS << ").");

    // Creates an instance of the component of type T with the constructor that matches the arguments passed with the parameter args
    T component(std::forward<Args>(args)...);
    component.entityID = entity;    
    GetEntitySignature(entity)->insert(GetComponentTypeID<T>());
    GetComponentVector<T>()->Insert(component);
    UpdateEntityTargetSystems(entity);
  }

  /**
   * \brief Remove a component from an entity.
   * \tparam T The component type.
   * \param[in] entity The entity to remove the component from.
   */
  template<typename T>
  void EntityManager::RemoveComponent(const EntityID entity) {
    ASSERT(entity < MAX_ENTITIES, "This entity (" << entity << ") is out of range.");

    const ComponentTypeID componentTypeID = GetComponentTypeID<T>();
    GetEntitySignature(entity)->erase(componentTypeID);
    GetComponentVector<T>()->Erase(componentTypeID);

    // Since we removed a component, we need to check if the entity still has a signature that matches an existing system.
    UpdateEntityTargetSystems(entity);
  }

  /**
   * \brief Get a component from an entity.
   * \tparam T The component type.
   * \param[in] entity The entity to get the component from.
   * \return Reference to the component.
   */
  template<typename T>
  T& EntityManager::GetComponent(const EntityID entity) {
    ASSERT(entity < MAX_ENTITIES, "This entity (" << entity << ") is out of range.");
    return GetComponentVector<T>()->Get(entity);
  }

  /**
   * \brief Check if an entity has a component.
   * \tparam T The component type.
   * \param[in] entity The entity to check.
   * \return True if the entity has the component, false otherwise.
   */
  template<typename T>
  const bool EntityManager::HasComponent(const EntityID entity) const {
    ASSERT(entity < MAX_ENTITIES, "This entity (" << entity << ") is out of range.");
    return GetEntitySignature(entity)->count(GetComponentTypeID<T>()) > 0;
  }

  /**
   * \brief Register a system of type T.
   * \tparam T The system type.
   */
  template<typename T>
  void EntityManager::RegisterSystem() {
    const SystemTypeID systemTypeID = GetSystemTypeID<T>();
    ASSERT(registeredSystems.find(systemTypeID) == registeredSystems.end(), "The system of type " << systemTypeID << " already exists.");
    auto system = std::make_shared<T>();

    for (EntityID entity = 0; entity < entityCount; entity++) {
      AddEntityToSystem(entity, *system);
    }
    system->Start();
    registeredSystems[systemTypeID] = std::move(system);
  }

  /**
   * \brief Unregister a system of type T.
   * \tparam T The system type.
   */
  template<typename T>
  void EntityManager::UnRegisterSystem() {
    const SystemTypeID systemTypeID = GetSystemTypeID<T>();
    ASSERT(registeredSystems.find(systemTypeID) != registeredSystems.end(), "The system of type " << systemTypeID << " was not found.");
    registeredSystems.erase(systemTypeID);
  }

  /**
   * \brief Add a component of type T vector to the map.
   * \tparam T The component type.
   */
  template<typename T>
  void EntityManager::AddComponentVector() {
    const ComponentTypeID componentTypeID = GetComponentTypeID<T>();
    ASSERT(components.find(componentTypeID) == components.end(), "The component vector for type " << componentTypeID << " already exists.");
    components[componentTypeID] = std::move(std::make_shared<ComponentVector<T>>());
  }

  /**
   * \brief Get a component vector of type T.
   * \tparam T The component type.
   * \return The component vector of type T.
   */
  template<typename T>
  std::shared_ptr<ComponentVector<T>> EntityManager::GetComponentVector() {
    const ComponentTypeID componentTypeID = GetComponentTypeID<T>();
    if (components.count(componentTypeID) == 0) {
      AddComponentVector<T>();
    }
    return std::static_pointer_cast<ComponentVector<T>>(components.at(componentTypeID));
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
      AddEntityToSystem(entity, *system.second);
    }
  }

  /**
   * \brief Add an entity to a system.
   * \param[in] entity The entity to add to the system.
   * \param[in] system The system to add the entity to.
   */
  void EntityManager::AddEntityToSystem(const EntityID entity, System& system) {
    if (IsInSystem(entity, system.signature)) {
      system.entities.insert(entity);
    } else {
      system.entities.erase(entity);
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
