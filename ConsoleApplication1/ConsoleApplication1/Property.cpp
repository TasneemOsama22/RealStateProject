#include "Property.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;



Property::Property(const std::string& id, const std::string& title, double price,
    const std::string& location, const std::string& owner, double area,
    int bedrooms, int bathrooms, const std::string& type)
    : id(id), title(title), price(price),location(location), ownerName(owner),
    area(area), bedrooms(bedrooms), bathrooms(bathrooms), status(status), type(type)
{
}

Property::Property(const std::string& title, double price,
    const std::string& location, const std::string& owner, double area,
    int bedrooms, int bathrooms, PropertyStatus status, const std::string& type)
    : title(title), price(price), location(location), ownerName(owner),
    area(area), bedrooms(bedrooms), bathrooms(bathrooms), status(status), type(type)
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
    return area;
}

int Property::getBedrooms() const
{
    return bedrooms;
}

int Property::getBathrooms() const
{
    return bathrooms;
}

string Property::getType() const {
    return type;
}
PropertyStatus getStatus() {
    return getStatus();
}
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

void Property::setType(const string& newType) {
    type = newType;
}
string Property::toFileString() const {

    return id + "," + title + "," + to_string(price) + "," + to_string(area) + "," + ownerName;
}

void Property::fromFileString(const std::string& line) {
    stringstream SS(line);
    getline(SS, id, ',');
    getline(SS, title, ',');
    string priceStr; //take price as string to the file
    getline(SS, priceStr, ',');
    string areaStr;
    getline(SS, areaStr, ',');
    getline(SS, ownerName);
    try {
        price = stod(priceStr); //to make the price value double 
    }
    catch (invalid_argument e) {
        cerr << "ERROR  " << e.what() << endl; //throw error when its not double
    }

}
