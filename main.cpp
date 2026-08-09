#include <iostream>
#include "User.h"
#include "UserManager.h"
#include "AuthSystem.h"
#include "IncomeManager.h"
#include "ExpenseManager.h"
#include "TransactionManager.h"
#include "utils.h"


using namespace std;

int main()
{
    // just for testing
    User u;
   

    // testing the UserManager class
    UserManager U("Users.txt");
    
    //  the AuthSystem class
    AuthSystem auth(U);
    while (true)
    {
        clearScreen();
        cout << "\n==== Finance Manager ====\n";
        cout << "1. Login\n";
        cout << "2. Sign Up\n";
        
        cout << "3. Exit\n";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
           {
            string username, password;

            cout << "Enter username: ";
            cin >> username;

            cout << "Enter password: ";
            cin >> password;

            if (auth.login(username, password))
            {
                cout << "Login successful!\n";
                cout << "Welcome, " << auth.getCurrentUser()->getUsername() << "!\n";

                IncomeManager incomeManager("Income.txt", auth.getCurrentUser()->getId());
                ExpenseManager expenseManager("Expenses.txt", auth.getCurrentUser()->getId());
                TransactionManager transactionManager(incomeManager.getIncomeForCurrentUser(),
                                                      expenseManager.getExpensesForCurrentUser(),
                                                      auth.getCurrentUser()->getId());

                while (true)
                {
                    cout << "\n==== FINANCE MANAGER ====\n";
                    cout << "1. Income\n";
                    cout << "2. Expenses\n";
                    cout << "3. Transactions\n";
                    cout << "4. View Profile\n";
                    cout << "5. Logout\n";
                    int financeChoice;
                    cin >> financeChoice;
                    switch (financeChoice)
                    {
                    case 1:
                        while (true)
                        {
                            cout << "\n==== INCOME ====\n";
                            cout << "1. Add Income\n";
                            cout << "2. View Income\n";
                            cout << "3. Update Income\n";
                            cout << "4. Delete Income\n";
                            cout << "5. Search Income\n";
                            cout << "6. Back\n";
                            int incomeChoice;
                            cin >> incomeChoice;
                            switch (incomeChoice)
                            {
                            case 1:
                                incomeManager.addIncome();
                                break;
                            case 2:
                                incomeManager.viewIncome();
                                break;
                            case 3:
                                incomeManager.updateIncome();
                                break;
                            case 4:
                                incomeManager.deleteIncome();
                                break;
                            case 5:
                                incomeManager.searchIncome();
                                break;
                            case 6:
                                break;
                            default:
                                cout << "Invalid choice!\n";
                            }
                            if (incomeChoice == 6)
                            {
                                break;
                            }
                        }
                        break;
                    case 2:
                        while (true)
                        {
                            cout << "\n==== EXPENSES ====\n";
                            cout << "1. Add Expense\n";
                            cout << "2. View Expenses\n";
                            cout << "3. Update Expense\n";
                            cout << "4. Delete Expense\n";
                            cout << "5. Search Expense\n";
                            cout << "6. Back\n";
                            int expenseChoice;
                            cin >> expenseChoice;
                            switch (expenseChoice)
                            {
                            case 1:
                                expenseManager.addExpense();
                                break;
                            case 2:
                                expenseManager.viewExpenses();
                                break;
                            case 3:
                                expenseManager.updateExpense();
                                break;
                            case 4:
                                expenseManager.deleteExpense();
                                break;
                            case 5:
                                expenseManager.searchExpense();
                                break;
                            case 6:
                                break;
                            default:
                                cout << "Invalid choice!\n";
                            }
                            if (expenseChoice == 6)
                            {
                                break;
                            }
                        }
                        break;
                    case 3:
                        while (true)
                        {
                            TransactionManager transactionManager(incomeManager.getIncomeForCurrentUser(),
                                                                  expenseManager.getExpensesForCurrentUser(),
                                                                  auth.getCurrentUser()->getId());
                            cout << "\n==== TRANSACTIONS ====\n";
                            cout << "1. View All Transactions\n";
                            cout << "2. Search\n";
                            cout << "3. Filter by Type\n";
                            cout << "4. Filter by Date\n";
                            cout << "5. Filter by Category\n";
                            cout << "6. Sort by Amount\n";
                            cout << "7. Sort by Date\n";
                            cout << "8. Back\n";
                            int transactionChoice;
                            cin >> transactionChoice;
                            switch (transactionChoice)
                            {
                            case 1:
                                transactionManager.viewTransactions();
                                break;
                            case 2:
                                cin.ignore();
                                transactionManager.searchTransaction();
                                break;
                            case 3:
                                transactionManager.filterByType();
                                break;
                            case 4:
                                cin.ignore();
                                transactionManager.filterByDate();
                                break;
                            case 5:
                                cin.ignore();
                                transactionManager.filterByCategory();
                                break;
                            case 6:
                                transactionManager.sortByAmount();
                                break;
                            case 7:
                                transactionManager.sortByDate();
                                break;
                            case 8:
                                break;
                            default:
                                cout << "Invalid choice!\n";
                            }
                            if (transactionChoice == 8)
                            {
                                break;
                            }
                        }
                        break;
                    case 4:
                        cout << "User Profile:\n";
                        cout << "Username: " << auth.getCurrentUser()->getUsername() << endl;
                        cout << "User ID: " << auth.getCurrentUser()->getId() << endl;
                        break;
                    case 5:
                        auth.logout();
                        cout << "Logged out successfully!\n";
                        break;
                    default:
                        cout << "Invalid choice!\n";
                    }
                    if (financeChoice == 5)
                    {
                        break;
                    }
                }
            }
            else
            {
                cout << "Invalid username or password!\n";
            }

            break;
        }


        case 2:
        {
            string username, password;
            int signupchoice;
            cout << "Enter username: ";
            cin >> username;


            std::cout << "1. Enter my own password\n";
            std::cout << "2. Generate a strong password\n";

            cin >> signupchoice;
            switch(signupchoice){
                case 1:
                    cout << "Enter password: ";
                        cin >> password;
                        if (auth.signup(username, password))
                        {
                            cout << "Signup successful!\n";
                        }
                        else
                        {
                            cout << "Username already exists!\n";
                        }

                        break;
                case 2:
                {
                    int length;
                    cout << "Enter password length: ";
                    cin >> length;
                    if (length < 6)
                    {
                        length = 8;
                    }
                    string strongPassword = generateStrongPassword(length);
                    cout << "Generated strong password: " << strongPassword << endl;
                    password = strongPassword;
                    if (auth.signup(username, password))
                    {
                        cout << "Signup successful!\n";
                    }
                    else
                    {
                        cout << "Signup failed. Username may already exist or password is invalid.\n";
                    }
                    break;
                }
                        

            }


           break;
        }
        // case 3:
            // // testing search algorithm
            // {
            //     string key;
            //     cout << "Enter username: ";
            //     cin >> key;

            //     vector<User> result = U.searchUsers(key);

            //     if (result.empty())
            //     {
            //         cout << "No users found.\n";
            //     }
            //     else
            //     {
            //         cout << "\nMatching Users:\n";

            //         for (const auto &user : result)
            //         {
            //             cout << user.getId() << " "
            //                  << user.getUsername() << " " << endl;
            //         }
            //     }

            //     break;
            // }

        case 3:
            return 0;

        case 67:
            // just for testing the generateStrongPassword function
            {
                int length;
                cout << "Enter password length: ";
                cin >> length;
                string strongPassword = generateStrongPassword(length=8);
                cout << "Generated strong password: " << strongPassword << endl;
            }
            break;

        default:
            cout << "Invalid choice!\n";
        }

        pauseScreen();
        clearScreen();
    }
}