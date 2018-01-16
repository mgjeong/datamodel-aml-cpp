#include "CommonElement.h"

CommonElement::CommonElement() {}

std::string CommonElement::getName() {
    return Name;
}

void CommonElement::setName(std::string name) {
    Name = name;
}