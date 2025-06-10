/**
 * @file Context.h
 * @brief Base Context class for the CIL (Context, Interface, Layers) design.
 * @details The context surves as the main container for the application layers, data, configuration, events, etc.
 */

#pragma once
#include <vector>

#include "Interface.h"
#include "../common/Event.h"
#include "../ecs/ECS.h"
#include "../window/Window.h"
#include "../graphics/Renderer.h"

namespace HeimskrEngine {
  class AppInterface;

  class AppContext {
  public:
    AppContext() {
      Window = std::make_unique<class Window>(&EventDispatcher, 1280, 1280, "Heimskr Engine");
      Renderer = std::make_unique<class Renderer>(1280, 1280);
    }

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
    std::unique_ptr<Window> Window;
    std::unique_ptr<Renderer> Renderer;
    EventDispatcher EventDispatcher;
    entt::registry SceneRegistry;
  };
}
