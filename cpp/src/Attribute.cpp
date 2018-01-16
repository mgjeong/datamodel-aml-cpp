#include "Attribute.h"

Attribute::Attribute() {}
Attribute::Attribute(std::string name) {
    setName(name);
}
Attribute::Attribute(std::string name, std::string attributeDataType) {
    setName(name);
    setAttributeDataType(attributeDataType);
}
Attribute::Attribute(std::string name, std::string attributeDataType, std::string value) {
    setName(name);
    setAttributeDataType(attributeDataType);
    setValue(value);
}
Attribute::Attribute(std::string name, std::string attributeDataType, std::string value, std::string description) {
    setName(name);
    setAttributeDataType(attributeDataType);
    setValue(value);
    setDescription(description);
}

std::string Attribute::getName() {
    return CommonElement::getName();
}
void Attribute::setName(std::string name) {
    CommonElement::setName(name);
}

std::string Attribute::getAttributeDataType() {
    return attributeDataType;
}
void Attribute::setAttributeDataType(std::string attributedatatype) {
    attributeDataType = attributedatatype;
}

std::string Attribute::getValue() {
    return value;
}
void Attribute::setValue(std::string val) {
    value = val;
}

std::string Attribute::getDescription() {
    return description;
}
void Attribute::setDescription(std::string des) {
    description = des;
}

std::vector<Attribute*> Attribute::getAttribute() {
    return subAttribute;
}
void Attribute::setAttribute(std::vector<Attribute*> attribute) {
    subAttribute = attribute;
}

void Attribute::addSubAttribute(std::string name) {
    Attribute* newatt = new Attribute(name);
    subAttribute.push_back(newatt);
}
Attribute* Attribute::searchAttribute(std::string name) {
    for (Attribute* att : subAttribute) {
        if (name.compare(att->getName()) == 0) {
            return att;
        }
    }
    return nullptr;
}
Attribute* Attribute::copyAttribute() {
    Attribute* newatt = new Attribute();

    newatt->setName(getName());
    newatt->setAttributeDataType(getAttributeDataType());
    newatt->setValue(getValue());
    newatt->setDescription(getValue());
    
    std::vector<Attribute*> newsubatt;
    for (Attribute* att : subAttribute) {
        newsubatt.push_back(att->copyAttribute());
    }

    return newatt;
}