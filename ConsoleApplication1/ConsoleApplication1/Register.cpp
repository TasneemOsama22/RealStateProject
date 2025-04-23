#include "Account.h"
#include "Register.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

void Register::registerUser() {
    string name, email, password;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your email: ";
    getline(cin, email);
    while (!isEmailValid(email)) {
        cout << "Invalid email. Try again: ";
        getline(cin, email);
    }

    ifstream inFile("accounts.txt");
    string line, existingEmail;
    bool emailExists = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string tempName, tempPassword, tempType;
        getline(ss, tempName, ',');
        getline(ss, existingEmail, ',');
        getline(ss, tempPassword, ',');
        getline(ss, tempType, '\n');

        if (email == existingEmail) {
            emailExists = true;
            break;
        }
    }
    inFile.close();

    if (emailExists) {
        cout << "An account with this email already exists. Please try logging in or use a different email.\n";
        return;
    }

    cout << "Enter your password: ";
    getline(cin, password);
    while (!isPasswordStrong(password)) {
        cout << "Weak password. Must be at least 6 characters. Try again: ";
        getline(cin, password);
    }

    string type = detectType();
    Account newAcc(name, email, password, type);
    ofstream outFile("accounts.txt", ios::app);
    if (outFile.is_open()) {
        outFile << name << "," << email << "," << password << "," << type << "\n";
        outFile.close();
        cout << "Account registered successfully as a " << type << "!\n";
    }
    else {
        cout << "Error opening file.\n";
    }
}

bool Register::isEmailValid(const string& email) {
    const regex pattern(R"((\w+)(\.{0,1})(\w*)@(\w+)\.(\w+))");
    return regex_match(email, pattern);
}

bool Register::isPasswordStrong(const string& password) {
    return password.length() >= 6;
}

string Register::detectType() {
    int code;
    cout << "1.Admin\n2.User ";
    cin >> code;
    cin.ignore(); 
    return (code == 1) ? "admin" : "user";
}
