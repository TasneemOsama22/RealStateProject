#include "Property.h"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

// Constructors
Property::Property()
    : id(0), price(0), area(0), bedrooms(0), bathrooms(0),
    status(Pending), highlighted(false), isSold(false) {
}

Property::Property(const int id, const string& userId, const string& title, double price,
    const string& location, const string& owner, double area,
    int bedrooms, int bathrooms, PropertyStatus status, bool highlighted)
    : id(id), userId(userId), title(title), price(price), location(location),
    ownerName(owner), area(area), bedrooms(bedrooms), bathrooms(bathrooms),
    status(status), highlighted(highlighted), isSold(false) {
}

Property::Property(const string& title, double price,
    const string& location, const string& owner, double area,
    int bedrooms, int bathrooms, PropertyStatus status)
    : id(0), title(title), price(price), location(location), ownerName(owner),
    area(area), bedrooms(bedrooms), bathrooms(bathrooms), status(status),
    highlighted(false), isSold(false) {
}

// Getters
int Property::getId() const { return id; }
string Property::getTitle() const { return title; }
string Property::getType() const { return type; }
double Property::getPrice() const { return price; }
string Property::getLocation() const { return location; }
string Property::getOwnerName() const { return ownerName; }
string Property::getUserId() const { return userId; }
double Property::getArea() const { return area; }
int Property::getBedrooms() const { return bedrooms; }
int Property::getBathrooms() const { return bathrooms; }
PropertyStatus Property::getStatus() const { return status; }
bool Property::isHighlighted() const { return highlighted; }
bool Property::getIsSold() const { return isSold; }

// Setters
void Property::setId(const int newId) { id = newId; }
void Property::setTitle(const string& newTitle) { title = newTitle; }
void Property::setType(const string& newType) { type = newType; }
void Property::setPrice(double newPrice) { price = newPrice; }
void Property::setLocation(const string& newLocation) { location = newLocation; }
void Property::setOwnerName(const string& newOwner) { ownerName = newOwner; }
void Property::setUserId(const string& newUserId) { userId = newUserId; }
void Property::setArea(double newArea) { area = newArea; }
void Property::setBedrooms(int newBedrooms) { bedrooms = newBedrooms; }
void Property::setBathrooms(int newBathrooms) { bathrooms = newBathrooms; }
void Property::setStatus(PropertyStatus newStatus) { status = newStatus; }
void Property::setHighlighted(bool highlight) { highlighted = highlight; }
void Property::setIsSold(bool sold) { isSold = sold; }

string Property::toFileString() const {
    stringstream ss;
    ss << id << "|"
        << title << "|"
        << type << "|"
        << location << "|"
        << price << "|"
        << ownerName << "|"
        << userId << "|"
        << bedrooms << "|"
        << bathrooms << "|"
        << area << "|";

    if (status == Pending) ss << "Pending";
    else if (status == Approved) ss << "Approved";
    else ss << "Rejected";

    ss << "|" << (highlighted ? 1 : 0)
        << "|" << (isSold ? 1 : 0);

    return ss.str();
}

void Property::fromFileString(const string& line) {
    stringstream ss(line);
    string field;

    try {
        getline(ss, field, '|');
        id = stoi(field);
        getline(ss, title, '|');
        getline(ss, type, '|');
        getline(ss, location, '|');
        getline(ss, field, '|'); price = stod(field);
        getline(ss, ownerName, '|');
        getline(ss, userId, '|');
        getline(ss, field, '|'); bedrooms = stoi(field);
        getline(ss, field, '|'); bathrooms = stoi(field);
        getline(ss, field, '|'); area = stod(field);

        getline(ss, field, '|');
        if (field == "Pending") status = Pending;
        else if (field == "Approved") status = Approved;
        else if (field == "Rejected") status = Rejected;
        else {
            cout << "Error: Invalid status value: " << field << endl;
            status = Rejected;
        }

        getline(ss, field, '|');
        highlighted = (stoi(field) == 1);

        if (getline(ss, field, '|')) {
            isSold = (stoi(field) == 1);
        }
        else {
            isSold = false;
        }
    }
    catch (const exception& e) {
        cout << "Error reading property from file: " << e.what() << endl;
    }
}


