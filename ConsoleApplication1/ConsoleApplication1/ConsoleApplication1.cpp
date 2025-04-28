#include <iostream>
#include "Property.h"
#include"search.h"
#include <vector>
#include <iomanip>
using namespace std;
int main() {
    search s;
    vector<Property>  properties =
    {
    Property("123", "This Property Is Good", 1500000, "Cairo","Omnia",150000,4,2,"Apartment"),
    Property("454", "Look At Our Property", 2500000, "Cairo","Alaa",236734,8,4,"Villa"),
    Property("323", "Simple", 3000000, "Cairo","Esraa",35990,10,5,"Block"),

    };
        string location = "Cairo";
        double lowerPrice = 100000;
        double higherPrice = 200000;
        string type = "Apartment";
        char Exit = 'y';
       do {
           int choice = 0;
            cout << "Press 1 if you want to searching By Location,Price or Type" << endl;
            cout << "Press 2 if you want to searching By Location only" << endl;
            cout << "Press 3 if you want to searching By Price only" << endl;
            cout << "Press 4 if you want to searching By Type only" << endl;
            cin >> choice;
            switch (choice)
            {
            case 1: {
                cout << "Enter Your Desired Search!" << endl;
                cout << "Location:";
                cin >> location;
                cout << "Lower Price:";
                cin >> lowerPrice;
                cout << "Higher Price:";
                cin >> higherPrice;
                cout << "Type:";
                cin >> type;

                for (const auto& prop : s.searchProperties(properties, location, lowerPrice, higherPrice, type)) {
                    cout << "Owner User Name:" << prop.getOwnerUsername() << "\n" << "Property Title:" << prop.getTitle() << "\n" << "Location:" << prop.getLocation() << "\t\t" << fixed << setprecision(2) << "Price:" << prop.getPrice() << "\n" << "Type: " << prop.getType() <<
                        "\t\t" << "Number Of Bedrooms:" << prop.getBedrooms() << "\t\t" << "Number of Bathrooms:" << prop.getBathrooms() << "\t\t" << fixed << setprecision(2) << "Property Area:" << prop.getArea() << endl;
                }
                break;
            }
            case 2:
            {
                cout << "Enter Your Target Location:";
                cin >> location;
                vector<Property> locationResult = s.binarySearchByLocation(properties, location);
                if (!locationResult.empty()) {
                    for (const auto& prop : locationResult) {
                        cout << "\n\n" << "Owner User Name:" << prop.getOwnerUsername() << "\n" << "Property Title:" << prop.getTitle() << "\n" << "Location: " << prop.getLocation() << "\t\t" << fixed << setprecision(2) << "Price:" << prop.getPrice() << "\n" << "Type: " << prop.getType() <<
                            "\t\t" << "Number Of Bedrooms:" << prop.getBedrooms() << "\t\t" << "Number of Bathrooms:" << prop.getBathrooms() << "\t\t" << fixed << setprecision(2) << "Property Area:" << prop.getArea() << endl;
                    }
                }
                else {
                    cout << "Not Found Any Property Has Location Like That!" << endl;
                }
                break;
            }
            case 3: {
                double targetPrice;
                cout << "Enter Your Target Price:";
                cin >> targetPrice;
                vector<Property> priceResult = s.binarySearchByPrice(properties, targetPrice);
                if (!priceResult.empty()) {
                    for (const auto& prop : priceResult) {
                        cout << "\n\n" << "Owner User Name:" << prop.getOwnerUsername() << "\n" << "Property Title:" << prop.getTitle() << "\n" << "Location: " << prop.getLocation() << "\t\t" << fixed << setprecision(2) << "Price:" << prop.getPrice() << "\n" << "Type: " << prop.getType() <<
                            "\t\t" << "Number Of Bedrooms:" << prop.getBedrooms() << "\t\t" << "Number of Bathrooms:" << prop.getBathrooms() << "\t\t" << fixed << setprecision(2) << "Property Area:" << prop.getArea() << endl;
                    }
                }
                else {
                    cout << "Not Found Properties Match your Price Search! " << endl;
                }
                break;
            }
            case 4: {
                cout << "Enter Your Target Type:";
                cin >> type;
                vector<Property> TypeResult = s.binarySearchByType(properties, type);
                if (!TypeResult.empty()) {
                    for (const auto& prop : TypeResult) {
                        cout << "\n\n" << "Owner User Name:" << prop.getOwnerUsername() << "\n" << "Property Title:" << prop.getTitle() << "\n" << "Location: " << prop.getLocation() << "\t\t" << fixed << setprecision(2) << "Price:" << prop.getPrice() << "\n" << "Type: " << prop.getType() <<
                            "\t\t" << "Number Of Bedrooms:" << prop.getBedrooms() << "\t\t" << "Number of Bathrooms:" << prop.getBathrooms() << "\t\t" << fixed << setprecision(2) << "Property Area:" << prop.getArea() << endl;
                    }
                }
                else {
                    cout << "Not Found This Type Of Properties!" << endl;
                }
                break;
            }
            default: {
                cout << "invalid Choice!" << endl;
                break;
            }
            }
            cout << "\n\n" << "Do You Want To Make A new Search?(y/n):";
            cin >> Exit;
       } while (Exit=='y'||Exit=='Y');
       return 0;
 }
