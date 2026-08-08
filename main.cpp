#include <iostream>
#include "User.h"
#include "UserManager.h"
#include "AuthSystem.h"

using namespace std;

int main()
{
    // just for testing
    User u;
    u.setPassword("123123");
    string x = u.getPassword();

    // testing the UserManager class
    UserManager U("Users.txt");
    U.display();
    // testing the AuthSystem class
    AuthSystem auth(U);
    while (true)
    {
        cout << "\n==== Finance Manager ====\n";
        cout << "1. Login\n";
        cout << "2. Sign Up\n";
        cout << "3. Search User\n";
        cout << "4. Exit\n";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            // just testing the setUsername and getUsername
            cout << x << endl;

            break;

        case 2:
        {
            string username, password;

            cout << "Enter username: ";
            cin >> username;

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
        }
        case 3:
            // testing search algorithm
            {
                string key;
                cout << "Enter username: ";
                cin >> key;

                vector<User> result = U.searchUsers(key);

                if (result.empty())
                {
                    cout << "No users found.\n";
                }
                else
                {
                    cout << "\nMatching Users:\n";

                    for (const auto &user : result)
                    {
                        cout << user.getId() << " "
                             << user.getUsername() << " " << endl;
                    }
                }

                break;
            }

        case 4:
            return 0;

        default:
            cout << "Invalid choice!\n";
        }
    }
}