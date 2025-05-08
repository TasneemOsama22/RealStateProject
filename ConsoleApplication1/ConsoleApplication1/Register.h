#include <string>
#include "User.h"
#include "Admin.h"
using namespace std;
class Register {
public:
    bool registerUser(unordered_map<string, User>& userMap, unordered_map<string, Admin>& adminMap,
        string& id, string& name, string& email, string& password, string& type);
    void loadAccounts(unordered_map<string, User>& userMap, unordered_map<string, Admin>& adminMap);
    void storeAccount(const string& id, const string& name, const string& email, const string& password, const string& type);

private:
    bool isEmailValid(const std::string& email);
    bool isPasswordStrong(const std::string& password);
    string detectType();
    string generateUniqueID(const string& type);
   

};
