#include <base_log.h>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

void log_dispatch(const char* type, const char* tag, const std::string& message) {
    auto t = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch()) % 1000;

    std::time_t tt = std::chrono::system_clock::to_time_t(t);
    std::tm tm = *std::localtime(&tt);

    std::cout << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << ":"
              << std::setfill('0') << std::setw(3) << ms.count() << "] "
              << "[" << type << "] [" << tag << "]: " << message << std::endl;
}
