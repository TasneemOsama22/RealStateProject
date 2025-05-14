#ifndef REGISTER_H
#define REGISTER_H

#include <QString>
#include <unordered_map>
#include "User.h"
#include "Admin.h"

class Register {
public:
    QString registerUser(const QString& name,
                         const QString& email,
                         const QString& password,
                         const QString& type,
                         std::unordered_map<std::string, User>& userMap,
                         std::unordered_map<std::string, Admin>& adminMap);

private:
    bool isEmailValid(const std::string& email);
    bool isPasswordStrong(const std::string& password);
    std::string generateUniqueID(const std::unordered_map<std::string, User>& userMap,
                                 const std::unordered_map<std::string, Admin>& adminMap,
                                 const std::string& type);
};

#endif // REGISTER_H
