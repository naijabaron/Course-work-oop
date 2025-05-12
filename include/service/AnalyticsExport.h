#ifndef ANALYTICSEXPORT_H
#define ANALYTICSEXPORT_H

#include "../ExportStrategy.h"
#include <string>

class AnalyticsExport : public ExportStrategy {
    const std::string analyticsDir = "analytics_data";

    void ensureDirectoryExists() const;

public:
    void exportData(const std::string& data) override;
};

#endif // ANALYTICSEXPORT_H