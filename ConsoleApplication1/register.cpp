#include "Register.h"
#include "User.h"
#include "Admin.h"
#include <iostream>
#include <unordered_map>
#include <regex>

using namespace std;

bool Register::registerUser(unordered_map<string, User>& userMap, unordered_map<string, Admin>& adminMap) {
    string name, email, password, type, id;

    type = detectType();

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your email: ";
    getline(cin, email);
    transform(email.begin(), email.end(), email.begin(), ::tolower);

    while (!isEmailValid(email)) {
        cout << "Invalid email. Try again: ";
        getline(cin, email);
    }

    bool emailExists = any_of(userMap.begin(), userMap.end(),
        [&email](const auto& pair) { return pair.second.getEmail() == email; });

    if (emailExists) {
        cout << "User email exists!\n";
        return false;
    }

    emailExists = any_of(adminMap.begin(), adminMap.end(),
        [&email](const auto& pair) { return pair.second.getEmail() == email; });

    if (emailExists) {
        cout << "Admin email exists!\n";
        return false;
    }

    cout << "Enter your password: ";
    getline(cin, password);
    while (!isPasswordStrong(password)) {
        cout << "Weak password. Must be at least 6 characters. Try again: ";
        getline(cin, password);
    }

    id = generateUniqueID(userMap, adminMap, type);

    if (type == "user") {
        userMap[id] = User(id, name, email, password);
    }
    else {
        adminMap[id] = Admin(id, name, email, password);
    }

    cout << "Account successfully registered.\n";
    return true;
}

bool Register::isEmailValid(const string& email) {
    const regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
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

string Register::generateUniqueID(
    const unordered_map<string, User>& userMap,
    const unordered_map<string, Admin>& adminMap,
    const string& type
) {
    int maxID = (type == "user") ? 1000 : 2000;

    if (type == "user") {
        for (const auto& pair : userMap) {
            const string& id = pair.first;
            if (id.substr(0, 3) == "USR") {
                int num = stoi(id.substr(3));
                if (num >= maxID)
                    maxID = num + 1;
            }
        }
    }
    else {
        for (const auto& pair : adminMap) {
            const string& id = pair.first;
            if (id.substr(0, 3) == "ADM") {
                int num = stoi(id.substr(3));
                if (num >= maxID)
                    maxID = num + 1;
            }
        }
    }

    return (type == "user" ? "USR" : "ADM") + to_string(maxID);
}
