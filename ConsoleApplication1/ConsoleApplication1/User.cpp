#include "User.h"
#include "Property.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <sstream>
#include <fstream>
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
bool User::getIsBanned()const {
    return isBanned;
}

int User::getblockDaysRemaining()const {
    return blockDaysRemaining;
}

bool User::getIsBlocked()const {
    return IsBlocked;
}

bool User::getCanPost()const {
    return CanPost;
}

int User::getWarningCount()const {
    return WarningCount;
}
string User::getUsername()const { return username; }
string User::getEmail()const { return email; }
string User::getPassword()const { return password; }
string User::getId()const { return userId; }
vector<Property>& User::getProperties() {
    return this->UserProperty;
}

//store and load property for each user
#include <fstream>
#include <iostream>
#include "User.h"       // Assumes User has getProperties() or similar
#include "Property.h"

using namespace std;

void User:: savePropertyForUser(unordered_map<string, User> userMap, string userId) {
    ofstream outFile("accounts.txt", ios::app);
    if (!outFile.is_open()) {
        cout << "Error opening file for saving properties.\n";
        return;
    }

    auto it = userMap.find(userId);
    if (it == userMap.end()) {
        cout << "User not found.\n";
        return;
    }

    const vector<Property>& properties = it->second.getProperties(); 
    for (const Property& prop : properties) {
        outFile << "PROPERTY " << userId << " "
            << prop.getId() << " "
            << prop.getTitle() << " "
            << prop.getType() << " "
            << prop.getPrice() << " "
            << prop.getLocation() << " "
            << prop.getOwnerName() << " "
            << prop.getArea() << " "
            << prop.getBedrooms() << " "
            << prop.getBathrooms() << " "
            << prop.getStatus() << " "
            << prop.isHighlighted() << " "
            << prop.getIsSold() << "\n";
    }

    outFile.close();
}

unordered_map<string, vector<Property>>User:: loadPropertyforUser() {
    unordered_map<string, vector<Property>> userProperties;
    ifstream inFile("accounts.txt");
    if (!inFile.is_open()) {
        cout << "Error opening file for loading properties.\n";
        return userProperties;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.rfind("PROPERTY ", 0) == 0) {
            istringstream iss(line);
            string tag, userId, title, type, location, owner;
            int id, bedrooms, bathrooms, status;
            double price, area;
            bool highlighted, isSold;

            iss >> tag >> userId >> id >> title >> type >> price >> location
                >> owner >> area >> bedrooms >> bathrooms >> status >> highlighted >> isSold;

            Property p(id, userId, title, price, location, owner, area, bedrooms, bathrooms, static_cast<PropertyStatus>(status), highlighted);
            p.setIsSold(isSold);

            userProperties[userId].push_back(p);
        }
    }

    inFile.close();
    return userProperties;
}




User::~User() = default;

