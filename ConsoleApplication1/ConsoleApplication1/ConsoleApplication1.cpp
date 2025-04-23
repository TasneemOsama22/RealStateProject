#include <iostream>
#include "AccCtrl.h"
#include "Register.h"
#include "Login.h"
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    Register reg;
    Login log;
    int choice;

    do {
        std::cout << "\n1. Register\n2. Login\n0. Exit\nChoose option: ";
        std::cin >> choice;
        std::cin.ignore(); // clear newline from input buffer

        switch (choice) {
        case 1:
            reg.registerUser();
            break;
        case 2:
            log.loginUser();
            break;
        case 0:
            std::cout << "Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}