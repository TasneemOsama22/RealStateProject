#include <iostream>
#include "FileHandler.h"
#include "User.h"
#include "Property.h"
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    unordered_map<string, User> users;
    vector<Property> properties;
    try {
        
        FileHandler::loadUsers(users, "../users.txt");
        FileHandler::loadProperties(properties, "../properties.txt");

        
        FileHandler::saveUsers(users, "../users.txt");
        cout << "Users saved to users.txt\n";


            properties.emplace_back("P001", "Beach Villa", 2500000, "Malibu", "admin");
            properties.emplace_back("P002", "City Apartment", 1200000, "New York", "superadmin");
            properties.emplace_back("P003", "Mountain Cabin", 750000, "Aspen", "admin");
          
            cout << "Default properties added\n";
        

        
        FileHandler::saveProperties(properties, "../properties.txt");
        cout << "Properties saved to properties.txt\n";

    }
    catch (const exception& e) {
        cerr << "[Main Error] " << e.what() << endl;
        return 1;
    }

    return 0;
}
