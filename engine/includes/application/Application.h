/**
 * @file Application.h
 * @brief Base Application class for the CIL (Context, Interface, Layers) design.
 */

#pragma once
#include "Interface.h"

namespace HeimskrEngine {
  class Application : AppInterface {
  public:
    Application() {
      context = new AppContext();
      ID = TypeID<Application>();
    }

    ~Application() override {
      if (context != nullptr) {
        delete context;
        context = nullptr;
      }
    }

    /**
     * \brief Update every layers in the context.
     */
     void RunContext() const {
      while (true) {
        for (const auto& layer : context->Layers) {
          layer->OnUpdate();
        }
      }
    }
  };
}
