#ifndef TASKHANDLER_H
#define TASKHANDLER_H
#include "../entity/handler/Handler.h"
#include "TaskManager.h"

class TaskHandler : public Handler {
    TaskManager& manager;
public:
    TaskHandler(TaskManager& manager) : manager(manager) {}

    void handle(const std::string& request) override {
        if (request.find("task:") == 0) {
            std::cout << "Handling task request: " << request << std::endl;
        } else {
            Handler::handle(request);
        }
    }
};

#endif //TASKHANDLER_H
