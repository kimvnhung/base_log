#pragma once

#include <string>
#include <fmt/core.h>
#include <utility>


#ifndef LOG_TAG
#define LOG_TAG "BASE_LOG"
#endif

#ifndef PROJECT_SOURCE_DIR
#define PROJECT_SOURCE_DIR ""
#endif

#define FILE_PATH_REMOVE_PREFIX(path, prefix) \
    (std::strncmp(path, prefix, sizeof(prefix) - 1) == 0 \
        ? (path + sizeof(prefix) - 1) \
        : path)

#define FILE_NAME FILE_PATH_REMOVE_PREFIX(__FILE__, PROJECT_SOURCE_DIR)

#define FUNCTION_NAME fmt::format("{} {} {}", LOG_TAG, FILE_NAME,__LINE__).c_str()

#define TRACE(...)          log_message("T",FUNCTION_NAME, "{}", __VA_ARGS__)
#define TRACEF(format,...)  log_message("T",FUNCTION_NAME,format, __VA_ARGS__)

#define DEBUG(...)          log_message("D",FUNCTION_NAME, "{}", __VA_ARGS__)
#define DEBUGF(format,...)  log_message("D",FUNCTION_NAME,format, __VA_ARGS__)

#define INFO(...)          log_message("I",FUNCTION_NAME, "{}", __VA_ARGS__)
#define INFOF(format,...)  log_message("I",FUNCTION_NAME,format, __VA_ARGS__)

#define WARN(...)          log_message("W",FUNCTION_NAME, "{}", __VA_ARGS__)
#define WARNF(format,...)  log_message("W",FUNCTION_NAME,format, __VA_ARGS__)

#define ERROR(...)          log_message("E",FUNCTION_NAME, "{}", __VA_ARGS__)
#define ERRORF(format,...)  log_message("E",FUNCTION_NAME,format, __VA_ARGS__)

#define CRITICAL(...)          log_message("C",FUNCTION_NAME, "{}", __VA_ARGS__)
#define CRITICALF(format,...)  log_message("C",FUNCTION_NAME,format, __VA_ARGS__)


/// Only forward declaration of dispatcher (defined in .cpp)
void log_dispatch(const char* type, const char* tag, const std::string& message);

template<typename... Args>
void log_message(const char* type, const char* tag, const char* format, Args&&... args) {
    std::string formatted = fmt::format(format, std::forward<Args>(args)...);
    log_dispatch(type,tag,formatted);
}

#define LOGT(...)           TRACE(__VA_ARGS__)
#define LOGTF(...)          TRACEF(__VA_ARGS__)

#define LOGD(...)           DEBUG(__VA_ARGS__)
#define LOGDF(...)          DEBUGF(__VA_ARGS__)

#define LOGI(...)           INFO(__VA_ARGS__)
#define LOGIF(...)          INFOF(__VA_ARGS__)

#define LOGW(...)           WARN(__VA_ARGS__)
#define LOGWF(...)          WARNF(__VA_ARGS__)

#define LOGE(...)           ERROR(__VA_ARGS__)
#define LOGEF(...)          ERRORF(__VA_ARGS__)

#define LOGC(...)           CRITICAL(__VA_ARGS__)
#define LOGCF(...)          CRITICALF(__VA_ARGS__)
