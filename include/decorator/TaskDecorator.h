#ifndef TASKDECORATOR_H
#define TASKDECORATOR_H
#include <memory>

class TaskDecorator : public class Task {
protected:
    std::unique_ptr<Task> decoratedTask;
public:
    TaskDecorator(std::unique_ptr<Task> task) : decoratedTask(std::move(task)) {}
};

#endif //TASKDECORATOR_H
