#include <iostream>
#include "Logger.hpp"
#include <thread>
using namespace std;

void user1Logs() {
    Logger* logger = Logger::getLogger();
    logger->log("Hello, world! user1");
}

void user2Logs() {
    Logger* logger = Logger::getLogger();
    logger->log("Hello, world! user2");
}

main() {

    thread t1(user1Logs);
    thread t2(user2Logs);

    t1.join();
    t2.join();

    return 0;
}