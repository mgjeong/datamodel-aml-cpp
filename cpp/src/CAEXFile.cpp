#include "CAEXFile.h"

CAEXFile::CAEXFile() {
    instanceHierarchy = new InstanceHierarchy();
    roleClassLib = new RoleClassLib();
    systemUnitClassLib = new SystemUnitClassLib();

    setFileName("test.aml");
    setSchemaVersion("2.15");
    setNoNamespace("CAEX_ClassModel_V2.15.xsd");
    setXsi("http://www.w3.org/2001/XMLSchema-instance");
}
CAEXFile::CAEXFile(std::string filename) {
    instanceHierarchy = new InstanceHierarchy();
    roleClassLib = new RoleClassLib();
    systemUnitClassLib = new SystemUnitClassLib();

    setFileName(filename + ".aml");
    setSchemaVersion("2.15");
    setNoNamespace("CAEX_ClassModel_V2.15.xsd");
    setXsi("http://www.w3.org/2001/XMLSchema-instance");
}

std::string CAEXFile::getFileName() {
    return FileName;
}
void CAEXFile::setFileName(std::string fileName) {
    this->FileName = fileName;
}
std::string CAEXFile::getSchemaVersion() {
    return SchemaVersion;
}
void CAEXFile::setSchemaVersion(std::string schemaVersion) {
    this->SchemaVersion = schemaVersion;
}
std::string CAEXFile::getNoNamespace() {
    return noNamespace;
}
void CAEXFile::setNoNamespace(std::string noNamespace) {
    this->noNamespace = noNamespace;
}
std::string CAEXFile::getXsi() {
    return xsi;
}
void CAEXFile::setXsi(std::string xsi) {
    this->xsi = xsi;
}

InstanceHierarchy* CAEXFile::getInstanceHierarchy() {
    return instanceHierarchy;
}
void CAEXFile::setInstanceHierarchy(InstanceHierarchy* instancehierarchy) {
    instanceHierarchy = instancehierarchy;
}
RoleClassLib* CAEXFile::getRoleClassLib() {
    return roleClassLib;
}
void CAEXFile::setRoleClassLib(RoleClassLib* roleclasslib) {
    roleClassLib = roleclasslib;
}
SystemUnitClassLib* CAEXFile::getSystemUnitClassLib() {
    return systemUnitClassLib;
}
void CAEXFile::setSystemUnitClassLib(SystemUnitClassLib* systemunitclasslib) {
    systemUnitClassLib = systemunitclasslib;
}