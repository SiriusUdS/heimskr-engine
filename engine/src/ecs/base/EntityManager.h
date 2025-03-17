/**
 * @file EntityManager.h
 * @brief Manager class for entities.
 */

#pragma once

#include <map>
#include <memory>
#include <queue>

#include "../utility/AssertMsgFormat.h"
#include "Component.h"
#include "ComponentVector.h"
#include "ECSTypes.h"
#include "System.h"

namespace ECS {
  class EntityManager {
  public:
    EntityManager();
    ~EntityManager() = default;

    void Update() const;
    void Render() const;

    const EntityID CreateEntity();
    void DestroyEntity(const EntityID entity);


    /**
     * \brief Add a component to an entity.
     * \tparam T The component type.
     * \tparam Args The arguments to pass to the component constructor.
     * \param[in] entity The entity to add the component to.
     * \param[in] args The arguments to pass to the component constructor.
     */
    template<typename T, typename... Args>
    void AddComponent(const EntityID entity, Args&&... args) {
      ASSERT(entity < MAX_ENTITIES, "This entity (" << entity << ") is out of range.");
      ASSERT(GetEntitySignature(entity)->size() < MAX_COMPONENTS, "The entity (" << entity << " has the maximum amount of component (" << MAX_COMPONENTS << ").");

      // Creates an instance of the component of type T with the constructor that matches the arguments passed with the parameter args
      T component(std::forward<Args>(args)...);
      component.entityID = entity;
      GetEntitySignature(entity)->insert(GetComponentTypeID<T>());
      auto test = GetComponentVector<T>();
      GetComponentVector<T>()->Add(component);
      UpdateEntityTargetSystems(entity);
    }


    /**
     * \brief Remove a component from an entity.
     * \tparam T The component type.
     * \param[in] entity The entity to remove the component from.
     */
    template<typename T>
    void RemoveComponent(const EntityID entity) {
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
    T& GetComponent(const EntityID entity) {
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
    const bool HasComponent(const EntityID entity) const {
      ASSERT(entity < MAX_ENTITIES, "This entity (" << entity << ") is out of range.");
      return GetEntitySignature(entity)->count(GetComponentTypeID<T>()) > 0;
    }


    /**
     * \brief Register a system of type T.
     * \tparam T The system type.
     */
    template<typename T>
    void RegisterSystem() {
      const SystemTypeID systemTypeID = GetSystemTypeID<T>();
      ASSERT(registeredSystems.find(systemTypeID) == registeredSystems.end(), "The system of type " << systemTypeID << " already exists.");
      auto system = std::make_shared<T>();

      for (EntityID entity = 0; entity < entityCount; entity++) {
        AddEntityToSystem(entity, system.get());
      }
      system->Start();
      registeredSystems[systemTypeID] = std::move(system);
    }


    /**
     * \brief Unregister a system of type T.
     * \tparam T The system type.
     */
    template<typename T>
    void UnRegisterSystem() {
      const SystemTypeID systemTypeID = GetSystemTypeID<T>();
      ASSERT(registeredSystems.find(systemTypeID) != registeredSystems.end(), "The system of type " << systemTypeID << " was not found.");
      registeredSystems.erase(systemTypeID);
    }

  private:

    /**
     * \brief Add a component of type T vector to the map.
     * \tparam T The component type.
     */
    template<typename T>
    void AddComponentVector() {
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
    std::shared_ptr<ComponentVector<T>> GetComponentVector() {
      const ComponentTypeID componentTypeID = GetComponentTypeID<T>();
      if (components.count(componentTypeID) == 0) {
        AddComponentVector<T>();
      }
      return std::static_pointer_cast<ComponentVector<T>>(components.at(componentTypeID));
    }


    void AddEntitySignature(const EntityID entity);
    std::shared_ptr<EntitySignature> GetEntitySignature(const EntityID entity) const;
    void UpdateEntityTargetSystems(const EntityID entity);
    void AddEntityToSystem(const EntityID entity, System* system);
    bool IsInSystem(const EntityID entity, const EntitySignature& signatures);

  private:
    uint16_t entityCount;
    std::queue<EntityID> availableEntityIDs;
    std::map<EntityID, std::shared_ptr<EntitySignature>> entitySignatures;
    std::map<SystemTypeID, std::shared_ptr<System>> registeredSystems;
    std::map<ComponentTypeID, std::shared_ptr<IComponentVector>> components;
  };
}