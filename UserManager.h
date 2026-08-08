#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "User.h"

class UserManager
{
private:
    std::string filename;
    std::vector<User> users;

public:
    UserManager(const std::string &filename);
    ~UserManager();
    void display();
    void loadUsers();
    void saveUsers();
    void addUser(const std::string &username, const std::string &password);
    bool usernameExists(const std::string &username);                                // to check if username already exists(for sign up)
    bool checkCredentials(const std::string &username, const std::string &password); // to check if username and password match(for login)
    std::vector<User> searchUsers(const std::string &keyword, int limit = 5);        // function rakheko
};
