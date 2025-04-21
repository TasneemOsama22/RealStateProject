#include "Login.h"
#include "Account.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <conio.h>
using namespace std;

bool Login::loginUser() {
    string email, password;

    cout << "Enter email: ";
    getline(cin, email);

    cout << "Enter password: ";
    password = getMaskedPassword();  // Fixed: removed redefinition

    ifstream inFile("accounts.txt");
    if (!inFile.is_open()) {
        cout << "Could not open accounts file.\n";
        return false;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string name, fileEmail, filePassword, type;

        getline(ss, name, ',');
        getline(ss, fileEmail, ',');
        getline(ss, filePassword, ',');
        getline(ss, type, '\n');

        if (email == fileEmail && password == filePassword) {
            Account acc(name, fileEmail, filePassword, type);
            cout << "\nLogin successful!\n";
            acc.displayProfile();
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
