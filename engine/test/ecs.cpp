#include "../../engine/src/ecs/base/EntityManager.h"
#include "../../engine/src/ecs/base/Entity.h"

class TestComponent1 : public ECS::Component {
  //int A = 5;
};

class TestComponent2 : public ECS::Component {
  //int A = 5;  
};

class TestSystem1 : public ECS::System {
public:
  TestSystem1() {
    AddComponentSignature<TestComponent1>();
    AddComponentSignature<TestComponent1>();
  }
};

class TestSystem2 : public ECS::System {
public:
  TestSystem2() {
    AddComponentSignature<TestComponent2>();
  }
};

class TestSystem3 : public ECS::System {
public:
  TestSystem3() {
    AddComponentSignature<TestComponent1>();
    AddComponentSignature<TestComponent2>();
  }
};

void TestECS() {

  ECS::EntityManager manager;

  manager.RegisterSystem<TestSystem1>();
  manager.RegisterSystem<TestSystem2>();
  manager.RegisterSystem<TestSystem3>();

  auto entity1 = manager.CreateEntity();
  ECS::Entity ent(entity1, &manager);
  ent.AddComponent<TestComponent1>();

  auto entity2 = manager.CreateEntity();
  manager.AddComponent<TestComponent2>(entity2);

  auto entity3 = manager.CreateEntity();
  manager.AddComponent<TestComponent1>(entity3);
  manager.AddComponent<TestComponent2>(entity3);

  manager.Update();
}
