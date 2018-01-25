#pragma once

#include <string>

#include "CommonElement.h"
#include "InstanceHierarchy.h"

    class AMLObject
        : public CommonElement {
    private:
        InstanceHierarchy* instanceHierarchy;

    public:
        AMLObject();
        AMLObject(std::string name);

        std::string getName();
        void setName(std::string);
        class::InstanceHierarchy* getInstanceHierarchy();
        void setInstanceHierarchy(class::InstanceHierarchy* instancehierarchy);

    };
