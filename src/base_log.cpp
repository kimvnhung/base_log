#include <base_log.h>

#include <spdlog/spdlog.h>
#include <cstring>

void log_dispatch(const char* type,const char* tag, const std::string& message) {
    // Log the message using spdlog
    std::string formatted_message = std::string("[") + tag + "] " + message;
    if (strcmp(type, "TRACE") == 0) {
        spdlog::trace("{}", formatted_message);
    } else if (strcmp(type, "DEBUG") == 0) {
        spdlog::debug("{}", formatted_message);
    } else if (strcmp(type, "INFO") == 0) {
        spdlog::info("{}", formatted_message);
    } else if (strcmp(type, "WARN") == 0) {
        spdlog::warn("{}", formatted_message);
    } else if (strcmp(type, "ERROR") == 0) {
        spdlog::error("{}", formatted_message);
    } else if (strcmp(type, "CRITICAL") == 0) {
        spdlog::critical("{}", formatted_message);
    }
}
