/**
 * @file Logger.h
 * @brief Logging macros and class for easier logging with spdlog.
 */

#pragma once

#include <memory>
#include <spdlog/sinks/stdout_color_sinks-inl.h>
#include <spdlog/spdlog.h>

// For enabling/disabling logging, define HEIMSKR_ENGINE_ENABLE_LOGGING in Project settings -> C/C++ -> Preprocessor -> Preprocessor definitions.
#ifdef HEIMSKR_ENGINE_ENABLE_LOGGING
  namespace HeimskrEngine {
    class Logger {
    public:
      Logger() {
        spdLogger = spdlog::stdout_color_mt("HeimskrEngine");
        spdlog::set_level(spdlog::level::trace);
        spdlog::set_pattern("%^[%T]: [#%t] %v%$");
      }
  
      static std::shared_ptr<spdlog::logger>& GetInstance() {
        static Logger instance;
        return instance.spdLogger;
      }
  
    private:
      std::shared_ptr<spdlog::logger> spdLogger;
    };

    /**
     * \brief Convert a spdlog log level (enum value) to a string for display purposes
     * \param level The severity of the log message
     * \return The string representation of the log level
     */
    inline const char* SpdlogLevelToString(spdlog::level::level_enum level) {
      switch (level) {
      case spdlog::level::trace:
        return "TRACE";
      case spdlog::level::debug:
        return "DEBUG";
      case spdlog::level::info:
        return "INFO";
      case spdlog::level::warn:
        return "WARN";
      case spdlog::level::err:
        return "ERROR";
      case spdlog::level::critical:
        return "CRITICAL";
      case spdlog::level::off:
        return "OFF";
      case spdlog::level::n_levels:
      default:
        return "";
      }
    }

  }

  #define HEIMSKR_LOG(level, ...) ::HeimskrEngine::Logger::GetInstance()->log(level, "[{}] {}", ::HeimskrEngine::SpdlogLevelToString(level), __VA_ARGS__)

  #define HEIMSKR_TRACE(...) HEIMSKR_LOG(spdlog::level::trace, __VA_ARGS__)
  #define HEIMSKR_DEBUG(...) HEIMSKR_LOG(spdlog::level::debug, __VA_ARGS__)
  #define HEIMSKR_INFO(...) HEIMSKR_LOG(spdlog::level::info, __VA_ARGS__)
  #define HEIMSKR_WARN(...) HEIMSKR_LOG(spdlog::level::warn, __VA_ARGS__)
  #define HEIMSKR_ERROR(...) HEIMSKR_LOG(spdlog::level::err, __VA_ARGS__)
  #define HEIMSKR_CRITICAL(...) HEIMSKR_LOG(spdlog::level::critical, __VA_ARGS__)

#else
  #define HEIMSKR_TRACE
  #define HEIMSKR_DEBUG
  #define HEIMSKE_INFO
  #define HEIMSKR_WARN
  #define HEIMSKR_ERROR
  #define HEIMSKR_CRITICAL
#endif
