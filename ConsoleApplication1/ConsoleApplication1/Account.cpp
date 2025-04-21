#include "Account.h"
#include <iostream>
#include <string>
using namespace std;

Account::Account() {}
Account::Account(string n, string e, string p, string t)
    : name(n), email(e), password(p), type(t) {
}

string Account::getName() const {
    return name;
}
string Account::getEmail() const {
    return email;
}
string Account::getPassword() const {
    return password;
}
string Account::getType() const {
    return type;
}
void Account::displayProfile() const {
    std::cout << "Name: " << name << "\nEmail: " << email << "\nType: " << type << "\n";
}


