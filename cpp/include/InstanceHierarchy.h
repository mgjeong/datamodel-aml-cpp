#pragma once

#include <string>
#include <vector>

#include "CommonElement.h"
#include "InternalElement.h"
#include "SystemUnitClassLib.h"
#include "SystemUnitClass.h"

class InstanceHierarchy
    : public CommonElement {
private:
    std::string version;
    std::vector<InternalElement*> internalElement;

public:
    InstanceHierarchy();
    InstanceHierarchy(std::string name);
    InstanceHierarchy(std::string name, std::string version);

    std::string getName();
    void setName(std::string name);
    std::string getVersion();
    void setVersion(std::string version);
    std::vector<InternalElement*> getInternalElement();
    void setInternalElement(std::vector<InternalElement*> internalElement);

    InternalElement* addInternalElement(std::string name);
    InternalElement* addInternalElement(std::string name, SystemUnitClassLib* suc_lib, std::string suc_name);

    InternalElement* searchInternalElement(std::string name);
};
