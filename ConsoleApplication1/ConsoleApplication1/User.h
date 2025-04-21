#pragma once
#include <string>
using namespace std;
class User
{
public:
	string username;
	string password;
	bool isAdmin;//flag to check if its admin or regular user
	User() = default;
	User(const string& u, const string& p, bool a) : username(u), password(p), isAdmin(a) {}
	string toFileString() const; //for the user files
	void fromFileString(const string& line);
	bool checkPassword(const string& inputPassword) const;
};

