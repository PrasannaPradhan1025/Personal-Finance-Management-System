#pragma once

#include <string>
#include <vector>
#include "Expense.h"
#include "Income.h"

class TransactionManager
{
private:
    std::vector<Income> incomes;
    std::vector<Expense> expenses;
    int loggedInUserId;

public:
    TransactionManager(const std::vector<Income> &incomes,
                       const std::vector<Expense> &expenses,
                       int loggedInUserId);

    void viewTransactions() const;
    void searchTransaction() const;
    void filterByType() const;
    void filterByDate() const;
    void filterByCategory() const;
    void sortByAmount() const;
    void sortByDate() const;
};
