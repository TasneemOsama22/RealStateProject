#pragma once
#include<vector>
#include <sstream>
#include<string>
#include"Property.h"
class search {
public:
    vector<Property> searchProperties(const vector<Property>& properties, const string& location = "", double lowerPrice = 0, double higherPrice = 1000000000, const string& type = "");

    void sortByPrice(vector<Property>& properties);
    void sortByLocation(vector<Property>& properties);
    void sortByType(vector<Property>& properties);

    void sortByArea(vector<Property>& properties);
    void sortByNumOfBedRooms(vector<Property>& properties);

    vector<Property> binarySearchByLocation(vector<Property>& properties,const string&location);
    vector<Property> binarySearchByPrice(vector<Property>& properties, double targetPrice);
    vector<Property> binarySearchByType(vector<Property>& properties, const string& targetType);

    vector<Property> binarySearchByArea(vector<Property>& properties, double area);
    vector<Property> binarySearchByNumOfBedRooms(vector<Property>& properties, int numOfBedRooms);

    /*vector<Property> searchByLocation(const vector<Property>& properties,const string&location="");
  vector<Property> searchByPrices(const vector<Property>& properties,double lowerPrice=0,double higherPrice=1000000000);
  vector<Property> searchByType(const vector<Property>& properties,const string& type = "");*/


};
