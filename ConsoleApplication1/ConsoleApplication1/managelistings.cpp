#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Property.h"

using namespace std;


vector<Property> approvedProperties;
vector<Property> pendingProperties;
vector<Property> rejectedProperties;


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



int generateNewId() {
    int maxId = 1000;

    for (const Property& p : approvedProperties)
        maxId = max(maxId, p.getId());
    for (const Property& p : pendingProperties)
        maxId = max(maxId, p.getId());
    for (const Property& p : rejectedProperties)
        maxId = max(maxId, p.getId());

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

        switch (p.getStatus()) {
        case Approved: approvedProperties.push_back(p); break;
        case Pending: pendingProperties.push_back(p); break;
        case Rejected: rejectedProperties.push_back(p); break;
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

    for (const Property& p : approvedProperties)
        file << p.toFileString() << endl;
    for (const Property& p : pendingProperties)
        file << p.toFileString() << endl;
    for (const Property& p : rejectedProperties)
        file << p.toFileString() << endl;

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
    do {
        cout << "Enter Price: ";
        cin >> price;
        if (price < 0)
            cout << "Price cannot be negative. Try again.\n";
    } while (price < 0);
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
    do {
        cout << "Enter Area (Square meter): ";
        cin >> area;
        if (area < 0)
            cout << "Area cannot be negative. Try again.\n";
    } while (area < 0);
    p.setArea(area);

    int bedrooms;
    do {
        cout << "Enter Number of Bedrooms: ";
        cin >> bedrooms;
        if (bedrooms < 0)
            cout << "Bedrooms cannot be negative. Try again.\n";
    } while (bedrooms < 0);
    p.setBedrooms(bedrooms);

    int bathrooms;
    do {
        cout << "Enter Number of Bathrooms: ";
        cin >> bathrooms;
        if (bathrooms < 0)
            cout << "Bathrooms cannot be negative. Try again.\n";
    } while (bathrooms < 0);
    p.setBathrooms(bathrooms);

    int isHighlighted;
    do {
        cout << "Highlight this property? (1: Yes, 0: No): ";
        cin >> isHighlighted;
        if (isHighlighted != 0 && isHighlighted != 1)
            cout << "Invalid input. Please enter 1 (Yes) or 0 (No).\n";
    } while (isHighlighted != 0 && isHighlighted != 1);
    p.setHighlighted(isHighlighted == 1);

    p.setStatus(Pending);
    pendingProperties.push_back(p);

    saveListings();

    cout << "\nProperty added successfully! ID: " << p.getId() << "\n";
}

void editProperty() {
    vector<Property>* selectedList = nullptr;
    int choice1;
    cout << "\n--- Edit Property ---\n";

    while (true) {
        cout << "\nChoose the property list to edit from:\n";
        cout << "1. Approved\n";
        cout << "2. Pending\n";
        cout << "3. Rejected\n";
        cout << "Enter your choice: ";
        cin >> choice1;

        if (choice1 == 1) {
            selectedList = &approvedProperties;
            break;
        }
        else if (choice1 == 2) {
            selectedList = &pendingProperties;
            break;
        }
        else if (choice1 == 3) {
            selectedList = &rejectedProperties;
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    cout << "Enter the ID of the property to edit: ";
    int id;
    cin >> id;

    for (size_t i = 0; i < selectedList->size(); ++i) {
        if ((*selectedList)[i].getId() == id) {
            Property& p = (*selectedList)[i];
            cout << "Editing property with ID " << p.getId() << ":\n";

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
                    do {
                        cout << "Enter new Price: ";
                        cin >> newPrice;
                        if (newPrice < 0)
                            cout << "Price cannot be negative. Please enter a valid price.\n";
                    } while (newPrice < 0);
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
                    do {
                        cout << "Enter new Area (Square meter): ";
                        cin >> newArea;
                        if (newArea < 0)
                            cout << "Area cannot be negative. Please enter a valid area.\n";
                    } while (newArea < 0);
                    p.setArea(newArea);
                    break;
                }
                case 7: {
                    int newBedrooms;
                    do {
                        cout << "Enter new Bedrooms: ";
                        cin >> newBedrooms;
                        if (newBedrooms < 0)
                            cout << "Bedrooms cannot be negative. Please enter a valid number.\n";
                    } while (newBedrooms < 0);
                    p.setBedrooms(newBedrooms);
                    break;
                }
                case 8: {
                    int newBathrooms;
                    do {
                        cout << "Enter new Bathrooms: ";
                        cin >> newBathrooms;
                        if (newBathrooms < 0)
                            cout << "Bathrooms cannot be negative. Please enter a valid number.\n";
                    } while (newBathrooms < 0);
                    p.setBathrooms(newBathrooms);
                    break;
                }
                case 9: {
                    int newStatus;
                    do {
                        cout << "Enter new Status (0: Pending, 1: Approved, 2: Rejected): ";
                        cin >> newStatus;
                        if (newStatus < 0 || newStatus > 2)
                            cout << "Invalid status. Please enter 0, 1, or 2.\n";
                    } while (newStatus < 0 || newStatus > 2);

                    if (newStatus != p.getStatus()) {
                        Property updated = p;
                        updated.setStatus(static_cast<PropertyStatus>(newStatus));

                        switch (newStatus) {
                        case Approved: approvedProperties.push_back(updated); break;
                        case Pending: pendingProperties.push_back(updated); break;
                        case Rejected: rejectedProperties.push_back(updated); break;
                        }

                        selectedList->erase(selectedList->begin() + i);

                        cout << "Property moved to new list and updated.\n";
                        saveListings();
                        return;
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
            return;
        }
    }
    cout << "Property not found.\n";
}


void removeProperty() {
        vector<Property>* selectedList = nullptr;
        int choice;

        cout << "\n--- Remove Property ---\n";

        while (true) {
            cout << "Select the list to remove from:\n";
            cout << "1. Approved Properties\n";
            cout << "2. Pending Properties\n";
            cout << "3. Rejected Properties\n";
            cout << "4. Back\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                selectedList = &approvedProperties;
                break;
            }
            else if (choice == 2) {
                selectedList = &pendingProperties;
                break;
            }
            else if (choice == 3) {
                selectedList = &rejectedProperties;
                break;
            }
            else if (choice == 4) {
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

        bool found = false;
        for (auto it = selectedList->begin(); it != selectedList->end(); ++it) {
            if (it->getId() == id) {
                selectedList->erase(it);
                found = true;
                break;
            }
        }

        if (found) {
            saveListings();
            cout << "Property removed successfully.\n";
        }
        else {
            cout << "Property not found in the selected list.\n";
        }
    }

bool compareHighlighted(Property& a, Property& b) {
    return a.isHighlighted() > b.isHighlighted();
}

void toggleHighlightProperty() {
    vector<Property>* selectedList = nullptr;
    int choice;

    cout << "\n--- Toggle Highlight ---\n";

    while (true) {
        cout << "Select the list to toggle highlight from:\n";
        cout << "1. Approved Properties\n";
        cout << "2. Pending Properties\n";
        cout << "3. Rejected Properties\n";
        cout << "4. Back\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            selectedList = &approvedProperties;
            break;
        }
        else if (choice == 2) {
            selectedList = &pendingProperties;
            break;
        }
        else if (choice == 3) {
            selectedList = &rejectedProperties;
            break;
        }
        else if (choice == 4) {
            cout << "Returning to main menu...\n";
            return;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    int id;
    cout << "Enter Property ID: ";
    cin >> id;

    for (Property& p : *selectedList) {
        if (p.getId() == id) {
            p.setHighlighted(!p.isHighlighted());
            cout << "Highlight status toggled successfully "<< ".\n";
            saveListings();
            return;
        }
    }

    cout << "Property not found in the selected list.\n";
}

void showAllProperties() {
    cout << fixed << setprecision(2);

    vector<Property>* listingsToShow = nullptr;

    while (true) {
        int choice;
        cout << "\nChoose which listings to display:\n";
        cout << "1. Approved Listings\n";
        cout << "2. Pending Listings\n";
        cout << "3. Rejected Listings\n";
        cout << "4. Show All Listings\n";  
        cout << "5. Back\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            listingsToShow = &approvedProperties;
            break;
        }
        else if (choice == 2) {
            listingsToShow = &pendingProperties;
            break;
        }
        else if (choice == 3) {
            listingsToShow = &rejectedProperties;
            break;
        }
        else if (choice == 4) {
           
            vector<Property> combinedListings;
            combinedListings.insert(combinedListings.end(), approvedProperties.begin(), approvedProperties.end());
            combinedListings.insert(combinedListings.end(), pendingProperties.begin(), pendingProperties.end());
            combinedListings.insert(combinedListings.end(), rejectedProperties.begin(), rejectedProperties.end());

          
            sort(combinedListings.begin(), combinedListings.end(), compareHighlighted);

            
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

            cout << "----------------------------------------------------------------------------------------------------------------------------------\n";

            for (Property& p : combinedListings) {
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

            if (combinedListings.empty()) {
                cout << "No properties listed yet.\n";
            }
            cout << "==================================================================================================================================\n";
            return;
        }
        else if (choice == 5) {
            cout << "Returning to the main menu...\n";
            return;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

   
    sort(listingsToShow->begin(), listingsToShow->end(), compareHighlighted);

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

    cout << "----------------------------------------------------------------------------------------------------------------------------------\n";

    for (Property& p : *listingsToShow) {
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

    if (listingsToShow->empty()) {
        cout << "No properties listed yet.\n";
    }

    cout << "==================================================================================================================================\n";
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
