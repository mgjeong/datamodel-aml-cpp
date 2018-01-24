#pragma once

#include <string>
#include <vector>

#include "CommonElement.h"
#include "Attribute.h"
#include "SupportedRoleClass.h"


class SystemUnitClassLib;
class SystemUnitClass;

class InternalElement
    : public CommonElement {

private:
    std::string refBaseSystemUnitPath;
    SupportedRoleClass* supportedRoleClass;
    std::vector<Attribute*> attribute;
    std::vector<InternalElement*> subInternalElement;

public:
    InternalElement();
    InternalElement(std::string name);

    std::string getName();
    void setName(std::string name);
    std::string getRefBaseSystemUnitPath();
    void setRefBaseSystemUnitPath(std::string refBaseSystemUnitPath);
    std::vector<Attribute*> getAttribute();
    void setAttribute(std::vector<Attribute*> attribute);
    SupportedRoleClass* getSupportedRoleClass();
    void setSupportedRoleClass(SupportedRoleClass* supportedRoleClass);
    std::vector<InternalElement*> getInternalElement();
    void setInternalElement(std::vector<InternalElement*> internalElement);

    InternalElement* searchInternalElement(std::string name);
    Attribute* searchAttribute(std::string name);

    void setAttributeValue(std::string name, std::string value);
    std::string getAttributeValue(std::string name);

    InternalElement* addSubInternalElement(std::string name);
    InternalElement* addSubInternalElement(std::string name, SystemUnitClassLib* suc_lib, std::string suc_name);
    InternalElement* addSubInternalElement(std::string name, SystemUnitClass* suc, std::string refBaseSystemUnitPath);
};
