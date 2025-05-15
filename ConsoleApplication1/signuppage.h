#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include <QDialog>
#include <unordered_map>
#include "User.h"
#include "Admin.h"

namespace Ui {
class SignUpPage;
}

class SignUpPage : public QDialog {
    Q_OBJECT

public:
    explicit SignUpPage(std::unordered_map<std::string, User>& userMap,
                        std::unordered_map<std::string, Admin>& adminMap,
                        QWidget *parent = nullptr);
    ~SignUpPage();

private slots:
    void onSignUpClicked();

private:
    Ui::SignUpPage *ui;
    std::unordered_map<std::string, User>& userMap;
    std::unordered_map<std::string, Admin>& adminMap;
};

#endif // SIGNUPPAGE_H
