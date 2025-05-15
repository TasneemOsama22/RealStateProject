#include "widget.h"
#include "ui_widget.h"
#include "SignUpPage.h"
#include "LogInPage.h"
#include "Files.h"
#include <QCloseEvent>
#include "UserWindow.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Widget) {
    ui->setupUi(this);

    // Load accounts and properties from files on start
    Files::loadAccountsFromFile(userMap, adminMap, accountsFilePath);
    Files::loadPropertiesFromFile(pendingAds, approvedAds, rejectedAds, propertiesFilePath);

    // Connect Sign Up button
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::openSignUpDialog);

    // Connect Log In button
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Widget::openLogInDialog);
}

Widget::~Widget() {
    delete ui;
}

void Widget::openSignUpDialog() {
    SignUpPage dialog(userMap, adminMap, this);
    dialog.exec();
}

void Widget::openLogInDialog() {
    LogInPage dialog(this);
    dialog.setUserAndAdminMaps(userMap, adminMap);
    if (dialog.exec() == QDialog::Accepted) {
        std::string loggedInId = dialog.getLoggedInId();
        std::string accountType = dialog.getAccountType();

        if (accountType == "user") {
            // Create UserWindow
            UserWindow* userWin = new UserWindow(userMap, pendingAds, loggedInId);

            // Show UserWindow
            userWin->setAttribute(Qt::WA_DeleteOnClose);
            userWin->show();

            // Hide main Widget window
            this->hide();

            // When UserWindow closes, show main window again
            connect(userWin, &UserWindow::destroyed, this, [this]() {
                this->show();
            });
        }
        else if (accountType == "admin") {
            QMessageBox::information(this, "Admin Login", "Admin dashboard not yet implemented.");
        }
    }
}


void Widget::closeEvent(QCloseEvent *event) {
    // Save all data on app exit
    Files::storeAccountsToFile(userMap, adminMap, accountsFilePath);
    Files::savePropertiesToFile(pendingAds, approvedAds, rejectedAds, propertiesFilePath);
    event->accept();
}
