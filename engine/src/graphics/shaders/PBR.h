/**
 * @file PBR.h
 * @brief PBR type shader class for physical-based rendering.
 */

#pragma once

#include "Shader.h"
#include "../ecs/ECS.h"

#include "../utility/GLGetError.h"

namespace HeimskrEngine {
  /**
   * @class PBRShader
   * @brief Class for PBR (Physically Based Rendering) shader.
   */
  class PBRShader : public Shader {
  public:
    PBRShader() = default;
    PBRShader(const std::string& filename);

    void SetCamera(const Camera3D& camera, const Transform3D& transform, float ratio) const;
    void Draw(const Mesh3D& mesh, const Transform3D& transform) const;

  private:
    GLint u_Model = 0u;
    GLint u_View = 0u;
    GLint u_Projection = 0u;
  };
}

