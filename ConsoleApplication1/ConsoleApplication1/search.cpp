#include "search.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;
vector<Property>search:: searchProperties(const vector<Property>& properties, const string& location = "", double lowerPrice = 0, double higherPrice = 1000000000, const string& type = "") {
    vector<Property> Result;
    bool found = false;
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
            found = true;
        }
    }
    if (!found) {
        cout << "Not Found!"<<endl;
    }
    return Result;
}
vector<Property>search::searchByLocation(const vector<Property>& properties, const string& location = "") {
    vector<Property> locationResult;
    bool found = false;
    for (auto& property : properties) {
        bool searchMatching = true;

        if (!location.empty() && property.getLocation() != location) {
            searchMatching = false;
        }
        if (searchMatching == true) {
            locationResult.push_back(property);
            found = true;
        }
       
    }
    if (!found) {
        cout << "Not Found Location Like This!" << endl;
    }
    return locationResult;
}
vector<Property>search::searchByPrices(const vector<Property>& properties, double lowerPrice = 0, double higherPrice = 1000000000) {
    vector<Property> PriceResult;
    bool found = false;
    for (auto& property : properties) {
        bool searchMatching = true;
        if (property.getPrice() < lowerPrice || property.getPrice() > higherPrice) {
            searchMatching = false;
        }
        if (searchMatching == true) {
            PriceResult.push_back(property);
            found = true;
        }
       
    }
    if (!found) {
        cout << "Not Found Properties Match your Price Search!" << endl;
    }
    return PriceResult;
}
vector<Property>search::searchByType(const vector<Property>& properties, const string& type = "") {
    vector<Property> TypeResult;
    bool found = false;
    for (auto& property : properties) {
        bool searchMatching = true;
        if (!type.empty() && property.getType() != type) {
            searchMatching = false;
        }

        if (searchMatching == true) {
            TypeResult.push_back(property);
            found = true;
        }
        
    }
    if (!found) {
        cout << "Not Found This Type Of Properties!" << endl;
    }
    return TypeResult;
}
