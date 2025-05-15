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
void Files::savePropertiesToFile(const std::vector<Property>& pending,
                                 const std::vector<Property>& approved,
                                 const std::vector<Property>& rejected,
                                 const QString& filePath) {
    QFile outFile(filePath);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error opening file for writing:" << filePath;
        return;
    }

    QTextStream out(&outFile);

    auto writeProperties = [&](const std::vector<Property>& props) {
        for (const Property& p : props) {
            out << p.getId() << ","
                << QString::fromStdString(p.getUserId()) << ","
                << QString::fromStdString(p.getTitle()) << ","
                << QString::fromStdString(p.getType()) << ","
                << p.getPrice() << ","
                << QString::fromStdString(p.getLocation()) << ","
                << QString::fromStdString(p.getOwnerName()) << ","
                << p.getArea() << ","
                << p.getBedrooms() << ","
                << p.getBathrooms() << ","
                << static_cast<int>(p.getStatus()) << ","
                << p.isHighlighted() << ","
                << p.getIsSold() << "\n";
        }
    };

    writeProperties(pending);
    writeProperties(approved);
    writeProperties(rejected);

    outFile.close();
    qDebug() << "Properties saved to file:" << filePath;
}

void Files::loadPropertiesFromFile(std::vector<Property>& pending,
                                   std::vector<Property>& approved,
                                   std::vector<Property>& rejected,
                                   const QString& filePath) {
    QFile inFile(filePath);
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "File not found or cannot be opened:" << filePath;
        return;
    }

    QTextStream in(&inFile);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList tokens = line.split(',');

        if (tokens.size() < 13) continue;

        Property p;
        p.setId(tokens[0].toInt());
        p.setUserId(tokens[1].toStdString());
        p.setTitle(tokens[2].toStdString());
        p.setType(tokens[3].toStdString());
        p.setPrice(tokens[4].toDouble());
        p.setLocation(tokens[5].toStdString());
        p.setOwnerName(tokens[6].toStdString());
        p.setArea(tokens[7].toDouble());
        p.setBedrooms(tokens[8].toInt());
        p.setBathrooms(tokens[9].toInt());

        int status = tokens[10].toInt();
        int highlighted = tokens[11].toInt();
        int sold = tokens[12].toInt();

        p.setStatus(static_cast<PropertyStatus>(status));
        p.setHighlighted(highlighted);
        p.setIsSold(sold);

        switch (p.getStatus()) {
        case PropertyStatus::Pending: pending.push_back(p); break;
        case PropertyStatus::Approved: approved.push_back(p); break;
        case PropertyStatus::Rejected: rejected.push_back(p); break;
        default: break;
        }
    }

    inFile.close();
    qDebug() << "Properties loaded from file:" << filePath;
}
