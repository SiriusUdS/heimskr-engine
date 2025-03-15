/**
 * @file Context.h
 * @brief Base Context class for the CIL (Context, Interface, Layers) design.
 * @details The context surves as the main container for the application layers, data, configuration, events, etc.
 */

#pragma once
#include <vector>

#include "Interface.h"

namespace HeimskrEngine {
  class AppInterface;

  class AppContext {
  public:
    AppContext() = default;
    ~AppContext() {
      for (auto& layer : Layers) {
        if (layer == nullptr) {
          continue;
        }
        delete layer;
        layer = nullptr;
      }
    }

    /**
     * \brief Layers are object can be seem as extensions adding functionalities to the engine. They allow the user to manipulate the engine's unused functionalities.
     */
    std::vector<AppInterface*> Layers;
  };
}
