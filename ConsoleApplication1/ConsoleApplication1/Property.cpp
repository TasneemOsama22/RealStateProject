#include "Property.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;



Property::Property(const std::string& id, const std::string& title, double price, const std::string& location, const std::string& owner, double area, int bedrooms, int bathrooms)
{
}
Property::Property(const std::string& title, double price, const std::string& location,
    const std::string& owner, double area, int bedrooms, int bathrooms, PropertyStatus status)
{
}

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

double Property::getArea() const
{
    return 0.0;
}

int Property::getBedrooms() const
{
    return 0;
}

int Property::getBathrooms() const
{
    return 0;
}
PropertyStatus getStatus() const { return status; }
void Property::setId(const string& newId) {
    id = newId;
}

void Property::setTitle(const string& newTitle) {
    title = newTitle;
}

void Property::setPrice(double newPrice) {
    price = newPrice;
}

void Property::setLocation(const string& newLocation) {
    location = newLocation;
}

void Property::setOwnerUsername(const string& newOwner) {
    ownerName = newOwner;
}

void Property::setArea(double newArea) {
    area = newArea;
}

void Property::setBedrooms(int newBedrooms) {
    bedrooms = newBedrooms;
}

void Property::setBathrooms(int newBathrooms) {
    bathrooms = newBathrooms;
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

