#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "User.h"

class UserManager {
private:
    std::string filename;
    std::vector<User> users;

public:
    UserManager(const std::string& filename);
    ~UserManager();
    void display();
    void loadUsers();
    void saveUsers();
    void addUser(const std::string& username, const std::string& password);
    std::string findUser(const std::string& username);
};
