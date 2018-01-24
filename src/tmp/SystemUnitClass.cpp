#include "SystemUnitClass.h"
#include "InternalElement.h"

SystemUnitClass::SystemUnitClass() {
    supportedRoleClass = new SupportedRoleClass();
}
SystemUnitClass::SystemUnitClass(std::string name) {
    supportedRoleClass = new SupportedRoleClass();
    setName(name);
}
SystemUnitClass::SystemUnitClass(std::string name, std::string refbaseclasspath) {
    supportedRoleClass = new SupportedRoleClass();
    setName(name);
    setRefBaseClassPath(refbaseclasspath);
}

std::string SystemUnitClass::getName() {
    return CommonElement::getName();
}
void SystemUnitClass::setName(std::string name) {
    CommonElement::setName(name);
}
std::string SystemUnitClass::getRefBaseClassPath() {
    return refBaseClassPath;
}
void SystemUnitClass::setRefBaseClassPath(std::string refbaseclasspath) {
    refBaseClassPath = refbaseclasspath;
}
SupportedRoleClass* SystemUnitClass::getSupportedRoleClass() {
    return supportedRoleClass;
}
void SystemUnitClass::setSupportedRoleClass(SupportedRoleClass* supportedroleclass) {
    supportedRoleClass = supportedroleclass;
}
std::vector<Attribute*> SystemUnitClass::getAttribute() {
    return attribute;
}
void SystemUnitClass::setAttribute(std::vector<Attribute*> att) {
    attribute = att;
}
std::vector<InternalElement*> SystemUnitClass::getInternalElement() {
    return internalElement;
}
void SystemUnitClass::setInternalElement(std::vector<InternalElement*> internalelement) {
    internalElement = internalelement;
}

InternalElement* SystemUnitClass::addInternalElement(std::string name) {
    InternalElement* newie = new InternalElement(name);
    internalElement.push_back(newie);

    return newie;
}
InternalElement* SystemUnitClass::addInternalElement(std::string name, SystemUnitClass* suc, std::string refbasesystemunitpath) {
    InternalElement* newie = new InternalElement(name);

    for (Attribute* att : suc->getAttribute()) {
        newie->getAttribute().push_back(att->copyAttribute());
    }

    newie->setRefBaseSystemUnitPath(refbasesystemunitpath);
    newie->setSupportedRoleClass(suc->getSupportedRoleClass());
    
    internalElement.push_back(newie);
    
    return newie;
}

InternalElement* SystemUnitClass::searchInternalElement(std::string name) {
    for (InternalElement* ie : internalElement) {
        if (name.compare(ie->getName()) == 0) {
            return ie;
        }
    }
    return nullptr;
}
Attribute* SystemUnitClass::searchAttribute(std::string name) {
    for (Attribute* att : attribute) {
        if (name.compare(att->getName()) == 0) {
            return att;
        }
    }
    return nullptr;
}