/**
 * @file Transform3D.h
 * @brief Data structure for 3D transformations, including position, rotation, and scale.
 */

#pragma once
#include "../GLMCommon.h"

namespace HeimskrEngine {
  /**
   * @brief Represents a 3D transformation with position, rotation, and scale.
   */
  struct Transform3D {
    Transform3D() = default;
    Transform3D(const Transform3D&) = default;
    virtual ~Transform3D() = default;

    /**
     * \brief Constructs the transformation matrix with the given translation, rotation, and scale.
     * \return The transformation matrix.
     */
    [[nodiscard]] glm::mat4 Matrix() const {
      const glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), Translation);
      const glm::mat4 rotationMatrix = glm::toMat4(glm::quat(glm::radians(Rotation)));
      const glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), Scale);

      return translationMatrix * rotationMatrix * scaleMatrix;
    }

    glm::vec3 Translation = glm::vec3(0.0f);
    glm::vec3 Rotation = glm::vec3(0.0f);
    glm::vec3 Scale = glm::vec3(0.0f);
  };
}
