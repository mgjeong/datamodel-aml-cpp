#pragma once

#include "InstanceHierarchy.h"
#include "RoleClassLib.h"
#include "SystemUnitClassLib.h"

class CAEXFile {
private:
    std::string FileName;
    std::string SchemaVersion;
    std::string noNamespace;
    std::string xsi;

    InstanceHierarchy* instanceHierarchy;
    RoleClassLib* roleClassLib;
    SystemUnitClassLib* systemUnitClassLib;

public:
    CAEXFile();
    CAEXFile(std::string filename);

    std::string getFileName();
    void setFileName(std::string fileName);
    std::string getSchemaVersion();
    void setSchemaVersion(std::string schemaVersion);
    std::string getNoNamespace();
    void setNoNamespace(std::string noNamespace);
    std::string getXsi();
    void setXsi(std::string xsi);

    InstanceHierarchy* getInstanceHierarchy();
    void setInstanceHierarchy(InstanceHierarchy* instanceHierarchy);
    RoleClassLib* getRoleClassLib();
    void setRoleClassLib(RoleClassLib* roleClassLib);
    SystemUnitClassLib* getSystemUnitClassLib();
    void setSystemUnitClassLib(SystemUnitClassLib* systemUnitClassLib);
};