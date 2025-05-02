/**
 * @file Entities3D.h
 * @brief Since an entity is only a 32 bits integer, this class is used as a wrapper around entities to simplify the handling of game objects.
 */

#pragma once

#include "ECS.h"

namespace HeimskrEngine {
  /**
   * \class Entity
   * \brief Wrapper class for entities in the ECS framework.
   */
  class Entity {
  public:
    Entity() = default;
    Entity(entt::registry* registry, entt::entity entity) : registry(registry), entity(entity) {}
    Entity(entt::registry* registry) : registry(registry) {}
    virtual ~Entity() = default;

    /**
     * \brief Implicit conversion operator to entt::entity.
     * Allows the Entity object to be implicitly used as an entt::entity.
     * Useful for passing Entity objects directly to functions that expect an entt::entity.
     */
    operator entt::entity() const {
      return entity;
    }


    /**
     * \brief Implicit conversion operator to bool.
     * Returns true if the entity is valid (i.e., the registry is non-null and the entity is alive).
     * Enables the use of Entity in conditional expressions (e.g., `if (entity)`).
     */
    operator bool() const {
      return registry != nullptr && registry->valid(entity);
    }


    /**
     * \brief Returns the entity ID.
     * \return The entity ID.
     */
    entt::entity ID() const {
      return entity;
    }


    /**
     * \brief Attaches a component to the entity.
     * \tparam T Type of the component to attach.
     * \tparam Args Variadic template arguments for component constructor.
     * \param args Constructor arguments for the component.
     * \return Reference to the attached component.
     */
    template<typename T, typename ... Args>
    T& Attach(Args&&... args) {
      return registry->get_or_emplace<T>(entity, std::forward<Args>(args)...);
    }


    /**
     * \brief Detaches a component from the entity.
     * \tparam T Type of the component to detach.
     */
    template<typename T>
    void Detach() const {
      registry->remove<T>(entity);
    }


    /**
     * \brief Destroys the entity.
     */
    void Destroy() const {
      if (!registry) {
        return;
      }
      registry->destroy(entity);
    }


    /**
     * \brief Checks if the entity has a specific component.
     * \tparam T Type of the component to check.
     * \return True if the entity has the component, false otherwise.
     */
    template<typename T>
    bool Has() const {
      if (!registry) {
        return false;
      }
      return registry->all_of<T>(entity);
    }


    /**
     * \brief Gets a component from the entity.
     * \tparam T Type of the component to get.
     * \return Reference to the component.
     */
    template<typename T>
    T& Get() const {
      return registry->get<T>(entity);
    }

  protected:
    entt::registry* registry = nullptr;
    entt::entity entity = entt::null;
  };
}