#ifndef PROJECT_H
#define PROJECT_H
#include <memory>
#include <string>
#include <vector>

#include "../rules/RionRule.h"


class Project {
    std::string name;
    std::vector<std::unique_ptr<Task>> tasks;
    std::vector<RionRule> rules;
    mutable std::mutex mtx;

public:
    Project(const std::string& name) : name(name) {}

    void addTask(std::unique_ptr<Task> task) {
        std::lock_guard<std::mutex> lock(mtx);
        for (const auto& rule : rules) {
            rule.apply(*task);
        }
        tasks.push_back(std::move(task));
    }

    void addRule(const RionRule& rule) {
        std::lock_guard<std::mutex> lock(mtx);
        rules.push_back(rule);
    }

    std::vector<Task*> getTasks() const {
        std::lock_guard<std::mutex> lock(mtx);
        std::vector<Task*> result;
        for (const auto& task : tasks) {
            result.push_back(task.get());
        }
        return result;
    }

    std::string getName() const {
        return name;
    }
};


#endif //PROJECT_H
