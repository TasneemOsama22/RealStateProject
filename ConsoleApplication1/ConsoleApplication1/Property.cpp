#include "Property.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;


Property::Property(const string& id, const string& Userid, const string& title, double price, const string& location, const string& owner)
    : id(id), UserId(Userid), title(title), price(price), location(location), ownerName(owner), status(PENDING) {
}

string Property::getId() const {
    return id;
}
string Property::getUserId() const {
    return UserId;
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


PropertyStatus Property::getStatus() const {
    return status;
}

string Property::getStatusAsString() const {
    switch (status) {
    case PENDING: return "Pending";
    case APPROVED: return "Approved";
    case REJECTED: return "Rejected";
    default: return "Unknown";
    }
}

void Property::setStatus(PropertyStatus newStatus) {
    status = newStatus;
}