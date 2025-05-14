#include "SignUpPage.h"
#include "ui_SignUpPage.h"
#include "Register.h"
#include <QMessageBox>

SignUpPage::SignUpPage(std::unordered_map<std::string, User>& userMap,
                       std::unordered_map<std::string, Admin>& adminMap,
                       QWidget *parent)
    : QDialog(parent),
    ui(new Ui::SignUpPage),
    userMap(userMap),
    adminMap(adminMap) {
    ui->setupUi(this);

    // Connect the Sign Up button in SignUpPage.ui to the slot
    connect(ui->pushButton, &QPushButton::clicked, this, &SignUpPage::onSignUpClicked);
}

SignUpPage::~SignUpPage() {
    delete ui;
}

void SignUpPage::onSignUpClicked() {
    QString name = ui->lineEdit->text();
    QString email = ui->lineEdit_2->text();
    QString password = ui->lineEdit_3->text();

    QString type;
    if (ui->radioButton->isChecked()) {
        type = "admin";
    } else if (ui->radioButton_2->isChecked()) {
        type = "user";
    } else {
        QMessageBox::warning(this, "Sign Up", "Please select an account type.");
        return;
    }

    Register reg;
    QString result = reg.registerUser(name, email, password, type, userMap, adminMap);

    QMessageBox::information(this, "Sign Up", result);

    if (result == "Account successfully registered.") {
        this->accept(); // Close dialog on success
    }
}
