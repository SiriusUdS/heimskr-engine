/**
 * @file Inputs.h
 * @brief Contains the structure for the window inputs.
 */

#pragma once

#include <bitset>

#include "../common/Event.h"

#include "../common/Core.h"

namespace HeimskrEngine {
  struct WindowInputs {
    std::bitset<GLFW_MOUSE_BUTTON_LAST> Mouse;
    std::bitset<GLFW_KEY_LAST> Keys;
    double MouseX = 0.0;
    double MouseY = 0.0;
  };
}
