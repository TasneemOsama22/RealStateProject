#ifndef USERWINDOW_H
#define USERWINDOW_H
#include <QTableWidget>
#include <QWidget>
#include <unordered_map>
#include <vector>
#include <QDialog>
#include "user.h"
#include "property.h"

using namespace std;

namespace Ui {
class UserWindow;
}

class UserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit UserWindow(unordered_map<string, User>& users,
                        vector<Property>& pendingProperties,
                        const string& currentUserId,
                        QWidget *parent = nullptr);
    ~UserWindow();

private slots:
    void on_addPropbtn_clicked();        // Navigate to Add Property form
    void on_submitPropertyBtn_clicked(); // Trigger add property logic
    void on_viewPropbtn_clicked();


private:
    Ui::UserWindow *ui;
    unordered_map<string, User>& users;
    vector<Property>& pendingProperties;
    string currentUserId;

    int getNextPropertyId();
    void loadPropertiesToTable(const std::vector<Property>& properties, QTableWidget* tableWidget);
};

#endif // USERWINDOW_H
