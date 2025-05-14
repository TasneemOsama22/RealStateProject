#include <string>
#include "User.h"
#include "Admin.h"
using namespace std;
class Register {
public:
    bool registerUser(unordered_map<string, User>& userMap, unordered_map<string, Admin>& adminMap);

private:

    bool isEmailValid(const string& email);
    bool isPasswordStrong(const string& password);
    string detectType();
    string generateUniqueID(
        const unordered_map<string, User>& userMap,
        const unordered_map<string, Admin>& adminMap,
        const string& type
    );


};