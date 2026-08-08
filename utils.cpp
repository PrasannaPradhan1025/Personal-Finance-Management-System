// utils.cpp
#include <iostream>
#include <cstdlib>
#include "utils.h"

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}