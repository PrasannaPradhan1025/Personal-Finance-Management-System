#include <iostream>
#include <string>

#include "AuthSystem.h"
#include "FileManager.h"
#include "Statistics.h"
#include "TransactionManager.h"
#include "UserManager.h"
#include "utils.h"

namespace
{
bool readTransactionDetails(double &amount, TransactionType &type,
                            std::string &category, std::string &description,
                            std::string &date)
{
    if (!readAmount("Enter amount: ", amount) || amount <= 0.0)
    {
        std::cout << "Amount must be greater than zero.\n";
        return false;
    }

    int typeChoice;
    if (!readInt("1. Income\n2. Expense\nEnter type: ", typeChoice) ||
        (typeChoice != 1 && typeChoice != 2))
    {
        std::cout << "Invalid transaction type.\n";
        return false;
    }
    type = typeChoice == 1 ? TransactionType::INCOME : TransactionType::EXPENSE;

    category = readText("Enter category: ");
    description = readText("Enter description: ");
    date = readText("Enter date (DD-MM-YYYY): ");
    return true;
}

void pauseAndClear()
{
    pauseScreen();
    clearScreen();
}
}

int main()
{
    UserManager userManager("Users.txt");
    AuthSystem auth(userManager);

    while (true)
    {
        clearScreen();
        std::cout << "\n==== Finance Manager ====\n"
                  << "1. Login\n"
                  << "2. Sign Up\n"
                  << "3. Exit\n";

        int choice;
        if (!readInt("Choose an option: ", choice))
        {
            pauseAndClear();
            continue;
        }

        if (choice == 3)
            return 0;

        if (choice == 2)
        {
            std::string username = readText("Enter username: ");
            std::string password;
            int signupChoice;

            if (!readInt("1. Enter my own password\n2. Generate a strong password\nChoose an option: ", signupChoice))
            {
                pauseAndClear();
                continue;
            }

            if (signupChoice == 1)
            {
                password = readText("Enter password: ");
            }
            else if (signupChoice == 2)
            {
                int length;
                if (!readInt("Enter password length: ", length))
                {
                    pauseAndClear();
                    continue;
                }
                if (length < 6)
                    length = 8;
                password = generateStrongPassword(length);
                std::cout << "Generated strong password: " << password << '\n';
            }
            else
            {
                std::cout << "Invalid signup option.\n";
                pauseAndClear();
                continue;
            }

            if (auth.signup(username, password))
                std::cout << "Signup successful!\n";
            else
                std::cout << "Signup failed. Check the username and password requirements.\n";
            pauseAndClear();
            continue;
        }

        if (choice != 1)
        {
            std::cout << "Invalid choice.\n";
            pauseAndClear();
            continue;
        }

        std::string username = readText("Enter username: ");
        std::string password = readText("Enter password: ");
        if (!auth.login(username, password))
        {
            std::cout << "Invalid username or password.\n";
            pauseAndClear();
            continue;
        }

        std::cout << "Login successful! Welcome, " << auth.getCurrentUser()->getUsername() << "!\n";
        FileManager fileManager("Trans.txt");
        TransactionManager transactionManager(fileManager, auth.getCurrentUser()->getId());

        bool loggedIn = true;
        while (loggedIn)
        {
            std::cout << "\n==== Personal Finance Menu ====\n"
                      << "1. View Profile\n"
                      << "2. View Transactions\n"
                      << "3. Add Transaction\n"
                      << "4. Edit Transaction\n"
                      << "5. Delete Transaction\n"
                      << "6. Search Transactions\n"
                      << "7. Financial Summary\n"
                      << "8. Logout\n";

            int financeChoice;
            if (!readInt("Choose an option: ", financeChoice))
            {
                pauseAndClear();
                continue;
            }

            switch (financeChoice)
            {
            case 1:
                std::cout << "\nUser Profile\nUsername: " << auth.getCurrentUser()->getUsername()
                          << "\nUser ID: " << auth.getCurrentUser()->getId() << '\n';
                break;
            case 2:
                transactionManager.displayTransactions();
                break;
            case 3:
            {
                double amount;
                TransactionType type;
                std::string category, description, date;
                if (readTransactionDetails(amount, type, category, description, date))
                    transactionManager.addTransaction(amount, type, category, description, date);
                break;
            }
            case 4:
            {
                transactionManager.displayTransactions();
                int id;
                if (readInt("Enter transaction ID to edit: ", id))
                {
                    double amount;
                    TransactionType type;
                    std::string category, description, date;
                    if (readTransactionDetails(amount, type, category, description, date))
                        transactionManager.updateTransaction(id, amount, type, category, description, date);
                }
                break;
            }
            case 5:
            {
                transactionManager.displayTransactions();
                int id;
                if (readInt("Enter transaction ID to delete: ", id))
                    transactionManager.deleteTransaction(id);
                break;
            }
            case 6:
            {
                std::string keyword = readText("Search category, description, or date: ");
                transactionManager.displayTransactions(transactionManager.searchTransactions(keyword));
                break;
            }
            case 7:
            {
                Statistics statistics(transactionManager.getTransactions());
                statistics.displayFinancialSummary();
                break;
            }
            case 8:
                auth.logout();
                loggedIn = false;
                std::cout << "Logged out successfully!\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
                break;
            }

            if (loggedIn)
                pauseAndClear();
        }
    }
}
