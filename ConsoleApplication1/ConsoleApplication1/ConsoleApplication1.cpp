#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include "User.h"
#include "Admin.h"
#include "Register.h"
#include "Login.h"
#include "Property.h"
#include "Files.h"
using namespace std;
int main() {
    unordered_map<string, User> userMap;
    unordered_map<string, Admin> adminMap;
    Files f;
    vector<Property> approvedAds, pendingAds, rejectedAds;
    vector<string> types = {
        "Apartment", "Villa", "Chalet", "Studio",
        "Duplex", "Townhouse", "Farmhouse"
    };
    vector<string> locations = {
        "New Cairo", "6th October", "North Coast",
        "Zayed City", "Maadi", "Heliopolis", "Nasr City"
    };

    Register reg;
    Login login;
    User user;
    ifstream inFile("accounts.txt");
    if (inFile.is_open()) {
        f.loadAccountsFromFile(userMap, adminMap, inFile);
        inFile.close();
    }

    f.loadPropertiesFromFile(pendingAds, approvedAds, rejectedAds, "properties.txt");

    string loggedInId, accountType;

    while (true) {
        cout << "\n=== Main Menu ===\n";
        cout << "1. Register\n2. Login\n3. Exit\nChoose: ";
        string input;
        getline(cin, input);

        if (input == "1") {
            reg.registerUser(userMap, adminMap); 
        }
        else if (input == "2") {
            if (login.loginUser(userMap, adminMap, loggedInId, accountType)) {
                if (accountType == "user") {
                    user.userDashboard(userMap, pendingAds, approvedAds, loggedInId); 
                }
                else if (accountType == "admin") {
                    Admin currentAdmin;
                    currentAdmin.showAdminDashboard(adminMap, userMap, pendingAds, approvedAds, rejectedAds, types, locations); 
                }
            }
        }
        else if (input == "3") {
            break;
        }
        else {
            cout << "Invalid input. Please try again.\n";
        }
    }

    ofstream outFile("accounts.txt");
    if (outFile.is_open()) {
        f.storeAccountsToFile(userMap, adminMap, outFile);
        outFile.close();
    }

    f.savePropertiesToFile(pendingAds, approvedAds, rejectedAds, "properties.txt");

    return 0;
}
