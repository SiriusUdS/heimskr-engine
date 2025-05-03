/**
 * @file Components3D.h
 * @brief Structure for 3D components in the ECS framework.
 */

#pragma once
#include <string>

#include "../graphics/buffers/Mesh.h"
#include "ECS.h"

namespace HeimskrEngine {
  /**
   * \brief Component for 3D transformations.
   */
  struct TransformComponent {
    TransformComponent() = default;
    TransformComponent(const TransformComponent&) = default;
    virtual ~TransformComponent() = default;

    Transform3D Transform;
  };


  /**
   * \brief Component for 3D cameras.
   */
  struct CameraComponent {
    CameraComponent() = default;
    CameraComponent(const CameraComponent&) = default;
    virtual ~CameraComponent() = default;

    Camera3D Camera;
  };


  /**
   * \brief Base component for Entt components.
   *
   */
  struct EnttComponent {
    EnttComponent() = default;
    EnttComponent(const EnttComponent&) = default;
    virtual ~EnttComponent() = default;

    std::string Name = "Undefined";
  };


  /**
   * \brief Component for 3D meshes.
   */
  struct MeshComponent {
    MeshComponent() = default;
    MeshComponent(const MeshComponent&) = default;
    virtual ~MeshComponent() = default;

    Mesh3D Mesh;
  };
}
