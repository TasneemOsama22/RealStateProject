#include <iostream>
#include "Property.h"
#include"search.h"
#include <vector>
using namespace std;
int main() {
    search s;
    vector<Property>  properties =
    {
    Property("123", "This Property If Good", 1500000, "Cairo","Omnia",150000,4,2,"Apartment"),
    Property("454", "Look At Our Property", 2500000, "Cairo","Alaa",236734,8,4,"Villa"),
    Property("323", "Simple", 3000000, "Cairo","Esraa",35990,10,5,"Block"),

    };
        string location = "Cairo";
        double lowerPrice = 100000;
        double higherPrice = 200000;
        string type = "Apartment";
         int choice=0;
         cout << "Press 1 if you want to searching By Location,Price or Type"<<endl;
         cout << "Press 2 if you want to searching By Location only" << endl;
         cout << "Press 3 if you want to searching By Price only" << endl;
         cout << "Press 4 if you want to searching By Type only" << endl;
         cin >> choice;
         switch (choice)
         {
         case 1:
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
                     cout << "Owner User Name:" << prop.getOwnerUsername() << "\t" << "Property Title:" << prop.getTitle() << "\n" << "Location: " << prop.getLocation() << "\t" << "Price:" << prop.getPrice() << "\n" << "Type: " << prop.getType() <<
                         "\t" << "Number Of Bedrooms:" << prop.getBedrooms() << "\t" << "Number of Bathrooms:" << prop.getBedrooms() << "\t" << "Property Area:" << prop.getArea() << endl;
                 }
                 break;
         case 2:
             cout << "Location:" << endl;
             cin >> location;
                 for (const auto& prop : s.searchByLocation(properties, location)) {

                     cout << "Owner User Name:" << prop.getOwnerUsername() << "\t" << "Property Title:" << prop.getTitle() << "\n" << "Location: " << prop.getLocation() << "\t" << "Price:" << prop.getPrice() << "\n" << "Type: " << prop.getType() <<
                         "\t" << "Number Of Bedrooms:" << prop.getBedrooms()<<"\t"<<"Number of Bathrooms:"<<prop.getBedrooms()<<"\t"<< "Property Area:" << prop.getArea() << endl;
                 }
                 break;
         case 3:
             cout << "Lower Price:";
             cin >> lowerPrice;
             cout << "Higher Price:";
             cin >> higherPrice;
                 for (const auto& prop : s.searchByPrices(properties, lowerPrice, higherPrice)) {
                     cout << "Owner User Name:" << prop.getOwnerUsername() << "\t" << "Property Title:" << prop.getTitle() << "\n" << "Location: " << prop.getLocation() << "\t" << "Price:" << prop.getPrice() << "\n" << "Type: " << prop.getType() <<
                         "\t" << "Number Of Bedrooms:" << prop.getBedrooms() << "\t" << "Number of Bathrooms:" << prop.getBedrooms() << "\t" << "Property Area:" << prop.getArea() << endl;
                 }
                 break;
         case 4:
             cout << "Type:";
             cin >> type;
                 for (const auto& prop : s.searchByType(properties, type)) {
                     cout << "Owner User Name:" << prop.getOwnerUsername() << "\t" << "Property Title:" << prop.getTitle() << "\n" << "Location: " << prop.getLocation() << "\t" << "Price:" << prop.getPrice() << "\n" << "Type: " << prop.getType() <<
                         "\t" << "Number Of Bedrooms:" << prop.getBedrooms()<<"\t"<<"Number of Bathrooms:"<<prop.getBedrooms()<<"\t"<< "Property Area:" << prop.getArea() << endl;
                 }
                 break;
         default:
             break;
             }
       return 0;
 }
