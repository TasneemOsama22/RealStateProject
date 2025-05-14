#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include "User.h"
#include "Property.h"
#include <unordered_map>
#include <vector>
#include <QString>
#include <QMessageBox>
#include "Files.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sidebarWidget->setStyleSheet(R"(
    background-color: qlineargradient(
        spread:pad,
        x1:0, y1:0.795, x2:0.911, y2:0.0454545,
        stop:0.100559 rgba(145, 70, 145, 255),
        stop:1 rgba(54, 57, 57, 255)
    );
    background-color: rgb(196, 123, 255);
)");

    // Background gradient
    this->setStyleSheet(R"(
        background: qlineargradient(
            x1:0, y1:0, x2:1, y2:1,
            stop:0 #1c1c1c, stop:1 #2e2e2e
        );
    )");

    // Button style
    QString buttonStyle = R"(
        QPushButton {
            background-color: #2e2e2e;
            color: white;
            font-size: 16px;
            font-weight: 500;
            padding: 10px 20px;
            border: 2px solid transparent;
            border-radius: 10px;
            border-image: linear-gradient(to right,
                rgba(255, 100, 100, 255),
                rgba(255, 255, 150, 255),
                rgba(100, 255, 100, 255),
                rgba(100, 255, 255, 255),
                rgba(100, 100, 255, 255),
                rgba(255, 100, 255, 255),
                rgba(255, 100, 100, 255)) 1;
            min-width: 200px;
        }

        QPushButton:hover {
            background-color: #4d4d4d;
            border: 2px solid white;
        }

        QPushButton:pressed {
            background-color: #666;
        }
    )";

    // Apply to buttons
    ui->addPropbtn->setStyleSheet(buttonStyle);
    ui->viewPropbtn->setStyleSheet(buttonStyle);
    ui->searchPropbtn->setStyleSheet(buttonStyle);
    ui->comparePropbtn->setStyleSheet(buttonStyle);
    ui->buyPropbtn->setStyleSheet(buttonStyle);
    ui->backbtn->setStyleSheet(buttonStyle);
    ui->backbtn_2->setStyleSheet(buttonStyle);

    //apply to functions
    connect(ui->addPropbtn, &QPushButton::clicked, this, &MainWindow::showAddPropertyPage);


    // Drop shadow effect for buttons
    auto createShadow = [this]() {
        auto* shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(10);
        shadow->setOffset(0, 2);
        shadow->setColor(QColor(0, 0, 0, 160));
        return shadow;
    };

    ui->addPropbtn->setGraphicsEffect(createShadow());
    ui->viewPropbtn->setGraphicsEffect(createShadow());
    ui->searchPropbtn->setGraphicsEffect(createShadow());
    ui->comparePropbtn->setGraphicsEffect(createShadow());
    ui->buyPropbtn->setGraphicsEffect(createShadow());
    ui->backbtn->setGraphicsEffect(createShadow());

    // Enhance title label


    QGraphicsDropShadowEffect* titleShadow = new QGraphicsDropShadowEffect(this);
    titleShadow->setBlurRadius(15);
    titleShadow->setOffset(0, 0);
    titleShadow->setColor(QColor(255, 255, 255, 100));


    QString labelStyle = R"(
    QLabel {
        color: white;
        background-color: #3a3a3a;
        border-radius: 15px;
        padding: 6px 12px;
        font-family: 'Segoe UI';
        font-size: 16px;
        font-weight: 700;
    }
)";

    ui->ownernamelbl->setStyleSheet(labelStyle);
    ui->arealbl->setStyleSheet(labelStyle);
    ui->locationlbl->setStyleSheet(labelStyle);
    ui->typelbl->setStyleSheet(labelStyle);
    ui->bedroomslbl->setStyleSheet(labelStyle);
    ui->bathroomslbl->setStyleSheet(labelStyle);
    ui->pricelbl->setStyleSheet(labelStyle);


    QString inputStyle = R"(
    QLineEdit {
        background-color: #2e2e2e;
        color: white;
        border: 2px solid #444;
        border-radius: 8px;
        padding: 6px 10px;
        font-size: 14px;
    }
    QLineEdit:focus {
        border: 2px solid #a066ff;
    }
)";

    ui->ownernameEdit->setStyleSheet(inputStyle);
    ui->areaEdit->setStyleSheet(inputStyle);
    ui->priceEdit->setStyleSheet(inputStyle);
    QString comboStyle = R"(
    QComboBox {
        background-color: #2e2e2e;
        color: white;
        border: 2px solid #444;
        border-radius: 8px;
        padding: 5px 10px;
        font-size: 14px;
    }
    QComboBox::drop-down {
        border: none;
    }
    QComboBox QAbstractItemView {
        background-color: #3a3a3a;
        color: white;
        selection-background-color: #a066ff;
        border-radius: 4px;
    }
)";
    ui->typeCombo->setStyleSheet(comboStyle);
    ui->locationCombo->setStyleSheet(comboStyle);

    // Type ComboBox
    ui->typeCombo->addItems({
        "Apartment", "Villa", "Chalet", "Studio",
        "Duplex", "Townhouse", "Farmhouse"
    });

    // Location ComboBox
    ui->locationCombo->addItems({
        "New Cairo", "6th October", "North Coast",
        "Zayed City", "Maadi", "Heliopolis", "Nasr City"
    });

    //bedrooms and bath
    // Bedrooms Slider (1 to 6)
    ui->horizontalSlider_2->setMinimum(1);
    ui->horizontalSlider_2->setMaximum(6);

    // Bathrooms Slider (1 to 5)
    ui->horizontalSlider->setMinimum(1);
    ui->horizontalSlider->setMaximum(5);
    //default value
    ui->horizontalSlider_2->setValue(1);
    ui->horizontalSlider->setValue(1);

    QString sliderStyle = R"(
    QSlider::groove:horizontal {
        border: 1px solid #444;
        height: 8px;
        background: #3a3a3a;
        border-radius: 4px;
    }

    QSlider::handle:horizontal {
        background: #a066ff;
        border: 1px solid #5c2ca1;
        width: 18px;
        height: 18px;
        margin: -5px 0;
        border-radius: 9px;
    }

    QSlider::sub-page:horizontal {
        background: #a066ff;
        border-radius: 4px;
    }

    QSlider::add-page:horizontal {
        background: #2e2e2e;
        border-radius: 4px;
    }
)";
    ui->horizontalSlider_2->setStyleSheet(sliderStyle);
    ui->horizontalSlider->setStyleSheet(sliderStyle);

    connect(ui->horizontalSlider_2, &QSlider::valueChanged, this, [=](int value){
        ui->bedroomslbl->setText("Bedrooms: " + QString::number(value));
    });

    connect(ui->horizontalSlider, &QSlider::valueChanged, this, [=](int value){
        ui->bathroomslbl->setText("Bathrooms: " + QString::number(value));
    });

    //submit
    connect(ui->submitPropbtn, &QPushButton::clicked, this, &MainWindow::handleAddProperty);
    QString submitButtonStyle = R"(
    QPushButton {
        background: qlineargradient(
            x1:0, y1:0, x2:1, y2:1,
            stop:0 #3ac162, stop:1 #2e8b57
        );
        color: white;
        font-family: 'Segoe UI';
        font-size: 16px;
        font-weight: bold;
        border: none;
        border-radius: 20px;


        box-shadow: 0px 4px 15px rgba(0, 255, 100, 0.3);
    }

    QPushButton:hover {
        background: #34b350;
    }

    QPushButton:pressed {
        background: #2a9c47;
    }
)";

    ui->submitPropbtn->setStyleSheet(submitButtonStyle);


    ui->userPropTable->setStyleSheet(R"(
    QHeaderView::section {
        background-color: #3a3a3a;
        color: white;
        padding: 5px;
        border: 1px solid #444;
    }
    QTableWidget {
        background-color: #2e2e2e;
        color: white;
        gridline-color: #444;
        font-size: 14px;
    }
)");











}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addPropbtn_clicked()
{
    User currentUser = users[currentUserId]; // gets the current user
    pendingProperties = currentUser.addProperty(users, currentUserId, pendingProperties);
}
void MainWindow::showAddPropertyPage() {
    qDebug() << "Button clicked";  // Add this line to verify if the function is called
    ui->stackedWidget->setCurrentWidget(ui->page_2);  // Switch to Add Property Page
}

void MainWindow::on_backbtn_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_1);
}
void MainWindow::handleAddProperty() {
    // Get values from the UI
    QString ownerName = ui->ownernameEdit->text();
    QString areaStr = ui->areaEdit->text();
    QString location = ui->locationCombo->currentText();
    QString type = ui->typeCombo->currentText();
    int bedrooms = ui->horizontalSlider_2->value();
    int bathrooms = ui->horizontalSlider->value();

    // Optional: Validate inputs
    if (ownerName.isEmpty() || areaStr.isEmpty()) {
        QMessageBox::warning(this, "Missing Info", "Please fill in all required fields.");
        return;
    }

    // Call your addProperty function
    User currentUser = users[currentUserId];
    pendingProperties = currentUser.addProperty(users, currentUserId, pendingProperties);

    // Show confirmation
    QMessageBox msgBox;
    msgBox.setStyleSheet(R"(
        QMessageBox { background-color: white; }
        QLabel { color: black; font-family: 'Segoe UI'; font-size: 14px; }
        QPushButton {
            background-color: #3ac162;
            color: white;
            border-radius: 10px;
            padding: 5px 15px;
        }
        QPushButton:hover { background-color: #34b350; }
    )");
    msgBox.setText("Property added and is now under review. Please wait for admin's approval.");
    msgBox.exec();

    // Optional: Clear fields or navigate back
}




void MainWindow::on_viewPropbtn_clicked() {
    User currentUser = users[currentUserId];
    vector<Property> approvedProps = currentUser.getUserPropertiesByStatus("Approved");

    if (approvedProps.empty()) {
        QMessageBox::information(this, "No Properties", "You have no approved properties.");
        return;
    }

    // Navigate to view page
    ui->stackedWidget->setCurrentWidget(ui->page_3);
    showUserPropertiesInTable();
}


void MainWindow::showUserPropertiesInTable() {
    ui->stackedWidget->setCurrentWidget(ui->page_3); // Switch to view page

    // Clear previous content
    ui->userPropTable->clear();
    ui->userPropTable->setRowCount(0);

    // Set headers
    QStringList headers = {
        "ID", "Title", "Location", "Owner", "Area (sqft)",
        "Price", "Bedrooms", "Bathrooms", "Status"
    };
    ui->userPropTable->setColumnCount(headers.size());
    ui->userPropTable->setHorizontalHeaderLabels(headers);

    // Get user's properties
    const std::vector<Property>& props = users[currentUserId].UserProperty;
    int row = 0;

    for (const auto& prop : props) {
        if (prop.getStatus() == Approved || prop.getStatus() == Pending || prop.getStatus() == Rejected) {
            ui->userPropTable->insertRow(row);

            ui->userPropTable->setItem(row, 0, new QTableWidgetItem(QString::number(prop.getId())));
            ui->userPropTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(prop.getTitle())));
            ui->userPropTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(prop.getLocation())));
            ui->userPropTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(prop.getOwnerName())));
            ui->userPropTable->setItem(row, 4, new QTableWidgetItem(QString::number(prop.getArea())));
            ui->userPropTable->setItem(row, 5, new QTableWidgetItem(QString::number(prop.getPrice())));
            ui->userPropTable->setItem(row, 6, new QTableWidgetItem(QString::number(prop.getBedrooms())));
            ui->userPropTable->setItem(row, 7, new QTableWidgetItem(QString::number(prop.getBathrooms())));
            ui->userPropTable->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(
                                                   users[currentUserId].checkPropertyStatus(prop))));

            row++;
        }
    }

    ui->userPropTable->resizeColumnsToContents();  // Optional: auto-size columns
}



