#ifndef CREATETASKCOMMAND_H
#define CREATETASKCOMMAND_H

#include "Command.h"
#include "../logger/Logger.h"
#include "../../service/TaskManager.h"

class CreateTaskCommand : public Command {
    TaskManager& manager;
    std::string title;
    std::string description;
    int priority;
    Task* createdTask;

public:
    CreateTaskCommand(TaskManager& manager, const std::string& title,
                     const std::string& description, int priority = 0)
        : manager(manager), title(title), description(description), priority(priority),
          createdTask(nullptr) {}

    void execute() override {
        createdTask = manager.createTask(title, description, priority);
        Logger::getInstance().log("Created task: " + title);
    }

    void undo() override {
        if (createdTask) {
            Logger::getInstance().log("Undo create task: " + title);
            createdTask = nullptr;
        }
    }
};

#endif //CREATETASKCOMMAND_H
