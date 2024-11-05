#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H

#include <GLFW/glfw3.h>
#include <memory>

#include "ControlsWindow.h"
#include "LoggingWindow.h"

namespace ImGuiManager {
    void init(GLFWwindow* window);
    void render();
    void shutdown();

    extern std::unique_ptr<ControlsWindow> controlsWindow;
    extern std::unique_ptr<LoggingWindow> loggingWindow;
}

#endif //IMGUIMANAGER_H
