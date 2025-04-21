#pragma once
#include <string>
using namespace std;
class Register
{
public:
    void registerUser();

private:
    bool isEmailValid(const std::string& email);
    bool isPasswordStrong(const std::string& password);
    std::string detectType();
};


