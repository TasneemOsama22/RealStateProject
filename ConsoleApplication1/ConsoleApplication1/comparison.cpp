#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "Property.h"
#include "Property.cpp"
#include <iomanip>
using namespace std;

void CompareProperties(const vector<Property>& properties) {
    if (properties.size() < 2) { //check if we have at least two properties to compare
        cout << "Sorry! there are no enough properties to Compare\n";
        return;
    }

    unordered_map<string, Property> propertyMap; //make vector property into map with id as key to speed up the search
    for (const auto& prop : properties) {
        propertyMap[prop.getId()] = prop;
    }

    vector<Property> selectedProperties; //take the properties user enters
    cout << "Enter up to 4 properties id or type done to finish\n";
    for (int i = 0; i < 4; i++) {
        string id;
        cout << "Enter id for property #" << i + 1 << ": ";
        cin >> id;

        if (id == "done") {
            break;
        }
        else {
            auto it = propertyMap.find(id);
            if (it != propertyMap.end()) {
                selectedProperties.push_back(it->second); // Add the found property to the vector
            }
            else { //no matching id found
                cout << "property with ID" << id << "not found.Please try again.\n";
                i--; // Repeat this one again
            }
        }
    }

    cout << "\n=== COMPARISON RESULTS (" << selectedProperties.size() << " properties) ===\n";
    cout << "+----------+--------------------------+--------------+--------------+-----------------+\n";
    cout << "| " << left << setw(8) << "ID" << " | " << setw(24) << "Property Name"
        << " | " << setw(12) << "Location" << " | " << setw(12) << "Price"
        << " | " << setw(15) << "Owner" << "|\n";
    cout << "+----------+--------------------------+--------------+--------------+-----------------+\n";

    for (const auto& prop : selectedProperties) {
        cout << "| " << setw(8) << prop.getId()
            << " | " << setw(24) << (prop.getTitle().substr(0, 23) + (prop.getTitle().length() > 23 ? "..." : ""))
            << " | " << setw(12) << prop.getLocation()
            << " | $" << setw(11) << fixed << setprecision(2) << prop.getPrice()
            << " | " << setw(15) << prop.getOwnerUsername() << "|\n";
    }
    cout << "+----------+--------------------------+--------------+--------------+-----------------+\n";

    if (!selectedProperties.empty()) {
        double minPrice = selectedProperties[0].getPrice();
        double maxPrice = minPrice;
        for (const auto& prop : selectedProperties) {
            if (prop.getPrice() < minPrice) minPrice = prop.getPrice();
            if (prop.getPrice() > maxPrice) maxPrice = prop.getPrice();
        }
        cout << "\n  Price range: " << minPrice << " - " << maxPrice
            << " (Difference: " << (maxPrice - minPrice) << ")\n";
    }
}