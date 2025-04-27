#include "search.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;
vector<Property>search:: searchProperties(const vector<Property>& properties, const string& location = "", double lowerPrice = 0, double higherPrice = 1000000000, const string& type = "") {
    vector<Property> Result;

    for (auto& property : properties) {
        bool found = true;

        if (!location.empty() && property.getLocation() != location) {
            found = false;
        }
        if (property.getPrice() < lowerPrice || property.getPrice() > higherPrice) {
            found = false;
        }
        if (!type.empty() && property.getType() != type) {
            found = false;
        }

        if (found == true) {
            Result.push_back(property);
        }
        else {
            cout << "Not Found!" << endl;
        }
    }
    return Result;
}
vector<Property>search::searchByLocation(const vector<Property>& properties, const string& location = "") {
    vector<Property> locationResult;
    for (auto& property : properties) {
        bool found = true;

        if (!location.empty() && property.getLocation() != location) {
            found = false;
        }
        if (found == true) {
            locationResult.push_back(property);
        }
        else {
            cout << "Not Found Location Like This!" << endl;
        }
    }
    return locationResult;
}
vector<Property>search::searchByPrices(const vector<Property>& properties, double lowerPrice = 0, double higherPrice = 1000000000) {
    vector<Property> PriceResult;
    for (auto& property : properties) {
        bool found = true;
        if (property.getPrice() < lowerPrice || property.getPrice() > higherPrice) {
            found = false;
        }
        if (found == true) {
            PriceResult.push_back(property);
        }
        else {
            cout << "Not Found Properties Match your Price Search!" << endl;
        }
    }
    return PriceResult;
}
vector<Property>search::searchByType(const vector<Property>& properties, const string& type = "") {
    vector<Property> TypeResult;

    for (auto& property : properties) {
        bool found = true;
        if (!type.empty() && property.getType() != type) {
            found = false;
        }

        if (found == true) {
            TypeResult.push_back(property);
        }
        else {
            cout << "Not Found This Type Of Properties!" << endl;
        }
    }
    return TypeResult;
}
