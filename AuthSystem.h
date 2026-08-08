#pragma once
#include "UserManager.h"
class AuthSystem
{
private:
    UserManager &userManager;
    User *currentUser;

public:
    AuthSystem(UserManager &manager);
    bool signup(const std::string &username,
                const std::string &password);
};