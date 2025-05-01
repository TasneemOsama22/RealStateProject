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

    ifstream inFile("accounts.txt");
    if (!inFile.is_open()) {
        cout << "Could not open accounts file.\n";
        return false;
    }

    string line;
    while (getline(inFile, line)) {
        string id, name, fileEmail, filePassword, type;

        stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, fileEmail, ',');
        getline(ss, filePassword, ',');
        getline(ss, type);

        if (email == fileEmail && password == filePassword) {
            loggedInId = id;
            accountType = type;

            cout << "\nLogin successful!\n";
            cout << "Welcome, " << name << " (" << type << ")\n";

            return true;
        }
    }

    cout << "Login failed. Incorrect email or password.\n";
    return false;
}

string Login::getMaskedPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') {  // Enter key
        if (ch == '\b') { // Backspace
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
