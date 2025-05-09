#include <iostream>
#include <vector>
#include <map>
#include "Adminreport.h"
#include "User.h"
#include "Property.h"

using namespace std;

int main() {

    generateAdminReport(users, approvedProperties, pendingProperties, rejectedProperties);

    return 0;
}
