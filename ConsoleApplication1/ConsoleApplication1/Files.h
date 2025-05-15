#pragma once
#include <unordered_map>
#include <vector>
#include <sstream>
#include "User.h"
#include "Admin.h"
class Files
{
public:
	void loadAccountsFromFile(unordered_map<string, User>& userMap, unordered_map<string, Admin>& adminMap, istream& inFile);
	void storeAccountsToFile(const unordered_map<string, User>& userMap, const unordered_map<string, Admin>& adminMap, ostream& outFile);
	void savePropertiesToFile(const vector<Property>& pending, const vector<Property>& approved,
		const vector<Property>& rejected, const string& filename);
	void loadPropertiesFromFile(vector<Property>& pending, vector<Property>& approved,
		vector<Property>& rejected, const string& filename);
};
