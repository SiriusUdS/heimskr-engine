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

  //EntityManager::~EntityManager() { }

  const EntityID EntityManager::CreateEntity() {
    ASSERT(entityCount < MAX_ENTITIES, "Maximum number of entities reached (" << MAX_ENTITIES << ").");
    const EntityID entityID = availableEntityIDs.front();
    availableEntityIDs.pop();
    entityCount++;
    return entityID;
  }

}
