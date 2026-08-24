#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

FileManager::FileManager(const std::string &transactionFilename)
    : transactionFilename(transactionFilename)
{
}

std::vector<Transaction> FileManager::loadTransactions(int userId)
{
    std::vector<Transaction> transactions;

    std::ifstream file(transactionFilename);

    if (!file.is_open())
    {
        return transactions;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::stringstream ss(line);

        std::string id;
        std::string storedUserId;
        std::string amount;
        std::string type;
        std::string category;
        std::string description;
        std::string date;
        std::string savingIdStr;
        std::string targetAmountStr;
        std::string savedAmountStr;

        std::getline(ss, id, '|');
        std::getline(ss, storedUserId, '|');
        std::getline(ss, amount, '|');
        std::getline(ss, type, '|');
        std::getline(ss, category, '|');
        std::getline(ss, description, '|');
        std::getline(ss, date, '|');

        // optional saving-specific fields
        std::getline(ss, savingIdStr, '|');
        std::getline(ss, targetAmountStr, '|');
        std::getline(ss, savedAmountStr, '|');

        try
        {
            if (std::stoi(storedUserId) == userId)
            {
                TransactionType transactionType;

                if (type == "INCOME")
                {
                    transactionType = TransactionType::INCOME;
                }
                else if (type == "EXPENSE")
                {
                    transactionType = TransactionType::EXPENSE;
                }
                else // SAVING or unknown
                {
                    transactionType = TransactionType::SAVING;
                }

                int savingId = 0;
                double targetAmt = 0.0;
                double savedAmt = 0.0;

                if (!savingIdStr.empty())
                {
                    try { savingId = std::stoi(savingIdStr); } catch(...) { savingId = 0; }
                }
                if (!targetAmountStr.empty())
                {
                    try { targetAmt = std::stod(targetAmountStr); } catch(...) { targetAmt = 0.0; }
                }
                if (!savedAmountStr.empty())
                {
                    try { savedAmt = std::stod(savedAmountStr); } catch(...) { savedAmt = 0.0; }
                }

                Transaction transaction(
                    std::stoi(id),
                    std::stoi(storedUserId),
                    std::stod(amount),
                    transactionType,
                    category,
                    description,
                    date,
                    savingId,
                    targetAmt,
                    savedAmt);

                transactions.push_back(transaction);
            }
        }
        catch (const std::exception &)
        {
            std::cout << "Warning: skipping malformed transaction line.\n";
            continue;
        }
    }

    file.close();

    return transactions;
}

void FileManager::saveTransactions(
    const std::vector<Transaction> &transactions, int userId)
{
    std::vector<Transaction> allTransactions;

    std::ifstream inputFile(transactionFilename);

    if (inputFile.is_open())
    {
        std::string line;

        while (std::getline(inputFile, line))
        {
            if (line.empty())
            {
                continue;
            }

            std::stringstream ss(line);

            std::string id;
            std::string storedUserId;
            std::string amount;
            std::string type;
            std::string category;
            std::string description;
            std::string date;

            std::getline(ss, id, '|');
            std::getline(ss, storedUserId, '|');
            std::getline(ss, amount, '|');
            std::getline(ss, type, '|');
            std::getline(ss, category, '|');
            std::getline(ss, description, '|');
            std::getline(ss, date, '|');

            try
            {
                TransactionType transactionType;

                if (type == "INCOME")
                {
                    transactionType = TransactionType::INCOME;
                }
                else if (type == "EXPENSE")
                {
                    transactionType = TransactionType::EXPENSE;
                }
                else
                {
                    transactionType = TransactionType::SAVING;
                }

                // try to read optional saving fields
                std::string savingIdStr;
                std::string targetAmountStr;
                std::string savedAmountStr;
                std::getline(ss, savingIdStr, '|');
                std::getline(ss, targetAmountStr, '|');
                std::getline(ss, savedAmountStr, '|');

                int savingId = 0;
                double targetAmt = 0.0;
                double savedAmt = 0.0;

                if (!savingIdStr.empty()) { try { savingId = std::stoi(savingIdStr); } catch(...) { savingId = 0; } }
                if (!targetAmountStr.empty()) { try { targetAmt = std::stod(targetAmountStr); } catch(...) { targetAmt = 0.0; } }
                if (!savedAmountStr.empty()) { try { savedAmt = std::stod(savedAmountStr); } catch(...) { savedAmt = 0.0; } }

                Transaction transaction(
                    std::stoi(id),
                    std::stoi(storedUserId),
                    std::stod(amount),
                    transactionType,
                    category,
                    description,
                    date,
                    savingId,
                    targetAmt,
                    savedAmt);

                allTransactions.push_back(transaction);
            }
            catch (const std::exception &)
            {
                std::cout << "Warning: skipping malformed transaction line.\n";
                continue;
            }
        }
        inputFile.close();
    }
    std::vector<Transaction> updatedTransactions;

    // Keep transactions belonging to other users.
    for (const Transaction &transaction : allTransactions)
    {
        if (transaction.getUserId() != userId)
        {
            updatedTransactions.push_back(transaction);
        }
    }

    // Add the current user's transactions.
    for (const Transaction &transaction : transactions)
    {
        updatedTransactions.push_back(transaction);
    }

    std::ofstream file(transactionFilename);

    if (!file.is_open())
    {
        std::cout << "Unable to save transactions.\n";
        return;
    }

    for (const Transaction &transaction : updatedTransactions)
    {
        file << transaction.getId() << "|"
             << transaction.getUserId() << "|"
             << transaction.getAmount() << "|";

        if (transaction.getType() == TransactionType::INCOME)
        {
            file << "INCOME|";
        }
        else if (transaction.getType() == TransactionType::EXPENSE)
        {
            file << "EXPENSE|";
        }
        else // SAVING
        {
            file << "SAVING|";
        }

        file << transaction.getCategory() << "|"
             << transaction.getDescription() << "|"
             << transaction.getDate() << "|";

        // If saving, append saving fields; otherwise write empty placeholders for compatibility
        if (transaction.getType() == TransactionType::SAVING)
        {
            file << transaction.getSavingId() << "|"
                 << transaction.getTargetAmount() << "|"
                 << transaction.getSavedAmount() << "\n";
        }
        else
        {
            file << "|" << "|" << "\n"; // placeholders to keep field positions
        }
    }

    file.close();
}

int FileManager::getNextTransactionId()
{
    std::ifstream file(transactionFilename);

    if (!file.is_open())
    {
        return 1;
    }

    int highestId = 0;
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string id;
        std::getline(ss, id, '|');

        try
        {
            int currentId = std::stoi(id);
            if (currentId > highestId)
            {
                highestId = currentId;
            }
        }
        catch (const std::exception &)
        {
            continue;
        }
    }

    file.close();

    return highestId + 1;
}