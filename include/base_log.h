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

constexpr const char* file_path_remove_prefix(const char* path, const char* prefix) {
    const char* p = path;
    const char* pr = prefix;
    while (*pr && *p == *pr) {
        ++p;
        ++pr;
    }
    return (*pr == '\0') ? p : path;
}

#define FILE_NAME file_path_remove_prefix(__FILE__, PROJECT_SOURCE_DIR)

inline std::string make_function_tag(const char* tag, const char* file, int line) {
    return fmt::format("{} {} {}", tag, file, line);
}

#define TRACE(...)          do { auto __tag = make_function_tag(LOG_TAG, FILE_NAME, __LINE__); log_message("T", __tag.c_str(), "{}", __VA_ARGS__); } while(0)
#define TRACEF(format,...)  do { auto __tag = make_function_tag(LOG_TAG, FILE_NAME, __LINE__); log_message("T", __tag.c_str(), format, __VA_ARGS__); } while(0)

#define DEBUG(...)          do { auto __tag = make_function_tag(LOG_TAG, FILE_NAME, __LINE__); log_message("D", __tag.c_str(), "{}", __VA_ARGS__); } while(0)
#define DEBUGF(format,...)  do { auto __tag = make_function_tag(LOG_TAG, FILE_NAME, __LINE__); log_message("D", __tag.c_str(), format, __VA_ARGS__); } while(0)

#define INFO(...)          do { auto __tag = make_function_tag(LOG_TAG, FILE_NAME, __LINE__); log_message("I", __tag.c_str(), "{}", __VA_ARGS__); } while(0)
#define INFOF(format,...)  do { auto __tag = make_function_tag(LOG_TAG, FILE_NAME, __LINE__); log_message("I", __tag.c_str(), format, __VA_ARGS__); } while(0)

#define WARN(...)          do { auto __tag = make_function_tag(LOG_TAG, FILE_NAME, __LINE__); log_message("W", __tag.c_str(), "{}", __VA_ARGS__); } while(0)
#define WARNF(format,...)  do { auto __tag = make_function_tag(LOG_TAG, FILE_NAME, __LINE__); log_message("W", __tag.c_str(), format, __VA_ARGS__); } while(0)

#define ERROR(...)          do { auto __tag = make_function_tag(LOG_TAG, FILE_NAME, __LINE__); log_message("E", __tag.c_str(), "{}", __VA_ARGS__); } while(0)
#define ERRORF(format,...)  do { auto __tag = make_function_tag(LOG_TAG, FILE_NAME, __LINE__); log_message("E", __tag.c_str(), format, __VA_ARGS__); } while(0)

#define CRITICAL(...)          do { auto __tag = make_function_tag(LOG_TAG, FILE_NAME, __LINE__); log_message("C", __tag.c_str(), "{}", __VA_ARGS__); } while(0)
#define CRITICALF(format,...)  do { auto __tag = make_function_tag(LOG_TAG, FILE_NAME, __LINE__); log_message("C", __tag.c_str(), format, __VA_ARGS__); } while(0)


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
