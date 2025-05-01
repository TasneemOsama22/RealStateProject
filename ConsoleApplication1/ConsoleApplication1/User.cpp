#include "User.h"
#include <iostream>
#include <string>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

User::User() {}
User::User(const string& u, const string& p, bool a)
    : username(u), password(p), isAdmin(a) {
}
User::User(const string& id, const string& name, const string& email, const string& password)
    : userId(id), username(name), email(email), password(password), isAdmin(false) {
}

User::User(string userId, string pass) {
    this->userId = userId;
    this->password = pass;
}

string User::toFileString() const {
    return username + "," + password + "," + (isAdmin ? "1" : "0");
}
void User::fromFileString(const string& line) {
    stringstream SS(line);
    getline(SS, username, ',');
    getline(SS, password, ',');
    string adminFlag; //carry 1 or 0
    getline(SS, adminFlag);
    isAdmin = (adminFlag == "1"); //check if its 1 then the isAdmin value is true otherwise its false
}
bool User::checkPassword(const string& p) const {
    return password == p;
}

// Setters
void User::setIsBanned(bool value) {
    isBanned = value;
}

void User::setblockDaysRemaining(int value) {
    blockDaysRemaining = value;
}

void User::setIsBlocked(bool value) {
    IsBlocked = value;
}

void User::setCanPost(bool value) {
    CanPost = value;
}

void User::setWarningCount(int value) {
    WarningCount = value;
}

// Getters
bool User::getIsBanned() {
    return isBanned;
}

int User::getblockDaysRemaining() {
    return blockDaysRemaining;
}

bool User::getIsBlocked() {
    return IsBlocked;
}

bool User::getCanPost() {
    return CanPost;
}

int User::getWarningCount() {
    return WarningCount;
}
string User::getUsername()const { return username; }
string User::getEmail()const { return email; }
string User::getPassword()const { return password; }

User::~User() = default;

