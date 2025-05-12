#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <memory>
#include <vector>
#include <sstream>

#include "../entity/category/Category.h"
#include "ExportService.h"
#include "../entity/project/Project.h"
#include "../entity/reminder/Reminder.h"
#include "../factory/TadTaskFactory.h"
#include "../factory/TaskFactory.h"
#include "../entity/user/User.h"

class TaskManager {
    std::vector<std::unique_ptr<Project>> projects;
    std::vector<std::unique_ptr<Category>> categories;
    std::vector<std::unique_ptr<User>> users;
    ExportService exportService;
    Reminder reminder;
    std::unique_ptr<TaskFactory> taskFactory;
    mutable std::mutex mtx;

public:
    TaskManager() : taskFactory(std::make_unique<TadTaskFactory>()) {}

    Project* createProject(const std::string& name) {
        std::lock_guard<std::mutex> lock(mtx);
        projects.push_back(std::make_unique<Project>(name));
        return projects.back().get();
    }

    Category* createCategory(const std::string& name) {
        std::lock_guard<std::mutex> lock(mtx);
        categories.push_back(std::make_unique<Category>(name));
        return categories.back().get();
    }

    User* createUser(const std::string& username, const std::string& password) {
        std::lock_guard<std::mutex> lock(mtx);
        users.push_back(std::make_unique<User>(username, password));
        return users.back().get();
    }

    Task* createTask(const std::string& title, const std::string& description, int priority = 0) {
        auto task = taskFactory->createTask(title, description, priority);
        auto rawPtr = task.get();

        std::lock_guard<std::mutex> lock(mtx);
        if (!projects.empty()) {
            projects[0]->addTask(std::move(task));
        }

        reminder.addTask(rawPtr);
        return rawPtr;
    }

    void exportTaskData(Task* task, const std::string& exporterName) {
        std::stringstream data;
        data << "Task: " << task->getTitle() << ", Status: " << static_cast<int>(task->getStatus());
        exportService.exportData(exporterName, data.str());
    }

    std::vector<Project*> getProjects() const {
        std::lock_guard<std::mutex> lock(mtx);
        std::vector<Project*> result;
        for (const auto& project : projects) {
            result.push_back(project.get());
        }
        return result;
    }

    std::vector<Category*> getCategories() const {
        std::lock_guard<std::mutex> lock(mtx);
        std::vector<Category*> result;
        for (const auto& category : categories) {
            result.push_back(category.get());
        }
        return result;
    }
};

#endif //TASKMANAGER_H
