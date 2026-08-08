#include "UserManager.h"
#include <iostream>
#include <string>

UserManager::UserManager(const std::string &filename) : filename(filename)
{

    loadUsers();
}

UserManager::~UserManager()
{
}

#include <iostream>

void UserManager::display()
{
    if (users.empty())
    {
        std::cout << "No users found.\n";
        return;
    }

    for (const User &user : users)
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

    while (file >> id >> username >> password)
    {
        users.push_back(User(id, username, password));
    }

    file.close();
}
void UserManager::addUser(const std::string &username,
                          const std::string &password)
{
    int id;

    if (users.empty())
    {
        id = 1;
    }
    else
    {
        id = users.back().getId() + 1;
    }

    User newUser(id, username, password);

    users.push_back(newUser);

    saveUsers();

    std::cout << "User added successfully!\n";
}
void UserManager::saveUsers()
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Unable to save users.\n";
        return;
    }

    for (const User &user : users)
    {
        file << user.getId() << " "
             << user.getUsername() << " "
             << user.getPassword() << std::endl;
    }

    file.close();
}
bool UserManager::usernameExists(const std::string &username)
{
    for (const auto &user : users)
    {
        if (user.getUsername() == username)
        {
            return true;
        }
    }
    return false;
}
std::vector<User> UserManager::searchUsers(const std::string &keyword, int limit)
{
    std::vector<User> results;

    for (const auto &user : users)
    {
        // inbuilt nai use garei this is case sensitive
        if (user.getUsername().find(keyword) != std::string::npos)
        {
            results.push_back(user);

            if (results.size() >= limit)
                break;
        }
    }

    return results;
}