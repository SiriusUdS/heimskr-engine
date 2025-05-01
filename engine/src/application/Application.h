/**
 * @file Application.h
 * @brief Base Application class for the CIL (Context, Interface, Layers) design.
 */

#pragma once
#include "Interface.h"

namespace HeimskrEngine {
  class Application : public AppInterface {
  public:
    Application() {
      context = new AppContext();
      id = TypeID<Application>();
    }

    ~Application() override {
      if (context != nullptr) {
        delete context;
        context = nullptr;
      }
    }

    /**
     * \brief Update every layers in the context and poll for events.
     */
    [[noreturn]]
    void RunContext() const {
      while (context->Window->PollEvents()) {
        for (const auto& layer : context->Layers) {
          layer->OnUpdate();
        }
      }
    }
  };
}
