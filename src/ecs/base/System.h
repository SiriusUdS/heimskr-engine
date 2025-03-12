/**
 * @file System.h
 * @brief Base class for systems.
 */

#pragma once

#include <iostream>

#include "ECSTypes.h"

namespace ECS {

  class System {
  public:
    System() = default;
    virtual ~System() = default;

    void AddEntity(const EntityID entity);
    void RemoveEntity(const EntityID entity);

    EntitySignature GetSignature() const;


    /**
     * \brief Add a component to the system signature. This will allow the system to process entities with this component.
     */
    template<typename T>
    void AddComponentSignature() {
      signature.insert(GetComponentTypeID<T>());
    }

    virtual void Start();
    virtual void Update();
    virtual void Render();
    virtual void Destroy();

  protected:
    friend class EntityManager;
    EntitySignature signature;
    std::set<EntityID> entities;
  };
}
