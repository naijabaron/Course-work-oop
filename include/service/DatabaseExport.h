#ifndef DATABASEEXPORT_H
#define DATABASEEXPORT_H

#include "../ExportStrategy.h"
#include <string>

class DatabaseExport : public ExportStrategy {
    const std::string dbFileName = "task_database.csv";

    void createDatabaseIfNotExists() const;
    std::string escapeCsv(const std::string& input) const;

public:
    void exportData(const std::string& data) override;
};

#endif // DATABASEEXPORT_H