#pragma once
#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
enum PropertyStatus {
    Pending, Approved, Rejected
};

class Property {
private:
    string id;
    string UserId;
    string title;
    double price;
    string location;
    string ownerName;
    PropertyStatus status;

public:
    Property() = default;
    Property(const std::string& id, const std::string& Userid, const std::string& title, double price, const std::string& location, const std::string& owner);
    string getId() const;
    string getUserId() const;
    string getTitle() const;
    double getPrice() const;
    string getLocation() const;
    string getOwnerUsername() const;
    PropertyStatus getStatus() const;
    string getStatusAsString() const;

    // Setters
    void setStatus(PropertyStatus newStatus);
};
