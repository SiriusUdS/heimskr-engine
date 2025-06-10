/**
 * @file GLGetError.h
 * @brief Module that contains OpenGL error handling functions for debugging.
 */

#pragma once

#include "../logging/Logger.h"
#include "../common/Core.h"

namespace HeimskrEngine {
  inline GLenum GLGetError(const char* file, int line) {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
      switch (error) {
      case GL_INVALID_ENUM:
        HEIMSKR_ERROR(fmt::format("Error in file '{}' at line '{}': GL_INVALID_ENUM", file, line));
        break;
      case GL_INVALID_VALUE:
        HEIMSKR_ERROR(fmt::format("Error in file '{}' at line '{}': GL_INVALID_VALUE", file, line));
        break;
      case GL_INVALID_OPERATION:
        HEIMSKR_ERROR(fmt::format("Error in file '{}' at line '{}': GL_INVALID_OPERATION", file, line));
        break;
      case GL_STACK_OVERFLOW:
        HEIMSKR_ERROR(fmt::format("Error in file '{}' at line '{}': GL_STACK_OVERFLOW", file, line));
        break;
      case GL_STACK_UNDERFLOW:
        HEIMSKR_ERROR(fmt::format("Error in file '{}' at line '{}': GL_STACK_UNDERFLOW", file, line));
        break;
      case GL_OUT_OF_MEMORY:
        HEIMSKR_ERROR(fmt::format("Error in file '{}' at line '{}': GL_OUT_OF_MEMORY", file, line));
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        HEIMSKR_ERROR(fmt::format("Error in file '{}' at line '{}': GL_INVALID_FRAMEBUFFER_OPERATION", file, line));
        break;
      }
    }
    return error;
  }

#define GLCheckError() GLGetError(__FILE__, __LINE__)
}
