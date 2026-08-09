#include "Expense.h"

Expense::Expense() : expenseId(0), userId(0), amount(0.0), category(""), date(""), description("") {}

Expense::Expense(int expenseId, int userId, double amount, const std::string &category, const std::string &date, const std::string &description)
    : expenseId(expenseId), userId(userId), amount(amount), category(category), date(date), description(description) {}

int Expense::getExpenseId() const 
{ 
    return expenseId; 
}

int Expense::getUserId() const //user id passed from previous checks
{ 
    return userId; 
}

double Expense::getAmount() const 
{ 
    return amount; 
}

std::string Expense::getCategory() const 
{
    return category; 
}

std::string Expense::getDate() const 
{ 
    return date; 
}

std::string Expense::getDescription() const 
{ 
    return description; 
}

void Expense::setAmount(double amount) 
{ 
    this->amount = amount; 
}

void Expense::setCategory(const std::string &category) 
{ 
    this->category = category; 
}

void Expense::setDate(const std::string &date) 
{ 
    this->date = date; 
}

void Expense::setDescription(const std::string &description) 
{ 
    this->description = description; 
}