#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "logger.h"

using namespace std;

// Global logger pointer definition
Logger* g_logger = nullptr;

static string currentTimestamp() {
    using namespace chrono;
    auto now = system_clock::now();
    time_t t = system_clock::to_time_t(now);
    tm tm{};
#if defined(_WIN32) || defined(_WIN64)
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif
    char buf[64];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tm);
    return string(buf);
}

void Logger::openStream(bool append) {
    if (fileStream.is_open()) fileStream.close();
    ios_base::openmode mode = ios::out;
    mode |= (append ? ios::app : ios::trunc);
    fileStream.open(filename, mode);
}

Logger::Logger(const string& filename, bool append, bool consoleOutput, bool autoFlush)
    : filename(filename), consoleOutput(consoleOutput), autoFlush(autoFlush) {
    openStream(append);
}

Logger::~Logger() {
    lock_guard<mutex> lock(mtx);
    if (fileStream.is_open()) fileStream.close();
}

void Logger::log(const string& level, const string& message) {
    lock_guard<mutex> lock(mtx);
    string entry = "[" + currentTimestamp() + "] [" + level + "] " + message;
    if (fileStream.is_open()) {
        fileStream << entry << "\n";
        if (autoFlush) fileStream.flush();
    }
    if (consoleOutput) {
        cout << entry << "\n";
    }
}

void Logger::logInfo(const string& message) {
    log("INFO", message);
}

void Logger::logWarning(const string& message) {
    log("WARN", message);
}

void Logger::logError(const string& message) {
    log("ERROR", message);
}

void Logger::save() {
    lock_guard<mutex> lock(mtx);
    if (fileStream.is_open()) fileStream.flush();
}

void Logger::setFilename(const string& fname, bool append) {
    lock_guard<mutex> lock(mtx);
    filename = fname;
    openStream(append);
}

void Logger::setConsoleOutput(bool enabled) {
    lock_guard<mutex> lock(mtx);
    consoleOutput = enabled;
}

void Logger::setAutoFlush(bool enabled) {
    lock_guard<mutex> lock(mtx);
    autoFlush = enabled;
}