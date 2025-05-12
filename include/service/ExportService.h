#ifndef EXPORTSERVICE_H
#define EXPORTSERVICE_H

#include <memory>
#include <string>
#include <unordered_map>

#include "AnalyticsExport.h"
#include "DatabaseExport.h"
#include "../ExportStrategy.h"

class ExportService {
    std::unordered_map<std::string, std::unique_ptr<ExportStrategy>> exporters;
    std::mutex mtx;

public:
    ExportService() {
        registerExporter("analytics", std::make_unique<AnalyticsExport>());
        registerExporter("database", std::make_unique<DatabaseExport>());
    }

    void registerExporter(const std::string& name, std::unique_ptr<ExportStrategy> exporter) {
        std::lock_guard<std::mutex> lock(mtx);
        exporters[name] = std::move(exporter);
    }

    void exportData(const std::string& exporterName, const std::string& data) {
        std::lock_guard<std::mutex> lock(mtx);
        if (exporters.find(exporterName) != exporters.end()) {
            exporters[exporterName]->exportData(data);
        } else {
            throw std::runtime_error("Exporter not found");
        }
    }
};

#endif //EXPORTSERVICE_H
