#pragma once

#include <string>

class Income
{
private:
    int incomeId;
    int userId;
    double amount;
    std::string source;
    std::string date;
    std::string description;

public:
    Income();
    Income(int incomeId, int userId, double amount,
           const std::string &source, const std::string &date,
           const std::string &description);

    int getIncomeId() const;
    int getUserId() const;
    double getAmount() const;
    std::string getSource() const;
    std::string getDate() const;
    std::string getDescription() const;

    void setAmount(double amount);
    void setSource(const std::string &source);
    void setDate(const std::string &date);
    void setDescription(const std::string &description);
};
