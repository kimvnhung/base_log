#pragma once

#include <string>
#include <fmt/core.h>
#include <utility>


#ifndef LOG_TAG
#define LOG_TAG "BASE_LOG"
#endif

#define FUNCTION_NAME fmt::format("{} {}", LOG_TAG, __func__).c_str()

#define TRACE(...)          log_message("TRACE",FUNCTION_NAME, "{}", __VA_ARGS__)
#define TRACEF(format,...)  log_message("TRACE",FUNCTION_NAME,format, __VA_ARGS__)

#define DEBUG(...)          log_message("DEBUG",FUNCTION_NAME, "{}", __VA_ARGS__)
#define DEBUGF(format,...)  log_message("DEBUG",FUNCTION_NAME,format, __VA_ARGS__)

#define INFO(...)          log_message("INFO",LOG_TAG, "{}", __VA_ARGS__)
#define INFOF(format,...)  log_message("INFO",LOG_TAG,format, __VA_ARGS__)

#define WARN(...)          log_message("WARN",LOG_TAG, "{}", __VA_ARGS__)
#define WARNF(format,...)  log_message("WARN",LOG_TAG,format, __VA_ARGS__)

#define ERROR(...)          log_message("ERROR",LOG_TAG, "{}", __VA_ARGS__)
#define ERRORF(format,...)  log_message("ERROR",LOG_TAG,format, __VA_ARGS__)

#define CRITICAL(...)          log_message("CRITICAL",LOG_TAG, "{}", __VA_ARGS__)
#define CRITICALF(format,...)  log_message("CRITICAL",LOG_TAG,format, __VA_ARGS__)


/// Only forward declaration of dispatcher (defined in .cpp)
void log_dispatch(const char* type, const char* tag, const std::string& message);

template<typename... Args>
void log_message(const char* type, const char* tag, const char* format, Args&&... args) {
    std::string formatted = fmt::format(format, std::forward<Args>(args)...);
    log_dispatch(type,tag,formatted);
}

