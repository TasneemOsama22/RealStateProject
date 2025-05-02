#pragma once
#include <string>
#include <sstream>
using namespace std;
enum PropertyStatus {
    Pending, Approved, Rejected
};
class Property {
private:
    string id;
    string title;
    double price;
    string location;
    string ownerName;
    double area;
    int bedrooms, bathrooms;
    PropertyStatus status;
    string type;
public:
    Property() = default;
    Property(const std::string& id, const std::string& title, double price,
        const std::string& location, const std::string& owner, double area,
        int bedrooms, int bathrooms,const std::string& type);

    Property(const std::string& title, double price,
        const std::string& location, const std::string& owner, double area,
        int bedrooms, int bathrooms, PropertyStatus status, const std::string& type);
    string getId() const;
    string getTitle() const;
    double getPrice() const;
    string getLocation() const;
    string getOwnerUsername() const;
    double getArea() const;
    int getBedrooms() const;
    int getBathrooms() const;
    string getType() const;
    void setId(const string& id);
    void setTitle(const string& title);
    void setPrice(double price);
    void setLocation(const string& location);
    void setOwnerUsername(const string& owner);
    void setArea(double area);
    void setBedrooms(int bedrooms);
    void setBathrooms(int bathrooms);
    void setType(const string& type);
    string toFileString() const;
    void fromFileString(const std::string& line);
};


