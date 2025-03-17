/**
 * @file Interface.h
 * @brief Base Interface class for the CIL (Context, Interface, Layers) design.
 * @details This class is responsible for implementing functions that facilitate the communication between the Context and Layers.
 */

#pragma once

#include "Context.h"
#include "../../../common/src/utility/AssertMsgFormat.h"
#include "../../../common/src/Types.h"
#include "../../../common/src/logging/Logger.h"

namespace HeimskrEngine {
  class AppInterface {
  public:
    AppInterface() = default;
    virtual ~AppInterface() = default;


    /**
     * \brief Gets a specific layer from the context if found.
     * \tparam Layer The layer to get from the context. Must inherit from the AppInterface class.
     * \return The layer pointer if found, otherwise nullptr.
     */
    template<typename Layer>
    Layer* GetLayer() {
      static_assert(std::is_base_of_v<AppInterface, Layer>, "The Layer type needs to inherit from the AppInterface class.");

      auto iterator = std::find_if(context->Layers.begin(), context->Layers.end(), [&](AppInterface* layer) {
        return layer->id == TypeID<Layer>();
      });
      if (iterator == context->Layers.end()) {
        return nullptr;
      }
      return static_cast<Layer*>(*iterator);
    }


    /**
     * \brief Attaches a new layer to the context if not already attached.
     * \tparam Layer The layer to attach to the context. Must inherit from the AppInterface class.
     * \param args The arguments to pass to the layer's constructor.
     * \return The layer pointer if successfully attached, otherwise nullptr.
     */
    template<typename  Layer, typename... Args>
    Layer* AttachLayer(Args&&... args) {
      static_assert(std::is_base_of_v<AppInterface, Layer>, "The Layer type needs to inherit from the AppInterface class.");

      if (GetLayer<Layer>() != nullptr) {
        HEIMSKR_ERROR("Cannot attach layer. The layer is already attached to this application context.");
        return nullptr;
      }

      Layer layer = new Layer(std::forward<Args>(args)...);
      context->Layers.push_back(layer);
      layer.id = TypeID<Layer>();
      layer.context = context;
      layer.OnStart();
      return layer;
    }

    /**
     * \brief Start a task that detaches a layer from the context if found.
     * \details Since we cannot simply remove a layer from the context while iterating through the layers, we need to post a task to the event queue to remove the layer while it is not in use.
     * \tparam Layer The layer to detach from the context. Must inherit from the AppInterface class.
     */
    template<typename Layer>
    void DetachLayer() {
      static_assert(std::is_base_of_v<AppInterface, Layer>, "The Layer type needs to inherit from the AppInterface class.");

      context->EventDispatcher.PostTask([this] {
        context->Layers.erase(std::remove_if(context->Layers.begin(), context->Layers.end(), [this](auto& layer) {
          if (layer.id == TypeID<Layer>()) {
            context->EventDispatcher.EraseListener(layer.id);
            if (layer != nullptr) {
              delete layer;
              layer = nullptr;
            }
            return true;
          }
          return false;
        }), context->Layers.end());
      });
    }

  protected:
    virtual void OnUpdate() {}
    virtual void OnStart() {}

  private:
    friend class Application;
    AppContext* context;
    uint32_t id;
  };
}
