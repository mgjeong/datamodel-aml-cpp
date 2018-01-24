#pragma once

#include <string>

class SupportedRoleClass {
private:
    std::string refRoleClassPath;
public:
    std::string getRefRoleClassPath();
    void setRefRoleClassPath(std::string refRoleClassPath);
};