#pragma once

#include <vector>
#include "Transaction.h"

class Statistics
{
private:
    std::vector<Transaction> transactions;

public:
    explicit Statistics(const std::vector<Transaction>& transactions);

    double getTotalIncome() const;
    double getTotalExpenses() const;
    double getNetIncome() const;
    double getCurrentBalance() const;
    int getTotalTransactions() const;
    double getSavingsRate() const;

    void displayFinancialSummary() const;
};
