#include<iostream>

#include "InternalElement.h"
#include "SystemUnitClassLib.h"
#include "SystemUnitClass.h"


InternalElement::InternalElement() {
    supportedRoleClass = new SupportedRoleClass();
}
InternalElement::InternalElement(std::string name) {
    supportedRoleClass = new SupportedRoleClass(); 
    setName(name);
}

std::string InternalElement::getName() {
    return CommonElement::getName();
}
void InternalElement::setName(std::string name) {
    CommonElement::setName(name);
}
std::string InternalElement::getRefBaseSystemUnitPath() {
    return refBaseSystemUnitPath;
}
void InternalElement::setRefBaseSystemUnitPath(std::string refbasesystemunitpath) {
    refBaseSystemUnitPath = refbasesystemunitpath;
}
std::vector<Attribute*> InternalElement::getAttribute() {
    return attribute;
}
void InternalElement::setAttribute(std::vector<Attribute*> att) {
    attribute = att;
}
SupportedRoleClass* InternalElement::getSupportedRoleClass() {
    return supportedRoleClass;
}
void InternalElement::setSupportedRoleClass(SupportedRoleClass* supportedroleclass) {
    supportedRoleClass = supportedroleclass;
}
std::vector<InternalElement*> InternalElement::getInternalElement() {
    return subInternalElement;
}
void InternalElement::setInternalElement(std::vector<InternalElement*> internalelement) {
    subInternalElement = internalelement;
}

InternalElement* InternalElement::searchInternalElement(std::string name) {
    for (InternalElement* ie : subInternalElement) {
        if (name.compare(ie->getName()) == 0) {
            return ie;
        }
    }
    return nullptr;
}
Attribute* InternalElement::searchAttribute(std::string name) {
    for (Attribute* att : attribute) {
        if (name.compare(att->getName()) == 0) {
            return att;
        }
    }
    return nullptr;
}

void InternalElement::setAttributeValue(std::string name, std::string value) {
    Attribute* att = searchAttribute(name);

    if (att == nullptr) {
        std::cout << "Not matching attribute name" << std::endl;
        return;
    }
    att->setValue(value);
}
std::string InternalElement::getAttributeValue(std::string name) {
    Attribute* att = searchAttribute(name);

    if (att == nullptr) {
        std::cout << "Not matching attribute name" << std::endl;
        return nullptr;
    }
    return att->getValue();
}

InternalElement* InternalElement::addSubInternalElement(std::string name) {
    InternalElement* newie = new InternalElement(name);
    subInternalElement.push_back(newie);

    return newie;
}
InternalElement* InternalElement::addSubInternalElement(std::string name, SystemUnitClassLib* suc_lib, std::string suc_name) {
    InternalElement* newie = new InternalElement(name);
    SystemUnitClass* suc = suc_lib->searchSystemUnitClass(suc_name);

    for (Attribute* att : suc->getAttribute()) {
        newie->getAttribute().push_back(att->copyAttribute());
    }
    newie->setRefBaseSystemUnitPath(suc_lib->getName() + "/" + suc_name);
    newie->setSupportedRoleClass(suc->getSupportedRoleClass());

    subInternalElement.push_back(newie);
    
    return newie;
}
InternalElement* InternalElement::addSubInternalElement(std::string name, SystemUnitClass* suc, std::string refBaseSystemUnitPath) {
    InternalElement* newie = new InternalElement(name);

    for (Attribute* att : suc->getAttribute()) {
        newie->getAttribute().push_back(att->copyAttribute());
    }
    newie->setRefBaseSystemUnitPath(refBaseSystemUnitPath);
    newie->setSupportedRoleClass(suc->getSupportedRoleClass());

    subInternalElement.push_back(newie);

    return newie;
}