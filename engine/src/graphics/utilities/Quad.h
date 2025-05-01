/**
 * @file Quad.h
 * @brief Contains the function to generate a quad mesh for rendering testing.
 */

#pragma once

#include "../buffers/Mesh.h"

namespace HeimskrEngine {
  using Quad3D = std::unique_ptr<Mesh<ShadedVertex>>;
  using Quad2D = std::unique_ptr<Mesh<QuadVertex>>;

  inline Quad2D CreateQuad2D() {
    MeshData<QuadVertex> quadData;
    quadData.Vertices = {
      { -1.0f, -1.0f, 0.0f, 0.0f },
      {  -1.0f, 0.0f, 0.0f, 1.0f },
      {  1.0f,  1.0f, 1.0f, 1.0f },
      { 0.0f,  -1.0f, 1.0f, 0.0f }
    };
    quadData.Indices = {
      0, 1, 2,
      0, 2, 3
    };
    return std::make_unique<Mesh<QuadVertex>>(std::move(quadData));
  }

  inline Quad3D CreateQuad3D() {
    MeshData<ShadedVertex> quadData;

    ShadedVertex v0, v1, v2, v3;

    v0.Position = glm::vec3(-0.5f, -0.5f, 0.0f);
    v1.Position = glm::vec3(0.05, -0.5f, 0.0f);
    v2.Position = glm::vec3(0.5f, 0.5f, 0.0f);
    v3.Position = glm::vec3(-0.5f, 0.5f, 0.0f);

    v0.Normal = glm::vec3(0.0f, 0.0f, 1.0f);
    v1.Normal = glm::vec3(0.0f, 0.0f, 1.0f);
    v2.Normal = glm::vec3(0.0f, 0.0f, 1.0f);
    v3.Normal = glm::vec3(0.0f, 0.0f, 1.0f);

    v0.UVs = glm::vec2(0.0f, 0.0f);
    v1.UVs = glm::vec2(1.0f, 0.0f);
    v2.UVs = glm::vec2(1.0f, 1.0f);
    v3.UVs = glm::vec2(0.0f, 1.0f);

    quadData.Vertices = { v0, v1, v2, v3 };

    quadData.Indices = {
      0, 1, 2,
      0, 2, 3
    };

    return std::make_unique<Mesh<ShadedVertex>>(std::move(quadData));
  }
}