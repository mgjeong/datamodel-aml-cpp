#pragma once

#include <string>
#include <vector>
#include "CommonElement.h"

class Attribute 
    : public CommonElement {
private:
    std::string attributeDataType;
    std::string description;
    std::string value;
    std::vector<Attribute*> subAttribute;

public:
    Attribute();
    Attribute(std::string name);
    Attribute(std::string name, std::string attributedatatype);
    Attribute(std::string name, std::string attributedatatype, std::string value);
    Attribute(std::string name, std::string attributedatatype, std::string value, std::string description);
    
    std::string getName();
    void setName(std::string name);
    std::string getAttributeDataType();
    void setAttributeDataType(std::string attributedatatype);
    std::string getDescription();
    void setDescription(std::string description);
    std::string getValue();
    void setValue(std::string value);

    std::vector<Attribute*> getAttribute();
    void setAttribute(std::vector<Attribute*> attribute);
    void addSubAttribute(std::string name);
    
    Attribute* searchAttribute(std::string name);
    Attribute* copyAttribute();
};
