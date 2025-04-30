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
    HEIMSKR_INFO("OnUpdate() called");
    if (count++ == 10) {
      PostEvent<TestEvent>();
    }
  }

  void OnStart() override {
    AttachCallback<TestEvent>([this] (auto e) {
      HEIMSKR_TRACE(fmt::format("TestEvent: {}", e.deta));
      DetachLayer<TestLayer>();
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
  application->AttachLayer<TestLayer>();
  auto testar = application->GetLayer<TestLayer>();
  //application->DetachLayer<TestLayer>();
  application->RunContext();
  //test();
  return EXIT_SUCCESS;
}
