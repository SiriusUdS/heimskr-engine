/**
 * @file Final.cpp
 * @brief Implementation of the Final shader class methods.
 */

#include "Final.h"

namespace HeimskrEngine {
  FinalShader::FinalShader(const std::string& filename) : Shader(filename) {
    u_Map = glGetUniformLocation(shaderID, "u_map");
    quad = CreateQuad2D();
  }


  /**
   * \brief Activates a texture unit and binds the scene map to it.
   * \param map The texture ID of the scene map to be set.
   */
  void FinalShader::SetSceneMap(uint32_t map) const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, map);
    glUniform1i(u_Map, 0);
  }


  /**
   * \brief Configures the framebuffer for rendering the final scene.
   * \param map The texture ID of the scene map to be displayed.
   */
  void FinalShader::Show(uint32_t map) const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, map);
    glUniform1i(u_Map, 0);
    quad->Draw(GL_TRIANGLES);
    glUseProgram(0);
  }

}