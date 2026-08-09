#include "IncomeManager.h"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

IncomeManager::IncomeManager(const std::string &filename, int loggedInUserId)
    : filename(filename), loggedInUserId(loggedInUserId) {
    loadIncome();
}

bool IncomeManager::isValidDate(const std::string &date) {
    if (date.size() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(static_cast<unsigned char>(date[i]))) return false;
    }

    return true;
}

bool IncomeManager::isValidAmount(double amount) {
    return amount > 0;
}

int IncomeManager::getNextIncomeId() {
    int nextId = 1;
    for (const Income &income : incomes) {
        if (income.getIncomeId() >= nextId) {
            nextId = income.getIncomeId() + 1;
        }
    }
    return nextId;
}

std::vector<Income> IncomeManager::getIncomeForCurrentUser() const {
    std::vector<Income> result;
    for (const Income &income : incomes) {
        if (income.getUserId() == loggedInUserId) {
            result.push_back(income);
        }
    }
    return result;
}

void IncomeManager::loadIncome() {
    incomes.clear();
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::stringstream ss(line);
        std::string token;
        std::vector<std::string> parts;
        while (std::getline(ss, token, '|')) {
            parts.push_back(token);
        }

        if (parts.size() != 6) continue;

        int incomeId = std::stoi(parts[0]);
        int userId = std::stoi(parts[1]);
        double amount = std::stod(parts[2]);
        std::string source = parts[3];
        std::string date = parts[4];
        std::string description = parts[5];

        incomes.push_back(Income(incomeId, userId, amount, source, date, description));
    }

    file.close();
}

void IncomeManager::saveIncome() {
    std::ofstream file(filename.c_str(), std::ios::trunc);
    if (!file.is_open()) {
        std::cout << "Unable to save income records.\n";
        return;
    }

    for (const Income &income : incomes) {
        file << income.getIncomeId() << '|'
             << income.getUserId() << '|'
             << std::fixed << std::setprecision(2) << income.getAmount() << '|'
             << income.getSource() << '|'
             << income.getDate() << '|'
             << income.getDescription() << '\n';
    }

    file.close();
}

void IncomeManager::addIncome() {
    double amount;
    std::string source;
    std::string date;
    std::string description;

    std::cout << "Enter amount: ";
    std::cin >> amount;
    std::cin.ignore();

    if (!isValidAmount(amount)) {
        std::cout << "Amount must be greater than 0.\n";
        return;
    }

    std::cout << "Enter source: ";
    std::getline(std::cin, source);

    std::cout << "Enter date (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    if (!isValidDate(date)) {
        std::cout << "Invalid date format. Use YYYY-MM-DD.\n";
        return;
    }

    std::cout << "Enter description: ";
    std::getline(std::cin, description);

    int incomeId = getNextIncomeId();
    Income newIncome(incomeId, loggedInUserId, amount, source, date, description);
    incomes.push_back(newIncome);
    saveIncome();

    std::cout << "Income added successfully!\n";
}

void IncomeManager::viewIncome() {
    std::vector<Income> userIncomes = getIncomeForCurrentUser();

    if (userIncomes.empty()) {
        std::cout << "No income records found.\n";
        return;
    }

    std::cout << "ID | Amount | Source | Date | Description\n";
    std::cout << "--------------------------------------\n";
    for (const Income &income : userIncomes) {
        std::cout << income.getIncomeId() << " | "
                  << std::fixed << std::setprecision(2) << income.getAmount() << " | "
                  << income.getSource() << " | "
                  << income.getDate() << " | "
                  << income.getDescription() << "\n";
    }
}

void IncomeManager::updateIncome() {
    int id;
    std::cout << "Enter Income ID to update: ";
    std::cin >> id;
    std::cin.ignore();

    int index = -1;
    for (size_t i = 0; i < incomes.size(); ++i) {
        if (incomes[i].getIncomeId() == id && incomes[i].getUserId() == loggedInUserId) {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1) {
        std::cout << "Income record not found for this user.\n";
        return;
    }

    int choice;
    std::cout << "1. Update amount\n2. Update source\n3. Update date\n4. Update description\nEnter choice: ";
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
    case 1: {
        double amount;
        std::cout << "Enter new amount: ";
        std::cin >> amount;
        std::cin.ignore();
        if (!isValidAmount(amount)) {
            std::cout << "Amount must be greater than 0.\n";
            return;
        }
        incomes[index].setAmount(amount);
        break;
    }
    case 2: {
        std::string source;
        std::cout << "Enter new source: ";
        std::getline(std::cin, source);
        incomes[index].setSource(source);
        break;
    }
    case 3: {
        std::string date;
        std::cout << "Enter new date (YYYY-MM-DD): ";
        std::getline(std::cin, date);
        if (!isValidDate(date)) {
            std::cout << "Invalid date format.\n";
            return;
        }
        incomes[index].setDate(date);
        break;
    }
    case 4: {
        std::string description;
        std::cout << "Enter new description: ";
        std::getline(std::cin, description);
        incomes[index].setDescription(description);
        break;
    }
    default:
        std::cout << "Invalid choice.\n";
        return;
    }

    saveIncome();
    std::cout << "Income updated successfully!\n";
}

void IncomeManager::deleteIncome() {
    int id;
    std::cout << "Enter Income ID to delete: ";
    std::cin >> id;
    std::cin.ignore();

    int index = -1;
    for (size_t i = 0; i < incomes.size(); ++i) {
        if (incomes[i].getIncomeId() == id && incomes[i].getUserId() == loggedInUserId) {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1) {
        std::cout << "Income record not found for this user.\n";
        return;
    }

    char confirmation;
    std::cout << "Delete this income record? (y/n): ";
    std::cin >> confirmation;
    std::cin.ignore();

    if (confirmation == 'y' || confirmation == 'Y') {
        incomes.erase(incomes.begin() + index);
        saveIncome();
        std::cout << "Income deleted successfully!\n";
    } else {
        std::cout << "Deletion cancelled.\n";
    }
}

void IncomeManager::searchIncome() {
    std::string keyword;
    std::cout << "Enter income ID, source, or date: ";
    std::getline(std::cin, keyword);

    bool found = false;
    std::vector<Income> userIncomes = getIncomeForCurrentUser();
    for (const Income &income : userIncomes) {
        std::string idString = std::to_string(income.getIncomeId());
        if (idString == keyword || income.getSource() == keyword || income.getDate() == keyword) {
            std::cout << income.getIncomeId() << " | "
                      << income.getAmount() << " | "
                      << income.getSource() << " | "
                      << income.getDate() << " | "
                      << income.getDescription() << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No matching income found.\n";
    }
}

double IncomeManager::getTotalIncome() {
    double total = 0.0;
    std::vector<Income> userIncomes = getIncomeForCurrentUser();
    for (const Income &income : userIncomes) {
        total += income.getAmount();
    }
    return total;
}
