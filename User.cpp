#include <iostream>
#include "User.h"

User::User() : id(0), username(""), password("") {}

User::User(int id, const std::string& username, const std::string& password)
    : id(id), username(username), password(password) {}

int User::getId() const {
    return id;
}

void User::show(){  
    std::cout<< "id: " <<id;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getPassword() const {
    return password;
}

void User::setUsername(const std::string& username)  {
    this->username = username;

}

void User::setPassword(const std::string& password)  {
    this->password = password;

}
