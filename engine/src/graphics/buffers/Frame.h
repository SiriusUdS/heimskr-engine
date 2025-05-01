/**
 * @file Frame.h
 * @brief Wrapper class that manipulates the framebuffer from OpenGL
 */

#pragma once
#include <cstdint>
#include <GL/glew.h>

#include "Logger.h"

namespace HeimskrEngine {
  class FrameBuffer {
  public:
    FrameBuffer() = default;
    FrameBuffer(int32_t width, int32_t height);
    ~FrameBuffer();

    [[nodiscard]] float Ratio() const;
    void Resize(int32_t width, int32_t height);
    [[nodiscard]] uint32_t GetTexture() const;

    void Begin() const;
    void End() const;

  private:
    inline void CreateColorAttachment();
    inline void CreateRenderBuffer();

  private:
    uint32_t bufferID = 0u;
    uint32_t render = 0u;
    uint32_t color = 0u;
    int32_t height = 0;
    int32_t width = 0;
  };
}
