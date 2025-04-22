#include "User.h"
#include <string>
#include <queue>
#include <vector>

User::User() = default;
#include <iostream>
#include <string>
#include <queue>
#include <vector>

User::User() = default;

User::User(const string& u, const string& p, bool a)
    : username(u), password(p), isAdmin(a) {
}

User::User(string UserId, string pass) {
    this->UserId = UserId;
    this->password = pass;
}

User::~User() = default;

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


User::User(const string& u, const string& p, bool a)
    : username(u), password(p), isAdmin(a) {
}

User::User(string UserId, string pass) {
    this->UserId = UserId;
    this->password = pass;
}

User::~User() = default;

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
