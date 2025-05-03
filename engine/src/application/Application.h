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

      AttachCallback<WindowResizeEvent>([this](auto e) {
        context->Renderer->Resize(e.Width, e.Height);
      });
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
    void RunContext() {
      auto camera = CreateEntity<Entity>();
      camera.Attach<CameraComponent>();
      camera.Attach<TransformComponent>().Transform.Translation.z = 2.0f;

      auto quad = CreateEntity<Entity>();
      quad.Attach<TransformComponent>();
      quad.Attach<MeshComponent>().Mesh = CreateQuad3D();

      while (context->Window->PollEvents()) {

        context->Renderer->BeginFrame();
        //context->Renderer->Resize(100, 100);

        // Setting the camera shader
        EntityView<Entity, CameraComponent>([this](auto entity, auto& component) {
          auto& transform = entity.template Get<TransformComponent>().Transform;
          context->Renderer->SetCamera(component.Camera, transform);
        });

        // Settings the mesh shader
        EntityView<Entity, MeshComponent>([this](auto entity, auto& component) {
          auto& transform = entity.template Get<TransformComponent>().Transform;
          context->Renderer->Draw(component.Mesh, transform);
        });

        context->Renderer->EndFrame();

        for (const auto& layer : context->Layers) {
          layer->OnUpdate();
        }

        context->Renderer->ShowFrame();
      }
    }
  };
}
