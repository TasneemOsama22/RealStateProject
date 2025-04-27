#pragma once
#include<vector>
#include <sstream>
#include<string>
#include"Property.h"
class search {
    vector<Property> searchProperties(const vector<Property>& properties, const string& location = "", double lowerPrice = 0, double higherPrice = 1000000000, const string& type = "");
    vector<Property> searchByLocation(const vector<Property>& properties,const string&location="");
    vector<Property> searchByPrices(const vector<Property>& properties,double lowerPrice=0,double higherPrice=1000000000);
    vector<Property> searchByType(const vector<Property>& properties,const string& type = "");
};
