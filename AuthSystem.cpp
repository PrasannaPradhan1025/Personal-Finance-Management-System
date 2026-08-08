#include "AuthSystem.h"
#include <iostream>
#include <cctype>
#include <string>

AuthSystem::AuthSystem(UserManager &manager)
    : userManager(manager), currentUser(nullptr)
{
}

bool AuthSystem::isStrongPassword(const std::string& password){
    bool hasNumber = false;
    bool hasUppercase = false;

    for (char c : password) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            hasNumber = true;
        }

        if (std::isupper(static_cast<unsigned char>(c))) {
            hasUppercase = true;
        }
    }

    return hasNumber && hasUppercase;
}

bool AuthSystem::signup(const std::string &username,
                        const std::string &password)
{



    if (userManager.usernameExists(username) )
    {
        return false;
    }

    if (username.length() > 20 || password.length() > 20) {
        std::cout << "Username and password should not exceed 20 characters.\n";
        return false;
    }

    if (username.length() < 3 || password.length() < 6) {
        std::cout << "Username must be at least 3 characters long and password must be at least 6 characters long.\n";
        return false;
    }

    if (username.empty() || password.empty() ) {
        std::cout << "Username and password cannot be empty.\n";
        return false;   
    }

    if(isStrongPassword(password) == false){
        std::cout << "Password must contain at least one number and one uppercase letter.\n";
        return false;
    }

    userManager.addUser(username, password);

    return true;
}


