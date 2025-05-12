#ifndef EXPORTSTRATEGY_H
#define EXPORTSTRATEGY_H
#include <string>

class ExportStrategy {
public:
    virtual ~ExportStrategy() = default;
    virtual void exportData(const std::string& data) = 0;
};

#endif //EXPORTSTRATEGY_H
