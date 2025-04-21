#pragma once
#include <string>
#include <sstream>
using namespace std;
class Property {
private:
    string id;
    string title;
    double price;
    string location;
    string ownerName;

public:
    Property() = default;
    Property(const std::string& id, const std::string& title, double price, const std::string& location, const std::string& owner);
    string getId() const;
    string getTitle() const;
    double getPrice() const;
    string getLocation() const;
    string getOwnerUsername() const;

    string toFileString() const;
    void fromFileString(const std::string& line);
};


