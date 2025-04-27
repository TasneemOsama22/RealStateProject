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

        
        users["admin"] = User("admin", "123", true);
        users["superadmin"] = User("superadmin", "12345", true);

        
        FileHandler::saveUsers(users, "../users.txt");
        cout << "Users saved to users.txt\n";

        
        if (properties.empty()) {
            properties.emplace_back("default001", "Villa", 100000, "City1", "admin");
            properties.emplace_back("default002", "Apartment", 75000.0, "City2", "superadmin");
            cout << "Default properties added\n";
        }

        
        FileHandler::saveProperties(properties, "../properties.txt");
        cout << "Properties saved to properties.txt\n";

    }
    catch (const exception& e) {
        cerr << "[Main Error] " << e.what() << endl;
        return 1;
    }

    return 0;
}
