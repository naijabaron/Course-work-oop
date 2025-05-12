#include "../../../include/entity/user/User.h"

User::User(const std::string &username, const std::string &password)
    : username(username) {
    passwordHash = password;
}

bool User::hasPermission(const std::string &permission) const {
    std::lock_guard<std::mutex> lock(mtx);
    return std::find(permissions.begin(), permissions.end(), permission) != permissions.end();
}

void User::addPermission(const std::string &permission) {
    std::lock_guard<std::mutex> lock(mtx);
    permissions.push_back(permission);
}

std::string User::getUsername() const {
    return username;
}
