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



public:
    Admin(const string Id, const string Pass);

    // view all pending ads
    void ReviewPendingAds(vector<Property>& PendingAds, vector<Property>& ApprovedAds, unordered_map <string, User>& Users);
    // Approve ad
    void ApproveAd(Property ad, vector<Property>& approvedAds, vector<Property>& PendingAds, string UserId, unordered_map <string, User>& Users);
    // Reject ad
    void RejectAd(Property ad, string UserId, vector<Property>& pendingAds, string reason, unordered_map <string, User>& Users, int ChoiseNumber);

    // block a user from posting ads for a period of time
    void blockUser(string UserId, unordered_map <string, User>& Users);

    // Unblock a user
    void unblockUser(string UserId, unordered_map <string, User>& Users);

    // Ban user completely :prevent login or usage
    void banUser(string UserId, unordered_map <string, User>& Users);

    // Unban user
    void unbanUser(string UserId, unordered_map <string, User>& Users);

    // View Approved ads
    void ViewApprovedAds(vector<Property>& ApprovedAds);

};

