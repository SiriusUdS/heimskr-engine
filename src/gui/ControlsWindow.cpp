#include "ControlsWindow.h"

#include <imgui.h>

void ControlsWindow::draw() {
    ImGui::Begin("Controls");
    ImGui::Button("Launch la fusée");
    ImGui::End();
}
