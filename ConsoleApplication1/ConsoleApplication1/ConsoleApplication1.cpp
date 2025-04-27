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
         vector<Property>searchResult = s.searchProperties(properties, location, lowerPrice, higherPrice, type);
         vector<Property>searchResultLocation = s.searchByLocation(properties, location);
         vector<Property>searchResultPrices = s.searchByPrices(properties ,lowerPrice, higherPrice);
         vector<Property>searchResultType = s.searchByType(properties,type);
         cout << "Press 1 if you want to searching By Location,Price or Type"<<endl;
         cout << "Press 2 if you want to searching By Location only" << endl;
         cout << "Press 3 if you want to searching By Price only" << endl;
         cout << "Press 4 if you want to searching By Type only" << endl;
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
             
             if (!searchResult.empty()) {
                 cout << "Search Result:"<<endl;
             }
                 for (const auto& prop : searchResult) {
                     cout << "Owner User Name:" << prop.getOwnerUsername() << "\t" << "Property Title:" << prop.getTitle() << "\n" << "Location: " << prop.getLocation() << "\t" << "Price:" << prop.getPrice() << "\n" << "Type: " << prop.getType() <<
                         "\t" << "Number Of Bedrooms:" << prop.getBedrooms() << "\t" << "Number of Bathrooms:" << prop.getBedrooms() << "\t" << "Property Area:" << prop.getArea() << endl;
                 }
                 break;
         case 2:
             cout << "Location:" << endl;
             cin >> location;
             if (!searchResultLocation.empty()) {
                 cout << "Search Result:" << endl;
             }
                 for (const auto& prop : searchResultLocation) {

                     cout << "Owner User Name:" << prop.getOwnerUsername() << "\t" << "Property Title:" << prop.getTitle() << "\n" << "Location: " << prop.getLocation() << "\t" << "Price:" << prop.getPrice() << "\n" << "Type: " << prop.getType() <<
                         "\t" << "Number Of Bedrooms:" << prop.getBedrooms()<<"\t"<<"Number of Bathrooms:"<<prop.getBedrooms()<<"\t"<< "Property Area:" << prop.getArea() << endl;
                 }
                 break;
         case 3:
             cout << "Lower Price:";
             cin >> lowerPrice;
             cout << "Higher Price:";
             cin >> higherPrice;
             if (!searchResultPrices.empty()) {
                 cout << "Search Result:" << endl;
             }
                 for (const auto& prop : searchResultPrices) {
                     cout << "Owner User Name:" << prop.getOwnerUsername() << "\t" << "Property Title:" << prop.getTitle() << "\n" << "Location: " << prop.getLocation() << "\t" << "Price:" << prop.getPrice() << "\n" << "Type: " << prop.getType() <<
                         "\t" << "Number Of Bedrooms:" << prop.getBedrooms() << "\t" << "Number of Bathrooms:" << prop.getBedrooms() << "\t" << "Property Area:" << prop.getArea() << endl;
                 }
                 break;
         case 4:
             cout << "Type:";
             cin >> type;
             if (!searchResultType.empty()) {
                 cout << "Search Result:" << endl;
             }
                 for (const auto& prop : searchResultType) {
                     cout << "Owner User Name:" << prop.getOwnerUsername() << "\t" << "Property Title:" << prop.getTitle() << "\n" << "Location: " << prop.getLocation() << "\t" << "Price:" << prop.getPrice() << "\n" << "Type: " << prop.getType() <<
                         "\t" << "Number Of Bedrooms:" << prop.getBedrooms()<<"\t"<<"Number of Bathrooms:"<<prop.getBedrooms()<<"\t"<< "Property Area:" << prop.getArea() << endl;
                 }
                 break;
         default:
             break;
             }
       return 0;
 }
