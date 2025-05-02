/**
 * @file Camera3D.h
 * @brief Data structure for 3D camera properties, including position, rotation, and projection matrix.
 */

#pragma once
#include <glm/ext/matrix_transform.hpp>

#include "Transform3D.h"

namespace HeimskrEngine {
  /**
   * \brief Represents a 3D camera with properties for position, rotation, and projection.
   */
  struct Camera3D {
    Camera3D() = default;

    /**
     * \brief Constructs the camera with the given position, rotation, and projection matrix.
     * \return The camera's view matrix.
     */
    [[nodiscard]] static glm::mat4 View(const Transform3D& transform3D) {
      const glm::vec3 eyeVector = transform3D.Translation;
      const glm::vec3 centerVector = transform3D.Translation + glm::vec3(0.0f, 0.0f, -1.0f);
      constexpr glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

      return glm::lookAt(eyeVector, centerVector, upVector);
    }


    /**
     * \brief Combines the projection and view matrices to create a frustum matrix.
     * \param transform3D The transformation matrix for the camera.
     * \param ratio The aspect ratio of the viewport (width/height).
     * \return The combined frustum matrix.
     */
    [[nodiscard]] glm::mat4 Frustum(const Transform3D& transform3D, float ratio) const {
      return Projection(ratio) * View(transform3D);
    }


    /**
     * \brief Creates a perspective projection matrix based on the camera's properties.
     * \param ratio The aspect ratio of the viewport (width/height).
     * \return The perspective projection matrix.
     */
    [[nodiscard]] glm::mat4 Projection(float ratio) const {
      return glm::perspective(FOV, ratio, NearPlane, FarPlane);
    }

    float NearPlane = 0.3f;
    float FarPlane = 1000.0f;
    float FOV = 45.0f;
  };
}
