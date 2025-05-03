#include <cstdlib>

#include "engine/src/application/Application.h"
#include "engine/src/application/Interface.h"

class Editor : public HeimskrEngine::AppInterface {
public:
  Editor() {
    // AttachLayer<EditorLayer>();
  }

  ~Editor() override = default;

  void OnStart() override {
    // Initialize the editor layer
  }

  void OnUpdate() override {
    // Update the editor layer
  }
};

int main() {
  auto application = new HeimskrEngine::Application();
  application->AttachLayer<Editor>();
  application->RunContext();
  return EXIT_SUCCESS;
}
