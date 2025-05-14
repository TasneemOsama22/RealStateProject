#include "signupdialog.h"
#include "ui_signupdialog.h"
#include <QMessageBox>

SignUpDialog::SignUpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpDialog) {
    ui->setupUi(this);
}

SignUpDialog::~SignUpDialog() {
    delete ui;
}

void SignUpDialog::on_registerButton_clicked() {
    QString name = ui->nameLineEdit->text();
    QString email = ui->emailLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    QString type = ui->adminRadioButton->isChecked() ? "admin" : "user";

    QString result = reg.registerUser(name, email, password, type, userMap, adminMap);
    QMessageBox::information(this, "Registration", result);
}
