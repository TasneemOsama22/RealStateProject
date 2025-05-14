#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <unordered_map>
#include "User.h"
#include "Admin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class SignUpPage;  // Forward declaration
class LogInPage;   // Forward declaration

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void openSignUpDialog();
    void openLogInDialog();  // Added for login

protected:
    void closeEvent(QCloseEvent *event) override;  // Declare closeEvent here

private:
    Ui::Widget *ui;

    // Store users and admins
    std::unordered_map<std::string, User> userMap;
    std::unordered_map<std::string, Admin> adminMap;
};

#endif // WIDGET_H
