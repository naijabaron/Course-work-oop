#ifndef TADTASK_H
#define TADTASK_H
#include "Task.h"

class TadTask : public Task {
    int priority;
public:
    TadTask(const std::string& title, const std::string& description, int priority)
        : Task(title, description), priority(priority) {}

    int getPriority() const override {
        return priority;
    }

    void display() const override {
        Task::display();
        std::cout << "Priority: " << priority << std::endl;
    }
};

#endif //TADTASK_H
