#include "Register.h"
#include "Account.h"
#include <iostream>
#include <string>
#include <fstream>
#include <regex>
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
    cout << "Enter your password: ";
    getline(cin, password);
    while (!isPasswordStrong(password)) {
        cout << "Weak password. Must be at least 6 characters. Try again: ";
        getline(cin, password);
    }
    string type = detectType();
    Account newAcc(name, email, password, type);
    ofstream outFile("accounts.txt",ios::app);
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
    return (code == 1) ? "admin" : "user";
}

