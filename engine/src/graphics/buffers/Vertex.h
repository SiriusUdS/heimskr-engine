/**
 * @file Vertex.h
 * @brief Class containing the basic vertex data structure.
 */

#pragma once

#include <vector>

#include "../GLMCommon.h"

namespace HeimskrEngine {

  /**
   * \brief Represents a quad vertex used for rendering basic shapes, like sprite and GUI elements.
   */
  struct QuadVertex {
    /**
     * \brief First 2 floats represents the position in space, the next 2 are the texture coordinates (UV).
     */
    float Data[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
  };


  /**
   * \brief Represents a vertex used for simple color shading without lighting or shading.
   */
  struct UnlitVertex {
    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec4 Color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
  };


  /**
   * \brief Represents a vertex used for shading with lighting and texture mapping (UV).
   */
  struct ShadedVertex {
    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Normal = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec2 UVs = glm::vec2(0.0f, 0.0f);
  };


  /**
   * \brief Contains the vertex buffer data for a mesh.
   * \tparam Vertex Vertex type in the mesh. 
   */
  template<typename Vertex>
  struct MeshData {
    std::vector<Vertex> Vertices;
    /**
     * \brief Makes vertices that are at the same place in the vector share the same index so it doesn't duplicate vertices data unnecessarily. See figure 5.5
     */
    std::vector<uint32_t> Indices;
  };
}