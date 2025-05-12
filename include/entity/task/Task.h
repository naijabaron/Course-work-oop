#ifndef TASK_H
#define TASK_H
#include <ctime>
#include <iostream>
#include <mutex>
#include <string>
#include <vector>

#include "TaskStatus.h"

class Task {
    std::string title;
    std::string description;
    TaskStatus status;
    std::time_t creationTime;
    std::time_t dueDate;
    std::vector<std::string> tags;
    std::string category;
    mutable std::mutex mtx;

public:
    Task(const std::string& title, const std::string& description)
        : title(title), description(description), status(TaskStatus::PENDING),
          creationTime(std::time(nullptr)), dueDate(0) {}

    virtual ~Task() = default;

    virtual int getPriority() const { return 0; }

    std::string getTitle() const {
        std::lock_guard<std::mutex> lock(mtx);
        return title;
    }

    void setTitle(const std::string& newTitle) {
        std::lock_guard<std::mutex> lock(mtx);
        title = newTitle;
    }

    std::string getDescription() const {
        std::lock_guard<std::mutex> lock(mtx);
        return description;
    }

    TaskStatus getStatus() const {
        std::lock_guard<std::mutex> lock(mtx);
        return status;
    }

    void setStatus(TaskStatus newStatus) {
        std::lock_guard<std::mutex> lock(mtx);
        status = newStatus;
    }

    void setDueDate(std::time_t date) {
        std::lock_guard<std::mutex> lock(mtx);
        dueDate = date;
    }

    std::time_t getDueDate() const {
        std::lock_guard<std::mutex> lock(mtx);
        return dueDate;
    }

    void addTag(const std::string& tag) {
        std::lock_guard<std::mutex> lock(mtx);
        tags.push_back(tag);
    }

    std::vector<std::string> getTags() const {
        std::lock_guard<std::mutex> lock(mtx);
        return tags;
    }

    void setCategory(const std::string& cat) {
        std::lock_guard<std::mutex> lock(mtx);
        category = cat;
    }

    std::string getCategory() const {
        std::lock_guard<std::mutex> lock(mtx);
        return category;
    }

    virtual void display() const {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Title: " << title << "\nDescription: " << description
                  << "\nStatus: " << static_cast<int>(status)
                  << "\nCreated: " << std::ctime(&creationTime);
        if (dueDate != 0) {
            std::cout << "Due: " << std::ctime(&dueDate);
        }
        if (!tags.empty()) {
            std::cout << "Tags: ";
            for (const auto& tag : tags) {
                std::cout << tag << " ";
            }
            std::cout << std::endl;
        }
        if (!category.empty()) {
            std::cout << "Category: " << category << std::endl;
        }
    }
};

#endif //TASK_H
