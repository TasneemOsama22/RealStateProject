#include "User.h"
#include "Property.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

// constructors
User::User() {}
User::User(const string& u, const string& p, bool a)
    : username(u), password(p), isAdmin(a) {
}
User::User(const string& id, const string& name, const string& email, const string& password)
    : userId(id), username(name), email(email), password(password), isAdmin(false) {
}

User::User(string userId, string pass) {
    this->userId = userId;
    this->password = pass;
}

string User::toFileString() const {
    return userId + "," + username + "," + email + "," + password + "," +
           (isAdmin ? "1" : "0") + "," +
           (isBanned ? "1" : "0") + "," +
           (IsBlocked ? "1" : "0") + "," +
           to_string(blockDaysRemaining);
}

void User::fromFileString(const string& line) {
    stringstream SS(line);
    string adminFlag, bannedFlag, blockedFlag, blockDaysStr;

    getline(SS, userId, ',');
    getline(SS, username, ',');
    getline(SS, email, ',');
    getline(SS, password, ',');
    getline(SS, adminFlag, ',');
    getline(SS, bannedFlag, ',');
    getline(SS, blockedFlag, ',');
    getline(SS, blockDaysStr);

    isAdmin = (adminFlag == "1");
    isBanned = (bannedFlag == "1");
    IsBlocked = (blockedFlag == "1");
    blockDaysRemaining = stoi(blockDaysStr);
}

bool User::checkPassword(const string& p) const {
    return password == p;
}

// Setters
void User::setIsBanned(bool value) {isBanned = value;}
void User::setblockDaysRemaining(int value) {blockDaysRemaining = value;}
void User::setIsBlocked(bool value) {IsBlocked = value;}
void User::setCanPost(bool value) {CanPost = value;}
void User::setWarningCount(int value) {WarningCount = value;}

// Getters
bool User::getIsBanned()const {return isBanned;}
int User::getblockDaysRemaining()const {return blockDaysRemaining;}
bool User::getIsBlocked()const {return IsBlocked;}
bool User::getCanPost()const {return CanPost;}
int User::getWarningCount()const {return WarningCount;}
string User::getUsername()const { return username; }
string User::getEmail()const { return email; }
string User::getPassword()const { return password; }
string User::getId()const { return userId; }
vector<Property>& User::getProperties() {
    return UserProperty;
}

// User functionalities
vector<Property> User::addProperty(unordered_map<string, User>& users,
                                   const string& currentUserId,
                                   vector<Property>& pendingProp)
{
    if (users.find(currentUserId) == users.end()) {
        cout << "Error: User not found." << endl;
        return pendingProp;
    }

    // Get the user's existing properties
    vector<Property>& userProperties = users[currentUserId].UserProperty;

    // Find the last property ID (if any) for this user
    int lastUserPropertyId = 0;
    if (!userProperties.empty()) {
        for (const Property& prop : userProperties) {
            if (prop.getId() > lastUserPropertyId) {
                lastUserPropertyId = prop.getId();
            }
        }
    }

    // Set the new property ID (it will be the next number after the last one)
    int newId = lastUserPropertyId + 1;

    string title, location, owner,type;
    double price, area;
    int bedrooms, bathrooms;

    cout << "Enter property details:" << endl;
    cout << "Title: ";
    getline(cin, title);
    cout << "Location: ";
    getline(cin, location);
    cout << "Type: ";
    getline(cin, type);
    cout << "Owner's name: ";
    getline(cin, owner);

    cout << "Area (in sqft): "; cin >> area;
    cout << "Price: "; cin >> price;
    cout << "Number of bedrooms: "; cin >> bedrooms;
    cout << "Number of bathrooms: "; cin >> bathrooms;
    cin.ignore();

    // Create the new property
    Property p(newId, currentUserId, title, price, location, owner, area,type, bedrooms, bathrooms, PropertyStatus::Pending, false);

    // Add the property to both the user's property list and the pending properties list
    pendingProp.push_back(p);
    users[currentUserId].UserProperty.push_back(p);

    cout << "Property added and is now under review. Please wait for admin's approval." << endl;
    return pendingProp;
}

void User::viewUserProperties(unordered_map<string, User>& users,
                              const string& currentUserId, const string& stat) {
    if (users.find(currentUserId) == users.end()) {
        cout << "Error: User not found." << endl;
        return;
    }

    vector<Property>& properties = users[currentUserId].UserProperty;

    if (properties.empty()) {
        cout << "You have not added any properties yet." << endl;
        return;
    }

    PropertyStatus filterStatus;
    if (stat == "Approved") filterStatus = PropertyStatus::Approved;
    else if (stat == "Pending") filterStatus = PropertyStatus::Pending;
    else if (stat == "Rejected") filterStatus = PropertyStatus::Rejected;
    else {
        cout << "Invalid status filter." << endl;
        return;
    }

    bool found = false;
    for (const auto& property : properties) {
        if (property.getStatus() == filterStatus) {
            found = true;
            cout << "---------------------------" << endl;
            cout << "Property ID: " << property.getId() << endl;
            cout << "Title: " << property.getTitle() << endl;
            cout << "Location: " << property.getLocation() << endl;
            cout << "Owner: " << property.getOwnerName() << endl;
            cout << "Area: " << property.getArea() << " sqft" << endl;
            cout << "Price: $" << property.getPrice() << endl;
            cout << "Bedrooms: " << property.getBedrooms() << endl;
            cout << "Bathrooms: " << property.getBathrooms() << endl;
            cout << "Status: " << checkPropertyStatus(property) << endl;

            if (filterStatus == PropertyStatus::Approved) {
                cout << "Sale Status: " << (property.getIsSold() ? "SOLD" : "Available for Sale") << endl;
            }
        }
    }

    if (!found) {
        cout << "No properties found with status: " << stat << endl;
    }
}
void User::CompareProperties(const vector<Property>& properties) {
    if (properties.size() < 2) { //check if we have at least two properties to compare
        cout << "Sorry! there are no enough properties to Compare\n";
        return;
    }

    unordered_map<int, Property> propertyMap; //make vector property into map with id as key to speed up the search
    for (const auto& prop : properties) {
        propertyMap[prop.getId()] = prop;
    }

    vector<Property> selectedProperties; //take the properties user enters
    cout << "Enter up to 4 properties id or type done to finish\n\n";
    for (int i = 0; i < 4; i++) {
        string input;
        cout << "Enter id for property #" << i + 1 << ": ";
        cin >> input;

        if (input == "done") {
            break;
        }
        try {
            int id = stoi(input);
            auto it = propertyMap.find(id);
            if (it != propertyMap.end()) {

                // prevent adding the same property twice
                bool alreadyAdded = false;
                for (const auto& p : selectedProperties) {
                    if (p.getId() == id) {
                        alreadyAdded = true;
                        break;
                    }
                }
                if (alreadyAdded) {
                    cout << "This property is already selected. Please enter a different ID.\n";
                    i--;
                }
                else {
                    selectedProperties.push_back(it->second);
                }
            }
            else {
                cout << "Property with ID " << id << " not found. Please try again.\n";
                i--; //do the iteration again
            }
        }
        catch (invalid_argument&) {
            cout << "Invalid input. Please enter a valid numeric ID or 'done'.\n";
            i--;
        }
    }
    //formatting a table for view
    cout << "\n=== COMPARISON RESULTS (" << selectedProperties.size() << " properties) ===\n";
    cout << "+----------+--------------------------+--------------+--------------+-----------------+\n";
    cout << "| " << left << setw(8) << "ID" << " | " << setw(24) << "Property Name"
         << " | " << setw(12) << "Location" << " | " << setw(12) << "Price"
         << " | " << setw(15) << "Owner" << "|\n";
    cout << "+----------+--------------------------+--------------+--------------+-----------------+\n";
    //showing selected props info
    for (const auto& prop : selectedProperties) {
        cout << "| " << setw(8) << prop.getId()
        << " | " << setw(24) << (prop.getTitle().substr(0, 23) + (prop.getTitle().length() > 23 ? "..." : ""))
        << " | " << setw(12) << prop.getLocation()
        << " | $" << setw(11) << fixed << setprecision(2) << prop.getPrice()
        << " | " << setw(15) << prop.getOwnerName() << "|\n";
    }
    cout << "+----------+--------------------------+--------------+--------------+-----------------+\n";
    //the props price range
    if (!selectedProperties.empty()) {
        double minPrice = selectedProperties[0].getPrice();
        double maxPrice = minPrice;
        for (const auto& prop : selectedProperties) {
            if (prop.getPrice() < minPrice) minPrice = prop.getPrice();
            if (prop.getPrice() > maxPrice) maxPrice = prop.getPrice();
        }
        cout << "\n  Price range: MIN " << minPrice << " -  MAX " << maxPrice
             << " (Difference: " << (maxPrice - minPrice) << ")\n";
    }
}
vector<Property> User::searchProperties(const vector<Property>& properties, const string& location, double lowerPrice, double higherPrice, const string& type) {
    vector<Property> Result;
    for (auto& property : properties) {
        bool searchMatching = true;

        if (!location.empty() && property.getLocation() != location) {
            searchMatching = false;
        }
        if (property.getPrice() < lowerPrice || property.getPrice() > higherPrice) {
            searchMatching = false;
        }
        if (!type.empty() && property.getType() != type) {
            searchMatching = false;
        }

        if (searchMatching == true) {
            Result.push_back(property);
        }
    }
    return Result;
}
void User::sortByPrice(vector<Property>& properties) {
    sort(properties.begin(), properties.end(), [](const Property& a, const Property& b) {
        return a.getPrice() < b.getPrice(); });
}
void User::sortByLocation(vector<Property>& properties) {
    sort(properties.begin(), properties.end(), [](const Property& a, const Property& b) {
        return a.getLocation() < b.getLocation(); });
}
void User::sortByType(vector<Property>& properties) {
    sort(properties.begin(), properties.end(), [](const Property& a, const Property& b) {
        return a.getType() < b.getType(); });
}
void User::sortByArea(vector<Property>& properties) {
    sort(properties.begin(), properties.end(), [](const Property& a, const Property& b) {
        return a.getArea() < b.getArea(); });
}
void User::sortByNumOfBedRooms(vector<Property>& properties) {
    sort(properties.begin(), properties.end(), [](const Property& a, const Property& b) {
        return a.getBedrooms() < b.getBedrooms(); });
}
vector<Property>User::binarySearchByLocation(vector<Property>& properties, const string& location)
{
    vector<Property> result;
    int low = 0, high = properties.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (properties[mid].getLocation() == location) {
            int left = mid;
            int right = mid + 1;
            result.push_back(properties[mid]);
            while (left > 0 && properties[left - 1].getLocation() == location) {
                result.push_back(properties[left - 1]);
                left--;
            }
            while (right < properties.size() && properties[right].getLocation() == location) {
                result.push_back(properties[right]);
                right++;
            }
            break;
        }
        else if (properties[mid].getLocation() < location) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return result;
}
vector<Property>User::binarySearchByPrice(vector<Property>& properties, double targetPrice) {
    vector<Property> result;
    int low = 0, high = properties.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (properties[mid].getPrice() == targetPrice) {
            int left = mid;
            int right = mid + 1;
            result.push_back(properties[mid]);
            while (left > 0 && properties[left - 1].getPrice() == targetPrice) {
                result.push_back(properties[left - 1]);
                left--;
            }
            while (right < properties.size() && properties[right].getPrice() == targetPrice) {
                result.push_back(properties[right]);
                right++;
            }
            break;
        }
        else if (properties[mid].getPrice() < targetPrice) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return result;
}
vector<Property>User::binarySearchByType(vector<Property>& properties, const string& targetType) {
    vector<Property> result;
    int low = 0, high = properties.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (properties[mid].getType() == targetType) {
            int left = mid;
            int right = mid + 1;
            result.push_back(properties[mid]);
            while (left > 0 && properties[left - 1].getType() == targetType) {
                result.push_back(properties[left - 1]);
                left--;
            }
            while (right < properties.size() && properties[right].getType() == targetType) {
                result.push_back(properties[right]);
                right++;
            }
            break;
        }
        else if (properties[mid].getType() < targetType) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return result;
}
vector<Property>User::binarySearchByNumOfBedRooms(vector<Property>& properties, int numOfBedRooms) {
    vector<Property> result;
    int low = 0, high = properties.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (properties[mid].getBedrooms() == numOfBedRooms) {
            int left = mid;
            int right = mid + 1;
            result.push_back(properties[mid]);
            while (left > 0 && properties[left - 1].getBedrooms() == numOfBedRooms) {
                result.push_back(properties[left - 1]);
                left--;
            }
            while (right < properties.size() && properties[right].getBedrooms() == numOfBedRooms) {
                result.push_back(properties[right]);
                right++;
            }
            break;
        }
        else if (properties[mid].getBedrooms() < numOfBedRooms) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return result;
}

vector<Property>User::binarySearchByArea(vector<Property>& properties, double area) {
    vector<Property> result;
    int low = 0, high = properties.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (properties[mid].getArea() == area) {
            int left = mid;
            int right = mid + 1;
            result.push_back(properties[mid]);
            while (left > 0 && properties[left - 1].getArea() == area) {
                result.push_back(properties[left - 1]);
                left--;
            }
            while (right < properties.size() && properties[right].getArea() == area) {
                result.push_back(properties[right]);
                right++;
            }
            break;
        }
        else if (properties[mid].getArea() < area) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return result;
}


void User::buyProperty(vector<Property>& properties, const string& buyerId) {
    cout << "Available Properties for Sale:\n";
    bool found = false;
    for (const auto& prop : properties) {
        if (prop.getStatus() == PropertyStatus::Approved && !prop.getIsSold()) {
            found = true;
            cout << "---------------------------" << endl;
            cout << "Property ID: " << prop.getId() << endl;
            cout << "Title: " << prop.getTitle() << endl;
            cout << "Location: " << prop.getLocation() << endl;
            cout << "Price: $" << prop.getPrice() << endl;
            cout << "Owner: " << prop.getOwnerName() << endl;
        }
        if (!found) {
            cout << "No properties available for purchase." << endl;
            return;
        }
        cout << "Write property Id you want to purchase : ";
        int choosenId;
        cin >> choosenId;

        for (auto& prop : properties) {
            if (prop.getId() == choosenId) {
                prop.setIsSold(true);
                cout << "Property purchased successfully!" << endl;
                return;
            }
        }

        cout << "Invalid Property ID or Property already sold." << endl;
    }
}
string User::checkPropertyStatus(const Property& property) {
    switch (property.getStatus()) {
    case PropertyStatus::Pending:
        return "Pending (Under Review)";
    case PropertyStatus::Approved:
        return "Approved";
    case PropertyStatus::Rejected:
        return "Rejected";
    default:
        return "Unknown Status";
    }
}

void User::userDashboard(unordered_map<string, User>& userMap, vector<Property>& pendingAds, vector<Property>& approvedAds, const string& loggedInId) {
    while (true) {
        cout << "\nUser Menu:\n";
        cout << "1. Search Properties\n";
        cout << "2. Add Property\n";
        cout << "3. View My Properties\n";
        cout << "4. Buy Property\n";
        cout << "5. Compare Properties\n";
        cout << "6. Logout\n";
        cout << "Choose: ";
        int userChoice;
        cin >> userChoice;
        cin.ignore();

        if (userChoice == 1) {
            string location, type;
            double minPrice, maxPrice;
            cout << "Location: "; getline(cin, location);
            cout << "Type: "; getline(cin, type);
            cout << "Min Price: "; cin >> minPrice;
            cout << "Max Price: "; cin >> maxPrice; cin.ignore();
            auto results = searchProperties(approvedAds, location, minPrice, maxPrice, type);
            cout << "\nSearch Results:\n";
            for (const auto& prop : results) {
                cout << "ID: " << prop.getId() << ", Title: " << prop.getTitle() << ", Price: " << prop.getPrice() << endl;
            }
        }
        else if (userChoice == 2) {
            addProperty(userMap, loggedInId, pendingAds);
        }
        else if (userChoice == 3) {
            viewUserProperties(userMap, loggedInId, "Pending");
        }
        else if (userChoice == 4) {
            buyProperty(approvedAds, loggedInId);
        }
        else if (userChoice == 5) {
            CompareProperties(approvedAds);
        }
        else if (userChoice == 6) {
            break;
        }
    }
}
QTextStream& operator<<(QTextStream& out, const User& user) {
    out << QString::fromStdString(user.getId()) << ","
        << QString::fromStdString(user.getUsername()) << ","
        << QString::fromStdString(user.getEmail()) << ","
        << QString::fromStdString(user.getPassword()) << ","
        << "user";
    return out;
}
User::~User() = default;
