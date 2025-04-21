#include "User.h"
#include <sstream>
using namespace std;

string User::toFileString() const{
	return username + "," + password + "," + (isAdmin ? "1" : "0");
}
void User::fromFileString(const string& line) {
	stringstream SS(line);
	getline(SS, username, ',');
	getline(SS, password, ',');
	string adminFlag; //carry 1 or 0
	getline(SS, adminFlag);
	isAdmin = (adminFlag == "1"); //check if its 1 then the isAdmin value is true otherwise its false
}
bool User::checkPassword(const string& p) const {
	return password == p;
 }
