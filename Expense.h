#pragma once

#include <string>

class Expense
{
private:
    int expenseId;
    int userId;
    double amount;
    std::string category;
    std::string date;
    std::string description;

public:
    Expense();
    Expense(int expenseId, int userId, double amount,
            const std::string &category, const std::string &date,
            const std::string &description);

    int getExpenseId() const;
    int getUserId() const;
    double getAmount() const;
    std::string getCategory() const;
    std::string getDate() const;
    std::string getDescription() const;

    void setAmount(double amount);
    void setCategory(const std::string &category);
    void setDate(const std::string &date);
    void setDescription(const std::string &description);
};
