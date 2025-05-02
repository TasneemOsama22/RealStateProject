#include"Admindashboard.h"
#include<iostream>
#include<fstream>
using namespace std;


void writeAdminstofile() {

	ifstream checkfile;
	checkfile.open("Adminsfile.txt");

	if (checkfile.is_open()) {

		string data;

		if (getline(checkfile, data)) {

			return;

		}
		checkfile.close();
	}

	ofstream myfile;
	myfile.open("Adminsfile.txt");

	if (myfile.is_open()) {

		myfile << "Habibakhaled,2912006," << endl;
		myfile << "Habibabasel,01234h" << endl;
		myfile << "Tasneemmohamed,01234t" << endl;
		myfile << "Basmalaahmed,01234b" << endl;
		myfile << "Alaamohamed,01234a" << endl;
		myfile << "Aytenabdelrahman,01234ay" << endl;
		myfile << "Omniamustafa,01234o" << endl;
		myfile << "Dohaayman,01234d" << endl;

		myfile.close();
	}
}

void loadAdminsfromfile(unordered_map<string, string>& Admins) {

	ifstream input;
	input.open("Adminsfile.txt");
	string line;

	while (getline(input, line)) {

		size_t separate = line.find(',');

		if (separate != string::npos) {

			string username = line.substr(0, separate);
			string password = line.substr(separate + 1);

			Admins[password] = username;
		}
	}
	input.close();
}

bool checkisadmin(string& username, string& password, unordered_map<string, string>& Admins) {

	auto adminsdata = Admins.find(password);
	return adminsdata != Admins.end() && adminsdata->second == username;

}


void savedAdmenstofile(unordered_map<string, string>& Admins) {

	ofstream file;
	file.open("Adminsfile.txt");

	if (file.is_open()) {
		for (auto add : Admins) {
			file << add.second << "," << add.first << endl;
		}
		file.close();
	}
	else {
		cout << "Failed to open file for writing. please try again!" << endl;
	}

}


void AddnewAdmin(unordered_map<string, string>& Admins) {

	string username, password;

	cout << "Enter new username:" << endl;
	getline(cin, username);
	cout << "Enter new password:" << endl;
	getline(cin, password);

	Admins[password] = username;
	savedAdmenstofile(Admins);
	cout << "New admin added successfuly." << endl;
}

void RemoveAdmin(unordered_map<string, string>& Admins) {
	string password;
	cout << "Enter password of the admin to remove:" << endl;
	getline(cin, password);

	auto removepass = Admins.find(password);
	if (removepass != Admins.end()) {
		Admins.erase(removepass);
		savedAdmenstofile(Admins);
		cout << "Admin removed successfuly.\n" << endl;
		showAdminDashboard(Admins);
	}
	else {
		cout << "Not found admin has that password!" << endl;
	}
}


void Addproperty() {
	cout << "add\n" << endl;
}

void Editproperty() {
	cout << "edit\n" << endl;
}

void Removeproperty() {
	cout << "remove\n" << endl;
}

void Highlightproperty() {
	cout << "highlight\n" << endl;
}

void Manage() {
	cout << "manage\n" << endl;
}


void showAdminDashboard(unordered_map<string,string>& Admins){

	int choice;
	while (true) {
		cout << "Admin Dashboard" << endl;
		cout << "--------------------------" << endl;
		cout << "1. Add New property" << endl;
		cout << "2. Edit property" << endl;
		cout << "3. Remove property" << endl;
		cout << "4. Highlight specific property" << endl;
		cout << "5. manage user accounts" << endl;
		cout << "6. Add new admin" << endl;
		cout << "7. Remove admin" << endl;
		cout << "8. Exit" << endl;
		cout << "--------------------------" << endl;
		cout << "Enter your choice :" << endl;

		cin >> choice;
		cout << endl; 
	    cin.ignore();

		switch (choice)
		{
		case 1:
			cout << "Add new property:-" << endl;
			addproperty();
			break;
		case 2:
			cout << "Edit property:-" << endl;
			editproperty();
			break;
		case 3:
			cout << "Remove property:- " << endl;
			remove();
			break;
		case 4:
			cout << "Highlight property:- " << endl;
			highlight();
			break;
		case 5:
			cout << "Manage user account:- " << endl;
			manage();
			break;
		case 6:
			cout << "Add new admin:-" << endl;
			AddnewAdmin(Admins);
			break;
		case 7:
			cout << "Remove Admin:-" << endl;
			RemoveAdmin(Admins);
		case 8:
			cout << "Logging out... " << endl;
			return;
		default:
			cout << "Invalid choice,please enter choice from 1 to 8." << endl;

		}
	}
}