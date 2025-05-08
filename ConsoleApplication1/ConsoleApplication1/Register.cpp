#include "Register.h"
#include "User.h"
#include "Admin.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;

bool Register::registerUser(unordered_map<string, User>& userMap, unordered_map<string, Admin>& adminMap,
    string& id, string& name, string& email, string& password, string& type) {
    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your email: ";
    getline(cin, email);
    while (!isEmailValid(email)) {
        cout << "Invalid email. Try again: ";
        getline(cin, email);
    }

    // Check if email already exists
    for (const auto& pair : userMap) {
        if (pair.second.getEmail() == email) {
            cout << "An account with this email already exists.\n";
            return false;
        }
    }
    for (const auto& pair : adminMap) {
        if (pair.second.getEmail() == email) {
            cout << "An account with this email already exists.\n";
            return false;
        }
    }

    cout << "Enter your password: ";
    getline(cin, password);
    while (!isPasswordStrong(password)) {
        cout << "Weak password. Must be at least 6 characters. Try again: ";
        getline(cin, password);
    }

    type = detectType();
    id = generateUniqueID(type);

    if (type == "user") {
        User newUser(id, name, email, password);
        userMap[id] = newUser;
    }
    else {
        Admin newAdmin(id, name, email, password);
        adminMap[id] = newAdmin;
    }

    return true;
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

void Register::loadAccounts(unordered_map<string, User>& userMap, unordered_map<string, Admin>& adminMap) {
    ifstream inFile("accounts.txt");
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, name, email, password, type;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, password, ',');
        getline(ss, type, ',');

        if (type == "user") {
            userMap[id] = User(id, name, email, password);
        }
        else if (type == "admin") {
            adminMap[id] = Admin(id, name, email, password);
        }
    }
    inFile.close();
}

void Register::storeAccount(const string& id, const string& name, const string& email, const string& password, const string& type) {
    ofstream outFile("accounts.txt", ios::app);
    if (!outFile.is_open()) {
        cout << "Error opening file for saving accounts.\n";
        return;
    }

    // Add default values for loginAttempts, isBlocked, isBanned
    outFile << id << "," << name << "," << email << "," << password << "," << type
        << ",0,0,0" << endl;

    outFile.close();
}

