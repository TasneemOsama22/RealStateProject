#pragma once
#include <string>
#include <sstream>
using namespace std;

enum PropertyStatus {
    Pending,
    Approved,
    Rejected
};

class Property {
private:
    int id;
    string title;
    string type;
    double price;
    string location;
    string ownerName;
    string userId;
    double area;
    int bedrooms, bathrooms;
    PropertyStatus status;
    bool highlighted; 



public:
    Property();
    Property(const int id, const string& title, const string& type, const string& location, double price, const string& owner, const string& userId, int bedrooms, int bathrooms, double area, PropertyStatus status, bool highlighted = 0);
    

    // Getters
    int getId() const;
    string getTitle() const;
    string getType() const;
    double getPrice() const;
    string getLocation() const;
    string getOwnerName() const;
    string getUserId() const;
    double getArea() const;
    int getBedrooms() const;
    int getBathrooms() const;
    PropertyStatus getStatus() const;
    bool isHighlighted() const;

    // Setters
    void setId(const int newId);
    void setTitle(const string& newTitle);
    void setType(const string& newType);
    void setPrice(double newPrice);
    void setLocation(const string& newLocation);
    void setOwnerName(const string& newOwner);
    void setUserId(const string& newUserId);
    void setArea(double newArea);
    void setBedrooms(int newBedrooms);
    void setBathrooms(int newBathrooms);
    void setStatus(PropertyStatus newStatus);
    void setHighlighted(bool highlight);

   
    string toFileString() const;

    
    void fromFileString(const std::string& line);
};

