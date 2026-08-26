#include "Statistics.h"

#include <iostream>

Statistics::Statistics(const std::vector<Transaction>& transactions)
    : transactions(transactions)
{
}

double Statistics::getTotalIncome() const
{
    double total = 0.0;
    for (const Transaction& transaction : transactions)
    {
        if (transaction.getType() == TransactionType::INCOME)
        {
            total += transaction.getAmount();
        }
    }
    return total;
}

double Statistics::getTotalExpenses() const
{
    double total = 0.0;
    for (const Transaction& transaction : transactions)
    {
        if (transaction.getType() == TransactionType::EXPENSE)
        {
            total += transaction.getAmount();
        }
    }
    return total;
}

double Statistics::getNetIncome() const
{
    return getTotalIncome() - getTotalExpenses();
}

double Statistics::getCurrentBalance() const
{
    return getNetIncome();
}

int Statistics::getTotalTransactions() const
{
    return static_cast<int>(transactions.size());
}

double Statistics::getSavingsRate() const
{
    const double income = getTotalIncome();
    return income == 0.0 ? 0.0 : getNetIncome() / income * 100.0;
}

void Statistics::displayFinancialSummary() const
{
    std::cout << "\nFinancial Summary\n"
              << "Total income: " << getTotalIncome() << '\n'
              << "Total expenses: " << getTotalExpenses() << '\n'
              << "Current balance: " << getCurrentBalance() << '\n'
              << "Transactions: " << getTotalTransactions() << '\n'
              << "Savings rate: " << getSavingsRate() << "%\n";
}
