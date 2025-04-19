#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

#include <entt/entt.hpp>
#include "logging/Logger.h"

#include "logging/Logging.h"
#include "../../editor/src/gui/ImGuiManager.h"

#include "common/Core.h"
#include "ecs/base/Entity.h"
#include "ecs/base/EntityManager.h"

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

int main() {

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

  HEIMSKR_DEBUG("HELLO THIS DEBUG TEST MON");
  HEIMSKR_TRACE("HELLO THIS TRACE TEST MON");
  HEIMSKR_INFO("HELLO THIS INFO TEST MON");
  HEIMSKR_WARN("HELLO THIS WARN TEST MON");
  HEIMSKR_ERROR("HELLO THIS ERROR TEST MON");
  HEIMSKR_CRITICAL("HELLO THIS CRITICAL TEST MON");

  //HeimskrEngine::Engine::GetInstance().Initialize();
  HeimskrEngine::Core.Initialize();
  HeimskrEngine::Timer.Initialize();
  HeimskrEngine::Events.Initialize();

  //while (HeimskrEngine::Engine::GetInstance().IsRunning()) {
  while (HeimskrEngine::Core.IsRunning()) {
    HeimskrEngine::Timer.Update();
    HeimskrEngine::Events.Update();
    HeimskrEngine::Core.Update();
    //HeimskrEngine::Engine::GetInstance().Update();
  }

  return EXIT_SUCCESS;

  //HeimskrEngine::Core.Run();
	//Logging::initSpdLog();

	//glfwInit();
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
 //   glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

	//GLFWwindow* window = glfwCreateWindow(2560, 1440, "Heimskr Engine", nullptr, nullptr);
	//if (window == nullptr)
	//{
	//	GCS_LOG_ERROR("Failed to create GLFW window");
	//	glfwTerminate();
	//	return -1;
	//}
	//glfwMakeContextCurrent(window);

	//gladLoadGL();
	//glViewport(0, 0, 800, 800);

	//ImGuiManager::init(window);

	//GCS_LOG_TRACE("Starting program");

	//while (!glfwWindowShouldClose(window))
	//{
	//	glClearColor(0, 0, 0.1f, 1.0f);
	//	glClear(GL_COLOR_BUFFER_BIT);

	//	ImGuiManager::render();

	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}

	//ImGuiManager::shutdown();

	//glfwDestroyWindow(window);
	//glfwTerminate();

	//GCS_LOG_TRACE("Terminating program");
}
