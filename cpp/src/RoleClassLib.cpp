#include "RoleClassLib.h"

RoleClassLib::RoleClassLib() {}
RoleClassLib::RoleClassLib(std::string name) {
    setName(name);
}
RoleClassLib::RoleClassLib(std::string name, std::string version) {
    setName(name);
    setVersion(version);
}

std::string RoleClassLib::getName() {
    return CommonElement::getName();
}
void RoleClassLib::setName(std::string name) {
    CommonElement::setName(name);
}
std::string RoleClassLib::getDescription() {
    return description;
}
void RoleClassLib::setDescription(std::string des) {
    description = des;
}
std::string RoleClassLib::getVersion() {
    return version;
}
void RoleClassLib::setVersion(std::string ver) {
    version = ver;
}
std::vector<RoleClass*> RoleClassLib::getRoleClass() {
    return roleClass;
}
void RoleClassLib::setRoleClass(std::vector<RoleClass*> roleclass) {
    roleClass = roleclass;
}

RoleClass* RoleClassLib::addRoleClass(std::string name) {
    RoleClass* newrc = new RoleClass(name);
    roleClass.push_back(newrc);

    return newrc;
}
RoleClass* RoleClassLib::addRoleClass(std::string name, std::vector<Attribute*> attribute) {
    RoleClass* newrc = new RoleClass(name);
    newrc->setAttribute(attribute);
    roleClass.push_back(newrc);

    return newrc;
}

RoleClass* RoleClassLib::searchRoleClass(std::string name) {
    for (RoleClass* rc : roleClass) {
        if (name.compare(rc->getName()) == 0) {
            return rc;
        }
    }
    return nullptr;
}