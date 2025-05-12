#include "../../../include/entity/category/Category.h"

Category::Category(const std::string &name) : name(name) {
}

void Category::addTask(Task *task) {
    std::lock_guard<std::mutex> lock(mtx);
    tasks.push_back(task);
    task->setCategory(name);
}

std::vector<Task *> Category::getTasks() const {
    std::lock_guard<std::mutex> lock(mtx);
    return tasks;
}

std::string Category::getName() const {
    return name;
}
