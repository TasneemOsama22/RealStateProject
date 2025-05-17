#pragma once
#include <vector>
#include <list>
#include "User.h"
#include <string>
#include "property.h"
#include <unordered_map>
using namespace std;

class Admin
{
private:
    string Id;
    string Password;
    string Username;
    string Email;



public:
    Admin();
    Admin(const string Id, const string Pass);
    Admin(const string Username, const string Email, const string Id, const string Pass);
    //setter
    void setUsername(const string& newUsername);

    void setEmail(const string& newEmail);

    void setPassword(const string& newPassword);
    void setId(const string& newId);
    //getter
    string getUsername()const;
    string getEmail()const;
    string getPassword()const;
    string getId()const;
    // view all pending ads
    void ReviewPendingAds(vector<Property>& PendingAds,
                         vector<Property>& ApprovedAds,
                         vector<Property>& RejectedAds, 
                         unordered_map <string, User>& Users);
    // Approve ad
    void ApproveAd(Property ad, 
                   vector<Property>& approvedAds, 
                   vector<Property>& PendingAds,
                   string UserId, 
                   unordered_map <string,
                   User>& Users);
    // Reject ad
    void RejectAd(Property ad, 
                 string UserId, 
                 vector<Property>& pendingAds, 
                 vector<Property>& ApprovedAds,
                 vector<Property>& RejectedAds, 
                 unordered_map <string, User>& Users);

    // block a user from posting ads for a period of time
    void blockUser(string UserId, unordered_map <string, User>& Users);

    // Unblock a user
    void unblockUser(string UserId, unordered_map <string, User>& Users);

    // Ban user completely :prevent login or usage
    void banUser(string UserId,
                 unordered_map <string, User>& Users, 
                 vector<Property>& ApprovedAds,
                 vector<Property>& PendingAds);

    // Unban user
    void unbanUser(string UserId, unordered_map <string, User>& Users);

    // View Approved ads
    void ViewApprovedAds(vector<Property>& ApprovedAds);

    //Moderate User's Activities
    void ModerateUserActivity(unordered_map<string, User>& Users,
                              vector<Property>ApprovedAds, 
                              vector<Property>PendingAds);

    void ViewUserInfo(unordered_map<string, User>& Users);

    //HabibaKhaled
    bool checkisadmin(string& username, string& password, unordered_map<string, string>& Admins);

    void AddnewAdmin(unordered_map<string, Admin>& Admins,
        unordered_map<string, User>& Users,
        vector<Property>& PendingAds,
        vector<Property>& ApprovedAds);

    void RemoveAdmin(unordered_map<string, Admin>& Admins,
        unordered_map<string, User>& Users,
        vector<Property>& PendingAds,
        vector<Property>& ApprovedAds,
        vector<Property>& RejectedAds,
        vector<string>types,
        vector<string>locations);

    void showAdminDashboard(unordered_map<string, Admin>& Admins,
        unordered_map<string, User>& Users,
        vector<Property>& PendingAds,
        vector<Property>& ApprovedAds,
        vector<Property>& RejectedAds,
        vector<string>types,
        vector<string>locations, const string& loggedInId);

    //Habiba Basel

    int generateNewId(vector<Property>& approvedProperties,
        vector<Property>& pendingProperties,
        vector<Property>& rejectedProperties);
    string chooseType(vector<string>& types);
    string chooseLocation(vector<string>& locations);

    void addProperty(vector<Property>& approvedProperties,
        vector<Property>& pendingProperties,
        vector<Property>& rejectedProperties,
        vector<string>& types,
        vector<string>& locations);
    void editProperty(vector<Property>& approvedProperties,
        vector<Property>& pendingProperties,
        vector<Property>& rejectedProperties,
        vector<string>& types,
        vector<string>& locations);
    void removeProperty(vector<Property>& approvedProperties,
        vector<Property>& pendingProperties,
        vector<Property>& rejectedProperties);
    static bool compareHighlighted(const Property& a, const Property& b);
    void toggleHighlightProperty(vector<Property>& approvedProperties,
        vector<Property>& pendingProperties,
        vector<Property>& rejectedProperties);
    void showAllProperties(vector<Property>& approvedProperties,
        vector<Property>& pendingProperties,
        vector<Property>& rejectedProperties);
    void manageAdminProfile(unordered_map<string, Admin>& admins, const string& adminId);
};
