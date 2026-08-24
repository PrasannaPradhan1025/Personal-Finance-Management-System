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
    int id = fileManager.getNextTransactionId();

    Transaction transaction(
        id,
        userId,
        amount,
        type,
        category,
        description,
        date,
        0, // savingId
        0.0,
        0.0);

    transactions.push_back(transaction);

    saveTransactions();

    std::cout << "Transaction added successfully!\n";
}

void TransactionManager::addTransaction(
    double amount,
    TransactionType type,
    const std::string &category,
    const std::string &description,
    const std::string &date,
    int savingId,
    double targetAmount,
    double savedAmount)
{
    int id = fileManager.getNextTransactionId();

    Transaction transaction(
        id,
        userId,
        amount,
        type,
        category,
        description,
        date,
        savingId,
        targetAmount,
        savedAmount);

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
                  << transaction.getDate() << "\n";
        if (transaction.getType() == TransactionType::SAVING)
        {
            std::cout << "Saving ID: " << transaction.getSavingId() << "\n";
            std::cout << "Target Amount: " << transaction.getTargetAmount() << "\n";
            std::cout << "Saved Amount: " << transaction.getSavedAmount() << "\n";
        }
        std::cout << "\n";
    }
}

std::vector<Transaction> TransactionManager::getTransactions() const
{
    return transactions;
}