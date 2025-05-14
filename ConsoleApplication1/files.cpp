#include "Files.h"
#include <fstream>
#include <QString>
#include <QFile>
#include <QTextStream>

void Files::loadAccountsFromFile(std::unordered_map<std::string, User> &userMap,
                                 std::unordered_map<std::string, Admin> &adminMap,
                                 const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        if (parts.size() < 5) continue;

        std::string type = parts[0].toStdString();
        std::string id = parts[1].toStdString();
        std::string name = parts[2].toStdString();
        std::string email = parts[3].toStdString();
        std::string password = parts[4].toStdString();

        if (type == "user") {
            userMap[id] = User(id, name, email, password);
        } else if (type == "admin") {
            adminMap[id] = Admin(id, name, email, password);
        }
    }
    file.close();
}


void Files::storeAccountsToFile(const std::unordered_map<std::string, User> &userMap,
                                const std::unordered_map<std::string, Admin> &adminMap,
                                const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    for (const auto &pair : userMap) {
        const User &u = pair.second;
        out << "user," << QString::fromStdString(u.getId()) << ","
            << QString::fromStdString(u.getUsername()) << ","
            << QString::fromStdString(u.getEmail()) << ","
            << QString::fromStdString(u.getPassword()) << "\n";
    }

    for (const auto &pair : adminMap) {
        const Admin &a = pair.second;
        out << "admin," << QString::fromStdString(a.getId()) << ","
            << QString::fromStdString(a.getUsername()) << ","
            << QString::fromStdString(a.getEmail()) << ","
            << QString::fromStdString(a.getPassword()) << "\n";
    }

    file.close();
}
