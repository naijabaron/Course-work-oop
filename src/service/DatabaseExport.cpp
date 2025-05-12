#include "../../include/service/DatabaseExport.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <chrono>
#include <iomanip>

void DatabaseExport::createDatabaseIfNotExists() const {
    if (!std::filesystem::exists(dbFileName)) {
        std::ofstream dbFile(dbFileName);
        if (dbFile.is_open()) {
            dbFile << "Timestamp,TaskTitle,TaskStatus,TaskData\n";
            dbFile.close();
        }
    }
}

std::string DatabaseExport::escapeCsv(const std::string& input) const {
    std::string output;
    output.reserve(input.length());

    for (char c : input) {
        if (c == '"') {
            output += "\"\"";
        } else {
            output += c;
        }
    }

    return output;
}

void DatabaseExport::exportData(const std::string& data) {
    try {
        createDatabaseIfNotExists();

        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        std::tm tm_buf;
        localtime_s(&tm_buf, &in_time_t);

        std::ofstream dbFile(dbFileName, std::ios::app);
        if (!dbFile.is_open()) {
            throw std::runtime_error("Failed to open database file");
        }

        dbFile << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S") << ","
               << "\"" << escapeCsv(data) << "\"\n";

        dbFile.close();

        std::cout << "Successfully exported to database file: "
                 << dbFileName << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Database export failed: " << e.what() << std::endl;
    }
}