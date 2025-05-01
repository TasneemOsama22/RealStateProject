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
    string userId;
    string username;
    string password;
    string email;
    bool isAdmin = true; // flag to check if it's admin or regular user
    queue<string> InboxMessages;
    vector<Property> UserProperty;

    User(const string& u, const string& p, bool a);
    User(const string userId, const string pass);
    User();
    User(const string& id, const string& name, const string& email, const string& password);
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
    string getUsername()const;
    string getEmail()const;
    string getPassword()const;
};

