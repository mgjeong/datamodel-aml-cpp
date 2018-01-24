#pragma once

#include <string>
#include <vector>

#include "CommonElement.h"
#include "RoleClass.h"

class RoleClassLib
    : public CommonElement {
private:
    std::string description;
    std::string version;
    std::vector<RoleClass*> roleClass;

public:
    RoleClassLib();
    RoleClassLib(std::string name);
    RoleClassLib(std::string name, std::string version);

    std::string getName();
    void setName(std::string name);
    std::string getDescription();
    void setDescription(std::string description);
    std::string getVersion();
    void setVersion(std::string version);
    std::vector<RoleClass*> getRoleClass();
    void setRoleClass(std::vector<RoleClass*> roleClass);

    RoleClass* addRoleClass(std::string name);
    RoleClass* addRoleClass(std::string name, std::vector<Attribute*> attribute);

    RoleClass* searchRoleClass(std::string name);
};