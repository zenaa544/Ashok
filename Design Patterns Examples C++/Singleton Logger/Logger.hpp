#ifndef logger_h
#define logger_h

#include <string>
#include <mutex>
using namespace std;

class Logger {
    Logger();//private constructor for singleton
    static Logger* LoggerInstance;
    static mutex loggerMutex;
    static int ctr;
    Logger * Logger(const Logger&); //private copy constructor
    Logger& operator=(const Logger&); //private assignment operator
 public:
    static Logger* getLogger();
    void log(string message);
};   

#endif
