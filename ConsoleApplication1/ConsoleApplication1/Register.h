#include <string>
#include "User.h"
#include "Admin.h"
using namespace std;
class Register {
public:
    void registerUser(unordered_map<string, User>& userMap, unordered_map<string, Admin>& adminMap);

private:
    bool isEmailValid(const std::string& email);
    bool isPasswordStrong(const std::string& password);
    string detectType();
    string generateUniqueID(const string& type);
};