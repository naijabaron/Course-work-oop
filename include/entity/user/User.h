#ifndef USER_H
#define USER_H
#include <algorithm>
#include <mutex>
#include <string>
#include <vector>

class User {
    std::string username;
    std::string passwordHash;
    std::vector<std::string> permissions;
    mutable std::mutex mtx;

public:
    User(const std::string& username, const std::string& password);

    bool hasPermission(const std::string& permission) const;

    void addPermission(const std::string& permission);

    std::string getUsername() const;
};

#endif //USER_H
