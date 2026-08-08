// utils.cpp
#include <iostream>
#include <cstdlib>
#include "utils.h"
#include <random>
#include <string>


void clearScreen() {
    system("cls");
}

void pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}


std::string generateStrongPassword(int length)
{
    const std::string chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        "!@#$%^&*()_+-=[]|;:,.<>?";

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<size_t> dist(0, chars.size() - 1);

    std::string password;

    for (int i = 0; i < length; ++i)
    {
        password += chars[dist(gen)];
    }

    return password;
}