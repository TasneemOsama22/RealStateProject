#pragma once
#include <string>
using namespace std;
class Account
{
private:
	string name;
	string email;
	string password;
	string type;
public:
	Account();
	Account(string name, string email, string password, string type);

	string getName() const;
	string getEmail() const;
	string getPassword() const;
	string getType() const;

	void displayProfile() const;


};

