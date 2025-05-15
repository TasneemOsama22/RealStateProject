#include "userwindow.h"
#include "ui_userwindow.h"
#include <QMessageBox>

UserWindow::UserWindow(unordered_map<string, User>& users,
                       vector<Property>& pendingProperties,
                       const string& currentUserId,
                       QWidget *parent)
    : QDialog(parent),
    ui(new Ui::UserWindow),
    users(users),
    pendingProperties(pendingProperties),
    currentUserId(currentUserId)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->userDashBoard);

    // Set up table headers and properties
    QStringList headers = {"ID", "Title", "Location", "Owner", "Area", "Price", "Bedrooms", "Bathrooms", "Status"};
    ui->tableWidget->setColumnCount(9);
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Connect buttons
    connect(ui->addPropbtn, &QPushButton::clicked, this, &UserWindow::on_addPropbtn_clicked);
    connect(ui->submitPropertyBtn, &QPushButton::clicked, this, &UserWindow::on_submitPropertyBtn_clicked);
    connect(ui->viewPropbtn, &QPushButton::clicked, this, &UserWindow::on_viewPropbtn_clicked);
}


UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::on_addPropbtn_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->addPropFun); // Go to the Add Property page
}

int UserWindow::getNextPropertyId()
{
    if (users.find(currentUserId) == users.end()) return 1;

    int lastId = 0;
    for (const Property& prop : users[currentUserId].UserProperty) {
        if (prop.getId() > lastId) {
            lastId = prop.getId();
        }
    }
    return lastId + 1;
}

void UserWindow::on_submitPropertyBtn_clicked()
{
    if (users.find(currentUserId) == users.end()) {
        QMessageBox::critical(this, "Error", "User not found.");
        return;
    }

    QString title = ui->titleEdit->text();  // NEW: Get title
    QString owner = ui->ownernameEdit_2->text();
    QString areaStr = ui->areaEdit_2->text();
    QString priceStr = ui->priceEdit_2->text();
    QString location = ui->locationCombo_2->currentText();
    QString type = ui->typeCombo_2->currentText();
    int bedrooms = ui->horizontalSlider_3->value();
    int bathrooms = ui->horizontalSlider_4->value();

    // Input validation (basic)
    if (title.isEmpty()) qDebug() << "Title is empty!";  // NEW
    if (owner.isEmpty()) qDebug() << "Owner is empty!";
    if (areaStr.isEmpty()) qDebug() << "Area is empty!";
    if (priceStr.isEmpty()) qDebug() << "Price is empty!";
    if (ui->locationCombo_2->currentIndex() == 0) qDebug() << "Location not selected!";
    if (ui->typeCombo_2->currentIndex() == 0) qDebug() << "Type not selected!";
    if (bedrooms == 0) qDebug() << "Bedrooms is 0!";
    if (bathrooms == 0) qDebug() << "Bathrooms is 0!";

    double area = areaStr.toDouble();
    double price = priceStr.toDouble();
    int newId = getNextPropertyId();

    // Construct Property with title
    Property p(newId, currentUserId, title.toStdString(), price,
               location.toStdString(), owner.toStdString(),
               area, type.toStdString(), bedrooms, bathrooms,
               PropertyStatus::Pending, false);

    users[currentUserId].UserProperty.push_back(p);
    pendingProperties.push_back(p);
    qDebug() << "Property added with ID:" << p.getId()
             << "Status:" << static_cast<int>(p.getStatus())
             << "Total user properties now:" << users[currentUserId].UserProperty.size();


    // Reset fields
    ui->titleEdit->clear();  // NEW
    ui->ownernameEdit_2->clear();
    ui->areaEdit_2->clear();
    ui->priceEdit_2->clear();
    ui->locationCombo_2->setCurrentIndex(0);
    ui->typeCombo_2->setCurrentIndex(0);
    ui->horizontalSlider_3->setValue(0);
    ui->horizontalSlider_4->setValue(0);

    ui->stackedWidget->setCurrentWidget(ui->userDashBoard);
}

void UserWindow::on_viewPropbtn_clicked()
{
    // Show the viewPropFun page
    ui->stackedWidget->setCurrentWidget(ui->viewPropFun);

    // Load properties with a filter, e.g. "Approved"
    loadPropertiesToTable(pendingProperties, ui->tableWidget);
}
void UserWindow::loadPropertiesToTable(const std::vector<Property>& properties, QTableWidget* tableWidget) {
    tableWidget->clearContents();
    tableWidget->setRowCount(static_cast<int>(properties.size()));

    for (int row = 0; row < static_cast<int>(properties.size()); ++row) {
        const Property& property = properties[row];

        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(property.getId())));
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(property.getTitle())));
        tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(property.getLocation())));
        tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(property.getOwnerName())));
        tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(property.getArea())));
        tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(property.getPrice())));
        tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(property.getBedrooms())));
        tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(property.getBathrooms())));

        QString statusText;
        switch (property.getStatus()) {
        case PropertyStatus::Pending:  statusText = "Pending"; break;
        case PropertyStatus::Approved: statusText = "Approved"; break;
        case PropertyStatus::Rejected: statusText = "Rejected"; break;
        default:                       statusText = "Unknown"; break;
        }

        tableWidget->setItem(row, 8, new QTableWidgetItem(statusText));
    }
}

