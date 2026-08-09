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
    TransactionManager(const std::vector<Income> &incomes,  const std::vector<Expense> &expenses, int loggedInUserId);
    //yesma income and expense both ko pass vaako xa and user kun ho check gareko pass vaako xa

    void viewTransactions() const;
    void searchTransaction() const;
    void filterByType() const;
    void filterByDate() const;
    void filterByCategory() const;
    void sortByAmount() const;
    void sortByDate() const;
};