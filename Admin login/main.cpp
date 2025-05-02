#include"Admindashboard.h"
#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;



int main() {

	string username, password;
	unordered_map<string, string> Admins;

	writeAdminstofile();
	loadAdminsfromfile(Admins);

	cout << "*********Admin login****** " << endl;

	while (true) {

		cout << "Enter username:" << endl;
		getline(cin, username);

		cout << endl;

		cout << "Enter password:" << endl;
		getline(cin, password);

		if (checkisadmin(username, password, Admins)) {

			cout << "Login successful , welcome " << username << "!\n" << endl;
			showAdminDashboard(Admins);

			break;
		}

		else {
			cout << "Failed login ,wrong username or password! please try again.\n" << endl;
		}
	}

	return 0;
}