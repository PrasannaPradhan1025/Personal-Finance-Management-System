#include "AuthSystem.h"

AuthSystem::AuthSystem(UserManager &manager)
    : userManager(manager)
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
    return userManager.checkCredentials(username, password);
}