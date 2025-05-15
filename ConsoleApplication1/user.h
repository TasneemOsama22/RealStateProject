#pragma once
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
#include "Property.h"

using namespace std;

class User {
private:
    bool isBanned = false;
    bool CanPost = true;
    bool IsBlocked = false;
    int WarningCount = 0;

public:
    int blockDaysRemaining = 0;
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
    bool getIsBanned()const;
    int getblockDaysRemaining()const;
    bool getIsBlocked()const;
    bool getCanPost()const;
    int getWarningCount()const;
    string getUsername()const;
    string getEmail()const;
    string getPassword()const;
    string getId()const;
    vector<Property>& getProperties();

    // user functionalites
    void CompareProperties(const vector<Property>& properties);
    void sortByPrice(vector<Property>& properties);
    void sortByLocation(vector<Property>& properties);
    vector<Property> searchProperties(const vector<Property>& properties, const string& location, double lowerPrice, double higherPrice, const string& type);
    void sortByType(vector<Property>& properties);
    void sortByArea(vector<Property>& properties);
    void sortByNumOfBedRooms(vector<Property>& properties);
    vector<Property> binarySearchByLocation(vector<Property>& properties, const string& location);
    vector<Property> binarySearchByPrice(vector<Property>& properties, double targetPrice);
    vector<Property> binarySearchByType(vector<Property>& properties, const string& targetType);
    vector<Property> binarySearchByArea(vector<Property>& properties, double area);
    vector<Property> binarySearchByNumOfBedRooms(vector<Property>& properties, int numOfBedRooms);
    void displayResult(vector<Property>& approved);
    vector<Property> addProperty(unordered_map<string, User>& users,
        const string& currentUserId,
        vector<Property>& pendingProp);
    string checkPropertyStatus(const Property& property);
    void viewUserProperties(unordered_map<string, User>& users,
        const string& currentUserId, const string& status);
    void buyProperty(vector<Property>& properties, const string& buyerId);
    void userDashboard(unordered_map<string, User>& userMap, vector<Property>& pendingAds, vector<Property>& approvedAds, const string& loggedInId);
    void manageUserProfile(unordered_map<string, User>& users, const string& userId);

};
