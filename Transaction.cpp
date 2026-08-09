#include "Transaction.h"

Transaction::Transaction()
{
    id = 0;
    userId = 0;
    amount = 0;
    type = TransactionType::EXPENSE;
    category = "";
    description = "";
    date = "";
}

Transaction::Transaction(int id, int userId, double amount,
                         TransactionType type,
                         std::string category,
                         std::string description,
                         std::string date)
{
    this->id = id;
    this->userId = userId;
    this->amount = amount;
    this->type = type;
    this->category = category;
    this->description = description;
    this->date = date;
}

int Transaction::getId() const
{
    return id;
}

int Transaction::getUserId() const
{
    return userId;
}

double Transaction::getAmount() const
{
    return amount;
}

TransactionType Transaction::getType() const
{
    return type;
}

std::string Transaction::getTypeAsString() const
{
    if (type == TransactionType::INCOME)
        return "INCOME";

    return "EXPENSE";
}

std::string Transaction::getCategory() const
{
    return category;
}

std::string Transaction::getDescription() const
{
    return description;
}

std::string Transaction::getDate() const
{
    return date;
}

void Transaction::setAmount(double amount)
{
    this->amount = amount;
}

void Transaction::setType(TransactionType type)
{
    this->type = type;
}

void Transaction::setCategory(const std::string &category)
{
    this->category = category;
}

void Transaction::setDescription(const std::string &description)
{
    this->description = description;
}

void Transaction::setDate(const std::string &date)
{
    this->date = date;
}