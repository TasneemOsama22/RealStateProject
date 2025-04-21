#pragma once
#include <string>

class Login {
public:
    bool loginUser();

private:
    std::string getMaskedPassword();
};
