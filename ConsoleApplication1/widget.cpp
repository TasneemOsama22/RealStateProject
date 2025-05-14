#include "widget.h"
#include "ui_widget.h"
#include "SignUpPage.h"
#include "LogInPage.h" // Include the login page
#include "Files.h" // Include the Files class to load and store accounts
#include <QCloseEvent>  // Include QCloseEvent header
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::Widget) {
    ui->setupUi(this);

    QString filePath = "accounts.txt";  // Set the file path here

    // Load accounts from file at the start of the application
    Files::loadAccountsFromFile(userMap, adminMap, filePath);

    // Connect Sign Up button (pushButton)
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::openSignUpDialog);

    // Connect Log In button (pushButton_2)
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

        // You can add logic to open user/admin dashboard here
    }
}

void Widget::closeEvent(QCloseEvent *event) {
    // Save the account file without asking the user for a file path
    QString filePath = "accounts.txt";  // Use the same fixed path to save the file
    Files::storeAccountsToFile(userMap, adminMap, filePath);
    event->accept(); // Proceed with closing the application
}
