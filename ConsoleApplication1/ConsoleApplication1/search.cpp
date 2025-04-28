#include "search.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdexcept>
using namespace std;
vector<Property>search:: searchProperties(const vector<Property>& properties, const string& location , double lowerPrice , double higherPrice, const string& type) {
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

void search::sortByPrice(vector<Property>& properties) {
    sort(properties.begin(), properties.end(), [](const Property& a, const Property& b) {
        return a.getPrice() < b.getPrice();});
}

void search::sortByLocation(vector<Property>& properties) {
    sort(properties.begin(), properties.end(), [](const Property& a, const Property& b) {
        return a.getLocation() < b.getLocation();});
}

void search::sortByType(vector<Property>& properties) {
    sort(properties.begin(), properties.end(), [](const Property& a, const Property& b) {
        return a.getType() < b.getType();});
}


vector<Property> search::binarySearchByLocation(vector<Property>& properties, const string& location)
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

vector<Property> search::binarySearchByPrice(vector<Property>& properties, double targetPrice) {
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
vector<Property> search::binarySearchByType(vector<Property>& properties, const string& targetType) {
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
//vector<Property>search::searchByLocation(const vector<Property>& properties, const string& location) {
//    vector<Property> locationResult;
//    bool found = false;
//    for (auto& property : properties) {
//        bool searchMatching = true;
//
//        if (!location.empty() && property.getLocation() != location) {
//            searchMatching = false;
//        }
//        if (searchMatching == true) {
//            locationResult.push_back(property);
//            found = true;
//        }
//       
//    }
//  /*  if (!found) {
//        cout << "Not Found Location Like This!" << endl;
//    }*/
//    return locationResult;
//}
//vector<Property>search::searchByPrices(const vector<Property>& properties, double lowerPrice, double higherPrice) {
//    vector<Property> PriceResult;
//    bool found = false;
//    for (auto& property : properties) {
//        bool searchMatching = true;
//        if (property.getPrice() < lowerPrice || property.getPrice() > higherPrice) {
//            searchMatching = false;
//        }
//        if (searchMatching == true) {
//            PriceResult.push_back(property);
//            found = true;
//        }
//       
//    }
//  /*  if (!found) {
//        cout << "Not Found Properties Match your Price Search!" << endl;
//    }*/
//    return PriceResult;
//}
//vector<Property>search::searchByType(const vector<Property>& properties, const string& type) {
//    vector<Property> TypeResult;
//    bool found = false;
//    for (auto& property : properties) {
//        bool searchMatching = true;
//        if (!type.empty() && property.getType() != type) {
//            searchMatching = false;
//        }
//
//        if (searchMatching == true) {
//            TypeResult.push_back(property);
//            found = true;
//        }
//        
//    }
//   /* if (!found) {
//        cout << "Not Found This Type Of Properties!" << endl;
//    }*/
//    return TypeResult;
//}
