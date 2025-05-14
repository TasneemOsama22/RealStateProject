#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unordered_map>
#include <vector>
#include "User.h"
#include "Property.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_addPropbtn_clicked();
    void showAddPropertyPage();
    void handleAddProperty();
    void on_backbtn_2_clicked();
    //void on_submitPropbtn_clicked();
    void showUserPropertiesInTable();

    void on_viewPropbtn_clicked();

private:
    Ui::MainWindow *ui;
    std::unordered_map<std::string, User> users;
    std::vector<Property> pendingProperties;
    std::string currentUserId = "user123"; // just a dummy value for now
};
#endif // MAINWINDOW_H
