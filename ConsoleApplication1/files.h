#ifndef FILES_H
#define FILES_H

#include <unordered_map>
#include <string>
#include "User.h"
#include "Admin.h"
#include "Property.h"
#include <QString>
#include <vector>
#include <QDebug>

class Files {
public:
    static void loadAccountsFromFile(std::unordered_map<std::string, User> &userMap,
                                     std::unordered_map<std::string, Admin> &adminMap,
                                     const QString &filePath);

    static void storeAccountsToFile(const std::unordered_map<std::string, User> &userMap,
                                    const std::unordered_map<std::string, Admin> &adminMap,
                                    const QString &filePath);
    static void savePropertiesToFile(const std::vector<Property>& pending,
                                     const std::vector<Property>& approved,
                                     const std::vector<Property>& rejected,
                                     const QString& filePath);

    // Make sure this one exists too, if you also updated loadPropertiesFromFile
    static void loadPropertiesFromFile(std::vector<Property>& pending,
                                       std::vector<Property>& approved,
                                       std::vector<Property>& rejected,
                                       const QString& filePath);
};

#endif // FILES_H
