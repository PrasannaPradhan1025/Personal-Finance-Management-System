#include "TransactionManager.h"
#include <iostream>

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
    fileManager.saveTransactions(transactions);
}

void TransactionManager::addTransaction(
    double amount,
    TransactionType type,
    const std::string &category,
    const std::string &description,
    const std::string &date)
{
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
    if (transactions.empty())
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