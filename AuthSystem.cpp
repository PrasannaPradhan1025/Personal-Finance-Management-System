#include "AuthSystem.h"

AuthSystem::AuthSystem(UserManager &manager)
    : userManager(manager), currentUser(nullptr)
{
}
bool AuthSystem::signup(const std::string &username,
                        const std::string &password)
{
    if (userManager.usernameExists(username))
    {
        return false;
    }

    userManager.addUser(username, password);

    return true;
}
bool AuthSystem::login(const std::string &username,
                       const std::string &password)
{
    currentUser = userManager.checkCredentials(username, password);
    return currentUser != nullptr;
}

User *AuthSystem::getCurrentUser() const
{
    return currentUser;
}
void AuthSystem::logout()
{
    currentUser = nullptr;
}