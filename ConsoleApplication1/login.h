#pragma once
#include <string>
#include <unordered_map>
#include "User.h"
#include "Admin.h"

class Login {
public:
    // Updated function to take email/password as parameters
    bool loginUser(const std::string& email, const std::string& password,
                   std::unordered_map<std::string, User>& userMap,
                   std::unordered_map<std::string, Admin>& adminMap,
                   std::string& loggedInId, std::string& accountType);
};
