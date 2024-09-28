#include <iostream>
#include "Logger.hpp"

using namespace std;

Logger* Logger::LoggerInstance = nullptr;
mutex Logger::loggerMutex;
int Logger::ctr = 0;

Logger::Logger() {
    ctr++;   
    cout << "Number of Logger instance  created " << ctr << endl;
}

Logger* Logger::getLogger() {
    if (LoggerInstance == nullptr) {
        //lock_guard<mutex> lock(loggerMutex);
        loggerMutex.lock()
        if (LoggerInstance == nullptr) {
            LoggerInstance = new Logger();
        }
    }
    return LoggerInstance;
}

Logger::log(string message) {
    cout << message << endl;
}
