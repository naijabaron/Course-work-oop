#ifndef TADTASKFACTORY_H
#define TADTASKFACTORY_H
#include "../entity/task/TadTask.h"
#include "TaskFactory.h"

class TadTaskFactory : public TaskFactory {
public:
    std::unique_ptr<Task> createTask(const std::string& title, const std::string& description, int priority) override {
        return std::make_unique<TadTask>(title, description, priority);
    }
};

#endif //TADTASKFACTORY_H
