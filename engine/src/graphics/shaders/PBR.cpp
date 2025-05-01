/**
 * @file PBR.cpp
 * @brief Method implementation for the PBRShader class.
 */

#include "PBR.h"

namespace HeimskrEngine {
  PBRShader::PBRShader(const std::string& filename) : Shader(filename) {
    u_Model = glGetUniformLocation(shaderID, "u_model");
    u_View = glGetUniformLocation(shaderID, "u_view");
    u_Projection = glGetUniformLocation(shaderID, "u_projection");
  }
}
