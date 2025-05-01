/**
 * @file Shader.h
 * @brief Base class for shaders with common methods and properties.
 */

#pragma once
#include <cstdint>
#include <string>
#include <fstream>

#include <GL/glew.h>

#include "../logging/Logger.h"

namespace HeimskrEngine {
  class Shader {
  public:
    Shader() = default;
    Shader(const std::string& filename);
    virtual ~Shader();

    inline static void Unbind();
    inline void Bind() const;

  private:
    static uint32_t Build(const char* shaderSource, uint32_t type);
    static uint32_t Link(uint32_t vertexShader, uint32_t fragmentShader);
    static uint32_t Load(const std::string& filename);

  protected:
    uint32_t shaderID = 0u;
  };
}
