#ifndef REMINDER_H
#define REMINDER_H
#include <atomic>
#include <thread>
#include <vector>

#include "../task/Task.h"

class Reminder {
    std::vector<Task*> tasks;
    std::atomic<bool> running;
    std::thread reminderThread;
    std::mutex mtx;

    void checkDueDates() {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(10));

            std::lock_guard<std::mutex> lock(mtx);
            auto now = std::time(nullptr);

            for (auto task : tasks) {
                auto dueDate = task->getDueDate();
                if (dueDate != 0 && dueDate <= now + 3600 && dueDate > now) {
                    std::cout << "REMINDER: Task '" << task->getTitle()
                              << "' is due soon!" << std::endl;
                }
            }
        }
    }

public:
    Reminder() : running(true) {
        reminderThread = std::thread(&Reminder::checkDueDates, this);
    }

    ~Reminder() {
        running = false;
        if (reminderThread.joinable()) {
            reminderThread.join();
        }
    }

    void addTask(Task* task) {
        std::lock_guard<std::mutex> lock(mtx);
        tasks.push_back(task);
    }
};

#endif //REMINDER_H
