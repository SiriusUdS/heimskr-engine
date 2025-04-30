/**
 * @file Interface.h
 * @brief Base Interface class for the CIL (Context, Interface, Layers) design.
 * @details This class is responsible for implementing functions that facilitate the communication between the Context and Layers.
 */

#pragma once

#include "Context.h"
#include "../logging/Logger.h"
#include "../common/Types.h"

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

      Layer* layer = new Layer(std::forward<Args>(args)...);
      context->Layers.push_back(layer);
      layer->id = TypeID<Layer>();
      layer->context = context;
      layer->OnStart();
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
          if (layer->id == TypeID<Layer>()) {
            context->EventDispatcher.EraseListener(layer->id);
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


    /**
     * \brief Attach an event callback function to the event dispatcher.
     * \tparam Event The event type to attach the callback to. Must inherit from the Event class.
     * \tparam Callback The callback function type. Must be callable with the event type as the first argument.
     * \param callback The callback function to attach to the event dispatcher.
     */
    template<typename Event, typename Callback>
    void AttachCallback(Callback&& callback) {
      context->EventDispatcher.AttachListener<Event>(std::move(callback), id);
    }


    /**
     * \brief Post an event to the event dispatcher.
     * \tparam Event The event type to post. Must inherit from the Event class.
     * \tparam Args The arguments type to pass to the event constructor.
     * \param args The arguments to pass to the event constructor.
     */
    template <typename Event, typename ... Args>
    void PostEvent(Args&& ... args) {
      context->EventDispatcher.PostEvent<Event>(std::forward<Args>(args)...);
    }


    /**
     * \brief Post a task to the event dispatcher.
     * \tparam Task The task type to post. Must be callable.
     * \param task The task to post to the event dispatcher.
     */
    template<typename Task>
    void PostTask(Task&& task) {
      context->EventDispatcher.PostTask(std::move(task));
    }


    /**
     * \brief Detach a callback function from the event dispatcher.
     * \tparam Event The event type to detach the callback from. Must inherit from the Event class.
     */
    template<typename Event>
    void DetachCallback() const {
      context->EventDispatcher.DetachListener<Event>(id);
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
