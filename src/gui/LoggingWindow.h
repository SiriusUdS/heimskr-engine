#ifndef LOGGINGWINDOW_H
#define LOGGINGWINDOW_H

#include <imgui.h>

class LoggingWindow {
public:
    explicit LoggingWindow();
    void draw();
    void clear();
    void addLog(const char *str, const char *strEnd);
private:
    ImGuiTextBuffer _buf;
    ImGuiTextFilter _filter;
    ImVector<int> _lineOffsets;
    bool _autoScroll;
};

#endif //LOGGINGWINDOW_H
