#include <cstdlib>

//#include "engine/src/HeimskrEngine.h"
//#include "logging/Logger.h"
#include <iostream>
#include <ostream>

#include "engine/src/common/Core.h"
#include "engine/src/common/Types.h"
//#include "engine/src/core/Engine.h"
//#include "engine/src/common/Core.h"
#include "engine/src/application/Application.h"
#include "engine/src/application/Interface.h"
#include "engine/src/ecs/base/ECSTypes.h"

//#include "../../engine/src/common/Types.h"
//#include "../../engine/src/common/Core.h"
//#include "../../engine/src/ecs/base/ECSTypes.h"

//#include "../../engine/src/HeimskrEngine.h"
//#include "../../engine/src/logging/Logger.h"

class TestEvent {
public:
  int32_t deta = 69;
};

class TestLayer : public HeimskrEngine::AppInterface {
private:
  int32_t count = 0;
public:
  void OnUpdate() override {
    //HEIMSKR_INFO("OnUpdate() called");
    //if (count++ == 10) {
    //  PostEvent<TestEvent>();
    //}
  }

  void OnStart() override {
    //AttachCallback<TestEvent>([this] (auto e) {
    //  HEIMSKR_TRACE(fmt::format("TestEvent: {}", e.deta));
    //  DetachLayer<TestLayer>();
    //});
    AttachCallback<HeimskrEngine::MouseMotionEvent>([this](auto e) {
      HEIMSKR_TRACE(fmt::format("Mouse x: {}, y: {}", e.TargetX, e.TargetY));
    });
  }
};

void test() {
  for (int i = 0; i < 10000; i++) {
    std::cout << "Hello World!" << std::endl;
  }
}

int main() {
  //test();
  //uint32_t test = HeimskrEngine::TypeID<int>();
  //std::cout << test << std::endl;

  //ECS::ComponentTypeID id = ECS::GetNextComponentTypeID();
  //std::cout << id << std::endl;

  //int asd = HeimskrEngine::ENGINE_WINDOW_HEIGHT;
  //auto atest = HeimskrEngine::Engine::GetInstance().IsRunning();
  //auto teatae = HeimskrEngine::Core.IsRunning();
  HeimskrEngine::Application* application = new HeimskrEngine::Application();

  application->AttachCallback<HeimskrEngine::KeyPressEvent>([](auto e) {
    HEIMSKR_TRACE(fmt::format("Key pressed: {}", e.Key));
  });

  application->AttachCallback<HeimskrEngine::KeyRepeatEvent>([](auto e) {
    HEIMSKR_TRACE(fmt::format("Key repeated: {}", e.Key));
  });

  application->AttachCallback<HeimskrEngine::KeyReleaseEvent>([](auto e) {
    HEIMSKR_TRACE(fmt::format("Key released: {}", e.Key));
  });

  application->AttachCallback<HeimskrEngine::WindowResizeEvent>([](auto e) {
    HEIMSKR_TRACE(fmt::format("Window resized to x: {}, y: {}", e.Width, e.Height));
  });

  application->AttachCallback<HeimskrEngine::MouseWheelEvent>([](auto e) {
    HEIMSKR_TRACE(fmt::format("Scrolled to x: {}, y: {}", e.ScrollX, e.ScrollY));
  }); 

  application->AttachCallback<HeimskrEngine::MouseDownEvent>([](auto e) {
    HEIMSKR_TRACE(fmt::format("Pressed mouse button: {}", e.Button));
  });

  application->AttachCallback<HeimskrEngine::MouseReleaseEvent>([](auto e) {
    HEIMSKR_TRACE(fmt::format("Released mouse button: {}", e.Button));
  });

  application->AttachCallback<HeimskrEngine::MouseDragEvent>([](auto e) {
    HEIMSKR_TRACE(fmt::format("Mouse dragged with deltaX: {}, deltaY: {}", e.DeltaX, e.DeltaY));
  });

  application->AttachLayer<TestLayer>();
  application->RunContext();

  //application->AttachLayer<TestLayer>();
  //auto testar = application->GetLayer<TestLayer>();
  //application->RunContext();
  return EXIT_SUCCESS;
}
