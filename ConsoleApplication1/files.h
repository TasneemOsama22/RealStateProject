#ifndef FILES_H
#define FILES_H

#include <unordered_map>
#include <string>
#include "User.h"
#include "Admin.h"
#include <QString>

class Files {
public:
    static void loadAccountsFromFile(std::unordered_map<std::string, User> &userMap,
                                     std::unordered_map<std::string, Admin> &adminMap,
                                     const QString &filePath);

    static void storeAccountsToFile(const std::unordered_map<std::string, User> &userMap,
                                    const std::unordered_map<std::string, Admin> &adminMap,
                                    const QString &filePath);
};

#endif // FILES_H
