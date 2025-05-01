/**
 * @file PBR.h
 * @brief PBR type shader class for physical-based rendering.
 */

#pragma once

#include "Shader.h"

namespace HeimskrEngine {
  /**
   * @class PBRShader
   * @brief Class for PBR (Physically Based Rendering) shader.
   */
  class PBRShader : public Shader {
  public:
    PBRShader() = default;
    PBRShader(const std::string& filename);

  private:
    uint32_t u_Model = 0u;
    uint32_t u_View = 0u;
    uint32_t u_Projection = 0u;
  };
}

