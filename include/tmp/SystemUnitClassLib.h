#pragma once
#include <string>
#include <vector>

#include "CommonElement.h"
#include "SystemUnitClass.h"

class SystemUnitClassLib
    : public CommonElement {
private:
    std::string version;
    std::vector<SystemUnitClass*> systemUnitClass;
    
public:
    SystemUnitClassLib();
    SystemUnitClassLib(std::string name);
    SystemUnitClassLib(std::string name, std::string version);

    std::string getName();
    void setName(std::string name);
    std::string getVersion();
    void setVersion(std::string version); 
    std::vector<SystemUnitClass*> getSystemUnitClass();
    void setSystemUnitClass(std::vector<SystemUnitClass*> systemUnitClass);

    SystemUnitClass* addSystemUnitClass(std::string name);
    SystemUnitClass* addSystemUnitClass(std::string name, std::vector<Attribute*> attribute);

    SystemUnitClass* searchSystemUnitClass(std::string name);
};
