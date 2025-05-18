#include <gtest/gtest.h>

#include <base_log.h>

TEST(TestLog, BasicAssertion) {
    // Test log message
    TRACE("This is a trace message");
    DEBUG("This is a debug message");
    INFO("This is an info message");
    WARN("This is a warning message");
    ERROR("This is an error message");
    CRITICAL("This is a critical message");

    // Test formatted log message
    TRACEF("Formatted trace message: {}", 42);
    DEBUGF("Formatted debug message: {}", 3.14);
    INFOF("Formatted info message: {}", "Hello, World!");
    WARNF("Formatted warning message: {}", "Warning!");
    ERRORF("Formatted error message: {}", "Error!");
    CRITICALF("Formatted critical message: {}", "Critical error!");

    // Test log with different tags
    TRACEF("This is a trace message with tag {} {}", "TAG1",11);
    DEBUGF("This is a debug message with tag {} {}", "TAG2",22);
    INFOF("This is an info message with tag {} {}", "TAG3",33);
    WARNF("This is a warning message with tag {} {}", "TAG4",44);
    ERRORF("This is an error message with tag {} {}", "TAG5",55);
    CRITICALF("This is a critical message with tag {} {}", "TAG6",66);
}
