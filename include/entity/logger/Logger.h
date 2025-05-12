#ifndef LOGGER_H
#define LOGGER_H

#include <iomanip>
#include <fstream>
#include <mutex>
#include <chrono>
#include <iostream>
#include <memory>
#include "../../Observable.h"

class Logger : public Observable {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex mtx;
    std::ofstream logFile;

    Logger() : logFile("taskmaster.log", std::ios::app) {
        if (!logFile.is_open()) {
            throw std::runtime_error("Failed to open log file");
        }
    }

    Logger(const Logger &) = delete;

    Logger &operator=(const Logger &) = delete;

public:
    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    static Logger &getInstance() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!instance) {
            instance = std::unique_ptr<Logger>(new Logger());
        }
        return *instance;
    }

    void log(const std::string &message) {
        std::lock_guard<std::mutex> lock(mtx);
        try {
            auto now = std::chrono::system_clock::now();
            auto now_time = std::chrono::system_clock::to_time_t(now);

            std::tm tm_buffer;
            localtime_s(&tm_buffer, &now_time);

            logFile << std::put_time(&tm_buffer, "%Y-%m-%d %X")
                    << " - " << message << std::endl;

            notifyObservers(message);
        } catch (const std::exception &e) {
            std::cerr << "Logging failed: " << e.what() << std::endl;
        }
    }
};

inline std::unique_ptr<Logger> Logger::instance = nullptr;
inline std::mutex Logger::mtx;

#endif // LOGGER_H
