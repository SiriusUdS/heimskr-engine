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


    /**
     * \brief Add a component to the entity.
     * \tparam T The type of the component.
     * \tparam Args The arguments type to pass to the component constructor.
     * \param[in] args The arguments to pass to the component constructor.
     */
    template<typename T, typename... Args>
    void AddComponent(Args&&... args) {
      manager->AddComponent<T>(id, std::forward<Args>(args)...);
    }


    /**
     * \brief Add a component to the entity.
     * \tparam T The type of the component.
     * \param[in] component The component to add.
     */
    template<typename T>
    void AddComponent(T& component) {
      manager->AddComponent<T>(id, component);
    }


    /**
     * \brief Get a component from the entity.
     * \tparam T The type of the component.
     * \return[in] The component.
     */
    template<typename T>
    T& GetComponent() {
      return manager->GetComponent<T>(id);
    }


    /**
     * \brief Remove a component from the entity.
     * \tparam T The type of the component.
     */
    template<typename T>
    void RemoveComponent() const {
      manager->RemoveComponent<T>(id);
    }


    /**
     * \brief Check if the entity has a component.
     * \tparam T The type of the component.
     * \return True if the entity has the component, false otherwise.
     */
    template<typename T>
    bool HasComponent() const {
      return manager->HasComponent<T>(id);
    }

  private:
    EntityID id;
    EntityManager* manager;
  };
}
