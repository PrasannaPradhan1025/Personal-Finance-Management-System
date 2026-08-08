#include <iostream>
#include "User.h"
#include "UserManager.h"
#include "AuthSystem.h"
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
                while (true)
                {
                    cout << "\n==== Personal Finance Menu ====\n";
                    cout << "1. View Profile\n";
                    // Additional personal finance features can be added here
                    cout << "5. Logout\n";
                    int financeChoice;
                    cin >> financeChoice;
                    switch (financeChoice)
                    {
                    case 1:
                        cout << "User Profile:\n";
                        cout << "Username: " << auth.getCurrentUser()->getUsername() << endl;
                        cout << "User ID: " << auth.getCurrentUser()->getId() << endl;
                        // additionals
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
                        break; // exit the personal finance menu loop
                    }
                }
                // personal finance menu and further features can be implemented here
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