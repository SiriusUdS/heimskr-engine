#include "ImGuiTextBufferSink.h"

void ImGuiTextBufferSink::sink_it_(const spdlog::details::log_msg &msg) {
    spdlog::memory_buf_t formatted;
    formatter_->format(msg, formatted);
    _loggingWindow->addLog(formatted.data(), formatted.data() + formatted.size());
}

void ImGuiTextBufferSink::flush_() {
    // ImGuiTextBuffer directly appends data to an internal buffer and does not need a flush function
};
