// utils.cpp
#include <iostream>
#include <cstdlib>
#include "utils.h"
#include <random>
#include <string>
#include <sstream>
#include <cmath>


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

bool readInt(const std::string &prompt, int &value)
{
    std::cout << prompt;
    std::string input;
    if (!std::getline(std::cin, input))
        return false;

    std::stringstream stream(input);
    char extra;
    if (!(stream >> value) || (stream >> extra))
    {
        std::cout << "Please enter a whole number.\n";
        return false;
    }
    return true;
}

bool readAmount(const std::string &prompt, double &value)
{
    std::cout << prompt;
    std::string input;
    if (!std::getline(std::cin, input))
        return false;

    std::stringstream stream(input);
    char extra;
    if (!(stream >> value) || (stream >> extra) || !std::isfinite(value))
    {
        std::cout << "Please enter a valid amount.\n";
        return false;
    }
    return true;
}

std::string readText(const std::string &prompt)
{
    std::cout << prompt;
    std::string value;
    std::getline(std::cin, value);
    return value;
}