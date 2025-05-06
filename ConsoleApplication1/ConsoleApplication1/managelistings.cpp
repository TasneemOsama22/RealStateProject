#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Property.h"

using namespace std;

// Global Variables 
map<int, Property> approvedListings;
map<int, Property> allListings;
vector<string> types = {
    "Apartment",
    "Villa",
    "Chalet",
    "Studio",
    "Duplex",
    "Townhouse",
    "Farmhouse"
};

vector<string> locations = {
    "New Cairo",
    "6th October",
    "North Coast",
    "Zayed City",
    "Maadi",
    "Heliopolis",
    "Nasr City",
};

// Function Declarations
void loadListings();
void saveListings();
int generateNewId();
string chooseType();
string chooseLocation();

void addProperty();
void editProperty();
void removeProperty();
void toggleHighlightProperty();
void showAllProperties();
void adminDashboard();

// Function Definitions 


int generateNewId() {
    if (allListings.empty()) return 1001;

    int maxId = 0;
    for (const auto& pair : allListings) {
        if (pair.first > maxId) {
            maxId = pair.first;
        }
    }
    return maxId + 1;
}


void loadListings() {
    ifstream file("listings.txt");
    if (!file) {
        cout << "Error: Could not open listings.txt\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        Property p;
        p.fromFileString(line);
        allListings[p.getId()] = p;  

       
        if (p.getStatus() == Approved) {
            approvedListings[p.getId()] = p;
        }
    }
    file.close();
}

void saveListings() {
    ofstream file("listings.txt");
    if (!file) {
        cout << "Error: Could not open listings.txt for writing\n";
        return;
    }

    for (const auto& pair : allListings) {
        file << pair.second.toFileString() << endl;
    }

    file.close();
}

string chooseType() {
    int choice;
    while (true) {
        cout << "\nAvailable Types: \n";
        for (int i = 0; i < types.size(); ++i) {
            cout << i + 1 << ". " << types[i] << "\n";
        }
        cout << "Enter the number corresponding to the property type: ";
        cin >> choice;

        if (choice >= 1 && choice <= types.size()) {
            return types[choice - 1];
        }

        cout << "Invalid choice. Please try again.\n";
    }
}

string chooseLocation() {
    int choice;
    while (true) {
        cout << "\nAvailable Locations: \n";
        for (int i = 0; i < locations.size(); ++i) {
            cout << i + 1 << ". " << locations[i] << "\n";
        }
        cout << "Enter the number corresponding to the property location: ";
        cin >> choice;

        if (choice >= 1 && choice <= locations.size()) {
            return locations[choice - 1];
        }

        cout << "Invalid choice. Please try again.\n";
    }
}


void addProperty() {
    Property p;
    cout << "\n--- Add New Property ---\n";

    p.setId(generateNewId());
    cin.ignore();

    string title;
    cout << "Enter Title: ";
    getline(cin, title);
    p.setTitle(title);

    p.setType(chooseType());
    p.setLocation(chooseLocation());

    double price;
    cout << "Enter Price: ";
    cin >> price;
    p.setPrice(price);

    cin.ignore();
    string owner;
    cout << "Enter Owner Name: ";
    getline(cin, owner);
    p.setOwnerName(owner);

    string userId;
    cout << "Enter User ID: ";
    getline(cin, userId);
    p.setUserId(userId);

    double area;
    cout << "Enter Area (Square meter): ";
    cin >> area;
    p.setArea(area);

    int bedrooms;
    cout << "Enter Number of Bedrooms: ";
    cin >> bedrooms;
    p.setBedrooms(bedrooms);

    int bathrooms;
    cout << "Enter Number of Bathrooms: ";
    cin >> bathrooms;
    p.setBathrooms(bathrooms);

    int isHighlighted;
    cout << "Highlight this property? (1: Yes, 0: No): ";
    cin >> isHighlighted;

    while (isHighlighted != 1 && isHighlighted != 0) {
        cout << "Invalid input. Please enter 1 (Yes) or 0 (No): ";
        cin >> isHighlighted;
    }
    p.setHighlighted(isHighlighted == 1);

    p.setStatus(Approved); 

   
    approvedListings[p.getId()] = p;
    allListings[p.getId()] = p;

    saveListings();

    cout << "\nProperty added successfully! ID: " << p.getId() << "\n";
}


void editProperty() {
    cout << "\n--- Edit Property ---\n";

    map<int, Property>* listingsToEdit = nullptr;

    while (true) {
        int choice1;
        cout << "Choose where to edit property:\n";
        cout << "1. Edit in All Listings\n";
        cout << "2. Edit in Approved Listings\n";
        cout << "3. Back\n";
        cout << "Enter your choice: ";
        cin >> choice1;

        if (choice1 == 1) {
            listingsToEdit = &allListings;
            break;
        }
        else if (choice1 == 2) {
            listingsToEdit = &approvedListings;
            break;
        }
        else if (choice1 == 3) {
            cout << "Returning to main menu...\n";
            return;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    int id;
    cout << "\nEnter Property ID to Edit: ";
    cin >> id;

    auto it = listingsToEdit->find(id);
    if (it == listingsToEdit->end()) {
        cout << "Property not found in selected listings.\n";
        return;
    }

    Property& p = it->second;
    cout << "Editing: " << p.getTitle() << "\n";

    int choice;
    do {
        cout << "\nWhich property field would you like to edit?\n";
        cout << "1. Title (" << p.getTitle() << ")\n";
        cout << "2. Type (" << p.getType() << ")\n";
        cout << "3. Location (" << p.getLocation() << ")\n";
        cout << "4. Price (" << p.getPrice() << ")\n";
        cout << "5. Owner Name (" << p.getOwnerName() << ")\n";
        cout << "6. Area (" << p.getArea() << " Square meter)\n";
        cout << "7. Bedrooms (" << p.getBedrooms() << ")\n";
        cout << "8. Bathrooms (" << p.getBathrooms() << ")\n";
        cout << "9. Status (" << (p.getStatus() == Approved ? "Approved" : (p.getStatus() == Pending ? "Pending" : "Rejected")) << ")\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string newTitle;
            cout << "Enter new Title: ";
            getline(cin, newTitle);
            p.setTitle(newTitle);
            break;
        }
        case 2: {
            p.setType(chooseType());

            break;
        }
        case 3: {
            p.setLocation(chooseLocation());
            break;
        }
        case 4: {
            double newPrice;
            cout << "Enter new Price: ";
            cin >> newPrice;
            p.setPrice(newPrice);
            break;
        }
        case 5: {
            string newOwner;
            cout << "Enter new Owner Name: ";
            getline(cin, newOwner);
            p.setOwnerName(newOwner);
            break;
        }
        case 6: {
            double newArea;
            cout << "Enter new Area (Square meter): ";
            cin >> newArea;
            p.setArea(newArea);
            break;
        }
        case 7: {
            int newBedrooms;
            cout << "Enter new Bedrooms: ";
            cin >> newBedrooms;
            p.setBedrooms(newBedrooms);
            break;
        }
        case 8: {
            int newBathrooms;
            cout << "Enter new Bathrooms: ";
            cin >> newBathrooms;
            p.setBathrooms(newBathrooms);
            break;
        }
        case 9: {
            int newStatus;
            cout << "Enter new Status (0: Pending, 1: Approved, 2: Rejected): ";
            cin >> newStatus;
            p.setStatus(static_cast<PropertyStatus>(newStatus));

            if (p.getStatus() == Approved) {
                approvedListings[p.getId()] = p;
            }
            else {
                approvedListings.erase(p.getId());
            }
            break;
        }
        case 10:
            cout << "Exiting Edit Menu.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 10);

    saveListings();
    cout << "Property updated and saved.\n";
}


void removeProperty() {
    map<int, Property>* listingsToRemove = nullptr;

    while (true) {
        int choice1;
        cout << "\n--- Remove Property ---\n";
        cout << "1. Remove from All Listings\n";
        cout << "2. Remove from Approved Listings\n";
        cout << "3. Back\n";
        cout << "Enter your choice: ";
        cin >> choice1;

        if (choice1 == 1) {
            listingsToRemove = &allListings;
            break;
        }
        else if (choice1 == 2) {
            listingsToRemove = &approvedListings;
            break;
        }
        else if (choice1 == 3) {
            cout << "Returning to main menu...\n";
            return;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    int id;
    cout << "Enter Property ID to remove: ";
    cin >> id;

    if (listingsToRemove->erase(id)) {
   
        allListings.erase(id);
        approvedListings.erase(id);

        saveListings();
        cout << "Property removed successfully.\n";
    }
    else {
        cout << "Property not found in the selected listings.\n";
    }
}


bool compareHighlighted(Property& a, Property& b) {
    return a.isHighlighted() > b.isHighlighted();
}

void toggleHighlightProperty() {
    int id;
    cout << "\n--- Toggle Highlight ---\n";
    cout << "Enter Property ID: ";
    cin >> id;

    auto it = approvedListings.find(id);
    if (it != approvedListings.end()) {
      
        it->second.setHighlighted(!it->second.isHighlighted());

       
        auto itall = allListings.find(id);
        if (itall != allListings.end()) {
            itall->second.setHighlighted(it->second.isHighlighted());
        }

        saveListings();
        cout << "Highlight status toggled successfully.\n";
    }
    else {
        cout << "Property not found in approved listings.\n";
    }
}


void showAllProperties() {
    cout << fixed << setprecision(2);

   
    int choice1;
    cout << "Choose which listings to display:\n";
    cout << "1. Show All Listings\n";
    cout << "2. Show Approved Listings\n";
    cout << "3. Back\n";
    cout << "Enter your choice: ";
    cin >> choice1;

  
    map<int, Property>* listingsToShow = nullptr;

    while (true) {
        if (choice1 == 1) {
            listingsToShow = &allListings;
            break;
        }
        else if (choice1 == 2) {
            listingsToShow = &approvedListings;
            break;
        }
        else if (choice1 == 3) {
            cout << "Returning to the main menu...\n";
            return;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
            cout << "Enter your choice: ";
            cin >> choice1;
        }
    }

     // convert map to vector
    vector<Property> listingsVec;
    for (const auto& pair : *listingsToShow) {
        listingsVec.push_back(pair.second);
    }
    sort(listingsVec.begin(), listingsVec.end(), compareHighlighted);

    
        cout << "\n======================================================== Property Listings =======================================================\n";

    cout << left
        << setw(5) << "HL"
        << setw(7) << "ID"
        << setw(20) << "Title"
        << setw(13) << "Type"
        << setw(15) << "Location"
        << setw(13) << "Price"
        << setw(16) << "Owner"
        << setw(10) << "Bedrooms"
        << setw(12) << "Bathrooms"
        << setw(10) << "Area"
        << setw(15) << "Status" << endl;

       cout <<   "----------------------------------------------------------------------------------------------------------------------------------\n";


    for (Property& p : listingsVec) {
        cout << setw(5) << (p.isHighlighted() ? "*" : "")
            << setw(7) << p.getId()
            << setw(20) << p.getTitle()
            << setw(13) << p.getType()
            << setw(15) << p.getLocation()
            << setw(13) << p.getPrice()
            << setw(16) << p.getOwnerName()
            << setw(10) << p.getBedrooms()
            << setw(12) << p.getBathrooms()
            << setw(10) << p.getArea()
            << setw(15) << (p.getStatus() == Approved ? "Approved" : (p.getStatus() == Pending ? "Pending" : "Rejected"))
            << endl;
    }

    if (listingsVec.empty()) {
        cout << "No properties listed yet.\n";
    }
      cout <<   "==================================================================================================================================\n";

}


void adminDashboard() {
    int choice;
    do {
        cout << "\n--- Admin Dashboard ---\n";
        cout << "1. Add Property Listing\n";
        cout << "2. Edit Property Listing\n";
        cout << "3. Remove Property Listing\n";
        cout << "4. Toggle Highlight Property\n";
        cout << "5. Show All Listings\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addProperty(); break;
        case 2: editProperty(); break;
        case 3: removeProperty(); break;
        case 4: toggleHighlightProperty(); break;
        case 5: showAllProperties(); break;
        case 6: cout << "Exiting Dashboard...\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);
}

int main() {
    loadListings();
    adminDashboard();
    return 0;
}
