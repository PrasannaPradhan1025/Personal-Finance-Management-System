#pragma once
#include <string>
using namespace std;

class Statistics
{
private:
    int userId;//yeta baata user sanga link garni
    
public:
    
    Statistics();
    Statistics(int userId);

    double getTotalIncome();

    double getTotalExpenses();

    double getNetIncome();

    double getCurrentBalance();

    int getTotalTransactions();

    int getIncomeTransactionCount();

    int getExpenseTransactionCount();

    double getAverageIncome();

    double getAverageExpense();

    double getLargestIncome();

    double getSmallestIncome();

    double getLargestExpense();

    double getSmallestExpense();

    //STATISTICS and functions paaxi implement garna
    double getIncomeBySource(const string& source);//kata ko kun feild ko income and paaxi transaction ko banepaaxi logic halni

    double getIncomePercentageBySource(const string& source);

    string getHighestIncomeSource();
    string getLowestIncomeSource();

    int getIncomeSourceCount();
    int getMostFrequentIncomeSource();


    double getAverageIncomeBySource(const string& source);

    // Same thing as income ko for expenses
    double getExpensesByCategory(const string& category);

    double getExpensePercentageByCategory(const string& category);

    string getHighestSpendingCategory();
    string getLowestSpendingCategory();

    int getExpenseCategoryCount();
    string getMostFrequentExpenseCategory();

    double getAverageExpenseByCategory(const string& category);

    // Time clasiify garepaxi transaction ma link garni yo
    double getMonthlyIncome(int month, int year);
    double getMonthlyExpenses(int month, int year);

    double getMonthlyNetIncome(int month, int year);
    int getMonthlyTransactionCount(int month, int year);
    double getAverageMonthlyIncome(int year);


    double getAverageMonthlyExpenses(int year);

    double getHighestMonthlyIncome(int year);
    double getLowestMonthlyIncome(int year);


    double getHighestMonthlyExpenses(int year);
    double getLowestMonthlyExpenses(int year);


    int getHighestSpendingMonth(int year);
    int getLowestSpendingMonth(int year);

    // Same thing yearly summary
    double getYearlyIncome(int year);
    double getYearlyExpenses(int year);

    double getYearlyNetIncome(int year);

    int getYearlyTransactionCount(int year);

    double getAverageYearlyIncome();
    double getAverageYearlyExpenses();

    int getHighestIncomeYear();
    int getHighestExpenseYear();

    // Income and expenses dubai vayepaxi garni kaam
    double getCashFlow();
    double getMonthlyCashFlow(int month, int year);

    double getAverageCashFlow(int year);

    double getHighestPositiveCashFlow(int year);
    double getLargestNegativeCashFlow(int year);

    // Savings ko stats
    double getTotalSavings();

    double getRemainingSavingsAmount(int savingsId);

    int getTotalSavingsGoals();

    int getCompletedSavingsGoals();

    int getIncompleteSavingsGoals();

    double getAverageSavingsProgress();

    double getSavingsRate();

    // Hamro budget save garni waala yo for each category function banauni
    double getTotalBudget();

    double getTotalBudgetSpent();
    double getTotalRemainingBudget();

    double getBudgetUsagePercentage();
    double getCategoryBudgetUsage(const string& category);

    int getExceededBudgetCount();
    int getWithinBudgetCount();

    double getAverageBudgetUsage();

    // Transactions xuttayepaaxi huni waala kam idk yo required hunxa nai paaxi j j feild banauni tesma kam gaaram
    int getTransactionCountByType(const string& type);

    int getTransactionCountByCategory(const string& category);

    int getTransactionCountByDate(const string& date);

    double getAverageTransactionAmount();
    double getLargestTransaction();
    double getSmallestTransaction();

    int getMostActiveMonth(int year);


    // Yo hamro chaini waala paxi implement garna formula xa taara feilds chaiyo paila

    // Savings Rate = Net Income / Total Income * 100
    double getSavingsRate();

    // Expense Ratio = Total Expenses / Total Income * 100
    double getExpenseRatio();

    // Income Expense Ratio = Total Income / Total Expenses
    double getIncomeExpenseRatio();

    // Category Expense Percentage = Expenses for category / Total Expenses * 100
    double getCategoryExpensePercentage(const string& category);

    // Income Source Percentage = Income for source / Total Income * 100
    double getIncomeSourcePercentage(const string& source);

    // Previous month sanga comparision important graphs ko lagi

    // Growth = (Current - Previous) / Previous * 100
    double getIncomeGrowth(int currentMonth, int currentYear);

    // Growth = (Current - Previous) / Previous * 100
    double getExpenseGrowth(int currentMonth, int currentYear);

    // Growth = (Current - Previous) / Previous * 100
    double getSavingsGrowth(int currentMonth, int currentYear);
 
    void displayFinancialSummary();

    double accountHealth();
};
