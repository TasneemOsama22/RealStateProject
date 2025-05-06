#include<iostream>
#include"Admin.h"
#include "unordered_map"
#include <string>
#include <list>
#include <vector>
#include <iomanip>
#include<queue>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
Admin::Admin(string Id, string password) {
    this->Id = Id;
    this->Password = password;
}

Admin::Admin(const string Username, const string Email, const string Id, const string Pass) {
    this->Username = Username;
    this->Email = Email;
    this->Id = Id;
    this->Password = Pass;
}

void Admin::setUsername(const string& newUsername) {
    Username = newUsername;
}

void Admin::setEmail(const string& newEmail) {
    Email = newEmail;
}

void Admin::setPassword(const string& newPassword) {
    Password = newPassword;
}

void Admin::setId(const string& newId) {
    Id = newId;
}
//getters
string Admin::getUsername() const {
    return Username;
}

string Admin::getEmail() const {
    return Email;
}

string Admin::getPassword() const {
    return Password;
}

string Admin::getId() const {
    return Id;
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



void Admin::ReviewPendingAds(vector<Property>& PendingAds, vector<Property>& ApprovedAds, vector<Property>& RejectedAds, unordered_map<string, User>& Users) {
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

            RejectAd(ad, Userid, PendingAds, ApprovedAds, RejectedAds, Users);
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
    Users[UserId].InboxMessages.push("Your property listing has been approved and is now visible to other users. Good luck!");


    if (!Users[UserId].UserProperty.empty()) {
        Users[UserId].UserProperty.back().setStatus(PropertyStatus::Approved);
    }
}

void Admin::RejectAd(Property p, string UserId, vector<Property>& PendingAds, vector<Property>& ApprovedAds, vector<Property>& RejectedAds, unordered_map<string, User>& Users) {

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

    Users[UserId].InboxMessages.push("Warning! Your last Property listing has been rejected. Reason: " + reason);

    int warnings = Users[UserId].getWarningCount();
    Users[UserId].setWarningCount(++warnings);

    if (!Users[UserId].UserProperty.empty()) {
        Users[UserId].UserProperty.back().setStatus(PropertyStatus::Rejected);
    }

    if (ChoiseNumber == 6 || warnings == 3) {
        blockUser(UserId, Users);
    }
    else if (ChoiseNumber == 4 || ChoiseNumber == 7) {
        banUser(UserId, Users, ApprovedAds, PendingAds);
    }
    RejectedAds.push_back(p);
}




void Admin::blockUser(string UserId, unordered_map <string, User>& Users) {
    Users[UserId].InboxMessages.push("Dear user\nYour account has been temporarily blocked due to a violation of our platform's rules or policies\nPlease note that this block is only temporary and will be lifted automatically after the designated period\nWe encourage you to review our community guidelines to avoid future issues\nThank you for your understanding\n_The Real Estate Portal Team");
    Users[UserId].setIsBlocked(true);
    Users[UserId].setCanPost(false);
    Users[UserId].setblockDaysRemaining(3);
}
void Admin::unblockUser(string UserId, unordered_map <string, User>& Users) {
    Users[UserId].InboxMessages.push("Dear user\nYour temporary block has been lifted, and you now have full access to your account again.\n\nThank you for your cooperation.\n_The Real Estate Portal Team");
    Users[UserId].setCanPost(true);
    Users[UserId].setIsBlocked(false);
    Users[UserId].setblockDaysRemaining(0);
}

void Admin::banUser(string UserId, unordered_map <string, User>& Users, vector<Property>& ApprovedAds, vector<Property>& PendingAds)
{
    Users[UserId].setCanPost(false);
    Users[UserId].setIsBanned(true);
    Users[UserId].InboxMessages.push("Dear user\nYour account has been permanently banned due to serious violations of our platform's rules and regulations.\n_The Real Estate Portal Team.");
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
    cout << "This User has been banned\n";
}
void Admin::unbanUser(string UserId, unordered_map <string, User>& Users) {
    Users[UserId].InboxMessages.push("Dear user\nWe would like to inform you that your account has been successfully unbanned.\nYou can now access all platform features, including posting new property listings.\n\nWelcome back!\n_The Real Estate Portal Team");
    Users[UserId].setCanPost(true);
    Users[UserId].setIsBanned(false);
    cout << "This User has been unbanned\n";
}
void Admin::ModerateUserActivity(unordered_map<string, User>& Users, vector<Property>ApprovedAds, vector<Property>PendingAds) {
    cout << "\n====== User Moderation ======\n";
    cout << "Entre User Id to manage: ";
    string Id;
    cin >> Id;
    if (Users.find(Id) == Users.end()) {
        cout << "User not found.\n";
        return;
    }
    User& user = Users[Id];
    cout << left
        << setw(15) << "Manging User"
        << setw(15) << "UserID"
        << setw(15) << "Warnings"
        << setw(15) << "Blocked"
        << setw(15) << "Banned";
    cout << endl;

    cout << string(80, '-') << endl;

    cout << left
        << setw(15) << user.username
        << setw(15) << user.userId
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
    while (choice < 1 || choice>6) {
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
        banUser(Id, Users, ApprovedAds, PendingAds);
        break;
    case 6:
        unbanUser(Id, Users);
        break;
    default:
        cout << "Invalid choice.\n";
        break;
    }

}
void Admin::ViewUserInfo(unordered_map<string, User>& Users) {
    int option;
    cout << "Choose an option:\n";
    cout << "1. View specific user by ID\n";
    cout << "2. View multiple users by IDs\n";
    cout << "3. View all users\n";
    cout << "Enter your choice (1-3): ";
    cin >> option;

    queue<User> userQueue;
    cin.ignore();

    if (option == 1) {
        string id;
        cout << "Enter User ID: ";
        getline(cin, id);
        if (Users.find(id) != Users.end()) {
            userQueue.push(Users[id]);
        }
        else {
            cout << "User not found.\n";
            return;
        }

    }
    else if (option == 2) {
        int count;
        cout << "How many users do you want to view? ";
        cin >> count;
        cin.ignore();
        for (int i = 0; i < count; i++) {
            string id;
            cout << "Enter User ID " << (i + 1) << ": ";
            getline(cin, id);
            if (Users.find(id) != Users.end()) {
                userQueue.push(Users[id]);
            }
            else {
                cout << "User ID " << id << " not found, skipping.\n";
            }
        }

    }
    else if (option == 3) {
        for (const auto& user : Users) {
            userQueue.push(user.second);
        }
    }
    else {
        cout << "Invalid option.\n";
        return;
    }


    cout << "\n" << left
        << setw(15) << "User ID"
        << setw(20) << "Username"
        << setw(10) << "Warnings"
        << setw(10) << "Blocked"
        << setw(10) << "Banned"
        << setw(10) << "CanPost" << endl;

    cout << string(75, '-') << endl;


    while (!userQueue.empty()) {
        User user = userQueue.front();
        userQueue.pop();

        cout << left
            << setw(15) << user.userId
            << setw(20) << user.getUsername()
            << setw(10) << user.getWarningCount()
            << setw(10) << (user.getIsBlocked() ? "Yes" : "No")
            << setw(10) << (user.getIsBanned() ? "Yes" : "No")
            << setw(10) << (user.getCanPost() ? "Yes" : "No")
            << endl;
    }
}

bool Admin::checkisadmin(string& username, string& password, unordered_map<string, string>& Admins) {

    auto adminsdata = Admins.find(password);
    return adminsdata != Admins.end() && adminsdata->second == username;

}

void Admin::AddnewAdmin(unordered_map<string, string>& Admins,
    unordered_map<string, User>& Users,
    vector<Property>& PendingAds,
    vector<Property>& ApprovedAds) {

    string username, password;

    cout << "Enter new username:" << endl;
    getline(cin, username);
    cout << "Enter new password:" << endl;
    getline(cin, password);

    Admins[password] = username;
    cout << "New admin added successfuly." << endl;
}

void Admin::RemoveAdmin(unordered_map<string, string>& Admins,
    unordered_map<string, User>& Users,
    vector<Property>& PendingAds,
    vector<Property>& ApprovedAds,
    vector<Property>& RejectedAds,
    vector<string>types,
    vector<string>locations) {
    string password;
    cout << "Enter password of the admin to remove:" << endl;
    getline(cin, password);

    auto removepass = Admins.find(password);
    if (removepass != Admins.end()) {
        Admins.erase(removepass);
        cout << "Admin removed successfuly.\n" << endl;
        showAdminDashboard(Admins, Users, PendingAds, ApprovedAds, RejectedAds, types, locations);
    }
    else {
        cout << "Not found admin has that password!" << endl;
    }
}

void Admin::showAdminDashboard(unordered_map<string, string>& Admins,
    unordered_map<string, User>& Users,
    vector<Property>& PendingAds,
    vector<Property>& ApprovedAds,
    vector<Property>& RejectedAds,
    vector<string>types,
    vector<string>locations) {
    int choice;
    while (true) {
        cout << "Admin Dashboard" << endl;
        cout << "--------------------------" << endl;
        cout << "1. Add New property" << endl;
        cout << "2. Edit property" << endl;
        cout << "3. Remove property" << endl;
        cout << "4. Highlight specific property" << endl;
        cout << "5. Add new admin" << endl;
        cout << "6. Remove admin" << endl;
        cout << "7. Review pending property lists" << endl;
        cout << "8. View approved Property lists" << endl;
        cout << "9. Moderate user activities" << endl;
        cout << "10. View user info" << endl;
        cout << "11. Exit" << endl;
        cout << "--------------------------" << endl;
        cout << "Enter your choice (1-11)" << endl;

        cin >> choice;
        cout << endl;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Add new property:-" << endl;
            addProperty(ApprovedAds, PendingAds, RejectedAds, types, locations);
            break;
        case 2:
            cout << "Edit property:-" << endl;
            editProperty(ApprovedAds, PendingAds, RejectedAds, types, locations);
            break;
        case 3:
            cout << "Remove property:-" << endl;
            removeProperty(ApprovedAds, PendingAds, RejectedAds);
            break;
        case 4:
            cout << "Highlight property:-" << endl;
            toggleHighlightProperty(ApprovedAds, PendingAds, RejectedAds);
            break;

        case 5:
            cout << "Add new admin:-" << endl;
            AddnewAdmin(Admins, Users, PendingAds, ApprovedAds);
            break;
        case 6:
            cout << "Remove Admin:-" << endl;
            RemoveAdmin(Admins, Users, PendingAds, ApprovedAds, RejectedAds, types, locations);
            break;
        case 7:
            ReviewPendingAds(PendingAds, ApprovedAds, RejectedAds, Users);
            break;
        case 8:
            ViewApprovedAds(ApprovedAds);
            break;
        case 9:
            ModerateUserActivity(Users, ApprovedAds, PendingAds);
            break;
        case 10:
            ViewUserInfo(Users);
            break;
        case 11:
            cout << "Logging out... " << endl;
            return;
        default:
            cout << "Invalid choice, please enter a choice from 1 to 12." << endl;
        }
    }
}


void Admin::loadListings(vector<Property>& approvedProperties,
    vector<Property>& pendingProperties,
    vector<Property>& rejectedProperties) {
    ifstream file("listings.txt");
    if (!file) {
        cout << "Error: Could not open listings.txt\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        Property p;
        p.fromFileString(line);

        switch (p.getStatus()) {
        case Approved: approvedProperties.push_back(p); break;
        case Pending: pendingProperties.push_back(p); break;
        case Rejected: rejectedProperties.push_back(p); break;
        }
    }

    file.close();
}

void Admin::saveListings(vector<Property>& approvedProperties,
    vector<Property>& pendingProperties,
    vector<Property>& rejectedProperties) {
    ofstream file("listings.txt");
    if (!file) {
        cout << "Error: Could not open listings.txt for writing\n";
        return;
    }

    for (const Property& p : approvedProperties)
        file << p.toFileString() << endl;
    for (const Property& p : pendingProperties)
        file << p.toFileString() << endl;
    for (const Property& p : rejectedProperties)
        file << p.toFileString() << endl;

    file.close();
}

int Admin::generateNewId(vector<Property>& approvedProperties,
    vector<Property>& pendingProperties,
    vector<Property>& rejectedProperties) {
    int maxId = 1000;

    for (const Property& p : approvedProperties)
        maxId = max(maxId, p.getId());
    for (const Property& p : pendingProperties)
        maxId = max(maxId, p.getId());
    for (const Property& p : rejectedProperties)
        maxId = max(maxId, p.getId());


    return maxId + 1;
}

string Admin::chooseType(vector<string>& types) {
    int choice;
    while (true) {
        cout << "\nAvailable Types: \n";
        for (int i = 0; i < types.size(); ++i) {
            cout << i + 1 << ". " << types[i] << "\n";
        }
        cout << "Enter the number corresponding to the property type: ";
        cin >> choice;

        if (choice >= 1 && choice <= types.size()) {
            return types[choice - 1];
        }

        cout << "Invalid choice. Please try again.\n";
    }
}

string Admin::chooseLocation(vector<string>& locations) {
    int choice;
    while (true) {
        cout << "\nAvailable Locations: \n";
        for (int i = 0; i < locations.size(); ++i) {
            cout << i + 1 << ". " << locations[i] << "\n";
        }
        cout << "Enter the number corresponding to the property location: ";
        cin >> choice;

        if (choice >= 1 && choice <= locations.size()) {
            return locations[choice - 1];
        }

        cout << "Invalid choice. Please try again.\n";
    }
}

void Admin::addProperty(vector<Property>& approvedProperties,
    vector<Property>& pendingProperties,
    vector<Property>& rejectedProperties,
    vector<string>& types,
    vector<string>& locations) {
    Property p;
    cout << "\n--- Add New Property ---\n";

    p.setId(generateNewId(approvedProperties, pendingProperties, rejectedProperties));
    cin.ignore();

    string title;
    cout << "Enter Title: ";
    getline(cin, title);
    p.setTitle(title);

    p.setType(chooseType(types));
    p.setLocation(chooseLocation(locations));

    double price;
    do {
        cout << "Enter Price: ";
        cin >> price;
        if (price < 0)
            cout << "Price cannot be negative. Try again.\n";
        cin.ignore();  // Clear the input buffer
    } while (price < 0);
    p.setPrice(price);

    string owner;
    cout << "Enter Owner Name: ";
    getline(cin, owner);  // No need for cin.ignore() here because getline doesn't leave an extra newline
    p.setOwnerName(owner);

    string userId;
    cout << "Enter User ID: ";
    getline(cin, userId);  // No need for cin.ignore() here either
    p.setUserId(userId);

    double area;
    do {
        cout << "Enter Area (Square meter): ";
        cin >> area;
        if (area < 0) {
            cout << "Area cannot be negative. Try again.\n";
        }
        cin.ignore();  // Clear the input buffer
    } while (area < 0);
    p.setArea(area);

    int bedrooms;
    do {
        cout << "Enter Number of Bedrooms: ";
        cin >> bedrooms;
        if (bedrooms < 0) {
            cout << "Bedrooms cannot be negative. Try again.\n";
        }
        cin.ignore();  // Clear the input buffer
    } while (bedrooms < 0);
    p.setBedrooms(bedrooms);

    int bathrooms;
    do {
        cout << "Enter Number of Bathrooms: ";
        cin >> bathrooms;
        if (bathrooms < 0) {
            cout << "Bathrooms cannot be negative. Try again.\n";
        }
        cin.ignore();  // Clear the input buffer
    } while (bathrooms < 0);
    p.setBathrooms(bathrooms);

    int isHighlighted;
    do {
        cout << "Highlight this property? (1: Yes, 0: No): ";
        cin >> isHighlighted;
        if (isHighlighted != 0 && isHighlighted != 1)
            cout << "Invalid input. Please enter 1 (Yes) or 0 (No).\n";
        cin.ignore();  // Clear the input buffer
    } while (isHighlighted != 0 && isHighlighted != 1);

    p.setHighlighted(isHighlighted == 1);

    p.setStatus(Pending);
    pendingProperties.push_back(p);

    //saveListings();

    cout << "\nProperty added successfully! ID: " << p.getId() << "\n";
}

void Admin::editProperty(vector<Property>& approvedProperties,
    vector<Property>& pendingProperties,
    vector<Property>& rejectedProperties,
    vector<string>& types,
    vector<string>& locations) {
    vector<Property>* selectedList = nullptr;
    int choice1;
    cout << "\n--- Edit Property ---\n";

    while (true) {
        cout << "\nChoose the property list to edit from:\n";
        cout << "1. Approved\n";
        cout << "2. Pending\n";
        cout << "3. Rejected\n";
        cout << "Enter your choice: ";
        cin >> choice1;

        if (choice1 == 1) {
            selectedList = &approvedProperties;
            break;
        }
        else if (choice1 == 2) {
            selectedList = &pendingProperties;
            break;
        }
        else if (choice1 == 3) {
            selectedList = &rejectedProperties;
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    cout << "Enter the ID of the property to edit: ";
    int id;
    cin >> id;

    for (size_t i = 0; i < selectedList->size(); ++i) {
        if ((*selectedList)[i].getId() == id) {
            Property& p = (*selectedList)[i];
            cout << "Editing property with ID " << p.getId() << ":\n";

            int choice;
            do {
                cout << "\nWhich property field would you like to edit?\n";
                cout << "1. Title (" << p.getTitle() << ")\n";
                cout << "2. Type (" << p.getType() << ")\n";
                cout << "3. Location (" << p.getLocation() << ")\n";
                cout << "4. Price (" << p.getPrice() << ")\n";
                cout << "5. Owner Name (" << p.getOwnerName() << ")\n";
                cout << "6. Area (" << p.getArea() << " Square meter)\n";
                cout << "7. Bedrooms (" << p.getBedrooms() << ")\n";
                cout << "8. Bathrooms (" << p.getBathrooms() << ")\n";
                cout << "9. Status (" << (p.getStatus() == Approved ? "Approved" : (p.getStatus() == Pending ? "Pending" : "Rejected")) << ")\n";
                cout << "10. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                cin.ignore();
                switch (choice) {
                case 1: {
                    string newTitle;
                    cout << "Enter new Title: ";
                    getline(cin, newTitle);
                    p.setTitle(newTitle);
                    break;
                }
                case 2: {
                    p.setType(chooseType(types));
                    break;
                }
                case 3: {
                    p.setLocation(chooseLocation(locations));
                    break;
                }
                case 4: {
                    double newPrice;
                    do {
                        cout << "Enter new Price: ";
                        cin >> newPrice;
                        if (newPrice < 0)
                            cout << "Price cannot be negative. Please enter a valid price.\n";
                    } while (newPrice < 0);
                    p.setPrice(newPrice);
                    break;
                }
                case 5: {
                    string newOwner;
                    cout << "Enter new Owner Name: ";
                    getline(cin, newOwner);
                    p.setOwnerName(newOwner);
                    break;
                }
                case 6: {
                    double newArea;
                    do {
                        cout << "Enter new Area (Square meter): ";
                        cin >> newArea;
                        if (newArea < 0)
                            cout << "Area cannot be negative. Please enter a valid area.\n";
                    } while (newArea < 0);
                    p.setArea(newArea);
                    break;
                }
                case 7: {
                    int newBedrooms;
                    do {
                        cout << "Enter new Bedrooms: ";
                        cin >> newBedrooms;
                        if (newBedrooms < 0)
                            cout << "Bedrooms cannot be negative. Please enter a valid number.\n";
                    } while (newBedrooms < 0);
                    p.setBedrooms(newBedrooms);
                    break;
                }
                case 8: {
                    int newBathrooms;
                    do {
                        cout << "Enter new Bathrooms: ";
                        cin >> newBathrooms;
                        if (newBathrooms < 0)
                            cout << "Bathrooms cannot be negative. Please enter a valid number.\n";
                    } while (newBathrooms < 0);
                    p.setBathrooms(newBathrooms);
                    break;
                }
                case 9: {
                    int newStatus;
                    do {
                        cout << "Enter new Status (0: Pending, 1: Approved, 2: Rejected): ";
                        cin >> newStatus;
                        if (newStatus < 0 || newStatus > 2)
                            cout << "Invalid status. Please enter 0, 1, or 2.\n";
                    } while (newStatus < 0 || newStatus > 2);

                    if (newStatus != p.getStatus()) {
                        Property updated = p;
                        updated.setStatus(static_cast<PropertyStatus>(newStatus));

                        switch (newStatus) {
                        case Approved: approvedProperties.push_back(updated); break;
                        case Pending: pendingProperties.push_back(updated); break;
                        case Rejected: rejectedProperties.push_back(updated); break;
                        }

                        selectedList->erase(selectedList->begin() + i);

                        cout << "Property moved to new list and updated.\n";
                        saveListings(approvedProperties, pendingProperties, rejectedProperties);
                        return;
                    }
                    break;
                }
                case 10:
                    cout << "Exiting Edit Menu.\n";
                    break;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            } while (choice != 10);

            //saveListings(approvedProperties,pendingProperties,rejectedProperties);
            cout << "Property updated and saved.\n";
            return;
        }
    }
    cout << "Property not found.\n";
}

void Admin::removeProperty(vector<Property>& approvedProperties,
    vector<Property>& pendingProperties,
    vector<Property>& rejectedProperties) {
    vector<Property>* selectedList = nullptr;
    int choice;

    cout << "\n--- Remove Property ---\n";

    while (true) {
        cout << "Select the list to remove from:\n";
        cout << "1. Approved Properties\n";
        cout << "2. Pending Properties\n";
        cout << "3. Rejected Properties\n";
        cout << "4. Back\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            selectedList = &approvedProperties;
            break;
        }
        else if (choice == 2) {
            selectedList = &pendingProperties;
            break;
        }
        else if (choice == 3) {
            selectedList = &rejectedProperties;
            break;
        }
        else if (choice == 4) {
            cout << "Returning to main menu...\n";
            return;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    int id;
    cout << "Enter Property ID to remove: ";
    cin >> id;

    bool found = false;
    for (auto it = selectedList->begin(); it != selectedList->end(); ++it) {
        if (it->getId() == id) {
            selectedList->erase(it);
            found = true;
            break;
        }
    }

    if (found) {
        //saveListings(approvedProperties,pendingProperties,rejectedProperties);
        cout << "Property removed successfully.\n";
    }
    else {
        cout << "Property not found in the selected list.\n";
    }
}

bool Admin::compareHighlighted(const Property& a, const Property& b) {
    return a.isHighlighted() > b.isHighlighted();
}
void Admin::toggleHighlightProperty(vector<Property>& approvedProperties,
    vector<Property>& pendingProperties,
    vector<Property>& rejectedProperties) {
    vector<Property>* selectedList = nullptr;
    int choice;

    cout << "\n--- Toggle Highlight ---\n";

    while (true) {
        cout << "Select the list to toggle highlight from:\n";
        cout << "1. Approved Properties\n";
        cout << "2. Pending Properties\n";
        cout << "3. Rejected Properties\n";
        cout << "4. Back\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            selectedList = &approvedProperties;
            break;
        }
        else if (choice == 2) {
            selectedList = &pendingProperties;
            break;
        }
        else if (choice == 3) {
            selectedList = &rejectedProperties;
            break;
        }
        else if (choice == 4) {
            cout << "Returning to main menu...\n";
            return;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    int id;
    cout << "Enter Property ID: ";
    cin >> id;

    for (Property& p : *selectedList) {
        if (p.getId() == id) {
            p.setHighlighted(!p.isHighlighted());
            cout << "Highlight status toggled successfully " << ".\n";
            //saveListings();
            return;
        }
    }

    cout << "Property not found in the selected list.\n";
}

void Admin::showAllProperties(vector<Property>& approvedProperties,
    vector<Property>& pendingProperties,
    vector<Property>& rejectedProperties) {
    cout << fixed << setprecision(2);

    vector<Property>* listingsToShow = nullptr;

    while (true) {
        int choice;
        cout << "\nChoose which listings to display:\n";
        cout << "1. Approved Listings\n";
        cout << "2. Pending Listings\n";
        cout << "3. Rejected Listings\n";
        cout << "4. Show All Listings\n";
        cout << "5. Back\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            listingsToShow = &approvedProperties;
            break;
        }
        else if (choice == 2) {
            listingsToShow = &pendingProperties;
            break;
        }
        else if (choice == 3) {
            listingsToShow = &rejectedProperties;
            break;
        }
        else if (choice == 4) {

            vector<Property> combinedListings;
            combinedListings.insert(combinedListings.end(), approvedProperties.begin(), approvedProperties.end());
            combinedListings.insert(combinedListings.end(), pendingProperties.begin(), pendingProperties.end());
            combinedListings.insert(combinedListings.end(), rejectedProperties.begin(), rejectedProperties.end());


            // sort(combinedListings.begin(), combinedListings.end(), compareHighlighted);


            cout << "\n======================================================== Property Listings =======================================================\n";
            cout << left
                << setw(5) << "HL"
                << setw(7) << "ID"
                << setw(20) << "Title"
                << setw(13) << "Type"
                << setw(15) << "Location"
                << setw(13) << "Price"
                << setw(16) << "Owner"
                << setw(10) << "Bedrooms"
                << setw(12) << "Bathrooms"
                << setw(10) << "Area"
                << setw(15) << "Status" << endl;

            cout << "----------------------------------------------------------------------------------------------------------------------------------\n";

            for (Property& p : combinedListings) {
                cout << setw(5) << (p.isHighlighted() ? "*" : "")
                    << setw(7) << p.getId()
                    << setw(20) << p.getTitle()
                    << setw(13) << p.getType()
                    << setw(15) << p.getLocation()
                    << setw(13) << p.getPrice()
                    << setw(16) << p.getOwnerName()
                    << setw(10) << p.getBedrooms()
                    << setw(12) << p.getBathrooms()
                    << setw(10) << p.getArea()
                    << setw(15) << (p.getStatus() == Approved ? "Approved" : (p.getStatus() == Pending ? "Pending" : "Rejected"))
                    << endl;
            }

            if (combinedListings.empty()) {
                cout << "No properties listed yet.\n";
            }
            cout << "==================================================================================================================================\n";
            return;
        }
        else if (choice == 5) {
            cout << "Returning to the main menu...\n";
            return;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }


    //sort(listingsToShow.begin(), listingsToShow.end(), compareHighlighted);

    cout << "\n======================================================== Property Listings =======================================================\n";
    cout << left
        << setw(5) << "HL"
        << setw(7) << "ID"
        << setw(20) << "Title"
        << setw(13) << "Type"
        << setw(15) << "Location"
        << setw(13) << "Price"
        << setw(16) << "Owner"
        << setw(10) << "Bedrooms"
        << setw(12) << "Bathrooms"
        << setw(10) << "Area"
        << setw(15) << "Status" << endl;

    cout << "----------------------------------------------------------------------------------------------------------------------------------\n";

    for (Property& p : *listingsToShow) {
        cout << setw(5) << (p.isHighlighted() ? "*" : "")
            << setw(7) << p.getId()
            << setw(20) << p.getTitle()
            << setw(13) << p.getType()
            << setw(15) << p.getLocation()
            << setw(13) << p.getPrice()
            << setw(16) << p.getOwnerName()
            << setw(10) << p.getBedrooms()
            << setw(12) << p.getBathrooms()
            << setw(10) << p.getArea()
            << setw(15) << (p.getStatus() == Approved ? "Approved" : (p.getStatus() == Pending ? "Pending" : "Rejected"))
            << endl;
    }

    if (listingsToShow->empty()) {
        cout << "No properties listed yet.\n";
    }

    cout << "==================================================================================================================================\n";
}




