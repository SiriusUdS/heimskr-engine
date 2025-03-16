/**
 * @file Event.h
 * @brief This contains the event dispatcher and listener classes.
 */

#pragma once
#include <functional>
#include <memory>
#include <queue>
#include <ranges>

#include "../../../../common/src/Types.h"

namespace HeimskrEngine {

  template<typename Event>
  class EventListener {
    using CallbackFunction = std::function<void(const Event&)>;
  public:
    EventListener(CallbackFunction&& cb, uint32_t listenerId) : Callback(std::move(cb), Id(listenerId)) {}

  public:
    CallbackFunction Callback;
    uint32_t Id;
  };

  template<typename Event>
  class EventRegistry {
    using Listener = std::unique_ptr<EventListener<Event>>;
  public:
    EventRegistry() = default;
    virtual ~EventRegistry() = default;

  public:
    std::queue<std::unique_ptr<Event>> Queue;
    std::vector<Listener> Listeners;
  };

  class EventDispatcher {
  public:
    EventDispatcher() = default;
    virtual ~EventDispatcher() {
      // Reminder since unused to syntax. It just means that we are iterating over the values of the registry map.
      for (const auto& ptr : registry | std::views::values) {
        // We cast the void* of the Event as a char since we don't know the type of the event and just use char as a placeholder.
        auto reg = ConvertToRegistry<char>(ptr);
        if (reg == nullptr) {
          continue;
        }
        delete reg;
        reg = nullptr;
      }
    }


    /**
     * \brief Create a new event with a listener and add it to the registry.
     * \tparam Event The type of the event to create.
     * \tparam CallbackFunc The callback function to call when the event is dispatched.
     * \param cb The callback function to call when the event is dispatched.
     * \param listenerId The unique identifier for the listener.
     */
    template<typename Event, typename CallbackFunc>
    void AttachListener(CallbackFunc&& cb, uint32_t listenerId) {
      EventListener<Event> listener = std::make_unique<EventListener<Event>>(std::move<CallbackFunc>(cb), listenerId);
      GetRegistry<Event>()->Listeners.push_back(std::move(listener));
    }


    /**
     * \brief Detach a listener from the event registry.
     * \tparam Event The type of the event to detach the listener from.
     * \param listenerId The unique identifier for the listener.
     */
    template<typename Event>
    void DetachListener(uint32_t listenerId) {
      auto& listeners = GetRegistry<Event>()->Listeners;
      listeners.erase(std::remove_if(listeners.begin(), listeners.end(), [&](const auto& listener) {
        return listener->Id == listenerId;
      }), listeners.end());
    }


    /**
     * \brief Erase a listener from the event registry.
     * \param listenerId The unique identifier for the listener.
     */
    void EraseListener(uint32_t listenerId) {
      for (auto& [_, registry] : registry) {
        auto& listeners = ConvertToRegistry<int8_t>(registry)->Listeners;
        listeners.erase(std::remove_if(listeners.begin(), listeners.end(), [&](const auto& listener) {
          return listener->Id == listenerId;
        }), listeners.end());
      }
    }


    /**
     * \brief Post(Add) a new event to the event queue if there are listeners for the event.
     * \tparam Event The type of the event to post.
     * \tparam Args The arguments to pass to the event constructor.
     * \param args The arguments to pass to the event constructor.
     */
    template<typename Event, typename... Args>
    void PostEvent(Args&&... args) {
      EventRegistry<Event> reg = GetRegistry<Event>();
      if (reg->Listeners.empty()) {
        return;
      }
      reg->Queue.push(std::make_unique<Event>(std::forward<Args>(args)...));
    }


    /**
     * \brief Post(Add) a new task to the task queue.
     * \tparam Task The type of the task to post.
     * \param task The task to post.
     */
    template<typename Task>
    void PostTask(Task&& task) {
      tasks.push(std::move(task));
    }

    /**
     * \brief Poll the event queue and call the listeners for the events in the queue.
     */
    void PollEvent() {
      for (auto& [_, ptr] : registry) {
        auto reg = ConvertToRegistry<char>(ptr);

        while (!reg->Queue.empty()) {
          for (auto& listener : reg->Listeners) {
            listener->Callback(*reg->Queue.front());
          }
          reg->Queue.pop();
        }
      }

      while (!tasks.empty()) {
        tasks.front()();
        tasks.pop();
      }
    }

  private:
    /**
     * \brief Convert a void pointer to an event registry pointer. This needs to be a separate function from the destructor because the destructor cannot be templated.
     * \tparam Event The type of the event to convert to.
     * \param ptr The void pointer to convert.
     * \return The event registry pointer.
     */
    template<typename Event>
    static EventRegistry<Event>* ConvertToRegistry(void* ptr) {
      return static_cast<EventRegistry<Event>*>(ptr);
    }


    /**
     * \brief Get the event registry for the specified event type. If the registry does not exist, create a new one.
     * \tparam Event The type of the event to get the registry for.
     * \return The event registry for the specified event type.
     */
    template<typename Event>
    EventRegistry<Event>* GetRegistry() {
      auto iterator = registry.find(TypeID<Event>());
      if (iterator != registry.end()) {
        return ConvertToRegistry<Event>(iterator->second);
      }
      // If the event registry does not exist, create a new one and store it in the registry.
      EventRegistry registry = new EventRegistry<Event>();
      registry[TypeID<Event>()] = registry;
      return registry;
    }

  private:
    // We use void* type to store the event data because we don't know the type of the event.
    // The uint32_t type is the unique identifier for the event.
    std::unordered_map<uint32_t, void*> registry;
    std::queue<std::function<void()>> tasks;
  };
}
