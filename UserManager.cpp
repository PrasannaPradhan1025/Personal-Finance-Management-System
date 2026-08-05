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
//like top 5 return garxa if incomplete username input garei also name change garei
std::vector<User> UserManager::searchUsers(const std::string& keyword, int limit)
{
    std::vector<User> results;

    for (const auto& user : users)
    {
        //inbuilt nai use garei this is case sensitive
        if (user.getUsername().find(keyword) != std::string::npos)
        {
            results.push_back(user);

            if (results.size() >= limit)
                break;
        }
    }

    return results;
}


