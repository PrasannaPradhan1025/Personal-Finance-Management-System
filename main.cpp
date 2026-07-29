#include <iostream>
#include "User.h"

using namespace std;

int main() {
    
    User user(10,"Prasanna","pasdfksd");
  

    while (true) {
        cout << "\n==== Finance Manager ====\n";
        cout << "1. Login\n";
        cout << "2. Sign Up\n";
        cout << "3. Exit\n";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
           
            user.show();
           
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