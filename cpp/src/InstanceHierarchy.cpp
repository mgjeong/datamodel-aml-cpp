#include "InstanceHierarchy.h"

InstanceHierarchy::InstanceHierarchy() {}
InstanceHierarchy::InstanceHierarchy(std::string name) {
    setName(name);
}
InstanceHierarchy::InstanceHierarchy(std::string name, std::string version) {
    setName(name);
    setVersion(version);
}

std::string InstanceHierarchy::getName() {
    return CommonElement::getName();
}
void InstanceHierarchy::setName(std::string name) {
    CommonElement::setName(name);
}
std::string InstanceHierarchy::getVersion() {
    return version;
}
void InstanceHierarchy::setVersion(std::string ver) {
    version = ver;
}
std::vector<InternalElement*> InstanceHierarchy::getInternalElement() {
    return internalElement;
}
void InstanceHierarchy::setInternalElement(std::vector<InternalElement*> internalelement) {
    internalElement = internalelement;
}

InternalElement* InstanceHierarchy::addInternalElement(std::string name) {
    InternalElement* newie = new InternalElement(name);
    internalElement.push_back(newie);

    return newie;
}
InternalElement* InstanceHierarchy::addInternalElement(std::string name, SystemUnitClassLib* suc_lib, std::string suc_name) {
    InternalElement* newie = new InternalElement(name);
    SystemUnitClass* suc = suc_lib->searchSystemUnitClass(suc_name);
    
    for (Attribute* att : suc->getAttribute()) {
        newie->getAttribute().push_back(att->copyAttribute());
    }
    newie->setRefBaseSystemUnitPath(suc_lib->getName() + "/" + suc_name);
    internalElement.push_back(newie);

    return newie;
}

InternalElement* InstanceHierarchy::searchInternalElement(std::string name) {
    for (class::InternalElement* ie : internalElement) {
        if (name.compare(ie->getName()) == 0) {
            return ie;
        }
    }
    return nullptr;
}
