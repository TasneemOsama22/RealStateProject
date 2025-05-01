#include <iostream>
#include "Register.h"
#include "Login.h"
#include "User.h"
#include "Admin.h"
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    unordered_map<string, User> userMap;
    unordered_map<string, Admin> adminMap;

    Register reg;
    Login log;
    int choice;

    do {
        cout << "\n1. Register\n2. Login\n0. Exit\nChoose option: ";
        cin >> choice;
        cin.ignore(); // Clear newline from input buffer

        switch (choice) {
        case 1:
            reg.registerUser(userMap, adminMap);
            break;
        case 2: {
            string loggedInId;
            string accountType;

            bool success = log.loginUser(userMap, adminMap, loggedInId, accountType);
            if (success) {
                if (accountType == "admin") {
                    cout << "Admin logged in with ID: " << loggedInId << endl;
                    // TODO: Call admin menu or features here
                }
                else {
                    cout << "User logged in with ID: " << loggedInId << endl;
                    // TODO: Call user menu or features here
                }
            }
            break;
        }
        case 0:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
