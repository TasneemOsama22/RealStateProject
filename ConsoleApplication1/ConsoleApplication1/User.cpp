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
    return userId + "," + username + "," + email + "," + password + "," +
        (isAdmin ? "1" : "0") + "," +
        (isBanned ? "1" : "0") + "," +
        (IsBlocked ? "1" : "0") + "," +
        to_string(blockDaysRemaining);
}

void User::fromFileString(const string& line) {
    stringstream SS(line);
    string adminFlag, bannedFlag, blockedFlag, blockDaysStr;

    getline(SS, userId, ',');
    getline(SS, username, ',');
    getline(SS, email, ',');
    getline(SS, password, ',');
    getline(SS, adminFlag, ',');
    getline(SS, bannedFlag, ',');
    getline(SS, blockedFlag, ',');
    getline(SS, blockDaysStr);

    isAdmin = (adminFlag == "1");
    isBanned = (bannedFlag == "1");
    IsBlocked = (blockedFlag == "1");
    blockDaysRemaining = stoi(blockDaysStr);
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

