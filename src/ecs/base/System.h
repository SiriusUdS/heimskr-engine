/**
 * @file System.h
 * @brief Base class for systems.
 */

#pragma once
#include "ECSTypes.h"

namespace ECS {

  class System {
  public:
    System() = default;
    virtual ~System() = default;

    void AddEntity(const EntityID entity);
    void RemoveEntity(const EntityID entity);

    EntitySignature GetSignature() const;
    template<typename T>
    void AddComponentSignature();

    virtual void Start();
    virtual void Update();
    virtual void Destroy();

  protected:
    friend class Manager;
    EntitySignature signature;
    std::set<EntityID> entities;
  };
}
