#pragma once

#include <string>

class User {
private:
    int id;
    std::string username;
    std::string password;

public:
    User();
    User(int id, const std::string& username, const std::string& password);

    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;

    void show();
};