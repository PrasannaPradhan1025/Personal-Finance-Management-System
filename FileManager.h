#pragma once

#include <vector>
#include <string>
#include "Transaction.h"

class FileManager
{
private:
    std::string transactionFilename;

public:
    FileManager(const std::string &transactionFilename);

    std::vector<Transaction> loadTransactions(int userId);

    void saveTransactions(
        const std::vector<Transaction> &transactions, int userId);

    int getNextTransactionId();
};