#include "Property.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;


Property::Property(const string& id, const string& title, double price,const string& location, const string& owner)
    : id(id), title(title), price(price), location(location), ownerName(owner) {}

string Property::getId() const {
    return id;
}

string Property::getTitle() const {
    return title;
}

double Property::getPrice() const {
    return price;
}

string Property::getLocation() const {
    return location;
}

string Property::getOwnerUsername() const {
    return ownerName;
}

string Property::toFileString() const {
   
    return id + "," + title + "," + to_string( price) + "," + location + "," + ownerName;
}

void Property::fromFileString(const std::string& line) {
    stringstream SS(line);
    getline(SS, id, ',');
    getline(SS, title, ',');
    string priceStr; //take price as string to the file
    getline(SS, priceStr, ',');
    getline(SS, location, ',');
    getline(SS, ownerName);
    try {
        price = stod(priceStr); //to make the price value double 
    }
    catch (invalid_argument e) {
        cerr << "ERROR  " << e.what() << endl; //throw error when its not double
    }
       
}



