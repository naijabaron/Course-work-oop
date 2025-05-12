#include "../../include/service/AnalyticsExport.h"
#include <fstream>
#include <ctime>
#include <iomanip>
#include <filesystem>
#include <iostream>
#include <chrono>
#include <sstream>

void AnalyticsExport::ensureDirectoryExists() const {
    if (!std::filesystem::exists(analyticsDir)) {
        std::filesystem::create_directory(analyticsDir);
    }
}

void AnalyticsExport::exportData(const std::string& data) {
    try {
        ensureDirectoryExists();

        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm tm_buf;
        localtime_s(&tm_buf, &in_time_t);

        std::ostringstream filename;
        filename << analyticsDir << "/analytics_"
                << std::put_time(&tm_buf, "%Y-%m-%d_%H-%M-%S") << ".log";

        std::ofstream outFile(filename.str(), std::ios::app);
        if (!outFile.is_open()) {
            throw std::runtime_error("Failed to open analytics file");
        }

        outFile << "[" << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S") << "] "
               << data << "\n";

        outFile.close();

        std::cout << "Successfully exported to analytics file: "
                 << filename.str() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Analytics export failed: " << e.what() << std::endl;
    }
}