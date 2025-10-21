#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <mutex>
#include <fstream>

using namespace std;

class Logger {
private:
    string filename;
    ofstream fileStream;
    bool consoleOutput;
    bool autoFlush;
    mutable mutex mtx;

    void openStream(bool append);

public:
    // Constructor: filename (default "app.log"), append (default true), consoleOutput (default true), autoFlush (default true)
    Logger(const string& filename = "app.log", bool append = true, bool consoleOutput = true, bool autoFlush = true);
    ~Logger();

    // Logging methods
    void logInfo(const string& message);
    void logWarning(const string& message);
    void logError(const string& message);
    void log(const string& level, const string& message);

    // Flush / save
    void save();

    // Configuration
    void setFilename(const string& fname, bool append = true);
    void setConsoleOutput(bool enabled);
    void setAutoFlush(bool enabled);
};

#endif

// Global logger instance pointer (set in main)
extern Logger* g_logger;