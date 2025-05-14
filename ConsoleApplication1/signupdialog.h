#ifndef SIGNUPDIALOG_H
#define SIGNUPDIALOG_H

#include <QDialog>
#include "register.h" // if you use Register class
#include "user.h"     // if User type is used
#include "admin.h"    // if Admin type is used

namespace Ui {
class SignUpDialog;
}

class SignUpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpDialog(QWidget *parent = nullptr);
    ~SignUpDialog();

private slots:
    void on_registerButton_clicked();

private:
    Ui::SignUpDialog *ui;
    Register reg;
    std::unordered_map<std::string, User> userMap;
    std::unordered_map<std::string, Admin> adminMap;
};

#endif // SIGNUPDIALOG_H
