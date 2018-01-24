#pragma once

#include "CommonElement.h"
#include "RoleClassLib.h"
#include "SystemUnitClassLib.h"

class AMLModel
    : public CommonElement {
private:
    RoleClassLib* roleClassLib;
    SystemUnitClassLib* systemUnitClassLib;

public:
    AMLModel();
    AMLModel(std::string name);

    std::string getName();
    void setName(std::string);
    class::RoleClassLib* getRoleClassLib();
    void setRoleClassLib(class::RoleClassLib* roleclasslib);
    class::SystemUnitClassLib* getSystemUnitClassLib();
    void setSystemUnitClassLib(class::SystemUnitClassLib* systemunitclasslib);
};
