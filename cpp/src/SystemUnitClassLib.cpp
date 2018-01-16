#include "SystemUnitClassLib.h"

SystemUnitClassLib::SystemUnitClassLib() {}
SystemUnitClassLib::SystemUnitClassLib(std::string name) {
    setName(name);
}
SystemUnitClassLib::SystemUnitClassLib(std::string name, std::string version) {
    setName(name);
    setVersion(version);
}

std::string SystemUnitClassLib::getName() {
    return CommonElement::getName();
}
void SystemUnitClassLib::setName(std::string name) {
    CommonElement::setName(name);
}
std::string SystemUnitClassLib::getVersion() {
    return version;
}
void SystemUnitClassLib::setVersion(std::string ver) {
    version = ver;
}
std::vector<SystemUnitClass*> SystemUnitClassLib::getSystemUnitClass() {
    return systemUnitClass;
}
void SystemUnitClassLib::setSystemUnitClass(std::vector<SystemUnitClass*> systemunitclass) {
    systemUnitClass = systemunitclass;
}

SystemUnitClass* SystemUnitClassLib::addSystemUnitClass(std::string name) {
    SystemUnitClass* newsuc = new SystemUnitClass(name);
    systemUnitClass.push_back(newsuc);

    return newsuc;
}
SystemUnitClass* SystemUnitClassLib::addSystemUnitClass(std::string name, std::vector<Attribute*> attribute) {
    SystemUnitClass* newsuc = new SystemUnitClass(name);
    newsuc->setAttribute(attribute);
    systemUnitClass.push_back(newsuc);

    return newsuc;
}

SystemUnitClass* SystemUnitClassLib::searchSystemUnitClass(std::string name) {
    for (SystemUnitClass* suc : systemUnitClass) {
        if (name.compare(suc->getName()) == 0) {
            return suc;
        }
    }
    return nullptr;
}