#include <base_log.h>

#ifdef BASE_LOG_USE_QT
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QThread>
#else
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#endif

void log_dispatch(const char* type, const char* tag, const std::string& message) {
#ifdef BASE_LOG_USE_QT
    // Use Qt logging system when available
    QString qtMessage = QString::fromStdString(message);
    QString qtTag = QString::fromStdString(tag);
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
    
    // Format: [timestamp] [type] [tag]: message
    QString formattedMessage = QString("[%1] [%2] [%3] [%4]: %5")
        .arg(timestamp)
        // Print thread ID as hex
        .arg(QString::number(reinterpret_cast<quintptr>(QThread::currentThreadId()), 16))
        .arg(type)
        .arg(qtTag, qtMessage);
    
    // Route to appropriate Qt logging function based on type
    switch(type[0]) {
        case 'T': // Trace -> Debug
        case 'D': // Debug
            qDebug().noquote() << formattedMessage;
            break;
        case 'I': // Info
            qInfo().noquote() << formattedMessage;
            break;
        case 'W': // Warning
            qWarning().noquote() << formattedMessage;
            break;
        case 'E': // Error
        case 'C': // Critical
            qCritical().noquote() << formattedMessage;
            break;
        default:
            qDebug().noquote() << formattedMessage;
            break;
    }
#else
    // Fallback to standard iostream logging
    auto t = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t.time_since_epoch()) % 1000;

    std::time_t tt = std::chrono::system_clock::to_time_t(t);
    std::tm tm = *std::localtime(&tt);

    std::cout << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << ":"
              << std::setfill('0') << std::setw(3) << ms.count() << "] "
              << "[" << type << "] [" << tag << "]: " << message << std::endl;
#endif
}
