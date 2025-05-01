#pragma once
#include <string>
#include <unordered_map>
#include "User.h"
#include "Admin.h"

class Login {
public:
    bool loginUser(std::unordered_map<std::string, User>& userMap,
        std::unordered_map<std::string, Admin>& adminMap,
        std::string& loggedInId,
        std::string& accountType);

private:
    string getMaskedPassword();  
};
