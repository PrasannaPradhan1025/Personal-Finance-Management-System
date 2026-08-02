#include <iostream>
#include "User.h"
#include "UserManager.h"

using namespace std;

int main() {
    //just for testing 
    User u;
    u.setPassword("123123");
    string x = u.getPassword();


    //testing the UserManager class
    UserManager U("Users.txt");
    U.display();

    while (true) {
        cout << "\n==== Finance Manager ====\n";
        cout << "1. Login\n";
        cout << "2. Sign Up\n";
        cout << "3. Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            //just testing the setUsername and getUsername
            cout <<x <<endl;
           
            break;

        case 2:
            cout<<"signup"<<endl;
            break;

        case 3:
            return 0;

        default:
            cout << "Invalid choice!\n";
        }
    }
}