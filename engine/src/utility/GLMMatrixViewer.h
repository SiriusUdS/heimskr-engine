/**
 * @file GLMMatrixViewer.h
 * @brief Module that contains utility functions for viewing the contents of GLM matrices.
 */

#pragma once

#include <iostream>
#include <string>

#include "../common/Core.h"

namespace HeimskrEngine {
  inline void printMat4(const glm::mat4& mat, const std::string& name) {
    std::cout << name << ":" << std::endl;
    for (int row = 0; row < 4; ++row) {
      std::cout << "[ ";
      for (int col = 0; col < 4; ++col) {
        std::cout << mat[col][row] << " ";
      }
      std::cout << "]" << std::endl;
    }
  }
}