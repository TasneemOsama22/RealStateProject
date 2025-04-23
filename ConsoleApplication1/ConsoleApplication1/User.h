#pragma once

#include <queue>
#include <string>
#include <vector>
#include "Property.h"
using namespace std;

class User {
private:
    bool isBanned = false;
    bool CanPost = true;
    bool IsBlocked = false;
    int blockDaysRemaining = 0;
    int WarningCount = 0;

public:
    string UserId;
    string username;
    string password;
    bool isAdmin = true; // flag to check if it's admin or regular user
    queue<string> InboxMesseges;
    vector<Property> UserProperty;

    User(); // default constructor
    User(const string& u, const string& p, bool a);
    User(string UserId, string pass);
    ~User();
    //Files
    string toFileString() const; //for the user files
    void fromFileString(const string& line);
    bool checkPassword(const string& inputPassword) const;

    // setters
    void setIsBanned(bool value);
    void setblockDaysRemaining(int value);
    void setIsBlocked(bool value);
    void setCanPost(bool value);
    void setWarningCount(int value);

    // getters
    bool getIsBanned();
    int getblockDaysRemaining();
    bool getIsBlocked();
    bool getCanPost();
    int getWarningCount();
};

