#pragma once
#include<vector>
#include<string>
#include"Property.h"
template<class T>
class search {
    vector<Property> searchProperties(const vector<Property>& properties, const string& location = "", double lowerPrice = 0, double higherPrice = 1000000000, const string& type = "");
  
};
