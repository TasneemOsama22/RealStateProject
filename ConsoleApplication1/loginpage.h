#pragma once

#include <QDialog>
#include <unordered_map>
#include "User.h"
#include "Admin.h"

namespace Ui {
class LogInPage;
}

class LogInPage : public QDialog {
    Q_OBJECT

public:
    explicit LogInPage(QWidget *parent = nullptr);
    ~LogInPage();

    void setUserAndAdminMaps(std::unordered_map<std::string, User>& users,
                             std::unordered_map<std::string, Admin>& admins);

    std::string getLoggedInId() const;
    std::string getAccountType() const;

private slots:
    void on_pushButton_clicked(); // Login button handler

private:
    Ui::LogInPage *ui;
    std::unordered_map<std::string, User>* userMap;
    std::unordered_map<std::string, Admin>* adminMap;

    std::string loggedInId;
    std::string accountType;
};
