#pragma once
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "User.h"
#include "Property.h"
using namespace std;
class FileHandler
{
public:
    static void saveUsers(unordered_map<string, User>& users, const string& filename);
    static void loadUsers(unordered_map<string, User>& users, const string& filename);

    static void saveProperties(vector<Property>& properties, const string& filename);
    static void loadProperties(vector<Property>& properties, const string& filename);
};

