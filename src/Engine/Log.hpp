#pragma once

#include "raylib.h"
#include <cstdarg>
#include <cstdio>
#include <format>
#include <mutex>
#include <print>

namespace Engine {

class Log {
private:
  static std::mutex log_mutex;

public:
  Log() = delete;

  template <typename... Args>
  static void Trace(std::format_string<Args...> fmt, Args &&...args) {
    std::lock_guard<std::mutex> lock(log_mutex);
    std::println("[TRACE]: {}", std::format(fmt, std::forward<Args>(args)...));
  }

  template <typename... Args>
  static void Info(std::format_string<Args...> fmt, Args &&...args) {
    std::lock_guard<std::mutex> lock(log_mutex);
    std::println("[INFO]: {}", std::format(fmt, std::forward<Args>(args)...));
  }

  template <typename... Args>
  static void Debug(std::format_string<Args...> fmt, Args &&...args) {
    std::lock_guard<std::mutex> lock(log_mutex);
    std::println("[DEBUG]: {}", std::format(fmt, std::forward<Args>(args)...));
  }

  template <typename... Args>
  static void Warning(std::format_string<Args...> fmt, Args &&...args) {
    std::lock_guard<std::mutex> lock(log_mutex);
    std::println("[WARNING]: {}",
                 std::format(fmt, std::forward<Args>(args)...));
  }

  template <typename... Args>
  static void Error(std::format_string<Args...> fmt, Args &&...args) {
    std::lock_guard<std::mutex> lock(log_mutex);
    std::println(stderr, "[ERROR]: {}",
                 std::format(fmt, std::forward<Args>(args)...));
  }

  template <typename... Args>
  static void Fatal(std::format_string<Args...> fmt, Args &&...args) {
    std::lock_guard<std::mutex> lock(log_mutex);
    std::println(stderr, "[FATAL]: {}",
                 std::format(fmt, std::forward<Args>(args)...));
  }

  static void InitRaylibLogger() { SetTraceLogCallback(RaylibCallback); }

private:
  static void RaylibCallback(int logLevel, const char *text, va_list args) {
    char buffer[4096];
    vsnprintf(buffer, sizeof(buffer), text, args);

    switch (logLevel) {
    case LOG_INFO:
      Log::Info("{}", buffer);
      break;
    case LOG_WARNING:
      Log::Warning("{}", buffer);
      break;
    case LOG_ERROR:
      Log::Error("{}", buffer);
      break;
    case LOG_FATAL:
      Log::Fatal("{}", buffer);
      break;
    case LOG_DEBUG:
      Log::Debug("{}", buffer);
      break;
    case LOG_TRACE:
      Log::Trace("{}", buffer);
      break;
    default:
      break;
    }
  }
};

} // namespace Engine
