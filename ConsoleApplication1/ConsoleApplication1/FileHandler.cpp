#include "FileHandler.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace std;

void FileHandler::saveUsers(unordered_map<string, User>& users, const string& filename)
{
    try {
            ofstream outFile(filename);
            if (!outFile) throw runtime_error("Could not open file to save users");

            for (const auto& pair : users) { //take data (users data) from the map and save it in our file
                outFile << pair.second.toFileString() <<endl;
            }
            outFile.close();
        }
        catch (const exception& e) {
            cerr << "saveUsers Error " << e.what() <<endl;
        }
    }


void FileHandler::loadUsers(unordered_map<string, User>& users, const string& filename)
{
    try {
        ifstream inFile(filename);
        if (!inFile) throw runtime_error("Could not open file to load users");

        string line;
        while (getline(inFile, line)) {
            User u;
            u.fromFileString(line);
            users[u.username] = u;
        }
        inFile.close();
    }
    catch (const exception& e) {
        cerr << "loadUsers Error " << e.what() <<endl;
    }
}

void FileHandler::saveProperties(vector<Property>& properties, const string& filename)
{
    try {
        ofstream outFile(filename);
        if (!outFile) throw runtime_error("Could not open file to save property.");
        for (const auto& var : properties) { //take properties data and save it in our file
            outFile << var.toFileString() << endl;
        }
        outFile.close();
    }
    catch (const exception& e) {
        cerr << "saveProperties Error " << e.what() << endl;
    }
}

void FileHandler::loadProperties(vector<Property>& properties, const string& filename)
{
    try {
        ifstream inFile(filename);
        if (!inFile) throw runtime_error("Could not open file to load Properties");
        string line;
        while (getline(inFile, line)) {
            if (!line.empty()) {
                Property p;
                p.fromFileString(line);  
                properties.push_back(p);

            }
        }
        inFile.close();
    }
    catch (const exception& e) {
        cerr << "loadProperties Error " << e.what() << endl;
    }
}
