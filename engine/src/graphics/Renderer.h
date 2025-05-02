/**
 * @file Renderer.h
 * @brief Renderer class that interacts with GLEW and OpenGL.
 */

#pragma once
#include <cstdint>
#include <GL/glew.h>

#include "Logger.h"
#include "buffers/Frame.h"
#include "shaders/Final.h"
#include "shaders/PBR.h"

namespace HeimskrEngine {
  class Renderer {
  public:
    Renderer(int32_t width, int32_t height) {
      if (glewInit() != GLEW_OK) {
        HEIMSKR_CRITICAL("GLEW not initialized. Engine shutting down...");
        exit(EXIT_FAILURE);
      }
      glewExperimental = GL_TRUE;

      finalShader = std::make_unique<FinalShader>("resources/shaders/final.glsl");
      pbrShader = std::make_unique<PBRShader>("resources/shaders/pbr.glsl");
      frameBuffer = std::make_unique<FrameBuffer>(width, height);
    }


    /**
     * \brief Sets the camera properties for the shader.
     * \param camera The camera object containing the projection and view matrices.
     * \param transform The transform object containing the camera's transformation data.
     */
    void SetCamera(const Camera3D& camera, const Transform3D& transform) const {
      pbrShader->SetCamera(camera, transform, frameBuffer->Ratio());
    }


    /**
     * \brief Draws the mesh using the shader.
     * \param mesh The mesh object to be drawn.
     * \param transform The transform object containing the mesh's transformation data.
     */
    void Draw(const Mesh3D& mesh, const Transform3D& transform) const {
      pbrShader->Draw(mesh, transform);
    }


    /**
     * \brief Resizes the frame buffer.
     * \param width The new width of the frame buffer.
     * \param height The new height of the frame buffer.
     */
    void Resize(int32_t width, int32_t height) const {
      frameBuffer->Resize(width, height);
    }


    /**
     * \brief Gets the frame buffer texture.
     * \return The texture ID of the frame buffer.
     */
    uint32_t GetFrameBuffer() const {
      return frameBuffer->GetTexture();
    }


    /**
     * \brief Begins the frame rendering process.
     */
    void BeginFrame() const {
      frameBuffer->Begin();
      pbrShader->Bind();
    }


    /**
     * \brief Ends the frame rendering process.
     */
    void EndFrame() const {
      pbrShader->Unbind();
      frameBuffer->End();
    }


    /**
     * \brief Displays the frame buffer texture using the final shader.
     */
    void ShowFrame() const {
      finalShader->Show(frameBuffer->GetTexture());
    }

  private:
    std::unique_ptr<FrameBuffer> frameBuffer;
    std::unique_ptr<FinalShader> finalShader;
    std::unique_ptr<PBRShader> pbrShader;
  };
}
