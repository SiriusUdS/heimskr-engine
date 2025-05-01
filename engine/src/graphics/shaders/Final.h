/**
 * @file Final.h
 * @brief Final shader class for post-processing effects.
 */

#pragma once
#include <cstdint>

#include "Shader.h"
#include "../utilities/Quad.h"

namespace HeimskrEngine {
  /**
   * @class FinalShader
   * @brief Class for the final shader used in post-processing effects.
   */
  class FinalShader : public Shader {
  public:
    FinalShader() = default;
    FinalShader(const std::string& filename);

    void SetSceneMap(uint32_t map) const;
    void Show(uint32_t map) const;

  private:
    GLint u_Map = 0;
    Quad2D quad;
  };
}
