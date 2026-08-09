#pragma once

#include <string>
#include <vector>
#include "Income.h"
#include "User.h"

class IncomeManager
{
private:
    std::string filename;
    std::vector<Income> incomes;
    int loggedInUserId;

public:
    IncomeManager(const std::string &filename, int loggedInUserId);

    void loadIncome();
    void saveIncome();
    void addIncome();
    void viewIncome();
    void updateIncome();
    void deleteIncome();
    void searchIncome();
    double getTotalIncome();

    bool isValidDate(const std::string &date);
    bool isValidAmount(double amount);
    int getNextIncomeId();
    std::vector<Income> getIncomeForCurrentUser() const;
};
