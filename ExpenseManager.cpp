#include "ExpenseManager.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

ExpenseManager::ExpenseManager(const std::string &filename, int loggedInUserId)
    : filename(filename), loggedInUserId(loggedInUserId) {
    loadExpenses();
}

bool ExpenseManager::isValidDate(const std::string &date) {
    if (date.size() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(static_cast<unsigned char>(date[i]))) return false;
    }

    return true;
}

bool ExpenseManager::isValidAmount(double amount) {
    return amount > 0;
}

int ExpenseManager::getNextExpenseId() {
    int nextId = 1;
    for (const Expense &expense : expenses) {
        if (expense.getExpenseId() >= nextId) {
            nextId = expense.getExpenseId() + 1;
        }
    }
    return nextId;
}

std::vector<Expense> ExpenseManager::getExpensesForCurrentUser() const {
    std::vector<Expense> result;
    for (const Expense &expense : expenses) {
        if (expense.getUserId() == loggedInUserId) {
            result.push_back(expense);
        }
    }
    return result;
}

void ExpenseManager::loadExpenses() {
    expenses.clear();
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

        int expenseId = std::stoi(parts[0]);
        int userId = std::stoi(parts[1]);
        double amount = std::stod(parts[2]);
        std::string category = parts[3];
        std::string date = parts[4];
        std::string description = parts[5];

        expenses.push_back(Expense(expenseId, userId, amount, category, date, description));
    }

    file.close();
}

void ExpenseManager::saveExpenses() {
    std::ofstream file(filename.c_str(), std::ios::trunc);
    if (!file.is_open()) {
        std::cout << "Unable to save expense records.\n";
        return;
    }

    for (const Expense &expense : expenses) {
        file << expense.getExpenseId() << '|'
             << expense.getUserId() << '|'
             << std::fixed << std::setprecision(2) << expense.getAmount() << '|'
             << expense.getCategory() << '|'
             << expense.getDate() << '|'
             << expense.getDescription() << '\n';
    }

    file.close();
}

void ExpenseManager::addExpense() {
    double amount;
    std::string category;
    std::string date;
    std::string description;

    std::cout << "Enter amount: ";
    std::cin >> amount;
    std::cin.ignore();

    if (!isValidAmount(amount)) {
        std::cout << "Amount must be greater than 0.\n";
        return;
    }

    std::cout << "Enter category: ";
    std::getline(std::cin, category);

    std::cout << "Enter date (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    if (!isValidDate(date)) {
        std::cout << "Invalid date format. Use YYYY-MM-DD.\n";
        return;
    }

    std::cout << "Enter description: ";
    std::getline(std::cin, description);

    int expenseId = getNextExpenseId();
    Expense newExpense(expenseId, loggedInUserId, amount, category, date, description);
    expenses.push_back(newExpense);
    saveExpenses();

    std::cout << "Expense added successfully!\n";
}

void ExpenseManager::viewExpenses() {
    std::vector<Expense> userExpenses = getExpensesForCurrentUser();

    if (userExpenses.empty()) {
        std::cout << "No expense records found.\n";
        return;
    }

    std::cout << "ID | Amount | Category | Date | Description\n";
    std::cout << "-----------------------------------------\n";
    for (const Expense &expense : userExpenses) {
        std::cout << expense.getExpenseId() << " | "
                  << std::fixed << std::setprecision(2) << expense.getAmount() << " | "
                  << expense.getCategory() << " | "
                  << expense.getDate() << " | "
                  << expense.getDescription() << "\n";
    }
}

void ExpenseManager::updateExpense() {
    int id;
    std::cout << "Enter Expense ID to update: ";
    std::cin >> id;
    std::cin.ignore();

    int index = -1;
    for (size_t i = 0; i < expenses.size(); ++i) {
        if (expenses[i].getExpenseId() == id && expenses[i].getUserId() == loggedInUserId) {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1) {
        std::cout << "Expense record not found for this user.\n";
        return;
    }

    int choice;
    std::cout << "1. Update amount\n2. Update category\n3. Update date\n4. Update description\nEnter choice: ";
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
        expenses[index].setAmount(amount);
        break;
    }
    case 2: {
        std::string category;
        std::cout << "Enter new category: ";
        std::getline(std::cin, category);
        expenses[index].setCategory(category);
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
        expenses[index].setDate(date);
        break;
    }
    case 4: {
        std::string description;
        std::cout << "Enter new description: ";
        std::getline(std::cin, description);
        expenses[index].setDescription(description);
        break;
    }
    default:
        std::cout << "Invalid choice.\n";
        return;
    }

    saveExpenses();
    std::cout << "Expense updated successfully!\n";
}

void ExpenseManager::deleteExpense() {
    int id;
    std::cout << "Enter Expense ID to delete: ";
    std::cin >> id;
    std::cin.ignore();

    int index = -1;
    for (size_t i = 0; i < expenses.size(); ++i) {
        if (expenses[i].getExpenseId() == id && expenses[i].getUserId() == loggedInUserId) {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1) {
        std::cout << "Expense record not found for this user.\n";
        return;
    }

    char confirmation;
    std::cout << "Delete this expense record? (y/n): ";
    std::cin >> confirmation;
    std::cin.ignore();

    if (confirmation == 'y' || confirmation == 'Y') {
        expenses.erase(expenses.begin() + index);
        saveExpenses();
        std::cout << "Expense deleted successfully!\n";
    } else {
        std::cout << "Deletion cancelled.\n";
    }
}

void ExpenseManager::searchExpense() {
    std::string keyword;
    std::cout << "Enter expense ID, category, or date: ";
    std::getline(std::cin, keyword);

    bool found = false;
    std::vector<Expense> userExpenses = getExpensesForCurrentUser();
    for (const Expense &expense : userExpenses) {
        std::string idString = std::to_string(expense.getExpenseId());
        if (idString == keyword || expense.getCategory() == keyword || expense.getDate() == keyword) {
            std::cout << expense.getExpenseId() << " | "
                      << expense.getAmount() << " | "
                      << expense.getCategory() << " | "
                      << expense.getDate() << " | "
                      << expense.getDescription() << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No matching expense found.\n";
    }
}

double ExpenseManager::getTotalExpenses() {
    double total = 0.0;
    std::vector<Expense> userExpenses = getExpensesForCurrentUser();
    for (const Expense &expense : userExpenses) {
        total += expense.getAmount();
    }
    return total;
}
