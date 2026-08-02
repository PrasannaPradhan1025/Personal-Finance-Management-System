#include "UserManager.h"
#include <iostream>
#include <string>

UserManager::UserManager(const std::string& filename) : filename(filename) {
    
    loadUsers();
}

UserManager::~UserManager() {
}

#include <iostream>

void UserManager::display()
{
    if (users.empty())
    {
        std::cout << "No users found.\n";
        return;
    }

    for (const User& user : users)
    {
        std::cout << "ID: " << user.getId() << '\n';
        std::cout << "Username: " << user.getUsername() << '\n';
        std::cout << "Password: " << user.getPassword() << "\n\n";
    }
}

void UserManager::loadUsers()
{
    users.clear();

    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "No user file found.\n";
        return;
    }
    int id;
    std::string username;
    std::string password;

    while (file >>id >> username >> password)
    {
        users.push_back(User(id,username, password));
    }

    file.close();
}


