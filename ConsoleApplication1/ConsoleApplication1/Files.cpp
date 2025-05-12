#include "Files.h"
#include "User.h"
#include "Admin.h"
#include "Property.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>


void Files::loadAccountsFromFile(
    unordered_map<string, User>& userMap,
    unordered_map<string, Admin>& adminMap,
    istream& inFile
) {
    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        if (line.rfind("PROPERTY ", 0) == 0) {
            // Parse PROPERTY line
            istringstream iss(line);
            string tag, userId;
            int id, bedrooms, bathrooms, status;
            double price, area;
            bool highlighted, isSold;
            string title, type, location, owner;

            iss >> tag >> userId >> id
                >> quoted(title) >> quoted(type)
                >> price >> quoted(location) >> quoted(owner)
                >> area >> bedrooms >> bathrooms
                >> status >> highlighted >> isSold;

            Property p(id, userId, title, price, location, owner, area, bedrooms, bathrooms, static_cast<PropertyStatus>(status), highlighted);
            p.setIsSold(isSold);

            // Add property to corresponding user if user exists
            auto it = userMap.find(userId);
            if (it != userMap.end()) {
                it->second.getProperties().push_back(p);
            }
            else {
                cout << "Warning: PROPERTY for unknown userId " << userId << "\n";
            }

            continue;
        }

        // Parse normal account line
        stringstream ss(line);
        string id, name, email, password, type;

        if (!getline(ss, id, ',')) continue;
        if (!getline(ss, name, ',')) continue;
        if (!getline(ss, email, ',')) continue;
        if (!getline(ss, password, ',')) continue;
        if (!getline(ss, type, ',')) continue;

        transform(email.begin(), email.end(), email.begin(), ::tolower);

        if (type == "user") {
            string isBlockedStr, isBannedStr, warningCountStr, blockDaysStr, inboxField;

            if (!getline(ss, isBlockedStr, ',')) continue;
            if (!getline(ss, isBannedStr, ',')) continue;
            if (!getline(ss, warningCountStr, ',')) continue;
            if (!getline(ss, blockDaysStr, ',')) continue;
            getline(ss, inboxField);  // inbox is last

            User user(id, name, email, password);
            user.setIsBlocked(stoi(isBlockedStr));
            user.setIsBanned(stoi(isBannedStr));
            user.setWarningCount(stoi(warningCountStr));
            user.setblockDaysRemaining(stoi(blockDaysStr));

            stringstream inboxStream(inboxField);
            string message;
            while (getline(inboxStream, message, '|')) {
                if (!message.empty()) {
                    user.InboxMessages.push(message);
                }
            }

            userMap[id] = user;
        }
        else if (type == "admin") {
            Admin admin(id, name, email, password);
            adminMap[id] = admin;
        }
        else {
            cout << "Unknown account type: " << type << " in line: " << line << endl;
        }
    }
}


void Files::storeAccountsToFile(
    const unordered_map<string, User>& userMap,
    const unordered_map<string, Admin>& adminMap,
    ostream& outFile
) {
    for (const auto& pair : userMap) {
        const User& user = pair.second;

        // Save user info
        outFile << user.getId() << ","
            << user.getUsername() << ","
            << user.getEmail() << ","
            << user.getPassword() << ","
            << "user" << ","
            << user.getIsBlocked() << ","
            << user.getIsBanned() << ","
            << user.getWarningCount() << ","
            << user.getblockDaysRemaining() << ",";

        // Save inbox messages
        queue<string> messages = user.InboxMessages;
        while (!messages.empty()) {
            outFile << messages.front();
            messages.pop();
            if (!messages.empty()) outFile << "|";
        }
        outFile << "\n";
        // Save user properties
        for (const Property& prop : const_cast<User&>(user).getProperties()) {
            outFile << "PROPERTY " << user.getId() << " "
                << prop.getId() << " "
                << quoted(prop.getTitle()) << " "
                << quoted(prop.getType()) << " "
                << prop.getPrice() << " "
                << quoted(prop.getLocation()) << " "
                << quoted(prop.getOwnerName()) << " "
                << prop.getArea() << " "
                << prop.getBedrooms() << " "
                << prop.getBathrooms() << " "
                << prop.getStatus() << " "
                << prop.isHighlighted() << " "
                << prop.getIsSold() << "\n";
        }


    }

    for (const auto& pair : adminMap) {
        const Admin& admin = pair.second;

        outFile << admin.getId() << ","
            << admin.getUsername() << ","
            << admin.getEmail() << ","
            << admin.getPassword() << ","
            << "admin" << "\n";
    }
}
void Files::savePropertiesToFile(const vector<Property>& pending,
    const vector<Property>& approved,
    const vector<Property>& rejected,
    const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    auto saveVector = [&](const vector<Property>& props) {
        for (const Property& p : props) {
            outFile << p.getId() << ","
                << p.getUserId() << ","
                << p.getTitle() << ","
                << p.getType() << ","
                << p.getPrice() << ","
                << p.getLocation() << ","
                << p.getOwnerName() << ","
                << p.getArea() << ","
                << p.getBedrooms() << ","
                << p.getBathrooms() << ","
                << static_cast<int>(p.getStatus()) << ","
                << p.isHighlighted() << ","
                << p.getIsSold() << "\n";
        }
        };

    saveVector(pending);
    saveVector(approved);
    saveVector(rejected);

    outFile.close();
    cout << "All properties saved to file successfully." << endl;
}

void Files::loadPropertiesFromFile(vector<Property>& pending,
    vector<Property>& approved,
    vector<Property>& rejected,
    const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "File not found. No properties loaded." << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;

        Property p;
        int statusInt, highlightedInt, soldInt;

        getline(ss, token, ','); p.setId(stoi(token));
        getline(ss, token, ','); p.setUserId(token);
        getline(ss, token, ','); p.setTitle(token);
        getline(ss, token, ','); p.setType(token);
        getline(ss, token, ','); p.setPrice(stod(token));
        getline(ss, token, ','); p.setLocation(token);
        getline(ss, token, ','); p.setOwnerName(token);
        getline(ss, token, ','); p.setArea(stod(token));
        getline(ss, token, ','); p.setBedrooms(stoi(token));
        getline(ss, token, ','); p.setBathrooms(stoi(token));
        getline(ss, token, ','); statusInt = stoi(token);
        getline(ss, token, ','); highlightedInt = stoi(token);
        getline(ss, token, ','); soldInt = stoi(token);

        p.setStatus(static_cast<PropertyStatus>(statusInt));
        p.setHighlighted(highlightedInt);
        p.setIsSold(soldInt);

        switch (p.getStatus()) {
        case Pending: pending.push_back(p); break;
        case Approved: approved.push_back(p); break;
        case Rejected: rejected.push_back(p); break;
        }
    }

    inFile.close();
}


