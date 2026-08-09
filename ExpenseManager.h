#pragma once

#include <string>
#include <vector>
#include "Expense.h"

class ExpenseManager
{
private:
    std::string filename;
    std::vector<Expense> expenses;
    int loggedInUserId;

public:
    ExpenseManager(const std::string &filename, int loggedInUserId);

    void loadExpenses();
    void saveExpenses();
    void addExpense();
    void viewExpenses();
    void updateExpense();
    void deleteExpense();
    void searchExpense();
    double getTotalExpenses();

    bool isValidDate(const std::string &date);
    bool isValidAmount(double amount);
    int getNextExpenseId();
    std::vector<Expense> getExpensesForCurrentUser() const;
};
