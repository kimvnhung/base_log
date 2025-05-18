#include <base_log.h>

#include <cstring>
#include <iostream>

void log_dispatch(const char* type,const char* tag, const std::string& message) {
    std::cout << "[" << type << "] [" << tag << "] " << message << std::endl;
}
