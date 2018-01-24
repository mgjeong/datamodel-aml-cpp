#include "AMLObject.h"

AMLObject::AMLObject() {
    instanceHierarchy = new InstanceHierarchy();
}
AMLObject::AMLObject(std::string name) {
    instanceHierarchy = new InstanceHierarchy(); 
    setName(name);
}

std::string AMLObject::getName() {
    return CommonElement::getName();
}
void AMLObject::setName(std::string name) {
    CommonElement::setName(name);
}
class::InstanceHierarchy* AMLObject::getInstanceHierarchy() {
    return instanceHierarchy;
}
void AMLObject::setInstanceHierarchy(class::InstanceHierarchy* instancehierarchy) {
    instanceHierarchy = instancehierarchy;
}