# base_log

A flexible C++ logging library with automatic Qt Core integration.

## Features

- 🎯 **Smart Qt Detection**: Automatically uses Qt logging (qDebug, qInfo, qWarning, qCritical) when Qt6 Core is available
- 📝 **Format String Support**: Uses {fmt} library for powerful string formatting
- 🔄 **Fallback Support**: Falls back to standard iostream when Qt is not available
- 🏷️ **Tagged Logging**: Automatic tagging with file location and line numbers
- ⚡ **Zero Configuration**: Works out of the box with or without Qt

## Logging Levels

The library provides multiple logging levels with corresponding macros:

| Level    | Macro      | Formatted Macro | Qt Function  | Use Case |
|----------|------------|-----------------|--------------|----------|
| Trace    | `TRACE()`  | `TRACEF()`      | `qDebug()`   | Detailed diagnostic information |
| Debug    | `DEBUG()`  | `DEBUGF()`      | `qDebug()`   | Debug-level messages |
| Info     | `INFO()`   | `INFOF()`       | `qInfo()`    | Informational messages |
| Warning  | `WARN()`   | `WARNF()`       | `qWarning()` | Warning messages |
| Error    | `ERROR()`  | `ERRORF()`      | `qCritical()`| Error messages |
| Critical | `CRITICAL()`| `CRITICALF()` | `qCritical()`| Critical errors |

## Usage

### Basic Logging

```cpp
#include <base_log.h>

// Simple logging
DEBUG("Application started");
INFO("Processing data");
WARN("Low memory warning");
ERROR("Failed to open file");

// Formatted logging (using fmt syntax)
DEBUGF("User {} logged in", username);
INFOF("Processing item {} of {}", current, total);
WARNF("Temperature: {}°C (threshold: {}°C)", temp, threshold);
ERRORF("Connection failed after {} attempts", retries);
```

### Custom Log Tags

By default, the log tag is set to the project name. You can customize it:

```cmake
# In your CMakeLists.txt
target_compile_definitions(your_target
    PRIVATE
        LOG_TAG="MyModule"
)
```

### Short Aliases

For convenience, shorter macro names are also available:

```cpp
LOGD("Debug message");        // Same as DEBUG()
LOGI("Info message");          // Same as INFO()
LOGW("Warning message");       // Same as WARN()
LOGE("Error message");         // Same as ERROR()
LOGC("Critical message");      // Same as CRITICAL()

// With formatting
LOGDF("Value: {}", value);     // Same as DEBUGF()
LOGIF("Count: {}", count);     // Same as INFOF()
```

## CMake Integration

### Standalone Usage (without Qt)

```cmake
add_subdirectory(thirdparty/base_log)

target_link_libraries(your_target
    PRIVATE
        base_log
)
```

Output format (iostream):
```
[2025-11-18 15:36:32.918] [D] [MyApp src/main.cpp 42]: Debug message
```

### With Qt Core (Automatic)

```cmake
# Qt will be automatically detected if available
find_package(Qt6 COMPONENTS Core)

add_subdirectory(thirdparty/base_log)

target_link_libraries(your_target
    PRIVATE
        base_log
        Qt6::Core  # If linking Qt
)
```

Output format (Qt logging):
```
[2025-11-18 15:36:32.918] [D] [MyApp src/main.cpp 42]: Debug message
```

When Qt6 Core is detected, base_log will:
- ✅ Automatically route logs through Qt's logging system
- ✅ Use `qDebug()`, `qInfo()`, `qWarning()`, `qCritical()`
- ✅ Support Qt's logging configuration and filtering
- ✅ Integrate with Qt Creator's Application Output
- ✅ Work with Qt's logging categories and context

## Build Options

### BASE_LOG_SHARED

Controls whether base_log is built as a shared or static library:

```cmake
option(BASE_LOG_SHARED "Build base_log as shared lib" ON)
```

## How It Works

### Qt Detection

The library automatically detects Qt6 Core during CMake configuration:

```cmake
find_package(Qt6 QUIET COMPONENTS Core)
if(Qt6_FOUND AND TARGET Qt6::Core)
    target_compile_definitions(base_log PUBLIC BASE_LOG_USE_QT)
    target_link_libraries(base_log PUBLIC Qt6::Core)
endif()
```

### Log Routing

When `BASE_LOG_USE_QT` is defined, logs are routed as follows:

- **TRACE/DEBUG** → `qDebug()`
- **INFO** → `qInfo()`
- **WARN** → `qWarning()`
- **ERROR/CRITICAL** → `qCritical()`

When Qt is not available, logs are output to `std::cout` with timestamps.

## Examples

### Example 1: Simple Application

```cpp
#include <base_log.h>

int main() {
    INFO("Application starting...");
    
    int result = processData();
    if (result < 0) {
        ERRORF("Processing failed with code: {}", result);
        return 1;
    }
    
    INFOF("Processing completed successfully: {} items", result);
    return 0;
}
```

### Example 2: Class with Logging

```cpp
#include <base_log.h>

class DataProcessor {
public:
    void process(const std::string& filename) {
        DEBUGF("Opening file: {}", filename);
        
        if (!openFile(filename)) {
            ERRORF("Failed to open file: {}", filename);
            return;
        }
        
        INFOF("Processing file: {}", filename);
        // ... processing logic
        
        DEBUG("File processed successfully");
    }
};
```

### Example 3: Qt Application Integration

```cpp
#include <QCoreApplication>
#include <base_log.h>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    
    // Logs will automatically use Qt's logging system
    INFO("Qt application started");
    DEBUGF("Qt version: {}", qVersion());
    
    // Qt logging categories will work
    qSetMessagePattern("[%{time yyyy-MM-dd hh:mm:ss.zzz}] %{message}");
    
    WARN("This will respect Qt's message pattern");
    
    return app.exec();
}
```

## Requirements

- **C++11** or later
- **CMake 3.10** or later
- **{fmt} library** (automatically fetched via FetchContent)
- **Qt6 Core** (optional, auto-detected)

## License

[Your license here]
