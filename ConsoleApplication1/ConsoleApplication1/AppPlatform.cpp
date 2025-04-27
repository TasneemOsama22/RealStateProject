#include "UserPlatform.h"
#include<iostream>
#include <sstream>
#include <vector>
#include "AppPlatform.h"
using namespace std;
vector <Property> pendingProp ; //waiting list for admin approval

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
	cin.ignore();

	Property p = new Property(title, price, location, owner, area, bedrooms, bathrooms,Pending);
	pendingProp.push_back(p);

	cout << "Property now is under review, please wait for admin's approval.";
}

AppPlatform::string checkPropertyStatus(const Property& property) {
	switch (property.getStatus()) {
	case Status::Pending:   return "Pending (Under Review)";
	case Status::Approved:  return "Approved";
	case Status::Rejected:  return "Rejected";
	default:                return "Unknown Status";
	}
}