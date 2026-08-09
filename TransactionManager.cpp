#include "TransactionManager.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct TransactionRecord {
    int id;
    std::string type;
    double amount;
    std::string categoryOrSource;
    std::string date;
    std::string description;
};

TransactionManager::TransactionManager(const std::vector<Income> &incomes,
                                       const std::vector<Expense> &expenses,
                                       int loggedInUserId)
    : incomes(incomes), expenses(expenses), loggedInUserId(loggedInUserId) {}

static std::vector<TransactionRecord> buildTransactions(const std::vector<Income> &incomes,
                                                       const std::vector<Expense> &expenses,
                                                       int loggedInUserId) {
    std::vector<TransactionRecord> records;
    for (const Income &income : incomes) {
        if (income.getUserId() == loggedInUserId) {
            TransactionRecord record;
            record.id = income.getIncomeId();
            record.type = "INCOME";
            record.amount = income.getAmount();
            record.categoryOrSource = income.getSource();
            record.date = income.getDate();
            record.description = income.getDescription();
            records.push_back(record);
        }
    }

    for (const Expense &expense : expenses) {
        if (expense.getUserId() == loggedInUserId) {
            TransactionRecord record;
            record.id = expense.getExpenseId();
            record.type = "EXPENSE";
            record.amount = expense.getAmount();
            record.categoryOrSource = expense.getCategory();
            record.date = expense.getDate();
            record.description = expense.getDescription();
            records.push_back(record);
        }
    }

    return records;
}

void TransactionManager::viewTransactions() const {
    std::vector<TransactionRecord> records = buildTransactions(incomes, expenses, loggedInUserId);
    if (records.empty()) {
        std::cout << "No transactions found.\n";
        return;
    }

    std::cout << "ID | Type | Amount | Category/Source | Date | Description\n";
    std::cout << "--------------------------------------------------------\n";
    for (const TransactionRecord &record : records) {
        std::cout << record.id << " | " << record.type << " | "
                  << record.amount << " | " << record.categoryOrSource << " | "
                  << record.date << " | " << record.description << "\n";
    }
}

void TransactionManager::searchTransaction() const {
    std::string keyword;
    std::cout << "Enter ID, date, or type: ";
    std::getline(std::cin, keyword);

    std::vector<TransactionRecord> records = buildTransactions(incomes, expenses, loggedInUserId);
    bool found = false;
    for (const TransactionRecord &record : records) {
        std::string idString = std::to_string(record.id);
        if (idString == keyword || record.date == keyword || record.type == keyword) {
            std::cout << record.id << " | " << record.type << " | "
                      << record.amount << " | " << record.categoryOrSource << " | "
                      << record.date << " | " << record.description << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No matching transactions found.\n";
    }
}

void TransactionManager::filterByType() const {
    std::vector<TransactionRecord> records = buildTransactions(incomes, expenses, loggedInUserId);
    int choice;
    std::cout << "1. All\n2. Income\n3. Expense\nEnter choice: ";
    std::cin >> choice;
    std::cin.ignore();

    for (const TransactionRecord &record : records) {
        if (choice == 1 || (choice == 2 && record.type == "INCOME") || (choice == 3 && record.type == "EXPENSE")) {
            std::cout << record.id << " | " << record.type << " | "
                      << record.amount << " | " << record.categoryOrSource << " | "
                      << record.date << " | " << record.description << "\n";
        }
    }
}

void TransactionManager::filterByDate() const {
    std::string date;
    std::cout << "Enter date: ";
    std::getline(std::cin, date);

    std::vector<TransactionRecord> records = buildTransactions(incomes, expenses, loggedInUserId);
    bool found = false;
    for (const TransactionRecord &record : records) {
        if (record.date == date) {
            std::cout << record.id << " | " << record.type << " | "
                      << record.amount << " | " << record.categoryOrSource << " | "
                      << record.date << " | " << record.description << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No transactions found for that date.\n";
    }
}

void TransactionManager::filterByCategory() const {
    std::string keyword;
    std::cout << "Enter category/source: ";
    std::getline(std::cin, keyword);

    std::vector<TransactionRecord> records = buildTransactions(incomes, expenses, loggedInUserId);
    bool found = false;
    for (const TransactionRecord &record : records) {
        if (record.categoryOrSource == keyword) {
            std::cout << record.id << " | " << record.type << " | "
                      << record.amount << " | " << record.categoryOrSource << " | "
                      << record.date << " | " << record.description << "\n";
            found = true;
        }
    }

    if (!found) {
        std::cout << "No transactions found for that category/source.\n";
    }
}

void TransactionManager::sortByAmount() const {
    std::vector<TransactionRecord> records = buildTransactions(incomes, expenses, loggedInUserId);
    int choice;
    std::cout << "1. Lowest to highest\n2. Highest to lowest\nEnter choice: ";
    std::cin >> choice;
    std::cin.ignore();

    std::vector<TransactionRecord> sortedRecords = records;
    std::sort(sortedRecords.begin(), sortedRecords.end(), [](const TransactionRecord &a, const TransactionRecord &b) {
        return a.amount < b.amount;
    });

    if (choice == 2) {
        std::reverse(sortedRecords.begin(), sortedRecords.end());
    }

    for (const TransactionRecord &record : sortedRecords) {
        std::cout << record.id << " | " << record.type << " | "
                  << record.amount << " | " << record.categoryOrSource << " | "
                  << record.date << " | " << record.description << "\n";
    }
}

void TransactionManager::sortByDate() const {
    std::vector<TransactionRecord> records = buildTransactions(incomes, expenses, loggedInUserId);
    int choice;
    std::cout << "1. Newest first\n2. Oldest first\nEnter choice: ";
    std::cin >> choice;
    std::cin.ignore();

    std::vector<TransactionRecord> sortedRecords = records;
    std::sort(sortedRecords.begin(), sortedRecords.end(), [](const TransactionRecord &a, const TransactionRecord &b) {
        return a.date < b.date;
    });

    if (choice == 1) {
        std::reverse(sortedRecords.begin(), sortedRecords.end());
    }

    for (const TransactionRecord &record : sortedRecords) {
        std::cout << record.id << " | " << record.type << " | "
                  << record.amount << " | " << record.categoryOrSource << " | "
                  << record.date << " | " << record.description << "\n";
    }
}
