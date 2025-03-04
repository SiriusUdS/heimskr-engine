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

    const EntityID CreateEntity();

  private:
    uint16_t entityCount;
    std::queue<EntityID> availableEntityIDs;
    std::map<EntityID, EntitySignature> entitySignatures;
    std::map<SystemTypeID, std::unique_ptr<System>> registeredSystems;
    std::map<ComponentTypeID, std::unique_ptr<IComponentVector>> componentVectors;
  };
}