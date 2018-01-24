#pragma once

#include <string>
#include <vector>

#include "CommonElement.h"
#include "Attribute.h"

class RoleClass
    : public CommonElement {
private:
    std::string description;
    std::string refBaseClassPath;
    std::vector<Attribute*> attribute;

public:
    RoleClass();
    RoleClass(std::string name);

    std::string getName();
    void setName(std::string name);
    std::string getDescription();
    void setDescription(std::string description);
    std::string getRefBaseClassPath();
    void setRefBaseClassPath(std::string refBaseClassPath);
    std::vector<Attribute*> getAttribute();
    void setAttribute(std::vector<Attribute*> attribute);

    Attribute* searchAttribute(std::string name);
};