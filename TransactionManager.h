#pragma once

#include <vector>
#include <string>
#include "Transaction.h"
#include "FileManager.h"

class TransactionManager
{
private:
    std::vector<Transaction> transactions;
    FileManager &fileManager;
    int userId;

public:
    TransactionManager(FileManager &fileManager, int userId);

    void loadTransactions();
    void saveTransactions();

    void addTransaction(double amount,
                        TransactionType type,
                        const std::string &category,
                        const std::string &description,
                        const std::string &date);

    void displayTransactions();

    std::vector<Transaction> getTransactions() const;
};