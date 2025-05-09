#include "Adminreport.h"      
#include "User.h"             
#include "Property.h"         

#include <iostream>
#include <vector>
#include <map>
using namespace std;

void generateAdminReport(const vector<User>& users,
    const vector<Property>& approvedProperties,
    const vector<Property>& pendingProperties,
    const vector<Property>& rejectedProperties) {
    while (true) {
        cout << "\n*********** Admin Reports ************"<<endl;
        cout << "Choose the report to generate:"<<endl;
        cout << "1. Listings Statistics"<< endl;
        cout << "2. User Activity" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "\n--- Listings Statistics Report ---" << endl;

            cout << "Approved Properties : " << approvedProperties.size() << endl;
            cout << "Pending Properties  : " << pendingProperties.size() << endl;
            cout << "Rejected Properties : " << rejectedProperties.size() << endl;
            cout << "Total Properties    : "
                << approvedProperties.size() + pendingProperties.size() + rejectedProperties.size()
                << endl;

            cout << "\n--- General Analytics ---" << endl;

            vector<Property> all;
            all.insert(all.end(), approvedProperties.begin(), approvedProperties.end());
            all.insert(all.end(), pendingProperties.begin(), pendingProperties.end());
            all.insert(all.end(), rejectedProperties.begin(), rejectedProperties.end());

            if (all.empty()) {
                cout << "No properties available to analyze." << endl;
                continue;
            }

            double totalPrice = 0;
            map<string, int> typeCount, locationCount;

            for ( auto& prop : all) {
                totalPrice += prop.getPrice();
                typeCount[prop.getType()]++;
                locationCount[prop.getLocation()]++;
            }

            double averagePrice = totalPrice / all.size();
            cout << "Average Price: " << averagePrice << " EGP" << endl;

            string popularType;
            int maxType = 0;
            for ( auto& pair : typeCount) {
                if (pair.second > maxType) {
                    maxType = pair.second;
                    popularType = pair.first;
                }
            }
            cout << "Most Common Property Type: " << popularType << " (" << maxType << " listings)" << endl;

            string popularLocation;
            int maxLocation = 0;
            for ( auto& pair : locationCount) {
                if (pair.second > maxLocation) {
                    maxLocation = pair.second;
                    popularLocation = pair.first;
                }
            }
            cout << "Most Common Location: " << popularLocation << " (" << maxLocation << " listings)" << endl;

            break;
        }

        else if (choice == 2) {
            cout << "\n--- User Activity Report ---" << endl;

            int userCount = 0;
            for ( auto& user : users) {
                if (user.isAdmin) continue;

                userCount++;
                cout << endl << "-----------------------------" << endl;
                cout << "Username             : " << user.getUsername() << endl;
                cout << "Email                : " << user.getEmail() << endl;
                cout << "Properties Posted    : " << user.UserProperty.size() << endl;
                cout << "Inbox Messages       : " << user.InboxMessages.size() << endl;
                cout << "Is Banned            : " << (user.getIsBanned() ? "Yes" : "No") << endl;
                cout << "Is Blocked           : " << (user.getIsBlocked() ? "Yes" : "No") << endl;
                cout << "Block Days Remaining : " << user.getblockDaysRemaining() << endl;
                cout << "Warnings             : " << user.getWarningCount() << endl;
            }

            if (userCount == 0) {
                cout << "No regular users found." << endl;
            }
            else {
                cout << endl << "Total Regular Users: " << userCount << endl;
            }

            break;
        }

        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
