#include "AMLModel.h"

AMLModel::AMLModel() {
    roleClassLib = new RoleClassLib();
    systemUnitClassLib = new SystemUnitClassLib();
}
AMLModel::AMLModel(std::string name) {
    roleClassLib = new RoleClassLib();
    systemUnitClassLib = new SystemUnitClassLib(); 
    setName(name);
}

std::string AMLModel::getName() {
    return CommonElement::getName();
}
void AMLModel::setName(std::string name) {
    CommonElement::setName(name);
}
RoleClassLib* AMLModel::getRoleClassLib() {
    return roleClassLib;
}
void AMLModel::setRoleClassLib(RoleClassLib* roleclasslib) {
    roleClassLib = roleclasslib;
}
SystemUnitClassLib* AMLModel::getSystemUnitClassLib() {
    return systemUnitClassLib;
}
void AMLModel::setSystemUnitClassLib(SystemUnitClassLib* systemunitclasslib) {
    systemUnitClassLib = systemunitclasslib;
}