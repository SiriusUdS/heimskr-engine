/**
 * @file Shader.cpp
 * @brief Method implementation for the Shader class.
 */

#include "Shader.h"

namespace HeimskrEngine {
  Shader::Shader(const std::string& filename) {
    shaderID = Load(filename);
  }

  Shader::~Shader() {
    glDeleteProgram(shaderID);
  }


  /**
   * \brief Unbinds the shader program.
   */
  void Shader::Unbind() {
    glUseProgram(0);
  }


  /**
   * \brief Binds the shader program.
   */
  void Shader::Bind() const {
    glUseProgram(shaderID);
  }


  /**
   * \brief Builds a shader from the provided source code to the specified type.
   * \param shaderSource The source code of the shader to be built.
   * \param type The type of the shader to be built (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
   * \return The ID of the compiled shader program.
   */
  uint32_t Shader::Build(const char* shaderSource, uint32_t type) {
    uint32_t id = glCreateShader(type);
    glShaderSource(id, 1, &shaderSource, nullptr);
    glCompileShader(id);

    int32_t status = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
      char error[512];
      glGetShaderInfoLog(id, sizeof(error), nullptr, error);
      HEIMSKR_CRITICAL(fmt::format("Failed to compile shader: {}. Error code: {}", shaderSource, error));
      glDeleteShader(id);
      return 0u;
    }
    return id;
  }


  /**
   * \brief Links the vertex and fragment shaders into a shader program.
   * \param vertexShader The ID of the vertex shader to be linked.
   * \param fragmentShader The ID of the fragment shader to be linked.
   * \return The ID of the linked shader program.
   */
  uint32_t Shader::Link(uint32_t vertexShader, uint32_t fragmentShader) {
    const uint32_t programID = glCreateProgram();
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glLinkProgram(programID);

    int32_t status = 0;
    glGetProgramiv(programID, GL_LINK_STATUS, &status);

    if (status == GL_FALSE) {
      char error[512];
      glGetProgramInfoLog(programID, sizeof(error), nullptr, error);
      HEIMSKR_CRITICAL(fmt::format("Failed to link program. Error code: {}", error));
      glDeleteProgram(programID);
      return 0u;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return programID;
  }


  /**
   * \brief Loads a shader from a file and compiles it.
   * \param filename The name of the file containing the shader source code.
   * \return The ID of the compiled shader program.
   */
  uint32_t Shader::Load(const std::string& filename) {
    std::ifstream file;
    file.exceptions(std::ifstream::failbit | std::fstream::badbit);

    try {
      bool loadingVertexSource = true;
      file.open(filename);
      std::string line;
      std::string vertexSource;
      std::string fragmentSource;

      // TODO: Instead of this, use a shader file for vertex and another for fragment
      while (std::getline(file, line)) {
        if (loadingVertexSource) {
          if (line.compare("++VERTEX++")) {
            vertexSource.append(line + "\n");
            continue;
          }
          loadingVertexSource = false;
        } else {
          if (line.compare("++FRAGMENT++")) {
            fragmentSource.append(line + "\n");
          }
        }
      }
      file.close();
      const uint32_t vertexShader = Build(vertexSource.c_str(), GL_VERTEX_SHADER);
      const uint32_t fragmentShader = Build(fragmentSource.c_str(), GL_FRAGMENT_SHADER);
      return Link(vertexShader, fragmentShader);
    } catch (const std::exception& exception) {
      HEIMSKR_ERROR(fmt::format("Loading of the file '{}' failed with error: '{}'", filename, exception.what()));
    }
    return 0;
  }
}
