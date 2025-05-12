#ifndef PRIORITYTASKDECORATOR_H
#define PRIORITYTASKDECORATOR_H

#include <iostream>

#include "TaskDecorator.h"

class PriorityTaskDecorator : public TaskDecorator {
    int priority;
public:
    PriorityTaskDecorator(std::unique_ptr<Task> task, int priority)
        : TaskDecorator(std::move(task)), priority(priority) {}

    int getPriority() const override {
        return priority;
    }

    void display() const override {
        decoratedTask->display();
        std::cout << "Priority: " << priority << std::endl;
    }
};

#endif //PRIORITYTASKDECORATOR_H
