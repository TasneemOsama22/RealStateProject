#include "Register.h"
#include "User.h"
#include "Admin.h"
#include <regex>
#include <algorithm>

QString Register::registerUser(const QString& qName, const QString& qEmail, const QString& qPassword, const QString& qType,
                               std::unordered_map<std::string, User>& userMap,
                               std::unordered_map<std::string, Admin>& adminMap) {

    std::string name = qName.toStdString();
    std::string email = qEmail.toStdString();
    std::string password = qPassword.toStdString();
    std::string type = qType.toStdString();

    std::transform(email.begin(), email.end(), email.begin(), ::tolower);

    if (!isEmailValid(email)) {
        return "Invalid email format.";
    }

    bool emailExists = std::any_of(userMap.begin(), userMap.end(),
                                   [&email](const auto& pair) {
                                       return pair.second.getEmail() == email;
                                   });

    if (emailExists || std::any_of(adminMap.begin(), adminMap.end(),
                                   [&email](const auto& pair) {
                                       return pair.second.getEmail() == email;
                                   })) {
        return "Email already exists!";
    }

    if (!isPasswordStrong(password)) {
        return "Weak password. Must be at least 6 characters.";
    }

    std::string id = generateUniqueID(userMap, adminMap, type);

    if (type == "user") {
        userMap[id] = User(id, name, email, password);
    } else if (type == "admin") {
        adminMap[id] = Admin(id, name, email, password);
    } else {
        return "Invalid account type.";
    }

    return "Account successfully registered.";
}

bool Register::isEmailValid(const std::string& email) {
    const std::regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
    return std::regex_match(email, pattern);
}

bool Register::isPasswordStrong(const std::string& password) {
    return password.length() >= 6;
}

std::string Register::generateUniqueID(const std::unordered_map<std::string, User>& userMap,
                                       const std::unordered_map<std::string, Admin>& adminMap,
                                       const std::string& type) {
    int maxID = (type == "user") ? 1000 : 2000;

    if (type == "user") {
        for (const auto& pair : userMap) {
            const std::string& id = pair.first;
            if (id.substr(0, 3) == "USR") {
                int num = std::stoi(id.substr(3));
                maxID = std::max(maxID, num + 1);
            }
        }
        return "USR" + std::to_string(maxID);
    } else {
        for (const auto& pair : adminMap) {
            const std::string& id = pair.first;
            if (id.substr(0, 3) == "ADM") {
                int num = std::stoi(id.substr(3));
                maxID = std::max(maxID, num + 1);
            }
        }
        return "ADM" + std::to_string(maxID);
    }
}
