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

    std::vector<InstanceHierarchy*> instanceHierarchy;
    std::vector<RoleClassLib*> roleClassLib;
    std::vector<SystemUnitClassLib*> systemUnitClassLib;

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

    std::vector<InstanceHierarchy*> getInstanceHierarchy();
    void setInstanceHierarchy(std::vector<InstanceHierarchy*> instanceHierarchy);
    std::vector<RoleClassLib*> getRoleClassLib();
    void setRoleClassLib(std::vector<RoleClassLib*> roleClassLib);
    std::vector<SystemUnitClassLib*> getSystemUnitClassLib();
    void setSystemUnitClassLib(std::vector<SystemUnitClassLib*> systemUnitClassLib);
};