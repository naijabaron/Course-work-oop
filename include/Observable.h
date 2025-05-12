#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#include <mutex>
#include <vector>
#include <algorithm>

#include "entity/observer/Observer.h"

class Observable {
    std::vector<Observer*> observers;
    std::mutex mtx;
public:
    void addObserver(Observer* observer) {
        std::lock_guard<std::mutex> lock(mtx);
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        std::lock_guard<std::mutex> lock(mtx);
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notifyObservers(const std::string& message) {
        std::lock_guard<std::mutex> lock(mtx);
        for (auto observer : observers) {
            observer->update(message);
        }
    }
};

#endif //OBSERVABLE_H
