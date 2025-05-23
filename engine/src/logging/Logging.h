#ifndef LOGGING_H
#define LOGGING_H

#include <spdlog/spdlog.h>

#include "../../editor/src/gui/LoggingWindow.h"

namespace Logging {
    void initSpdLog();
    void updateSpdLog();
    void linkLoggingWindow(LoggingWindow *loggingWindow);

    extern std::vector<spdlog::sink_ptr> _sinks;
}

#define HEIMSKR_LOG_DEBUG(msg) spdlog::debug(msg)
#define HEIMSKR_LOG_ERROR(msg) spdlog::error(msg)
#define HEIMSKR_LOG_INFO(msg) spdlog::info(msg)
#define HEIMSKR_LOG_TRACE(msg) spdlog::trace(msg)
#define HEIMSKR_LOG_WARN(msg) spdlog::warn(msg)

#endif //LOGGING_H
