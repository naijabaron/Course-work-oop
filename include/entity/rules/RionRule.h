#ifndef RIONRULE_H
#define RIONRULE_H
#include <functional>

#include "../task/Task.h"

class RionRule {
    std::string name;
    std::function<bool(const Task&)> condition;
    std::function<void(Task&)> action;
public:
    RionRule(const std::string& name,
             std::function<bool(const Task&)> condition,
             std::function<void(Task&)> action)
        : name(name), condition(condition), action(action) {}

    void apply(Task& task) const {
        if (condition(task)) {
            action(task);
        }
    }

    std::string getName() const { return name; }
};


#endif //RIONRULE_H
