#include "Login.h"
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <string>
#include "Admin.h"
#include "User.h"

bool Login::loginUser(const std::string& inputEmail, const std::string& inputPassword,
                      std::unordered_map<std::string, User>& userMap,
                      std::unordered_map<std::string, Admin>& adminMap,
                      std::string& loggedInId, std::string& accountType) {

    std::string loginEmail = inputEmail;
    std::transform(loginEmail.begin(), loginEmail.end(), loginEmail.begin(), ::tolower);

    for (auto& pair : userMap) {
        User& user = pair.second;

        if (user.getEmail() == loginEmail) {
            if (user.getPassword() != inputPassword) {
                return false; // incorrect password
            }

            if (user.getIsBanned()) {
                return false; // banned
            }

            if (user.getIsBlocked()) {
                int daysRemaining = user.getblockDaysRemaining();
                if (daysRemaining > 0) {
                    user.setblockDaysRemaining(daysRemaining - 1);
                    if (daysRemaining - 1 <= 0) {
                        user.setIsBlocked(false);
                        loggedInId = user.getId();
                        accountType = "user";
                        return true;
                    }
                    return false; // still blocked
                }
            }

            loggedInId = user.getId();
            accountType = "user";
            return true;
        }
    }

    for (auto& pair : adminMap) {
        Admin& admin = pair.second;

        if (admin.getEmail() == loginEmail) {
            if (admin.getPassword() != inputPassword) {
                return false;
            }
            loggedInId = admin.getId();
            accountType = "admin";
            return true;
        }
    }

    return false; // no account found
}
