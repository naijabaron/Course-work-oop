#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>


#include "../task/Task.h"

class Category {
    std::string name;
    std::vector<Task *> tasks;
    mutable std::mutex mtx;

public:
    Category(const std::string &name);

    void addTask(Task *task);

    std::vector<Task *> getTasks() const;

    std::string getName() const;
};


#endif //CATEGORY_H
