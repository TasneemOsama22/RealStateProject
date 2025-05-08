#include <iostream>
#include "FileHandler.h"
#include "User.h"
#include "Property.h"
#include <unordered_map>
#include <vector>
#include <iomanip>
using namespace std;
void CompareProperties(const vector<Property>& properties);
int main() {
    unordered_map<string, User> users;
    vector<Property> properties;
    try {
        
        FileHandler::loadUsers(users, "../users.txt");
        FileHandler::loadProperties(properties, "../properties.txt");
     
            properties.emplace_back("P001", "Beach Villa", 2500000, "Malibu", "admin");
            properties.emplace_back("P002", "City Apartment", 1200000, "New York", "superadmin");
            properties.emplace_back("P003", "Mountain Cabin", 750000, "Aspen", "admin");
          
            cout << "Default properties added\n";
        

        FileHandler::saveUsers(users, "../users.txt");
        cout << "Users saved to users.txt\n";
        FileHandler::saveProperties(properties, "../properties.txt");
        cout << "Properties saved to properties.txt\n";

    }
    catch (const exception& e) {
        cerr << "[Main Error] " << e.what() << endl;
        return 1;
    }
    CompareProperties(properties);


    return 0;
}

void CompareProperties(const vector<Property>& properties) {
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
            << " | " << setw(15) << prop.getOwnerUsername() << "|\n";
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