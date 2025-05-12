#ifndef TASKFACTORY_H
#define TASKFACTORY_H
#include <memory>

class TaskFactory {
public:
    virtual ~TaskFactory() = default;
    virtual std::unique_ptr<class Task> createTask(const std::string& title, const std::string& description, int priority) = 0;
};

#endif //TASKFACTORY_H
