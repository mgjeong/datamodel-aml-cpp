#pragma once

#include <string>
#include <vector>

#include "CommonElement.h"
#include "Attribute.h"
#include "SupportedRoleClass.h"

class InternalElement;

class SystemUnitClass
    : public CommonElement {
private:
    std::string refBaseClassPath;
    std::vector<Attribute*> attribute;
    std::vector<InternalElement*> internalElement;
    SupportedRoleClass* supportedRoleClass;

public:
    SystemUnitClass();
    SystemUnitClass(std::string name);
    SystemUnitClass(std::string name, std::string refBaseClassPath);

    std::string getName();
    void setName(std::string name);
    std::string getRefBaseClassPath();
    void setRefBaseClassPath(std::string refBaseClassPath);
    SupportedRoleClass* getSupportedRoleClass();
    void setSupportedRoleClass(SupportedRoleClass* supportedRoleClass);
    std::vector<Attribute*> getAttribute();
    void setAttribute(std::vector<Attribute*> attribute);
    std::vector<InternalElement*> getInternalElement();
    void setInternalElement(std::vector<InternalElement*> internalElement);

    InternalElement* addInternalElement(std::string name);
    InternalElement* addInternalElement(std::string name, SystemUnitClass* suc, std::string refBaseSystemUnitPath);

    InternalElement* searchInternalElement(std::string name);
    Attribute* searchAttribute(std::string name);
};
