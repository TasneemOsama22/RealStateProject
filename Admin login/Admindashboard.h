#pragma once
#include<unordered_map>
#include<string>
using namespace std;


void writeAdminstofile();

void loadAdminsfromfile(unordered_map<string, string>& Admins);

bool checkisadmin(string& username, string& password, unordered_map<string, string>& Admins);

void AddnewAdmin(unordered_map<string, string>& Admins);

void RemoveAdmin(unordered_map<string, string>& Admins);

void savedAdmenstofile(unordered_map<string, string>& Admins);

void Addproperty();

void Editproperty();

void Removeproperty();

void Highlightproperty();

void Manage();

void showAdminDashboard(unordered_map<string, string>& Admins);
