#include "RoleClass.h"

RoleClass::RoleClass() {}
RoleClass::RoleClass(std::string name) {
    setName(name);
}

std::string RoleClass::getName() {
    return CommonElement::getName();
}
void RoleClass::setName(std::string name) {
    CommonElement::setName(name);
}
std::string RoleClass::getDescription() {
    return description;
}
void RoleClass::setDescription(std::string description) {
    description = description;
}
std::string RoleClass::getRefBaseClassPath() {
    return refBaseClassPath;
}
void RoleClass::setRefBaseClassPath(std::string refbaseclasspath) {
    refBaseClassPath = refbaseclasspath;
}
std::vector<Attribute*> RoleClass::getAttribute() {
    return attribute;
}
void RoleClass::setAttribute(std::vector<Attribute*> att) {
    attribute = att;
}

Attribute* RoleClass::searchAttribute(std::string name) {
    for (class::Attribute* att : attribute) {
        if (name.compare(att->getName()) == 0) {
            return att;
        }
    }
}