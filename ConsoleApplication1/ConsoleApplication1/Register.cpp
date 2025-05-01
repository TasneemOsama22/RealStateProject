#include "Register.h"
#include "User.h"
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

void Register::registerUser(unordered_map<string, User>& userMap, unordered_map<string, Admin>& adminMap) {
    string name, email, password;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your email: ";
    getline(cin, email);
    while (!isEmailValid(email)) {
        cout << "Invalid email. Try again: ";
        getline(cin, email);
    }

    // Check if email already exists
    ifstream inFile("accounts.txt");
    string line;
    bool emailExists = false;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string tempID, tempName, tempEmail, tempPassword, tempType;
        getline(ss, tempID, ',');
        getline(ss, tempName, ',');
        getline(ss, tempEmail, ',');
        getline(ss, tempPassword, ',');
        getline(ss, tempType, ',');
        if (email == tempEmail) {
            emailExists = true;
            break;
        }
    }
    inFile.close();

    if (emailExists) {
        cout << "An account with this email already exists.\n";
        return;
    }

    cout << "Enter your password: ";
    getline(cin, password);
    while (!isPasswordStrong(password)) {
        cout << "Weak password. Must be at least 6 characters. Try again: ";
        getline(cin, password);
    }

    string type = detectType();
    string uniqueID = generateUniqueID(type);

    // Create appropriate object and store in map
    if (type == "user") {
        User newUser(uniqueID, name, email, password);
        userMap[uniqueID] = newUser;
    }
    else {
        Admin newAdmin(uniqueID, name, email, password);
        adminMap[uniqueID] = newAdmin;
    }

    // Append new account to file 
    ofstream outFile("accounts.txt", ios::app);
    if (!outFile.is_open()) {
        cout << "Error opening file for saving accounts.\n";
        return;
    }


    outFile << uniqueID << "," << name << "," << email << "," << password << "," << type
        << ",0,0,0" << endl;

    outFile.close();

    cout << "Account registered successfully as a " << type << "! Your ID is " << uniqueID << ".\n";
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
    cout << "1.Admin\n2.User: ";
    while (!(cin >> code) || (code != 1 && code != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter 1 for Admin or 2 for User: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return (code == 1) ? "admin" : "user";
}

string Register::generateUniqueID(const string& type) {
    int maxID = (type == "user") ? 1000 : 2000;

    ifstream inFile("accounts.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string id, name, email, password, userType;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, password, ',');
            getline(ss, userType, ',');

            if ((type == "user" && id.substr(0, 3) == "USR") ||
                (type == "admin" && id.substr(0, 3) == "ADM")) {
                int num = stoi(id.substr(3));
                if (num >= maxID)
                    maxID = num + 1;
            }
        }
        inFile.close();
    }

    return (type == "user" ? "USR" : "ADM") + to_string(maxID);
}
