/**
 * @file Renderer.h
 * @brief Renderer class that interacts with GLEW and OpenGL.
 */

#pragma once
#include <cstdint>
#include <GL/glew.h>

#include "Logger.h"

namespace HeimskrEngine {
  class Renderer {
  public:
    Renderer(int32_t width, int32_t height) {
      if (glewInit() != GLEW_OK) {
        HEIMSKR_CRITICAL("GLEW not initialized. Engine shutting down...");
        exit(EXIT_FAILURE);
      }
      glewExperimental = GL_TRUE;
    }
  };
}
