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
    savingId = 0;
    targetAmount = 0.0;
    savedAmount = 0.0;
}

Transaction::Transaction(int id, int userId, double amount,
                         TransactionType type,
                         std::string category,
                         std::string description,
                         std::string date,
                         int savingId,
                         double targetAmount,
                         double savedAmount)
{
    this->id = id;
    this->userId = userId;
    this->amount = amount;
    this->type = type;
    this->category = category;
    this->description = description;
    this->date = date;
    this->savingId = savingId;
    this->targetAmount = targetAmount;
    this->savedAmount = savedAmount;
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
    if (type == TransactionType::EXPENSE)
        return "EXPENSE";

    return "SAVING";
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

// saving-specific getters
int Transaction::getSavingId() const { return savingId; }
double Transaction::getTargetAmount() const { return targetAmount; }
double Transaction::getSavedAmount() const { return savedAmount; }

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

// saving-specific setters
void Transaction::setSavingId(int id) { this->savingId = id; }
void Transaction::setTargetAmount(double amt) { this->targetAmount = amt; }
void Transaction::setSavedAmount(double amt) { this->savedAmount = amt; }