#include "UserPlatform.h"
#include<iostream>
#include <sstream>
#include <list>
using namespace std;
list <Property> pendingProp; //waiting list for admin approval

void AppPlatform::addProperty(){
	string title, location, owner;
	double price, area;
	int bedrooms, bathrooms;

	cout << "Enter property details:" <<endl;
	cout << "Title: ";
	getline(cin, title);
	cout << "Location: ";
	getline(cin, location);
	cout << "Owner's name: ";
	getline(cin, owner);
	cout << "Area: "; cin >> area;
	cout << "Price: "; cin >> price;
	cout << "Number of bedrooms: "; cin >> bedrooms;
	cout << "Number of bathrooms: "; cin >> bathrooms;

	Property p = new Property(title, price, location, owner, area, bedrooms, bathrooms);
	pendingProp.push_back(p);

	cout << "Property now is under review, please wait for admin's approval.";
}
