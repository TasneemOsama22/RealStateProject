#pragma once
#include <string>
#include <unordered_map>
#include "User.h"
#include "Admin.h"

class Login {
public:
    bool loginUser(unordered_map<string, User>& userMap, unordered_map<string, Admin>& adminMap, string& loggedInId, string& accountType);

private:
    string getMaskedPassword();
};