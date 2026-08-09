#include "Income.h"

Income::Income() : incomeId(0), userId(0), amount(0.0), source(""), date(""), description("") {}

Income::Income(int incomeId, int userId, double amount,
               const std::string &source, const std::string &date,
               const std::string &description)
    : incomeId(incomeId), userId(userId), amount(amount), source(source), date(date), description(description) {}

int Income::getIncomeId() const { return incomeId; }
int Income::getUserId() const { return userId; }
double Income::getAmount() const { return amount; }
std::string Income::getSource() const { return source; }
std::string Income::getDate() const { return date; }
std::string Income::getDescription() const { return description; }

void Income::setAmount(double amount) { this->amount = amount; }
void Income::setSource(const std::string &source) { this->source = source; }
void Income::setDate(const std::string &date) { this->date = date; }
void Income::setDescription(const std::string &description) { this->description = description; }
