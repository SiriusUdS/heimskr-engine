/**
 * @file Mesh.h
 * @brief Class containing the mesh data and methods to load and draw the mesh.
 */

#pragma once
#include <cstdint>
#include <GL/glew.h>

#include "Logger.h"
#include "Vertex.h"
#include "../../common/Types.h"

namespace HeimskrEngine {
  template<typename Vertex>
  class Mesh {
  public:
    Mesh() = default;
    Mesh(const MeshData<Vertex>& data) {
      InitializeMesh(data);
    }

    ~Mesh() {
      glDeleteVertexArrays(1, &bufferID);
    }


    /**
     * \brief Draws the mesh with the given mode.
     * \param mode The mode to draw the mesh with. See OpenGL documentation for more information.
     */
    void Draw(uint32_t mode) const {
      glBindVertexArray(bufferID);
      if (indexCount != 0) {
        glDrawElements(mode, indexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
      }
      glDrawArrays(mode, 0, vertexCount);
      glBindVertexArray(0);
    }

  private:
    /**
     * \brief Initializes the mesh with the given data.
     * \param data The mesh data to initialize the mesh with.
    */
    void InitializeMesh(const MeshData<Vertex>& data) {
      if (data.Vertices.empty()) {
        HEIMSKR_ERROR("Mesh data is empty. Cannot create mesh.");
        return;
      }

      vertexCount = static_cast<uint32_t>(data.Vertices.size());
      indexCount = static_cast<uint32_t>(data.Indices.size());

      // Note: The VAO contains the VBO and EBO (IBO) and their configuration. Used primarily for optimization purposes.
      glGenVertexArrays(1, &bufferID);
      glBindVertexArray(bufferID);

      // Note: The VBO contains the vertex related data.
      uint32_t vertexBufferObject = 0u;
      glGenBuffers(1, &vertexBufferObject);
      glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
      glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), data.Vertices.data(), GL_STATIC_DRAW);

      if (indexCount != 0) {
        // Note: The EBO (or IBO) contains the indices of the vertices to be drawn. It is used to optimize the drawing process by reducing the amount of data sent to the GPU by skipping the duplicated vertices.
        uint32_t elementBufferObject = 0u;
        glGenBuffers(1, &elementBufferObject);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(uint32_t), data.Indices.data(), GL_STATIC_DRAW);
      }

      if (TypeID<Vertex>() == TypeID<ShadedVertex>()) {
        SetAttribute(0, 3, reinterpret_cast<void*>(offsetof(ShadedVertex, Position)));
        SetAttribute(1, 3, reinterpret_cast<void*>(offsetof(ShadedVertex, Normal)));
        SetAttribute(2, 2, reinterpret_cast<void*>(offsetof(ShadedVertex, UVs)));
      }
      else if (TypeID<Vertex>() == TypeID<UnlitVertex>()) {
        SetAttribute(0, 3, reinterpret_cast<void*>(offsetof(UnlitVertex, Position)));
        SetAttribute(1, 4, reinterpret_cast<void*>(offsetof(UnlitVertex, Color)));
      }
      else if (TypeID<Vertex>() == TypeID<QuadVertex>()) {
        SetAttribute(0, 4, reinterpret_cast<void*>(offsetof(QuadVertex, Data)));
      }
      else {
        HEIMSKR_ERROR("Unknown vertex type. Cannot create mesh.");
      }
      glBindVertexArray(0);
    }


    /**
     * \brief Sets attributes for the vertex buffer.
     * \param index The index of the attribute to set.
     * \param size The size of the attribute.
     * \param value The value of the attribute.
     */
    static void SetAttribute(uint32_t index, int32_t size, const void* value) {
      glEnableVertexAttribArray(index);
      glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, sizeof(Vertex), value);
    }

  private:
    uint32_t vertexCount = 0;
    uint32_t indexCount = 0;
    uint32_t bufferID = 0;
  };

  using ShadedMesh = Mesh<ShadedVertex>;
  using Mesh3D = std::shared_ptr<ShadedMesh>;
}
