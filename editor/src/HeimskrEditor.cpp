#include <cstdlib>

//#include "engine/src/HeimskrEngine.h"
//#include "logging/Logger.h"
#include <iostream>
#include <ostream>

#include "engine/src/common/Core.h"
#include "engine/src/common/Types.h"
//#include "engine/src/core/Engine.h"
//#include "engine/src/common/Core.h"
#include "engine/src/ecs/base/ECSTypes.h"

//#include "../../engine/src/common/Types.h"
//#include "../../engine/src/common/Core.h"
//#include "../../engine/src/ecs/base/ECSTypes.h"

//#include "../../engine/src/HeimskrEngine.h"
//#include "../../engine/src/logging/Logger.h"


//class TestLayer : public HeimskrEngine::AppInterface {
//public:
//  void OnUpdate() override {
//    //HEIMSKR_INFO("OnUpdate() called");
//  }
//
//  void OnStart() override {
//    //HEIMSKR_TRACE("OnStart() called");
//  }
//};

void test() {
  for (int i = 0; i < 10000; i++) {
    std::cout << "Hello World!" << std::endl;
  }
}

int main() {
  //test();
  uint32_t test = HeimskrEngine::TypeID<int>();
  std::cout << test << std::endl;

  ECS::ComponentTypeID id = ECS::GetNextComponentTypeID();
  std::cout << id << std::endl;

  //int asd = HeimskrEngine::ENGINE_WINDOW_HEIGHT;
  auto atest = HeimskrEngine::Engine::GetInstance().IsRunning();
  return EXIT_SUCCESS;
}
