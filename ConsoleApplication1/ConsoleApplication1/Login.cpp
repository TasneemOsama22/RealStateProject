#include "Login.h"
#include "User.h"
#include "Admin.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <unordered_map>

using namespace std;

bool Login::loginUser(unordered_map<string, User>& userMap,unordered_map<string, Admin>& adminMap, string& loggedInId, string& accountType) {
    cout << "Enter email: ";
    string loginEmail;
    getline(cin, loginEmail);
    transform(loginEmail.begin(), loginEmail.end(), loginEmail.begin(), ::tolower);

    cout << "Enter password: ";
    string loginPassword;
    loginPassword = getMaskedPassword();

    for (auto& pair : userMap) {
        User& user = pair.second;  

        if (user.getEmail() == loginEmail) {
            if (user.getPassword() != loginPassword) {
                cout << "Incorrect password.\n";
                return false;
            }

            if (user.getIsBanned()) {
                cout << "Your account is permanently banned. Contact support.\n";
                return false;
            }

            if (user.getIsBlocked()) {
                int daysRemaining = user.getblockDaysRemaining();
                if (daysRemaining > 0) {
                    cout << "Your account is currently blocked for " << daysRemaining << " more day(s).\n";
                    // Reduce block days by 1
                    user.setblockDaysRemaining(daysRemaining - 1);
                    if (daysRemaining - 1 <= 0) {
                        user.setIsBlocked(false);
                        cout << "Block lifted. You can now access your account.\n";
                        return true;
                    }
                    return false;
                }
            }

            cout << "Login successful: " << user.getUsername() << "\n";
            loggedInId = user.getId();
            accountType = "user";
            return true;
        }
    }

    // Search in admin map
    for (auto& pair : adminMap) {
        Admin& admin = pair.second;  

        if (admin.getEmail() == loginEmail) {
            if (admin.getPassword() != loginPassword) {
                cout << "Incorrect password.\n";
                return false;
            }

            cout << "Login successful: " << admin.getUsername() << "\n";
            loggedInId = admin.getId();
            accountType = "admin";
            return true;
        }
    }

    cout << "No account found with this email.\n";
    return false;
}


string Login::getMaskedPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') {
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password += ch;
            cout << '*';
        }
    }
    cout << "\n";
    return password;
}
