#include "TransactionManager.h"
#include <iostream>
#include <cctype>
#include <cmath>

namespace
{
bool validDate(const std::string &date)
{
    if (date.size() != 10 || date[2] != '-' || date[5] != '-')
        return false;

    for (size_t index = 0; index < date.size(); ++index)
    {
        if (index != 2 && index != 5 && !std::isdigit(static_cast<unsigned char>(date[index])))
            return false;
    }

    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));
    return year >= 1 && month >= 1 && month <= 12 && day >= 1 && day <= 31;
}

bool validTransaction(double amount, const std::string &category,
                      const std::string &description, const std::string &date)
{
    return std::isfinite(amount) && amount > 0.0 && !category.empty() &&
           !description.empty() && category.find('|') == std::string::npos &&
           description.find('|') == std::string::npos && validDate(date);
}
}

TransactionManager::TransactionManager(
    FileManager &fileManager,
    int userId)
    : fileManager(fileManager), userId(userId)
{
    loadTransactions();
}

void TransactionManager::loadTransactions()
{
    transactions = fileManager.loadTransactions(userId);
}

void TransactionManager::saveTransactions()
{
    fileManager.saveTransactions(transactions, userId);
}
bool TransactionManager::deleteTransaction(int transactionId)
{
    for (auto it = transactions.begin(); it != transactions.end(); ++it)
    {
        if (it->getId() == transactionId)
        {
            transactions.erase(it);
            saveTransactions();
            std::cout << "Transaction deleted successfully!\n";
            return true;
        }
    }

    std::cout << "Transaction not found.\n";
    return false;
}
void TransactionManager::addTransaction(
    double amount,
    TransactionType type,
    const std::string &category,
    const std::string &description,
    const std::string &date)
{
    if (!validTransaction(amount, category, description, date))
    {
        std::cout << "Invalid transaction. Use a positive amount, non-empty text, and date DD-MM-YYYY.\n";
        return;
    }

    int id = fileManager.getNextTransactionId();

    Transaction transaction(
        id,
        userId,
        amount,
        type,
        category,
        description,
        date);

    transactions.push_back(transaction);

    saveTransactions();

    std::cout << "Transaction added successfully!\n";
}

void TransactionManager::displayTransactions()
{
    displayTransactions(transactions);
}

void TransactionManager::displayTransactions(const std::vector<Transaction> &items) const
{
    if (items.empty())
    {
        std::cout << "No transactions found.\n";
        return;
    }

    for (const Transaction &transaction : transactions)
    {
        std::cout << "ID: " << transaction.getId() << '\n';
        std::cout << "User ID: " << transaction.getUserId() << '\n';
        std::cout << "Amount: " << transaction.getAmount() << '\n';
        std::cout << "Type: "
                  << transaction.getTypeAsString() << '\n';
        std::cout << "Category: "
                  << transaction.getCategory() << '\n';
        std::cout << "Description: "
                  << transaction.getDescription() << '\n';
        std::cout << "Date: "
                  << transaction.getDate() << "\n\n";
    }
}

std::vector<Transaction> TransactionManager::getTransactions() const
{
    return transactions;
}

bool TransactionManager::updateTransaction(
    int transactionId,
    double amount,
    TransactionType type,
    const std::string &category,
    const std::string &description,
    const std::string &date)
{
    if (!validTransaction(amount, category, description, date))
    {
        std::cout << "Invalid transaction. Use a positive amount, non-empty text, and date DD-MM-YYYY.\n";
        return false;
    }

    for (Transaction &transaction : transactions)
    {
        if (transaction.getId() == transactionId)
        {
            transaction.setAmount(amount);
            transaction.setType(type);
            transaction.setCategory(category);
            transaction.setDescription(description);
            transaction.setDate(date);
            saveTransactions();
            std::cout << "Transaction updated successfully!\n";
            return true;
        }
    }

    std::cout << "Transaction not found.\n";
    return false;
}

std::vector<Transaction> TransactionManager::searchTransactions(const std::string &keyword) const
{
    std::vector<Transaction> results;
    for (const Transaction &transaction : transactions)
    {
        if (transaction.getCategory().find(keyword) != std::string::npos ||
            transaction.getDescription().find(keyword) != std::string::npos ||
            transaction.getDate().find(keyword) != std::string::npos)
        {
            results.push_back(transaction);
        }
    }
    return results;
}