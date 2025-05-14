#include "LogInPage.h"
#include "ui_LogInPage.h"
#include <QString>
#include <QMessageBox>
#include <algorithm>

LogInPage::LogInPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LogInPage)
    , userMap(nullptr)
    , adminMap(nullptr)
{
    ui->setupUi(this);
}

LogInPage::~LogInPage() {
    delete ui;
}

void LogInPage::setUserAndAdminMaps(std::unordered_map<std::string, User>& users,
                                    std::unordered_map<std::string, Admin>& admins) {
    userMap = &users;
    adminMap = &admins;
}

std::string LogInPage::getLoggedInId() const {
    return loggedInId;
}

std::string LogInPage::getAccountType() const {
    return accountType;
}

void LogInPage::on_pushButton_clicked() {
    if (!userMap || !adminMap) {
        QMessageBox::critical(this, "Error", "User/Admin data not initialized.");
        return;
    }

    QString emailInput = ui->lineEdit->text().trimmed();
    ui->lineEdit_2->setEchoMode(QLineEdit::Password); // Set echo mode (no return value)
    QString passwordInput = ui->lineEdit_2->text();
    std::string email = emailInput.toStdString();
    std::string password = passwordInput.toStdString();

    std::transform(email.begin(), email.end(), email.begin(), ::tolower);

    // Check User Map
    for (auto& pair : *userMap) {
        User& user = pair.second;
        if (user.getEmail() == email) {
            if (user.getPassword() != password) {
                QMessageBox::warning(this, "Login Failed", "Incorrect password.");
                return;
            }

            if (user.getIsBanned()) {
                QMessageBox::critical(this, "Banned", "Your account is permanently banned. Contact support.");
                return;
            }

            if (user.getIsBlocked()) {
                int daysRemaining = user.getblockDaysRemaining();
                if (daysRemaining > 0) {
                    QMessageBox::warning(this, "Blocked",
                                         QString("Your account is blocked for %1 more day(s).").arg(daysRemaining));
                    user.setblockDaysRemaining(daysRemaining - 1);
                    if (daysRemaining - 1 <= 0) {
                        user.setIsBlocked(false);
                        QMessageBox::information(this, "Unblocked", "Block lifted. You can now log in.");
                        loggedInId = user.getId();
                        accountType = "user";
                        accept();
                        return;
                    }
                    return;
                }
            }

            loggedInId = user.getId();
            accountType = "user";
            QMessageBox::information(this, "Login Successful", "Welcome " + QString::fromStdString(user.getUsername())+" your ID: "+QString::fromStdString(user.getId()));
            accept(); // Close the dialog with success
            return;
        }
    }

    // Check Admin Map
    for (auto& pair : *adminMap) {
        Admin& admin = pair.second;
        if (admin.getEmail() == email) {
            if (admin.getPassword() != password) {
                QMessageBox::warning(this, "Login Failed", "Incorrect password.");
                return;
            }

            loggedInId = admin.getId();
            accountType = "admin";
            QMessageBox::information(this, "Login Successful", "Welcome " + QString::fromStdString(admin.getUsername())+" your ID: "+QString::fromStdString(admin.getId()));
            accept(); // Close the dialog with success
            return;
        }
    }

    QMessageBox::warning(this, "Login Failed", "No account found with this email.");
}
