#include "Login.h"
#include "User.h"
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <unordered_map>

using namespace std;

bool Login::loginUser(unordered_map<string, User>& userMap,
    unordered_map<string, Admin>& adminMap,
    string& loggedInId,
    string& accountType) {
    string email, password;

    cout << "Enter email: ";
    getline(cin, email);

    cout << "Enter password: ";
    password = getMaskedPassword();

    // Check in userMap
    for (const auto& pair : userMap) {
        const User& user = pair.second;
        if (user.getEmail() == email && user.getPassword() == password) {
            if (user.getIsBanned()) {
                cout << "Your account has been permanently banned. Access denied.\n";
                return false;
            }
            if (user.getIsBlocked()) {
                cout << "Your account is currently blocked for " << user.getblockDaysRemaining() << " more day(s).\n";
                return false;
            }
            loggedInId = user.getId();
            accountType = "user";
            cout << "\nLogin successful!\n";
            cout << "Welcome, " << user.getUsername() << " (user)\n";
            return true;
        }
    }
    for (const auto& pair : adminMap) {
        const Admin& admin = pair.second;
        if (admin.getEmail() == email && admin.getPassword() == password) {
           
            loggedInId = admin.getId();
            accountType = "admin";
            cout << "\nLogin successful!\n";
            cout << "Welcome, " << admin.getUsername() << " (admin)\n";
            return true;
        }
    }
    cout << "Login failed. Incorrect email or password.\n";
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
        }
        else {
            password += ch;
            cout << '*';
        }
    }
    cout << "\n";
    return password;
}
