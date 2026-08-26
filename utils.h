// utils.h
#pragma once

void clearScreen();
void pauseScreen();

std::string generateStrongPassword(int length);
bool readInt(const std::string &prompt, int &value);
bool readAmount(const std::string &prompt, double &value);
std::string readText(const std::string &prompt);