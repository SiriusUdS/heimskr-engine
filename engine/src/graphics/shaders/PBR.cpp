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


  /**
   * \brief Sets the camera properties for the shader.
   * \param camera The camera object containing the projection and view matrices.
   * \param transform The transform object containing the camera's transformation data.
   * \param ratio The aspect ratio of the viewport (width/height).
   */
  void PBRShader::SetCamera(const Camera3D& camera, const Transform3D& transform, float ratio) const {
    glUniformMatrix4fv(u_Projection, 1, GL_FALSE, glm::value_ptr(camera.Projection(ratio)));
    glUniformMatrix4fv(u_View, 1, GL_FALSE, glm::value_ptr(Camera3D::View(transform)));
  }


  /**
   * \brief Draws the mesh using the shader.
   * \param mesh The mesh object to be drawn.
   * \param transform The transform object containing the mesh's transformation data.
   */
  void PBRShader::Draw(const Mesh3D& mesh, const Transform3D& transform) const {
    glUniformMatrix4fv(u_Model, 1, GL_FALSE, glm::value_ptr(transform.Matrix()));
    mesh->Draw(GL_TRIANGLES);
  }
}
