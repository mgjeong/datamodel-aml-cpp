#pragma once

#include <string>

class CommonElement {
private:
    std::string Name;
public:
    CommonElement();
    std::string getName();
    void setName(std::string name);
};
