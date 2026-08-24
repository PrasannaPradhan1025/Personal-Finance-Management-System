#include "Statistics.h"
#include "FileManager.h"
#include "Transaction.h"
#include <vector>
#include <algorithm>
#include <iostream>

static std::vector<Transaction> loadUserTransactions(int userId)
{
    FileManager fm("Trans.txt");
    return fm.loadTransactions(userId);
}

Statistics::Statistics()
{
    userId = 0;
}

Statistics::Statistics(int userId)
{
    this->userId = userId;
}

double Statistics::getTotalIncome()
{
    auto transactions = loadUserTransactions(userId);
    double sum = 0.0;
    for (const auto &t : transactions)
    {
        if (t.getType() == TransactionType::INCOME)
            sum += t.getAmount();
    }
    return sum;
}

double Statistics::getTotalExpenses()
{
    auto transactions = loadUserTransactions(userId);
    double sum = 0.0;
    for (const auto &t : transactions)
    {
        if (t.getType() == TransactionType::EXPENSE)
            sum += t.getAmount();
    }
    return sum;
}

double Statistics::getNetIncome()
{
    return getTotalIncome() - getTotalExpenses();
}

double Statistics::getTotalSavings()
{
    auto transactions = loadUserTransactions(userId);
    double sum = 0.0;
    for (const auto &t : transactions)
    {
        if (t.getType() == TransactionType::SAVING)
            sum += t.getSavedAmount();
    }
    return sum;
}

double Statistics::getCurrentBalance()
{
    // Define current balance as income - expense - saved amounts (funds put into savings)
    return getTotalIncome() - getTotalExpenses() - getTotalSavings();
}

int Statistics::getTotalTransactions()
{
    auto transactions = loadUserTransactions(userId);
    return static_cast<int>(transactions.size());
}

int Statistics::getIncomeTransactionCount()
{
    auto transactions = loadUserTransactions(userId);
    return static_cast<int>(std::count_if(transactions.begin(), transactions.end(), [](const Transaction &t){ return t.getType() == TransactionType::INCOME; }));
}

int Statistics::getExpenseTransactionCount()
{
    auto transactions = loadUserTransactions(userId);
    return static_cast<int>(std::count_if(transactions.begin(), transactions.end(), [](const Transaction &t){ return t.getType() == TransactionType::EXPENSE; }));
}

double Statistics::getAverageIncome()
{
    double total = getTotalIncome();
    int cnt = getIncomeTransactionCount();
    if (cnt == 0) return 0.0;
    return total / cnt;
}

double Statistics::getAverageExpense()
{
    double total = getTotalExpenses();
    int cnt = getExpenseTransactionCount();
    if (cnt == 0) return 0.0;
    return total / cnt;
}

double Statistics::getLargestIncome()
{
    auto transactions = loadUserTransactions(userId);
    double largest = 0.0;
    bool found = false;
    for (const auto &t : transactions)
    {
        if (t.getType() == TransactionType::INCOME)
        {
            if (!found || t.getAmount() > largest)
            {
                largest = t.getAmount();
                found = true;
            }
        }
    }
    return found ? largest : 0.0;
}

double Statistics::getSmallestIncome()
{
    auto transactions = loadUserTransactions(userId);
    double smallest = 0.0;
    bool found = false;
    for (const auto &t : transactions)
    {
        if (t.getType() == TransactionType::INCOME)
        {
            if (!found || t.getAmount() < smallest)
            {
                smallest = t.getAmount();
                found = true;
            }
        }
    }
    return found ? smallest : 0.0;
}

double Statistics::getLargestExpense()
{
    auto transactions = loadUserTransactions(userId);
    double largest = 0.0;
    bool found = false;
    for (const auto &t : transactions)
    {
        if (t.getType() == TransactionType::EXPENSE)
        {
            if (!found || t.getAmount() > largest)
            {
                largest = t.getAmount();
                found = true;
            }
        }
    }
    return found ? largest : 0.0;
}

double Statistics::getSmallestExpense()
{
    auto transactions = loadUserTransactions(userId);
    double smallest = 0.0;
    bool found = false;
    for (const auto &t : transactions)
    {
        if (t.getType() == TransactionType::EXPENSE)
        {
            if (!found || t.getAmount() < smallest)
            {
                smallest = t.getAmount();
                found = true;
            }
        }
    }
    return found ? smallest : 0.0;
}

int Statistics::getTransactionCountByType(const string &typeStr)
{
    auto transactions = loadUserTransactions(userId);
    TransactionType ty = TransactionType::EXPENSE;
    if (typeStr == "INCOME") ty = TransactionType::INCOME;
    else if (typeStr == "SAVING") ty = TransactionType::SAVING;
    else if (typeStr == "EXPENSE") ty = TransactionType::EXPENSE;

    return static_cast<int>(std::count_if(transactions.begin(), transactions.end(), [&](const Transaction &t){ return t.getType() == ty; }));
}

int Statistics::getTransactionCountByCategory(const string &category)
{
    auto transactions = loadUserTransactions(userId);
    return static_cast<int>(std::count_if(transactions.begin(), transactions.end(), [&](const Transaction &t){ return t.getCategory() == category; }));
}

int Statistics::getTransactionCountByDate(const string &date)
{
    auto transactions = loadUserTransactions(userId);
    return static_cast<int>(std::count_if(transactions.begin(), transactions.end(), [&](const Transaction &t){ return t.getDate() == date; }));
}

double Statistics::getAverageTransactionAmount()
{
    auto transactions = loadUserTransactions(userId);
    if (transactions.empty()) return 0.0;
    double sum = 0.0;
    for (const auto &t : transactions) sum += t.getAmount();
    return sum / transactions.size();
}

double Statistics::getLargestTransaction()
{
    auto transactions = loadUserTransactions(userId);
    if (transactions.empty()) return 0.0;
    double largest = transactions.front().getAmount();
    for (const auto &t : transactions) largest = std::max(largest, t.getAmount());
    return largest;
}

double Statistics::getSmallestTransaction()
{
    auto transactions = loadUserTransactions(userId);
    if (transactions.empty()) return 0.0;
    double smallest = transactions.front().getAmount();
    for (const auto &t : transactions) smallest = std::min(smallest, t.getAmount());
    return smallest;
}

// Savings-related helpers

double Statistics::getRemainingSavingsAmount(int savingsId)
{
    auto transactions = loadUserTransactions(userId);
    for (const auto &t : transactions)
    {
        if (t.getType() == TransactionType::SAVING && t.getSavingId() == savingsId)
        {
            return std::max(0.0, t.getTargetAmount() - t.getSavedAmount());
        }
    }
    return 0.0;
}

int Statistics::getTotalSavingsGoals()
{
    auto transactions = loadUserTransactions(userId);
    std::vector<int> ids;
    for (const auto &t : transactions)
    {
        if (t.getType() == TransactionType::SAVING)
        {
            if (std::find(ids.begin(), ids.end(), t.getSavingId()) == ids.end())
                ids.push_back(t.getSavingId());
        }
    }
    return static_cast<int>(ids.size());
}

int Statistics::getCompletedSavingsGoals()
{
    auto transactions = loadUserTransactions(userId);
    int count = 0;
    for (const auto &t : transactions)
    {
        if (t.getType() == TransactionType::SAVING && t.getTargetAmount() > 0)
        {
            if (t.getSavedAmount() >= t.getTargetAmount()) count++;
        }
    }
    return count;
}

int Statistics::getIncompleteSavingsGoals()
{
    int total = getTotalSavingsGoals();
    int completed = getCompletedSavingsGoals();
    return total - completed;
}

double Statistics::getAverageSavingsProgress()
{
    auto transactions = loadUserTransactions(userId);
    double sumProgress = 0.0;
    int count = 0;
    for (const auto &t : transactions)
    {
        if (t.getType() == TransactionType::SAVING && t.getTargetAmount() > 0)
        {
            sumProgress += (t.getSavedAmount() / t.getTargetAmount()) * 100.0;
            count++;
        }
    }
    if (count == 0) return 0.0;
    return sumProgress / count;
}

// Financial ratios

double Statistics::getSavingsRate()
{
    double totalIncome = getTotalIncome();
    if (totalIncome == 0.0) return 0.0;
    double net = getNetIncome();
    return (net / totalIncome) * 100.0;
}

double Statistics::getExpenseRatio()
{
    double totalIncome = getTotalIncome();
    if (totalIncome == 0.0) return 0.0;
    return (getTotalExpenses() / totalIncome) * 100.0;
}

double Statistics::getIncomeExpenseRatio()
{
    double totalExpenses = getTotalExpenses();
    if (totalExpenses == 0.0) return 0.0;
    return getTotalIncome() / totalExpenses;
}

void Statistics::displayFinancialSummary()
{
    std::cout << "--- Financial Summary for User " << userId << " ---\n";
    std::cout << "Total Income: " << getTotalIncome() << "\n";
    std::cout << "Total Expenses: " << getTotalExpenses() << "\n";
    std::cout << "Total Savings (saved amounts): " << getTotalSavings() << "\n";
    std::cout << "Net Income: " << getNetIncome() << "\n";
    std::cout << "Current Balance: " << getCurrentBalance() << "\n";
    std::cout << "Savings Rate (%): " << getSavingsRate() << "\n";
    std::cout << "Expense Ratio (%): " << getExpenseRatio() << "\n";
}


double Statistics::accountHealth()
{
    // Simple heuristic: combination of savings rate and expense ratio
    double sr = getSavingsRate();
    double er = getExpenseRatio();
    // higher is better, so return savings rate minus expense ratio
    return sr - er;
}

// ----------------- Stubbed / not-yet-implemented functions -----------------
// These provide safe defaults so the program links and can be extended later.

double Statistics::getIncomeBySource(const string &source) { return 0.0; }
double Statistics::getIncomePercentageBySource(const string &source) { return 0.0; }
string Statistics::getHighestIncomeSource() { return string(); }
string Statistics::getLowestIncomeSource() { return string(); }
int Statistics::getIncomeSourceCount() { return 0; }
int Statistics::getMostFrequentIncomeSource() { return 0; }
double Statistics::getAverageIncomeBySource(const string &source) { return 0.0; }

double Statistics::getExpensesByCategory(const string &category) { return 0.0; }
double Statistics::getExpensePercentageByCategory(const string &category) { return 0.0; }
string Statistics::getHighestSpendingCategory() { return string(); }
string Statistics::getLowestSpendingCategory() { return string(); }
int Statistics::getExpenseCategoryCount() { return 0; }
string Statistics::getMostFrequentExpenseCategory() { return string(); }
double Statistics::getAverageExpenseByCategory(const string &category) { return 0.0; }

double Statistics::getMonthlyIncome(int month, int year) { return 0.0; }
double Statistics::getMonthlyExpenses(int month, int year) { return 0.0; }
double Statistics::getMonthlyNetIncome(int month, int year) { return 0.0; }
int Statistics::getMonthlyTransactionCount(int month, int year) { return 0; }
double Statistics::getAverageMonthlyIncome(int year) { return 0.0; }
double Statistics::getAverageMonthlyExpenses(int year) { return 0.0; }
double Statistics::getHighestMonthlyIncome(int year) { return 0.0; }
double Statistics::getLowestMonthlyIncome(int year) { return 0.0; }
double Statistics::getHighestMonthlyExpenses(int year) { return 0.0; }
double Statistics::getLowestMonthlyExpenses(int year) { return 0.0; }
int Statistics::getHighestSpendingMonth(int year) { return 0; }
int Statistics::getLowestSpendingMonth(int year) { return 0; }

double Statistics::getYearlyIncome(int year) { return 0.0; }
double Statistics::getYearlyExpenses(int year) { return 0.0; }
double Statistics::getYearlyNetIncome(int year) { return 0.0; }
int Statistics::getYearlyTransactionCount(int year) { return 0; }
double Statistics::getAverageYearlyIncome() { return 0.0; }
double Statistics::getAverageYearlyExpenses() { return 0.0; }
int Statistics::getHighestIncomeYear() { return 0; }
int Statistics::getHighestExpenseYear() { return 0; }

double Statistics::getCashFlow() { return getNetIncome(); }
double Statistics::getMonthlyCashFlow(int month, int year) { return 0.0; }
double Statistics::getAverageCashFlow(int year) { return 0.0; }
double Statistics::getHighestPositiveCashFlow(int year) { return 0.0; }
double Statistics::getLargestNegativeCashFlow(int year) { return 0.0; }

double Statistics::getTotalBudget() { return 0.0; }
double Statistics::getTotalBudgetSpent() { return 0.0; }
double Statistics::getTotalRemainingBudget() { return 0.0; }
double Statistics::getBudgetUsagePercentage() { return 0.0; }
double Statistics::getCategoryBudgetUsage(const string &category) { return 0.0; }
int Statistics::getExceededBudgetCount() { return 0; }
int Statistics::getWithinBudgetCount() { return 0; }
double Statistics::getAverageBudgetUsage() { return 0.0; }

int Statistics::getMostActiveMonth(int year) { return 0; }

double Statistics::getCategoryExpensePercentage(const string &category) { return 0.0; }
double Statistics::getIncomeSourcePercentage(const string &source) { return 0.0; }

double Statistics::getIncomeGrowth(int currentMonth, int currentYear) { return 0.0; }
double Statistics::getExpenseGrowth(int currentMonth, int currentYear) { return 0.0; }
double Statistics::getSavingsGrowth(int currentMonth, int currentYear) { return 0.0; }
