#include<iostream>
#include"Admin.h"
#include "unordered_map"
#include <string>
#include <list>
#include <vector>
#include <iomanip>
using namespace std;
Admin::Admin(string Id, string password) {
    this->Id = Id;
    this->Password = password;
}


void Admin::ViewApprovedAds(vector<Property>& ApprovedAds) {
    int AdsCount = 0;
    for (int i = 0; i < ApprovedAds.size(); i++) {
        cout << "\n========== Approved Property Ad ==========" << endl;
        cout << "Ad Number          : " << ++AdsCount << endl;
        cout << "Ad ID              : " << ApprovedAds[i].getId() << endl;
        cout << "Title              : " << ApprovedAds[i].getTitle() << endl;
        cout << "User ID            : " << ApprovedAds[i].getUserId() << endl;
        cout << "User Name          : " << ApprovedAds[i].getOwnerUsername() << endl;
        cout << "Location           : " << ApprovedAds[i].getLocation() << endl;
        cout << "Area               : " << ApprovedAds[i].getArea() << endl;
        cout << "Number of Bedrooms : " << ApprovedAds[i].getBedrooms() << endl;
        cout << "Number of Bathrooms: " << ApprovedAds[i].getBathrooms() << endl;
        cout << "Price              : " << ApprovedAds[i].getPrice() << " EGP" << endl;
        cout << "==========================================\n" << endl;
    }


}



void Admin::ReviewPendingAds(vector<Property>& PendingAds, vector<Property>& ApprovedAds, unordered_map<string, User>& Users) {
    if (PendingAds.empty()) {
        cout << "There is no pending Ads\n";
        return;
    }
    int counter = 0;

    cout << "There are " << PendingAds.size() << " Pending Property Lists\n";

    for (int i = 0; i < PendingAds.size(); ) {
        Property ad = PendingAds[i];
        string Userid = ad.getUserId();

        cout << "\n================= Pending Property Review=================" << endl;
        cout << "Ad Number          : " << ++counter << endl;
        cout << "Ad ID              : " << ad.getId() << endl;
        cout << "Title              : " << ad.getTitle() << endl;
        cout << "User ID            : " << ad.getUserId() << endl;
        cout << "User Name          : " << ad.getOwnerUsername() << endl;
        cout << "Location           : " << ad.getLocation() << endl;
        cout << "Area               : " << ad.getArea() << endl;
        cout << "Number of Bedrooms : " << ad.getBedrooms() << endl;
        cout << "Number of Bathrooms: " << ad.getBathrooms() << endl;
        cout << "Price       : " << ad.getPrice() << " EGP" << endl;
        cout << "=========================================================" << endl;

        cout << "\nChoose an action for this property:\n";
        cout << "  1. Approve\n";
        cout << "  2. Reject\n";
        cout << "  3. Skip to next\n";
        cout << "Enter your choice (1/2/3): ";
        int choice;
        cin >> choice;

        while (choice < 1 || choice > 3) {
            cout << "Invalid choice! Please try again: ";
            cin >> choice;
        }



        if (choice == 1) {

            ApproveAd(ad, ApprovedAds, PendingAds, Userid, Users);
            cout << "\nAd approved successfully and moved to approved list.\n\n";
        }
        else if (choice == 2) {

            RejectAd(ad, Userid, PendingAds, Users);
            cout << "\nAd rejected and removed from the pending list.\n";

        }
        else if (choice == 3) {

            i++;
            if (i == PendingAds.size()) {
                cout << "\nThere are no pending property ads to review.\n";
                return;
            }
        }


        if (PendingAds.empty()) {
            cout << "\nThere are no more pending ads to review.\n";
            return;
        }
    }
}

void Admin::ApproveAd(Property p, vector<Property>& ApprovedAds, vector<Property>& PendingAds, string UserId, unordered_map<string, User>& Users) {
    for (int i = 0; i < PendingAds.size(); ++i) {
        if (p.getId() == PendingAds[i].getId()) {
            PendingAds.erase(PendingAds.begin() + i);
            break;
        }
    }

    ApprovedAds.push_back(p);
    Users[UserId].InboxMesseges.push("Your property listing has been approved and is now visible to other users. Good luck!");


    if (!Users[UserId].UserProperty.empty()) {
        Users[UserId].UserProperty.back().setStatus(PropertyStatus::Approved);
    }
}

void Admin::RejectAd(Property p, string UserId, vector<Property>& PendingAds, unordered_map<string, User>& Users) {

    string reason = "No reason specified";
    cout << "\nPlease choose a reason for rejection (will be sent to the user): \n";
    cout << "1. The price is unrealistic or too high\n";
    cout << "2. Incomplete or unclear property information\n";
    cout << "3. Missing or inappropriate images\n";
    cout << "4. The description contains inappropriate or prohibited content\n";
    cout << "5. Invalid property location\n";
    cout << "6. Duplicate or very similar to an existing listing\n";
    cout << "7. Violates the platform's posting policies\n";
    cout << "8. Unsupported or undefined property type\n";
    cout << "9. Other (please specify)\n";
    cout << "Enter your choice (1-9): ";
    int ChoiseNumber;
    cin >> ChoiseNumber;

    while (ChoiseNumber < 1 || ChoiseNumber > 9) {
        cout << "Invalid choice! Please try again: ";
        cin >> ChoiseNumber;
    }

    switch (ChoiseNumber) {
    case 1:
        reason = "The price is unrealistic or too high.";
        break;
    case 2:
        reason = "Incomplete or unclear property information.";
        break;
    case 3:
        reason = "Missing or inappropriate images.";
        break;
    case 4:
        reason = "The description contains inappropriate or prohibited content.";
        break;
    case 5:
        reason = "Invalid property location.";
        break;
    case 6:
        reason = "Duplicate or very similar to an existing listing.";
        break;
    case 7:
        reason = "Violates the platform's posting policies.";
        break;
    case 8:
        reason = "Unsupported or undefined property type.";
        break;
    case 9:
        cout << "Please type your reason: ";
        cin.ignore();
        getline(cin, reason);
        break;
    }
    for (int i = 0; i < PendingAds.size(); i++) {
        if (p.getId() == PendingAds[i].getId()) {
            PendingAds.erase(PendingAds.begin() + i);
            break;
        }
    }

    Users[UserId].InboxMesseges.push("Warning! Your last Property listing has been rejected. Reason: " + reason);

    int warnings = Users[UserId].getWarningCount();
    Users[UserId].setWarningCount(++warnings);

    if (!Users[UserId].UserProperty.empty()) {
        Users[UserId].UserProperty.back().setStatus(PropertyStatus::Rejected);
    }

    if (ChoiseNumber == 6 || warnings == 3) {
        blockUser(UserId, Users);
    }
    else if (ChoiseNumber == 4 || ChoiseNumber == 7) {
        banUser(UserId, Users);
    }
}




void Admin::blockUser(string UserId, unordered_map <string, User>& Users) {
    Users[UserId].InboxMesseges.push("Dear user\nYour account has been temporarily blocked due to a violation of our platform's rules or policies\nPlease note that this block is only temporary and will be lifted automatically after the designated period\nWe encourage you to review our community guidelines to avoid future issues\nThank you for your understanding\n_The Real Estate Portal Team");
    Users[UserId].setIsBlocked(true);
    Users[UserId].setCanPost(false);
    Users[UserId].setblockDaysRemaining(3);
}
void Admin::unblockUser(string UserId, unordered_map <string, User>& Users) {
    Users[UserId].InboxMesseges.push("Dear user\nYour temporary block has been lifted, and you now have full access to your account again.\n\nThank you for your cooperation.\n_The Real Estate Portal Team");
    Users[UserId].setCanPost(true);
    Users[UserId].setIsBlocked(false);
    Users[UserId].setblockDaysRemaining(0);
}

void Admin::banUser(string UserId, unordered_map <string, User>& Users)
{
    Users[UserId].setCanPost(false);
    Users[UserId].setIsBanned(true);
    Users[UserId].InboxMesseges.push("Dear user\nYour account has been permanently banned due to serious violations of our platform's rules and regulations.\n_The Real Estate Portal Team.");
    // Delete user's properties from the approved list
    ApprovedAds.erase(remove_if(ApprovedAds.begin(), ApprovedAds.end(),
        [&](const Property& prop) {
            return prop.getUserId() == UserId;
        }),
        ApprovedAds.end());

    // Delete user's properties from the pending list
    PendingAds.erase(remove_if(PendingAds.begin(), PendingAds.end(),
        [&](const Property& prop) {
            return prop.getUserId() == UserId;
        }),
        PendingAds.end());
}
void Admin::unbanUser(string UserId, unordered_map <string, User>& Users) {
    Users[UserId].InboxMesseges.push("Dear user\nWe would like to inform you that your account has been successfully unbanned.\nYou can now access all platform features, including posting new property listings.\n\nWelcome back!\n_The Real Estate Portal Team");
    Users[UserId].setCanPost(true);
    Users[UserId].setIsBanned(false);
}
void Admin::ModerateUserActivity(unordered_map<string, User>& Users) {
    cout << "\n====== User Moderation ======\n";
    cout << "Entre User Id to manage: ";
    string Id;
    cin >> Id;
    if (Users.find(Id) == Users.end()) {
        cout << "User not found.\n";
        return;
    }
    User& user = Users[userId];
    cout << left
        << setw(15) << "Manging User"
        << setw(15) << "UserID"
        << setw(15) << "Warnings"
        << setw(15) << "Blocked"
        << setw(15) << "Banned";

    cout << string(80, '-') << endl;

    cout << left
        << setw(15) << user.username
        << setw(15) << user.UserId
        << setw(15) << user.getWarningCount()
        << setw(15) << (user.getIsBlocked() ? "Yes" : "No")
        << setw(15) << (user.getIsBanned() ? "Yes" : "No");

    cout << "\nChoose an action:\n";
    cout << "1." << "Add warning\n";
    cout << "2." << "Remove warning\n";
    cout << "3." << "Block user\n";
    cout << "4." << "Unblock user\n";
    cout << "5." << "Ban user\n";
    cout << "6." << "Unban user\n";
    cout << "Enter your choice (1-6): ";
    int choice;
    cin >> choice;
    while (choise < 1 || choise>6) {
        cout << "Invalide choice\nEnter your choice (1-6): ";
        cin >> choice;
    }
    switch (choice)
    {
    case 1:
        user.setWarningCount(user.getWarningCount() + 1);
        if (user.getWarningCount() == 3) {
            blockUser(Id, Users);
            user.setWarningCount(0);
        }
        cout << "Warning added.\n";
        break;
    case 2:
        if (user.getWarningCount() > 0) {
            user.setWarningCount(user.getWarningCount() - 1);
            cout << "Warning removed.\n";
        }
        else {
            cout << "User has no warnings.\n";
        }
        break;
    case 3:
        blockUser(Id, Users);
        break;
    case 4:
        unblockUser(Id, Users);
        break;
    case 5:
        banUser(Id, Users);
        break;
    case 6:
        unbanUser(Id, Users);
        break;
    default:
        cout << "Invalid choice.\n";
        break;
    }

        
}


